/**

    @file      CTASKMNGR.H
    @brief
    @details   ~
    @author    조철희
    @date      3.05.2023
    @copyright © Cool Guy, 2023. All right reserved.

**/

#pragma once


using namespace std;

#include "../Anal/Identify/define.h"
#include "../Utils/cthread.h"
#include "../Utils/clog.h"
#include "../System/csysconfig.h"
#include "../Anal/MIDAS/RawFile.h"

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

    ENUM_MODE m_enMode;

    CRawFile m_theRawFile;

    time_t m_tiOPStart;

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
    //void SetMode();
    void Start();
    void AnalysisStart( bool bOut=true );
    void AnalysisReStart();
    void ReqSetSystemVar();
    void ReqSystemVar();

    // 데이터베이스 처리
    int IsThrereELNOT( char *pszELNOT );

    // 명령어 처리에 대한 하부 함수 목록 입니다.
    void TaskSummary();

    // 인터페이스 관련 함수 모음 입니다.
    //void SendLan( UINT uiOpCode, UINT uiLength, void *pData );

    bool WaitThread( CThread *pThread );

    void StopUserCollecting();

    inline void *GetRecvData() {
        void *pRet;

        if( m_pMsg->iArrayIndex >= 0 ) {
            pRet = (void *) ( CThread::GetRecvData() );
        }
        else {
            pRet = (void *) ( & m_pMsg->x.szData[0] );
        }

        return pRet;
    }

public:
#ifdef _MSSQL_
    CTaskMngr( int iThreadPriority, const char *pClassName=NULL, bool bArrayLanData=false, time_t tiNow=0 );
#else
    CTaskMngr( int iThreadPriority, const char *pClassName=NULL, bool bArrayLanData=false, const char *pFileName=NULL, time_t tiNow = 0 );
#endif

    ~CTaskMngr(void);
    virtual void _routine();
    virtual const char *GetThreadName() { return m_szThreadName; }

    time_t OPStartTime() const { return m_tiOPStart; }
    void OPStartTime( time_t val ) { m_tiOPStart = val; }
public:
    //void Run( key_t key=IPC_PRIVATE );
    void Run();
    void Shutdown( bool bAbnormalEvent=false, bool bOut=true );


    STR_MessageData *GetParentMessage() {
        return m_pMsg;
    }

    inline ENUM_MODE GetMode() { return m_enMode; }
    inline void SetMode( ENUM_MODE enMode ) { m_enMode = enMode; }


};

// #define TMNGR   CTaskMngr::GetInstance()


