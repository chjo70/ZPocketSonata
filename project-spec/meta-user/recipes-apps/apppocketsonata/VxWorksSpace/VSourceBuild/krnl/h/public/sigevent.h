/* sigevent.h - sigevent structure, needed by several header files */

/*
 * Copyright (c) 1992-1993, 2003, 2010, 2014 Wind River Systems, Inc.
 * 
 * The right to copy, distribute, modify, or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */
 
/*
modification history
--------------------
31jan14,to   include vxWorks.h for STATUS
02f,04mar10,cww  LP64 adaptation
02e,02dec03,ans  Added taskId parameter to sigeventInit ().
02d,14oct03,ans  Added sigevenLib support.
02c,09nov93,rrr  update to posix 1003.4 draft 14
02b,22sep92,rrr  added support for c++
02a,04jul92,jcf  cleaned up.
01b,26may92,rrr  the tree shuffle
01a,19feb92,rrr  written from posix spec
*/

#ifndef __INCsigeventh
#define __INCsigeventh

#include <vxWorks.h>    /* for STATUS */
#include <sigeventCommon.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct sigevent_t * SIGEVENT_ID;

extern SIGEVENT_ID sigeventCreate        (struct sigevent * pSigev);
extern STATUS      sigeventInit          (SIGEVENT_ID sigevId, TASK_ID taskId,
                                          struct sigevent * pSigev);
extern STATUS      sigeventNotify        (SIGEVENT_ID sigevId);
extern STATUS      sigeventDelete        (SIGEVENT_ID sigevId);
extern int         sigeventSigOverrunGet (SIGEVENT_ID  sigevId);

#ifdef __cplusplus
}
#endif

#endif /* __INCsigeventh */
