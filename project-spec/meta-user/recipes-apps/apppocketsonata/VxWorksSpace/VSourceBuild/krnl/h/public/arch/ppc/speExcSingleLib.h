/* speExcSingleLib.h - single precision floating point support library header */

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

#ifndef __INCspeExcSingleLibh
#define __INCspeExcSingleLibh

#include "speExcCommon.h"

/*
 * Care must be taken when a variable of FLT_INT type is initialized together
 * with its declaration. The order of fields does matter and it is possible
 * to initialize the variable with number of unsigned int. If it
 * is necessary to initialize it with single precision floating point number,
 * then this must be done in two steps: declaration and assignment separately.
 */

typedef union Flt_Int
    {
    UINT32  i;
    float   f;
    } FLT_INT;

/*
 * The below definitions rely on the order of fields in the FLT_INT union.
 * If order of fields in the FLT_INT union changes, then the initialization
 * of the constants below has to be updated.
 */

LOCAL const FLT_INT qNaN_f   = {0x7FC00000u}; /* quiet NaN          */
LOCAL const FLT_INT pqNaN_f  = {0x7FC00000u}; /* positive quiet NaN */
LOCAL const FLT_INT nqNaN_f  = {0xFFC00000u}; /* negative quiet NaN */
LOCAL const FLT_INT pInf_f   = {0x7F800000u}; /* positive Infinity  */
LOCAL const FLT_INT nInf_f   = {0xFF800000u}; /* negative Infinity  */
LOCAL const FLT_INT pZero_f  = {0x00000000u}; /* positive zero      */
LOCAL const FLT_INT nZero_f  = {0x80000000u}; /* negative zero      */

IMPORT COMP_CODE CompareSafelyS (float a, float b);
IMPORT float AddSafelyS (float a, float b);
IMPORT float MultiplySafelyS (float a, float b);
IMPORT float DivideSafelyS (float a, float b);
IMPORT double EFDCFS_safely (float x);

#endif /* __INCspeExcSingleLibh */

