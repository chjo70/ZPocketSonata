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

#if !defined(AFX_SQLITEDATABASE_H__F7FB8804_D427_4541_8961_E2FDDAAC5633__INCLUDED_)
#define AFX_SQLITEDATABASE_H__F7FB8804_D427_4541_8961_E2FDDAAC5633__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SQLite\SQLite3.h"
#include "AbstractDatabase.h"
#include "SQLiteRecordset.h"

class CSQLiteDatabase : public CAbstractDatabase
{
public:
	virtual BOOL UpdateBlob(LPCTSTR szQuery, void *pData, int iLength, CString &sError);
	virtual int GetType();
	virtual BOOL UnlockRecord(BOOL bCommit, CString &sError);
	virtual BOOL LockRecord(LPCTSTR szQuery, CString &sError);
	virtual BOOL Rollback(CString &sError);
	virtual BOOL Commit(CString &sError);
	virtual BOOL BeginTransaction(CString &sError);
	virtual BOOL Query(LPCTSTR szStatement, CString &sError, CAbstractRecordset **ppRecordset);
	virtual BOOL Query(LPCTSTR szStatement, CString &sError);
	virtual BOOL Prepare(LPCTSTR szStatement, CString &sError, CAbstractRecordset **ppRecordset);
	virtual BOOL Execute(CAbstractRecordset *pRecordset, CString &sError);
	virtual BOOL IsConnected();
	virtual BOOL Disconnect();
	virtual BOOL Connect(LPCTSTR szDatabase, LPCTSTR szLogin, LPCTSTR szPassword, CString &sError);
	CSQLiteDatabase();
	virtual ~CSQLiteDatabase();

	virtual BOOL GetParamCount(CAbstractRecordset *pRecordset, int &iCount                , CString &sError);
	virtual BOOL GetParamName (CAbstractRecordset *pRecordset, int index, CString &sName  , CString &sError);
	virtual BOOL GetParamIndex(CAbstractRecordset *pRecordset, LPCTSTR szName, int &index , CString &sError);
	virtual BOOL BindParam    (CAbstractRecordset *pRecordset, int index, int     iValue  , CString &sError);
	virtual BOOL BindParam    (CAbstractRecordset *pRecordset, int index, __int64 i64Value, CString &sError);
	virtual BOOL BindParam    (CAbstractRecordset *pRecordset, int index, LPCTSTR szValue , CString &sError);
	virtual BOOL BindParam    (CAbstractRecordset *pRecordset, int index, double  fValue  , CString &sError);
	virtual BOOL Rewind       (CAbstractRecordset *pRecordset, CString &sError);
private:
	BOOL m_bTransaction;
	sqlite3 *m_pDatabase;
	CString GetLastError();
};

#endif // !defined(AFX_SQLITEDATABASE_H__F7FB8804_D427_4541_8961_E2FDDAAC5633__INCLUDED_)
