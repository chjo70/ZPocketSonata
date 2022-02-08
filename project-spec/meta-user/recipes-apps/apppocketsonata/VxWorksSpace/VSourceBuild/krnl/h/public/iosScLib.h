/* iosScLib.h - real time process IO system library header file */

/* Copyright 2003, 2010 Wind River Systems, Inc. */

/*
modification history
--------------------
01b,29apr10,pad  Moved extern C statement after include statements.
01a,21oct03,dat  written, from rtpLib.h, v01i
*/

#ifndef __INCiosScLibh
#define __INCiosScLibh

/* includes */

#include "vxWorks.h"
#include "rtpLibCommon.h"

#ifdef __cplusplus
extern "C" {
#endif

/* defines */

/* externs */

#ifndef	_ASMLANGUAGE

/* function declarations */

extern STATUS 	iosScLibInit (void);

#endif	/* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCiosScLibh */
