// CScanAnalysis.cpp: implementation of the CScanAnalysis class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"


#include "cscananalysis.h"
#include "cemittermerge.h"

#include "../Utils/csingleserver.h"
#include "../Utils/cmultiserver.h"

#include "../Include/globals.h"

#define _DEBUG_



/**
 * @brief CScanAnalysis::CScanAnalysis
 * @param iKeyId
 * @param pClassName
 */
CScanAnalysis::CScanAnalysis( int iKeyId, char *pClassName, bool bArrayLanData ) : CThread( iKeyId, pClassName, bArrayLanData )
{

#ifdef _SQLITE_
    // SQLITE 파일명 생성하기
    char szSQLiteFileName[100];

    strcpy(szSQLiteFileName, EMITTER_SQLITE_FOLDER);
    strcat(szSQLiteFileName, "/");
    strcat(szSQLiteFileName, EMITTER_SQLITE_FILENAME);

    m_pTheScanSigAnal = new CScanSigAnal(KWN_COLLECT_PDW, false, szSQLiteFileName);
#else
    m_pTheScanSigAnal = new CScanSigAnal(KWN_COLLECT_PDW, false);

#endif

    //m_pTheSysPara = new CSysPara();
    _SAFE_NEW( m_pTheSysPara, CSysPara() )
}


/**
 * @brief CScanAnalysis::~CScanAnalysis
 */
CScanAnalysis::~CScanAnalysis(void)
{

    _SAFE_DELETE(m_pTheScanSigAnal)

    _SAFE_DELETE(m_pTheSysPara)

}


/**
 * @brief CScanAnalysis::Run
 */
void CScanAnalysis::Run(key_t msgQ)
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

    m_pMsg = GetDataMessage();

    while( g_AnalLoop ) {
        if( QMsgRcv() == -1 ) {
            perror( "QMsgRcv" );
        }
        else {
            switch( m_pMsg->uiOpCode ) {
                case enTHREAD_SCANANAL_START :
                    AnalysisStart();
                    break;

                case enTHREAD_REQ_SHUTDOWN :
                    LOGMSG1( enDebug, "[%s]를 Shutdown 메시지를 처리합니다...", GetThreadName() );
                    bWhile = false;
                    break;

                 default:
                    LOGMSG1( enError, "=================================== 잘못된 명령(0x%x)을 수신하였습니다 !!", m_pMsg->uiOpCode );
                    break;
            }
        }
    }

}

/**
 * @brief CScanAnalysis::AnalysisStart
 */
void CScanAnalysis::AnalysisStart()
{
    LOGENTRY;

    SRxLOBData *pLOBData;

    STR_TRKSCNPDWDATA *pScnPDWData;

    LOGMSG3( enDebug, " SCN: Analyzing the PDW[%d] in the Ch[%d] for the B[%d]..." , m_pMsg->x.strCollectInfo.uiTotalPDW, m_pMsg->x.strCollectInfo.iCh, m_pMsg->x.strCollectInfo.uiABTID );

    //CCommonUtils::Disp_FinePDW( ( STR_PDWDATA *) GetRecvData() );

    // 1. 스캔 신호 분석을 호출한다.
    pScnPDWData = ( STR_TRKSCNPDWDATA *) GetRecvData();
    m_pTheScanSigAnal->Start( & pScnPDWData->strPDW, & pScnPDWData->strABTData );

    // 2. 분석 결과를 병합/식별 쓰레드에 전달한다.
    STR_ANALINFO strAnalInfo;

    strAnalInfo.enBoardID = g_enBoardId;
    strAnalInfo.uiTotalLOB = _spOne;
    strAnalInfo.iCh = m_pMsg->x.strCollectInfo.iCh;
    strAnalInfo.uiAETID = m_pMsg->x.strAnalInfo.uiAETID;
    strAnalInfo.uiABTID = m_pMsg->x.strCollectInfo.uiABTID;
    pLOBData = m_pTheScanSigAnal->GetLOBData();
    pLOBData->uiAETID = strAnalInfo.uiAETID;
    pLOBData->uiABTID = strAnalInfo.uiABTID;
    pLOBData->uiLOBID = 0;

#ifndef _XBAND_
    pLOBData->iScanType = 0;
    pLOBData->fScanPeriod = 0;
#endif

    //EMTMRG->QMsgSnd( enTHREAD_SCANANAL_START, pLOBData, sizeof(SRxLOBData), & strAnalInfo, sizeof(STR_ANALINFO) );

}
