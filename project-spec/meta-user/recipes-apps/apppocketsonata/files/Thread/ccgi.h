#ifndef CCGI_H
#define CCGI_H


#include "../Include/system.h"
#include "../Utils/cthread.h"

class CCGI : public CThread
{
public:
    static CCGI *m_pInstance;

    STR_MessageData *m_pMsg;

public:
    CCGI( int iKeyId, char *pClassName=NULL, bool bArrayLanData=false );
    virtual ~CCGI();

    THREAD_STANDARD_FUNCTION( CCGI )
};

#define CGI     CCGI::GetInstance()

#endif // CCGI_H
