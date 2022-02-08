/* sysLib.h - system dependent routines header file */

/*
 * Copyright (c) 2004, 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
01e,29jul10,pad  Moved extern C statement after include statements.
01d,16jun10,jpb  Removed references to sysMemTop and sysPhysMemTop for LP64
01c,20jan10,jpb  Updated syscallInfo.
01b,07jun04,job  Added sysAuxClkRateGet, sysBspRev, sysModel, sysMemTop,
                 sysPhysMemTop, sysProcNumGet prototypes.
01a,22may04,job  written 
*/

#ifndef __INCsysLibh
#define __INCsysLibh

#include <sys/sysctlCommon.h>

#ifdef __cplusplus
extern "C" {
#endif

extern int syscallInfo (int syscallNum, char * buffer, size_t * bufSize, 
                        int type);
extern int syscallNumArgsGet (int syscallNum, int * pNargs);
extern int syscallGroupNumRtnGet (int syscallGroup, int * pNargs);
extern int sysClkRateGet (void);
extern int sysAuxClkRateGet (void);
extern int sysProcNumGet (void);
extern char * sysBspRev (void);
extern char * sysModel (void);
#ifndef _WRS_CONFIG_LP64
extern char * sysMemTop (void);
extern char * sysPhysMemTop (void);
#endif /* ! _WRS_CONFIG_LP64 */

#define syscallGroupNameGet(syscallGroup, buffer, bufSize)                     \
	syscallInfo ( (syscallGroup), (buffer), (bufSize), KERN_SYSCALL_GROUP)

#define syscallPresent(syscallNum, buffer, bufSize)                          \
	syscallInfo ( (syscallNum), (buffer), (bufSize), KERN_SYSCALL_NAME)

#ifdef __cplusplus
}
#endif

#endif /* __INCsysLibh */
