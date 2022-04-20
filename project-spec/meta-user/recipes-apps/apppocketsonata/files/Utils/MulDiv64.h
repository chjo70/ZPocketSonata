/*
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
 * @brief     TDIV
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
    T toaRet;

    if (sizeof(T) == sizeof(unsigned long long int)) {
        toaRet = MulDiv64(x, 1, y);
    }
    else if (sizeof(T) == sizeof(unsigned int)) {
        toaRet = (T) ( (float)x / (float)y );
    }
    else {
        TRACE("잘못된 연산 입니다....");
    }

    return toaRet;
}

/**
 * @brief     TDIV
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

    if (sizeof(T) == sizeof(unsigned long long int)) {
        toaRet = MulDiv64(x, y, 1);
    }
    else if (sizeof(T) == sizeof(unsigned int)) {
        toaRet = (T) ( (float)x * (float)y );
    }
    else {
        TRACE("잘못된 연산 입니다....");
    }

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

    if (sizeof(T) == sizeof(unsigned long long int)) {
        toaRet = MulDiv64(x, y, z);
    }
    else if (sizeof(T) == sizeof(unsigned int)) {
        toaRet = (T) ( ( (float) x * (float) y ) / (float) z );
    }
    else {
        TRACE("잘못된 연산 입니다....");
    }

    return toaRet;
}



#endif //__FULL_MULDIV64_
