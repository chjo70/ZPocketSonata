/* vxInline.h - Inline macro configuration file. */

/*
 * Copyright (c) 2007, 2009-2010, 2013 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify, or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement. 
 */

/*
modification history
--------------------
19dec13,to   include vxWorks.h
01d,29apr10,pad  Moved extern C statement after include statements.
01c,03dec09,cww  added inlined ffs64
01b,17sep09,s_s  added _WRS_INLINE_intCpuMicroLock/Unlock
01a,19jun07,zl   written.
*/

/*
DESCRIPTION
This header contains the defines for inline macro configuration. 
All header files that provide inlined assembly macro implementations
must include this file and use the respective _WRS_INLINE_foo 
configuration macro for conditionally defining the macro to the inlined
or non-inlined implementation.

  #include <vxWorks.h>
  #include <vxInline.h>
  #include <arch/<arch>/fooArch.h>

  #ifdef _WRS_INLINE_foo
  ...
  #else
  ...
  #endif
  

An architecture that provides an inlined implementation of a 
macro should define the respective _WRS_INLINE_xxx in it's own 
<arch/<arch_dir>/vxInlineArch.h>:

  #define _WRS_INLINE_foo
*/

#ifndef __INCvxInlineh
#define __INCvxInlineh

#include <vxWorks.h>    /* for ARCH_HEADER */

/* 
 * this is a canonical list of inline assembly macros available across 
 * architectures. When an architecture provides an implementation, it 
 * defines the corresponding _WRS_INLINE_xxx in vxInlineArch.h.
 */

#undef _WRS_INLINE_ffsLsb
#undef _WRS_INLINE_ffsMsb
#undef _WRS_INLINE_ffs64Lsb
#undef _WRS_INLINE_ffs64Msb
#undef _WRS_INLINE_intCpuLock
#undef _WRS_INLINE_intCpuUnlock
#undef _WRS_INLINE_intCpuMicroLock
#undef _WRS_INLINE_intCpuMicroUnlock

#include ARCH_HEADER(vxInlineArch.h)

#ifdef __cplusplus
extern "C" {
#endif


#ifdef __cplusplus
}
#endif

#endif /* __INCvxInlineh */
