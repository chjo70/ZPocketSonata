#ifndef CSCANANALYSIS_H
#define CSCANANALYSIS_H

#include "../Utils/clog.h"

#include "../Include/system.h"
#include "../Utils/cthread.h"


class CScanAnalysis : public CThread
{
public:
    static CScanAnalysis *pInstance;

    STR_MessageData *m_pMsg;

public:
    CScanAnalysis( int iKeyId, char *pClassName=NULL, bool bArrayLanData=false );
    virtual ~CScanAnalysis(void);

    THREAD_STANDARD_FUNCTION( CScanAnalysis )
};

#define SCANANL             CScanAnalysis::GetInstance()
#define SCANANL_RELEASE     CScanAnalysis::ReleaseInstance()

#endif // CSCANANALYSIS_H
