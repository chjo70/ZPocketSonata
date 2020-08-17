#ifndef CEMITTERMERGE_H
#define CEMITTERMERGE_H

#include "../Utils/clog.h"

#include "../Include/system.h"
#include "../Utils/cthread.h"

class CEmitterMerge : public CThread
{
private:
    UNI_LAN_DATA m_uniLanData;

public:
    static CEmitterMerge *pInstance;

    STR_MessageData *m_pMsg;

public:
    CEmitterMerge( int iKeyId, char *pClassName, bool bArrayLanData );
    virtual ~CEmitterMerge(void);

    void Run();

    virtual void _routine();
    virtual const char *ChildClassName() { return m_szClassName; }

    static CEmitterMerge* GetInstance()
    { // 게으른 초기화
        if(pInstance == NULL) {
            pInstance = new CEmitterMerge( g_iKeyId++, (char*)"CDetectAnalysis", true );
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

private:
    void MergeEmitter();

};

#define EMTMRG  CEmitterMerge::GetInstance()

#endif // CEMITTERMERGE_H
