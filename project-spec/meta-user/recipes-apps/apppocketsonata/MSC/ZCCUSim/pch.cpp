// pch.cpp: 미리 컴파일된 헤더에 해당하는 소스 파일

#include "pch.h"

// 미리 컴파일된 헤더를 사용하는 경우 컴파일이 성공하려면 이 소스 파일이 필요합니다.
//#define LOGMSG1( A, B, C)           TRACE( B, C )


#ifdef _DEBUG

/**
 * @brief     _TRACE
 * @param     char * format
 * @param     ...
 * @return    bool
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-06-05 16:04:12
 * @warning
 */
bool _TRACE( char *format, ... )
{
    char buffer[1000];
    va_list argptr;

    va_start( argptr, format );
    vsprintf( buffer, format, argptr );
    va_end( argptr );

    OutputDebugString( buffer );

    return true;

}

/**
 * @brief     _TRACE
 * @param     CString strFormat
 * @param     ...
 * @return    bool
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-06-05 16:04:15
 * @warning
 */
bool _TRACE( CString strFormat, ... )
{
    char *format = ( char * ) ( LPCTSTR ) strFormat;
    char buffer[1000];

    va_list argptr;
    va_start( argptr, format );
    wvsprintf( buffer, format, argptr );
    va_end( argptr );

    OutputDebugString( buffer );

    return true;

}

#else

bool _TRACE( char *format, ... )
{
    return true;

}

bool _TRACE( CString strFormat, ... )
{

    return true;

}

#endif