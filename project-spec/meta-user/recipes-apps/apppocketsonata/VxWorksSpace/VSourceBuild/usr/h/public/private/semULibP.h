/* semULibP.h - private user semaphore header */
 
/*
 * Copyright (c) 2009-2011 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */
 
/*
modification history
--------------------
01e,10jan11,gls  added timeout parameter to VX_SEM_CTL_VAR_EXCHANGE_CMD
                 and VX_SEM_CTL_VAR_HARD_CMD (WIND00231560)
01d,16jun10,pcs  change the data type of timeout from an int to _Vx_ticks_t
01c,08jun10,jpb  Changed SEM_USER_NO_OWNER to integer type for both kernel &
                 user.
01b,18jan10,cww  Changed SEM_USER_NO_OWNER to integer type on usr side
01a,16may09,gls  created.
*/
 
/*
 * Note: This file contains definitions that must be maintained in both kernel
 * and user space
 */

#ifndef __INCsemULibPh
#define __INCsemULibPh

/* includes */

#include <vxWorks.h>

#if defined(__cplusplus)
extern "C" {
#endif  /* __cplusplus */

/* command structures for the user semaphore VX_SEM_CTL commands */

typedef struct vx_sem_ctl_var_hard_cmd
    {
    volatile OBJ_HANDLE *pSemOwner;
    BOOL                *pSendEvents;
    _Vx_ticks_t         timeout;
    } VX_SEM_CTL_VAR_HARD_CMD;

typedef struct vx_sem_ctl_var_exchange_cmd
    {
    OBJ_HANDLE           takeSemId;
    volatile OBJ_HANDLE *pTakeSemOwner;
    volatile OBJ_HANDLE *pGiveSemOwner;
    BOOL                *pSendEvents;
    _Vx_ticks_t         timeout;
    } VX_SEM_CTL_VAR_EXCHANGE_CMD;

/*
 * The most signicant bit of the semaphore handle is used to denote that the
 * underlying kernel semaphore is owned.
 */

#define SEM_USER_NO_OWNER  0

#define SEM_USER_K_OWNED   0x80000000

#if defined(_WRS_KERNEL)
extern STATUS 	     semUMGiveHard (SEM_ID semId, 
				    volatile OBJ_HANDLE *pUserSemOwner,
				    BOOL *pSendEvents);
extern STATUS 	     semUMTakeHard (SEM_ID semId, 
				    volatile OBJ_HANDLE *pUserSemOwner,
				    _Vx_ticks_t timeout);
extern STATUS 	     semUExchange (SEM_ID giveSemId, SEM_ID takeSemId, 
				   volatile OBJ_HANDLE *pUserGiveSemOwner,
				   volatile OBJ_HANDLE *pUserTakeSemOwner,
				   BOOL *pSendEvents, _Vx_ticks_t timeout);
#endif /* defined(_WRS_KERNEL) */

#ifdef __cplusplus
}
#endif

#endif /* __INCsemULibPh */
