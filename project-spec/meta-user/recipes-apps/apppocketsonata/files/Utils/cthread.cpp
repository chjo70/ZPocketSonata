/****************************************************************************************
 파 일 명 : programrev.c
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

#include "stdafx.h"

#ifdef _MSC_VER

#elif __VXWORKS__
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
CThread::CThread( int iThreadID, char *pThreadName, bool bArrayLanData, bool bCreateOnlyThread ) : CArrayMsgData( bArrayLanData )
{

    m_bMainLoop = true;

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
	
#elif __VXWORKS__
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

#elif __linux__
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
    g_vecThis.push_back( this );

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
        Stop();
        
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

    g_pTheLog->UnLock();

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
    CThread *pThhread = reinterpret_cast<CThread*> (pArg);

    if( pThhread == NULL ) {
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
        pThhread->_routine();

#endif
    }

    LOGMSG1( enNormal, "The [%s] is stopped the the main loop...", pThhread->m_szThreadName );

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
void CThread::Run( void *(*pFunc)(void*), key_t key )
{
    m_bMainLoop = true;

#ifdef __linux__
    pthread_create( & m_MainThread, NULL, pFunc, this );

    LOGMSG4( enDebug, "Create the task[%s] ID[%d/%d] & queue ID[%d] ..." , m_szThreadName, m_TaskID, m_iPriority, m_hEvent );

#elif _MSC_VER

    // 쓰레드 생성
    Attach( (LPTHREAD_START_ROUTINE) pFunc );
    Start();    
    
#elif __VXWORKS__        
   
    // 타스크 큐 생성
    m_iPriority = GetPriorityByThreadName();
    m_TaskID = taskSpawn( m_szThreadName, GetPriority(), VX_STDIO|VX_SUPERVISOR_MODE, GetStackSize(), (FUNCPTR) *pFunc, (int) this, 0, 0, 0, 0, 0, 0, 0, 0, 0 );
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
 * @brief CThread::Run
 */
void CThread::Run(key_t key)
{
    Run( CallBack, key );

}

/**
 * @brief CThread::Pend
 * @return
 */
int CThread::Pend()
{
    //void *pStatus;
    //int iStatus[100];
    int iStatus=0;

#ifdef _MSC_VER
#elif __VXWORKS__    
#else    
    iStatus = pthread_join( m_MainThread, /* (void **) & iStatus[0] */ NULL );
    
#endif    

    return iStatus;
}

/**
 * @brief CThread::Stop
 */
void CThread::Stop()
{
#ifdef _MSC_VER
    if ( m_MainThread.m_hThread ) {
        GetExitCodeThread(m_MainThread.m_hThread, & m_MainThread.m_dwExitCode );

        if ( m_MainThread.m_dwExitCode == STILL_ACTIVE ) {
            HANDLE hThread;

            // 로그 관련 CriticalSection 락을 푼다.
            TRACE( "Stop::" );
            while( g_pTheLog->IsLock() == true ) {
                Sleep(10);
                TRACE( "*" );
            }

            hThread = m_MainThread.m_hThread;
            m_MainThread.m_hThread = NULL;
            TerminateThread( hThread, DWORD(-1));

            -- m_iCoThread;
        }
        else {
            m_MainThread.m_hThread = NULL;
        }

        
    }
#elif __VXWORKS__

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

    m_bMainLoop = false;

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
 * @brief CThread::QMsgRcv
 * @return
 */
int CThread::QMsgRcv( ENUM_RCVMSG enFlag )
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
            dwRes = ::WaitForSingleObject(m_hEvent, INFINITE );

            if( dwRes == WAIT_FAILED ) {
                
            }
            else if( dwRes == WAIT_ABANDONED ) {
                ResetEvent( m_hEvent );
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
        }
        else {
            //Lock();
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
            }
            else {
                TRACE( "AAAA" );
            }
        }

    }
   
    UnLock();

#elif __VXWORKS__
    _Vx_ticks_t option;

    if( enFlag == enWAIT_FOREVER ) {
        option = WAIT_FOREVER;        
    }
    else {
        option = NO_WAIT;        
    }

    STATUS stat = msgQReceive( m_MsgKeyID, (char *) & m_RcvMsg, sizeof(STR_MessageData), option );
    if( ERROR == stat ) {
        int noError = errnoGet();

        if( noError != S_objLib_OBJ_TIMEOUT ) {
            // printErrno( noError );
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
 * @brief CThread::QMsgSnd
 * @param uiOpCode
 * @param pData
 * @param uiDataLength
 */
void CThread::QMsgSnd( unsigned int uiOpCode, void *pData, unsigned int uiDataLength )
{

    QMsgSnd( uiOpCode, NULL, 0, pData, uiDataLength );
}

/**
 * @brief CThread::QMsgSnd
 * @param uiOpCode
 */
void CThread::QMsgSnd( unsigned int uiOpCode, const char *pszClassName )
{

    QMsgSnd( uiOpCode, NULL, 0, NULL, 0, pszClassName );
}

/**
 * @brief CThread::QMsgSnd
 * @param uiOpCode
 * @param pArrayMsgData
 * @param uiLength
 */
void CThread::QMsgSnd( unsigned int uiOpCode, void *pArrayMsgData, unsigned int uiArrayLength, void *pData, unsigned int uiDataLength, const char *pszClassName )
{
    STR_MessageData sndMsg;

#ifdef __linux__    
    sndMsg.mtype = 1;
#endif
    
    sndMsg.uiOpCode = uiOpCode;
    sndMsg.iSocket = 0;

    if( pData != NULL ) {
   		sndMsg.uiDataLength = uiDataLength;
        memcpy( sndMsg.x.szData, pData, sizeof(char)*sndMsg.uiDataLength );
    }
    else {
    	sndMsg.uiDataLength = 0;
    }

    if( pArrayMsgData != NULL ) {
        //Lock();

    	sndMsg.uiArrayLength = uiArrayLength;
    	sndMsg.iArrayIndex = PushLanData( pArrayMsgData, sndMsg.uiArrayLength );

        //UnLock();
    }
    else {
    	sndMsg.uiArrayLength = 0;
    	sndMsg.iArrayIndex = -1;
    }

    QMsgSnd( & sndMsg, pszClassName );

}

/**
 * @brief CThread::QMsgSnd
 * @param pMessageData
 */
void CThread::QMsgSnd( STR_MessageData *pMessageData, void *pArrayMsgData )
{

    if( pArrayMsgData != NULL ) {
        //Lock();        

        pMessageData->iArrayIndex = PushLanData( pArrayMsgData, pMessageData->uiArrayLength );

        //UnLock();        
    }

    QMsgSnd( pMessageData );

}

/**
 * @brief		QMsgSnd
 * @param		STR_MessageData * pMessageData
 * @return		void
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2021/11/10 12:07:00
 * @warning		
 */
void CThread::QMsgSnd( STR_MessageData *pMessageData, const char *pszThreadName )
{

#ifdef __linux__
    if( msgsnd( m_MsgKeyID, (void *) pMessageData, sizeof(STR_MessageData)-sizeof(long), IPC_NOWAIT) < 0 ) {
        perror( "msgsnd 실패" );
    }
    else {
        // DisplayMsg( true, m_szThreadName, pMessageData );

    }

#elif _MSC_VER
    Lock();
	m_queue.push(*pMessageData);
    UnLock();

    //TRACE( "\nQueue Size : %d" , m_queue.size() );
    TRACE( "\nSending into the [%s] from [%s]..." , m_szThreadName, pszThreadName );

	::SetEvent(m_hEvent);    
	
#elif __VXWORKS__    
    STATUS stat=msgQSend( GetKeyId(), (char *) pMessageData, sizeof(STR_MessageData), NO_WAIT, MSG_PRI_NORMAL );
    if( stat == ERROR ) {
        LOGMSG( enError, "msgsnd 실패" );
    }                                   
    else {
        DisplayMsg( true, m_szThreadName, pMessageData );

    }

#endif

}

/**
 * @brief		Sleep
 * @param		int mssleep
 * @return		void
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2021/11/23 10:17:49
 * @warning		
 */
void CThread::Sleep( int mssleep )
{
#ifdef __linux__
    sleep( mssleep );
#elif defined(_MSC_VER)  
    //::Sleep( mssleep );
    ResetEvent( m_hSleepEvent );
    ::WaitForSingleObject( m_hSleepEvent, mssleep );

#elif defined(__VXWORKS__)
    int iDelay=mssleep / g_iClkTickPerSecond;

    if( iDelay == 0 ) {
        iDelay = 1;
    }

    taskDelay( iDelay );
#else    

#endif    
}

/**
 * @brief CThread::DisplayMsg
 */
void CThread::DisplayMsg( bool bSend, const char *pszClassName, STR_MessageData *pInMsg )
{
    bool bRet=true;
    char szOpcode[50];
    char buffer[200];

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
    switch( pMsg->uiOpCode ) {
        case enREQ_MODE :
            strcpy( szOpcode, "모드 설정" );
            break;

        case enREQ_ANAL_START :
            strcpy( szOpcode, "분석 시작" );
            break;

        case enREQ_IBIT :
            strcpy( szOpcode, "IBIT" );
            break;

        case enREQ_UBIT :
            strcpy( szOpcode, "UBIT" );
            break;

        case enREQ_CBIT :
            strcpy( szOpcode, "CBIT" );
            break;

        case enREQ_SBIT :
            strcpy( szOpcode, "SBIT" );
            break;

        case enREQ_COL_START :
            strcpy( szOpcode, "탐지 시작" );
            break;

        case enTHREAD_DETECTANAL_END :
            strcpy( szOpcode, "탐지 종료" );
            //bRet = false;
            break;

        case enTHREAD_KNOWNANAL_START :
            strcpy( szOpcode, "추적 시작" );
            break;

        case enTHREAD_KNOWNANAL_END :
            strcpy( szOpcode, "추적 종료" );
            break;

        case enTHREAD_SCANANAL_START :
            strcpy( szOpcode, "스캔 시작" );
            break;

        case enTHREAD_SCANANAL_END :
            strcpy( szOpcode, "스캔 종료" );
            break;

        case enREQ_STOP :
            strcpy( szOpcode, "수집 종료" );
            break;

        case enREQ_SET_CONFIG :
            strcpy( szOpcode, "수집 설정" );
            break;

        case enTHREAD_REQ_SIM_PDWDATA :
            strcpy( szOpcode, "모의PDW" );
            break;

        case enTHREAD_REQ_SET_TRACKWINDOWCELL :
            strcpy( szOpcode, "추적채널 생성 요청" );
            break;

        case enTHREAD_REQ_CLOSE_TRACKWINDOWCELL :
            strcpy( szOpcode, "추적채널 삭제 요청" );
            break;

        case enTHREAD_REQ_SET_SCANWINDOWCELL :
            strcpy( szOpcode, "스캔채널 생성 요청" );
            break;

        case enTHREAD_REQ_CLOSE_SCANWINDOWCELL :
            strcpy( szOpcode, "스캔채널 삭제 요청" );
            break;

        case enREQ_IPL_START :
            strcpy( szOpcode, "IPL시작" );
            break;

         case enREQ_IPL_DOWNLOAD :
             strcpy( szOpcode, "IPL 레코드" );
             break;

        case enREQ_IPL_END :
            strcpy( szOpcode, "IPL 종료" );
            break;

        // CGI 관련 메시지 처리
        case enCGI_FETCH :
            strcpy( szOpcode, "CGI_FETCH" );
            break;

        case enCGI_REQ_SPECTRUM :
            strcpy( szOpcode, "스펙트럼 요청" );
            break;

        default :
            strcpy( szOpcode, "이름 없음" );
            break;
    }

    if( bRet == true ) {
        if( bSend == false ) {
            if( pMsg->uiDataLength == sizeof(int) ) {
                sprintf( buffer, ">>수신: [%12s]서 Op[%s:0x%04X], Len[%d], Idx[%d], D[%d]" , m_szThreadName, szOpcode, pMsg->uiOpCode, pMsg->uiDataLength, pMsg->iArrayIndex, pMsg->x.uiData );
            }
            else {
                sprintf( buffer, ">>수신: [%12s]서 Op[%s:0x%04X], Len[%d], Idx[%d]" , m_szThreadName, szOpcode, pMsg->uiOpCode, pMsg->uiDataLength, pMsg->iArrayIndex );
            }
             
        }
        else {
            if( pMsg->uiDataLength == sizeof(int) ) {
                sprintf( buffer, "<<송신: [%12s]로 Op[%s:0x%04X], Len[%d], Idx[%d], D[%d]" , m_szThreadName, szOpcode, pMsg->uiOpCode, pMsg->uiDataLength, pMsg->iArrayIndex, pMsg->x.uiData );
            }
            else {
                sprintf( buffer, "<<송신: [%12s]로 Op[%s:0x%04X], Len[%d], Idx[%d]" , m_szThreadName, szOpcode, pMsg->uiOpCode, pMsg->uiDataLength, pMsg->iArrayIndex );
            }
        }

        LOGMSG1( enDebug, "%s" , buffer );
    }

}
