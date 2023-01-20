﻿// CSignalCollect.cpp: implementation of the CScanAnalysis class.
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

    m_uiPDWID = 0;

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
 * @brief CSignalCollect::~CSignalCollect
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
            WhereIs;
            printf( "\n [%d]" , m_pMsg->uiOpCode );
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

            WhereIs;

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
                    CloseScanWindowCell();
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
                    CheckAllCollectBank();
                    break;

                default:
                    LOGMSG1( enError, "잘못된 명령(0x%x)을 수신하였습니다 !!", m_pMsg->uiOpCode );
                    break;
                
            }
        }

        // 신호 수집은 여기서 수행한다.
//         if( bRoutineForDetectAnal == true ) {
//             AnalysisStart();
//         }
    }
    
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
void CSignalCollect::Init()
{
    // 탐지/추적/스캔 윈도우 셀을 닫는다.
    CloseCollectBank();

    // 탐지 분석판을 초기 설정합니다.
    int j;
    for( j=0 ; j < DETECT_CHANNEL ; ++j ) {
        SetupDetectCollectBank( j );
    }

}

/**
 * @brief     팀지 수집 뱅크의 초기 설정 값으로 설정한다.
 * @param     int iCh
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-05-10, 13:58
 * @warning
 */
void CSignalCollect::SetupDetectCollectBank( int iCh )
{
    STR_WINDOWCELL *pWindowCell;

    CCollectBank *pCollectBank = m_pTheDetectCollectBank[iCh];

    pCollectBank->SetCollectMode( enCollecting );

    pWindowCell = pCollectBank->GetWindowCell();

    pWindowCell->bUse = true;

    pWindowCell->uiMaxCoPDW = 100; //250;
    pWindowCell->uiMaxCollectTimesec = 10;
    pWindowCell->uiMaxCollectTimems = 100;

    pWindowCell->strAoa.iLow = (int) IAOACNV( 0 );
    pWindowCell->strAoa.iHgh = (int) ( IAOACNV( 360. ) - 1 );

    pWindowCell->strFreq.iLow = 0; // IFRQMhzCNV( 0, MIN_FREQ_MHZ );
    pWindowCell->strFreq.iHgh = 0x7fffffff - 100000; // IFRQMhzCNV( 0, MAX_FREQ_MHZ );

    pWindowCell->strPA.iLow = NDIV( -90, _spAMPres );   //I_IPACNV( -70 );
    pWindowCell->strPA.iHgh = (int) UDIV( 10, _spAMPres );    //I_IPACNV( 10 );

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

    while( g_AnalLoop ) {
        bIsOut = true;

        CheckAllCollectBank();

        // 사용자 채널 버퍼 체크
        iCh = CheckCollectBank( enUserCollectBank );
        if( iCh >= 0 ) {
            //CCommonUtils::SendLan( enREQ_MODE, & iCh, sizeof(int) );
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

    unsigned int uiIndex, uiArrayLength, uiGetMinAnalPulse=0;

	size_t szSize;

    CCollectBank *pCollectBank;

    STR_COLLECTINFO strCollectInfo;

    // 탐지 채널 버퍼 체크
    iCh = CheckCollectBank( enDetectCollectBank );        
    if( iCh >= 0 ) {
        pCollectBank = m_pTheDetectCollectBank[iCh];
        strCollectInfo.uiTotalPDW = pCollectBank->GetTotalPDW();

        uiGetMinAnalPulse = g_pTheSysConfig->GetMinAnalPulse();

        if( strCollectInfo.uiTotalPDW >= uiGetMinAnalPulse ) {
            strCollectInfo.iCh = iCh;
            MakeStaticPDWData( pCollectBank->GetPDWData(), true );

            uiArrayLength = sizeof(UNION_HEADER) + sizeof(_PDW) * m_stPDWData.GetTotalPDW();
            g_pTheDetectAnalysis->QMsgSnd( enTHREAD_DETECTANAL_START, & m_stPDWData, uiArrayLength, & strCollectInfo, sizeof(STR_COLLECTINFO), GetThreadName() );
        }

        // 아래는 탐지 윈도우셀을 자동 재설정하도록 한다.
        pCollectBank->UpdateWindowCell();

        SendEndCollect();

    }

    // 추적 채널 버퍼 체크
    iCh = CheckCollectBank( enTrackCollectBank );
    if( iCh >= 0 ) {
        //int iMaxCh;

        pCollectBank = GetCollectBank( iCh );

        //iMaxCh = _max( iCh - DETECT_CHANNEL, _spZero );
        uiIndex = (unsigned int) max( (int)( iCh - DETECT_CHANNEL), _spZero);

        strCollectInfo.uiTotalPDW = pCollectBank->GetTotalPDW();
        strCollectInfo.iCh = iCh;
        strCollectInfo.uiAETID = m_ABTData[uiIndex].uiAETID;
        strCollectInfo.uiABTID = m_ABTData[uiIndex].uiABTID;

        MakeStaticPDWData( pCollectBank->GetPDWData(), true );
		szSize = sizeof(UNION_HEADER) + sizeof(_PDW) * m_stPDWData.GetTotalPDW();
        memcpy( & m_theTrkScnPDW.strPDW, & m_stPDWData, szSize ); // sizeof(STR_STATIC_PDWDATA) );
        memcpy( & m_theTrkScnPDW.strABTData, GetABTData(uiIndex), sizeof(SRxABTData) );

        if( strCollectInfo.uiTotalPDW >= _spAnalMinPulseCount ) {
            g_pTheTrackAnalysis->QMsgSnd( enTHREAD_KNOWNANAL_START, & m_theTrkScnPDW, sizeof(STR_TRKSCNPDWDATA), & strCollectInfo, sizeof(STR_COLLECTINFO), GetThreadName() );
        }
        // PDW 펄스 개수 부족시 위협 처리로 바로 전달
        else {
            g_pTheEmitterMerge->QMsgSnd( enTHREAD_KNOWNANAL_FAIL, & m_theTrkScnPDW, sizeof(STR_TRKSCNPDWDATA), & strCollectInfo, sizeof(STR_COLLECTINFO), GetThreadName() );
        }

    }

    // 스캔 채널 버퍼 체크
    iCh = CheckCollectBank( enScanCollectBank );        
    if( iCh >= 0 ) {
        pCollectBank = GetCollectBank( iCh );
        uiIndex = (unsigned int) max( iCh - DETECT_CHANNEL - TRACK_CHANNEL, _spZero );

        strCollectInfo.uiTotalPDW = pCollectBank->GetTotalPDW();
        strCollectInfo.iCh = iCh;
        strCollectInfo.uiAETID = m_ABTData[uiIndex].uiAETID;
        strCollectInfo.uiABTID = m_ABTData[uiIndex].uiABTID;

        MakeStaticPDWData( pCollectBank->GetPDWData(), true );
		szSize = sizeof(UNION_HEADER) + sizeof(_PDW) * m_stPDWData.GetTotalPDW();
        memcpy( & m_theTrkScnPDW.strPDW, & m_stPDWData, szSize ); //sizeof(STR_STATIC_PDWDATA) );
        memcpy( & m_theTrkScnPDW.strABTData, GetABTData(uiIndex), sizeof(SRxABTData) );

        g_pTheScanAnalysis->QMsgSnd( enTHREAD_SCANANAL_START, & m_theTrkScnPDW, sizeof(STR_TRKSCNPDWDATA), & strCollectInfo, sizeof(STR_COLLECTINFO), GetThreadName() );
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

                    LOGMSG2( enDebug, "추적 [%d] 채널에서 [%d]개 수집 완료..." , iCh, pWindowCell->uiTotalPDW );

                    pCollectBank->SetCollectMode( enCompleteCollection );
                    pCollectBank->SetCollectUpdateTime();
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
    if(  m_pMsg->x.strAnalInfo.iCh == _spZero ) {
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

    LOGMSG3( enDebug, "D[%d] 대역, [%d] 채널 에서 분석된 빔 번호[%d]의 윈도우 셀을 닫습니다." , m_pMsg->x.strAnalInfo.enBoardID, m_pMsg->x.strAnalInfo.iCh, m_pMsg->x.strAnalInfo.uiABTID );

     m_theTrackChannel.Push( m_pMsg->x.strAnalInfo.iCh );

    // 빔 정보를 기반으로 추적 및 스캔 채널을 업데이트 한다.
    //CloseTrackWindowCell( pABTData );

    CCollectBank *pCCollectBank=GetCollectBank( m_pMsg->x.strAnalInfo.iCh );
    if( pCCollectBank != NULL ) {
        pCCollectBank->CloseTrackWindowCell();
    }

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

    CCollectBank *pCCollectBank=GetCollectBank( m_pMsg->x.strAnalInfo.iCh );
    if( pCCollectBank != NULL ) {
        pCCollectBank->UpdateWindowCell( & strWindowCell );
    }

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
    int iCh=DETECT_CHANNEL;

    STR_WINDOWCELL strWindowCell;

    if( m_theTrackChannel.Pop( & iCh ) == true ) {
        memcpy( & m_ABTData[iCh-DETECT_CHANNEL], pABTData, sizeof(SRxABTData) );

        CalTrackWindowCell( & strWindowCell, pABTData );

        m_pTheCollectBank = GetCollectBank( iCh );
        if( m_pTheCollectBank != NULL ) {
            m_pTheCollectBank->UpdateWindowCell( & strWindowCell );

            CCollectBank *pCollectBank = GetCollectBank(iCh);
            STR_PDWDATA *pPDWData = pCollectBank->GetPDWData();

#ifdef _ELINT_            
            strcpy((char *)pPDWData->x.el.aucTaskID, m_pMsg->x.strAnalInfo.uniPDWHeader.el.aucTaskID );
            pPDWData->x.el.uiIsStorePDW = m_pMsg->x.strAnalInfo.uniPDWHeader.el.uiIsStorePDW;
            pPDWData->x.el.enCollectorID = m_pMsg->x.strAnalInfo.uniPDWHeader.el.enCollectorID;
            pPDWData->x.el.enBandWidth = m_pMsg->x.strAnalInfo.uniPDWHeader.el.enBandWidth;
#elif defined(_XBAND_)
            strcpy((char *)pPDWData->x.xb.aucTaskID, m_pMsg->x.strAnalInfo.uniPDWHeader.xb.aucTaskID);
            pPDWData->x.xb.uiIsStorePDW = m_pMsg->x.strAnalInfo.uniPDWHeader.xb.uiIsStorePDW;
            pPDWData->x.xb.enCollectorID = m_pMsg->x.strAnalInfo.uniPDWHeader.xb.enCollectorID;
            pPDWData->x.xb.enBandWidth = m_pMsg->x.strAnalInfo.uniPDWHeader.xb.enBandWidth;

#endif
            LOGMSG2(enDebug, " 추적 채널 설정 성공 [%d]Ch for B[%d]", iCh, pABTData->uiABTID);
        }
        else {
            LOGMSG2(enDebug, " 추적 채널 설정 실패 [%d]Ch for B[%d]", iCh, pABTData->uiABTID);
        }

        
    }
    else {
        LOGMSG( enDebug, "Nont of Track channel !!" );
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

        pstrWindowCell->uiMaxCoPDW = 100; // (unsigned int)_min(KWN_COLLECT_PDW, 100);

        uiCollectTime = UADD( 5000, fMinCollectTime );
        pstrWindowCell->uiMaxCollectTimesec = UDIV( uiCollectTime, 1000 );
        pstrWindowCell->uiMaxCollectTimems = uiCollectTime % 1000;

    }
    else {

    }
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

    // 랜 데이터를 갖고온다.
    memcpy( m_uniLanData.szFile, GetRecvData(), m_pMsg->uiArrayLength );

    // 데이터를 지정하여 지정한 행렬에 저장한다.
    //pPDWData = m_pTheDetectCollectBank[0]->GetPDW();

#ifdef _POCKETSONATA_
    m_theDataFile.ReadDataMemory( (char *) m_uniLanData.szFile, (char *) PDW_EXT, NULL, enUnitToPDW );
#elif defined(_XBAND_)
    m_theDataFile.ReadDataMemory( (char *) m_uniLanData.szFile, ( char *) PDW_EXT, NULL, enPDWToPDW );
#else
    m_theDataFile.ReadDataMemory( (char *) m_uniLanData.szFile, (char *) PDW_EXT, NULL, enUnitToPDW );
#endif

    // 추적/스캔/사용자 채널을 모의하여 해당 CCollectBank 객체에 저장한다.
    pstPDWData = m_theDataFile.GetPDWData();
    SimFilter( pstPDWData );

    // 모의 PDW 데이터를 수집 버퍼에 추가한다.
    //pCollectBank = GetCollectBank( uiCh );
    //pCollectBank->PushPDWData( pPDWData );

    //_SAFE_DELETE( m_theDataFile.m_pData )

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
        // 추적 채널 설정
        for( uj=0 ; uj < TRACK_CHANNEL ; ++uj ) {
            pCollectBank = m_pTheTrackCollectBank[uj];
            if( pCollectBank->IsFiltered( pstPDW ) == true ) {
                if( pCollectBank->IsSave() == true ) {
                    pCollectBank->PushPDWData( pstPDW, & pPDWData->x );
                }
                uiTrackCh = uj + DETECT_CHANNEL;
            }
        }

        // 추적 채널에 속하지 않은 PDW는 탐지 채널에 저장한다.
        if( uiTrackCh == 0 ) {
            for( uj=0 ; uj < DETECT_CHANNEL ; ++uj ) {
                pCollectBank = m_pTheDetectCollectBank[uj];
                if( pCollectBank->IsFiltered( pstPDW ) == true ) {
                    pCollectBank->PushPDWData( pstPDW, &pPDWData->x );
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
                    pCollectBank->PushPDWData( pstPDW, &pPDWData->x );
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
    if(  m_pMsg->x.strAnalInfo.iCh == _spZero ) {
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

    LOGMSG3( enDebug, "D[%d] 대역, [%d] 채널 에서 분석된 빔 번호[%d]의 윈도우 셀을 닫습니다." , m_pMsg->x.strAnalInfo.enBoardID, m_pMsg->x.strAnalInfo.iCh, m_pMsg->x.strAnalInfo.uiABTID );

    m_theTrackChannel.Push( m_pMsg->x.strAnalInfo.iCh );

    //GetCollectBank( m_pMsg->x.strAnalInfo.iCh )->CloseTrackWindowCell();
    CCollectBank *pCCollectBank=GetCollectBank( m_pMsg->x.strAnalInfo.iCh );
    if( pCCollectBank != NULL ) {
        pCCollectBank->CloseTrackWindowCell();
    }

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
    int iCh=TRACK_CHANNEL;

    STR_WINDOWCELL strWindowCell;

    if( m_theScanChannel.Pop( & iCh ) == true ) {
        memcpy( & m_ABTData[iCh-TRACK_CHANNEL], pABTData, sizeof(SRxABTData) );

        CalScanWindowCell( & strWindowCell, pABTData );

        CCollectBank *pCCollectBank = GetCollectBank( iCh );
        if (pCCollectBank != NULL) {
            pCCollectBank->UpdateWindowCell(&strWindowCell);
        }

        LOGMSG3( enDebug, " [%d] 대역, 스캔 [%d] 채널 에서 분석된 빔 번호[%d] 을 기반으로 윈도우 셀을 설정합니다." , m_pMsg->x.strAnalInfo.enBoardID, iCh, m_pMsg->x.strAnalInfo.uiABTID );
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

            pstrWindowCell->strPW.iLow = IPWCNVLOW( pRadarMode->fPD_TypicalMin );
            pstrWindowCell->strPW.iHgh = IPWCNVHGH( pRadarMode->fPD_TypicalMax );

            fMinCollectTime = _max( pRadarMode->fScanPrimaryTypicalMax, pRadarMode->fScanSecondaryTypicalMax );
        }
        else {
            pstrWindowCell->strFreq.iLow = I_IFRQMhzCNV( g_enBoardId, pABTData->fFreqMin );
            pstrWindowCell->strFreq.iHgh = I_IFRQMhzCNV( g_enBoardId, pABTData->fFreqMax );

            pstrWindowCell->strPW.iLow = IPWCNVLOW( pABTData->fPWMin );
            pstrWindowCell->strPW.iHgh = IPWCNVHGH( pABTData->fPWMax );

#ifndef _XBAND_
            fMinCollectTime = pABTData->fMaxScanPeriod;
#endif
        }

        pstrWindowCell->strAoa.iLow = (int) ( ( IAOACNV( pABTData->fDOAMin-10 ) + MAX_AOA ) % MAX_AOA );
        pstrWindowCell->strAoa.iHgh = (int) ( ( IAOACNV( pABTData->fDOAMax+10 ) + MAX_AOA ) % MAX_AOA );

        pstrWindowCell->uiMaxCoPDW = 1000; //  _min(SCN_COLLECT_PDW, 1000);

        uiCollectTime = UADD( 5000, fMinCollectTime );
        pstrWindowCell->uiMaxCollectTimesec = UDIV( uiCollectTime, 1000 );
        pstrWindowCell->uiMaxCollectTimems = uiCollectTime % 1000;

    }
    else {

    }
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
    STR_WINDOWCELL strWindowCell;

    // 정보 업데이트
    CalScanWindowCell( & strWindowCell, pABTData );

    //GetCollectBank( m_pMsg->x.strAnalInfo.iCh )->UpdateWindowCell( & strWindowCell );
    CCollectBank *pCCollectBank=GetCollectBank( m_pMsg->x.strAnalInfo.iCh );
    if( pCCollectBank != NULL ) {
        pCCollectBank->UpdateWindowCell( & strWindowCell );
    }

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