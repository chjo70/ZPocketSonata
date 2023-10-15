
// stdafx.cpp : 표준 포함 파일만 들어 있는 소스 파일입니다.
// MSIGA.pch는 미리 컴파일된 헤더가 됩니다.
// stdafx.obj에는 미리 컴파일된 형식 정보가 포함됩니다.

#include "stdafx.h"




#if _MSC_VER > 1600

#ifdef _LOG_ANALTYPE_
bool _TRACE(char *format, ...)
{
#ifdef _DEBUG
    char buffer[2000];
    va_list argptr;

    va_start(argptr, format);
    vsprintf(buffer, format, argptr);
    va_end(argptr);

    OutputDebugString(buffer);

#endif

    return true;

}
#endif



#endif