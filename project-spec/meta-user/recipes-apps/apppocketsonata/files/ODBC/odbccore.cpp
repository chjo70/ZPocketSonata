//
//  MODULE:   odbccore.cpp
//
//	AUTHOR: Carlos Antollini
//
//  mailto: cantollini@hotmail.com
//
//	Date: 08/21/2001
//
//	Version 1.11
//

#include "odbccore.h"

/////////////////////////////////////////////////////////////
//
// CODBCDatabase Class
//

void CODBCDatabase::SQLAlloc()
{

	if( SQL_SUCCESS == SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &m_hEnv) ) {
	    if( SQL_SUCCESS == SQLSetEnvAttr(m_hEnv, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, 0) ) {
	        SQLAllocHandle(SQL_HANDLE_DBC, m_hEnv, &m_hDbc);
        }
    }
}

void CODBCDatabase::SQLFree()
{
	SQLFreeHandle(SQL_HANDLE_DBC, m_hDbc);
	SQLFreeHandle(SQL_HANDLE_ENV, m_hEnv);
	m_hDbc = NULL;
	m_hEnv = NULL;
}

void CODBCDatabase::Close()
{
	m_bIsConnected = false;

	if(m_hDbc == NULL) {
    }
    else {
	    SQLDisconnect(m_hDbc);
	    SQLFree();
    }
}

bool CODBCDatabase::Open(CHAR* szDSN,CHAR* szUser, CHAR* szPass)
{
	SQLRETURN ret;

	if(m_lConnectionTimeout > 0) {
		SQLSetConnectAttr(m_hDbc, SQL_ATTR_CONNECTION_TIMEOUT, (SQLPOINTER)m_lConnectionTimeout, 0);
	}

	SQLSetConnectAttr(m_hDbc, SQL_ATTR_LOGIN_TIMEOUT, (SQLPOINTER)m_lLoginTimeout, 0);

	ret = SQLConnect(m_hDbc,
					(SQLCHAR*)szDSN,
					sizeof(szDSN),
					(SQLCHAR*)szUser,
					sizeof(szUser),
					(SQLCHAR*)szPass,
					sizeof(szPass));

	m_bIsConnected = ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO;
	return m_bIsConnected;
}

bool CODBCDatabase::Browse(UCHAR* szConnStrIn, UCHAR* szConnStrOut)
{
	SQLRETURN ret;
	SWORD swLenOut = 0;

	ret = SQLBrowseConnect(m_hDbc,
							(SQLCHAR*)szConnStrIn,
							sizeof(szConnStrIn),
							(SQLCHAR*)szConnStrOut,
							MAX_BUFFER,
							&swLenOut);

	m_bIsConnected = ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO;
	return m_bIsConnected;
}

#ifdef _WIN64
void CODBCDatabase::SetConnectionTimeout(LONGLONG nSeconds)
#else
void CODBCDatabase::SetConnectionTimeout( LONG nSeconds )
#endif
{
	if(m_hDbc) {
		SQLSetConnectAttr(m_hDbc, SQL_ATTR_CONNECTION_TIMEOUT, (SQLPOINTER)nSeconds, 0);
	}

	m_lConnectionTimeout = nSeconds;
}

/**
 * @brief     bool
 * @param     CHAR * szConnStr
 * @param     CHAR * szConnStrOut
 * @param     HWND hWnd
 * @param     enum drvCompletion drvConn
 * @return    bool
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-03-28, 10:19
 * @warning
 */
bool CODBCDatabase::DriverConnect(CHAR* szConnStr, CHAR* szConnStrOut, HWND hWnd, enum drvCompletion drvConn)
{
	SQLRETURN ret;
	SQLSMALLINT pcbConnStrOut;
    SQLCHAR szOut[1024];

	if(drvConn == sqlPrompt && hWnd == NULL) {
		m_bIsConnected = false;
    }
    else {
	    if(m_lConnectionTimeout > 0) {
		    SQLSetConnectAttr(m_hDbc, SQL_ATTR_CONNECTION_TIMEOUT, (SQLPOINTER)m_lConnectionTimeout, 0);
        }
        else {
	        SQLSetConnectAttr(m_hDbc, SQL_ATTR_LOGIN_TIMEOUT, (SQLPOINTER)m_lLoginTimeout, 0);
        }

	    ret = SQLDriverConnect(m_hDbc,
							    hWnd,
							    (SQLCHAR*)szConnStr,
							    SQL_NTS,
							    (SQLCHAR*)szOut,
							    sizeof(szOut),
							    &pcbConnStrOut,
							    (SQLUSMALLINT)drvConn);

        if( ret == SQL_ERROR ) {
            show_error( SQL_HANDLE_DBC );
        }

	    m_bIsConnected = ( ret == SQL_SUCCESS ) || ( ret == SQL_SUCCESS_WITH_INFO );
    }

	return m_bIsConnected;
}

void CODBCDatabase::show_error( SQLSMALLINT handletype )
{
//     SQLCHAR sqlstate[1024];
//     SQLCHAR message[1024];
//     if(SQL_SUCCESS == SQLGetDiagRec(handletype, m_hDbc, 1, sqlstate, NULL, message, 1024, NULL)) {
//         // cout<<"Message: "<<message<<"\nSQLSTATE: "<<sqlstate<<endl;
//     }
}

void CODBCDatabase::SetReadOnly(bool bReadOnly)
{

	SQLSetConnectAttr(m_hDbc, SQL_ATTR_ACCESS_MODE, (SQLPOINTER)(bReadOnly? SQL_MODE_READ_ONLY : SQL_MODE_READ_WRITE), 0);
}

LONG CODBCDatabase::GetConnectionTimeout()
{
	LONG nSeconds;

	SQLGetConnectAttr(m_hDbc, SQL_ATTR_CONNECTION_TIMEOUT, &nSeconds, NULL, 0);

	return nSeconds;
}

// bool CODBCDatabase::Execute(CHAR *szSqlStr)
// {
//     bool bRet=false;
// 	SQLRETURN ret;
// 	SQLHSTMT hStmt = NULL;
// 	SQLINTEGER nRowCount;
//
// 	SQLAllocHandle(SQL_HANDLE_STMT, m_hDbc, &hStmt);
//
//     if( hStmt != NULL ) {
// 	    ret = SQLExecDirect(hStmt, (SQLCHAR*)szSqlStr, SQL_NTS);
//
// 	    SQLRowCount(hStmt, &nRowCount);
//
// 	    m_nRowsAffected = nRowCount;
//
//         bRet = ( ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO );
//     }
//     else {
//     }
// 	return bRet;
// }


/////////////////////////////////////////////////////////////
//
// CODBCRecordset Class
//

void CODBCRecordset::AllocStmt()
{
	SQLAllocHandle(SQL_HANDLE_STMT, m_hDbc, &m_hStmt);
}

bool CODBCRecordset::Open(CHAR *szSqlStr)
{
    bool bRet=false;
	SQLRETURN ret;

	ret = SQLExecDirect(m_hStmt, (SQLCHAR*)szSqlStr, SQL_NTS);
	if( ( ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO ) && m_hStmt != NULL )
	{
		SQLRETURN sqlreturn=SQLFetch(m_hStmt);
		if( SQL_NO_DATA == sqlreturn ) {
			m_bIsEOF = true;
		}
		bRet = true;
	}
    else if(ret == SQL_NO_DATA ) {
        bRet = true;
    }
    else {
	    throw (int) SQL_ERROR_QUERY;

	}

    return bRet;
}

bool CODBCRecordset::GetFieldValue(SQLSMALLINT nField, CHAR *szData)
{
	SQLRETURN ret;
    SQLLEN cbValue;
	int nLength = GetFieldLength(nField) + 1;

	//ret = SQLGetData(m_hStmt, (SQLUSMALLINT)(nField + 1), SQL_C_CHAR, szData, nLength, &cbValue) == SQL_SUCCESS;
    ret = SQLGetData(m_hStmt, (SQLUSMALLINT)(nField + 1), SQL_C_CHAR, szData, nLength, &cbValue);
	return ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO;
}

bool CODBCRecordset::GetFieldValue(CHAR *szFieldName, CHAR *szData)
{
	return GetFieldValue(GetFieldIndex(szFieldName), szData);
}

bool CODBCRecordset::GetFieldValue(SQLSMALLINT nField, int *lData)
{
	SQLRETURN ret;
    SQLLEN cbValue;
	int nLength;

    if( nField >= 0 ) {
        nLength = GetFieldLength(nField) + 1;
	    //ret = SQLGetData(m_hStmt, (SQLUSMALLINT)(nField + 1), SQL_C_LONG, lData, nLength, &cbValue) == SQL_SUCCESS;
        ret = SQLGetData(m_hStmt, (SQLUSMALLINT)(nField + 1), SQL_C_LONG, lData, nLength, &cbValue);

		if (cbValue == -1) {
			*lData = 0;
		}

    }
    else {
        ret = SQL_ERROR;
    }
	return ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO;
}

bool CODBCRecordset::GetFieldValue( SQLSMALLINT nField, unsigned int *lData )
{
    SQLRETURN ret;
    SQLLEN cbValue;
    int nLength;

    if( nField >= 0 ) {
        nLength = GetFieldLength( nField ) + 1;
        //ret = SQLGetData(m_hStmt, (SQLUSMALLINT)(nField + 1), SQL_C_LONG, lData, nLength, &cbValue) == SQL_SUCCESS;
        ret = SQLGetData( m_hStmt, ( SQLUSMALLINT ) ( nField + 1 ), SQL_C_LONG, lData, nLength, &cbValue );

        if( cbValue == -1 ) {
            *lData = 0;
        }

    }
    else {
        ret = SQL_ERROR;
    }
    return ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO;
}

bool CODBCRecordset::GetFieldValue(CHAR *szFieldName, int *lData)
{
	return GetFieldValue(GetFieldIndex(szFieldName), lData);
}

bool CODBCRecordset::GetFieldValue(SQLSMALLINT nField, LONG *lData)
{
	SQLRETURN ret;
    SQLLEN cbValue;
	int nLength;

    if( nField >= 0 ) {
        nLength = GetFieldLength(nField) + 1;

	    //ret = SQLGetData(m_hStmt, (SQLUSMALLINT)(nField + 1), SQL_C_LONG, lData, nLength, &cbValue) == SQL_SUCCESS;
        ret = SQLGetData(m_hStmt, (SQLUSMALLINT)(nField + 1), SQL_C_LONG, lData, nLength, &cbValue);
    }
    else {
        ret = SQL_ERROR;
    }
	return ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO;
}

bool CODBCRecordset::GetFieldValue(CHAR *szFieldName, LONG *lData)
{
	return GetFieldValue(GetFieldIndex(szFieldName), lData);
}

bool CODBCRecordset::GetFieldValue(SQLSMALLINT nField, DOUBLE *dblData)
{

    SQLLEN cbValue;
	SQLRETURN ret;
	int nLength;

    if( nField >= 0 ) {
        nLength = GetFieldLength(nField) + 1;

	    //ret = SQLGetData(m_hStmt, (SQLUSMALLINT)(nField + 1), SQL_C_DOUBLE, dblData, nLength, &cbValue) == SQL_SUCCESS;
        ret = SQLGetData(m_hStmt, (SQLUSMALLINT)(nField + 1), SQL_C_DOUBLE, dblData, nLength, &cbValue);
    }
    else {
        ret = SQL_ERROR;
    }
	return ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO;
}

bool CODBCRecordset::GetFieldValue(CHAR *szFieldName, DOUBLE *dblData)
{
	return GetFieldValue(GetFieldIndex(szFieldName), dblData);
}

bool CODBCRecordset::GetFieldValue(SQLSMALLINT nField, float *dblData)
{

    SQLLEN cbValue;
	SQLRETURN ret;
	int nLength;

    if( nField >= 0 ) {
        nLength = GetFieldLength(nField) + 1;

	    //ret = SQLGetData(m_hStmt, (SQLUSMALLINT)(nField + 1), SQL_REAL, dblData, nLength, &cbValue) == SQL_SUCCESS;
        ret = SQLGetData(m_hStmt, (SQLUSMALLINT)(nField + 1), SQL_REAL, dblData, nLength, &cbValue);

		if (cbValue == -1) {
			*dblData = 0;
		}

    }
    else {
        ret = SQL_ERROR;
    }
	return ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO;
}

bool CODBCRecordset::GetFieldValue(CHAR *szFieldName, float *dblData)
{
	return GetFieldValue(GetFieldIndex(szFieldName), dblData);
}

bool CODBCRecordset::GetFieldValue(SQLSMALLINT nField, struct tm* pTime)
{
	bool bRet = false;
    SQLLEN cbValue;
	SQLRETURN ret;
	int nLength;

    if( nField >= 0 ) {
        nLength = GetFieldLength(nField) + 1;
	    SQL_TIMESTAMP_STRUCT* sqltm = new SQL_TIMESTAMP_STRUCT;

	    //ret = SQLGetData(m_hStmt, (SQLUSMALLINT)(nField + 1), SQL_C_TYPE_TIMESTAMP, sqltm, nLength, &cbValue) == SQL_SUCCESS;
        ret = SQLGetData(m_hStmt, (SQLUSMALLINT)(nField + 1), SQL_C_TYPE_TIMESTAMP, sqltm, nLength, &cbValue);
	    if(ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO)
	    {
		    pTime->tm_year = sqltm->year;
		    pTime->tm_mon = sqltm->month - 1; //January must be = 0
		    pTime->tm_mday = sqltm->day;
		    pTime->tm_hour = sqltm->hour;
		    pTime->tm_min = sqltm->minute;
		    pTime->tm_sec = sqltm->second;
		    bRet = true;
	    }
    }
    else {
    }
	return bRet;
}

bool CODBCRecordset::GetFieldValue(CHAR *szFieldName, struct tm* pTime)
{
	return GetFieldValue(GetFieldIndex(szFieldName), pTime);
}

bool CODBCRecordset::GetFieldTimeValue(SQLSMALLINT nField, time_t * pTime)
{
    bool bRet=false;
    SQLLEN cbValue;
	SQLRETURN ret;
	int nLength = GetFieldLength(nField) + 1;
	SQL_TIMESTAMP_STRUCT sqltm;
	struct tm sTm;

	//ret = SQLGetData(m_hStmt, (SQLUSMALLINT)nField + 1, SQL_C_TYPE_TIMESTAMP, & sqltm, nLength, &cbValue) == SQL_SUCCESS;
    ret = SQLGetData(m_hStmt, (SQLUSMALLINT)( nField + 1), SQL_C_TYPE_TIMESTAMP, & sqltm, nLength, &cbValue);
	if(ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO)
	{
		sTm.tm_year = sqltm.year - 1900;
		sTm.tm_mon = sqltm.month - 1; //January must be = 0
		sTm.tm_mday = sqltm.day;
		sTm.tm_hour = sqltm.hour;
		sTm.tm_min = sqltm.minute;
		sTm.tm_sec = sqltm.second;
		*pTime = mktime( & sTm );

// 		__time32_t now;
// 		struct tm *pt1;
//
// 		_time32( & now );
// 		pt1 = _localtime32( & now );

		bRet = true;
	}
	return bRet;
}

// bool CODBCRecordset::GetFieldTimeValue(SQLSMALLINT nField, time_t *pTime)
// {
// 	bool bRet = false;
// 	SQLINTEGER cbValue;
// 	SQLRETURN ret;
// 	int nLength = GetFieldLength(nField) + 1;
// 	SQL_TIMESTAMP_STRUCT sqltm;
// 	struct tm sTm;
//
// 	//ret = SQLGetData(m_hStmt, (SQLUSMALLINT)nField + 1, SQL_C_TYPE_TIMESTAMP, & sqltm, nLength, &cbValue) == SQL_SUCCESS;
// 	ret = SQLGetData(m_hStmt, (SQLUSMALLINT)nField + 1, SQL_C_TYPE_TIMESTAMP, &sqltm, nLength, &cbValue);
// 	if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO)
// 	{
// 		sTm.tm_year = sqltm.year - 1900;
// 		sTm.tm_mon = sqltm.month - 1; //January must be = 0
// 		sTm.tm_mday = sqltm.day;
// 		sTm.tm_hour = sqltm.hour;
// 		sTm.tm_min = sqltm.minute;
// 		sTm.tm_sec = sqltm.second;
// 		pTime = _mktime64(&sTm);
//
// 		// 		__time32_t now;
// 		// 		struct tm *pt1;
// 		//
// 		// 		_time32( & now );
// 		// 		pt1 = _localtime32( & now );
//
// 		bRet = true;
// 	}
// 	return bRet;
// }

bool CODBCRecordset::GetFieldTimeValue(CHAR *szFieldName, time_t * pTime)
{
	return GetFieldTimeValue(GetFieldIndex(szFieldName), pTime);
}



bool CODBCRecordset::GetFieldName(SQLSMALLINT nField, CHAR *szFieldName)
{
	int nType, nLength;

	return GetFieldAttributes(nField, szFieldName, nType, nLength);
}

int CODBCRecordset::GetFieldIndex(CHAR *szFieldName)
{
    int iRet=-1;

	SQLSMALLINT nCols=0;
	SQLUSMALLINT nCol = 1;
	CHAR szColName[MAX_COL_NAME_LEN];
	SQLSMALLINT cbColNameLen, fSqlType, ibScale, fNullable;
    SQLULEN cbColDef;

	SQLNumResultCols(m_hStmt, &nCols);
	while(nCol < nCols)
	{
		memset(szColName, 0, 32 * sizeof(CHAR));
		SQLDescribeCol(m_hStmt, nCol, (SQLCHAR*)szColName, MAX_COL_NAME_LEN, &cbColNameLen, &fSqlType, &cbColDef, &ibScale, &fNullable);

		if(_stricmp(szColName, szFieldName) == 0) {
			iRet = nCol - 1;
            break;
        }
		nCol++;
	}
	return iRet;
}

bool CODBCRecordset::MoveFirst()
{
	SQLRETURN ret;

	ret = SQLFetchScroll(m_hStmt, SQL_FETCH_FIRST, 0);

	m_bIsBOF = ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO;
	if(m_bIsBOF) {
		m_bIsEOF = false;
	}

	return m_bIsBOF;
}

bool CODBCRecordset::MoveNext()
{
	SQLRETURN ret;

	ret = SQLFetchScroll(m_hStmt, SQL_FETCH_NEXT, 0);

	m_bIsEOF = ret == SQL_NO_DATA;
	m_bIsBOF = false;
	return ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO;
}

bool CODBCRecordset::MovePrevious()
{
	SQLRETURN ret;

	ret = SQLFetchScroll(m_hStmt, SQL_FETCH_PRIOR, 0);
	m_bIsBOF = ret == SQL_NO_DATA;
	m_bIsEOF = false;
	return ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO;
}

bool CODBCRecordset::MoveLast()
{
	SQLRETURN ret;

	ret = SQLFetchScroll(m_hStmt, SQL_FETCH_LAST, 0);

	m_bIsEOF = ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO;
	if(m_bIsEOF) {
		m_bIsBOF = false;
	}

	return m_bIsEOF;
}

/**
 * @brief     GetFieldLength
 * @param     SQLSMALLINT nField
 * @return    LONG
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-04-21, 17:29
 * @warning
 */
LONG CODBCRecordset::GetFieldLength(SQLSMALLINT nField)
{
    SQLSMALLINT fSqlType, ibScale, fNullable;
    SQLULEN cbColDef;

	SQLDescribeCol(m_hStmt, (SQLUSMALLINT) (nField + 1), NULL, 0, 0, &fSqlType, &cbColDef, &ibScale, &fNullable);

	return (LONG) cbColDef;
}

bool CODBCRecordset::GetFieldAttributes(int nField, CHAR* szFieldName, int& nType, int& nLength)
{
	SQLRETURN ret;
	SQLSMALLINT cbColNameLen, fSqlType, ibScale, fNullable;
    SQLULEN cbColDef;

	ret = SQLDescribeCol(m_hStmt, (SQLUSMALLINT)(nField + 1), (SQLCHAR*)szFieldName, MAX_COL_NAME_LEN, &cbColNameLen, &fSqlType, &cbColDef, &ibScale, &fNullable);

	nType = fSqlType;
	nLength = (int) cbColDef;

	return ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO;
}

int CODBCRecordset::GetFieldCount()
{

	SQLSMALLINT nFieldCount = 0;
	SQLNumResultCols(m_hStmt, &nFieldCount);

	return nFieldCount;
}

void CODBCRecordset::Close()
{
	if(m_hStmt != NULL) {
		SQLFreeHandle(SQL_HANDLE_STMT, m_hStmt);
	}
	m_hStmt = NULL;
}