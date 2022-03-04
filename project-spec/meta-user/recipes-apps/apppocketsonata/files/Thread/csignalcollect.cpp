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
#include "../Utils/cmultiserver.h"
#include "../Utils/ccommonutils.h"

#include "../System/csysconfig.h"

#include "../Include/globals.h"

#define _DEBUG_


CCollectBank* CSignalCollect::m_pTheDetectCollectBank[DETECT_CHANNEL];
CCollectBank* CSignalCollect::m_pTheTrackCollectBank[TRACK_CHANNEL];
CCollectBank* CSignalCollect::m_pTheScanCollectBank[SCAN_CHANNEL];
CCollectBank* CSignalCollect::m_pTheUserCollectBank[USER_CHANNEL];

/**
 * @brief CSignalCollect::CSignalCollect
 * @param iKeyId
 * @param pClassName
 */
#ifdef _MSSQL_
CSignalCollect::CSignalCollect( int iKeyId, char *pClassName, bool bArrayLanData ) : CThread( iKeyId, pClassName, bArrayLanData ), CMSSQL( & m_theMyODBC )
#else
CSignalCollect::CSignalCollect( int iKeyId, char *pClassName, bool bArrayLanData ) : CThread( iKeyId, pClassName, bArrayLanData )
#endif
{
    int i, iCh;

    iCh = 0;
    for( i=0 ; i < DETECT_CHANNEL ; ++i ) {
        m_pTheDetectCollectBank[i] = new CCollectBank(TOTAL_CHANNELS, iCh++ );
    }

    m_theTrackChannel.Init( TRACK_CHANNEL );
    for( i=0 ; i < TRACK_CHANNEL ; ++i ) {
        if( false == m_theTrackChannel.Push( iCh ) ) {
            printf( " Push error...\n" );
        }
        m_pTheTrackCollectBank[i] = new CCollectBank(TOTAL_CHANNELS, iCh++ );
    }

    m_theScanChannel.Init( SCAN_CHANNEL );
    for( i=0 ; i < SCAN_CHANNEL ; ++i ) {
        if( false == m_theScanChannel.Push( iCh ) ) {
            printf( " Push error...\n" );
        }
        m_pTheScanCollectBank[i] = new CCollectBank(TOTAL_CHANNELS, iCh++ );
    }

    for( i=0 ; i < USER_CHANNEL ; ++i ) {
        m_pTheUserCollectBank[i] = new CCollectBank(TOTAL_CHANNELS, iCh++ );
    }

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

}


/**
 * @brief CSignalCollect::~CJamTech
 */
CSignalCollect::~CSignalCollect(void)
{
    int i;

    for( i=0 ; i < DETECT_CHANNEL ; ++i ) {
        delete m_pTheDetectCollectBank[i];
        m_pTheDetectCollectBank[i] = NULL;
    }
    for( i=0 ; i < TRACK_CHANNEL ; ++i ) {
        delete m_pTheTrackCollectBank[i];
        m_pTheTrackCollectBank[i] = NULL;
    }
    for( i=0 ; i < SCAN_CHANNEL ; ++i ) {
        delete m_pTheScanCollectBank[i];
        m_pTheScanCollectBank[i] = NULL;
    }
    for( i=0 ; i < USER_CHANNEL ; ++i ) {
        delete m_pTheUserCollectBank[i];
        m_pTheUserCollectBank[i] = NULL;
    }

    delete m_pIdentifyAlg;

}



/**
 * @brief CSignalCollect::Run
 */
void CSignalCollect::Run(key_t key)
{
    LOGENTRY;

    CThread::Run();

}

/**
 * @brief CSignalCollect::_routine
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

    while( true ) {
        if( QMsgRcv() == -1 ) {
            perror( "QMsgRcv" );
        }
        else {
            switch( m_pMsg->uiOpCode ) {
                case enTHREAD_DETECTANAL_START :
                    RoutineForDetectAnal();
                    break;

                case enTHREAD_REQ_SHUTDOWN :
                    LOGMSG1( enDebug, "[%s] 를 종료 처리 합니다...", GetThreadName() );
                    break;

                case enTHREAD_MODE :
                    break;

                default:
                    LOGMSG1( enError, "잘못된 명령(0x%x)을 수신하였습니다 !!", m_pMsg->uiOpCode );
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
 * @brief		RoutineForDetectAnal
 * @return		void
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2021/11/23 11:59:24
 * @warning		
 */
void CSignalCollect::RoutineForDetectAnal()
{
    bool bRoutineForDetectAnal=true;

    Init();

    while( bRoutineForDetectAnal == true ) {
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
                    //CloseSetScanWindowCell();
                    break;

                case enTHREAD_REQ_SHUTDOWN :
                    LOGMSG1( enDebug, "[%s] 를 종료 처리 합니다...", GetThreadName() );
                    break;

                case enTHREAD_MODE :
                    bRoutineForDetectAnal = false;
                    break;

                    // 모의 명령 처리
                case enTHREAD_REQ_SIM_PDWDATA :
                    SimPDWData();
                    break;

                default:
                    LOGMSG1( enError, "잘못된 명령(0x%x)을 수신하였습니다 !!", m_pMsg->uiOpCode );
                    break;
                
            }
        }

        // 신호 수집은 여기서 수행한다.
        if( bRoutineForDetectAnal == true ) {
            AnalysisStart();
        }
    }
    
}

/**
 * @brief CSignalCollect::SendEndCollect
 */
void CSignalCollect::SendEndCollect()
{
    if( m_bSendEnd == false || true ) {
        //TRACE( "\nCSignalCollect::SendEndCollect()");
        g_pTheEmitterMerge->QMsgSnd( enTHREAD_DETECTANAL_END, GetThreadName() );
        //TRACE( "!");

        m_bSendEnd = true;
    }

}

/**
 * @brief 객체를 초기화 합니다.
 */
void CSignalCollect::Init()
{
    // 탐지/추적/스캔 윈도우 셀을 닫는다.
    CloseCollectBank();

    // 탐지 분석판을 초기 설정합니다.
    unsigned int uj;
    for( uj=0 ; uj < DETECT_CHANNEL ; ++uj ) {
        SetupDetectCollectBank( uj );
    }

}

/**
 * @brief CSignalCollect::SetupDetectCollectBank
 */
void CSignalCollect::SetupDetectCollectBank( int iCh )
{
    STR_WINDOWCELL *pWindowCell;

    CCollectBank *pCollectBank = m_pTheDetectCollectBank[iCh];

    STR_PDWDATA *pPDWData = pCollectBank->GetPDWData();

#if defined(_ELINT_) || defined(_XBAND_)
    // memset( pPDWData->x.el.aucTaskID, 0, sizeof(char)*LENGTH_OF_TASK_ID );
    strcpy_s( (char *) pPDWData->x.el.aucTaskID, sizeof(pPDWData->x.el.aucTaskID), "MSIGA" );
    pPDWData->x.el.iIsStorePDW = 1;
    pPDWData->x.el.iCollectorID = RADARCOL_1;
    pPDWData->x.el.enBandWidth = en5MHZ_BW;
#else

#endif

    pCollectBank->SetCollectMode( enCollecting );

    pWindowCell = pCollectBank->GetWindowCell();

    pWindowCell->bUse = true;

    pWindowCell->uiMaxCoPDW = 100; //250;
    pWindowCell->uiMaxCollectTimesec = 10;
    pWindowCell->uiMaxCollectTimems = 100;

    pWindowCell->strAoa.iLow = IAOACNV( 0 );
    pWindowCell->strAoa.iHgh = IAOACNV( 360. ) - 1;

    pWindowCell->strFreq.iLow = 0; // IFRQMhzCNV( 0, MIN_FREQ_MHZ );
    pWindowCell->strFreq.iHgh = 0xffffff; // IFRQMhzCNV( 0, MAX_FREQ_MHZ );

    pWindowCell->strPA.iLow = I_IPACNV( -70 );
    pWindowCell->strPA.iHgh = I_IPACNV( 10 );

    pWindowCell->strPW.iLow = 0;
    pWindowCell->strPW.iHgh = 0xFFFFFF;

    clock_gettime( CLOCK_REALTIME, & pWindowCell->tsCollectStart );

}

/**
 * @brief 추적 윈도우셀을 닫는다.
 */
void CSignalCollect::CloseCollectBank()
{
    int i;

    for( i=0 ; i < DETECT_CHANNEL ; ++i ) {
        m_pTheDetectCollectBank[i]->CloseCollectBank();
    }

    for( i=0 ; i < TRACK_CHANNEL ; ++i ) {
        m_pTheTrackCollectBank[i]->CloseCollectBank();
    }

    for( i=0 ; i < SCAN_CHANNEL ; ++i ) {
        m_pTheScanCollectBank[i]->CloseCollectBank();
    }

    for( i=0 ; i < USER_CHANNEL ; ++i ) {
        m_pTheUserCollectBank[i]->CloseCollectBank();
    }
}

/**
 * @brief 분석 시작을 처리한다.
 */
void CSignalCollect::AnalysisStart()
{
    LOGENTRY;

    int iCh;
    bool bIsOut = true;

    STR_COLLECTINFO strCollectInfo;

    CCollectBank *pCollectBank;

    while( g_AnalLoop ) {
        bIsOut = true;

        // 탐지 채널 버퍼 체크
        iCh = CheckCollectBank( enDetectCollectBank );        
        if( iCh >= 0 ) {
            pCollectBank = m_pTheDetectCollectBank[iCh];
            strCollectInfo.uiTotalPDW = pCollectBank->GetTotalPDW();

            //unsigned int uiGetMinAnalPulse = (unsigned int) GP_SYSCFG->GetMinAnalPulse();  
            int iGetMinAnalPulse = g_pTheSysConfig->GetMinAnalPulse();
            unsigned int uiGetMinAnalPulse=0;
            if( iGetMinAnalPulse > 0 ) {
                uiGetMinAnalPulse = iGetMinAnalPulse;
            }

            if( strCollectInfo.uiTotalPDW >= uiGetMinAnalPulse ) {
                strCollectInfo.uiCh = iCh;
                MakeStaticPDWData( pCollectBank->GetPDWData() );
                g_pTheDetectAnalysis->QMsgSnd( enTHREAD_DETECTANAL_START, & m_stPDWData, sizeof(STR_STATIC_PDWDATA), & strCollectInfo, sizeof(STR_COLLECTINFO), GetThreadName() );
            }

            // 아래는 탐지 윈도우셀을 자동 재설정하도록 한다.
            pCollectBank->UpdateWindowCell();

            SendEndCollect();

            bIsOut = false;
        }

        // 추적 채널 버퍼 체크
        iCh = CheckCollectBank( enTrackCollectBank );
        if( iCh >= 0 ) {
            pCollectBank = GetCollectBank( iCh );

            strCollectInfo.uiTotalPDW = pCollectBank->GetTotalPDW();
            strCollectInfo.uiCh = iCh;
            strCollectInfo.uiAETID = m_ABTData[iCh-DETECT_CHANNEL].uiAETID;
            strCollectInfo.uiABTID = m_ABTData[iCh-DETECT_CHANNEL].uiABTID;

            memcpy( & m_theTrkScnPDW.strPDW, pCollectBank->GetPDWData(), sizeof(STR_PDWDATA) );
            memcpy( & m_theTrkScnPDW.strABTData, GetABTData(iCh-DETECT_CHANNEL), sizeof(SRxABTData) );

            if( strCollectInfo.uiTotalPDW >= _spAnalMinPulseCount ) {
                //TRACE( "\nCSignalCollect::AnalysisStart()");
                g_pTheTrackAnalysis->QMsgSnd( enTHREAD_KNOWNANAL_START, & m_theTrkScnPDW, sizeof(STR_TRKSCNPDWDATA), & strCollectInfo, sizeof(STR_COLLECTINFO), GetThreadName() );
                //TRACE( "#");
            }
            // PDW 펄스 개수 부족시 위협 처리로 바로 전달
            else {
                //TRACE( "\nCSignalCollect::AnalysisStart()");
                g_pTheEmitterMerge->QMsgSnd( enTHREAD_KNOWNANAL_FAIL, & m_theTrkScnPDW, sizeof(STR_TRKSCNPDWDATA), & strCollectInfo, sizeof(STR_COLLECTINFO), GetThreadName() );
                //TRACE( "#");
            }

            bIsOut = false;
        }

        // 스캔 채널 버퍼 체크
        iCh = CheckCollectBank( enScanCollectBank );        
        if( iCh >= 0 ) {
            pCollectBank = GetCollectBank( iCh );

            strCollectInfo.uiTotalPDW = pCollectBank->GetTotalPDW();
            strCollectInfo.uiCh = iCh;
            strCollectInfo.uiAETID = m_ABTData[iCh-DETECT_CHANNEL-TRACK_CHANNEL].uiAETID;
            strCollectInfo.uiABTID = m_ABTData[iCh-DETECT_CHANNEL-TRACK_CHANNEL].uiABTID;

            memcpy( & m_theTrkScnPDW.strPDW, pCollectBank->GetPDWData(), sizeof(STR_PDWDATA) );
            memcpy( & m_theTrkScnPDW.strABTData, GetABTData(iCh-DETECT_CHANNEL), sizeof(SRxABTData) );

            //g_pTheScanAnalysis->QMsgSnd( enTHREAD_SCANANAL_START, & m_theTrkScnPDW, sizeof(STR_TRKSCNPDWDATA), & strCollectInfo, sizeof(STR_COLLECTINFO) );
            bIsOut = false;
        }

        // 사용자 채널 버퍼 체크
        iCh = CheckCollectBank( enUserCollectBank );
        if( iCh >= 0 ) {
            CCommonUtils::SendLan( enREQ_MODE, & iCh, sizeof(int) );
            bIsOut = false;
        }

#ifdef __VXWORKS__        
        //usleep( 1000 );
#elif _MSC_VER
        // 이 쓰레드에서는 Sleep() 없이 코딩해야 UseCollect 쓰레드에 지연 없이 처리할 수 있음.
        //Sleep( 10 );
#else   
        usleep( 1000 );
#endif        
        //printf( "." );
        if( bIsOut == true ) {
            break;
        }
    }

}

/**
 * @brief 탐지 뱅크에 저장된 PDW 들을 검사하여 수집 완료된 채널을 리턴한다.
 * @return
 */
int CSignalCollect::CheckCollectBank( ENUM_COLLECTBANK enCollectBank )
{
    int i, iCh=-1;

    CCollectBank *pCollectBank;
    STR_WINDOWCELL *pWindowCell;

    // 채널을 랜덤 또는 증가/감소 교대로 번갈아 가며 체크한다.
    switch( enCollectBank ) {
        case enDetectCollectBank :
            for( i=0 ; i < DETECT_CHANNEL ; ++i ) {
                pCollectBank = m_pTheDetectCollectBank[i];
                if( true == pCollectBank->IsCompleteCollect() ) {
                    pWindowCell = pCollectBank->GetWindowCell();
                    iCh = pCollectBank->GetChannelNo();

                    if( pWindowCell->uiTotalPDW != _spZero ) {
                        LOGMSG3( enDebug, " It was collected the [%d]PDWs at the NEW [%2d]Bank/[%2d]Ch." , i, iCh, pWindowCell->uiTotalPDW );
                    }

                    pCollectBank->SetCollectMode( enCompleteCollection );
                    pCollectBank->SetCollectUpdateTime();
                    break;
                }
                else {
                    // 아래는 탐지 윈도우셀을 자동 재설정하도록 한다.
                    //pWindowCell = pCollectBank->GetWindowCell();

                    //pCollectBank->UpdateWindowCell();

                    //SendEndCollect();

                }

            }
            break;

        case enTrackCollectBank :
            for( i=0 ; i < TRACK_CHANNEL ; ++i ) {
                pCollectBank = m_pTheTrackCollectBank[i];

                if( true == pCollectBank->IsCompleteCollect() ) {
                    pWindowCell = pCollectBank->GetWindowCell();
                    iCh = pCollectBank->GetChannelNo();

                    LOGMSG2( enDebug, "Completion of TRK [%d] Collecting in the Ch[%2d]..." , pWindowCell->uiTotalPDW, iCh );

                    pCollectBank->SetCollectMode( enCompleteCollection );
                    break;
                }
            }
            break;

        case enScanCollectBank :
            for( i=0 ; i < SCAN_CHANNEL ; ++i ) {
                pCollectBank = m_pTheScanCollectBank[i];
                if( true == pCollectBank->IsCompleteCollect() ) {
                    pWindowCell = pCollectBank->GetWindowCell();
                    iCh = m_pTheScanCollectBank[i]->GetChannelNo();

                    LOGMSG2( enDebug, " 스캔 뱅크 [%2d]채널에서 [%d]개를 수집 완료되었습니다." , iCh, pWindowCell->uiTotalPDW );

                    //pCollectBank->SetCollectMode( enCompleteCollection );
                    pCollectBank->CloseTrackWindowCell();
                    break;
                }
            }
            break;

        case enUserCollectBank :
            for( i=0 ; i < USER_CHANNEL ; ++i ) {
                if( true == m_pTheUserCollectBank[i]->IsCompleteCollect() ) {
                    iCh = m_pTheUserCollectBank[i]->GetChannelNo();

                    LOGMSG2( enDebug, "\n 사용자 뱅크[%d]에서 [%d] 채널에서 수집 완료되었습니다." , i, iCh );
                    break;
                }
            }
            break;

        default :
            break;

    }

    return iCh;
}

/**
 * @brief CSignalCollect::ReqSetWindowCell
 */
void CSignalCollect::ReqTrackWindowCell()
{
    SRxABTData *pABTData = ( SRxABTData *) m_uniLanData.szFile;

    // 랜 데이터를 갖고온다.
    memcpy( m_uniLanData.szFile, GetRecvData(), m_pMsg->uiArrayLength );

    //LOGMSG3( enDebug, " [%d] 대역, 추적 [%d] 채널 에서 분석된 빔 번호[%d] 을 기반으로 윈도우 셀을 설정합니다." , m_pMsg->x.strAnalInfo.uiBand, m_pMsg->x.strAnalInfo.uiCh, m_pMsg->x.strAnalInfo.uiABTID );

    // 빔 정보를 기반으로 추적 및 스캔 채널을 업데이트 한다.
    if(  m_pMsg->x.strAnalInfo.uiCh == 0 ) {
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
    PopLanData( m_uniLanData.szFile, m_pMsg->iArrayIndex, m_pMsg->uiArrayLength );

    LOGMSG3( enDebug, "D[%d] 대역, [%d] 채널 에서 분석된 빔 번호[%d]의 윈도우 셀을 닫습니다." , m_pMsg->x.strAnalInfo.uiBand, m_pMsg->x.strAnalInfo.uiCh, m_pMsg->x.strAnalInfo.uiABTID );

     m_theTrackChannel.Push( m_pMsg->x.strAnalInfo.uiCh );

    // 빔 정보를 기반으로 추적 및 스캔 채널을 업데이트 한다.
    //CloseTrackWindowCell( pABTData );

    GetCollectBank( m_pMsg->x.strAnalInfo.uiCh )->CloseTrackWindowCell();

}

/**
 * @brief CSignalCollect::UpdateTrackWindowCell
 * @param pABTData
 */
void CSignalCollect::UpdateTrackWindowCell( SRxABTData *pABTData )
{
    STR_WINDOWCELL strWindowCell;

    // 정보 업데이트
    CalTrackWindowCell( & strWindowCell, pABTData );

    GetCollectBank( m_pMsg->x.strAnalInfo.uiCh )->UpdateWindowCell( & strWindowCell );

}

/**
 * @brief CSignalCollect::NewTrackWindowCell
 * @param pABTData
 */
void CSignalCollect::NewTrackWindowCell( SRxABTData *pABTData )
{
    unsigned int uiCh=DETECT_CHANNEL;

    STR_WINDOWCELL strWindowCell;

    if( m_theTrackChannel.Pop( & uiCh ) == true ) {
        memcpy( & m_ABTData[uiCh-DETECT_CHANNEL], pABTData, sizeof(SRxABTData) );

        m_pTheCollectBank = GetCollectBank( uiCh );

        CalTrackWindowCell( & strWindowCell, pABTData );

        m_pTheCollectBank->UpdateWindowCell( & strWindowCell );

        LOGMSG2( enDebug, " Setting up in the TRK [%d]Ch for B[%d]" , uiCh, pABTData->uiABTID );
    }
    else {
        LOGMSG( enDebug, "Nont of Track channel !!" );
    }


}

/**
 * @brief     CalTrackWindowCell
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
        pRadarMode = m_pIdentifyAlg->GetRadarMode( pABTData->iRadarModeIndex );

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
            pstrWindowCell->strFreq.iLow = I_IFRQMhzCNV( g_enBoardId, pABTData->fFreqMin );
            pstrWindowCell->strFreq.iHgh = I_IFRQMhzCNV( g_enBoardId, pABTData->fFreqMax );

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

        pstrWindowCell->strAoa.iLow = ( IAOACNV( pABTData->fDOAMin-10 ) + MAX_AOA ) % MAX_AOA;
        pstrWindowCell->strAoa.iHgh = ( IAOACNV( pABTData->fDOAMax+10 ) + MAX_AOA ) % MAX_AOA;

        pstrWindowCell->uiMaxCoPDW = _min( KWN_COLLECT_PDW, 100 );

        uiCollectTime = UADD( 5000, fMinCollectTime );
        pstrWindowCell->uiMaxCollectTimesec = UDIV( uiCollectTime, 1000 );
        pstrWindowCell->uiMaxCollectTimems = uiCollectTime % 1000;

    }
    else {

    }
}

/**
 * @brief CSignalCollect::SimPDWData
 */
void CSignalCollect::SimPDWData()
{
    STR_PDWDATA *pstPDWData;

    // 랜 데이터를 갖고온다.
    memcpy( m_uniLanData.szFile, GetRecvData(), m_pMsg->uiArrayLength );

    // 데이터를 지정하여 지정한 행렬에 저장한다.
    //pPDWData = m_pTheDetectCollectBank[0]->GetPDW();

#ifdef _POCKETSONATA_
    m_theDataFile.ReadDataMemory( (const char *) m_uniLanData.szFile, (char *) PDW_EXT, NULL, enUnitToPDW );
#elif _XBAND_
    m_theDataFile.ReadDataMemory( (const char *) m_uniLanData.szFile, (char *) PDW_EXT, NULL, enPDWToPDW );
#else
    m_theDataFile.ReadDataMemory( (const char *) m_uniLanData.szFile, (char *) PDW_EXT, NULL, enUnitToPDW );
#endif

    // 추적/스캔/사용자 채널을 모의하여 해당 CCollectBank 객체에 저장한다.
    pstPDWData = m_theDataFile.GetPDWData();
    SimFilter( pstPDWData );

    // 모의 PDW 데이터를 수집 버퍼에 추가한다.
    //pCollectBank = GetCollectBank( uiCh );
    //pCollectBank->PushPDWData( pPDWData );

    //_SAFE_DELETE( m_theDataFile.m_pData );

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
void CSignalCollect::SimFilter( STR_PDWDATA *pPDWData )
{
    unsigned int ui, uj, uiTotalPDW;
    unsigned int uiTrackCh=0, uiScanCh=0, uiDetectCh=(unsigned int) -1;

    _PDW *pstPDW;

    CCollectBank *pCollectBank;

    uiTotalPDW = pPDWData->GetTotalPDW();

    pstPDW = & pPDWData->pstPDW[0];
    for( ui=0 ; ui < uiTotalPDW ; ++ui ) {
        // 모의
        pstPDW->uiAOA = pstPDW->uiAOA;

        /*
        pstPDW->uiAOA = pstPDW->uiAOA + ( ( rand() % 10 ) - 5 );
        if( (int) pstPDW->uiAOA < 0 ) {
            pstPDW->uiAOA += MAX_AOA;
        }
        pstPDW->uiAOA = pstPDW->uiAOA % MAX_AOA;    */

        pstPDW->uiFreq = pstPDW->uiFreq; // + ( ( rand() % 20 ) - 10 );
        pstPDW->uiPW = pstPDW->uiPW; // + ( ( rand() % 20 ) - 10 );
        pstPDW->uiPA = pstPDW->uiPA; // + ( ( rand() % 20 ) - 10 );


        // 추적 채널 설정
        for( uj=0 ; uj < TRACK_CHANNEL ; ++uj ) {
            pCollectBank = m_pTheTrackCollectBank[uj];
            if( pCollectBank->IsFiltered( pstPDW ) == true ) {
                if( pCollectBank->IsSave() == true ) {
                    pCollectBank->PushPDWData( pstPDW );
                }
                uiTrackCh = uj + DETECT_CHANNEL;
            }
        }

        // 추적 채널에 속하지 않은 PDW는 탐지 채널에 저장한다.
        if( uiTrackCh == 0 ) {
            for( uj=0 ; uj < DETECT_CHANNEL ; ++uj ) {
                pCollectBank = m_pTheDetectCollectBank[uj];
                if( pCollectBank->IsFiltered( pstPDW ) == true ) {
                    pCollectBank->PushPDWData( pstPDW );
                    uiDetectCh = uj;

                    //pCollectBank->SimCollectMode();
                }
            }

        }

        // 스캔 채널 설정
        for( uj=0 ; uj < SCAN_CHANNEL ; ++uj ) {
            pCollectBank = m_pTheScanCollectBank[uj];
            if( pCollectBank->IsFiltered( pstPDW ) == true ) {
                if( pCollectBank->IsSave() == true ) {
                    pCollectBank->PushPDWData( pstPDW );
                }
                uiScanCh = uj + ( DETECT_CHANNEL + TRACK_CHANNEL );
            }
        }

        // 사용자 채널 설정

        ++pstPDW;
    }

    return;

}

/**
 * @brief CSignalCollect::ReqScanWindowCell
 */
void CSignalCollect::ReqScanWindowCell()
{
    SRxABTData *pABTData = ( SRxABTData *) m_uniLanData.szFile;

    // 랜 데이터를 갖고온다.
    memcpy( m_uniLanData.szFile, GetRecvData(), m_pMsg->uiArrayLength );

    //LOGMSG3( enDebug, " [%d] 대역, 스캔 [%d] 채널 에서 분석된 빔 번호[%d] 을 기반으로 윈도우 셀을 설정합니다." , m_pMsg->x.strAnalInfo.uiBand, m_pMsg->x.strAnalInfo.uiCh, m_pMsg->x.strAnalInfo.uiABTID );

    // 빔 정보를 기반으로 추적 및 스캔 채널을 업데이트 한다.
    if(  m_pMsg->x.strAnalInfo.uiCh == 0 ) {
        NewScanWindowCell( pABTData );
    }
    // 스캔 채널 업데이트한다.
    else {
        UpdateScanWindowCell( pABTData );
    }

}

/**
 * @brief CSignalCollect::CloseScanWindowCell
 */
void CSignalCollect::CloseScanWindowCell()
{

    // 랜 데이터를 갖고온다.
    PopLanData( m_uniLanData.szFile, m_pMsg->iArrayIndex, m_pMsg->uiArrayLength );

    LOGMSG3( enDebug, "D[%d] 대역, [%d] 채널 에서 분석된 빔 번호[%d]의 윈도우 셀을 닫습니다." , m_pMsg->x.strAnalInfo.uiBand, m_pMsg->x.strAnalInfo.uiCh, m_pMsg->x.strAnalInfo.uiABTID );

    m_theTrackChannel.Push( m_pMsg->x.strAnalInfo.uiCh );

    GetCollectBank( m_pMsg->x.strAnalInfo.uiCh )->CloseTrackWindowCell();

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
    unsigned int uiCh=TRACK_CHANNEL;

    STR_WINDOWCELL strWindowCell;

    if( m_theScanChannel.Pop( & uiCh ) == true ) {
        memcpy( & m_ABTData[uiCh-TRACK_CHANNEL], pABTData, sizeof(SRxABTData) );

        CalScanWindowCell( & strWindowCell, pABTData );

        GetCollectBank( uiCh )->UpdateWindowCell( & strWindowCell );

        LOGMSG3( enDebug, " [%d] 대역, 스캔 [%d] 채널 에서 분석된 빔 번호[%d] 을 기반으로 윈도우 셀을 설정합니다." , m_pMsg->x.strAnalInfo.uiBand, uiCh, m_pMsg->x.strAnalInfo.uiABTID );
        //LOGMSG2( enDebug, " 빔 번호[%d]를 스캔 [%d]채널에 설정 합니다." , pABTData->uiABTID, uiCh );
    }
    else {
        LOGMSG( enDebug, "스캔 채널이 없습니다 !!"  );
    }


}

/**
 * @brief CSignalCollect::CalScanWindowCell
 * @param pABTData
 */
void CSignalCollect::CalScanWindowCell( STR_WINDOWCELL *pstrWindowCell, SRxABTData *pABTData )
{
    UINT uiCollectTime;

    SRadarMode *pRadarMode;

    float fMinCollectTime=0;

    if( pstrWindowCell != NULL ) {
        pRadarMode = m_pIdentifyAlg->GetRadarMode( pABTData->iRadarModeIndex );

        memset( pstrWindowCell, 0, sizeof(STR_WINDOWCELL) );

        pstrWindowCell->uiABTID = pABTData->uiABTID;

        // 레이더모드 식별 경우에 식별 정보를 이용하여 주파수 및 펄스폭을 설정
        if( pRadarMode != NULL ) {
            pstrWindowCell->strFreq.iLow = I_IFRQMhzCNV( 0, pRadarMode->fRF_TypicalMin );
            pstrWindowCell->strFreq.iHgh = I_IFRQMhzCNV( 0, pRadarMode->fRF_TypicalMax );
            //CPOCKETSONATAPDW::EncodeRealFREQMHz( & pstrWindowCell->strFreq.iLow, & pstrWindowCell->strCh.iLow, (int) g_enBoardId, pRadarMode->fRF_TypicalMin );
            //CPOCKETSONATAPDW::EncodeRealFREQMHz( & pstrWindowCell->strFreq.iHgh, & pstrWindowCell->strCh.iHgh, (int) g_enBoardId, pRadarMode->fRF_TypicalMax );

            pstrWindowCell->strPW.iLow = IPWCNVLOW( pRadarMode->fPD_TypicalMin );
            pstrWindowCell->strPW.iHgh = IPWCNVHGH( pRadarMode->fPD_TypicalMax );

            fMinCollectTime = _max( pRadarMode->fScanPrimaryTypicalMax, pRadarMode->fScanSecondaryTypicalMax );
        }
        else {
            pstrWindowCell->strFreq.iLow = I_IFRQMhzCNV( 0, pABTData->fFreqMin );
            pstrWindowCell->strFreq.iHgh = I_IFRQMhzCNV( 0, pABTData->fFreqMax );
            //CPOCKETSONATAPDW::EncodeRealFREQMHz( & pstrWindowCell->strFreq.iLow, & pstrWindowCell->strCh.iLow, (int) g_enBoardId, pABTData->fFreqMin );
            //CPOCKETSONATAPDW::EncodeRealFREQMHz( & pstrWindowCell->strFreq.iHgh, & pstrWindowCell->strCh.iHgh, (int) g_enBoardId, pABTData->fFreqMax );

            pstrWindowCell->strPW.iLow = IPWCNVLOW( pABTData->fPWMin );
            pstrWindowCell->strPW.iHgh = IPWCNVHGH( pABTData->fPWMax );

#ifndef _XBAND_
            fMinCollectTime = pABTData->fMaxScanPeriod;
#endif
        }

        pstrWindowCell->strAoa.iLow = ( IAOACNV( pABTData->fDOAMin-10 ) + MAX_AOA ) % MAX_AOA;
        pstrWindowCell->strAoa.iHgh = ( IAOACNV( pABTData->fDOAMax+10 ) + MAX_AOA ) % MAX_AOA;

        pstrWindowCell->uiMaxCoPDW = _min( SCN_COLLECT_PDW, 1000 );

        uiCollectTime = UADD( 5000, fMinCollectTime );
        pstrWindowCell->uiMaxCollectTimesec = UDIV( uiCollectTime, 1000 );
        pstrWindowCell->uiMaxCollectTimems = uiCollectTime % 1000;

    }
    else {

    }
}

/**
 * @brief CSignalCollect::UpdateScanWindowCell
 * @param pABTData
 */
void CSignalCollect::UpdateScanWindowCell( SRxABTData *pABTData )
{
    STR_WINDOWCELL strWindowCell;

    // 정보 업데이트
    CalScanWindowCell( & strWindowCell, pABTData );

    GetCollectBank( m_pMsg->x.strAnalInfo.uiCh )->UpdateWindowCell( & strWindowCell );

}

/**
 * @brief     MakeStaticPDWData
 * @param     STR_PDWDATA * pPDWData
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-03-03, 14:08
 * @warning
 */
void CSignalCollect::MakeStaticPDWData( STR_PDWDATA *pPDWData )
{
    unsigned int i, uiTotalPDW;

    _PDW *pPDWSrc, *pPDWDest;

    // 헤더 복사
    memcpy( & m_stPDWData.x, & pPDWData->x, sizeof(UNION_HEADER) );

    // 데이터 복사
    pPDWSrc = pPDWData->pstPDW;
    pPDWDest = & m_stPDWData.stPDW[0];
    uiTotalPDW = pPDWData->GetTotalPDW();    
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