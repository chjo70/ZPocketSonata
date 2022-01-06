/* cacheLib.h - cache library header file */

/* Copyright 2005, 2010 Wind River Systems, Inc. */

/*
modification history
--------------------
01b,29jul10,pad  Moved extern C statement after include statements.
01a,20jan05,zl   written.
*/

#ifndef __INCcacheLibh
#define __INCcacheLibh

#include "vxWorks.h"

#ifdef __cplusplus
extern "C" {
#endif

/* type definitions */

typedef int CACHE_TYPE;

/* explicit names of the cache types */

#define	INSTRUCTION_CACHE 	0	/* Instruction Cache(s) */
#define	DATA_CACHE		1	/* Data Cache(s) */

#ifndef	_ASMLANGUAGE

/* function declarations */

extern STATUS	cacheFlush (CACHE_TYPE cache, void * adrs, size_t bytes);
extern STATUS	cacheInvalidate (CACHE_TYPE cache, void *adrs, size_t bytes);
extern STATUS	cacheClear (CACHE_TYPE cache, void * adrs, size_t bytes);
extern STATUS	cacheTextUpdate (void * adrs, size_t bytes);

#endif	/* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCcacheLibh */
