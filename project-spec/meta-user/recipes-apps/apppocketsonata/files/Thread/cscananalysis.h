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

    void Run();

    virtual void _routine();
    virtual const char *ChildClassName() { return m_szClassName; }

    static CScanAnalysis* GetInstance()
    { // 게으른 초기화
        if(pInstance == NULL) {
            pInstance = new CScanAnalysis( g_iKeyId++, (char*)"CScanAnalysis" );
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

#define SCANANL     CScanAnalysis::GetInstance()

#endif // CSCANANALYSIS_H
