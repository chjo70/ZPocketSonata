/* poolLib.h - header file for Wind Memory Pools */

/* Copyright 1998, 2003-2004, 2009-2010 Wind River Systems, Inc. */

/*
modification history
--------------------
01i,28apr10,pad  Moved extern C statement after include statements.
01h,31aug09,jpb  Added poolShow prototype.
01g,20apr09,jpb  Completed removal of memPartLib.h.
01f,20apr09,jpb  Added memPartLib.h after reomval.
01e,15apr09,jpb  Updated for LP64 support.
01d,18feb04,dat  moved POOL struct to private header
01c,19aug03,zl   added alignment support, create options to poolLib.
01b,03nov98,mas  added use of "#ifndef _ASMLANGUAGE".
01a,22feb98,dat, original version.  TOR 1.0.1/VXW 5.3 compatible.
	    mas,tm
*/

/*
DESCRIPTION
This file contains the public configuration parameters for the Wind Memory Pool
library.
*/

/*
 * Note: This file contains definitions that must be maintained in both kernel
 * and user space
 */

#ifndef __INCpoolLibh
#define __INCpoolLibh

/* Includes */

#include <vwModNum.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Defines/Macros */

/* status codes */

#define S_poolLib_ARG_NOT_VALID		(M_poolLib | 1) /* invalid input arg */
#define S_poolLib_INVALID_POOL_ID	(M_poolLib | 2) /* invalid pool ID */
#define S_poolLib_NOT_POOL_ITEM		(M_poolLib | 3) /* unrecognized item */
#define S_poolLib_UNUSED_ITEM		(M_poolLib | 4) /* unused item */
#define S_poolLib_POOL_IN_USE		(M_poolLib | 5) /* can't delete pool */
#define S_poolLib_STATIC_POOL_EMPTY	(M_poolLib | 6) /* empty static pool */
#define S_poolLib_INVALID_BLK_ADDR	(M_poolLib | 7) /* invalid block addr */
#define S_poolLib_BLOCK_TOO_SMALL	(M_poolLib | 8) /* block too small */
#define S_poolLib_INT_CTX_POOL_EMPTY	(M_poolLib | 9) /* pool empty in ISR */

/* Pool option bits */

#define	POOL_THREAD_SAFE	1	/* enable multi-task protection */
#define POOL_CHECK_ITEM		2	/* enable item check on return */

#ifndef _ASMLANGUAGE

/* Typedefs */

typedef struct pool *	POOL_ID;

/* Public function prototypes */

void 	poolShow (POOL_ID poolId, int level);
POOL_ID poolCreate (const char * pName, size_t itmSize, size_t alignemnt, 
		    ULONG initCnt, ULONG incrCnt, PART_ID partId, 
		    ULONG options);
STATUS  poolDelete (POOL_ID poolId, BOOL force);
void *  poolItemGet (POOL_ID poolID);
STATUS  poolItemReturn (POOL_ID poolID, void *pItem);
STATUS  poolUnusedBlocksFree (POOL_ID poolId);
ULONG   poolTotalCount (POOL_ID poolId);
ULONG   poolFreeCount (POOL_ID poolId);
STATUS  poolIncrementSet (POOL_ID poolId, ULONG incrCnt);
ULONG   poolIncrementGet (POOL_ID poolId);
ULONG   poolBlockAdd (POOL_ID poolId, void * pBlock, size_t size);
int     poolIdListGet (POOL_ID * poolIdList, int listSize);

#endif /* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif  /* __INCpoolLibh */
