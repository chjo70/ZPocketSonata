// CTrackAnalysis.cpp: implementation of the CTrackAnalysis class.
//
//////////////////////////////////////////////////////////////////////


#include "stdafx.h"


#include "ctrackanalysis.h"
#include "cemittermerge.h"
//#include "../Utils/clog.h"

#include "../Utils/csingleserver.h"
#include "../Utils/csingleclient.h"
#include "../Utils/cmultiserver.h"

#include "../Utils/ccommonutils.h"

#include "../Include/globals.h"

#define _DEBUG_


/**
 * @brief CTrackAnalysis::CTrackAnalysis
 * @param iKeyId
 * @param pClassName
 */
CTrackAnalysis::CTrackAnalysis( int iKeyId, char *pClassName, bool bArrayLanData ) : CThread( iKeyId, pClassName, bArrayLanData )
{
    m_pTheKnownSigAnal = new CKnownSigAnal( KWN_COLLECT_PDW );
    if( m_pTheKnownSigAnal == NULL ) {
        LOGMSG( enDebug, "메모리 부족입니다. CNewSigAnal 객체를 생성할 수 없습니다 !" );
    }

    m_pTheSysPara = new CSysPara();
    if( m_pTheSysPara == NULL ) {
        LOGMSG( enDebug, "메모리 부족입니다. CNewSigAnal 객체를 생성할 수 없습니다 !" );
    }
}


/**
 * @brief CTrackAnalysis::~CTrackAnalysis
 */
CTrackAnalysis::~CTrackAnalysis(void)
{
    delete m_pTheKnownSigAnal;
    m_pTheKnownSigAnal = NULL;

    delete m_pTheSysPara;
    m_pTheSysPara = NULL;
}


/**
 * @brief CTrackAnalysis::Run
 */
void CTrackAnalysis::Run(key_t key)
{
    LOGENTRY;

    CThread::Run();

}

/**
 * @brief CTrackAnalysis::_routine
 */
void CTrackAnalysis::_routine()
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
            switch( m_pMsg->uiOpCode ) {
                case enTHREAD_KNOWNANAL_START :
                    AnalysisStart();
                    break;

                case enTHREAD_REQ_SHUTDOWN :
                    LOGMSG1( enDebug, "[%s]를 Shutdown 메시지를 처리합니다...", GetThreadName() );
                    bWhile = false;
                    break;

                default:
                    LOGMSG1( enError, "잘못된 명령(0x%x)을 수신하였습니다 !!", m_pMsg->uiOpCode );
                    break;
            }
        }
    }
}

/**
 * @brief     AnalysisStart
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2021-07-24, 17:57
 * @warning
 */
void CTrackAnalysis::AnalysisStart()
{
    LOGENTRY;
    unsigned int uiTotalLOB;

    STR_TRKSCNPDWDATA *pTrkPDWData;

    LOGMSG3( enDebug, " TRK: Analyzing the PDW[%d] in the Ch[%d] for the B[%d]..." , m_pMsg->x.strCollectInfo.uiTotalPDW, m_pMsg->x.strCollectInfo.uiCh, m_pMsg->x.strCollectInfo.uiABTID );

    //CCommonUtils::Disp_FinePDW( ( STR_PDWDATA *) GetRecvData() );

    // 1. 추적 신호 분석을 호출한다.
    pTrkPDWData = ( STR_TRKSCNPDWDATA *) GetRecvData();
    m_pTheKnownSigAnal->Start( & pTrkPDWData->strPDW, & pTrkPDWData->strABTData );

    // 2. 분석 결과를 병합/식별 쓰레드에 전달한다.
    STR_ANALINFO strAnalInfo;

    uiTotalLOB = m_pTheKnownSigAnal->GetCoLOB();

    strAnalInfo.enBoardID = g_enBoardId;
    strAnalInfo.uiTotalLOB = uiTotalLOB;
    strAnalInfo.uiCh = m_pMsg->x.strCollectInfo.uiCh;
    strAnalInfo.uiAETID = m_pMsg->x.strAnalInfo.uiAETID;
    strAnalInfo.uiABTID = m_pMsg->x.strCollectInfo.uiABTID;
    g_pTheEmitterMerge->QMsgSnd( enTHREAD_KNOWNANAL_START, m_pTheKnownSigAnal->GetLOBData(), sizeof(SRxLOBData)*uiTotalLOB, & strAnalInfo, sizeof(STR_ANALINFO), GetThreadName() );

}
