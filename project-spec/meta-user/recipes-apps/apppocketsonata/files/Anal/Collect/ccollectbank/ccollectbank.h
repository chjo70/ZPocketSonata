#ifndef CCOLLECTBANK_H
#define CCOLLECTBANK_H

#include "../../../Include/system.h"

#include "../../../Anal/EmitterMerge/Stack.h"

#include "../../../Anal/INC/PDW.h"

class CCollectBank
{
private:
    int m_iTotalChannels;
    int m_iChannelNo;

    STR_WINDOWCELL m_strWindowCell;

    STR_PDWDATA m_strPDW;

public:
    CCollectBank( int iTotalChannels, int iChannelNo );
    ~CCollectBank();

private:
    void Init();

    void InitWindowCell();
    bool IsValidChannel();

public:
    void CloseCollectBank();
    void UpdateWindowCell();
    bool IsCompleteCollect();

    void SetWindowCell( STR_WINDOWCELL *pSTR_WINDOWCELL );

    //void PushPDWData( STR_PDWDATA *pstrArrayPDW );
    void PushPDWData( _PDW *pstPDW, UNION_HEADER *pHeader );
    void UpdateWindowCell( STR_WINDOWCELL *pstrWindowCell );
    void CloseTrackWindowCell();

    bool IsFiltered( _PDW *pstPDW );

    void SetCollectUpdateTime();

	// 모의 관련 함수
	void SimCollectMode();

	// 인라인 함수 모음
    inline void SetCollectMode( ENUM_COLLECT_MODE enMode ) { m_strWindowCell.enCollectMode=enMode; }
    inline int GetChannelNo() { return m_iChannelNo; }
    inline unsigned int GetTotalPDW() { return m_strWindowCell.uiTotalPDW; }
    inline STR_WINDOWCELL *GetWindowCell() { return & m_strWindowCell; }
    inline STR_PDWDATA *GetPDWData() { return & m_strPDW; }
    inline bool IsSave() { return m_strWindowCell.enCollectMode == enCollecting; }
};


#endif // CCOLLECTBANK_H
