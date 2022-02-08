/* kernelBaseLibP.h - Kernel base library header file */

/*
 * Copyright (c) 1984-2005, 2008, 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01s,29apr10,pad  Moved extern C statement after include statements.
01r,04jun08,to   move MY_CTX_ID() to taskLibP.h
01q,13mar08,to   revised MY_CTX_ID() to be inline function
01p,14oct05,zl   removed kernelMemInfo.
01o,07jun05,yvp  Updated copyright. #include now with angle-brackets.
01n,26apr05,yvp  Added externs for kernelObjClassId & kernelMemInfo.
01m,01feb05,kk   make IS_KERNEL_TASK() public (SPR# 104271)
01l,21oct04,kk   comments cleanup
01k,12oct04,kk   added kernelIdGet() prototype, removed getpid() prototype
01j,23sep04,kk   enable MY_CTX_ID macro
01i,09sep04,kk   renamed rtpKernelInit() and rtpIdKernel.
01h,05may04,cjj  Added RTP_ID_OF_TASK and RTP_ID_TO_PID.
01g,22may04,job  MY_CTX_ID macro not working correctly, so replaced by a
		 function.
01f,18may04,kk   change CURRENT_TASK_RTP_ID to be MY_CTX_ID
01e,21oct03,dat  Adding rtpKernelInit
01d,21oct03,nrj  introduced macros and extern for RTP lib dependency
01c,09sep03,dcc  added prototype for rtpIdSelf()
01b,29aug03,nrj  added kernel rtp ID
01a,09may03,to   created from pdBaseLib.h in AE.
*/

#ifndef __INCkernelBaseLibPh
#define __INCkernelBaseLibPh

#include <vxWorks.h>
#include <types/vxWind.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef	_ASMLANGUAGE

/* macros */

#define RTP_ID_OF_TASK(tid)	((RTP_ID)(((WIND_TCB *)tid)->rtpId))
#define RTP_ID_TO_PID(rtpId)	(((RTP_ID)rtpId)->rtpHandleId)

/* externs */

extern RTP_ID	kernelId;
extern CLASS_ID kernelObjClassId;

/* prototypes */

extern RTP_ID	kernelIdGet (void);
extern STATUS	kernelBaseInit (void);

#endif	/* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCkernelBaseLibPh */
