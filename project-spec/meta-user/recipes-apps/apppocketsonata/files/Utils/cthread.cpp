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




// 타스크 및 쓰레드 포인터
vector<CThread *> g_vecThread;

// 클래스 내의 정적 멤버변수 값 정의
int CThread::m_iCoThread = 0;
int CThread::m_iCoMsgQueue = 0;

bool CThread::m_bSendEnable = false;


/**
 * @brief     CThread
 * @return
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-04-30 15:16:25
 * @warning
 */
CThread::CThread() : CArrayMsgData( false ), CLogName()
{
#ifdef _MSC_VER
    m_hEvent = NULL;
    m_hSleepEvent = NULL;
#endif

    m_bLog = false;

}

/**
 * @brief     CThread
 * @param     int iThreadPriority
 * @param     const char * pThreadName
 * @param     bool bArrayLanData
 * @param     bool bCreateOnlyThread
 * @return
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-08-29 10:38:21
 * @warning
 */
CThread::CThread( int iThreadPriority, const char *pThreadName, bool bArrayLanData, bool bCreateOnlyThread ) : CArrayMsgData( bArrayLanData ), CLogName( pThreadName )
{

    m_bLog = false;

    g_iKeyId++;

    m_iPriority = -1;

    m_bThreadLoop = true;

    m_bSendEnable = true;

    strcpy( m_szThreadName, pThreadName );

    // 송신 메시지 데이터 정의
    m_pstrCollectInfo = m_uniMsgData.GetCollectInfo();
    m_pstrDetectAnalInfo = m_uniMsgData.GetDetectAnalInfo();
    m_pstrTrackAnalInfo = m_uniMsgData.GetTrackAnalInfo();
    m_pstrScanAnalInfo = m_uniMsgData.GetScanAnalInfo();

    // 수신 메시지 데이터 정의
    m_pRecvCollectInfo = m_RcvMsg.x.GetCollectInfo();
    m_pRecvDetectAnalInfo = m_RcvMsg.x.GetDetectAnalInfo();
    m_pRecvTrackAnalInfo = m_RcvMsg.x.GetTrackAnalInfo();
    m_pRecvScanAnalInfo = m_RcvMsg.x.GetScanAnalInfo();

#ifdef _MSC_VER
    m_pThreadFunc = CThread::EntryPoint;

    // 메시지 큐
	m_hEvent = CreateEvent( NULL, FALSE, FALSE, pThreadName );
    if( m_hEvent == NULL ) {
        //Log( enError, "Warning: CreateEvent failed in CThread::CThread..." , m_szThreadName );
    }
    else {
        ++ m_iCoMsgQueue;
    }

    // Sleep 큐
    m_hSleepEvent = CreateEvent( NULL, FALSE, FALSE, pThreadName );
    if( m_hSleepEvent == NULL ) {
        //Log( enError, "Warning: CreateEvent failed in CThread::CThread::Sleep..." , m_szThreadName );
    }

    //Log( enDebug, "Create the task[%s] & queue ID[%d] ..." , m_szThreadName, m_hEvent );

#elif defined(__VXWORKS__)
    m_iPriority = iThreadPriority;
    m_MsgKeyID = 0;
    m_bTaskRunStat = false;

    // 메시지 큐 생성
    m_MsgKeyID = msgQCreate( SIZE_OF_MSGDATA_ARRAY, sizeof( STR_MessageData), MSG_Q_FIFO );
    if( m_MsgKeyID == NULL ) {
        printf( "\n큐 ID[%d]를 생성 실패했습니다 !" , m_MsgKeyID );
        while( true );
    }
    else {
        //printf( "\n큐 ID[%d]를 생성합니다." , m_MsgKeyID );
        // msgQShow( m_MsgKeyID, 1 );
        ++ m_iCoMsgQueue;
    }
    //printf( "\nCreate the task[%s] & queue ID[%d] ..." , m_szThreadName, m_MsgKeyID );

#elif defined(__linux__)
    m_MsgKeyID = 0;

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
        // Log( enDebug, "큐 ID[%d]를 생성합니다." , m_MsgKeyID );
        ++ m_iCoMsgQueue;
    }
    while( QMsgRcv( enNO_WAIT ) != -1 );

    Log( enDebug, "Create the task[%s] & queue ID[%d] ..." , m_szThreadName, m_MsgKeyID );

#else
#error 이 소스는 현재 플레폼에 지원하지 않습니다. 개발자에게 문의하세요..
#endif

    Init();

    // 스레드 벡터에 삽입하기
    g_vecThread.push_back( this );

}

/**
 * @brief     ~CThread
 * @return
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-04-30 16:11:37
 * @warning
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
            Log( enDebug, "\t 큐 ID[%d]를 종료 처리합니다." , m_MsgKeyID );
        }
    }

#elif defined(_MSC_VER)
    // QMsgSnd( enTHREAD_EXIT, m_szThreadName );

    //delete m_pTheMessageQueue;



#elif defined(__VXWORKS__)

    // sem_destroy( & m_mutex );


#else

#endif

    // 1. 쓰레드를 죽인다.
#ifdef _MSC_VER
    if ( m_MainThread.m_hThread ) {
        CThread::StopThread();

        if( m_hEvent != 0 ) {
            CloseHandle( m_hEvent );
            -- m_iCoMsgQueue;
        }

        if( m_hSleepEvent != 0 ) {
            CloseHandle( m_hSleepEvent );
        }

        //Log( enDebug, "[%s]를 종료 처리합니다." , m_szThreadName );
    }

#elif defined(__VXWORKS__)
    printf( "[%s]를 종료 처리합니다." , m_szThreadName );

#else
    if( m_MainThread != 0 ) {
        -- m_iCoThread;

        pthread_cancel( m_MainThread );
        //Pend();
        printf( "[%s]를 종료 처리합니다." , m_szThreadName );

        //Stop();
    }
#endif

#ifdef _LOG_
    if( g_pTheLog != NULL && this != g_pTheLog ) {
        g_pTheLog->UnLock();
    }

#endif

    //
    // g_vecThis.erase( this );

    //Log( enDebug, "\t 쓰레드 [%d개], 큐 [%d개] 가 남아 있습니다." , m_iCoThread, m_iCoMsgQueue );

}

/**
 * @brief     Init
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-03-27 10:08:57
 * @warning
 */
void CThread::Init()
{
    m_pszRecvData = NULL;

    // 메시지큐 생성
    memset( & m_RcvMsg, 0, sizeof( STR_MessageData ) );

}

/**
 * @brief     Clear
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-12-27 15:14:12
 * @warning
 */
void CThread::Clear()
{
    CArrayMsgData::Clear();

}


/**
 * @brief     CallBack
 * @param     void * pArg
 * @return    void *
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-04-30 16:11:26
 * @warning
 */
void *CThread::CallBack( void *pArg )
{
    CThread *pThread = reinterpret_cast<CThread*> (pArg);

    if( pThread == NULL ) {
        // LOGMSG( enError, "함수 인자 포인터가 널 값 입니다. 인자를 객체 포인터로 입력해줘야 합니다." );
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

		//Log( enNormal, "The [%s] is stopped the the main loop...", pThread->m_szThreadName );
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

    //LOGMSG4( enDebug, "Create the task[%s] ID[%d/%d] & queue ID[%d] ..." , m_szThreadName, m_TaskID, m_iPriority, m_hEvent );

#elif defined(_MSC_VER)
    // 쓰레드 생성
    Attach( (LPTHREAD_START_ROUTINE) pFunc );
    Start();

#elif defined(__VXWORKS__)
    // 타스크 큐 생성
    // m_iPriority = GetPriorityByThreadName();
    m_TaskID = taskSpawn( m_szThreadName, GetPriority(), \
        VX_STDIO|VX_SUPERVISOR_MODE|VX_FP_TASK|VX_ALTIVEC_TASK, GetStackSize(), \
        (FUNCPTR) *pFunc, (int) this, 0, 0, 0, 0, 0, 0, 0, 0, 0 );
    if( m_TaskID != TASK_ID_ERROR ) {
        m_bTaskRunStat = true;
    }

    Log( enDebug, "타스크/쓰레드 (우선 순위[%3d]) 생성 ...", m_iPriority );
    // printErrno( errnoGet() );
	//LOG_LINEFEED;

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
    m_bThreadLoop = false;

#ifdef _MSC_VER
    if ( m_MainThread.m_hThread ) {
        GetExitCodeThread(m_MainThread.m_hThread, & m_MainThread.m_dwExitCode );

        if ( m_MainThread.m_dwExitCode == STILL_ACTIVE ) {
            HANDLE hThread;

            // 로그 관련 CriticalSection 락을 푼다.
            TRACE( "CThread::Stop" );
            SetEvent( m_hEvent );

#ifdef _LOG_
            while( g_pTheLog->IsLock() == true ) {
				CThread::msSleep(10);
                TRACE( "*" );
            }
#endif

            hThread = m_MainThread.m_hThread;

            // TerminateThread( m_MainThread.m_hThread, 0 ); //DWORD(-1));

            WaitForSingleObject( hThread, 1000 );



            CloseHandle( hThread );

            m_MainThread.m_hThread = NULL;

            // ExitThread( 0 );
            -- m_iCoThread;
        }
        else {
            m_MainThread.m_hThread = NULL;
        }


    }
#elif defined(__VXWORKS__)
    -- m_iCoThread;

    taskDelete( m_TaskID );

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

}

/**
 * @brief CThread::TCleanUpHandler
 * @param arg
 */
void CThread::TCleanUpHandler(void *arg )
{
    printf("cleanup \n");
    WhereIs;
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
    CLock::Lock();
    while( !m_queue.empty() ) {
        m_queue.pop();
    }
    CLock::UnLock();

#elif defined(__VXWORKS__)
    int noError;

    do {
		//STATUS stat;

        msgQReceive( m_MsgKeyID, ( char* ) &m_RcvMsg, sizeof( STR_MessageData ), WAIT_FOREVER );
        noError = errnoGet();
        // printf( "\n stat[%d], noError[%d]", stat, noError );

    } while( noError != S_objLib_OBJ_TIMEOUT );

#elif defined(__linux__)
    printf( "큐 메시지를 클리어 하도록 구현해야 합니다." );

#endif

    return;
}

/**
 * @brief     QMsgRcv
 * @param     ENUM_RCVMSG enFlag
 * @param     DWORD dwMilliSec
 * @return    int
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-05-14 14:17:51
 * @warning
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

    iMsgRcv = msgrcv( m_MsgKeyID, (void *) & m_RcvMsg, sizeof( struct STR_MessageData)-sizeof(long), 1 /* (1 >> 1)*/, iFlag );

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
            CLock::Lock();
            if( m_queue.size() != 0 ) {
                iMsgRcv = 1;

                m_RcvMsg = m_queue.front();

                if( m_RcvMsg.iArrayIndex != -1 ) {
                    m_pszRecvData = (char *) m_szRecvData;
                    //memcpy( m_szRecvData, m_RcvMsg.szArrayData, m_RcvMsg.uiArrayLength );
                    PopLanData(m_szRecvData, m_RcvMsg.iArrayIndex, m_RcvMsg.uiArrayLength);
                }
                else {
                    m_pszRecvData = NULL;
                }

                m_queue.pop();
            }
            CLock::UnLock();

        }
        else if( dwRes == WAIT_FAILED ) {

        }
        else {
        }
    }
    else {
        int iSize;

        CLock::Lock();
        iSize = (int) m_queue.size();
        CLock::UnLock();

//         if( iSize >= 10 /* SIZE_OF_MSGDATA_ARRAY */ ) {
//             TRACE( "\n 큐 사이즈가 초과[%d] 되고 있습니다." , iSize );
//         }

        if( iSize == 0 ) {
            if (enFlag == enTIMER) {
                dwRes = ::WaitForSingleObject(m_hEvent, dwMilliSec);
            }
            else {
#if defined(_DEBUG) && defined(_WIN64)
                if( strcmp( GetThreadName(), "CCU_O1" ) == 0 ) {
                    TRACE( "\n m_hEvent[%p]", m_hEvent );
                }
#endif
                dwRes = ::WaitForSingleObject(m_hEvent, INFINITE);
            }

            if( dwRes == WAIT_FAILED || m_bThreadLoop == false ) {
                iMsgRcv = -1;
                TRACE( "\nCThread[%s]..ResetEvent..", GetThreadName() );
            }
            else if( dwRes == WAIT_ABANDONED ) {
                ::ResetEvent( m_hEvent );
                //TRACE( "\nCThread[%s]..ResetEvent..", GetThreadName() );
            }
            else if (dwRes == WAIT_TIMEOUT ) {
				iMsgRcv = 1;

				m_RcvMsg.uiOpCode = enTHREAD_TIMER;
				m_RcvMsg.soSocket = 0;

                m_pszRecvData = NULL;

            }
            else if( dwRes == WAIT_OBJECT_0 ) {
#if defined(_DEBUG) && defined(_WIN64)
                if( strcmp( GetThreadName(), "TASKMNGR" ) == 0 ) {
                    TRACE( "\n TASKMNGR..." );
                    WhereIs;
                }

#endif
                //TRACE( "\nCThread[%s]..ResetEvent..", GetThreadName() );

                // 처리 한다.
                CLock::Lock();
                ::ResetEvent( m_hEvent );

                iSize = (int) m_queue.size();
                if( iSize != 0 ) {
                    iMsgRcv = 1;

                    m_RcvMsg = m_queue.front();

                    if( m_RcvMsg.iArrayIndex != -1 ) {
                        m_pszRecvData = (char *) m_szRecvData;
                        //memcpy( m_szRecvData, m_RcvMsg.szArrayData, m_RcvMsg.uiArrayLength );
#if defined(_DEBUG) && defined(_WIN64)
                        if( strcmp( GetThreadName(), "MRG" ) == 0 ) {
                            TRACE( "PopLanData=[%d]\n", m_RcvMsg.iArrayIndex );
                        }
#endif
                        PopLanData( m_szRecvData, m_RcvMsg.iArrayIndex, m_RcvMsg.uiArrayLength );
                    }
                    else {
                        m_pszRecvData = NULL;
                    }

                    m_queue.pop();

                }
                else {
                    iMsgRcv = -1;
                    // TRACE( "Invalid the receive message..." );
                }
                CLock::UnLock();

                //STR_CLIENT_SOCKET *pClientSocket;
                //pClientSocket = ( STR_CLIENT_SOCKET * ) & m_RcvMsg.x.szData;

                //TRACE( "\nCThread[%s] Wait...OpCode[0x%0x], 소켓[%d] 크기[%d]", GetThreadName(), m_RcvMsg.uiOpCode, pClientSocket->iSocket, iSize );
            }
            else {
            }

        }
        else {
            CLock::Lock();
            m_RcvMsg = m_queue.front();
            m_queue.pop();
            CLock::UnLock();

            iMsgRcv = 1;

            //STR_CLIENT_SOCKET *pClientSocket;
            //pClientSocket = ( STR_CLIENT_SOCKET * ) & m_RcvMsg.x.szData;
            //TRACE( "\nCThread[%s] Loop...OpCode[0x%0x], 소켓[%d] 크기[%d]", GetThreadName(), m_RcvMsg.uiOpCode, pClientSocket->iSocket, iSize );

            if( m_RcvMsg.iArrayIndex != -1 ) {
                m_pszRecvData = (char *) m_szRecvData;
                //memcpy( m_szRecvData, m_RcvMsg.szArrayData, m_RcvMsg.uiArrayLength );
                PopLanData( m_szRecvData, m_RcvMsg.iArrayIndex, m_RcvMsg.uiArrayLength );
            }
            else {
                m_pszRecvData = NULL;
            }
        }

    }

#elif defined(__VXWORKS__)
    _Vx_ticks_t option;

    if( enFlag == enWAIT_FOREVER ) {
        option = WAIT_FOREVER;
    }
    else {
        option = dwMilliSec;
    }

    STATUS stat = msgQReceive( m_MsgKeyID, (char *) & m_RcvMsg, sizeof( STR_MessageData), option );
    if( ERROR == stat ) {
        int noError = errnoGet();

        if( noError == S_objLib_OBJ_TIMEOUT ) {
            iMsgRcv = 1;

            m_RcvMsg.uiOpCode = enTHREAD_TIMER;
            m_RcvMsg.soSocket = 0;
            //m_RcvMsg.uiEchoBit = 0;
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

            PopLanData( m_szRecvData, m_RcvMsg.iArrayIndex, m_RcvMsg.uiArrayLength );
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
void CThread::QMsgSnd( unsigned int uiOpCode, void *pData, unsigned int uiDataLength, const char *pszClassName, int iOption )
{

    if( uiDataLength <= sizeof( UNI_MSG_DATA ) ) {
        QMsgSnd( uiOpCode, NULL, 0, 0, pData, uiDataLength, pszClassName, iOption );
    }
    else {
        QMsgSnd( uiOpCode, pData, 1, uiDataLength, NULL, 0, pszClassName, iOption );

    }

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
void CThread::QMsgSnd( unsigned int uiOpCode, const char *pszClassName, int iOption )
{
    QMsgSnd( uiOpCode, NULL, 0, 0, NULL, 0, pszClassName, iOption );

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
void CThread::QMsgSnd( unsigned int uiOpCode, void *pArrayMsgData, unsigned int uiArrayLength, void *pData, unsigned int uiDataLength, const char *pszClassName, int iOption )
{
    QMsgSnd( uiOpCode, pArrayMsgData, uiArrayLength, _spOne, pData, uiDataLength, pszClassName, iOption );

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
void CThread::QMsgSnd( unsigned int uiOpCode, void *pArrayMsgData, unsigned int uiArrayElement, unsigned int uiArraySize, void *pData, unsigned int uiDataLength, const char *pszClassName, int iOption )
{
    STR_MessageData sndMsg;

#ifdef __linux__
    sndMsg.mtype = 1;
#endif

    // 1. OPCODE 저장
    sndMsg.uiOpCode = uiOpCode;
    sndMsg.soSocket = 0;

    // 2. 데이터 저장
    if( pData != NULL ) {
   		sndMsg.uiDataLength = uiDataLength;
        memcpy( & sndMsg.x, pData, uiDataLength );
    }
    else {
    	sndMsg.uiDataLength = 0;
    }

    // 3. 추가 데이터 저장
    if( pArrayMsgData != NULL ) {
    	sndMsg.uiArrayLength = uiArrayElement * uiArraySize;
        //memcpy( & sndMsg.szArrayData, pArrayMsgData, sndMsg.uiArrayLength );

        sndMsg.iArrayIndex = PushLanData(pArrayMsgData, sndMsg.uiArrayLength);
        if( strcmp( GetThreadName(), "MRG" ) == 0 ) {
#ifdef _MSC_VER
            //TRACE( "PushLanData=[%d]\n", sndMsg.iArrayIndex );
            //PrintDebug( (unsigned int) -1 );
#endif
        }
    }
    else {
    	sndMsg.uiArrayLength = 0;
    	sndMsg.iArrayIndex = -1;
    }

    QMsgSnd( & sndMsg, pszClassName, iOption );

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

    QMsgSnd( pMessageData, pszThreadName );


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
void CThread::QMsgSnd( STR_MessageData *pMessageData, const char *pszThreadName, int iOption )
{

    if( IsSendEnabled() == true ) {
#ifdef __linux__
        if( msgsnd( m_MsgKeyID, (void *) pMessageData, sizeof( struct STR_MessageData)-sizeof(long), IPC_NOWAIT) < 0 ) {
            perror( "msgsnd 실패" );
            WhereIs;
            SendTaskMngr( enERROR_OF_SENDMSG );
        }
        else {
            // DisplayMsg( true, m_szThreadName, pMessageData );

        }

#elif defined(_MSC_VER)
        CLock::Lock();
	    m_queue.push(*pMessageData);
        ::SetEvent( m_hEvent );
        CLock::UnLock();


        //TRACE( "\nQueue Size : %d" , m_queue.size() );
        //TRACE( "\nCThread[%s]..SetEvent[%d]", GetThreadName(), m_hEvent );
        //DisplayMsg( true, m_szThreadName, GetThreadName(), pMessageData );

#elif defined(__VXWORKS__)
        STATUS stat=msgQSend( GetKeyId(), (char *) pMessageData, sizeof( STR_MessageData), iOption, MSG_PRI_NORMAL );
        if( stat == ERROR ) {
            // 메시지 송신 에러시 타스크 관리자에게 메시지 전달하여 긴급 복구하도록 메시지 전달함.
            _func_kprintf( "GetThreadName()=%s", GetThreadName() );
            WhereIs;
            SendTaskMngr( enERROR_OF_SENDMSG, pszThreadName );
        }
        else {
            //printf( "\n SnedOpcode[%d]", pMessageData->uiOpCode );
            //DisplayMsg( true, m_szThreadName, GetThreadName(), pMessageData );

        }

#endif

    }
    else {

    }

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

    STR_MessageData stMessageData;      // 의심

    memset( & stMessageData, 0, sizeof( STR_MessageData ) );

    for( i=0 ; i < g_vecThread.size() ; ++i ) {
        pThis = g_vecThread[i];
        if( typeid( *pThis ) == typeid(CTaskMngr) ) {
            stMessageData.uiOpCode = enREQ_SYSERROR;
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
void CThread::DisplayMsg( bool bSend, const char *pszFromClassName, const char *pszToClassName, STR_MessageData *pInMsg )
{
#if defined(__VXWORKS__) || defined(_WIN64)
    STR_MessageData *pMsg;

    if( pszFromClassName != NULL && strcmp( pszFromClassName, PCIISR_NAME ) != 0 ) {

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

        char buffer[300];

        std::string strMessage;

        // opcode 에 따른 명령어 파싱
        CCommonUtils::MakeStringMessage( &strMessage, pMsg->uiOpCode, bSend );

        if( bSend == false ) {
            if( pMsg->uiDataLength == sizeof(int) ) {
                sprintf( buffer, ">>수신: [%15s]에서 [%15s]로 Op[%s:0x%04X], Len[%d], D[%d]" , pszFromClassName, pszToClassName, strMessage.c_str(), pMsg->uiOpCode, pMsg->uiDataLength, pMsg->x.uiData );
            }
            else {
                sprintf( buffer, ">>수신: [%15s]에서 [%15s]로 Op[%s:0x%04X], Len[%d]" , pszFromClassName, pszToClassName, strMessage.c_str(), pMsg->uiOpCode, pMsg->uiDataLength );
            }

        }
        else {
            if( pMsg->uiDataLength == sizeof(int) ) {
                sprintf( buffer, "<<송신: [%15s]에서 [%15s]로 Op[%s:0x%04X], Len[%d], D[%d]" , pszFromClassName, pszToClassName, strMessage.c_str(), pMsg->uiOpCode, pMsg->uiDataLength, pMsg->x.uiData );
            }
            else {
                sprintf( buffer, "<<송신: [%15s]에서 [%15s]로 Op[%s:0x%04X], Len[%d]" , pszFromClassName, pszToClassName, strMessage.c_str(), pMsg->uiOpCode, pMsg->uiDataLength );
            }
        }

        TRACE( "%s", buffer );
        //Log( enNormal, "%s", buffer );
    }

    else {
    }

#endif



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
void CThread::ShowTaskMessae( int iLevel, bool bLog )
{
    if( bLog == true ) {
        TRACE( "\n[%s]", m_szThreadName );
    }

#ifdef _MSC_VER

#elif defined(__VXWORKS__)
    taskShow( m_TaskID, iLevel );

#elif __linux__

#endif

}

/**
 * @brief     큐 메시지 크기를 리턴합니다.
 * @return    int
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-03-26 14:50:49
 * @warning
 */
int CThread::QMsgRcvSize()
{
    int iSize;

#ifdef _MSC_VER
    CLock::Lock();
    iSize = ( int ) m_queue.size();
    CLock::UnLock();

#elif defined(__VXWORKS__)
    iSize = msgQNumMsgs( m_MsgKeyID );

#elif defined(__linux__)
    printf( "QMsgRcvSize() 큐 메시지 크기를 구현해야 합니다." );
    iSize = 0;

#endif

    return iSize;

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
void CThread::ShowQueueMessae( int iLevel, bool bLog )
{
    if( bLog == true ) {
        TRACE( "\n[%s]", m_szThreadName );
    }

#ifdef _MSC_VER
    CLock::Lock();
    //Log( enNormal, "\t처리할 메시지 큐 개수: %d", m_queue.size() );
    CLock::UnLock();

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
        QMsgRcv( enTIMER, OS_SEC(5) );
    }
#endif

}

/**
 * @brief     SendThreadMessage
 * @param     CThread * pThread
 * @param     unsigned int uiOpCode
 * @param     bool bWait
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-07-25 20:38:08
 * @warning
 */
void CThread::SendThreadMessage( CThread *pThread, unsigned int uiOpCode, bool bWait )
{

#if 1
    pThread->QMsgSnd( uiOpCode, GetThreadName() );

#else
    pThread->QMsgEchoSnd( uiOpCode, GetThreadName() );

    if( bWait == true ) {
        TRACE( "\n[Wait...%s]", pThread->GetThreadName() );
        QMsgRcv( enTIMER, OS_SEC( 5 ) );
    }
#endif

}

/**
 * @brief		ChangeTaskPriority
 * @param		int iPriority
 * @return		void
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2023/04/05 16:31:59
 * @warning
 */
void CThread::ChangeTaskPriority( int iPriority )
{

#ifdef __VXWORKS__
    STATUS status;

    // m_iPriority
    status = taskPrioritySet( m_TaskID, iPriority );
    if( status == OK ) {
        Log( enDebug, "[%s]타스크의 우선순위[%d]를 [%d]로 변경합니다.", GetThreadName(), m_iPriority, iPriority );

        m_iPriority = iPriority;
    }
    else {
        Log( enError, "[%s]타스크의 우선순위[%d]를 [%d]로 변경 실패했습니다.", GetThreadName(), m_iPriority, iPriority );
    }

#else
    Log( enDebug, "[%s]타스크의 우선순위를 [%d]로 변경합니다.", GetThreadName(), iPriority );

#endif

}


/**
 * @brief     GetCoThread
 * @return    int
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2024-01-02 11:39:44
 * @warning
 */
int CThread::GetCoThread()
{
    return (int) g_vecThread.size(); /* m_iCoThread; */
}

#ifdef _MSC_VER
void CThread::FlushEvent()
{
    ::SetEvent( m_hEvent );

}

#endif

