#ifndef CTASKMNGR_H
#define CTASKMNGR_H

using namespace std;

#include "../Include/system.h"
#include "../Utils/cthread.h"

//#include "../MinIni/minIni.h"



class CTaskMngr : public CThread
{
private:
    static CTaskMngr *m_pInstance;

    STR_MessageData *m_pMsg;

private:
    void Init();
    void InitVar();

    ENUM_BoardID GetBoardID();

    // 명령어 처리에 대한 각각의 함수이다.
    void SetMode();
    void AnalysisStart();


    // 명령어 처리에 대한 하부 함수 목록 입니다.
    void CreateAllAnalysisThread( bool bCreate=true );
    void ProcessSummary();


    // 인터페이스 관련 함수 모음 입니다.
    void SendLan( UINT uiOpCode, UINT uiLength, void *pData );

public:
    CTaskMngr( int iKeyId, char *pClassName=NULL, bool bArrayLanData=false );
    virtual ~CTaskMngr(void);

    THREAD_STANDARD_FUNCTION( CTaskMngr )

public:
    void Shutdown();

};

#define TMNGR   CTaskMngr::GetInstance()

#endif // CTASKMNGR_H
