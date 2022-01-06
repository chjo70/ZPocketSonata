/* wait.h - wait facility library header */

/*
 * Copyright (c) 2003-2006, 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement. 
 */

/*
modification history
--------------------
01h,28apr10,pad  Moved extern C statement after include statements.
01g,18jul06,jmg  removed kernel declaration of wait() and waitpid()
01f,21jun06,pcm  made pthread cancellation point modifications
01e,02feb06,mil  Updated for POSIX namespace conformance (P9*).
01d,24aug05,kk   updated wait() and waitpid() API
01c,27aug04,md   fixed WIFSIGNALED() macro
01b,26nov03,nrj  added function prototype
01a,28oct03,nrj  written from posix spec
*/

/*
 * Note: This file contains definitions that must be maintained in both kernel
 * and user space
 */

#ifndef __INCwaith
#define __INCwaith

/* includes */

#include <signal.h>

#ifdef __cplusplus
extern "C" {
#endif

/* defines */

#define WNOHANG			0x01	/* do not hang if no status is */
					/* available; return immediately */

/* not supported, for compatibility */

#define WUNTRACED		0x02	/* report status of stopped childs */

/* macros for analyzing process status */

#define	WIFEXITED(status)	((int)((status) & 0xFF00) == 0)
#define	WIFSIGNALED(status)	((int)((status) & 0xFF00) != 0)
#define	WIFSTOPPED(status)	((int)((status) & 0xFF0000) != 0)
#define	WEXITSTATUS(status)	((int)((status) & 0xFF))
#define	WTERMSIG(status)	((int)(((status) >> 8) & 0xFF))
#define	WSTOPSIG(status)	((int)(((status) >> 16) & 0xFF))

/* Only include while building kernel */

#ifdef _WRS_KERNEL

#define	SET_EXITSTATUS(status)	((int)((status)&0xFF))
#define	SET_TERMSIG(sig)	((int)(((sig)<<8)&0xFF00))
#define	SET_STOPSIG(sig)	((int)(((sig)<<16)&0xFF0000))

#else

extern pid_t wait(int *);
extern pid_t waitpid(pid_t, int *, int);
extern pid_t _waitpid(pid_t, int *, int);

#endif

#ifdef __cplusplus
}
#endif

#endif /* __INCwaith */
