/****************************************************************************************
 파 일 명 : cthread.cpp
 ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 목    적 : 쓰레드 및 메시지 통신 클래스
 가    정 :
 저 자 명 : 조철희
 변 경 자 :
 변경내용 : (목적)
 변경일시 :
 ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 입력정의 :
 출력정의 :
 관련모듈 :
 자료구조 : (전역변수)
 에러처리/복귀순서:
 컴파일 일시 :
*****************************************************************************************/

#include "pch.h"

#ifdef _MSC_VER

#elif defined(__VXWORKS__)
#include <netinet/in.h>
#include <msgQLib.h>
#include <errnoLib.h>
#include <usrLib.h>

#endif



#include "cthread.h"
#include "../Anal/SigAnal/_Type.h"

#include "../Include/globals.h"

#ifndef S_DEFFILEMODE
#define S_DEFFILEMODE   (S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH)
#endif

// 클래스 내의 정적 멤버변수 값 정의
int CThread::m_iCoThread = 0;
int CThread::m_iCoMsgQueue = 0;


/**
 * @brief CThread::CThread
 * @param iMsgKey
 * @param pClassName
 * @param bArrayLanData
 */
CThread::CThread( int iThreadID, const char *pThreadName, bool bArrayLanData, bool bCreateOnlyThread ) : CArrayMsgData( bArrayLanData )
{

    m_bThreadLoop = true;

    strcpy( m_szThreadName, pThreadName );

#ifdef _MSC_VER
    m_pThreadFunc = CThread::EntryPoint;

    // 메시지 큐
	m_hEvent = CreateEvent( NULL, FALSE, FALSE, pThreadName );
    if( m_hEvent == NULL ) {
        LOGMSG1( enError, "Warning: CreateEvent failed in CThread::CThread..." , m_szThreadName );
    }
    else {
        ++ m_iCoMsgQueue;
    }

    // Sleep 큐
    m_hSleepEvent = CreateEvent( NULL, FALSE, FALSE, pThreadName );
    if( m_hSleepEvent == NULL ) {
        LOGMSG1( enError, "Warning: CreateEvent failed in CThread::CThread::Sleep..." , m_szThreadName );
    }

    LOGMSG2( enDebug, "Create the task[%s] & queue ID[%d] ..." , m_szThreadName, m_hEvent );

#elif defined(__VXWORKS__)
    m_iPriority = -1;
    m_MsgKeyID = 0;
    m_bTaskRunStat = false;

    if( sem_init( & m_mutex, 1, 1 ) < 0 ) {
        perror( "세마포어 실패" );
    }

    // 메시지 큐 생성
    m_MsgKeyID = msgQCreate( SIZE_OF_MSGDATA_ARRAY, sizeof(STR_MessageData), MSG_Q_PRIORITY );
    if( m_MsgKeyID == NULL ) {
        LOGMSG1( enError, "큐 ID[%d]를 생성 실패했습니다 !" , m_MsgKeyID );
    }
    else {
        // LOGMSG1( enDebug, "큐 ID[%d]를 생성합니다." , m_MsgKeyID );
        // msgQShow( m_MsgKeyID, 1 );
        ++ m_iCoMsgQueue;
    }
    LOGMSG2( enDebug, "Create the task[%s] & queue ID[%d] ..." , m_szThreadName, m_MsgKeyID );

#elif defined(__linux__)
    m_MsgKeyID = 0;

    if( sem_init( & m_mutex, 1, 1 ) < 0 ) {
        perror( "세마포어 실패" );
    }

    // 기존의 메시지 큐를 삭제하고 재 생성한다.
    m_MsgKeyID = msgget( key, S_DEFFILEMODE | IPC_CREAT );
    if (m_MsgKeyID != -1 ) {
        msgctl( m_MsgKeyID, IPC_RMID, 0 );
    }

    m_MsgKeyID = msgget( key, S_DEFFILEMODE | IPC_CREAT );
    if (m_MsgKeyID == -1 ) {
        perror("msgget error : ");
        exit(0);
    }
    else {
        // LOGMSG1( enDebug, "큐 ID[%d]를 생성합니다." , m_MsgKeyID );
        ++ m_iCoMsgQueue;
    }
    while( QMsgRcv( enNO_WAIT ) != -1 );

    LOGMSG2( enDebug, "Create the task[%s] & queue ID[%d] ..." , m_szThreadName, m_MsgKeyID );

#else
#error 이 소스는 현재 플레폼에 지원하지 않습니다. 개발자에게 문의하세요..
#endif

    m_iThreadID = iThreadID;

    m_pszRecvData = NULL;

    // 메시지큐 생성
    memset( & m_RcvMsg, 0, sizeof(STR_MessageData) );

    // 스레드 벡터에 삽입하기
    g_vecThread.push_back( this );

    //printf( "\nm_szRecvData=%p" , & m_szRecvData[0] );

}

/**
 * @brief CThread::~CThread
 */
CThread::~CThread()
{

    // 2. 큐 메시지를 죽인다.
#ifdef __linux__
    if (m_MsgKeyID > 0 ) {

        if( msgctl( m_MsgKeyID, IPC_RMID, 0 ) == -1 ) {
            perror( "msgctl 실패" );
        }
        else {
            -- m_iCoMsgQueue;
            LOGMSG1( enDebug, "\t 큐 ID[%d]를 종료 처리합니다." , m_MsgKeyID );
        }
    }

#elif defined(_MSC_VER)
    // QMsgSnd( enTHREAD_EXIT, m_szThreadName );

    //delete m_pTheMessageQueue;

    if(m_hEvent != 0 ) {
        CloseHandle(m_hEvent);
        -- m_iCoMsgQueue;
    }

    if(m_hSleepEvent != 0 ) {
        CloseHandle(m_hSleepEvent);
    }

#elif defined(__VXWORKS__)

#else

#endif

    // 1. 쓰레드를 죽인다.
#ifdef _MSC_VER
    if ( m_MainThread.m_hThread ) {
        CThread::StopThread();

        LOGMSG1( enDebug, "[%s]를 종료 처리합니다." , m_szThreadName );
    }

#elif defined(__VXWORKS__)
    LOGMSG1( enDebug, "[%s]를 종료 처리합니다." , m_szThreadName );

#else
    if( m_MainThread != 0 ) {
        -- m_iCoThread;

        pthread_cancel( m_MainThread );
        //Pend();
        LOGMSG1( enDebug, "[%s]를 종료 처리합니다." , m_szThreadName );

        //Stop();
    }
#endif

#ifdef _LOG_
    g_pTheLog->UnLock();

#endif

    //
    // g_vecThis.erase( this );

    LOGMSG2( enDebug, "\t 쓰레드 [%d개], 큐 [%d개] 가 남아 있습니다." , m_iCoThread, m_iCoMsgQueue );

}

/**
 * @brief CThread::CallBack
 * @param pArg
 * @return
 */
void *CThread::CallBack( void *pArg )
{
    CThread *pThread = reinterpret_cast<CThread*> (pArg);

    if( pThread == NULL ) {
        LOGMSG( enError, "함수 인자 포인터가 널 값 입니다. 인자를 객체 포인터로 입력해줘야 합니다." );
    }
    else {
#ifdef __linux__
        //pthread_cleanup_push( TCleanUpHandler, NULL);

        pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
        pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS,NULL);

        pThhread->_routine();

        //pthread_cleanup_pop(1);
#else
        pThread->_routine();

#endif

		LOGMSG1( enNormal, "The [%s] is stopped the the main loop...", pThread->m_szThreadName );
    }

    return NULL;
}

/**
 * @brief     Run
 * @param     void *
 * @param     * pFunc
 * @param     void *
 * @param     key_t key
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2021-08-23, 18:02
 * @warning
 */
void CThread::Run( void *(*pFunc)(void*) )
{
	m_bThreadLoop = true;

#ifdef __linux__
    pthread_create( & m_MainThread, NULL, pFunc, this );

    LOGMSG4( enDebug, "Create the task[%s] ID[%d/%d] & queue ID[%d] ..." , m_szThreadName, m_TaskID, m_iPriority, m_hEvent );

#elif defined(_MSC_VER)

    // 쓰레드 생성
    Attach( (LPTHREAD_START_ROUTINE) pFunc );
    Start();

#elif defined(__VXWORKS__)

    // 타스크 큐 생성
    m_iPriority = GetPriorityByThreadName();
    m_TaskID = taskSpawn( m_szThreadName, GetPriority(), VX_STDIO|VX_SUPERVISOR_MODE|VX_FP_TASK|VX_ALTIVEC_TASK, GetStackSize(), (FUNCPTR) *pFunc, (int) this, 0, 0, 0, 0, 0, 0, 0, 0, 0 );
    if( m_TaskID != TASK_ID_ERROR ) {
        m_bTaskRunStat = true;
    }

    LOGMSG4( enDebug, "Create the task[%s] ID[%d/%d] & queue ID[%d] ..." , m_szThreadName, m_TaskID, m_iPriority, m_MsgKeyID );

    // printErrno( errnoGet() );
	LOG_LINEFEED;

#endif

    ++ m_iCoThread;

}

/**
 * @brief     Start
 * @param     void * pArg
 * @return    DWORD
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2021-05-07, 15:39
 * @warning
 */
DWORD CThread::Start( void *pArg )
{

#ifdef _MSC_VER
    m_MainThread.m_pUserData = pArg;
    m_MainThread.m_hThread = CreateThread(NULL, 0, m_pThreadFunc, this, 0, & m_MainThread.m_dwTID );
    m_MainThread.m_dwExitCode = (DWORD)-1;
#else

#endif

#ifdef _MSC_VER
    return GetLastError();
#else
    return 0;
#endif

}

/**
 * @brief     등록한 CallBack 함수를 호출합니다.
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-03-03 12:02:46
 * @warning
 */
void CThread::Run()
{
    Run( CallBack );

}

/**
 * @brief     쓰레드를 잠시 대기를 시키게 한다.
 * @return    int
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-03-03 12:03:06
 * @warning
 */
int CThread::Pend()
{
    //void *pStatus;
    //int iStatus[100];
    int iStatus=0;

#ifdef _MSC_VER
#elif defined(__VXWORKS__)
#else
    iStatus = pthread_join( m_MainThread, /* (void **) & iStatus[0] */ NULL );

#endif

    return iStatus;
}

/**
 * @brief     쓰레드를 종료 합니다.
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-02-28 15:53:21
 * @warning
 */
void CThread::StopThread()
{
#ifdef _MSC_VER
    if ( m_MainThread.m_hThread ) {
        GetExitCodeThread(m_MainThread.m_hThread, & m_MainThread.m_dwExitCode );

        if ( m_MainThread.m_dwExitCode == STILL_ACTIVE ) {
            HANDLE hThread;

            // 로그 관련 CriticalSection 락을 푼다.
            TRACE( "CThread::Stop" );

#ifdef _LOG_
            while( g_pTheLog->IsLock() == true ) {
				msSleep(10);
                TRACE( "*" );
            }
#endif

            hThread = m_MainThread.m_hThread;
            m_MainThread.m_hThread = NULL;
            TerminateThread( hThread, 0 ); //DWORD(-1));
            //ExitThread( 0 );

            -- m_iCoThread;
        }
        else {
            m_MainThread.m_hThread = NULL;
        }


    }
#elif defined(__VXWORKS__)

#else
    if( m_MainThread != 0 ) {
        if (!pthread_cancel(m_MainThread)) {
            pthread_join(m_MainThread, NULL);

            -- m_iCoMsgQueue;
            -- m_iCoThread;
        }
        else
        {
            perror("pthread_cancel");
        }
    }
#endif

    // g_pTheLog->UnLock();

	m_bThreadLoop = false;

}


/**
 * @brief CThread::TCleanUpHandler
 * @param arg
 */
void CThread::TCleanUpHandler(void *arg )
{
    printf("cleanup \n");
    // close your socket
}


/**
 * @brief     큐 메시지를 비웁니다.
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-03-07 11:41:40
 * @warning
 */
void CThread::QMsgClear()
{

#ifdef _MSC_VER
    Lock();
    while( !m_queue.empty() ) {
        m_queue.pop();
    }
    UnLock();

#elif defined(__VXWORKS__)
    int noError;
    STATUS stat;

    do {
        stat = msgQReceive( m_MsgKeyID, ( char* ) &m_RcvMsg, sizeof( STR_MessageData ), 1 );
        noError = errnoGet();
        // printf( "\n stat[%d], noError[%d]", stat, noError );

    } while( noError != S_objLib_OBJ_TIMEOUT );

#elif defined(__linux__)
    printf( "큐 메시지를 클리어 하도록 구현해야 합니다." );

#endif

    return;
}


/**
 * @brief CThread::QMsgRcv
 * @return
 */
int CThread::QMsgRcv( ENUM_RCVMSG enFlag, DWORD dwMilliSec )
{
    //LOGENTRY;
    int iMsgRcv = -1;

#ifdef __linux__
    int iFlag;

    if( enFlag == enNO_WAIT ) {
        iFlag = IPC_NOWAIT;
    }
    else {
        iFlag = IPC_FOREVER;
    }

    iMsgRcv = msgrcv( m_MsgKeyID, (void *) & m_RcvMsg, sizeof(STR_MessageData)-sizeof(long), 1 /* (1 >> 1)*/, iFlag );

    if( iMsgRcv > 0 ) {
        DisplayMsg( false );

        if( m_RcvMsg.iArrayIndex != -1 ) {
            m_pszRecvData = m_szRecvData;
            PopLanData( m_szRecvData, m_RcvMsg.iArrayIndex, m_RcvMsg.uiArrayLength );
        }
        else {
            m_pszRecvData = NULL;
        }
    }

#elif _MSC_VER
    DWORD dwRes;

    if( enFlag == enNO_WAIT ) {
	    dwRes = ::WaitForSingleObject(m_hEvent, 0 );

        if( dwRes == WAIT_OBJECT_0 || dwRes == WAIT_TIMEOUT ) {
            Lock();
            if( m_queue.size() != 0 ) {
                iMsgRcv = 1;

                m_RcvMsg = m_queue.front();

                if (m_RcvMsg.iArrayIndex != -1) {
                    m_pszRecvData = (char *) m_szRecvData;
                    PopLanData(m_szRecvData, m_RcvMsg.iArrayIndex, m_RcvMsg.uiArrayLength);
                }
                else {
                    m_pszRecvData = NULL;
                }

                m_queue.pop();
            }
        }
    }
    else {
        Lock();
        if( m_queue.size() == 0 ) {
            UnLock();
            if (enFlag == enTIMER) {
                dwRes = ::WaitForSingleObject(m_hEvent, dwMilliSec);
            }
            else {
                dwRes = ::WaitForSingleObject(m_hEvent, INFINITE);
            }

            if( dwRes == WAIT_FAILED ) {

            }
            else if( dwRes == WAIT_ABANDONED ) {
                ResetEvent( m_hEvent );
            }
            else if (dwRes == WAIT_TIMEOUT ) {
				iMsgRcv = 1;

				m_RcvMsg.uiOpCode = enTHREAD_TIMER;
				m_RcvMsg.uiSocket = 0;
                m_RcvMsg.uiEchoBit = 0;

                m_pszRecvData = NULL;

            }
            else if( dwRes == WAIT_OBJECT_0 ) {
                Lock();
                if( m_queue.size() != 0 ) {
                    iMsgRcv = 1;

                    m_RcvMsg = m_queue.front();

                    if (m_RcvMsg.iArrayIndex != -1) {
                        m_pszRecvData = (char *) m_szRecvData;
                        PopLanData( m_szRecvData, m_RcvMsg.iArrayIndex, m_RcvMsg.uiArrayLength );
                    }
                    else {
                        m_pszRecvData = NULL;
                    }

                    m_queue.pop();

                    ResetEvent( m_hEvent );
                }
                else {
                    TRACE( "Invalid the receive message..." );
                }
            }
			ELSE

        }
        else {
            iMsgRcv = 1;

            m_RcvMsg = m_queue.front();

            if (m_RcvMsg.iArrayIndex != -1) {
                m_pszRecvData = (char *) m_szRecvData;
                PopLanData( m_szRecvData, m_RcvMsg.iArrayIndex, m_RcvMsg.uiArrayLength );
            }
            else {
                m_pszRecvData = NULL;
            }

            m_queue.pop();
        }

    }

    UnLock();

#elif defined(__VXWORKS__)
    _Vx_ticks_t option;

    if( enFlag == enWAIT_FOREVER ) {
        option = WAIT_FOREVER;
    }
    else {
        option = dwMilliSec;
    }

    STATUS stat = msgQReceive( m_MsgKeyID, (char *) & m_RcvMsg, sizeof(STR_MessageData), option );
    if( ERROR == stat ) {
        int noError = errnoGet();

        if( noError == S_objLib_OBJ_TIMEOUT ) {
            iMsgRcv = 1;

            m_RcvMsg.uiOpCode = enTHREAD_DELETE_THREAT;
            m_RcvMsg.uiSocket = 0;
            m_RcvMsg.uiEchoBit = 0;
        }
        else if( noError == S_objLib_OBJ_UNAVAILABLE && enFlag == enNO_WAIT ) {

        }
        else {
            printf( "[%s]" , GetThreadName() );
            printf( "\nstat[%d/%d/%d/%d]" , stat, ERROR, option, noError );
        }
    }
    else {
        if( option == NO_WAIT ) {
            //printf( "\n opcode[0x%x]" , m_RcvMsg.uiOpCode );

            if( stat == S_objLib_OBJ_UNAVAILABLE ) {
                WhereIs;
            }
            else {
                iMsgRcv = 1;
            }
        }
        // 정상 적인 처리 입니다.
        else {
            iMsgRcv = 0;
        }

        if( m_RcvMsg.iArrayIndex != -1 ) {
            m_pszRecvData = (char *) m_szRecvData;

            Lock();
            PopLanData( m_szRecvData, m_RcvMsg.iArrayIndex, m_RcvMsg.uiArrayLength );
            UnLock();
        }
        else {
            m_pszRecvData = NULL;
        }


        //DisplayMsg( false );
    }

#else

    while( true ) {
        sleep( 1 );
    }

#endif

    return iMsgRcv;

}

/**
 * @brief     QMsgSnd
 * @param     unsigned int uiOpCode
 * @param     void * pData
 * @param     unsigned int uiDataLength
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-03-07 15:46:10
 * @warning
 */
void CThread::QMsgSnd( unsigned int uiOpCode, void *pData, unsigned int uiDataLength )
{
    QMsgSnd( uiOpCode, NO_ECHO, NULL, 0, 0, pData, uiDataLength, NULL );
}

/**
 * @brief     해당 쓰레드로 메시지를 전송한다.
 * @param     unsigned int uiOpCode
 * @param     const char * pszClassName
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-11-04 19:18:32
 * @warning
 */
void CThread::QMsgSnd( unsigned int uiOpCode, const char *pszClassName )
{
    QMsgSnd( uiOpCode, NO_ECHO, NULL, 0, 0, NULL, 0, pszClassName );
}

void CThread::QMsgEchoSnd( unsigned int uiOpCode, const char *pszClassName )
{
    QMsgSnd( uiOpCode, ECHO, NULL, 0, 0, NULL, 0, pszClassName );
}

/**
 * @brief     QMsgSnd
 * @param     unsigned int uiOpCode
 * @param     void * pArrayMsgData
 * @param     unsigned int uiArrayLength
 * @param     void * pData
 * @param     unsigned int uiDataLength
 * @param     const char * pszClassName
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-04-21, 18:06
 * @warning
 */
void CThread::QMsgSnd(unsigned int uiOpCode, unsigned int uiEchoBit, void *pArrayMsgData, unsigned int uiArrayLength, void *pData, unsigned int uiDataLength, const char *pszClassName)
{
    QMsgSnd(uiOpCode, uiEchoBit, pArrayMsgData, uiArrayLength, _spOne, pData, uiDataLength, pszClassName );
}

/**
 * @brief     QMsgSnd
 * @param     unsigned int uiOpCode
 * @param     void * pArrayMsgData
 * @param     unsigned int uiArrayLength
 * @param     void * pData
 * @param     unsigned int uiDataLength
 * @param     const char * pszClassName
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-03-07 15:25:28
 * @warning
 */
void CThread::QMsgSnd( unsigned int uiOpCode, void *pArrayMsgData, unsigned int uiArrayLength, void *pData, unsigned int uiDataLength, const char *pszClassName )
{
    QMsgSnd( uiOpCode, NO_ECHO, pArrayMsgData, uiArrayLength, _spOne, pData, uiDataLength, pszClassName );
}

/**
 * @brief     QMsgSnd
 * @param     unsigned int uiOpCode
 * @param     void * pArrayMsgData
 * @param     unsigned int uiArrayLength
 * @param     void * pData
 * @param     unsigned int uiDataLength
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-03-07 15:36:17
 * @warning
 */
void CThread::QMsgSnd( unsigned int uiOpCode, void *pArrayMsgData, unsigned int uiArrayLength, void *pData, unsigned int uiDataLength )
{
    QMsgSnd( uiOpCode, NO_ECHO, pArrayMsgData, uiArrayLength, _spOne, pData, uiDataLength, NULL );

}

/**
 * @brief     QMsgSnd
 * @param     unsigned int uiOpCode
 * @param     void * pArrayMsgData
 * @param     unsigned int uiArrayElement
 * @param     unsigned int uiArraySize
 * @param     void * pData
 * @param     unsigned int uiDataLength
 * @param     const char * pszClassName
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-03-07 15:46:03
 * @warning
 */
void CThread::QMsgSnd( unsigned int uiOpCode, void *pArrayMsgData, unsigned int uiArrayElement, unsigned int uiArraySize, void *pData, unsigned int uiDataLength, const char *pszClassName )
{
    QMsgSnd( uiOpCode, NO_ECHO, pArrayMsgData, uiArrayElement, uiArraySize, pData, uiDataLength, pszClassName );
}

/**
 * @brief     QMsgSnd
 * @param     unsigned int uiOpCode
 * @param     unsigned int uiEchoBit
 * @param     void * pArrayMsgData
 * @param     unsigned int uiArrayElement
 * @param     unsigned int uiArraySize
 * @param     void * pData
 * @param     unsigned int uiDataLength
 * @param     const char * pszClassName
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-03-07 15:36:22
 * @warning
 */
void CThread::QMsgSnd( unsigned int uiOpCode, unsigned int uiEchoBit, void *pArrayMsgData, unsigned int uiArrayElement, unsigned int uiArraySize, void *pData, unsigned int uiDataLength, const char *pszClassName )
{
    STR_MessageData sndMsg;

#ifdef __linux__
    sndMsg.mtype = 1;
#endif

    // 1. OPCODE 저장
    sndMsg.uiOpCode = uiOpCode;
    sndMsg.uiSocket = 0;
    sndMsg.uiEchoBit = uiEchoBit;

    // 2. 데이터 저장
    if( pData != NULL ) {
   		sndMsg.uiDataLength = uiDataLength;
        memcpy( & sndMsg.x, pData, sizeof(char)*sndMsg.uiDataLength );
    }
    else {
    	sndMsg.uiDataLength = 0;
    }

    // 3. 추가 데이터 저장
    if( pArrayMsgData != NULL ) {
    	sndMsg.uiArrayLength = uiArrayElement * uiArraySize;
        sndMsg.iArrayIndex = PushLanData(pArrayMsgData, sndMsg.uiArrayLength);
    }
    else {
    	sndMsg.uiArrayLength = 0;
    	sndMsg.iArrayIndex = -1;
    }

    if( sndMsg.uiArrayLength == 0 || sndMsg.iArrayIndex != -1 ) {
        QMsgSnd( & sndMsg, pszClassName );
    }

}

/**
 * @brief     QMsgSnd
 * @param     STR_MessageData * pMessageData
 * @param     void * pArrayMsgData
 * @param     const char * pszThreadName
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-03-07 15:35:06
 * @warning
 */
void CThread::QMsgSnd( STR_MessageData *pMessageData, void *pArrayMsgData, const char *pszThreadName )
{

    if( pArrayMsgData != NULL ) {
        pMessageData->iArrayIndex = PushLanData( pArrayMsgData, pMessageData->uiArrayLength );

    }

    if( pMessageData->uiArrayLength == 0 || pMessageData->iArrayIndex != -1 ) {
        QMsgSnd( pMessageData, pszThreadName );
    }

}

/**
 * @brief		큐 메시지로 데이터를 전송한다.
 * @param		STR_MessageData * pMessageData
 * @return		void
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2021/11/10 12:07:00
 * @warning
 */
void CThread::QMsgSnd( STR_MessageData *pMessageData, const char *pszThreadName )
{

    if( pMessageData->uiEchoBit == 1 ) {
        // LOGMSG4( enDebug, "[%s] ==> [%s]...[%d:%d]", pszThreadName, m_szThreadName, pMessageData->uiOpCode, pMessageData->uiArrayLength );
    }
    else {
        LOGMSG4( enDebug, "@[%s] ==> [%s]...[%d:%d]", pszThreadName, m_szThreadName, pMessageData->uiOpCode, pMessageData->uiArrayLength );
    }

#ifdef __linux__
    if( msgsnd( m_MsgKeyID, (void *) pMessageData, sizeof(STR_MessageData)-sizeof(long), IPC_NOWAIT) < 0 ) {
        perror( "msgsnd 실패" );

        SendTaskMngr( enERROR_OF_SENDMSG );
    }
    else {
        // DisplayMsg( true, m_szThreadName, pMessageData );

    }

#elif defined(_MSC_VER)
    Lock();
	m_queue.push(*pMessageData);
    UnLock();

    //TRACE( "\nQueue Size : %d" , m_queue.size() );

	::SetEvent(m_hEvent);

    DisplayMsg( true, m_szThreadName, pMessageData );

#elif defined(__VXWORKS__)
    STATUS stat=msgQSend( GetKeyId(), (char *) pMessageData, sizeof(STR_MessageData), NO_WAIT, MSG_PRI_NORMAL );
    if( stat == ERROR ) {
        // 메시지 송신 에러시 타스크 관리자에게 메시지 전달하여 긴급 복구하도록 메시지 전달함.

        SendTaskMngr( enERROR_OF_SENDMSG, pszThreadName );
    }
    else {
        // DisplayMsg( true, m_szThreadName, pMessageData );

    }

#endif

}

// void CThread::QWaitMsgUntillEmpty()
// {
// #ifdef __linux__
//
//
// #elif _MSC_VER
//     Lock();
//     m_queue.clear();
//     UnLock();
//
//     //TRACE( "\nQueue Clear..." );
//
// #elif __VXWORKS__
//
// #endif
// }

/**
 * @brief		SendTaskMngr
 * @param		unsigned int uiErrorCode
 * @param		const char * pszThreadName
 * @return		void
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2022/02/09 11:25:21
 * @warning
 */
void CThread::SendTaskMngr( unsigned int uiErrorCode, const char *pszThreadName )
{
    unsigned int i;
    CThread *pThis=NULL;

    STR_MessageData stMessageData;

    for( i=0 ; i < g_vecThread.size() ; ++i ) {
        pThis = g_vecThread[i];
        if( typeid( *pThis ) == typeid(CTaskMngr) ) {
            stMessageData.uiOpCode = enSYSERROR;
            stMessageData.x.uiData = uiErrorCode;
            pThis->QMsgSnd( & stMessageData, pszThreadName );
            break;
        }
    }

    if( g_vecThread.size() <= i ) {
        while( true ) {
            printf( "\n 타스크 관리자 객체가 없습니다.");
			msSleep( 2000 );
        }

    }


}

/**
 * @brief		msSleep
 * @param		int mssleep
 * @return		void
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2021/11/23 10:17:49
 * @warning
 */
void CThread::msSleep( unsigned int mssleep )
{
#ifdef __linux__
    sleep( mssleep );
#elif defined(_MSC_VER)
    ResetEvent( m_hSleepEvent );
    ::WaitForSingleObject( m_hSleepEvent, mssleep );

#elif defined(__VXWORKS__)
    int iDelay=mssleep / ( 1000 / g_iClkTickPerSecond );

    if( iDelay == 0 ) {
        iDelay = 1;
    }

    taskDelay( iDelay );
#else

#endif
}

/**
 * @brief     쓰레드 간의 메시지를 출력한다.
 * @param     bool bSend
 * @param     const char * pszClassName
 * @param     STR_MessageData * pInMsg
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-03-25, 15:37
 * @warning
 */
void CThread::DisplayMsg( bool bSend, const char *pszClassName, STR_MessageData *pInMsg )
{
    char buffer[200];

    std::string strMessage;

    STR_MessageData *pMsg;

    if( bSend == true ) {
        if( pInMsg != NULL ) {
            pMsg = pInMsg;
        }
        else {
            pMsg = & m_SndMsg;
        }
    }
    else {
        pMsg = & m_RcvMsg;
    }

    // opcode 에 따른 명령어 파싱
    CCommonUtils::MakeStringMessage( &strMessage, pMsg->uiOpCode );

    if( bSend == false ) {
        if( pMsg->uiDataLength == sizeof(int) ) {
            sprintf( buffer, ">>수신: [%12s]서 Op[%s:0x%04X], Len[%d], Idx[%d], D[%d]" , m_szThreadName, strMessage.c_str(), pMsg->uiOpCode, pMsg->uiDataLength, pMsg->iArrayIndex, pMsg->x.uiData );
        }
        else {
            sprintf( buffer, ">>수신: [%12s]서 Op[%s:0x%04X], Len[%d], Idx[%d]" , m_szThreadName, strMessage.c_str(), pMsg->uiOpCode, pMsg->uiDataLength, pMsg->iArrayIndex );
        }

    }
    else {
        if( pMsg->uiDataLength == sizeof(int) ) {
            sprintf( buffer, "<<송신: [%12s]로 Op[%s:0x%04X], Len[%d], Idx[%d], D[%d]" , m_szThreadName, strMessage.c_str(), pMsg->uiOpCode, pMsg->uiDataLength, pMsg->iArrayIndex, pMsg->x.uiData );
        }
        else {
            sprintf( buffer, "<<송신: [%12s]로 Op[%s:0x%04X], Len[%d], Idx[%d]" , m_szThreadName, strMessage.c_str(), pMsg->uiOpCode, pMsg->uiDataLength, pMsg->iArrayIndex );
        }
    }

    LOGMSG1( enDebug, "%s" , buffer );

}


/**
 * @brief     ShowTaskMessae
 * @param     int iLevel
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-03-07 13:35:22
 * @warning
 */
void CThread::ShowTaskMessae( int iLevel )
{
    LOGMSG1( enNormal, "[%s]", m_szThreadName );

#ifdef _MSC_VER

#elif defined(__VXWORKS__)
    // msgQShow( m_MsgKeyID, iLevel );

#elif __linux__

#endif

}

/**
 * @brief     ShowQueueMessae
 * @param     int iLevel
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-03-07 13:35:24
 * @warning
 */
void CThread::ShowQueueMessae( int iLevel )
{
    LOGMSG1( enNormal, "[%s]", m_szThreadName );

#ifdef _MSC_VER
    Lock();
    LOGMSG1( enNormal, "\t처리할 메시지 큐 개수: %d", m_queue.size() );
    UnLock();

#elif defined(__VXWORKS__)
    msgQShow( m_MsgKeyID, iLevel );

#elif __linux__

#endif

}

/**
 * @brief     SendThreadMessage
 * @param     CThread * pThread
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-03-07 14:25:33
 * @warning
 */
void CThread::SendThreadMessage( CThread *pThread, bool bWait )
{

#if 1
    pThread->QMsgSnd( GetParentMessage()->uiOpCode, GetThreadName() );

#else
    pThread->QMsgEchoSnd( GetParentMessage()->uiOpCode, GetThreadName() );

    if( bWait == true ) {
        TRACE( "\n[Wait...%s]", pThread->GetThreadName() );
        QMsgRcv( enTIMER, 5000 );
    }
#endif

}

/**
 * @brief     SendEchoMessage
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-03-07 16:03:05
 * @warning
 */
void CThread::SendEchoMessage()
{

    if( GetParentMessage()->uiEchoBit == ECHO ) {
        TRACE( " Send Echo Message..." );
        SendThreadMessage( g_pTheTaskMngr, false );

    }

}