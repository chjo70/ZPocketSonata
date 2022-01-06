/* semLibP.h - private semaphore library header file */

/*
 * Copyright (c) 1984-2010, 2013-2015, 2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
26aug17,dlk  added semMCouldBeOwner() (V7COR-5296)
13apr15,gpa  CERT: changes for semRW* api compatibility
23oct14,pcs  made semTerminate() public (V7COR-2110).
20may14,jpb  V7COR-1084: Fixed typo of semaphore.
27aug13,rfr  Added semMPendByProxyNoLock
07nov13,cww  Merge in semi-scalable inline RW semaphores
09nov10,gls  Added VX_OBJ_ALIGN_SIZE aligment to SEMAPHORE typedef
13oct10,jpb  Fixed wrong offset listed in comments of SEMAPHORE struct
09sep10,jpb  Removed unused function pointer semSmInfoRtn.
31aug10,cww  Use dynamically generated offsets in offset macros
27aug10,s_s  SEM_TYPE_MASK value is changed to 0x7 as the maximum number
             of semaphores supported is 8
26jul10,s_s  Fix for the defect WIND00207200
16jun10,pcs  change the data type of timeout from an int to _Vx_ticks_t
07may10,pch  reduced semaphore table size when using small footprint
06may10,cww  Updated SEM_OWNER for LP64
03may10,cww  Fix size mismatch in SMP version of SEM_OWNER
29apr10,pad  Moved extern C statement after include statements.
23feb10,gls  added SEMC_PENDED_TASK
22dec09,jpb  Introduced new kernel-side structure SEM_INFO_USR.
22dec09,gls  added SEM_KERNEL_INTERRUPTIBLE (WIND00193764)
21dec09,pcs  Fixed an issue with the macro enclosing the offsets into the
	     semaphore (used by optimized semaphore libraries.)
09mar09,pcs  Updated to add support for the LP64 data model.
11feb09,zl   replaced qLib.h with qLibP.h
31jul09,jpb  Fixed build warnings.
01may09,gls  added semMTakeByProxyNoLock() for SMP
17jun08,gls  added inline give/take routines
13dec07,gls  updated MAX_SEM_TYPE and SEM_TYPE_MASK
04jun07,gls  added non-locking give and take routines
	     added various semaphore function pointers
19jan07,gls  updated reader/writer semaphore support
23oct06,jpb  Removed deprecated functions and message for semQInit
	     (Defect# 35589).
13oct05,yvp  Changes text of deprecated messages - use semXInitialize.
26aug05,gls  fixed pSemExt index comment (SPR #111547)
04aug05,gls  added read/write semaphore support
04aug05,yvp  Added prototype for create/delete library init.
07jun05,yvp  Updated copyright. #include now with angle-brackets.
12apr05,kk   start deprecation of semXCoreInit() and semQInit().
28sep04,fr   removed vSemCreate prototype (SPR 101349)
10sep04,fr   declared semCreateTbl (SPR 101247)
22mar04,dcc  added vSemCreate prototype.
09mar04,dcc  updated SEMAPHORE offsets.
08mar04,aeg  removed Diab _WRS_DEPRECATED C++ workaround.
02mar04,aeg  deprecated semOLib APIs.
31oct03,md   Added semMTakeByProxy
26aug03,tcr  remove WindView InstClassId
31oct03,dcc  updated semaphore offset comments, as a result of OBJ_CORE
	     expansion.
29oct03,pcm  implemented changes from code review
20oct03,pcm  added new SEMAPHORE field
05sep03,dcc  moved SEM_TYPE definitions to semLibCommon.h
30may03,to   added offset SEM_CLASS_ID for optimized semaphore routine.
	     deleted K&R style prototypes.
09apr03,ymz  update semaphore offset due to OBJ_CORE change
17oct01,bwa  Corrected ASM offsets for events. Added SEM_M_SEND_EVENTS
	     definition.
06sep01,bwa  Added VxWorks events support.
19may97,jpd  made SEM_TYPE_MASK available from assembler files.
10jul96,dbt  moved declaration of semMGiveForce to semLib.h (SPR #4352).
	     Updated copyright.
10dec93,smb  added instrument class
22sep92,rrr  added support for c++
27jul92,jcf  changed semMTakeKern to semMPendQPut.
19jul92,pme  added external declaration of shared sem show routine.
04jul92,jcf  created.
*/

#ifndef __INCsemLibPh
#define __INCsemLibPh

#ifndef	_ASMLANGUAGE
#include <vxWorks.h>
#include <vwModNum.h>
#include <semLib.h>
#include <private/qLibP.h>
#include <private/classLibP.h>
#include <private/objLibP.h>
#include <private/eventLibP.h>
#include <stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif

    /*
     *  ***** WARNING *****
     *
     * This private header file is included by the public header file(s):
     *   - h/inline/semLibInline.h
     *
     * Ensure that no usage of a VSB source configuration macro is made
     * by any structure or macro in this file that is also used(directly or
     * indirectly) by the above list of public header files.
     */

typedef SEM_ID (*SEM_CREATE_FUNC)      (int options, int initialState);
typedef STATUS (*SEM_TAKE_FUNC)        (SEM_ID semId, _Vx_ticks_t timeout);
typedef STATUS (*SEM_GIVE_FUNC)        (SEM_ID semId);
typedef STATUS (*SEM_FLUSH_FUNC)       (SEM_ID semId);
typedef void   (*SEM_GIVE_DEFER_FUNC)  (SEM_ID semId);
typedef void   (*SEM_FLUSH_DEFER_FUNC) (SEM_ID semId);

/*
 * It is not possible to include file taskLib.h in this file because of an
 * issue with circular dependancy between files taskLib.h and semLibP.h
 * Non-inclusing of taskLib.h causes the scope of the struct windTcb in the
 * below typedef's to be local and this leads to a warning from the compiler
 * To avoid this and to make the scope of the struct windTcb global, the
 * following line 'struct windTcb;' needs exist.
 */

struct windTcb;

typedef STATUS (*SEM_GIVE_NOLOCK_FUNC) (SEM_ID semId, struct windTcb * tCurrent);
typedef STATUS (*SEM_TAKE_NOLOCK_FUNC) (SEM_ID semId, _Vx_ticks_t timeout, 
		struct windTcb * tCurrent);
typedef void   (*WIND_SEM_DELETE_FUNC) (SEM_ID);
typedef STATUS (*SEM_EXCHANGE_FUNC) (SEM_ID giveSemId, SEM_ID takeSemId, 
                _Vx_ticks_t timeout);

/*
 * Since the size of SEM_INFO is different in user & kernel space for 64bit
 * builds, we must have two different definitions.  In this definition,
 * we want the size to match with the size in the user-side so we define the
 * task id as being an object handle.
 */

typedef struct
    {
    SEM_INFO_FIELDS(OBJ_HANDLE)
    } SEM_INFO_USR;

typedef struct semaphore /* SEMAPHORE */
    {
    OBJ_CORE	objCore         /* 0x00/0x00: object management */
	_WRS_DATA_ALIGN_BYTES (VX_OBJ_ALIGN_SIZE);
    UINT8	semType;	/* 0x44/0x80: semaphore type */
    UINT8	options;	/* 0x45/0x81: semaphore options */
    UINT16	recurse;	/* 0x46/0x82: semaphore recursive take count */
    BOOL        priInheritFlag; /* 0x48/0x84: TRUE if sem involved in */
				/*	      inheritance */
    Q_HEAD	qHead;		/* 0x4c/0x88: blocked task queue head */
    union
	{
	UINT		 count;	/* 0x5c/0xa8: current state count */
	struct windTcb * owner;	/* 0x5c/0xa8: current state owner */
	} state;
    EVENTS_RSRC	events;		/* 0x60/0xb0: VxWorks events */
                                /* 0x70/0xc0: sizeof SEMAPHORE */
    } SEMAPHORE;

typedef struct semRWListEntry    /* SEM_RW_LIST_ENTRY */
    {
    struct windTcb * readerId;       /* 0x00/0x00: maximum concurrent readers */
    UINT             recurse;        /* 0x04/0x08: current reader count */
    BOOL	     priInheritFlag; /* 0x08/0x0c: sem involved in */
				     /*		   inheritance */
    } SEM_RW_LIST_ENTRY;

typedef struct semRWExtention   /* SEM_RW_EXT */
    {
    UINT                  maxReaders;     /* 0x00/0x00: maximum concurrent  */
					  /*		readers */
    UINT                  readCount;      /* 0x04/0x04: current reader count */
    Q_HEAD                readQHead;      /* 0x08/0x08: blocked task queue */
					  /*		head */
    } SEM_RW_EXT;

#define semCount	state.count
#define semOwner	state.owner

/*
 * High order bit in SEMAPHORE creation options byte, indicates a 'minimal'
 * implementation for reader/writer semaphores. Private and possibly
 * temporary.
 */

#define SEM_OPT_MINIMAL	 0x80

/*******************************************************************************
*
* SEM_IS_MINIMAL - check if a semaphore has the SEM_OPT_MINIMAL bit
*
* RETURNS - a nonzero value if the semphore is minimal; otherwise zero.
*
* int SEM_IS_MINIMAL (SEM_ID semId)
*
* \NOMANUAL
*/

#define SEM_IS_MINIMAL(semId) ((semId)->options & SEM_OPT_MINIMAL)

/*******************************************************************************
*
* SEMRW_EXT_PTR_GET - return the read/write semaphore extension pointer
*
* RETURNS: A pointer to the read/write semaphore extension
*
* SEM_RW_EXT * SEMRW_EXT_PTR_GET (SEM_ID semId)
*
* \NOMANUAL
*/

#define SEMRW_EXT_PTR_GET(semId)                                              \
	 (                                                                    \
	  (SEM_RW_EXT *) ((char *) semId + sizeof (SEMAPHORE))                 \
	 )

/*******************************************************************************
*
* SEMRW_READER_ENTRY_PTR - return a pointer to a read/write reader list entry
*
* RETURNS: The read/write semaphore reader list pointer
*
* UINT SEMRW_READER_LIST (SEM_ID semId)
*
* \NOMANUAL
*/

#define SEMRW_READER_ENTRY_PTR(semId, index)                                  \
	 (                                                                    \
	  ((SEM_RW_LIST_ENTRY *)((char *) semId + sizeof (SEMAPHORE) +        \
				sizeof (SEM_RW_EXT) +                         \
				(index * sizeof (SEM_RW_LIST_ENTRY))))        \
	 )

/*******************************************************************************
*
* SEMRW_MAX_READERS - return the read/write semaphore maximum readers value
*
* RETURNS: The read/write semaphore maximum concurrent reader value
*
* UINT SEMRW_MAX_READERS (SEM_ID semId)
*
* \NOMANUAL
*/

#define SEMRW_MAX_READERS(semId) (SEMRW_EXT_PTR_GET(semId)->maxReaders)

/*******************************************************************************
*
* SEMRW_READ_CNT - return the read/write semaphore read count
*
* RETURNS: The read/write semaphore read count
*
* UINT SEMRW_READ_CNT (SEM_ID semId)
*
* \NOMANUAL
*/

#define SEMRW_READ_CNT(semId) (SEMRW_EXT_PTR_GET(semId)->readCount)

/*******************************************************************************
*
* SEMRW_RQHEAD - return the read/write semaphore read queue head
*
* RETURNS: The read/write semaphore read queue head
*
* Q_HEAD SEMRW_RQHEAD (SEM_ID semId)
*
* \NOMANUAL
*/

#define SEMRW_RQHEAD(semId) (SEMRW_EXT_PTR_GET(semId)->readQHead)

/*******************************************************************************
*
* SEMRW_IS_FREE - check if a read/write semaphore is free
*
* RETURNS: TRUE if the semaphore is free, FALSE if not.
*
* BOOL SEMC_IS_FREE (SEM_ID semId)
*
* \NOMANUAL
*/

#define SEMRW_IS_FREE(semId)                                                  \
	 (                                                                    \
	  ((semId)->semOwner == NULL) && (SEMRW_READ_CNT(semId) == 0)        \
	 )

/*******************************************************************************
*
* SEM_RWMIN_VALUE - return main state value for minimal RW semaphore
*
* RETURNS: The value encoding the minimal RW semaphore's state.  This is
*          only used for 'minimal' RW semaphores (see semRWLibInline.h)
*
* atomic32_t SEM_RWMIN_VALUE (SEM_ID semId)
*
* NOTE: The return value is an lvalue, and it is intended for use only
*       by taking its address, e.g. &SEM_RWMIN_VALUE(semId).
*       Call vxAtomic32Get() to obtain the value from this address.
*
* \NOMANUAL
*/

#define SEM_RWMIN_VALUE(semId) (*(atomic32_t *)&(semId)->state.count)

/* Main semaphore state for minimal RW semaphores */

#define SEM_RWMIN_VAL_PEND	(0x1)
#define SEM_RWMIN_VAL_W_OWNS	(0x2)
#define SEM_RWMIN_VAL_R_INC	(0x4)

/*******************************************************************************
*
* SEMC_IS_FREE - check if a counting semaphore is free
*
* RETURNS: TRUE if the semaphore is free, FALSE if not.
*
* BOOL SEMC_IS_FREE (SEM_ID semId)
*
* \NOMANUAL
*/

#define SEMC_IS_FREE(semId) ((semId)->semCount > 0)

/*******************************************************************************
*
* SEMBM_IS_FREE - check if a binary or mutex semaphore is free
*
* RETURNS: TRUE if the semaphore is free, FALSE if not.
*
* BOOL SEMBM_IS_FREE (SEM_ID semId)
*
* \NOMANUAL
*/

#ifndef _WRS_CONFIG_SMP
#define SEMBM_IS_FREE(semId) ((semId)->semOwner == NULL)
#else
#define SEMBM_IS_FREE(semId) (vxAtomicGet_inline((atomic_t *) \
                                              (void *) &(semId)->semOwner) == 0)
#endif

/*******************************************************************************
*
* SEM_OWNER - retrieve owner field of semaphore
*
* RETURNS: semOwner field of semaphore
*
* \NOMANUAL
*/

#ifndef _WRS_CONFIG_SMP
#define SEM_OWNER(semId) ((semId)->semOwner)
#else
#define SEM_OWNER(semId)                                                       \
    ((struct windTcb *)(vxAtomicGet_inline ((atomic_t *) &(semId)->semOwner) & \
			~SEM_PENDED_TASK))
#endif

/* variable declarations */

extern OBJ_CLASS	    semClass;		 /* semaphore object class */
extern CLASS_ID		    semClassId;		 /* semaphore class id */
extern SEM_CREATE_FUNC	    semCreateTbl [];	 /* semCreate() methods */
extern SEM_GIVE_FUNC	    semGiveTbl [];	 /* semGive() methods */
extern SEM_TAKE_FUNC	    semTakeTbl [];	 /* semTake() methods */
extern SEM_FLUSH_FUNC	    semFlushTbl [];	 /* semFlush() methods */
extern SEM_GIVE_DEFER_FUNC  semGiveDeferTbl [];	 /* semGiveDefer() methods */
extern SEM_FLUSH_DEFER_FUNC semFlushDeferTbl []; /* semFlushDefer() methods */
extern SEM_GIVE_NOLOCK_FUNC semGiveNoLockTbl []; /* semGiveNoLock() methods */
extern SEM_TAKE_NOLOCK_FUNC semTakeNoLockTbl []; /* semTakeNoLock() methods */

extern FUNCPTR  semSmShowRtn;	/* shared semaphore show routine pointer */

/* function declarations */

extern STATUS	semLibInit		(void);
extern void	semDeleteLibInit	(void);
extern void	semBCreateLibInit	(void);
extern void	semCCreateLibInit	(void);
extern void	semMCreateLibInit	(void);
extern STATUS	semDestroy		(SEM_ID semId, BOOL dealloc);
extern STATUS	semGiveDefer		(SEM_ID semId);
extern STATUS	semFlushDefer		(SEM_ID semId);
extern STATUS	semInvalid		(SEM_ID semId);
extern STATUS	semIntRestrict		(SEM_ID semId);
extern STATUS	semQFlush		(SEM_ID semId);
extern void	semQFlushDefer		(SEM_ID semId);
extern STATUS	semBInit		(SEMAPHORE * pSem, int options,
					 SEM_B_STATE initialState);
extern STATUS	semBGive		(SEM_ID semId);
extern STATUS	semBGiveNoLock		(SEM_ID semId,
					 struct windTcb * tCurrent);
extern STATUS	semBTake		(SEM_ID semId, _Vx_ticks_t timeout);
extern STATUS	semBTakeNoLock		(SEM_ID semId, _Vx_ticks_t timeout, 
					 struct windTcb * tCurrent);
extern void	semBGiveDefer		(SEM_ID semId);
extern STATUS	semMInit		(SEMAPHORE * pSem, int options);
extern STATUS	semMGive		(SEM_ID semId);
extern STATUS	semMGiveNoLock		(SEM_ID semId,
					 struct windTcb * tCurrent);
extern STATUS	semMTake		(SEM_ID semId, _Vx_ticks_t timeout);
extern STATUS	semMTakeByProxy		(SEM_ID semId, TASK_ID tid);

#ifdef _WRS_CONFIG_SMP
extern STATUS	semMTakeByProxyNoLock	(SEM_ID semId, struct windTcb * pTcb);
#endif

extern STATUS	semMTakeNoLock		(SEM_ID semId, _Vx_ticks_t timeout, 
					 struct windTcb * tCurrent);
extern STATUS	semMPendQPut		(SEM_ID semId, _Vx_ticks_t timeout, 
			    		 struct windTcb * tCurrent);
extern STATUS	semCInit		(SEMAPHORE * pSem, int options,
					 int initialCount);
extern STATUS	semCGive		(SEM_ID semId);
extern STATUS	semCTake		(SEM_ID semId, _Vx_ticks_t timeout);
extern void	semCGiveDefer		(SEM_ID semId);

#ifndef _WRS_CONFIG_CERT
extern STATUS	semRWGive		(SEM_ID semId);
#else
#define semRWGive(semId) 		semMGive((semId))
#endif

extern STATUS	semQInit		(SEMAPHORE * pSemaphore, int options);

extern STATUS	semMGiveKernWork	(SEM_ID semId, int kernWork,
				 	 struct windTcb * tCurrent);


extern void	semMPendByProxyNoLock	(SEM_ID semId, struct windTcb *pTcb);

#ifdef _WRS_CONFIG_SMP
extern STATUS	semMGiveHard		(SEM_ID semId,
					 struct windTcb * tCurrent,
					 int options);
extern STATUS	semMTakeHard		(SEM_ID semId, _Vx_ticks_t timeout, 
			     		 struct windTcb * tCurrent,
					 int options);
extern STATUS	semBGiveHard		(SEM_ID semId, int options);
extern STATUS	semBTakeHard		(SEM_ID semId, _Vx_ticks_t timeout,
					 int options);
#endif

extern int      semMCouldBeOwner        (SEM_ID semId, TASK_ID taskId);

#ifdef __cplusplus
}
#endif

#else	/* _ASMLANGUAGE */

/*
 * offsets into SEMAPHORE - these must be in an ASM section due to a circular
 * dependency when compiling offsets.c
 *
 * WARNING: the old offset macros are provided temporarily only for a
 * transitionary phase.  They will be removed once existing references are
 * updated to use the dynamically generated offsets.
 */

#ifndef _WRS_CONFIG_LP64

#include <private/offsetMacrosP.h>

#define SEM_CLASS_ID            WIND_OBJ_CORE_CLASS_ID
#define SEM_TYPE                SEMAPHORE_semType_OFFSET
#define SEM_OPTIONS             SEMAPHORE_options_OFFSET
#define SEM_RECURSE             SEMAPHORE_recurse_OFFSET
#define SEM_PRI_INHERIT_FLAG    SEMAPHORE_priInheritFlag_OFFSET
#define SEM_Q_HEAD              SEMAPHORE_qHead_OFFSET
#define SEM_STATE               SEMAPHORE_count_OFFSET
#define SEM_EVENTS              SEMAPHORE_events_OFFSET
#define SEM_EVENTS_TASKID       SEMAPHORE_events_OFFSET
#define SEM_EVENTS_REGISTERED   SEMAPHORE_events_registered_OFFSET
#define SEM_EVENTS_OPTIONS      SEMAPHORE_events_options_OFFSET

#define	SEM_INST_RTN		OBJ_CLASS_createRtn_OFFSET

#endif  /* _WRS_CONFIG_LP64 */
#endif	/* _ASMLANGUAGE */

/* private semaphore options */

#define SEM_KERNEL_INTERRUPTIBLE 0x40   /* interruptible on signal */

/* semaphore types */

#define MAX_SEM_TYPE		SEM_TYPE_MAX	/* maximum # of sem classes */

/* must be different from OK, ERROR, and RESTART */

#define PENDED                  2

#define SEM_M_Q_GET		0x1
#define SEM_M_SAFE_Q_FLUSH	0x2
#define SEM_M_PRI_RESORT	0x4
#define SEM_M_SEND_EVENTS	0x8
#define SEM_M_INLINE_PRI_RESORT	0x10

#define SEM_PENDED_TASK		0x1	/* a task is pended */

/*
 * The SMP implementations for the take and give of a binary semaphore
 * use the following definitions for the "empty" and "full" state of a
 * semaphore.  This contrasts with the UP implementation which uses the value
 * NULL for the "full" state, and 'taskIdCurrent' for the "empty" state.
 *
 * The SEMB_PENDED_TASK bit is modified only when holding the kernel
 * lock.  When the SEMB_PENDED_TASK bit is set, this indicates that a
 * task has attempted a take operation while the semaphore was "empty".
 */

#define SEMB_FULL_STATE   	NULL
#define SEMB_EMPTY_STATE	0x10		/* ensure LSB is not set */
#define SEMB_PENDED_TASK	SEM_PENDED_TASK	/* a task is pended */

/*
 * For both SMP and UP NULL is used to designate a semaphore with no owner.
 *
 * The SEMM_PENDED_TASK bit is modified only when holding the kernel
 * lock.  When the SEMM_PENDED_TASK bit is set, this indicates that a
 * task has attempted a take operation while another task owned the mutex.
 */

#define SEMM_NO_OWNER 		NULL
#define SEMM_PENDED_TASK        SEM_PENDED_TASK	/* a task is pended */

/*
 * The SEMC_PENDED_TASK bit is modified only when holding the kernel
 * lock.  When the SEMC_PENDED_TASK bit is set, this indicates that a
 * task has attempted a take operation with a count of zero.
 *
 * While both mutex and binary semaphores use bit 0x1 to designate a task
 * has pended counting semaphores use the most significant bit of the
 * count field (which is an unsigned integer).  This is to allow the 
 * implementation to continue to increment/decrement by one.
 */

#define SEMC_PENDED_TASK        0x80000000

#ifdef	_WRS_CONFIG_CUSTOM_SEMAPHORE_TYPES

    /* normal configuration allows types 0-15 */

#define SEM_TYPE_MASK		0x7	/* semaphore class mask */

#else	/* _WRS_CONFIG_CUSTOM_SEMAPHORE_TYPES */

    /* small footprint allows only types 0-3 */

#define SEM_TYPE_MASK		0x3	/* semaphore class mask */

#endif	/* _WRS_CONFIG_CUSTOM_SEMAPHORE_TYPES */

#endif /* __INCsemLibPh */

