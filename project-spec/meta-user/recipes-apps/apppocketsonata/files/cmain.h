/**

    @file      cmain.h
    @brief
    @details   ~
    @author    조철희
    @date      2.05.2023
    @copyright ? Cool Guy, 2023. All right reserved.

**/
#pragma once


#include "./Anal/OFP_Main.h"

using namespace std;




#include "./Include/system.h"
#include "./Utils/cthread.h"
#include "./Utils/clog.h"


#ifdef _SQLITE_
#include "./SQLite/KompexSQLiteDatabase.h"
#include "./SQLite/KompexSQLiteStatement.h"
#include "./SQLite/KompexSQLiteException.h"
#include "./SQLite/KompexSQLiteStreamRedirection.h"
#include "./SQLite/KompexSQLiteBlob.h"

#elif _MSSQL_
#include "./ODBC/mssql.h"
#include "./ODBC/odbccore.h"

#else


#endif


//void ParsingArgument( int iArgc, char *iArgv[] );
void UpdateCPUMode();


class CMain : public CLogName {

private:
    void *m_pParent;

public:
    CMain();
    virtual ~CMain();

    void Run( int iArgc, char *iArgv[], void *pParent=NULL );

private:
    void ParsingArgument( int iArgc, char *iArgv[] );
    void InitDatabase();
    void CreateMngrThread();
    void CreateAnalThread();


};


