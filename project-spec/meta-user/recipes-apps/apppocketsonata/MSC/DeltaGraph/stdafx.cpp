
// stdafx.cpp : 표준 포함 파일만 들어 있는 소스 파일입니다.
// DeltaGraph.pch는 미리 컴파일된 헤더가 됩니다.
// stdafx.obj에는 미리 컴파일된 형식 정보가 포함됩니다.

#include "stdafx.h"


bool stbLocal=true;

CCriticalSection g_criticalLog;
CCriticalSection g_criticalDbg;
CCriticalSection g_criticalExe;

#define LOG_DIRECTORY					_T("DELTAGRAPH_LOG")

void Log( int nType, const TCHAR *fmt, ... )
{
	g_criticalLog.Lock();

	static TCHAR szLog[5096];
	static CHAR szLogMB[5096];

	FILE *fp=NULL;
	CTime tm=CTime::GetCurrentTime();

	CString strLog, strPath, strTemp;

	va_list args;
	SYSTEMTIME cur_time;

	if( fmt != NULL ) {
		ZeroMemory( szLog, sizeof(szLog) );

		va_start( args, fmt );
		sprintf_s( szLog, fmt, args );
		va_end( args );

		if( stbLocal == true ) {
			strPath.Format( _T("%s\\%s"), GetFilePath(), LOG_DIRECTORY );
		}
		else {
			strPath.Format( _T("%s\\%s"), GLOBAL_LOG_DIRECTORY, LOG_SUBDIRECTORY );
		}

		if( TRUE == CreateDir( strPath.GetBuffer() ) ) {
			//strTemp.Format( "\\%s" , tm.Format("%Y_%m_%d_%H.log" ) );
			strTemp.Format( _T("\\%s") , (char*)(LPCTSTR) tm.Format("%Y_%m_%d.log" ) );
			strPath = strPath + strTemp;

			//_wfopen_s( & fp, (LPSTR) (LPCTSTR) strPath, _T("a+") );
			fopen_s( & fp, strPath.GetBuffer(), _T("a+") );

			GetLocalTime( & cur_time );

			if( nType != enLineFeed ) {
				strLog.Format( _T("%04d-%02d-%02d %02d:%02d:%02d:%03ld") , cur_time.wYear, cur_time.wMonth, cur_time.wDay, cur_time.wHour, cur_time.wMinute, cur_time.wSecond, cur_time.wMilliseconds );
			}

			if( fp != NULL ) {
				switch( nType ) {
				case enNormal :
					strLog += _T( "[NORMAL]\t" );
					break;
				case enDebug :
					strLog += _T( "[DEBUG ]\t" );
					break;
				case enEnd :
					strLog += _T( "[END   ]\t" );
					break;

				case enLineFeed :
					strLog = "";
					break;

				case enError :
					strLog += _T( "[ERROR ]\t" );
					break;

				default :
					break;
				}

				strLog += szLog;

				fwrite( "\n", 1, 1, fp );
#ifdef _MBCS
				fwrite( strLog, strlen(strLog), 1, fp );
				TRACE( "\n%s" , strLog );
#else
				WideCharToMultiByte( CP_ACP, 0, strLog, -1, szLogMB, 5096, NULL, NULL );
				fwrite( szLogMB, strlen(szLogMB), 1, fp );

				TRACE( "\n%s" , szLogMB );
#endif

				fflush( fp );
				fclose( fp );


			}
			else {
				CString strErrorMsg;
				DWORD dwErrNo=GetLastError();

				strErrorMsg.Format( _T("LOG FILE Open Fail : Code = [%d]") , dwErrNo );
			}
		}
		else {
			SetLocal( true );
		}
	}

	g_criticalLog.Unlock();

}

void SetLocal( bool bLocal )
{
	stbLocal = bLocal;
}

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

BOOL CreateDir( TCHAR *pPath )
{
	BOOL bRet;
	TCHAR dirName[256];
	TCHAR *p=pPath;
	TCHAR *q=dirName;

	dirName[0] = NULL;
	while( *p ) {
		if( ('\\' == *p) || ('/'==*p)) {
			if( ':' != *(p-1) ) {
				if( dirName[0] != NULL && _tcscmp( dirName, _T("\\") ) != 0 && _tcscmp( dirName, GLOBAL_LOG_DIRECTORY2 ) != 0 && _tcscmp( dirName, GLOBAL_LOG_DIRECTORY ) != 0) {
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

CString GetIpAddress()
{
	WORD wVersionRequested;
	WSADATA wsaData;
	char name[255];
	PHOSTENT hostinfo;
	CString strIpAddress = _T("");
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

enPosition GetPosition()
{
	enPosition enPos;
	CString strIPAddress=GetIpAddress();

	if( strIPAddress.Compare( OFFICE_IP ) == 0 ) {
		enPos = enOffice;
	}
	else if( strIPAddress.Compare( MYHOME_IP ) == 0 || strIPAddress.Compare( MYHOME_IP_2 ) == 0 || strIPAddress.Find( MYHOME_SUBNET ) != -1 ) {
		enPos = enMyHome;
	}
	else if( strIPAddress.Compare( NO_NETWORK_IP ) == 0 ) {
		enPos = enNoNetwork;
	}
	else {
		enPos = enBuiltIn;
	}

	return enPos;

}

int UnicodeToUtf8( char* pUtf8, TCHAR* pUnicode)
{
	int len = ::WideCharToMultiByte(CP_UTF8, 0, (LPCWSTR)pUnicode, -1, NULL, 0, NULL, NULL);

	::WideCharToMultiByte(CP_UTF8, 0, (LPCWSTR)pUnicode, -1, pUtf8, len, NULL, NULL);

	return len;
}

#ifdef _DEBUG

bool _TRACE(char *format, ...)
{
    char buffer[1000];
    va_list argptr;

    va_start(argptr, format);
    vsprintf(buffer, format, argptr);
    va_end(argptr);

    OutputDebugString(buffer);

    return true;

}

bool _TRACE(CString strFormat, ...)
{
    char *format = (char*)(LPCTSTR)strFormat;
    char buffer[1000];

    va_list argptr;
    va_start(argptr, format);
    wvsprintf(buffer, format, argptr);
    va_end(argptr);

    OutputDebugString(buffer);

    return true;

}

#endif