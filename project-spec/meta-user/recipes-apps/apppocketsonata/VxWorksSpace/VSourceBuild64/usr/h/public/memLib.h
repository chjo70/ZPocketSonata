/* memLib.h - user heap management library header file */

/* 
 * Copyright (c) 2003-2005, 2010, 2014 Wind River Systems, Inc. 
 *
 * The right to copy, distribute, modify or otherwise make use 
 * of this software may be licensed only pursuant to the terms 
 * of an applicable Wind River license agreement. 
 */ 

/*
modification history
--------------------
26jun14,pcs  CERT: added external declaration for memAllocDisable and cert 
16jun14,pcs  CERT: added external declaration for rtpMemAllocDisable and cert 
             related errnos.
29jul10,pad  Moved extern C statement after include statements.
05jan10,pcs  Updated to add support for LP64.
26sep05,zl   added ED&R error handling flags (SPR#112822).
29aug05,zl   define S_memLib_NOT_ENOUGH_MEMORY as ENOMEM.
05may04,zl   changed memAddToPool(), memOptionsSet()/Get() to return status.
27oct03,zl   added memInfoGet() declaration.
10sep03,zl   created based on kernel version 03u
*/

#ifndef __INCmemLibh
#define __INCmemLibh

#include <vxWorks.h>
#include <memPartLib.h>
#include <vwModNum.h>

#ifdef __cplusplus
extern "C" {
#endif

/* status codes */

/*
 * The traditional VxWorks S_memLib_NOT_ENOUGH_MEMORY and the POSIX ENOMEM
 * describe exactly the same error condition. Therefore they are fully 
 * interchangeable.
 *
 * The NOSTATTBL mark at end will exclude the errno definitions from 
 * being included into status symbol table. This ensures that the standard
 * errno string takes precedence over the proprietary one.
 */

#define S_memLib_NOT_ENOUGH_MEMORY	ENOMEM		/* NOSTATTBL */
#define S_memLib_INVALID_NBYTES		(M_memLib | 2)
#define S_memLib_BLOCK_ERROR		(M_memLib | 3)
#define S_memLib_NO_PARTITION_DESTROY	(M_memLib | 4)
#define S_memLib_PAGE_SIZE_UNAVAILABLE	(M_memLib | 5)
#define S_memLib_WRONG_PART_ID		(M_memLib | 6)
#define S_memLib_INVALID_ADDRESS	(M_memLib | 7)
#define S_memLib_INVALID_ALIGNMENT	(M_memLib | 8)
#define S_memLib_FUNC_NOT_AVAILABLE	(M_memLib | 9)
#define S_memLib_MEM_ALLOC_ERROR_NO_ALLOC_SET       	(M_memLib | 10)
#define S_memLib_RTP_MEM_ALLOC_ERROR_NO_ALLOC_SET	(M_memLib | 11)
#define S_memLib_RTP_MEM_FREE_ERROR_NO_ALLOC_SET    	(M_memLib | 12)

/* partition options */

/* optional check for bad blocks */

#define MEM_BLOCK_CHECK			0x10

/* response to errors when allocating memory */

#define MEM_ALLOC_ERROR_EDR_WARN_FLAG	0x200
#define MEM_ALLOC_ERROR_EDR_FATAL_FLAG	0x400
#define MEM_ALLOC_ERROR_LOG_FLAG	0x20
#define MEM_ALLOC_ERROR_SUSPEND_FLAG	0x40	/* deprecated */

/* response to errors when freeing memory */

#define MEM_BLOCK_ERROR_EDR_WARN_FLAG	0x800
#define MEM_BLOCK_ERROR_EDR_FATAL_FLAG	0x1000
#define MEM_BLOCK_ERROR_LOG_FLAG	0x80
#define MEM_BLOCK_ERROR_SUSPEND_FLAG	0x100	/* deprecated */

/* old style allocation errors - block too big, insufficient space */

#define MEM_ALLOC_ERROR_MASK		0x03	/* deprecated */
#define MEM_ALLOC_ERROR_RETURN		0	/* deprecated */
#define MEM_ALLOC_ERROR_LOG_MSG		0x01	/* deprecated */
#define MEM_ALLOC_ERROR_LOG_AND_SUSPEND	0x02	/* deprecated */

/* old style bad block found */

#define MEM_BLOCK_ERROR_MASK		0x0c	/* deprecated */
#define MEM_BLOCK_ERROR_RETURN		0	/* deprecated */
#define MEM_BLOCK_ERROR_LOG_MSG		0x04	/* deprecated */
#define MEM_BLOCK_ERROR_LOG_AND_SUSPEND	0x08	/* deprecated */

#ifndef _ASMLANGUAGE

/* 
 * XXX - temporary, do not reference it! To be replaced by some thing
 * like memHeapIdGet().
 */

extern PART_ID heapPartId;

/* function declarations */

extern STATUS	memAddToPool (char *pPool, size_t poolSize);
extern void *	memalign (size_t alignment, size_t size);
extern void *   valloc (size_t size);
extern size_t 	memFindMax (void);
extern STATUS	memOptionsGet (unsigned * pOptions);
extern STATUS	memOptionsSet (unsigned options);
extern STATUS	cfree (char *pBlock);
extern STATUS	memInfoGet (MEM_PART_STATS * pPartStats);
#ifdef _WRS_CONFIG_CERT
extern void     memAllocDisable (void);
#endif

#endif /* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCmemLibh */
