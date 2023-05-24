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
		m_bIsConnected = false;
		m_nRowsAffected = 0;
		SQLAlloc();
	};

	~CODBCDatabase()
	{
		Close();
		m_lConnectionTimeout = 0;
		m_lLoginTimeout = 0;
		m_bIsConnected = false;
		m_nRowsAffected = 0;
	};

	SQLHDBC m_hDbc;

protected:
	LONG m_lLoginTimeout;
	LONG m_lConnectionTimeout;
	bool m_bIsConnected;
	SQLHENV m_hEnv;
    SQLINTEGER m_nRowsAffected;

public:
	bool Open(CHAR* lpstrDSN, CHAR* lpstrUser = NULL, CHAR* lpstrPass = NULL);
	bool DriverConnect(CHAR* szConnStr, CHAR* szConnStrOut = NULL, HWND hWnd = NULL, enum drvCompletion drvConn = sqlNoPrompt);
    void show_error( SQLSMALLINT handletype );
	void SetReadOnly(bool bReadOnly = true);
	void SetConnectionTimeout(LONG nSeconds);
	LONG GetConnectionTimeout();
	void SetLoginTimeout(LONG nSeconds)
	{m_lLoginTimeout = nSeconds;};
	bool Execute(CHAR* szSqlStr);
	int GetRowsAffected()
	{return m_nRowsAffected;};
	bool Browse(UCHAR* lpstrConnStrIn, UCHAR* lpstrConnStrOut);
	bool IsConnected()
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
		m_bIsEOF = false;
		m_bIsBOF = false;
		AllocStmt();
	};

	~CODBCRecordset()
	{
		Close();
		m_hStmt = NULL;
		m_bIsEOF = false;
		m_bIsBOF = false;
	};

	bool Open(CHAR* szSqlStr);

	LONG GetFieldLength(SQLSMALLINT nField);
	int GetFieldIndex(CHAR* szFieldName);
	bool GetFieldName(SQLSMALLINT nField, CHAR* szFieldName);
	bool GetFieldAttributes(int nField, CHAR* szFieldName, int& nType, int& nLength);
	int GetFieldCount();
	bool GetFieldValue(SQLSMALLINT nField, CHAR* szData);
	bool GetFieldValue(CHAR* szFieldName, CHAR *szData);
	bool GetFieldValue(SQLSMALLINT nField, int* szData);
    bool GetFieldValue( SQLSMALLINT nField, unsigned int *lData );
	bool GetFieldValue(CHAR* szFieldName, int *szData);
	bool GetFieldValue(SQLSMALLINT nField, LONG *lData);
	bool GetFieldValue(CHAR* szFieldName, LONG *lData);
	bool GetFieldValue(SQLSMALLINT nField, DOUBLE *dblData);
	bool GetFieldValue(CHAR* szFieldName, DOUBLE *dblData);	
	bool GetFieldValue(SQLSMALLINT nField, float *dblData);
	bool GetFieldValue(CHAR* szFieldName, float *dblData);	
	bool GetFieldValue(SQLSMALLINT nField, struct tm* pTime);
	bool GetFieldValue(CHAR* szFieldName, struct tm* pTime);
	//bool GetFieldTimeValue(SQLSMALLINT nField, time_t * pTime);
	bool GetFieldTimeValue(SQLSMALLINT nField, time_t *pTime);
	bool GetFieldTimeValue(CHAR *szFieldName, time_t* time);

	bool MoveFirst();
	bool MoveNext();
	bool MovePrevious();
	bool MoveLast();
	bool IsEof() 
	{return m_bIsEOF;};
	bool IsBof()
	{return m_bIsBOF;};

	void Close();

protected:
	bool m_bIsEOF;
	bool m_bIsBOF;
	SQLHDBC m_hDbc;
	SQLHSTMT m_hStmt;
	void AllocStmt();
};