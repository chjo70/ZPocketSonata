/* b_atomic_t.h - base type atomic_t definition header */

/*
 * Copyright (c) 2006, 2009-2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement. 
*/

/*
modification history
--------------------
01e,23aug10,pad  Added inclusion of vsbConfig.h
01d,18may09,cww  Revert atomic_t to int under ILP32
01c,20apr09,cww  LP64 update
01c,29apr09,cww  Update atomicXxx APIs with fixed sizing
01b,01dec06,rfr  Added definition of atomicVal_t
01a,22jun06,mmi  Created.
*/

#ifndef __INCb_atomic_th
#define __INCb_atomic_th

#include <vsbConfig.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _DEFINED_atomic_t
#define _DEFINED_atomic_t

#ifdef _WRS_CONFIG_LP64
typedef long            atomic_t;
#else
typedef int             atomic_t;
#endif /* _WRS_CONFIG_LP64 */

typedef atomic_t	atomicVal_t;
typedef int             atomic32_t;
typedef atomic32_t	atomic32Val_t;

#ifdef _WRS_CONFIG_LP64
typedef long	        atomic64_t;
#else
typedef long long      	atomic64_t;
#endif /* _WRS_CONFIG_LP64 */

typedef atomic64_t	atomic64Val_t;

#endif /* _DEFINED_atomic_t */

#ifdef __cplusplus
}
#endif

#endif /* __INCb_atomic_th */
