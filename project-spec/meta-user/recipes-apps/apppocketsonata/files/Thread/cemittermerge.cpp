// CEmitterMerge.cpp: implementation of the CEmitterMerge class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

//#include <memory.h>

#include "cemittermerge.h"

#include "csignalcollect.h"

#include "../Utils/ccommonutils.h"

#include "../Anal/SigAnal/cencdec.h"
#include "../Anal/Collect/DataFile/DataFile.h"

#include "../Include/globals.h"

#define _DEBUG_

extern std::string g_strPCIDrverDirection[en_ELEMENT_PCI_DRIVER];

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
 CEmitterMerge::CEmitterMerge( int iThreadPriority, const char *pThreadName, bool bArrayLanData ) : CThread( iThreadPriority, pThreadName, bArrayLanData ), CMSSQL( & m_theMyODBC )
 #else
 CEmitterMerge::CEmitterMerge( int iThreadPriority, const char *pThreadName, bool bArrayLanData ) : CThread( iThreadPriority, pThreadName, bArrayLanData )
 #endif
{
    //LOGENTRY;

#ifdef _SQLITE_
    // SQLITE 파일명 생성하기
    char szSQLiteFileName[100];

    strcpy( szSQLiteFileName, EMITTER_SQLITE_FOLDER );
    strcat( szSQLiteFileName, "/" );

#ifdef _MSC_VER
    char szSrcSQLiteFileName[100];

    sprintf( szSrcSQLiteFileName, "%s_%d.sqlite3", EMITTER_SQLITE_FILENAME, g_enBoardId );
    strcat( szSQLiteFileName, szSrcSQLiteFileName );
#else
    strcat( szSQLiteFileName, EMITTER_SQLITE_FILEEXTNAME );
#endif

    try {
#ifdef __VXWORKS__
        //! DB에 위협 관리 삽입할 때, true 로 설정 합니다.
        m_pTheEmitterMergeMngr = new CELEmitterMergeMngr( true, szSQLiteFileName, GetThreadName() );
#else
        m_pTheEmitterMergeMngr = new CELEmitterMergeMngr( true, szSQLiteFileName, CThread::GetThreadName() );
#endif

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

    // 추적 채널 번호 초기화
    m_theQueueTrackChannel[enLEFT_PCI_DRIVER].Init( CO_TRACK_CHANNEL );
    m_theQueueTrackChannel[enRIGHT_PCI_DRIVER].Init( CO_TRACK_CHANNEL );

    Init();

#if 0
    int szSize = sizeof( UNI_MSG_DATA );

#endif

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
    StopThread();

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

    m_theQueueTrackChannel[enLEFT_PCI_DRIVER].Reset();
    m_theQueueTrackChannel[enRIGHT_PCI_DRIVER].Reset();

#if CO_TRACK_CHANNEL > 0
    unsigned int uiCh;
    for( uiCh = CO_DETECT_CHANNEL ; uiCh < CO_DETECT_CHANNEL + CO_TRACK_CHANNEL ; ++uiCh ) {
        m_theQueueTrackChannel[enLEFT_PCI_DRIVER].Push( uiCh );
        m_theQueueTrackChannel[enRIGHT_PCI_DRIVER].Push( uiCh );
    }
#endif

    CThread::Clear();

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
    //LOGENTRY;

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
    //LOGENTRY;

    m_pMsg = GetRecvDataMessage();

    //! #시험_01 식별 다운로드 충돌
#if 0
    while( true ) {
        m_pTheEmitterMergeMngr->UpdateCEDEOBLibrary();
        m_pTheEmitterMergeMngr->LoadCEDEOBLibrary();
    }

#endif

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
                    //QMsgClear();
                    //InitEmitterMerge();
                    CloseEmitterMerge();
                    break;

				case enREQ_OP_RESTART:
					//QMsgClear();
                    InitEmitterMerge();
					break;

                case enREQ_DELETE_THREAT_DATA:
                    RemoveThreat();
                    break;

                ///////////////////////////////////////////////////////////////////////////////////
                // 위협 정보 관련 메시지
                case enTHREAD_DETECTANAL_RESULT:
                    InitOfMessageData();
                    MergeEmitter( enDET_ANAL );
					DeleteThreat();
                    break;

#if CO_SCAN_CHANNEL > 0
                case enREQ_ANAL_SCAN:
                    InitOfMessageData();
                    UserRequestScan();
                    break;

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

//                 case enTHREAD_SCANANAL_START:
//                     MergeEmitter( enSCN_ANAL );
//                     //UpdateScanEmitter();
//                     break;

#endif

#if CO_TRACK_CHANNEL > 0
                //
                case enTHREAD_KNOWNANAL_START :
                    // TRACE( "추적 성공 메시지: 위협[%04d/%04d], 채널[%d], LOB[%d]\n", m_pRecvTrackAnalInfo->uiAETID, m_pRecvTrackAnalInfo->uiABTID, m_pRecvTrackAnalInfo->uiGlobalCh, m_pRecvTrackAnalInfo->uiTotalLOB );
                    InitOfMessageData();
                    TrackEmitter();
                    MergeEmitter( enTRK_ANAL );
                    DeleteThreat();
                    break;

                case enTHREAD_KNOWNANAL_FAIL :
                    InitOfMessageData();
                    RequestTrackLostDelete();
                    break;

#endif

                case enTHREAD_TIMER:
                    DeleteThreat( 5 );
                    break;

                case enTHREAD_REQ_SHUTDOWN :
                    Log( enDebug, " [%s]를 Shutdown 메시지를 처리합니다...", GetThreadName() );

                    break;

                case enTHREAD_DETECTANAL_END :
                    Log( enDebug, " 탐지 수집/분석 완료를 수신했습니다." );

                    // 탐지 분석 완료로 이 시그널을 이용하여 위협 사이클 관리를 수행하고...
                    break;

                //case enTHREAD_IPL_END :
                case enTHREAD_RELOAD_LIBRARY :
                    ReloadLibrary();
                    break;

                case enTHREAD_REQ_CLEANUP :
                    CleanupDatabase();
                    break;

                case enMONITOR :
                    DisplayMonitor();
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

    // 위협 관리의 LOBDATA 초기화를 설정합니다.
    m_pTheEmitterMergeMngr->InitOfLOBData();

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
 * @brief     CloseEmitterMerge
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2024-01-24 09:59:54
 * @warning
 */
void CEmitterMerge::CloseEmitterMerge()
{
    //Close();

    m_pTheEmitterMergeMngr->Close();
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
void CEmitterMerge::MergeEmitter( ENUM_ANAL_TYPE enAnalType )
{
    //LOGENTRY;
    bool bRet;

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
            // 탐지 또는 추적에 신규 분석된 위협만 위협 관리를 수행합니다.
            if( pLOBData->uiABTID == 0 ) {

                // 2.1 분석된 LOB 데이터를 병합 관리한다.
                bRet = m_pTheEmitterMergeMngr->ManageThreat( & strLOBHeader, pLOBData, & m_sLOBOtherInfo );

                // TRACE( "ME 위협[%04d/%04d]\n", pLOBData->uiAETID, pLOBData->uiABTID );

                if( bRet == true ) {
                    ENUM_COLLECTBANK enCollectBank;

                    enCollectBank = ( enAnalType == enDET_ANAL ? enDetectCollectBank : enTrackCollectBank );
                    if( m_pTheEmitterMergeMngr->Merge() == false ) {
#if CO_TRACK_CHANNEL > 0
                        // 2.1.1 LOB의 추적 여부를 결정하게 합니다.
                        m_pTheEmitterMergeMngr->ManageTrack();

                        // 2.1.2 LOB의 추적 관리를 수행한다.
                        RequestTrackCollect( pLOBData, enCollectBank, true );
#endif

#if CO_SCAN_CHANNEL > 0
                        // 2.1.3 LOB의 스캔 관리를 수행한다.
                        m_pTheEmitterMergeMngr->ManageScan( m_pRecvDetectAnalInfo->enCollectBank, NULL, pLOBData );
                        RequestScanCollect( pLOBData->uiAETID, pLOBData->uiABTID );
#endif

                        m_pTheEmitterMergeMngr->InsertAETABT();

                        // 2.1.4 빔 정보를 통합 콘솔에 전송한다.
                        if( enAnalType == enDET_ANAL ) {
                            SendNewUpd( enNEWDET_THREAT_DATA );
                        }
                        else {
                            SendNewUpd( enNEWTRK_THREAT_DATA );
                        }
                    }
                    else {
                        // 2.2.1. 빔 병합을 수행 합니다.
                        ManageMergeOrSeperateBeam( enAnalType, NULL );
                    }
                }
                else {
                    Log( enError, "위협이 Full 이어서, 신규 LOB에 대해서 처리하지 못합니다 !, 해당 LOB는 무시하게 처리됩니다." );
                    break;

                }

            }
            else {
#ifdef _MSC_VER
                //TRACE( "무시 위협[%04d/%04d]\n", m_pRecvTrackAnalInfo->uiAETID, m_pRecvTrackAnalInfo->uiABTID );
#endif
            }

            ++ pLOBData;

        }
    }
    else {
        strLOBHeader.uiNumOfLOB = 0;
    }

#ifdef _SERIAL_DETECT_FLOW_
    if( m_pMsg->uiOpCode == enTHREAD_DETECTANAL_RESULT ) {
        STR_COLLECT_INFO strCollectInfo;

        strCollectInfo.Set( 0, 0, 0, 0, 0, m_pMsg->x.strDetAnalInfo.enPCIDriver, m_pMsg->x.strDetAnalInfo.enCollectBank, 0 );
        g_pTheSignalCollect->QMsgSnd( enTHREAD_REQ_SET_DETECTWINDOWCELL, & strCollectInfo, sizeof( STR_COLLECT_INFO ), GetThreadName() );

//         if( strLOBHeader.uiNumOfLOB == 0 || true ) {
//             strCollectInfo.Set( 0, 0, 0, 0, 0, 0, m_pMsg->x.strDetAnalInfo.enPCIDriver, m_pMsg->x.strDetAnalInfo.enCollectBank, 0 );
//             g_pTheSignalCollect->QMsgSnd( enTHREAD_REQ_SET_DETECTWINDOWCELL, & strCollectInfo, sizeof( STR_COLLECT_INFO ), GetThreadName() );
//         }
//         else {
//             printf( "\n 탐지 중지 !!" );
//         }
    }

#endif

}

/**
 * @brief     ManageMergeOrSeperateBeam
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2024-02-06 19:55:37
 * @warning
 */
void CEmitterMerge::ManageMergeOrSeperateBeam( ENUM_ANAL_TYPE enAnalType, SRxABTData *pABTData )
{
    unsigned int uiAETID, uiABTID;

    ENUM_MERGE_SEPERATE_BEAM enManageMergedOrSeperatedBeam;

    enManageMergedOrSeperatedBeam = m_pTheEmitterMergeMngr->ManageMergedOrSeperatedBeam();

    // 추적 성공 여부
    if( pABTData != NULL ) {
        SRxABTData *pUpdatedABTData;

        switch( enManageMergedOrSeperatedBeam ) {
            case enMERGE_BEAM:
                pUpdatedABTData = m_pTheEmitterMergeMngr->GetABTData();

                // 2.2 LOB의 추적 관리를 수행한다.(변경된 방사체 번호 적용)
                RequestTrackCollect( m_pLOBData, enTrackCollectBank, false, pUpdatedABTData );

                m_pTheEmitterMergeMngr->InsertAETABT();

                // 2.3.2 위협 삭제
                m_pTheEmitterMergeMngr->GetDeletedThreat( & uiAETID, & uiABTID );
                SendDelete( uiAETID, uiABTID );

                // 2.3.2 빔 병합 결과를 전송
                SendNewUpd( enMRGDET_THREAT_DATA );
                break;

            case enSEPERATE_BEAM:
                pUpdatedABTData = m_pTheEmitterMergeMngr->GetABTData();

                // 2.2 LOB의 추적 관리를 수행한다.(변경된 방사체 번호 적용)
                RequestTrackCollect( m_pLOBData, enTrackCollectBank, false, pUpdatedABTData );

                m_pTheEmitterMergeMngr->InsertAETABT();

                // 2.3.2 위협 삭제
                m_pTheEmitterMergeMngr->GetDeletedThreat( & uiAETID, & uiABTID );
                SendDelete( uiAETID, uiABTID );

                // 2.3.2 빔 병합 결과를 전송
                SendNewUpd( enMRGDET_THREAT_DATA );
                break;

            default:
                // 2.2 LOB의 추적 관리를 수행한다.
                RequestTrackCollect( m_pLOBData, enTrackCollectBank, false, pABTData );

                m_pTheEmitterMergeMngr->InsertAETABT();

                // 2.3.1 추적 성공 위협 결과를 전송
                SendNewUpd( enUPDTRK_THREAT_DATA );
                break;
        }
    }
    else {
        switch( enManageMergedOrSeperatedBeam ) {

            case enMERGE_BEAM:
                m_pTheEmitterMergeMngr->InsertAETABT();

                m_pTheEmitterMergeMngr->GetDeletedThreat( & uiAETID, & uiABTID );
                SendDelete( uiAETID, uiABTID );

                if( enAnalType == enDET_ANAL ) {
                    SendNewUpd( enMRGDET_THREAT_DATA );
                }
                else {
                    SendNewUpd( enMRGTRK_THREAT_DATA );
                }
                break;

            case enSEPERATE_BEAM:
                m_pTheEmitterMergeMngr->InsertAETABT();


                break;

            default:
                m_pTheEmitterMergeMngr->InsertAETABT();

                // 2.2.2 빔 정보를 통합 콘솔에 전송한다.
                if( enAnalType == enDET_ANAL ) {
                    SendNewUpd( enUPDDET_THREAT_DATA );
                }
                else {
                    SendNewUpd( enUPDTRKNEW_THREAT_DATA );
                }
                break;

        }
    }

}

/**
 * @brief     TrackEmitter
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-10-24 11:22:21
 * @warning
 */
void CEmitterMerge::TrackEmitter()
{
    SRxLOBHeader strLOBHeader;

    // 1. 위협 관리 초기화
    m_pTheEmitterMergeMngr->Start();

    if( m_pLOBData != NULL ) {
        // 2. 위협 관리를 호출한다.
        strLOBHeader.uiNumOfLOB = m_pRecvTrackAnalInfo->uiTotalLOB;

        // 첫번쨰 LOB 와 추적 성공 메시지의 방사체/빔 번호가 동일하면 추적 성공으로 처리 합니다.
        if( m_pRecvTrackAnalInfo->uiAETID == m_pLOBData->uiAETID && m_pRecvTrackAnalInfo->uiABTID == m_pLOBData->uiABTID ) {
            SRxABTData *pABTData = m_pTheEmitterMergeMngr->FindABTData( m_pRecvTrackAnalInfo->uiAETID, m_pRecvTrackAnalInfo->uiABTID );

            // TRACE( "추적 위협[%04d/%04d] 성공..%p\n", m_pRecvTrackAnalInfo->uiAETID, m_pRecvTrackAnalInfo->uiABTID, pABTData );

            if( pABTData != NULL ) {
            	//! #추후 : 추적 성공은 위협 관리에서 처리해야 함. 추적에서는 LOB 만...
                m_pTheEmitterMergeMngr->UpdateThreat( & strLOBHeader, m_pLOBData, & m_sLOBOtherInfo );

                // 2.3 변경된 위협 정보를 통합 운용 SW 에게 전송합니다.
                // TRACE( "추적 위협[%04d/%04d] [%04d/%04d] 채널 요청\n" , m_pLOBData->uiAETID, m_pLOBData->uiABTID, m_pRecvTrackAnalInfo->uiAETID, m_pRecvTrackAnalInfo->uiABTID );

                // 2.4 빔 병합을 체크 합니다.
                ManageMergeOrSeperateBeam( enCLEAR_ANAL, pABTData );

            }
            else {
                RequestTrackClose( enABNORMAL_TRACK_CLOSE  );
            }
        }

        // 추적 실패 또는 삭제 처리를 수행합니다.
        else {
            RequestTrackLostDelete();

        }

        //! 신규 LOB 에 대해서 신규 처리를 수행하면 됩니다. 아직 추적의 신규 처리는 무시하게 했습니다.

    }
    else {
        Log( enError, "추적 성공 메시지에서 LOB 데이터가 깨졌습니다 !" );

    }

    // 3. 신규 에미터 처리

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
void CEmitterMerge::DeleteThreat( int iMaxDelete )
{
    ENUM_MODE enMode;

    if( g_pTheTaskMngr != NULL ) {
        enMode = g_pTheTaskMngr->GetMode();

        if ( enMode == enOP_Mode ) {
            SELDELETE stELINDEX;

            int iDelete = 0;

            do {
                // 삭제 처리를 한다.
                stELINDEX = m_pTheEmitterMergeMngr->DeleteThreat( iMaxDelete > 1 );

                if (stELINDEX.uiAETID != 0 ) {
#ifdef __VXWORKS__
                    if( iMaxDelete > 1 ) {
                        printf( "\n" );
                    }
#endif
                    if( stELINDEX.uiABTID != 0 ) {
                        SendLan( enDEL_THREAT_DATA, & stELINDEX, sizeof( stELINDEX ) );
                        //g_pTheCCUSocket->SendLan( enDEL_THREAT_DATA, & stELINDEX, sizeof( stELINDEX ) );

                        Log(enDebug, "위협[%04d/%04d] 삭제 처리 메시지를 전송합니다.", stELINDEX.uiAETID, stELINDEX.uiABTID);
                    }
                    else {
                        SendLan( enDEL_THREAT_DATA, & stELINDEX.uiAETID, sizeof( int ) );
                        //g_pTheCCUSocket->SendLan( enDEL_THREAT_DATA, & stELINDEX.uiAET, sizeof(int) );

                        Log( enDebug, "위협[%04d] 삭제 처리 메시지를 전송합니다.", stELINDEX.uiAETID );
                    }

                    ++ iDelete;
                }
            } while( stELINDEX.uiAETID != 0 && iDelete < iMaxDelete );

        }
    }

}

/**
 * @brief     DeleteThreat
 * @param     unsigned int uiAETID
 * @param     unsigned int uiABTID
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-06-25 17:21:21
 * @warning
 */
void CEmitterMerge::RemoveThreat()
{
    ENUM_MODE enMode;

    enMode = g_pTheTaskMngr->GetMode();

    if( enMode == enOP_Mode ) {
        bool bRet=false;
        BOOL bResult;

        CELThreat *pABTThreat, *pABTNextThreat, *pAETThreat;

        STR_TRKANAL_INFO strTrkAnalInfo;

#ifdef _MSC_VER
        CCommonUtils::AllSwapData32( & m_pMsg->x.stDelete, sizeof( struct SELDELETE ) );

#endif
        pAETThreat = m_pTheEmitterMergeMngr->FindAETThreat( m_pMsg->x.stDelete.uiAETID );

        if( pAETThreat != NULL ) {
            pABTThreat = m_pTheEmitterMergeMngr->GetHeaderThreat( pAETThreat );
            while( pABTThreat != NULL ) {
                SELABTDATA_EXT *pABTExtData;

                if( m_pMsg->x.stDelete.uiABTID == 0 || m_pMsg->x.stDelete.uiABTID == pABTThreat->GetABTID() ) {
                    pABTExtData = m_pTheEmitterMergeMngr->GetABTExtData( pABTThreat->m_uiIndex );

                    m_pTheEmitterMergeMngr->UpdateEmitterStat( pABTExtData, E_ES_DELETE );

                    if( m_pTheEmitterMergeMngr->IsTracking( pABTExtData ) == true ) {
                        strTrkAnalInfo.Set( pABTExtData->uiGlobalCh, pABTExtData->enPCIDriver, 0, enTrackCollectBank, m_pMsg->x.stDelete.uiAETID, m_pMsg->x.stDelete.uiABTID, enNO_ROBUST_ANALYSIS );
                        RequestTrackClose( enNORMAL_TRACK_CLOSE_DELETE, & strTrkAnalInfo, pABTExtData );
                    }

                    pABTNextThreat = m_pTheEmitterMergeMngr->GetNextThreat( pABTThreat );

                    // 삭제 처리를 한다.
                    bRet = m_pTheEmitterMergeMngr->RemoveThreat( m_pMsg->x.stDelete.uiAETID, pABTThreat->GetABTID() );

                    if( bRet == false ) {
                        Log( enError, "삭제할 위협[%04d/%04d]이 존재하지 않아 운용자 삭제 요청을 처리하지 못 했습니다 !", m_pMsg->x.stDelete.uiAETID, pABTThreat->GetABTID() );
                        SendStringLan( enREQ_SYSERROR, ( const char * ) "삭제할 위협[%04d/%04d]이 존재하지 않아 운용자 삭제 요청을 처리하지 못 했습니다 !", m_pMsg->x.stDelete.uiAETID, m_pMsg->x.stDelete.uiABTID );
                    }
                    else {
                        // m_pTheEmitterMergeMngr->PushAETID( m_pMsg->x.stDelete.uiAETID );
                    }

                    pABTThreat = pABTNextThreat;
                }
            }

            bResult = ( bRet == true ? TRUE : FALSE );

#if 1
            SEL_RESULT_DELETE_USERSCAN stResultDeleteUserScan;

            stResultDeleteUserScan.uiAET = m_pMsg->x.stDelete.uiAETID;
            stResultDeleteUserScan.uiABT = m_pMsg->x.stDelete.uiABTID;
            stResultDeleteUserScan.uiStatus = ( unsigned int ) bResult;
            SendLan( enRES_USER_DELETE_THREAT_DATA, & stResultDeleteUserScan, sizeof( SEL_RESULT_DELETE_USERSCAN ) );
#else
            //g_pTheCCUSocket->SendLan( enRES_USER_DELETE_THREAT_DATA, & bResult, sizeof( BOOL ) );
            SendLan( enRES_USER_DELETE_THREAT_DATA, & bResult, sizeof( BOOL ) );
            Log( enDebug, "위협[%04d/%04d]은 운용자 삭제 응답 메시지[%d]를 전송합니다.", m_pMsg->x.stDelete.uiAETID, m_pMsg->x.stDelete.uiABTID, enRES_USER_DELETE_THREAT_DATA );

#endif
            if( bResult == TRUE ) {
                SELDELETE stELINDEX;

                stELINDEX.uiAETID = m_pMsg->x.stDelete.uiAETID;
                stELINDEX.uiABTID = m_pMsg->x.stDelete.uiABTID;
                //g_pTheCCUSocket->SendLan( enDEL_THREAT_DATA, & stELINDEX, sizeof( stELINDEX ) );
                SendLan( enDEL_THREAT_DATA, & stELINDEX, sizeof( stELINDEX ) );
                Log( enDebug, "위협[%04d/%04d]은 운용자 삭제 메시지[%d]를 전송합니다.", m_pMsg->x.stDelete.uiAETID, m_pMsg->x.stDelete.uiABTID, enDEL_THREAT_DATA );
            }

        }
        else {
            Log( enError, "삭제할 위협[%04d/%04d]이 존재하지 않아 운용자 삭제 요청을 처리하지 못 했습니다 !", m_pMsg->x.stDelete.uiAETID, m_pMsg->x.stDelete.uiABTID );
            SendStringLan( enREQ_SYSERROR, ( const char * ) "삭제할 위협[%04d/%04d]이 존재하지 않아 운용자 삭제 요청을 처리하지 못 했습니다 !" , m_pMsg->x.stDelete.uiAETID, m_pMsg->x.stDelete.uiABTID );
        }
    }
    else {
        // Log( enError, "대기 모드이어서 위협 삭제 명령을 삭제합니다 !" );
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
void CEmitterMerge::RequestTrackCollect( SRxLOBData *pLOBData, ENUM_COLLECTBANK enCollectBank, bool bCreateTrack, SRxABTData *pABTData, SELABTDATA_EXT *pABTExtData )
{
#if CO_TRACK_CHANNEL > 0
    bool bReqTrack;

    STR_TRKANAL_INFO strAnalInfo;

    // 빔 정보 얻기
    if( pABTData == NULL ) {
        pABTData = GetABTData( enCollectBank, pLOBData );
    }

    // 빔 추가 정보 얻기
    if( pABTExtData == NULL ) {
        pABTExtData = GetABTExtData( enCollectBank, pLOBData );
    }

    if( pABTData != NULL && pABTExtData != NULL ) {
        bReqTrack = m_pTheEmitterMergeMngr->ReqTrack( pABTExtData );

        // 빔이 생성 여부에 따라 추적으로 요청 여부를 결정한다.
        if( bReqTrack == true ) {
            memset( & strAnalInfo, 0, sizeof( STR_TRKANAL_INFO ) );

            strAnalInfo.enRobustAnal = m_pTheEmitterMergeMngr->CheckRobustAnal( pABTData, m_pRecvTrackAnalInfo->enRobustAnal );

            // 추적 신규 채널 설정하여 추적 분석 하게 합니다.
            if( bCreateTrack == true ) {
                strAnalInfo.uiAETID = pLOBData->uiAETID;
                strAnalInfo.uiABTID = pLOBData->uiABTID;

                strAnalInfo.enPCIDriver = m_pRecvDetectAnalInfo->enPCIDriver;
                strAnalInfo.enCollectBank = m_pRecvDetectAnalInfo->enCollectBank;

                if( m_pTheEmitterMergeMngr->Merge() == false ) {
                    // 탐지에서 온 추적은 채널을 새로이 할당해서 관리 합니다.
                    if( m_theQueueTrackChannel[(unsigned int) strAnalInfo.enPCIDriver].Pop( & strAnalInfo.uiGlobalCh ) == true ) {
                        Log( enDebug, "신규 위협[%04d/%04d]에 대해서, [%s]PCI 추적 채널[%2d]을 설정 합니다.", pLOBData->uiAETID, pLOBData->uiABTID, g_strPCIDrverDirection[(unsigned int)strAnalInfo.enPCIDriver].c_str(), strAnalInfo.uiGlobalCh-CO_DETECT_CHANNEL );

                        strAnalInfo.uiTotalLOB = _spOne;

                        // 빔 정보에 추적 관련 정보와 윈도우 셀 정보를 저장힙니다.
                        m_pTheEmitterMergeMngr->UpdateTrackWindowCellInfo( pABTData, pABTExtData, & strAnalInfo, false );

                        g_pTheSignalCollect->QMsgSnd( enTHREAD_REQ_SET_TRACKWINDOWCELL, pABTData, sizeof( struct SRxABTData ), &strAnalInfo, sizeof( STR_TRKANAL_INFO ), GetThreadName() );
                    }
                    else {
                        m_pTheEmitterMergeMngr->ReqTrack( pABTExtData, false );
                        Log( enDebug, "해당 위협 신호[%d/%d]는 추적 채널을 할당할 자원이 없어서, 탐지 분석으로 추적 합니다 !", pLOBData->uiAETID, pLOBData->uiABTID );
                    }
                }
                else {
                    //Log( enNormal, "탐지 LOB[%d]는 기존 위협[%04d/%04d]에 병합됐습니다.", pLOBData->uiLOBID, pLOBData->uiAETID, pLOBData->uiABTID );
                }
            }
            // 추적 성공/실패한 위협에 대해서 추적 채널을 재설정합니다.
            else {
                strAnalInfo.uiAETID = pABTData->uiAETID;
                strAnalInfo.uiABTID = pABTData->uiABTID;

                strAnalInfo.enPCIDriver = m_pRecvTrackAnalInfo->enPCIDriver;
                strAnalInfo.enCollectBank = m_pRecvTrackAnalInfo->enCollectBank;

                strAnalInfo.uiGlobalCh = pABTExtData->uiGlobalCh;

                Log( enDebug, "위협[%04d/%04d]에 추적 채널[%2d/%2d]을 재설정 합니다.", strAnalInfo.uiAETID, strAnalInfo.uiABTID, strAnalInfo.uiGlobalCh - CO_DETECT_CHANNEL, strAnalInfo.uiGlobalCh );
                m_pTheEmitterMergeMngr->UpdateTrackWindowCellInfo( pABTData, pABTExtData, & strAnalInfo, true );

                g_pTheSignalCollect->QMsgSnd( enTHREAD_REQ_SET_TRACKWINDOWCELL, pABTData, sizeof( struct SRxABTData ), &strAnalInfo, sizeof( STR_TRKANAL_INFO ), GetThreadName() );
            }

        }
        else {
            if( enCollectBank == enTrackCollectBank ) {
                //TRACE( "Ch[%d], Tracking[%d]", pABTExtData->uiGlobalCh, pABTExtData->enTracking );
                if( pABTExtData->uiGlobalCh != 0 ) {
                    Log( enDebug, "추적 위협[%04d/%04d]에 대해서 추적 할당 하지 않고 탐지로 추적합니다. 추적 할당 안 합니다.", m_pRecvTrackAnalInfo->uiAETID, m_pRecvTrackAnalInfo->uiABTID );
                    pABTExtData = m_pTheEmitterMergeMngr->FindABTExtData( m_pRecvTrackAnalInfo->uiAETID, m_pRecvTrackAnalInfo->uiABTID );
                    RequestTrackClose( enNORMAL_TRACK_CLOSE, NULL, pABTExtData );
                }
            }
            else {
                Log( enDebug, "탐지 위협[%04d/%04d]에 대해서 추적 할당 하지 않고 탐지로 추적합니다. 추적 할당 안 합니다.", pLOBData->uiAETID, pLOBData->uiABTID );
            }

        }
    }
    else {
        Log( enError, "%s 위협[%04d/%04d]에 대해서 [RequestTrackCollect] 함수를 수행할 수 없습니다 !", g_szCollectBank[(int)enCollectBank], pLOBData->uiAETID, pLOBData->uiABTID );

        pABTData = GetABTData( enCollectBank, pLOBData );
        pABTExtData = GetABTExtData( enCollectBank, pLOBData );
    }

#endif

}

/**
 * @brief     RequestTrackClose
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-11-27 16:47:49
 * @warning
 */
void CEmitterMerge::RequestTrackClose( ENUM_TRACK_CLOSE enTRACK_CLOSE, STR_TRKANAL_INFO *pstTRKAnalInfo, SELABTDATA_EXT *pABTExtData )
{
#if CO_TRACK_CHANNEL > 0
    // 입력값이 NULL 이면 메시지 값으로 처리합니다.
    if( pstTRKAnalInfo == NULL ) {
        pstTRKAnalInfo = m_pRecvTrackAnalInfo;
    }

    if( enTRACK_CLOSE == enABNORMAL_TRACK_CLOSE ) {
        Log( enNormal, "추적 위협[%04d/%04d]이 이미 삭제 처리 되었습니다 !", pstTRKAnalInfo->uiAETID, pstTRKAnalInfo->uiABTID );
    }
    else if( enTRACK_CLOSE == enNORMAL_TRACK_CLOSE_DELETE ) {
        Log( enNormal, "추적 위협[%04d/%04d] 채널[%2d/%2d]을 닫고 삭제 처리 하려 합니다.", pstTRKAnalInfo->uiAETID, pstTRKAnalInfo->uiABTID, pstTRKAnalInfo->uiGlobalCh - ( CO_DETECT_CHANNEL ), pstTRKAnalInfo->uiGlobalCh );
    }
    else {
        Log( enNormal, "추적 위협[%04d/%04d] 채널[%2d/%2d]을 닫으려고 합니다.", pstTRKAnalInfo->uiAETID, pstTRKAnalInfo->uiABTID, pstTRKAnalInfo->uiGlobalCh - CO_DETECT_CHANNEL, pstTRKAnalInfo->uiGlobalCh );
    }

    // 추적 채널을 반납합니다.
    if( enTRACK_CLOSE != enABNORMAL_TRACK_CLOSE ) {
        if( true == m_theQueueTrackChannel[( unsigned int ) pstTRKAnalInfo->enPCIDriver].Push( pstTRKAnalInfo->uiGlobalCh ) ) {
            m_theQueueTrackChannel[( unsigned int ) pstTRKAnalInfo->enPCIDriver].Print();
        }
        else {
            //TODO: 추적 채널 정보를 전시하여 추적 채널 오류를 확인해야 합니디.
            //date 	2023-10-26 19:27:15
            m_theQueueTrackChannel[( unsigned int ) pstTRKAnalInfo->enPCIDriver].Print();

            Log( enError, "추적 채널[%2d/%2d]이 잘못 관리 되고 있습니다. 담당자에게 문의하세요 !", pstTRKAnalInfo->uiGlobalCh-CO_DETECT_CHANNEL, pstTRKAnalInfo->uiGlobalCh );
        }

        // SELABTDATA_EXT *pABTExtData = m_pTheEmitterMergeMngr->GetABTExtData();
        m_pTheEmitterMergeMngr->CloseWindowCellInfo( pstTRKAnalInfo->uiGlobalCh, pABTExtData );

        g_pTheSignalCollect->QMsgSnd( enTHREAD_REQ_CLOSE_TRACKWINDOWCELL, pstTRKAnalInfo, sizeof( STR_TRKANAL_INFO ), GetThreadName() );
    }
#endif

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
void CEmitterMerge::RequestTrackLostDelete()
{
    CELThreat *pABTThreat = m_pTheEmitterMergeMngr->FindABTThreat( m_pRecvTrackAnalInfo->uiAETID, m_pRecvTrackAnalInfo->uiABTID );

    if( pABTThreat != NULL ) {
        SELABTDATA_EXT *pABTExtData;

        pABTExtData = m_pTheEmitterMergeMngr->GetABTExtData( pABTThreat->m_uiIndex );

        if( m_pTheEmitterMergeMngr->IsDeleteThreat( pABTThreat ) == E_ES_DELETE ) {
            m_pTheEmitterMergeMngr->UpdateEmitterStat( pABTExtData, E_ES_DELETE );

            RequestTrackClose( enNORMAL_TRACK_CLOSE_DELETE, NULL, pABTExtData );

            m_pTheEmitterMergeMngr->RemoveThreat( m_pRecvTrackAnalInfo->uiAETID, m_pRecvTrackAnalInfo->uiABTID );

            SendLostOrDelete( enDEL_BEAM_DATA, m_pRecvTrackAnalInfo, pABTExtData );
        }
        else {
            SRxABTData *pABTData = m_pTheEmitterMergeMngr->GetABTData( pABTThreat->m_uiIndex );

            m_pTheEmitterMergeMngr->UpdateEmitterStat( pABTExtData, E_ES_LOST );

            RequestTrackCollect( m_pLOBData, enTrackCollectBank, false, pABTData, pABTExtData );

            // 추적 성공이 실패했기 때문에 추적 실패 메서지를 전송 합니다.
            SendLostOrDelete( enLST_BEAM_DATA, m_pRecvTrackAnalInfo, pABTExtData );

            if( m_pRecvTrackAnalInfo->uiTotalLOB > 0 ) {
                Log( enDebug, "위협[%04d/%04d]은 추적 분석에서 LOB[%d 개]로 분석 되었지만, 위협으로 분석되지 않아 추적 실패 처리 됐습니다.", m_pRecvTrackAnalInfo->uiAETID, m_pRecvTrackAnalInfo->uiABTID, m_pRecvTrackAnalInfo->uiTotalLOB );
            }
            else {
                //TODO: 추적 채널을 더 넓히거나 2차 식별을 참조해서 다시 업데이트 해야 되나 ?
                //date 	2023-10-26 19:31:42

                Log( enDebug, "위협[%04d/%04d]은 추적 수집한 펄스가 없거나 LOB로 분석이 안 되어 추적 실패 처리 됐습니다.", m_pRecvTrackAnalInfo->uiAETID, m_pRecvTrackAnalInfo->uiABTID );
            }
        }

    }
    else {
        RequestTrackClose( enABNORMAL_TRACK_CLOSE );
    }

}

#if CO_SCAN_CHANNEL > 0
/**
 * @brief     LOB 데이터 기반으로 스캔 수집을 설정합니다.
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-03-10, 20:34
 * @warning
 */
void CEmitterMerge::RequestScanCollect( unsigned int uiAETID, unsigned int uiABTID )
{
    unsigned int uiScanStep, uiReqScanPeriod;
    ENUM_SCAN_PROCESS enScanProcess;

    enScanProcess = m_pTheEmitterMergeMngr->EnScanProcess();

    uiScanStep = m_pTheEmitterMergeMngr->GetABTScanStep();
    if( ( enScanProcess == enSCAN_Requesting || enScanProcess == enSCAN_Retrying ) && uiScanStep != UINT32_MAX ) {
        m_pTheEmitterMergeMngr->EnScanProcess( enSCAN_Collecting );

        uiReqScanPeriod = m_pTheEmitterMergeMngr->GetReqScanPeriod( uiScanStep );

        // 신규 스캔 수집 채널시
        if( uiAETID != 0 ) {
            m_pstrScanAnalInfo->Set( ( unsigned int ) -1, enUnknownCollectBank, uiAETID, uiABTID, m_pTheEmitterMergeMngr->GetABTIndex(), uiReqScanPeriod, uiScanStep );
        }
        // 스캔 분석 실패로 재시도 일 때
        else {
            m_pstrScanAnalInfo->Set( ( unsigned int ) -1, enUnknownCollectBank, m_pRecvScanAnalInfo->uiAETID, m_pRecvScanAnalInfo->uiABTID, m_pRecvScanAnalInfo->uiABTIndex, uiReqScanPeriod, uiScanStep, & m_pRecvScanAnalInfo->stScanResult );
        }

        // 위협 정보는 해당 쓰레드에서 실행시 해당 방사체/빔 번호를 갖고 와서 스캔 수집을 수행합니다.
        g_pTheSignalCollect->QMsgSnd( enTHREAD_REQ_SCAN_START, GetUniMessageData(), sizeof( union UNI_MSG_DATA ), GetThreadName() );
    }
    else if( enScanProcess == enSCAN_CANTProcessing ) {
        Log( enDebug, "위협[%04d/%04d]에 대해서 스캔 분석 불가 합니다.", m_pRecvScanAnalInfo->uiAETID, m_pRecvScanAnalInfo->uiABTID );
    }
    else {
        if( m_pTheEmitterMergeMngr->IsAliveABT() == true ) {
        }
        else {
            Log( enNormal, "위협[%04d/%04d]이 삭제되어 스캔 수집을 종료 합니다 !", m_pRecvScanAnalInfo->uiAETID, m_pRecvScanAnalInfo->uiABTID );
        }

    }

}
#endif

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
void CEmitterMerge::SendNewUpd( unsigned int uiOpCode )
{

#if defined(_POCKETSONATA_) || defined(_712_)
    SAETData stAET;
    SRxLOBData *pSRxLOBData;
    SRxABTData *pSRxABTData;
    SRxAETData *pSRxAETData;
    SELABTDATA_EXT *pABTExtData;

    pSRxLOBData = m_pTheEmitterMergeMngr->GetLOBData();
    pSRxABTData = m_pTheEmitterMergeMngr->GetABTData();
    pSRxAETData = m_pTheEmitterMergeMngr->GetAETData();
    pABTExtData = m_pTheEmitterMergeMngr->GetABTExtData();

	// 랜 메시지 전달한다.
   if( pSRxLOBData != NULL && pSRxABTData != NULL && pSRxAETData != NULL ) {

#ifdef _MSC_VER
        memset( & stAET, 0, sizeof( stAET ) );

#endif

        memcpy( & stAET.stLOBData, pSRxLOBData, sizeof( struct SRxLOBData ) );

#ifdef _MSC_VER
        memcpy_s( & stAET.stABTData, sizeof( struct SRxABTData ), pSRxABTData, sizeof( struct SRxABTData ) );
#else
        memcpy( & stAET.stABTData, pSRxABTData, sizeof( struct SRxABTData ) );
#endif

#ifdef _MSC_VER
        char szAnsi[100];

        memcpy_s( & stAET.stAETData, sizeof( struct SRxAETData ), pSRxAETData, sizeof( struct SRxAETData ) );
        ANSIToUTF8( szAnsi, sizeof( szAnsi ), stAET.stAETData.szRadarName );
        strcpy( stAET.stAETData.szRadarName, szAnsi );

#else
        memcpy( & stAET.stAETData, pSRxAETData, sizeof( struct SRxAETData ) );
#endif

        switch( uiOpCode ) {
            ///////////////////////////////////////////////////////////////////////////////////
            // 신규 메시지 출력
            case enNEWDET_THREAT_DATA:
                Log( enDebug, "위협[%04d/%04d/%d]는 탐지/신규 위협 메시지[%d]를 전송합니다.", stAET.stLOBData.uiAETID, stAET.stLOBData.uiABTID, stAET.stLOBData.uiLOBID, uiOpCode );
                ElseLog( enDebug, "DN[%04d/%04d]\n", stAET.stLOBData.uiAETID, stAET.stLOBData.uiABTID )
                break;

            case enNEWTRK_THREAT_DATA:
                Log( enDebug, "위협[%04d/%04d/%d]는 추적/신규 메시지[%d]를 전송합니다.", stAET.stLOBData.uiAETID, stAET.stLOBData.uiABTID, stAET.stLOBData.uiLOBID, uiOpCode );
                ElseLog( enDebug, "TN[%04d/%04d]\n", stAET.stLOBData.uiAETID, stAET.stLOBData.uiABTID )
                break;

            case enUPDDET_THREAT_DATA:
                Log( enDebug, "위협[%04d/%04d/%d]는 탐지/병합 메시지[%d]를 전송합니다.", stAET.stLOBData.uiAETID, stAET.stLOBData.uiABTID, stAET.stLOBData.uiLOBID, uiOpCode );
                ElseLog( enDebug, "DM[%04d/%04d]\n", stAET.stLOBData.uiAETID, stAET.stLOBData.uiABTID )
                break;

            ///////////////////////////////////////////////////////////////////////////////////
            // 추적 메시지 출력
            case enUPDTRK_THREAT_DATA:
                Log( enDebug, "위협[%04d/%04d/%d]는 추적/성공 메시지[%d]를 전송합니다.", stAET.stLOBData.uiAETID, stAET.stLOBData.uiABTID, stAET.stLOBData.uiLOBID, uiOpCode );
                ElseLog( enDebug, "TU[%04d/%04d]\n", stAET.stLOBData.uiAETID, stAET.stLOBData.uiABTID )
                break;

            case enUPDTRKNEW_THREAT_DATA:
                Log( enDebug, "위협[%04d/%04d/%d]는 추적/신규 병합처리 메시지[%d]를 전송합니다.", stAET.stLOBData.uiAETID, stAET.stLOBData.uiABTID, stAET.stLOBData.uiLOBID, uiOpCode );
                ElseLog( enDebug, "TN[%04d/%04d]\n", stAET.stLOBData.uiAETID, stAET.stLOBData.uiABTID )
                break;

            ///////////////////////////////////////////////////////////////////////////////////
            // 스캔 메시지 출력
            case enUPD_SCAN_THREAT_DATA:
                Log( enDebug, "위협[%04d/%04d/%d]는 스캔/결과 메시지[%d]를 전송합니다.", stAET.stLOBData.uiAETID, stAET.stLOBData.uiABTID, stAET.stLOBData.uiLOBID, uiOpCode );
                ElseLog( enDebug, "SC[%04d/%04d]\n", stAET.stLOBData.uiAETID, stAET.stLOBData.uiABTID )
                break;

            // 탐지에서 빔 병합 메시지
            case enMRGDET_THREAT_DATA:
                Log( enDebug, "위협[%04d/%04d/%d]는 빔 병합 메시지[%d]를 전송합니다.", stAET.stLOBData.uiAETID, stAET.stLOBData.uiABTID, stAET.stLOBData.uiLOBID, uiOpCode );
                ElseLog( enDebug, "MD[%04d/%04d]\n", stAET.stLOBData.uiAETID, stAET.stLOBData.uiABTID )
                break;

            // 추적에서 빔 병합 메시지
            case enMRGTRK_THREAT_DATA:
                Log( enDebug, "위협[%04d/%04d/%d]는 빔 병합 메시지[%d]를 전송합니다.", stAET.stLOBData.uiAETID, stAET.stLOBData.uiABTID, stAET.stLOBData.uiLOBID, uiOpCode );
                ElseLog( enDebug, "MD[%04d/%04d]\n", stAET.stLOBData.uiAETID, stAET.stLOBData.uiABTID )
                break;

            ///////////////////////////////////////////////////////////////////////////////////
            // 스캔 메시지 출력
            default:
                if( m_pTheEmitterMergeMngr->Merge() == true ) {
                    Log( enDebug, "위협[%04d/%04d/%d]는 병합 위협 메시지[%d]를 전송합니다.", stAET.stLOBData.uiAETID, stAET.stLOBData.uiABTID, stAET.stLOBData.uiLOBID, uiOpCode );
                }
                else {
                    Log( enDebug, "위협[%04d/%04d/%d]는 변경 위협 메시지[%d]를 전송합니다.", stAET.stLOBData.uiAETID, stAET.stLOBData.uiABTID, stAET.stLOBData.uiLOBID, uiOpCode );
                }
                break;

        }

        // 랜 메시지를 전달합니다.
        SendAETData( enNUP_THREAT_DATA, & stAET, pABTExtData );

    }
    else {
        Log( enNormal, "위협이 이미 삭제 처리가 되어 메시지 전송을 수행할 수 없습니다." );
    }

#else

#endif

}

/**
 * @brief     SwapAETData
 * @param     SAETData * pstAET
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-06-25 13:52:56
 * @warning
 */
void CEmitterMerge::SwapAETData( SAETData *pstAET )
{
    // LOB 데이터 변환
    CCommonUtils::AllSwapData32( & pstAET->stLOBData.uiPDWID, sizeof( UINT ) * 6 );
    CCommonUtils::AllSwapData16( & pstAET->stLOBData.tiContactTimems, sizeof( short ) );
    CCommonUtils::AllSwapData32( & pstAET->stLOBData.fDOAMean, sizeof( UINT ) * 6 );
    CCommonUtils::AllSwapData32( & pstAET->stLOBData.fFreqPatternPeriod, sizeof( UINT ) * 6 );
    CCommonUtils::AllSwapData32( & pstAET->stLOBData.fFreqSeq, sizeof( UINT ) * MAX_FREQ_PRI_STEP );
    CCommonUtils::AllSwapData32( & pstAET->stLOBData.fPRIPatternPeriod, sizeof( UINT ) * 7 );
    CCommonUtils::AllSwapData32( & pstAET->stLOBData.fPRISeq, sizeof( UINT ) * MAX_FREQ_PRI_STEP );
    CCommonUtils::AllSwapData32( & pstAET->stLOBData.fPWMean, sizeof( UINT ) * 10 );
    CCommonUtils::AllSwapData32( & pstAET->stLOBData.fMeanScanPeriod, sizeof( UINT ) * 1 );
    CCommonUtils::AllSwapData32( & pstAET->stLOBData.fMOPMaxFreq, sizeof( UINT ) * 4 );
    CCommonUtils::AllSwapData32( & pstAET->stLOBData.uiNumOfCollectedPDW, sizeof( UINT ) * 2 );
    CCommonUtils::AllSwapData32( & pstAET->stLOBData.uiRadarModeIndex, sizeof( UINT ) * 3 );

    // 빔 데이터 변환
    CCommonUtils::AllSwapData32( & pstAET->stABTData.uiABTID, sizeof( UINT ) * 2 );
    CCommonUtils::AllSwapData32( & pstAET->stABTData.uiCoLOB, sizeof( UINT ) * 5 );
    CCommonUtils::AllSwapData32( & pstAET->stABTData.fDOAMean, sizeof( UINT ) * 4 );
    CCommonUtils::AllSwapData32( & pstAET->stABTData.fFreqPatternPeriodMean, sizeof( UINT ) * 7 );
    CCommonUtils::AllSwapData32( & pstAET->stABTData.fFreqSeq, sizeof( UINT ) * MAX_FREQ_PRI_STEP );
    CCommonUtils::AllSwapData32( & pstAET->stABTData.fPRIPatternPeriodMean, sizeof( UINT ) * 8 );
    CCommonUtils::AllSwapData32( & pstAET->stABTData.fPRISeq, sizeof( UINT ) * MAX_FREQ_PRI_STEP );
    CCommonUtils::AllSwapData32( & pstAET->stABTData.fPWMean, sizeof( UINT ) * 8 );
    CCommonUtils::AllSwapData32( & pstAET->stABTData.fMeanScanPeriod, sizeof( UINT ) * 3 );
    CCommonUtils::AllSwapData32( & pstAET->stABTData.fMaxIntraMod, sizeof( UINT ) * 2 );
    CCommonUtils::AllSwapData32( & pstAET->stABTData.fLatitude, sizeof( UINT ) * 8 );
    CCommonUtils::AllSwapData32( & pstAET->stABTData.uiTotaOfPDW, sizeof( UINT ) * 4 );

    // 방사체 데이터 변환
    CCommonUtils::AllSwapData32( & pstAET->stAETData.uiAETID, sizeof( UINT ) * 3 );
    CCommonUtils::AllSwapData32( & pstAET->stAETData.uiPinNum, sizeof( UINT ) * 1 );
    CCommonUtils::AllSwapData32( & pstAET->stAETData.uiRadarModePriority, sizeof( UINT ) * 5 );
    CCommonUtils::AllSwapData32( & pstAET->stAETData.fDOAMean, sizeof( UINT ) * 4 );
    CCommonUtils::AllSwapData32( & pstAET->stAETData.fFreqMean, sizeof( UINT ) * 19 );
    CCommonUtils::AllSwapData32( & pstAET->stAETData.fLatitude, sizeof( UINT ) * 8 );

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
void CEmitterMerge::SendAETData( unsigned int uiOpcode, SAETData *pData, SELABTDATA_EXT *pABTExtData )
{
    time_t now;

    now = time(NULL);
    if( pABTExtData != NULL && ( ( pABTExtData->enBeamEmitterStat == E_ES_NEW || pABTExtData->enBeamEmitterStat == E_ES_REACTIVATED ) || difftime(now, pABTExtData->tiSendLan) > 1.0 || ( pABTExtData->uiOpcode != uiOpcode ) ) ) {

#ifdef _MSC_VER
        SwapAETData( pData );
#endif

        //g_pTheCCUSocket->SendLan( enNUP_THREAT_DATA, pData, uiDataSize, false );
        SendLan( uiOpcode, pData, sizeof(SAETData), false );

        pABTExtData->uiOpcode = uiOpcode;
        pABTExtData->tiSendLan = time( NULL );

    }
    else {
        //Log( enNormal, "위협 결과[%d/%d/%d] 랜 송신을 무시 합니다." , m_pLOBData->uiAETID, m_pLOBData->uiABTID, m_pLOBData->uiLOBID );
    }

}

/**
 * @brief     SendLanByTime
 * @param     unsigned int uiOpcode
 * @param     SELLOST * pData
 * @param     unsigned int uiDataSize
 * @param     SELABTDATA_EXT * pABTExtData
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-10-26 19:22:01
 * @warning
 */
// void CEmitterMerge::SendLanByTime( unsigned int uiOpcode, SELLOST *pLost, SELABTDATA_EXT *pABTExtData )
// {
//     time_t now;
//
//     now = time( NULL );
//     if( pABTExtData != NULL && ( ( pABTExtData->enBeamEmitterStat == E_ES_NEW || pABTExtData->enBeamEmitterStat == E_ES_REACTIVATED ) || difftime( now, pABTExtData->tiSendLan ) > 1.0 || ( pABTExtData->uiOpcode != uiOpcode ) ) ) {
//         size_t szSize;
//
//         szSize = sizeof( SELLOST );
//         Log( enNormal, "추적 실패 처리[%d/%d] !", pLost->uiAETID, pLost->uiABTID );
//
// #ifdef _MSC_VER
//         CCommonUtils::AllSwapData32( pLost, szSize );
// #endif
//
//         SendLan( enLST_THREAT_DATA, pLost, szSize, false );
//
//         pABTExtData->uiOpcode = uiOpcode;
//         pABTExtData->tiSendLan = time( NULL );
//
//     }
//     else {
//         //Log( enNormal, "위협 결과[%d/%d/%d] 랜 송신을 무시 합니다." , m_pLOBData->uiAETID, m_pLOBData->uiABTID, m_pLOBData->uiLOBID );
//     }
//
// }

/**
 * @brief     SendLanByTime
 * @param     unsigned int uiOpcode
 * @param     STR_TRKANAL_INFO * pRecvTrackAnalInfo
 * @param     unsigned int uiDataSize
 * @param     SELABTDATA_EXT * pABTExtData
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-11-27 15:12:53
 * @warning
 */
void CEmitterMerge::SendLostOrDelete( unsigned int uiOpcode, STR_TRKANAL_INFO *pRecvTrackAnalInfo, SELABTDATA_EXT *pABTExtData )
{

    if( pABTExtData != NULL && ( pABTExtData->enBeamEmitterStat == E_ES_DELETE || ( pABTExtData->uiOpcode != uiOpcode ) ) ) {
        SELLOST stLost;

        stLost.uiAETID = pRecvTrackAnalInfo->uiAETID;
        stLost.uiABTID = pRecvTrackAnalInfo->uiABTID;

        if( uiOpcode == (unsigned int) enDEL_BEAM_DATA ) {
            Log( enDebug, "위협[%04d/%04d]은 위협 삭제 메시지[%d]를 전송합니다.", stLost.uiAETID, stLost.uiABTID, uiOpcode );
        }
        else {
            Log( enDebug, "위협[%04d/%04d]은 위협 소실 메시지[%d]를 전송합니다.", stLost.uiAETID, stLost.uiABTID, uiOpcode );
        }

#ifdef _MSC_VER
        CCommonUtils::AllSwapData32( & stLost, sizeof( SELLOST ) );
#endif

        SendLan( uiOpcode, & stLost, sizeof( SELLOST), false );

        pABTExtData->uiOpcode = uiOpcode;
        pABTExtData->tiSendLan = time( NULL );

    }
    else {
        //Log( enNormal, "위협 결과[%d/%d/%d] 랜 송신을 무시 합니다." , m_pLOBData->uiAETID, m_pLOBData->uiABTID, m_pLOBData->uiLOBID );
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
void CEmitterMerge::SendDelete( unsigned int uiAETID, unsigned int uiABTID )
{
    SELDELETE stDelete;

    stDelete.uiAETID = uiAETID;
    stDelete.uiABTID = uiABTID;

    Log( enDebug, "위협[%04d/%04d]은 위협 삭제 메시지[%d]를 전송합니다.", stDelete.uiAETID, stDelete.uiABTID, enDEL_BEAM_DATA );

#ifdef _MSC_VER
    CCommonUtils::AllSwapData32( & stDelete, sizeof( stDelete ) );
#endif

    SendLan( enDEL_BEAM_DATA, & stDelete, sizeof( stDelete ), false );

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

    Log( enNormal, "CED/EOB 라이브러리 변경 요청을 수신했습니다." );

    sprintf( szSrcFilename, "%s/%s", SHARED_DATA_DIRECTORY, CEDEOB_SQLITE_FILENAME );
#ifdef __VXWORKS__
    sprintf( szDstFilename, "%s%s/%s/%s", RAMDRV, RAMDRV_NO, SQLITE_DIRECTORY, CEDEOB_SQLITE_FILENAME );

#else
    sprintf( szDstFilename, "%s/%s", SHARED_DATA_DIRECTORY, CEDEOB_TEST_SQLITE_FILENAME );

#endif

    Log( enNormal, "원본[%s] 위협 라이브러리를 경로[%s]에 백업 합니다.", szSrcFilename, szDstFilename );
    iRet = CCommonUtils::CopySrcToDstFile( szSrcFilename, szDstFilename, 1, 0077 );

    if( iRet <= 0 ) {
        Log( enError, "원본[%s] 위협 라이브러리를 목적지[%s]로 복사하지 못했습니다." , szSrcFilename, szDstFilename );
        SendStringLan( enREQ_SYSERROR, ( const char * ) "위협 라이브러리를 복사하지 못했습니다 !" );
    }
    else {
#ifdef __VXWORKS__
        sprintf( szDstFilename, "%s/%s/%s", ATADRV, SQLITE_DIRECTORY, CEDEOB_SQLITE_FILENAME );
        Log( enNormal, "원본[%s] 위협 라이브러리를 경로[%s]에 백업 합니다.", szSrcFilename, szDstFilename );

        iRet = CCommonUtils::CopySrcToDstFile( szSrcFilename, szDstFilename, 1, 0077 );

#endif

        m_pTheEmitterMergeMngr->UpdateCEDEOBLibrary();
        m_pTheEmitterMergeMngr->LoadCEDEOBLibrary();

        iRet = TRUE;
        //g_pTheCCUSocket->SendLan( enRES_RELOAD_LIBRARY, & iRet, sizeof(int) );
        SendLan( enRES_RELOAD_LIBRARY, & iRet, sizeof( int ) );
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
        Log( enDebug, "위협[%04d/%04d] 에 대해서 스캔 결과[%d/%.4f ms] 변경합니다.", m_pLOBData->uiAETID, m_pLOBData->uiABTID, m_pLOBData->vScanType, m_pLOBData->fMeanScanPeriod );

        // 1. LOB 헤더 데이터를 초기 설정합니다.
        strLOBHeader.uiNumOfLOB = 1;

        // 2. 스캔 결과를 저장합니다.
        m_pTheEmitterMergeMngr->ManageThreat( &strLOBHeader, m_pLOBData, &m_sLOBOtherInfo, true );

        // 3. 스캔 상태를 업데이트 합니다.
        m_pTheEmitterMergeMngr->ManageScan( m_pRecvScanAnalInfo->enCollectBank, & m_pRecvScanAnalInfo->stScanResult, m_pLOBData );

        // 4. 빔 정보를 제어조종장치로 전송한다.
//         if( m_pTheEmitterMergeMngr->IsUserReqScan() == true ) {
//             SendUserReqScan();
//
//         }
//         else {
//             SendNewUpd();
//         }

        // 5.  스캔 결과를 LOB/빔/방사체 데이터로 전달합니다.
        SendNewUpd( enUPD_SCAN_THREAT_DATA );

        // 5.1 스캔 결과를 확인하기 위해서 전달홥니다.
        if( m_pTheEmitterMergeMngr->IsUserReqScan() == true ) {
            SendUserReqScanResult();
        }

        // 6. 사용자 스캔 분석 플레그를 클리어 합니다.
        m_pTheEmitterMergeMngr->ResetUserReqScan();

    }
    else {
        Log( enError, "m_pLOBData 값이 NULL 입니다 !" );
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
    m_pTheEmitterMergeMngr->ManageScan( m_pRecvScanAnalInfo->enCollectBank, & m_pRecvScanAnalInfo->stScanResult, m_pLOBData );

    // 3. 스캔 상태에 따라 스캔 수집 요청을 합니다.
    RequestScanCollect( 0, 0 );

    // 4. 빔 정보를 제어조종장치로 전송한다.
    if( m_pTheEmitterMergeMngr->EnScanProcess() == enSCAN_Stopping ) {
        m_pTheEmitterMergeMngr->UpdateABTScanResult();

        if( m_pTheEmitterMergeMngr->IsUserReqScan() == true ) {
            SendUserReqScanResult();
        }
        else {


            SendSelfScanResult();
        }

        // 4.1 사용자 리셋 플레그 클리어 합니다.
        m_pTheEmitterMergeMngr->ResetUserReqScan();

    }

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

    m_pTheEmitterMergeMngr->ManageScan( m_pRecvScanAnalInfo->enCollectBank, & m_pRecvScanAnalInfo->stScanResult, m_pLOBData );

}

/**
 * @brief     UserRequestScan
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-08-20 17:48:41
 * @warning
 */
void CEmitterMerge::UserRequestScan()
{
    ENUM_AET_USER_SCAN_STAT enUserScanStat;

    BOOL bRet;

#ifdef _MSC_VER
    CCommonUtils::AllSwapData32( & m_pMsg->x.stReqScan, sizeof( struct SELREQSCAN ) );

#endif

    m_pTheEmitterMergeMngr->ABTPreSetting( m_pMsg->x.stReqScan.uiAET, m_pMsg->x.stReqScan.uiABT );

    bRet = m_pTheEmitterMergeMngr->IsAliveABT();
    if( bRet == FALSE ) {
        SendStringLan( enREQ_SYSERROR, ( const char * ) "사용자 스캔 분석 요구할 위협[%04d/%04d]이 이미 삭제되었거나 아직 생성되지 않았습니다 !", m_pMsg->x.stReqScan.uiAET, m_pMsg->x.stReqScan.uiABT );
        enUserScanStat = ENUM_AET_USER_SCAN_STAT::E_AET_USER_SCAN_CANT;
    }
    else {
        // 사용자 요구 스캔이 처음인 경우에 아래를 수행 합니다.
        if( m_pTheEmitterMergeMngr->IsUserReqScan() == false ) {
            m_pTheEmitterMergeMngr->ManageScan( enUnknownCollectBank, NULL, NULL );
            RequestScanCollect( m_pMsg->x.stReqScan.uiAET, m_pMsg->x.stReqScan.uiABT );
            enUserScanStat = ENUM_AET_USER_SCAN_STAT::E_AET_USER_SCAN_PROCESSING;
        }
        // 사용자 요구 스캔이 이미 수행하는 경우에 아래를 수행 합니다.
        else {
            int iGetEstimatedTimeScanAnal = m_pTheEmitterMergeMngr->GetEstimatedTimeScanAnal( m_pMsg->x.stReqScan.uiAET, m_pMsg->x.stReqScan.uiABT );

            //g_pTheCCUSocket->SendStringLan( enREQ_SYSERROR, ( const char * ) buffer );
            SendStringLan( enREQ_SYSERROR, ( const char * ) "사용자 스캔 분석 요구할 방사체/빔[%d/%d]이 이미 중복 요청 되어 이미 분석 중이고 최대 [%d]초 소요 예상 됩니다 !", m_pMsg->x.stReqScan.uiAET, m_pMsg->x.stReqScan.uiABT, iGetEstimatedTimeScanAnal );
            enUserScanStat = ENUM_AET_USER_SCAN_STAT::E_AET_USER_SCAN_ALREADYPROCESSING;
        }

    }

#ifdef _TRR2_
    SEL_RESULT_DELETE_USERSCAN stResultUserScan;

    stResultUserScan.uiAET = m_pMsg->x.stReqScan.uiAET;
    stResultUserScan.uiABT = m_pMsg->x.stReqScan.uiABT;
    stResultUserScan.uiStatus = ( unsigned int ) enUserScanStat;

    //g_pTheCCUSocket->SendLan( enRES_USERSCAN, & stResultUserScan, sizeof( SEL_RESULT_DELETE_USERSCAN ) );
    SendLan( enRES_USERSCAN, & stResultUserScan, sizeof( SEL_RESULT_DELETE_USERSCAN ) );
#else
    //g_pTheCCUSocket->SendLan( enRES_USERSCAN, & enUserScanStat, sizeof( ENUM_AET_USER_SCAN_STAT ) );
    SendLan( enRES_USERSCAN, & enUserScanStat, sizeof( ENUM_AET_USER_SCAN_STAT ) );

#endif

}

/**
 * @brief     SendUserReqScan
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-08-20 19:11:54
 * @warning
 */
void CEmitterMerge::SendUserReqScanResult()
{
    SELUSERSCANRESULT stUserScanResult;

    SRxABTData *pABTData;

    // 1. 스캔 결과 메시지를 랜으로 전송 합니다.
    stUserScanResult.uiAET = m_pRecvScanAnalInfo->uiAETID;
    stUserScanResult.uiABT = m_pRecvScanAnalInfo->uiABTID;
    stUserScanResult.enScanType = m_pRecvScanAnalInfo->stScanResult.enScanType;

    pABTData = m_pTheEmitterMergeMngr->GetABTData();
    stUserScanResult.enScanStat = pABTData->vScanStat;

    stUserScanResult.fScanPeriod = FDIV( m_pRecvScanAnalInfo->stScanResult.uiScanPeriod, _spOneMilli );

#ifdef _MSC_VER
    SwapScanResult( & stUserScanResult );

#endif

    //g_pTheCCUSocket->SendLan( enRES_SCAN_DATA, & stUserScanResult, sizeof( SELUSERSCANRESULT ), false );
    SendLan( enRES_SCAN_DATA, & stUserScanResult, sizeof( SELUSERSCANRESULT ), false );

}

/**
 * @brief     SendSelfScanResult
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-10-10 11:32:08
 * @warning
 */
void CEmitterMerge::SendSelfScanResult()
{
    SELUSERSCANRESULT stUserScanResult;

    SRxABTData *pABTData;

    // 1. 스캔 결과 메시지를 랜으로 전송 합니다.
    stUserScanResult.uiAET = m_pRecvScanAnalInfo->uiAETID;
    stUserScanResult.uiABT = m_pRecvScanAnalInfo->uiABTID;
    stUserScanResult.enScanType = m_pRecvScanAnalInfo->stScanResult.enScanType;

    pABTData = m_pTheEmitterMergeMngr->GetABTData();
    stUserScanResult.enScanStat = pABTData->vScanStat;

    stUserScanResult.fScanPeriod = FDIV( m_pRecvScanAnalInfo->stScanResult.uiScanPeriod, _spOneMilli );

#ifdef _MSC_VER
    SwapScanResult( & stUserScanResult );

#endif

    //g_pTheCCUSocket->SendLan( enRES_SCAN_DATA, & stUserScanResult, sizeof( SELUSERSCANRESULT ), false );
    SendLan( enRES_SCAN_DATA, & stUserScanResult, sizeof( SELUSERSCANRESULT ), false );

}

/**
 * @brief     SwapScanResult
 * @param     SELUSERSCANRESULT * pstUserScanResult
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-08-21 09:51:35
 * @warning
 */
void CEmitterMerge::SwapScanResult( SELUSERSCANRESULT *pstUserScanResult )
{

    CCommonUtils::AllSwapData32( & pstUserScanResult->uiAET, sizeof( UINT ) * 2 );
    CCommonUtils::AllSwapData32( & pstUserScanResult->fScanPeriod, sizeof( float ) );

}

#endif

#ifdef _SQLITE_
/**
 * @brief     CleanupDatabase
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-12-28 10:38:28
 * @warning
 */
void CEmitterMerge::CleanupDatabase()
{
    char buffer[200];

    sprintf( buffer, "데이터베이스를 백업하고 쿼리문으로 안정적으로 테이블을 삭제합니다..." );
    CCommonUtils::WallMakePrint( buffer, '-' );
    Log( enDebug, "%s", buffer );

    m_pTheEmitterMergeMngr->CleanupDatabase( true, true );

}

#endif

/**
 * @brief     SetSaveFile
 * @param     bool bSaveFile
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-09-26 19:19:22
 * @warning
 */
void CEmitterMerge::SetSaveFile( bool bSaveFile )
{
    m_pTheEmitterMergeMngr->SetDBEnable( bSaveFile );
}

/**
 * @brief     DisplayMinitor
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2024-01-25 22:08:22
 * @warning
 */
void CEmitterMerge::DisplayMonitor()
{

    m_pTheEmitterMergeMngr->PrintAllABTData();

}
