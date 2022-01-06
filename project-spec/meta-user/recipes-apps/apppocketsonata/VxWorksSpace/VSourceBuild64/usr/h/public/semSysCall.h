/* semSysCall.h - VxWorks semaphore system call definitions */

/* Copyright 2003-2007, 2009-2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
01h,08nov10,zl   updated semId type of the system calls, added SEM_ID_ERROR
01g,16jun10,pcs  change the data type of timeout from an int to _Vx_ticks_t
01f,19jan10,cww  Updated semCtl args
01e,01may09,gls  added user semaphores for SMP
01d,27jun07,gls  added _semExchange
01c,11jun07,mfj  Adding _semRTake and _semWTake
01b,22apr04,dcc  added "context" to _semOpen() parameters.
01a,31oct03,md   written
*/

#ifndef __INCsemSysCallh
#define __INCsemSysCallh

#include <vxWorks.h>

#ifdef __cplusplus
extern "C" {
#endif

/* return value for unsuccessful _semOpen() */

#define SEM_ID_KERNEL_ERROR	((SEM_ID_KERNEL) (-1))

/* command codes for the semCtl() system call */

typedef enum
    {
    VX_SEM_CTL_MTAKE_PROXY,
    VX_SEM_CTL_SEM_OWNER,
    VX_SEM_CTL_FLUSH,
    VX_SEM_CTL_MTAKE_HARD,
    VX_SEM_CTL_MGIVE_HARD,
    VX_SEM_CTL_EXCHANGE
    } VX_SEM_CTL_CMD;

/* command struct for VX_SEM_CTL_VAR_* commands */

typedef struct vx_sem_ctl_var_cmd
    {
    int *pVariable;
    int  value;
    } VX_SEM_CTL_VAR_CMD;

/* system call function prototypes */

#if !defined(_WRS_KERNEL)

extern STATUS        semCtl     (SEM_ID_KERNEL semId, VX_SEM_CTL_CMD command, 
                                 void * pArg, size_t * pArgSize);
extern SEM_ID_KERNEL _semOpen	(const char * name, SEM_TYPE type, 
				 int initState, int options, int mode, 
				 void * context);
extern STATUS 	     _semTake 	(SEM_ID_KERNEL semId, _Vx_ticks_t timeout);
extern STATUS 	     _semRTake 	(SEM_ID_KERNEL semId, _Vx_ticks_t timeout);
extern STATUS 	     _semWTake 	(SEM_ID_KERNEL semId, _Vx_ticks_t timeout);
extern STATUS 	     _semExchange (SEM_ID_KERNEL giveSemId, 
				   SEM_ID_KERNEL takeSemId,
				   _Vx_ticks_t timeout);
extern STATUS 	     _semGive 	(SEM_ID_KERNEL semId);
extern STATUS 	     _semFlush 	(SEM_ID_KERNEL semId);

#endif /* !_WRS_KERNEL */

#ifdef __cplusplus
}
#endif

#endif /* __INCsemSysCallh */
