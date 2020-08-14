//******************************************************************************//
//
//  A C++ class used to access SQLite databases from MFC programs. 
//
//  Designed for the Oxetta report builder, the free report design and print
//  library for C/C++ developers
//
//  http://www.oxetta.com for more details
//
//******************************************************************************//

#include "stdafx.h"
#include "SQLiteDatabase.h"
#include "UnicodeTools.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSQLiteDatabase::CSQLiteDatabase()
{
	m_bTransaction = FALSE;
}

CSQLiteDatabase::~CSQLiteDatabase()
{

}

BOOL CSQLiteDatabase::Connect(LPCTSTR szDatabase, LPCTSTR szLogin, LPCTSTR szPassword, CString &sError)
{
//  opening the database
	char *utf8Database = ToUtf8(szDatabase);
	int iResult = sqlite3_open(utf8Database, &m_pDatabase);
	FREE_AND_NULL(utf8Database);
	if (0 != iResult)
	{
		m_pDatabase = NULL;
		sError = _T("Failed to open database");
		return FALSE;
	}
	else
		return TRUE;
}

BOOL CSQLiteDatabase::Disconnect()
{
	if (!IsConnected())
		return TRUE;
	sqlite3_close(m_pDatabase);
	m_pDatabase = NULL;
	m_bTransaction = FALSE;
	return TRUE;
}

BOOL CSQLiteDatabase::IsConnected()
{
	return (NULL != m_pDatabase);
}

BOOL CSQLiteDatabase::Query(LPCTSTR szStatement, CString &sError)
{
//  preparing for execution of the SQL statement
	ASSERT(IsConnected());
	char *utf8Statement = ToUtf8(szStatement);
	char *utf8Error = NULL;

//  executing the statement
	int iResult = sqlite3_exec
					(
					m_pDatabase,
					utf8Statement,
					NULL,
					NULL, 
					&utf8Error
					);
	FREE_AND_NULL(utf8Statement);

//  exiting
	if (SQLITE_OK != iResult)
		sError = FromUtf8(utf8Error);
	return (SQLITE_OK == iResult);
}

BOOL CSQLiteDatabase::Query(LPCTSTR szStatement, CString &sError, CAbstractRecordset **ppRecordset)
{
	ASSERT(NULL == *ppRecordset);
	char *szTail = NULL;
	*ppRecordset = new CSQLiteRecordset;
	char *utf8Statement = ToUtf8(szStatement);
	int iResult = sqlite3_prepare_v2
						(
						m_pDatabase, 
						utf8Statement,
						-1,
						&((CSQLiteRecordset*)*ppRecordset)->m_pStatement,
						NULL
						);
	FREE_AND_NULL(utf8Statement);
	if (SQLITE_OK != iResult)
	{
		sError = GetLastError();
		(*ppRecordset)->Close();
		delete *ppRecordset;
		*ppRecordset = NULL;
		return FALSE;
	}
	else
		return TRUE;
}

BOOL CSQLiteDatabase::BeginTransaction(CString &sError)
{
	if (!IsConnected())
	{
		sError = _T("Not connected to the database");
		return FALSE;
	}
	else
	{
		m_bTransaction = Query(_T("begin transaction;"), sError);
		return m_bTransaction;
	}
}

BOOL CSQLiteDatabase::Commit(CString &sError)
{
	if (!IsConnected())
	{
		sError = _T("Not connected to the database");
		return FALSE;
	}
	else
	if (!m_bTransaction)
	{
		sError = _T("No transaction started");
		return FALSE;
	}
	else
	if (!Query(_T("commit;"), sError))
		return FALSE;
	else
	{
		m_bTransaction = FALSE;
		return TRUE;
	}
}

BOOL CSQLiteDatabase::Rollback(CString &sError)
{
	if (!IsConnected())
	{
		sError = _T("Not connected to the database");
		return FALSE;
	}
	else
	if (!m_bTransaction)
	{
		sError = _T("No transaction started");
		return FALSE;
	}
	if (!Query(_T("rollback;"), sError))
		return FALSE;
	else
	{
		m_bTransaction = FALSE;
		return TRUE;
	}
}

BOOL CSQLiteDatabase::LockRecord(LPCTSTR szQuery, CString &sError)
{
	if (Query(_T("begin transaction;"), sError))
	{
		m_bTransaction = TRUE;
		return TRUE;
	}
	else
		return FALSE;
}

BOOL CSQLiteDatabase::UnlockRecord(BOOL bCommit, CString &sError)
{
	if (bCommit)
		return Commit(sError);
	else
		return Rollback(sError);
}

int CSQLiteDatabase::GetType()
{
	return DATABASE_TYPE_SQLITE;
}

BOOL CSQLiteDatabase::UpdateBlob(LPCTSTR szQuery, void *pData, int iLength, CString &sError)
{
//  checking input parameters
	ASSERT(szQuery);
	sqlite3_stmt *pStatement = NULL;
	int iError = 0;

//  preparing the SQL statement
	char *utf8Statement = ToUtf8(szQuery);
	iError = sqlite3_prepare_v2
					(
					m_pDatabase,
					utf8Statement,
					-1,
					&pStatement,
					NULL
					);
	FREE_AND_NULL(utf8Statement);
	if (SQLITE_OK != iError)
	{
		sError = GetLastError();
		return FALSE;
	}

//  binding the BLOB to the prepared statement
	iError = sqlite3_bind_blob
					(
					pStatement,
					1,
					pData,
					iLength,
					SQLITE_STATIC
					);
	if (SQLITE_OK != iError)
	{
		sError = GetLastError();
		return FALSE;
	}

//  executing the statement
	iError = sqlite3_step(pStatement);
	if (SQLITE_DONE != iError)
	{
		sError = GetLastError();
		return FALSE;
	}

//  freing allocated resources and exiting
	sqlite3_finalize(pStatement);
	return TRUE;
}

BOOL CSQLiteDatabase::GetParamCount(CAbstractRecordset *pRecordset, int &iCount, CString &sError)
{
	if (!pRecordset->IsOpen())
	{
		sError = _T("The recordset is not prepared");
		return FALSE;
	}
	else
	{
		iCount = sqlite3_bind_parameter_count(((CSQLiteRecordset*)pRecordset)->m_pStatement);
		return TRUE;
	}
}

BOOL CSQLiteDatabase::GetParamName(CAbstractRecordset *pRecordset, int index, CString &sName, CString &sError)
{
//  checking parameters
	sError.Empty();
	sName.Empty();
	if (!CheckBindParam(pRecordset, index, sError))
		return FALSE;

//  requesting the database for parameter name
	sName = FromUtf8
				(
					(char*)sqlite3_bind_parameter_name
								(
								((CSQLiteRecordset*)pRecordset)->m_pStatement, 
								index+1   //  since SQLite counts parameters starting from 1
								)
				);

//  SQLite returns parameter name with parameter marker, e.g. ":paramname"
//  removing parameter marker from the name string
	if (
		(sName.GetLength() > 1) &&
		(0 == sName.FindOneOf(PARAMETER_MARKERS))
	   )
		sName = sName.Right(sName.GetLength()-1);

//  exiting
	return TRUE;
}

BOOL CSQLiteDatabase::GetParamIndex(CAbstractRecordset *pRecordset, LPCTSTR szName, int &index, CString &sError)
{
	if (!CheckBindParam(pRecordset, index, sError))
		return FALSE;
	else
	if (0 == _tcslen(szName))
	{
		sError = _T("Cannot find the index of the unnamed parameter when searching by name");
		return FALSE;
	}
	else
	{
		char *utf8Name = ToUtf8(szName);
		index = sqlite3_bind_parameter_index
						(
						((CSQLiteRecordset*)pRecordset)->m_pStatement, 
						utf8Name
						) - 1;  //  since SQLite counts parameters starting from 1
		FREE_AND_NULL(utf8Name);
		return (index > -1);
	}
}

BOOL CSQLiteDatabase::BindParam(CAbstractRecordset *pRecordset, int index, int iValue, CString &sError)
{
	if (!CheckBindParam(pRecordset, index, sError))
		return FALSE;
	else
	{
		int iError = sqlite3_bind_int
						(
						((CSQLiteRecordset*)pRecordset)->m_pStatement, 
						index+1, 
						iValue
						);
		if (SQLITE_OK == iError)
			return TRUE;
		else
		{
			 sError = GetLastError();
			 return FALSE;
		}
	}
}

BOOL CSQLiteDatabase::BindParam(CAbstractRecordset *pRecordset, int index, __int64 i64Value, CString &sError)
{
	if (!CheckBindParam(pRecordset, index, sError))
		return FALSE;
	else
	{
		int iError = sqlite3_bind_int64
						(
						((CSQLiteRecordset*)pRecordset)->m_pStatement, 
						index+1, 
						(sqlite_int64)i64Value
						);
		if (SQLITE_OK == iError)
			return TRUE;
		else
		{
			 sError = GetLastError();
			 return FALSE;
		}
	}
}

BOOL CSQLiteDatabase::BindParam(CAbstractRecordset *pRecordset, int index, LPCTSTR szValue , CString &sError)
{
	if (!CheckBindParam(pRecordset, index, sError))
		return FALSE;
	else
	{
		char *utf8Value = ToUtf8(szValue);
		int iError = sqlite3_bind_text
						(
						((CSQLiteRecordset*)pRecordset)->m_pStatement, 
						index+1, 
						utf8Value, 
						-1, 
						SQLITE_TRANSIENT
						);
		FREE_AND_NULL(utf8Value);
		if (SQLITE_OK == iError)
			return TRUE;
		else
		{
			 sError = GetLastError();
			 return FALSE;
		}
	}
}

BOOL CSQLiteDatabase::BindParam(CAbstractRecordset *pRecordset, int index, double  fValue  , CString &sError)
{
	if (!CheckBindParam(pRecordset, index, sError))
		return FALSE;
	else
	{
		int iError = sqlite3_bind_double
						(
						((CSQLiteRecordset*)pRecordset)->m_pStatement, 
						index+1, 
						fValue
						);
		if (SQLITE_OK == iError)
			return TRUE;
		else
		{
			 sError = GetLastError();
			 return FALSE;
		}
	}
}

BOOL CSQLiteDatabase::Prepare(LPCTSTR szStatement, CString &sError, CAbstractRecordset **ppRecordset)
{
	return Query(szStatement, sError, ppRecordset);
}

BOOL CSQLiteDatabase::Execute(CAbstractRecordset *pRecordset, CString &sError)
{
	return TRUE;
}

BOOL CSQLiteDatabase::Rewind(CAbstractRecordset *pRecordset, CString &sError)
{
//  checking if the query is prepared
	if (!pRecordset->IsOpen())
	{
		sError = _T("The recordset is not open");
		return FALSE;
	}

//  resetting the query
	int iError = sqlite3_reset(((CSQLiteRecordset*)pRecordset)->m_pStatement);
	if (SQLITE_OK == iError)
		return TRUE;
	else
	{
		sError = GetLastError();
		return FALSE;
	}
}

CString CSQLiteDatabase::GetLastError()
{
	return FromUtf8((char*)sqlite3_errmsg(m_pDatabase));
}
