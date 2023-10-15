﻿/*
 *	Header file:		MulDiv64.h
 *	Author:				Richard van der Wal
 *	Contact:			R.vdWal@xs4all.nl
 *
 *	Description:
 *		Header file with prototype for 64 bit scaling functions
 *
 *	$Log: $
 *
 */

/******************************************************************************/
#pragma once
#ifndef __FULL_MULDIV64_
#define __FULL_MULDIV64_


#ifdef __cplusplus

/*
 * MulDiv64
 * Multiplies an operant by a multiplier and divides the result by a divider
 * Used for scaling 64 bit integer values
 *     Xscaled = Xstart * Multiplier / Divider
 * Uses 128 bit intermediate result
 */
__int64 MulDiv64(__int64 operant, __int64 multiplier, __int64 divider);


/*
 * MulShr64
 * Multiplies an operant by a multiplier and right shifts the result rshift times
 * Used for scaling 64 bit integer values
 *     Xscaled = (Xstart * Multiplier) SHR rshift
 * Uses 128 bit intermediate result
 */
//__int64 MulShr64(__int64 operant, __int64 multiplier, unsigned char rshift);

#endif



/**
 * @brief     32비트/64비트 정수형 나누기 연산한다.
 * @param     T x1
 * @param     T y2
 * @return    bool
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-04-14, 18:22
 * @warning
 */
template <typename T>
T TDIV( T x, T y )
{
    T toaRet = 0;

#ifdef _MSC_VER
    if( y > 0 ) {
        toaRet = ( x / y );
    }

#else
    if( is_not_zero<T>( y ) ) {
        toaRet = ( x / y );
    }


#endif

    return toaRet;
}

/**
 * @brief     나누기 템플릿 함수
 * @param     T x1
 * @param     T y2
 * @return    bool
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-04-14, 18:22
 * @warning
 */
template <typename T>
T TMUL(T x, T y)
{
    T toaRet;

#ifdef _MSC_VER
    toaRet = ( x * y );

#else
    toaRet = ( x * y );

#endif

    return toaRet;
}

/**
 * @brief     TMULDIV
 * @param     T x
 * @param     T y
 * @param     T z
 * @return    T
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-04-19, 16:56
 * @warning
 */
template <typename T>
T TMULDIV(T x, T y, T z)
{
    T toaRet;

#ifdef _MSC_VER
    //if( is_not_zero<T>( z ) ) {
    if( z > 0 ) {
        toaRet = ( ( x * y ) / z);
    }
    else {
        toaRet = 0;
    }


// 	if (strcmp(typeid(T).name(), "unsigned __int64") == 0) {
// 		toaRet = MulDiv64(x, y, z);
// 	}
// 	else if (strcmp(typeid(T).name(), "float") == 0) {
// 		toaRet = (T)(((float)x * (float)y) / (float)z);
// 	}
#else

    if( is_not_zero<T>( z ) ) {
        toaRet = ( ( x * y ) / z );
    }
    else {
        toaRet = 0;
    }

//     if (sizeof(T) == sizeof(unsigned __int64)) {
//         toaRet = MulDiv64(x, y, z);
//     }
//     else if (sizeof(T) == sizeof(float)) {
//         toaRet = (T) ( ( (float) x * (float) y ) / (float) z );
//     }
//
//     else {
//         toaRet = 0;
//         TRACE( "잘못된 연산 입니다...." );
//     }
#endif


    return toaRet;
}



#endif //__FULL_MULDIV64_
