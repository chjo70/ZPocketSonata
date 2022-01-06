/* taskMemLibP.h - private task stack library interface header */

/*
 * Copyright (c) 1984-2004, 2009-2010 Wind River Systems, Inc. 
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01h,29apr10,pad  Moved extern C statement after include statements.
01g,15dec09,cww  Moved _func_taskMemCtxSwitch from funcBindP.h
01f,03dec09,cww  LP64 adaptation
01e,28sep04,tam  added RTP_ID parameter to taskStackAlloc(); added
                 taskStackGuardPageEnable and taskStackNoExecEnable def.
01d,27sep04,ans  Renamed IGNORE_RTP_STATE_DELETE to RTP_NOT_CHECK_CTX
01c,01jul04,pcs  Add macro IGNORE_RTP_STATE_DELETE to be used as option
                 parameter to taskMemCtxSwitch.
01b,12nov03,kk   added taskMemCtxSwitch prototype
01a,10nov03,tam  written
*/

#ifndef __INCtaskMemLibPh
#define __INCtaskMemLibPh

#ifndef _ASMLANGUAGE
#include <taskLib.h>

#ifdef __cplusplus
extern "C" {
#endif

#endif /* !_ASMLANGUAGE */

/* task stack allocation/deallocation options */

#define STACK_DOWN              0x1	/* stack grows down */
#define STACK_UP                0x2	/* stack grows up */
#define EXECUTION_STACK         0x4	/* alloc/free an execution stack */
#define EXCEPTION_STACK         0x8	/* alloc/free an exception stack */

/* 
 * option to taskMemCtxSwitch fn. to force context switch even though the
 * the RTP is in the RTP_DELETE_STATE. 
 * This is required so that and unmapping of the RTP pages are done within 
 * the context of the RTP.
 */ 

#define RTP_NOT_CHECK_CTX 0x01

/* funcBind pointers */

extern STATUS (*_func_taskStackAlloc)   (RTP_ID rtpId, size_t stackSize,
					 size_t taskOverflowSize,
					 size_t taskUnderflowSize, int options, 
					 size_t * pStackSize,
					 char ** pStackBase);
extern STATUS (*_func_taskStackFree)    (WIND_TCB * pTcb, char * stackBase,
					 size_t stackSize,
					 size_t taskOverflowSize,
					 size_t taskUnderflowSize, int options);

extern RTP_ID (*_func_taskMemCtxSwitch) (RTP_ID newRtp, int options);

/* function declarations */

extern	STATUS taskStackAlloc (RTP_ID	rtpId,
			       size_t	stackSize,
			       size_t	taskOverflowSize,
			       size_t	taskUnderflowSize,
			       int	options,
			       size_t *	pStackSize,
			       char **	pStackBase);

extern	STATUS taskStackFree (WIND_TCB *pTcb,
			      char *	stackBase,
			      size_t	stackSize,
			      size_t 	taskOverflowSize,
			      size_t	taskUnderflowSize,
			      int	options);

extern RTP_ID taskMemCtxSwitch (RTP_ID	newCtx,
				int 	options);

extern STATUS taskMemLibInit (void);

extern STATUS taskStackGuardPageEnable (void);

extern STATUS taskStackNoExecEnable (void);

#ifdef __cplusplus
}
#endif

#endif /* __INCtaskMemLibPh */
