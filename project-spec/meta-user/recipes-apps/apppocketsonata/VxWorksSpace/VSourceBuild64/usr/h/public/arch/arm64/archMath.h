/* archMath.h - ARM64 architecture inline math routines header file */

/*
 * Copyright (c) 2016 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify, or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
02sep16,h_k  created.
*/

#ifndef __INCarchMathh
#define __INCarchMathh

// The preprocessor idiom used below provides an inline definition
// if being used as a header or an out-of-line definition if this is
// the definition file.

#define _LIBC_HAS_INLINE_FABS

#ifdef	_LIBC_HAS_INLINE_FABS
#ifndef	_LIBC_DEFINE_FABS
inline
#endif	/* !_LIBC_DEFINE_FABS */
double fabs (double x)
    {
    double y;

    __asm__ ("fabs	%d0, %d1" : "=w"(y) : "w"(x));

    return y;
    }
#endif	/* _LIBC_HAS_INLINE_FABS */

#define _LIBC_HAS_INLINE_SQRT

#ifdef	_LIBC_HAS_INLINE_SQRT
#ifndef	_LIBC_DEFINE_SQRT
inline
#endif	/* !_LIBC_DEFINE_SQRT */
double sqrt (double x)
    {
    double y;

    __asm__ ("fsqrt	%d0, %d1" : "=w"(y) : "w"(x));

    return y;
    }
#endif	/* _LIBC_HAS_INLINE_SQRT */

#define _LIBC_HAS_INLINE_FABSF

#ifdef	_LIBC_HAS_INLINE_FABSF
#ifndef	_LIBC_DEFINE_FABSF
inline
#endif	/* !_LIBC_DEFINE_FABSF */
float fabsf (float x)
    {
    float y;

    __asm__ ("fabs	%s0, %s1" : "=w"(y) : "w"(x));

    return y;
    }
#endif	/* _LIBC_HAS_INLINE_FABSF */

#define _LIBC_HAS_INLINE_SQRTF

#ifdef	_LIBC_HAS_INLINE_SQRTF
#ifndef	_LIBC_DEFINE_SQRTF
inline
#endif	/* !_LIBC_DEFINE_SQRTF */
float sqrtf (float x)
    {
    float y;

    __asm__ ("fsqrt	%s0, %s1" : "=w"(y) : "w"(x));

    return y;
    }
#endif	/* _LIBC_HAS_INLINE_SQRTF */

#endif	/* __INCarchMathh */
