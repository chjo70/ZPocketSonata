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

    // 메시지큐 생성
    memset( & m_Msg, 0, sizeof(STR_MessageData) );

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
void CThread::Run( void *(*Func)(void*) )
{
    LOGMSG1( enDebug, "[%s] 쓰레드를 생성 합니다...", ChildClassName() );

    ++ m_iCoMsgQueue;
    m_MsgKeyID = msgget( IPC_PRIVATE, S_DEFFILEMODE | IPC_CREAT ); // 0666 | IPC_CREAT );
    if (m_MsgKeyID == -1 ) {
        perror("msgget error : ");
        exit(0);
    }
    else {
        LOGMSG1( enDebug, "\t 큐 ID[%d]를 생성합니다." , m_MsgKeyID );
    }

    ++ m_iCoThread;
    pthread_create( & m_MainThread, NULL, Func, this );

}

/**
 * @brief CThread::Run
 */
void CThread::Run()
{
    Run( CallBack );

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
        if (!pthread_cancel(m_MainThread))
        {
            pthread_join(m_MainThread, NULL);
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

    int iMsgRcv = msgrcv( m_MsgKeyID, (void *) & m_Msg, sizeof(STR_MessageData)-sizeof(long), 1 /* (1 >> 1)*/, iFlag );

    if( iMsgRcv > 0 ) {
        LOGMSG4( enDebug, "*수신: [%s]에서 Op[0x%02X], Len[%d], Idx[%d]" , m_szClassName, m_Msg.ucOpCode, m_Msg.uiDataLength, m_Msg.iArrayIndex );
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
    sndMsg.ucOpCode = uiOpCode;
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
void CThread::QMsgSnd( unsigned int uiOpCode )
{

    QMsgSnd( uiOpCode, NULL, 0, NULL, 0 );
}

/**
 * @brief CThread::QMsgSnd
 * @param uiOpCode
 * @param pArrayMsgData
 * @param uiLength
 */
void CThread::QMsgSnd( unsigned int uiOpCode, void *pArrayMsgData, unsigned int uiArrayLength, void *pData, unsigned int uiDataLength )
{
    STR_MessageData sndMsg;

    sndMsg.mtype = 1;
    sndMsg.ucOpCode = uiOpCode;
    sndMsg.iSocket = 0;

    if( pData != NULL ) {
        sndMsg.uiDataLength = uiDataLength;
        memcpy( sndMsg.x.szData, pData, sizeof(char)*sndMsg.uiDataLength );
    }
    else {
        sndMsg.uiDataLength = 0;
    }

    if( pArrayMsgData != NULL ) {
        sndMsg.uiArrayLength = uiArrayLength;
        sndMsg.iArrayIndex = PushLanData( pArrayMsgData, sndMsg.uiArrayLength );
    }
    else {
        sndMsg.uiArrayLength = 0;
        sndMsg.iArrayIndex = -1;
    }

    if( msgsnd( m_MsgKeyID, (void *) & sndMsg, sizeof(STR_MessageData)-sizeof(long), IPC_NOWAIT) < 0 ) {
        perror( "msgsnd 실패" );
    }
    else {
        // DisplayMsg( & sndMsg );

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

