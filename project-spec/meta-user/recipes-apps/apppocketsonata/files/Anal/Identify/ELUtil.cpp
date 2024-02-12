// Util.cpp: implementation of the CUtil class.
//
//////////////////////////////////////////////////////////////////////

#include "pch.h"

#include <stdlib.h>
#include <string.h>

#include "ELUtil.h"

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

#if defined(_POCKETSONATA_) || defined(_712_)
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
int MultiByteToUTF8(wchar_t *pszUniCode, char *pszMultiByte)
{
    //size_t nLen = strlen( pszMultiByte );
    //char carr[256];
    int iLen;

    //iLen = MultiByteToWideChar( CP_ACP, 0, pszMultiByte, -1, pszUniCode, iMaxSizeOfUnicode);

    iLen = (int) mbstowcs( pszUniCode, pszMultiByte, strlen(pszMultiByte) );

    if( iLen > 0 && iLen < MAX_SQL_SIZE ) {
        pszUniCode[iLen] = 0;
    }
    else {
    }

    //memset( carr, '\0', sizeof(carr) );
    //WideCharToMultiByte(CP_UTF8, 0, p, -1, carr, 256, NULL, NULL);

    return iLen;
}

#ifdef _MSC_VER
int ANSIToUTF8( char *pszUTF8, size_t szLength, char *pszAnsiCode )
{
    BSTR    bstrWide;
    int     nLength;

    *pszUTF8 = NULL;

    nLength = MultiByteToWideChar( CP_ACP, 0, pszAnsiCode, lstrlen( pszAnsiCode ) + 1, NULL, NULL );
    bstrWide = SysAllocStringLen( NULL, ( UINT ) nLength );

    MultiByteToWideChar( CP_ACP, 0, pszAnsiCode, lstrlen( pszAnsiCode ) + 1, bstrWide, nLength );

    nLength = WideCharToMultiByte( CP_UTF8, 0, bstrWide, -1, NULL, 0, NULL, NULL );

    if( (size_t) nLength < szLength  ) {
        WideCharToMultiByte( CP_UTF8, 0, bstrWide, -1, pszUTF8, nLength, NULL, NULL );
        SysFreeString( bstrWide );
    }
    else {

    }

    return nLength;

}

/**
 * @brief     UTF8ToANSI
 * @param     char_t * pszAnsiCode
 * @param     char * pszUTF8
 * @return    int
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-06-21 14:54:50
 * @warning
 */
int UTF8ToANSI( char *pszAnsiCode, char *pszUTF8 )
{
    BSTR    bstrWide;
    int     nLength;

    nLength = MultiByteToWideChar( CP_UTF8, 0, pszUTF8, lstrlen( pszUTF8 ) + 1, NULL, NULL );
    bstrWide = SysAllocStringLen( NULL, (UINT) nLength );

    MultiByteToWideChar( CP_UTF8, 0, pszUTF8, lstrlen( pszUTF8 ) + 1, bstrWide, nLength );

    nLength = WideCharToMultiByte( CP_ACP, 0, bstrWide, -1, NULL, 0, NULL, NULL );

    WideCharToMultiByte( CP_ACP, 0, bstrWide, -1, pszAnsiCode, nLength, NULL, NULL );
    SysFreeString( bstrWide );

    return nLength;

}

#endif

/**
 * @brief     UTF8을 멀티바이트로 변환한다.
 * @param     char * UTF8ToANSI( char *pszAn
 * @param     int iSizeOfMultiByte
 * @param     const wchar_t * p
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-11-22 12:03:09
 * @warning
 */
void UTF8ToMultibyte( char *pszMultiByte, size_t iSizeOfMultiByte, const wchar_t *p )
{

    if( p != NULL ) {
        wcstombs( pszMultiByte, p, iSizeOfMultiByte );
    }
    else {
        *pszMultiByte = 0;
    }

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
 * @brief     두 PRI 값들 사이에 하모닉 관계 여부를 계산한다.
 * @param     T priMean1
 * @param     T priMean2
 * @param     T tThreshold
 * @return    UINT
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-06-14, 16:38
 * @warning
 */
// UINT CheckHarmonicTOA(_TOA priMean1, _TOA priMean2, _TOA tThreshold) {
// 	UINT ret = 0;
//
// 	_TOA r;
// 	_TOA harmonic;
// 	_TOA max_mean, min_mean;
//
// 	if (priMean1 != 0 && priMean2 != 0) {
// 		if (priMean1 > priMean2) {
// 			max_mean = priMean1;
// 			min_mean = priMean2;
// 		}
// 		else {
// 			max_mean = priMean2;
// 			min_mean = priMean1;
// 		}
//
//         harmonic = max_mean % min_mean;
//
// 		// 10배수 이상이면 STABLE 마진 값을 두배로 해서 harmonic 체크한다.
// 		_TOA margin_th = tThreshold; // UDIV( max_mean, STB_MARGIN*1000 );
//
// 		// 하모닉 체크에서 배수만큼 더한 마진으로 체크한다.
// 		if (harmonic <= tThreshold + margin_th || min_mean - harmonic <= tThreshold + margin_th) {
// 			r = TDIV<_TOA>(max_mean, min_mean);
// 			// r = (T) MulDiv64((T)1, (T) max_mean, (T) min_mean);
// 			if (r > UINT_MAX) {
// 				ret = UINT_MAX;
// 			}
// 			else {
// 				ret = (UINT)r;
// 			}
// 		}
// 	}
// 	else {
//
// 	}
//
// 	return ret;
// }

/**
 * @brief     CheckMissingPulse
 * @param     _TOA priMean1
 * @param     STR_MINMAX_TOA * pPRI
 * @param     _TOA tThreshold
 * @return    UINT
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-06-27 20:18:52
 * @warning
 */
// UINT CheckMissingPulse( _TOA priMean1, STR_MINMAX_TOA *pPRI, _TOA tThreshold )
// {
//     return priMean1 / pPRI->priMean;
//
// }


#define  MAX_MISSING_PILSE  (5)
/**
 * @brief     CheckMissingPulse
 * @param     _TOA priMean1
 * @param     _TOA priMean2
 * @param     _TOA tThreshold
 * @return    UINT
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-06-16 13:07:54
 * @warning
 */
UINT ExpectedMissingPulses( int ext_type, _TOA priMean1, STR_MINMAX_TOA *pstPRI, _TOA tThreshold )
{
    UINT ret = 1;

    STR_MINMAX_TOA stPRIRange;

    if( ext_type == _STABLE || ext_type == _REFSTABLE || ext_type == _STABLE_STAGGER ) {
        _TOA r = 0;
        _TOA harmonic;
        _TOA max_mean, min_mean;

        if( priMean1 > pstPRI->tMean ) {
            max_mean = priMean1;
            min_mean = pstPRI->tMean;
        }
        else {
            max_mean = pstPRI->tMean;
            min_mean = priMean1;
        }

        if( max_mean != 0 && min_mean != 0 ) {
            harmonic = max_mean % min_mean;

            // 10배수 이상이면 STABLE 마진 값을 두배로 해서 harmonic 체크한다.
            //_TOA margin_th = tThreshold; // UDIV( max_mean, STB_MARGIN*1000 );

            // 하모닉 체크에서 배수만큼 더한 마진으로 체크한다.
            if( harmonic <= tThreshold ) {
                r = TDIV<_TOA>( max_mean, min_mean ) - 1;
                // r = (T) MulDiv64((T)1, (T) max_mean, (T) min_mean);
            }
            else if( min_mean - harmonic <= tThreshold ) {
                r = max_mean / min_mean;
            }
            else {

            }

            if( r != 0 ) {
                ret = ( UINT ) r;
            }
        }

    }
    else {
        stPRIRange = *pstPRI;

        do {
            ++ ret;
            if( ret >= MAX_MISSING_PILSE ) {
                ret = UINT_MAX + 1;
                break;
            }

            stPRIRange = ( *pstPRI ) * ret;
        } while( TCompMarginDiff<_TOA>( priMean1, stPRIRange.tMin, stPRIRange.tMax, tThreshold ) == false );

        -- ret;

    }

    return ret;
}

/**
 * @brief     ExpectedMissingPulses
 * @param     int ext_type
 * @param     _TOA priMean1
 * @param     STR_LOWHIGH_TOA * pstPRI
 * @param     _TOA tThreshold
 * @return    UINT
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2024-01-10 09:05:10
 * @warning
 */
UINT ExpectedMissingPulses( int ext_type, _TOA priMean1, STR_LOWHIGH_TOA *pstPRI, _TOA tThreshold )
{
    STR_MINMAX_TOA stMinMaxTOA;

    stMinMaxTOA.tMin = pstPRI->tLow;
    stMinMaxTOA.tMax = pstPRI->tHigh;
    stMinMaxTOA.tMean = ( pstPRI->tLow + pstPRI->tHigh ) / 2;
    return ExpectedMissingPulses( ext_type, priMean1, & stMinMaxTOA, tThreshold );
}
