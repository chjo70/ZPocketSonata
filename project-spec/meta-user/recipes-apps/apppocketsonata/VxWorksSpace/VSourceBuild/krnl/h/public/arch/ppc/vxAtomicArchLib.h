/* vxAtomicArchLib.h - PowerPC specific atomic library header */

/*
 * Copyright (c) 2006-2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
10dec14,w_x  Add PPC64 SMP support (F2518)
20nov14,ylu  LP64 adaptation to support PPC64.(F2518)
27dec10,lzh  remove the warning of vxAtomicGet_inline  when 
                 compiled with gnu.
29apr10,pad  Moved extern C statement after include statements.
15may09,gls  made memory barriers available in user space
28apr09,cww  Add fixed size APIs
27aug08,jpb  Renamed VSB header file
24jun08,jpb  Added include path for kernel configurations options set in
                 vsb.  Renamed _WRS_VX_SMP to _WRS_CONFIG_SMP.
16jun08,zl   use _WRS_BARRIER() for memory barrier implementations
07mar08,to   add vxAtomicGet_inline as macro; fix vxCas for UP
17jan08,gls  renamed inline routines
14dec07,gls  added _inline_vxCas()
22nov06,mmi  switch lwsync to sync
17nov06,mmi  add Created
*/

#ifndef __INCvxAtomicArchLibh
#define __INCvxAtomicArchLibh

#include <arch/ppc/vxAtomicArchLibCommon.h>
#include <arch/ppc/archPpc.h>

#ifndef _ASMLANGUAGE
	
#include <vsbConfig.h>

#ifdef __cplusplus
extern "C" {
#endif

#if defined (__DCC__)

#ifdef _WRS_CONFIG_SMP

#ifdef _WRS_CONFIG_LP64

#define vxCas_inline            vxAtomicCas
#define vxAtomicCas_inline	vxAtomicCas
#define vxAtomic32Cas_inline	vxAtomic32Cas

#else /* !_WRS_CONFIG_LP64 */

#define vxCas_inline vxAtomicCas_inline

__asm volatile BOOL vxAtomicCas_inline (atomic_t * address, atomicVal_t old_value,
				  atomicVal_t new_value)
{
% reg address; reg old_value; reg new_value; \
lab vxCas_inline_again; lab vxCasErr_inline; lab vxCasDone_inline
! "r6"
vxCas_inline_again:
	lwarx	r6, 0, address        /* load and reserve */
	cmpw	r6, old_value         /* operands equal */
	bne-	vxCasErr_inline       /* skip if not */
	stwcx.	new_value, 0, address /* store new value if still reserved */
	bne-	vxCas_inline_again    /* loop if lost reservation */
	li	r3, 1                 /* cmp and swap successful, return 1 */
	b       vxCasDone_inline
vxCasErr_inline:
	li	r3, 0           /*cmp and swap failed, return 0 */
vxCasDone_inline:
}

__asm volatile BOOL vxAtomic32Cas_inline (atomic32_t * address, atomic32Val_t old_value,
				  atomic32Val_t new_value)
{
% reg address; reg old_value; reg new_value; \
lab vxCas_inline_again; lab vxCasErr_inline; lab vxCasDone_inline
! "r6"
vxCas_inline_again:
	lwarx	r6, 0, address        /* load and reserve */
	cmpw	r6, old_value         /* operands equal */
	bne-	vxCasErr_inline       /* skip if not */
	stwcx.	new_value, 0, address /* store new value if still reserved */
	bne-	vxCas_inline_again    /* loop if lost reservation */
	li	r3, 1                 /* cmp and swap successful, return 1 */
	b       vxCasDone_inline
vxCasErr_inline:
	li	r3, 0           /*cmp and swap failed, return 0 */
vxCasDone_inline:
}
#endif /* _WRS_CONFIG_LP64 */

#else /* _WRS_CONFIG_SMP */

#define vxCas_inline            vxAtomicCas
#define vxAtomicCas_inline	vxAtomicCas
#define vxAtomic32Cas_inline	vxAtomic32Cas

#endif /* _WRS_CONFIG_SMP */

#elif defined (__GNUC__)

#define vxCas_inline            vxAtomicCas
#define vxAtomicCas_inline	vxAtomicCas
#define vxAtomic32Cas_inline	vxAtomic32Cas

#else

#define vxCas_inline            vxAtomicCas
#define vxAtomicCas_inline	vxAtomicCas
#define vxAtomic32Cas_inline	vxAtomic32Cas

#endif /* _VX_TOOL_FAMILY */



#ifndef _WRS_CONFIG_LP64

#if defined (__DCC__)
#define vxAtomic32Get_inline(target) \
        ((atomic32Val_t)(*(volatile atomic32_t *)(target)))
#elif defined (__GNUC__)
#define vxAtomic32Get_inline  vxAtomicGet
#else
#define vxAtomic32Get_inline  vxAtomicGet
#endif

#define vxAtomicGet_inline vxAtomic32Get_inline

#else  /* _WRS_CONFIG_LP64 */

#if defined (__DCC__)
#define vxAtomicGet_inline vxAtomicGet
#define vxAtomic32Get_inline(target) \
        ((atomic32Val_t)(*(volatile atomic32_t *)(target)))
#elif defined (__GNUC__)
#define vxAtomicGet_inline vxAtomicGet
#define vxAtomic32Get_inline vxAtomic32Get
#endif /* __GNUC__ */

#endif /* _WRS_CONFIG_LP64 */

#endif /* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCvxAtomicArchLibh */
