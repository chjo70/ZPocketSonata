﻿// Util.cpp: implementation of the CUtil class.
//
//////////////////////////////////////////////////////////////////////

#include "../SigAnal/stdafx.h"

#include <stdlib.h>

#include "ELUtil.h"
#include "../SigAnal/_Define.h"

//#include "../../MNGR/ELElintUtilMngr.h"

//#include "../PositionEstimation/Geo2UTM/constants.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

bool st_bSimulator=false;

//////////////////////////////////////////////////////////////////////////
/*! \brief    입력 값의 차이가 임계값 이내이면 TRUE, 그렇지 않으면 FALSE를 리턴한다.
		\author   조철희
		\param    x 인자형태 int
		\param    y 인자형태 int
		\param    thresh 인자형태 int
		\return   BOOL
		\version  0.0.1
		\date     2008-02-19 17:44:27
		\warning
*/


/**
 * @brief     입력 값의 차이가 임계값 이내이면 TRUE, 그렇지 않으면 FALSE를 리턴한다.
 * @param     unsigned long long int x
 * @param     unsigned long long int y
 * @param     int thresh
 * @return    bool
 * @exception 
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2014-11-12, 오후 12:14 
 * @warning   
 */
BOOL CompTOAMeanDiff( unsigned long long int x, unsigned long long int y, int thresh )
{
	BOOL bRet;
    long long int diff;

#ifdef _WIN32
    diff = _abs64( (long long int) ( x - y ) );
#else
    diff = llabs( (long long int) ( x - y ) );
#endif

    if( diff <= (long long int) thresh ) {
		bRet = TRUE;
	}
	else {
		bRet = FALSE;
	}

	return bRet;
}

/**
 * @brief     입력 값의 차이가 임계값 이내이면 TRUE, 그렇지 않으면 FALSE를 리턴한다.
 * @param     float x
 * @param     float y1
 * @param     float y2
 * @param     int thresh
 * @return    BOOL
 * @exception 
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2017-03-07, 오후 6:26 
 * @warning   
 */
BOOL CompMarginDiffFFF( float x, float fy1, float fy2, float thresh )
{
	BOOL bRet;
	/*! \bug  	float 자료형에서 동등성 비교연산을 수행하지 말아야 한다.
			\author 조철희 (churlhee.jo@lignex1.com)
			\date 	2014-02-03 10:22:14
	*/
	if( ( x < fy1-thresh ) || ( x > fy2+thresh ) ) {
		bRet = FALSE;
	}
	else {
		bRet = TRUE;
	}

	return bRet;

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
BOOL CompAoaDiff( float x, float y, float fthresh )
{
	float fDiff;
	BOOL bRet;

    fDiff = _diffabs<float>( x, y );

	if( ( fDiff < fthresh ) || ( ( 360. - fDiff ) < fthresh ) ) {
		bRet = TRUE;
	}
	else {
		bRet = FALSE;
	}

	return bRet;

}

float AoaDiff( float x, float y)
{
	float fDiff;

    fDiff = _diffabs<float>( x, y );

	if( fDiff > 180 ) {
		fDiff = (float) ( 360.0 ) - fDiff;
	}

	return fDiff;

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
	if( st_bSimulator == true || true ) {
		char str[300];

		va_list argptr;

		memset( str, 0, sizeof( str ) );

		va_start( argptr, format );            /* Initialize variable arguments. */
		vsprintf_s( str, 300, format, argptr );
		va_end( argptr );              /* Reset variable arguments.      */

		TRACE0( str );

	}
#endif

}

//
bool Is_FZero( const float &value )
{
	return ! ( value > 0 || value < 0 );
}

//
bool Is_DZero( const double &dvalue )
{
	return ! ( dvalue > 0 || dvalue < 0 );
}

//
bool Is_FNotZero( const float &value )
{
	return ( value > 0 || value < 0 );
}

//
/**
 * @brief     
 * @param     const double & dvalue
 * @return    bool
 * @return    성공시 true, 실패시 false
*/
bool Is_DNotZero( const double &dvalue )
{
	return ( dvalue > 0 || dvalue < 0 );
}



// 
// int CalOverlapSpace( int hgh1, int low1, int hgh2, int low2 )
// {
// 	int iRet;
// 
// 	if( hgh1 == low2 || hgh2 == low1 ) {			// debug, 99-12-22 09:36:19
// 		iRet = _spOne;
// 	}
// 
//   else if( low1 >= low2 &&	hgh1 <= hgh2 ) { 			//          |--------|
//     iRet = hgh1 - low1 + 1;											//    |------------------|
// 	}
// 
// 	else if( low1 <= low2 && hgh1 >= hgh2 ) {				//    |------------------|
// 		iRet = hgh2 - low2 + 1;			 								//          |--------|
// 	}
// 
//   else if( low1 <= hgh2 && low2 <= low1 ) {				//          |------------|
// 		iRet = ( hgh2 - low1 + 1);     						//    |-----------|
// 	}
// 
// 	/*! \debug  항상 true 이기 때문에 제거함
// 			\author 조철희 (churlhee.jo@lignex1.com)
// 			\date 	2015-12-24 12:41:27
// 	*/
//   else if( hgh1 >= low2 && hgh1 <= hgh2 ) {				//    |-----------|
// 		iRet = ( hgh1 - low2 + 1 );									//          |------------|
// 	}
// 	else {
// 		iRet = 0;
// 	}
// 
// 	return iRet;
// }