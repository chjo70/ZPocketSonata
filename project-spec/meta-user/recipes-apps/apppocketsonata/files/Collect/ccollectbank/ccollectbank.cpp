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
    memset( & m_strWindowCell, 0, sizeof(STR_WINDOWCELL) );

    memset( & m_strPDW, 0, sizeof(STR_ARRAY_PDW) );

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
void CCollectBank::PushPDWData( STR_ARRAY_PDW *pstrArrayPDW )
{
    unsigned int i;
    int iTo;

    iTo = (int) ( _MAX_COL_PDW - ( m_strWindowCell.uiTotalPDW + pstrArrayPDW->uiTotalPDW ) );
    if( iTo > 0 ) {
        iTo = pstrArrayPDW->uiTotalPDW;
    }
    else {
        iTo = (int) ( _MAX_COL_PDW - m_strWindowCell.uiTotalPDW );
    }

    // PDW 정보 복사
    memcpy( & m_strPDW.uiFreq[m_strPDW.uiTotalPDW], pstrArrayPDW->uiFreq, iTo * sizeof(UINT) );
    memcpy( & m_strPDW.uiAOA[m_strPDW.uiTotalPDW], pstrArrayPDW->uiAOA, iTo * sizeof(UINT) );
    memcpy( & m_strPDW.uiPW[m_strPDW.uiTotalPDW], pstrArrayPDW->uiPW, iTo * sizeof(UINT) );
    memcpy( & m_strPDW.uiPA[m_strPDW.uiTotalPDW], pstrArrayPDW->uiPA, iTo * sizeof(UINT) );

    m_strPDW.uiTotalPDW += iTo;

    m_strWindowCell.enCollectMode = enCompleteCollection;

}
