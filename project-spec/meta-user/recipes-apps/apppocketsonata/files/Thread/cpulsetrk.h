#ifndef CPULSETRK_H
#define CPULSETRK_H


//#include "../Include/system.h"
#include "../Utils/cthread.h"

class CPulseTrk : public CThread
{
public:
    static CPulseTrk *m_pInstance;

    STR_MessageData *m_pMsg;

public:
    CPulseTrk( int iKeyId, char *pClassName=NULL, bool bArrayLanData=false );
    virtual ~CPulseTrk();

    THREAD_STANDARD_FUNCTION( CPulseTrk )
};

#define PULTRK     CPulseTrk::GetInstance()

#endif // CPULSETRK_H
