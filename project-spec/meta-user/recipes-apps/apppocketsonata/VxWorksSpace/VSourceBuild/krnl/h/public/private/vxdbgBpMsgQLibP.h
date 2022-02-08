/* vxdbgBpMsgQLibP.h - VxDBG breakpoint message queue library header file */

/*
 * Copyright (c) 2008-2009 Wind River Systems, Inc.  
 *
 * The right to copy, distribute, modify or otherwise make use  of this 
 * software may be licensed only pursuant to the terms of an applicable Wind 
 * River license agreement.
 */

/*
modification history
--------------------
01e,04mar09,jmp  Updated for 64-bit support.
01d,24sep08,dbt  Renamed vxdbgBpMsgIsAvailable() in vxdbgBpMsgGet(). Added
                 vxdbgBpMsgDrop() (CQ:WIND00136074).
01c,25jun08,dbt  Added VXDBG_BP_MSG_NO_REDIRECT.
01b,20jun08,dbt  Added more verbosity levels.
01a,21apr08,dbt  written
*/

#ifndef __INCvxdbgBpMsgQLibPh
#define __INCvxdbgBpMsgQLibPh

#ifdef __cplusplus
extern "C" {
#endif

/* typedefs */

typedef struct vxdbgBpMsgQDesc *	VXDBG_BP_MSG_Q_ID;

typedef enum vxdbg_bp_msg_options
    {
    VXDBG_BP_MSG_QUIET		= 1,		/* quiet message */
    VXDBG_BP_MSG_VERBOSE_1	= 2,		/* low verbosity message */
    VXDBG_BP_MSG_NO_REDIRECT	= 4		/* do not redirect output */
    						/* to task stdout */
    } VXDBG_BP_MSG_OPTIONS;

/* function declarations */

extern VXDBG_BP_MSG_Q_ID vxdbgBpMsgQCreate (UINT32 maxMsgs,
						     size_t maxMsgLength,
						     char * name);
extern char *		vxdbgBpMsgGet (VXDBG_BP_MSG_Q_ID bpMsgQId);
extern BOOL		vxdbgBpMsgQHdlrIsRunning (VXDBG_BP_MSG_Q_ID bpMsgQId);
extern void		vxdbgBpMsgPost (VXDBG_BP_MSG_Q_ID bpMsgQId,
						VXDBG_BP_MSG_OPTIONS options,
						TASK_ID tid, void * addr);
extern void		vxdbgBpMsgDrop (VXDBG_BP_MSG_Q_ID bpMsgQId);
#ifdef __cplusplus
}
#endif

#endif	/* __INCvxdbgBpMsgQLibPh */
