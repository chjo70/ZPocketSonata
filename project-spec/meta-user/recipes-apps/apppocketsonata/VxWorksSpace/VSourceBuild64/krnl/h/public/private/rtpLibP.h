/* rtpLibP.h - private real time process library header */

/*
 * Copyright (c) 2003-2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
23oct17,dlk  avoid deadlock deleting RTP if deletion safe task takes RTP lock
             (V7COR-5328)
20apr16,gls  added _rtpSpawn()
31mar16,r_w  Added new field parentRtpHandle in WIND_RTP structure (V7COR-3946)
30sep15,rr   Updated rtpLibInit() prototype and
             added globalRtpMemFill (V7COR-3084)
23mar15,txu  Added 'cmask' member to WIND_RTP to support umask() (US55492)
09sep14,cww  fixed static analysis errors
03jul14,pad  Added 'pCredentials' member to WIND_RTP to support user
             identification inheritance (US40207). Removed paddings - now
             unnecessary - from this structure, along with all offset info.
22may14,jpb  V7COR-943: fixed documentation on WIND_RTP offsets
03mar14,cww  shlRtpDeleteAll() now returns STATUS
03mar14,pad  Added definitions of rtpDeletionDeferEnable() and
             rtpDeletionDeferDisable() (issue VXW7-2012).
08jan14,dbt  Added hooks when shared libraries are opened/closed
16oct13,h_k  removed loadRtpLibP.h header inclusion if LOADER pkg is
             uninstalled.
10sep13,jmp  Added _func_rtpTaskEach.
03feb12,jpb  CQ Req WIND00139205: Added pend queue member to WIND_RTP for
             RTP wait mechanism.
13jan12,cww  Updated RTP_ID_VERIFY to not use objVerify directly (WIND00320250)
26sep11,zl   removed unused ctxCnt from KERNEL_RTP_CMN.
15dec10,zl   optimized RTP_DELETE_SAFE_EXIT().
16aug10,cww  Use dynamically generated offsets in offset macros
18apr10,jpb  Added func bind prototypes.
06apr10,jpb  Added prototypes & function pointers.
09mar10,cww  Update pointer type for rtpSigReturnRtn and taskExitRtn
27jan10,cww  Added rtpAuxXXX and memRtp routine prototypes
19jan10,zl   added _func_rtpVerifiedLock.
28dec09,jpb  Added definition of RTP_USER_DESC.
22dec09,cww  Added rtpTaskExitRegister declaration
03dec09,cww  LP64 adaptation
26jun09,j_b  add WIND_RTP element offsets for lockTaskId and kernelRtpCmn
27aug08,jpb  Renamed VSB header file
09jul08,jpb  Now use objVerify() instead of OBJ_VERIFY() for the UP
             version of the RTP_ID_VERIFY() macro since the VSB feature
	     allows for OBJ_VERIFY() to be always TRUE.
24jun08,jpb  Added include path for kernel configurations options set in
             vsb.  Renamed _WRS_VX_SMP to _WRS_CONFIG_SMP.
11mar08,to   include taskLibP.h to use taskIdCurrent for UP
27jun07,pad  Replaced direct calls to spinLockTaskTake()/Give() with the
             SPIN_LOCK_TASK_TAKE/GIVE macros.
20apr07,jlk  Added fdTableSem to WIND_RTP structure.
20feb07,pad  Introduced SMP-safe RTP locking mechanism: reference count
	     field in WIND_RTP structure and additional macros.
21aug06,jpb  Removed pUsrPthreadInfo filed from the wind_rtp structure
             (WIND00062557).
22jun06,tcr  add traceData to WIND_RTP
20jan06,pad  Updated rtpLibInit()'s prototype.
13jan06,bpn  Added parentTaskId field to WIND_RTP to know which task
             created the RTP (SPR#114885).
14oct05,zl   removed memInfo.
29jun05,zl   added RTP_VM_CONTEXT_GET() and RTP_PAGE_MGR_GET();
11may05,gls  added zombieHandleId to ZOMBIE_RTP (SPR #109170)
08mar05,kk   added cpuTimeInfo[2] and pSchedInfo to WIND_RTP
25feb05,pcs  Updated the prototype of fn. rtpLibInit to handle different
             overflow and underflow sizes for the execution and exception
             stacks.
18oct04,kk   clean up comments
06oct04,dcc  added objMgtSemId to WIND_RTP
27sep04,ans  Added reserved, spare fields to WIND_RTP.
22sep04,ans  added rtpLibInit() rtpShowInit() rtpShellCmdInit()
10sep04,kk   renamed rtpBaseLib to kernelBaseLib
18aug04,pad  Added pUsrPthreadInfo field in wind_rtp structure.
02sep04,yvp  rtpHookLibInit() prototype change.
17aug04,yvp  Added exitCode parameter to RTP delete hooks.
05jul04,dcc  added handle table growing support.
05may04,yvp  Added extra parameter to RTP Pre-create hooks
26apr04,ans  added macros to get state definition
15apr04,kk   added rtpHandleId
14apr04,kk   added initTaskHandle for initTaskId
08apr04,yvp  Added RTP Init-Complete hooks.
31mar04,jn   Rename rtpLoadLib -> loadRtpLib
11mar04,job  Moved ACCESS_DENIED error value to public header file.
30mar04,dms  Add rtpShlNodeList and rtpShlNodeListMutex fields to the
             wind_rtp structure.
02mar04,kk   added rtpVar to RTP data structure
19feb04,dat  chg tableSize from int to size_t
05nov03,md   added lockTaskId for tracking task which has rtp locked
02dec03,dcc  added pHandleTable member to the WIND_RTP structure.
26nov03,jn   Add declaration for rtpIdVerify
01dec03,nrj  struct names changed as per coding std
12nov03,pmr  added default path to RTP struct.
25nov03,nrj  code review mods
23oct03,gls  added MEM_INFO to KERNEL_RTP_CMN
	     removed adrsSpaceId from KERNEL_RTP_CMN
             removed mmList from WIND_RTP
13nov03,yvp  Added RTP hook typedefs.
24oct03,nrj  added support for parent-child RTP
21oct03,nrj  moved kernel specific macros to rtpBaseLib.h
15oct03,nrj  sig lib includes the RTP and not the other way
12oct03,nrj  added signal feature
25aug03,x_p  Took from base6_itn2_rtp-dev.al
11sep03,zl   added mmList to WIND_RTP.
07sep03,kk   update NODE_TO_RTP to reflect KERNEL_RTP_CMN addition
04sep03,nrj  rationalized kernel RTP
29aug03,pad  Updated binaryInfo field RTP_IMAGE_INFO type.
14aug03,job  Added some useful macros
15jul03,pad  Added fields for segment info in WIND_RTP structure.
26jun03,nrj  created.
*/

#ifndef	__INCrtpLibPh
#define	__INCrtpLibPh

#ifndef	_ASMLANGUAGE

/* includes */

#include <vxWorks.h>
#include <vsbConfig.h>
#include <auxv.h>
#include <rtpLib.h>
#include <classLib.h>
#include <dllLib.h>
#include <lstLib.h>
#include <envLib.h>
#include <semLib.h>
#include <shlLib.h>
#include <rtpVarLib.h>
#include <private/shlLibP.h>
#include <private/taskLibP.h>
#include <private/objLibP.h>
#ifdef	_WRS_CONFIG_OSTOOLS
#include <symLib.h>
#endif	/* _WRS_CONFIG_OSTOOLS */
#ifdef	_WRS_CONFIG_LOADER
#include <private/loadRtpLibP.h>
#endif	/* _WRS_CONFIG_LOADER */
#include <private/rtpSigLibP.h>
#include <private/rtpPthreadLibP.h>
#include <private/vmLibP.h>
#include <private/pgMgrLibP.h>
#ifdef _WRS_CONFIG_SMP
#include <spinLockLib.h>
#include <private/kernelLibP.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* externs */

extern CLASS_ID	rtpClassId;
extern DL_LIST	rtpList;
extern BOOL     globalRtpMemFill;
#ifdef _WRS_CONFIG_SMP
extern spinlockTask_t rtpObjProtect;	/* Spinlock protecting the access to
					   the WIND_RTP object in SMP mode */
#endif

/* macros */

#define NUM_RTP_HOOK_TBLS	4

/*
 * Macros to update the RTP state and status field.
 * Using the XX_PUT_XX macros, one can write multiple state/status value(s).
 * Using the XX_SET_XX / XX_UNSET_XX macros, one can set or unset a specific
 * state/status value.
 * The XX_GET_XX macros are defined in rtpLibCommon.h, so that user code
 * can inspect the state/status of an RTP after the rtpInfoGet() system call.
 */

#define RTP_STATE_PUT(pValue, value) (*((UINT32 *)pValue) = \
         (((value) & RTP_STATE_MASK) | (*((UINT32 *)pValue) & RTP_STATUS_MASK)))
#define RTP_STATE_SET(pValue, value) (*((UINT32 *)pValue) |= \
                                      ((value) & RTP_STATE_MASK))
#define RTP_STATE_UNSET(pValue, value) (*((UINT32 *)pValue) = \
          (*((UINT32 *)pValue) & ((~(value)) & RTP_STATE_MASK)) | \
          (*((UINT32 *)pValue) & RTP_STATUS_MASK))

#define RTP_STATUS_PUT(pValue, value) (*((UINT32 *)pValue) = \
         (((value) & RTP_STATUS_MASK) | (*((UINT32 *)pValue) & RTP_STATE_MASK)))
#define RTP_STATUS_SET(pValue, value) (*((UINT32 *)pValue) |= \
                                      ((value) & RTP_STATUS_MASK))
#define RTP_STATUS_UNSET(pValue, value) (*((UINT32 *)pValue) = \
          (*((UINT32 *)pValue) & ((~(value)) & RTP_STATUS_MASK)) |  \
          (*((UINT32 *)pValue) & RTP_STATE_MASK))


/* Macro to get to the RTP_ID using the rtpNode pointer */

#define NODE_TO_RTP(pNode)	((RTP_ID)((long) pNode - sizeof(OBJ_CORE) - \
				 sizeof (KERNEL_RTP_CMN)))

/* RTP_ID_VERIFY() verifies the validity of a WIND_RTP object */

#define RTP_ID_VERIFY(rtpId)	rtpIdVerify ((rtpId))

/* RTP_SIG_RCB_GET obtains the signal data pointer for an RTP */

#define RTP_SIG_RCB_GET( rtpId ) (&((rtpId)->signalInfo))

/* get VM context ID and page manager of an RTP */

#define RTP_VM_CONTEXT_GET(rtp)	\
	((rtp)->kernelRtpCmn.vmContextId)

#define RTP_PAGE_MGR_GET(rtp)	\
	((rtp)->kernelRtpCmn.pgMgrId)


/*
 * RTP deletion safety macros used for RTP locking (SMP) and protection
 * during VM context switch (UP and SMP). The safety count is
 * incremented/decremented by 2, and the least significant bit is
 * set when there are deleter tasks pended.
 */

#define RTP_DELETE_SAFE_INIT(pRtp)	\
		(void) vxAtomic32Set (&(pRtp)->noDeleteCnt, 0)

#define RTP_DELETE_SAFE(pRtp)		\
		(void) vxAtomic32Add (&(pRtp)->noDeleteCnt, 2)

#define RTP_DELETE_PEND_SET(pRtp)	\
		(void) vxAtomic32Or (&(pRtp)->noDeleteCnt, 1)

#define RTP_IS_DELETE_SAFE(pRtp)	\
		(vxAtomic32Get (&(pRtp)->noDeleteCnt) > 1)

#define RTP_IS_DELETE_UNSAFE(pRtp)   (vxAtomic32Get (&(pRtp)->noDeleteCnt) < 2)

#define RTP_DELETE_UNSAFE(pRtp)						\
    do  {								\
	if (vxAtomic32Sub (&(pRtp)->noDeleteCnt, 2) == 3)		\
	    {								\
	    KERNEL_ENTER();						\
	    (void) vxAtomic32Set (&(pRtp)->noDeleteCnt, 0);		\
	    windPendQFlush (&(pRtp)->deleteQHead);			\
	    (void) KERNEL_EXIT();					\
	    }								\
	} while (0)

/*
 * RTP locking mechanism.
 *
 * Access to the WIND_RTP data structure must be done only after the WIND_RTP
 * object's protection semaphore has been acquired. It is usually necessary
 * to verify the validity of the WIND_RTP object before accessing its content.
 * Since a higher priority task may preempt the task trying to access the
 * WIND_RTP object and may delete this object, it is important that the
 * WIND_RTP object validation and locking be done in a protected manner.
 *
 * The set of macros below is used to ensure the proper functioning of the RTP
 * locking mechanism for UP and SMP builds. When the RTP object must be
 * validated before it is locked the standard way of using these macros is as
 * follows:
 *
 *    RTP_DELETE_SAFE_ENTER();
 *
 *    if (RTP_ID_VERIFY(rtpId) != OK)
 *        {
 *        RTP_DELETE_SAFE_ABORT();
 *        <set some error code>
 *        return ERROR;
 *        }
 *
 *    RTP_DELETION_DEFER (rtpId);
 *    RTP_LOCK (rtpId);
 *    RTP_DELETE_SAFE_EXIT (rtpId);
 *
 *    <Do something that manipulates the WIND_RTP data structure>
 *
 *    RTP_UNLOCK (rtpId);
 *
 * There is no need to verify the RTP object's validity in kernel routines that
 * are called only in the context of user tasks since the execution of these
 * tasks guarantees the validity of the RTP they belong to!  A simple RTP_LOCK()/
 * RTP_UNLOCK() pair may be used.  However, deletion of the RTP may have started
 * (though not completed), and so the return value from RTP_LOCK() must be
 * checked:
 *
 *    if (OK == RTP_LOCK (rtpId))
 *        {
 *        <Do something that manipulates the WIND_RTP data structure>
 *        RTP_UNLOCK (rtpId);
 *        }
 *    else
 *        {
 *        /@ clean up, report error to caller @/
 *        }
 *
 * In all other situations it is advised to use the RTP_VERIFIED_LOCK() or the
 * RTP_VERIFIED_LOCK_TASKID() macros.
 *
 * If the RTP_VERIFIED_LOCK() or the RTP_VERIFIED_LOCK_TASKID macros are used
 * they are paired to a call to RTP_UNLOCK() after the manipulation to the
 * WIND_RTP data structure is done.
 */

/*
 * RTP_LOCK locks the RTP semaphore without first verifying the RTP.
 * However RTP_LOCK does check if RTP deletion has started, and will fail
 * if a deleter task has been elected (or if the RTP has in fact been
 * deleted).  So check the return value.
 *
 * Note, it is preferable to call rtpLockWithCallerTcb() or
 * usrRtpLockWithCallerTcb(), if the current task's WIND_TCB pointer
 * is known and available in a local variable.
 *
 * usrRtpLockWithCallerTcb() may be called from code that might be
 * included in a VIP without INCLUDE_RTP enabled, whereas
 * rtpLockWithCallerTcb() should only be called from code requiring
 * user-space RTP support.
 */

#ifdef _WRS_CONFIG_RTP
#define RTP_LOCK(rtpId)         (usrRtpLock ((rtpId)))
#else
#define RTP_LOCK(rtpId)         (semTake ((rtpId)->semId, WAIT_FOREVER))
#endif

/* RTP_UNLOCK releases the protection semaphore of an RTP */

#define RTP_UNLOCK(rtpId)	((void) semGive ((rtpId)->semId))

/* RTP_VERIFIED_LOCK locks the RTP sem after verifying the object and state */

#define RTP_VERIFIED_LOCK(rtpId)	rtpVerifyAndLock ((rtpId))

/*
 * RTP_VERIFIED_LOCK_TASKID locks the owner RTP semaphore  of the given task
 * after verifying the task object,  the RTP object and the RTP state.
 */

#define RTP_VERIFIED_LOCK_TASKID(tid) rtpVerifyTaskIdAndLock ((tid))

/*
 * RTP_DELETE_SAFE_ENTER() indicates the beginning of a section of code during
 * which the task cannot be preempted by another task thus ensuring that the
 * RTP cannot be deleted.
 */

#ifdef _WRS_CONFIG_SMP
#define RTP_DELETE_SAFE_ENTER()	SPIN_LOCK_TASK_TAKE (&rtpObjProtect)
#else
#define RTP_DELETE_SAFE_ENTER()	TASK_LOCK()
#endif

/*
 * RTP_DELETE_SAFE_ABORT() indicates the end of the delete safe section but is
 * to be used _only_ when a failure happens before RTP_DELETION_DEFER() and
 * RTP_LOCK() can be called.
 */

#ifdef _WRS_CONFIG_SMP
#define RTP_DELETE_SAFE_ABORT()	SPIN_LOCK_TASK_GIVE (&rtpObjProtect)
#else
#define RTP_DELETE_SAFE_ABORT()	TASK_UNLOCK()
#endif

/*
 * RTP_DELETE_SAFE_EXIT() indicates the normal end of the delete safe section
 * and must be used after RTP_LOCK() has been called. This also re-instates the
 * right to delete the RTP (although the actual deletion of an RTP requires
 * to acquire the RTP protection semaphore first).
 */

#ifdef _WRS_CONFIG_SMP
#define RTP_DELETE_SAFE_EXIT(rtpId)			 		\
	do  {								\
	    RTP_DELETE_UNSAFE (rtpId);					\
	    TASK_UNSAFE();						\
	    } while (0)
#else
#define RTP_DELETE_SAFE_EXIT(rtpId)	TASK_UNLOCK()
#endif

/*
 * RTP_DELETION_DEFER() defers any deletion operation on the RTP until the
 * delete safe section is exited. It must be used prior to calling RTP_LOCK().
 */

#ifdef _WRS_CONFIG_SMP
#define RTP_DELETION_DEFER(rtpId)					\
	do  {								\
	    TASK_SAFE();						\
	    RTP_DELETE_SAFE (rtpId);					\
	    SPIN_LOCK_TASK_GIVE (&rtpObjProtect);			\
	    } while (0)
#else
#define RTP_DELETION_DEFER(rtpId)	/* do nothing on UP build */
#endif

/* typedefs */

/*
 * KERNEL_RTP_CMN: structure containing a collection of common elements
 * 		   between the kernelId and user RTPs.
 * vmContextId: VM context identifier.
 * sharedDataList: list of shared data regions mapped.
 * pWdbInfo: pointer to WDB info.
 *
 * NOTE: the vmContextId is stored directly in the kernelRtpCmn. This
 * is needed because arch and debug code (e.g. taskArchLib) needs a
 * unified way of getting the vmContextId of either an RTP or the
 * kernel. The RTP_VM_CONTEXT_GET() macro returns the value of this field.
 *
 * The kernel's vmContextId field is set in vmGlobalMapInit(), to make
 * sure the RTP_VM_CONTEXT_GET() macro works when no page manager
 * is created for it.
 *
 * For RTPs, the VM context is created during the page manager
 * initialization. The vmContextId field in kernelRtpCommon is a
 * copy from the page manager structure.
 */

typedef struct kernelRtpCommon
    {
    VM_CONTEXT_ID	vmContextId;	/* VM context ID */
    PAGE_MGR_ID		pgMgrId;	/* page manager ID */
    DL_LIST		sharedDataList;	/* List of the attached SD rgns */
    void *		pWdbInfo;	/* pointer to debugger specific info */
    } KERNEL_RTP_CMN;

/*
 * objCore: includes RTP name, ID
 * kernelRtpCmn: common between RTP and Kernel object
 * rtpNode: the rtp is linked to its parent when it becomes zombie via this node
 * semId:  semaphore to protect the RTP structure.
 * rtpStat (status): placeholder to represent the state and status of the RTP.
 * pPathName: Pointer to the executable file pathname string.
 * pArgv:Pointer to argv[] as supplied during creation.
 * pEnv: Pointer to envp[] as supplied during creation.
 * options: the options that are supplied during creation.
 * initTaskId: the task ID of the initial task
 * initTaskHandle: the initial task user handle ID, for user space.
 * symTabId: RTP's  symbol table.
 * binaryInfo: information about RTP code.
 * taskCnt: Number of tasks in the RTP.
 * fdTable: Pointer to shared FD table.
 * fdTableSize: number of entries in the FD table.
 * taskExitRtn: pointer to taskExit() in the RTP address space.
 * sigReturnRtn: Pointer to signal return routine in the RTP address space.
 * waitQHead: q of tasks waiting for RTP to die - to support waitpid().
 * signalInfo: RTP global Signal control block.
 * pSigQFreeHead: pointer to free pool of sigpend nodes (sigqueue).
 * sigwaitQ: list of tasks waiting for signals.
 * rtpChildList: list of RTP child and zombie RTPs attached to this RTP.
 * parentRtpId: ID of the RTP which created this RTP. This value is not updated
 *              when the parent RTP ends.
 * parentTaskId: ID of the task which created this RTP. This value is not
 *               updated when the parent task ends.
 * objMgtSemId: object management semaphore lock.
 * mstrHandleTbl: per RTP master handle table.
 * lockTaskId: ID of the task which locked the RTP.
 * rtpHandleId: handle ID of this RTP, for abstraction in user space.
 * pRtpVar: RTP specific variables, for SL support.
 * rtpShlNodeList: list of shared library references.
 * rtpShlNodeListMutex: mutex semaphore protecting the rtpShlNodeList list.
 * cpuTimeInfo: CPU time used by the RTP so far.
 * pTraceData: pointer to data for POSIX trace: Hash table and trace list head.
 * noDeleteCnt: keeps count of tasks about to lock the WIND_RTP structure after
 *              it has been verified. Any RTP deletion is postponed then (SMP).
 */

typedef struct wind_rtp
    {
    OBJ_CORE		objCore;	/* object management                  */
    KERNEL_RTP_CMN	kernelRtpCmn;	/* common between RTP and Kernel obj  */
    DL_NODE		rtpNode;	/* link of this zombie to its parent  */
    SEM_ID		semId;		/* semaphore to protect this struct   */
    WIND_TCB *          pDeleterTcb;    /* NULL, or deleter task ID           */
    char *		pPathName;	/* pointer to pathname of RTP         */
    char **		pArgv;		/* pointer to RTP's arguments         */
    char **		pEnv;		/* pointer to RTP's environment       */
    int			status;	        /* state and status of the RTP        */
    UINT32		options;	/* option bits, e.g. debug, symtable  */
    void *		entrAddr;	/* entry point of ELF file            */
    TASK_ID		initTaskId;	/* the RTP's initial task ID          */
#ifdef	_WRS_CONFIG_OSTOOLS
    SYMTAB_ID		symTabId;	/* symbol table                       */
#endif	/* _WRS_CONFIG_OSTOOLS */
#ifdef	_WRS_CONFIG_LOADER
    RTP_IMAGE_INFO	binaryInfo;	/* information about RTP code	      */
#endif	/* _WRS_CONFIG_LOADER */
    OBJ_HANDLE 		initTaskHandle;	/* the initial task user handle ID    */
    INT32		taskCnt;	/* number of tasks in the RTP         */
    Q_HEAD		deleteQHead;	/* q of tasks waiting the RTP delete  */
    SEM_ID		fdTableSem;     /* mutex to protect the FD table      */
    void *		fdTable;	/* file descriptor table              */
    size_t		fdTableSize;	/* number of entries in fd table      */
    char *              defPath;        /* default path for I/O               */
    size_t              defPathLen;     /* length of default path buffer      */
    void             (* taskExitRtn)(int);
                                        /* Pointer to task exit routine       */
    void *              sigReturnRtn;   /* Pointer to signal return routine   */
    RTP_SIG_CB		signalInfo;	/* Signal control block               */
    struct sigpend *	pSigQFreeHead;	/* ptr to free pool of sigpends       */
    DL_LIST		sigwaitQ;	/* tasks waiting for signals          */
    DL_LIST		rtpChildList;	/* list of Child RTP zombies          */
    struct wind_rtp *	parentRtpId;	/* RTP ID of this RTP's parent	      */
    TASK_ID 		parentTaskId;	/* RTP's creator task Id              */
    SEM_ID		objMgtSemId;    /* object management lock             */
    MASTER_HANDLE_TABLE mstrHandleTbl;  /* per RTP master handle table	      */
    TASK_ID 		lockTaskId;	/* the task which has the RTP locked  */
    struct rtp_var *	pRtpVar;	/* RTP specific variables             */
    DL_LIST		rtpShlNodeList;	/* list of shared library references  */
    SEM_ID		rtpShlNodeListMutex; /* lock for rtpShlNodeList       */

    /* extensions for plug-in schedulers */

    UINT64              cpuTimeInfo[2]; /* sched extension - CPU time info    */
    void *              pSchedInfo;     /* ptr to scheduler info              */

    struct trace_data * pTraceData;     /* POSIX trace support                */

    OBJ_HANDLE		rtpHandleId;	/* handle ID of this RTP              */
    OBJ_HANDLE      parentRtpHandle; /* handle ID of parent RTP */
    atomic32_t		noDeleteCnt;	/* don't delete RTP if > 1 (SMP)      */
    Q_HEAD		rtpWaitPendQ;   /* pend queue for kernel tasks waiting*/
                                        /* for this RTP to finish execution   */

#ifdef _WRS_CONFIG_USER_IDENTIFICATION_INHERITANCE
    void *              pCredentials;   /* RTP's credentials (identity)       */
#endif /* _WRS_CONFIG_USER_IDENTIFICATION_INHERITANCE */

#ifdef _WRS_CONFIG_FILE_CREATION_MASK
    mode_t              cmask;      /* mask for file creation               */
#endif /* _WRS_CONFIG_FILE_CREATION_MASK */

    int                 reserved1;    /* possible WRS extension               */
    long                reserved2;    /* possible WRS extension               */
    long                spare1;       /* possible user extension              */
    long                spare2;       /* possible user extension              */
    long                spare3;       /* possible user extension              */
    long                spare4;       /* possible user extension              */
    } WIND_RTP;

/* small footprint zombie data struct for dead child RTP, chained to parent */

typedef struct zombieRtp
    {
    DL_NODE		rtpNode;	/* link of this zombie to its parent */
    WIND_RTP * 		zombieId;	/* RTP ID of this RTP's parent */
    OBJ_HANDLE	 	zombieHandleId;	/* handle ID of this RTP's parent */
    int			exitStatus;	/* exit/termination status */
    } ZOMBIE_RTP;

/* typedef's for RTP create/delete hook functions */

typedef STATUS (* RTP_PRE_CREATE_HOOK)		(const char *, const char *[],
						 const char *[], int, size_t,
						 int, int);

typedef STATUS (* RTP_POST_CREATE_HOOK)		(const RTP_ID);

typedef void   (* RTP_INIT_COMPLETE_HOOK)	(const RTP_ID);

typedef void   (* RTP_DELETE_HOOK)		(const RTP_ID, const int exitCode);

/*
 * Since the size of RTP_DESC is different in user & kernel space for 64bit
 * builds, we must have two different definitions.  In this definition,
 * we want the size to match with the size in the user-side so we define the
 * task id and rtp id as being an object handles.
 */

typedef struct
    {
    RTP_DESC_FIELDS(OBJ_HANDLE, OBJ_HANDLE)
    } RTP_USER_DESC;

/* funcBind pointers */

extern STATUS	  (*_func_rtpDelete)	   (RTP_ID rtpId, int options,
					    int delStatus);
extern STATUS	  (*_func_rtpIdVerify)	   (RTP_ID rtpId);
extern RTP_ID	  (*_func_rtpSpawn)	   (const char * rtpFileName,
					    const char ** argv,
	   				    const char ** envp, int priority,
					    size_t uStackSize, int options,
					    int taskOptions);
extern BOOL	  (*_func_rtpShow)	   (char * rtpNameOrId, int level);
extern OBJ_HANDLE (*_func_rtpHandleIdGet)  (RTP_ID rtpId);
#ifdef	_WRS_CONFIG_OSTOOLS
extern SYMTAB_ID  (*_func_rtpSymTblIdGet)  (RTP_ID rtpId);
#endif	/* _WRS_CONFIG_OSTOOLS */
extern STATUS 	  (*_func_rtpVerifiedLock) (RTP_ID rtpId);
extern STATUS (* _func_rtpDeletionDeferEnable) (WIND_RTP * pRtpId);
extern void   (* _func_rtpDeletionDeferDisable) (WIND_RTP * pRtpId);
extern STATUS	  (*_func_rtpSdUnmapAll)   (RTP_ID rtpId);

extern STATUS (*_func_rtpPreCreateHookAdd)	 (RTP_PRE_CREATE_HOOK hook,
						  BOOL addToHead);
extern STATUS (*_func_rtpPreCreateHookDelete)	 (RTP_PRE_CREATE_HOOK hook);
extern STATUS (*_func_rtpPostCreateHookAdd)	 (RTP_POST_CREATE_HOOK hook,
						  BOOL addToHead);
extern STATUS (*_func_rtpPostCreateHookDelete)	 (RTP_POST_CREATE_HOOK hook);
extern STATUS (*_func_rtpInitCompleteHookAdd)	 (RTP_INIT_COMPLETE_HOOK hook,
						  BOOL addToHead);
extern STATUS (*_func_rtpInitCompleteHookDelete) (RTP_INIT_COMPLETE_HOOK hook);
extern STATUS (*_func_rtpDeleteHookAdd)		 (RTP_DELETE_HOOK hook,
						  BOOL addToHead);
extern STATUS (*_func_rtpDeleteHookDelete)	 (RTP_DELETE_HOOK hook);


extern STATUS (*_func_rtpShlSymbolsRegister)	(char * filePath, RTP_ID rtpId,
						 SHL_ID shlId, void * textBase,
						 void * database,
						 UINT32 options);
extern STATUS (*_func_rtpShlSymbolsUnregister)	(RTP_ID rtpId, SHL_ID shlId,
						 UINT32 scope);

extern STATUS (*_func_rtpShlDeleteAll)		(RTP_ID rtpId);
extern STATUS (*_func_rtpShlInfoGet)		(SHL_ID shlId, RTP_ID rtpId,
						 RTP_SHL_INFO * pRtpShlInfo);
extern STATUS (*_func_rtpVarAdd)		(RTP_VAR_ADDR pVar,
						 RTP_VAR value, RTP_ID rtpId);
extern STATUS (*_func_rtpTaskEach)     (RTP_ID rtpId,
					BOOL (*routine) (RTP_ID rtpId,
							 TASK_ID taskId,
							 _Vx_usr_arg_t arg),
					_Vx_usr_arg_t routineArg,
					TASK_ID * pLastTask);
extern void   (*_func_rtpShlOpenHook) (SHL_ID shlId, RTP_ID rtpId);
extern void   (*_func_rtpShlCloseHook)(SHL_ID shlId, RTP_ID rtpId);

/* externals */

extern int		        rtpHookTblSize;
extern RTP_PRE_CREATE_HOOK *    pRtpPreCreateHookTbl;
extern RTP_POST_CREATE_HOOK *   pRtpPostCreateHookTbl;
extern RTP_INIT_COMPLETE_HOOK * pRtpInitCompleteHookTbl;
extern RTP_DELETE_HOOK *        pRtpDeleteHookTbl;

/* function declarations */

extern RTP_ID _rtpSpawn	              (const char * rtpFileName,
                                       const char ** argv,
                                       const char ** envp, int priority,
                                       size_t uStackSize, int options,
                                       int taskOptions,
                                       OBJ_HANDLE * pRtpHandle);

extern STATUS rtpDeletionDeferEnable  (WIND_RTP * pRtpId);
extern void   rtpDeletionDeferDisable (WIND_RTP * pRtpId);
extern STATUS rtpLockWithCallerTcb    (WIND_RTP * pRtpId, WIND_TCB * pCallerTcb);
extern STATUS rtpVerifyAndLock        (WIND_RTP * pRtpId);
extern STATUS rtpVerifyTaskIdAndLock  (WIND_TCB * tid);
extern STATUS rtpIdVerify             (RTP_ID rtpId);
extern STATUS rtpHookLibInit          (int tblSize);
extern STATUS rtpPreCreateHookAdd     (RTP_PRE_CREATE_HOOK hook,
				       BOOL addToHead);
extern STATUS rtpPreCreateHookDelete  (RTP_PRE_CREATE_HOOK hook);
extern STATUS rtpPostCreateHookAdd    (RTP_POST_CREATE_HOOK hook,
				       BOOL addToHead);
extern STATUS rtpPostCreateHookDelete (RTP_POST_CREATE_HOOK hook);
extern STATUS rtpInitCompleteHookAdd  (RTP_INIT_COMPLETE_HOOK hook,
				       BOOL addTohead);
extern STATUS rtpInitCompleteHookDelete (RTP_INIT_COMPLETE_HOOK hook);
extern STATUS rtpDeleteHookAdd        (RTP_DELETE_HOOK hook, BOOL addTohead);
extern STATUS rtpDeleteHookDelete     (RTP_DELETE_HOOK hook);
extern OBJ_HANDLE rtpHandleIdGet      (RTP_ID rtpId);
extern STATUS rtpLibInit 	      (int rtpHookTblSize,
                                       int syscallHookTblSize,
                                       int rtpSignalQueueSize,
                                       size_t defExcStkOverflowSize,
                                       size_t defExecStkOverflowSize,
                                       size_t defExecStkUnderflowSize,
                                       unsigned int maxFdNum,
                                       BOOL rtpMemFill);
extern void   rtpShowInit 	      (void);
extern STATUS rtpMemShow              (char * rtpNameOrId, int level);
extern void   rtpHookShow             (void);
extern STATUS rtpShellCmdInit         (void);
extern STATUS rtpTaskExitRegister     (VOIDFUNCPTR exitRtnAdrs);
extern RTP_ID rtpIdFigure             (char * rtpNameOrId);
extern STATUS rtpScLibInit            (void);

extern STATUS rtpAuxvLibInit	      (void);
extern auxv_t * rtpAuxvAdd	      (auxv_t * pAuxv);
extern size_t rtpAuxvSizeGet	      (void);
extern void   rtpAuxvCopy	      (char * stack, size_t size);

extern void   memRtpLibInit	      (UINT rtpHeapInitSize,
				       UINT rtpHeapOptions);

extern STATUS rtpVarInit              (void);
extern void   rtpSysctlRegister       (void);
extern void   rtpWaitQInit            (RTP_ID rtpId);
extern void   rtpWaitQFlush 	      (RTP_ID rtpId, int delStatus);

extern STATUS usrRtpLock              (WIND_RTP * pRtpId);
extern STATUS usrRtpLockWithCallerTcb (WIND_RTP * pRtpId, WIND_TCB * pCallerTcb);

#ifdef __cplusplus
}
#endif

#else	/* _ASMLANGUAGE */

#ifndef _WRS_CONFIG_LP64

/*
 * old WIND_RTP element offset macros - these must be in an ASM section due to
 * a circular dependency when compiling offsets.c
 *
 * WARNING: the old offset macros are provided temporarily only for a
 * transitionary phase.  They will be removed once existing references are
 * updated to use the dynamically generated offsets.
 */

#include <private/offsetMacrosP.h>

#define _WRS_WIND_RTP_LOCK_TASK_ID	WIND_RTP_lockTaskId_OFFSET
#endif /* _WRS_CONFIG_LP64 */

#endif	/* _ASMLANGUAGE */

#endif	/* __INCrtpLibPh */
