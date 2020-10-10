#include "cscananalysis.h"
#include "../Utils/clog.h"

#include "../Utils/csingleserver.h"
#include "../Utils/cmultiserver.h"

#define _DEBUG_

extern CMultiServer *g_pTheZYNQSocket;
extern CSingleServer *g_pTheCCUSocket;

// 클래스 내의 정적 멤버변수 값 정의
CScanAnalysis* CScanAnalysis::m_pInstance = nullptr;

/**
 * @brief CScanAnalysis::CScanAnalysis
 * @param iKeyId
 * @param pClassName
 */
CScanAnalysis::CScanAnalysis( int iKeyId, char *pClassName, bool bArrayLanData ) : CThread( iKeyId, pClassName, bArrayLanData )
{

}


/**
 * @brief CScanAnalysis::~CScanAnalysis
 */
CScanAnalysis::~CScanAnalysis(void)
{

}


/**
 * @brief CScanAnalysis::Run
 */
void CScanAnalysis::Run()
{
    LOGENTRY;

    CThread::Run();

}

/**
 * @brief CScanAnalysis::_routine
 */
void CScanAnalysis::_routine()
{
    LOGENTRY;
    bool bWhile=true;
    UNI_LAN_DATA *pLanData;

    m_pMsg = GetDataMessage();

    pLanData = ( UNI_LAN_DATA * ) & m_pMsg->x.szData[0];

    while( g_AnalLoop ) {
        if( QMsgRcv() == -1 ) {
            perror( "QMsgRcv" );
        }
        else {
            switch( m_pMsg->ucOpCode ) {
            case enTHREAD_REQ_SHUTDOWN :
                LOGMSG1( enDebug, "[%s]를 Shutdown 메시지를 처리합니다...", ChildClassName() );
                bWhile = false;
                break;

             default:
                LOGMSG1( enError, "잘못된 명령(0x%x)을 수신하였습니다 !!", m_pMsg->ucOpCode );
                break;
            }
        }
    }

}
