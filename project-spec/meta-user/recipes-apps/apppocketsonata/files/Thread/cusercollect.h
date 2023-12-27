#ifndef CUSERCOLLECT_H
#define CUSERCOLLECT_H


#include "../Utils/cthread.h"

#include "../Anal/Collect/GenPDW/CGenPDW.h"

#define NUM_OF_SIM_PDW          (3000)

class CUserCollect : public CThread
{
private:
    STR_MessageData *m_pMsg;

    STR_RES_COL_START m_strResColStart;

    SIGAPDW *m_pSIGAPDW;
    UNION_HEADER *m_pUniHeader;

    CGenPDW *m_pTheGenPDW;

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
    void StopThread();
    void ColStart();
    void SendRawData();

    void MakeSIMPDWData();

    void MakeCollectHistogram();
    void NextCollectHistogram();
    void MakeSharedSpectrumData();

public:
    CUserCollect( int iKeyId, const char *pClassName=NULL, bool bArrayLanData=false );
    virtual ~CUserCollect();

    void Run( key_t key=IPC_PRIVATE );


    void _routine();
    const char *GetThreadName() { return m_szThreadName; }
    STR_MessageData *GetParentMessage() { return m_pMsg; }              ///< 메시지 데이터를 리턴 합니다.
};

//#define UCOL   CUserCollect::GetInstance()

#endif // CUSERCOLLECT_H
