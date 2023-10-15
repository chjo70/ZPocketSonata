/**

    @file      csignalcollect.cpp
    @brief     신호 수집 및 관리한다.
               신규 데이터를 수집하기위한 수집 제어와 분석된 데이터를 기반으로 추적 수집 채널을 할당해서 추적 채널을 관리한다.
               또한, 스캔 채널을 할당하여 스캔 수집을 하게 한다.
    @details   ~
    @author    조철희
    @date      24.03.2023
    @copyright © Cool Guy, 2023. All right reserved.

**/

#include "stdafx.h"

#include "../Anal/OFP_Main.h"

#include "csignalcollect.h"

#include "cdetectanalysis.h"
#include "cemittermerge.h"
#include "ctrackanalysis.h"
#include "cscananalysis.h"
#include "cusercollect.h"

#include "../Utils/csingleserver.h"
#include "../Utils/ccommonutils.h"

#include "../System/csysconfig.h"

#include "../Include/globals.h"


#define _DEBUG_

extern std::string g_strPCIDrverDirection[en_ELEMENT_PCI_DRIVER];


/**
 * @brief CSignalCollect::CSignalCollect
 * @param iKeyId
 * @param pClassName
 */
#ifdef _MSSQL_
CSignalCollect::CSignalCollect( int iThreadPriority, const char *pClassName, bool bArrayLanData ) : CThread( iThreadPriority, pClassName, bArrayLanData ), CMSSQL( & m_theMyODBC )
#else
CSignalCollect::CSignalCollect( int iThreadPriority, const char *pClassName, bool bArrayLanData ) : CThread( iThreadPriority, pClassName, bArrayLanData )
#endif
{

    m_uiPDWID = 0;

    Alloc();

#ifdef _SQLITE_
    // SQLITE 파일명 생성하기
    char szSQLiteFileName[100];

    strcpy( szSQLiteFileName, CEDEOB_SQLITE_FOLDER );
    strcat( szSQLiteFileName, "/" );
    strcat( szSQLiteFileName, CEDEOB_SQLITE_FILENAME );

    m_pIdentifyAlg = new CELSignalIdentifyAlg( szSQLiteFileName );
#elif _MSSQL_
    CMSSQL::Init();
    m_pIdentifyAlg = new CELSignalIdentifyAlg( & m_theMyODBC );

#else
    m_pIdentifyAlg = new CELSignalIdentifyAlg( NULL );
#endif

    InitSignalCollect();


#if 0
    int i;
    float fValue;

    for( i=0 ; i < 100 ; ++i ) {
        fValue = CCommonUtils::Random( ( float ) 17500, ( float ) 17504 );
        TRACE( "\n %f", fValue );
    }

    for( i = 0; i < 100; ++i ) {
        fValue = CCommonUtils::NormalDistribution( ( float ) 0, ( float ) 1 );
        TRACE( "\n %f", fValue );
    }

#endif

}

/**
 * @brief     ~CSignalCollect
 * @param     void
 * @return
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-03-06 14:37:39
 * @warning
 */
CSignalCollect::~CSignalCollect(void)
{
    Free();

}

/**
 * @brief		메모리를 할당합니다.
 * @return		void
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2023/03/11 18:29:53
 * @warning
 */
void CSignalCollect::Alloc()
{
    m_pTheLeftCollectBank = new CCollectBank( CO_DETECT_CHANNEL, CO_TRACK_CHANNEL, CO_SCAN_CHANNEL, enLEFT_PCI_DRIVER );
    m_pTheRigtCollectBank = new CCollectBank( CO_DETECT_CHANNEL, CO_TRACK_CHANNEL, CO_SCAN_CHANNEL, enRIGHT_PCI_DRIVER );

#ifdef _SIM_PDW_
    m_pstrPDWWithFileHeader = ( char * ) malloc( sizeof( SIGAPDW ) * NUM_OF_SIM_PDW + sizeof( union UNION_HEADER ) );
    if( m_pstrPDWWithFileHeader != NULL ) {
        m_pUniHeader = ( UNION_HEADER * ) & m_pstrPDWWithFileHeader[0];
        m_pSIGAPDW = ( SIGAPDW * ) & m_pstrPDWWithFileHeader[sizeof( struct STR_POCKETSONATA_HEADER )];
    }
    else {
        m_pUniHeader = NULL;
        m_pSIGAPDW = NULL;
    }

#endif

    m_theQueueScanAnal.Init( CO_SCAN_CHANNEL );

}

/**
 * @brief		메모리를 해지합니다.
 * @return		void
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2023/03/11 18:34:41
 * @warning
 */
void CSignalCollect::Free()
{
    delete m_pTheLeftCollectBank;
    delete m_pTheRigtCollectBank;

    delete m_pIdentifyAlg;

#ifdef _SIM_PDW_
    free( m_pstrPDWWithFileHeader );

#endif
}

/**
 * @brief		Run
 * @param		key_t key
 * @return		void
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2023/02/16 20:10:14
 * @warning
 */
void CSignalCollect::Run(key_t key)
{
    //LOGENTRY;

    CThread::Run();

}

/**
 * @brief		_routine
 * @return		void
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2023/02/13 13:41:07
 * @warning
 */
void CSignalCollect::_routine()
{
    //LOGENTRY;

    m_pMsg = GetRecvDataMessage();

#ifdef _MSC_VER
#else
    pthread_cleanup_push( TCleanUpHandler, NULL);
#endif

    while( m_bThreadLoop ) {
#ifdef _SIM_PDW_
        if( QMsgRcv( enTIMER, OS_MILLISEC(5) ) == -1 ) {
#else
        if( QMsgRcv() == -1 ) {
#endif
            perror( "QMsgRcv" );
        }
        else {
            switch( m_pMsg->uiOpCode ) {
                ///////////////////////////////////////////////////////////////////////////////////
                // 운용 제어 관련 메시지 처리
                case enREQ_OP_START:
                    // QMsgClear();
                    InitSignalCollect( true );
                    StartCollecting();
                    break;

                case enTHREAD_DISCONNECTED:
                case enREQ_OP_SHUTDOWN:
                    //QMsgClear();
                    InitSignalCollect();
                    break;

				case enREQ_OP_RESTART:
					//QMsgClear();
                    InitSignalCollect();
                    StartCollecting();
                    break;

                ///////////////////////////////////////////////////////////////////////////////////
                // 신호(탐지/추적/스캔) 수집 완료 처리
                case enTHREAD_REQ_COMPLETECOL :
                    //InitOfMessageData();
                    CompleteCollecting();
                    break;

                // 탐지 신호 수집 시작
                case enTHREAD_REQ_SET_DETECTWINDOWCELL:
                    ReqDetectWindowCell();
                    break;

                // 스캔 신호 수집 시작
                case enTHREAD_REQ_SCAN_START:
                    StartScanChannel();
                    break;

                case enTHREAD_REQ_SET_TRACKWINDOWCELL:
                    ReqTrackWindowCell();
                    break;

#ifdef _SIM_PDW_
                case enTHREAD_TIMER :
                    MakeSIMPDWData();
                    SimPDWData();
                    CheckAllCollectBank();
                    break;

#endif

#ifdef _MSC_VER
                //case enTHREAD_DETECTANAL_START :
				    //RoutineForSimPDW();
                    //break;

//                 case enTHREAD_REQ_SHUTDOWN:
//                     LOGMSG1( enDebug, "[%s] 를 종료 처리 합니다...", GetThreadName() );
//                     break;

#else
			    case enTHREAD_DETECTANAL_START:
				InitSignalCollect();
                    break;

                case enTHREAD_REQ_TRACK_COLSTOP:
                    WhereIs;
                    break;

                case enTHREAD_REQ_SCAN_COLSTOP:
                    WhereIs;
                    break;

#endif

			default:
				Log( enError, "[%s]에서 잘못된 명령(0x%x)을 수신하였습니다 !!", GetThreadName(), m_pMsg->uiOpCode );
				break;
            }

        }
    }

#ifdef _MSC_VER
#else
    pthread_cleanup_pop( 1 );
#endif

}

/**
 * @brief     InitOfMessageData
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-03-21 20:04:45
 * @warning
 */
void CSignalCollect::InitOfMessageData()
{
    // 1. 메지지 내용을 멤머 변수에 복사한다.
    // 1.1 메시지 헤더 정보를 저장한다.
    // memcpy( &m_strAnalInfo, &m_pMsg->x.strAnalInfo, sizeof( struct STR_ANALINFO ) );

}

/**
 * @brief		CompleteCollecting
 * @return		void
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2023/03/11 18:26:40
 * @warning
 */
void CSignalCollect::CompleteCollecting()
{
    unsigned int uiCh=0, uiTotalPDW;
    unsigned int uiReqStatusBit;

    uiReqStatusBit = m_pRecvCollectInfo->uiReqStatus;

    while( uiReqStatusBit ) {
        if( ( unsigned int ) ( uiReqStatusBit & ( unsigned int ) 1 ) ) {
            uiTotalPDW = m_pRecvCollectInfo->uiCh2TotalPDW[uiCh];
            //Log( enDebug, "uiReqStatusBit[0x%x], uiCh[%d], uiTotalPDW[%d]", uiReqStatusBit, uiCh, uiTotalPDW );

            if( uiCh < CO_DETECT_CHANNEL ) {
                Log( enNormal, "[%s]의 탐지 채널[%d]에서, PDW[%d] 신호 수집 완료", GetThreadName(), uiCh, uiTotalPDW );
                CloseDetectChannel( uiCh, m_pRecvCollectInfo->enPCIDriver, uiTotalPDW );

            }
#if CO_TRACK_CHANNEL > 0
            else if( uiCh < CO_TRACK_CHANNEL ) {
                Log( enNormal, "[%s]에서 위협[%d/%d]의 추적 채널[%d]에서, PDW[%d] 신호 수집 완료", GetThreadName(), m_pRecvCollectInfo->uiAETID, m_pRecvCollectInfo->uiABTID, uiCh, uiTotalPDW );
            }
#endif
            else {
                Log( enNormal, "[%s]의 스캔 채널[%d]에서, PDW[%d] 신호 수집 완료", GetThreadName(), uiCh, uiTotalPDW );
                CloseScanChannel( uiCh, m_pRecvCollectInfo->enPCIDriver, uiTotalPDW );
            }
        }
        uiReqStatusBit >>= 1;
        ++uiCh;
    }

}

/**
 * @brief		탐지 채널에 수집 완료된 PDW 데이터들을 탐지 분석 쓰레드에 전달하고 탐지 채널을 재설정합니다.
 * @param		int iCh
 * @return		void
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2023/02/22 16:29:25
 * @warning
 */
void CSignalCollect::CloseDetectChannel( unsigned int uiCh, ENUM_PCI_DRIVER enPCIDriver, unsigned int uiTotalPDW )
{
    CCollectBank *pTheCollectBank = GetCollectBank( enPCIDriver );

    unsigned int uiArrayLength, uiGetMinAnalPulse = 0;

    // 최소 분석 수집 개수 읽어오기
    uiGetMinAnalPulse = g_pTheSysConfig->GetMinAnalPulse();

    pTheCollectBank->CloseCollectBank( uiCh, uiTotalPDW );

    if( uiTotalPDW >= uiGetMinAnalPulse ) {
        STR_UZPOCKETPDW *pstPDW;

        unsigned int uiABTIndex = pTheCollectBank->GetChannel2ABTIndex( uiCh );
        ENUM_COLLECTBANK enCollectBank = pTheCollectBank->GetEnumCollectBank( uiCh );

        m_pstrCollectInfo->Set( uiCh, uiTotalPDW, 0, 0, enPCIDriver, enCollectBank, uiABTIndex );

        pstPDW = pTheCollectBank->GetPDWData( uiCh );

        pTheCollectBank->GetPDWData( pstPDW, uiCh, uiTotalPDW );

        // 로직에서 PDW 데이터를 복사 오기
        CCommonUtils::PrintAllPDWs( pstPDW );

        MakeStaticPDWData( & m_stPDWData, pstPDW, true );

        uiArrayLength = sizeof( union UNION_HEADER ) + sizeof( _PDW ) * uiTotalPDW;
        g_pTheDetectAnalysis->QMsgSnd( enTHREAD_DETECTANAL_START, &m_stPDWData, uiArrayLength, GetUniMessageData(), sizeof( union UNI_MSG_DATA ), GetThreadName() );

    }
    else {
        // 신호 수집이 부족하면 자체 재신호 수집하도록 합니다.
        UNI_MSG_DATA uniMsgData;

        uniMsgData.strCollectInfo.uiReqStatus = uiCh;
        uniMsgData.strCollectInfo.enPCIDriver = enPCIDriver;
        BackupRecvUNIDataMessage( & uniMsgData );

        ReqDetectWindowCell();

        RestoreRecvUNIDataMessage();

    }

}

/**
 * @brief     스캔 체널을 닫는다.
 * @param     unsigned int uiCh
 * @param     ENUM_PCI_DRIVER enPCIDriver
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-03-17 15:36:19
 * @warning
 */
void CSignalCollect::CloseScanChannel( unsigned int uiCh, ENUM_PCI_DRIVER enPCIDriver, unsigned int uiTotalPDW )
{
    unsigned int uiABTIndex;
    unsigned int uiScanDurationms;

    ENUM_COLLECTBANK enCollectBank;

    SRxABTData *pstABTData;
    CCollectBank *pTheCollectBank = GetCollectBank( enPCIDriver );

    STR_WINDOWCELL *pWindowCell;
    STR_UZPOCKETPDW *pstPDW;

    STR_SCANRESULT stScanResult;

    //unsigned int uiTotalPDW;
    unsigned int /* uiIndex, */ uiArrayLength, uiGetMinAnalPulse = 0;

    // 필터판을 닫는다.
    pTheCollectBank->CloseCollectBank( uiCh, uiTotalPDW );

    // 설정 정보
    pstABTData = pTheCollectBank->GetChannel2ABTData( uiCh );
    uiABTIndex = pTheCollectBank->GetChannel2ABTIndex( uiCh );
    enCollectBank = pTheCollectBank->GetEnumCollectBank( uiCh );

    pWindowCell = pTheCollectBank->GetWindowCell( uiCh );

    pstPDW = pTheCollectBank->GetPDWData( uiCh );
    uiScanDurationms = pstPDW->GetColDuration();

    //uiTotalPDW = pTheCollectBank->GetTotalPDW( uiCh );
    uiGetMinAnalPulse = g_pTheSysConfig->GetMinAnalPulse();

    if( uiTotalPDW >= uiGetMinAnalPulse ) {
        memcpy( & m_theTrkScnPDW.strABTData, pstABTData, sizeof( struct SRxABTData) );

        pTheCollectBank->GetPDWData( pstPDW, uiCh, uiTotalPDW );

        MakeStaticPDWData( & m_theTrkScnPDW.strPDW, pstPDW, true );

        SaveScanResult( & stScanResult, pWindowCell, uiTotalPDW, uiScanDurationms );
        m_pstrScanAnalInfo->Set( uiCh, enCollectBank, pstABTData->uiAETID, pstABTData->uiABTID, uiABTIndex, pWindowCell->uiReqScanPeriod, pWindowCell->uiScanStep, & stScanResult );

        uiArrayLength = sizeof( struct SRxABTData ) + ( sizeof( _PDW ) * uiTotalPDW ) + sizeof( UNION_HEADER );
        g_pTheScanAnalysis->QMsgSnd( enTHREAD_SCANANAL_START, & m_theTrkScnPDW, uiArrayLength, GetUniMessageData(), sizeof( union UNI_MSG_DATA ), GetThreadName() );

    }
    // 개수가 부족할 때 수집 실패 처리를 해야 한다.
    else {
        Log( enDebug, "위협[%d/%d] 스캔 채널[%d]에 대해서 수집 개수가 부족합니다.", pstABTData->uiAETID, pstABTData->uiABTID, uiCh );

        SaveScanResult( & stScanResult, pWindowCell, uiTotalPDW, uiScanDurationms );

        m_pstrScanAnalInfo->Set( uiCh, enCollectBank, pstABTData->uiAETID, pstABTData->uiABTID, uiABTIndex, 0, pWindowCell->uiScanStep, & stScanResult );
        g_pTheEmitterMerge->QMsgSnd( enTHREAD_SCANANAL_FAIL, GetUniMessageData(), sizeof( union UNI_MSG_DATA ), GetThreadName() );
    }

    // 스캔 채널을 재설정 합니다.
    ReqScanWindowCell();

}

/**
 * @brief     SaveScanResult
 * @param     STR_SCANRESULT * pstScanResult
 * @param     STR_WINDOWCELL * pWindowCell
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-09-10 14:23:44
 * @warning
 */
void CSignalCollect::SaveScanResult( STR_SCANRESULT *pstScanResult, STR_WINDOWCELL *pWindowCell, unsigned int uiCoScanCollectingPDW, unsigned int uiScanDurationms )
{
    pstScanResult->enResult = _spAnalFail;
    pstScanResult->uiScanPeriod = 0;
    pstScanResult->enScanType = ENUM_AET_SCAN_TYPE::E_AET_SCAN_UNKNOWN;
    pstScanResult->fCoScanCollectingPDW = FDIV( uiCoScanCollectingPDW, pWindowCell->uiCoCollectingPDW );
    pstScanResult->fScanDurationms = FDIV( CPOCKETSONATAPDW::DecodeTOAms(uiScanDurationms), pWindowCell->uiMaxCollectTimeMssec );

    // 신호세기는 신호 분석에서 계산합니다.
    pstScanResult->uiMedianPA = 0;

}

/**
 * @brief     스캔 신호 수집을 수행하기 위한 윈도우 정보를 설정 합니다.
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-03-16 20:03:56
 * @warning
 */
void CSignalCollect::ReqScanWindowCell()
{
    UNI_MSG_DATA uniMsgData;

    memset( & uniMsgData, 0, sizeof( union UNI_MSG_DATA ) );

    if( m_theQueueScanAnal.Pop( &uniMsgData ) == true ) {
        Log( enDebug, "대기 중인 위협 번호(%d/%d) 에 대해서 스캔 수집시간 [%d 초] 를 설정합니다.", uniMsgData.strScanAnalInfo.uiAETID, uniMsgData.strScanAnalInfo.uiABTID, uniMsgData.strScanAnalInfo.uiReqScanPeriod );

        BackupRecvUNIDataMessage( & uniMsgData );

        // m_RcvMsg 에 저장하면 되는데...
        StartScanChannel();

        RestoreRecvUNIDataMessage();
    }
    else {
        // Log( enDebug, "스캔 수집할 대기가 없습니다." );
    }

}

/**
 * @brief		채널에서 수집 완료 됨을 처리합니다.
 * @return		void
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2023/02/22 16:34:18
 * @warning
 */
void CSignalCollect::GetPDWDataFromDetectChannel()
{
    unsigned int ui, uiTotalPDW;
    //CCollectBank* pCollectBank;

    unsigned int uiCh;

    uiCh = (unsigned int) m_pMsg->x.strCollectInfo.uiReqStatus;
    uiTotalPDW = m_pMsg->x.strCollectInfo.uiTotalPDW;
    printf( "\n iCh[%d], TotalPDW[%d]", uiCh, uiTotalPDW );

    for( ui = 0; ui < uiTotalPDW; ++ui ) {
//         pCollectBank = m_pTheDetectCollectBank[uj];
//         if( pCollectBank->IsFiltered( pstPDW ) == true ) {
//             pCollectBank->PushPDWData( pstPDW, &pPDWData->x );
//             uiDetectCh = uj;
//         }
     }

    //SetupDetectCollectBank( 0 );

}

/**
 * @brief		RoutineForDetectAnal
 * @return		void
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2021/11/23 11:59:24
 * @warning
 */
// void CSignalCollect::RoutineForSimPDW()
// {
//
//     InitSignalCollect();
//
// #ifdef _MSC_VER
//     while( m_bThreadLoop ) {
//         if( QMsgRcv( enNO_WAIT ) > 0 ) {
//             switch( m_pMsg->uiOpCode ) {
//                 case enTHREAD_REQ_SET_TRACKWINDOWCELL :
//                     ReqTrackWindowCell();
//                     break;
//
//                 case enTHREAD_REQ_CLOSE_TRACKWINDOWCELL :
//                     CloseTrackWindowCell();
//                     break;
//
// //                 case enTHREAD_REQ_SET_SCANWINDOWCELL :
// //                     ReqScanWindowCell();
// //                     break;
//
// //                 case enTHREAD_REQ_CLOSE_SCANWINDOWCELL :
// //                     CloseScanWindowCell();
// //                     break;
//
//                 case enTHREAD_REQ_SHUTDOWN :
//                     LOGMSG1( enDebug, "[%s] 를 종료 처리 합니다...", GetThreadName() );
//                     break;
//
// //                 case enTHREAD_MODE :
// //                     m_bThreadLoop = false;
// //                     break;
//
//                 // 모의 명령 처리
//                 case enTHREAD_REQ_SIM_PDWDATA :
//                     SimPDWData();
//                     CheckAllCollectBank();
//                     break;
//
//                 case enTHREAD_REQ_DETECT_COLSTOP:
//                     GetPDWDataFromDetectChannel();
//                     break;
//
//                 default:
//                     Log( enError, "[%s]에서 잘못된 명령(0x%x)을 수신하였습니다 !!", GetThreadName(), m_pMsg->uiOpCode );
//                     break;
//
//             }
//         }
//
//         // 신호 수집은 여기서 수행한다.
// //         if( bRoutineForDetectAnal == true ) {
// //             AnalysisStart();
// //         }
//     }
// #endif
//
// }

/**
 * @brief CSignalCollect::SendEndCollect
 */
void CSignalCollect::SendEndCollect()
{
    if( m_bSendEnd == false ) {
        //TRACE( "\nCSignalCollect::SendEndCollect()");
        g_pTheEmitterMerge->QMsgSnd( enTHREAD_DETECTANAL_END, GetThreadName() );
        //TRACE( "!");

        m_bSendEnd = true;
    }

}

/**
 * @brief     객체를 초기화 합니다.
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-05-10, 14:40
 * @warning
 */
void CSignalCollect::InitSignalCollect( bool bWrite )
{
    m_uiPDWID = 0;

    // 탐지/추적/스캔 윈도우 셀을 닫는다.
    CloseCollectBank();

#ifdef _SIM_PDW_
    unsigned int i;

    m_bWriteDDRFile = bWrite;

    memcpy( & m_stRadarPDW, & g_stRadarPDW, sizeof( g_stRadarPDW ) );

    ///////////////////////////////////////////////////////////////////////////////////
    // 모의 레이더 환경 설정값 정의

    if( m_stRadarPDW.enScanType == ENUM_AET_SCAN_TYPE::E_AET_SCAN_STEADY ) {
        m_stRadarPDW.iAmplitude = 3;
    }
    else {
    }

    if( m_stRadarPDW.enScanType == ENUM_AET_SCAN_TYPE::E_AET_SCAN_CONICAL ) {
        m_stRadarPDW.fScanPeriod = FDIV( 1000, m_stRadarPDW.fScanPeriod );
    }
    else {

    }

    ///////////////////////////////////////////////////////////////////////////////////
    //
    _TOA tMainLobeDuration = 0;
    if( m_stRadarPDW.enScanType == ENUM_AET_SCAN_TYPE::E_AET_SCAN_CIRCULAR ) {
        for( i=0 ; i < m_stRadarPDW.uiCoPulsePerLobe; ++i ) {
            tMainLobeDuration += MakeSIMPRI( 0 );
        }

        m_uiMainLobeDuration = (unsigned int) TOAusCNV( tMainLobeDuration );
    }

    ///////////////////////////////////////////////////////////////////////////////////
    //
    m_uiCoSim = 0;
    m_uiIndex = 0;

    // 초기 시간 설정
    _TOA tTOA = IFTOAusCNV( ( float ) ( m_stRadarPDW.fScanPeriod * (float) (1000) ) );
    m_tTOA = (_TOA) ( CCommonUtils::Random( ( float ) 0.0, (float) tTOA ) + (float) 0.5 );

    m_tFirstTOA = 0;

    m_uiStartDuration = UDIV( ( m_stRadarPDW.fScanPeriod * (float) 1000000 ), 2 );

    if( m_stRadarPDW.enPRIType == ENUM_AET_PRI_TYPE::E_AET_PRI_STAGGER ) {
        sprintf( m_szDDRFile, "%s%s/%s[%05.0f]_%s[%02d]_%s_%d.ddr", SHARED_DATA_DIRECTORY, DDR_DIRECTORY, g_szAetFreqType[( int ) m_stRadarPDW.enFreqType], m_stRadarPDW.fFreq, \
            g_szAetPriType[( int ) m_stRadarPDW.enPRIType], m_stRadarPDW.iCoPRIDwellStaggerPositions, \
            g_szAetScanType[( int ) m_stRadarPDW.enScanType], \
            g_enBoardId );
    }
    else {
        sprintf( m_szDDRFile, "%s%s/%s[%05.0f]_%s[%04.0f]_%s_%d.ddr", SHARED_DATA_DIRECTORY, DDR_DIRECTORY, g_szAetFreqType[(int)m_stRadarPDW.enFreqType], m_stRadarPDW.fFreq, \
            g_szAetPriType[( int ) m_stRadarPDW.enPRIType], m_stRadarPDW.fPRI, \
            g_szAetScanType[( int ) m_stRadarPDW.enScanType], \
            g_enBoardId );
    }

    // GenerateDDRFile( false );

#endif

}

/**
 * @brief     StartCollecting
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-03-07 11:25:13
 * @warning
 */
void CSignalCollect::StartCollecting()
{

#ifdef _MSC_VER
    Sleep( 1 );
#endif

    // 탐지 신호 수집을 시작합니다.
    m_pTheLeftCollectBank->StartCollecting();
    m_pTheRigtCollectBank->StartCollecting();

    // 탐지 신호 수집을 위해 수집 설정합니다.
    unsigned int uiCh;
    for( uiCh=0 ; uiCh < ( unsigned int ) CO_DETECT_CHANNEL; ++uiCh ) {
        // 탐지 채널에 대해서 수집 설정 합니다.
        // 왼쪽 PCI 드라이버를 설정 합니다.
        StartDetectChannel( uiCh, enLEFT_PCI_DRIVER );

        // 우쪽 PCI 드라이버를 설정 합니다.
        StartDetectChannel( uiCh, enRIGHT_PCI_DRIVER );
        //WhereIs;

    }

}

/**
 * @brief		좌/우 탐지 채널을 수집 시작 합니다.
 * @param		unsigned int uiCh
 * @param		ENUM_PCI_DRIVER enPCIDriver
 * @return		void
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2023/03/11 18:51:55
 * @warning
 */
void CSignalCollect::StartDetectChannel( unsigned int uiCh, ENUM_PCI_DRIVER enPCIDriver )
{
    CCollectBank *pTheCollectBank = GetCollectBank( enPCIDriver );

    // 해당 채널의 WindowCell 얻기
    pTheCollectBank->StartDetectChannel( uiCh );

}

/**
 * @brief     StartScanChannel
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-03-16 20:21:12
 * @warning
 */
void CSignalCollect::StartScanChannel()
{
    int iCh;

    // 위협 관리 쓰레드에서 빔 데이터를 갖고 오기
    bool bRet = CopyFromEmitterABTData( & m_stABTData );

    if( bRet == true && IsValidABT() == true ) {
        ENUM_PCI_DRIVER enPCIDriver;

        SRadarMode *pRadarMode;

        enPCIDriver = WhichPCIDriver();

        CCollectBank *pTheCollectBank = GetCollectBank( enPCIDriver );

        pRadarMode = m_pIdentifyAlg->GetRadarMode( m_stABTData.uiRadarModeIndex );

        iCh = pTheCollectBank->StartScanChennel( &m_stABTData, pRadarMode, m_pRecvScanAnalInfo->uiReqScanPeriod, m_pRecvScanAnalInfo->uiScanStep, & m_pRecvScanAnalInfo->stScanResult );
        if( iCh >= 0 ) {
            // 이때 체널 번호가 결정 됩니다.
            pTheCollectBank->SaveCollectCahnnelInfo( ( unsigned int ) iCh, &m_stABTData, m_pRecvScanAnalInfo->uiABTIndex, m_pRecvScanAnalInfo->uiReqScanPeriod );

        }
        else {
            m_theQueueScanAnal.Push( GetRecvDataMessage()->x );
        }

    }
    else {
        m_pstrScanAnalInfo->Set( ( unsigned int ) -1, enUnknownCollectBank, m_pRecvScanAnalInfo->uiAETID, m_pRecvScanAnalInfo->uiABTID, m_pRecvScanAnalInfo->uiABTIndex, 0, m_pRecvScanAnalInfo->uiScanStep );

        // 해당 위협이 소실되거나 스캔 실패를 요청합니다.
        g_pTheEmitterMerge->QMsgSnd( enTHREAD_SCANANAL_ERROR, GetUniMessageData(), sizeof( union UNI_MSG_DATA ), GetThreadName() );

        Log( enError, "이미 소실된 방사체/빔[%d/%d] 데이터 입니다.", m_pRecvScanAnalInfo->uiAETID, m_pRecvScanAnalInfo->uiABTID );

    }

    //StartScanChannel( uiCh, enLEFT_PCI_DRIVER );
    // StartScanChannel();

}

/**
 * @brief     빔 데이터를 근거로 좌 또는 우 드라이버를 선택합니다.
 * @return    ENUM_PCI_DRIVER
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-03-17 11:49:29
 * @warning
 */
ENUM_PCI_DRIVER CSignalCollect::WhichPCIDriver()
{
    ENUM_PCI_DRIVER enPCIDriver;

    //!     주파수 정보를 보고 결정해야 합니다.
    //date 	2023-03-31 10:34:16

    printf( "\n m_stABTData.fFreqMean=%.1f", m_stABTData.fFreqMean );
    WhereIs;
    switch( g_enBoardId ) {
        case enPRC1 :
            if( m_stABTData.fFreqMean < 1000. ) {
                enPCIDriver = enLEFT_PCI_DRIVER;
            }
            else {
                enPCIDriver = enRIGHT_PCI_DRIVER;
            }
            break;
        case enPRC2 :
            if( m_stABTData.fFreqMean < 4000. ) {
                enPCIDriver = enLEFT_PCI_DRIVER;
            }
            else {
                enPCIDriver = enRIGHT_PCI_DRIVER;
            }
            break;
        case enPRC3:
            if( m_stABTData.fFreqMean < 8000. ) {
                enPCIDriver = enLEFT_PCI_DRIVER;
            }
            else {
                enPCIDriver = enRIGHT_PCI_DRIVER;
            }
            break;

        case enPRC4:
            if( m_stABTData.fFreqMean < 12000. ) {
                enPCIDriver = enLEFT_PCI_DRIVER;
            }
            else {
                enPCIDriver = enRIGHT_PCI_DRIVER;
            }
            break;

        case enPRC5:
            if( m_stABTData.fFreqMean < 16000. ) {
                enPCIDriver = enLEFT_PCI_DRIVER;
            }
            else {
                enPCIDriver = enRIGHT_PCI_DRIVER;
            }
            break;

        default:
            enPCIDriver = enLEFT_PCI_DRIVER;
            break;

    }

    return enPCIDriver;

}

/**
 * @brief     CopyFromEmitterABTData
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-03-17 10:37:46
 * @warning
 */
bool CSignalCollect::CopyFromEmitterABTData( SRxABTData *pABTData )
{
    bool bRet = true;
    SRxABTData *pSRxABTData = g_pTheEmitterMerge->GetABTData( m_pRecvScanAnalInfo->uiABTIndex );

    if( pSRxABTData != NULL ) {
        memcpy( pABTData, pSRxABTData, sizeof( struct SRxABTData ) );
    }
    else {
        bRet = false;

    }

    return bRet;

}

/**
 * @brief     IsValidABT
 * @param     SRxABTData * pABTData
 * @return    bool
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-03-17 10:45:07
 * @warning
 */
bool CSignalCollect::IsValidABT()
{
    bool bRet = false;

    if( m_stABTData.uiABTID == m_pRecvScanAnalInfo->uiABTID && m_stABTData.uiAETID == m_pRecvScanAnalInfo->uiAETID ) {
        bRet = true;
    }

    return bRet;

}

/**
 * @brief		CloseCollectBank
 * @return		void
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2023/02/13 13:42:32
 * @warning
 */
void CSignalCollect::CloseCollectBank()
{

    // 좌측 PCI 를 해지한다.
    m_pTheLeftCollectBank->CloseCollectBanks();

    // 우측 PCI 를 해지한다.
    m_pTheRigtCollectBank->CloseCollectBanks();

}

/**
 * @brief     탐지 신호 수집을 수행하기 위한 윈도우 정보를 설정 합니다.
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-03-13 15:01:30
 * @warning
 */
void CSignalCollect::ReqDetectWindowCell()
{
    ENUM_PCI_DRIVER enPCIDriver = m_pRecvCollectInfo->enPCIDriver;
    unsigned int uiCh = m_pRecvCollectInfo->uiReqStatus;

    Log( enNormal, "[%s]에서 [%s] 채널[%d] 신호 수집 재설정", GetThreadName(), g_strPCIDrverDirection[enPCIDriver].c_str(), uiCh+1 );

    //CCollectBank *pTheCollectBank = GetCollectBank( enPCIDriver );

    StartDetectChannel( uiCh, enPCIDriver );

}

/**
 * @brief		ReqTrackWindowCell
 * @return		void
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2023/02/22 16:17:30
 * @warning
 */
void CSignalCollect::ReqTrackWindowCell()
{
    SRxABTData *pABTData = ( SRxABTData *) m_uniLanData.szFile;

    // 랜 데이터를 갖고온다.
    memcpy( m_uniLanData.szFile, GetRecvData(), m_pMsg->uiArrayLength );

    // 빔 정보를 기반으로 추적 및 스캔 채널을 업데이트 한다.
    if(  m_pMsg->x.strDetAnalInfo.uiCh == _spZero ) {
        NewTrackWindowCell( pABTData );
    }
    // 추적 채널 업데이트한다.
    else {
        UpdateTrackWindowCell( pABTData );

    }

}

/**
 * @brief CSignalCollect::CloseSetWindowCell
 */
void CSignalCollect::CloseTrackWindowCell()
{
    //SRxABTData *pABTData = ( SRxABTData *) m_uniLanData.szFile;

    // 랜 데이터를 갖고온다.
//     PopLanData( m_uniLanData.szFile, m_pMsg->iArrayIndex, m_pMsg->uiArrayLength );
//
//     Log( enDebug, "[%d]번, [%d]채널 에서 분석된 빔 번호[%d]의 윈도우 셀을 닫습니다." , m_pMsg->x.strAnalInfo.enBoardID, m_pMsg->x.strAnalInfo.iCh, m_pMsg->x.strAnalInfo.uiABTID );
//
//      m_theTrackChannel.Push( m_pMsg->x.strAnalInfo.iCh );
//
//     // 빔 정보를 기반으로 추적 및 스캔 채널을 업데이트 한다.
//     //CloseTrackWindowCell( pABTData );
//
//     CCollectBank *pCCollectBank=GetCollectBank( m_pMsg->x.strAnalInfo.iCh );
//     if( pCCollectBank != NULL ) {
//         pCCollectBank->CloseTrackWindowCell();
//     }

}

/**
 * @brief CSignalCollect::UpdateTrackWindowCell
 * @param pABTData
 */
void CSignalCollect::UpdateTrackWindowCell( SRxABTData *pABTData )
{
//     STR_WINDOWCELL strWindowCell;
//
//     // 정보 업데이트
//     CalTrackWindowCell( & strWindowCell, pABTData );
//
//     CCollectBank *pCCollectBank=GetCollectBank( m_pMsg->x.strAnalInfo.iCh );
//     if( pCCollectBank != NULL ) {
//         pCCollectBank->UpdateWindowCell( & strWindowCell );
//     }

}


/**
 * @brief     빔 정보를 보고 추적 윈도우 셀을 설정한다.
 * @param     SRxABTData * pABTData
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-04-20, 16:16
 * @warning
 */
void CSignalCollect::NewTrackWindowCell( SRxABTData *pABTData )
{
    //int iCh=CO_DETECT_CHANNEL;

    //STR_WINDOWCELL strWindowCell;

//    if( false && m_theTrackChannel.Pop( & iCh ) == true ) {
//        //Log( enDebug, "추적 [%d]채널에 탐지 분석된 빔 번호[%d]를 기반으로 윈도우 셀을 설정합니다.", m_pMsg->x.strAnalInfo.iCh, m_pMsg->x.strAnalInfo.uiABTID );
//
//         memcpy( & m_ABTData[iCh-CO_DETECT_CHANNEL], pABTData, sizeof(struct SRxABTData) );
//
//         CalTrackWindowCell( & strWindowCell, pABTData );
//
//         m_pTheCollectBank = GetCollectBank( iCh );
//         if( m_pTheCollectBank != NULL ) {
//             m_pTheCollectBank->UpdateWindowCell( & strWindowCell );
//
//             CCollectBank *pCollectBank = GetCollectBank(iCh);
//             STR_PDWDATA *pPDWData = pCollectBank->GetPDWData();
//
// #ifdef _ELINT_
//             strcpy((char *)pPDWData->x.el.aucTaskID, m_pMsg->x.strAnalInfo.uniPDWHeader.el.aucTaskID );
//             pPDWData->x.el.uiIsStorePDW = m_pMsg->x.strAnalInfo.uniPDWHeader.el.uiIsStorePDW;
//             pPDWData->x.el.enCollectorID = m_pMsg->x.strAnalInfo.uniPDWHeader.el.enCollectorID;
//             pPDWData->x.el.enBandWidth = m_pMsg->x.strAnalInfo.uniPDWHeader.el.enBandWidth;
// #elif defined(_XBAND_)
//             strcpy((char *)pPDWData->x.xb.aucTaskID, m_pMsg->x.strAnalInfo.uniPDWHeader.xb.aucTaskID);
//             pPDWData->x.xb.uiIsStorePDW = m_pMsg->x.strAnalInfo.uniPDWHeader.xb.uiIsStorePDW;
//             pPDWData->x.xb.enCollectorID = m_pMsg->x.strAnalInfo.uniPDWHeader.xb.enCollectorID;
//             pPDWData->x.xb.enBandWidth = m_pMsg->x.strAnalInfo.uniPDWHeader.xb.enBandWidth;
//
// #endif
//             Log(enDebug, " 추적 채널 설정 성공 [%d]Ch for B[%d]", iCh, pABTData->uiABTID);
//         }
//         else {
//             Log(enDebug, " 추적 채널 설정 실패 [%d]Ch for B[%d]", iCh, pABTData->uiABTID);
//         }
//
//
//     }
//     else {
//         LOGMSG( enDebug, "추적 채널이 없어서 할당하지 못합니다. !!" );
//     }

}

/**
 * @brief     빔 정보를 보고 추적 윈도우 셀을 계산한다.
 * @param     STR_WINDOWCELL * pstrWindowCell
 * @param     SRxABTData * pABTData
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2021-07-24, 17:40
 * @warning
 */
void CSignalCollect::CalTrackWindowCell( STR_WINDOWCELL *pstrWindowCell, SRxABTData *pABTData )
{
    UINT uiCollectTime;

    SRadarMode *pRadarMode;

    float fMinCollectTime=0;

    if( pstrWindowCell != NULL ) {
        pRadarMode = m_pIdentifyAlg->GetRadarMode( pABTData->uiRadarModeIndex );

        memset( pstrWindowCell, 0, sizeof( struct STR_WINDOWCELL) );

        pstrWindowCell->uiABTID = pABTData->uiABTID;

        // 레이더모드 식별 경우에 식별 정보를 이용하여 주파수 및 펄스폭을 설정
        if( pRadarMode != NULL ) {
            pstrWindowCell->strFreq.iLow = I_IFRQMhzCNV( 0, pRadarMode->fRF_TypicalMin );
            pstrWindowCell->strFreq.iHigh = I_IFRQMhzCNV( 0, pRadarMode->fRF_TypicalMax );

            pstrWindowCell->strPW.iLow = IPWCNVLOW( pABTData->fPWMin );
            pstrWindowCell->strPW.iHigh = IPWCNVHGH( pABTData->fPWMax );

            fMinCollectTime = _max( pRadarMode->fScanPrimaryTypicalMax, pRadarMode->fScanSecondaryTypicalMax );
        }
        else {
            pstrWindowCell->strFreq.iLow = I_IFRQMhzCNV( g_enBoardId, pABTData->fFreqMin - 5 );
            pstrWindowCell->strFreq.iHigh = I_IFRQMhzCNV( g_enBoardId, pABTData->fFreqMax + 5 );

            pstrWindowCell->strPW.iLow = IPWCNVLOW( pABTData->fPWMin );
            pstrWindowCell->strPW.iHigh = IPWCNVHGH( pABTData->fPWMax );

#ifdef _XBAND_
            fMinCollectTime = (float) 10.0;
#else
            fMinCollectTime = pABTData->fMaxScanPeriod;
#endif
        }

        pstrWindowCell->strPA.iLow = 0;
        pstrWindowCell->strPA.iHigh = 0x7fffffff;

        pstrWindowCell->strAOA.iLow = (int) ( ( IAOACNV( pABTData->fDOAMin-10 ) + MAX_AOA_BIT ) % MAX_AOA_BIT );
        pstrWindowCell->strAOA.iHigh = (int) ( ( IAOACNV( pABTData->fDOAMax+10 ) + MAX_AOA_BIT ) % MAX_AOA_BIT );

        pstrWindowCell->uiCoCollectingPDW = KWN_COLLECT_PDW;

        uiCollectTime = UADD( 5000, fMinCollectTime );
        //pstrWindowCell->uiMaxCollectTimesec = UDIV( uiCollectTime, 1000 );
        pstrWindowCell->uiMaxCollectTimeMssec = uiCollectTime % 1000;

    }
    else {

    }
}

/**
 * @brief		GetCollectBank
 * @param		ENUM_PCI_DRIVER enPCIDriver
 * @return		CCollectBank *
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2023/03/11 20:08:00
 * @warning
 */
CCollectBank *CSignalCollect::GetCollectBank( ENUM_PCI_DRIVER enPCIDriver )
{
    CCollectBank *pCollectBank;

    if( enPCIDriver == enLEFT_PCI_DRIVER ) {
        pCollectBank = m_pTheLeftCollectBank;
    }
    else {
        pCollectBank = m_pTheRigtCollectBank;
    }

    return pCollectBank;
}



/**
 * @brief CSignalCollect::CloseScanWindowCell
 */
void CSignalCollect::CloseScanWindowCell()
{

    // 랜 데이터를 갖고온다.
//     PopLanData( m_uniLanData.szFile, m_pMsg->iArrayIndex, m_pMsg->uiArrayLength );
//
//     Log( enDebug, "D[%d] 대역, [%d] 채널 에서 분석된 빔 번호[%d]의 윈도우 셀을 닫습니다." , m_pMsg->x.strAnalInfo.enBoardID, m_pMsg->x.strAnalInfo.iCh, m_pMsg->x.strAnalInfo.uiABTID );
//
//     m_theTrackChannel.Push( m_pMsg->x.strAnalInfo.iCh );
//
//     //GetCollectBank( m_pMsg->x.strAnalInfo.iCh )->CloseTrackWindowCell();
//     CCollectBank *pCCollectBank=GetCollectBank( m_pMsg->x.strAnalInfo.iCh );
//     if( pCCollectBank != NULL ) {
//         pCCollectBank->CloseTrackWindowCell();
//     }

}



/**
 * @brief     빔 데이터 정보를 입력으로 스캔 윈도우 셀 정보를 계산한다.
 * @param     SRxABTData * pABTData
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-05-10, 14:05
 * @warning
 */
void CSignalCollect::UpdateScanWindowCell( SRxABTData *pABTData )
{
//     STR_WINDOWCELL strWindowCell;
//
//     // 정보 업데이트
//     CalScanWindowCell( & strWindowCell, pABTData );
//
//     //GetCollectBank( m_pMsg->x.strAnalInfo.iCh )->UpdateWindowCell( & strWindowCell );
//     CCollectBank *pCCollectBank=GetCollectBank( m_pMsg->x.strAnalInfo.iCh );
//     if( pCCollectBank != NULL ) {
//         pCCollectBank->UpdateWindowCell( & strWindowCell );
//     }

}

/**
 * @brief     STR_PDWDATA 구조체를 STR_STATIC_PDWDATA 으로 복사한다.
 * @param     STR_PDWDATA * pPDWData
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-03-03, 14:08
 * @warning
 */
void CSignalCollect::MakeStaticPDWData( STR_STATIC_PDWDATA *pStaticPDWData, STR_UZPOCKETPDW *pPDWData, bool bAutoIncPDWID )
{
    unsigned int ui, uiTotalPDW;

    if( bAutoIncPDWID == true ) {
        ++m_uiPDWID;
        pPDWData->SetPDWID( m_uiPDWID );
    }

    // 헤더 복사
    //printf( "\n 밴드: %d, 보드: %d, 시간: %d, 개수 : %d", pPDWData->x.ps.uiBand, pPDWData->x.ps.uiBoardID, pPDWData->x.ps.stCommon.tColTime, pPDWData->x.ps.stCommon.uiTotalPDW );
    memcpy( &pStaticPDWData->x, & pPDWData->x, sizeof(union UNION_HEADER) );

    // 데이터 복사
    uiTotalPDW = pPDWData->GetTotalPDW();

    _PDW *pstPDW = & pStaticPDWData->stPDW[0];
    for( ui=0 ; ui < uiTotalPDW ; ++ui ) {
        pPDWData->LoadPDWData( ui, pstPDW );
        ++ pstPDW;
    }

}

//////////////////////////////////////////////////////////////////////////
// PDW 및 필터판 모의

#ifdef _SIM_PDW_
/**
 * @brief		MakeSIMPDWData
 * @return		void
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2023/03/11 18:50:34
 * @warning
 */
void CSignalCollect::MakeSIMPDWData()
{
    unsigned int i, uiCoPDW, uiIndex = 0;

    float fRandomDOA;

    int iDOA;

    unsigned int uiTime=0;
    unsigned int uiRandomDOA, uiRandomPA, uiRandomPW, randomFreq;

    SIGAPDW *pSIGAPDW = m_pSIGAPDW;

    memset( m_pUniHeader, 0, sizeof( union UNION_HEADER ) );

    m_pUniHeader->SetBoardID( ( UINT ) g_enBoardId );


    time_t tTime = time( NULL );

    if( tTime > 0 ) {
        uiTime = ( unsigned int ) tTime;
    }

    m_pUniHeader->SetColTime( uiTime, 0 );
    //m_pUniHeader->SetTotalPDW( NUM_OF_PDW );
    m_pUniHeader->SetIsStorePDW( 1 );
    m_pUniHeader->SetBandWidth( 1 );
    m_pUniHeader->SetCollectorID( RADARCOL_1 );

    m_pUniHeader->SetBoardID( ( unsigned int ) g_enBoardId );
    m_pUniHeader->SetBand( ( unsigned int ) g_enBoardId );

    char *pTaskID = m_pUniHeader->GetTaskID( g_enUnitType );
#if defined(_XBAND_) || defined(_ELINT_)
    if( pTaskID != NULL ) {
        strcpy( pTaskID, "MSIGA" );
    }
#endif

    //if ((m_uiCoSim % 20) <= 5) {
//     if( ( m_uiCoSim % 20 ) <= 10 && false ) {
//         uiCoPDW = 0;
//     }
//     else {
//         uiCoPDW = NUM_OF_PDW;
//     }
    uiCoPDW = NUM_OF_SIM_PDW;

#ifdef __VXWORKS__
    uiCoPDW = 0;

#endif

    m_pUniHeader->SetTotalPDW( uiCoPDW );


    int iBandWidth = m_pUniHeader->GetBandWidth();

#ifdef _SIM_PDW_
#if defined(_POCKETSONATA_) || defined(_712_)
#define MANUALTOA   (35)

//     _TOA manualTOA[MANUALTOA] = { CPOCKETSONATAPDW::EncodeTOAus( ( float ) 1598.41 ),
//                                   CPOCKETSONATAPDW::EncodeTOAus( ( float ) 2986.972 ),
//                                   CPOCKETSONATAPDW::EncodeTOAus( ( float ) 4359.585 ),
//                                   CPOCKETSONATAPDW::EncodeTOAus( ( float ) 5746.258 ),
//                                   CPOCKETSONATAPDW::EncodeTOAus( ( float ) 7022.91 ),
//                                   CPOCKETSONATAPDW::EncodeTOAus( ( float ) 8270.053 ),
//                                   CPOCKETSONATAPDW::EncodeTOAus( ( float ) 9516.386 ),
//                                   CPOCKETSONATAPDW::EncodeTOAus( ( float ) 10763.56 ),
//                                   CPOCKETSONATAPDW::EncodeTOAus( ( float ) 12010.74 ),
//                                   CPOCKETSONATAPDW::EncodeTOAus( ( float ) 13362.59 ),
//                                   CPOCKETSONATAPDW::EncodeTOAus( ( float ) 16424.9 ),
//                                   CPOCKETSONATAPDW::EncodeTOAus( ( float ) 17956.39 ),
//                                   CPOCKETSONATAPDW::EncodeTOAus( ( float ) 21018.86 ),
//                                   CPOCKETSONATAPDW::EncodeTOAus( ( float ) 22410.07 ),
//                                   CPOCKETSONATAPDW::EncodeTOAus( ( float ) 23801.04 ),
//                                   CPOCKETSONATAPDW::EncodeTOAus( ( float ) 25192.14 ),
//                                   CPOCKETSONATAPDW::EncodeTOAus( ( float ) 26582.81 ),
//                                   CPOCKETSONATAPDW::EncodeTOAus( ( float ) 29115.85 ),
//                                   CPOCKETSONATAPDW::EncodeTOAus( ( float ) 30362.69 ),
//                                   CPOCKETSONATAPDW::EncodeTOAus( ( float ) 31609.92 ),
//                                   CPOCKETSONATAPDW::EncodeTOAus( ( float ) 32857.43 ),
//                                   CPOCKETSONATAPDW::EncodeTOAus( ( float ) 37344.84 ),
//                                   CPOCKETSONATAPDW::EncodeTOAus( ( float ) 38874.19 ),
//                                   CPOCKETSONATAPDW::EncodeTOAus( ( float ) 40402.47 ),
//                                   CPOCKETSONATAPDW::EncodeTOAus( ( float ) 41951.62 ),
//                                   CPOCKETSONATAPDW::EncodeTOAus( ( float ) 43256.66 ),
//                                   CPOCKETSONATAPDW::EncodeTOAus( ( float ) 44647.55 ),
//                                   CPOCKETSONATAPDW::EncodeTOAus( ( float ) 46038.38 ),
//                                   CPOCKETSONATAPDW::EncodeTOAus( ( float ) 47429.53 ),
//                                   CPOCKETSONATAPDW::EncodeTOAus( ( float ) 48715.07 ),
//                                   CPOCKETSONATAPDW::EncodeTOAus( ( float ) 49961.97 ),
//                                   CPOCKETSONATAPDW::EncodeTOAus( ( float ) 51209.08 ),
//    };

    iDOA = ( int ) m_uiCoSim * ( int ) CPOCKETSONATAPDW::EncodeDOA( 50 );

#if 0
    int iValue[1000];
    float fValue[1000];
    for( i=0 ; i < 1000 ; ++i ) {
        float fRandom;
        int iRandom;

        fRandom = CCommonUtils::Random( ( float ) 0.0, ( float ) 10. );
        iRandom = CCommonUtils::Random( 0, 9 );

        iValue[i] = iRandom;
        fValue[i] = fRandom;
        TRACE( "\n fRandom[%f], iRandom[%d]", fRandom, iRandom );
    }
#endif

    int iRandomIndex = ( int ) CCommonUtils::Random( ( float ) 0., ( float ) 100. );
    for( i = 0; i < uiCoPDW; ) {
        float fDOAMean = m_stRadarPDW.fDOA;

        // 방위 모의
        if( m_stRadarPDW.enDOA == E_AET_DOA_FIXED ) {
            fRandomDOA = ( float ) ( CCommonUtils::Random( -m_stRadarPDW.fDOARange, m_stRadarPDW.fDOARange ) + fDOAMean );
        }
        else if( m_stRadarPDW.enDOA == E_AET_DOA_GAUSSIAN ) {
            fRandomDOA = ( float ) ( CCommonUtils::NormalDistribution( (float) 0, (float) m_stRadarPDW.fDOARange ) + fDOAMean );
        }
        else if( m_stRadarPDW.enDOA == E_AET_DOA_MULTI ) {
            fRandomDOA = (float) ( (int) ( i / 50 )  * 40. );
            fRandomDOA = ( float ) ( CCommonUtils::Random( -m_stRadarPDW.fDOARange, m_stRadarPDW.fDOARange ) + fRandomDOA );
        }
        else {
            fRandomDOA = ( float ) ( CCommonUtils::Random( -m_stRadarPDW.fDOARange, m_stRadarPDW.fDOARange ) + 50. );
        }

        uiRandomDOA = ( unsigned int ) ( int ) CPOCKETSONATAPDW::EncodeDOA( fRandomDOA );

#if 0
        uiRandomDOA = ( unsigned int ) ( int ) CPOCKETSONATAPDW::EncodeDOA( 50 );

        if( i >= uiCoPDW / 2 && false ) {
            iCWPulse = 0;
        }
        else {
            uiRandomDOA = ( unsigned int ) ( int ) CPOCKETSONATAPDW::EncodeDOA( 150 );
            iCWPulse = 1;
        }
#endif

        m_iMissingPercent = m_stRadarPDW.iMissingPercent;

        // TOA 모의
        m_tTOA += MakeSIMPRI( iRandomIndex );

        if( m_tFirstTOA == 0 ) {
            m_tFirstTOA = m_tTOA;
        }

        // 주파수 모의
        randomFreq = MakeSIMFreq( iRandomIndex );

        // 신호세기 모의
        uiRandomPA = MakeSIMPA( iRandomIndex );

        // 펄스폭 모의
        uiRandomPW = CPOCKETSONATAPDW::EncodePWns( ( m_stRadarPDW.fPW * (float) 1000. ) + CCommonUtils::Random( ( float ) -3, ( float ) 3. ) );

        memset( pSIGAPDW, 0, sizeof( union DMAPDW ) );

        if( m_iMissingPercent > 0 && ( m_iMissingPercent == 0 || CCommonUtils::Random( 0, 100 ) >= m_iMissingPercent /*&& ( m_uiIndex < 40 || m_uiIndex > 60 )*/ ) ) {
            //TRACE( "@" );
            //
            pSIGAPDW->uPDW.stHwPdwDataRf.CwPulse = 0;        // ;
            pSIGAPDW->uPDW.stHwPdwDataRf.Pmop = 0;
            pSIGAPDW->uPDW.stHwPdwDataRf.Fmop = 0;
            pSIGAPDW->uPDW.stHwPdwDataRf.FalsePdw = 0;
            pSIGAPDW->uPDW.stHwPdwDataRf.FmopDir = 0;
            pSIGAPDW->uPDW.stHwPdwDataRf.BoardId = 6;
            pSIGAPDW->uPDW.stHwPdwDataRf.FmopBw = 8000;

            pSIGAPDW->uPDW.stHwPdwDataRf.uiAOA = uiRandomDOA;
            pSIGAPDW->uPDW.stHwPdwDataRf.Di = 0;
            pSIGAPDW->uPDW.stHwPdwDataRf.uiPA = uiRandomPA;

            pSIGAPDW->uPDW.stHwPdwDataRf.uiPW = uiRandomPW;
            pSIGAPDW->uPDW.stHwPdwDataRf.uiFreq = randomFreq;

            pSIGAPDW->uPDW.stHwPdwDataRf.PpfCh = 3;
            pSIGAPDW->uPDW.stHwPdwDataRf.ullTOA = m_tTOA;

            pSIGAPDW->uPDW.stHwPdwDataRf.Edge = 1;

            pSIGAPDW->uPDW.stHwPdwDataRf.Index = m_uiIndex;

            //printf( "m_ullTOA[%llx], [%0X:%0X]\n" , m_ullTOA, pDMAPDW->uPDW.uniPdw_toa_edge.stPdw_toa_edge.toa_H, pDMAPDW->uPDW.uniPdw_freq_toa.stPdw_freq_toa.toa_L );

            ++pSIGAPDW;

            ++ i;
        }
        else {
            // TRACE( "*" );
        }

        ++m_uiIndex;

    }

    m_tFirstTOA = 0;

    GenerateDDRFile( m_bWriteDDRFile );
    m_bWriteDDRFile = false;

#else
    uiCoPDW = m_strResColStart.uiCoPulseNum;

    iDOA = m_uiCoSim * 20;

    for( i = 0; i < uiCoPDW; ++i ) {
        int iCh;

        fRandomDOA = ( float ) iDOA + ( ( float ) CCommonUtils::Rand( 100 ) / ( float ) 10. );

        m_tTOA += 0x100; // CEncode::EncodeTOAus(100, 0);

        memset( pSIGAPDW, 0, sizeof( struct SIGAPDW ) );

        //
        pSIGAPDW->tTOA = m_tTOA;

        pSIGAPDW->iStat = CEncode::EncodePulseType( 0 );

        pSIGAPDW->uiAOA = CEncode::EncodeDOA( fRandomDOA );
        pSIGAPDW->uiFreq = CEncode::EncodeRealFREQMHz( &iCh, 9000. );
        pSIGAPDW->uiPA = CEncode::EncodePA( -100 );
        pSIGAPDW->uiPW = CEncode::EncodePWns( 100, iBandWidth );

        ++m_uiIndex;

        ++pSIGAPDW;
}

#endif


#else
    m_pTheGenPDW->OpenMakefile( g_szPDWScinarioFile );
    m_pTheGenPDW->ParseAndMakeMemory();

    pstPDW = m_pTheGenPDW->GetMergedPDWData();

    for( i = 0; i < uiCoPDW; ++i ) {
        memset( pSIGAPDW, 0, sizeof( struct DMAPDW ) );

        randomFreq = pstPDW->GetFrequency();
        randomCh = pstPDW->GetChannel();

        m_tTOA = pstPDW->GetTOA();

#if defined(_POCKETSONATA_) || defined(_712_)
        pSIGAPDW->uPDW.stHwPdwDataRf.CwPulse = CEncode::EncodePulseType( pstPDW->GetPulsetype() );        // uiPDW_CW;
        pSIGAPDW->uPDW.stHwPdwDataRf.Pmop = 0;
        pSIGAPDW->uPDW.stHwPdwDataRf.Fmop = 0;
        pSIGAPDW->uPDW.stHwPdwDataRf.FalsePdw = 0;
        pSIGAPDW->uPDW.x.uniPdw_status.stPdw_status.fmop_dir = 1;
        pSIGAPDW->uPDW.x.uniPdw_status.stPdw_status.fmop_bw = 8000;

        pSIGAPDW->uPDW.x.uniPdw_dir_pa.stPdw_dir_pa.doa = pstPDW->GetAOA();
        pSIGAPDW->uPDW.x.uniPdw_dir_pa.stPdw_dir_pa.di = 0;
        pSIGAPDW->uPDW.x.uniPdw_dir_pa.stPdw_dir_pa.pa = pstPDW->GetPulseamplitude();

        pSIGAPDW->uPDW.x.uniPdw_pw_freq.stPdw_pw_freq.pulse_width = pstPDW->GetPulsewidth();
        pSIGAPDW->uPDW.x.uniPdw_pw_freq.stPdw_pw_freq.frequency_L = randomFreq & 0xFF;

        pSIGAPDW->uPDW.x.uniPdw_freq_toa.stPdw_freq_toa.frequency_H = ( randomFreq >> 8 ) & 0xFF;
        pSIGAPDW->uPDW.x.uniPdw_freq_toa.stPdw_freq_toa.pdw_phch = randomCh;
        pSIGAPDW->uPDW.x.uniPdw_freq_toa.stPdw_freq_toa.toa_L = m_tTOA & 0xFFFF;

        pSIGAPDW->uPDW.x.uniPdw_toa_edge.stPdw_toa_edge.toa_H = ( m_tTOA >> 16 );
        pSIGAPDW->uPDW.x.uniPdw_toa_edge.stPdw_toa_edge.edge = 1;

        pSIGAPDW->uPDW.x.uniPdw_index.stPdw_index.index = uiIndex;
#else
        int iCh;

        pSIGAPDW->iStat = pstPDW->GetPulsetype();

        pSIGAPDW->tTOA = pstPDW->GetTOA();
        pSIGAPDW->uiAOA = pstPDW->GetAOA();
        pSIGAPDW->uiFreq = pstPDW->GetFrequency();
        pSIGAPDW->uiPA = pstPDW->GetPulseamplitude();
        pSIGAPDW->uiPW = pstPDW->GetPulsewidth();

#endif

        ++pstPDW;

        ++m_uiIndex;
        ++ uiIndex;

        ++pSIGAPDW;
    }

#if defined(_POCKETSONATA_) || defined(_712_)


#else

#endif



#endif

    ++m_uiCoSim;
}

/**
 * @brief     GeneratePDWFile
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-09-08 08:52:21
 * @warning
 */
void CSignalCollect::GenerateDDRFile( bool bWrite )
{
#ifdef _MSC_VER
    unsigned int i;
    char buffer[200];

    CRawFile theRawFile;

    if( bWrite == true ) {
        SIGAPDW *pSIGAPDW = m_pSIGAPDW;

        unsigned int uiCoPDW = m_pUniHeader->GetTotalPDW();

        theRawFile.RawOpenFile( m_szDDRFile, O_CREAT | O_RDWR | O_TEXT );
        //theRawFile.RawOpenFile( m_szDDRFile, O_CREAT | O_RDWR | O_TEXT | O_APPEND );

        for( i = 0; i < uiCoPDW; ++i ) {
            int iCount;

            unsigned int uiFreq, uiPW, uiPA, uiPhase = 0;
            _TOA tTOA;

            float fFreq, fTOA, fPW, fPA;

            uiFreq = pSIGAPDW->GetFrequency();
            uiPW = pSIGAPDW->GetPulsewidth();
            uiPA = pSIGAPDW->GetPulseamplitude();
            tTOA = pSIGAPDW->GetTOA();

            fTOA = (float) CPOCKETSONATAPDW::DecodeTOAus( tTOA );
            fFreq = CPOCKETSONATAPDW::DecodeFREQMHz( uiFreq );
            fPW = CPOCKETSONATAPDW::DecodePWus( (int) uiPW );
            fPA = CPOCKETSONATAPDW::DecodePA( (int) uiPA ) + (float) g_stRadarPDW.iDDROffset;

#ifdef _MSC_VER
            iCount = sprintf_s( buffer, 200, "%f\t%f\t%f\t%d\t%f\n", fTOA, fFreq, fPW, uiPhase, fPA );

#else
            iCount = sprintf( buffer, "%f\t%f\t%f\t%d\t%f\n", fTOA, fFreq, fPW, uiPhase, fPA );

#endif

            theRawFile.Write( buffer, (unsigned int) iCount );

            ++ pSIGAPDW;
        }

        theRawFile.CloseFile();

    }
#endif

}

/**
 * @brief     MakeSIMPA
 * @param     int iRandomIndex
 * @return    unsigned int
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-08-11 10:06:21
 * @warning
 */
unsigned int CSignalCollect::MakeSIMPA( int iRandomIndex )
{
    // int iDwell=50, iValue, iSlope, iDiv;

    unsigned int randomPA=0;

    float fPA;
    double dScanPrd;

    EN_CHECKLOBE enLobe;

    ///////////////////////////////////////////////////////////////////////////////////
    //
    switch( m_stRadarPDW.enScanType ) {
        case ENUM_AET_SCAN_TYPE::E_AET_SCAN_BI_DIRECTIONAL:
        case ENUM_AET_SCAN_TYPE::E_AET_SCAN_UNI_DIRECTIONAL:
        case ENUM_AET_SCAN_TYPE::E_AET_SCAN_CIRCULAR :
            enLobe = CheckLobe();
            switch( enLobe ) {
                case EN_MAINLOBE :

#if 0
                    dScanPrd = ( double ) ITOAusCNV( ( float ) m_uiMainLobeDuration );
                    fPA = ( float ) ( 20. * sin( ( ( 2. * M_PI ) / dScanPrd ) * m_tTOA ) );
                    fPA = fabs( fPA ) - 50;
#else
                    fPA = ( UCHAR ) ( sin( m_iMainLobe * M_PI / m_stRadarPDW.uiCoPulsePerLobe ) * m_stRadarPDW.iAmplitude + 0.5 );
                    fPA = fabs( fPA ) - 50;

#endif

//                     ScanPrd = ( UINT ) ( ScanPrd * ONE_MILLISEC - ( PRI * SPul_Cnt ) );
//                     for( i = 0; i < SPul_Cnt; i++ ) {
//                         pa_array[i] = ( UCHAR ) ( sin( i * PIE / SPul_Cnt ) * PA + 0.5 );
//                     }

                    randomPA = CPOCKETSONATAPDW::EncodePA( fPA );

                    ++ m_iMainLobe;
                    break;

#if 0
                case EN_SIDELOBE:
                    m_iMainLobe = 0;
                    randomPA = CPOCKETSONATAPDW::EncodePA( CCommonUtils::Random( ( float ) 300 - 2, ( float ) 300 + 2 ) );
                    break;
#endif

                case EN_NOISEOBE:
                    m_iMainLobe = 0;
                    randomPA = CPOCKETSONATAPDW::EncodePA( CCommonUtils::Random( ( float ) 10 - 2, ( float ) 10 + 2 ) );

                    m_iMissingPercent = -1;
                    break;

                default:
                    break;

            }

            break;

        case ENUM_AET_SCAN_TYPE::E_AET_SCAN_CONICAL:
            dScanPrd = (double) ITOAusCNV( (float) ( m_stRadarPDW.fScanPeriod * (float) 1000. ) );
            fPA = ( float ) ( 10. * sin( ( ( 2. * M_PI ) / dScanPrd ) * m_tTOA ) ) + (float) m_stRadarPDW.iSignalIntensity;
            randomPA = CPOCKETSONATAPDW::EncodePA( fPA );
            break;

        case ENUM_AET_SCAN_TYPE::E_AET_SCAN_STEADY:
            randomPA = CPOCKETSONATAPDW::EncodePA( CCommonUtils::Random( ( float ) m_stRadarPDW.iSignalIntensity - 2, ( float ) m_stRadarPDW.iSignalIntensity + 2 ) );
            break;

        default:
            break;

    }

    return randomPA;

}

/**
 * @brief     CheckLobe
 * @return    EN_CHECKLOBE
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-08-17 12:26:16
 * @warning
 */
EN_CHECKLOBE CSignalCollect::CheckLobe()
{
    EN_CHECKLOBE enLobe= EN_MAINLOBE;

    _TOA tModular;
    UINT uiMainLobeDuration;

    if( m_stRadarPDW.enScanType == ENUM_AET_SCAN_TYPE::E_AET_SCAN_CIRCULAR || m_stRadarPDW.enScanType == ENUM_AET_SCAN_TYPE::E_AET_SCAN_UNI_DIRECTIONAL ) {
        //tModular = ( m_tTOA - m_tFirstTOA );
        tModular = m_tTOA;
        tModular = (_TOA) CPOCKETSONATAPDW::DecodeTOAus( tModular );

        tModular = TModular<_TOA>( tModular, ( _TOA ) ( m_stRadarPDW.fScanPeriod * (float) 1000000 ) );
        //tModular = tModular % (_TOA) ( m_stRadarPDW.uiScanPeriod * 1000 );

        uiMainLobeDuration = m_uiMainLobeDuration / 2;

        if( TCompMarginDiff<_TOA>( tModular, ( m_uiStartDuration - uiMainLobeDuration ), ( m_uiStartDuration + uiMainLobeDuration ), 0 ) == true ) {
            //TRACE( "\n TOA[%lu, %.2f], 1stTOA[%lu], mod[%u]", m_tTOA, FDIV( m_tTOA, _spOneSec ), m_tFirstTOA, ( UINT ) ( m_tTOA - m_tFirstTOA ) );
            enLobe = EN_MAINLOBE;
        }
        else {
            enLobe = EN_NOISEOBE;
        }
    }

    return enLobe;

}

/**
 * @brief     MakeSIMFreq
 * @param     int iRandomIndex
 * @return    unsigned int
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-08-11 10:05:48
 * @warning
 */
unsigned int CSignalCollect::MakeSIMFreq( int iRandomIndex )
{
    int iValue, iSlope, iDiv, iDividen;
    float fSlope, fFreqPulsePerLobe, fModular;
    int iFreqPulsePerLobeDiv2, iFreqPulsePerLobe;

    unsigned int randomFreq=0;

    ///////////////////////////////////////////////////////////////////////////////////
    //
    switch( m_stRadarPDW.enFreqType ) {
        case ENUM_AET_FRQ_TYPE::E_AET_FRQ_FIXED:
            // 주파수 고정일 일때
            CPOCKETSONATAPDW::EncodeRealFREQMHz( ( int * ) &randomFreq, CCommonUtils::Random( ( float ) m_stRadarPDW.fFreq - 2, ( float ) m_stRadarPDW.fFreq + 2 ) );
            break;

        case ENUM_AET_FRQ_TYPE::E_AET_FRQ_HOPPING:
            //iDwell = 30;
            //iStep = m_stRadarPDW.uiCoFreqHoopingPositions;

            if( m_stRadarPDW.iFreqPulsePerLobe != 0 ) {
                if( m_stRadarPDW.iCoFreqHoopingPositions == 6 ) {
                    // iValue = (int) ( ( int ) m_uiIndex + iRandomIndex ) % ( m_stRadarPDW.iFreqPulsePerLobe * ( int ) m_stRadarPDW.iCoFreqHoopingPositions );
                    iValue = ( int ) TModular<int>( ( ( int ) m_uiIndex + iRandomIndex ), ( m_stRadarPDW.iFreqPulsePerLobe * ( int ) m_stRadarPDW.iCoFreqHoopingPositions ) );

                    iDiv = iValue / m_stRadarPDW.iFreqPulsePerLobe;
                    CPOCKETSONATAPDW::EncodeRealFREQMHz( ( int * ) &randomFreq, ( float ) ( 1000.0 + ( (int) 10 * iDiv ) ) );
                }
                else {
                    // 스태거 32단 엘리먼트 값 정의
                    float fHoppingPositions[32] = { 5500, 5700, 5900, 6100, 5300, 6400, 6200, 6400, \
                                                    6500, 5700, 5800, 6300, 5300, 6200, 6500, 5500, \
                                                    6500, 5700, 6100, 6400, 5300, 6100, 6400, 6500, \
                                                    6400, 5900, 6300, 6400, 5100, 6200, 6500, 6300 };

                    iDividen = m_stRadarPDW.iFreqPulsePerLobe * ( int ) m_stRadarPDW.iCoFreqHoopingPositions;
                    if( iDividen != 0 ) {
                        iValue = ( ( int ) m_uiIndex + iRandomIndex ) % ( m_stRadarPDW.iFreqPulsePerLobe * (int) m_stRadarPDW.iCoFreqHoopingPositions );
                    }
                    else {
                        iValue = 0;
                    }
                    iDiv = iValue / m_stRadarPDW.iFreqPulsePerLobe;
                    CPOCKETSONATAPDW::EncodeRealFREQMHz( ( int * ) &randomFreq, fHoppingPositions[iDiv] );
                }
            }

            break;

        case ENUM_AET_FRQ_TYPE::E_AET_FRQ_AGILE:
            // 주파수 어자일 일때
            CPOCKETSONATAPDW::EncodeRealFREQMHz( ( int * ) &randomFreq, ( float ) m_stRadarPDW.fFreq + ( float ) ( CCommonUtils::Random( ( float ) -m_stRadarPDW.iFreqBW, ( float ) m_stRadarPDW.iFreqBW ) ) );
            break;

        case ENUM_AET_FRQ_TYPE::E_AET_FRQ_PATTERN:
            //iDwell = 20;
            iSlope = 2;

            if( m_stRadarPDW.enFreqPatternType == ENUM_AET_FREQ_PRI_PATTERN_TYPE::E_AET_FREQ_PRI_SLIDE_INC && m_stRadarPDW.iFreqPulsePerLobe != 0 ) {
                randomFreq = ( UINT ) ( 1300. + ( ( int ) m_uiIndex % m_stRadarPDW.iFreqPulsePerLobe ) * iSlope );
            }
            else if( m_stRadarPDW.enFreqPatternType == ENUM_AET_FREQ_PRI_PATTERN_TYPE::E_AET_FREQ_PRI_SLIDE_DEC && m_stRadarPDW.iFreqPulsePerLobe != 0 ) {
                randomFreq = ( UINT ) ( 4800. - ( ( int ) m_uiIndex % m_stRadarPDW.iFreqPulsePerLobe ) * iSlope );
            }
            else if( m_stRadarPDW.enFreqPatternType == ENUM_AET_FREQ_PRI_PATTERN_TYPE::E_AET_FREQ_PRI_SAW_TRI ) {
                //iDwell = 30;
                //iSlope = 4;
                fFreqPulsePerLobe = FDIV( (float) 1000. * m_stRadarPDW.fFreqPeriod, m_stRadarPDW.fPRI );
                fSlope = FDIV( 4*m_stRadarPDW.iFreqBW, fFreqPulsePerLobe - 1 );
                iFreqPulsePerLobeDiv2 = IDIV( fFreqPulsePerLobe, 2 );
                iFreqPulsePerLobe = iFreqPulsePerLobeDiv2 * 2;

                if( ( iFreqPulsePerLobe != 0 ) && ( ( int ) m_uiIndex % iFreqPulsePerLobe ) / iFreqPulsePerLobeDiv2 ) {
                    randomFreq = ( UINT ) ( m_stRadarPDW.fFreq + ( ( int ) m_uiIndex % iFreqPulsePerLobeDiv2 ) * fSlope );
                }
                else {
                    //randomFreq = ( UINT ) ( ( m_stRadarPDW.fFreq + ( (float) iFreqPulsePerLobeDiv2 * fSlope ) ) - ( ( int ) m_uiIndex % iFreqPulsePerLobeDiv2 ) * fSlope );
                    int iModular = TModular<int>( ( int ) m_uiIndex, iFreqPulsePerLobeDiv2 );
                    randomFreq = ( UINT ) ( ( m_stRadarPDW.fFreq + ( ( float ) iFreqPulsePerLobeDiv2 * fSlope ) ) - ( (float) iModular * fSlope ) );
                }
                randomFreq -= (unsigned int) m_stRadarPDW.iFreqBW;

            }
            else {
                // 주파수 패턴(SINE 형)
                float fAmplitude, fPulsePerGroup;

                fAmplitude = ( float ) m_stRadarPDW.iFreqBW;
                fPulsePerGroup = FDIV( ( float ) 1000. * m_stRadarPDW.fFreqPeriod, m_stRadarPDW.fPRI );

                //fModular = ( float ) fmod( (float) ( m_tTOA - m_tFirstTOA), ( float ) ( CPOCKETSONATAPDW::EncodeTOAms( ( float ) ( m_stRadarPDW.fFreqPeriod ) ) ) );
                //fModular = fModular / ( float ) ( CPOCKETSONATAPDW::EncodeTOAms( ( float ) ( m_stRadarPDW.fFreqPeriod ) ) );
                fModular = ( float ) fmod( m_uiIndex, fPulsePerGroup );
                fModular = FDIV( fModular, fPulsePerGroup );
                randomFreq = ( UINT ) ( fAmplitude * sin( ( 2. * M_PI * fModular ) ) + m_stRadarPDW.fFreq );
            }

            CPOCKETSONATAPDW::EncodeRealFREQMHz( ( int * ) &randomFreq, ( float ) randomFreq );
            break;

        default:
            break;

    }

    return randomFreq;

}

/**
 * @brief     MakeSIMPRI
 * @param     int iRandomIndex
 * @return    _TOA
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-08-17 14:10:54
 * @warning
 */
_TOA CSignalCollect::MakeSIMPRI( int iRandomIndex )
{
    _TOA tTOA=0, tempTOA;

    float fAmplitude;

    unsigned int uiModuler;
    unsigned int uiSlope, uiValue, uiDiv;

    if( m_stRadarPDW.enScanType == ENUM_AET_SCAN_TYPE::E_AET_SCAN_CONICAL && m_stRadarPDW.fScanPeriod > (float) 500. ) {
        tTOA = CPOCKETSONATAPDW::EncodeTOAus( CCommonUtils::Random( ( float ) 19998., ( float ) 20002. ) );
    }
    else {
        float fPRIRange, fModular;

        switch( m_stRadarPDW.enPRIType ) {
            case ENUM_AET_PRI_TYPE::E_AET_PRI_FIXED:
                // Stable PRI 일때
                tTOA = CPOCKETSONATAPDW::EncodeTOAus( m_stRadarPDW.fPRI + CCommonUtils::Random( ( float ) -1., ( float ) 1. ) );
                break;

            case ENUM_AET_PRI_TYPE::E_AET_PRI_JITTER:
                // Jitter PRI 일때
                fPRIRange = ( float ) ( m_stRadarPDW.fPRI * ( m_stRadarPDW.iJitterRatio / 200. ) );
                tTOA = CPOCKETSONATAPDW::EncodeTOAus( m_stRadarPDW.fPRI + CCommonUtils::Random( -fPRIRange, fPRIRange ) );
                break;

            case ENUM_AET_PRI_TYPE::E_AET_PRI_DWELL_SWITCH:
                //uiDwell = 10;

                if( m_stRadarPDW.iCoPRIDwellStaggerPositions == 32 ) {
                    // 스태거 32단 엘리먼트 값 정의
                    float fDwellPositions[32] = { 180, 195, 210, 190, 180, 210, 220, 210, \
                                                  190, 210, 195, 180, 210, 220, 190, 180, \
                                                  215, 175, 190, 180, 200, 210, 180, 170, \
                                                  185, 210, 180, 210, 180, 210, 190, 210 };

                    if( m_stRadarPDW.iPRIPulsePerLobe != 0 ) {
                        uiValue = TModular<unsigned int>( ( ( m_uiIndex / m_stRadarPDW.iPRIPulsePerLobe ) + ( unsigned int ) iRandomIndex ), ( m_stRadarPDW.iCoPRIDwellStaggerPositions ) );
                    }
                    else {
                        uiValue = 0;
                    }
                    //uiValue = ( ( unsigned int ) ( ( m_uiIndex / uiDwell ) + iRandomIndex ) % ( m_stRadarPDW.uiCoPRIDwellStaggerPositions ) );
                    tTOA = CPOCKETSONATAPDW::EncodeTOAus( ( float ) fDwellPositions[uiValue] );
                }
                else {
                    uiValue = TModular< unsigned int >( ( m_uiIndex + ( unsigned int ) iRandomIndex ), (unsigned int) ( m_stRadarPDW.iPRIPulsePerLobe * m_stRadarPDW.iCoPRIDwellStaggerPositions ) );
                    //uiValue = ( unsigned int ) ( ( m_uiIndex + ( unsigned int ) iRandomIndex ) % ( uiDwell * m_stRadarPDW.uiCoPRIDwellStaggerPositions ) );
                    if( m_stRadarPDW.iPRIPulsePerLobe != 0 ) {
                        uiDiv = uiValue / m_stRadarPDW.iPRIPulsePerLobe;
                    }
                    else {
                        uiDiv = 0;
                    }
                    tTOA = CPOCKETSONATAPDW::EncodeTOAus( ( float ) ( 100.0 + ( 10 * uiDiv ) ) );

                }
                break;

            case ENUM_AET_PRI_TYPE::E_AET_PRI_STAGGER:
                // Stagger PRI 일때
                uiModuler = TModular<unsigned int>( m_uiIndex, m_stRadarPDW.iCoPRIDwellStaggerPositions );
                tTOA = CPOCKETSONATAPDW::EncodeTOAus( m_stRadarPDW.fStaggerPositions[uiModuler] );
                break;

            case ENUM_AET_PRI_TYPE::E_AET_PRI_PATTERN:
                //uiDwell = 40;

                // 패턴 PRI 일때
                if( m_stRadarPDW.enPRIPatternType == ENUM_AET_FREQ_PRI_PATTERN_TYPE::E_AET_FREQ_PRI_SLIDE_INC ) {
                    uiSlope = 800;
                    tempTOA = ( UINT ) ( 110000. + ( m_uiIndex % m_stRadarPDW.iPRIPulsePerLobe ) * uiSlope );
                }
                else if( m_stRadarPDW.enPRIPatternType == ENUM_AET_FREQ_PRI_PATTERN_TYPE::E_AET_FREQ_PRI_SLIDE_DEC ) {
                    uiSlope = 800;
                    tempTOA = ( UINT ) ( 150000. - ( m_uiIndex % m_stRadarPDW.iPRIPulsePerLobe ) * uiSlope );
                }
                else if( m_stRadarPDW.enPRIPatternType == ENUM_AET_FREQ_PRI_PATTERN_TYPE::E_AET_FREQ_PRI_SAW_TRI ) {
                    uiSlope = 800;
                    if( ( m_uiIndex % m_stRadarPDW.iPRIPulsePerLobe ) / ( m_stRadarPDW.iPRIPulsePerLobe / 2 ) ) {
                        tempTOA = ( UINT ) ( 100000. + ( m_uiIndex % ( m_stRadarPDW.iPRIPulsePerLobe / 2 ) ) * uiSlope );
                    }
                    else {
                        tempTOA = ( UINT ) ( ( 100000. + ( ( m_stRadarPDW.iPRIPulsePerLobe / 2 ) * uiSlope ) ) - ( m_uiIndex % ( m_stRadarPDW.iPRIPulsePerLobe / 2 ) ) * uiSlope );
                    }
                }
                else {
                    float fPulsePerGroup;
                    fAmplitude = m_stRadarPDW.fPRI * FDIV( m_stRadarPDW.iJitterRatio, 100 );
                    fPulsePerGroup = FDIV( (float) 1000. * m_stRadarPDW.fPRIPeriod,  m_stRadarPDW.fPRI );
                    fModular = (float) fmod( m_uiIndex, fPulsePerGroup );
                    fModular = FDIV( fModular, fPulsePerGroup );
                    tempTOA = (UINT) ( ( ( fAmplitude * sin( 2. * M_PI * fModular ) ) + m_stRadarPDW.fPRI ) + 0.5 );
                }

                tTOA = CPOCKETSONATAPDW::EncodeTOAus( (float) tempTOA );
                //tTOA = tempTOA;
                break;

            default:
                m_iMissingPercent = 5;
                tTOA = 0;
                break;
        }
    }

    return tTOA;

}

/**
 * @brief     SimFilter
 * @param     STR_PDWDATA * pPDWData
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2021-06-30, 18:27
 * @warning
 */
void CSignalCollect::SimFilter( STR_PDWDATA *pPDWData, ENUM_PCI_DRIVER enPCIDriver )
{
    CCollectBank *pTheCollectBank = GetCollectBank( enPCIDriver );

    pTheCollectBank->SimFilter( pPDWData, enPCIDriver == enLEFT_PCI_DRIVER );

    return;

}

/**
 * @brief     PDW 데이터를 모의 발생한다.
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-11-10 15:45:01
 * @warning
 */
void CSignalCollect::SimPDWData()
{
    STR_PDWDATA *pstPDWData;

    unsigned int uiTotalPDW = m_pUniHeader->GetTotalPDW();

    if( uiTotalPDW != 0 ) {
        // 랜 데이터를 갖고온다.
        if( GetRecvData() != NULL ) {
            memcpy( m_uniLanData.szFile, GetRecvData(), m_pMsg->uiArrayLength );
        }
        else {
            memcpy( m_uniLanData.szFile, m_pstrPDWWithFileHeader, sizeof( union UNION_HEADER ) + uiTotalPDW * sizeof( SIGAPDW ) );

        }

        // 데이터를 지정하여 지정한 행렬에 저장한다.
        //pPDWData = m_pTheDetectCollectBank[0]->GetPDW();

#if defined(_POCKETSONATA_) || defined(_712_)
        m_theDataFile.ReadDataMemory( ( char * ) m_uniLanData.szFile, PDW_EXT, NULL, enUnitToPDW );
#elif defined(_XBAND_)
        m_theDataFile.ReadDataMemory( ( char * ) m_uniLanData.szFile, PDW_EXT, NULL, enPDWToPDW );
#else
        m_theDataFile.ReadDataMemory( ( char * ) m_uniLanData.szFile, PDW_EXT, NULL, enUnitToPDW );
#endif

        // 추적/스캔/사용자 채널을 모의하여 해당 CCollectBank 객체에 저장한다.
        pstPDWData = m_theDataFile.GetPDWData();
        SimFilter( pstPDWData, enLEFT_PCI_DRIVER );
        SimFilter( pstPDWData, enRIGHT_PCI_DRIVER );

        // 모의 PDW 데이터를 수집 버퍼에 추가한다.
        //pCollectBank = GetCollectBank( uiCh );
        //pCollectBank->PushPDWData( pPDWData );

        //_SAFE_DELETE( m_theDataFile.m_pData )
    }

}

/**
 * @brief     CheckDetectCollectBank
 * @param     ENUM_PCI_DRIVER enPCIDriver
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-03-14 12:09:19
 * @warning
 */
void CSignalCollect::CheckDetectCollectBank( ENUM_PCI_DRIVER enPCIDriver )
{
    int iCh = CheckCollectBank( enDetectCollectBank, enPCIDriver );
    if( iCh >= 0 ) {
        unsigned int uiTotalPDW;

        CCollectBank *pTheCollectBank = GetCollectBank( enPCIDriver );
        uiTotalPDW = pTheCollectBank->GetTotalPDW( (unsigned int) iCh );
        CloseDetectChannel( (unsigned int) iCh, enPCIDriver, uiTotalPDW );
    }
}

/**
 * @brief     CheckScanCollectBank
 * @param     ENUM_PCI_DRIVER enPCIDriver
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-03-17 15:34:57
 * @warning
 */
void CSignalCollect::CheckScanCollectBank( ENUM_PCI_DRIVER enPCIDriver )
{
    int iCh = CheckCollectBank( enScanCollectBank, enPCIDriver );
    if( iCh >= 0 ) {
        unsigned int uiTotalPDW;

        CCollectBank *pTheCollectBank = GetCollectBank( enPCIDriver );
        uiTotalPDW = pTheCollectBank->GetTotalPDW( ( unsigned int ) iCh );
        CloseScanChannel( (unsigned int) iCh, enPCIDriver, uiTotalPDW );
    }
}

/**
 * @brief     CheckAllCollectBank
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-03-29, 10:36
 * @warning
 */
void CSignalCollect::CheckAllCollectBank()
{
    int iCh;

    unsigned int uiGetMinAnalPulse = 0;

    //size_t szSize;

    //CCollectBank *pCollectBank;

    //STR_COLLECT_INFO strCollectInfo;

    //ENUM_PCI_DRIVER enPCIDriver;

    // 탐지 채널 버퍼 체크
    CheckDetectCollectBank( enLEFT_PCI_DRIVER );
    CheckDetectCollectBank( enRIGHT_PCI_DRIVER );

    // 추적 채널 버퍼 체크
    iCh = CheckCollectBank( enTrackCollectBank, enLEFT_PCI_DRIVER );
    if( iCh >= 0 ) {
        //int iMaxCh;

//         pCollectBank = GetCollectBank( iCh );
//
//         //iMaxCh = _max( iCh - DETECT_CHANNEL, _spZero );
//         uiIndex = (unsigned int) max( (int)( iCh - CO_DETECT_CHANNEL), _spZero);
//
//         strCollectInfo.uiTotalPDW = pCollectBank->GetTotalPDW();
//         strCollectInfo.iCh = iCh;
//         strCollectInfo.uiAETID = m_ABTData[uiIndex].uiAETID;
//         strCollectInfo.uiABTID = m_ABTData[uiIndex].uiABTID;
//
//         MakeStaticPDWData( pCollectBank->GetPDWData(), true );
// 		szSize = sizeof(union UNION_HEADER) + sizeof(_PDW) * m_stPDWData.GetTotalPDW();
//         memcpy( & m_theTrkScnPDW.strPDW, & m_stPDWData, szSize ); // sizeof(struct STR_STATIC_PDWDATA) );
//         memcpy( & m_theTrkScnPDW.strABTData, GetABTData(uiIndex), sizeof(struct SRxABTData) );
//
//         if( strCollectInfo.uiTotalPDW >= _spAnalMinPulseCount ) {
//             g_pTheTrackAnalysis->QMsgSnd( enTHREAD_KNOWNANAL_START, & m_theTrkScnPDW, sizeof(struct STR_TRKSCNPDWDATA), & strCollectInfo, sizeof(STR_COLLECTINFO), GetThreadName() );
//         }
//         // PDW 펄스 개수 부족시 위협 처리로 바로 전달
//         else {
//             g_pTheEmitterMerge->QMsgSnd( enTHREAD_KNOWNANAL_FAIL, & m_theTrkScnPDW, sizeof(struct STR_TRKSCNPDWDATA), & strCollectInfo, sizeof(STR_COLLECTINFO), GetThreadName() );
//         }
//
    }

    // 스캔 채널 버퍼 체크
    CheckScanCollectBank( enLEFT_PCI_DRIVER );
    CheckScanCollectBank( enRIGHT_PCI_DRIVER );

    //iCh = CheckCollectBank( enScanCollectBank, enLEFT_PCI_DRIVER );
    //if( iCh >= 0 ) {
//         pCollectBank = GetCollectBank( iCh );
//         uiIndex = ( unsigned int ) max( iCh - CO_DETECT_CHANNEL - CO_TRACK_CHANNEL, _spZero );
//
//         strCollectInfo.uiTotalPDW = pCollectBank->GetTotalPDW();
//         strCollectInfo.uiCh = (unsigned int) iCh;
//         strCollectInfo.uiAETID = m_ABTData[uiIndex].uiAETID;
//         strCollectInfo.uiABTID = m_ABTData[uiIndex].uiABTID;
//
//         MakeStaticPDWData( pCollectBank->GetPDWData(), true );
//         szSize = sizeof(union UNION_HEADER) + sizeof(_PDW) * m_stPDWData.GetTotalPDW();
//         memcpy( & m_theTrkScnPDW.strPDW, & m_stPDWData, szSize ); //sizeof(struct STR_STATIC_PDWDATA) );
//         memcpy( & m_theTrkScnPDW.strABTData, GetABTData(uiIndex), sizeof(struct SRxABTData) );
//
//         g_pTheScanAnalysis->QMsgSnd( enTHREAD_SCANANAL_START, & m_theTrkScnPDW, sizeof(struct STR_TRKSCNPDWDATA), & strCollectInfo, sizeof(STR_COLLECTINFO), GetThreadName() );
//    }

}

/**
 * @brief		뱅크에 저장된 상태를 검사하여 수집 완료된 채널을 리턴한다.
 * @param		ENUM_COLLECTBANK enCollectBank
 * @return		int
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2023/03/12 11:04:55
 * @warning
 */
int CSignalCollect::CheckCollectBank( ENUM_COLLECTBANK enCollectBank, ENUM_PCI_DRIVER enPCIDriver )
{
    int iCh;

    CCollectBank *pTheCollectBank = GetCollectBank( enPCIDriver );

    iCh = pTheCollectBank->CheckCollectBank( enCollectBank );

    return iCh;
}


#endif
