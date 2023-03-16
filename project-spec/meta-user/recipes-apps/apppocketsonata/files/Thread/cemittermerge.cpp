﻿// CEmitterMerge.cpp: implementation of the CEmitterMerge class.
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



/**
 * @brief     초기 멤버 변수값등을 설정하는 객체 생성자 입니다.
 * @param     int iKeyId
 * @param     char * pClassName
 * @param     bool bArrayLanData
 * @return
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-01-04 16:44:46
 * @warning
 */
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

    Init();

}

/**
 * @brief     종료 메시지와 메모리 해지를 처리하는 객체 소멸자 입니다.
 * @return
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-02-03 10:13:33
 * @warning
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
 * @brief     Init
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-03-16 09:34:41
 * @warning
 */
void CEmitterMerge::Init()
{
    m_sLOBOtherInfo.bUpdate = false;
}

/**
 * @brief     CThread 클래스의 Run() 함수를 호출하여 쓰레드를 생성하게 합니다.
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
 * @brief     쓰레드에서 서버 또는 클라이언트를 실행하게 한다.
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

    while( m_bThreadLoop ) {
        //if( QMsgRcv( enTIMER, OS_SEC(5) ) == -1 ) {
        if( QMsgRcv() == -1 ) {
            perror( "QMsgRcv(CEmitterMerge)" );
        }
        else {
            switch( m_pMsg->uiOpCode ) {
                // 운용 제어 관련 메시지
                case enREQ_OP_START:
                    // QMsgClear();
                    InitEmitterMerge();
                    break;

                case enTHREAD_DISCONNECTED:
                case enREQ_OP_SHUTDOWN:
                    QMsgClear();
                    InitEmitterMerge();
                    break;

				case enREQ_OP_RESTART:
					QMsgClear();
                    InitEmitterMerge();
					break;

                // 위협 정보 관련 메시지
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

                //case enTHREAD_IPL_END :
                case enTHREAD_RELOAD_LIBRARY :
                    ReloadLibrary();
                    break;

                default:
                    LOGMSG2( enError, "[%s]에서 잘못된 명령(0x%x)을 수신하였습니다 !!", GetThreadName(), m_pMsg->uiOpCode );
                    break;
            }

            SendEchoMessage();
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
void CEmitterMerge::InitEmitterMerge()
{
    Init();

    m_pTheEmitterMergeMngr->Init();
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
        //LOGMSG5( enDebug, "[%d] Band, in the %s Ch[%d/%d] 채널/빔 번호 에서 [%d] 개의 위협 관리를 수행합니다." , m_strAnalInfo.enBoardID, g_szCollectBank[ CCommonUtils::GetEnumCollectBank( m_strAnalInfo.iCh ) ], m_strAnalInfo.iCh, m_strAnalInfo.uiABTID, m_strAnalInfo.uiTotalLOB );
    }
    else {
        //LOGMSG3( enDebug, "[%d] Band, [%d/%d] 채널/빔 번호 에서 스캔 결과를 업데이트합니다." , m_strAnalInfo.enBoardID, m_strAnalInfo.iCh, m_strAnalInfo.uiABTID );
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

    enMode = g_pTheTaskMngr->GetMode();

    if ( enMode == enOP_Mode ) {

        // 삭제 처리를 한다.
        SELINDEX stELINDEX = m_pTheEmitterMergeMngr->DeleteThreat();

        if (stELINDEX.uiAET != 0 && stELINDEX.uiABT != 0 ) {
            LOGMSG2(enDebug, "위협[%d/%d] 삭제 처리를 수행합니다.", stELINDEX.uiAET, stELINDEX.uiABT);
        }

    }

}

/**
 * @brief     LOB 데이터 기반으로 추적 수집을 설정합니다.
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
    bool bTrack = m_pTheEmitterMergeMngr->ReqTrack();

    SRxABTData *pABTData=m_pTheEmitterMergeMngr->GetABTData();

    // 빔이 생성 여부에 따라 추적으로 요청 여부를 결정한다.
    if (pABTData != NULL) {
        STR_ANALINFO strAnalInfo;

        // PDW 헤더 정보 저장
        memcpy(&strAnalInfo.uniPDWHeader, &m_pMsg->x.strAnalInfo.uniPDWHeader, sizeof(UNION_HEADER));

        if (pLOBData != NULL) {
            if (bTrack == true) {
                strAnalInfo.enBoardID = m_strAnalInfo.enBoardID;

                //strAnalInfo.iCh = (CCommonUtils::GetEnumCollectBank(m_strAnalInfo.iCh) == enTrackCollectBank ? m_strAnalInfo.iCh : _spZero);
                strAnalInfo.uiCh = 0;

                strAnalInfo.uiTotalLOB = _spOne;
                strAnalInfo.uiAETID = pLOBData->uiAETID;
                strAnalInfo.uiABTID = pLOBData->uiABTID;

                g_pTheSignalCollect->QMsgSnd(enTHREAD_REQ_SET_TRACKWINDOWCELL, pABTData, sizeof(SRxABTData), &strAnalInfo, sizeof(STR_ANALINFO), GetThreadName());
            }
        }
        else {
            if (bTrack == false) {
                g_pTheSignalCollect->QMsgSnd(enTHREAD_REQ_SET_TRACKWINDOWCELL, pABTData, sizeof(SRxABTData), &m_strAnalInfo, sizeof(STR_ANALINFO), GetThreadName());
            }
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
    UINT uiAETID, uiABTID;
    STR_ANALINFO strAnalInfo;

    SRxABTData *pSRxABTData;
    SELABTDATA_EXT *pABTExtData;

    uiAETID = m_pMsg->x.strCollectInfo.uiAETID;
    uiABTID = m_pMsg->x.strCollectInfo.uiABTID;

    strAnalInfo.enBoardID = g_enBoardId;
    strAnalInfo.uiCh = m_pMsg->x.strCollectInfo.uiCh;
    strAnalInfo.uiTotalLOB = _spOne;
    strAnalInfo.uiAETID = uiAETID;
    strAnalInfo.uiABTID = uiABTID;

    pSRxABTData = m_pTheEmitterMergeMngr->GetABTData( uiAETID, uiABTID);
    pABTExtData = m_pTheEmitterMergeMngr->GetABTExtData(uiAETID, uiABTID);

    if( pSRxABTData != NULL ) {
        //g_pTheSignalCollect->QMsgSnd( enTHREAD_REQ_SET_TRACKWINDOWCELL, pSRxABTData, (UINT) sizeof(SRxABTData), & strAnalInfo, sizeof(STR_ANALINFO) );

        //SendLan( enAET_LST_CCU, & strAnalInfo.uiABTID, sizeof(strAnalInfo.uiABTID), pABTExtData );
    }
    else {
        LOGMSG2( enNormal, " 위협[%d/%d] 이 이미 삭제되어 추적 채널을 닫도록 요청합니다. !", m_pMsg->x.strCollectInfo.uiAETID, m_pMsg->x.strCollectInfo.uiABTID );

        // 해당 추적 채널을 닫도록 요청합니다.
        //g_pTheSignalCollect->QMsgSnd(enTHREAD_REQ_CLOSE_TRACKWINDOWCELL, pSRxABTData, (UINT)sizeof(SRxABTData), &strAnalInfo, sizeof(STR_ANALINFO));
        //g_pTheSignalCollect->QMsgSnd(enTHREAD_REQ_CLOSE_TRACKWINDOWCELL, &strAnalInfo, sizeof(STR_ANALINFO));

        //SendLan(enAET_DEL_CCU, &strAnalInfo.uiABTID, sizeof(strAnalInfo.uiABTID), pABTExtData);
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
        strAnalInfo.uiCh = _spZero;
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
 * @brief     신규/추적/소실 LOB 데이터를 랜으로 전달합니다.
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

    SAETData stAET;
    SRxLOBData *pSRxLOBData;
    SRxABTData *pSRxABTData;
    SRxAETData *pSRxAETData;
    SELABTDATA_EXT *pABTExtData;

    pSRxLOBData = m_pTheEmitterMergeMngr->GetLOBData();
    pSRxABTData = m_pTheEmitterMergeMngr->GetABTData();
    pSRxAETData = m_pTheEmitterMergeMngr->GetAETData();
    pABTExtData = m_pTheEmitterMergeMngr->GetABTExtData();

	if (pSRxABTData != NULL) {
		// 랜 메시지 전달한다.

#ifdef _TESTSBC_
#else
        memcpy( & stAET.stLOBData, pSRxLOBData, sizeof( SRxLOBData ) );
        memcpy( &stAET.stABTData, pSRxABTData, sizeof( SRxABTData ) );
        memcpy( &stAET.stAETData, pSRxAETData, sizeof( SRxAETData ) );

		if (pABTExtData->enBeamEmitterStat == E_ES_NEW || pABTExtData->enBeamEmitterStat == E_ES_REACTIVATED) {
			SendLan( enNUP_THREAT_DATA, & stAET, sizeof(stAET), pABTExtData);
		}
		else {
			//SendLan(enAET_UPD_CCU, &stAET, sizeof(stAET), pABTExtData);
		}
#endif

#endif
	}

}

/**
 * @brief     연결된 서버에 데이터를 송신한다.
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
    if( pABTExtData != NULL && ( /* uiOpcode == ( UINT ) enNUP_THREAT_DATA || */ difftime(now, pABTExtData->tiSendLan) > 1.0 || ( pABTExtData->uiOpcode != uiOpcode ) ) ) {
        g_pTheCCUSocket->SendLan( enNUP_THREAT_DATA, pData, uiDataSize );

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
    //CCommonUtils::SendLan( enAET_DEL_CCU, & uiAETID, sizeof(uiAETID) );
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

