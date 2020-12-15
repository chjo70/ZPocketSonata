#include <string.h>

#include "../../Anal/OFP_Main.h"

using namespace std;

#include <algorithm>

#include "ccollectbank.h"
#include "../DataFile/DataFile.h"

#include "../../Utils/clog.h"
#include "../../Utils/ccommonutils.h"


//

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

    m_strPDW.iBoardID = g_enBoardId;

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

    m_strPDW.iBank = CCommonUtils::GetEnumCollectBank( m_uiID );

}

/**
 * @brief CCollectBank::SetWindowCell
 * @param pSTR_WINDOWCELL
 */
void CCollectBank::SetWindowCell( STR_WINDOWCELL *pSTR_WINDOWCELL )
{
    LOGENTRY;

    memcpy( & m_strWindowCell, pSTR_WINDOWCELL, sizeof(STR_WINDOWCELL) );
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
    m_strWindowCell.enCollectMode = enCollecting;

    m_strPDW.uiTotalPDW = 0;

}

/**
 * @brief CCollectBank::UpdateTrackWindowCell
 */
void CCollectBank::UpdateTrackWindowCell( STR_WINDOWCELL *pstrWindowCell )
{

    memcpy( & m_strWindowCell, pstrWindowCell, sizeof(STR_WINDOWCELL) );

    m_strWindowCell.bUse = true;

    if( IsValidChannel() == true ) {
        m_strWindowCell.enCollectMode = enCollecting;

    }

    UpdateWindowCell();
}

/**
 * @brief CCollectBank::CloseTrackWindowCell
 * @param pstrWindowCell
 */
void CCollectBank::CloseTrackWindowCell( STR_WINDOWCELL *pstrWindowCell )
{
    m_strWindowCell.bUse = false;

    m_strWindowCell.enCollectMode = enUnused;
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
void CCollectBank::PushPDWData( STR_PDWDATA *pPDWData )
{
    int iTo;

    iTo = (int) ( _MAX_COL_PDW - ( m_strWindowCell.uiTotalPDW + pPDWData->uiTotalPDW ) );
    if( iTo > 0 ) {
        iTo = pPDWData->uiTotalPDW;
        m_strPDW.uiTotalPDW = iTo;
    }
    else {
        iTo = (int) ( _MAX_COL_PDW - m_strWindowCell.uiTotalPDW );
        m_strPDW.uiTotalPDW = _MAX_COL_PDW;
    }

    // PDW 정보 복사
    memcpy( & m_strPDW.stPDW[m_strPDW.uiTotalPDW], & pPDWData->stPDW[0], iTo * sizeof(_PDW) );

    // 추적 윈도우 셀 정보 업데이트
    UpdateWindowCell();

    //m_strWindowCell.uiCollectTime = DecodeTOA( m_strPDW.llToa[m_strPDW.uiTotalPDW-1] - m_strPDW.llToa[0] );

    // 수집 완료 마킹함.
    m_strWindowCell.enCollectMode = enCompleteCollection;

}

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
                msDTOA = m_strPDW.stPDW[m_strPDW.uiTotalPDW-1].llTOA - m_strPDW.stPDW[0].llTOA;
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

            //round( ( tsNow.tv_nsec - m_strWindowCell.tsCollectStart.tv_nsec ) / 1.0e06 ) >= uiMaxCollectTimeMSec ) {
            //printf( "[%ld]\n" , round( ( tsNow.tv_nsec - m_strWindowCell.tsCollectStart.tv_nsec ) / 1.0e06 ) );

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
    // 수집한 PDW 개수 업데이트
    m_strWindowCell.uiTotalPDW = 0;

    m_strWindowCell.uiAccumulatedTime += m_strWindowCell.uiCollectTime;

    // 누적 수집 PDW 개수 업데이트
    m_strWindowCell.uiAccumulatedCoPDW += m_strWindowCell.uiTotalPDW;

    // 누적 사용 채널 횟수 업데이트
    m_strWindowCell.uiAccumulatedCoUsed += 1;

    m_strWindowCell.enCollectMode = enCollecting;

    // PDW 정보 클리어
    m_strPDW.uiTotalPDW = 0;

    // 시간 재설정
    clock_gettime( CLOCK_REALTIME, & m_strWindowCell.tsCollectStart );

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
        if( tsDiff.tv_sec > m_strWindowCell.uiMaxCollectTimesec ||
            ( tsDiff.tv_sec == m_strWindowCell.uiMaxCollectTimesec && tsDiff.tv_nsec >= m_strWindowCell.uiMaxCollectTimems * 1000000 ) ) {
            //bRet = true;
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
        bRet = CompMarginDiff<int>( pstPDW->iFreq, m_strWindowCell.strFreq.iLow, m_strWindowCell.strFreq.iHgh, 10 ) && \
               CompMarginDiff<int>( pstPDW->iPW, m_strWindowCell.strPW.iLow, m_strWindowCell.strPW.iHgh, 10 );
    }

    return bRet;
}
