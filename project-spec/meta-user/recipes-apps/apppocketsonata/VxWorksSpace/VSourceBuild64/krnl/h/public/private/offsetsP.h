/* offsetsP.h - absolute symbols support */

/* Copyright 2004, Wind River Systems, Inc. Alameda, CA */

/*
modification history
--------------------
01c,15oct04,kk   added a structure offset
01b,17mar04,dat  remove leading underscore from _absSymbols_xxx (95052)
01a,05mar04,dat  written
*/

#ifndef __INCoffsetsPh
#define __INCoffsetsPh

/*
 * standard prefix that the host tools will grep for.
 * Hardcoded into host/src/loader/makeSymTbl.tcl.
 * (Two occurrences below)
 */

#define _WRS_ABS_PREFIX    _vx_offset_

/* Define an absolute symbol, adding the prefix to the name */

#define	_WRS_ABS_VALUE(name,value)	_WRS_ABSOLUTE(_vx_offset_##name, value)

/* Define a structure offset as an absolute symbol */

#define	_WRS_GEN_OFFSET(S,M)	_WRS_ABS_VALUE(S##_##M, offsetof(S,M))

/* Define a structure size as an absolute symbol */

#define	_WRS_GEN_SIZEOF(T)	_WRS_ABS_VALUE(sizeof_##T, sizeof(T))

/*
 * For linkSyms.c in projects, and usrExtra.c for old BSP builds, 
 * we need a fake declaration as a FUNCPTR.  Note in 00vxWorks.cdf
 * we use 'absSymbols_' directly because linkSyms.c does not include
 * this header.  This special symbol is always generated.
 */

#define _WRS_ABS_SYMBOL(x)	absSymbols_##x

/* Define a structure offset as an absolute symbol, renaming the member */

#define	_WRS_GEN_OFFSET_RENAMED(S,M,R)	_WRS_ABS_VALUE(S##_##R, offsetof(S,M))


#endif /* __INCoffsetsP.h */
