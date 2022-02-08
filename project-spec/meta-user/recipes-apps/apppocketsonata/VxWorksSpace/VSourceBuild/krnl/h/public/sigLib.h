/* sigLib.h - obsolete vxWorks 5.0 header file */

/*
 * Copyright (c) 1984-1992, 2005, 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement. 
 */

/*
modification history
--------------------
01i,29apr10,pad  Moved extern C statement after include statements.
01h,08dec05,gls  increased NUM_SIGNALS to 64
01g,07dec05,gls  removed duplicate signal definitions
01f,09feb93,rrr  added SIGCONTEXT typedef for compatibility with 5.0.
01e,05feb93,rrr  fixed spr 1906 (signal numbers to match sun os)
01d,22sep92,rrr  added support for c++
01c,21sep92,rrr  more stuff to be more like 5.0.
01a,20sep92,smb  changed signalP.h to sigLibP.h
01a,19sep92,jcf  written for compatibility with 5.0.
*/

#ifndef __INCsigLibh
#define __INCsigLibh

#include <signal.h>
#include <sigCodes.h>
#include <unistd.h>
#include <private/sigLibP.h>

#ifdef __cplusplus
extern "C" {
#endif

#define NUM_SIGNALS	64

#define SIGIO		(SIGRTMIN + 0)
#define SIGWINCH	(SIGRTMIN + 5)
#define SIGLOST		(SIGRTMIN + 6)

#define SIGIOT		SIGABRT
#define SIGCLD		SIGCHLD

typedef struct sigvec SIGVEC;
typedef struct sigcontext SIGCONTEXT;

#ifdef __cplusplus
}
#endif

#endif /* __INCsigLibh */
