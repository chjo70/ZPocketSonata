/* mathP.h - private definitions for math functions */

/*
 * Copyright (c) 1990-1992,1997,2001,2010,2014-2015 Wind River Systems, Inc.  
 *
 * The right to copy, distribute, modify, or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement. 
 *
 */

/*
modification history
--------------------
16mar15,v_r  CERT: code adaptation
11feb14,mcm  Added getInf and getNan functions
31jan14,to   C99 support
16apr10,mcm  Fixed WIND00192604 - the structure DOUBLE had not been
             adapted to LP64. The members l1 and l2 should be 32-bit
             integers not long.
03oct01,to   use IEEE little endian for ARM
23jan97,cdp  reverse words in double for ARM.
22sep92,rrr  added support for c++
04sep92,wmd  modified definition of DOUBLE for BIG/LITTLE ENDIAN architectures.
30jul92,kdl  added fp type test macros; deleted declarations of unused
             routines (isnan(), etc.); changed _d_type() to fpTypeGet();
             deleted prototypes for _dNormalize, _finite, _upscale.
30jul92,kdl  added DOUBLE union definition, from floatLib.c.
08jul92,smb  added to clib library.
04oct91,rrr  passed through the ansification filter
             -fixed #else and #endif
             -changed copyright notice
14sep90,mcl  adapted from Berkeley.
*/

#ifndef __INCmathPh
#define __INCmathPh

#include <math.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _C99

#define isNan(num) 	isnan(num)
#define isInf(num) 	isinf(num)

#else /* !_C99 */

#define ZERO 	0
#define REAL 	1
#define INTEGER 2
#define INF 	3
#define NAN 	4

#define isNan(num) 	((fpTypeGet (num, 0)) == NAN)
#define isZero(num) 	((fpTypeGet (num, 0)) == ZERO)
#define isInf(num) 	((fpTypeGet (num, 0)) == INF)

#if (_BYTE_ORDER == _LITTLE_ENDIAN)
#define P_INDEX	3
#define INF_VAL(d)              \
    {                           \
    d.p_mant[0] = 0x00000000;   \
    d.p_mant[1] = 0x7ff00000;   \
    }

#define INF_VAL_NEG(d)          \
    {                           \
    d.p_mant[0] = 0x00000000;   \
    d.p_mant[1] = 0xfff00000;   \
    }

#define ZERO_VAL_NEG(d)          \
    {                            \
    d.p_mant[0] = 0x00000000;    \
    d.p_mant[1] = 0x80000000;    \
    }
#else	/* little_endian */
#define P_INDEX	0
#define INF_VAL(d)              \
    {                           \
    d.p_mant[0] = 0x7ff00000;   \
    d.p_mant[1] = 0x00000000;   \
    }

#define INF_VAL_NEG(d)          \
    {                           \
    d.p_mant[0] = 0xfff00000;   \
    d.p_mant[1] = 0x00000000;   \
    }

#define ZERO_VAL_NEG(d)          \
    {                            \
    d.p_mant[0] = 0x80000000;    \
    d.p_mant[1] = 0x00000000;    \
    }

#endif	/* little_endian */

typedef union
    {
    unsigned p_mant[2];
    double p_double;
    } __cv_type;

#define p_mantlow p_mant[0]
#define p_manthigh p_mant[1]

#endif /* !_C99 */

typedef union	/* DOUBLE */
    {
    double ddat;
#if (_BYTE_ORDER == _BIG_ENDIAN)
    struct
        {
        int l1;
        int l2;
        } ldat;
#else
    struct
        {
        int l2;
        int l1;
        } ldat;
#endif /* _BYTE_ORDER == _BIG_ENDIAN */
    } DOUBLE;

/* function declarations */

#if !defined(_C99)
extern int fpTypeGet (double v, double *r);
#endif /* !_C99 */

extern double getInf(void);
extern double getNan(void);

#ifdef __cplusplus
}
#endif

#endif /* __INCmathPh */
