/* vxPortableP.h - Portable defines for the system. */

/*
 * Copyright (c) 2007-2010, 2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
24jun15,pmr  removed _WRS_PORTABLE_vxCpuLibInit (V7SP-214)
20oct10,s_s  added _WRS_PORTABLE_vxCpuLib and portable defines for the APIs 
             in vxCpuLib.c (CQ:WIND00199670)
29apr10,pad  Moved extern C statement after include statements.
03dec09,cww  Added 64-bit ffsLib
28aug09,gls  removed minimal semaphore definitions (WIND00179395)
10oct08,kk   renamed _WRS_PORTABLE_spinlockIsrNdLib to
             _WRS_PORTABLE_spinLockIsrNdLib
10jun08,to   added _WRS_PORTABLE_intContext
18mar08,to   added _WRS_PORTABLE_taskIdSelf
11feb08,zl   added _WRS_PORTABLE_qPriBMapNext
16jan08,dlk  Rename spinLockFastLib --> spinlockIsrNdLib.
07jan08,gls  fast semaphores renamed to minimal semaphores
13dec07,gls  added _WRS_PORTABLE_semBFastLib and _WRS_PORTABLE_semMFastLib
10dec07,dlk  Added _WRS_PORTABLE_spinLockFastLib.
22sep07,zl   defined _WRS_PORTABLE_kernelLockLib.
03may07,zl   added full set of configurable libraries
22feb07,jmg  written.
*/

/*
DESCRIPTION
This header contains the portable defines for specific libraries. A
library or routine defined as PORTABLE will use the shared C implementation
of the library or routine.

All libraries that provides portable implementation must define the
portable macro here, and include this file:

  #include <vxWorks.h>
  #include <private/vxPortableP.h>

  #ifdef _WRS_PORTABLE_foo
  ...
  #endif

An architecture that wishes to provide a special implementation of a
routine or library should undefine the specific macro in it's own
<arch/<arch_dir>/private/vxPortableArchP.h>:

  #ifndef PORTABLE
  #undef _WRS_PORTABLE_foo
  #undef _WRS_PORTABLE_foo
  #endif

The source file that provides the architecture specific implementation
also has to include <private/vxPortableP.h>:

  #include <vxWorks.h>
  #include <private/vxPortableP.h>

  #ifndef _WRS_PORTABLE_foo
  ...
  #endif
*/

#ifndef __INCvxPortablePh
#define __INCvxPortablePh

#define _WRS_PORTABLE_bLib
#define _WRS_PORTABLE_dllLib
#define _WRS_PORTABLE_ffsLib
#define _WRS_PORTABLE_ffs64Lib
#define _WRS_PORTABLE_ffsTbl
#define _WRS_PORTABLE_intContext
#define _WRS_PORTABLE_kernelLockLib
#define _WRS_PORTABLE_qPriBMapLib
#define _WRS_PORTABLE_qPriBMapNext
#define _WRS_PORTABLE_qPriHeapLib
#define _WRS_PORTABLE_schedLib
#define _WRS_PORTABLE_semBLib
#define _WRS_PORTABLE_semCLib
#define _WRS_PORTABLE_semLib
#define _WRS_PORTABLE_semMLib
#define _WRS_PORTABLE_semOLib
#define _WRS_PORTABLE_sllLib
#define _WRS_PORTABLE_spinLockIsrNdLib
#define _WRS_PORTABLE_swab
#define _WRS_PORTABLE_syscallDispatch
#define _WRS_PORTABLE_taskIdSelf
#define _WRS_PORTABLE_trcLib
#define _WRS_PORTABLE_vxAtomicLib

/* 
 * If the architecture provides the non portable version implementation 
 * for all the APIs, then _WRS_PORTABLE_vxCpuLib should be used. 
 */

#define _WRS_PORTABLE_vxCpuIdGet
#define _WRS_PORTABLE_vxCpuIdToPhysIndex
#define _WRS_PORTABLE_vxCpuIndexGet
#define _WRS_PORTABLE_vxCpuLib
#define _WRS_PORTABLE_vxCpuPhysIndexGet
#define _WRS_PORTABLE_vxCpuPhysIndexToId
#define _WRS_PORTABLE_workQLib

#include ARCH_HEADER(private/vxPortableArchP.h)

#ifdef __cplusplus
extern "C" {
#endif


#ifdef __cplusplus
}
#endif

#endif /* __INCvxPortablePh */
