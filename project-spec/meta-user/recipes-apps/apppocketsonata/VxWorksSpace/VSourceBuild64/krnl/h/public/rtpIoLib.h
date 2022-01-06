/* rtpIoLib.h - real time process I/O library header file */

/* Copyright 2003-2004, 2010 Wind River Systems, Inc. */

/*
modification history
--------------------
01h,29apr10,pad  Moved extern C statement after include statements.
01g,27jan10,lxj  changed rtpIoFdValue return type from int to long for LP64
01f,31aug04,yvp  Removed rtpIoInit().
01e,30mar04,dat  removed rtpIoFdNew. (use iosFdNew)
01d,18feb04,dat  chg'd lengths from int to size_t
01c,12nov03,pmr  default path defines
01b,10nov03,pmr  new function rtpIoFdNew().
01a,31oct03,pmr  written.
*/

#ifndef __INCrtpIoLibh
#define __INCrtpIoLibh

/* includes */

#include "vxWorks.h"
#include "dllLib.h"
#include "vwModNum.h"
#include "rtpLibCommon.h"

#ifdef __cplusplus
extern "C" {
#endif

/* must have a minimum of 3 for standard I/O */
#define RTP_IO_MIN_FDS 3

/* default length for default path */
#define RTP_IO_DEF_PATH_LEN 256

#ifndef _ASMLANGUAGE

/* function prototypes */

IMPORT  long		rtpIoFdValue (RTP_ID pRtp, int fd);
IMPORT	STATUS		rtpIoDefPathGet (RTP_ID, char *, size_t);
IMPORT	STATUS		rtpIoDefPathSet (RTP_ID, const char *);
IMPORT	size_t		rtpIoTableSizeGet (RTP_ID);
IMPORT	STATUS		rtpIoTableSizeSet (RTP_ID, size_t);

#endif  /* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCrtpIoLibh */
