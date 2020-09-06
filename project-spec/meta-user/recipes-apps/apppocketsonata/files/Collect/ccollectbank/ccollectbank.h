#ifndef CCOLLECTBANK_H
#define CCOLLECTBANK_H

#include "../../Include/system.h"

#include "../../Utils/cqueue.h"

#include "../../Anal/INC/PDW.h"

class CCollectBank
{
private:
    unsigned int m_uiID;

    int m_iTotalChannels;
    int m_iChannelNo;

    STR_WINDOWCELL m_strWindowCell;

    STR_PDWDATA m_strPDW;

    static Queue<unsigned int> m_theQueueWindowCellID;

public:
    CCollectBank( int iTotalChannels, int iChannelNo );
    ~CCollectBank();

private:
    void Init();

    void InitWindowCell();
    void UpdateWindowCell();

public:
    void CloseCollectBank();

    void SetWindowCell( STR_WINDOWCELL *pSTR_WINDOWCELL );

    void CopyPDW();
    void PushPDWData( STR_PDWDATA *pstrArrayPDW );
    void PushPDWData( _PDW *pstPDW );

    ///
    void SimCollectMode();


    inline bool IsCompleteCollect() { return m_strWindowCell.enCollectMode == enCompleteCollection; }
    inline void SetCollectMode( ENUM_COLLECT_MODE enMode ) { m_strWindowCell.enCollectMode=enMode; }
    inline int GetChannelNo() { return m_strWindowCell.iChannelNo; }
    inline int GetTotalPDW() { return m_strWindowCell.uiTotalPDW; }
    inline STR_WINDOWCELL *GetWindowCell() { return & m_strWindowCell; }
    inline STR_PDWDATA *GetPDW() { return & m_strPDW; }
};


#endif // CCOLLECTBANK_H
