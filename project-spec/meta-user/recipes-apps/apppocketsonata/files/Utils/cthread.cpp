#include "cthread.h"
#include <errno.h>

#include "../Utils/clog.h"

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
CThread::CThread( int iMsgKey, char *pClassName, bool bArrayLanData ) : CArrayMsgData( bArrayLanData )
{
    m_MainThread = 0;
    m_MsgKeyID = 0;

    m_pszRecvData = NULL;

    // 메시지큐 생성
    memset( & m_RcvMsg, 0, sizeof(STR_MessageData) );

    strcpy( m_szClassName, pClassName );


}

/**
 * @brief CThread::~CThread
 */
CThread::~CThread()
{

    // 2. 큐 메시지를 죽인다.
    if (m_MsgKeyID > 0 ) {
        if( msgctl( m_MsgKeyID, IPC_RMID, 0 ) == -1 ) {
            perror( "msgctl 실패" );
        }
        else {
            -- m_iCoMsgQueue;
            LOGMSG1( enDebug, "\t 큐 ID[%d]를 종료 처리합니다." , m_MsgKeyID );
        }
    }

    // 1. 쓰레드를 죽인다.
    if( m_MainThread != 0 ) {
        -- m_iCoThread;

        pthread_cancel( m_MainThread );
        //Pend();
        LOGMSG1( enDebug, "[%s]를 종료 처리합니다." , m_szClassName );

        //Stop();
    }

}

/**
 * @brief CThread::Create
 */
void CThread::Run( void *(*Func)(void*), key_t key )
{
    LOGMSG1( enDebug, "[%s] 쓰레드를 생성 합니다...", ChildClassName() );

    ++ m_iCoMsgQueue;

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
        LOGMSG1( enDebug, "\t 큐 ID[%d]를 생성합니다." , m_MsgKeyID );
    }

    while( QMsgRcv( IPC_NOWAIT ) != -1 );

    ++ m_iCoThread;
    pthread_create( & m_MainThread, NULL, Func, this );

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
    int iStatus;

    //pStatus = ( void *) malloc( 100 );
    iStatus = pthread_join( m_MainThread, /* (void **) & iStatus[0] */ NULL );
    //free( pStatus );

    return iStatus;
}

/**
 * @brief CThread::Stop
 */
void CThread::Stop()
{
    static int retval=999;

    //printf( "\n thread die..[%d]\n" , retval );

    pthread_exit( (void *) & retval );

}

void CThread::Stop2()
{

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

}

/**
 * @brief CThread::CallBack
 * @param pArg
 * @return
 */
void *CThread::CallBack( void *pArg )
{
    CThread *pThhread = static_cast<CThread*> (pArg);

    //pthread_cleanup_push( TCleanUpHandler, NULL);

    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS,NULL);

    pThhread->_routine();

    //pthread_cleanup_pop(1);

    return NULL;
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
int CThread::QMsgRcv( int iFlag )
{
    //LOGENTRY;

    int iMsgRcv = msgrcv( m_MsgKeyID, (void *) & m_RcvMsg, sizeof(STR_MessageData)-sizeof(long), 1 /* (1 >> 1)*/, iFlag );

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

    return iMsgRcv;

}

/**
 * @brief 쓰레드간 메시지를 전달한다.
 * @param iKeyId
 * @param uiOpCode
 * @param pData
 * @param iByte
 */
void CThread::QMsgSnd( key_t iKeyId, UINT uiOpCode, void *pData, int iByte )
{
    STR_MessageData sndMsg;

    sndMsg.mtype = 1;
    sndMsg.uiOpCode = uiOpCode;
    sndMsg.iSocket = 0;
    sndMsg.iArrayIndex = -1;
    sndMsg.uiArrayLength = 0;
    sndMsg.uiDataLength = iByte;

    memcpy( & sndMsg.x.szData[0], pData, sizeof(char) * iByte );

    if( msgsnd( iKeyId, (void *)& sndMsg, sizeof(STR_MessageData)-sizeof(long), IPC_NOWAIT) < 0 ) {
        perror( "msgsnd 실패" );
    }
    else {
        // DisplayMsg( & sndMsg );

    }
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
    //STR_MessageData sndMsg;

    m_SndMsg.mtype = 1;
    m_SndMsg.uiOpCode = uiOpCode;
    m_SndMsg.iSocket = 0;

    if( pData != NULL ) {
        m_SndMsg.uiDataLength = uiDataLength;
        memcpy( m_SndMsg.x.szData, pData, sizeof(char)*m_SndMsg.uiDataLength );
    }
    else {
        m_SndMsg.uiDataLength = 0;
    }

    if( pArrayMsgData != NULL ) {
        m_SndMsg.uiArrayLength = uiArrayLength;
        m_SndMsg.iArrayIndex = PushLanData( pArrayMsgData, m_SndMsg.uiArrayLength );
    }
    else {
        m_SndMsg.uiArrayLength = 0;
        m_SndMsg.iArrayIndex = -1;
    }

    if( msgsnd( m_MsgKeyID, (void *) & m_SndMsg, sizeof(STR_MessageData)-sizeof(long), IPC_NOWAIT) < 0 ) {
        perror( "msgsnd 실패" );
    }
    else {
        DisplayMsg( true, pszClassName );
        //LOGMSG5( enDebug, "@송신: [%s]에서 [%12s] 으로 Op[0x%04X], Len[%d], Idx[%d]" , pszClassName, m_szClassName, uiOpCode, uiDataLength, m_Msg.iArrayIndex );

    }
}

/**
 * @brief CThread::QMsgSnd
 * @param pMessageData
 */
void CThread::QMsgSnd( STR_MessageData *pMessageData, void *pArrayMsgData )
{

    if( pArrayMsgData != NULL ) {
        pMessageData->iArrayIndex = PushLanData( pArrayMsgData, pMessageData->uiArrayLength );
    }

    if( msgsnd( m_MsgKeyID, (void *) pMessageData, sizeof(STR_MessageData)-sizeof(long), IPC_NOWAIT) < 0 ) {
        perror( "msgsnd 실패" );
    }
    else {
        // DisplayMsg( & sndMsg );

    }
}

/**
 * @brief CThread::DisplayMsg
 */
void CThread::DisplayMsg( bool bSend, const char *pszClassName )
{
    bool bRet=true;
    char szOpcode[50];
    char buffer[200];

    STR_MessageData *pMsg;

    if( bSend == true ) {
        pMsg = & m_SndMsg;
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
            bRet = false;
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
            sprintf( buffer, ">>수신: [%12s]서 Op[%s:0x%04X], Len[%d], Idx[%d]" , m_szClassName, szOpcode, pMsg->uiOpCode, pMsg->uiDataLength, pMsg->iArrayIndex );
        }
        else {
            sprintf( buffer, "<<송신: [%12s]로 Op[%s:0x%04X], Len[%d], Idx[%d]" , m_szClassName, szOpcode, pMsg->uiOpCode, pMsg->uiDataLength, pMsg->iArrayIndex );
        }

        LOGMSG1( enDebug, "%s" , buffer );
    }

}
