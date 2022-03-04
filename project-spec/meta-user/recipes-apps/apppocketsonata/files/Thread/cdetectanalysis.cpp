// CDetectAnalysis.cpp: implementation of the CDetectAnalysis class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"


#include "cdetectanalysis.h"
#include "cemittermerge.h"
#include "csignalcollect.h"

#include "../Utils/csingleserver.h"
#include "../Utils/cmultiserver.h"

#include "../Utils/ccommonutils.h"

#include "../Include/globals.h"

#define _DEBUG_


/**
 * @brief CDetectAnalysis::CDetectAnalysis
 */
CDetectAnalysis::CDetectAnalysis( int iKeyId, char *pClassName, bool bArrayLanData ) : CThread( iKeyId, pClassName, bArrayLanData )
{
    m_pTheNewSigAnal = new CNewSigAnal( NEW_COLLECT_PDW );
    if( m_pTheNewSigAnal == NULL ) {
        LOGMSG1( enDebug, "메모리 부족입니다. %s 객체를 생성할 수 없습니다 !", pClassName );
    }

    m_pTheSysPara = new CSysPara();
    if( m_pTheSysPara == NULL ) {
        LOGMSG1( enDebug, "메모리 부족입니다. %s 객체를 생성할 수 없습니다 !", pClassName );
    }

    m_PDWData.pstPDW = NULL;
    _SAFE_MALLOC( m_PDWData.pstPDW, _PDW, sizeof(_PDW) * MAX_PDW );

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

    _SAFE_FREE( m_PDWData.pstPDW );
}


/**
 * @brief CDetectAnalysis::Run
 */
void CDetectAnalysis::Run(key_t key)
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
            perror( "QMsgRcv" );
            //break;
        }
        else {
        switch( m_pMsg->uiOpCode ) {
            case enTHREAD_DETECTANAL_START :
                MakePDWData();
                AnalysisStart();
                break;

            case enTHREAD_REQ_SHUTDOWN :
                LOGMSG1( enDebug, "[%s]를 Shutdown 메시지를 처리합니다...", GetThreadName() );
                break;

            case enTHREAD_REQ_SET_TRACKWINDOWCELL :
                LOGMSG( enDebug, "윈도우 셀을 설정합니다." );
                break;

            default:
                LOGMSG1( enError, "잘못된 명령(0x%x)을 수신하였습니다 !!", m_pMsg->uiOpCode );
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

    LOGMSG2( enDebug, " DET : At the %d[Ch], collecting the analysis for the count of PDW[%d]..." , m_pMsg->x.strCollectInfo.uiCh, m_pMsg->x.strCollectInfo.uiTotalPDW );

    //CCommonUtils::Disp_FinePDW( ( STR_PDWDATA *) GetRecvData() );

    // 1. 탐지 신호 분석을 호출한다.
    m_pTheNewSigAnal->Start( & m_PDWData );
    //SIGCOL->QMsgSnd( enTHREAD_DETECTANAL_END );

    // 3. 분석 결과를 병합/식별 쓰레드에 전달한다.
    unsigned int uiTotalLOB=m_pTheNewSigAnal->GetCoLOB();

    if( uiTotalLOB >= _spOne ) {
        STR_ANALINFO strAnalInfo;

        memset( & strAnalInfo, 0, sizeof(STR_ANALINFO) );
        strAnalInfo.uiTotalLOB = uiTotalLOB;
        strAnalInfo.uiCh = m_pMsg->x.strCollectInfo.uiCh;        

        g_pTheEmitterMerge->QMsgSnd( enTHREAD_DETECTANAL_START, m_pTheNewSigAnal->GetLOBData(), sizeof(SRxLOBData)*uiTotalLOB, & strAnalInfo, sizeof(STR_ANALINFO), GetThreadName() );
    }

}

/**
 * @brief     MakePDWData
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-03-03, 14:51
 * @warning
 */
void CDetectAnalysis::MakePDWData()
{
    unsigned int i, uiTotalPDW;

    STR_STATIC_PDWDATA *pStaticPDWData; 

    _PDW *pPDWSrc, *pPDWDest;
    
    pStaticPDWData = ( STR_STATIC_PDWDATA * ) GetRecvData();

    // 헤더 복사
    memcpy( & m_PDWData.x, & pStaticPDWData->x, sizeof(UNION_HEADER) );

    // 데이터 복사
    pPDWSrc = & pStaticPDWData->stPDW[0];
    pPDWDest = & m_PDWData.pstPDW[0];
    uiTotalPDW = pStaticPDWData->GetTotalPDW();    
    for( i=0 ; i < uiTotalPDW ; ++i ) {
        pPDWDest->ullTOA = pPDWSrc->ullTOA;

        pPDWDest->iPulseType = pPDWSrc->iPulseType;

        pPDWDest->uiAOA = pPDWSrc->uiAOA;
        pPDWDest->uiFreq = pPDWSrc->uiFreq;
        pPDWDest->uiPA = pPDWSrc->uiPA;
        pPDWDest->uiPW = pPDWSrc->uiPW;

        pPDWDest->iPFTag = pPDWSrc->iPFTag;

#if defined(_ELINT_)
        pPDWDest->fPh1 = pPDWSrc->fPh1;
        pPDWDest->fPh2 = pPDWSrc->fPh2;
        pPDWDest->fPh3 = pPDWSrc->fPh3;
        pPDWDest->fPh4 = pPDWSrc->fPh4;

#elif defined(_XBAND_)
        pPDWDest->fPh1 = pPDWSrc->fPh1;
        pPDWDest->fPh2 = pPDWSrc->fPh2;
        pPDWDest->fPh3 = pPDWSrc->fPh3;
        pPDWDest->fPh4 = pPDWSrc->fPh4;
        pPDWDest->fPh5 = pPDWSrc->fPh5;

#elif _POCKETSONATA_
        pPDWDest->iPMOP = pPDWSrc->iPMOP;
        pPDWDest->iFMOP = pPDWSrc->iFMOP;
        pPDWDest->iChannel = pPDWSrc->iChannel;

#endif

        ++ pPDWSrc;
        ++ pPDWDest;
    }


}