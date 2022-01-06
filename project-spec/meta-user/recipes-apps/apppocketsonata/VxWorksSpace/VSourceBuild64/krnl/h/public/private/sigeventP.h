/* sigeventP.h - sigeventLib header files */

/*
 * Copyright (c) 2003, 2006, 2009-2011, 2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
16dec15,rr   Added notifyKernelTask variable to sigevent structure (V7COR-3877)
03jun15,h_k  added objHandleAndClassToObjId(). (F3937)
30nov11,jpb  WIND00309548.  sigeventUserToKernel possibly dereferences NULL
             pointer.  Fixed build warning.
28jan11,gls  added sigeventUserToKernel() (WIND00252562)
04mar10,cww  LP64 adapatation
23dec09,jpb  Updated for LP64 adaptation.
10jul06,gls  added the sigeventLibInit() prototype
             updated copyright
25sep03,ans  written
*/

#ifndef __INCsigeventph
#define __INCsigeventph

#include <sigevent.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _WRS_CONFIG_RTP
/*******************************************************************************
*
* sigeventUserToKernel - covert a sigevent structure from RTP to kernel
*
* This routine performs the necessary conversion between a user level 
* sigevent structure and the structure used in kernel during a system call.
*
* It takes as a parameter the address of sigevent structure guaranteed to
* be valid for the duration of the call (ie, a stack variable) and the pointer
* to the user level sigevent structure, and returns the address of the converted
* sigevent structure.
*
* RETURNS: address of sigevent structure to be used for the system call
*
* ERRNO: N/A
*
* \NOMANUAL
*/

_WRS_INLINE struct sigevent * sigeventUserToKernel 
    (
    struct sigevent * pKSigev,
    struct sigevent * pUSigev
    )
    {
    if ((pUSigev != NULL) && (IS_SIGEV_THREAD(pUSigev->sigev_notify)))
	{ 
	*pKSigev = *pUSigev;
	
	pKSigev->sigev_notifier_id = 
	    (void *) objHandleAndClassToObjId
			((OBJ_HANDLE) (long) pUSigev->sigev_notifier_id,
			 0, FALSE, taskClassId);

	pKSigev->sigev_value.sival_ptr = pUSigev->sigev_id;
	
	return (pKSigev);
	}

    return (pUSigev);
    }
#endif /* _WRS_CONFIG_RTP */

struct sigevent_t
    {
    OBJ_ID          notifierId;  /* task or RTP Id to notify */
    struct sigevent sigEvent;    /* sigevent descibing the notification */
    BOOL notifyKernelTask;       /* True notifying task is kernel task */
    union 
        {
        struct sigpend _timerSigPend;
        } notifier;
#define timerSigPend notifier._timerSigPend
  
    };

extern STATUS (*_func_sigeventInit)(SIGEVENT_ID sigevId, TASK_ID taskId,
                                    struct sigevent * pSigev);

extern STATUS sigeventLibInit (void);

#ifdef __cplusplus
}
#endif

#endif /* __INCsigeventph */
