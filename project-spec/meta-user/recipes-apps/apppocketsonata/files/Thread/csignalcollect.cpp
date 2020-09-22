// 신호 수집 및 관리한다.
// 신규 데이터를 수집하기위한 수집 제어와 분석된 데이터를 기반으로 추적 수집 채널을 할당해서 추적 채널을 관리한다.
// 또한, 스캔 채널을 할당하여 스캔 수집을 하게 한다.

#include "../Anal/OFP_Main.h"

#include "csignalcollect.h"
#include "../Utils/clog.h"

#include "cdetectanalysis.h"
#include "cemittermerge.h"
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
                case enTHREAD_DETECTANAL_START :
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
 * @brief CSignalCollect::SendEndCollect
 */
void CSignalCollect::SendEndCollect()
{
    if( m_bSendEnd == false || true ) {
        EMTMRG->QMsgSnd( enTHREAD_DETECTANAL_END );

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

    // 탐지 분석판을
    SetupDetectCollectBank( 0 );

}

/**
 * @brief CSignalCollect::SetupDetectCollectBank
 */
void CSignalCollect::SetupDetectCollectBank( int iCh )
{
    STR_WINDOWCELL *pWindowCell;

    pWindowCell = m_pTheDetectCollectBank[iCh]->GetWindowCell();

    pWindowCell->bUse = true;

    pWindowCell->uiMaxCoPDW = 250;
    pWindowCell->uiMaxCollectTimesec = 0;
    pWindowCell->uiMaxCollectTimems = 500;

    pWindowCell->strAoa.iLow = IAOACNV( 0 );
    pWindowCell->strAoa.iHgh = IAOACNV( 360. ) - 1;

    pWindowCell->strFreq.iLow = IFRQMhzLOW( 450.0 );
    pWindowCell->strFreq.iHgh = IFRQMhzLOW( 18050 );

    pWindowCell->strPA.iLow = 0;
    pWindowCell->strPA.iHgh = 360;

    pWindowCell->strPW.iLow = IPWCNVLOW( 0.0 );
    pWindowCell->strPW.iHgh = IPWCNVLOW( 1000000.0 );

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
        pCollectBank = m_pTheDetectCollectBank[iCh];
        if( iCh >= 0 ) {
            strCollectInfo.uiTotalPDW = pCollectBank->GetTotalPDW();
            if( strCollectInfo.uiTotalPDW >= (7) ) {
                strCollectInfo.uiCh = iCh;
                DETANL->QMsgSnd( enTHREAD_DETECTANAL_START, pCollectBank->GetPDW(), sizeof(STR_PDWDATA), & strCollectInfo, sizeof(STR_COLLECTINFO) );
            }

            // 아래는 탐지 윈도우셀을 자동 재설정하도록 한다.
            pCollectBank->UpdateWindowCell();

            SendEndCollect();

            bIsOut = false;
        }

        // 추적 채널 버퍼 체크
        iCh = CheckCollectBank( enTrackCollectBank );
        pCollectBank = m_pTheTrackCollectBank[iCh];
        if( iCh >= 0 ) {
            strCollectInfo.uiTotalPDW = pCollectBank->GetTotalPDW();
            if( strCollectInfo.uiTotalPDW >= (7) ) {
                strCollectInfo.uiCh = iCh;
                TRKANL->QMsgSnd( enTHREAD_KNOWNANAL_START, pCollectBank->GetPDW(), sizeof(STR_PDWDATA), & strCollectInfo, sizeof(STR_COLLECTINFO) );
            }

            // 아래는 추적 윈도우셀을 자동 재설정하도록 한다.
            pCollectBank->UpdateWindowCell();

            bIsOut = false;
        }

        // 스캔 채널 버퍼 체크
        iCh = CheckCollectBank( enScanCollectBank );
        if( iCh >= 0 ) {
            //QMsgSnd( SCANANL->GetKeyId(), enTHREAD_DETECTANAL_START, & pCollectBank->GetPDW(), sizeof(STR_PDWDATA), & strCollectInfo, sizeof(STR_COLLECTINFO) );
            bIsOut = false;
        }

        // 사용자 채널 버퍼 체크
        iCh = CheckCollectBank( enUserCollectBank );
        if( iCh >= 0 ) {
            CCommonUtils::SendLan( enREQ_MODE, & iCh, sizeof(int) );
            bIsOut = false;
        }

        usleep( 1000 );
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
                    iCh = pWindowCell->iChannelNo;
                    LOGMSG4( enDebug, "%s [%2d]뱅크/[%2d]채널 에서 수집 완료되었습니다 [%d]." , g_szCollectBank[enDetectCollectBank], i, iCh, pWindowCell->uiAccumulatedCoUsed );

                    pCollectBank->SetCollectMode( enCompleteCollection );

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
                    iCh = pWindowCell->iChannelNo;

                    LOGMSG3( enDebug, "\n %s 뱅크[%d]에서 [%d] 채널에서 수집 완료되었습니다." , g_szCollectBank[enTrackCollectBank], i, iCh );

                    pCollectBank->SetCollectMode( enCompleteCollection );
                    break;
                }
            }
            break;

        case enScanCollectBank :
            for( i=0 ; i < SCAN_CHANNEL ; ++i ) {
                if( true == m_pTheScanCollectBank[i]->IsCompleteCollect() ) {
                    iCh = m_pTheScanCollectBank[i]->GetChannelNo();

                    LOGMSG3( enDebug, "\n %s 뱅크[%d]에서 [%d] 채널에서 수집 완료되었습니다." , g_szCollectBank[enScanCollectBank], i, iCh );
                    break;
                }
            }
            break;

        case enUserCollectBank :
            for( i=0 ; i < USER_CHANNEL ; ++i ) {
                if( true == m_pTheUserCollectBank[i]->IsCompleteCollect() ) {
                    iCh = m_pTheUserCollectBank[i]->GetChannelNo();

                    LOGMSG3( enDebug, "\n %s 뱅크[%d]에서 [%d] 채널에서 수집 완료되었습니다." , g_szCollectBank[enDetectCollectBank], i, iCh );
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
    if(  m_pMsg->x.strAnalInfo.uiCh == 0 ) {
        NewTrackWindowCell( pABTData );

        UpdateTrackWindowCell();
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
    // 정보 업데이트

}

/**
 * @brief CSignalCollect::StartTrackWindowCell
 */
void CSignalCollect::UpdateTrackWindowCell()
{
    m_pStrWindowCell->bUse = true;

    if( IsValidChannle() == true ) {
        m_pStrWindowCell->enCollectMode = enCollecting;

    }

}

/**
 * @brief CSignalCollect::IsValidChannle
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

    STR_WINDOWCELL strWindowCell;

    if( m_theTrackChannel.Pop( & uiCh ) == true ) {
        m_pTheCollectBank = GetCollectBank( uiCh );

        CalTrackWindowCell( & strWindowCell, pABTData );
    }
    else {
        LOGMSG( enDebug, "추적 채널이 없습니다 !!"  );
    }

/*
 *
        m_pTheCollectBank = GetCollectBank( uiCh );
        m_pStrWindowCell = m_pTheCollectBank->GetWindowCell();

        CalTrackWindowCell( pABTData );

    }
    else {

    }
*/

}

/**
 * @brief CSignalCollect::CalTrackWindowCell
 * @param pABTData
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
            pstrWindowCell->strFreq.iLow = IFRQMhzLOW( pRadarMode->fRF_RangeMin );
            pstrWindowCell->strFreq.iHgh = IFRQMhzHGH( pRadarMode->fRF_RangeMax );

            pstrWindowCell->strPW.iLow = IPWCNVLOW( pRadarMode->fPD_RangeMin );
            pstrWindowCell->strPW.iHgh = IPWCNVHGH( pRadarMode->fPD_RangeMax );

            fMinCollectTime = _max( pRadarMode->fScanPrimaryTypicalMax, pRadarMode->fScanSecondaryTypicalMax );
        }
        else {
            pstrWindowCell->strFreq.iLow = IFRQMhzLOW( pABTData->fMinFreq );
            pstrWindowCell->strFreq.iHgh = IFRQMhzHGH( pABTData->fMaxFreq );

            pstrWindowCell->strPW.iLow = IPWCNVLOW( pABTData->fMinPW );
            pstrWindowCell->strPW.iHgh = IPWCNVHGH( pABTData->fMaxPW );

            fMinCollectTime = pABTData->fMaxScanPeriod;
        }

        pstrWindowCell->strAoa.iLow = pABTData->fMinDOA;
        pstrWindowCell->strAoa.iHgh = pABTData->fMaxDOA;

        pstrWindowCell->uiMaxCoPDW = 100;

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
    STR_PDWDATA stPDWData;
    //CCollectBank *pCollectBank;
    //unsigned int uiCh;

    // 랜 데이터를 갖고온다.
    PopLanData( m_uniLanData.szFile, m_pMsg->iArrayIndex, m_pMsg->uiArrayLength );

    // 데이터를 지정하여 지정한 행렬에 저장한다.
    //pPDWData = m_pTheDetectCollectBank[0]->GetPDW();
    m_theDataFile.ReadDataMemory( & stPDWData, (const char *) m_uniLanData.szFile, ".ppdw" );

    // 추적/스캔/사용자 채널을 모의하여 해당 CCollectBank 객체에 저장한다.
    SimFilter( & stPDWData );

    // 모의 PDW 데이터를 수집 버퍼에 추가한다.
    //pCollectBank = GetCollectBank( uiCh );
    //pCollectBank->PushPDWData( pPDWData );

}

/**
 * @brief CSignalCollect::SimFilter
 * @param pPDWData
 */
unsigned int CSignalCollect::SimFilter( STR_PDWDATA *pPDWData )
{
    unsigned int ui, uj;
    unsigned int uiTrackCh=0, uiScanCh=0, uiDetectCh=(unsigned int) -1;

    _PDW *pstPDW;

    CCollectBank *pCollectBank;
    STR_WINDOWCELL *pWindowCell;

    pstPDW = & pPDWData->stPDW[0];
    for( ui=0 ; ui < pPDWData->uiTotalPDW ; ++ui ) {
        // 추적 채널 설정
        for( uj=0 ; uj < TRACK_CHANNEL ; ++uj ) {
            pCollectBank = m_pTheTrackCollectBank[uj];
            pWindowCell = pCollectBank->GetWindowCell();
            if( IsFiltered(pstPDW, pWindowCell ) == true ) {
                pCollectBank->PushPDWData( pstPDW );
                uiTrackCh = uj + DETECT_CHANNEL;
            }
        }

        // 추적 채널에 속하지 않은 PDW는 탐지 채널에 저장한다.
        if( uiTrackCh == 0 ) {
            for( uj=0 ; uj < DETECT_CHANNEL ; ++uj ) {
                pCollectBank = m_pTheDetectCollectBank[uj];
                pWindowCell = pCollectBank->GetWindowCell();
                if( IsFiltered(pstPDW, pWindowCell ) == true ) {
                    pCollectBank->PushPDWData( pstPDW );
                    uiDetectCh = uj;

                    pCollectBank->SimCollectMode();
                }
            }

        }

        // 스캔 채널 설정
        for( uj=0 ; uj < SCAN_CHANNEL ; ++uj ) {
            pCollectBank = m_pTheScanCollectBank[uj];
            pWindowCell = pCollectBank->GetWindowCell();
            if( pWindowCell->bUse == true && IsFiltered(pstPDW, pWindowCell ) == true ) {
                pCollectBank->PushPDWData( pstPDW );
                uiScanCh = uj + ( DETECT_CHANNEL + TRACK_CHANNEL );
            }

        }

        // 사용자 채널 설정

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
    bool bRet=false;

    if( pWindowCell->bUse == true && pWindowCell->enCollectMode == enCollecting ) {
        bRet = CompMarginDiff<int>( pstPDW->iFreq, pWindowCell->strFreq.iLow, pWindowCell->strFreq.iHgh, 10 ) && \
               CompMarginDiff<int>( pstPDW->iPW, pWindowCell->strPW.iLow, pWindowCell->strPW.iHgh, 10 );
    }

    return bRet;
}
