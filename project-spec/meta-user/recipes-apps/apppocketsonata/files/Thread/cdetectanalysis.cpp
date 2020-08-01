#include "cdetectanalysis.h"

#include "../Utils/csingleserver.h"
#include "../Utils/cmultiserver.h"

#define _DEBUG_

extern CMultiServer *g_pTheZYNQSocket;
extern CSingleServer *g_pTheCCUSocket;

// 클래스 내의 정적 멤버변수 값 정의
CDetectAnalysis* CDetectAnalysis::pInstance = nullptr;

/**
 * @brief CDetectAnalysis::CDetectAnalysis
 */
CDetectAnalysis::CDetectAnalysis( int iKeyId, char *pClassName ) : CThread( iKeyId, pClassName )
{

}

/**
 * @brief CDetectAnalysis::~CDetectAnalysis
 */
CDetectAnalysis::~CDetectAnalysis(void)
{

}


/**
 * @brief CDetectAnalysis::Run
 */
void CDetectAnalysis::Run()
{
    LOGENTRY;

    CThread::Run();

}

/**
 * @brief CDetectAnalysis::_routine
 */
void CDetectAnalysis::_routine()
{
    LOGENTRY;
    bool bWhile=true;
    UNI_LAN_DATA *pLanData;

    m_pMsg = GetDataMessage();

    pLanData = ( UNI_LAN_DATA * ) & m_pMsg->szMessage[0];

    while( bWhile ) {
        if( QMsgRcv() == -1 ) {
            perror( "error ");
        }

        switch( m_pMsg->opCode ) {
            case enTHREAD_ANAL_START :
                break;

            case enTHREAD_REQ_SHUTDOWN :
                LOGMSG1( enDebug, "[%s] 를 종료 처리 합니다...", ChildClassName() );
                bWhile = false;
                break;

            case enTHREAD_REQ_SETWINDOWCELL :
                LOGMSG( enDebug, "윈도우 셀을 설정합니다." );
                break;

            default:
                LOGMSG1( enError, "잘못된 명령(0x%x)을 수신하였습니다 !!", m_pMsg->opCode );
                break;
        }
    }

}
