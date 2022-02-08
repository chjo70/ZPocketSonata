/* taskLibCommon.h - VxWorks tasking library common (user/kernel) definitions */

/*
 * Copyright (c) 2003-2010, 2012-2015, 2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify, or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
20may17,dlk  added taskDelayEx() / taskSafeTcbGet() / taskSafeTcb() /
             taskUnsafeTcb() / taskDoom() / taskWindTcbCurrent() (F5593)
17aug15.h_k  changed VX_PRIVATE_UMASK to 0x0400 to solve a conflict between
             VX_DEALLOC_TCB. (V7COR-3479)
08jul15,rr   Updated data type of stackMargin variables as ssize_t (V7RAD-305)
20apr15,txu  Added support for task-specific umask(). (US57390)
06aug14,pad  Added td_uid and td_gid fields to TASK_DESC (US40207)
14jan14,vhe  removed reference to SIMPENTIUM build
21feb13,cww  Added definition of errno S_taskLib_STOPPED_DELETE_SAFE_TASK
             (part of fix for WIND00402989).
15jun12,jpb  Defect# WIND00354653.  Backed out removal of VX_PRIVATE_ENV
             from VX_USR_TASK_OPTIONS_BASE.
15feb12,jpb  #Defect WIND00308068.  Removed VX_PRIVATE_ENV from user options.
09nov10,zl   added TASK_ID_NULL definition
16jun10,pcs  Change the data types of ticks and td_delay from an int to
             _Vx_ticks_t
27may10,pad  Moved extern C statement after include statements.
07jan10,jpb  Removed user-side definitions which are now the same as kernel
17dec09,jpb  Updated sharing of TASK_DESC structure.
16mar09,zl   fixed taskIdDefault() to return TASK_ID.
02mar09,pcs  Updated to limit the taskLibXXX API signature changes to the
             kernel, to avoid usr side build errors.
27feb09,pcs  revert back the signature change of taskStackSizeGet.
03feb09,pcs  Updated to add support for the LP64 data model.
20jan09,jb   Adding x86_64 Support
28aug08,nld  added taskIsDelayed()
13jul07,rps  added errno S_taskLib_ILLEGAL_STACK_INFO
14may07,jmg  Moved taskCpuAffinityGet() and taskCpuAffinitySet() to here.
08feb07,lei  added td_affinity to TASK_DESC
18jan07,dlk  Added taskStackSizeGet() prototype.
11aug06,lei  added td_cpuIndex to TASK_DESC for SMP; removed _WRS_VX_SMP
10jul06,jpb  Updated for POSIX namespace conformance.
             Changed C preprocessor macro CPU_FAMILY to _VX_CPU_FAMILY.
06jul06,jmg  Added extern declaration for taskPriNormalget() as part of
             Defect #WIND00045158
07feb06,kk   renamed taskOpenExt to taskOpenWithGuard
13dec05,jln  added taskOpenExt
18may05,rec  add hook for coprocColdfire.h
01apr05,kk   remove old coprocessor options, now all archs PAL'ifies coprocs
28sep04,aeg  added td_excStackCurrent to TASK_DESC.
27sep04,tam  updated VX_NO_STACK_PROTECT documentation
22sep04,md   added taskSafe()/taskUnsafe() prototype.
03aug04,scm  add hook for coprocArm.h...
20may04,dcc  added taskUnlink() prototype.
05may04,cjj  added VX_USR_TASK_OPTIONS.
29apr04,h_k  added SH coprocessor support.
22apr04,dcc  added inclusion of objLib.h
25mar04,dbt  Added SIMPENTIUM support.
13apr04,zmm  Add Pentium coprocessor.
29mar04,dcc  added taskClose() prototype. Moved VX_TASK_OBJ_OWNER option
             bit to kernel taskLib.h
29mar04,aeg  updated taskOpen() function prototype.
22jan04,aeg  added coprocessor related task option bits.
25nov03,aeg  added S_taskLib_ILLEGAL_OPERATION errno;
             changed taskOpen() function prototype.
14nov03,kk   added VX_NO_STACK_PROTECT option
31oct03,aeg  added taskIsPended().
10oct03,pcm  added td_pExcStackStart; removed td_pStackLimit
09oct03,aeg  added S_taskLib_NO_TCB errno.
15sep03,kk   added exception stack info and RTP id
12sep03,aeg  added S_taskLib_ILLEGAL_OPTIONS errno.
10sep03,dcc  moved more function prototypes from taskLib.h
09sep03,dcc  added #ifndef	_ASMLANGUAGE directives.
05sep03,dcc  added function prototypes.
19aug03,aeg  written based on v05b of kernel version of taskLib.h
*/

#ifndef __INCtaskLibCommonh
#define __INCtaskLibCommonh

#include <vwModNum.h>
#include <eventLibCommon.h>
#include <objLib.h>

/* generic status codes */

#define S_taskLib_NAME_NOT_FOUND		(M_taskLib | 101)
#define S_taskLib_TASK_HOOK_TABLE_FULL		(M_taskLib | 102)
#define S_taskLib_TASK_HOOK_NOT_FOUND		(M_taskLib | 103)
#define S_taskLib_TASK_SWAP_HOOK_REFERENCED	(M_taskLib | 104)
#define S_taskLib_TASK_SWAP_HOOK_SET		(M_taskLib | 105)
#define S_taskLib_TASK_SWAP_HOOK_CLEAR		(M_taskLib | 106)
#define S_taskLib_TASK_VAR_NOT_FOUND		(M_taskLib | 107)
#define S_taskLib_TASK_UNDELAYED		(M_taskLib | 108)
#define S_taskLib_ILLEGAL_PRIORITY		(M_taskLib | 109)
#define S_taskLib_ILLEGAL_OPTIONS		(M_taskLib | 110)
#define S_taskLib_NO_TCB			(M_taskLib | 111)
#define S_taskLib_ILLEGAL_OPERATION		(M_taskLib | 112)
#define S_taskLib_ILLEGAL_STACK_INFO            (M_taskLib | 113)
#define S_taskLib_STOPPED_DELETE_SAFE_TASK      (M_taskLib | 114)

/* miscellaneous */

#define VX_TASK_NAME_LENGTH	31	/* max length of name in TASK_DESC */

/*
 * Task option bits.  BE SURE to modify either of the
 * VX_USR_TASK_OPTIONS_BASE or VX_USR_TASK_OPTIONS definitions
 * below when modifying/adding individual task options.
 *
 * The VX_PRIVATE_ENV option is obsoleted for RTP-side tasks since the
 * corresponding feature is not available in the RTP environment. Its usage
 * remains allowed for now for backward compatibility at compile time.
 */


#define VX_PRIVATE_ENV		0x0080	/* 1 = private environment variables */
#define VX_NO_STACK_FILL	0x0100	/* 1 = avoid stack fill of 0xee */
#define VX_PRIVATE_UMASK	0x0400  /* 1 = private file creation mode mask */
#define VX_TASK_NOACTIVATE	0x2000  /* taskOpen() does not taskActivate() */
#define VX_NO_STACK_PROTECT	0x4000  /* no over/underflow stack protection,*/
					/* stack space remains executable     */

/* define for all valid user task options */

#define VX_USR_TASK_OPTIONS_BASE    (VX_PRIVATE_ENV		| \
				     VX_NO_STACK_FILL 		| \
				     VX_TASK_NOACTIVATE		| \
				     VX_NO_STACK_PROTECT    | \
				     VX_PRIVATE_UMASK)

/*
 * All 6.0 architectures have PAL'ified the coprocessor layer by specifying
 * _WRS_PAL_COPROC_LIB.  The definition of the coprocessor task options
 * (e.g. VX_FP_TASK, VX_DSP_TASK, VX_ALTIVEC_TASK) are now defined in
 * the architecture file target/h/arch/<arch>/coproc<Arch>.h.
 */

#define VX_COPROC1_TASK     	0x01000000
#define VX_COPROC2_TASK		0x02000000
#define VX_COPROC3_TASK     	0x04000000
#define VX_COPROC4_TASK     	0x08000000
#define VX_COPROC5_TASK     	0x10000000
#define VX_COPROC6_TASK     	0x20000000
#define VX_COPROC7_TASK     	0x40000000
#define VX_COPROC8_TASK     	0x80000000

/* define for all valid user task options */

#define VX_USR_TASK_OPTIONS    (VX_USR_TASK_OPTIONS_BASE	| \
				VX_COPROC1_TASK			| \
				VX_COPROC2_TASK			| \
				VX_COPROC3_TASK			| \
				VX_COPROC4_TASK			| \
				VX_COPROC5_TASK			| \
				VX_COPROC6_TASK			| \
				VX_COPROC7_TASK			| \
				VX_COPROC8_TASK)

/* Indicates that the TASK_ID returned by taskSpawn() is not valid. */

#define TASK_ID_ERROR ((TASK_ID)(-1))

/* Indicates that the TASK_ID returned by taskOpen() is not valid. */

#define TASK_ID_NULL ((TASK_ID)(0))

/* taskDelayEx() flag */
#define TASK_DELAY_EX_DELETION_WAKEUP 1

#if (_VX_CPU_FAMILY == _VX_PPC)
#include <arch/ppc/coprocPpc.h>
#endif /* (_VX_CPU_FAMILY == _VX_PPC) */

#if (_VX_CPU_FAMILY == _VX_I80X86)
#include <arch/i86/coprocI86.h>
#endif /* (_VX_CPU_FAMILY == _VX_I80X86) */

#if (_VX_CPU_FAMILY == _VX_ARM)
#include <arch/arm/coprocArm.h>
#endif /* (_VX_CPU_FAMILY == _VX_ARM) */

#if (_VX_CPU_FAMILY == _VX_MIPS)
#include <arch/mips/coprocMips.h>
#endif /* (_VX_CPU_FAMILY == _VX_MIPS) */

#if (_VX_CPU_FAMILY == _VX_SH)
#include <arch/sh/coprocSh.h>
#endif /* (_VX_CPU_FAMILY == _VX_SH) */

#if (_VX_CPU_FAMILY == _VX_SIMNT)
#include <arch/simnt/coprocSimnt.h>
#endif /* (_VX_CPU_FAMILY == _VX_SIMNT) */

#if (_VX_CPU_FAMILY == _VX_SIMLINUX)
#include <arch/simlinux/coprocSimlinux.h>
#endif /* (_VX_CPU_FAMILY == _VX_SIMLINUX) */

#if (_VX_CPU_FAMILY == _VX_SIMSPARCSOLARIS)
#include <arch/simsolaris/coprocSimsolaris.h>
#endif /* (_VX_CPU_FAMILY == _VX_SIMSPARCSOLARIS) */

#if (_VX_CPU_FAMILY == _VX_COLDFIRE)
#include <arch/coldfire/coprocColdfire.h>
#endif /* (_VX_CPU_FAMILY == _VX_COLDFIRE) */

#ifdef __cplusplus
extern "C" {
#endif

/* typedefs */

#ifndef	_ASMLANGUAGE

/*
 * Since the size of TASK_DESC is different in user & kernel space for 64bit
 * builds, we must have two different definitions for the kernel-side.  In this
 * definition of TASK_DESC, On the kernel side, we want to define the task id
 * and the rtp id as being id's.  On the user-side, we want to define the
 * task id and the rtp id as being handles.  The other kernel definition is
 * located in taskULibP.h named TASK_UDESC.
 *
 * The ordering of the structure must stay the same as we rely on it in the
 * system call handling.  If fields are added to this structure or re-ordered,
 * it must also be reflected in the objInfoGet system call.
 */

#define TASK_DESC_FIELDS(tidType, rtpIdType)						\
    tidType		td_id;		/* task id */					\
    rtpIdType           td_rtpId;         /* RTP owning the task */			\
    char *              td_pExcStackBase; /* exception stack base */			\
    char *              td_pExcStackEnd;  /* exception stack end */			\
    char *              td_pExcStackStart;/* exception stack start */			\
    FUNCPTR		td_entry;	/* original entry point of task */		\
    char *		td_sp;		/* saved stack pointer */			\
    char *		td_pStackBase;	/* the bottom of the stack */			\
    char *		td_pStackEnd;	/* the actual end of the stack */		\
    int			td_options;	/* task option bits (see below) */		\
    int			td_priority;	/* task priority */				\
    int			td_status;	/* task status */				\
    int			td_errorStatus;	/* most recent task error status */		\
    size_t		td_stackSize;	/* size of stack in bytes */			\
    size_t		td_stackCurrent;/* current stack usage in bytes */		\
    size_t		td_stackHigh;	/* maximum stack usage in bytes */		\
    ssize_t		td_stackMargin;	/* current stack margin in bytes */		\
    _Vx_ticks_t		td_delay;	/* delay/timeout ticks */			\
    EVENTS_DESC		td_events;	/* VxWorks events information */		\
    char		td_name [VX_TASK_NAME_LENGTH+1];  /* name of task */		\
    size_t              td_excStackSize;  /* size of exception stack in bytes */	\
    size_t              td_excStackHigh;  /* exception stack max usage */		\
    ssize_t             td_excStackMargin;/* exception stack margin */			\
    size_t		td_excStackCurrent;/* current exc stack usage (bytes) */	\
    int                 td_cpuIndex;       /* cpu index running on (if any) */		\
    cpuset_t            td_affinity;       /* task affinity */                          \
    uid_t               td_uid;            /* task's user ID */                         \
    gid_t               td_gid;            /* task's group ID */

typedef struct
    {
    TASK_DESC_FIELDS(TASK_ID, RTP_ID)
    } TASK_DESC;

/* function declarations */

extern TASK_ID	taskSpawn 	(char * name, int priority, int options,
			   	 size_t stackSize, FUNCPTR entryPt,
                                 _Vx_usr_arg_t arg1, _Vx_usr_arg_t arg2,
                                 _Vx_usr_arg_t arg3, _Vx_usr_arg_t arg4,
                                 _Vx_usr_arg_t arg5, _Vx_usr_arg_t arg6,
                                 _Vx_usr_arg_t arg7, _Vx_usr_arg_t arg8,
                                 _Vx_usr_arg_t arg9, _Vx_usr_arg_t arg10);
extern TASK_ID	taskCreate 	(char * name, int priority, int options,
			         size_t stackSize, FUNCPTR entryPt,
                                 _Vx_usr_arg_t arg1,  _Vx_usr_arg_t arg2,
                                 _Vx_usr_arg_t arg3, _Vx_usr_arg_t arg4,
                                 _Vx_usr_arg_t arg5, _Vx_usr_arg_t arg6,
                                 _Vx_usr_arg_t arg7, _Vx_usr_arg_t arg8,
                                 _Vx_usr_arg_t arg9, _Vx_usr_arg_t arg10);
extern STATUS	taskActivate 	(TASK_ID tid);
extern STATUS	taskDelete 	(TASK_ID tid);
extern STATUS	taskDeleteForce (TASK_ID tid);
extern STATUS	taskSuspend 	(TASK_ID tid);
extern STATUS	taskResume 	(TASK_ID tid);
extern STATUS	taskRestart 	(TASK_ID tid);
extern STATUS   taskPriNormalGet(TASK_ID tid, int *pPriNormal);
extern STATUS	taskPrioritySet (TASK_ID tid, int newPriority);
extern STATUS	taskPriorityGet (TASK_ID tid, int * pPriority);
extern STATUS	taskStackSizeGet (TASK_ID tid, size_t * pStackSize);
extern char *	taskName 	(TASK_ID tid);
extern TASK_ID	taskNameToId 	(char * name);
extern STATUS	taskIdVerify 	(TASK_ID tid);
extern TASK_ID	taskIdSelf 	(void);
extern TASK_ID	taskIdDefault 	(TASK_ID tid);
extern BOOL	taskIsReady 	(TASK_ID tid);
extern BOOL	taskIsSuspended (TASK_ID tid);
extern BOOL	taskIsPended	(TASK_ID tid);
extern BOOL	taskIsDelayed	(TASK_ID tid, _Vx_ticks_t * pDelayTicks);
extern STATUS	taskInfoGet 	(TASK_ID tid, TASK_DESC * pTaskDesc);
extern STATUS	taskOptionsGet 	(TASK_ID tid, int * pOptions);
extern STATUS	taskDelay 	(_Vx_ticks_t ticks);
extern STATUS	taskDelayEx 	(_Vx_ticks_t ticks, UINT32 flags);
extern TASK_ID	taskOpen 	(const char * name, int priority, int options,
			   	 int mode, char * pStackBase, size_t stackSize,
				 void * context, FUNCPTR entryPt,
				 _Vx_usr_arg_t arg1, _Vx_usr_arg_t arg2,
				 _Vx_usr_arg_t arg3, _Vx_usr_arg_t arg4,
				 _Vx_usr_arg_t arg5, _Vx_usr_arg_t arg6,
				 _Vx_usr_arg_t arg7, _Vx_usr_arg_t arg8,
				 _Vx_usr_arg_t arg9, _Vx_usr_arg_t arg10);
extern STATUS 	taskClose	(TASK_ID  tid);
extern STATUS 	taskUnlink	(const char * name);
extern STATUS	taskSafe	(void);
extern STATUS	taskUnsafe	(void);
extern STATUS 	taskCpuAffinitySet	(TASK_ID tid, cpuset_t newAffinity);
extern STATUS 	taskCpuAffinityGet	(TASK_ID tid, cpuset_t* pAffinity);

struct windTcb; /* struct windTcb is opaque/abstract here */

extern struct windTcb * taskWindTcbCurrent (void);
extern struct windTcb * taskSafeTcbGet (void);
extern void taskSafeTcb (struct windTcb * pCurrentTcb);
extern void taskUnsafeTcb (struct windTcb * pCurrentTcb);
extern void taskDoom (void);

/***************************************************************************
*
* taskWindTcbToTaskId - conviert pointer to TCB to TASK_ID
*
* This routine is specifically intended to be supported for both
* kernel and user space, and to convert a pointer to a WIND_TCB to
* a TASK_ID.  If the input pointer <pTcb> is NULL, TASK_ID_NULL
* is returned.
*
* RETURNS: The TASK_ID corresponding to the WIND_TCB pointer <pTcb>.
* \NOMANUAL
*/

_WRS_INLINE TASK_ID taskWindTcbToTaskId
    (
    struct windTcb * pTcb
    )
    {
    return (TASK_ID)pTcb;
    }

#endif /* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCtaskLibCommonh */
