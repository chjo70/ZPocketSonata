#include "cdetectanalysis.h"
#include "cemittermerge.h"
#include "csignalcollect.h"

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
CDetectAnalysis::CDetectAnalysis( int iKeyId, char *pClassName, bool bArrayLanData ) : CThread( iKeyId, pClassName, bArrayLanData )
{
    m_pTheNewSigAnal = new CNewSigAnal( NEW_COLLECT_PDW );
    if( m_pTheNewSigAnal == NULL ) {
        LOGMSG( enDebug, "메모리 부족입니다. CNewSigAnal 객체를 생성할 수 없습니다 !" );
    }

    m_pTheSysPara = new CSysPara();
    if( m_pTheSysPara == NULL ) {
        LOGMSG( enDebug, "메모리 부족입니다. CNewSigAnal 객체를 생성할 수 없습니다 !" );
    }

}

/**
 * @brief CDetectAnalysis::~CDetectAnalysis
 */
CDetectAnalysis::~CDetectAnalysis(void)
{
    delete m_pTheNewSigAnal;
    m_pTheNewSigAnal = NULL;

    delete m_pTheSysPara;
    m_pTheSysPara = NULL;
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

    UNI_LAN_DATA *pLanData;

    m_pMsg = GetDataMessage();

    pLanData = ( UNI_LAN_DATA * ) & m_pMsg->x.szData[0];

    while( g_AnalLoop ) {
        if( QMsgRcv() == -1 ) {
            break;
            perror( "QMsgRcv" );
        }
        else {
        switch( m_pMsg->ucOpCode ) {
            case enTHREAD_DETECTANAL_START :
                AnalysisStart();
                break;

            case enTHREAD_REQ_SHUTDOWN :
                LOGMSG1( enDebug, "[%s]를 Shutdown 메시지를 처리합니다...", ChildClassName() );
                break;

            case enTHREAD_REQ_SETWINDOWCELL :
                LOGMSG( enDebug, "윈도우 셀을 설정합니다." );
                break;

            default:
                LOGMSG1( enError, "잘못된 명령(0x%x)을 수신하였습니다 !!", m_pMsg->ucOpCode );
                break;
            }
        }
    }

}

/**
 * @brief PDW 데이터를 Fetch 해서 탐지 신호 분석을 수행한다. 분석 결과(LOB)를 병합/식별 쓰레드로 전달한다.
 */
void CDetectAnalysis::AnalysisStart()
{
    LOGENTRY;

    LOGMSG2( enDebug, " 탐지 분석: %d 채널에서 %d개의 PDW 분석을 시작합니다." , m_pMsg->x.strCollectInfo.uiCh, m_pMsg->x.strCollectInfo.uiTotalPDW );

    // 1. PDW 데이터를 갖고온다.
    PopLanData( m_uniLanData.szFile, m_pMsg->iArrayIndex, m_pMsg->uiArrayLength );

    // 2. 탐지 신호 분석을 호출한다.
    m_pTheNewSigAnal->Start( ( STR_PDWDATA *) m_uniLanData.szFile );
    //SIGCOL->QMsgSnd( enTHREAD_DETECTANAL_END );

    // 3. 분석 결과를 병합/식별 쓰레드에 전달한다.
    unsigned int uiTotalLOB=m_pTheNewSigAnal->GetCoLOB();

    if( uiTotalLOB >= _spOne ) {
        STR_ANALINFO strAnalInfo;

        strAnalInfo.uiTotalLOB = uiTotalLOB;
        strAnalInfo.uiCh = m_pMsg->x.strCollectInfo.uiCh;

        EMTMRG->QMsgSnd( enTHREAD_DETECTANAL_START, m_pTheNewSigAnal->GetLOB(), sizeof(SRxLOBData)*uiTotalLOB, & strAnalInfo, sizeof(STR_ANALINFO) );
    }

}
