
// stdafx.cpp : ǥ�� ���� ���ϸ� ��� �ִ� �ҽ� �����Դϴ�.
// RADARDIRAPP.pch�� �̸� �����ϵ� ����� �˴ϴ�.
// stdafx.obj���� �̸� �����ϵ� ���� ������ ���Ե˴ϴ�.

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

