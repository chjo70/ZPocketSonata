#ifndef CUSERCOLLECT_H
#define CUSERCOLLECT_H

#include "../Include/system.h"
#include "../Utils/cthread.h"

#include "../Anal/Collect/DataFile/CRWRCommonVariables.h"

class CUserCollect : public CThread
{
private:
    static CUserCollect *m_pInstance;

    STR_MessageData *m_pMsg;

    STR_RES_COL_START m_strResColStart;

    DMAPDW *m_pstrDMAPDW;
    char *m_pstrDMAPDWWithFileHeader;

    unsigned int m_uiColStart;

    // SIM 모의 데이터 생성하기 위한 변수
    unsigned int m_uiIndex;
    _TOA m_ullTOA;

    unsigned int m_uiCoSim;

private:
    void InitVar();
    void AllocMemory();
    void FreeMemory();

    // 수집 제어 관련 함수
    void SetConfig();
    void Stop();
    void ColStart();
    void SendRawData();

    void MakeSIMPDWData();

public:
    CUserCollect( int iKeyId, char *pClassName=NULL, bool bArrayLanData=false );
    virtual ~CUserCollect();

    THREAD_STANDARD_FUNCTION( CUserCollect )
};

#define UCOL   CUserCollect::GetInstance()

#endif // CUSERCOLLECT_H
