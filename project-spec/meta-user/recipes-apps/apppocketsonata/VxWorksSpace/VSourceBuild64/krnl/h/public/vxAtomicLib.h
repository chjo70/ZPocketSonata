/* vxAtomicLib.h - header file for atomic operators */

/*
 * Copyright (c) 2006-2010, 2014-2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
19oct15,pcs Added missing define vxAtomic64Set_inline.
14jan14,vhe removed reference to SIMPENTIUM build
28apr10,pad  Moved extern C statement after include statements.
19jun09,mze  replacing PAD64
20apr09,cww  Fixed size API update
20jan09,jb   Adding x86_64 support
15may09,gls  made memory barriers available in user space
29apr09,cww  Update atomicXxx APIs with fixed sizing
19mar09,gls  added atomicXXX() inline definitions
19feb09,kk   make the AMP atomic APIs public
01sep08,kk   add AMP atomicXXX() APIs
16jun08,zl   added VX_CODE_BARRIER() definition.
16jan08,gls  added _WRS_INLINE_ macros
08jun07,jmg  Modified for user side
07may07,m_h  Add ARM  to list that support vxAtomicArchLib.h
28mar07,mmi  Removed obsolete memory barrier macros
05dec06,scm  add hook for IA32 memory barrier support...
04dec06,slk  add MIPS to list that support vxAtomicArchLib.h
01dec06,rfr  Changed prototypes to use atomicVal_t
27nov06,dbt  Added VxSim support.
16nov06,mmi Add memory barrier Macros
28sep06,kk  created.
*/

/*
 * Note: This file contains definitions that must be maintained in both kernel
 * and user space
 */

#ifndef __INCvxAtomicLibh
#define __INCvxAtomicLibh

#ifndef	_ASMLANGUAGE

#include <base/b_atomic_t.h>
#include <base/b_BOOL.h>

#ifdef _WRS_KERNEL
#include <vxInline.h>
#endif  /* _WRS_KERNEL */

/* 
 * The following could be replaced by #include ARCH_HEADER(vxAtomicArchLib.h),
 * but as of now only architectures that support SMP have vxAtomicArchLib.h
 */ 

#if	CPU_FAMILY == PPC
#include <arch/ppc/vxAtomicArchLib.h>
#elif   CPU_FAMILY == I80X86
#ifndef _WRS_CONFIG_LP64
#include <arch/i86/vxAtomicArchLib.h>
#else
#include <arch/i86/x86_64/vxAtomicArchLib.h>
#endif  /* LP64 */
#elif	CPU_FAMILY == MIPS
#include <arch/mips/vxAtomicArchLib.h>
#elif	CPU_FAMILY == ARM
#include <arch/arm/vxAtomicArchLib.h>
#elif	CPU_FAMILY == SIMSPARCSOLARIS
#include <arch/simsolaris/vxAtomicArchLib.h>
#elif	CPU_FAMILY == SIMLINUX
#include <arch/simlinux/vxAtomicArchLib.h>
#elif	CPU_FAMILY == SIMNT
#include <arch/simnt/vxAtomicArchLib.h>
#endif	/* CPU_FAMILY == SIMNT */


#ifdef __cplusplus
extern "C" {
#endif

/* definitions */

#define VX_CODE_BARRIER()	_WRS_BARRIER("")

/* prototypes */

extern atomicVal_t vxAtomicAdd   (atomic_t * target, atomicVal_t value); 
extern atomicVal_t vxAtomicAnd   (atomic_t * target, atomicVal_t value);
extern atomicVal_t vxAtomicDec   (atomic_t * target);
extern atomicVal_t vxAtomicInc   (atomic_t * target);
extern atomicVal_t vxAtomicNand  (atomic_t * target, atomicVal_t value);
extern atomicVal_t vxAtomicOr    (atomic_t * target, atomicVal_t value);
extern atomicVal_t vxAtomicSub   (atomic_t * target, atomicVal_t value);
extern atomicVal_t vxAtomicXor   (atomic_t * target, atomicVal_t value);
extern atomicVal_t vxAtomicClear (atomic_t * target);
extern atomicVal_t vxAtomicGet   (atomic_t * target);
extern atomicVal_t vxAtomicSet   (atomic_t * target, atomicVal_t value);
extern BOOL 	   vxAtomicCas 	 (atomic_t * target, atomicVal_t oldValue, 
			          atomicVal_t newValue);
#ifndef _WRS_CONFIG_LP64
extern BOOL 	   vxCas 	 (atomic_t * target, atomicVal_t oldValue, 
			          atomicVal_t newValue)
	    _WRS_DEPRECATED("vxCas is deprecated. Please use vxAtomicCas.");
#endif

extern atomic32Val_t vxAtomic32Add   (atomic32_t * target,
				      atomic32Val_t value);
extern atomic32Val_t vxAtomic32And   (atomic32_t * target,
				      atomic32Val_t value);
extern atomic32Val_t vxAtomic32Dec   (atomic32_t * target);
extern atomic32Val_t vxAtomic32Inc   (atomic32_t * target);
extern atomic32Val_t vxAtomic32Nand  (atomic32_t * target,
				      atomic32Val_t value);
extern atomic32Val_t vxAtomic32Or    (atomic32_t * target,
				      atomic32Val_t value);
extern atomic32Val_t vxAtomic32Sub   (atomic32_t * target,
				      atomic32Val_t value);
extern atomic32Val_t vxAtomic32Xor   (atomic32_t * target,
				      atomic32Val_t value);
extern atomic32Val_t vxAtomic32Clear (atomic32_t * target);
extern atomic32Val_t vxAtomic32Get   (atomic32_t * target);
extern atomic32Val_t vxAtomic32Set   (atomic32_t * target,
				      atomic32Val_t value);
extern BOOL	     vxAtomic32Cas   (atomic32_t * target,
				      atomic32Val_t oldValue, 
				      atomic32Val_t newValue);

extern atomic64Val_t vxAtomic64Add   (atomic64_t * target,
				      atomic64Val_t value);
extern atomic64Val_t vxAtomic64And   (atomic64_t * target,
				      atomic64Val_t value);
extern atomic64Val_t vxAtomic64Dec   (atomic64_t * target);
extern atomic64Val_t vxAtomic64Inc   (atomic64_t * target);
extern atomic64Val_t vxAtomic64Nand  (atomic64_t * target,
				      atomic64Val_t value);
extern atomic64Val_t vxAtomic64Or    (atomic64_t * target,
				      atomic64Val_t value);
extern atomic64Val_t vxAtomic64Sub   (atomic64_t * target,
				      atomic64Val_t value);
extern atomic64Val_t vxAtomic64Xor   (atomic64_t * target,
				      atomic64Val_t value);
extern atomic64Val_t vxAtomic64Clear (atomic64_t * target);
extern atomic64Val_t vxAtomic64Get   (atomic64_t * target);
extern atomic64Val_t vxAtomic64Set   (atomic64_t * target,
				      atomic64Val_t value);
extern BOOL	     vxAtomic64Cas   (atomic64_t * target,
				      atomic64Val_t oldValue, 
				      atomic64Val_t newValue);

extern atomic32Val_t atomic32Add (atomic32_t * target, atomic32Val_t value); 
extern atomic32Val_t atomic32And (atomic32_t * target, atomic32Val_t value);
extern atomic32Val_t atomic32Dec (atomic32_t * target);
extern atomic32Val_t atomic32Inc (atomic32_t * target);
extern atomic32Val_t atomic32Nand (atomic32_t * target, atomic32Val_t value);
extern atomic32Val_t atomic32Or (atomic32_t * target, atomic32Val_t value);
extern atomic32Val_t atomic32Sub (atomic32_t * target, atomic32Val_t value);
extern atomic32Val_t atomic32Xor (atomic32_t * target, atomic32Val_t value);
extern atomic32Val_t atomic32Clear (atomic32_t * target);
extern atomic32Val_t atomic32Get (atomic32_t * target);
extern atomic32Val_t atomic32Set (atomic32_t * target, atomic32Val_t value);

extern BOOL atomic32Cas (atomic32_t * target, atomic32Val_t oldValue, 
		   atomic32Val_t newValue);

extern atomic64Val_t atomic64Add (atomic64_t * target, atomic64Val_t value); 
extern atomic64Val_t atomic64And (atomic64_t * target, atomic64Val_t value);
extern atomic64Val_t atomic64Dec (atomic64_t * target);
extern atomic64Val_t atomic64Inc (atomic64_t * target);
extern atomic64Val_t atomic64Nand (atomic64_t * target, atomic64Val_t value);
extern atomic64Val_t atomic64Or (atomic64_t * target, atomic64Val_t value);
extern atomic64Val_t atomic64Sub (atomic64_t * target, atomic64Val_t value);
extern atomic64Val_t atomic64Xor (atomic64_t * target, atomic64Val_t value);
extern atomic64Val_t atomic64Clear (atomic64_t * target);
extern atomic64Val_t atomic64Get (atomic64_t * target);
extern atomic64Val_t atomic64Set (atomic64_t * target, atomic64Val_t value);

extern BOOL atomic64Cas (atomic64_t * target, atomic64Val_t oldValue, 
		   atomic64Val_t newValue);

#define _VX_ATOMIC_INIT(i) {(i)}

#ifdef _WRS_KERNEL

/* inline definitions */

#ifndef _WRS_INLINE_vxAtomicAdd
#define vxAtomicAdd_inline vxAtomicAdd
#define vxAtomic32Add_inline vxAtomic32Add
#define vxAtomic64Add_inline vxAtomic64Add
#endif

#ifndef _WRS_INLINE_vxAtomicAnd
#define vxAtomicAnd_inline vxAtomicAnd
#define vxAtomic32And_inline vxAtomic32And
#define vxAtomic64And_inline vxAtomic64And
#endif

#ifndef _WRS_INLINE_vxAtomicDec
#define vxAtomicDec_inline vxAtomicDec
#define vxAtomic32Dec_inline vxAtomic32Dec
#define vxAtomic64Dec_inline vxAtomic64Dec
#endif

#ifndef _WRS_INLINE_vxAtomicInc
#define vxAtomicInc_inline vxAtomicInc
#define vxAtomic32Inc_inline vxAtomic32Inc
#define vxAtomic64Inc_inline vxAtomic64Inc
#endif

#ifndef _WRS_INLINE_vxAtomicNand
#define vxAtomicNand_inline vxAtomicNand
#define vxAtomic32Nand_inline vxAtomic32Nand
#define vxAtomic64Nand_inline vxAtomic64Nand
#endif

#ifndef _WRS_INLINE_vxAtomicOr
#define vxAtomicOr_inline vxAtomicOr
#define vxAtomic32Or_inline vxAtomic32Or
#define vxAtomic64Or_inline vxAtomic64Or
#endif

#ifndef _WRS_INLINE_vxAtomicSub
#define vxAtomicSub_inline vxAtomicSub
#define vxAtomic32Sub_inline vxAtomic32Sub
#define vxAtomic64Sub_inline vxAtomic64Sub
#endif

#ifndef _WRS_INLINE_vxAtomicXor
#define vxAtomicXor_inline vxAtomicXor
#define vxAtomic32Xor_inline vxAtomic32Xor
#define vxAtomic64Xor_inline vxAtomic64Xor
#endif

#ifndef _WRS_INLINE_vxAtomicClear
#define vxAtomicClear_inline vxAtomicClear
#define vxAtomic32Clear_inline vxAtomic32Clear
#define vxAtomic64Clear_inline vxAtomic64Clear
#endif

#ifndef _WRS_INLINE_vxAtomicGet
#define vxAtomicGet_inline vxAtomicGet
#define vxAtomic32Get_inline vxAtomic32Get
#define vxAtomic64Get_inline vxAtomic64Get
#endif

#ifndef _WRS_INLINE_vxAtomicSet
#define vxAtomicSet_inline vxAtomicSet
#define vxAtomic32Set_inline vxAtomic32Set
#define vxAtomic64Set_inline vxAtomic64Set
#endif

#ifndef _WRS_INLINE_vxCas
#define vxAtomicCas_inline vxAtomicCas
#define vxAtomic32Cas_inline vxAtomic32Cas
#define vxAtomic64Cas_inline vxAtomic64Cas

#ifndef _WRS_CONFIG_LP64
#define vxCas_inline vxAtomicCas_inline
#endif
#endif

#ifndef _WRS_INLINE_atomicAdd
#define atomic32Add_inline atomic32Add
#endif

#ifndef _WRS_INLINE_atomicAnd
#define atomic32And_inline atomic32And
#endif

#ifndef _WRS_INLINE_atomicDec
#define atomic32Dec_inline atomic32Dec
#endif

#ifndef _WRS_INLINE_atomicInc
#define atomic32Inc_inline atomic32Inc
#endif

#ifndef _WRS_INLINE_atomicNand
#define atomic32Nand_inline atomic32Nand
#endif

#ifndef _WRS_INLINE_atomicOr
#define atomic32Or_inline atomic32Or
#endif

#ifndef _WRS_INLINE_atomicSub
#define atomic32Sub_inline atomic32Sub
#endif

#ifndef _WRS_INLINE_atomicXor
#define atomic32Xor_inline atomic32Xor
#endif

#ifndef _WRS_INLINE_atomicClear
#define atomic32Clear_inline atomic32Clear
#endif

#ifndef _WRS_INLINE_atomicGet
#define atomic32Get_inline atomic32Get
#endif

#ifndef _WRS_INLINE_atomicSet
#define atomic32Set_inline atomic32Set
#endif

#ifndef _WRS_INLINE_atomicCas
#define atomic32Cas_inline atomic32Cas
#endif
#endif /* _WRS_KERNEL */

#endif /* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCvxAtomicLibh */
