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

int CEmitterMerge::_uiCoManageDatabase = 0;


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
 CEmitterMerge::CEmitterMerge( int iThreadPriority, const char *pClassName, bool bArrayLanData ) : CThread( iThreadPriority, pClassName, bArrayLanData ), CMSSQL( & m_theMyODBC )
 #else
 CEmitterMerge::CEmitterMerge( int iThreadPriority, const char *pClassName, bool bArrayLanData ) : CThread( iThreadPriority, pClassName, bArrayLanData )
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
        m_pTheEmitterMergeMngr = new CELEmitterMergeMngr( true, szSQLiteFileName );
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

    m_pMsg = GetRecvDataMessage();

    while( m_bThreadLoop ) {
        if( QMsgRcv( enTIMER, OS_SEC(5) ) == -1 ) {
            perror( "QMsgRcv(CEmitterMerge)" );
        }
        else {

            switch( m_pMsg->uiOpCode ) {
                ///////////////////////////////////////////////////////////////////////////////////
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

                ///////////////////////////////////////////////////////////////////////////////////
                // 위협 정보 관련 메시지
                case enTHREAD_DETECTANAL_RESULT:
                    InitOfMessageData();
                    MergeEmitter();
					DeleteThreat();
                    break;

#if CO_SCAN_CHANNEL > 0
                // 스캔 분석 관련 메시지
                case enTHREAD_SCANANAL_RESULT :
                    InitOfMessageData();
                    UpdateScanResult();
                    break;

                case enTHREAD_SCANANAL_FAIL:
                    InitOfMessageData();
                    UpdateScanFail();
                    break;

                case enTHREAD_SCANANAL_ERROR:
                    InitOfMessageData();
                    UpdateScanError();
                    break;
#endif

                //
                case enTHREAD_KNOWNANAL_START :
                    MergeEmitter();
                    break;

                case enTHREAD_KNOWNANAL_FAIL :
                    RequestTrackReCollect();
                    break;

                case enTHREAD_SCANANAL_START :
                    MergeEmitter();
                    //UpdateScanEmitter();
                    break;

                case enTHREAD_TIMER:
                    DeleteThreat();
                    ManageDatabase();
                    break;

                case enTHREAD_REQ_SHUTDOWN :
                    Log( enDebug, " [%s]를 Shutdown 메시지를 처리합니다...", GetThreadName() );
                    //bWhile = false;
                    break;

                case enTHREAD_DETECTANAL_END :
                    Log( enDebug, " 탐지 수집/분석 완료를 수신했습니다." );

                    // 탐지 분석 완료로 이 시그널을 이용하여 위협 사이클 관리를 수행하고...
                    break;

                //case enTHREAD_IPL_END :
                case enTHREAD_RELOAD_LIBRARY :
                    // Log( enDebug, " 큐 크기가 [%d] 입니다.", QMsgRcvSize() );
                    ReloadLibrary();
                    break;

                default:
                    Log( enError, "[%s]에서 잘못된 명령(0x%x)을 수신하였습니다 !!", GetThreadName(), m_pMsg->uiOpCode );
                    break;
            }

        }
    }
}

/**
 * @brief     메시지간의 데이터를
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-03-20 12:14:14
 * @warning
 */
void CEmitterMerge::InitOfMessageData()
{

    // 1. 메지지 내용을 멤머 변수에 복사한다.
    // 1.1 메시지 헤더 정보를 저장한다.
    // STR_DETANAL_INFO *pstrDetAnalInfo = GetRecvDetectAnalInfo();

    // 1.2 LOB 데이터를 갖고온다.
    void *pRecvData = GetRecvData();
    if( pRecvData != NULL ) {
        // LOB 데이터가 여러개인 탐지에서 올 경우의
        memcpy( m_uniLanData.szFile, GetRecvData(), m_pMsg->uiArrayLength );

        m_pLOBData = & m_uniLanData.stLOBData[0];
    }
    else {
        m_pLOBData = NULL;
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

    SRxLOBHeader strLOBHeader;

    SRxLOBData *pLOBData;

    // 위협 관리 초기화
    m_pTheEmitterMergeMngr->Start();

    if( m_pLOBData != NULL ) {
        // 2. 위협 관리를 호출한다.
        strLOBHeader.uiNumOfLOB = m_pRecvDetectAnalInfo->uiTotalLOB;
        pLOBData = m_pLOBData;

        for( i=0 ; i < strLOBHeader.uiNumOfLOB; ++i ) {
            // 2.1 분석된 LOB 데이터를 병합 관리한다.
            m_pTheEmitterMergeMngr->ManageThreat( & strLOBHeader, pLOBData, & m_sLOBOtherInfo );

#if CO_TRACK_CHANNEL > 0
            // 2.2 LOB의 추적 관리를 수행한다.
            m_pTheEmitterMergeMngr->ManageTrack( m_pRecvDetectAnalInfo, pLOBData, & m_sLOBOtherInfo, false );
            RequestTrackCollect( pLOBData );
#endif

#if CO_SCAN_CHANNEL > 0
            // 2.3 LOB의 스캔 관리를 수행한다.
            m_pTheEmitterMergeMngr->ManageScan( m_pRecvDetectAnalInfo->enCollectBank, pLOBData, & m_sLOBOtherInfo );
            RequestScanCollect( pLOBData );
#endif

            // 2.3 빔 정보를 제어조종 및 재밍신호관리 장치에게 전송한다.
            SendNewUpd();

        // 2.4 추적 업데이트 성공 여부 플레그 업데이트
    //         if( pLOBData->uiABTID == m_strDetAnalInfo.uiABTID && m_strDetAnalInfo.uiABTID != _spZero ) {
    //             bTrkLOB = true;
    //         }

            ++ pLOBData;

        }
    }

#if CO_TRACK_CHANNEL > 0
    // 추적 실패 처리여부를 수행한다.
    m_pTheEmitterMergeMngr->ManageTrack( m_pRecvDetectAnalInfo, NULL, & m_sLOBOtherInfo, false );
    RequestTrackCollect( NULL );
#endif

#ifdef _SERIAL_DETECT_FLOW_
    STR_COLLECT_INFO strCollectInfo;

    strCollectInfo.Set( 0, 0, 0, 0, m_pMsg->x.strDetAnalInfo.enPCIDriver, m_pMsg->x.strDetAnalInfo.enCollectBank, 0 );
    g_pTheSignalCollect->QMsgSnd( enTHREAD_REQ_SET_DETECTWINDOWCELL, & strCollectInfo, sizeof( STR_COLLECT_INFO ), GetThreadName() );

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
            Log(enDebug, "위협[%d/%d] 삭제 처리를 수행합니다.", stELINDEX.uiAET, stELINDEX.uiABT);
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
//     bool bTrack = m_pTheEmitterMergeMngr->ReqTrack();
//
//     SRxABTData *pABTData=m_pTheEmitterMergeMngr->GetABTData();
//
//     // 빔이 생성 여부에 따라 추적으로 요청 여부를 결정한다.
//     if (pABTData != NULL) {
//         STR_DETANAL_INFO strAnalInfo;
//
//         // PDW 헤더 정보 저장
//         //memcpy(&strAnalInfo.uniPDWHeader, &m_pMsg->x.strAnalInfo.uniPDWHeader, sizeof(UNION_HEADER));
//
//         if (pLOBData != NULL) {
//             if (bTrack == true) {
//                 strAnalInfo.enBoardID = m_strDetAnalInfo.enBoardID;
//
//                 //strAnalInfo.iCh = (CCommonUtils::GetEnumCollectBank(m_strAnalInfo.iCh) == enTrackCollectBank ? m_strAnalInfo.iCh : _spZero);
//                 strAnalInfo.uiCh = 0;
//
//                 strAnalInfo.uiTotalLOB = _spOne;
//                 strAnalInfo.uiAETID = pLOBData->uiAETID;
//                 strAnalInfo.uiABTID = pLOBData->uiABTID;
//
//                 g_pTheSignalCollect->QMsgSnd(enTHREAD_REQ_SET_TRACKWINDOWCELL, pABTData, sizeof(SRxABTData), &strAnalInfo, sizeof(STR_DETANAL_INFO), GetThreadName());
//             }
//         }
//         else {
//             if (bTrack == false) {
//                 g_pTheSignalCollect->QMsgSnd(enTHREAD_REQ_SET_TRACKWINDOWCELL, pABTData, sizeof(SRxABTData), &m_strDetAnalInfo, sizeof(STR_DETANAL_INFO), GetThreadName());
//             }
//         }
//     }

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
    //STR_DETANAL_INFO strAnalInfo;

    SRxABTData *pSRxABTData;
    //SELABTDATA_EXT *pABTExtData;

    uiAETID = m_pMsg->x.strCollectInfo.uiAETID;
    uiABTID = m_pMsg->x.strCollectInfo.uiABTID;

    //strAnalInfo.enBoardID = g_enBoardId;
    //strAnalInfo.uiCh = m_pMsg->x.strCollectInfo.uiCh;
    //strAnalInfo.uiTotalLOB = _spOne;
    //strAnalInfo.uiAETID = uiAETID;
    //strAnalInfo.uiABTID = uiABTID;

    pSRxABTData = m_pTheEmitterMergeMngr->GetABTData( uiAETID, uiABTID);
    //pABTExtData = m_pTheEmitterMergeMngr->GetABTExtData(uiAETID, uiABTID);

    if( pSRxABTData != NULL ) {
        //g_pTheSignalCollect->QMsgSnd( enTHREAD_REQ_SET_TRACKWINDOWCELL, pSRxABTData, (UINT) sizeof(SRxABTData), & strAnalInfo, sizeof(STR_ANALINFO) );

        //SendLan( enAET_LST_CCU, & strAnalInfo.uiABTID, sizeof(strAnalInfo.uiABTID), pABTExtData );
    }
    else {
        Log( enNormal, " 위협[%d/%d] 이 이미 삭제되어 추적 채널을 닫도록 요청합니다. !", m_pMsg->x.strCollectInfo.uiAETID, m_pMsg->x.strCollectInfo.uiABTID );

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
    unsigned int uiScanStep;
    ENUM_SCAN_PROCESS enScanProcess;

    enScanProcess = m_pTheEmitterMergeMngr->EnScanProcess();

    uiScanStep = m_pTheEmitterMergeMngr->GetABTScanStep();
    if( ( enScanProcess == enSCAN_Requesting || enScanProcess == enSCAN_Retrying ) && uiScanStep != _spZero ) {
        m_pTheEmitterMergeMngr->EnScanProcess( enSCAN_Collecting );

        // 신규 스캔 수집 채널시
        if( pLOBData != NULL ) {
            m_pstrScanAnalInfo->Set( g_enBoardId, ( unsigned int ) -1, enUnknownCollectBank, pLOBData->uiAETID, pLOBData->uiABTID, m_pTheEmitterMergeMngr->GetABTIndex(), uiScanStep );
        }
        // 스캔 분석 실패로 재시도 일 때
        else {
            m_pstrScanAnalInfo->Set( g_enBoardId, ( unsigned int ) -1, enUnknownCollectBank, m_pRecvScanAnalInfo->uiAETID, m_pRecvScanAnalInfo->uiABTID, m_pRecvScanAnalInfo->uiABTIndex, uiScanStep );
        }

        // 위협 정보는 해당 쓰레드에서 실행시 해당 방사체/빔 번호를 갖고 와서 스캔 수집을 수행합니다.
        g_pTheSignalCollect->QMsgSnd( enTHREAD_REQ_SCAN_START, GetUniMessageData(), sizeof( UNI_MSG_DATA ), GetThreadName() );
    }
    else if( enScanProcess == enSCAN_CANTProcessing ) {
        Log( enDebug, "위협[%d/%d]에 대해서 스캔 분석 불가 합니다.", m_pRecvScanAnalInfo->uiAETID, m_pRecvScanAnalInfo->uiABTID );
    }
    else {

    }

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
    //char *pString;

    SAETData stAET;
    SRxLOBData *pSRxLOBData;
    SRxABTData *pSRxABTData;
    SRxAETData *pSRxAETData;
    SELABTDATA_EXT *pABTExtData;

    pSRxLOBData = m_pTheEmitterMergeMngr->GetLOBData();
    pSRxABTData = m_pTheEmitterMergeMngr->GetABTData();
    pSRxAETData = m_pTheEmitterMergeMngr->GetAETData();
    pABTExtData = m_pTheEmitterMergeMngr->GetABTExtData();

	if (pSRxABTData != NULL && pSRxAETData != NULL ) {
		// 랜 메시지 전달한다.

#ifdef _TESTSBC_
#else
        memcpy( & stAET.stLOBData, pSRxLOBData, sizeof( SRxLOBData ) );
        memcpy( & stAET.stABTData, pSRxABTData, sizeof( SRxABTData ) );
        memcpy( & stAET.stAETData, pSRxAETData, sizeof( SRxAETData ) );

		SendLan( enNUP_THREAT_DATA, & stAET, sizeof(stAET), pABTExtData);
#endif

#endif
	}
    else {
        Log( enError, "위협 정보가 잘못 됐습니다 !!" );
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
    if( pABTExtData != NULL && ( ( pABTExtData->enBeamEmitterStat == E_ES_NEW || pABTExtData->enBeamEmitterStat == E_ES_REACTIVATED ) || difftime(now, pABTExtData->tiSendLan) > 1.0 || ( pABTExtData->uiOpcode != uiOpcode ) ) ) {
        g_pTheCCUSocket->SendLan( enNUP_THREAT_DATA, pData, uiDataSize );

        pABTExtData->uiOpcode = uiOpcode;
        pABTExtData->tiSendLan = time( NULL );
    }
    else {
        Log( enNormal, "위협 결과[%d/%d] 랜 송신을 무시 합니다." , m_pLOBData->uiAETID, m_pLOBData->uiABTID );
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
    int iRet;

    char szSrcFilename[100], szDstFilename[100];

    Log( enDebug, "CEDEOB 라이브러리 변경됨을 수신했습니다." );

    sprintf( szSrcFilename, "%s/%s", SHARED_DATA_DIRECTORY, CEDEOB_SQLITE_FILENAME );
    sprintf( szDstFilename, "%s%s/%s", RAMDRV, RAMDRV_NO, CEDEOB_SQLITE_FILENAME );

    iRet = CCommonUtils::CopySrcToDstFile( szSrcFilename, szDstFilename, 1, 0077 );

    if( iRet <= 0 ) {
        Log( enError, "원본[%s] 위협 라이브러리를 목적지[%s]로 복사하지 못했습니다." , szSrcFilename, szDstFilename );
        g_pTheCCUSocket->SendLan( enSYSERROR, "SBC 시간을 설정하지 못했습니다 !" );
    }
    else {
        m_pTheEmitterMergeMngr->UpdateCEDEOBLibrary();
        m_pTheEmitterMergeMngr->LoadCEDEOBLibrary();

        //g_pTheCCUSocket->SendLan( enRES_RELOAD_LIBRARY,
    }

}

#if CO_SCAN_CHANNEL > 0
/**
 * @brief     UpdateScanInfo
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-03-17 10:55:47
 * @warning
 */
void CEmitterMerge::UpdateScanResult()
{
    SRxLOBHeader strLOBHeader;

    if( m_pLOBData != NULL ) {
        Log( enDebug, "빔 번호[%d] 에 대해서 스캔 결과[%d/%.4f] 변경합니다.", m_pLOBData->uiABTID, m_pLOBData->ucScanType, m_pLOBData->fScanPeriod );

        // 1. LOB 헤더 데이터를 초기 설정합니다.
        strLOBHeader.uiNumOfLOB = 1;

        // 2. 스캔 결과를 저장합니다.
        m_pTheEmitterMergeMngr->ManageThreat( &strLOBHeader, m_pLOBData, &m_sLOBOtherInfo, true );

        // 3. 스캔 상태를 업데이트 합니다.
        m_pTheEmitterMergeMngr->ManageScan( m_pRecvScanAnalInfo->enCollectBank, m_pLOBData, &m_sLOBOtherInfo );

        // 4. 빔 정보를 제어조종장치로 전송한다.
        SendNewUpd();
    }
    else {
        Log( enError, "m_pLOBData 값이 NULL 입니다." );
    }

}

/**
 * @brief     스캔 실패 처리로 다음 수집 단계로 진행하며 마지막 단계시 수집 중지 처리를 수행합니다.
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-03-21 13:19:54
 * @warning
 */
void CEmitterMerge::UpdateScanFail()
{
    // 1. ABT 빔 데이터를 설정 합니다.
    m_pTheEmitterMergeMngr->ABTPreSetting( m_pRecvScanAnalInfo->uiAETID, m_pRecvScanAnalInfo->uiABTID );

    // 2. 스캔 상태를 업데이트 합니다.
    m_pTheEmitterMergeMngr->ManageScan( m_pRecvScanAnalInfo->enCollectBank, m_pLOBData, &m_sLOBOtherInfo );

    // 3. 스캔 상태에 따라 스캔 수집 요청을 합니다.
    RequestScanCollect( m_pLOBData );

    // 5. 빔 정보를 제어조종장치로 전송한다.
    // SendNewUpd();

}

/**
 * @brief     스캔 분석 에러시 처리 한다. 스캔 중지 처리를 수행합니다.
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-03-23 11:32:37
 * @warning
 */
void CEmitterMerge::UpdateScanError()
{
    m_pTheEmitterMergeMngr->ABTPreSetting( m_pRecvScanAnalInfo->uiAETID, m_pRecvScanAnalInfo->uiABTID );

    m_pTheEmitterMergeMngr->ManageScan( m_pRecvScanAnalInfo->enCollectBank, m_pLOBData, &m_sLOBOtherInfo );

}
#endif

/**
 * @brief     데이터 베이스를 유지 관리한다.
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-03-19 16:50:28
 * @warning
 */
void CEmitterMerge::ManageDatabase()
{
    if( g_pTheTaskMngr->GetMode() == enOP_Mode ) {
        if( _uiCoManageDatabase % 200 ) {
            m_pTheEmitterMergeMngr->ManageDatabase();
        }
    }

    ++_uiCoManageDatabase;
}
