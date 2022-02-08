/* ptyLib.h - UNIX library for allocating pseudo-terminal devices */

/* 
 * Copyright 1992-2002, 2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/* modification history
-----------------------
08feb15,ymz  CERT cleanup on legacy prototype
08may02,dat  cplusplus protection SPR 74987
14dec93,gae  tweaked for the simulator.
19aug93,c_s  Added ptySetNonBlocking (); mod history corrected.
18aug93,c_s  Adjusted Ultrix port.
17aug93,c_s  Added ptySetCanonical ().
02aug93,c_s  Added #include of <sys/stropts.h> in the svr4 streams case.
18sep92,c_s  Ported to Ultrix.
16sep92,c_s  Ported to IRIX.  Adjusted port to HP-UX.
10sep92,maf  conditionally include <sys/ioctl.h> or <sys/filio.h> based
		   on presence of HP-UX predefined macro "hpux."
01a,09jul92,c_s  Adapted from PtyConnection.h (in C++).
*/

#ifndef	INCptyLibh
#define	INCptyLibh

#if	defined(hpux) || defined(__hpux)
#define	_INCLUDE_XOPEN_SOURCE
#define	_INCLUDE_HPUX_SOURCE
#define	_INCLUDE_POSIX_SOURCE
#define	_INCLUDE_AES_SOURCE
#endif

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/signal.h>
#include <fcntl.h>
#include <sys/file.h>

#if	defined(hpux) || defined(__hpux)
#define	hpux
#include <sys/ioctl.h>
#include <sys/termios.h>
#define	TCSETS	TCSETATTR
#define	TCGETS	TCGETATTR
#else
#if	defined(ultrix)
#include <sys/termios.h>
#include <sys/ioctl.h>
#define	TCSETS	TCSETA
#define	TCGETS	TCGETA
#else
#if	defined(sgi)
#include <sys/ioctl.h>
#include <sys/termio.h>
#define termios termio
#define TCSETS TCSETA
#define TCGETS TCGETA
#else
#if	defined(_AIX)
#include <sys/ioctl.h>
#include <termio.h>
#include <unistd.h>
#else
#if	defined(HAVE_STREAMS_TERMIO)
#include <errno.h>
#include <sys/conf.h>
#include <sys/stropts.h>
#endif
#include <termios.h>
#include <sys/filio.h>
#include <unistd.h>
#endif
#endif
#endif
#endif

#define	PTY_MASTER 	0
#define	PTY_SLAVE 	1

#ifdef __cplusplus
extern "C" {
#endif

int ptyOpen (int fd[2], char name[2]);
int ptyBind (int fd[2], char *pgm);
int ptyBindToXterm (int fd[2], char name[2], char *title, int detachPgm);

#ifdef __cplusplus
}
#endif


#endif	/* INCptyLibh */
