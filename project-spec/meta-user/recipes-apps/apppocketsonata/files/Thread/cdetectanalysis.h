#ifndef CDETECTANALYSIS_H
#define CDETECTANALYSIS_H

#include "../Utils/clog.h"

#include "../Include/system.h"
#include "../Utils/cthread.h"

class CDetectAnalysis : public CThread
{
public:
    static CDetectAnalysis *pInstance;

    STR_MessageData *m_pMsg;

public:
    CDetectAnalysis( int iKeyId, char *pClassName );
    virtual ~CDetectAnalysis(void);

    void Run();

    virtual void _routine();
    virtual const char *ChildClassName() { return m_szClassName; }

    static CDetectAnalysis* GetInstance()
    { // 게으른 초기화
        if(pInstance == NULL) {
            pInstance = new CDetectAnalysis( g_iKeyId++, (char*)"CDetectAnalysis" );
        }
        return pInstance;
    }

    void ReleaseInstance()
    {
        if(pInstance)
        {
            LOGMSG1( enDebug, "[%s] 를 종료 처리 합니다...", ChildClassName() );

            delete pInstance;
            pInstance = NULL;
        }
    }

};

#define DETANL     CDetectAnalysis::GetInstance()

#endif // CDETECTANALYSIS_H
