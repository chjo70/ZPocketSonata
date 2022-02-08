/* wvFileUploadPathLibP.h - file upload path header */

/* Copyright 1997, 1998, 2003, 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01e,29apr10,pad  Moved extern C statement after include statements.
01e,10feb10,tcr  update for 64bit
01d,04sep03,tcr  rename init function
01c,27jan98,cth  added openFlags arg to create call, fileUpPathDefaultPerm
01b,18dec97,cth  renamed to wvFileUploadPathLibP.h from wvFileUploadPathP.h,
		 added fileUploadPathLibInit prototype, updated include
01a,16nov97,cth  written, taken from evtSockLibP.h
*/

#ifndef __INCwvfileuploadpathlibph
#define __INCwvfileuploadpathlibph

#include "private/wvUploadPathP.h"

#ifdef __cplusplus
extern "C" {
#endif


/* variable declarations */

extern int fileUpPathDefaultPerm;

/* function declarations */

extern STATUS 	    wvFileUploadPathLibInit (void);
extern UPLOAD_ID    wvFileUploadPathCreate (char *fname, int openFlags);
extern STATUS       wvFileUploadPathClose (UPLOAD_ID upId);
extern ssize_t      wvFileUploadPathWrite (UPLOAD_ID upId, char * pData,
                                           size_t size);

#ifdef __cplusplus
}
#endif

#endif /* __INCwvfileuploadpathlibph*/

