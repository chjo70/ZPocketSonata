#include <string.h>

using namespace std;

#include <algorithm>

#include "ccollectbank.h"
#include "../../Utils/clog.h"



//

/////////////////////////////////////////////////////////////////////////////////

Queue<int> CCollectBank::m_theQueueWindowCellID;

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

    m_theQueueWindowCellID.Pop( & m_iID );

    m_strWindowCell.iChannelNo = m_iChannelNo;

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

}

/**
 * @brief CCollectBank::PushPDWData
 * @param pstrArrayPDW
 */
void CCollectBank::PushPDWData( STR_PDWDATA *pPDWData )
{
    unsigned int i;
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
 * @brief 윈도우셀을 수집 종료 후에 업데이트 한다.
 */
void CCollectBank::UpdateWindowCell()
{
    // 수집한 PDW 개수 업데이트
    m_strWindowCell.uiTotalPDW = m_strPDW.uiTotalPDW;

    m_strWindowCell.uiAccumulatedTime += m_strWindowCell.uiCollectTime;

    // 누적 수집 PDW 개수 업데이트
    m_strWindowCell.uiAccumulatedCoPDW += m_strWindowCell.uiTotalPDW;

    // 누적 사용 채널 횟수 업데이트
    m_strWindowCell.uiAccumulatedCoUsed += 1;

}
