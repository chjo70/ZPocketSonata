#ifndef CJAMTECH_H
#define CJAMTECH_H

#include "../Include/system.h"
#include "../Utils/cthread.h"

//#include "../Utils/clog.h"


class CJamTech : public CThread
{
public:
    static CJamTech *m_pInstance;

    STR_MessageData *m_pMsg;

public:
    CJamTech( int iKeyId, char *pClassName=NULL, bool bArrayLanData=false );
    ~CJamTech();

    THREAD_STANDARD_FUNCTION( CJamTech )
};

#define JAMTEC     CJamTech::GetInstance()

#endif // CJAMTECH_H
