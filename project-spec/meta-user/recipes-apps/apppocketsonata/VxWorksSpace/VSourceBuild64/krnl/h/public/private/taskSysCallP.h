/* taskSysCallP.h - VxWorks tasking system call definitions */

/*
 * Copyright (c) 2010, 2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
13may15,h_k  added task delete safe flag in user.safeCnt and removed
             pSafeDeleteFlag from VX_TASK_CTL_DELETE_CMD. (V7COR-2631)
20aug10,gls  modified VX_TASK_CTL_DELETE command (WIND00216710)
17jun10,jpb  Changed stackGuardSize type from ssize_t to size_t
22jan10,cww  Written
*/

#ifndef __INCtaskSysCallPh
#define __INCtaskSysCallPh

#include <vxWorks.h>

#ifdef __cplusplus
extern "C" {
#endif

/* command struct for VX_TASK_CTL_TASKNAME_TO_ID_STRUCT command */
    
typedef struct vx_task_ctl_taskname_to_id
    {
    char *      name;
    OBJ_HANDLE  tid;		
    } VX_TASK_CTL_TASKNAME_TO_ID_STRUCT;

/* command struct for VX_TASK_CTL_DELETE command */

typedef struct vx_task_ctl_delete
    {
    OBJ_HANDLE semToGive;
    OBJ_HANDLE semToTake;
    BOOL *     pRestart;
    volatile
    UINT *     pSafeCnt;
    } VX_TASK_CTL_DELETE_CMD;
    
/* command struct for VX_TASK_CTL_PX_ATTR_* commands */

typedef struct vx_task_ctl_px_attr
    {
    void *  pAttr;
    size_t attrSz;
    } VX_TASK_CTL_PX_ATTR;

/* 
 * command structs for VX_TASK_CTL_ATOMIC_OPP_* commands
 * XXX - These are temp structs that will need to be removed in the future when
 * atomic operations are no longer required in system calls.
 */

typedef struct vx_task_ctl_atomic32_opp
	{
        int		atomicSwitch;
        atomic32_t * 	target;		
        atomic32Val_t	value;		
        atomic32Val_t	newValue;	
        atomic32Val_t	returnVal;	
	} VX_TASK_CTL_VX_ATOMIC32_STRUCT;

typedef struct vx_task_ctl_atomic64_opp
	{
        int		atomicSwitch;
	int		pad;
        atomic64_t * 	target;		
        atomic64Val_t	value;		
        atomic64Val_t	newValue;	
        atomic64Val_t	returnVal;	
	} VX_TASK_CTL_VX_ATOMIC64_STRUCT;

typedef enum
    {
    VX_ATOMIC32_ADD,	/*  0 */
    VX_ATOMIC32_AND,	/*  1 */
    VX_ATOMIC32_DEC,	/*  2 */
    VX_ATOMIC32_INC,	/*  3 */
    VX_ATOMIC32_NAND,	/*  4 */
    VX_ATOMIC32_OR,	/*  5 */
    VX_ATOMIC32_SUB,	/*  6 */
    VX_ATOMIC32_XOR,	/*  7 */
    VX_ATOMIC32_CLEAR,	/*  8 */
    VX_ATOMIC32_GET,	/*  9 */
    VX_ATOMIC32_SET,	/* 10 */
    VX_ATOMIC32_CAS,	/* 11 */
    VX_ATOMIC64_ADD,	/* 12 */
    VX_ATOMIC64_AND,	/* 13 */
    VX_ATOMIC64_DEC,	/* 14 */
    VX_ATOMIC64_INC,	/* 15 */
    VX_ATOMIC64_NAND,	/* 16 */
    VX_ATOMIC64_OR,	/* 17 */
    VX_ATOMIC64_SUB,	/* 18 */
    VX_ATOMIC64_XOR,	/* 19 */
    VX_ATOMIC64_CLEAR,	/* 20 */
    VX_ATOMIC64_GET,	/* 21 */
    VX_ATOMIC64_SET,	/* 22 */
    VX_ATOMIC64_CAS	/* 23 */
    } VX_TASK_ATOMIC_COMMAND;

/* argument structure for the _taskOpenWithGuard() system call */
                                                                                
typedef struct vx_task_open_guard_sc_args
    {
    const char * name;           /* task name - default name will be chosen */
    int          priority;       /* task priority */
    int          options;        /* VX_ task option bits */
    int          mode;           /* object management mode bits */
    char       * pStackBase;     /* location of execution stack */
    size_t       stackSize;      /* execution stack size */
    size_t       stackGuardSize; /* execution stack overflow guard size */
    BOOL       * pTaskCreated;   /* new kernel task created? */
    void       * context;        /* context value */
    FUNCPTR      entryPt;        /* application entry point */
    int          argc;           /* number of arguments to entry point */
    char      ** argv;           /* arguments to application entry point */
    } VX_TASK_OPEN_GUARD_SC_ARGS;


/* function declarations */

#ifndef _WRS_KERNEL
extern TASK_ID 	_taskOpenWithGuard (VX_TASK_OPEN_GUARD_SC_ARGS *pArgs);
#endif /* !_WRS_KERNEL */

#ifdef __cplusplus
}
#endif

#endif /* __INCtaskSysCallPh */
