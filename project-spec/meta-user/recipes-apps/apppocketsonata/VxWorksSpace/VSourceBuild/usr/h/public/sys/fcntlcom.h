/* fcntlcom.h - basic control types header */

/*
* Copyright (c) 1984-1999, 2005-2006, 2008, 2010, 2015-2016 Wind River Systems, Inc.
*
* The right to copy, distribute, modify or otherwise make use
* of this software may be licensed only pursuant to the terms
* of an applicable Wind River license agreement.
*/

/*
 * Copyright (c) 1983 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 */

/*
modification history
--------------------
29feb16,wap  Added O_CLOEXEC (V7COR-2528)
22feb15,jsp  Added O_ASYNC
28apr10,pad  Moved extern C statement after include statements.
09apr10,lxj  change struct flock l_pid from int type to long type for LP64
15sep08,jmp  added O_TEXT flag to allow opening a file in text translation
             mode (CQ:WIND00119715).
28jun06,jlk  added open mode flag, O_NOATIME
17oct06,jlk  Fix WIND00069548. Added _FFD_CLOEXEC for POSIX
14feb06,act  O_SYNC and variants are POSIX, should be outside #if test
13feb06,act  POSIX fixes for struct flock
12feb06,mil  Updated for POSIX namespace conformance (P2).
18oct05,md   added FCNTRL flag
01mar05,hya  added new defines to support POSIX compliance
13dec99,jkf  added _ASMLANGUAGE
25jan93,smb  added documentation for POSIX
22sep92,rrr  added support for c++
29jul92,smb  taken from UCB stdio.
*/

#ifndef __INCfcntlcomh
#define __INCfcntlcomh

/* include */

#if !defined(_POSIX_C_SOURCE) && !defined(_XOPEN_SOURCE) && \
    !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE)
#include "types/vxANSI.h"
#endif  /* _POSIX_xxx_SOURCE */

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Rewack the FXXXXX values as _FXXXX so that _POSIX_C_SOURCE works.
 */
#define	_FOPEN		(-1)	/* from sys/file.h, kernel use only */
#define	_FREAD		0x0001	/* read enabled */
#define	_FWRITE		0x0002	/* write enabled */
#define	_FNDELAY	0x0004	/* non blocking I/O (4.2 style) */
#define	_FAPPEND	0x0008	/* append (writes guaranteed at the end) */
#define	_FMARK		0x0010	/* internal; mark during gc() */
#define	_FDEFER		0x0020	/* internal; defer for next gc pass */
#define	_FASYNC		0x0040	/* signal pgrp when data ready */
#define	_FSHLOCK	0x0080	/* BSD flock() shared lock present */
#define	_FEXLOCK	0x0100	/* BSD flock() exclusive lock present */
#define	_FCREAT		0x0200	/* open with file create */
#define	_FTRUNC		0x0400	/* open with truncation */
#define	_FEXCL		0x0800	/* error on open if file exists */
#define	_FNBIO		0x1000	/* non blocking I/O (sys5 style) */
#define	_FSYNC		0x2000	/* do all writes synchronously */
#define	_FNONBLOCK	0x4000	/* non blocking I/O (POSIX style) */
#define	_FNOCTTY	0x8000	/* don't assign a ctty on this open */
#define	_FDSYNC	       0x10000	/* file data only integrity while writing */
#define	_FRSYNC	       0x20000	/* sync read operations at same level by */
				/* _FSYNC and _FDSYNC flags */
#define	_FCNTRL	       0x40000	/* special open mode for vnode ioctl's */
#define	_FNOATIME      0x80000	/* special open mode to not update access */
				/* time on close */
#define	_FFD_CLOEXEC   0x100000	/* special flag for FD_CLOEXEC */
#define _FTEXT	       0x200000 /* text translation mode */

#define	O_ACCMODE	(O_RDONLY|O_WRONLY|O_RDWR)

/*
 * Flag values for open(2) and fcntl(2)
 * The kernel adds 1 to the open modes to turn it into some
 * combination of FREAD and FWRITE.
 */
#define	O_RDONLY	0		/* +1 == FREAD */
#define	O_WRONLY	1		/* +1 == FWRITE */
#define	O_RDWR		2		/* +1 == FREAD|FWRITE */
#define	O_CREAT		_FCREAT
#define O_TEXT		_FTEXT		/* text translation mode */

/*
 * added for future POSIX extensions
 */
#define	O_APPEND	_FAPPEND
#define	O_TRUNC		_FTRUNC
#define	O_EXCL		_FEXCL
#define	O_NONBLOCK	_FNONBLOCK
#define	O_NOCTTY	_FNOCTTY
#define	O_SYNC		_FSYNC
#define	O_DSYNC		_FDSYNC
#define	O_RSYNC		_FRSYNC
#define O_ASYNC		_FASYNC
#define O_CLOEXEC	_FFD_CLOEXEC

#if !defined(_POSIX_C_SOURCE) && !defined(_XOPEN_SOURCE) && \
    !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE)

#define	O_CNTRL		_FCNTRL
#define	O_NOATIME	_FNOATIME

#define	DEFFILEMODE 	0666

/*
 * Flags that work for fcntl(fd, F_SETFL, FXXXX)
 */
#define	FAPPEND		_FAPPEND
#define	FSYNC		_FSYNC
#define	FDSYNC		_FDSYNC
#define	FRSYNC		_FRSYNC
#define	FASYNC		_FASYNC
#define	FNBIO		_FNBIO
#define	FNONBIO		_FNONBLOCK
#define	FNDELAY		_FNDELAY

/*
 * Flags that are disallowed for fcntl's (FCNTLCANT);
 * used for opens, internal state, or locking.
 */
#define	FREAD		_FREAD
#define	FWRITE		_FWRITE
#define	FMARK		_FMARK
#define	FDEFER		_FDEFER
#define	FSHLOCK		_FSHLOCK
#define	FEXLOCK		_FEXLOCK

/*
 * The rest of the flags, used only for opens
 */
#define	FOPEN		_FOPEN
#define	FCREAT		_FCREAT
#define	FTRUNC		_FTRUNC
#define	FEXCL		_FEXCL
#define	FNOCTTY		_FNOCTTY

#endif  /* _POSIX_xxx_SOURCE */

/* XXX close on exec request; must match UF_EXCLOSE in user.h */
#define	FD_CLOEXEC	1	/* posix */

/* fcntl(2) requests */
#define	F_DUPFD		0	/* Duplicate fildes */
#define	F_GETFD		1	/* Get fildes flags (close on exec) */
#define	F_SETFD		2	/* Set fildes flags (close on exec) */
#define	F_GETFL		3	/* Get file flags */
#define	F_SETFL		4	/* Set file flags */
#define	F_GETOWN 	5	/* Get owner - for ASYNC */
#define	F_SETOWN 	6	/* Set owner - for ASYNC */
#define	F_GETLK  	7	/* Get record-locking information */
#define	F_SETLK  	8	/* Set or Clear a record-lock (Non-Blocking) */
#define	F_SETLKW 	9	/* Set or Clear a record-lock (Blocking) */
#if !defined(_POSIX_C_SOURCE) && !defined(_XOPEN_SOURCE) && \
    !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE)
#define	F_RGETLK 	10	/* Test a remote lock to see if it is blocked */
#define	F_RSETLK 	11	/* Set or unlock a remote lock */
#define	F_CNVT 		12	/* Convert a fhandle to an open fd */
#define	F_RSETLKW 	13	/* Set or Clear remote record-lock(Blocking) */
#endif  /* _POSIX_xxx_SOURCE */

/* fcntl(2) flags (l_type field of flock structure) */
#define	F_RDLCK		1	/* read lock */
#define	F_WRLCK		2	/* write lock */
#define	F_UNLCK		3	/* remove lock(s) */
#if !defined(_POSIX_C_SOURCE) && !defined(_XOPEN_SOURCE) && \
    !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE)
#define	F_UNLKSYS	4	/* remove remote locks for a given system */
#endif  /* _POSIX_xxx_SOURCE */

#ifndef _ASMLANGUAGE

/* file segment locking set data type - information passed to system by user */
/* NB: l_start and l_len are off_t, but we do not know if off_t is defined */
struct flock {
	short	  l_type;	/* F_RDLCK, F_WRLCK, or F_UNLCK */
	short	  l_whence;	/* flag to choose starting offset */
	long long l_start;	/* relative offset, in bytes */
	long long l_len;	/* length, in bytes; 0 means lock to EOF */
	long	  l_pid;	/* returned with F_GETLK */
};

#if !defined(_POSIX_C_SOURCE) && !defined(_XOPEN_SOURCE) && \
    !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE)
/* extended file segment locking set data type */
struct eflock {
	short	  l_type;	/* F_RDLCK, F_WRLCK, or F_UNLCK */
	short	  l_whence;	/* flag to choose starting offset */
	long long l_start;	/* relative offset, in bytes */
	long long l_len;	/* length, in bytes; 0 means lock to EOF */
	long	  l_pid;	/* returned with F_GETLK */
	long	  l_rpid;	/* Remote process id wanting this lock */
	long	  l_rsys;	/* Remote system id wanting this lock */
};
#endif  /* _POSIX_xxx_SOURCE */

#endif /* #ifndef _ASMLANGUAGE */


#ifdef __cplusplus
}
#endif

#endif /* __INCfcntlcomh */
