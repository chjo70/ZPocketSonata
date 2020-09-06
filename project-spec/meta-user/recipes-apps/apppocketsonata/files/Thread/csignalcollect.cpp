// 신호 수집 및 관리한다.
// 신규 데이터를 수집하기위한 수집 제어와 분석된 데이터를 기반으로 추적 수집 채널을 할당해서 추적 채널을 관리한다.
// 또한, 스캔 채널을 할당하여 스캔 수집을 하게 한다.

#include "../Anal/OFP_Main.h"

#include "csignalcollect.h"
#include "../Utils/clog.h"

#include "cdetectanalysis.h"
#include "ctrackanalysis.h"
#include "cscananalysis.h"

#include "../Utils/csingleserver.h"
#include "../Utils/cmultiserver.h"
#include "../Utils/ccommonutils.h"

#define _DEBUG_


// 클래스 내의 정적 멤버변수 값 정의
CSignalCollect* CSignalCollect::pInstance = nullptr;

/**
 * @brief CSignalCollect::CSignalCollect
 * @param iKeyId
 * @param pClassName
 */
CSignalCollect::CSignalCollect( int iKeyId, char *pClassName, bool bArrayLanData ) : CThread( iKeyId, pClassName, bArrayLanData )
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

    for( i=0 ; i < SCAN_CHANNEL ; ++i ) {

        m_pTheScanCollectBank[i] = new CCollectBank(TOTAL_CHANNELS, iCh++ );
    }

    for( i=0 ; i < USER_CHANNEL ; ++i ) {
        m_pTheUserCollectBank[i] = new CCollectBank(TOTAL_CHANNELS, iCh++ );
    }

    m_pIdentifyAlg = new CELSignalIdentifyAlg( "" );

}


/**
 * @brief CSignalCollect::~CJamTech
 */
CSignalCollect::~CSignalCollect(void)
{
    int i;

    for( i=0 ; i < DETECT_CHANNEL ; ++i ) {
        delete m_pTheDetectCollectBank[i];
        m_pTheDetectCollectBank[i] = 0;
    }
    for( i=0 ; i < TRACK_CHANNEL ; ++i ) {
        delete m_pTheTrackCollectBank[i];
        m_pTheTrackCollectBank[i] = 0;
    }
    for( i=0 ; i < SCAN_CHANNEL ; ++i ) {
        delete m_pTheScanCollectBank[i];
        m_pTheScanCollectBank[i] = 0;
    }
    for( i=0 ; i < USER_CHANNEL ; ++i ) {
        delete m_pTheUserCollectBank[i];
        m_pTheUserCollectBank[i] = 0;
    }

    delete m_pIdentifyAlg;

}



/**
 * @brief CSignalCollect::Run
 */
void CSignalCollect::Run()
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
    bool bRunCollecting=false;

    //UNI_LAN_DATA *pLanData;

    m_pMsg = GetDataMessage();

    //pLanData = ( UNI_LAN_DATA * ) & m_pMsg->x.szData[0];

    pthread_cleanup_push( TCleanUpHandler, NULL);

    while( g_AnalLoop ) {
        if( QMsgRcv( IPC_NOWAIT ) > 0 ) {
            switch( m_pMsg->ucOpCode ) {
                case enTHREAD_ANAL_START :
                    Init();
                    bRunCollecting = true;
                    break;

                case enTHREAD_REQ_SHUTDOWN :
                    LOGMSG1( enDebug, "[%s] 를 종료 처리 합니다...", ChildClassName() );
                    break;

                case enTHREAD_REQ_SETWINDOWCELL :
                    ReqSetWindowCell();

                    break;

                // 모의 명령 처리
                case enTHREAD_REQ_SIM_PDWDATA :
                    SimPDWData();
                    break;

                default:
                    LOGMSG1( enError, "잘못된 명령(0x%x)을 수신하였습니다 !!", m_pMsg->ucOpCode );
                    break;
            }
        }
        else {
            // 신호 수집은 여기서 수행한다.
            if( bRunCollecting == true ) {
                AnalysisStart();
            }
        }
    }

    pthread_cleanup_pop( 1 );

}

/**
 * @brief 객체를 초기화 합니다.
 */
void CSignalCollect::Init()
{
    // 추적 윈도우 셀을 닫는다.
    CloseTrackCollectBank();

    // 스캔 윈도우 셀을 닫는다.
    CloseScanCollectBank();

    // 탐지 분석판을
    //m_pTheDetectCollectBank[0]->SetWindowCell( );
}

/**
 * @brief 추적 윈도우셀을 닫는다.
 */
void CSignalCollect::CloseTrackCollectBank()
{
    int i;

    for( i=0 ; i < TRACK_CHANNEL ; ++i ) {
        m_pTheTrackCollectBank[i]->CloseCollectBank();
    }
}

/**
 * @brief 스캔 윈도우셀을 닫는다.
 */
void CSignalCollect::CloseScanCollectBank()
{
    int i;

    for( i=0 ; i < SCAN_CHANNEL ; ++i ) {
        m_pTheScanCollectBank[i]->CloseCollectBank();
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

    while( g_AnalLoop ) {
        bIsOut = true;

        // 탐지 채널 버퍼 체크
        iCh = CheckCollectBank( enDetectCollectBank );
        if( iCh >= 0 ) {
            STR_COLLECTINFO strCollectInfo;

            strCollectInfo.uiCh = iCh;
            strCollectInfo.uiTotalPDW = m_pTheDetectCollectBank[0]->GetTotalPDW();
            DETANL->QMsgSnd( enTHREAD_ANAL_START, m_pTheDetectCollectBank[0]->GetPDW(), sizeof(STR_PDWDATA), & strCollectInfo, sizeof(STR_COLLECTINFO) );

            bIsOut = false;
        }

        // 추적 채널 버퍼 체크
        iCh = CheckCollectBank( enTrackCollectBank );
        if( iCh >= 0 ) {
            QMsgSnd( TRKANL->GetKeyId(), enTHREAD_ANAL_START, & iCh, sizeof(int) );
            bIsOut = false;
        }

        // 스캔 채널 버퍼 체크
        iCh = CheckCollectBank( enScanCollectBank );
        if( iCh >= 0 ) {
            QMsgSnd( SCANANL->GetKeyId(), enTHREAD_ANAL_START, & iCh, sizeof(int) );
            bIsOut = false;
        }

        // 사용자 채널 버퍼 체크
        iCh = CheckCollectBank( enUserCollectBank );
        if( iCh >= 0 ) {
            CCommonUtils::SendLan( enREQ_MODE, & iCh, sizeof(int) );
            bIsOut = false;
        }

        sleep( 1 );
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

    // 채널을 랜덤 또는 증가/감소 교대로 번갈아 가며 체크한다.
    switch( enCollectBank ) {
        case enDetectCollectBank :
            for( i=0 ; i < DETECT_CHANNEL ; ++i ) {
                if( true == m_pTheDetectCollectBank[i]->IsCompleteCollect() ) {
                    m_pTheDetectCollectBank[i]->SetCollectMode( enCollecting );

                    iCh = m_pTheDetectCollectBank[i]->GetChannelNo();

                    LOGMSG3( enDebug, "%s 뱅크[%d]에서 [%d] 채널에서 수집 완료히었습니다." , g_szCollectBank[enDetectCollectBank], i, iCh );
                    break;
                }
            }
            break;

        case enTrackCollectBank :
            for( i=0 ; i < TRACK_CHANNEL ; ++i ) {
                if( true == m_pTheTrackCollectBank[i]->IsCompleteCollect() ) {
                    iCh = m_pTheTrackCollectBank[i]->GetChannelNo();

                    LOGMSG3( enDebug, "\n %s 뱅크[%d]에서 [%d] 채널에서 수집 완료히었습니다." , g_szCollectBank[enDetectCollectBank], i, iCh );
                    break;
                }
            }
            break;

        case enScanCollectBank :
            for( i=0 ; i < SCAN_CHANNEL ; ++i ) {
                if( true == m_pTheScanCollectBank[i]->IsCompleteCollect() ) {
                    iCh = m_pTheScanCollectBank[i]->GetChannelNo();

                    LOGMSG3( enDebug, "\n %s 뱅크[%d]에서 [%d] 채널에서 수집 완료히었습니다." , g_szCollectBank[enDetectCollectBank], i, iCh );
                    break;
                }
            }
            break;

        case enUserCollectBank :
            for( i=0 ; i < USER_CHANNEL ; ++i ) {
                if( true == m_pTheUserCollectBank[i]->IsCompleteCollect() ) {
                    iCh = m_pTheUserCollectBank[i]->GetChannelNo();

                    LOGMSG3( enDebug, "\n %s 뱅크[%d]에서 [%d] 채널에서 수집 완료히었습니다." , g_szCollectBank[enDetectCollectBank], i, iCh );
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
void CSignalCollect::ReqSetWindowCell()
{
    SRxABTData *pABTData = ( SRxABTData *) m_uniLanData.szFile;

    // 랜 데이터를 갖고온다.
    PopLanData( m_uniLanData.szFile, m_pMsg->iArrayIndex, m_pMsg->uiArrayLength );

    LOGMSG3( enDebug, "%d 대역, %d 채널에서 분석된 %d 빔 정보를 기반으로 윈도우 셀을 설정합니다." , m_pMsg->x.strAnalInfo.uiBand, m_pMsg->x.strAnalInfo.uiCh, pABTData->uiABTID );

    // 빔 정보를 기반으로 추적 및 스캔 채널을 업데이트 한다.
    ReqSetWindowCell( pABTData, m_pMsg->x.strAnalInfo.uiCh );

}

/**
 * @brief CSignalCollect::ReqSetWindowCell
 * @param pABTData
 * @param uiCh
 */
void CSignalCollect::ReqSetWindowCell( SRxABTData *pABTData, UINT uiCh )
{
    //ENUM_COLLECTBANK enCollectBank;

    //enCollectBank = GetCollectBank( uiCellID );

    // 신규이어서 추적 채널로 생성
    if( uiCh == _spZero ) {
        NewTrackWindowCell( pABTData );

        StartTrackWindowCell();
    }
    // 추적 채널 업데이트한다.
    else {
        UpdateTrackWindowCell( pABTData );

    }

}

/**
 * @brief CSignalCollect::UpdateTrackWindowCell
 * @param pABTData
 */
void CSignalCollect::UpdateTrackWindowCell( SRxABTData *pABTData )
{

}

/**
 * @brief CSignalCollect::StartTrackWindowCell
 */
void CSignalCollect::StartTrackWindowCell()
{
    m_pStrWindowCell->bUse = true;

    if( IsValidChannle() == true ) {
        m_pStrWindowCell->enCollectMode = enCollecting;

    }

}

/**
 * @brief CSignalCollect
 */
bool CSignalCollect::IsValidChannle()
{
    bool bRet=true;

    switch( m_pStrWindowCell->enCollectMode ) {
        case enUnused:
            break;
        case enCollecting:
            bRet = false;
            break;
        case enCompleteCollection:
            break;

        default :
            break;
   }

   if( bRet == false ) {
       printf( "IsValidChannle\n" );
   }

   return bRet;

}

/**
 * @brief CSignalCollect::NewTrackWindowCell
 * @param pABTData
 */
void CSignalCollect::NewTrackWindowCell( SRxABTData *pABTData )
{
    unsigned int uiCh;

    if( m_theTrackChannel.Pop( & uiCh ) == true ) {
        m_pTheCollectBank = GetCollectBank( uiCh );
        m_pStrWindowCell = m_pTheCollectBank->GetWindowCell();

        CalTrackWindowCell( pABTData );

    }
    else {
        printf( "추적 채널이 없습니다 !!\n" );
    }

}

/**
 * @brief CSignalCollect::CalTrackWindowCell
 * @param pABTData
 */
void CSignalCollect::CalTrackWindowCell( SRxABTData *pABTData )
{
    SRadarMode *pRadarMode;

    float fMinCollectTime=0;

    if( m_pStrWindowCell != NULL ) {
        pRadarMode = m_pIdentifyAlg->GetRadarMode( pABTData->iRadarModeIndex );

        memset( m_pStrWindowCell, 0, sizeof(STR_WINDOWCELL) );

        m_pStrWindowCell->uiABTID = pABTData->uiABTID;

        // 레이더모드 식별 경우에 식별 정보를 이용하여 주파수 및 펄스폭을 설정
        if( pRadarMode != NULL ) {
            m_pStrWindowCell->strFreq.iLow = IFRQMhzLOW( pRadarMode->fRF_RangeMin );
            m_pStrWindowCell->strFreq.iHgh = IFRQMhzHGH( pRadarMode->fRF_RangeMax );

            m_pStrWindowCell->strPW.iLow = IPWCNVLOW( pRadarMode->fPD_RangeMin );
            m_pStrWindowCell->strPW.iHgh = IPWCNVHGH( pRadarMode->fPD_RangeMax );

            fMinCollectTime = _max( pRadarMode->fScanPrimaryTypicalMax, pRadarMode->fScanSecondaryTypicalMax );
        }
        else {
            m_pStrWindowCell->strFreq.iLow = IFRQMhzLOW( pABTData->fMinFreq );
            m_pStrWindowCell->strFreq.iHgh = IFRQMhzHGH( pABTData->fMaxFreq );

            m_pStrWindowCell->strPW.iLow = IPWCNVLOW( pABTData->fMinPW );
            m_pStrWindowCell->strPW.iHgh = IPWCNVHGH( pABTData->fMaxPW );

            fMinCollectTime = pABTData->fMaxScanPeriod;
        }

        m_pStrWindowCell->strAoa.iLow = pABTData->fMinDOA;
        m_pStrWindowCell->strAoa.iHgh = pABTData->fMaxDOA;

        m_pStrWindowCell->uiMaxCoPDW = 100;
        m_pStrWindowCell->uiMaxCollectTime = 500 + fMinCollectTime;
    }
    else {

    }
}

/**
 * @brief CSignalCollect::SimPDWData
 */
void CSignalCollect::SimPDWData()
{
    STR_PDWDATA *pPDWData;
    CCollectBank *pCollectBank;
    unsigned int uiCh;

    // 랜 데이터를 갖고온다.
    PopLanData( m_uniLanData.szFile, m_pMsg->iArrayIndex, m_pMsg->uiArrayLength );

    // 데이터를 지정하여 지정한 행렬에 저장한다.
    pPDWData = m_pTheDetectCollectBank[0]->GetPDW();
    m_theDataFile.ReadDataMemory( pPDWData, (const char *) m_uniLanData.szFile, ".ppdw" );

    // 추적/스캔/사용자 채널을 모의하여 해당 CCollectBank 객체에 저장한다.
    uiCh = SimFilter( pPDWData );

    // 모의 PDW 데이터를 수집 버퍼에 추가한다.
    pCollectBank = GetCollectBank( uiCh );
    pCollectBank->PushPDWData( pPDWData );

}

/**
 * @brief CSignalCollect::SimFilter
 * @param pPDWData
 */
unsigned int CSignalCollect::SimFilter( STR_PDWDATA *pPDWData )
{
    unsigned int ui, uj;
    unsigned int uiTrackCh=0, uiScanCh=0;

    _PDW *pstPDW;

    CCollectBank *pCollectBank;
    STR_WINDOWCELL *pWindowCell;

    pstPDW = & pPDWData->stPDW[0];
    for( ui=0 ; ui < pPDWData->uiTotalPDW ; ++ui ) {
        // 추적 채널 설정
        for( uj=0 ; uj < TRACK_CHANNEL ; ++uj ) {
            pCollectBank = m_pTheTrackCollectBank[uj];
            pWindowCell = pCollectBank->GetWindowCell();
            if( pWindowCell->bUse == true && IsFiltered(pstPDW, pWindowCell ) == true ) {
                pCollectBank->PushPDWData( pstPDW );
                uiTrackCh = uj + DETECT_CHANNEL;
            }

        }

        // 스캔 채널 설정
        for( uj=0 ; uj < SCAN_CHANNEL ; ++uj ) {
            pCollectBank = m_pTheScanCollectBank[uj];
            pWindowCell = pCollectBank->GetWindowCell();
            if( pWindowCell->bUse == true ) {
                uiScanCh = uj + ( DETECT_CHANNEL + TRACK_CHANNEL );
            }

        }

        ++pstPDW;
    }

    return uiTrackCh;

}

/**
 * @brief CSignalCollect::IsFiltered
 * @param pstPDW
 * @param pWindowCell
 * @return
 */
bool CSignalCollect::IsFiltered( _PDW *pstPDW, STR_WINDOWCELL *pWindowCell )
{
    bool bRet;

    bRet = CompMarginDiff<int>( pstPDW->iFreq, pWindowCell->strFreq.iLow, pWindowCell->strFreq.iHgh, 10 ) && \
           CompMarginDiff<int>( pstPDW->iPW, pWindowCell->strPW.iLow, pWindowCell->strPW.iHgh, 10 );

    return bRet;
}
