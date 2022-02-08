/* qmanLib.h - Freescale QorIQ queue manager primitives */

/*
 * Copyright (c) 2008,2010-2012 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01c,30oct12,wyt  make it compatible with e500v2 core
01d,30aug12,jpb  Renamed _WRS_CONFIG_MILS_VDK_1_1 to _WRS_CONFIG_MILS_VBI.
01c,12oct11,wap  Add MILS support
01b,01apr10,wap  dcbzl can now be inlined
01a,15dec08,wap  written
*/

#ifndef __INCqmanLibh
#define __INCqmanLibh

#ifdef __cplusplus
extern "C" {
#endif
#ifndef _ASMLANGUAGE

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

/*
 * Note that dcbi is a privileged instruction and can only
 * be executed in supervisor or guest supervisor mode.
 * Currently MILS runs guests in user mode, and does not
 * emulate the dcbi instruction. The Freescale code uses a
 * dcbf instead of dcbi, so we do that here. This seems
 * to contradict the DPAA documentation that claims a dcbi
 * is needed though.
 */

#if defined (__DCC__)
__asm volatile void QorIQdcbi_inline (volatile void * addr)
{
%reg addr
#ifdef _WRS_CONFIG_MILS_VBI
    dcbf r0, addr
#else
    dcbi r0, addr
#endif /* _WRS_CONFIG_MILS_VBI */
}
#else /* GNU C */
#ifdef _WRS_CONFIG_MILS_VBI
#define QorIQdcbi_inline(addr)	\
    __asm__ __volatile__ ("dcbf 0, %0" : : "r" (addr));
#else
#define QorIQdcbi_inline(addr)	\
    __asm__ __volatile__ ("dcbi 0, %0" : : "r" (addr));
#endif /* _WRS_CONFIG_MILS_VBI */
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

#endif /* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCqmanLibh */
