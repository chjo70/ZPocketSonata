/* vxPortableArchP.h - PowerPC portable library configuration */

/*
 * Copyright (c) 2007-2008, 2010, 2014-2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
02jul15,w_x  #undef _WRS_PORTABLE_syscallDispatch for PPC64 (F2518)
06jan15,w_x  #undef _WRS_PORTABLE_(bLib/ffsLib...etc) for PPC64 (F2518)
19dec14,w_x  #undef _WRS_PORTABLE_kernelLockLib for PPC64 (F2518)
20nov14,ylu  LP64 adaptation to support PPC64. (F2518)
20oct10,s_s  renamed _WRS_PORTABLE_vxCpuIndexGet to _WRS_PORTABLE_vxCpuLib
                 (CQ:WIND00199670)
29apr10,pad  Moved extern C statement after include statements.
10oct08,kk   renamed _WRS_PORTABLE_spinlockIsrNdLib to
                 _WRS_PORTABLE_spinLockIsrNdLib
27aug08,jpb  Renamed VSB header file
24jun08,jpb  Added include path for kernel configurations options set in
                 vsb.  Renamed _WRS_VX_SMP to _WRS_CONFIG_SMP.
10jun08,to   enabled optimized intContext for SMP
18mar08,to   enabled optimized taskIdSelf for SMP
13feb08,to   enabled optimized syscallDispatch
16jan08,dlk  Rename spinLockFastLib --> spinlockIsrNdLib.
11dec07,dlk  Add ppc-specific spinLockFastLib.
22sep07,zl   enabled optimized kernel lock library.
11jul07,kk   disabled optimized vxAtomicLib for UP
04may07,zl   created
*/

#ifndef __INCvxPortableArchPh
#define __INCvxPortableArchPh

	
#include <vsbConfig.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * This file is included from <private/vxPortableP.h>. It may undefine
 * portable library definitions in order to enable architecture specific
 * implementation of a library or routine.
 */

/* the following can be overridden with PORTABLE */

#if (!defined(PORTABLE))

#undef _WRS_PORTABLE_syscallDispatch
#undef _WRS_PORTABLE_bLib
#undef _WRS_PORTABLE_ffsLib
#undef _WRS_PORTABLE_ffsTbl
#undef _WRS_PORTABLE_swab
#undef _WRS_PORTABLE_spinLockIsrNdLib
#undef _WRS_PORTABLE_kernelLockLib

#if defined(_WRS_CONFIG_LP64)
#undef _WRS_PORTABLE_ffs64Lib
#endif

#ifdef _WRS_CONFIG_SMP
/*
 * These functions' optimized implementations are only used for SMP,
 * as portable implementations are already optimal for UP.
 */
#undef _WRS_PORTABLE_intContext
#undef _WRS_PORTABLE_taskIdSelf
#endif /* _WRS_CONFIG_SMP */

#endif /* !PORTABLE */

/* the following cannot be overridden with PORTABLE */

#ifdef _WRS_CONFIG_SMP
/*
 * UP can disable the cache, hence the optimized version that uses the
 * lwarx/stwcx. can't be used
 */

#undef _WRS_PORTABLE_vxAtomicLib
#endif /* _WRS_CONFIG_SMP */

#undef _WRS_PORTABLE_vxCpuLib

#ifdef __cplusplus
}
#endif

#endif /* __INCvxPortableArchPh */
