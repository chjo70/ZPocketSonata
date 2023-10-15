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

#include <stdafx.h>

#include <iostream>
#include <iomanip>
#include <exception>
#include <sstream>
#include <string.h>
#include <stddef.h>

#include <iosfwd>

#include "KompexSQLiteStatement.h"
#include "KompexSQLiteDatabase.h"
#include "KompexSQLiteException.h"

namespace Kompex
{

SQLiteStatement::SQLiteStatement(CSQLiteDatabase *db):
	mDatabase(db),
	mStatement(NULL),
	mTransactionID(0),
	mIsColumnNumberAssignedToColumnName(false)
{
}

SQLiteStatement::~SQLiteStatement()
{
	FreeQuery();
	CleanUpTransaction();
}

void SQLiteStatement::Prepare(const char *sqlStatement)
{
	mIsColumnNumberAssignedToColumnName = false;

	// If the nByte argument is less than zero,
	// then zSql is read up to the first zero terminator.

	if(sqlite3_prepare_v2(mDatabase->GetDatabaseHandle(), sqlStatement, -1, &mStatement, NULL ) != SQLITE_OK) {
        //printf( " m_szSQLString[%s]" , sqlStatement );
		KOMPEX_EXCEPT(sqlite3_errmsg(mDatabase->GetDatabaseHandle()), sqlite3_errcode(mDatabase->GetDatabaseHandle()));
    }

	if(!mStatement) {
		KOMPEX_EXCEPT("Prepare() SQL statement failed", -1);
	}
}

void SQLiteStatement::Prepare(const wchar_t *sqlStatement)
{
	mIsColumnNumberAssignedToColumnName = false;
	CheckDatabase();

	// If the nByte argument is less than zero,
	// then zSql is read up to the first zero terminator.

	if(sqlite3_prepare16_v2(mDatabase->GetDatabaseHandle(), sqlStatement, -1, &mStatement, NULL ) != SQLITE_OK) {
		KOMPEX_EXCEPT(sqlite3_errmsg(mDatabase->GetDatabaseHandle()), sqlite3_errcode(mDatabase->GetDatabaseHandle()));
	}

	if(!mStatement) {
		KOMPEX_EXCEPT("Prepare() SQL statement failed", -1);
	}
}

bool SQLiteStatement::Step() const
{
    bool bRet=false;

    int iSql=sqlite3_step(mStatement);
    if( iSql == SQLITE_DONE ) {
    }
    else if( iSql == SQLITE_ROW ) {
        bRet = true;
    }
    else {
        KOMPEX_EXCEPT(sqlite3_errmsg(mDatabase->GetDatabaseHandle()), sqlite3_errcode(mDatabase->GetDatabaseHandle()));
    }

// 	switch(sqlite3_step(mStatement))
// 	{
// 		// sqlite3_step() has finished executing
// 		case SQLITE_DONE:
// 			bRet = false;
//             break;
// 		// sqlite3_step() has another row ready
// 		case SQLITE_ROW:
// 			bRet = true;
//             break;
// 		default:
// 			KOMPEX_EXCEPT(sqlite3_errmsg(mDatabase->GetDatabaseHandle()), sqlite3_errcode(mDatabase->GetDatabaseHandle()));
//             //break;
// 	}
    return bRet;
}

void SQLiteStatement::SqlStatement(const char *sqlStatement)
{
	Prepare(sqlStatement);
	Step();
	FreeQuery();
}

void SQLiteStatement::SqlStatement(const wchar_t *sqlStatement)
{
	Prepare(sqlStatement);
	Step();
	FreeQuery();
}

bool SQLiteStatement::FetchRow() const
{
	int rc = sqlite3_step(mStatement);

    bool bRet=false;

    if( rc == SQLITE_BUSY ) {
        bRet = false;
        KOMPEX_EXCEPT("FetchRow() SQLITE_BUSY", SQLITE_BUSY);
    }
    else if( rc == SQLITE_DONE ) {
        bRet = false;
    }
    else if( rc == SQLITE_ROW ) {
        bRet = true;
    }
    else if( rc == SQLITE_ERROR ) {
        bRet = false;
        KOMPEX_EXCEPT(sqlite3_errmsg(mDatabase->GetDatabaseHandle()), SQLITE_ERROR);
    }
    else if( rc == SQLITE_MISUSE ) {
        bRet = false;
        KOMPEX_EXCEPT("FetchRow() SQLITE_MISUSE", SQLITE_MISUSE);
    }
    else {

    }

	return bRet;
}

void SQLiteStatement::FreeQuery()
{
	// destroy prepared statement
	sqlite3_finalize(mStatement);
	mStatement = NULL;
}

void SQLiteStatement::CheckStatement() const
{
	if(!mStatement) {
		KOMPEX_EXCEPT("empty statement pointer", -1);
	}
}

void SQLiteStatement::CheckDatabase() const
{
	if(!mDatabase) {
		KOMPEX_EXCEPT("database pointer invalid", -1);
	}
}

float SQLiteStatement::SqlAggregateFuncResult(const std::string &countSql)
{
	float result=-1.0;

	Sql(countSql);
	while(FetchRow()) {
		result = static_cast<float>(GetColumnDouble(0));
	}

	FreeQuery();
	return result;
}

float SQLiteStatement::SqlAggregateFuncResult(wchar_t *countSql)
{
	float result=-1.0;

	Sql(countSql);
	while(FetchRow()) {
		result = static_cast<float>(GetColumnDouble(0));
	}

	FreeQuery();
	return result;
}

float SQLiteStatement::SqlAggregateFuncResult(const char *countSql)
{
	float result=-1.0;

	Sql(countSql);
	while(FetchRow()) {
		result = static_cast<float>(GetColumnDouble(0));
    }

	FreeQuery();
	return result;
}

//------------------------------------------------------------------------------------
// GetColumn...() Methods

const char *SQLiteStatement::GetColumnName(int column) const
{
	CheckStatement();
	CheckColumnNumber(column, "GetColumnName()");

	return sqlite3_column_name(mStatement, column);
}

const wchar_t *SQLiteStatement::GetColumnName16(int column) const
{
	CheckStatement();
	CheckColumnNumber(column, "GetColumnName16()");

	return (const wchar_t*)sqlite3_column_name16(mStatement, column);
}


const wchar_t *SQLiteStatement::GetColumnCString16(int column) const
{
    const wchar_t *pReturn;

    CheckStatement();
    CheckColumnNumber(column, "GetColumnCString16()");

    pReturn = (const wchar_t *)sqlite3_column_text16(mStatement, column);

    return pReturn;

}

const unsigned char *SQLiteStatement::GetColumnCString(int column ) const
{
    const unsigned char *pReturn;

	CheckStatement();
	CheckColumnNumber(column, "GetColumnCString()");

    pReturn = (const unsigned char *) sqlite3_column_text(mStatement, column);

    return pReturn;

}

std::string SQLiteStatement::GetColumnString(int column) const
{
	CheckStatement();
	CheckColumnNumber(column, "GetColumnString()");

	const unsigned char *result = sqlite3_column_text(mStatement, column);

    std::stringstream ss;

	// capture NULL results
	if(result == NULL ) {
		ss << "";
    }
    else {
	    ss << result;

    }

    return ss.str();

}

double SQLiteStatement::GetColumnDouble(int column) const
{
	CheckStatement();
	CheckColumnNumber(column, "GetColumnDouble()");

	return sqlite3_column_double(mStatement, column);
}

int SQLiteStatement::GetColumnInt(int column) const
{
	CheckStatement();
	CheckColumnNumber(column, "GetColumnInt()");

	return sqlite3_column_int(mStatement, column);
}

bool SQLiteStatement::GetColumnBool(int column) const
{
	CheckStatement();
	CheckColumnNumber(column, "GetColumnBool()");

	return !!sqlite3_column_int(mStatement, column);
}

int64 SQLiteStatement::GetColumnInt64(int column) const
{
	CheckStatement();
	CheckColumnNumber(column, "GetColumnInt64()");

	return sqlite3_column_int64(mStatement, column);
}

int SQLiteStatement::GetColumnType(int column) const
{
	CheckStatement();
	CheckColumnNumber(column, "GetColumnType()");

	return sqlite3_column_type(mStatement, column);
}

const wchar_t *SQLiteStatement::GetColumnString16(int column) const
{
	CheckStatement();
	CheckColumnNumber(column, "GetColumnString16()");

	return (const wchar_t*) sqlite3_column_text16(mStatement, column);
}

const void *SQLiteStatement::GetColumnBlob(int column) const
{
	CheckStatement();
	CheckColumnNumber(column, "GetColumnBlob()");

	return sqlite3_column_blob(mStatement, column);
}

int SQLiteStatement::GetColumnCount() const
{
	CheckStatement();
	return sqlite3_column_count(mStatement);
}

int SQLiteStatement::GetColumnBytes(int column) const
{
	CheckStatement();
	CheckColumnNumber(column, "GetColumnBytes()");

	return sqlite3_column_bytes(mStatement, column);
}

int SQLiteStatement::GetColumnBytes16(int column) const
{
	CheckStatement();
	CheckColumnNumber(column, "GetColumnBytes16()");

	return sqlite3_column_bytes16(mStatement, column);
}

const char *SQLiteStatement::GetColumnDatabaseName(int column) const
{
	CheckStatement();
	CheckColumnNumber(column, "GetColumnDatabaseName()");

	return sqlite3_column_database_name(mStatement, column);
}

const wchar_t *SQLiteStatement::GetColumnDatabaseName16(int column) const
{
	CheckStatement();
	CheckColumnNumber(column, "GetColumnDatabaseName16()");

	return (const wchar_t *) sqlite3_column_database_name16(mStatement, column);
}

const char *SQLiteStatement::GetColumnTableName(int column) const
{
	CheckStatement();
	CheckColumnNumber(column, "GetColumnTableName()");

	return sqlite3_column_table_name(mStatement, column);
}

// wchar_t *SQLiteStatement::GetColumnTableName16(int column) const
// {
// 	CheckStatement();
// 	CheckColumnNumber(column, "GetColumnTableName16()");
//
// 	return (wchar_t*)sqlite3_column_table_name16(mStatement, column);
// }

const char *SQLiteStatement::GetColumnOriginName(int column) const
{
	CheckStatement();
	CheckColumnNumber(column, "GetColumnOriginName()");

	return sqlite3_column_origin_name(mStatement, column);
}

// wchar_t *SQLiteStatement::GetColumnOriginName16(int column) const
// {
// 	CheckStatement();
// 	CheckColumnNumber(column, "GetColumnOriginName16()");
//
// 	return (wchar_t*)sqlite3_column_origin_name16(mStatement, column);
// }

// const char *SQLiteStatement::GetColumnDeclaredDatatype(int column) const
// {
// 	CheckStatement();
// 	CheckColumnNumber(column, "GetColumnDeclaredDatatype()");
//
// 	return sqlite3_column_decltype(mStatement, column);
// }

// wchar_t *SQLiteStatement::GetColumnDeclaredDatatype16(int column) const
// {
// 	CheckStatement();
// 	CheckColumnNumber(column, "GetColumnDeclaredDatatype16()");
//
// 	return (wchar_t*)sqlite3_column_decltype16(mStatement, column);
// }

int SQLiteStatement::GetColumnBytes(const std::string &column) const
{
	AssignColumnNumberToColumnName();
	return sqlite3_column_bytes(mStatement, GetAssignedColumnNumber(column));
}

int SQLiteStatement::GetColumnBytes16(const std::string &column) const
{
	AssignColumnNumberToColumnName();
	return sqlite3_column_bytes16(mStatement, GetAssignedColumnNumber(column));
}

const char *SQLiteStatement::GetColumnDatabaseName(const std::string &column) const
{
	AssignColumnNumberToColumnName();
	return sqlite3_column_database_name(mStatement, GetAssignedColumnNumber(column));
}

const wchar_t *SQLiteStatement::GetColumnDatabaseName16(const std::string &column) const
{
	AssignColumnNumberToColumnName();
	return (const wchar_t*)sqlite3_column_database_name16(mStatement, GetAssignedColumnNumber(column));
}

const char *SQLiteStatement::GetColumnTableName(const std::string &column) const
{
	AssignColumnNumberToColumnName();
	return sqlite3_column_table_name(mStatement, GetAssignedColumnNumber(column));
}

const wchar_t *SQLiteStatement::GetColumnTableName16(const std::string &column) const
{
	AssignColumnNumberToColumnName();
	return (const wchar_t*)sqlite3_column_table_name16(mStatement, GetAssignedColumnNumber(column));
}

const char *SQLiteStatement::GetColumnOriginName(const std::string &column) const
{
	AssignColumnNumberToColumnName();
	return sqlite3_column_origin_name(mStatement, GetAssignedColumnNumber(column));
}

const wchar_t *SQLiteStatement::GetColumnOriginName16(const std::string &column) const
{
	AssignColumnNumberToColumnName();
	return ( const wchar_t*)sqlite3_column_origin_name16(mStatement, GetAssignedColumnNumber(column));
}

const char *SQLiteStatement::GetColumnDeclaredDatatype(const std::string &column) const
{
	AssignColumnNumberToColumnName();
	return sqlite3_column_decltype(mStatement, GetAssignedColumnNumber(column));
}

const wchar_t *SQLiteStatement::GetColumnDeclaredDatatype16(const std::string &column) const
{
	AssignColumnNumberToColumnName();
	return ( const wchar_t*)sqlite3_column_decltype16(mStatement, GetAssignedColumnNumber(column));
}

const char *SQLiteStatement::GetColumnName(const std::string &column) const
{
	AssignColumnNumberToColumnName();
	return sqlite3_column_name(mStatement, GetAssignedColumnNumber(column));
}

// const wchar_t *SQLiteStatement::GetColumnName16(const std::string &column) const
// {
// 	AssignColumnNumberToColumnName();
// 	return (wchar_t*)sqlite3_column_name16(mStatement, GetAssignedColumnNumber(column));
// }

const unsigned char *SQLiteStatement::GetColumnCString(const std::string &column) const
{
	AssignColumnNumberToColumnName();
	return sqlite3_column_text(mStatement, GetAssignedColumnNumber(column));
}

/**
 * @brief     테이블의 특정 필드에서 문자열로 리턴한다.
 * @param     const std::string & column
 * @return    std::string
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-07-04 18:44:08
 * @warning
 */
std::string SQLiteStatement::GetColumnString(const std::string &column) const
{
    std::stringstream ss;

	AssignColumnNumberToColumnName();

	const unsigned char *result = sqlite3_column_text(mStatement, GetAssignedColumnNumber(column));

	// capture NULL results
    if (result == NULL) {
        ss << "";
    }

    else {
        ss << result;
    }

	return ss.str();
}

double SQLiteStatement::GetColumnDouble(const std::string &column) const
{
	AssignColumnNumberToColumnName();
	return sqlite3_column_double(mStatement, GetAssignedColumnNumber(column));
}

int SQLiteStatement::GetColumnInt(const std::string &column) const
{
	AssignColumnNumberToColumnName();
	return sqlite3_column_int(mStatement, GetAssignedColumnNumber(column));
}

bool SQLiteStatement::GetColumnBool(const std::string &column) const
{
	AssignColumnNumberToColumnName();
	return !!sqlite3_column_int(mStatement, GetAssignedColumnNumber(column));
}

int64 SQLiteStatement::GetColumnInt64(const std::string &column) const
{
	AssignColumnNumberToColumnName();
	return sqlite3_column_int64(mStatement, GetAssignedColumnNumber(column));
}

int SQLiteStatement::GetColumnType(const std::string &column) const
{
	AssignColumnNumberToColumnName();
	return sqlite3_column_type(mStatement, GetAssignedColumnNumber(column));
}

const wchar_t *SQLiteStatement::GetColumnString16(const std::string &column) const
{
	AssignColumnNumberToColumnName();
	//return (wchar_t*)sqlite3_column_text16(mStatement, GetAssignedColumnNumber(column));
    return (const wchar_t*)sqlite3_column_text16(mStatement, GetAssignedColumnNumber(column));
}

const void *SQLiteStatement::GetColumnBlob(const std::string &column) const
{
	AssignColumnNumberToColumnName();
	return sqlite3_column_blob(mStatement, GetAssignedColumnNumber(column));
}

//------------------------------------------------------------------------------------
// Bind...() Methods

void SQLiteStatement::BindInt(int column, int value) const
{
	if(sqlite3_bind_int(mStatement, column, value) != SQLITE_OK) {
		KOMPEX_EXCEPT(sqlite3_errmsg(mDatabase->GetDatabaseHandle()), sqlite3_errcode(mDatabase->GetDatabaseHandle()));
	}
}

void SQLiteStatement::BindBool(int column, bool value) const
{
	if(sqlite3_bind_int(mStatement, column, static_cast<int>(value)) != SQLITE_OK) {
		KOMPEX_EXCEPT(sqlite3_errmsg(mDatabase->GetDatabaseHandle()), sqlite3_errcode(mDatabase->GetDatabaseHandle()));
	}
}

void SQLiteStatement::BindString(int column, const std::string &string) const
{
	// SQLITE_TRANSIENT: SQLite makes its own private copy of the data immediately, before the sqlite3_bind_*() routine returns
	if(sqlite3_bind_text(mStatement, column, string.c_str(), (int) string.length(), SQLITE_TRANSIENT) != SQLITE_OK) {
		KOMPEX_EXCEPT(sqlite3_errmsg(mDatabase->GetDatabaseHandle()), sqlite3_errcode(mDatabase->GetDatabaseHandle()));
	}
}

void SQLiteStatement::BindString16(int column, const wchar_t *string) const
{
	// SQLITE_TRANSIENT: SQLite makes its own private copy of the data immediately, before the sqlite3_bind_*() routine returns
	if(sqlite3_bind_text16(mStatement, column, string, -1, SQLITE_TRANSIENT) != SQLITE_OK) {
		KOMPEX_EXCEPT(sqlite3_errmsg(mDatabase->GetDatabaseHandle()), sqlite3_errcode(mDatabase->GetDatabaseHandle()));
	}
}

void SQLiteStatement::BindString64(int column, const char *string, uint64 byteLength, ENCODING encoding) const
{
	// SQLITE_TRANSIENT: SQLite makes its own private copy of the data immediately, before the sqlite3_bind_*() routine returns
    int iSql=sqlite3_bind_text64(mStatement, column, string, byteLength, SQLITE_TRANSIENT, (unsigned char) encoding);

    if( iSql == SQLITE_OK ) {

    }
    else if( iSql == SQLITE_TOOBIG ) {
        KOMPEX_EXCEPT("SQLITE_TOOBIG - string was larger than stated in byteLength or exceeded the default maximum length", -1);
        //KOMPEX_EXCEPT(sqlite3_errmsg(mDatabase->GetDatabaseHandle()), sqlite3_errcode(mDatabase->GetDatabaseHandle()));
    }
    else {
        KOMPEX_EXCEPT(sqlite3_errmsg(mDatabase->GetDatabaseHandle()), sqlite3_errcode(mDatabase->GetDatabaseHandle()));
    }

// 	switch(sqlite3_bind_text64(mStatement, column, string, byteLength, SQLITE_TRANSIENT, encoding))
// 	{
// 		case SQLITE_OK:
// 			break;
// 		case SQLITE_TOOBIG:
// 			KOMPEX_EXCEPT("SQLITE_TOOBIG - string was larger than stated in byteLength or exceeded the default maximum length", -1);
//             KOMPEX_EXCEPT(sqlite3_errmsg(mDatabase->GetDatabaseHandle()), sqlite3_errcode(mDatabase->GetDatabaseHandle()));
//             // break;
// 		default:
// 			KOMPEX_EXCEPT(sqlite3_errmsg(mDatabase->GetDatabaseHandle()), sqlite3_errcode(mDatabase->GetDatabaseHandle()));
//             //break;
// 	}
}

void SQLiteStatement::BindDouble(int column, double value) const
{
	if(sqlite3_bind_double(mStatement, column, value) != SQLITE_OK) {
		KOMPEX_EXCEPT(sqlite3_errmsg(mDatabase->GetDatabaseHandle()), sqlite3_errcode(mDatabase->GetDatabaseHandle()));
	}
}

void SQLiteStatement::BindInt64(int column, int64 value) const
{
	if(sqlite3_bind_int64(mStatement, column, value) != SQLITE_OK) {
		KOMPEX_EXCEPT(sqlite3_errmsg(mDatabase->GetDatabaseHandle()), sqlite3_errcode(mDatabase->GetDatabaseHandle()));
	}
}

void SQLiteStatement::BindNull(int column) const
{
	if(sqlite3_bind_null(mStatement, column) != SQLITE_OK) {
		KOMPEX_EXCEPT(sqlite3_errmsg(mDatabase->GetDatabaseHandle()), sqlite3_errcode(mDatabase->GetDatabaseHandle()));
	}
}

void SQLiteStatement::BindBlob(int column, const void* data, int numberOfBytes) const
{
	if(sqlite3_bind_blob(mStatement, column, data, numberOfBytes, SQLITE_TRANSIENT) != SQLITE_OK) {
		KOMPEX_EXCEPT(sqlite3_errmsg(mDatabase->GetDatabaseHandle()), sqlite3_errcode(mDatabase->GetDatabaseHandle()));
	}
}

void SQLiteStatement::BindBlob64(int column, const void* data, uint64 numberOfBytes) const
{
	if(sqlite3_bind_blob64(mStatement, column, data, numberOfBytes, SQLITE_TRANSIENT) != SQLITE_OK) {
		KOMPEX_EXCEPT(sqlite3_errmsg(mDatabase->GetDatabaseHandle()), sqlite3_errcode(mDatabase->GetDatabaseHandle()));
	}
}

void SQLiteStatement::BindZeroBlob(int column, int length) const
{
	if(sqlite3_bind_zeroblob(mStatement, column, length) != SQLITE_OK) {
		KOMPEX_EXCEPT(sqlite3_errmsg(mDatabase->GetDatabaseHandle()), sqlite3_errcode(mDatabase->GetDatabaseHandle()));
	}
}

void SQLiteStatement::BindZeroBlob64(int column, uint64 length) const
{
	if(sqlite3_bind_zeroblob64(mStatement, column, length) != SQLITE_OK) {
		KOMPEX_EXCEPT(sqlite3_errmsg(mDatabase->GetDatabaseHandle()), sqlite3_errcode(mDatabase->GetDatabaseHandle()));
	}
}

//------------------------------------------------------------------------------------
void SQLiteStatement::ExecuteAndFree()
{
	Step();
	FreeQuery();
}

void SQLiteStatement::Execute() const
{
	Step();
}

void SQLiteStatement::GetTable(const std::string &sql, unsigned short consoleOutputColumnWidth) const
{
	CheckDatabase();

	char *errMsg;
	char **result;
	int rows, columns;

	if(sqlite3_get_table(mDatabase->GetDatabaseHandle(), sql.c_str(), &result, &rows, &columns, &errMsg) != SQLITE_OK) {
		KOMPEX_EXCEPT(sqlite3_errmsg(mDatabase->GetDatabaseHandle()), sqlite3_errcode(mDatabase->GetDatabaseHandle()));
	}

	int counter = 0;
	for(int r = 0; r <= rows; ++r)
	{
		for(int c = 0; c < columns; ++c)
		{
			std::cout << std::left << std::setw(consoleOutputColumnWidth - 3);
			if(result[counter]) {
				std::cout << result[counter];
			}
			else {
				std::cout << "NULL";
			}

			if(c < columns - 1) {
				std::cout << " | ";
			}

			counter++;
		}
		std::cout << std::endl;

		if(r == 0)
		{
			for(int dum = consoleOutputColumnWidth * columns; dum != 0; --dum) {
				std::cout << "-";
			}

			std::cout << std::endl;
		}
	}

	sqlite3_free_table(result);
}

void SQLiteStatement::GetTableColumnMetadata(const std::string &tableName, const std::string &columnName) const
{
	CheckDatabase();

	int notnull, primaryKey, autoInc;
	const char *dataType, *collSeq;

	if(sqlite3_table_column_metadata(mDatabase->GetDatabaseHandle(), NULL, tableName.c_str(), columnName.c_str(), &dataType, &collSeq, &notnull, &primaryKey, &autoInc)) {
		KOMPEX_EXCEPT(sqlite3_errmsg(mDatabase->GetDatabaseHandle()), sqlite3_errcode(mDatabase->GetDatabaseHandle()));
	}

	std::cout << "TableColumnMetadata:" << std::endl;
	std::cout << "data type: " << dataType << std::endl;
	std::cout << "collation sequence: " << primaryKey << std::endl;
	std::cout << "not null: " << notnull << std::endl;
	std::cout << "primary key: " << primaryKey << std::endl;
	std::cout << "auto increment: " << autoInc << std::endl;
}

void SQLiteStatement::ClearBindings() const
{
	CheckStatement();

    sqlite3_clear_bindings(mStatement);

//     if(sqlite3_clear_bindings(mStatement) != SQLITE_OK) {
// 		// KOMPEX_EXCEPT(sqlite3_errmsg(mDatabase->GetDatabaseHandle()), sqlite3_errcode(mDatabase->GetDatabaseHandle()));
//     }
}

void SQLiteStatement::Reset() const
{
	CheckStatement();

	if(sqlite3_reset(mStatement) != SQLITE_OK) {
		KOMPEX_EXCEPT(sqlite3_errmsg(mDatabase->GetDatabaseHandle()), sqlite3_errcode(mDatabase->GetDatabaseHandle()));
	}
}

/**
 * @brief     트랜젝션을 커밋하여 반영한다.
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-07-04 18:39:51
 * @warning
 */
void SQLiteStatement::CommitTheTransaction()
{
	if(!mTransactionSQL.empty() || !mTransactionSQL16.empty())
	{
		try
		{

			// check wheter we have sql statements with different data types
			if(!mTransactionSQL.empty() && !mTransactionSQL16.empty())
			{
				//
				CommitDifferentDataTypes();

			}
			else
			{
				// because we have only one data type, we can execute all sql statements from the filled container
				if(!mTransactionSQL.empty())
				{
					for(TTransactionSQL::iterator transIter = mTransactionSQL.begin(); transIter != mTransactionSQL.end(); ++transIter) {
						SqlStatement(transIter->second.first);
					}
				}
				else
				{
					for(TTransactionSQL16::iterator trans16Iter = mTransactionSQL16.begin(); trans16Iter != mTransactionSQL16.end(); ++trans16Iter) {
						SqlStatement(trans16Iter->second.first);
					}
				}
			}

			SqlStatement("COMMIT;");
			CleanUpTransaction();
		}
		catch(SQLiteException &exception)
		{
			std::cerr << "Exception Occured!" << std::endl;
			exception.Show();
			RollbackTheTransaction();
			std::cerr << "Rollback has been executed!" << std::endl;
			CleanUpTransaction();
		}
	}
	else
	{
		SqlStatement("COMMIT;");
	}
	mTransactionID = 0;
}

/**
 * @brief     CommitDifferentDataTypes
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-02-03 16:19:21
 * @warning
 */
void SQLiteStatement::CommitDifferentDataTypes()
{
	unsigned short us = 0;

	TTransactionSQL::iterator transIter;
	TTransactionSQL16::iterator trans16Iter;

	unsigned short transactions = (unsigned short) ( mTransactionSQL.size() + mTransactionSQL16.size() );

	while (us < transactions)
	{
		transIter = mTransactionSQL.find(us);
		if (transIter != mTransactionSQL.end())
		{
			SqlStatement(transIter->second.first);
		}
		else
		{
			trans16Iter = mTransactionSQL16.find(us);
			if (trans16Iter != mTransactionSQL16.end())
			{
				SqlStatement(trans16Iter->second.first);
			}
			else
			{
				KOMPEX_EXCEPT("CommitTransaction() transaction id not found", -1);
			}
		}

		++us;
	}
}

void SQLiteStatement::CleanUpTransaction()
{
	// clean up memory and container
	for(TTransactionSQL::iterator transIter = mTransactionSQL.begin(); transIter != mTransactionSQL.end(); ++transIter) {
		DeleteTransactionSqlStr(transIter->second.second, transIter->second.first);
	}
	mTransactionSQL.clear();

	for(TTransactionSQL16::iterator trans16Iter = mTransactionSQL16.begin(); trans16Iter != mTransactionSQL16.end(); ++trans16Iter) {
		DeleteTransactionSqlStr(trans16Iter->second.second, trans16Iter->second.first);
	}
	mTransactionSQL16.clear();
}

void SQLiteStatement::BeginTransaction()
{
	SqlStatement("BEGIN;");
	CleanUpTransaction();
}

void SQLiteStatement::SecureTransaction(const char *sql)
{
	char *buffer = new char[strlen(sql) + 1];
	strcpy(buffer, sql);
	mTransactionSQL[mTransactionID++] = std::make_pair(buffer, true);
}

void SQLiteStatement::SecureTransaction(const std::string sql)
{
	char *buffer = new char[sql.length() + 1];
	strcpy(buffer, sql.c_str());
	mTransactionSQL[mTransactionID++] = std::make_pair(buffer, true);
}

void SQLiteStatement::SecureTransaction(const wchar_t *sql)
{
	//wchar_t *buffer = new wchar_t[wcslen(sql) + 1];
	//wcscpy(buffer, sql);
	//mTransactionSQL16[mTransactionID++] = std::make_pair(buffer, true);
}

//------------------------------------------------------------------------------------
template<class S, class T>
T SQLiteStatement::GetColumnValue(S sql, T(Kompex::SQLiteStatement::*getColumnFunc)(int columnNumber)const, T defaultReturnValue)
{
	Sql(sql);

	T queryResult;

	if(!FetchRow()) {
		queryResult = defaultReturnValue;
	}
	else {
		queryResult = (this->*getColumnFunc)(0);
	}

	FreeQuery();

	return queryResult;
}

std::string SQLiteStatement::GetSqlResultString(const std::string &sql, const std::string &defaultReturnValue)
{
	return GetColumnValue(sql, &Kompex::SQLiteStatement::GetColumnString, defaultReturnValue);
}

std::string SQLiteStatement::GetSqlResultString(const char *sql, const std::string &defaultReturnValue)
{
	return GetColumnValue(sql, &Kompex::SQLiteStatement::GetColumnString, defaultReturnValue);
}

std::string SQLiteStatement::GetSqlResultString(const wchar_t *sql, const std::string &defaultReturnValue)
{
	return GetColumnValue(sql, &Kompex::SQLiteStatement::GetColumnString, defaultReturnValue);
}

int SQLiteStatement::GetSqlResultInt(const std::string &sql, int defaultReturnValue)
{
	return GetColumnValue(sql, &Kompex::SQLiteStatement::GetColumnInt, defaultReturnValue);
}

int SQLiteStatement::GetSqlResultInt(const char *sql, int defaultReturnValue)
{
	return GetColumnValue(sql, &Kompex::SQLiteStatement::GetColumnInt, defaultReturnValue);
}

int SQLiteStatement::GetSqlResultInt(const wchar_t *sql, int defaultReturnValue)
{
	return GetColumnValue(sql, &Kompex::SQLiteStatement::GetColumnInt, defaultReturnValue);
}

int64 SQLiteStatement::GetSqlResultInt64(const std::string &sql, int64 defaultReturnValue)
{
	return GetColumnValue<std::string, int64>(sql, &Kompex::SQLiteStatement::GetColumnInt64, defaultReturnValue);
}

int64 SQLiteStatement::GetSqlResultInt64(const char *sql, int64 defaultReturnValue)
{
	return GetColumnValue<const char*, int64>(sql, &Kompex::SQLiteStatement::GetColumnInt64, defaultReturnValue);
}

int64 SQLiteStatement::GetSqlResultInt64(const wchar_t *sql, int64 defaultReturnValue)
{
	return GetColumnValue<const wchar_t*, int64>(sql, &Kompex::SQLiteStatement::GetColumnInt64, defaultReturnValue);
}

double SQLiteStatement::GetSqlResultDouble(const std::string &sql, double defaultReturnValue)
{
	return GetColumnValue(sql, &Kompex::SQLiteStatement::GetColumnDouble, defaultReturnValue);
}

double SQLiteStatement::GetSqlResultDouble(const char *sql, double defaultReturnValue)
{
	return GetColumnValue(sql, &Kompex::SQLiteStatement::GetColumnDouble, defaultReturnValue);
}

double SQLiteStatement::GetSqlResultDouble(const wchar_t *sql, double defaultReturnValue)
{
	return GetColumnValue(sql, &Kompex::SQLiteStatement::GetColumnDouble, defaultReturnValue);
}

const unsigned char *SQLiteStatement::SqlResultCString(const unsigned char *defaultReturnValue)
{
	const unsigned char *queryResult;

	if(!FetchRow()) {
		queryResult = defaultReturnValue;
	}
	else {
		queryResult = SQLiteStatement::GetColumnCString(0);
	}

	std::stringstream strStream;
	strStream << queryResult;
	std::string result = strStream.str();

	unsigned char *buffer = new unsigned char[result.length() + 1];
	memcpy(buffer, result.c_str(), result.length() + 1);

	FreeQuery();

	return buffer;
}

const unsigned char *SQLiteStatement::GetSqlResultCString(const std::string &sql, const unsigned char *defaultReturnValue)
{
	Sql(sql);
	return SqlResultCString(defaultReturnValue);
}

const unsigned char *SQLiteStatement::GetSqlResultCString(const char *sql, const unsigned char *defaultReturnValue)
{
	Sql(sql);
	return SqlResultCString(defaultReturnValue);
}

const unsigned char *SQLiteStatement::GetSqlResultCString(const wchar_t *sql, const unsigned char *defaultReturnValue)
{
	Sql(sql);
	return SqlResultCString(defaultReturnValue);
}

wchar_t *SQLiteStatement::SqlResultString16(wchar_t *defaultReturnValue)
{
	const wchar_t *queryResult;

	if(!FetchRow()) {
		queryResult = defaultReturnValue;
	}
	else {
		queryResult = SQLiteStatement::GetColumnString16(0);
	}

	std::stringstream wstrStream;
	wstrStream << queryResult;
	std::string result = wstrStream.str();

	wchar_t *buffer = new wchar_t[result.length() + 1];
	memcpy(buffer, result.c_str(), result.length() + 1);

	FreeQuery();

	return buffer;
}

wchar_t *SQLiteStatement::GetSqlResultString16(const std::string &sql, wchar_t *defaultReturnValue)
{
	Sql(sql);
	return SqlResultString16(defaultReturnValue);
}

wchar_t *SQLiteStatement::GetSqlResultString16(const char *sql, wchar_t *defaultReturnValue)
{
	Sql(sql);
	return SqlResultString16(defaultReturnValue);
}

wchar_t *SQLiteStatement::GetSqlResultString16(const wchar_t *sql, wchar_t *defaultReturnValue)
{
	Sql(sql);
	return SqlResultString16(defaultReturnValue);
}

const void *SQLiteStatement::SqlResultBlob(const void *defaultReturnValue)
{
	const void *queryResult;

	if(!FetchRow()) {
		queryResult = defaultReturnValue;
	}
	else {
		queryResult = SQLiteStatement::GetColumnBlob(0);
	}

	std::stringstream strStream;
	strStream << static_cast<const char *>(queryResult);
	std::string result = strStream.str();

	char *buffer = new char[result.length() + 1];
	memcpy(buffer, result.c_str(), result.length() + 1);

	FreeQuery();

	return static_cast<void *>(buffer);
}

const void *SQLiteStatement::GetSqlResultBlob(const std::string &sql, const void *defaultReturnValue)
{
	Sql(sql);
	return SqlResultBlob(defaultReturnValue);
}

const void *SQLiteStatement::GetSqlResultBlob(const char *sql, const void *defaultReturnValue)
{
	Sql(sql);
	return SqlResultBlob(defaultReturnValue);
}

const void *SQLiteStatement::GetSqlResultBlob(const wchar_t *sql, const void *defaultReturnValue)
{
	Sql(sql);
	return SqlResultBlob(defaultReturnValue);
}

//------------------------------------------------------------------------------------
unsigned int SQLiteStatement::GetNumberOfRows()
{
	unsigned int uiCount = 0;
	while(FetchRow()) {
		++uiCount;
	}

	Reset();
	return uiCount;
}

void SQLiteStatement::CheckColumnNumber(int columnNumber, const std::string &functionName) const
{
    if(columnNumber < 0 || columnNumber >= sqlite3_column_count(mStatement)) {
        KOMPEX_EXCEPT(functionName + " column number does not exists", -1);
	}
}

//------------------------------------------------------------------------------------
void SQLiteStatement::AssignColumnNumberToColumnName() const
{
	CheckStatement();

	// a previous executed SELECT query is necessary
	if(!mIsColumnNumberAssignedToColumnName && sqlite3_column_count(mStatement) >= 0)
	{
		// delete old entries
		auto iterBegin=mColumnNumberToColumnNameAssignment.begin();
		auto iterEnd = mColumnNumberToColumnNameAssignment.end();
		mColumnNumberToColumnNameAssignment.erase(iterBegin, iterEnd);

		for(int i = 0; i < sqlite3_column_count(mStatement); ++i) {
			mColumnNumberToColumnNameAssignment[sqlite3_column_name(mStatement, i)] = i;
		}

		mIsColumnNumberAssignedToColumnName = true;
    }
}

int SQLiteStatement::GetAssignedColumnNumber(const std::string &columnName) const
{
	std::map<std::string, int>::const_iterator iter = mColumnNumberToColumnNameAssignment.find(columnName);

	if(iter == mColumnNumberToColumnNameAssignment.end())
	{
		// if you don't catch the exception then we will return -1 so that the function sqlite3_column_*()
		// will return a undefined value
		KOMPEX_EXCEPT("GetAssignedColumnNumber() column name '" + columnName + "' does not exists", -1);
		//return -1;
	}

	return iter->second;
}

// std::string SQLiteStatement::Mprintf(const char *sql, ...)
// {
//     va_list args;
//     va_start(args, sql);
// 	char *sqlResult = sqlite3_vmprintf(sql, args);
// 	va_end(args);
//
// 	if(!sqlResult)
// 	{
// 		KOMPEX_EXCEPT("unable to allocate enough memory to hold the resulting string", -1);
// 		//return "";
// 	}
//
// 	std::string result = sqlResult;
// 	sqlite3_free(sqlResult);
// 	return result;
// }

// std::string SQLiteStatement::Vmprintf(const char *sql, va_list args)
// {
// 	char *sqlResult = sqlite3_vmprintf(sql, args);
//
// 	if(!sqlResult) {
// 		KOMPEX_EXCEPT("unable to allocate enough memory to hold the resulting string", -1);
// 		//return "";
// 	}
//
// 	std::string result = sqlResult;
// 	sqlite3_free(sqlResult);
// 	return result;
//
// }

}	// namespace Kompex

#endif