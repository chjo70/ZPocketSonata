/* usrRtpLibP.h - private header file for rtp user interface library */

/*
 * Copyright (c) 2004,2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01c,29apr10,pad  Moved extern C statement after include statements.
01b,21jan10,jmp  LP64 adaptation.
01a,03aug04,bpn  Written.
*/

#ifndef __INCusrRtpLibPh
#define __INCusrRtpLibPh

#include <rtpLib.h>

#ifdef __cplusplus
extern "C" {
#endif

extern int rtpSpPriority;
extern int rtpSpOptions;
extern long rtpSpStackSize;
extern int rtpSpDelay;
extern int rtpSpTaskOptions;

/* function declarations */

extern STATUS	usrRtpLibInit	(void);
extern STATUS	rtpi		(long rtpId);
extern void	rtpHelp		(void);
extern void	rtpLkup		(char * substr, long rtpId);
extern void	rtpLkAddr	(unsigned long addr, long rtpId);
extern long	rtpSp		(char * execAndArgs, int initTaskPrio,
				 long userStackSize, int launchOptions,
				 int launchTaskOptions);
extern STATUS	rtpSymsAdd	(long rtpId, unsigned int regPolicy,
				 char * filePath);
extern STATUS	rtpTaskShow	(RTP_ID rtpId);
extern STATUS	shlSymsAdd	(long shlId, long rtpId, unsigned int regPolicy,
				 char * filePath);
extern STATUS	shlSymsRemove	(long shlId, long rtpId,
				 unsigned int remPolicy);
extern STATUS	rtpSymsRemove	(long rtpId, unsigned int remPolicy);
extern STATUS	rtpSymsOverride (int overridePolicy);

#ifdef __cplusplus
}
#endif

#endif /* __INCusrRtpLibPh */

