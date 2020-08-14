//******************************************************************************//
//
//  A base class used to access SQLite databases from MFC programs. 
//
//  Designed for the Oxetta report builder, the free report design and print
//  library for C/C++ developers
//
//  http://www.oxetta.com for more details
//
//******************************************************************************//

#if !defined(AFX_ABSTRACTDATABASE_H__2F86C1E9_F607_4A8C_9D01_B0ECE0D49E37__INCLUDED_)
#define AFX_ABSTRACTDATABASE_H__2F86C1E9_F607_4A8C_9D01_B0ECE0D49E37__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "AbstractRecordset.h"

#define DATABASE_TYPE_NONE    -1
#define DATABASE_TYPE_SQLITE   0
#define DATABASE_TYPE_FIREBIRD 1
#define DATABASE_TYPE_ODBC     2

#define DATABASE_BLOB_BLOCK_SIZE 1024

#define PARAMETER_MARKERS _T("?:@$")

class CAbstractDatabase  
{
public:
	virtual BOOL GetParamCount(CAbstractRecordset *pRecordset, int &iCount                , CString &sError) = 0;
	virtual BOOL GetParamName (CAbstractRecordset *pRecordset, int index, CString &sName  , CString &sError) = 0;
	virtual BOOL GetParamIndex(CAbstractRecordset *pRecordset, LPCTSTR szName, int &index , CString &sError) = 0;
	virtual BOOL BindParam    (CAbstractRecordset *pRecordset, int index, int     iValue  , CString &sError) = 0;
	virtual BOOL BindParam    (CAbstractRecordset *pRecordset, int index, __int64 i64Value, CString &sError) = 0;
	virtual BOOL BindParam    (CAbstractRecordset *pRecordset, int index, LPCTSTR szValue , CString &sError) = 0;
	virtual BOOL BindParam    (CAbstractRecordset *pRecordset, int index, double  fValue  , CString &sError) = 0;
	virtual BOOL Prepare(LPCTSTR szStatement, CString &sError, CAbstractRecordset **ppRecordset) = 0;
	virtual BOOL Execute(CAbstractRecordset *pRecordset, CString &sError) = 0;
	virtual BOOL Rewind(CAbstractRecordset *pRecordset, CString &sError) = 0;

	virtual BOOL UpdateBlob(LPCTSTR szQuery, void *pData, int iLength, CString &sError) = 0;
	virtual BOOL Query(LPCTSTR szStatement, CString &sError) = 0;
	virtual BOOL Query(LPCTSTR szStatement, CString &sError, CAbstractRecordset **ppRecordset) = 0;
	virtual BOOL Disconnect() = 0;
	virtual BOOL IsConnected() = 0;
	virtual BOOL Connect(LPCTSTR szDatabase, LPCTSTR szLogin, LPCTSTR szPassword, CString &sError) = 0;
	virtual BOOL BeginTransaction(CString &sError) = 0;
	virtual BOOL Commit(CString &sError) = 0;
	virtual BOOL Rollback(CString &sError) = 0;
	virtual BOOL LockRecord(LPCTSTR szQuery, CString &sError) = 0;
	virtual BOOL UnlockRecord(BOOL bCommit, CString &sError) = 0;
	virtual int GetType() = 0;
protected:
	BOOL CheckBindParam(CAbstractRecordset *pRecordset, int index, CString &sError)
	{
		ASSERT(pRecordset);
		if (-1 == index)
		{
			sError = "Wrong parameter index: (-1)";
			return FALSE;
		}
		else
		if (!pRecordset->IsOpen())
		{
			sError = "The recordset is closed";
			return FALSE;
		}
		else
			return TRUE;
	};
	BOOL IsOneOf(TCHAR cChar, LPCTSTR szCharSet)
	{
		return (NULL != _tcschr(szCharSet, cChar));
	};
	void ParseForParamNames(CString sQuery, CStringArray &saParams)
	{
	//  declaring variables
		int  iStart        = -1, 
			 iStop         = -1;
		BOOL bSingleQuote  = FALSE,
			 bDoubleQuote  = FALSE;
		saParams.RemoveAll();

	//  looping thru the query string characters
		for (int i=0; i<sQuery.GetLength(); i++)
		{
		//  checking the query string character
			switch (sQuery[i])
			{
			case ':':
			case '?':
			case '@':
			case '$':
				if (!bSingleQuote && !bDoubleQuote)
					iStart = i;
				break;
			case '\'':
				if (!bDoubleQuote)
					bSingleQuote = !bSingleQuote;
				break;
			case '"':
				if (!bSingleQuote)
					bDoubleQuote = !bDoubleQuote;
				break;
			case ' ':
			case '\r':
			case '\n':
			case '\t':
				if (-1 != iStart)
					iStop = i;
			}
		//  analyzing the situation
			if ((-1 != iStart) && (-1 != iStop))
			{
				if (iStart == iStop-1)
					saParams.Add(_T(""));
				else
				{
					CString sParamName = sQuery.Mid(iStart+1, iStop-1);
					saParams.Add(sParamName);
				}
				iStart = -1;
				iStop  = -1;
			}
		}

	//  adding the last parameter if necessary
		if (-1 != iStart && -1 == iStop)
		{
			iStop = sQuery.GetLength()-1;
			CString sParamName;
			if (iStart+1 < iStop)
				sParamName = sQuery.Mid(iStart+1, iStop);
			else
				sParamName = _T("");
			saParams.Add(sParamName);
			iStart = -1;
			iStop  = -1;
		}

	};
};

#endif // !defined(AFX_ABSTRACTDATABASE_H__2F86C1E9_F607_4A8C_9D01_B0ECE0D49E37__INCLUDED_)
