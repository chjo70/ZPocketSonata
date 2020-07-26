#ifndef CJAMTECH_H
#define CJAMTECH_H

#include "./Include/system.h"
#include "./Utils/cthread.h"


class CJamTech : public CThread
{
public:
    static CJamTech *pInstance;

    STR_MessageData *m_pMsg;

public:
    CJamTech( int iKeyId, char *pClassName=NULL );
    ~CJamTech();

    void Run();
    void ReleaseInstance();

    virtual void _routine();
    virtual const char *ChildClassName() { return m_szClassName; }

    static CJamTech* GetInstance()
    { // 게으른 초기화
        if(pInstance == NULL) {
            pInstance = new CJamTech( g_iKeyId++, (char*)"CJamTech" );
        }
        return pInstance;
    }
};

#define JAMTEC     CJamTech::GetInstance()

#endif // CJAMTECH_H
