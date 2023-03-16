// CCollectBank.cpp: implementation of the CCollectBank class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include <string.h>

#include "../../OFP_Main.h"

using namespace std;

#include <algorithm>

#include "ccollectbank.h"
#include "../DataFile/DataFile.h"

#include "../../../Utils/ccommonutils.h"

#include "../../../Thread/csignalcollect.h"

#include "../../../System/csysconfig.h"

#include "../../../Include/globals.h"

extern std::string g_strPCIDrverDirection[en_ELEMENT_PCI_DRIVER];


/////////////////////////////////////////////////////////////////////////////////

//Queue<unsigned int> CCollectBank::m_theQueueWindowCellID;

/**
 * @brief     객체 초기화를 수행합니다.
 * @param     int iTotalChannels
 * @param     int iChannelNo
 * @return
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-07-10 12:46:48
 * @warning
 */
CCollectBank::CCollectBank( unsigned int uiDetectChannel, unsigned int uiTracnChannel, unsigned int uiScanChannel, ENUM_PCI_DRIVER enPCIDriver )
    :m_uiDetectChannle( uiDetectChannel ),
     m_uiTrackChannle( uiTracnChannel ),
     m_uiScanChannle( uiScanChannel ),
     m_uiTotalChannels( uiDetectChannel + uiTracnChannel + uiScanChannel ),
     m_enPCIDriver( enPCIDriver )
{
    // 메모리를 할당 합니다.
    Alloc();

    // 구조체 및 변수를 초기화 합니다.
    Init();

}

/**
 * @brief     ~CCollectBank
 * @return
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-07-10 12:03:25
 * @warning
 */
CCollectBank::~CCollectBank()
{

    Free();
}

/**
 * @brief     Alloc
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-03-06 11:19:44
 * @warning
 */
void CCollectBank::Alloc()
{
    unsigned int i;
    unsigned int uiCh;
    STR_WINDOWCELL* pstWindowCell;

    m_pstrWindowCell = ( STR_WINDOWCELL** ) malloc( sizeof( STR_WINDOWCELL* ) * (unsigned int) m_uiTotalChannels );
    if( m_pstrWindowCell == NULL ) {
        Log( enError, "메모리 할당 에러[CCollectBank::m_pstrWindowCell] !" );
    }

    uiCh = 0;
    for( i = 0; i < m_uiTotalChannels; ++i ) {
        m_pstrWindowCell[uiCh] = ( STR_WINDOWCELL* ) malloc( sizeof( STR_WINDOWCELL ) );

        pstWindowCell = m_pstrWindowCell[uiCh];

        // m_strPDW.pstPDW = NULL;
        pstWindowCell->strPDW.pstPDW = ( _PDW * ) malloc( sizeof( _PDW ) * MAX_PDW );
        if( pstWindowCell->strPDW.pstPDW == NULL ) {
            Log( enError, "메모리 할당 에러[CCollectBank::pstWindowCell->strPDW.pstPDW] !" );
        }

        ++uiCh;
    }

    m_pThePCI = new CPCIDriver( m_enPCIDriver );

}

/**
 * @brief     Free
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-03-06 12:07:13
 * @warning
 */
void CCollectBank::Free()
{
    unsigned int i;

    for( i = 0; i < m_uiTotalChannels; ++i ) {
        free( m_pstrWindowCell[i]->strPDW.pstPDW );
        free( m_pstrWindowCell[i] );
    }

    free( m_pstrWindowCell );

    delete m_pThePCI;
}

/**
 * @brief     객체 초기화를 수행한다.
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-07-10 12:03:34
 * @warning
 */
void CCollectBank::Init()
{
    unsigned int uiCh;

    // 객체 관련 멤버 변수 초기화를 수행합니다.
    for( uiCh = 0; uiCh < (unsigned int) m_uiTotalChannels; ++uiCh ) {
        InitWindowCell( uiCh );

    }

    // PCI 핸들 관련 초기화를 수행합니다.
    m_pThePCI->Init();

	// 탐지는 1서부터 시작하고 추적/스캔은 0 부터 시작한다.
	// 이렇게 해야 PDWID는 1부터 매기게 된다.
    //m_strPDW.SetPDWID( _spOne );

    //m_strPDW.SetBoardID( (unsigned int) g_enBoardId );
    //m_strPDW.SetBand((unsigned int) g_enBoardId );

    // InitWindowCell();

}

/**
 * @brief     InitWindowCell
 * @param     unsigned int uiCh
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-03-06 14:08:37
 * @warning
 */
void CCollectBank::InitWindowCell( unsigned int uiCh )
{
    STR_WINDOWCELL* pstWindowCell;

    pstWindowCell = m_pstrWindowCell[uiCh];

    pstWindowCell->Init( uiCh );

    ENUM_COLLECTBANK enBank = GetEnumCollectBank( uiCh );
    pstWindowCell->strPDW.SetBank( enBank );

}

/**
 * @brief     신호 수집을 시작합니다.
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-03-07 11:26:50
 * @warning
 */
void CCollectBank::StartCollecting()
{
    m_pThePCI->StartCollecting();

}

/**
 * @brief     수집 뱅크를 리턴합니다.
 * @param     unsigned int uiCh
 * @return    ENUM_COLLECTBANK
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-03-06 14:02:41
 * @warning
 */
ENUM_COLLECTBANK CCollectBank::GetEnumCollectBank( unsigned int uiCh ) const
{
    ENUM_COLLECTBANK enCollectBank = enUnknownCollectBank;

    if( uiCh < m_uiDetectChannle ) {
        enCollectBank = enDetectCollectBank;
    }
    else if( uiCh < m_uiDetectChannle + m_uiTrackChannle ) {
        enCollectBank = enTrackCollectBank;
    }
    else if( uiCh < m_uiDetectChannle + m_uiTrackChannle + m_uiScanChannle ) {
        enCollectBank = enScanCollectBank;
    }
    else {
        enCollectBank = enUserCollectBank;
    }

    return enCollectBank;
}

/**
 * @brief     윈도우 셀 설정 값을 설정합니다.
 * @param     STR_WINDOWCELL * pSTR_WINDOWCELL
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-07-10 12:46:27
 * @warning
 */
void CCollectBank::SetWindowCell( STR_WINDOWCELL *pstWindowCell )
{
    pstWindowCell->uiTotalPDW = 0;

    // 수집 시간 업데이트
    clock_gettime( CLOCK_REALTIME, & pstWindowCell->tsCollectStart );

    pstWindowCell->bUse = true;

    // 전처리 필터 세팅
    m_pThePCI->StartCollecting( pstWindowCell );

    //memcpy( & m_strWindowCell, pSTR_WINDOWCELL, sizeof(STR_WINDOWCELL) );
    //g_pTheSysConfig->SetWindowCell( (UINT) m_iChannelNo, & m_strWindowCell );
}

/**
 * @brief     CloseCollectBanks
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-03-07 10:30:00
 * @warning
 */
void CCollectBank::CloseCollectBanks()
{
    unsigned int i;

    m_pThePCI->EndCollecting();

    // 변수를 초기화 합니다.
    Init();

//     // 구조체 초기화 한다.
//     for( i = 0; i < m_uiTotalChannels; ++i ) {
//         CloseCollectBank( i );
//     }


}

/**
 * @brief     수집 뱅크를 닫는다.
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-07-10 12:47:35
 * @warning
 */
void CCollectBank::CloseCollectBank( unsigned int uiCh )
{
    struct timespec tsDiff;

    STR_WINDOWCELL*pstWindowCell = GetWindowCell( uiCh );

    pstWindowCell->uiAccumulatedCoPDW += pstWindowCell->uiTotalPDW;

    ++pstWindowCell->uiAccumulatedCoUsed;

    CCommonUtils::DiffTimespec( & tsDiff, &pstWindowCell->tsCollectStart );
#ifdef _MSC_VAER
    pstWindowCell->uiAccumulatedTime += (unsigned int) ( ( tsDiff.tv_sec * 1000 ) + ( tsDiff.tv_usec / 1000 ) );
#else
    printf( "\n [%d.%d]" , tsDiff.tv_sec, tsDiff.tv_usec );
    pstWindowCell->uiAccumulatedTime = 0;
#endif

    pstWindowCell->SetCollectMode( enColseCollection );

    // 선택한 채널에 대해서 초기화를 수행 합니다.
    m_pThePCI->CloseChannel( uiCh );

    // pWindowCell->

    g_pTheSysConfig->SetWindowCell( (UINT) uiCh, pstWindowCell );

}

/**
 * @brief     윈도우 값을 설정 합니다.
 * @param     unsigned int uiCh
 * @param     STR_WINDOWCELL * pstrWindowCell
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-03-06 14:28:50
 * @warning
 */
void CCollectBank::UpdateWindowCell( unsigned int uiCh, STR_WINDOWCELL *pstrWindowCell )
{
    STR_WINDOWCELL* pWindowCell = GetWindowCell( uiCh );

    if( pstrWindowCell != NULL ) {
        pWindowCell->uiCoCollectingPDW = pstrWindowCell->uiCoCollectingPDW;
        pWindowCell->uiMaxCollectTimesec = pstrWindowCell->uiMaxCollectTimesec;
        pWindowCell->uiMaxCollectTimeMssec = pstrWindowCell->uiMaxCollectTimeMssec;

        pWindowCell->strAoa = pstrWindowCell->strAoa;
        pWindowCell->strFreq = pstrWindowCell->strFreq;
        pWindowCell->strPA = pstrWindowCell->strPA;
        pWindowCell->strPW = pstrWindowCell->strPW;

        pWindowCell->tsCollectStart = pstrWindowCell->tsCollectStart;

        pWindowCell->uiCollectTime = pstrWindowCell->uiCollectTime;

        pWindowCell->uiABTID = pstrWindowCell->uiABTID;
    }

    // memcpy( & m_strWindowCell, pstrWindowCell, sizeof(STR_WINDOWCELL) );

    pWindowCell->bUse = true;

    ///////////////////////////////////////////////////////////////////////////////////
    // 추가 정보 업데이트
    pWindowCell->uiAccumulatedTime += pWindowCell->uiCollectTime;

    // 누적 수집 PDW 개수 업데이트
    pWindowCell->uiAccumulatedCoPDW += pWindowCell->uiTotalPDW;

    // 누적 사용 채널 횟수 업데이트
    pWindowCell->uiAccumulatedCoUsed += 1;

    pWindowCell->enCollectMode = enCollecting;

    // 수집한 PDW 개수 업데이트
    pWindowCell->uiTotalPDW = 0;

    // PDW 정보 클리어
    pWindowCell->strPDW.SetTotalPDW( 0 );

    // 시간 재설정
    clock_gettime( CLOCK_REALTIME, & pWindowCell->tsCollectStart );

    //g_pTheSysConfig->SetWindowCell( ( UINT ) uiCh, &m_strWindowCell );

    //UpdateWindowCell();
}

/**
 * @brief     추적 윈도우셀을 닫는다.
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-07-10 12:47:21
 * @warning
 */
void CCollectBank::CloseTrackWindowCell()
{
//     m_strWindowCell.bUse = false;
//
//     m_strWindowCell.enCollectMode = enUnused;
//
//     g_pTheSysConfig->SetWindowCell( (UINT) m_iChannelNo, & m_strWindowCell );
}

/**
 * @brief     유효 채널을 확인한다.
 * @return    bool
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-07-10 12:47:47
 * @warning
 */
bool CCollectBank::IsValidChannel()
{
    bool bRet=true;

//     switch( m_strWindowCell.enCollectMode ) {
//         case enUnused:
//             break;
//         case enCollecting:
//             bRet = false;
//             break;
//         case enCompleteCollection:
//             break;
//
//         default :
//             break;
//    }
//
//    if( bRet == false ) {
//        printf( "IsValidChannle\n" );
//    }

   return bRet;

}

/**
 * @brief CCollectBank::PushPDWData
 * @param pstrArrayPDW
 */
// void CCollectBank::PushPDWData( STR_PDWDATA *pPDWData )
// {
//     int iTo;
//
//     iTo = (int) ( _MAX_COL_PDW - ( m_strWindowCell.uiTotalPDW + pPDWData->uiTotalPDW ) );
//     if( iTo > 0 ) {
//         iTo = pPDWData->uiTotalPDW;
//         m_strPDW.uiTotalPDW = iTo;
//     }
//     else {
//         iTo = (int) ( _MAX_COL_PDW - m_strWindowCell.uiTotalPDW );
//         m_strPDW.uiTotalPDW = _MAX_COL_PDW;
//     }
//
//     // PDW 정보 복사
//     UINT uiTo;
//     if( iTo > 0 ) {
//         uiTo = (unsigned int) iTo * sizeof(_PDW);
//
//         memcpy( & m_strPDW.stPDW[m_strPDW.uiTotalPDW], & pPDWData->stPDW[0], uiTo );
//     }
//
//     // 추적 윈도우 셀 정보 업데이트
//     UpdateWindowCell();
//
//     //m_strWindowCell.uiCollectTime = DecodeTOA( m_strPDW.llToa[m_strPDW.uiTotalPDW-1] - m_strPDW.llToa[0] );
//
//     // 수집 완료 마킹함.
//     m_strWindowCell.enCollectMode = enCompleteCollection;
//
// }

/**
 * @brief     _PDW 구조체 데이터를 수집뱅크 구조체의 데이터에 삽입한다.
 * @param     _PDW * pstPDW
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-05-10, 14:00
 * @warning
 */
void CCollectBank::PushPDWData( unsigned int uiCh, _PDW *pstPDW, UNION_HEADER *pHeader )
{
    STR_WINDOWCELL *pWindowCell;

    unsigned int uiTotalPDW;

    pWindowCell = GetWindowCell( uiCh );

    if( pWindowCell->bUse == true ) {
        uiTotalPDW = pWindowCell->strPDW.GetTotalPDW();

        if( uiTotalPDW+1 <= pWindowCell->uiCoCollectingPDW ) {
            memcpy( &pWindowCell->strPDW.x, pHeader, sizeof( UNION_HEADER ) );

            memcpy( &pWindowCell->strPDW.pstPDW[uiTotalPDW], pstPDW, sizeof(_PDW) );

            ++ uiTotalPDW;
            pWindowCell->strPDW.SetTotalPDW( uiTotalPDW );

            ++pWindowCell->uiTotalPDW;
        }
        else {
            //printf( "PDW 데이터가 꽉 참 !!" );
        }
    }

    SimCollectMode( uiCh );

}

/**
 * @brief     수집 완료됨을 체크한다.
 * @return    bool
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-07-10 12:47:01
 * @warning
 */
bool CCollectBank::IsCompleteCollect( unsigned int uiCh )
{
    bool bRet;// = false;
    //struct timespec tsDiff;

    STR_WINDOWCELL *pWindowCell = GetWindowCell( uiCh );

//     if( pWindowCell->bUse == true && pWindowCell->enCollectMode == enCollecting ) {
//         CCommonUtils::DiffTimespec( & tsDiff, &pWindowCell->tsCollectStart );
//
//         // 수집 시간 확인
//         if( tsDiff.tv_sec > (long) pWindowCell->uiMaxCollectTimesec ||
// #ifdef _MSC_VER
//         ( tsDiff.tv_sec == (long) pWindowCell->uiMaxCollectTimesec && tsDiff.tv_usec >= (long) pWindowCell->uiMaxCollectTimems * 1000 ) ) {
// #else
//         ( tsDiff.tv_sec == pWindowCell->uiMaxCollectTimesec && tsDiff.tv_nsec >= pWindowCell->uiMaxCollectTimems * 1000000 ) ) {
// #endif
//             bRet = true;
//         }
//
//         // 수집 개수 확인
//         unsigned int uiTotalPDW= GetPDWData(uiCh)->GetTotalPDW();
//
//         if(uiTotalPDW >= pWindowCell->uiCoCollectingPDW ) {
//             GetPDWData(uiCh)->SetTotalPDW( pWindowCell->uiCoCollectingPDW );
//             bRet = true;
//         }
//     }

    return pWindowCell->enCollectMode == enCompleteCollection;

}

/**
 * @brief     StartDetectChannel
 * @param     unsigned int uiCh
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-03-14 10:08:56
 * @warning
 */
void CCollectBank::StartDetectChannel( unsigned int uiCh )
{
    STR_WINDOWCELL *pWindowCell;

    // 윈도우 정보 얻기
    pWindowCell = GetWindowCell( uiCh );

    // 계산하기
    CalDetectWindowCell( pWindowCell );

    // 세팅하기
    SetWindowCell( pWindowCell );

}

/**
 * @brief     CalDetectWindowCell
 * @param     STR_WINDOWCELL * pstWindowCell
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-03-06 15:31:15
 * @warning
 */
void CCollectBank::CalDetectWindowCell( STR_WINDOWCELL *pstWindowCell )
{
    pstWindowCell->enCollectMode = enCollecting;

    pstWindowCell->uiCoCollectingPDW = NEW_COLLECT_PDW;
    pstWindowCell->uiMaxCollectTimesec = 0;
#ifdef _MSC_VER
    pstWindowCell->uiMaxCollectTimeMssec = 100;
#else
    pstWindowCell->uiMaxCollectTimeMssec = 250;
#endif

    pstWindowCell->strAoa.iLow = ( int ) IAOACNV( 0 );
    pstWindowCell->strAoa.iHgh = ( int ) IAOACNV( 360. );

    pstWindowCell->strFreq.iLow = 0; // IFRQMhzCNV( 0, MIN_FREQ_MHZ );
    pstWindowCell->strFreq.iHgh = 0x7fffffff - 100000; // IFRQMhzCNV( 0, MAX_FREQ_MHZ );

    pstWindowCell->strPA.iLow = ( int ) IPACNV( -90 );
    pstWindowCell->strPA.iHgh = ( int ) IPACNV( 0 );

    pstWindowCell->strPW.iLow = IPWCNV( 0 );
    pstWindowCell->strPW.iHgh = IPWCNV( 100000 );

}

/**
 * @brief     입력한 PDW 데이터가 윈도우 셀 통과 여부를 문의한다.
 * @param     _PDW * pstPDW
 * @return    bool
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-07-10 12:48:40
 * @warning
 */
bool CCollectBank::IsFiltered( unsigned int uiCh, _PDW *pstPDW )
{
    bool bRet=false;

    STR_WINDOWCELL *pstrWindowCell;

    pstrWindowCell = m_pstrWindowCell[uiCh];

     if( pstrWindowCell->bUse == true && pstrWindowCell->enCollectMode == enCollecting ) {
         bRet = CompMarginDiff<int>( (int)pstPDW->uiFreq, pstrWindowCell->strFreq.iLow, pstrWindowCell->strFreq.iHgh, 10 ) && \
                CompMarginDiff<int>( (int)pstPDW->uiPW, pstrWindowCell->strPW.iLow, pstrWindowCell->strPW.iHgh, 10 );
     }

    return bRet;
}


/**
 * @brief     윈도우셀에 시간 정보를 업데이트 한다.
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-01-25, 10:46
 * @warning
 */
void CCollectBank::SetCollectUpdateTime( unsigned int uiCh )
{
    time_t tNow;
    tNow = time( NULL );

    GetPDWData(uiCh)->SetColTime( tNow, 0 );

}


// CCollectBank* CCollectBank::GetCollectBank( unsigned int uiCh )
// {
//     CCollectBank* pCCollectBank = NULL;
//
//     if( iCh >= 0 ) {
//         if( iCh < CO_DETECT_CHANNEL )
//             pCCollectBank = m_pTheDetectCollectBank[iCh];
//         else if( iCh < CO_DETECT_CHANNEL + CO_TRACK_CHANNEL )
//             pCCollectBank = m_pTheTrackCollectBank[iCh - CO_DETECT_CHANNEL];
//         else if( iCh < CO_DETECT_CHANNEL + CO_TRACK_CHANNEL + CO_SCAN_CHANNEL )
//             pCCollectBank = m_pTheScanCollectBank[iCh - CO_DETECT_CHANNEL - CO_TRACK_CHANNEL];
//         else
//             pCCollectBank = m_pTheUserCollectBank[iCh - CO_DETECT_CHANNEL - CO_TRACK_CHANNEL - CO_SCAN_CHANNEL];
//     }
//     else {
//         TRACE( "잘못된 채널 번호 입니다." );
//     }
//
//     return pCCollectBank;
//
// }

#ifdef _SIM_PDW_

/**
 * @brief     채널을 모의하기 위한 함수 입니다.
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-07-10 12:48:01
 * @warning
 */
void CCollectBank::SimCollectMode( unsigned int uiCh )
{
    _TOA msDTOA = 0;

    unsigned int uiTotalPDW;

    struct timespec tsDiff;

    STR_WINDOWCELL *pWindowCell = GetWindowCell( uiCh );

    double d;

    switch( pWindowCell->enCollectMode ) {
        case enUnused:
            break;

        case enCollecting:
            CCommonUtils::DiffTimespec( &tsDiff, &pWindowCell->tsCollectStart );

            uiTotalPDW = GetTotalPDW( uiCh );

            if( uiTotalPDW >= _spTwo ) {
                msDTOA = GetPDWData( uiCh )->pstPDW[uiTotalPDW - 1].ullTOA - GetPDWData( uiCh )->pstPDW[0].ullTOA;
            }

            d = TOAmsCNV( msDTOA );

            // 개수 비교
            if( uiTotalPDW >= pWindowCell->uiCoCollectingPDW ) {
                pWindowCell->enCollectMode = enCompleteCollection;
            }
            // 시간 비교
            else if( TOAmsCNV( msDTOA ) >= (double) ( pWindowCell->uiMaxCollectTimeMssec + ( pWindowCell->uiMaxCollectTimesec * 1000 ) ) ) {
                pWindowCell->enCollectMode = enCompleteCollection;
            }
            else if( tsDiff.tv_sec >= 60 ) {
                //                 m_strWindowCell.enCollectMode = enCompleteCollection;
            }
            else {

            }

            if( pWindowCell->enCollectMode == enCompleteCollection ) {
                pWindowCell->uiTotalPDW = uiTotalPDW;
            }

            //round( ( tsNow.tv_nsec - m_strWindowCell.tsCollectStart.tv_nsec ) / 1.0e06 ) >= uiMaxCollectTimeMSec ) {
            //printf( "[%lld]\n" , round( ( tsNow.tv_nsec - m_strWindowCell.tsCollectStart.tv_nsec ) / 1.0e06 ) );

//                 m_strWindowCell.enCollectMode = enCompleteCollection;
            break;

        case enCompleteCollection:
            break;

        case enAnalysing:
            break;

        default:
            break;
    }

}

/**
 * @brief     CheckCollectBank
 * @param     ENUM_COLLECTBANK enCollectBank
 * @return    int
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-03-14 11:56:16
 * @warning
 */
int CCollectBank::CheckCollectBank( ENUM_COLLECTBANK enCollectBank )
{
    int iCh = -1;
    unsigned int uiCh;

    STR_WINDOWCELL *pTheWindowCell;

    // 채널을 랜덤 또는 증가/감소 교대로 번갈아 가며 체크한다.
    switch( enCollectBank ) {
        case enDetectCollectBank:
            for( uiCh = 0; uiCh < CO_DETECT_CHANNEL; ++uiCh ) {
                if( true == IsCompleteCollect( uiCh ) ) {
                    pTheWindowCell = GetWindowCell( uiCh );

                    LOGMSG3( enDebug, "[%s]에서 탐지 채널[%d]에서 [%d]개 수집 완료", g_strPCIDrverDirection[m_enPCIDriver].c_str(), uiCh, pTheWindowCell->uiTotalPDW );

                    //pCollectBank->SetCollectMode( ui, enCompleteCollection );
                    SetCollectUpdateTime( uiCh );
                    iCh = ( int ) uiCh;
                    break;
                }
                else {
                    // 아래는 탐지 윈도우셀을 자동 재설정하도록 한다.
    //                     pWindowCell = pCollectBank->GetWindowCell();
                        //pCollectBank->UpdateWindowCell();
                        //SendEndCollect();

                }

            }
            break;

            //         case enTrackCollectBank :
            //             for( i=0 ; i < CO_TRACK_CHANNEL ; ++i ) {
            //                 pCollectBank = m_pTheTrackCollectBank[i];
            //
            //                 if( true == pCollectBank->IsCompleteCollect() ) {
            //                     pWindowCell = pCollectBank->GetWindowCell();
            //                     iCh = pCollectBank->GetChannelNo();
            //
            //                     LOGMSG2( enDebug, "추적 [%d] 채널에서 [%d]개 수집 완료..." , iCh, pWindowCell->uiTotalPDW );
            //
            //                     pCollectBank->SetCollectMode( enCompleteCollection );
            //                     pCollectBank->SetCollectUpdateTime();
            //                     break;
            //                 }
            //             }
            //             break;
            //
            //         case enScanCollectBank :
            //             for( i=0 ; i < CO_SCAN_CHANNEL ; ++i ) {
            //                 pCollectBank = m_pTheScanCollectBank[i];
            //                 if( true == pCollectBank->IsCompleteCollect() ) {
            //                     pWindowCell = pCollectBank->GetWindowCell();
            //                     iCh = m_pTheScanCollectBank[i]->GetChannelNo();
            //
            //                     LOGMSG2( enDebug, " 스캔 뱅크 [%2d]채널에서 [%d]개를 수집 완료되었습니다." , iCh, pWindowCell->uiTotalPDW );
            //
            //                     //pCollectBank->SetCollectMode( enCompleteCollection );
            //                     pCollectBank->CloseTrackWindowCell();
            //                     break;
            //                 }
            //             }
            //             break;
            //
            //         case enUserCollectBank :
            //             for( i=0 ; i < CO_USER_CHANNEL ; ++i ) {
            //                 if( true == m_pTheUserCollectBank[i]->IsCompleteCollect() ) {
            //                     iCh = m_pTheUserCollectBank[i]->GetChannelNo();
            //
            //                     LOGMSG2( enDebug, "\n 사용자 뱅크[%d]에서 [%d] 채널에서 수집 완료되었습니다." , i, iCh );
            //                     break;
            //                 }
            //             }
            //             break;
            //
        default:
            break;
    }

    return iCh;

}

#endif