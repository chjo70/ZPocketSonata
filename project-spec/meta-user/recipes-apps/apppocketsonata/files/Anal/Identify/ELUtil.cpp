// Util.cpp: implementation of the CUtil class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include <stdlib.h>

#include "ELUtil.h"
//#include "../SigAnal/_Define.h"
#include "../Identify/define.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/**
 * @brief     장치에 따른 장치명을 설정한다.
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-08-24 10:24:09
 * @warning
 */
void SetUnitType()
{
#ifdef _POCKETSONATA_
    g_enUnitType = en_ZPOCKETSONATA;
#elif defined(_ELINT_)
    g_enUnitType = en_ELINT;
#elif defined(_XBAND_)
    g_enUnitType = en_XBAND;
#elif defined(_701_)
	g_enUnitType = en_701;
#else
    g_enUnitType = en_UnknownUnit;

#endif
}

/**
 * @brief     입력 값의 차이가 임계값 이내이면 TRUE, 그렇지 않으면 FALSE를 리턴한다.
 * @param     double x
 * @param     double y
 * @param     float fthresh
 * @return    BOOL
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2017-01-16, 오후 11:24
 * @warning
 */
bool CompAoaDiff( float x, float y, float fthresh )
{
    float fDiff;
    bool bRet;

    fDiff = _diffabs<float>( x, y );

    if( ( fDiff < fthresh ) || ( ( 360. - fDiff ) < fthresh ) ) {
        bRet = true;
    }
    else {
        bRet = false;
    }

    return bRet;

}

/**
 * @brief     방탐 오차를 계산한다.
 * @param     float x
 * @param     float y
 * @return    float
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-08-24 10:24:48
 * @warning
 */
float DOADiff( float x, float y)
{
    float fDiff;

    fDiff = _diffabs<float>( x, y );

    if( fDiff > 180 ) {
        fDiff = (float) ( 360.0 ) - fDiff;
    }

    return fDiff;

}

/**
 * @brief     MultiByteToUTF8
 * @param     wchar_t * p
 * @param     char * pszMultiByte
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-11-22 12:40:15
 * @warning
 */
int MultiByteToUTF8(wchar_t *pszUniCode, int iMaxSizeOfUnicode, char *pszMultiByte)
{
    //size_t nLen = strlen( pszMultiByte );
    //char carr[256];
    int iLen;

    //iLen = MultiByteToWideChar( CP_ACP, 0, pszMultiByte, -1, pszUniCode, iMaxSizeOfUnicode);

    iLen = mbstowcs( pszUniCode, pszMultiByte, strlen(pszMultiByte) );

    //memset( carr, '\0', sizeof(carr) );
    //WideCharToMultiByte(CP_UTF8, 0, p, -1, carr, 256, NULL, NULL);

    return iLen;
}


/**
 * @brief     UTF8을 멀티바이트로 변환한다.
 * @param     char * pszMultiByte
 * @param     int iSizeOfMultiByte
 * @param     const wchar_t * p
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-11-22 12:03:09
 * @warning
 */
void UTF8ToMultibyte( char *pszMultiByte, int iSizeOfMultiByte, const wchar_t *p )
{

    if( p != NULL ) {
        printf( "\n p=%s" , p );
        wcstombs( pszMultiByte, p, iSizeOfMultiByte );
    }
    else {
        *pszMultiByte = NULL;
    }
//     int iLen=WideCharToMultiByte(CP_ACP, 0, p, -1, NULL, 0, NULL, NULL);
//     
//     if (iLen < iSizeOfMultiByte) {
//         WideCharToMultiByte(CP_ACP, 0, p, -1, pszMultiByte, iLen, NULL, NULL);
//     }
//     else {
//         *pszMultiByte = NULL;
//     }
    //*pszMultiByte = NULL;

    return;
}

/*!
 * @brief     로그 출력을 주어진 포멧대로 출력한다.
 * @return    void
 * @param     char * format
 * @param     ...
 * @version   1.0
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희(churlhee.jo@lignex1.com)
 * @date      2014-09-02 오후 3:56
 * @warning
 */
void LogPrint( const char *format, ... )
{

#ifdef _DEBUG
//     if( st_bSimulator == true || true ) {
//         char str[300];
// 
//         va_list argptr;
// 
//         memset( str, 0, sizeof( str ) );
// 
//         va_start( argptr, format );            /* Initialize variable arguments. */
//         vsprintf_s( str, 300, format, argptr );
//         va_end( argptr );              /* Reset variable arguments.      */
// 
//         TRACE0( str );
// 
//     }
#endif

}

/**
 * @brief     
 * @param     const float & value
 * @return    bool
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-04-27, 15:54
 * @warning
 */
// bool Is_FZero( const float &value )
// {
//     return ! ( value > 0 || value < 0 );
// }

/**
 * @brief     Is_DZero
 * @param     const double & dvalue
 * @return    bool
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-04-27, 15:54
 * @warning
 */
// bool Is_DZero( const double &dvalue )
// {
//     return ! ( dvalue > 0 || dvalue < 0 );
// }

/**
 * @brief     Is_FNotZero
 * @param     const float & value
 * @return    bool
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-04-27, 15:54
 * @warning
 */
// bool Is_FNotZero( const float &value )
// {
//     return ( value > 0 || value < 0 );
// }

//
/**
 * @brief
 * @param     const double & dvalue
 * @return    bool
 * @return    성공시 true, 실패시 false
*/
// bool Is_DNotZero( const double &dvalue )
// {
//     return ( dvalue > 0 || dvalue < 0 );
// }
// 
