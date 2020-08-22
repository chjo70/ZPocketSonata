#ifndef CJAMTECH_H
#define CJAMTECH_H

#include "../Include/system.h"
#include "../Utils/cthread.h"

#include "../Utils/clog.h"


class CJamTech : public CThread
{
public:
    static CJamTech *pInstance;

    STR_MessageData *m_pMsg;

public:
    CJamTech( int iKeyId, char *pClassName=NULL, bool bArrayLanData=false );
    ~CJamTech();

    void Run();

    virtual void _routine();
    virtual const char *ChildClassName() { return m_szClassName; }

    static CJamTech* GetInstance()
    { // 게으른 초기화
        if(pInstance == NULL) {
            pInstance = new CJamTech( g_iKeyId++, (char*)"CJamTech" );
        }
        return pInstance;
    }

    void ReleaseInstance()
    {
        if(pInstance)
        {
            LOGMSG1( enDebug, "[%s]를 종료 처리 합니다...", ChildClassName() );

            delete pInstance;
            pInstance = NULL;
        }
    }
};

#define JAMTEC     CJamTech::GetInstance()

#endif // CJAMTECH_H
