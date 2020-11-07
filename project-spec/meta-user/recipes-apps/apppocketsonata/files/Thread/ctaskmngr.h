#ifndef CTASKMNGR_H
#define CTASKMNGR_H

using namespace std;

#include "../Include/system.h"
#include "../Utils/cthread.h"

#include "../Anal/Identify/cipl.h"

#ifdef _SQLITE_
#include "../SQLite/SQLiteCpp.h"

#else
#include "../../ELINTOP/ODBC/mssql.h"
#include "../../ELINTOP/ODBC/odbccore.h"
#endif



class CTaskMngr : public CThread, public SQLite::Database
{
private:
    static CTaskMngr *m_pInstance;

    STR_MessageData *m_pMsg;

    int m_iTotalIPL;
    CIPL m_theIPL;

private:
    void Init();
    void InitVar();

    ENUM_BoardID GetBoardID();

    // 명령어 처리에 대한 각각의 함수이다.
    void SetMode();
    void AnalysisStart();
    void ReqIPLVersion();
    void IPLDownload();
    void InsertIPL( int iIndex );
    void DeleteIPL();

    // 명령어 처리에 대한 하부 함수 목록 입니다.
    void CreateAllAnalysisThread( bool bCreate=true );
    void ProcessSummary();

    // 인터페이스 관련 함수 모음 입니다.
    void SendLan( UINT uiOpCode, UINT uiLength, void *pData );

public:
    CTaskMngr( int iKeyId, char *pClassName=NULL, bool bArrayLanData=false, const char *pFileName=NULL );
    virtual ~CTaskMngr(void);

    THREAD_STANDARD_FUNCTION_2( CTaskMngr )

public:
    void Shutdown();

};

#define TMNGR   CTaskMngr::GetInstance()

#endif // CTASKMNGR_H
