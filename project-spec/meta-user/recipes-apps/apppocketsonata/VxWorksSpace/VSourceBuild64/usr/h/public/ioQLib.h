/* ioQLib.h - I/O queue library header file */

/* Copyright 1993-2006, 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use 
 * of this software may be licensed only pursuant to the terms 
 * of an applicable Wind River license agreement. 
 */ 

/*
modification history
--------------------
01h,23jun10,jxu  LP64 support: changed structure member(taskId) of _Vx_io_node
                 from type of int to TASK_ID, and member(retVal) from int to 
                 ssize_t.
01g,28apr10,pad  Moved extern C statement after include statements.
01f,24jul06,jpb  Removal of duplicate definiton of IO_NODE and IO_Q.
01e,13mar06,mil  Added prefix _Vx_ to struct io_node and struct io_q.
01d,26jan06,mil  Updated for POSIX namespace conformance (P2).
01c,29apr05,hya  added IO_DSYNC.
01b,26jan94,kdl  changed name to ioQLib.h.
01a,04apr93,elh  written.
*/

/*
 * Note: This file contains definitions that must be maintained in both kernel
 * and user space
 */

#ifndef __INCioQLibh
#define __INCioQLibh

/* includes */

#if !defined(_POSIX_C_SOURCE) && !defined(_XOPEN_SOURCE) && \
    !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE)
#include <vxWorks.h>
#include <semLib.h>
#else   /* _POSIX_xxx_SOURCE */
#include <types/vxTypesOld.h>
#endif  /* _POSIX_xxx_SOURCE */
#include <lstLib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* typedefs */

#if defined(_POSIX_C_SOURCE) || defined(_XOPEN_SOURCE) || \
    defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE)
#undef node
#undef op
#undef prio
#undef taskId
#undef retVal
#undef errorVal
#undef doneRtn
#undef value
#endif

typedef struct _Vx_io_node			/* I/O node */
    {
    _Vx_NODE		node;			/* list node */
    int			op;			/* op IO_READ | IO_WRITE */ 
    int			prio;			/* priority */
#ifdef _WRS_KERNEL	
    TASK_ID		taskId;			/* initiating task id */
#else
    _Vx_TASK_ID		taskId;			/* initiating task id */
#endif		

    ssize_t		retVal;			/* return value */
    int			errorVal;		/* error value */
#ifdef _WRS_KERNEL	
    VOIDFUNCPTR	doneRtn;		/* done routine */
#else
    _Vx_VOIDFUNCPTR	doneRtn;		/* done routine */
#endif		
    int 		value;
    } _Vx_IO_NODE;

#if defined(_POSIX_C_SOURCE) || defined(_XOPEN_SOURCE) || \
    defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE)
#undef workQ
#undef waitQ
#undef lock
#undef unlock
#undef lockArg
#endif

typedef struct _Vx_io_q				/* I/O queue */
    {
    _Vx_LIST		workQ;			/* list structure */
    _Vx_LIST		waitQ;			/* list structure */
    void (*lock)(_Vx_usr_arg_t); 		/* lock routine */
    void (*unlock)(_Vx_usr_arg_t); 		/* unlock routine */
    _Vx_usr_arg_t	lockArg;		/* arg for lock/unlock */
    } _Vx_IO_Q;

#if !defined(_POSIX_C_SOURCE) && !defined(_XOPEN_SOURCE) && \
    !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE)	
typedef _Vx_IO_NODE IO_NODE;
typedef _Vx_IO_Q IO_Q;
#endif	

/* defines */

#if !defined(_POSIX_C_SOURCE) && !defined(_XOPEN_SOURCE) && \
    !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE)

/* i/o operations */

#define IO_READ	 		0	/* READ operation */
#define	IO_WRITE		1	/* WRITE operation */
#define IO_SYNC			2	/* Sync operation */
#define IO_DSYNC		3	/* Data sync operation */

/* i/o synchronization and operations */

#define IOQ_LOCK(pQ)		((*(pQ)->lock) ((pQ)->lockArg))
#define IOQ_UNLOCK(pQ)		((*(pQ)->unlock) ((pQ)->lockArg))

#define IOQ_WORK_ADD(pQ, pNode, prio)				\
    		ioQAdd (&(pQ)->workQ, (pNode), (prio))

#define IOQ_WORK_ADD_HEAD(pQ, pNode)				\
		lstInsert (&(pQ)->workQ, NULL, &(pNode)->node)

#define IOQ_WAIT_ADD(pQ, pNode, prio)				\
    		ioQAdd (&(pQ)->waitQ, (pNode), (prio))

#define IOQ_WORK_DELETE(pQ, pNode)	lstDelete (&(pQ)->workQ, &(pNode)->node)
#define IOQ_WAIT_DELETE(pQ, pNode)	lstDelete (&(pQ)->waitQ, &(pNode)->node)

/* forward declarations */

extern void 	ioQInit (IO_Q * , void (*)(_Vx_usr_arg_t), 
                         void (*)(_Vx_usr_arg_t), _Vx_usr_arg_t );
extern void	ioQNodeDone (IO_NODE * pNode);
extern void	ioQLockSem (SEM_ID semId);
extern void	ioQUnlockSem (SEM_ID semId);
extern void 	ioQAdd (LIST * pQ, IO_NODE * pNode, int prio);
extern void 	ioQDelete (IO_Q * pQ, IO_NODE * pNode);
extern IO_NODE* ioQEach (LIST * , 
                         BOOL ( * )(IO_NODE*, _Vx_usr_arg_t, _Vx_usr_arg_t),
                         _Vx_usr_arg_t , _Vx_usr_arg_t );

#endif  /* _POSIX_xxx_SOURCE */

#ifdef __cplusplus
}
#endif

#endif /* __INCioQLibh */
