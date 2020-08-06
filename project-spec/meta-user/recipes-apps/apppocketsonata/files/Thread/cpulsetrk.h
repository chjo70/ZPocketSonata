#ifndef CPULSETRK_H
#define CPULSETRK_H


#include "../Include/system.h"
#include "../Utils/cthread.h"

class CPulseTrk : public CThread
{
public:
    static CPulseTrk *pInstance;

    STR_MessageData *m_pMsg;

public:
    CPulseTrk( int iKeyId, char *pClassName=NULL, bool bArrayLanData=false );
    virtual ~CPulseTrk();

    void Run();
    void ReleaseInstance();

    virtual void _routine();
    virtual const char *ChildClassName() { return m_szClassName; }

    static CPulseTrk* GetInstance()
    { // 게으른 초기화
        if(pInstance == NULL) {
            pInstance = new CPulseTrk( g_iKeyId++, (char*)"CPulseTrk" );
        }
        return pInstance;
    }
};

#define PULTRK     CPulseTrk::GetInstance()

#endif // CPULSETRK_H
