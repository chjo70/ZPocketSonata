//  MODULE:   odbccore.h
//
//	AUTHOR: Carlos Antollini 
//
//  mailto: cantollini@hotmail.com
//
//	Date: 08/21/2001
//
//	Version 1.11
// 
#pragma once

#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include <time.h>

#define MAX_BUFFER 256
#define MAX_COL_NAME_LEN 32


// 에러 정의
#define SQL_ERROR_DISCONNECTION				(0xFFFF)
#define SQL_ERROR_QUERY								(0xFFF0)
#define SQL_ERROR_FIELD_LENGTH				(0xFFE0)


class CODBCDatabase
{
public:
	enum drvCompletion
	{
		sqlNoPrompt = SQL_DRIVER_NOPROMPT,
		sqlPrompt = SQL_DRIVER_PROMPT
	};

protected:
	void SQLFree();
	void SQLAlloc();

public:
	CODBCDatabase()
	{
		m_hDbc = NULL;
		m_hEnv = NULL;
		m_lConnectionTimeout = 0;
		m_lLoginTimeout = 5;
		m_bIsConnected = FALSE;
		m_nRowsAffected = 0;
		SQLAlloc();
	};

	~CODBCDatabase()
	{
		Close();
		m_lConnectionTimeout = 0;
		m_lLoginTimeout = 0;
		m_bIsConnected = FALSE;
		m_nRowsAffected = 0;
	};

	SQLHDBC m_hDbc;

protected:
	LONG m_lLoginTimeout;
	LONG m_lConnectionTimeout;
	BOOL m_bIsConnected;
	SQLHENV m_hEnv;
	int m_nRowsAffected;

public:
	BOOL Open(CHAR* lpstrDSN, CHAR* lpstrUser = NULL, CHAR* lpstrPass = NULL);
	BOOL DriverConnect(CHAR* szConnStr, CHAR* szConnStrOut = NULL, HWND hWnd = NULL, enum drvCompletion drvConn = sqlNoPrompt);
    void show_error(unsigned int handletype );
	void SetReadOnly(BOOL bReadOnly = TRUE);
	void SetConnectionTimeout(LONG nSeconds);
	LONG GetConnectionTimeout();
	void SetLoginTimeout(LONG nSeconds)
	{m_lLoginTimeout = nSeconds;};
	BOOL Execute(CHAR* szSqlStr);
	int GetRowsAffected()
	{return m_nRowsAffected;};
	BOOL Browse(UCHAR* lpstrConnStrIn, UCHAR* lpstrConnStrOut);
	BOOL IsConnected()
	{return m_bIsConnected;};
	void Close();

};

class CODBCRecordset
{
public:
	enum datatypeEnum
	{
		typeChar = SQL_CHAR, 
		typeVarChar = SQL_VARCHAR, 
		typeLongVarChar = SQL_LONGVARCHAR, 
		typeWChar = SQL_WCHAR, 
		typeWVarChar = SQL_WVARCHAR,
		typeWLongVarChar = SQL_WLONGVARCHAR,
		typeDecimal = SQL_DECIMAL,
		typeNumeric = SQL_NUMERIC,
		typeSmallint = SQL_SMALLINT,
		typeInteger = SQL_INTEGER,
		typeReal = SQL_REAL,
		typeFloat = SQL_FLOAT,
		typeDouble = SQL_DOUBLE,
		typeBit = SQL_BIT,
		typeTinyint = SQL_TINYINT,
		typeBigInt = SQL_BIGINT,
		typeBinary = SQL_BINARY,
		typeVarBinary = SQL_VARBINARY,
		typeLongVarBinary =  SQL_LONGVARBINARY,
		typeDate = SQL_TYPE_DATE,
		typeTime = SQL_TYPE_TIME,
		typeTimeStamp = SQL_TYPE_TIMESTAMP,
		typeIntervalMonth = SQL_INTERVAL_MONTH,
		typeIntervalYear = SQL_INTERVAL_YEAR,
		typeIntervalYearToMonth = SQL_INTERVAL_YEAR_TO_MONTH,
		typeIntervalDay = SQL_INTERVAL_DAY,
		typeIntervalHour = SQL_INTERVAL_HOUR,
		typeIntervalMinute = SQL_INTERVAL_MINUTE,
		typeIntervalSecond = SQL_INTERVAL_SECOND,
		typeIntervalDayToHour = SQL_INTERVAL_DAY_TO_HOUR,
		typeIntervalDayToMinute = SQL_INTERVAL_DAY_TO_MINUTE,
		typeIntervalDayToSecond = SQL_INTERVAL_DAY_TO_SECOND,
		typeIntervalHourToMinute = SQL_INTERVAL_HOUR_TO_MINUTE,
		typeIntervalHourToSecond = SQL_INTERVAL_HOUR_TO_SECOND,
		typeIntervalMinuteToSecond = SQL_INTERVAL_MINUTE_TO_SECOND,
		typeGUID = SQL_GUID		
	};

	CODBCRecordset(CODBCDatabase* pDb)
	{
		m_hDbc = pDb->m_hDbc;
		m_hStmt = NULL;
		m_bIsEOF = FALSE;
		m_bIsBOF = FALSE;
		AllocStmt();
	};

	~CODBCRecordset()
	{
		Close();
		m_hStmt = NULL;
		m_bIsEOF = FALSE;
		m_bIsBOF = FALSE;
	};

	BOOL Open(CHAR* szSqlStr);

	LONG GetFieldLength(int nField);
	int GetFieldIndex(CHAR* szFieldName);
	BOOL GetFieldName(int nField, CHAR* szFieldName);
	BOOL GetFieldAttributes(int nField, CHAR* szFieldName, int& nType, int& nLength);
	int GetFieldCount();
	BOOL GetFieldValue(int nField, CHAR* szData);
	BOOL GetFieldValue(CHAR* szFieldName, CHAR *szData);
	BOOL GetFieldValue(int nField, int* szData);
	BOOL GetFieldValue(CHAR* szFieldName, int *szData);
	BOOL GetFieldValue(int nField, LONG *lData);
	BOOL GetFieldValue(CHAR* szFieldName, LONG *lData);
	BOOL GetFieldValue(int nField, DOUBLE *dblData);
	BOOL GetFieldValue(CHAR* szFieldName, DOUBLE *dblData);	
	BOOL GetFieldValue(int nField, float *dblData);
	BOOL GetFieldValue(CHAR* szFieldName, float *dblData);	
	BOOL GetFieldValue(int nField, struct tm* time);
	BOOL GetFieldValue(CHAR* szFieldName, struct tm* time);
	BOOL GetFieldTimeValue(int nField, __time32_t * pTime);
	BOOL GetFieldTimeValue(CHAR *szFieldName, __time32_t* time);

	BOOL MoveFirst();
	BOOL MoveNext();
	BOOL MovePrevious();
	BOOL MoveLast();
	BOOL IsEof() 
	{return m_bIsEOF;};
	BOOL IsBof()
	{return m_bIsBOF;};

	void Close();

protected:
	BOOL m_bIsEOF;
	BOOL m_bIsBOF;
	SQLHDBC m_hDbc;
	SQLHSTMT m_hStmt;
	void AllocStmt();
};