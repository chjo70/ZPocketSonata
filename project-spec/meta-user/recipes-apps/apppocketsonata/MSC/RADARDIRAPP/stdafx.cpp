
// stdafx.cpp : 표준 포함 파일만 들어 있는 소스 파일입니다.
// RADARDIRAPP.pch는 미리 컴파일된 헤더가 됩니다.
// stdafx.obj에는 미리 컴파일된 형식 정보가 포함됩니다.

#include "stdafx.h"

#include "../RADARDIR/RadarDirAlgorithm.h"

HWND sthWnd;

//////////////////////////////////////////////////////////////////////////
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
	if( sthWnd ) {
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

#if _MSC_VER > 1600

bool _TRACE( const char *format, ...)
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

// bool _TRACE(CString strFormat, ...)
// {
// #ifdef _DEBUG
//     char *format = (char*)(LPCTSTR)strFormat;
//     char buffer[1000];
// 
//     va_list argptr;
//     va_start(argptr, format);
//     wvsprintf(buffer, format, argptr);
//     va_end(argptr);
// 
//     OutputDebugString(buffer);
// #endif
// 
//     return true;
// 
// }

#endif