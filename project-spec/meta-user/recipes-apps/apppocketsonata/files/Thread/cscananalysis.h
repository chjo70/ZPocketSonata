#ifndef CSCANANALYSIS_H
#define CSCANANALYSIS_H

#include "../Utils/clog.h"

#include "../Include/system.h"
#include "../Utils/cthread.h"

#include "../Anal/SigAnal/SysPara.h"
#include "../Anal/ScanSigAnal/ScanSigAnal.h"


class CScanAnalysis : public CThread
{
private:
    CSysPara *m_pTheSysPara;
    CScanSigAnal *m_pTheScanSigAnal;

public:
    static CScanAnalysis *m_pInstance;

    STR_MessageData *m_pMsg;

private:
    void AnalysisStart();

public:
    CScanAnalysis( int iKeyId, char *pClassName=NULL, bool bArrayLanData=false );
    virtual ~CScanAnalysis(void);

    THREAD_STANDARD_FUNCTION( CScanAnalysis )
};

#define SCNANL             CScanAnalysis::GetInstance()
#define SCNANL_RELEASE     CScanAnalysis::ReleaseInstance()
#define SCNANL_IS          CScanAnalysis::IsThereInstance()

#endif // CSCANANALYSIS_H
