/* ffsLib.h - header for ffsLib bit search functions */

/*
 * Copyright (c) 2006-2007, 2009-2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
19mar10,cww  Changed macro implementation to ffsXsb_autosize
03dec09,cww  Added 64-bit ffs routines
11jul07,zl   added inlined ffsLib macros for MIPS
19jun07,zl   added FFS_MSB() and FFS_LSB().
03feb06,dlk  Written.
*/

/*
 * Note: This file contains definitions that must be maintained in both kernel
 * and user space
 */

#ifndef __INCffsLibh
#define __INCffsLibh

#include <vxWorks.h>

#ifdef _WRS_KERNEL

#include <vxInline.h>

#if (defined (_WRS_INLINE_ffsLsb) || defined (_WRS_INLINE_ffsMsb) || \
     defined (_WRS_INLINE_ffs64Lsb) || defined (_WRS_INLINE_ffs64Msb))
#include ARCH_HEADER(ffsArchLib.h)
#endif /* _WRS_INLINE_ffsXsb */

#endif /* _WRS_KERNEL */

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _ASMLANGUAGE

/* function declarations */

int ffsLsb (UINT32 i);
int ffsMsb (UINT32 i);
int ffs32Lsb (UINT32 i);
int ffs32Msb (UINT32 i);
int ffs64Msb (UINT64 i);
int ffs64Lsb (UINT64 i);

#define ffsLsb_autosize(i) ((sizeof(i) == 8) ? ffs64Lsb(i) : ffs32Lsb(i))
#define ffsMsb_autosize(i) ((sizeof(i) == 8) ? ffs64Msb(i) : ffs32Msb(i))

#ifdef _WRS_INLINE_ffsLsb
#define FFS_LSB(i)		_inline_ffs32Lsb(i)
#else
#define FFS_LSB(i)		ffs32Lsb(i)
#endif /* _WRS_INLINE_ffsLsb */

#ifdef _WRS_INLINE_ffsMsb
#define FFS_MSB(i)		_inline_ffs32Msb(i)
#else
#define FFS_MSB(i)		ffs32Msb(i)
#endif /* _WRS_INLINE_ffsMsb */

#ifdef _WRS_INLINE_ffs64Lsb
#define FFS64_LSB(i)		_inline_ffs64Lsb(i)
#else
#define _inline_ffs64Lsb(i)	ffs64Lsb(i)
#define FFS64_LSB(i)		ffs64Lsb(i)
#endif /* _WRS_INLINE_ffs64Lsb */

#ifdef _WRS_INLINE_ffs64Msb
#define FFS64_MSB(i)		_inline_ffs64Msb(i)
#else
#define _inline_ffs64Msb(i)	ffs64Msb(i)
#define FFS64_MSB(i)		ffs64Msb(i)
#endif /* _WRS_INLINE_ffs64Msb */

#endif /* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCffsLibh */
