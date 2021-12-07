#ifndef CTRACKANALYSIS_H
#define CTRACKANALYSIS_H

//#include "../Utils/clog.h"

//#include "../Include/system.h"
#include "../Utils/cthread.h"

#include "../Anal/SigAnal/SysPara.h"
#include "../Anal/KnownSigAnal/KnownSigAnal.h"

class CTrackAnalysis : public CThread
{
private:
    CSysPara *m_pTheSysPara;
    CKnownSigAnal *m_pTheKnownSigAnal;

public:
    STR_MessageData *m_pMsg;

private:
    void AnalysisStart();

public:
    CTrackAnalysis( int iKeyId, char *pClassName=NULL, bool bArrayLanData=false );
    virtual ~CTrackAnalysis(void);

    void Run( key_t key=IPC_PRIVATE );
    virtual void _routine();
    virtual const char *GetThreadName() { return m_szThreadName; }
};

#endif // CTRACKANALYSIS_H
