#ifndef CTHREAD_H
#define CTHREAD_H

#ifdef _MSC_VER
//#include "../Common/MessageQueue.h"

#include <iostream>
#include <queue>

#if _MSC_VER <= 1600 || _AFXDLL

#else
#include <mutex>
#include <atomic>
#include <condition_variable>

#endif

using namespace std;



#else
#include <pthread.h>
#include <unistd.h>

#endif

#ifdef __linux__
#include <sys/msg.h>
#include <sys/ipc.h>
#include <regex.h>
#include <semaphore.h>
#elif __VXWORKS__
#include <semaphore.h>

#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "../Include/system.h"
#include "../Anal/INC/System.h"

#include "../Utils/carraymsgdata.h"

#define LENGTH_OF_CLASSNAME (30)

#define THREAD_STANDARD_FUNCTION(A)    \
void Run( key_t key=IPC_PRIVATE ); \
virtual void _routine();    \
virtual char *GetThreadName() { return m_szThreadName; } \
static A* GetInstance() { \
    if(m_pInstance == NULL) { \
        m_pInstance = new A( g_iKeyId++, (char*) #A, true ); \
    } \
    return m_pInstance; } \
static void ReleaseInstance() { \
    if(m_pInstance) { \
        delete m_pInstance; \
        m_pInstance = NULL; \
    } } \
static bool IsThereInstance() { \
    bool bRet = true; \
    if(m_pInstance == NULL) { \
        bRet = false; \
    } \
    return bRet; }

// 오직 CTaskMngr 에서만 사용하는 정의문 입니다.
#define THREAD_STANDARD_FUNCTION_2(A )    \
void Run( key_t key=IPC_PRIVATE ); \
virtual void _routine();    \
virtual const char *GetThreadName() { return m_szThreadName; } \
static A* GetInstance() { \
    if(m_pInstance == NULL) { \
        char szSQLiteFileName[100]; \
        strcpy( szSQLiteFileName, CEDEOB_SQLITE_FOLDER ); \
        strcat( szSQLiteFileName, "/" ); \
        strcat( szSQLiteFileName, CEDEOB_SQLITE_FILENAME ); \
        m_pInstance = new A( g_iKeyId++, (char*) #A, true, (char*) szSQLiteFileName ); \
    } \
    return m_pInstance; } \
static void ReleaseInstance() { \
    if(m_pInstance) { \
        delete m_pInstance; \
        m_pInstance = NULL; \
    } } \
static bool IsThereInstance() { \
    bool bRet = true; \
    if(m_pInstance == NULL) { \
        bRet = false; \
    } \
    return bRet; }


typedef enum {
    enNO_WAIT=0,
    enWAIT_FOREVER,

} ENUM_RCVMSG ;

//#pragma pack(push, 1)


/**
 * @brief 수집 쓰레드 정보
 */
typedef struct {
    int iCh;
    unsigned int uiTotalPDW;

    // 방사체 번호
    unsigned int uiAETID;
    // 빔 번호
    unsigned int uiABTID;


} STR_COLLECTINFO ;

// 수집한 데이터에서 분석한 LOB 헤더 정보
struct STR_ANALINFO {
    ENUM_BoardID enBoardID;
    unsigned int uiTotalLOB;

    // 수집한 채널 정보
    int iCh;

    // 방사체 번호
    unsigned int uiAETID;
    // 빔 번호
    unsigned int uiABTID;

} ;


/**
 * @brief 메시지 데이터 구조체
 */
union UNI_MSG_DATA {
    unsigned int uiData;
    time_t tiNow;

    STR_COLLECTINFO strCollectInfo;
    STR_ANALINFO strAnalInfo;

    char szData[32];
} ;


/**
 * @brief 쓰레드간의 메시지 데이터 구조체 정의
 */
struct STR_MessageData {
#ifdef __linux__
    long mtype;
#endif

    // Opcode
    unsigned int uiOpCode;

    // Src/Dest
    unsigned char ucSrcDest;

    //랜 송신시 이 값이 0 이 아니면 이 소켓 값으로 데이터를 전송한다.
    unsigned int uiSocket;

    // 데이터 길이
    unsigned int uiDataLength;

    // 데이터 영역 이다.
    UNI_MSG_DATA x;

    // CArrayData 클래스 사용시 인덱스 값을 의미함. 0 보다 작은 값은 CArrayData 를 사용하지 않은 것이다.
    int iArrayIndex;
    unsigned int uiArrayLength;

} ;

#if defined(_MSC_VER) || defined(__VXWORKS__)
class CThreadContext
{
public:
	CThreadContext() {
		memset(this, 0, sizeof(this));
	}

	/*
		*	Attributes Section
		*/
public:
	HANDLE m_hThread;					//	The Thread Handle
	DWORD  m_dwTID;						//	The Thread ID
	LPVOID m_pUserData;						//	The user data pointer
	LPVOID m_pParent;					//	The this pointer of the parent CThread object
	DWORD  m_dwExitCode;				//	The Exit Code of the thread
};
#endif

//#pragma pack(pop)

/**
 * @brief The CThread class
 */
class CThread : public CArrayMsgData
{
private:
    

#ifdef _MSC_VER
    CThreadContext m_MainThread;

    LPTHREAD_START_ROUTINE	m_pThreadFunc;	//	The Worker Thread Function Pointer

    HANDLE m_hEvent;
    HANDLE m_hSleepEvent;

    queue<STR_MessageData> m_queue;

#if _MSC_VER <= 1600 || _AFXDLL
	CCriticalSection m_cs;
#else
	std::mutex m_mutex;
#endif

#elif __VXWORKS__
    sem_t m_mutex;

    // 타스크 관련 멤버 변수
    TASK_ID m_TaskID;
    int m_iPriority;
    bool m_bTaskRunStat;

    // 메시지 큐 관련 멤버 변수
    MSG_Q_ID m_MsgKeyID;

#elif __linux__
    sem_t m_mutex;

    pthread_t m_MainThread;
    key_t m_MsgKeyID;
#else
#endif

    STR_MessageData m_RcvMsg;
    STR_MessageData m_SndMsg;

    char *m_pszRecvData;

#ifdef __VXWORKS__
    int m_szRecvData[_MAX_LANDATA/sizeof(UINT)] __attribute__ ((aligned(16)));	// 32 -> 16
#else
    UINT m_szRecvData[_MAX_LANDATA/sizeof(UINT)];
#endif

    static int m_iCoThread;
    static int m_iCoMsgQueue;

protected:
    bool m_bMainLoop;
    int m_iThreadID;
    char m_szThreadName[LENGTH_OF_CLASSNAME];

private:
    void DisplayMsg( bool bSend, const char *pszClassName=NULL, STR_MessageData *pInMsg=NULL );
    
public:
    CThread( int iMsgKey, const char *pThreadName, bool bArrayLanData=false, bool bCreateOnlyThread=false );
    ~CThread();

    void Run( key_t key=IPC_PRIVATE );

#ifdef _MSC_VER
    void Run( void *(*pFunc)(void*), key_t key );
    DWORD Start( void *pArg=NULL );
#elif __VXWORKS__
    void Run( void *(*pFunc)(void*), key_t key );
    DWORD Start( void *pArg=NULL );

    inline int GetPriority() { return m_iPriority; }
    inline TASK_ID GetTaskID() { return m_TaskID; }
    inline bool GetTaskRunStat() { return m_bTaskRunStat; }
    inline void SetTaskSuspend() { taskSuspend( m_TaskID ), m_bTaskRunStat=false; }
    inline void SetTaskResume() { taskResume( m_TaskID ), m_bTaskRunStat=true; }
    inline void ShowTaskMessae( int iLevel=0 ) { printf( "\n*** %s ***" , m_szThreadName ), msgQShow( m_MsgKeyID, iLevel ); }
    
#define TASK_DEFAULT_PRIORITY   (100)

    int GetPriorityByThreadName() {
        int iPriority=TASK_DEFAULT_PRIORITY;

        if( (++ iPriority) && strcmp( "CTaskMngr" , m_szThreadName ) == 0 ) {
            //WhereIs;
        }
        else if( (++ iPriority) && strcmp( "CCCUSocket" , m_szThreadName ) == 0 ) {
            //WhereIs;
        }
        else if( (++ iPriority) && strcmp( "RECCCU" , m_szThreadName ) == 0 ) {
            //WhereIs;
        }
        else if( (++ iPriority) && strcmp( "CUrBit" , m_szThreadName ) == 0 ) {
            //WhereIs;
        }
        else if( (++ iPriority) && strcmp( "CUserCollect" , m_szThreadName ) == 0 ) {
            //WhereIs;
        }
        else if( (++ iPriority) && strcmp( "CEmitterMerge" , m_szThreadName ) == 0 ) {
            //WhereIs;
        }
        else if( (++ iPriority) && strcmp( "CDetectAnalysis" , m_szThreadName ) == 0 ) {
            //WhereIs;
        }
        else if( (++ iPriority) && strcmp( "CTrackAnalysis" , m_szThreadName ) == 0 ) {
            //WhereIs;
        }
        else if( (++ iPriority) && strcmp( "CScanAnalysis" , m_szThreadName ) == 0 ) {
            //WhereIs;
        }
        else if( (++ iPriority) && strcmp( "CSignalCollect" , m_szThreadName ) == 0 ) {
            //WhereIs;
        }
        else {
            printf( "\n 타스크 우선순위가 설정되지 않아서 기본 값으로 설정 합니다.");

            iPriority = TASK_DEFAULT_PRIORITY;
            WhereIs;
        }

        //printf( "[iPriority=%d]" , iPriority );
        return iPriority;
    }

#define TASK_DEFAULT_STACKSIZE   (0x1000)

    size_t GetStackSize() { 
        int iStackSize=TASK_DEFAULT_STACKSIZE;

        if( strcmp( "CTaskMngr" , m_szThreadName ) == 0 ) {
            iStackSize = 0x10000;
        }
        else if( strcmp( "CCCUSocket" , m_szThreadName ) == 0 ) {
            iStackSize = 0x10000;
        }
        else if( strcmp( "RECCCU" , m_szThreadName ) == 0 ) {
            iStackSize = 0x10000;
        }
        else if( strcmp( "CUrBit" , m_szThreadName ) == 0 ) {
            iStackSize = 0x10000;
        }
        else if( strcmp( "CUserCollect" , m_szThreadName ) == 0 ) {
            iStackSize = 0x10000;
        }
        else if( strcmp( "CEmitterMerge" , m_szThreadName ) == 0 ) {
            iStackSize = 0x30000;
        }
        else if( strcmp( "CSignalCollect" , m_szThreadName ) == 0 ) {
            iStackSize = 0x10000;
        }
        else if( strcmp( "CDetectAnalysis" , m_szThreadName ) == 0 ) {
            iStackSize = 0x10000;
        }
        else if( strcmp( "CTrackAnalysis" , m_szThreadName ) == 0 ) {
            iStackSize = 0x10000;
        }
        else if( strcmp( "CScanAnalysis" , m_szThreadName ) == 0 ) {
            iStackSize = 0x10000;
        }

        return iStackSize;
    }
#else
    DWORD Start( void *pArg=NULL );
    void Run( void *(*Func)(void*), key_t key );
#endif

    int Pend();
    void Stop();
    void Sleep( unsigned int mssleep );
    int QMsgRcv( ENUM_RCVMSG enFlag=enWAIT_FOREVER );
    void QMsgSnd( STR_MessageData *pMessageData, const char *pszThreadName=NULL );
    void QMsgSnd( STR_MessageData *pMessageData, void *pArrayMsgData, const char *pszThreadName );
    void QMsgSnd( unsigned int uiOpCode, void *pArrayMsgData, unsigned int uiLength, void *pData=NULL, unsigned int uiDataLength=0, const char *pszClassName=NULL );
    void QMsgSnd( unsigned int uiOpCode, void *pData, unsigned int uiDataLength );
    void QMsgSnd( unsigned int uiOpCode, const char *pszClassName=NULL );

    int GetThreadID() { return m_iThreadID; }

    void SendTaskMngr( unsigned int uiErrorCode, const char *pszThreadName=NULL );

#ifdef _MSC_VER
    inline key_t GetKeyId() { return 0; }

    static DWORD WINAPI EntryPoint( LPVOID pArg)
    {
        CThread *pParent = reinterpret_cast<CThread*>(pArg);

        pParent->ThreadCtor();

        pParent->Run( pParent->m_MainThread.m_pUserData );

        pParent->ThreadDtor();

        return STILL_ACTIVE;
    }

	/*
		*	Info: Constructor-like function. 
		*	
		*	Will be called by EntryPoint before executing the thread body.
		*  Override this function to provide your extra initialization.
		*
		*  NOTE: do not confuse it with the classes constructor
		*/
	virtual void ThreadCtor() {	}

	/*
		*	Info: Destructor-like function. 
		*	
		*	Will be called by EntryPoint after executing the thread body.
		*  Override this function to provide your extra destruction.
		*
		*  NOTE: do not confuse it with the classes constructor
		*/
	virtual void ThreadDtor() {	}

    /*
	*	Info: Override this method.
	*	
	*	This function should contain the body/code of your thread.
	*	Notice the signature is similar to that of any worker thread function
	*  except for the calling convention.
	*/
    virtual DWORD Run( LPVOID /* arg */ ) {
        return m_MainThread.m_dwExitCode; 
    }

	/*
		*	Info: Attaches a Thread Function
		*	
		*	Used primarily for porting but can serve in developing generic thread objects
		*/
	void Attach( LPTHREAD_START_ROUTINE lpThreadFunc ) {
		m_pThreadFunc = lpThreadFunc;
	}

#else
    inline key_t GetKeyId() { return m_MsgKeyID; }
#endif

    void Lock() {
#ifdef _MSC_VER
#if _MSC_VER <= 1600 || _AFXDLL
        m_cs.Lock();
#elif __VXWORKS__
        printf( "\n set up lock()...");
#else
        std::unique_lock<std::mutex> lk(m_mutex);
#endif
#else
        sem_wait( & m_mutex );
#endif

    }

    void UnLock() {
#ifdef _MSC_VER
#if _MSC_VER <= 1600 || _AFXDLL
        m_cs.Unlock();
#elif __VXWORKS__
        printf( "\n set up unlock()...");
#else

#endif
#else
        sem_post( & m_mutex );
#endif

    }

    inline STR_MessageData *GetDataMessage() { return & m_RcvMsg; }
    inline int GetCoThread() { return m_iCoThread; }
    inline int GetCoMsgQueue() { return m_iCoMsgQueue; }
    inline void *GetRecvData() { return m_pszRecvData; }

    static void TCleanUpHandler(void *arg );
    static void *CallBack( void *pArg );

    virtual void _routine() { }
    virtual char *GetThreadName() { return NULL; }
    

    //pthread_create(&thread,NULL,thread_routine, NULL);
};

#endif // CTHREAD_H
