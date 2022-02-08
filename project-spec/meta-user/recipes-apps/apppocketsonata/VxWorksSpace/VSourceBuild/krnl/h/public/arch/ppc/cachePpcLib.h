/* cachePpcLib.h - PowerPC cache library header file */

/* Copyright 1984-1994, 2010 Wind River Systems, Inc. */

/*
modification history
--------------------
01d,29apr10,pad  Moved extern C statement after include statements.
01c,14oct04,mil  Changed CACHE_FLUSH_LOAD_INIT value.
01b,27sep04,dtr  Add some global defines. SPR 100373
01a,06nov96,tpr  added CACHE_CMD_XXX macros for PPC860.
*/

#ifndef __INCcachePpcLibh
#define __INCcachePpcLibh

#include "vxWorks.h"

#ifdef __cplusplus
extern "C" {
#endif

#define CACHE_CMD_ENABLE	0x02000000	/* Enable the cache */
#define CACHE_CMD_DISABLE	0x04000000	/* Disable the cache */
#define CACHE_CMD_LOAD_LOCK	0x06000000	/* Load and Lock */
#define CACHE_CMD_UNLOCK_LINE	0x08000000	/* Unlock a cache line */
#define CACHE_CMD_UNLOCK_ALL	0x0a000000	/* Unlock all the cache */
#define CACHE_CMD_INVALIDATE	0x0c000000	/* Invalidate all the cache */

#define CACHE_FLUSH_LOAD_ADRS 0x10000	/* default address */
#define CACHE_FLUSH_LOAD_INIT (CACHE_FLUSH_LOAD_ADRS + _CPU_CACHE_ALIGN_SIZE)
                                        /* initial magic value */

#ifdef __cplusplus
}
#endif

#endif /* __INCcachePpcLibh */
