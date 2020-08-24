#ifndef CDETECTANALYSIS_H
#define CDETECTANALYSIS_H

#include "../Utils/clog.h"

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

public:
    static CDetectAnalysis *pInstance;

    STR_MessageData *m_pMsg;

public:
    CDetectAnalysis( int iKeyId, char *pClassName=NULL, bool bArrayLanData=false );
    virtual ~CDetectAnalysis(void);

    THREAD_STANDARD_FUNCTION( CDetectAnalysis )

private:
    void AnalysisStart();

};

#define DETANL          CDetectAnalysis::GetInstance()
#define DETANL_RELEASE  CDetectAnalysis::ReleaseInstance()

#endif // CDETECTANALYSIS_H
