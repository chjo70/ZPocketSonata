#ifndef CDETECTANALYSIS_H
#define CDETECTANALYSIS_H

//#include "../Utils/clog.h"

#include "../Include/system.h"
#include "../Utils/cthread.h"

#include "../Anal/SigAnal/SysPara.h"
#include "../Anal/NewSigAnal/NewSigAnal.h"

class CDetectAnalysis : public CThread
{
private:
    UNI_LAN_DATA m_uniLanData;

    CSysPara *m_pTheSysPara;
    CNewSigAnal *m_pTheNewSigAnal;

    STR_PDWDATA m_PDWData;

public:
    STR_MessageData *m_pMsg;

public:
    CDetectAnalysis( int iKeyId, char *pClassName=NULL, bool bArrayLanData=false );
    virtual ~CDetectAnalysis(void);

    void Run( key_t key=IPC_PRIVATE );

    void MakePDWData();

    virtual void _routine();
    virtual const char *GetThreadName() { return m_szThreadName; }

private:
    void AnalysisStart();


};



#endif // CDETECTANALYSIS_H
