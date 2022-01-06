/* aioPxLibP.h - asynchronous I/O header file */

/* Copyright 1984-2006, 2010, 2016 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use 
 * of this software may be licensed only pursuant to the terms 
 * of an applicable Wind River license agreement. 
 */ 

/*
modification history
--------------------
19nov16,zl   unified user/kernel implementation using native condition
             variables and mutexes (V7COR-4556).
10aug16,i_l  used native API for kernel.
30jun10,jxu  LP64:change member(maxFiles) of structure aio_dev from 
	     int to size_t. 
28apr10,pad  Moved extern C statement after include statements.
24jul06,jpb  Removed duplicate definition of AIO_SYS.
14jul06,jlk  Added SIGEV_THREAD support
07mar06,mil  Removed stdbool.h.  Added conditional for non-POSIX code.
20jan06,mil  Updated for POSIX namespace conformance.
30jan04,dat  Rework for RTP compatibility
18jul96,dbt  moved aioPxLibInit() and aioShow() prototypes to aio.h 
    	     (SPR #3227).
    	     Updated copyright.
15apr94,kdl  changed FD_NODE_TO_SYS macro to use offsetof().
08apr94,kdl  changed aio_show() to aioShow().
26jan94,kdl  changed include of ioQPxLib.h to ioQLib.h.
12jan94,kdl  changed aioInit() to aioPxLibInit(); general cleanup.
06dec93,dvs  changed M_aioLib to M_aioPxLib
	     changed S_aioLib* to S_aioPxLib*
04apr93,elh  written.
*/

/*
 * Note: This file contains definitions that must be maintained in both kernel
 * and user space
 */

#ifndef __INCaioPxLibh
#define __INCaioPxLibh

/* includes */

#ifdef _WRS_KERNEL
#include <sigLib.h> /* need generic signal send rtn in RTP space!*/
#endif

#if !defined(_POSIX_C_SOURCE) && !defined(_XOPEN_SOURCE) && \
    !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE)
#include <private/semLibP.h>
#ifdef _WRS_KERNEL
#include <private/condVarLibP.h>
#else
#include <condVarLib.h>
#endif
#include <semLib.h>
#include <pthread.h>
#include <selectLib.h>
#include <lstLib.h>
#include <semLib.h>
#include <ioQLib.h>
#include <dllLib.h>
#include <stddef.h>
#else   /* _POSIX_xxx_SOURCE */
#include <base/b_union_sigval.h>
#include <types/vxWind.h>
#include <types/vxTypesOld.h>
#include <private/base/b_struct_vx_semaphore.h>
#include <ioQLib.h>
#include <dllLib.h>
#endif  /* _POSIX_xxx_SOURCE */

#ifdef __cplusplus
extern "C" {
#endif

/* defines */

#if !defined(_POSIX_C_SOURCE) && !defined(_XOPEN_SOURCE) && \
    !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE)

/* aio driver ioctl functions */

#define  FAIO_PUSH		1		/* push request to head */
#define  FAIO_CANCEL		2		/* cancel a request */

/* aio control block states */

#define AIO_FREE		0		/* not submitted */
#define AIO_COMPLETED		1		/* completed */
#define AIO_READY		2		/* ready to be submitted */
#define AIO_QUEUED		3		/* queued */
#define AIO_WAIT   		4		/* waiting */
#define AIO_RUNNING		5		/* running */

#define AIO_CLUST_MAX           100             /* default max clusters */

/* easy access to aio_sys */

#define aio_state		aio_sys.state
#define aio_retVal 		aio_sys.ioNode.retVal
#define aio_errorVal		aio_sys.ioNode.errorVal

/* mark request done */

#define AIO_DONE_SET(pAiocb, _ret, _err) 	\
    {						\
    (pAiocb)->aio_sys.state    = AIO_COMPLETED;	\
    (pAiocb)->aio_sys.ioNode.retVal   = (_ret);	\
    (pAiocb)->aio_sys.ioNode.errorVal = (_err);	\
    }

#define FD_NODE_TO_SYS(pNode)			\
	((AIO_SYS *)(void *)((char *)(pNode) - offsetof(AIO_SYS, fdNode)))

#ifdef _WRS_KERNEL
#define _AIO_COND	CONDVAR
#else
#define _AIO_COND	CONDVAR_ID
#endif

/* typedefs */

typedef struct aio_clust			/* aio cluster */
    {
    BOOL		inuse;			/* cluster in use */
    BOOL		initialized;		/* cluster initialized */
    int			refCnt;			/* reference count */
#ifdef _WRS_KERNEL
    struct sigpend	sigpend;		/* signal */
#else
    struct sigevent	aio_clust_sigevent;	/* signal info for cluster */
#endif

    SEMAPHORE           lock;			/* mutex */
    _AIO_COND           wake;			/* condition variable */
    } AIO_CLUST;

#endif  /* _POSIX_xxx_SOURCE */

#if defined(_POSIX_C_SOURCE) || defined(_XOPEN_SOURCE) || \
    defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE)
#undef ioNode
#undef state
#undef pClust
#undef pAiocb
#undef sigNo
#undef sigVal
#undef lock
#undef wait
#undef fdNode
#endif

typedef struct aio_sys				/* aio system info */
    {
    _Vx_IO_NODE		ioNode;			/* I/O queue node */
    int			state;			/* state */
    struct aio_clust *	pClust;			/* lio cluster */
    struct aiocb *	pAiocb;			/* A-I/O control block */
#ifdef _WRS_KERNEL
    struct sigpend     	sigpend;		/* signal */
    SEMAPHORE           lock;			/* mutex */
#else  /* _WRS_KERNEL */
    int			sigNo;
    union sigval	sigVal;
    _Vx_SEMAPHORE       lock;			/* mutex */
#endif /* _WRS_KERNEL */
    _Vx_LIST		wait; 			/* wait list */
    _Vx_DL_NODE		fdNode;			/* node for fd list */
    } AIO_SYS;

struct aio_clust;
struct aiocb;

#if !defined(_POSIX_C_SOURCE) && !defined(_XOPEN_SOURCE) && \
    !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE)
typedef struct aio_wait_id			/* wait structure */
    {
    NODE		node;			/* wait list node */
    BOOL		done;			/* completed */
    SEMAPHORE           lock;			/* mutex */
    _AIO_COND           wake;			/* condition variable */
    } AIO_WAIT_ID;

typedef struct aio_fd_entry			/* A-I/O fd table entry */
    {
    DL_LIST 		ioQ;			/* I/O queue */
    SEM_ID	   	ioQSem;			/* semaphore for I/O queue */
    } AIO_FD_ENTRY;

typedef struct aio_dev				/* driver A-I/O struct */
    {
    IO_Q		ioQ;			/* I/O queues */
    size_t		maxFiles;		/* max files */
    SEM_ID		lockSem;		/* system lock semaphore */
    AIO_FD_ENTRY *	fdTable;		/* table array */
    AIO_CLUST *		clustTable;		/* cluster array */
    int			clustMax;		/* cluster array size */
    FUNCPTR		printRtn;		/* print rtn */
    SEM_ID		ioSem;			/* mutex ?? */
    SEM_ID		qSem;			/* work and done ? */
    SEM_ID		workSem;		/* work semaphore */
    int			waitFd;			/* wait pipe fd */
    fd_set		ioWait[2];		/* Yuch ! */
    fd_set		io[2];			/* more yuch ! */
    } AIO_DEV;
#endif  /* _POSIX_xxx_SOURCE */

#if !defined(_POSIX_C_SOURCE) && !defined(_XOPEN_SOURCE) && \
    !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE)

extern AIO_DEV	aioDev;				/* single global struct */

/* forward declarations These are PRIVATE */

extern STATUS 	aioCancel (AIO_DEV * pDev, struct aiocb * pAiocb);
extern STATUS 	aioPush (AIO_DEV * pDev, struct aiocb * pAiocb);
extern STATUS 	aioSync (AIO_DEV * pDev, struct aiocb * pAiocb, 
	       	         FUNCPTR syncReqRtn, int op);
extern void 	aioDone (AIO_SYS * pReq);

extern AIO_SYS* aioNext (AIO_DEV * pDev);
extern AIO_FD_ENTRY* aioEntryFind (int fd);

#endif  /* _POSIX_xxx_SOURCE */

#ifdef __cplusplus
}
#endif

#endif /* __INCaioPxLibh */
