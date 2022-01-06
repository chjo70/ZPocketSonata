/* rtpIoLibP.h - real time process I/O library private header file */

/* Copyright 2003-2004, 2010 Wind River Systems, Inc. */

/*
modification history
--------------------
01g,29apr10,pad  Moved extern C statement after include statements.
01f,01mar06,md   fix dup'ing rtp's vxe file descriptor, SPR 117466
01e,11may05,hya  changed rtpIoSysConstruct prototype, SPR 109163
01d,04mar04,dat  merge rtpIo with iosLib, new rtpIoFdSetup()
01c,12nov03,pmr  rtpIoDefPathSet/Get.
01b,10nov03,pmr  fix rtpIoFdEntryGet().
01a,31oct03,pmr  written.
*/

#ifndef __INCrtpIoLibPh
#define __INCrtpIoLibPh

/* includes */

#include "rtpLibCommon.h"
#include "private/iosLibP.h"
#include "rtpIoLib.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _ASMLANGUAGE

/* PRIVATE function prototypes */

IMPORT	STATUS		rtpIoSysConstruct (RTP_ID,int numFds,
					   const char* path, int vxefd,
					   int *vxeRtpFd);
IMPORT	STATUS		rtpIoSysDestruct (RTP_ID);
IMPORT	void *		rtpIoFdTableGet (RTP_ID);
IMPORT	FD_ENTRY * 	rtpIoFdEntryGet (RTP_ID, int fd);
IMPORT	STATUS		rtpIoFdEntryMap (RTP_ID, int fd, FD_ENTRY *);
IMPORT	STATUS		rtpIoFdUnmap (RTP_ID, int fd);
IMPORT	STATUS		rtpIoFdTableShow (RTP_ID);
IMPORT	STATUS		rtpIoDevCheck (DEV_HDR *);
IMPORT	STATUS		rtpIoDevClose (DEV_HDR *);
IMPORT	int		rtpIoFdReserve (RTP_ID pRtp);
IMPORT	int		rtpIoFdSetup (RTP_ID pRtp, FD_ENTRY* pFdEntry, int fd,
			    DEV_HDR * pDevHdr, const char * name, int value);
 
#endif  /* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCrtpIoLibPh */
