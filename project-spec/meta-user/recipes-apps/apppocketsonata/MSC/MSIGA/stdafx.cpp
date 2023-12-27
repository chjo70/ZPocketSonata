
// stdafx.cpp : 표준 포함 파일만 들어 있는 소스 파일입니다.
// MSIGA.pch는 미리 컴파일된 헤더가 됩니다.
// stdafx.obj에는 미리 컴파일된 형식 정보가 포함됩니다.

#include "stdafx.h"

#include <process.h>


#if _MSC_VER > 1600

char g_szTraceBuffer[8000];

#ifdef _LOG_ANALTYPE_
CRITICAL_SECTION g_CSTrace;

#endif


#ifdef _LOG_ANALTYPE_
bool _TRACE(const char *format, ...)
{
#ifdef _DEBUG
    EnterCriticalSection( & g_CSTrace );

    va_list argptr;

    va_start(argptr, format);
    vsprintf( g_szTraceBuffer, format, argptr);
    va_end(argptr);

    OutputDebugString( g_szTraceBuffer );

    LeaveCriticalSection( & g_CSTrace );

#endif

    return true;

}
#endif



#endif