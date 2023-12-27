/*
    This file is part of Kompex SQLite Wrapper.
	Copyright (c) 2008-2017 Sven Broeske

    Kompex SQLite Wrapper is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Kompex SQLite Wrapper is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with Kompex SQLite Wrapper. If not, see <http://www.gnu.org/licenses/>.
*/

#ifdef _SQLITE_

#include <iostream>

#include "../Anal/SigAnal/_Type.h"

#include "KompexSQLiteBlob.h"
#include "KompexSQLiteStatement.h"
#include "KompexSQLiteDatabase.h"
#include "KompexSQLiteException.h"

namespace Kompex
{

SQLiteBlob::SQLiteBlob():
	mBlobHandle(NULL)
{
}

SQLiteBlob::SQLiteBlob(CSQLiteDatabase *db, std::string symbolicDatabaseName, std::string tableName, std::string columnName, int64 rowId, BLOB_ACCESS_MODE accessMode):
	mBlobHandle(NULL)
{
	OpenBlob(db, symbolicDatabaseName, tableName, columnName, rowId, accessMode);
}

SQLiteBlob::~SQLiteBlob()
{
    if( mBlobHandle != NULL ) {
        CloseBlob();
    }
}

void SQLiteBlob::OpenBlob(CSQLiteDatabase *db, std::string symbolicDatabaseName, std::string tableName, std::string columnName, int64 rowId, BLOB_ACCESS_MODE accessMode)
{
    if( mBlobHandle != NULL ) {
        CloseBlob();
    }

	mDatabase = db;
	if(sqlite3_blob_open(mDatabase->GetDatabaseHandle(), symbolicDatabaseName.c_str(), tableName.c_str(), columnName.c_str(), rowId, accessMode, &mBlobHandle) != SQLITE_OK) {
		KOMPEX_EXCEPT(sqlite3_errmsg(mDatabase->GetDatabaseHandle()), sqlite3_errcode(mDatabase->GetDatabaseHandle()));
    }
}

void SQLiteBlob::CloseBlob()
{
	if(sqlite3_blob_close(mBlobHandle) != SQLITE_OK) {
		KOMPEX_EXCEPT(sqlite3_errmsg(mDatabase->GetDatabaseHandle()), sqlite3_errcode(mDatabase->GetDatabaseHandle()));
    }

	mBlobHandle = NULL;
}

int SQLiteBlob::GetBlobSize() const
{
	if(mBlobHandle == NULL) {
		KOMPEX_EXCEPT("GetBlobSize() no open BLOB handle", -1);
    }

	return sqlite3_blob_bytes(mBlobHandle);
}

void SQLiteBlob::ReadBlob(void *buffer, int numberOfBytes, int offset)
{
	if(mBlobHandle == NULL) {
		KOMPEX_EXCEPT("ReadBlob() no open BLOB handle", -1);
    }
	if((offset + numberOfBytes) > GetBlobSize()) {
		KOMPEX_EXCEPT("ReadBlob() offset and numberOfBytes exceed the BLOB size", -1);
    }

    int iSql=sqlite3_blob_read(mBlobHandle, buffer, numberOfBytes, offset);

    if( iSql == SQLITE_OK ) {

    }
    else if( iSql == SQLITE_ABORT ) {
        KOMPEX_EXCEPT("ReadBlob() BLOB handle expired - can not read BLOB", -1);
        //KOMPEX_EXCEPT(sqlite3_errmsg(mDatabase->GetDatabaseHandle()), sqlite3_errcode(mDatabase->GetDatabaseHandle()));
    }
    else {
        KOMPEX_EXCEPT(sqlite3_errmsg(mDatabase->GetDatabaseHandle()), sqlite3_errcode(mDatabase->GetDatabaseHandle()));
    }

//
// 	switch(sqlite3_blob_read(mBlobHandle, buffer, numberOfBytes, offset))
// 	{
// 		case SQLITE_OK:
// 			break;
// 		case SQLITE_ABORT:
// 			KOMPEX_EXCEPT("ReadBlob() BLOB handle expired - can not read BLOB", -1);
//             KOMPEX_EXCEPT(sqlite3_errmsg(mDatabase->GetDatabaseHandle()), sqlite3_errcode(mDatabase->GetDatabaseHandle()));
//             break;
// 		default:
// 			KOMPEX_EXCEPT(sqlite3_errmsg(mDatabase->GetDatabaseHandle()), sqlite3_errcode(mDatabase->GetDatabaseHandle()));
//             break;
// 	}
}

void SQLiteBlob::WriteBlob(const void *buffer, int numberOfBytes, int offset)
{
	if(mBlobHandle == NULL) {
		KOMPEX_EXCEPT("WriteBlob() no open BLOB handle", -1);
    }
	if((offset + numberOfBytes) > GetBlobSize()) {
		KOMPEX_EXCEPT("WriteBlob() offset and numberOfBytes exceed the BLOB size", -1);
    }

    int iSql=sqlite3_blob_write(mBlobHandle, buffer, numberOfBytes, offset);

    if( iSql == SQLITE_OK ) {

    }
    else if( iSql == SQLITE_ABORT ) {
        KOMPEX_EXCEPT("WriteBlob() BLOB handle expired - can not write BLOB", -1);
        //KOMPEX_EXCEPT(sqlite3_errmsg(mDatabase->GetDatabaseHandle()), sqlite3_errcode(mDatabase->GetDatabaseHandle()));
    }
    else {
        KOMPEX_EXCEPT(sqlite3_errmsg(mDatabase->GetDatabaseHandle()), sqlite3_errcode(mDatabase->GetDatabaseHandle()));
    }

// 	switch(sqlite3_blob_write(mBlobHandle, buffer, numberOfBytes, offset))
// 	{
// 		case SQLITE_OK:
// 			break;
// 		case SQLITE_ABORT:
// 			KOMPEX_EXCEPT("WriteBlob() BLOB handle expired - can not write BLOB", -1);
//             KOMPEX_EXCEPT(sqlite3_errmsg(mDatabase->GetDatabaseHandle()), sqlite3_errcode(mDatabase->GetDatabaseHandle()));
//             break;
// 		default:
// 			KOMPEX_EXCEPT(sqlite3_errmsg(mDatabase->GetDatabaseHandle()), sqlite3_errcode(mDatabase->GetDatabaseHandle()));
//             break;
// 	}
}

}	// namespace Kompex

#endif