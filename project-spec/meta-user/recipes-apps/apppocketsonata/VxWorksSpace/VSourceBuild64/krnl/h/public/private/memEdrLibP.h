/* memEdrLibP.h - private memory ED&R library header file */

/*
 * Copyright (c) 2003-2004, 2007, 2010-2011 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01n,11jan11,jpb  Defect WIND00246791: Fixed size conflict of task ID between
                 kernel & user-side LP64 builds.
01m,17sep10,pcs  Update to use avlUintLib for ILP32 and avlUint64Lib for LP64.
01m,29sep10,zl   fixed ADDR_ADD() for 64-bit.
01l,31aug10,jpb  Added __rta_longjmp.
01k,12jul10,pcs  Updated to add support for LP64.
01j,28apr10,pad  Moved extern C statement after include statements.
01i,27jul07,pcs  Remove references to the deprecated tlsLib and replace it
                 with __thread variable.
01h,02may07,gls  removed direct rtpTlsCurrent usage
01g,14dec04,aeg  added memEdrBlockMark() function prototype (SPR #105335).
01f,13sep04,zl   exception stack support.
01e,12may04,zl   use new name format for global msgQ
01d,27apr04,zl   reworking show support.
01c,12mar04,zl   ED&R error injection integration
01b,02feb04,zl   implemented guard zone support. Fixes from code inspection.
01a,02dec03,zl 	 created
*/

/*
 * Note: This file contains definitions that must be maintained in both kernel
 * and user space
 */

#ifndef __INCmemEdrLibPh
#define __INCmemEdrLibPh

#include <vxWorks.h>
#include <vsbConfig.h>
#ifdef _WRS_CONFIG_LP64
#include <avlUint64Lib.h>
#else
#include <avlUintLib.h>
#endif
#include <dllLib.h>
#include <poolLib.h>
#include <semLib.h>
#include <private/taskLibP.h>
#include <private/memPartLibP.h>
#ifdef _WRS_KERNEL
#include <private/edrLibP.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* definitions */

#define MD_ANY			0	/* any type */
#define MD_VAR			1	/* global variable */
#define MD_ALLOC		2	/* allocated block */
#define MD_FREE			3	/* free queued */
#define MD_STACK		4	/* stack (local) variable */
#define MD_REALLOC		5	/* interim realloc status */
#define MD_MASK			0x07

#define MF_MARKED		0x10	/* marked by user */
#define MF_REFERENCED		0x20	/* reference found (not leaked) */
#define MF_REPORTED		0x40	/* memory leak was reported */

#define FREE_PATTERN		0xdd
#define MEM_TRACE_LEN		(sizeof (MEM_EDR_BLK) / sizeof (void *))
					/* trc. buff size same as MEM_EDR_BLK */

/* partition info status field */

#define PART_INST_ENABLED	0x0001	/* instrumentation enabled */
#define PART_INST_FAILED	0x0002	/* hook install failed */
#define PART_DELETED		0x0003	/* deleted */

/* 
 * severity levels; these are similar to edrLib, but we use different
 * definitions for portability.
 */

#define	MEM_EDR_FATAL		0x01
#define	MEM_EDR_ERROR		0x02
#define	MEM_EDR_WARNING		0x03
#define	MEM_EDR_INFO		0x04

#ifndef	_ASMLANGUAGE

/* block mode set/get macros */

#define MODE_GET(m)		((m)->blkFlags & MD_MASK)
#define MODE_SET(m,v)		((m)->blkFlags = ((m)->blkFlags & ~MD_MASK) | \
						 ((v) & MD_MASK))

/* macros for mutex */

#define MEM_EDR_MUTEX_OPT	SEM_Q_PRIORITY | 	\
				SEM_DELETE_SAFE |	\
				SEM_INVERSION_SAFE

#define MEM_EDR_LOCK()		semTake(&memEdrDb.sem, WAIT_FOREVER)
#define MEM_EDR_UNLOCK()	semGive(&memEdrDb.sem)
#define MEM_EDR_LOCK_INIT()	semMInit(&memEdrDb.sem, MEM_EDR_MUTEX_OPT)

#define ADDR_ADD(x,y) 		((void *)((char *)(x) + (ULONG)(y)))

#ifdef _WRS_KERNEL

#define TINFO_GET()		((EDR_TCB_INFO *) taskIdCurrent->pEdrInfo)
#define LOCALS_GET()		(TINFO_GET() == NULL ? NULL : \
				 TINFO_GET()->memEdrLocals)
#define LOCALS_PGET()		(TINFO_GET() == NULL ? NULL : \
				 &TINFO_GET()->memEdrLocals)
#define STACK_BASE_GET()	(taskIdCurrent == NULL ? NULL : \
				 (taskIdCurrent->excCnt == 0 ? \
				  taskIdCurrent->pStackBase  :\
				  taskIdCurrent->pExcStackBase))
#define STACK_END_GET()		(taskIdCurrent == NULL ? NULL : \
				 (taskIdCurrent->excCnt == 0 ? \
				  taskIdCurrent->pStackEnd  :\
				  taskIdCurrent->pExcStackEnd))

#else /* _WRS_KERNEL */

extern __thread struct mem_edr_task * memEdrTaskThreadVar;

#define TINFO_GET()		((MEM_EDR_TASK *) memEdrTaskThreadVar)
#define TINFO_CAST()		((MEM_EDR_TASK *) memEdrTaskThreadVar)
#define LOCALS_GET()		(TINFO_GET() == NULL ? NULL : TINFO_CAST()->locals)
#define LOCALS_PGET()		(TINFO_GET() == NULL ? NULL : &TINFO_CAST()->locals)
#define STACK_BASE_GET()	(TINFO_GET() == NULL ? NULL : TINFO_CAST()->pStackBase)
#define STACK_END_GET()		(TINFO_GET() == NULL ? NULL : TINFO_CAST()->pStackEnd)

#endif /* _WRS_KERNEL */

#define IS_PTR_IN_CURRENT_STACK(p)				\
    (((p) >= STACK_END_GET()) && ((p) < STACK_BASE_GET()))

#define EXTD_BUF_GET(m)				\
    ((MEM_EDR_EXTD *) ((char *) (m) + sizeof (MEM_EDR_BLK)))

#define MEDR_PART_INFO_CMD	1
#define MEDR_BLOCK_INFO_CMD	2
#define MEDR_BLOCK_MARK_CMD	3

#define MEM_EDR_SHOW_PRINT_CNT	20

#define MEDR_CMD_Q_FMT		"/qMedrCmd%x"
#define MEDR_INF_Q_FMT		"/qMedrInf%x"


#ifdef _WRS_CONFIG_LP64
#define MEMEDR_AVL_TREE	           AVLUINT64_TREE
#define MEMEDR_AVL_NODE	           AVLUINT64_NODE
#define MEMEDR_AVL_INSERT	   avlUint64Insert
#define MEMEDR_AVL_DELETE	   avlUint64Delete
#define MEMEDR_AVL_SEARCH	   avlUint64Search
#define MEMEDR_AVL_TREE_WALK	   avlUint64TreeWalk
#define MEMEDR_AVL_MINIMUM_GET	   avlUint64MinimumGet
#define MEMEDR_AVL_PREDECESSOR_GET avlUint64PredecessorGet
#else
#define MEMEDR_AVL_TREE	           AVLU_TREE
#define MEMEDR_AVL_NODE	           AVLU_NODE
#define MEMEDR_AVL_INSERT	   avlUintInsert
#define MEMEDR_AVL_DELETE	   avlUintDelete
#define MEMEDR_AVL_SEARCH	   avlUintSearch
#define MEMEDR_AVL_TREE_WALK	   avlUintTreeWalk
#define MEMEDR_AVL_MINIMUM_GET	   avlUintMinimumGet
#define MEMEDR_AVL_PREDECESSOR_GET avlUintPredecessorGet
#endif

/* typedefs */

/* structure defining the member blocks of the database tree */

typedef struct mem_edr_blk
    {
    MEMEDR_AVL_NODE	adrNode;        /* AVL node (32 bytes) */
    UINT		blkFlags;	/* flags (4/4 bytes) */
    size_t		blkSize;	/* size of block (4/8 bytes) */
    union
        {
	struct
	    {
	    PART_ID	partId;		/* memory partition (4/8 bytes)*/
	    TASK_ID	taskId;		/* task id (4/8 bytes) */
	    }		gbl;
	struct
	    {
	    struct mem_edr_blk * next;	/* next in list (4/8 bytes) */
	    int		level;		/* call stack level (4/4 bytes)*/
	    }		loc;
	}		inf;
    } MEM_EDR_BLK;			/* obtained from pool; */
					/* must be exactly 32/64 bytes */

/* trace information */

typedef struct mem_edr_extd
    {
    void *		trace[MEM_TRACE_LEN];	/* trace buffer */
    } MEM_EDR_EXTD;				/* obtained from pool, */
						/* must be <= 32/64 bytes */

/* task info */

typedef struct mem_edr_task
    {	
    MEMEDR_AVL_TREE	locals;			/* AVL tree for locals */
    UINT		ctrl;			/* enable features per task */
#ifndef _WRS_KERNEL
    char *		pStackBase;		/* stack base (user lib only) */
    char *		pStackEnd;		/* stack end (user lib only) */
#endif
    } MEM_EDR_TASK;				/* obtained from pool, */
						/* must be <= 32/64 bytes */

/* partition info */

typedef struct mem_edr_part
    {
    DL_NODE		node;			/* DLL node */
    PART_ID		partId;			/* partition ID */
    FUNC_ALLOC		allocFunc;		/* allocation function */
    FUNC_FREE		freeFunc;		/* free function */
    FUNC_REALLOC	reallocFunc;		/* reallocation function */
    size_t		defAlign;		/* default alloc alignment */
    UINT32		status;			/* partition ctrl and status */
    } MEM_EDR_PART;				/* obtained from pool, */
						/* must be <= 32/64 bytes */
/* free queue node */

typedef struct mem_edr_free
    {
    DL_NODE		node;			/* list node */
    MEM_EDR_BLK *	pBlk;			/* pointer to block info */
    FUNC_FREE		freeFunc;		/* function for freeing block */
    } MEM_EDR_FREE;				/* obtained from pool, */
						/* must be <= 32/64 bytes */

/* database info */

typedef struct mem_edr_db
    {
    POOL_ID		memEdrPoolId;		/* pool ID used for DB */
    BOOL		isKernel;		/* TRUE if kernel database */
    BOOL		memEdrInitialized;	/* library init complete */
    BOOL		extendedEnabled;	/* trace collection enabled */
    BOOL		freePatternEnabled;	/* pattern-fill freed blocks */
    BOOL		guardEnabled;		/* block guard zone */
    MEMEDR_AVL_TREE	avlRoot;		/* block database root */
    DL_LIST		freeQueue;		/* free block queue */
    size_t		freeQueueMax;		/* maximum for free queue */
    size_t		freeQLen;		/* lenght of free queue */
    DL_LIST		partList;		/* partition list */
    SEMAPHORE		sem;			/* mutex semaphore */
						/* IMPORTANT: keep sem last */
						/* in structure: user and */
						/* kernel sizes differ! */
    } MEM_EDR_DB;

/* show support structures */

typedef struct mem_edr_filter
    {
    PART_ID		partId;		/* partition ID selector */
    void *		addr;		/* address */
    long		taskId;		/* task ID selector */
                                        /* IMPORTANT: this must be a long so */
                                        /* user and kernel sizes will be the */
                                        /* same in LP64			     */
    int			level;		/* detail level */
    UINT		type;		/* block type selector */
    int			count;		/* block show counter */
    int			first;		/* first to get */
    int			last;		/* last to get */
    } MEM_EDR_FILTER;

typedef struct mem_edr_part_info
    {
    PART_ID 		partId;		/* partition ID */
    size_t		allocBlocks;	/* allocated blocks */
    size_t		allocBytes;	/* allocated bytes */
    UINT		status;		/* partition status */
    UINT		fqBlocks;	/* blocks in free queue */
    MEM_EDR_PART * 	next;		/* next in partition list */
    } MEM_EDR_PART_INFO;

typedef struct mem_edr_blk_info
    {
    MEM_EDR_BLK		blk;		/* memory block info */
    MEM_EDR_EXTD	xtd;		/* extended memory block info */
    } MEM_EDR_BLK_INFO;

typedef struct mem_edr_show_cmd
    {
    MEM_EDR_PART *	pPart;		/* partition info pointer */
    PART_ID		partId;		/* parittion ID */
    MEM_EDR_FILTER	filt;		/* block filter */
    int			cmd;		/* command */
    } MEM_EDR_SHOW_CMD;

typedef struct mem_edr_part_msg
    {
    MEM_EDR_PART_INFO	partInfo;	/* partition info */
    STATUS		status;		/* info get status */
    } MEM_EDR_PART_MSG;

typedef struct mem_edr_blk_msg
    {
    STATUS		status;		/* info get status */
    int			count;		/* block count */
    MEM_EDR_BLK_INFO	blkInfo[MEM_EDR_SHOW_PRINT_CNT];
    } MEM_EDR_BLK_MSG;

typedef union
    {
    MEM_EDR_PART_MSG	part;		/* partition info message */
    MEM_EDR_BLK_MSG	blk;		/* block info message */
    } MEM_EDR_SHOW_MSG;

/* private globals */

extern MEM_EDR_DB memEdrDb;

/* private functions */

extern void   memEdrConfigInit (BOOL extendedEnable, BOOL freePatternEnable, 
			        size_t freeQueueMax, BOOL guardEnable);
extern void   memEdrConfigClear (void);
extern STATUS memEdrMemInit (void * pPool, size_t poolSize);
extern void   memEdrErrorLog (int severity, char * file, int line, void * ptr,
			      size_t offs, size_t sz, MEM_EDR_BLK * pBlk, 
			      PART_ID partId, char * msg);
extern MEM_EDR_BLK * memEdrBlockFind (MEMEDR_AVL_TREE avlRoot, void * pStart, 
                                      void * pEnd);
extern MEM_EDR_BLK * memEdrLocalFind (void * pStart, void * pEnd);
extern void * memEdrItemGet (POOL_ID poolId);
extern STATUS memEdrPartInfoGet (MEM_EDR_PART * pEdrPart, PART_ID partId,
				 MEM_EDR_PART_INFO * pInfo);
extern STATUS memEdrBlockInfoGet (MEM_EDR_FILTER * pFilt,
				  MEM_EDR_BLK_INFO * pBlocks);
extern STATUS memEdrShowUtilInit ();
extern void   memEdrPartInfoPrint  (MEM_EDR_PART_INFO * pInfo);
extern void   memEdrBlockInfoPrint (MEM_EDR_BLK_INFO * pInfo, int level, 
				    RTP_ID rtpId);
extern void   memEdrPartHdrPrint ();
extern void   memEdrBlockHdrPrint ();
extern BOOL   memEdrUserStopGet (BOOL first);
extern long   memEdrTaskUidGet (TASK_ID taskId);
extern int    memEdrBlockMark (PART_ID partId, TASK_ID taskId, BOOL unmark);
extern STATUS memEdrPartShow (PART_ID partId);
extern STATUS memEdrBlockShow (PART_ID partId, void * addr, TASK_ID taskId,
                               UINT type, UINT level, BOOL continuous);
extern void   memEdrFreeQueueFlush (void);
extern STATUS memEdrRtpPartShow (RTP_ID rtpId, PART_ID partId);
extern STATUS memEdrRtpBlockShow (RTP_ID rtpId, PART_ID partId, void * addr,
                                  TASK_ID taskId, UINT type, UINT level,
                                  BOOL continuous);
extern int    memEdrRtpBlockMark (RTP_ID rtpId, PART_ID partId, TASK_ID taskId,
                                  BOOL unmark);

/* function pointers */

extern void (*__rta_longjmp)(void *);

#endif	/* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCmemEdrLibPh */
