/* wvSockUploadPathLibP.h - socket upload path library header */

/* Copyright 1997, 1997-1998, 2003, 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01g,29apr10,pad  Moved extern C statement after include statements.
01g,10feb10,tcr  update for 64bit
01f,04sep03,tcr  rename init function
01e,27jan98,cth  removed sockUploadPathError prototypes, SOSENDBUFSIZE, added
		 sockUpPathSendBufSize
01d,18dec97,cth  renamed again to wvSockUploadPathLibP.h from, updated include, 
		 wvSockUploadPathP.h, added sockUploadPathLibInit prototype
01c,16nov97,cth  renamed again from sockUploadPathP.h to wvSockUploadPathP.h
01b,16nov97,cth  changed prototypes to match WV2.0 upload-path model
                 renamed from evtSockLibP.h to sockUploadPathP.h
01a,10dec93,smb  written.
*/

#ifndef __INCwvsockuploadpathlibph
#define __INCwvsockuploadpathlibph

#include "private/wvUploadPathP.h"

#ifdef __cplusplus
extern "C" {
#endif


/* variable declarations */

extern int sockUpPathSendBufSize;

/* function declarations */

extern STATUS	    wvSockUploadPathLibInit (void);
extern UPLOAD_ID    wvSockUploadPathCreate (char *ipAddress, int port);
extern STATUS       wvSockUploadPathClose (UPLOAD_ID upId);
extern ssize_t      wvSockUploadPathWrite (UPLOAD_ID upId, char * pData,
                                           size_t size);

#ifdef __cplusplus
}
#endif

#endif /* __INCwvsockuploadpathlibph*/

