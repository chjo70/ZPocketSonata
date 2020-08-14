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

#if !defined(AFX_ABSTRACTRECORDSET_H__D5DB6ED3_5AC5_4BBA_AF07_32A35938F8AE__INCLUDED_)
#define AFX_ABSTRACTRECORDSET_H__D5DB6ED3_5AC5_4BBA_AF07_32A35938F8AE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#pragma warning(disable : 4996 4244 4018)

#define CLOSE_RECORDSET(recordset)\
{\
	recordset->Close();\
	delete recordset;\
	recordset = NULL;\
}

class CAbstractRecordset  
{
public:
	virtual void AsBlob(LPCTSTR szName, LPBYTE *ppData, int &iLength) = 0;
	virtual void AsBlob(int index, LPBYTE *ppData, int &iLength) = 0;
	virtual BOOL IsNULL(int index) = 0;
	virtual CString AsString(LPCTSTR szName) = 0;
	virtual int AsInteger(LPCTSTR szName) = 0;
	virtual double AsFloat(LPCTSTR szName) = 0;
	virtual double AsFloat(int index) = 0;
	virtual int AsInteger(int index) = 0;
	virtual CString AsString(int index) = 0;
	virtual BOOL IsInteger(int index) = 0;
	virtual BOOL IsFloat(int index) = 0;
	virtual BOOL IsString(int index) = 0;
	virtual int GetFieldCount() = 0;
	virtual CString GetFieldName(int index) = 0;
	virtual int GetFieldIndex(LPCTSTR szName)
	{
		if (IsOpen())
			for (int i=0; i<GetFieldCount(); i++)
				if (0 == GetFieldName(i).CompareNoCase(szName))
					return i;
		return -1;
	};
	virtual BOOL Next() = 0;
	virtual void Close() = 0;
	virtual BOOL IsOpen() = 0;
};

#endif // !defined(AFX_ABSTRACTRECORDSET_H__D5DB6ED3_5AC5_4BBA_AF07_32A35938F8AE__INCLUDED_)
