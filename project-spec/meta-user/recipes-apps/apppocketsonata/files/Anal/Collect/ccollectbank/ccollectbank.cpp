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

//#include "../../../Utils/clog.h"
#include "../../../Utils/ccommonutils.h"

#include "../../../Thread/csignalcollect.h"

#include "../../../System/csysconfig.h"
//

#include "../../../Include/globals.h"

/////////////////////////////////////////////////////////////////////////////////

Queue<unsigned int> CCollectBank::m_theQueueWindowCellID;

/**
 * @brief CCollectBank::CCollectBank
 */
CCollectBank::CCollectBank( int iTotalChannels, int iChannelNo )
    :m_iTotalChannels(iTotalChannels),
     m_iChannelNo(iChannelNo)
{

    Init();

}

/**
 * @brief CCollectBank::~CCollectBank
 */
CCollectBank::~CCollectBank()
{

}

/**
 * @brief 객체 초기화를 수행한다.
 */
void CCollectBank::Init()
{
    memset( & m_strPDW, 0, sizeof(STR_PDWDATA) );

    m_strPDW.x.ps.iBoardID = g_enBoardId;
    m_strPDW.x.ps.uiBand = g_enBoardId;

    InitWindowCell();

}

/**
 * @brief 윈도우셀을 초기화한다.
 */
void CCollectBank::InitWindowCell()
{
    memset( & m_strWindowCell, 0, sizeof(STR_WINDOWCELL) );

    // 큐가 생성되지 않았으면 한번 수행하여 ID를 저장한다.
    if( m_theQueueWindowCellID.Count() == 0 && m_iTotalChannels >= 2 ) {
        m_theQueueWindowCellID.Init( m_iTotalChannels );
        for( int i=0 ; i < m_iTotalChannels ; ++i ) {
            m_theQueueWindowCellID.Push( i );
        }
    }

    m_theQueueWindowCellID.Pop( & m_uiID );

    m_strPDW.x.ps.iBank = CCommonUtils::GetEnumCollectBank( m_uiID );

}

/**
 * @brief CCollectBank::SetWindowCell
 * @param pSTR_WINDOWCELL
 */
void CCollectBank::SetWindowCell( STR_WINDOWCELL *pSTR_WINDOWCELL )
{
    LOGENTRY;

    memcpy( & m_strWindowCell, pSTR_WINDOWCELL, sizeof(STR_WINDOWCELL) );
    g_pTheSysConfig->SetWindowCell( m_uiID, & m_strWindowCell );
}

/**
 * @brief 수집 윈도우셀 과 수집한 PDW 를 초기화한다.
 */
void CCollectBank::CloseCollectBank()
{
    LOGENTRY;

    // 구조체 초기화 한다.
    memset( & m_strWindowCell, 0, sizeof(STR_WINDOWCELL) );
    m_strWindowCell.bUse = false;
    m_strWindowCell.enCollectMode = enUnused;

    m_strPDW.uiTotalPDW = 0;

    g_pTheSysConfig->SetWindowCell( m_uiID, & m_strWindowCell );

}

/**
 * @brief CCollectBank::UpdateWindowCell
 */
void CCollectBank::UpdateWindowCell( STR_WINDOWCELL *pstrWindowCell )
{

    /**
    * @brief 최대 수집 게수 및 수집 시간
    */
    m_strWindowCell.uiMaxCoPDW = pstrWindowCell->uiMaxCoPDW;
    m_strWindowCell.uiMaxCollectTimesec = pstrWindowCell->uiMaxCollectTimesec;
    m_strWindowCell.uiMaxCollectTimems = pstrWindowCell->uiMaxCollectTimems;

    m_strWindowCell.strAoa = pstrWindowCell->strAoa;
    m_strWindowCell.strFreq = pstrWindowCell->strFreq;
    m_strWindowCell.strPA = pstrWindowCell->strPA;
    m_strWindowCell.strPW = pstrWindowCell->strPW;

    m_strWindowCell.tsCollectStart = pstrWindowCell->tsCollectStart;

    m_strWindowCell.uiCollectTime = pstrWindowCell->uiCollectTime;;

    m_strWindowCell.uiABTID = pstrWindowCell->uiABTID;

    // memcpy( & m_strWindowCell, pstrWindowCell, sizeof(STR_WINDOWCELL) );

    m_strWindowCell.bUse = true;

//    if( IsValidChannel() == true ) {
//        m_strWindowCell.enCollectMode = enCollecting;

//    }

    UpdateWindowCell();
}

/**
 * @brief CCollectBank::CloseTrackWindowCell
 * @param pstrWindowCell
 */
void CCollectBank::CloseTrackWindowCell()
{
    m_strWindowCell.bUse = false;

    m_strWindowCell.enCollectMode = enUnused;

    g_pTheSysConfig->SetWindowCell( m_uiID, & m_strWindowCell );
}

/**
 * @brief CSignalCollect::IsValidChannle
 */
bool CCollectBank::IsValidChannel()
{
    bool bRet=true;

    switch( m_strWindowCell.enCollectMode ) {
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
 * @brief CCollectBank::SimCollectMode
 */
void CCollectBank::SimCollectMode()
{
    _TOA msDTOA=0;

    struct timespec tsDiff;

    switch( m_strWindowCell.enCollectMode ) {
        case enUnused:
            break;

        case enCollecting :
            CCommonUtils::DiffTimespec( & tsDiff, & m_strWindowCell.tsCollectStart );

            if( m_strPDW.uiTotalPDW >= _spTwo ) {
                msDTOA = m_strPDW.stPDW[m_strPDW.uiTotalPDW-1].ullTOA - m_strPDW.stPDW[0].ullTOA;
            }

            // 개수 비교
            if( m_strPDW.uiTotalPDW >= m_strWindowCell.uiMaxCoPDW ) {
                m_strWindowCell.enCollectMode = enCompleteCollection;
            }
            // 시간 비교
            else if( TOAmsCNV( msDTOA ) >= m_strWindowCell.uiMaxCollectTimems + ( m_strWindowCell.uiMaxCollectTimesec * 1000 ) ) {
                m_strWindowCell.enCollectMode = enCompleteCollection;
            }
            else if( tsDiff.tv_sec >= 60 ) {
                m_strWindowCell.enCollectMode = enCompleteCollection;
            }

            if( m_strWindowCell.enCollectMode == enCompleteCollection ) {
                m_strWindowCell.uiTotalPDW = m_strPDW.uiTotalPDW;
            }

            //round( ( tsNow.tv_nsec - m_strWindowCell.tsCollectStart.tv_nsec ) / 1.0e06 ) >= uiMaxCollectTimeMSec ) {
            //printf( "[%lld]\n" , round( ( tsNow.tv_nsec - m_strWindowCell.tsCollectStart.tv_nsec ) / 1.0e06 ) );

            //m_strWindowCell.enCollectMode = enCompleteCollection;
            break;

        case enCompleteCollection :
            break;

        case enAnalysing :
            break;

        default :
            break;
    }

}

/**
 * @brief CCollectBank::PushPDWData
 * @param pstPDW
 */
void CCollectBank::PushPDWData( _PDW *pstPDW )
{

    if( m_strWindowCell.bUse == true ) {
        if( m_strPDW.uiTotalPDW+1 <= m_strWindowCell.uiMaxCoPDW ) {
            memcpy( & m_strPDW.stPDW[m_strPDW.uiTotalPDW], pstPDW, sizeof(_PDW) );

            ++ m_strPDW.uiTotalPDW;
            ++ m_strWindowCell.uiTotalPDW;
        }
        else {
            //printf( "PDW 데이터가 꽉 참 !!" );
        }
    }

    //SimCollectMode();

}

/**
 * @brief 윈도우셀을 수집 종료 후에 업데이트 한다.
 */
void CCollectBank::UpdateWindowCell()
{

    m_strWindowCell.uiAccumulatedTime += m_strWindowCell.uiCollectTime;

    // 누적 수집 PDW 개수 업데이트
    m_strWindowCell.uiAccumulatedCoPDW += m_strWindowCell.uiTotalPDW;

    // 누적 사용 채널 횟수 업데이트
    m_strWindowCell.uiAccumulatedCoUsed += 1;

    m_strWindowCell.enCollectMode = enCollecting;

    // PDW 정보 클리어
    m_strPDW.uiTotalPDW = 0;

    // 수집한 PDW 개수 업데이트
    m_strWindowCell.uiTotalPDW = 0;

    // 시간 재설정
    clock_gettime( CLOCK_REALTIME, & m_strWindowCell.tsCollectStart );

    g_pTheSysConfig->SetWindowCell( m_uiID, & m_strWindowCell );

}

/**
 * @brief CCollectBank::IsCompleteCollect
 * @return
 */
bool CCollectBank::IsCompleteCollect()
{
    bool bRet=false;
    struct timespec tsDiff;

    if( m_strWindowCell.bUse == true && m_strWindowCell.enCollectMode == enCollecting ) {
        CCommonUtils::DiffTimespec( & tsDiff, & m_strWindowCell.tsCollectStart );

        // 수집 시간 확인
        if( tsDiff.tv_sec > (long) m_strWindowCell.uiMaxCollectTimesec ||
#ifdef _MSC_VER
            ( tsDiff.tv_sec == (long) m_strWindowCell.uiMaxCollectTimesec && tsDiff.tv_usec >= (long) m_strWindowCell.uiMaxCollectTimems * 1000 ) ) {
#else
            ( tsDiff.tv_sec == m_strWindowCell.uiMaxCollectTimesec && tsDiff.tv_nsec >= m_strWindowCell.uiMaxCollectTimems * 1000000 ) ) {
#endif
            bRet = true;
        }

        // 수집 개수 확인
        if( m_strPDW.uiTotalPDW >= m_strWindowCell.uiMaxCoPDW ) {
            m_strPDW.uiTotalPDW = m_strWindowCell.uiMaxCoPDW;
            bRet = true;
        }
    }

    return bRet;   //m_strWindowCell.enCollectMode == enCompleteCollection;

}

/**
 * @brief CSignalCollect::IsFiltered
 * @param pstPDW
 * @param pWindowCell
 * @return
 */
bool CCollectBank::IsFiltered( _PDW *pstPDW )
{
    bool bRet=false;

    if( m_strWindowCell.bUse == true ) {
        bRet = CompMarginDiff<int>( (int)pstPDW->uiFreq, m_strWindowCell.strFreq.iLow, m_strWindowCell.strFreq.iHgh, 10 ) && \
               CompMarginDiff<int>( (int)pstPDW->uiPW, m_strWindowCell.strPW.iLow, m_strWindowCell.strPW.iHgh, 10 );
    }

    return bRet;
}


/**
 * @brief     SetCollectUpdateTime
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-01-25, 10:46
 * @warning
 */
void CCollectBank::SetCollectUpdateTime()
{
    __time32_t tNow;
    tNow = time( NULL );

#ifdef _MSC_VER
    m_strPDW.tColTime = tNow;

#else
    m_strPDW.tColTime = tNow;

#endif

}