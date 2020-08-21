#ifndef CTASKMNGR_H
#define CTASKMNGR_H

using namespace std;

#include "../Include/system.h"
#include "../Utils/cthread.h"

//#include "../MinIni/minIni.h"



class CTaskMngr : public CThread
{
private:
    static CTaskMngr *pInstance;

    STR_MessageData *m_pMsg;

private:
    void Init();
    void InitVar();

    ENUM_BoardID GetBoardID();

    // 명령어 처리에 대한 각각의 함수이다.
    void SetMode();
    void AnalysisStart();


    // 명령어 처리에 대한 하부 함수 목록 입니다.
    void CreateAllAnalysisThread( bool bCreate );
    void ProcessSummary();


    // 인터페이스 관련 함수 모음 입니다.
    void SendLan( UINT uiOpCode, UINT uiLength, void *pData );

public:
    CTaskMngr( int iKeyId, char *pClassName=NULL );
    virtual ~CTaskMngr(void);

    void Run();

    virtual void _routine();
    virtual const char *ChildClassName() { return m_szClassName; }

    static CTaskMngr* GetInstance()
    { // 게으른 초기화
        if(pInstance == NULL) {
            pInstance = new CTaskMngr( g_iKeyId++, (char *)"CTaskMngr" );
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


public:
    void Shutdown();

};

#define TMNGR   CTaskMngr::GetInstance()

#endif // CTASKMNGR_H
