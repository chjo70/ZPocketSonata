#ifndef CTRACKANALYSIS_H
#define CTRACKANALYSIS_H

#include "../Utils/clog.h"

#include "../Include/system.h"
#include "../Utils/cthread.h"

class CTrackAnalysis : public CThread
{
public:
    static CTrackAnalysis *pInstance;

    STR_MessageData *m_pMsg;

public:
    CTrackAnalysis( int iKeyId, char *pClassName=NULL, bool bArrayLanData=false );
    virtual ~CTrackAnalysis(void);

    THREAD_STANDARD_FUNCTION( CTrackAnalysis )
};

#define TRKANL          CTrackAnalysis::GetInstance()
#define TRKANL_RELEASE  CTrackAnalysis::ReleaseInstance()

#endif // CTRACKANALYSIS_H
