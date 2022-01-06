/* bootLoadLib.h - object module boot loader library header */

/* Copyright 1992,2009-2010 Wind River Systems, Inc. */

/*
modification history
--------------------
01g,29apr10,pad  Moved extern C statement after include statements.
01f,02mar10,pgh  Return ELF file class from loader
01e,14dec09,pgh  64-bit conversion
01d,22sep92,rrr  added support for c++
01c,04jul92,jcf  cleaned up.
01b,23jun92,ajm  fixed function prototype for bootLoadModule
01a,01jun92,ajm  written
*/

#ifndef __INCbootLoadLibh
#define __INCbootLoadLibh

#include "vwModNum.h"
#include "symLib.h"

#ifdef __cplusplus
extern "C" {
#endif

/* status codes */

#define S_bootLoadLib_ROUTINE_NOT_INSTALLED		(M_bootLoadLib | 1)

/* data structures */

extern STATUS (*bootLoadRoutine)(int, void **, int *);

/* function declarations */

#if defined(__STDC__) || defined(__cplusplus)

extern STATUS 	bootLoadModule (int fd, void **pEntry, int *elfClass);

#else	/* __STDC__ */

extern STATUS 	bootLoadModule ();

#endif	/* __STDC__ */

#ifdef __cplusplus
}
#endif

#endif /* __INCbootLoadLibh */
