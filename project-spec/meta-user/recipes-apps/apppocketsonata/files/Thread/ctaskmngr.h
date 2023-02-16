#ifndef CTASKMNGR_H
#define CTASKMNGR_H

using namespace std;

#include "../Anal/Identify/define.h"
#include "../Utils/cthread.h"

#include "../Anal/Identify/cipl.h"

#ifdef _MSSQL_
#include "../ODBC/mssql.h"
#include "../ODBC/odbccore.h"

#elif _SQLITE_
#include "../SQLite/KompexSQLitePrerequisites.h"
#include "../SQLite/KompexSQLiteDatabase.h"
#include "../SQLite/KompexSQLiteStatement.h"
#include "../SQLite/KompexSQLiteException.h"
#include "../SQLite/KompexSQLiteStreamRedirection.h"
#include "../SQLite/KompexSQLiteBlob.h"

#endif




#ifdef _MSSQL_
class CTaskMngr : public CThread, public CMSSQL 
#else
class CTaskMngr : public CThread
#endif
{
private:
    STR_MessageData *m_pMsg;

    CIPL m_theIPL;

#ifdef _SQLITE_
    char m_szSQLString[MAX_SQL_SIZE];
    wchar_t m_szSQLString16[MAX_SQL_SIZE];

    Kompex::CSQLiteDatabase *m_pDatabase;

#elif defined(_MSSQL_)
    CODBCDatabase m_theMyODBC;
#else
#endif

private:
    void Init();
    void InitVar();

    ENUM_BoardID GetBoardID();

    // 명령어 처리에 대한 각각의 함수이다.
    void SetMode();
    void AnalysisStart();
    void ReqIPLVersion();
    void ReqAudio();
    void ReqAudioParam();
    void BandEnable();
    void FMOPThreshold();
    void PMOPThreshold();
    void RxThreshold();
    void IPLDownload();
    void ReqSystemVar();

    // 데이터베이스 처리
    void InsertIPL( int iIndex );
    void DeleteIPL( char *pszELNOT=NULL );
    int IsThrereELNOT( char *pszELNOT );

    // 명령어 처리에 대한 하부 함수 목록 입니다.
    void ProcessSummary();

    // 인터페이스 관련 함수 모음 입니다.
    void SendLan( UINT uiOpCode, UINT uiLength, void *pData );

    void StopUserCollecting();

    inline void *GetRecvData() { 
        void *pRet;

        if( m_pMsg->iArrayIndex >= 0 ) 
            pRet = (void *) ( CThread::GetRecvData() ); 
        else 
            pRet = (void *) ( & m_pMsg->x.szData[0] ); 

        return pRet;
    }

public:
#ifdef _MSSQL_
    CTaskMngr( int iKeyId, const char *pClassName=NULL, bool bArrayLanData=false );
#else
    CTaskMngr( int iKeyId, const char *pClassName=NULL, bool bArrayLanData=false, const char *pFileName=NULL );
#endif

    virtual ~CTaskMngr(void);
    virtual void _routine();
    virtual char *GetThreadName() { return m_szThreadName; }

public:
    void Run( key_t key=IPC_PRIVATE );
    void Shutdown();

};

// #define TMNGR   CTaskMngr::GetInstance()

#endif // CTASKMNGR_H
