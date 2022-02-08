/* vxAtomicLibP.h - private atomic library header file */

/*
 * Copyright (c) 2007-2010, 2016 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
14jun16,ajt  Removed VX_ATOMIC_OP_OPTIMIZED macro (V7COR-3460).
28jun10,pad  Allow inclusion of vsbConfig.h for RTP environment.
28apr10,pad  Moved extern C statement after include statements.
27jul09,cww  Changed vxCas to vxAtomicCas
27aug08,jpb  Renamed VSB config file.
24jun08,jpb  Added include path for kernel configurations options set in
             vsb.  Renamed _WRS_VX_SMP to _WRS_CONFIG_SMP.
07mar08,to   fix _WRS_ATOMIC_GET() for UP
30aug07,kk   added VX_ATOMIC_OP_OPTIMIZED
01aug07,jmg  Created.
*/

/*
DESCRIPTION

This library contains optimized version of the vxAtomicLib. These macros
should be used in the kernel when ever possible rather then making the
direct calls to the vxAtomicLib functions.

An architecture that wishes to provide a special implementation of an
atomic routine should undefine the specific macro in it's own
<arch/<arch_dir>/private/vxAtomicLibP.h> file and then define it:

  #undef  _WRS_ATOMIC_FOO
  #define _WRS_ATOMIC_FOO()

As soon as all architectures have a <arch/<arc_dir>/private/vxAtomicLibP.h>
the line as the bottom of this header file should be uncommented so that
the architecture specific vxAtomicLibP.h will be included.
*/

/*
 * Note: This file contains definitions that must be maintained in both kernel
 * and user space
 */

#ifndef __INCvxAtomicLibPh
#define __INCvxAtomicLibPh

#include <vsbConfig.h>
#include <vxAtomicLib.h>
#include <base/b_atomic_t.h>
#include <base/b_BOOL.h>

#ifdef __cplusplus
extern "C" {
#endif

/* macros for the atomic operators */

#define _WRS_ATOMIC_ADD(target,value) 	vxAtomicAdd (target,value)
#define _WRS_ATOMIC_AND(target,value) 	vxAtomicAnd (target, value)
#define _WRS_ATOMIC_DEC(target) 	vxAtomicSub (target,(atomicVal_t)1)
#define _WRS_ATOMIC_INC(target) 	vxAtomicAdd (target,(atomicVal_t)1)
#define _WRS_ATOMIC_NAND(target,value) 	vxAtomicNand (target, value)
#define _WRS_ATOMIC_OR(target,value) 	vxAtomicOr (target, value)
#define _WRS_ATOMIC_SUB(target,value) 	vxAtomicSub (target, value)
#define _WRS_ATOMIC_XOR(target,value) 	vxAtomicXor (target, value)
#define _WRS_ATOMIC_CLEAR(target) 	vxAtomicClear (target)
#define _WRS_ATOMIC_SET(target, value) 	vxAtomicSet (target, value)
#define _WRS_CAS(target, oldValue, newValue) \
			vxAtomicCas (target, oldValue, newValue)

#ifdef _WRS_KERNEL
#ifndef _WRS_CONFIG_SMP
#define _WRS_ATOMIC_GET(target)	((atomicVal_t)(*(volatile atomic_t *)(target)))
#else  /*_WRS_CONFIG_SMP */
#define _WRS_ATOMIC_GET(target)		vxAtomicGet(target)
#endif /*_WRS_CONFIG_SMP */
#else  /* !_WRS_KERNEL */
#define _WRS_ATOMIC_GET(target)		vxAtomicGet(target)
#endif /* _WRS_KERNEL */

#ifdef __cplusplus
}
#endif

/*
 * As soon as all the architectures have a private/vxAtomicLibP.h This code
 * can be uncommented and used.
 *
 * #include ARCH_HEADER(private/vxAtomicLibP.h)
 */

#endif /* __INCvxAtomicLibPh */

