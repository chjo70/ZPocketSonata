// CSignalCollect.cpp: implementation of the CScanAnalysis class.
//
// 신호 수집 및 관리한다.
// 신규 데이터를 수집하기위한 수집 제어와 분석된 데이터를 기반으로 추적 수집 채널을 할당해서 추적 채널을 관리한다.
// 또한, 스캔 채널을 할당하여 스캔 수집을 하게 한다.
//////////////////////////////////////////////////////////////////////


#include "stdafx.h"


#include "../Anal/OFP_Main.h"

#include "csignalcollect.h"


#include "cdetectanalysis.h"
#include "cemittermerge.h"
#include "ctrackanalysis.h"
#include "cscananalysis.h"
#include "cusercollect.h"

#include "../Utils/csingleserver.h"
//#include "../Utils/cmultiserver.h"
#include "../Utils/ccommonutils.h"

#include "../System/csysconfig.h"

#include "../Include/globals.h"

#define _DEBUG_


/**
 * @brief CSignalCollect::CSignalCollect
 * @param iKeyId
 * @param pClassName
 */
#ifdef _MSSQL_
CSignalCollect::CSignalCollect( int iKeyId, const char *pClassName, bool bArrayLanData, const ENUM_PCI_DRIVER enPCIDriver ) : CThread( iKeyId, pClassName, bArrayLanData ), CMSSQL( & m_theMyODBC )
#else
CSignalCollect::CSignalCollect( int iKeyId, const char *pClassName, bool bArrayLanData, const ENUM_PCI_DRIVER enPCIDriver ) : CThread( iKeyId, pClassName, bArrayLanData )
#endif
{
    int i, iCh;

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

    InitSignalColletct();

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
 * @brief		Alloc
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
    m_pstrPDWWithFileHeader = ( char * ) malloc( sizeof( SIGAPDW ) * NUM_OF_PDW + sizeof( UNION_HEADER ) );

    m_pUniHeader = ( UNION_HEADER * ) &m_pstrPDWWithFileHeader[0];
    m_pSIGAPDW = ( SIGAPDW * ) &m_pstrPDWWithFileHeader[sizeof( UNION_HEADER )];
#endif

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
    LOGENTRY;

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
    LOGENTRY;

    m_pMsg = GetDataMessage();

#ifdef _MSC_VER
#else
    pthread_cleanup_push( TCleanUpHandler, NULL);
#endif

    // 사용자 수집 함수로 시작
    //g_pTheUserCollect->QMsgSnd( enTHREAD_REQ_COLSTART, GetThreadName() );

    while( m_bThreadLoop ) {
#ifdef _SIM_PDW_
        if( QMsgRcv( enTIMER, 500 ) == -1 ) {
#else
        if( QMsgRcv() == -1 ) {
#endif
            perror( "QMsgRcv" );
        }
        else {
            switch( m_pMsg->uiOpCode ) {
                case enREQ_OP_START:
                    // QMsgClear();
                    InitSignalColletct();
                    StartCollecting();
                    break;

                case enTHREAD_DISCONNECTED:
                case enREQ_OP_SHUTDOWN:
                    QMsgClear();
                    InitSignalColletct();
                    break;

				case enREQ_OP_RESTART:
					QMsgClear();
                    InitSignalColletct();
                    StartCollecting();
                    break;

                // 신호(탐지/추적/스캔) 수집 완료 처리
                case enTHREAD_REQ_COMPLETECOL :
                    CompleteCollecting();
                    break;

                case enTHREAD_REQ_SET_DETECTWINDOWCELL:
                    ReqDetectWindowCell();
                    break;

                case enTHREAD_REQ_SET_TRACKWINDOWCELL:
                    ReqTrackWindowCell();
                    break;

#ifdef _MSC_VER
#ifdef _SIM_PDW_
                case enTHREAD_TIMER :
                    MakeSIMPDWData();
                    SimPDWData();
                    CheckAllCollectBank();
                    break;

#endif

                //case enTHREAD_DETECTANAL_START :
				    //RoutineForSimPDW();
                    //break;

//                 case enTHREAD_REQ_SHUTDOWN:
//                     LOGMSG1( enDebug, "[%s] 를 종료 처리 합니다...", GetThreadName() );
//                     break;

#else
			    case enTHREAD_DETECTANAL_START:
				InitSignalColletct();
                    break;

                case enTHREAD_REQ_TRACK_COLSTOP:
                    WhereIs;
                    break;

                case enTHREAD_REQ_SCAN_COLSTOP:
                    WhereIs;
                    break;

#endif

			default:
				LOGMSG2( enError, "[%s]에서 잘못된 명령(0x%x)을 수신하였습니다 !!", GetThreadName(), m_pMsg->uiOpCode );
				break;
            }

            SendEchoMessage();

        }
    }

#ifdef _MSC_VER
#else
    pthread_cleanup_pop( 1 );
#endif

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
    unsigned int uiCh, uiTotalPDW;

    uiCh = ( unsigned int ) m_pMsg->x.strCollectInfo.uiCh;
    uiTotalPDW = m_pMsg->x.strCollectInfo.uiTotalPDW;

    LOGMSG3( enNormal, "[%s]에서 채널[%d], PDW[%d] 신호 수집 완료", GetThreadName(), uiCh, uiTotalPDW );

    if( uiCh < CO_DETECT_CHANNEL ) {
        CollectingDetectChannel( uiCh, m_pMsg->x.strCollectInfo.enPCIDriver );

    }
    else {

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
void CSignalCollect::CollectingDetectChannel( unsigned int uiCh, ENUM_PCI_DRIVER enPCIDriver )
{
    CCollectBank *pTheCollectBank = GetCollectBank( enPCIDriver );

    STR_COLLECTINFO strCollectInfo;

    unsigned int uiIndex, uiArrayLength, uiGetMinAnalPulse = 0;

    // pCollectBank = m_pTheDetectCollectBank[iCh];
    strCollectInfo.uiTotalPDW = pTheCollectBank->GetTotalPDW( uiCh );
    strCollectInfo.uiAETID = 0;
    strCollectInfo.uiABTID = 0;
    strCollectInfo.enPCIDriver = enPCIDriver;

    uiGetMinAnalPulse = g_pTheSysConfig->GetMinAnalPulse();

    pTheCollectBank->CloseCollectBank( uiCh );

    if( strCollectInfo.uiTotalPDW >= uiGetMinAnalPulse ) {
        strCollectInfo.uiCh = (int) uiCh;
        MakeStaticPDWData( pTheCollectBank->GetPDWData(uiCh), true );

        uiArrayLength = sizeof( UNION_HEADER ) + sizeof( _PDW ) * m_stPDWData.GetTotalPDW();
        g_pTheDetectAnalysis->QMsgSnd( enTHREAD_DETECTANAL_START, &m_stPDWData, uiArrayLength, &strCollectInfo, sizeof( STR_COLLECTINFO ), GetThreadName() );

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
    CCollectBank* pCollectBank;

    unsigned int uiCh;

    uiCh = (unsigned int) m_pMsg->x.strCollectInfo.uiCh;
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
void CSignalCollect::RoutineForSimPDW()
{

    InitSignalColletct();

#ifdef _MSC_VER
    while( m_bThreadLoop ) {
        if( QMsgRcv( enNO_WAIT ) > 0 ) {
            switch( m_pMsg->uiOpCode ) {
                case enTHREAD_REQ_SET_TRACKWINDOWCELL :
                    ReqTrackWindowCell();
                    break;

                case enTHREAD_REQ_CLOSE_TRACKWINDOWCELL :
                    CloseTrackWindowCell();
                    break;

                case enTHREAD_REQ_SET_SCANWINDOWCELL :
                    ReqScanWindowCell();
                    break;

                case enTHREAD_REQ_CLOSE_SCANWINDOWCELL :
                    CloseScanWindowCell();
                    break;

                case enTHREAD_REQ_SHUTDOWN :
                    LOGMSG1( enDebug, "[%s] 를 종료 처리 합니다...", GetThreadName() );
                    break;

//                 case enTHREAD_MODE :
//                     m_bThreadLoop = false;
//                     break;

                // 모의 명령 처리
                case enTHREAD_REQ_SIM_PDWDATA :
                    SimPDWData();
                    CheckAllCollectBank();
                    break;

                case enTHREAD_REQ_DETECT_COLSTOP:
                    GetPDWDataFromDetectChannel();
                    break;

                default:
                    LOGMSG2( enError, "[%s]에서 잘못된 명령(0x%x)을 수신하였습니다 !!", GetThreadName(), m_pMsg->uiOpCode );
                    break;

            }
        }

        // 신호 수집은 여기서 수행한다.
//         if( bRoutineForDetectAnal == true ) {
//             AnalysisStart();
//         }
    }
#endif

}

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
void CSignalCollect::InitSignalColletct()
{
    // 탐지/추적/스캔 윈도우 셀을 닫는다.
    CloseCollectBank();

#ifdef _SIM_PDW_
    m_uiCoSim = 0;
    m_ullTOA = 0;
    m_uiIndex = 0;

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
    Sleep( 4 );
#endif

    // 탐지 신호 수집을 시작합니다.
    m_pTheLeftCollectBank->StartCollecting();
    m_pTheRigtCollectBank->StartCollecting();

    // 탐지 신호 수집을 위해 수집 설정합니다.
    unsigned int uiCh;
    for( uiCh = 0; uiCh < ( unsigned int ) CO_DETECT_CHANNEL; ++uiCh ) {
        // 탐지 채널에 대해서 수집 설정 합니다.

        // 왼쪽 PCI 드라이버를 설정 합니다.
        StartDetectChannel( uiCh, enLEFT_PCI_DRIVER );

        // 우쪽 PCI 드라이버를 설정 합니다.
        StartDetectChannel( uiCh, enRIGHT_PCI_DRIVER );

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
    STR_WINDOWCELL *pWindowCell;

    CCollectBank *pTheCollectBank = GetCollectBank( enPCIDriver );

    // 해당 채널의 WindowCell 얻기
    pTheCollectBank->StartDetectChannel( uiCh );

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

    m_pTheLeftCollectBank->CloseCollectBanks();
    m_pTheRigtCollectBank->CloseCollectBanks();

}

/**
 * @brief 분석 시작을 처리한다.
 */
void CSignalCollect::AnalysisStart()
{
//     LOGENTRY;
//
//     int iCh;
//
//     bool bIsOut = true;
//
//     while( g_AnalLoop ) {
//         bIsOut = true;
//
//         CheckAllCollectBank();
//
//         // 사용자 채널 버퍼 체크
//         iCh = CheckCollectBank( enUserCollectBank );
//         if( iCh >= 0 ) {
//             //CCommonUtils::SendLan( enREQ_MODE, & iCh, sizeof(int) );
//             bIsOut = false;
//         }
//
// #ifdef __VXWORKS__
//         //usleep( 1000 );
// #elif _MSC_VER
//         // 이 쓰레드에서는 Sleep() 없이 코딩해야 UseCollect 쓰레드에 지연 없이 처리할 수 있음.
//         //Sleep( 10 );
// #else
        //usleep( 1000 );
// #endif
//         //printf( "." );
//         if( bIsOut == true ) {
//             break;
//         }
//     }

}

/**
 * @brief     ReqDetectWindowCell
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-03-13 15:01:30
 * @warning
 */
void CSignalCollect::ReqDetectWindowCell()
{
    LOGMSG2( enNormal, "[%s]에서 채널[%d] 신호 수집 재설정", GetThreadName(), m_pMsg->x.strCollectInfo.uiCh );

    CCollectBank *pTheCollectBank = GetCollectBank( m_pMsg->x.strCollectInfo.enPCIDriver );

    // 아래는 탐지 윈도우셀을 자동 재설정하도록 한다.
    pTheCollectBank->UpdateWindowCell( m_pMsg->x.strCollectInfo.uiCh, NULL );

    // 	SendEndCollect();
    StartDetectChannel( m_pMsg->x.strCollectInfo.uiCh, m_pMsg->x.strCollectInfo.enPCIDriver );

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
    if(  m_pMsg->x.strAnalInfo.uiCh == _spZero ) {
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
//     LOGMSG3( enDebug, "[%d]번, [%d]채널 에서 분석된 빔 번호[%d]의 윈도우 셀을 닫습니다." , m_pMsg->x.strAnalInfo.enBoardID, m_pMsg->x.strAnalInfo.iCh, m_pMsg->x.strAnalInfo.uiABTID );
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
    int iCh=CO_DETECT_CHANNEL;

    STR_WINDOWCELL strWindowCell;

    if( false && m_theTrackChannel.Pop( & iCh ) == true ) {
        //LOGMSG2( enDebug, "추적 [%d]채널에 탐지 분석된 빔 번호[%d]를 기반으로 윈도우 셀을 설정합니다.", m_pMsg->x.strAnalInfo.iCh, m_pMsg->x.strAnalInfo.uiABTID );
//
//         memcpy( & m_ABTData[iCh-CO_DETECT_CHANNEL], pABTData, sizeof(SRxABTData) );
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
//             LOGMSG2(enDebug, " 추적 채널 설정 성공 [%d]Ch for B[%d]", iCh, pABTData->uiABTID);
//         }
//         else {
//             LOGMSG2(enDebug, " 추적 채널 설정 실패 [%d]Ch for B[%d]", iCh, pABTData->uiABTID);
//         }
//
//
    }
    else {
        LOGMSG( enDebug, "추적 채널이 없어서 할당하지 못합니다. !!" );
    }

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

        memset( pstrWindowCell, 0, sizeof(STR_WINDOWCELL) );

        pstrWindowCell->uiABTID = pABTData->uiABTID;

        // 레이더모드 식별 경우에 식별 정보를 이용하여 주파수 및 펄스폭을 설정
        if( pRadarMode != NULL ) {
            pstrWindowCell->strFreq.iLow = I_IFRQMhzCNV( 0, pRadarMode->fRF_TypicalMin );
            pstrWindowCell->strFreq.iHgh = I_IFRQMhzCNV( 0, pRadarMode->fRF_TypicalMax );

            pstrWindowCell->strPW.iLow = IPWCNVLOW( pABTData->fPWMin );
            pstrWindowCell->strPW.iHgh = IPWCNVHGH( pABTData->fPWMax );

            fMinCollectTime = _max( pRadarMode->fScanPrimaryTypicalMax, pRadarMode->fScanSecondaryTypicalMax );
        }
        else {
            pstrWindowCell->strFreq.iLow = I_IFRQMhzCNV( g_enBoardId, pABTData->fFreqMin - 5 );
            pstrWindowCell->strFreq.iHgh = I_IFRQMhzCNV( g_enBoardId, pABTData->fFreqMax + 5 );

            pstrWindowCell->strPW.iLow = IPWCNVLOW( pABTData->fPWMin );
            pstrWindowCell->strPW.iHgh = IPWCNVHGH( pABTData->fPWMax );

#ifdef _XBAND_
            fMinCollectTime = (float) 10.0;
#else
            fMinCollectTime = pABTData->fMaxScanPeriod;
#endif
        }

        pstrWindowCell->strPA.iLow = 0;
        pstrWindowCell->strPA.iHgh = 0x7fffffff;

        pstrWindowCell->strAoa.iLow = (int) ( ( IAOACNV( pABTData->fDOAMin-10 ) + MAX_AOA ) % MAX_AOA );
        pstrWindowCell->strAoa.iHgh = (int) ( ( IAOACNV( pABTData->fDOAMax+10 ) + MAX_AOA ) % MAX_AOA );

        pstrWindowCell->uiCoCollectingPDW = 100; // (unsigned int)_min(KWN_COLLECT_PDW, 100);

        uiCollectTime = UADD( 5000, fMinCollectTime );
        pstrWindowCell->uiMaxCollectTimesec = UDIV( uiCollectTime, 1000 );
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
 * @brief CSignalCollect::ReqScanWindowCell
 */
void CSignalCollect::ReqScanWindowCell()
{
//     SRxABTData *pABTData = ( SRxABTData *) m_uniLanData.szFile;
//
//     // 랜 데이터를 갖고온다.
//     memcpy( m_uniLanData.szFile, GetRecvData(), m_pMsg->uiArrayLength );
//
//     //LOGMSG3( enDebug, " [%d] 대역, 스캔 [%d] 채널 에서 분석된 빔 번호[%d] 을 기반으로 윈도우 셀을 설정합니다." , m_pMsg->x.strAnalInfo.uiBand, m_pMsg->x.strAnalInfo.uiCh, m_pMsg->x.strAnalInfo.uiABTID );
//
//     // 빔 정보를 기반으로 추적 및 스캔 채널을 업데이트 한다.
//     if(  m_pMsg->x.strAnalInfo.iCh == _spZero ) {
//         NewScanWindowCell( pABTData );
//     }
//     // 스캔 채널 업데이트한다.
//     else {
//         UpdateScanWindowCell( pABTData );
//     }

}

/**
 * @brief CSignalCollect::CloseScanWindowCell
 */
void CSignalCollect::CloseScanWindowCell()
{

    // 랜 데이터를 갖고온다.
//     PopLanData( m_uniLanData.szFile, m_pMsg->iArrayIndex, m_pMsg->uiArrayLength );
//
//     LOGMSG3( enDebug, "D[%d] 대역, [%d] 채널 에서 분석된 빔 번호[%d]의 윈도우 셀을 닫습니다." , m_pMsg->x.strAnalInfo.enBoardID, m_pMsg->x.strAnalInfo.iCh, m_pMsg->x.strAnalInfo.uiABTID );
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
 * @brief		NewScanWindowCell
 * @param		SRxABTData * pABTData
 * @return		void
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2022/03/02 12:00:14
 * @warning
 */
void CSignalCollect::NewScanWindowCell( SRxABTData *pABTData )
{
//     int iCh=CO_TRACK_CHANNEL;
//
//     STR_WINDOWCELL strWindowCell;
//
//     if( m_theScanChannel.Pop( & iCh ) == true ) {
//         memcpy( & m_ABTData[iCh-CO_TRACK_CHANNEL], pABTData, sizeof(SRxABTData) );
//
//         CalScanWindowCell( & strWindowCell, pABTData );
//
//         CCollectBank *pCCollectBank = GetCollectBank( iCh );
//         if (pCCollectBank != NULL) {
//             pCCollectBank->UpdateWindowCell(&strWindowCell);
//         }
//
//         LOGMSG3( enDebug, " [%d] 대역, 스캔 [%d] 채널 에서 분석된 빔 번호[%d] 을 기반으로 윈도우 셀을 설정합니다." , m_pMsg->x.strAnalInfo.enBoardID, iCh, m_pMsg->x.strAnalInfo.uiABTID );
//         //LOGMSG2( enDebug, " 빔 번호[%d]를 스캔 [%d]채널에 설정 합니다." , pABTData->uiABTID, uiCh );
//     }
//     else {
//         LOGMSG( enDebug, "스캔 채널이 없습니다 !!"  );
//     }


}

/**
 * @brief		CalScanWindowCell
 * @param		STR_WINDOWCELL * pstrWindowCell
 * @param		SRxABTData * pABTData
 * @return		void
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2023/02/23 10:23:43
 * @warning
 */
void CSignalCollect::CalScanWindowCell( STR_WINDOWCELL *pstrWindowCell, SRxABTData *pABTData )
{
//     UINT uiCollectTime;
//
//     SRadarMode *pRadarMode;
//
//     float fMinCollectTime=0;
//
//     if( pstrWindowCell != NULL ) {
//         pRadarMode = m_pIdentifyAlg->GetRadarMode( pABTData->iRadarModeIndex );
//
//         memset( pstrWindowCell, 0, sizeof(STR_WINDOWCELL) );
//
//         pstrWindowCell->uiABTID = pABTData->uiABTID;
//
//         // 레이더모드 식별 경우에 식별 정보를 이용하여 주파수 및 펄스폭을 설정
//         if( pRadarMode != NULL ) {
//             pstrWindowCell->strFreq.iLow = I_IFRQMhzCNV( 0, pRadarMode->fRF_TypicalMin );
//             pstrWindowCell->strFreq.iHgh = I_IFRQMhzCNV( 0, pRadarMode->fRF_TypicalMax );
//
//             pstrWindowCell->strPW.iLow = IPWCNVLOW( pRadarMode->fPD_TypicalMin );
//             pstrWindowCell->strPW.iHgh = IPWCNVHGH( pRadarMode->fPD_TypicalMax );
//
//             fMinCollectTime = _max( pRadarMode->fScanPrimaryTypicalMax, pRadarMode->fScanSecondaryTypicalMax );
//         }
//         else {
//             pstrWindowCell->strFreq.iLow = I_IFRQMhzCNV( g_enBoardId, pABTData->fFreqMin );
//             pstrWindowCell->strFreq.iHgh = I_IFRQMhzCNV( g_enBoardId, pABTData->fFreqMax );
//
//             pstrWindowCell->strPW.iLow = IPWCNVLOW( pABTData->fPWMin );
//             pstrWindowCell->strPW.iHgh = IPWCNVHGH( pABTData->fPWMax );
//
// #ifndef _XBAND_
//             fMinCollectTime = pABTData->fMaxScanPeriod;
// #endif
//         }
//
//         pstrWindowCell->strAoa.iLow = (int) ( ( IAOACNV( pABTData->fDOAMin-10 ) + MAX_AOA ) % MAX_AOA );
//         pstrWindowCell->strAoa.iHgh = (int) ( ( IAOACNV( pABTData->fDOAMax+10 ) + MAX_AOA ) % MAX_AOA );
//
//         pstrWindowCell->uiCoCollectingPDW = 1000; //  _min(SCN_COLLECT_PDW, 1000);
//
//         uiCollectTime = UADD( 5000, fMinCollectTime );
//         pstrWindowCell->uiMaxCollectTimesec = UDIV( uiCollectTime, 1000 );
//         pstrWindowCell->uiMaxCollectTimems = uiCollectTime % 1000;
//
//     }
//     else {
//
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
void CSignalCollect::MakeStaticPDWData( STR_PDWDATA *pPDWData, bool bAutoIncPDWID )
{
    unsigned int uiTotalPDW;

    if( bAutoIncPDWID == true ) {
        ++m_uiPDWID;
        pPDWData->SetPDWID( m_uiPDWID );
    }

    // 헤더 복사
    memcpy( & m_stPDWData.x, & pPDWData->x, sizeof(UNION_HEADER) );

    // 데이터 복사
    uiTotalPDW = pPDWData->GetTotalPDW();

    memcpy( & m_stPDWData.stPDW[0], pPDWData->pstPDW, sizeof( _PDW )*uiTotalPDW );

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
    unsigned int i, uiCoPDW;

    float fRandomDOA;

    int iDOA;
    int iRandomDOA;
    unsigned int uiRandomDOA, uiRandomPA, uiRandomPW, randomFreq, randomCh;

    STR_PDWDATA *pPDWData;
    _PDW *pstPDW;

    SIGAPDW *pSIGAPDW = m_pSIGAPDW;

    memset( m_pUniHeader, 0, sizeof( UNION_HEADER ) );

    m_pUniHeader->SetBoardID( g_enUnitType, ( UINT ) g_enBoardId );

    m_pUniHeader->SetColTime( time( NULL ), 0 );
    //m_pUniHeader->SetTotalPDW( NUM_OF_PDW );
    m_pUniHeader->SetIsStorePDW( 1 );
    m_pUniHeader->SetBandWidth( 1 );
    m_pUniHeader->SetCollectorID( RADARCOL_1 );

    m_pUniHeader->SetBoardID( ( unsigned int ) g_enBoardId );
    m_pUniHeader->SetBand( ( unsigned int ) g_enBoardId );

    char *pTaskID = m_pUniHeader->GetTaskID( g_enUnitType );
    if( pTaskID != NULL ) {
        strcpy( pTaskID, "MSIGA" );
    }

    //if ((m_uiCoSim % 20) <= 5) {
    if( ( m_uiCoSim % 10 ) <= 3 ) {
        uiCoPDW = 0;
    }
    else {
        uiCoPDW = NUM_OF_PDW;
    }

    uiCoPDW = 5;

#ifdef __VXWORKS__
    uiCoPDW = 0;

#endif

    m_pUniHeader->SetTotalPDW( uiCoPDW );

    int iBandWidth = m_pUniHeader->GetBandWidth();

#ifdef _SIM_PDW_
#if defined(_POCKETSONATA_)
#define MANUALTOA   (35)

    _TOA manualTOA[MANUALTOA] = { CPOCKETSONATAPDW::EncodeTOAus( ( float ) 1598.41 ),
                                  CPOCKETSONATAPDW::EncodeTOAus( ( float ) 2986.972 ),
                                  CPOCKETSONATAPDW::EncodeTOAus( ( float ) 4359.585 ),
                                  CPOCKETSONATAPDW::EncodeTOAus( ( float ) 5746.258 ),
                                  CPOCKETSONATAPDW::EncodeTOAus( ( float ) 7022.91 ),
                                  CPOCKETSONATAPDW::EncodeTOAus( ( float ) 8270.053 ),
                                  CPOCKETSONATAPDW::EncodeTOAus( ( float ) 9516.386 ),
                                  CPOCKETSONATAPDW::EncodeTOAus( ( float ) 10763.56 ),
                                  CPOCKETSONATAPDW::EncodeTOAus( ( float ) 12010.74 ),
                                  CPOCKETSONATAPDW::EncodeTOAus( ( float ) 13362.59 ),
                                  CPOCKETSONATAPDW::EncodeTOAus( ( float ) 16424.9 ),
                                  CPOCKETSONATAPDW::EncodeTOAus( ( float ) 17956.39 ),
                                  CPOCKETSONATAPDW::EncodeTOAus( ( float ) 21018.86 ),
                                  CPOCKETSONATAPDW::EncodeTOAus( ( float ) 22410.07 ),
                                  CPOCKETSONATAPDW::EncodeTOAus( ( float ) 23801.04 ),
                                  CPOCKETSONATAPDW::EncodeTOAus( ( float ) 25192.14 ),
                                  CPOCKETSONATAPDW::EncodeTOAus( ( float ) 26582.81 ),
                                  CPOCKETSONATAPDW::EncodeTOAus( ( float ) 29115.85 ),
                                  CPOCKETSONATAPDW::EncodeTOAus( ( float ) 30362.69 ),
                                  CPOCKETSONATAPDW::EncodeTOAus( ( float ) 31609.92 ),
                                  CPOCKETSONATAPDW::EncodeTOAus( ( float ) 32857.43 ),
                                  CPOCKETSONATAPDW::EncodeTOAus( ( float ) 37344.84 ),
                                  CPOCKETSONATAPDW::EncodeTOAus( ( float ) 38874.19 ),
                                  CPOCKETSONATAPDW::EncodeTOAus( ( float ) 40402.47 ),
                                  CPOCKETSONATAPDW::EncodeTOAus( ( float ) 41951.62 ),
                                  CPOCKETSONATAPDW::EncodeTOAus( ( float ) 43256.66 ),
                                  CPOCKETSONATAPDW::EncodeTOAus( ( float ) 44647.55 ),
                                  CPOCKETSONATAPDW::EncodeTOAus( ( float ) 46038.38 ),
                                  CPOCKETSONATAPDW::EncodeTOAus( ( float ) 47429.53 ),
                                  CPOCKETSONATAPDW::EncodeTOAus( ( float ) 48715.07 ),
                                  CPOCKETSONATAPDW::EncodeTOAus( ( float ) 49961.97 ),
                                  CPOCKETSONATAPDW::EncodeTOAus( ( float ) 51209.08 ),
    };

    iDOA = ( int ) m_uiCoSim * ( int ) CPOCKETSONATAPDW::EncodeDOA( 50 );

    for( i = 0; i < uiCoPDW; ++i ) {
        uiRandomDOA = ( unsigned int ) ( iDOA + ( ( rand() % 4 ) - 20 ) );
        //uiRandomDOA = ( unsigned int ) iDOA;
        uiRandomPA = ( unsigned int ) ( ( rand() % 140 ) + 20 );
        uiRandomPW = ( unsigned int ) ( ( rand() % 1000 ) + 20000 );

        if( m_uiCoSim % 20 == 0 || true ) {
            CPOCKETSONATAPDW::EncodeRealFREQMHz( ( int * ) &randomFreq, ( int * ) &randomCh, ( int ) g_enBoardId, 9800.0 );
        }
        else {
            CPOCKETSONATAPDW::EncodeRealFREQMHz( ( int * ) &randomFreq, ( int * ) &randomCh, ( int ) g_enBoardId, 3985.0 );
        }

        //m_ullTOA += CPOCKETSONATAPDW::EncodeTOAus( ( float ) 100 ) + ( ( rand() % 10000 ) - 5000 );
        m_ullTOA += CPOCKETSONATAPDW::EncodeTOAus( ( float ) 100 );

        memset( pSIGAPDW, 0, sizeof( DMAPDW ) );

        //
        pSIGAPDW->uPDW.x.uniPdw_status.stPdw_status.cw_pulse = 0;        // ;
        pSIGAPDW->uPDW.x.uniPdw_status.stPdw_status.pmop_flag = 0;
        pSIGAPDW->uPDW.x.uniPdw_status.stPdw_status.fmop_flag = 0;
        pSIGAPDW->uPDW.x.uniPdw_status.stPdw_status.false_pdw = 0;
        pSIGAPDW->uPDW.x.uniPdw_status.stPdw_status.fmop_dir = 1;
        pSIGAPDW->uPDW.x.uniPdw_status.stPdw_status.fmop_bw = 8000;

        pSIGAPDW->uPDW.x.uniPdw_dir_pa.stPdw_dir_pa.doa = uiRandomDOA;
        pSIGAPDW->uPDW.x.uniPdw_dir_pa.stPdw_dir_pa.di = 0;
        pSIGAPDW->uPDW.x.uniPdw_dir_pa.stPdw_dir_pa.pa = uiRandomPA;

        pSIGAPDW->uPDW.x.uniPdw_pw_freq.stPdw_pw_freq.pulse_width = uiRandomPW;
        pSIGAPDW->uPDW.x.uniPdw_pw_freq.stPdw_pw_freq.frequency_L = randomFreq & ( unsigned int ) 0xFF;

        pSIGAPDW->uPDW.x.uniPdw_freq_toa.stPdw_freq_toa.frequency_H = ( randomFreq >> 8 ) & ( unsigned int ) 0xFF;
        pSIGAPDW->uPDW.x.uniPdw_freq_toa.stPdw_freq_toa.pdw_phch = randomCh;
        pSIGAPDW->uPDW.x.uniPdw_freq_toa.stPdw_freq_toa.toa_L = m_ullTOA & ( _TOA ) 0xFFFF;

        pSIGAPDW->uPDW.x.uniPdw_toa_edge.stPdw_toa_edge.toa_H = ( m_ullTOA >> 16 );
        pSIGAPDW->uPDW.x.uniPdw_toa_edge.stPdw_toa_edge.edge = 1;

        pSIGAPDW->uPDW.x.uniPdw_index.stPdw_index.index = m_uiIndex;

        //printf( "m_ullTOA[%llx], [%0X:%0X]\n" , m_ullTOA, pDMAPDW->uPDW.uniPdw_toa_edge.stPdw_toa_edge.toa_H, pDMAPDW->uPDW.uniPdw_freq_toa.stPdw_freq_toa.toa_L );

        ++m_uiIndex;

        ++pSIGAPDW;
    }


#else
    uiCoPDW = m_strResColStart.uiCoPulseNum;

    iDOA = m_uiCoSim * 20;

    for( i = 0; i < uiCoPDW; ++i ) {
        int iCh;

        fRandomDOA = ( float ) iDOA + ( ( float ) CCommonUtils::Rand( 100 ) / ( float ) 10. );

        m_ullTOA += 0x100; // CEncode::EncodeTOAus(100, 0);

        memset( pSIGAPDW, 0, sizeof( SIGAPDW ) );

        //
        pSIGAPDW->ullTOA = m_ullTOA;

        pSIGAPDW->iPulseType = CEncode::EncodePulseType( 0 );

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
        memset( pSIGAPDW, 0, sizeof( DMAPDW ) );

        randomFreq = pstPDW->GetFrequency();
        randomCh = pstPDW->GetChannel();

        m_ullTOA = pstPDW->GetTOA();

#if defined(_POCKETSONATA_)
        pSIGAPDW->uPDW.x.uniPdw_status.stPdw_status.cw_pulse = CEncode::EncodePulseType( pstPDW->GetPulsetype() );        // uiPDW_CW;
        pSIGAPDW->uPDW.x.uniPdw_status.stPdw_status.pmop_flag = 0;
        pSIGAPDW->uPDW.x.uniPdw_status.stPdw_status.fmop_flag = 0;
        pSIGAPDW->uPDW.x.uniPdw_status.stPdw_status.false_pdw = 0;
        pSIGAPDW->uPDW.x.uniPdw_status.stPdw_status.fmop_dir = 1;
        pSIGAPDW->uPDW.x.uniPdw_status.stPdw_status.fmop_bw = 8000;

        pSIGAPDW->uPDW.x.uniPdw_dir_pa.stPdw_dir_pa.doa = pstPDW->GetAOA();
        pSIGAPDW->uPDW.x.uniPdw_dir_pa.stPdw_dir_pa.di = 0;
        pSIGAPDW->uPDW.x.uniPdw_dir_pa.stPdw_dir_pa.pa = pstPDW->GetPulseamplitude();

        pSIGAPDW->uPDW.x.uniPdw_pw_freq.stPdw_pw_freq.pulse_width = pstPDW->GetPulsewidth();
        pSIGAPDW->uPDW.x.uniPdw_pw_freq.stPdw_pw_freq.frequency_L = randomFreq & 0xFF;

        pSIGAPDW->uPDW.x.uniPdw_freq_toa.stPdw_freq_toa.frequency_H = ( randomFreq >> 8 ) & 0xFF;
        pSIGAPDW->uPDW.x.uniPdw_freq_toa.stPdw_freq_toa.pdw_phch = randomCh;
        pSIGAPDW->uPDW.x.uniPdw_freq_toa.stPdw_freq_toa.toa_L = m_ullTOA & 0xFFFF;

        pSIGAPDW->uPDW.x.uniPdw_toa_edge.stPdw_toa_edge.toa_H = ( m_ullTOA >> 16 );
        pSIGAPDW->uPDW.x.uniPdw_toa_edge.stPdw_toa_edge.edge = 1;

        pSIGAPDW->uPDW.x.uniPdw_index.stPdw_index.index = m_uiIndex;
#else
        int iCh;

        pSIGAPDW->iPulseType = pstPDW->GetPulsetype();

        pSIGAPDW->ullTOA = pstPDW->GetTOA();
        pSIGAPDW->uiAOA = pstPDW->GetAOA();
        pSIGAPDW->uiFreq = pstPDW->GetFrequency();
        pSIGAPDW->uiPA = pstPDW->GetPulseamplitude();
        pSIGAPDW->uiPW = pstPDW->GetPulsewidth();

#endif

        ++pstPDW;

        ++m_uiIndex;

        ++pSIGAPDW;
    }

#if defined(_POCKETSONATA_)


#else

#endif



#endif

    ++m_uiCoSim;
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
    unsigned int ui, uj, uiTotalPDW;
    unsigned int uiTrackCh = 0, uiScanCh = 0, uiDetectCh = ( unsigned int ) -1;

    _PDW *pstPDW;

    CCollectBank *pTheCollectBank = GetCollectBank( enPCIDriver );

    uiTotalPDW = pPDWData->GetTotalPDW();

    pstPDW = &pPDWData->pstPDW[0];
    if( uiTotalPDW != 0 ) {
        for( ui = 0; ui < uiTotalPDW; ++ui ) {
            uiTrackCh = 0;

            // 추적 채널 설정
            for( uj = CO_DETECT_CHANNEL; uj < CO_DETECT_CHANNEL + CO_TRACK_CHANNEL; ++uj ) {
                // pCollectBank = m_pTheTrackCollectBank[uj];
                if( pTheCollectBank->IsFiltered( uj, pstPDW ) == true ) {
                    if( pTheCollectBank->IsSave( uj ) == true ) {
                        pTheCollectBank->PushPDWData( uj, pstPDW, &pPDWData->x );
                    }
                    uiTrackCh = uj;
                }
            }

            // 탐지 채널에 저장한다.
            if( uiTrackCh == 0 ) {
                for( uj = 0; uj < CO_DETECT_CHANNEL; ++uj ) {
                    // pCollectBank = m_pTheDetectCollectBank[uj];
                    if( pTheCollectBank->IsFiltered( uj, pstPDW ) == true ) {
                        pTheCollectBank->PushPDWData( uj, pstPDW, &pPDWData->x );
                        uiDetectCh = uj;
                    }
                }
            }

            // 스캔 채널 설정
//             for( uj = 0; uj < CO_SCAN_CHANNEL; ++uj ) {
//             pCollectBank = m_pTheScanCollectBank[uj];
//             if( pCollectBank->IsFiltered( pstPDW ) == true ) {
//                 if( pCollectBank->IsSave() == true ) {
//                     pCollectBank->PushPDWData( pstPDW, &pPDWData->x );
//                 }
//                     uiScanCh = uj + ( CO_DETECT_CHANNEL + CO_TRACK_CHANNEL );
//             }
//         }

            // 사용자 채널 설정

            ++pstPDW;
        }
    }
    else {
        STR_COLLECTINFO stCollectInfo;

        //         memset( &stCollectInfo, 0, sizeof( STR_COLLECTINFO ) );
        //         stCollectInfo.iCh = 0;
        //         stCollectInfo.uiTotalPDW = 0;
        //         g_pTheSignalCollect->QMsgSnd( enTHREAD_REQ_DETECT_COLSTOP, &stCollectInfo, sizeof( STR_COLLECTINFO ) );
    }

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

    if( m_pUniHeader->ps.GetTotalPDW() != 0 ) {
        // 랜 데이터를 갖고온다.
        if( GetRecvData() != NULL ) {
            memcpy( m_uniLanData.szFile, GetRecvData(), m_pMsg->uiArrayLength );
        }
        else {
            memcpy( m_uniLanData.szFile, m_pstrPDWWithFileHeader, sizeof( UNION_HEADER ) + m_pUniHeader->ps.GetTotalPDW() * sizeof( SIGAPDW ) );
        }

        // 데이터를 지정하여 지정한 행렬에 저장한다.
        //pPDWData = m_pTheDetectCollectBank[0]->GetPDW();

#ifdef _POCKETSONATA_
        m_theDataFile.ReadDataMemory( ( char * ) m_uniLanData.szFile, PDW_EXT, NULL, enUnitToPDW );
#elif defined(_XBAND_)
        m_theDataFile.ReadDataMemory( ( char * ) m_uniLanData.szFile, PDW_EXT, NULL, enPDWToPDW );
#else
        m_theDataFile.ReadDataMemory( ( char * ) m_uniLanData.szFile, PDW_EXT, NULL, enUnitToPDW );
#endif

        // 추적/스캔/사용자 채널을 모의하여 해당 CCollectBank 객체에 저장한다.
        pstPDWData = m_theDataFile.GetPDWData();
        SimFilter( pstPDWData, enLEFT_PCI_DRIVER );
        //SimFilter( pstPDWData, enRIGHT_PCI_DRIVER );

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
        CollectingDetectChannel( iCh, enPCIDriver );
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

    unsigned int uiIndex, uiArrayLength, uiGetMinAnalPulse = 0;

    size_t szSize;

    CCollectBank *pCollectBank;

    STR_COLLECTINFO strCollectInfo;

    ENUM_PCI_DRIVER enPCIDriver;

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
// 		szSize = sizeof(UNION_HEADER) + sizeof(_PDW) * m_stPDWData.GetTotalPDW();
//         memcpy( & m_theTrkScnPDW.strPDW, & m_stPDWData, szSize ); // sizeof(STR_STATIC_PDWDATA) );
//         memcpy( & m_theTrkScnPDW.strABTData, GetABTData(uiIndex), sizeof(SRxABTData) );
//
//         if( strCollectInfo.uiTotalPDW >= _spAnalMinPulseCount ) {
//             g_pTheTrackAnalysis->QMsgSnd( enTHREAD_KNOWNANAL_START, & m_theTrkScnPDW, sizeof(STR_TRKSCNPDWDATA), & strCollectInfo, sizeof(STR_COLLECTINFO), GetThreadName() );
//         }
//         // PDW 펄스 개수 부족시 위협 처리로 바로 전달
//         else {
//             g_pTheEmitterMerge->QMsgSnd( enTHREAD_KNOWNANAL_FAIL, & m_theTrkScnPDW, sizeof(STR_TRKSCNPDWDATA), & strCollectInfo, sizeof(STR_COLLECTINFO), GetThreadName() );
//         }
//
    }

    // 스캔 채널 버퍼 체크
    iCh = CheckCollectBank( enScanCollectBank, enLEFT_PCI_DRIVER );
    //     if( iCh >= 0 ) {
    //         pCollectBank = GetCollectBank( iCh );
    //         uiIndex = (unsigned int) max( iCh - CO_DETECT_CHANNEL - CO_TRACK_CHANNEL, _spZero );
    //
    //         strCollectInfo.uiTotalPDW = pCollectBank->GetTotalPDW();
    //         strCollectInfo.iCh = iCh;
    //         strCollectInfo.uiAETID = m_ABTData[uiIndex].uiAETID;
    //         strCollectInfo.uiABTID = m_ABTData[uiIndex].uiABTID;
    //
    //         MakeStaticPDWData( pCollectBank->GetPDWData(), true );
    // 		szSize = sizeof(UNION_HEADER) + sizeof(_PDW) * m_stPDWData.GetTotalPDW();
    //         memcpy( & m_theTrkScnPDW.strPDW, & m_stPDWData, szSize ); //sizeof(STR_STATIC_PDWDATA) );
    //         memcpy( & m_theTrkScnPDW.strABTData, GetABTData(uiIndex), sizeof(SRxABTData) );
    //
    //         g_pTheScanAnalysis->QMsgSnd( enTHREAD_SCANANAL_START, & m_theTrkScnPDW, sizeof(STR_TRKSCNPDWDATA), & strCollectInfo, sizeof(STR_COLLECTINFO), GetThreadName() );
    //     }

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

    iCh = pTheCollectBank->CheckCollectBank( enDetectCollectBank );

    return iCh;
}


#endif