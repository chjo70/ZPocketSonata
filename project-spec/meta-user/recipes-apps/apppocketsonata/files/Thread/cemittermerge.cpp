﻿// CEmitterMerge.cpp: implementation of the CEmitterMerge class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "cemittermerge.h"

#include "csignalcollect.h"

#include "../Utils/ccommonutils.h"

#include "../Anal/Collect/DataFile/DataFile.h"

#include "../Include/globals.h"

#define _DEBUG_


CEmitterMerge::CEmitterMerge( int iKeyId, char *pClassName, bool bArrayLanData ) : CThread( iKeyId, pClassName, bArrayLanData )
{
    LOGENTRY;

    // SQLITE 파일명 생성하기
    char szSQLiteFileName[100];

    strcpy( szSQLiteFileName, EMITTER_SQLITE_FOLDER );
    strcat( szSQLiteFileName, "/" );
    strcat( szSQLiteFileName, EMITTER_SQLITE_FILENAME );

    m_pTheEmitterMergeMngr = new CELEmitterMergeMngr( false, szSQLiteFileName );

    InitData();

}

/**
 * @brief CEmitterMerge::~CEmitterMerge
 */
CEmitterMerge::~CEmitterMerge()
{
    delete m_pTheEmitterMergeMngr;
}

/**
 * @brief CEmitterMerge::Run
 */
void CEmitterMerge::Run(key_t key)
{
    LOGENTRY;

    CThread::Run();

}

/**
 * @brief CEmitterMerge::_routine
 */
void CEmitterMerge::_routine()
{
    LOGENTRY;
    bool bWhile=true;
    UNI_LAN_DATA *pLanData;

    m_pMsg = GetDataMessage();

    pLanData = ( UNI_LAN_DATA * ) & m_pMsg->x.szData[0];

    while( bWhile ) {
        if( QMsgRcv() == -1 ) {
            perror( "QMsgRcv" );
        }
        else {
            switch( m_pMsg->uiOpCode ) {
                case enTHREAD_DETECTANAL_START :
                    m_bScanInfo = false;
                    MergeEmitter();
                    break;

                case enTHREAD_KNOWNANAL_START :
                    m_bScanInfo = false;
                    MergeEmitter();
                    break;

                case enTHREAD_KNOWNANAL_FAIL :
                    TrackFail();
                    break;

                case enTHREAD_SCANANAL_START :
                    m_bScanInfo = true;
                    MergeEmitter();
                    //UpdateScanEmitter();
                    break;

                case enTHREAD_REQ_SHUTDOWN :
                    LOGMSG1( enDebug, " [%s]를 Shutdown 메시지를 처리합니다...", GetThreadName() );
                    bWhile = false;
                    break;

                case enTHREAD_DETECTANAL_END :
                    LOGMSG( enDebug, " 탐지 수집/분석 완료를 수신했습니다." );

                    // 탐지 분석 완료로 이 시그널을 이용하여 위협 사이클 관리를 수행하고...
                    break;

                case enTHREAD_IPL_END :
                case enTHREAD_RELOAD_LIBRARY :
                    ReloadLibrary();
                    break;

                default:
                    LOGMSG1( enError, " 잘못된 명령(0x%x)을 수신하였습니다 !!", m_pMsg->uiOpCode );
                    break;
            }
        }
    }
}


/**
 * @brief CEmitterMerge::InitData
 */
void CEmitterMerge::InitData()
{
    m_sLOBOtherInfo.bUpdate = false;
}

/**
 * @brief CEmitterMerge::MergeEmitter
 */
void CEmitterMerge::MergeEmitter()
{
    LOGENTRY;

    int i;
    bool bMerge, bTrkLOB=false;

    STR_ANALINFO strAnalInfo;
    SRxLOBHeader strLOBHeader;

    SRxLOBData *pLOBData;
    SRxABTData *pABTData;

    if( m_bScanInfo == false ) {
        LOGMSG4( enDebug, "Operating the [%d] Band, in the Ch[%d/%d] 채널/빔 번호 에서 [%d] 개의 위협 관리를 수행합니다." , m_pMsg->x.strAnalInfo.uiBand, m_pMsg->x.strAnalInfo.uiCh, m_pMsg->x.strAnalInfo.uiABTID, m_pMsg->x.strAnalInfo.uiTotalLOB );
    }
    else {
        LOGMSG3( enDebug, "[%d] Band, [%d/%d] 채널/빔 번호 에서 스캔 결과를 업데이트합니다." , m_pMsg->x.strAnalInfo.uiBand, m_pMsg->x.strAnalInfo.uiCh, m_pMsg->x.strAnalInfo.uiABTID );
    }

    memcpy( & strAnalInfo, & m_pMsg->x.strAnalInfo, sizeof(STR_ANALINFO) );

    // 위협 관리 초기화
    m_pTheEmitterMergeMngr->Start( m_bScanInfo );

    // 1. LOB 데이터를 갖고온다.
    memcpy( m_uniLanData.szFile, GetRecvData(), m_pMsg->uiArrayLength );

    // 2. 위협 관리를 호출한다.
    strLOBHeader.iNumOfLOB = m_pMsg->x.strAnalInfo.uiTotalLOB;
    pLOBData = ( SRxLOBData *) & m_uniLanData.stLOBData[0];
    
    for( i=0 ; i < strLOBHeader.iNumOfLOB ; ++i ) {

        // 2.1 분석된 LOB 데이터를 병합 관리한다.
        bMerge = m_pTheEmitterMergeMngr->ManageThreat( & strLOBHeader, pLOBData, & m_sLOBOtherInfo, m_bScanInfo );
        

        // 2.2 병합 관리된 빔 및 AET 정보를 처리한다.
        if( !m_bScanInfo && ( bMerge == false || strAnalInfo.uiAETID != _spZero || (m_pTheEmitterMergeMngr->GetABTExtData())->enBeamEmitterStat == E_ES_REACTIVATED ) ) {
            strAnalInfo.uiBand = g_enBoardId;
            strAnalInfo.uiCh = ( bMerge == true ? m_pMsg->x.strAnalInfo.uiCh : _spZero );
            strAnalInfo.uiTotalLOB = _spOne;
            strAnalInfo.uiAETID = pLOBData->uiAETID;
            strAnalInfo.uiABTID = pLOBData->uiABTID;
            g_pTheSignalCollect->QMsgSnd( enTHREAD_REQ_SET_TRACKWINDOWCELL, m_pTheEmitterMergeMngr->GetABTData(), sizeof(SRxABTData), & strAnalInfo, sizeof(STR_ANALINFO) );

        }

        if( m_pTheEmitterMergeMngr->DoesAnalScanTry() == true ) {
            SetStartOfAnalScan();

            strAnalInfo.uiBand = g_enBoardId;
            strAnalInfo.uiCh = 0;
            strAnalInfo.uiTotalLOB = _spOne;
            strAnalInfo.uiAETID = pLOBData->uiAETID;
            strAnalInfo.uiABTID = pLOBData->uiABTID;
            g_pTheSignalCollect->QMsgSnd( enTHREAD_REQ_SET_SCANWINDOWCELL, m_pTheEmitterMergeMngr->GetABTData(), sizeof(SRxABTData), & strAnalInfo, sizeof(STR_ANALINFO) );
        }

        // 2.3 빔 정보를 제어조종 및 재밍신호관리 장치에게 전송한다.
        SendNewUpd();

        // 2.4 추적 업데이트 성공 여부 플레그 업데이트
        if( strAnalInfo.uiABTID == m_pMsg->x.strAnalInfo.uiABTID && m_pMsg->x.strAnalInfo.uiABTID != _spZero ) {
            bTrkLOB = true;
        }

        ++ pLOBData;
    }

    // 3. 추적 채널 경우에는 재시도 또는 추적 채널을 닫는다.
    if( m_bScanInfo == false ) {
        ENUM_COLLECTBANK enCollectBank;
        enCollectBank = CCommonUtils::GetEnumCollectBank( m_pMsg->x.strAnalInfo.uiCh );

        if( enCollectBank == enTrackCollectBank && bTrkLOB == false ) {
            strAnalInfo.uiBand = g_enBoardId;
            strAnalInfo.uiCh = m_pMsg->x.strAnalInfo.uiCh;
            strAnalInfo.uiTotalLOB = _spOne;
            strAnalInfo.uiAETID = m_pMsg->x.strAnalInfo.uiAETID;
            strAnalInfo.uiABTID = m_pMsg->x.strAnalInfo.uiABTID;

            pABTData = m_pTheEmitterMergeMngr->GetABTData(strAnalInfo.uiAETID, strAnalInfo.uiABTID);

            // 3.1 추적 채널 업데이트 및 빔 정보 제어조종 및 재밍신호관리장치에게 전달
            if( m_pTheEmitterMergeMngr->IsDeleteAET( strAnalInfo.uiAETID ) == false ) {
                SELABTDATA_EXT *pABTExtData;

                g_pTheSignalCollect->QMsgSnd( enTHREAD_REQ_SET_TRACKWINDOWCELL, pABTData, sizeof(SRxABTData), & strAnalInfo, sizeof(STR_ANALINFO) );

                pABTExtData = m_pTheEmitterMergeMngr->GetABTExtData( strAnalInfo.uiAETID, strAnalInfo.uiABTID );
                SendLan( enAET_LST_CCU, & strAnalInfo.uiABTID, sizeof(strAnalInfo.uiABTID), pABTExtData );
            }
            else {
                g_pTheSignalCollect->QMsgSnd( enTHREAD_REQ_CLOSE_TRACKWINDOWCELL, pABTData, sizeof(SRxABTData), & strAnalInfo, sizeof(STR_ANALINFO) );

                SendDelete( strAnalInfo.uiAETID );
            }
        }
    }

}

/**
 * @brief     TrackFail
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2021-07-24, 17:03
 * @warning
 */
void CEmitterMerge::TrackFail()
{
    STR_ANALINFO strAnalInfo;

    SRxLOBData *pLOBData;
    SRxABTData *pSRxABTData;
    SELABTDATA_EXT *pABTExtData;

    pLOBData = ( SRxLOBData *) m_uniLanData.szFile;

    pSRxABTData = m_pTheEmitterMergeMngr->GetABTData( pLOBData->uiAETID, pLOBData->uiABTID );
    
    if( pSRxABTData != NULL ) {
        strAnalInfo.uiBand = g_enBoardId;
        strAnalInfo.uiCh = m_pMsg->x.strCollectInfo.uiCh;
        strAnalInfo.uiTotalLOB = _spOne;
        strAnalInfo.uiAETID = pLOBData->uiAETID;
        strAnalInfo.uiABTID = pLOBData->uiABTID;
        g_pTheSignalCollect->QMsgSnd( enTHREAD_REQ_SET_TRACKWINDOWCELL, pSRxABTData, sizeof(SRxABTData), & strAnalInfo, sizeof(STR_ANALINFO) );

        pABTExtData = m_pTheEmitterMergeMngr->GetABTExtData( pLOBData->uiAETID, pLOBData->uiABTID );
        SendLan( enAET_LST_CCU, & strAnalInfo.uiABTID, sizeof(strAnalInfo.uiABTID), pABTExtData );
    }
    else {
        LOGMSG1( enError, " Invalid the Track Fail [%d] !!!", pLOBData->uiAETID );
    }

}

void CEmitterMerge::ScanFail()
{

}

/**
 * @brief     SendNewUpd
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2021-07-24, 17:03
 * @warning
 */
void CEmitterMerge::SendNewUpd()
{
    //CCommonUtils::SendLan( enRES_IBIT, & m_stESIbit, sizeof(m_stESIbit) );

#ifdef _POCKETSONATA_
    int i;

    char *pString;

    STR_AET stAET;
    SRxABTData *pSRxABTData;
    SELABTDATA_EXT *pABTExtData;

    pSRxABTData = m_pTheEmitterMergeMngr->GetABTData();
    pABTExtData = m_pTheEmitterMergeMngr->GetABTExtData();

    // AET로 변환
    memset( & stAET, 0, sizeof(stAET) );

    stAET.aoa = SONATA::ENCODE::DOA( pSRxABTData->fDOAMean );
    stAET.noEMT = pSRxABTData->uiABTID;
    stAET.sigType = pSRxABTData->iSignalType;

    stAET.frq.band = SONATA::ENCODE::BAND( pSRxABTData->fFreqMean );
    stAET.frq.type = pSRxABTData->iFreqType;
    stAET.frq.mean = SONATA::ENCODE::FREQ( stAET.frq.band, pSRxABTData->fFreqMean );
    stAET.frq.min = SONATA::ENCODE::FREQ( stAET.frq.band, pSRxABTData->fFreqMin );
    stAET.frq.max = SONATA::ENCODE::FREQ( stAET.frq.band, pSRxABTData->fFreqMax );
    stAET.frq.patType = pSRxABTData->iFreqPatternType;
    stAET.frq.patPrd = SONATA::ENCODE::TOA( pSRxABTData->fFreqPatternPeriodMean );
    stAET.frq.swtLev = pSRxABTData->iFreqPositionCount;
    for( i=0 ; i < stAET.frq.swtLev; ++i ) {
        stAET.frq.swtVal[i] = SONATA::ENCODE::FREQ( stAET.frq.band, pSRxABTData->fFreqSeq[i] );
    }

    stAET.pri.type = pSRxABTData->iPRIType;
    stAET.pri.mean = SONATA::ENCODE::TOA( pSRxABTData->fPRIMean );
    stAET.pri.min = SONATA::ENCODE::TOA( pSRxABTData->fPRIMin );
    stAET.pri.max = SONATA::ENCODE::TOA( pSRxABTData->fPRIMax );
    stAET.pri.patType = pSRxABTData->iPRIPatternType;
    stAET.pri.jtrPer = pSRxABTData->fPRIJitterRatio;
    stAET.pri.swtLev = pSRxABTData->iPRIPositionCount;
    for( i=0 ; i < stAET.pri.swtLev; ++i ) {
        stAET.pri.swtVal[i] = SONATA::ENCODE::TOA( pSRxABTData->fPRISeq[i] );
    }

    stAET.pw.mean = SONATA::ENCODE::PW( pSRxABTData->fPWMean );
    stAET.pw.min = SONATA::ENCODE::PW( pSRxABTData->fPWMin );
    stAET.pw.max = SONATA::ENCODE::PW( pSRxABTData->fPWMax );

    stAET.pa.mean = SONATA::ENCODE::PA( pSRxABTData->fPAMean );
    stAET.pa.min = SONATA::ENCODE::PA( pSRxABTData->fPAMin );
    stAET.pa.max = SONATA::ENCODE::PA( pSRxABTData->fPAMax );

    stAET.as.stat = pSRxABTData->iScanType != 0 ? SELF_SUCCESS : SELF_FAIL;
    stAET.as.type = pSRxABTData->iScanType;
    stAET.as.prd = SONATA::ENCODE::SCNPRD( pSRxABTData->fMeanScanPeriod );

    stAET.seen.frst = pSRxABTData->tiFirstSeenTime;
    stAET.seen.last = pSRxABTData->tiLastSeenTime;

    stAET.priLev = pSRxABTData->iRadarModePriority;
    pString = m_pTheEmitterMergeMngr->GetELNOT( pSRxABTData->iRadarModeIndex );
    if( pString ) { strncpy( (char *) stAET.elintNotation, pString, sizeof(stAET.elintNotation) ); }
    pString = m_pTheEmitterMergeMngr->GetRadarModeName( pSRxABTData->iRadarModeIndex );
    if( pString ) { strncpy( (char *) stAET.emitterName, pString, sizeof(stAET.emitterName) ); }
    pString = m_pTheEmitterMergeMngr->GetThreatName( pSRxABTData->iRadarModeIndex );
    if( pString ) { strncpy( (char *) stAET.threatName, pString, sizeof(stAET.threatName) ); }

    stAET.id.coAmbi = min( pABTExtData->idInfo.nCoRadarModeIndex, _spMaxCoSysAmbi );
    memcpy( stAET.id.noIPL, pABTExtData->idInfo.nRadarModeIndex, sizeof(int) * stAET.id.coAmbi );

    // 랜 메시지 전달한다.
    
    if( pABTExtData->enBeamEmitterStat == E_ES_NEW || pABTExtData->enBeamEmitterStat == E_ES_REACTIVATED ) {
        SendLan( enAET_NEW_CCU, & stAET, sizeof(stAET), pABTExtData );
    }
    else {
        SendLan( enAET_UPD_CCU, & stAET, sizeof(stAET), pABTExtData );
    }

#endif

}

/**
 * @brief     SendLan
 * @param     unsigned int uiOpcode
 * @param     void * pData
 * @param     unsigned int uiDataSize
 * @param     SELABTDATA_EXT * pABTExtData
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2021-08-02, 13:25
 * @warning
 */
void CEmitterMerge::SendLan( unsigned int uiOpcode, void *pData, unsigned int uiDataSize, SELABTDATA_EXT *pABTExtData )
{
    time_t now;

    now = time(NULL);
    if( pABTExtData != NULL && ( uiOpcode == enAET_NEW_CCU || difftime( now, pABTExtData->tiSendLan ) > 1.0 || ( pABTExtData->uiOpcode != uiOpcode ) ) ) {
        CCommonUtils::SendLan( uiOpcode, pData, uiDataSize );

        pABTExtData->uiOpcode = uiOpcode;
        pABTExtData->tiSendLan = time( NULL );
    }
    else {
        LOGMSG( enNormal, " Ignore the Sending the LAN message !!!" );
    }

}

/**
 * @brief CEmitterMerge::SendDelete
 */
void CEmitterMerge::SendDelete( unsigned int uiAETID )
{
    CCommonUtils::SendLan( enAET_DEL_CCU, & uiAETID, sizeof(uiAETID) );
}

/**
 * @brief CEmitterMerge::ReloadLibrary
 */
void CEmitterMerge::ReloadLibrary()
{
    m_pTheEmitterMergeMngr->UpdateCEDEOBLibrary();
}

/**
 * @brief CEmitterMerge::SetStartOfAnalScan
 */
void CEmitterMerge::SetStartOfAnalScan()
{
    m_pTheEmitterMergeMngr->SetStartOfAnalScan();
}
