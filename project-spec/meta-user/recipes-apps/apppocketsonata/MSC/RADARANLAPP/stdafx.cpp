
// stdafx.cpp : 표준 포함 파일만 들어 있는 소스 파일입니다.
// RADARANLAPP.pch는 미리 컴파일된 헤더가 됩니다.
// stdafx.obj에는 미리 컴파일된 형식 정보가 포함됩니다.

#include "stdafx.h"

#include <stdio.h>

#include "../RADARANL/RadarAnlAlgorithm.h"

HWND sthWnd;

CCriticalSection g_criticalLog;
CCriticalSection g_criticalDbg;
CCriticalSection g_criticalExe;

// void Log( int nType, const char *fmt, ... )
// {
// 	g_criticalLog.Lock();
// 
// 	static _TCHAR szLog[5096];
// 
// 	FILE *fp=NULL;
// 	CTime tm=CTime::GetCurrentTime();
// 
// 	CString strLog, strPath, strTemp;
// 
// 	va_list args;
// 	SYSTEMTIME cur_time;
// 
// 	if( fmt != NULL ) {
// 		ZeroMemory( szLog, sizeof(szLog) );
// 
// 		va_start( args, fmt );
// 		wvsprintf( szLog, fmt, args );
// 		va_end( args );
// 
// 		strPath.Format( "%s\\%s", GetFilePath(), LOG_DIRECTORY );
// 		CreateDir( (LPSTR) (LPCSTR) strPath );
// 		//strTemp.Format( "\\%s" , tm.Format("%Y_%m_%d_%H.log" ) );
// 		strTemp.Format( "\\%s" , tm.Format("%Y_%m_%d.log" ) );
// 		strPath = strPath + "//" + strTemp;
// 
// 		fopen_s( & fp, (LPSTR) (LPCSTR) strPath, "a+" );
// 
// 		GetLocalTime( & cur_time );
// 
// 		strLog.Format( "%04d-%02d-%02d %02d:%02d:%02d:%3ld" , cur_time.wYear, cur_time.wMonth, cur_time.wDay, cur_time.wHour, cur_time.wMinute, cur_time.wSecond, cur_time.wMilliseconds );
// 
// 		if( fp != NULL ) {
// 			switch( nType ) {
// 			case enNormal :
// 				strLog += _T( "[NORMAL]\t" );
// 				break;
// 			case enDebug :
// 				strLog += _T( "[DEBUG ]\t" );
// 				break;
// 			case enEnd :
// 				strLog += _T( "[END   ]\t" );
// 				break;
// 			case enError :
// 				strLog += _T( "[ERROR ]\t" );
// 				break;
// 
// 			default :
// 				break;
// 			}
// 
// 			strLog += szLog;
// 
// 			fprintf( fp, "%s\n" , (LPCSTR) (LPCSTR) strLog );
// 			fflush( fp );
// 			fclose( fp );
// 		}
// 		else {
// 			CString strErrorMsg;
// 			DWORD dwErrNo=GetLastError();
// 
// 			strErrorMsg.Format( "LOG FILE Open Fail : Code = [%d]" , dwErrNo );
// 		}
// 	}
// 
// 	g_criticalLog.Unlock();
// 
// }

CString GetFilePath()
{
	g_criticalExe.Lock();

	static TCHAR pBuf[256] = { 0, } ;

	memset( pBuf, NULL, sizeof(pBuf) );

	GetModuleFileName( NULL, pBuf, sizeof(pBuf) );

	CString strFilePath;

	strFilePath.Format( _T("%s"), pBuf );
	strFilePath = strFilePath.Left( strFilePath.ReverseFind( _T('\\') ) );

	g_criticalExe.Unlock();

	return strFilePath;

}

BOOL CreateDir( char *pPath )
{
	BOOL bRet;
	char dirName[256];
	char *p=pPath;
	char *q=dirName;

	while( *p ) {
		if( ('\\' == *p) || ('/'==*p)) {
			if( ':' != *(p-1) ) {
				CreateDirectory( dirName, NULL );
			}
		}

		*q++ = *p++;
		*q = '\0';
	}
	bRet = CreateDirectory( dirName, NULL );

	return bRet;
}

CString GetIpAddress()
{
	WORD wVersionRequested;
	WSADATA wsaData;
	char name[255];
	PHOSTENT hostinfo;
	CString strIpAddress = "";
	wVersionRequested = MAKEWORD(2, 0);

	if(WSAStartup(wVersionRequested, &wsaData) == 0)
	{
		if(gethostname(name, sizeof(name)) == 0)
		{
			if((hostinfo = gethostbyname(name)) != NULL)
				strIpAddress = inet_ntoa (*(struct in_addr *)*hostinfo->h_addr_list);
		} 
		WSACleanup();
	}

	//AfxMessageBox(strIpAddress);

	return strIpAddress;
}

void SetWindowHandler( HWND hWnd )
{
	sthWnd = hWnd;
}

int Printf(char *format, ...)
{
	char str[200];
	int cnt;

	va_list argptr;

	memset(str, 0, sizeof(str));

	va_start(argptr, format);            /* Initialize variable arguments. */
	cnt = vsprintf_s(str, format, argptr);
	va_end(argptr);              /* Reset variable arguments.      */

	OutputDebugString( str );
	SendMessage( sthWnd, WM_USER_LOGMSG, (WPARAM) str, NULL );
	//SendMessage( sthWnd, WM_USER_LOGMSG, (WPARAM) str, NULL );
	//TRACE( "%s", str );
	// pView->LogPrintf( str );
	return(cnt);

}

// enPosition GetPosition()
// {
// 	enPosition enPos;
// 	CString strIPAddress=GetIpAddress();
// 
// 	if( strIPAddress.Compare( OFFICE_IP ) == 0 ) {
// 		enPos = enOffice;
// 	}
// 	else if( strIPAddress.Compare( MYHOME_IP ) == 0 ) {
// 		enPos = enMyHome;
// 	}
// 	else {
// 		enPos = enBuiltIn;
// 	}
// 
// 	return enPos;
// 
// }