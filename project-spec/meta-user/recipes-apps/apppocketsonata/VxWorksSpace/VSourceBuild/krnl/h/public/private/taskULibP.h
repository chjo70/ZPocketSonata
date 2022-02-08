/* taskLibP.h - VxWorks user tasking library private interface header */

/*
 * Copyright (c) 2003-2010, 2012, 2015, 2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
28mar17,dlk  move stackSize and version into kernel portion of WIND_UTCB;
             remove explicit field offsets; bump WIND_UTCB_VERSION (V7COR-4763)
29oct15,rr   Added stackSize variable to WIND_TCB (F3906)
13may15,h_k  removed safeDeleteFlag from WIND_TCB in user land. (V7COR-2631)
27sep12,zl   removed obsolete comment and type related to task lists.
18sep12,zl   re-implement SMP version of TASK_TCB_CURRENT_GET() using
             syscall (WIND00371412).
30sep10,gls  added TASK_IS_LAST_TASK() (WIND00234934)
27jul10,jpb  Changed type of exit code.
02jul10,pcs  change data type of delayTick from an int to _Vx_ticks_t.
24jun10,jpb  Changed guardSize type from ssize_t to size_t.
18may10,pad  Moved extern C statement after include statements.
26apr10,gls  fixed race condition in task list (WIND00209197)
31mar10,gls  renamed taskRtpLock/Unlock() and TASK_RTPLOCK/UNLOCK()
04mar10,zl   use windTcbCurrent task variable for 64-bit UP.
28jan10,jpb  Updated TASK_TCB_CURRENT_GET for LP64.
17dec09,jpb  Updated for LP64 adaptation.
01sep08,nld  added TASK_DELAY_INFO structure
19jun08,zl   replaced _WRS_ASM() with VX_CODE_BARRIER()
27apr07,gls  added __thread support
04apr07,gls  added taskTcbGet() and taskTcbCurrentGet() definitions
07feb06,kk   moved taskOpenWithGuard() from taskLibCommon.h to here
03jun05,kk   fix syntax error (SPR# 109861)
22sep04,md   CI changes
05may04,cjj  moved errorStatus from WIND_TCB to WIND_UTCB.
29apr04,dcc  added WIND_UTCB_LOCK_CNT and WIND_UTCB_REL_CPU offsets.
29mar04,aeg  added argv pointer to WIND_TCB.
27oct03,md   added kernel/user tcb separation
08oct03,aeg  added definitions for task create/delete hooks;
             moved TASK_UXXX() macros from taskLib.h
24sep03,aeg  written
*/

#ifndef __INCtaskLibPh_u
#define __INCtaskLibPh_u

#include <vxWorks.h>
#include <vsbConfig.h>

#define	WIND_UTCB_VERSION	2

#if !defined(_WRS_KERNEL)

#include <semLib.h>
#include <tlsLib.h>		/* TLS_KEY */
#include <sllLib.h>
#include <vxAtomicLib.h>
#include <private/vxSysInfoCommonP.h>

/* defines */

#define VX_MAX_TASK_CREATE_RTNS 16
#define VX_MAX_TASK_DELETE_RTNS 16

#endif /* _WRS_KERNEL */

/* flag to indicate task is safe and pended to be deleted */

#define USER_TASK_SAFE_DELETE_PEND_FLAG	1

/* task safe count incremental value */

#define USER_TASK_SAFE_INC_VALUE	2

/* offsets */

#define WIND_UTCB_LOCK_CNT	0x08 /* (WIND_UTCB *)->kernel.lockCnt */
#define WIND_UTCB_REL_CPU	0x0c /* (WIND_UTCB *)->kernel.relinquishCpu */

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _ASMLANGUAGE

/* typedefs */

/*
 * The user level TCB is available in both the kernel and the RTP environments.
 * It is however divided into two sections, a kernel section and a user section.
 * In the kernel environment *only* the kernel section of the TCB is visible,
 * whereas in the RTP environment both sections are visible.
 *
 * The user level TCB is also known by two different names.  In the RTP
 * environment it goes by the name "struct windTcb" or WIND_TCB, whereas in
 * the kernel it is known as "struct windUTcb" or WIND_UTCB.  This is done
 * so that the RTP environment remains similar to the kernel environment.
 *
 * WARNING, any changes to the kernel portion of the TCB structure must be
 * backwards compatible with previous versions otherwise binary backwards
 * compatibility will be broken.  In essence this basically means that fields
 * may only ever be added to the kernel portion and never removed.  The user
 * level portion of the TCB may change at any time.
 *
 * A TCB version identifier is present as the first member of the TCB
 * structure.  The version identifier is initialized by the task init code
 * to the value of the WIND_UTCB_VERSION define.  The version member must be
 * checked by the kernel to verify the TCB member they are interested in is
 * available in the TCB version being used.
 *
 * Note: we have moved the 'version' member into the kernel substructure
 * of WIND_UTCB in order to avoid changing the offsets of existing members
 * of the kernel substructure (relative to the start of the UTCB) when a new,
 * 8-byte aligned member is added to the kernel substructure.
 */

#if defined(_WRS_KERNEL)

typedef struct windUTcb		  /* kernel-level version of task control block */

#else  /* ! _WRS_KERNEL */

typedef struct windTcb		  /* user-level version of task control block */

#endif /* _WRS_KERNEL */
    {
    struct
	{
        int     version;          /* TCB structure version identifier */
	OBJ_HANDLE	tid;	  /* handle returned by _taskOpen */
	volatile
	UINT	lockCnt;	  /* preemption lock count */
	volatile
	BOOL    relinquishCpu;	  /* higher pri task waiting for cpu? */
	int	errorStatus;	  /* task's most recent 'errno' */

        /* 32-bit alignment gap here in LP64; may use */

        size_t  stackSize;        /* task stack size, cached for user mode */

        } kernel;
#if defined(_WRS_KERNEL)
    } WIND_UTCB;
#else  /* !_WRS_KERNEL */

    /*
     * The following portion of the WIND_TCB structure is only visible in
     * the RTP environment and is not accessible by the kernel.
     */
    struct
	{
	volatile
	UINT	   safeCnt;	    /* safe-from-delete count */

        /* 32-bit alignment gap here in LP64; may use */

	SEM_ID	   safeQFlushSemId; /* semaphore to flush deleters */
	_Vx_exit_code_t exitCode;   /* exit code from entry function */
	FUNCPTR	   entryPoint;	    /* application task entry function */
	char *	   pName;   	    /* ptr to task's name */
	char *	   pTls;   	    /* ptr to TLS area */
	char **    argv;	    /* ptr to argument buffer */
	void **	   pTlsOld;	    /* ptr to obsolete TLS area */

        struct selContext * pSelectContext;  /* select context */
        void * 	   pMemCache;       /* pointer to task's memory cache */
	} user;

    } WIND_TCB;
#endif /* _WRS_KERNEL */

/*
 * Since the size of TASK_DESC is different in user & kernel space for 64bit
 * builds, we must have two different definitions.  In this definition, we want
 * the size to match with the size in the user-side so we define the task id
 * and the rtp id as being object handles.
 */

#ifdef _WRS_KERNEL
typedef struct
    {
    TASK_DESC_FIELDS(OBJ_HANDLE, OBJ_HANDLE)
    } TASK_UDESC;
#endif

/* variable declarations */

#if !defined(_WRS_KERNEL)

extern WIND_TCB * windTcbCurrent;
extern FUNCPTR taskCreateTable[];
extern FUNCPTR taskDeleteTable[];

typedef struct delayInfo
    {
    BOOL isDelayed;             /* TRUE if the task is in delayed state */
    _Vx_ticks_t  delayTick;     /* delay tick for the task */
    } TASK_DELAY_INFO;

extern BOOL       taskIsLastTask(void);
extern STATUS     taskTcbGet(TASK_ID tid, WIND_TCB **ppTcb);
extern WIND_TCB * _taskTcbCurrentGet (void);

extern STATUS	  __taskRtpLock (void);
extern STATUS	  __taskRtpUnlock (void);

/******************************************************************************
*
* TASK_IS_LAST_TASK - check if the caller is the last task in the RTP
*
* TRUE if the caller is the last task in the RTP and FALSE if it is not.
*
* RETURNS: N/A
*
* \NOMANUAL
*/

#define TASK_IS_LAST_TASK() taskIsLastTask()

/******************************************************************************
*
* TASK_TCB_CURRENT_GET - Get the current TCB
*
* Sets the value of <pTcb> to the address of the current task's TCB
*
* In an SMP systems task variables do not work. Instead, a system call
* is used to return the pUTCB value stored in the kernel-side TCB. For fast
* performance this system call is implemented using a fast-path that avoids
* much of the system call overhead.
*
* RETURNS: N/A
*
* \NOMANUAL
*/

#define TASK_TCB_CURRENT_GET(pTcb)                                            \
    do                                                                        \
    {                                                                         \
    if (_VX_IS_SYS_MODE_SMP)                                                  \
        {                                                                     \
        pTcb =  _taskTcbCurrentGet();                                         \
        }                                                                     \
    else                                                                      \
        {                                                                     \
        pTcb =  (WIND_TCB *) windTcbCurrent;                                  \
        }                                                                     \
    } while (0)

/*******************************************************************************
*
* TASK_RTPSAFE - guard self from deletion
*
* Utilization of this macro protects the calling task from deletion by other
* tasks in the same RTP.  In other words, a task residing in another RTP can
* still delete the current task.
*
* This macro should only be used if it has already been determined that the
* current task has a valid WIND_TCB structure.  Otherwise the taskUSafe()
* function should be used.
*
* RETURNS: N/A
*
* NOMANUAL
*/

#define TASK_RTPSAFE()							     \
    do									     \
	{								     \
	VX_CODE_BARRIER();						     \
	  								     \
        windTcbCurrent->safeCnt++;				             \
          								     \
	VX_CODE_BARRIER();						     \
	} while (0)

/*******************************************************************************
*
* TASK_RTPUNSAFE - unguard self from deletion
*
* This macro invokes the taskUnsafe (2) routine.
*
* NOMANUAL
*/

#define TASK_RTPUNSAFE()						\
    (									\
    taskUnsafe ()							\
    )


/* function declarations */

extern STATUS taskTlsOfInitTaskCreate (void);
extern TASK_ID taskOpenWithGuard (const char * name, int priority,
                                  int options, int mode, char * pStackBase,
                                  size_t stackSize, size_t guardSize,
                                  void * context, FUNCPTR entryPt,
                                  _Vx_usr_arg_t arg1, _Vx_usr_arg_t arg2,
                                  _Vx_usr_arg_t arg3, _Vx_usr_arg_t arg4,
                                  _Vx_usr_arg_t arg5, _Vx_usr_arg_t arg6,
                                  _Vx_usr_arg_t arg7, _Vx_usr_arg_t arg8,
                                  _Vx_usr_arg_t arg9, _Vx_usr_arg_t arg10);

#endif /* !_WRS_KERNEL */

#endif /* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCtaskLibPh_u */
