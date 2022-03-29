#ifndef CSCANANALYSIS_H
#define CSCANANALYSIS_H

//#include "../Utils/clog.h"

//#include "../Include/system.h"
#include "../Utils/cthread.h"

#include "../Anal/SigAnal/SysPara.h"
#include "../Anal/ScanSigAnal/ScanSigAnal.h"


class CScanAnalysis : public CThread
{
private:
    CSysPara *m_pTheSysPara;
    CScanSigAnal *m_pTheScanSigAnal;

public:
    STR_MessageData *m_pMsg;

private:
    void AnalysisStart();

public:
    CScanAnalysis( int iKeyId, char *pClassName=NULL, bool bArrayLanData=false );
    virtual ~CScanAnalysis(void);

    void Run( key_t key=IPC_PRIVATE ); 

    virtual void _routine();
    virtual char *GetThreadName() { return m_szThreadName; }
};


#endif // CSCANANALYSIS_H
