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

#include <stdio.h>

#include "../Anal/SigAnal/_Type.h"

#include "SQLiteRecordset.h"
#include "UnicodeTools.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSQLiteRecordset::CSQLiteRecordset()
{
	m_pStatement = NULL;
}

CSQLiteRecordset::~CSQLiteRecordset()
{
	Close();
}

void CSQLiteRecordset::Close()
{
	if (!IsOpen())
		return;
	sqlite3_finalize(m_pStatement);
	m_pStatement = NULL;
}

BOOL CSQLiteRecordset::IsOpen()
{
	return (NULL != m_pStatement);
}

BOOL CSQLiteRecordset::Next()
{
//  stepping thru the result record set - 20 times
	int iResult = sqlite3_step(m_pStatement);
	return ((SQLITE_ROW == iResult) || (SQLITE_OK == iResult));
}

CString CSQLiteRecordset::AsString(int index)
{
	ASSERT(IsOpen());
	return FromUtf8((char*)sqlite3_column_text(m_pStatement, index));
}

int CSQLiteRecordset::AsInteger(int index)
{
	ASSERT(IsOpen());
	return sqlite3_column_int(m_pStatement, index);
}

double CSQLiteRecordset::AsFloat(int index)
{
	ASSERT(IsOpen());
	return sqlite3_column_double(m_pStatement, index);
}

int CSQLiteRecordset::GetFieldIndex(LPCTSTR szName)
{
	ASSERT(IsOpen());
	for (int i=0; i<GetFieldCount(); i++)
		if (0 == FromUtf8((char*)sqlite3_column_name(m_pStatement, i)).CompareNoCase(szName))
			return i;
	return -1;
}

int CSQLiteRecordset::GetFieldCount()
{
	ASSERT(IsOpen());
	return sqlite3_column_count(m_pStatement);
}

CString CSQLiteRecordset::AsString(LPCTSTR szName)
{
	ASSERT(IsOpen());
	return AsString(GetFieldIndex(szName));
}

int CSQLiteRecordset::AsInteger(LPCTSTR szName)
{
	ASSERT(IsOpen());
	return AsInteger(GetFieldIndex(szName));
}

double CSQLiteRecordset::AsFloat(LPCTSTR szName)
{
	ASSERT(IsOpen());
	return AsFloat(GetFieldIndex(szName));
}

CString CSQLiteRecordset::GetFieldName(int index)
{
	ASSERT(IsOpen());
	return FromUtf8((char*)sqlite3_column_name(m_pStatement, index));
}

BOOL CSQLiteRecordset::IsNULL(int index)
{
	ASSERT(IsOpen());
	return (SQLITE_NULL == sqlite3_column_type(m_pStatement, index));
}

BOOL CSQLiteRecordset::IsFloat(int index)
{
	ASSERT(IsOpen());
	return (SQLITE_FLOAT == sqlite3_column_type(m_pStatement, index));
}

BOOL CSQLiteRecordset::IsString(int index)
{
	ASSERT(IsOpen());
	return  (SQLITE_TEXT == sqlite3_column_type(m_pStatement, index)) ||
			(SQLITE_BLOB == sqlite3_column_type(m_pStatement, index))  ;
}

BOOL CSQLiteRecordset::IsInteger(int index)
{
	ASSERT(IsOpen());
	return (SQLITE_INTEGER == sqlite3_column_type(m_pStatement, index));
}

void CSQLiteRecordset::AsBlob(int index, LPBYTE *ppData, int &iLength)
{
//  checking input parameters
	ASSERT(ppData);
	ASSERT(NULL == *ppData);
	ASSERT(IsOpen());

//  getting BLOB data
	LPBYTE pBuffer = (LPBYTE)sqlite3_column_blob(m_pStatement, index);
	iLength = sqlite3_column_bytes(m_pStatement, index);
	if (0 == iLength)
		return;

//  copying BLOB data from SQLite buffers to the passed memory pointer
	ASSERT(pBuffer);
	*ppData = (LPBYTE)malloc(iLength);
	memcpy(*ppData, pBuffer, iLength);
}

void CSQLiteRecordset::AsBlob(LPCTSTR szName, LPBYTE *ppData, int &iLength)
{
	ASSERT(IsOpen());
	AsBlob(GetFieldIndex(szName), ppData, iLength);
}
