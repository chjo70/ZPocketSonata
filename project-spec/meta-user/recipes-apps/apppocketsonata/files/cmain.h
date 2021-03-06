#ifndef CMAIN_H
#define CMAIN_H

using namespace std;

#include "./Include/system.h"
#include "./Utils/cthread.h"


#ifdef _SQLITE_
#include "./SQLite/KompexSQLiteDatabase.h"
#include "./SQLite/KompexSQLiteStatement.h"
#include "./SQLite/KompexSQLiteException.h"
#include "./SQLite/KompexSQLiteStreamRedirection.h"
#include "./SQLite/KompexSQLiteBlob.h"

#elif _NO_SQLITE_

#elif _MSSQL_
#include "../../ELINTOP/ODBC/mssql.h"
#include "../../ELINTOP/ODBC/odbccore.h"
#endif


void ParsingArgument( int iArgc, char *iArgv[] );


#endif // CMAIN_H
