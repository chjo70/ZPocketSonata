/* b_off_t.h - base type off_t definition header */

/*
 * Copyright (c) 2006, 2010, 2014 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify, or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
*/

/*
modification history
--------------------
31jan14,to   off64_t should be defined independently
19feb10,zl   added off64_t
20mar06,mil  Added protection against user stdio.h off_t definition.
16feb06,pes  Created from types/vxTypes.h.
*/

#ifndef __INCb_off_th
#define __INCb_off_th

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_DEFINED_off_t) && !defined(_OFF_T)
# define _DEFINED_off_t
# define _OFF_T

/* POSIX requires off_t to be a signed int type */
# ifdef __RTP__
typedef long long       off_t;
# else  /* __RTP__ */
typedef long            off_t;
# endif /* __RTP__ */

#endif /* _DEFINED_off_t && _OFF_T */

#ifndef __RTP__
/* 64-bit offset in kernel; this matches the user-space off_t */

# ifndef _DEFINED_off64_t
# define _DEFINED_off64_t
typedef long long       off64_t;
# endif /* _DEFINED_off_t64 */

/* off_t64 is for compatibility only; off64_t should be used instead */

# ifndef _DEFINED_off_t64
# define _DEFINED_off_t64
typedef long long       off_t64;
# endif /* _DEFINED_off_t64 */

#endif /* !__RTP__ */

#ifdef __cplusplus
}
#endif

#endif /* __INCb_off_th */

