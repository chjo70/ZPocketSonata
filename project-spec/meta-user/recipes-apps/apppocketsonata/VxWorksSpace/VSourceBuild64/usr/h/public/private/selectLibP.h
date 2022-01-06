/* selectLibP.h - private select library header */

/*
 * Copyright (c) 2015-2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
20may17,dlk  Use EDOOM mechanism in select(); remove pendedOnSelect
             and simplify task deletion hook (F5593)
23mar16,dlk  Introduce _selectX(), _selWakeupOp() to support
             user-level I/O system select().
12aug15,zl   added user space select support.
*/

#ifndef __INCselectLibP
#define __INCselectLibP

#ifndef _ASMLANGUAGE
#include <selectLib.h>   /* SELECT_TYPE */
#include <private/semLibP.h>
#include <semLib.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _WRS_CONFIG_USER_MODE_IOS

typedef struct selContext
    {
    fd_set     *pReadFds;		/* select'ed task's read fd_set */
    fd_set     *pWriteFds;		/* select'ed task's write fd_set */
    fd_set     *pExcFds;		/* select'ed task's exc fd_set */

    /* the following are needed for safe task deletion */

    fd_set     *pOrigReadFds;		/* task's original read fd_set */
    fd_set     *pOrigWriteFds;		/* task's original write fd_set */
    fd_set     *pOrigExcFds;		/* task's original exc fd_set */

    /* translation to kernel fd sets */

    char       *pKBase;			/* base address of kernel fd sets */
    fd_set     *pKReadFds;		/* task's kernel read fd_set */
    fd_set     *pKWriteFds;		/* task's kernel write fd_set */
    fd_set     *pKExcFds;		/* task's kernel exc fd_set */

    int         fdsetSize;		/* size of fd_set in context in bytes */
    int         kWidth;			/* width for kernel size fd */
    int		maxFd;			/* maxFd for saved sets above */
    int		width;			/* width parm passed to select() */
    BOOL        badfd;			/* fd is closed */
    int         numFdsSet;		/* number of fds set in return sets */
    } SEL_CONTEXT;

#define SEL_WAKEUP_OP_WAKEUP 0
#define SEL_WAKEUP_OP_CLEAR  1
    
/* select-related function pointers */

extern void   (*_func_selWakeup)         (SEL_WAKEUP_NODE *pWakeupNode);
extern void   (*_func_selWakeupAll)      (SEL_WAKEUP_LIST *pWakeupList,
                                          SELECT_TYPE type);
extern void   (*_func_selWakeupListInit) (SEL_WAKEUP_LIST *pWakeupList);
extern void   (*_func_selWakeupListTerm) (SEL_WAKEUP_LIST *pWakeupList);
extern STATUS (*_func_selNodeAdd)        (SEL_WAKEUP_LIST *pList, 
                                          SEL_WAKEUP_NODE *pNode);
extern STATUS (*_func_selNodeDelete)     (SEL_WAKEUP_LIST *pList,
                                          SEL_WAKEUP_NODE *pNode);
extern STATUS (*_func_selKfdSelect)      (SEL_WAKEUP_NODE *pWakeupNode,
                                          int kernelFd);
extern STATUS (*_func_selKfdUnselect)    (SEL_WAKEUP_NODE *pWakeupNode,
                                          int kernelFd);
extern void   (*_func_selWakeupTermHook) (void * pUmf);
extern void   (*_func_selWakeupAllHook)  (void * pUmf, SELECT_TYPE selType);

#endif /* _WRS_CONFIG_USER_MODE_IOS */

/* system calls */

extern STATUS _selectX    (int width,  fd_set *pReadFds, fd_set *pWriteFds, 
                           fd_set *pExcFds, struct timeval * pTimeOut,
                           BOOL clearSem);
extern STATUS _selWakeupOp (TASK_ID taskId, int op);

#endif /* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCselectLibP */
