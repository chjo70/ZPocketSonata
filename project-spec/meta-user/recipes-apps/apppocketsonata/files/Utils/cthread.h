/**

    @file      cthread.h
    @brief
    @details   ~
    @author    조철희
    @date      2.05.2023
    @copyright © Cool Guy, 2023. All right reserved.

**/

#pragma once


#ifdef _MSC_VER

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
#elif defined(__VXWORKS__)
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


#define LENGTH_OF_CLASSNAME                 (30)


#define NO_ECHO                             (0)
#define ECHO                                (1)

#define PCIISR_NAME                         "PCIISR"



// VxWorks 용 타스크 전용 정의
#define TASK_DEFAULT_PRIORITY   (100)
#define TASK_LOWEST_PRIORITY    (TASK_DEFAULT_PRIORITY+20)

enum TASK_PRIORITY {
    en_LOG_PRIORITY = TASK_DEFAULT_PRIORITY,

    en_TASK_MANAGER_PRIORITY,
    en_RECLAN_PRIORITY,
    en_BIT_PRIORITY,
    en_EMTMERGE_PRIORITY,
    en_COLLECT_PRIORITY,

    en_DETECT_ANAL_PRIORITY,
    en_TRACK_ANAL_PRIORITY,
    en_SCAN_ANAL_PRIORITY,

};



#define THREAD_STANDARD_FUNCTION(A)    \
void Run( key_t key=IPC_PRIVATE ); \
virtual void _routine();    \
char *GetThreadName() { return m_szThreadName; } \
STR_MessageData *GetParentMessage() { return m_pMsg; } \
static A* GetInstance() { \
    if(m_pInstance == NULL) { \
        m_pInstance = new A( g_iKeyId++, #A, true ); \
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





/**
 * @brief 수신 메시지 정의
 */
enum ENUM_RCVMSG {
    enNO_WAIT=0,
    enWAIT_FOREVER,

    enTIMER,            // 주기적인 타이머 설정

}  ;






/**
 * @brief 쓰레드간의 메시지 데이터 구조체 정의
 */
struct STR_MessageData {
#ifdef __linux__
    long mtype;
#endif

    // Opcode : 명령어
    unsigned int uiOpCode;

    // Src/Dest :
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

    STR_MessageData()
    {
        memset( & x, 0, sizeof( UNI_MSG_DATA ) );
    };

} ;

#if defined(_MSC_VER)
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


/**
 * @brief 쓰레드 클래스
 */
class CThread : public CArrayMsgData
{
private:
    // 송신할 때 사용하는 메시지 데이터
    UNI_MSG_DATA m_uniMsgData;

    bool m_bLog;

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

#elif defined(__VXWORKS__)
    sem_t m_mutex;

    // 타스크 관련 멤버 변수
    TASK_ID m_TaskID;
    int m_iPriority;
    bool m_bTaskRunStat;

    // 메시지 큐 관련 멤버 변수
    MSG_Q_ID m_MsgKeyID;

#elif defined(__linux__)
    sem_t m_mutex;

    pthread_t m_MainThread;
    key_t m_MsgKeyID;
#else
#endif

    STR_MessageData m_RcvMsg;
    STR_MessageData m_SndMsg;

    UNI_MSG_DATA m_RcvBackupUniMsg;

    char *m_pszRecvData;

#ifdef __VXWORKS__
    int m_szRecvData[_MAX_LANDATA/sizeof(UINT)] __attribute__ ((aligned(16)));	// 32 -> 16
#else
    UINT m_szRecvData[_MAX_LANDATA/sizeof(UINT)];
#endif

    static int m_iCoThread;
    static int m_iCoMsgQueue;

    static bool m_bSendEnable;

protected:
    bool m_bThreadLoop;                     //! 사용자 쓰레드의 무한 루프 값
    int m_iThreadID;
    char m_szThreadName[LENGTH_OF_CLASSNAME];

    // 송신할 때 사용하는 메시지 데이터
    STR_COLLECT_INFO *m_pstrCollectInfo;
    STR_DETANAL_INFO *m_pstrDetectAnalInfo;
    STR_SCANANAL_INFO *m_pstrScanAnalInfo;

    // 수신할 때 사용하는 메시지 데이터
    STR_COLLECT_INFO *m_pRecvCollectInfo;
    STR_DETANAL_INFO *m_pRecvDetectAnalInfo;
    STR_SCANANAL_INFO *m_pRecvScanAnalInfo;

private:
    void DisplayMsg( bool bSend, const char *pszFromClassName=NULL, const char *pszToClassName=NULL, STR_MessageData *pInMsg=NULL );

public:
    CThread();
    CThread( int iThreadPriority, const char *pThreadName, bool bArrayLanData=false, bool bCreateOnlyThread=false );
    ~CThread();

    void Init();

    //void Run( key_t key=IPC_PRIVATE );
    void Run();

    void SendThreadMessage( CThread *pThread, bool bWait=true );

    void ShowTaskMessae( int iLevel = 0 );
    void ShowQueueMessae( int iLevel = 0 );

    void ChangeTaskPriority( int iPriority );

#ifdef _MSC_VER
    void Run( void *(*pFunc)(void*) );
    DWORD Start( void *pArg=NULL );

#elif defined(__VXWORKS__)
    void Run( void *(*pFunc)(void*) );
    DWORD Start( void *pArg=NULL );


    inline int GetPriority() { return m_iPriority; }
    inline TASK_ID GetTaskID() { return m_TaskID; }
    inline bool GetTaskRunStat() { return m_bTaskRunStat; }
    inline void SetTaskSuspend() { taskSuspend( m_TaskID ), m_bTaskRunStat=false; }
    inline void SetTaskResume() { taskResume( m_TaskID ), m_bTaskRunStat=true; }

#define TASK_DEFAULT_STACKSIZE   (0x30000)

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
    void StopThread();
    void msSleep( unsigned int mssleep );
    int QMsgRcv( ENUM_RCVMSG enFlag=enWAIT_FOREVER, DWORD dwMilliSec=0 );
    void QMsgSnd( STR_MessageData *pMessageData, const char *pszThreadName=NULL );
    void QMsgSnd( STR_MessageData *pMessageData, void *pArrayMsgData, const char *pszThreadName );
    void QMsgSnd( unsigned int uiOpCode, void *pArrayMsgData, unsigned int uiArrayLength, void *pData, unsigned int uiDataLength, const char *pszClassName );
    void QMsgSnd( unsigned int uiOpCode, void *pArrayMsgData, unsigned int uiArrayElement, unsigned int uiArraySize, void *pData=NULL, unsigned int uiDataLength=0, const char *pszClassName=NULL );
    void QMsgSnd( unsigned int uiOpCode, void *pData, unsigned int uiDataLength, const char *pszClassName );
    void QMsgSnd( unsigned int uiOpCode, const char *pszClassName=NULL );

    void QMsgClear();

    //int GetThreadID() { return m_iThreadID; }

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
#elif defined(__VXWORKS__)
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
#elif defined(__VXWORKS__)
        printf( "\n set up unlock()...");
#else

#endif
#else
        sem_post( & m_mutex );
#endif

    }

    int QMsgRcvSize();

    inline STR_MessageData *GetRecvDataMessage() { return & m_RcvMsg; }

    inline void BackupRecvUNIDataMessage( UNI_MSG_DATA *pUniMsgData )
    {
        memcpy( & m_RcvBackupUniMsg, & m_RcvMsg, sizeof( UNI_MSG_DATA ) );
        memcpy( &m_RcvMsg.x, pUniMsgData, sizeof( UNI_MSG_DATA ) );
    }

    inline void RestoreRecvUNIDataMessage()
    {
        memcpy( & m_RcvMsg.x, & m_RcvBackupUniMsg, sizeof( UNI_MSG_DATA ) );

    }

    inline UNI_LAN_DATA* GeLanData() { return ( UNI_LAN_DATA  * ) &m_RcvMsg.x.szData[0]; }

    inline int GetCoThread() { return m_iCoThread; }
    inline int GetCoMsgQueue() { return m_iCoMsgQueue; }
    inline void *GetRecvData() { return m_pszRecvData; }


    inline UNI_MSG_DATA *GetUniMessageData() { return &m_uniMsgData; }
    inline STR_COLLECT_INFO *GetCollectInfo() { return m_pstrCollectInfo; }
    inline STR_DETANAL_INFO *GetDetectAnalInfo() { return m_pstrDetectAnalInfo; }
    inline STR_SCANANAL_INFO *GetScanAnalInfo() { return m_pstrScanAnalInfo; }

    inline void SetSendDisable() { m_bSendEnable = false; }
    inline void SetSendEnable() { m_bSendEnable = true; }
    inline bool IsSendEnabled() { return m_bSendEnable; }

    static void TCleanUpHandler(void *arg );
    static void *CallBack( void *pArg );

    virtual void _routine() { }
    virtual char *GetThreadName() { return NULL; }
    virtual STR_MessageData *GetParentMessage() = 0;

    //pthread_create(&thread,NULL,thread_routine, NULL);

    //_DEFINE_LOG_VIRTUAL_FUNCTION
    //virtual void LogMsg( int nType, const char *pszFunction, const char *pszFile, const int iLine, const char *fmt, ... ) = 0;

};


