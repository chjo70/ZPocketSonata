// CEmitterMerge.cpp: implementation of the CEmitterMerge class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "cemittermerge.h"

#include "csignalcollect.h"

#include "../Utils/ccommonutils.h"

#include "../Anal/SigAnal/cencdec.h"
#include "../Anal/Collect/DataFile/DataFile.h"

#include "../Include/globals.h"

#define _DEBUG_

#ifdef _MSSQL_
CEmitterMerge::CEmitterMerge( int iKeyId, const char *pClassName, bool bArrayLanData ) : CThread( iKeyId, pClassName, bArrayLanData ), CMSSQL( & m_theMyODBC )
#else
CEmitterMerge::CEmitterMerge( int iKeyId, const char *pClassName, bool bArrayLanData ) : CThread( iKeyId, pClassName, bArrayLanData )
#endif
{
    LOGENTRY;

#ifdef _SQLITE_
    // SQLITE 파일명 생성하기
    char szSQLiteFileName[100];

    strcpy( szSQLiteFileName, EMITTER_SQLITE_FOLDER );
    strcat( szSQLiteFileName, "/" );
    strcat( szSQLiteFileName, EMITTER_SQLITE_FILENAME );

    try {
        m_pTheEmitterMergeMngr = new CELEmitterMergeMngr( false, szSQLiteFileName );
    }
    catch( bad_alloc ex ) {
        TRACE( "new memory[m_pTheEmitterMergeMngr]:%s" , ex.what() );
    }
#elif _MSSQL_
    CMSSQL::Init();

    try {
        m_pTheEmitterMergeMngr = new CELEmitterMergeMngr( false, & m_theMyODBC );
    }
    catch( bad_alloc ex ) {
        TRACE( "new memory[m_pTheEmitterMergeMngr]:%s" , ex.what() );
    }

#else
    try {
	    m_pTheEmitterMergeMngr = new CELEmitterMergeMngr( false, NULL );
    }
    catch( bad_alloc ex ) {
        TRACE( "new memory[m_pTheEmitterMergeMngr]:%s" , ex.what() );
    }

#endif

    InitData();

}

/**
 * @brief CEmitterMerge::~CEmitterMerge
 */
CEmitterMerge::~CEmitterMerge()
{
#ifdef _SQLITE_
    // delete m_pDatabase;

#elif _MSSQL_
    m_theMyODBC.Close();


#else

#endif

    delete m_pTheEmitterMergeMngr;
}

/**
 * @brief     쓰레드를 호출한다.
 * @param     key_t key
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-11-18 13:46:43
 * @warning
 */
void CEmitterMerge::Run(key_t key)
{
    LOGENTRY;

    CThread::Run();

}

/**
 * @brief     쓰레드에서 메시지에 따라 처리한다.
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-11-04 18:48:41
 * @warning
 */
void CEmitterMerge::_routine()
{
    LOGENTRY;
    bool bWhile=true;
    UNI_LAN_DATA *pLanData;

    m_pMsg = GetDataMessage();

    pLanData = ( UNI_LAN_DATA * ) & m_pMsg->x.szData[0];

    while( bWhile ) {
        if( QMsgRcv( enTIMER, OS_SEC(5) ) == -1 ) {
            perror( "QMsgRcv(CEmitterMerge)" );
        }
        else {
            switch( m_pMsg->uiOpCode ) {
                case enTHREAD_DETECTANAL_START :
                    m_bScanInfo = false;
                    MergeEmitter();
					DeleteThreat();
                    break;

                case enTHREAD_KNOWNANAL_START :
                    m_bScanInfo = false;
                    MergeEmitter();
                    break;

                case enTHREAD_KNOWNANAL_FAIL :
                    RequestTrackReCollect();
                    break;

                case enTHREAD_SCANANAL_START :
                    m_bScanInfo = true;
                    MergeEmitter();
                    //UpdateScanEmitter();
                    break;

                case enTHREAD_DELETE_THREAT:
                    DeleteThreat();
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
 * @brief     멤버 변수를 초기화합니다. 
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-11-04 18:49:18
 * @warning
 */
void CEmitterMerge::InitData()
{
    m_sLOBOtherInfo.bUpdate = false;
}

/**
 * @brief     병합 에미터를 처리합니다.
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-11-04 18:49:40
 * @warning
 */
void CEmitterMerge::MergeEmitter()
{
    LOGENTRY;

    unsigned int i;
    bool bTrkLOB=false;

    SRxLOBHeader strLOBHeader;

    SRxLOBData *pLOBData;
    //SRxABTData *pABTData;

    // 1. 메지지 내용을 멤머 변수에 복사한다.
    // 1.1 메시지 헤더 정보를 저장한다.
    memcpy( & m_strAnalInfo, & m_pMsg->x.strAnalInfo, sizeof(STR_ANALINFO) );
    // 1.2 LOB 데이터를 갖고온다.
    memcpy( m_uniLanData.szFile, GetRecvData(), m_pMsg->uiArrayLength );

    if( m_bScanInfo == false ) {
        LOGMSG5( enDebug, "[%d] Band, in the %s Ch[%d/%d] 채널/빔 번호 에서 [%d] 개의 위협 관리를 수행합니다." , m_strAnalInfo.enBoardID, g_szCollectBank[ CCommonUtils::GetEnumCollectBank( m_strAnalInfo.iCh ) ], m_strAnalInfo.iCh, m_strAnalInfo.uiABTID, m_strAnalInfo.uiTotalLOB );
    }
    else {
        LOGMSG3( enDebug, "[%d] Band, [%d/%d] 채널/빔 번호 에서 스캔 결과를 업데이트합니다." , m_strAnalInfo.enBoardID, m_strAnalInfo.iCh, m_strAnalInfo.uiABTID );
    }

    // 위협 관리 초기화
    m_pTheEmitterMergeMngr->Start( m_bScanInfo );

    // 2. 위협 관리를 호출한다.
    strLOBHeader.uiNumOfLOB = m_strAnalInfo.uiTotalLOB;
    pLOBData = ( SRxLOBData *) & m_uniLanData.stLOBData[0];
    
     for( i=0 ; i < m_strAnalInfo.uiTotalLOB ; ++i ) {
        // 2.1 분석된 LOB 데이터를 병합 관리한다.
        m_pTheEmitterMergeMngr->ManageThreat( & strLOBHeader, pLOBData, & m_sLOBOtherInfo, m_bScanInfo );        

#ifdef _TRACK_ENABLED_
        // 2.2 LOB의 추적 관리를 수행한다.
        m_pTheEmitterMergeMngr->ManageTrack( & m_strAnalInfo, pLOBData, & m_sLOBOtherInfo, m_bScanInfo );
        RequestTrackCollect( pLOBData );
#endif

#ifdef _SCAN_ENABLED_
        // 2.3 LOB의 스캔 관리를 수행한다.
        m_pTheEmitterMergeMngr->ManageScan( & m_strAnalInfo, pLOBData, & m_sLOBOtherInfo, m_bScanInfo );
        RequestScanCollect( pLOBData );
#endif

        // 2.3 빔 정보를 제어조종 및 재밍신호관리 장치에게 전송한다.
        SendNewUpd();

        // 2.4 추적 업데이트 성공 여부 플레그 업데이트
        if( pLOBData->uiABTID == m_strAnalInfo.uiABTID && m_strAnalInfo.uiABTID != _spZero ) {
            bTrkLOB = true;
        }
        ++ pLOBData;

    }

#ifdef _TRACK_ENABLED_
    // 추적 실패 처리여부를 수행한다.
    m_pTheEmitterMergeMngr->ManageTrack( & m_strAnalInfo, NULL, & m_sLOBOtherInfo, m_bScanInfo );
    RequestTrackCollect( NULL );
#endif

}

/**
 * @brief     위협 삭제 처리를 수행합니다.
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-11-23 15:27:00
 * @warning
 */
void CEmitterMerge::DeleteThreat()
{
    ENUM_MODE enMode;

    enMode = g_pTheSysConfig->GetMode();

    if ( enMode == enANAL_ES_MODE || enMode == enANAL_EW_MODE ) {
		UINT noAET;

        // 삭제 처리를 한다.
        noAET = m_pTheEmitterMergeMngr->DeleteThreat();		

		LOGMSG1(enDebug, "위협[A:%d]/빔 삭제 처리를 수행합니다." , noAET );

    }

}

/**
 * @brief     LOB 데이터로 추적 수집을 설정합니다.
 * @param     bool bReqTrack
 * @param     SRxLOBData * pLOBData
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-03-08, 13:44
 * @warning
 */
void CEmitterMerge::RequestTrackCollect( SRxLOBData *pLOBData )
{
    STR_ANALINFO strAnalInfo;

    // PDW 헤더 정보 저장
    memcpy(&strAnalInfo.uniPDWHeader, &m_pMsg->x.strAnalInfo.uniPDWHeader, sizeof(UNION_HEADER));

    bool bTrack = m_pTheEmitterMergeMngr->ReqTrack();
    if( pLOBData != NULL ) {        
        if( bTrack == true ) {
            strAnalInfo.enBoardID = m_strAnalInfo.enBoardID;
            strAnalInfo.iCh = ( CCommonUtils::GetEnumCollectBank( m_strAnalInfo.iCh) == enTrackCollectBank ? m_strAnalInfo.iCh : _spZero );
            strAnalInfo.uiTotalLOB = _spOne;
            strAnalInfo.uiAETID = pLOBData->uiAETID;
            strAnalInfo.uiABTID = pLOBData->uiABTID;

            g_pTheSignalCollect->QMsgSnd( enTHREAD_REQ_SET_TRACKWINDOWCELL, m_pTheEmitterMergeMngr->GetABTData(), sizeof(SRxABTData), & strAnalInfo, sizeof(STR_ANALINFO), GetThreadName() );
        }
    }
    else {
        if(bTrack == false ) {
            g_pTheSignalCollect->QMsgSnd( enTHREAD_REQ_SET_TRACKWINDOWCELL, m_pTheEmitterMergeMngr->GetABTData(), sizeof(SRxABTData), & m_strAnalInfo, sizeof(STR_ANALINFO), GetThreadName() );
        }
    }

}

/**
 * @brief     추적 중인 LOB에 대해서 수집을 재설정합니다.
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2021-07-24, 17:03
 * @warning
 */
void CEmitterMerge::RequestTrackReCollect()
{
    STR_ANALINFO strAnalInfo;

    SRxLOBData *pLOBData;
    SRxABTData *pSRxABTData;
    SELABTDATA_EXT *pABTExtData;

    pLOBData = ( SRxLOBData *) m_uniLanData.szFile;

    pSRxABTData = m_pTheEmitterMergeMngr->GetABTData( pLOBData->uiAETID, pLOBData->uiABTID );
    
    if( pSRxABTData != NULL ) {
        strAnalInfo.enBoardID = g_enBoardId;
        strAnalInfo.iCh = m_pMsg->x.strCollectInfo.iCh;
        strAnalInfo.uiTotalLOB = _spOne;
        strAnalInfo.uiAETID = pLOBData->uiAETID;
        strAnalInfo.uiABTID = pLOBData->uiABTID;
        g_pTheSignalCollect->QMsgSnd( enTHREAD_REQ_SET_TRACKWINDOWCELL, pSRxABTData, (UINT) sizeof(SRxABTData), & strAnalInfo, sizeof(STR_ANALINFO) );

        pABTExtData = m_pTheEmitterMergeMngr->GetABTExtData( pLOBData->uiAETID, pLOBData->uiABTID );
        SendLan( enAET_LST_CCU, & strAnalInfo.uiABTID, sizeof(strAnalInfo.uiABTID), pABTExtData );
    }
    else {
        LOGMSG1( enError, " Invalid the Track Fail [%d] !!!", pLOBData->uiAETID );
    }

}

/**
 * @brief     LOB 데이터 기반으로 스캔 수집을 설정합니다.
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-03-10, 20:34
 * @warning
 */
void CEmitterMerge::RequestScanCollect( SRxLOBData *pLOBData )
{
#ifdef _POCKETSONATA_
    STR_ANALINFO strAnalInfo;

    if( m_pTheEmitterMergeMngr->EnScanProcess() == enSCAN_Requesting ) {
        m_pTheEmitterMergeMngr->EnScanProcess( enSCAN_Processing );

        strAnalInfo.enBoardID = m_strAnalInfo.enBoardID;
        strAnalInfo.iCh = _spZero;
        strAnalInfo.uiTotalLOB = _spOne;
        strAnalInfo.uiAETID = pLOBData->uiAETID;
        strAnalInfo.uiABTID = pLOBData->uiABTID;
        g_pTheSignalCollect->QMsgSnd( enTHREAD_REQ_SET_SCANWINDOWCELL, m_pTheEmitterMergeMngr->GetABTData(), sizeof(SRxABTData), & strAnalInfo, sizeof(STR_ANALINFO), GetThreadName() );
    }
#endif

}

/**
 * @brief     스캔 중인 LOB에 대해서 재설정하여 스캔 분석을 수행하도록 합니다.
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-01-16 18:06:04
 * @warning
 */
void CEmitterMerge::RequestScanReCollect()
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

#ifdef _POCKETSONATA_
    int i;

    char *pString;

    //size_t szSize;

    STR_AET stAET;
    SRxABTData *pSRxABTData;
    SELABTDATA_EXT *pABTExtData;

    pSRxABTData = m_pTheEmitterMergeMngr->GetABTData();
    pABTExtData = m_pTheEmitterMergeMngr->GetABTExtData();

	if (pSRxABTData != NULL) {
		// AET로 변환
		memset(&stAET, 0, sizeof(stAET));

		stAET.aoa = SONATA::ENCODE::DOA(pSRxABTData->fDOAMean);
		stAET.noEMT = (int)pSRxABTData->uiABTID;
		stAET.sigType = pSRxABTData->iSignalType;

		stAET.frq.iBand = SONATA::ENCODE::BAND(pSRxABTData->fFreqMean);
		stAET.frq.iType = pSRxABTData->iFreqType;
		stAET.frq.iMean = SONATA::ENCODE::FREQ(stAET.frq.iBand, pSRxABTData->fFreqMean);
		stAET.frq.iMin = SONATA::ENCODE::FREQ(stAET.frq.iBand, pSRxABTData->fFreqMin);
		stAET.frq.iMax = SONATA::ENCODE::FREQ(stAET.frq.iBand, pSRxABTData->fFreqMax);
		stAET.frq.iPatType = pSRxABTData->iFreqPatternType;
		stAET.frq.iPatPrd = (int)SONATA::ENCODE::TOA(pSRxABTData->fFreqPatternPeriodMean);
		stAET.frq.iSwtLev = pSRxABTData->iFreqPositionCount;
		for (i = 0; i < stAET.frq.iSwtLev; ++i) {
			stAET.frq.iSwtVal[i] = SONATA::ENCODE::FREQ(stAET.frq.iBand, pSRxABTData->fFreqSeq[i]);
		}

		stAET.pri.iType = pSRxABTData->iPRIType;
		stAET.pri.tMean = SONATA::ENCODE::TOA(pSRxABTData->fPRIMean);
		stAET.pri.tMin = SONATA::ENCODE::TOA(pSRxABTData->fPRIMin);
		stAET.pri.tMax = SONATA::ENCODE::TOA(pSRxABTData->fPRIMax);
		stAET.pri.iPatType = pSRxABTData->iPRIPatternType;
		stAET.pri.fJtrPer = pSRxABTData->fPRIJitterRatio;
		stAET.pri.iSwtLev = pSRxABTData->iPRIPositionCount;
		for (i = 0; i < stAET.pri.iSwtLev; ++i) {
			stAET.pri.TSwtVal[i] = SONATA::ENCODE::TOA(pSRxABTData->fPRISeq[i]);
		}

		stAET.pw.iMean = SONATA::ENCODE::PW(pSRxABTData->fPWMean);
		stAET.pw.iMin = SONATA::ENCODE::PW(pSRxABTData->fPWMin);
		stAET.pw.iMax = SONATA::ENCODE::PW(pSRxABTData->fPWMax);

		stAET.pa.iMean = SONATA::ENCODE::PA(pSRxABTData->fPAMean);
		stAET.pa.iMin = SONATA::ENCODE::PA(pSRxABTData->fPAMin);
		stAET.pa.iMax = SONATA::ENCODE::PA(pSRxABTData->fPAMax);

		stAET.as.iStat = pSRxABTData->iScanType != 0 ? SELF_SUCCESS : SELF_FAIL;
		stAET.as.iType = pSRxABTData->iScanType;
		stAET.as.iPrd = SONATA::ENCODE::SCNPRD(pSRxABTData->fMeanScanPeriod);

		stAET.seen.uiFrst = (UINT)pSRxABTData->tiFirstSeenTime;
		stAET.seen.uiLast = (UINT)pSRxABTData->tiLastSeenTime;

		stAET.priLev = (unsigned int)pSRxABTData->iRadarModePriority;
		pString = m_pTheEmitterMergeMngr->GetELNOT(pSRxABTData->iRadarModeIndex);
		if (pString) { strncpy((char *)stAET.elintNotation, pString, sizeof(stAET.elintNotation)); }
		pString = m_pTheEmitterMergeMngr->GetRadarModeName(pSRxABTData->iRadarModeIndex);
		if (pString) { strncpy((char *)stAET.emitterName, pString, sizeof(stAET.emitterName)); }
		pString = m_pTheEmitterMergeMngr->GetThreatName(pSRxABTData->iRadarModeIndex);
		if (pString) { strncpy((char *)stAET.threatName, pString, sizeof(stAET.threatName)); }

		stAET.id.coAmbi = min(pABTExtData->idInfo.nCoRadarModeIndex, _spMaxCoSysAmbi);
		//szSize = sizeof(int) * MAX_IDCANDIDATE;
		memcpy((int *)stAET.id.iNoIPL, (int *)pABTExtData->idInfo.nRadarModeIndex, sizeof(stAET.id.iNoIPL));

		// 랜 메시지 전달한다.

#ifdef _TESTSBC_
#else
		if (pABTExtData->enBeamEmitterStat == E_ES_NEW || pABTExtData->enBeamEmitterStat == E_ES_REACTIVATED) {
			SendLan(enAET_NEW_CCU, &stAET, sizeof(stAET), pABTExtData);
		}
		else {
			SendLan(enAET_UPD_CCU, &stAET, sizeof(stAET), pABTExtData);
		}
#endif

#endif
	}

}

/**
 * @brief     
 * @param     unsigned int uiOpcode
 * @param     void * pData
 * @param     unsigned int uiDataSize
 * @param     SELABTDATA_EXT * pABTExtData
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-02-27, 23:00
 * @warning
 */
void CEmitterMerge::SendLan( unsigned int uiOpcode, void *pData, unsigned int uiDataSize, SELABTDATA_EXT *pABTExtData )
{
    time_t now;

    now = time(NULL);
    if( pABTExtData != NULL && ( uiOpcode == (UINT) enAET_NEW_CCU || difftime( now, pABTExtData->tiSendLan ) > 1.0 || ( pABTExtData->uiOpcode != uiOpcode ) ) ) {
        CCommonUtils::SendLan( uiOpcode, pData, uiDataSize );

        pABTExtData->uiOpcode = uiOpcode;
        pABTExtData->tiSendLan = time( NULL );
    }
    else {
        LOGMSG( enNormal, " Ignore the Sending the LAN message !!!" );
    }

}

/**
 * @brief     TCPIP를 통해서 위협 삭제 메시지를 전송합니다.
 * @param     unsigned int uiAETID
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-02-27, 23:52
 * @warning
 */
void CEmitterMerge::SendDelete( unsigned int uiAETID )
{
    CCommonUtils::SendLan( enAET_DEL_CCU, & uiAETID, sizeof(uiAETID) );
}

/**
 * @brief     CED/EOB 라이브러리를 재로딩 합니다.
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-11-04 19:06:17
 * @warning
 */
void CEmitterMerge::ReloadLibrary()
{
    m_pTheEmitterMergeMngr->UpdateCEDEOBLibrary();
}

