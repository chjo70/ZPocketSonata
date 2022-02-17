#ifndef CUSERCOLLECT_H
#define CUSERCOLLECT_H

//#include "../Include/system.h"
#include "../Utils/cthread.h"

//#include "../Anal/Collect/DataFile/CRWRCommonVariables.h"

class CUserCollect : public CThread
{
private:
    STR_MessageData *m_pMsg;

    STR_RES_COL_START m_strResColStart;

    SIGAPDW *m_pstrPDW;

    char *m_pstrPDWWithFileHeader;

    unsigned int m_uiColStart;

    // SIM 모의 데이터 생성하기 위한 변수
    unsigned int m_uiIndex;
    _TOA m_ullTOA;

    unsigned int m_uiCoSim;

    unsigned int m_iColHistoTime;

    unsigned char m_ucColHisto[COLHISTO_TIME][COLHISTO_CELLS+1];

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

    void MakeCollectHistogram();
    void NextCollectHistogram();
    void MakeSharedSpectrumData();

public:
    CUserCollect( int iKeyId, char *pClassName=NULL, bool bArrayLanData=false );
    virtual ~CUserCollect();

    void Run( key_t key=IPC_PRIVATE ); 


    virtual void _routine();
    virtual const char *GetThreadName() { return m_szThreadName; }
};

//#define UCOL   CUserCollect::GetInstance()

#endif // CUSERCOLLECT_H
