/* ffsArchLib.h - PPC-specific ffs library header */

/*
 * Copyright (c) 2007-2009 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01d,10dec09,cww  64-bit ffsLib update
01c,26jun08,zl   fixed diab version of _inline_ffsLsb()
01b,12jul07,zl   renamed to ffsArchLib.h
01a,19jun07,zl   created, based on ffsALib.s vn 01g.
*/

#ifndef __INCffsArchLibh
#define __INCffsArchLibh

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _ASMLANGUAGE

#if defined (__DCC__)

__asm int _inline_ffs32Msb (UINT32 i)
{
! "r3"						/* r3 clobbered */
% reg i;					/* input: i */
	cntlzw	r3, i				/* r3 = # leading zeros */
	subfic	r3, r3, 32			/* r3 = 32 - r3         */
}

__asm int _inline_ffs32Lsb (UINT32 i)
{
! "r3", "r4"					/* r3, r4 clobbered */
% reg i;					/* input: i */
	mr	r4, i				/* r4 = i */
	neg	r3, r4				/* r3 = -i */
	and	r3, r4, r3			/* r3 = i & (-i) */
	cntlzw	r3, r3				/* r3 = # leading zeros */
	subfic	r3, r3, 32			/* r3 = 32 - r3         */
}

#elif	defined (__GNUC__)

static __inline__ int _inline_ffs32Msb (UINT32 i)
    {
    int j;
    __asm__ 
	(
	"cntlzw  %0, %1;		\n"	/* count leading zeros */
	"subfic  %0, %0, 32		\n"	/* subtract from 32  */
	: "=&r" (j)				/* output: j is %0 (register) */
	: "r" (i)				/* input: i is %1 */
						/* no clobbered registers */
	);
    return (j);
    }

static __inline__ int _inline_ffs32Lsb (UINT32 i)
    {
    int j;
    __asm__ 
	(
	"neg	 %0, %1;		\n"	/* j = -i */
	"and	 %0, %0, %1;		\n"	/* j = i & (-i) */
	"cntlzw	 %0, %0;		\n"	/* j = # leading zeros */
	"subfic  %0, %0, 32		\n"	/* subtract from 32  */
	: "=&r" (j) 				/* output: j is %0 (register) */
	: "r" (i) 				/* input: i is %1 */
						/* no clobbered registers */
	);
    return (j);
    }

#else	/* __GNUC__ */

#define _inline_ffs32Msb(i)	ffs32Msb(i)
#define _inline_ffs32Lsb(i)	ffs32Lsb(i)

#endif /* __GNUC__ */


#endif /* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __INCffsArchLibh */
