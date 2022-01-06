/* Copyright (c) 2010-2011 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

#ifndef INChpcHwDrvUtils_h
#define INChpcHwDrvUtils_h

#ifdef __cplusplus
extern "C" {
#endif

extern int hpcGetFirstBitSet(unsigned int value);

#if defined(__VXWORKS__)
#include <intLib.h>
#if _VX_CPU_FAMILY == _VX_I80X86
#include <arch/i86/pentiumLib.h>
#endif
#endif

#ifdef __cplusplus
}
#endif
#endif /* INChpcHwDrvUtils_h */
