#ifndef CTRACKANALYSIS_H
#define CTRACKANALYSIS_H

#include "../Utils/clog.h"

#include "../Include/system.h"
#include "../Utils/cthread.h"

#include "../Anal/SigAnal/SysPara.h"
#include "../Anal/KnownSigAnal/KnownSigAnal.h"

class CTrackAnalysis : public CThread
{
private:
    CSysPara *m_pTheSysPara;
    CKnownSigAnal *m_pTheKnownSigAnal;

public:
    static CTrackAnalysis *m_pInstance;

    STR_MessageData *m_pMsg;

private:
    void AnalysisStart();

public:
    CTrackAnalysis( int iKeyId, char *pClassName=NULL, bool bArrayLanData=false );
    virtual ~CTrackAnalysis(void);

    THREAD_STANDARD_FUNCTION( CTrackAnalysis )
};

#define TRKANL          CTrackAnalysis::GetInstance()
#define TRKANL_RELEASE  CTrackAnalysis::ReleaseInstance()
#define TRKANL_IS       CTrackAnalysis::IsThereInstance()

#endif // CTRACKANALYSIS_H
