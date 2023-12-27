#ifndef CCGI_H
#define CCGI_H


#include "../Include/system.h"

#include "../Utils/clog.h"
#include "../Utils/cthread.h"

class CCGI : public CThread
{
public:
    static CCGI *m_pInstance;

    STR_MessageData *m_pMsg;

public:
    CCGI( int iKeyId, const char *pClassName=NULL, bool bArrayLanData=false );
    virtual ~CCGI();

    THREAD_STANDARD_FUNCTION( CCGI )

    void LogMsg( int nType, const char *pszFunction, const char *pszFile, const int iLine, const char *fmt, ... ) { }
    void LogMsg( int nType, const char *fmt, ... ) { }

};

#define CGI     CCGI::GetInstance()

#endif // CCGI_H
