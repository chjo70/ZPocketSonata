/* usrFsLib.h - header for user file (io) interface subroutines */

/*
 * Copyright (c) 1984-2005, 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */


/*
modification history
--------------------
01d,30jun10,jxu  LP64: add prototype of API commit and ioHelp.
01c,01dec05,md   changed hrfsDiskFormat parameters
01b,23aug05,pcm  added hrfsDiskFormat() and dosfsDiskFormat()
01a,09apr04,dat  written (from usrLib.h, ver 02j)
*/

#ifndef __INCusrFsLibh
#define __INCusrFsLibh

#ifdef __cplusplus
extern "C" {
#endif

/* function declarations */

IMPORT STATUS copy (const char *in, const char *out);
IMPORT STATUS copyStreams (int inFd, int outFd);
IMPORT STATUS diskFormat (const char *devName);
IMPORT STATUS diskInit (const char *devName);
IMPORT STATUS cd (const char *name);
IMPORT void   pwd (void);
IMPORT STATUS chkdsk (const char * pDevName, u_int repairLevel, u_int verbose);
IMPORT STATUS ls (const char *dirName, BOOL doLong);
IMPORT STATUS ll (const char * dirName);
IMPORT STATUS lsr (const char * dirName);
IMPORT STATUS llr (const char * dirName);
IMPORT STATUS rm (const char *fileName);
IMPORT STATUS cp (const char * src, const char *dest);
IMPORT STATUS mv (const char * src, const char *dest);
IMPORT STATUS xcopy (const char * src, const char *dest);
IMPORT STATUS xdelete (const char * src);
IMPORT STATUS attrib (const char * fileName, const char * attr);
IMPORT STATUS xattrib (const char * fileName, const char * attr);
IMPORT STATUS dirList (int fd, const char * dirName, BOOL doLong, BOOL doTree);
IMPORT STATUS hrfsDiskFormat (const char * pDevName, int files,
			      UINT32 majorVer, UINT32 minorVer, UINT32 options);
IMPORT STATUS dosfsDiskFormat (const char * pDevName);
IMPORT STATUS commit (const char*);
IMPORT void   ioHelp (void);
#ifdef __cplusplus
}
#endif

#endif /* __INCusrFsLibh */
