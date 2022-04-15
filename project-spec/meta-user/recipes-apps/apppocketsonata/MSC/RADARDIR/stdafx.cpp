// stdafx.cpp : 표준 포함 파일만 들어 있는 소스 파일입니다.
// RADARDIR.pch는 미리 컴파일된 헤더가 됩니다.
// stdafx.obj에는 미리 컴파일된 형식 정보가 포함됩니다.

#include "stdafx.h"

#include <stdio.h>

#include <iphlpapi.h>
#include <icmpapi.h>

#include <winsock.h>
#include <Ipexport.h>

#pragma comment( lib, "Iphlpapi" )
#pragma comment( lib, "wsock32" )


#include "RadarDirAlgorithm.h"


HWND sthWnd;
bool stbMuteEnable=false;

bool stbLocal=false;
//EN_RADARCOLLECTORID stiCollectorId=RADARCOL_Unknown;

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
// 		vsprintf_s( szLog, fmt, args );
// 		va_end( args );
// 
// 		if( stbLocal == true ) {
// 			strPath.Format( "%s\\%s", GetFilePath(), LOG_DIRECTORY );
// 		}
// 		else {
// 			strPath.Format( "%s\\%s\\수집소_%d", GLOBAL_LOG_DIRECTORY, LOG_SUB_DIRECTORY, stiCollectorId );
// 		}
// 
// 		if( TRUE == _CreateDir( (LPSTR) (LPCSTR) strPath ) ) {
// 			strTemp.Format( "\\%s" , tm.Format("%Y_%m_%d.log" ) );
// 			strPath = strPath + "//" + strTemp;
// 
// 			fopen_s( & fp, (LPSTR) (LPCSTR) strPath, "a+" );
// 
// 			GetLocalTime( & cur_time );
// 
// 			strLog.Format( "%04d-%02d-%02d %02d:%02d:%02d:%03ld" , cur_time.wYear, cur_time.wMonth, cur_time.wDay, cur_time.wHour, cur_time.wMinute, cur_time.wSecond, cur_time.wMilliseconds );
// 
// 			if( fp != NULL ) {
// 				switch( nType ) {
// 				case enNormal :
// 					strLog += _T( "[NORMAL]\t" );
// 					break;
// 				case enDebug :
// 					strLog += _T( "[DEBUG ]\t" );
// 					break;
// 				case enEnd :
// 					strLog += _T( "[END   ]\t" );
// 					break;
// 
// 				case enLineFeed :
// 					strLog = "";
// 					break;
// 
// 				case enError :
// 					strLog += _T( "[ERROR ]\t" );
// 					break;
// 
// 				default :
// 					break;
// 				}
// 
// 				strLog += szLog;
// 
// 				fprintf( fp, "%s\n" , (LPCSTR) (LPCSTR) strLog );
// 				fflush( fp );
// 				fclose( fp );
// 			}
// 			else {
// 				CString strErrorMsg;
// 				DWORD dwErrNo=GetLastError();
// 
// 				strErrorMsg.Format( "LOG FILE Open Fail : Code = [%d]" , dwErrNo );
// 			}
// 		}
// 	}
// 	else {
// 		SetLocal( true );
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

BOOL _CreateDir( char *pPath )
{
	BOOL bRet;
	char dirName[256];
	char *p=pPath;
	char *q=dirName;

	dirName[0] = NULL;
	while( *p ) {
		if( ('\\' == *p) || ('/'==*p)) {
			if( ':' != *(p-1) ) {
				if( dirName[0] != NULL && strcmp( dirName, "\\" ) != 0 && strcmp( dirName, GLOBAL_LOG_DIRECTORY2 ) != 0 && strcmp( dirName, GLOBAL_LOG_DIRECTORY ) != 0) {
					CreateDirectory( dirName, NULL );
				}
			}
		}

		*q++ = *p++;
		*q = '\0';
	}
	bRet = CreateDirectory( dirName, NULL );

	if( bRet == 0 ) {
		bRet = ( GetLastError() == ERROR_ALREADY_EXISTS );
	}

	return bRet;
}

BOOL CheckPing()
{
	BOOL bChkInternet;
	int nMaxTime = 3;
	char szSendData[20] = "Check TCP/IP";

	char szReplyBuffer[100];
	//DWORD dwRetVal;
	HANDLE hlcmpFile;

	hlcmpFile = IcmpCreateFile();

	while(TRUE) {
		bChkInternet = IcmpSendEcho(hlcmpFile, inet_addr( DB_SERVER_IP_ADDRESS ), szSendData, strlen(szSendData), NULL, szReplyBuffer, sizeof(szReplyBuffer), 1000 );

		if( bChkInternet )
			break;

		Sleep(1000);

		nMaxTime--;
		if( 0 == nMaxTime ) {
			char szBuffer[100];

			sprintf_s( szBuffer, sizeof(szBuffer), "DB 서버(%s) 컴퓨터가 연결이 안 되었습니다. 관리자에게 문의하세요.", DB_SERVER_IP_ADDRESS );
			AfxMessageBox( szBuffer, MB_OK );
			return FALSE;
		}
	}

	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
int Printf(char *format, ...)
{
	char str[1000];
	int cnt;

	va_list argptr;

	memset(str, 0, sizeof(str));

	va_start(argptr, format);            /* Initialize variable arguments. */
	cnt = vsprintf_s(str, format, argptr);
	va_end(argptr);              /* Reset variable arguments.      */

  OutputDebugString( str );
	if( sthWnd && stbMuteEnable == false ) {
		SendMessage( sthWnd, WM_USER_LOGMSG, (WPARAM) str, NULL );
	}
	else {
		//Log( enNormal, str );
		//
	}
  
	//TRACE( "%s", str );
	// pView->LogPrintf( str );
	return(cnt);

}

void SetWindowHandler( HWND hWnd )
{
	sthWnd = hWnd;
}

void SetMute( bool bEnable )
{
	stbMuteEnable = bEnable;
}

void SetLocal( bool bLocal )
{
	stbLocal = bLocal;
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

// enPosition GetPosition()
// {
// 	enPosition enPos;
// 	CString strIPAddress=GetIpAddress();
// 
// 	if( strIPAddress.Compare( RADARDIR_1_IP_ADDRESS ) == 0 ) {
// 		stiCollectorId = RADARCOL_1;
// 	}
// 	else if( strIPAddress.Compare( RADARDIR_2_IP_ADDRESS ) == 0 ) {
// 		stiCollectorId = RADARCOL_2;
// 	}
// 	else if( strIPAddress.Compare( RADARDIR_3_IP_ADDRESS ) == 0 ) {
// 		stiCollectorId = RADARCOL_3;
// 	}
// 	else {
// 		stiCollectorId = RADARCOL_Unknown;
// 	}
// 
// 	if( strIPAddress.Compare( BUILTIN_IP ) == 0 || 
// 			strIPAddress.Compare( RADARDIR_1_IP_ADDRESS ) == 0 || strIPAddress.Compare( RADARDIR_2_IP_ADDRESS ) == 0 || strIPAddress.Compare( RADARDIR_3_IP_ADDRESS ) == 0 ) {
// 		enPos = enBuiltIn;
// 	}
// 	else if( strIPAddress.Compare( MYHOME_IP ) == 0 ) {
// 		enPos = enMyHome;
// 	}
// 	else {
// 		enPos = enOffice;
// 	}
// 
// 	return enPos;
// 
// }


#if _MSC_VER > 1600

bool _TRACE(char *format, ...)
{
#ifdef _DEBUG
    char buffer[1000];
    va_list argptr;

    va_start(argptr, format);
    vsprintf(buffer, format, argptr);
    va_end(argptr);

    OutputDebugString(buffer);

#endif

    return true;

}

bool _TRACE(CString strFormat, ...)
{
#ifdef _DEBUG
    char *format = (char*)(LPCTSTR)strFormat;
    char buffer[1000];

    va_list argptr;
    va_start(argptr, format);
    wvsprintf(buffer, format, argptr);
    va_end(argptr);

    OutputDebugString(buffer);
#endif

    return true;

}

#endif