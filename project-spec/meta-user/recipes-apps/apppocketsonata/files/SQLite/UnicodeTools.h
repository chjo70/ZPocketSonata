//******************************************************************************//
//
//  Helper file for the sample application illustrating the usage of 
//  the CSQLiteDatabase and CSQLiteRecordset classes, used to access SQLite 
//  databases from MFC applications
//
//  Designed for the Oxetta report builder, the free report design and print
//  library for C/C++ developers
//
//  http://www.oxetta.com for more details
//
//******************************************************************************//

#pragma once

#define FREE_AND_NULL(pointer)\
{\
	free((void*)pointer);\
	pointer = NULL;\
}

char* Utf16ToAnsi(WCHAR *wszString, int *piLength = NULL);
WCHAR* AnsiToUtf16(char *szString, int *piLength = NULL);
char* Utf16ToUtf8(WCHAR *wszSource, int *piLength = NULL);
WCHAR* Utf8ToUtf16(char *szSource, int *piLength = NULL);
char* AnsiToUtf8(char *szSource, int *piLength = NULL);
char* Utf8ToAnsi(char *szSource, int *piLength = NULL);
char* ToUtf8(LPCTSTR szSource, int *piLength = NULL);
CString FromUtf8(char* szSource);
