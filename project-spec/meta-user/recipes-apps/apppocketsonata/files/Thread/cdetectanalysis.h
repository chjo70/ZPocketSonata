#ifndef CDETECTANALYSIS_H
#define CDETECTANALYSIS_H

#include "../Utils/clog.h"

#include "../Include/system.h"
#include "../Utils/cthread.h"

#include "../Anal/NewSigAnal/NewSigAnal.h"

class CDetectAnalysis : public CThread
{
private:
    UNI_LAN_DATA m_uniLanData;

    CNewSigAnal *m_pTheNewSigAnal;

public:
    static CDetectAnalysis *pInstance;

    STR_MessageData *m_pMsg;

public:
    CDetectAnalysis( int iKeyId, char *pClassName=NULL, bool bArrayLanData=false );
    virtual ~CDetectAnalysis(void);

    void Run();

    virtual void _routine();
    virtual const char *ChildClassName() { return m_szClassName; }

    static CDetectAnalysis* GetInstance()
    { // 게으른 초기화
        if(pInstance == NULL) {
            pInstance = new CDetectAnalysis( g_iKeyId++, (char*)"CDetectAnalysis", true );
        }
        return pInstance;
    }

    void ReleaseInstance()
    {
        if(pInstance)
        {
            delete pInstance;
            pInstance = NULL;
        }
    }

private:
    void AnalysisStart();

};

#define DETANL     CDetectAnalysis::GetInstance()

#endif // CDETECTANALYSIS_H
