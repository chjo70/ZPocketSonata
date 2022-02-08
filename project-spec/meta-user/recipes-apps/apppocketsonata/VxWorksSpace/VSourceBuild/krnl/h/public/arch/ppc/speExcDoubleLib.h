/* speExcDoubleLib.h - double precision floating point support library header */

/*
 * Copyright (c) 2012 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01b,28jun12,vp  Coding standard corrections.
01a,17may12,vp  Written.
*/

#ifndef __INCspeExcDoubleLibh
#define __INCspeExcDoubleLibh

#include "speExcCommon.h"

/*
 * Care must be taken when a variable of DBL_INT type is initialized together
 * with its declaration. The order of fields does matter and it is possible
 * to initialize the variable with number of unsigned long long type. If it
 * is necessary to initialize it with double precision floating point number,
 * then this must be done in two steps: declaration and assignment separately.
 */

typedef union Dbl_Int
    {
    UINT64   l;
    double   d;
    UINT32   ui[2];
    } DBL_INT;

/*
 * The below definitions rely on the order of fields in the DBL_INT union.
 * If order of fields in the DBL_INT union changes, then the initialization
 * of the constants below has to be updated.
 */

LOCAL const DBL_INT qNaN_d   = {0x7FF8000000000000ull}; /* quiet NaN          */
LOCAL const DBL_INT pqNaN_d  = {0x7FF8000000000000ull}; /* positive quiet NaN */
LOCAL const DBL_INT nqNaN_d  = {0xFFF8000000000000ull}; /* negative quiet NaN */
LOCAL const DBL_INT pInf_d   = {0x7FF0000000000000ull}; /* positive Infinity  */
LOCAL const DBL_INT nInf_d   = {0xFFF0000000000000ull}; /* negative Infinity  */
LOCAL const DBL_INT pZero_d  = {0x0000000000000000ull}; /* positive zero      */
LOCAL const DBL_INT nZero_d  = {0x8000000000000000ull}; /* negative zero      */

IMPORT COMP_CODE CompareSafelyD (double a, double b);
IMPORT double AddSafelyD (double a, double b);
IMPORT double MultiplySafelyD (double a, double b);
IMPORT double DivideSafelyD (double a, double b);
IMPORT float  EFSCFD_safely (double d);

#endif /* __INCspeExcDoubleLibh */

