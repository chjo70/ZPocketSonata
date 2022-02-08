/* coreDumpRtpLib.h - RTP core dump interface header */

/*
 * Copyright (c) 2009 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */
 
/*
modification history
--------------------
01a,16jul09,jmp  written.
*/

#ifndef __INCcoreDumpRtpLibh
#define __INCcoreDumpRtpLibh

#ifdef __cplusplus
extern "C" {
#endif

extern STATUS	coreDumpRtpFsPathSet		(char * coreDumpRtpPath);
extern char *	coreDumpRtpFsPathGet		(void);
extern STATUS	coreDumpRtpNameSuffixSet	(char * nameSuffix);

#ifdef __cplusplus
}
#endif

#endif /* __INCcoreDumpRtpLibh */
