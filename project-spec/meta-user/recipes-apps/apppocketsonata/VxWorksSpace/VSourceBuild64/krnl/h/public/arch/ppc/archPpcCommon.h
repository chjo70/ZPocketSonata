/* archPpcCommon.h - common PPC architecture specific header */

/*
* Copyright (c) 2003-2007, 2012 Wind River Systems, Inc.
*
* The right to copy, distribute, modify or otherwise make use
* of this software may be licensed only pursuant to the terms
* of an applicable Wind River license agreement.
*/

/*
modification history
--------------------
01i,23mar12,jpb  Updated for POSIX namespace isolation conformance (part of 
                 defect Defect WIND000307800).
01h,04may07,zl   updated portable library build configuration
01g,20jan06,mil  Updated for POSIX namespace conformance (P2).
01f,01oct04,tam  moved definition of _TYPE_PHYS_ADDR to the kernel
                 architecture scpecific header
01e,22mar04,zl   moved trcLib_PORTABLE and INSTR definitions here.
01d,03feb04,aeg  added _WRS_PAL_COPROC_LIB from archPpc.h
01c,27jan04,gls  added definition of _TYPE_PHYS_ADDR
01b,12nov03,job  Moved some blib stuff from archPpc.h
01a,11nov03,pes  written.
*/

#ifndef __INCarchPpcCommonh
#define __INCarchPpcCommonh

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _ASMLANGUAGE
typedef unsigned int _Vx_INSTR;          /* 32 bit word-aligned instructions */
#endif  /* !_ASMLANGUAGE */

#if !defined(_POSIX_C_SOURCE) && !defined(_XOPEN_SOURCE) && \
    !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE)

/* from bLib.c */

#define _WRS_BLIB_ALIGNMENT     3       /* quad byte alignment mask */

/* from archPpc.h */

/* Enable Coprocessor Abstraction.  For PPC32, must do all or none. */

#define _WRS_PAL_COPROC_LIB

/* moved here from h/types/vxTypesOld.h */

#ifndef _ASMLANGUAGE
typedef _Vx_INSTR	INSTR;
#endif 	/* !_ASMLANGUAGE */

#endif  /* !_POSIX_xxx_SOURCE */


#ifdef __cplusplus
}
#endif

#endif /* __INCarchPpcCommonh */

