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

#if !defined(AFX_SQLITERECORDSET_H__296505E0_8957_4ED4_BFEB_FC7FC00F8620__INCLUDED_)
#define AFX_SQLITERECORDSET_H__296505E0_8957_4ED4_BFEB_FC7FC00F8620__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SQLite\SQLite3.h"
#include "AbstractRecordset.h"

class CSQLiteRecordset : public CAbstractRecordset  
{
	friend class CSQLiteDatabase;
public:
	virtual void AsBlob(LPCTSTR szName, LPBYTE *ppData, int &iLength);
	virtual void AsBlob(int index, LPBYTE *ppData, int &iLength);
	virtual BOOL IsInteger(int index);
	virtual BOOL IsString(int index);
	virtual BOOL IsFloat(int index);
	virtual BOOL IsNULL(int index);
	virtual CString GetFieldName(int index);
	virtual double AsFloat(LPCTSTR szName);
	virtual int AsInteger(LPCTSTR szName);
	virtual CString AsString(LPCTSTR szName);
	virtual int GetFieldCount();
	virtual double AsFloat(int index);
	virtual int AsInteger(int index);
	virtual BOOL Next();
	virtual BOOL IsOpen();
	virtual void Close();
	virtual CString AsString(int index);

	CSQLiteRecordset();
	virtual ~CSQLiteRecordset();
private:
	int GetFieldIndex(LPCTSTR szName);
	sqlite3_stmt *m_pStatement;
};

#endif // !defined(AFX_SQLITERECORDSET_H__296505E0_8957_4ED4_BFEB_FC7FC00F8620__INCLUDED_)
