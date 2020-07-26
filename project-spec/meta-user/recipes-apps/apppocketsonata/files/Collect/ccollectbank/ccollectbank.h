#ifndef CCOLLECTBANK_H
#define CCOLLECTBANK_H

#include "./Include/system.h"

#include "../../Utils/cqueue.h"

class CCollectBank
{
private:
    int m_iID;

    STR_WINDOWCELL m_strWindowCell;

    STR_PDW m_strPDW;

    static Queue<int> m_theQueueWindowCellID;

public:
    CCollectBank( int iTotalChannels, int iChannelNo );
    ~CCollectBank();

public:
    void CloseCollectBank();

    void SetWindowCell( STR_WINDOWCELL *pSTR_WINDOWCELL );

    inline bool IsCompleteCollect() { return m_strWindowCell.bComplete; }
    inline int GetChannelNo() { return m_strWindowCell.iChannelNo; }
};


#endif // CCOLLECTBANK_H
