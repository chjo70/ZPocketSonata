/* taskWaitShowP.h - private header file for taskWaitShow routines */

/* Copyright 2004, 2009 Wind River Systems, Inc. */

/*
modification history
--------------------
01b,15may09,jmp  Adapted for 64-bit support.
01a,07sep04,bpn  Written.
*/

#ifndef __INCtaskWaitShowPh
#define __INCtaskWaitShowPh

#ifdef __cplusplus
extern "C" {
#endif

extern STATUS	taskWaitShowCoreRtn (BOOL allTasks, BOOL detail, TASK_ID taskId,
				     const char * errorStr);

#ifdef __cplusplus
}
#endif

#endif /* __INCtaskWaitShowPh */
