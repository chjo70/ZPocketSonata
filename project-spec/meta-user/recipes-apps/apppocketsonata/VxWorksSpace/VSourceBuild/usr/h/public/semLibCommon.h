/* semLibCommon.h - common semaphore library header file */

/*
 * Copyright (c) 2003-2005, 2007-2010, 2013, 2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
*/

/*
modification history
--------------------
20may17,dlk  Adding SEM_TASK_DELETION_WAKEUP (F5593)
07nov13,cww  Merge in support for semi-scalable inline RW semaphores.
12nov10,zl   added SEM_ID_NULL definition
18aug10,s_s  removing shared memory references from enum SEM_TYPE and
             changing SEM_TYPE_MAX from 16 to 8
16jun10,pcs  change the data type of timeout from an int to _Vx_ticks_t
05may10,pch  reduced semaphore table size when using small footprint
28apr10,pad  Moved extern C statement after include statements.
15dec09,jpb  Added shared SEM_INFO structure for kernel & user.
09mar09,pcs  Updated to add support for the LP64 data model.
05sep08,cww  Removed semBMinimalXXX() and semMMinimalXXX() APIs
	     (WIND00133039)
05jul08,gls  added inline give/take routines
07jan08,gls  fast semaphores renamed to minimal semaphores
13dec07,gls  added SEM_TYPE_FAST_MUTEX and SEM_TYPE_FAST_BINARY
14sep07,gls  fixed SEM_TYPE_RW (Defect #WIND00104600)
27jun07,gls  added semExchange()
21jun07,mfj  Fixing comment reg. read/write semaphores
23jan07,gls  updated reader/writer semaphore support for release
03aug05,gls  added read/write semaphore support
05apr05,kk   added OPTIONS_MASK for each type of semaphore
02sep04,bwa  added S_semLib_INVALID_INITIAL_COUNT/COUNT_OVERFLOW errnos.
04may04,cjj  modified SEM_INFO struct. Removed semInfo prototype.
23apr04,dcc  added "context" to semOpen() parameters
11mar04,dcc  added semClose() and semUnlink() prototypes.
30mar04,ans  added SEM_INTERRUPTIBLE semaphore option
05nov03,md   added user level semaphores
25nov03,aeg  added SEM_INFO structure definition.
05sep03,dcc  added SEM_TYPE_OLD to the SEM_TYPE enum.
26aug03,cjj  written based on kernel version 04h of semLib.h
*/

#ifndef __INCsemLibCommonh
#define __INCsemLibCommonh

#include <vxWorks.h>
#include <vwModNum.h>
#include <objLib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* generic status codes */

#define S_semLib_INVALID_STATE			(M_semLib | 101)
#define S_semLib_INVALID_OPTION			(M_semLib | 102)
#define S_semLib_INVALID_QUEUE_TYPE		(M_semLib | 103)
#define S_semLib_INVALID_OPERATION		(M_semLib | 104)
#define S_semLib_INVALID_INITIAL_COUNT  	(M_semLib | 105)
#define S_semLib_COUNT_OVERFLOW                 (M_semLib | 106)

/* return value for unsuccessful semOpen() or semXCreate() */

#define SEM_ID_NULL	((SEM_ID) 0)

/* semaphore options */

#define SEM_Q_FIFO		 0x00	/* first in first out queue */
#define SEM_Q_PRIORITY		 0x01	/* priority sorted queue */
#define SEM_DELETE_SAFE		 0x04	/* owner delete safe (mutex opt.) */
#define SEM_INVERSION_SAFE	 0x08	/* no priority inversion (mutex opt.) */
#define SEM_EVENTSEND_ERR_NOTIFY 0x10	/* notify when eventRsrcSend fails */
#define SEM_INTERRUPTIBLE        0x20   /* interruptible on RTP signal */
/* semaphore options bit 0x80 is presently reserved */

#define SEM_NO_EVENT_SEND        0x100  /* inline: do not send events */
#define SEM_NO_SYSTEM_VIEWER     0x200  /* inline: no system viewer events */
#define SEM_NO_RECURSE           0x400  /* inline (mutex opt.): no recursion */
#define SEM_NO_ID_VALIDATE       0x800  /* inline: no semaphore validation */
#define SEM_NO_ERROR_CHECK       0x1000 /* inline: no error checking */

/* creation only */
#define SEM_TASK_DELETION_WAKEUP 0x2000 /* awaken early in case of deletion
                                           atempt on pending task. */

#define SEM_OPT_INLINE (SEM_NO_ID_VALIDATE | \
                        SEM_NO_ERROR_CHECK | \
                        SEM_NO_EVENT_SEND  | \
                        SEM_NO_SYSTEM_VIEWER | \
                        SEM_NO_RECURSE)

/* option masks for the types of semaphores */

#if !defined (_WRS_KERNEL)

#define SEM_BIN_OPTIONS_MASK	(SEM_Q_FIFO | 			\
				 SEM_Q_PRIORITY | 		\
				 SEM_EVENTSEND_ERR_NOTIFY | 	\
				 SEM_INTERRUPTIBLE | 		\
				 SEM_KUTYPE_MASK)

#else
#define SEM_BIN_OPTIONS_MASK	(SEM_Q_FIFO | 			\
				 SEM_Q_PRIORITY | 		\
				 SEM_EVENTSEND_ERR_NOTIFY | 	\
				 SEM_INTERRUPTIBLE)
#endif /* !_WRS_KERNEL */

#define SEM_CNT_OPTIONS_MASK	SEM_BIN_OPTIONS_MASK

#define SEM_MUT_OPTIONS_MASK	(SEM_BIN_OPTIONS_MASK | 	\
				 SEM_DELETE_SAFE |		\
				 SEM_INVERSION_SAFE)

#define SEM_RW_OPTIONS_MASK    (SEM_MUT_OPTIONS_MASK)

#ifndef	_ASMLANGUAGE

/*
 * semaphore types
 *
 * If changing this enum, also change the semTypeMsg[] translation arrays
 * in wind/semShow.c and vxmp/wind/semSmShow.c.  The initialization of
 * semEvIsFreeTbl[] in wind/semEvLib.c, and the table initializations in
 * configlette usrSemLib.c, may also need to be updated.
 */

typedef enum 		/* SEM_TYPE */
    {
    SEM_TYPE_BINARY,         /* 0: binary semaphore */
    SEM_TYPE_MUTEX,          /* 1: mutual exclusion semaphore */
    SEM_TYPE_COUNTING,       /* 2: counting semaphore */
    SEM_TYPE_RW,	     /* 3: read/write semaphore */
#ifndef	_WRS_CONFIG_CUSTOM_SEMAPHORE_TYPES
    /*
     * Reduce SEM_TYPE_MAX for small footprint, which allows only the
     * above 4 types, to eliminate wasted space in semaphore tables.
     */
    SEM_TYPE_MAX = 4
#else	/* _WRS_CONFIG_CUSTOM_SEMAPHORE_TYPES */
    /*
     * The semType field of the semaphore structure is a single byte.
     *
     * VxWorks uses various function pointer arrays indexed by the semaphore
     * type.  To limit the size of these arrays, the semaphore type is
     * masked with SEM_TYPE_MASK to obtain the array index.  Currently, when
     * _WRS_CONFIG_CUSTOM_SEMAPHORE_TYPES is defined, SEM_TYPE_MASK is 0x7,
     * allowing 8 semaphore types. SEM_TYPE_MASK is 0x3, allowing 4 semaphore
     * types, when _WRS_CONFIG_CUSTOM_SEMAPHORE_TYPES is not defined; in that
     * case, semaphores with type greater than SEM_TYPE_RW are not supported.
     *
     * The SEM_TYPE_MASK macro is currently defined in the private semaphore
     * header file.  It must be updated if the number of semaphore types
     * reaches 9 or more.
     */

    SEM_TYPE_MAX = 8
#endif	/* _WRS_CONFIG_CUSTOM_SEMAPHORE_TYPES */
    } SEM_TYPE;

/* binary semaphore initial state */

typedef enum		/* SEM_B_STATE */
    {
    SEM_EMPTY,			/* 0: semaphore not available */
    SEM_FULL			/* 1: semaphore available */
    } SEM_B_STATE;

/*
 * Since the size of SEM_INFO is different in user & kernel space for 64bit
 * builds, we must have two different definitions for the kernel-side.  In this
 * definition of SEM_INFO, we want to define the task id as being an id.  On
 * the user-side, we want to define the task id as being a handle.  The other
 * kernel definition is located in semLibP.h named SEM_INFO_USER.
 */

#define SEM_INFO_FIELDS(tidType)					      \
    UINT	numTasks;	/* OUT: number of blocked tasks */	      \
    SEM_TYPE 	semType;	/* OUT: semaphore type */                     \
    int		options;	/* OUT: options with which sem was created */ \
    union								      \
	{								      \
	UINT	count;		/* OUT: semaphore count (couting sems) */     \
	BOOL	full;		/* OUT: binary semaphore FULL? */	      \
	tidType	owner;		/* OUT: task ID of mutex semaphore owner */   \
        } state;

typedef struct
    {
    SEM_INFO_FIELDS(TASK_ID)
#ifdef _WRS_KERNEL
    int		taskIdListMax;	/* IN: max tasks to fill in taskIdList */
    TASK_ID *	taskIdList;	/* PTR: array of pending task IDs */
#endif /* _WRS_KERNEL */
    } SEM_INFO;

/* function declarations */

extern SEM_ID 	  semMCreate 	(int options);
extern SEM_ID 	  semBCreate 	(int options, SEM_B_STATE initialState);
extern SEM_ID 	  semCCreate 	(int options, int initialCount);
extern SEM_ID	  semRWCreate   (int options, int maxReaders);
extern STATUS 	  semDelete 	(SEM_ID semId);
extern STATUS 	  semExchange 	(SEM_ID giveSemId, SEM_ID takeSemId,
				 _Vx_ticks_t timeout);
extern STATUS 	  semFlush 	(SEM_ID semId);
extern STATUS 	  semGive 	(SEM_ID semId);
extern STATUS 	  semTake 	(SEM_ID semId, _Vx_ticks_t timeout);
extern STATUS	  semRTake      (SEM_ID semId, _Vx_ticks_t timeout);
extern STATUS	  semWTake      (SEM_ID semId, _Vx_ticks_t timeout);
extern SEM_ID	  semOpen	(const char * name, SEM_TYPE type,
				 int initState, int options, int mode,
				 void * context);
extern STATUS	  semInfoGet	(SEM_ID semId, SEM_INFO *pInfo);
extern STATUS 	  semClose	(SEM_ID semId);
extern STATUS 	  semUnlink	(const char * name);

#endif	/* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCsemLibCommonh */
