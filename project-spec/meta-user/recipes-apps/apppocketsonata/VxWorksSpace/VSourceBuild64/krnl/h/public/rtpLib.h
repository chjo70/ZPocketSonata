/* rtpLib.h - real time process library header file */

/*
 * Copyright (c) 2003-2004, 2007, 2009-2010, 2012-2013 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement. 
 */

/*
modification history
--------------------
01w,22feb13,pad  Added prototype of rtpDeleteForce() (part of fix for
                 WIND00402989).
01v,03feb12,jpb  CQ Req WIND00139205: added rtpWait declaration and 
                 RTP_WAIT_ANY definition.
01u,29apr10,pad  Moved extern C statement after include statements.
01t,03dec09,cww  LP64 adaptation
01s,17sep07,gls  added public RTP signal APIs (Defect #00102843)
01r,12oct04,kk   updated kernelBaseLib.h to private/kernelBaseLibP.h,
		 added rtpShow prototype
01q,22sep04,ans  moved rtpLibInit() rtpShowInit() rtpShellCmdInit() to
                 rtpLibP.h
01p,10aug04,kk   renamed rtpBaseLib.h to kernelBaseLib.h
01p,02sep04,yvp  Remove const from rtpLibInit params.
01o,27apr04,ans  Added RTP_DEL_FORCE option
01n,15apr04,kk   rename rtpSelfIdGet to rtpIdSelf(), added include of 
                 rtpBaseLib.h
01m,06apr04,job  Extended rtpLibInit() prototype.
01l,18feb04,ans  Added rtpSignalQueueSz parameter to rtpLibInit ().
01k,17nov03,yvp  Added RTP hook support.
01j,30oct03,nrj  added support for waitpid
01j,22sep03,bpn  Cleaned up. Added rtpShellCmdInit() prototype.
01i,22sep03,kk   remove rtpSpawn, moved to rtpLibCommon.h
01h,15sep03,kk   move common definitions to rtpLibCommon.h,
		 added options arg to rtpDelete(), 
		 added RTP_DEL_VIA_TASK_DELETE option
01g,26aug03,nrj  reorganized and moved to private hdr
01f,18aug03,job  Added rtpShowInit() prototype.
01e,22jul03,pad  Moved _exit() declaration to taskLibP.h for decoupling
                 reasons.
01d,07jul03,nrj  added rtpDelete
01c,07jul03,nrj  removing RTP_ID from here
01b,07jul03,nrj  changed create API
01a,26jun03,nrj  written.
*/

#ifndef __INCrtpLibh
#define __INCrtpLibh

/* includes */

#include <vxWorks.h>
#include <rtpLibCommon.h>
#include <signal.h>

#ifdef __cplusplus
extern "C" {
#endif

/* defines */

#define RTP_DEL_VIA_TASK_DELETE 0x1 	/* rtpDelete() via taskDestroy() */
#define RTP_DEL_FORCE           0x2     /* Forceful  rtpDelete()  */
#define RTP_ID_ANY		((RTP_ID) 0) /* used for when a kernel task */
                                              /* wants to wait for the next  */
                                              /* RTP to finish               */

#ifndef	_ASMLANGUAGE

/* function declarations */

extern STATUS 	rtpDelete (RTP_ID id, int options, int status);
extern STATUS   rtpDeleteForce (RTP_ID rtpId);
extern BOOL	rtpShow (char * rtpNameOrId, int level);

/* 
 * RTP signals are always present when RTPs are included.  The public RTP 
 * signal APIs are declared here.
 */

extern int rtpKill (RTP_ID rtpId,  int signo);
extern int rtpSigqueue (RTP_ID rtpId,  int signo , 
			const union sigval value);
extern int rtpTaskKill (TASK_ID tid, int signo);
extern int rtpTaskSigqueue (TASK_ID tid, int signo, 
			    const union sigval value);

extern STATUS rtpWait       (RTP_ID rtpWaitId, _Vx_ticks_t timeout, 
                             RTP_ID * pRtpId, int * pStatus);
#endif	/* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCrtpLibh */
