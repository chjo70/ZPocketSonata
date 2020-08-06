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

    void Run();

    virtual void _routine();
    virtual const char *ChildClassName() { return m_szClassName; }

    static CTrackAnalysis* GetInstance()
    { // 게으른 초기화
        if(pInstance == NULL) {
            pInstance = new CTrackAnalysis( g_iKeyId++, (char*)"CTrackAnalysis" );
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

#define TRKANL     CTrackAnalysis::GetInstance()

#endif // CTRACKANALYSIS_H
