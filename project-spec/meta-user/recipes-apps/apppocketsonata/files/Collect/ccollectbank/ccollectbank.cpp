#include <string.h>

#include "ccollectbank.h"
#include "../../Utils/clog.h"



//

/////////////////////////////////////////////////////////////////////////////////

Queue<int> CCollectBank::m_theQueueWindowCellID;

/**
 * @brief CCollectBank::CCollectBank
 */
CCollectBank::CCollectBank( int iTotalChannels, int iChannelNo )
{

    memset( & m_strWindowCell, 0, sizeof(STR_WINDOWCELL) );

    memset( & m_strPDW, 0, sizeof(STR_PDW) );

    // 큐가 생성되지 않았으면 한번 수행하여 ID를 저장한다.
    if( m_theQueueWindowCellID.Count() == 0 && iTotalChannels >= 2 ) {
        m_theQueueWindowCellID.Init( iTotalChannels );
        for( int i=0 ; i < iTotalChannels ; ++i ) {
            m_theQueueWindowCellID.Push( i );
        }
    }

    m_theQueueWindowCellID.Pop( & m_iID );

    m_strWindowCell.iChannelNo = iChannelNo;


}

/**
 * @brief CCollectBank::~CCollectBank
 */
CCollectBank::~CCollectBank()
{

}

/**
 * @brief CCollectBank::SetWindowCell
 * @param pSTR_WINDOWCELL
 */
void CCollectBank::SetWindowCell( STR_WINDOWCELL *pSTR_WINDOWCELL )
{
    LOGENTRY;
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
