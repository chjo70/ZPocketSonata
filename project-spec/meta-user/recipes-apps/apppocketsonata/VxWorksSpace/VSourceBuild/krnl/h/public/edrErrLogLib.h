/* edrErrLogLib - edrErrLogLib header file */

/* Copyright (c) 2003-2004, 2009-2011 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
01l,21jan11,cww  Updated EDR_ERR_LOG_NODE data field for alignment 
                 (WIND00251544)
01k,18aug10,cww  Additional 64-bit updates
01j,29apr10,pad  Moved extern C statement after include statements.
01i,09jun09,pcs  Updated to add support for LP64 data model.
01h,17sep04,md   add prototypes for node protection functions
01g,26aug04,md   make record size configurable
01f,05aug04,md   added committed state tracking
01e,30mar04,md   bump payload size to 4096 bytes
01d,16feb04,md   general cleanup and documentation
01c,06nov03,aim  reworked iterators
01b,05nov03,aim  reworked for intLock/intUnlock
01a,24oct03,aim  created
*/

#ifndef __INCedrErrLogLib_h
#define __INCedrErrLogLib_h

#include <vxWorks.h>

#ifdef __cplusplus
extern "C" {
#endif

/*

The structure of the error log in memory is as follows:

          +------------------------+ ----+
          |      endianness        |     |
          |      magic             |     |
          |      version           |     |
     +->  |      payloadSize       |     |
     |    |      nodeSize          |     | -- EDR_ERR_LOG_HEADER
     |    |      size              |     |
     |    |      nPages            |     |
     |    |      nHeaderPages      |     |
     |    |     *pageProtect       |     |
     |    |      osVersion         |     |
     |    |      cpuType           |     |
     |    |      reserved [32]     |     |
     |    +------------------------+ ----+
     +--- |      checksum          |
          +------------------------+
          |      modCount          |
          +------------------------+
          |      genCount          |
          +------------------------+
          |      bootCount         |
          +------------------------+
          |      missedErrors      |
          +------------------------+
          |      reserved [32]     |
          +------------------------+
          +------------------------+ ----+
          |      maxNodeCount      |     |
          |      oldestNode        |     |
          |      nextNode          |     |-- EDR_ERR_LOG_NODE_LIST
          |      nodeCount         |     |
          |      reserved [32]     |     |
          +------------------------+     |
          +------------------------+     |
          |      status            | ---------+
          |      position          |     |    |
          |      genCount          |     |    |
          |      logGenCount       |     |    |--  EDR_ERR_LOG_NODE
          |      bootCount         |     |    |
          |      committed         |     |    |
          |      reserved [32]     |     |    |
          |      data []           | ---------+
          +------------------------+     |
          |      status            |     |
          |      position          |     |
          |      genCount          |     |
          |      logGenCount       |     |
          |      bootCount         |     |
          |      committed         |     |
          |      reserved [32]     |     |
          |      data []           |     |
          +------------------------+     |
          |      status            |     |
          |      position          |     |
          |      genCount          |     |
          |      logGenCount       |     |
          |      bootCount         |     |
          |      committed         |     |
          |      reserved [32]     |     |
          |      data []           |     |
          +------------------------+     |
          |      status            |     |
          |      position          |     |
          |      genCount          |     |
          |      logGenCount       |     |
          |      bootCount         |     |
          |      committed         |     |
          |      reserved [32]     |     |
          |      data []           |     |
          +------------------------+     |
          |          .             |     |
          |          .             |     |
          |          .             |     |
          |          .             |     |
          |          .             |     |
          +------------------------+ ----+
*/

/* default payload size for each record */

#define EDR_ERR_LOG_PAYLOAD_SIZE	4096

/* minimum payload size for each record */

#define EDR_ERR_LOG_MIN_PAYLOAD_SIZE	512

/*
 * We use sizeof(EDR_ERR_LOG_NODE) when calculating record addresses, so in
 * LP64 this value must be a multiple of 8 to avoid misaligned members in the
 * error records.  The offset of the data field must be an even 8-byte
 * in LP64 for a similar reason.
 */

typedef struct edr_err_log_node
    {
    int			status;		   /* current status of this node   */
    UINT32		position;	   /* abs position of record in log */
    UINT32		genCount;          /* generation count of node      */
    UINT32		logGenCount;	   /* log gen count we belong to    */
    UINT32		bootCount;         /* boot count indicator	    */
    UINT32		committed;         /* committed/uncommitted state   */
    UINT32		reserved [32];     /* reserved for future use	    */
    long 	        data[1];	   /* payload                       */
    } EDR_ERR_LOG_NODE;

typedef struct edr_err_log_node_list
    {
    int			maxNodeCount;      /* maximum number of nodes       */
    int			oldestNode;        /* index of oldest node	    */
    int			nextNode;          /* index of next free node	    */
    int			nodeCount;         /* number of nodes[] in use	    */
    UINT32		reserved [32];     /* reserved for future use	    */
    EDR_ERR_LOG_NODE    node [1];          /* variable-sized set of nodes   */
    } EDR_ERR_LOG_NODE_LIST;

typedef struct edr_err_log_header
    {
    int			endianness;        /* endianness identifier         */
    int			magic;             /* log identifier 	            */
    int			version;           /* log version number            */
    int			payloadSize;       /* payload size (in bytes)       */
    int			nodeSize;	   /* node size (in bytes)          */
    int			size;              /* log size (in bytes)           */
    UINT32		nPages;		   /* log size (in pages)           */
    UINT32              nHeaderPages;	   /* number of pages for header    */
    UINT32 *            pageProtect;	   /* page protection counts        */
    UINT32		osVersion;         /* version of OS/ED&R            */
    UINT32		cpuType;           /* WindRiver CPU type code       */
    UINT32		reserved [32];     /* reserved for future use       */
    } EDR_ERR_LOG_HEADER;

typedef struct edr_err_log
    {
    EDR_ERR_LOG_HEADER	header;		   /* log header		    */
    INT32		checksum;          /* checksum for the header	    */

    UINT32		modCount;          /* co-modification count	    */
    UINT32		genCount;          /* generation count of error log */
    UINT32		bootCount;         /* boot count indicator	    */
    UINT32              missedErrors;      /* missed error count	    */
    UINT32		reserved [32];     /* reserved for future use	    */
    EDR_ERR_LOG_NODE_LIST nodeList;        /* nodes; must be last member    */
    } EDR_ERR_LOG;

typedef struct edr_err_log_iter
    {
    EDR_ERR_LOG *	pLog;	           /* log instance being iterated   */
    int			nodeCount;         /* number of nodes to iterate    */
    int			nodeIndex;         /* current node		    */
    int			maxNodeCount;      /* maximum node count	    */
    } EDR_ERR_LOG_ITER;


EDR_ERR_LOG *		edrErrLogCreate		(void * pAddr, size_t size,
						 size_t recordSize);
BOOL			edrErrLogIterCreate	(EDR_ERR_LOG * pLog,
					   	 EDR_ERR_LOG_ITER * pIter,
						 int start, int count);
EDR_ERR_LOG_NODE *	edrErrLogIterNext	(EDR_ERR_LOG_ITER * pIter);
EDR_ERR_LOG *		edrErrLogAttach		(void * pAddr);
BOOL			edrErrLogClear		(EDR_ERR_LOG * pLog);
BOOL			edrErrLogNodeCommit	(EDR_ERR_LOG * pLog,
						 EDR_ERR_LOG_NODE * pNode);
EDR_ERR_LOG_NODE *	edrErrLogNodeAlloc	(EDR_ERR_LOG * pLog);
int			edrErrLogNodeCount	(EDR_ERR_LOG * pLog);
int			edrErrLogMaxNodeCount	(EDR_ERR_LOG * pLog);

/* private routines */

STATUS edrErrLogHeaderProtect	(EDR_ERR_LOG * pLog);
STATUS edrErrLogHeaderUnprotect	(EDR_ERR_LOG * pLog);
STATUS edrErrLogNodeProtect	(EDR_ERR_LOG * pLog, EDR_ERR_LOG_NODE * pNode);
STATUS edrErrLogNodeUnprotect	(EDR_ERR_LOG * pLog, EDR_ERR_LOG_NODE * pNode);
int    edrErrLogNodePosition	(EDR_ERR_LOG * pLog, EDR_ERR_LOG_NODE * pNode);
BOOL   edrErrLogValidate        (EDR_ERR_LOG * pLog);

#ifdef  __cplusplus
}
#endif /* __cplusplus */

#endif /* __INCedrErrLogLib_h */
