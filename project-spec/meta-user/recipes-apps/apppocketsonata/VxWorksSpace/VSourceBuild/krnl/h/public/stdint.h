/* stdint.h - ANSI C / POSIX.1 integer type definitions */

/*
 * Copyright (c) 2009, 2010, 2012, 2016 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement. 
 */

/*
modification history
--------------------
11may16,mcm  Added definitions for UINTxx_C(x)
30jul12,cww  explicitly declare int8_t as signed (WIND00365953)
29apr10,pad  Moved extern C statement after include statements.
02oct09,pad  Created.
*/

/*
This include file holds ANSI C / POSIX.1 integer type definitions and
related limit macro definitions per POSIX IEEE 1003.1-2001. No other
definitions are allowed here, in particular for VxWorks-specific types or
macros.

INTERNAL
Definitions for types and macros that ought to be in stdint.h but are
currently not will be moved here over time.
*/

#ifndef __INCstdinth
#define __INCstdinth

/* includes */

#include <vsbConfig.h>	/* compulsory to know whether _WRS_CONFIG_LP64 exists */

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _ASMLANGUAGE

/* Exact-width integer types */

typedef signed char int8_t;
typedef unsigned char uint8_t;
typedef short int16_t;
typedef unsigned short uint16_t;
typedef int int32_t;
typedef unsigned int uint32_t;
typedef long long int64_t;
typedef unsigned long long uint64_t;

/* Integer types capable of holding object pointers */

#ifndef _WRS_CONFIG_LP64
typedef int intptr_t;
typedef unsigned int uintptr_t;
#else
typedef long intptr_t;
typedef unsigned long uintptr_t;
#endif /* _WRS_CONFIG_LP64 */

/* Limits of Specified-Width Integer Types */

#define INT8_MIN	(-0x7F - 1)
#define INT8_MAX	0x7F
#define UINT8_MAX	0xFF

#define INT16_MIN	(-0x7FFF - 1)
#define INT16_MAX	0x7FFF
#define UINT16_MAX	0xFFFF

#define INT32_MIN	(-0x7FFFFFFF - 1)
#define INT32_MAX	0x7FFFFFFF
#define UINT32_MAX	0xFFFFFFFFU

#define INT64_MIN	(-0x7FFFFFFFFFFFFFFFLL - 1)
#define INT64_MAX	0x7FFFFFFFFFFFFFFFLL
#define UINT64_MAX	0xFFFFFFFFFFFFFFFFULL

#ifndef _WRS_CONFIG_LP64
#define INTPTR_MIN	INT32_MIN
#define INTPTR_MAX	INT32_MAX
#define UINTPTR_MAX	UINT32_MAX
#else
#define INTPTR_MIN	INT64_MIN
#define INTPTR_MAX	INT64_MAX
#define UINTPTR_MAX	UINT64_MAX
#endif /* _WRS_CONFIG_LP64 */

/* Limits of Other Integer Types */

#ifndef _WRS_CONFIG_LP64
#define PTRDIFF_MIN	INT32_MIN
#define PTRDIFF_MAX	INT32_MAX
#else
#define PTRDIFF_MIN	INT64_MIN
#define PTRDIFF_MAX	INT64_MAX
#endif /* _WRS_CONFIG_LP64 */

#ifndef _WRS_CONFIG_LP64
#define SIG_ATOMIC_MIN	INT32_MIN
#define SIG_ATOMIC_MAX	INT32_MAX
#else
#define SIG_ATOMIC_MIN	INT64_MIN
#define SIG_ATOMIC_MAX	UINT64_MAX
#endif /* _WRS_CONFIG_LP64 */

#ifndef _WRS_CONFIG_LP64
#define SIZE_MAX	UINT32_MAX
#else
#define SIZE_MAX	UINT64_MAX
#endif /* _WRS_CONFIG_LP64 */

#endif  /* _ASMLANGUAGE */

#ifndef UINT16_C
#define UINT16_C(c)     (c ## U)
#endif

#ifndef UINT32_C
#define UINT32_C(c)     (c ## U)
#endif

#ifndef UINT64_C
#define UINT64_C(c)     (c ## ULL)
#endif

#ifdef __cplusplus
}
#endif

#endif /* __INCstdinth */
