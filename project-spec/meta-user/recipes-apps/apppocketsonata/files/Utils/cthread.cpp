#include "cthread.h"
#include <errno.h>
#include "../Utils/clog.h"

#ifndef S_DEFFILEMODE
#define S_DEFFILEMODE   (S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH)
#endif

// 클래스 내의 정적 멤버변수 값 정의
int CThread::m_iCoThread = 0;
int CThread::m_iCoMsgQueue = 0;

CThread::CThread( int iMsgKey, char *pClassName )
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

    if( m_MainThread != 0 ) {
        -- m_iCoThread;

        pthread_cancel( m_MainThread );
        LOGMSG1( enDebug, "\t[%s]를 종료 처리합니다." , m_szClassName );
    }


    if (m_MsgKeyID > 0 ) {
        if( msgctl( m_MsgKeyID, IPC_RMID, 0 ) == -1 ) {
            perror( "msgctl 실패" );
        }
        else {
            -- m_iCoMsgQueue;
            LOGMSG1( enDebug, "\t 큐 ID[%d]를 종료 처리합니다." , m_MsgKeyID );
        }
    }


}

/**
 * @brief CThread::Create
 */
void CThread::Run( void *(*Func)(void*) )
{
    LOGMSG( enNormal, "\n Running thread..." );

    ++ m_iCoMsgQueue;
    m_MsgKeyID = msgget( IPC_PRIVATE, 0666 | IPC_CREAT);
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
    //LOGMSG1( enNormal, " Running thread...%s", ChildClassName() );
    LOGMSG1( enDebug, "[%s] 쓰레드를 생성 합니다...", ChildClassName() );

    ++ m_iCoMsgQueue;
    m_MsgKeyID = msgget( IPC_PRIVATE, 0666 | IPC_CREAT);
    if (m_MsgKeyID == -1 ) {
        perror("msgget error : ");
        exit(0);
    }
    else {
        LOGMSG1( enDebug, "\t 큐 ID[%d]를 생성합니다." , m_MsgKeyID );
    }

    ++ m_iCoThread;
    pthread_create( & m_MainThread, NULL, CallBack, this );

}

//static void *CThread::CallBack( void *pArg )
//{
//    CThread *pThhread = static_cast<CThread*> (pArg);

//    pThhread->_routine();
//}

/**
 * @brief CThread::Pend
 * @return
 */
int CThread::Pend()
{
    void *pStatus;
    //int iStatus[100];
    int iStatus;

    pStatus = ( void *) malloc( 100 );
    iStatus = pthread_join( m_MainThread, /* (void **) & iStatus[0] */ NULL );
    free( pStatus );

    return iStatus;
}

/**
 * @brief CThread::Stop
 */
void CThread::Stop()
{
    static int retval=999;

    printf( "\n thread die..[%d]\n" , retval );

    pthread_exit( (void *) & retval );

    printf( "\n thread die..[%d]\n" , retval );

}

void *CThread::CallBack( void *pArg )
{
    CThread *pThhread = static_cast<CThread*> (pArg);

    pThhread->_routine();

    return NULL;
}


/**
 * @brief CThread::QMsgRcv
 * @return
 */
int CThread::QMsgRcv()
{
    //LOGENTRY;

    int iMsgRcv = msgrcv( m_MsgKeyID, (void *) & m_Msg, sizeof(STR_MessageData)-sizeof(long), (1 >> 1), 0);

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
    sndMsg.opCode = uiOpCode;
    sndMsg.iSocket = 0;

    memcpy( & sndMsg.szMessage[0], pData, sizeof(char) * iByte );

    if( msgsnd( iKeyId, (void *)& sndMsg, sizeof(STR_MessageData)-sizeof(long), IPC_NOWAIT) < 0 ) {
        perror( "msgsnd 실패" );
    }
    else {
        // DisplayMsg( & sndMsg );

    }
}

/**
 * @brief CThread::QMsgSnd
 * @param iKeyId
 * @param pMessageData
 */
void CThread::QMsgSnd( key_t iKeyId, STR_MessageData *pMessageData )
{
    STR_MessageData sndMsg;

    sndMsg.mtype = 1;
    sndMsg.opCode = pMessageData->opCode;
    sndMsg.iSocket = 0;

    memcpy( & sndMsg.szMessage[0], & pMessageData->szMessage[0], pMessageData->iLength );

    if( msgsnd( iKeyId, (void *)& sndMsg, sizeof(STR_MessageData)-sizeof(long), IPC_NOWAIT) < 0 ) {
        perror( "msgsnd 실패" );
    }
    else {
        // DisplayMsg( & sndMsg );

    }
}
