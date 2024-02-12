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

#include "../Utils/clock.h"
#include "../Utils/clogname.h"


#define LENGTH_OF_CLASSNAME                 (10)


#define NO_ECHO                             (0)
#define ECHO                                (1)

#define PCIISR_NAME                         "PCIISR"



// VxWorks 용 타스크 전용 정의
#define TASK_DEFAULT_PRIORITY               (100)
#define TASK_LOWEST_PRIORITY                (TASK_DEFAULT_PRIORITY+50)

#define WAIT_THREAD_MAX_RESPOND             (10)


enum TASK_PRIORITY {
    en_LOG_PRIORITY = TASK_DEFAULT_PRIORITY,

    en_TASK_MANAGER_PRIORITY,
    en_RECLAN_PRIORITY,
    en_RECLAN2_PRIORITY,
    en_BIT_PRIORITY,
    en_EMTMERGE_PRIORITY,

    en_DETECT_ANAL_PRIORITY,
    en_TRACK_ANAL_PRIORITY,
    en_SCAN_ANAL_PRIORITY,

    en_COLLECT_PRIORITY,

};



#define THREAD_STANDARD_FUNCTION(A)    \
void Run( key_t key=IPC_PRIVATE ); \
virtual void _routine();    \
const char *GetThreadName() { return m_szThreadName; } \
STR_MessageData *GetParentMessage() { return m_pMsg; } \
static A* GetInstance() { \
    if(m_pInstance == NULL) { \
        m_pInstance = new A( g_iKeyId++, (const char *) #A, true ); \
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

//virtual const char *GetThreadName() { return m_szThreadName; }
// 오직 CTaskMngr 에서만 사용하는 정의문 입니다.
#define THREAD_STANDARD_FUNCTION_2(A )    \
void Run( key_t key=IPC_PRIVATE ); \
virtual void _routine();    \
static A* GetInstance() { \
    if(m_pInstance == NULL) { \
        char szSQLiteFileName[100]; \
        strcpy( szSQLiteFileName, CEDEOB_SQLITE_FOLDER ); \
        strcat( szSQLiteFileName, "/" ); \
        strcat( szSQLiteFileName, CEDEOB_SQLITE_FILENAME ); \
        m_pInstance = new A( g_iKeyId++, (const char*) #A, true, (char*) szSQLiteFileName ); \
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
typedef struct stSTR_MessageData {
#ifdef __linux__
    long mtype;
#endif

    // Opcode : 명령어
    unsigned int uiOpCode;

    // Src/Dest :
    unsigned char ucSrcDest;

    //랜 송신시 이 값이 0 이 아니면 이 소켓 값으로 데이터를 전송한다.
    SOCKET soSocket;

    // 데이터 길이
    unsigned int uiDataLength;

    // 데이터 영역 이다.
    UNI_MSG_DATA x;

    // CArrayData 클래스 사용시 인덱스 값을 의미함. 0 보다 작은 값은 CArrayData 를 사용하지 않은 것이다.
    int iArrayIndex;
    unsigned int uiArrayLength;

    stSTR_MessageData()
    {
        memset( & x, 0, sizeof( union UNI_MSG_DATA ) );
        uiArrayLength = 0;
    };

} STR_MessageData;

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
class CThread : public CLock, public CArrayMsgData, public CLogName
{
private:
    // 송신할 때 사용하는 메시지 데이터
    UNI_MSG_DATA m_uniMsgData;

    bool m_bLog;

    int m_iPriority;

#ifdef _MSC_VER
    CThreadContext m_MainThread;

    LPTHREAD_START_ROUTINE	m_pThreadFunc;	//	The Worker Thread Function Pointer

    HANDLE m_hEvent;
    HANDLE m_hSleepEvent;

    queue<STR_MessageData> m_queue;

#elif defined(__VXWORKS__)
    sem_t m_mutex;

    // 타스크 관련 멤버 변수
    TASK_ID m_TaskID;
    //int m_iPriority;
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
    STR_TRKANAL_INFO *m_pstrTrackAnalInfo;
    STR_SCANANAL_INFO *m_pstrScanAnalInfo;

    // 수신할 때 사용하는 메시지 데이터
    STR_COLLECT_INFO *m_pRecvCollectInfo;
    STR_DETANAL_INFO *m_pRecvDetectAnalInfo;
    STR_TRKANAL_INFO *m_pRecvTrackAnalInfo;
    STR_SCANANAL_INFO *m_pRecvScanAnalInfo;

private:
    void DisplayMsg( bool bSend, const char *pszFromClassName=NULL, const char *pszToClassName=NULL, STR_MessageData *pInMsg=NULL );

public:
    CThread();
    CThread( int iThreadPriority, const char *pThreadName, bool bArrayLanData=false, bool bCreateOnlyThread=false );
    virtual ~CThread();

    void Init();

    //void Run( key_t key=IPC_PRIVATE );
    void Run();

    void SendThreadMessage( CThread *pThread, bool bWait=true );
    void SendThreadMessage( CThread *pThread, unsigned int uiOpCode, bool bWait=true );

    void ShowTaskMessae( int iLevel = 0, bool bLog=true );
    void ShowQueueMessae( int iLevel = 0, bool bLog=true );

    void ChangeTaskPriority( int iPriority );

    void Clear();

#ifdef _MSC_VER
    void Run( void *(*pFunc)(void*) );
    DWORD Start( void *pArg=NULL );

    void FlushEvent();

#elif defined(__VXWORKS__)
    void Run( void *(*pFunc)(void*) );
    DWORD Start( void *pArg=NULL );


    inline int GetPriority() { return m_iPriority; }
    inline TASK_ID GetTaskID() { return m_TaskID; }
    inline bool GetTaskRunStat() { return m_bTaskRunStat; }
    inline void SetTaskSuspend() { taskSuspend( m_TaskID ), m_bTaskRunStat=false; }
    inline void SetTaskResume() { taskResume( m_TaskID ), m_bTaskRunStat=true; }
    inline STATUS GetTaskInfo( TASK_DESC *pTaskDesc ) {
        return taskInfoGet( m_TaskID, pTaskDesc );
    }

#define TASK_DEFAULT_STACKSIZE   (0x40000)

    size_t GetStackSize() {
        size_t iStackSize=TASK_DEFAULT_STACKSIZE;

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
        else {
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
    void QMsgSnd( STR_MessageData *pMessageData, const char *pszThreadName=NULL, int iOption=WAIT_FOREVER );
    void QMsgSnd( STR_MessageData *pMessageData, void *pArrayMsgData, const char *pszThreadName );
    void QMsgSnd( unsigned int uiOpCode, void *pArrayMsgData, unsigned int uiArrayLength, void *pData, unsigned int uiDataLength, const char *pszClassName, int iOption=WAIT_FOREVER );
    void QMsgSnd( unsigned int uiOpCode, void *pArrayMsgData, unsigned int uiArrayElement, unsigned int uiArraySize, void *pData=NULL, unsigned int uiDataLength=0, const char *pszClassName=NULL, int iOptions=WAIT_FOREVER );
    void QMsgSnd( unsigned int uiOpCode, void *pData, unsigned int uiDataLength, const char *pszClassName, int iOption=WAIT_FOREVER );
    void QMsgSnd( unsigned int uiOpCode, const char *pszClassName=NULL, int iOptio=WAIT_FOREVER );

    void QMsgClear();

    //int GetThreadID() { return m_iThreadID; }

    void SendTaskMngr( unsigned int uiErrorCode, const char *pszThreadName=NULL );

    const char *GetThreadName() { return m_szThreadName; }
    int GetCoThread();

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

    int QMsgRcvSize();

    //const const char *GetThreadName() { return m_szThreadName; }

    inline STR_MessageData *GetRecvDataMessage() { return & m_RcvMsg; }

    /**
     * @brief     BackupRecvUNIDataMessage
     * @param     UNI_MSG_DATA * pUniMsgData
     * @return    void
     * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   1.0.0
     * @date      2023-12-27 11:26:26
     * @warning
     */
    inline void BackupRecvUNIDataMessage( UNI_MSG_DATA *pUniMsgData )
    {
        memcpy( & m_RcvBackupUniMsg, & m_RcvMsg, sizeof( STR_MessageData ) );
        memcpy( &m_RcvMsg.x, pUniMsgData, sizeof( UNI_MSG_DATA ) );
    }

    /**
     * @brief     RestoreRecvUNIDataMessage
     * @return    void
     * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   1.0.0
     * @date      2023-12-27 11:26:23
     * @warning
     */
    inline void RestoreRecvUNIDataMessage()
    {
        memcpy( & m_RcvMsg, & m_RcvBackupUniMsg, sizeof( STR_MessageData ) );

    }

    inline UNI_LAN_DATA* GeLanData() { return ( UNI_LAN_DATA  * ) &m_RcvMsg.x.szData[0]; }
    inline UNI_MSG_DATA *GeUniMsgData() { return ( UNI_MSG_DATA * ) &m_RcvMsg.x.szData[0]; }

    inline int GetCoMsgQueue() { return m_iCoMsgQueue; }
    inline void *GetRecvData() { return m_pszRecvData; }


    inline UNI_MSG_DATA *GetUniMessageData() { return &m_uniMsgData; }
    inline STR_COLLECT_INFO *GetCollectInfo() { return m_pstrCollectInfo; }
    inline STR_DETANAL_INFO *GetDetectAnalInfo() { return m_pstrDetectAnalInfo; }
    inline STR_TRKANAL_INFO *GetTrackAnalInfo() { return m_pstrTrackAnalInfo; }
    inline STR_SCANANAL_INFO *GetScanAnalInfo() { return m_pstrScanAnalInfo; }

    inline void SetSendDisable() { m_bSendEnable = false; }
    inline void SetSendEnable() { m_bSendEnable = true; }
    inline bool IsSendEnabled() { return m_bSendEnable; }

    static void TCleanUpHandler(void *arg );
    static void *CallBack( void *pArg );

    virtual void _routine() { }
    virtual STR_MessageData *GetParentMessage() = 0;

    //pthread_create(&thread,NULL,thread_routine, NULL);

    //_DEFINE_LOG_VIRTUAL_FUNCTION
    //virtual void LogMsg( int nType, const char *pszFunction, const char *pszFile, const int iLine, const char *fmt, ... ) = 0;

};


