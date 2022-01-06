/* qmanLib.h - Freescale QorIQ queue manager primitives */

/*
 * Copyright (c) 2008, 2010, 2012, 2014, 2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
02may17,wch  added support for ARM (F8333)
12mar14,fao  corrected the modify history
30oct12,wyt  make it compatible with e500v2 core
01apr10,wap  dcbzl can now be inlined
15dec08,wap  written
*/

#ifndef __INCqmanLibh
#define __INCqmanLibh

#ifdef __cplusplus
extern "C" {
#endif
#ifndef _ASMLANGUAGE

#if CPU_FAMILY==PPC
IMPORT void QorIQlwsync (void);
IMPORT void QorIQdcbt (volatile void *);
IMPORT void QorIQdcbi (volatile void *);
IMPORT void QorIQdcbf (volatile void *);
IMPORT void QorIQdcbzl (volatile void *);

/* DCBF */

#if defined (__DCC__)
__asm volatile void QorIQdcbf_inline (volatile void * addr)
{
%reg addr
    dcbf r0, addr
}
#else /* GNU C */
#define QorIQdcbf_inline(addr)	\
    __asm__ __volatile__ ("dcbf 0, %0" : : "r" (addr));
#endif /* DCC */

/* DCBI */

#if defined (__DCC__)
__asm volatile void QorIQdcbi_inline (volatile void * addr)
{
%reg addr
    dcbi r0, addr
}
#else /* GNU C */
#define QorIQdcbi_inline(addr)	\
    __asm__ __volatile__ ("dcbi 0, %0" : : "r" (addr));
#endif /* DCC */

/* DCBT */

#if defined (__DCC__)
__asm volatile void QorIQdcbt_inline (volatile void * addr)
{
%reg addr
    dcbt r0, addr
}
#else /* GNU C */
#define QorIQdcbt_inline(addr)	\
    __asm__ __volatile__ ("dcbt 0, %0" : : "r" (addr));
#endif /* DCC */

/* DCZL */

#if defined (__DCC__)
__asm volatile void QorIQdcbzl_inline (volatile void * addr)
{
%reg addr
    dcbz r0, addr
}
#else /* GNU C */
#define QorIQdcbzl_inline(addr)	\
    __asm__ __volatile__ ("dcbz 0, %0" : : "r" (addr));
#endif /* DCC */

#ifndef _WRS_INLINE_QorIQdcbf
#define QorIQdcbf_inline(x)	QorIQdcbf (x)
#endif

#ifndef _WRS_INLINE_QorIQdcbi
#define QorIQdcbi_inline(x)	QorIQdcbi (x)
#endif

#ifndef _WRS_INLINE_QorIQdcbt
#define QorIQdcbt_inline(x)	QorIQdcbt (x)
#endif

#ifndef _WRS_INLINE_QorIQdcbzl
#define QorIQdcbzl_inline(x)	QorIQdcbzl (x)
#endif

#ifndef _WRS_INLINE_QorIQlwsync
#define QorIQlwsync_inline()	QorIQlwsync ()
#else
#define QorIQlwsync_inline()	_WRS_ASM("lwsync")
#endif

#define QorIQsyncbr_inline()    _WRS_ASM("eieio")

#define QorIQisync_inline()     _WRS_ASM("isync")

#endif /* CPU_FAMILY==PPC */

#if CPU_FAMILY==ARM

#ifdef _WRS_CONFIG_LP64

#define QorIQdcbi_inline(p)  { asm volatile("dc ivac, %0" : : "r"(p) : "memory"); }
#define QorIQdcbf_inline(p)  { asm volatile("dc cvac, %0;" : : "r" (p) : "memory"); }
#define QorIQdcbzl_inline(p) { asm volatile("dc zva, %0" : : "r" (p) : "memory"); }
#define QorIQdcbt_inline(p)  { asm volatile("prfm pldl1keep, [%0, #0]" : : "r" (p)); }
#define QorIQsyncbr_inline() { asm volatile("dsb sy"); }
#define QorIQlwsync_inline() { asm volatile("dsb st"); }
#define QorIQisync_inline()  { asm volatile("isb sy");}

#else /* !_WRS_CONFIG_LP64 */

#define QorIQdcbzl_inline(p) { memset((void *)p, 0, _CACHE_ALIGN_SIZE); }

#ifdef __DCC__
__asm volatile void QorIQdcbi_inline (volatile void * addr)
{
%reg addr
    mcr p15, 0, addr, c7, c6, 1
}

__asm volatile void QorIQdcbf_inline (volatile void * addr)
{
%reg addr
    mcr p15, 0, addr, c7, c10, 1
}

__asm volatile void QorIQdcbt_inline (volatile void * addr)
{
%reg addr
    pld [addr, #64]
}

__asm volatile void QorIQsyncbr_inline (void)
{
    dsb
}

__asm volatile void QorIQlwsync_inline (void)
{
    dsb
}

__asm volatile void QorIQisync_inline (void)
{
    isb sy
}

#else /* for __GNU__ */

#define QorIQdcbi_inline(p)  { asm volatile("mcr p15, 0, %0, c7, c6, 1" : : "r" (p) : "memory"); }
#define QorIQdcbf_inline(p)  { asm volatile("mcr p15, 0, %0, c7, c10, 1" : : "r" (p) : "memory"); }
#define QorIQdcbt_inline(p)  { asm volatile("pld [%0, #64];": : "r" (p)); }
#define QorIQsyncbr_inline() { asm volatile("dsb": : : "memory"); }
#define QorIQlwsync_inline() { asm volatile("dsb": : : "memory"); }
#define QorIQisync_inline()  { asm volatile("isb sy": : : "memory");}

#endif /* __DCC__ */

#endif /* _WRS_CONFIG_LP64 */

#endif /* CPU_FAMILY==ARM */

#endif /* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCqmanLibh */
