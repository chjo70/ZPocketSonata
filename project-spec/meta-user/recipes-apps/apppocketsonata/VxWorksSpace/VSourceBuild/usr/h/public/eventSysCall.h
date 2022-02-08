/* eventSysCall.h - VxWorks user event system call definitions */

/*
 * Copyright 2004, 2009-2010 Wind River Systems, Inc
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01d,28apr10,pad  Moved extern C statement after include statements.
01c,08feb10,jpb  Updated for LP64 adaptation.
01b,24apr09,pad  Included eventLib.h and removed external references to
                 eventSend() and eventReceive().
01a,09mar04,hya  created
*/

#ifndef __INCeventSysCallh
#define __INCeventSysCallh

#include <vxWorks.h>
#include <eventLib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* command codes for the eventCtl system call */
typedef enum
    {
    VX_EVT_CTL_SEM_START,
    VX_EVT_CTL_SEM_STOP,
    VX_EVT_CTL_MQ_START,
    VX_EVT_CTL_MQ_STOP,
    VX_EVT_CTL_EVENT_CLEAR
    } VX_EVT_CTL_CMD;

/* argument structure for the eventCtl() system call */

typedef struct vx_rsc_event_start_args
    {
    UINT32 registered;	/* 0x00: events registered for that resource	*/
    UINT32 options;	/* 0x04: user options				*/
    } VX_SRC_EVENT_START_ARGS;

/* system call function prototypes */
extern STATUS eventCtl (
			OBJ_HANDLE handle,
			VX_EVT_CTL_CMD command,
			void * pArg,
			size_t * pArgSize
			);

#ifdef __cplusplus
}
#endif

#endif /* __INCeventSysCallh */
