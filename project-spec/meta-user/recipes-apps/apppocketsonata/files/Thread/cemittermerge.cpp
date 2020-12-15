#include "cemittermerge.h"

#include "csignalcollect.h"

#include "../Utils/ccommonutils.h"

#define _DEBUG_


// 클래스 내의 정적 멤버변수 값 정의
CEmitterMerge* CEmitterMerge::m_pInstance = nullptr;

CEmitterMerge::CEmitterMerge( int iKeyId, char *pClassName, bool bArrayLanData ) : CThread( iKeyId, pClassName, bArrayLanData )
{
   LOGENTRY;

    // SQLITE 파일명 생성하기
    char szSQLiteFileName[100];

    strcpy( szSQLiteFileName, EMITTER_SQLITE_FOLDER );
    strcat( szSQLiteFileName, EMITTER_SQLITE_FILENAME );

    //Init();
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

    while( g_AnalLoop ) {
        if( QMsgRcv() == -1 ) {
            perror( "QMsgRcv" );
        }
        else {
            switch( m_pMsg->uiOpCode ) {
                case enTHREAD_DETECTANAL_START :
                    MergeEmitter();
                    break;

                case enTHREAD_KNOWNANAL_START :
                    MergeEmitter();
                    break;

                case enTHREAD_REQ_SHUTDOWN :
                    LOGMSG1( enDebug, " [%s]를 Shutdown 메시지를 처리합니다...", ChildClassName() );
                    bWhile = false;
                    break;

                case enTHREAD_DETECTANAL_END :
                    //LOGMSG( enDebug, " 탐지 수집/분석 완료를 수신했습니다." );

                    // 탐지 분석 완료로 이 시그널을 이용하여 위협 사이클 관리를 수행하고...
                    break;

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

    CELThreat *pThreatAET;

    STR_ANALINFO strAnalInfo;
    SRxLOBHeader strLOBHeader;

    SRxLOBData *pLOBData;
    SRxABTData *pABTData;

    LOGMSG4( enDebug, " [%d] 대역, [%d/%d] 채널/빔 번호 에서 [%d] 개의 위협 관리를 수행합니다." , m_pMsg->x.strAnalInfo.uiBand, m_pMsg->x.strAnalInfo.uiCh, m_pMsg->x.strAnalInfo.uiABTID, m_pMsg->x.strAnalInfo.uiTotalLOB );

    memcpy( & strAnalInfo, & m_pMsg->x.strAnalInfo, sizeof(STR_ANALINFO) );

    // 위협 관리 초기화
    m_pTheEmitterMergeMngr->Start();

    // 1. LOB 데이터를 갖고온다.
    //PopLanData( m_uniLanData.szFile, m_pMsg->iArrayIndex, m_pMsg->uiArrayLength );
    memcpy( m_uniLanData.szFile, GetRecvData(), m_pMsg->uiArrayLength );

    // 2. 위협 관리를 호출한다.
    strLOBHeader.iNumOfLOB = m_pMsg->x.strAnalInfo.uiTotalLOB;
    pLOBData = ( SRxLOBData *) m_uniLanData.szFile;
    for( i=0 ; i < strLOBHeader.iNumOfLOB ; ++i ) {
        // 2.1 분석된 LOB 데이터를 병합 관리한다.
        bMerge = m_pTheEmitterMergeMngr->ManageThreat( & strLOBHeader, pLOBData, & m_sLOBOtherInfo );

        // 2.2 병합 관리된 빔 및 AET 정보를 처리한다.
        if( bMerge != true || strAnalInfo.uiAETID != _spZero ) {
            strAnalInfo.uiBand = 0;
            strAnalInfo.uiCh = ( bMerge == true ? m_pMsg->x.strAnalInfo.uiCh : _spZero );
            strAnalInfo.uiTotalLOB = _spOne;
            strAnalInfo.uiAETID = pLOBData->uiAETID;
            strAnalInfo.uiABTID = pLOBData->uiABTID;
            SIGCOL->QMsgSnd( enTHREAD_REQ_SETWINDOWCELL, m_pTheEmitterMergeMngr->GetABTData(), sizeof(SRxABTData), & strAnalInfo, sizeof(STR_ANALINFO) );
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
    ENUM_COLLECTBANK enCollectBank;
    enCollectBank = CCommonUtils::GetEnumCollectBank( m_pMsg->x.strAnalInfo.uiCh );

    if( enCollectBank == enTrackCollectBank && bTrkLOB == false ) {
        strAnalInfo.uiBand = 0;
        strAnalInfo.uiCh = m_pMsg->x.strAnalInfo.uiCh;
        strAnalInfo.uiTotalLOB = _spOne;
        strAnalInfo.uiAETID = m_pMsg->x.strAnalInfo.uiAETID;
        strAnalInfo.uiABTID = m_pMsg->x.strAnalInfo.uiABTID;

        pABTData = m_pTheEmitterMergeMngr->GetABTData(strAnalInfo.uiAETID, strAnalInfo.uiABTID);

        // 3.1 추적 채널 업데이트 수행
        if( m_pTheEmitterMergeMngr->IsDeleteAET( strAnalInfo.uiAETID ) == false ) {
            SIGCOL->QMsgSnd( enTHREAD_REQ_SETWINDOWCELL, pABTData, sizeof(SRxABTData), & strAnalInfo, sizeof(STR_ANALINFO) );

            // 2.3 빔 정보를 제어조종 및 재밍신호관리 장치에게 전송한다.
            SendLost( strAnalInfo.uiAETID );
        }
        else {
            SIGCOL->QMsgSnd( enTHREAD_REQ_CLOSEWINDOWCELL, pABTData, sizeof(SRxABTData), & strAnalInfo, sizeof(STR_ANALINFO) );

            // 2.3 빔 정보를 제어조종 및 재밍신호관리 장치에게 전송한다.
            SendDelete( strAnalInfo.uiAETID );
        }


    }

}

/**
 * @brief CEmitterMerge::SendAnalResult
 */
void CEmitterMerge::SendNewUpd()
{
#ifdef _PREBUILD_
        //CCommonUtils::SendLan( enRES_IBIT, & m_stESIbit, sizeof(m_stESIbit) );
#else
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

    stAET.frq.band = 0;
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

    if( pABTExtData->enBeamEmitterStat == E_ES_NEW || pABTExtData->enBeamEmitterStat == E_ES_REACTIVATED ) {
        CCommonUtils::SendLan( esAET_NEW_CCU, & stAET, sizeof(stAET) );
    }
    else {
        CCommonUtils::SendLan( esAET_UPD_CCU, & stAET, sizeof(stAET) );
    }

#endif

}

/**
 * @brief CEmitterMerge::SendLost
 */
void CEmitterMerge::SendLost( unsigned int uiAETID )
{
    CCommonUtils::SendLan( esAET_LST_CCU, & uiAETID, sizeof(uiAETID) );
}


/**
 * @brief CEmitterMerge::SendDelete
 */
void CEmitterMerge::SendDelete( unsigned int uiAETID )
{
    CCommonUtils::SendLan( esAET_DEL_CCU, & uiAETID, sizeof(uiAETID) );
}

/**
 * @brief CEmitterMerge::ReloadLibrary
 */
void CEmitterMerge::ReloadLibrary()
{
    m_pTheEmitterMergeMngr->UpdateCEDEOBLibrary();
}
