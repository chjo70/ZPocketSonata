/* errno.h - errno numbers */

/*
 * Copyright (c) 1990-1993, 1995, 1998-2006, 2010, 2016-2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)errno.h	7.1 (Berkeley) 6/4/86
 */

/*
modification history
--------------------
20may17,dlk  adding EDOOM (F5593)
23dec16,h_k  cleaned up a compiler warning in LLVM. (F5261)
28apr10,pad  Moved extern C statement after include statements.
04aug06,pad  Let's not include types/vxANSI.h for strictly conforming
             POSIX applications.
24jan06,mil  Updated for POSIX namespace conformance (P1).
21dec05,pad  Added definitions for EMULTIHOP, ENOLINK and ESTALE errnos.
19dec05,pad  Added missing POSIX error codes.
24jan05,vvv  added EDQUOT
05nov03,mcm  Adding EFPOS, EILSEQ
21jun00,rsh  upgrade to dosFs 2.0
10feb99,spm  added comments for STREAMS errors and updated ERRMAX value
30jun98,lrn  added ERRNO_PX_FLAG and MAP_ERRNO_2_POSIX (SPR#20700)
20aug95,jag  added ENOSR ENOSTR EPROTO EBADMSG ENODATA ETIME ENOMSG
15nov93,dvs  added ENOSYS and ECANCELED
13nov92,dnw  added conditional definition of errno for non-ANSI (SPR #1771)
02oct92,srh  added c++ version of errno macro
22sep92,rrr  added support for c++
18jul92,smb  finished ANSI merge
08jul92,smb  Phase 1 of ANSI merge
04jul92,jcf  cleaned up.
26may92,rrr  the tree shuffle
04oct91,rrr  passed through the ansification filter
              -changed ASMLANGUAGE to _ASMLANGUAGE
              -changed copyright notice
25oct90,dnw  removed some unused definitions.
05oct90,shl  added copyright notice.
24sep90,elr  ifdef'd errno declaration for assembly.
13jul90,dnw  added declaration of errno for ANSI compliance
*/

/*
 * Note: This file contains definitions that must be maintained in both kernel
 * and user space
 */

#ifndef __INCerrnoh
#define __INCerrnoh

#if !defined(_POSIX_C_SOURCE) && !defined(_XOPEN_SOURCE) && \
     !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE)
#include <types/vxANSI.h>
#endif  /* _POSIX_xxx_SOURCE */

#ifdef __cplusplus
extern "C" {
#endif

/*
 * POSIX Error codes
 */

#define	EPERM		1		/* Not owner */
#define	ENOENT		2		/* No such file or directory */
#define	ESRCH		3		/* No such process */
#define	EINTR		4		/* Interrupted system call */
#define	EIO		5		/* I/O error */
#define	ENXIO		6		/* No such device or address */
#define	E2BIG		7		/* Arg list too long */
#define	ENOEXEC		8		/* Exec format error */
#define	EBADF		9		/* Bad file number */
#define	ECHILD		10		/* No children */
#define	EAGAIN		11		/* No more processes */
#define	ENOMEM		12		/* Not enough core */
#define	EACCES		13		/* Permission denied */
#define	EFAULT		14		/* Bad address */
#define	ENOTEMPTY	15		/* Directory not empty */
#define	EBUSY		16		/* Mount device busy */
#define	EEXIST		17		/* File exists */
#define	EXDEV		18		/* Cross-device link */
#define	ENODEV		19		/* No such device */
#define	ENOTDIR		20		/* Not a directory*/
#define	EISDIR		21		/* Is a directory */
#define	EINVAL		22		/* Invalid argument */
#define	ENFILE		23		/* File table overflow */
#define	EMFILE		24		/* Too many open files */
#define	ENOTTY		25		/* Not a typewriter */
#define	ENAMETOOLONG	26		/* File name too long */
#define	EFBIG		27		/* File too large */
#define	ENOSPC		28		/* No space left on device */
#define	ESPIPE		29		/* Illegal seek */
#define	EROFS		30		/* Read-only file system */
#define	EMLINK		31		/* Too many links */
#define	EPIPE		32		/* Broken pipe */
#define	EDEADLK		33		/* Resource deadlock avoided */
#define	ENOLCK		34		/* No locks available */
#define	ENOTSUP		35		/* Unsupported value */
#define	EMSGSIZE	36		/* Message size */

/* ANSI math software */
#define	EDOM		37		/* Argument too large */
#define	ERANGE		38		/* Result too large */

/* This one is VxWorks specific */
#define EDOOM           39              /* Task deletion attempt in progress */

/* ipc/network software */

	/* argument errors */
#define	EDESTADDRREQ	40		/* Destination address required */
#define	EPROTOTYPE	41		/* Protocol wrong type for socket */
#define	ENOPROTOOPT	42		/* Protocol not available */
#define	EPROTONOSUPPORT	43		/* Protocol not supported */
#define	ESOCKTNOSUPPORT	44		/* Socket type not supported */
#define	EOPNOTSUPP	45		/* Operation not supported on socket */
#define	EPFNOSUPPORT	46		/* Protocol family not supported */
#define	EAFNOSUPPORT	47		/* Addr family not supported */
#define	EADDRINUSE	48		/* Address already in use */
#define	EADDRNOTAVAIL	49		/* Can't assign requested address */
#define	ENOTSOCK	50		/* Socket operation on non-socket */

	/* operational errors */
#define	ENETUNREACH	51		/* Network is unreachable */
#define	ENETRESET	52		/* Network dropped connection on reset*/
#define	ECONNABORTED	53		/* Software caused connection abort */
#define	ECONNRESET	54		/* Connection reset by peer */
#define	ENOBUFS		55		/* No buffer space available */
#define	EISCONN		56		/* Socket is already connected */
#define	ENOTCONN	57		/* Socket is not connected */
#define	ESHUTDOWN	58		/* Can't send after socket shutdown */
#define	ETOOMANYREFS	59		/* Too many references: can't splice */
#define	ETIMEDOUT	60		/* Connection timed out */
#define	ECONNREFUSED	61		/* Connection refused */
#define	ENETDOWN	62		/* Network is down */
#define	ETXTBSY		63		/* Text file busy */
#define	ELOOP		64		/* Too many levels of symbolic links */
#define	EHOSTUNREACH	65		/* No route to host */
#define	ENOTBLK		66		/* Block device required */
#define	EHOSTDOWN	67		/* Host is down */

/* non-blocking and interrupt i/o */
#define	EINPROGRESS	68		/* Operation now in progress */
#define	EALREADY	69		/* Operation already in progress */
#define	EWOULDBLOCK	70		/* Operation would block */

#define	ENOSYS		71		/* Function not implemented */

/* aio errors (should be under posix) */
#define	ECANCELED	72		/* Operation canceled */

/* specific STREAMS errno values */
#define ENOSR           74              /* Insufficient memory */
#define ENOSTR          75              /* STREAMS device required */
#define EPROTO          76              /* Generic STREAMS error */
#define EBADMSG         77              /* Invalid STREAMS message */
#define ENODATA         78              /* Missing expected message data */
#define ETIME           79              /* STREAMS timeout occurred */
#define ENOMSG          80              /* Unexpected message type */ 

#define EFPOS		81		/* File positioning error */
#define EILSEQ		82		/* Illegal byte sequence. */

/* error codes used by network stack */

#define EDQUOT          83              /* routing error */

#define	EIDRM		84		/* Identifier removed */
#define	EOVERFLOW	85		/* Value too large for data type */
#define EMULTIHOP	86		/* Reserved */
#define ENOLINK		87		/* Reserved */
#define ESTALE		88		/* Reserved */

#define	ERRMAX		89

/* for module specific error codes which can be mapped to one of the above */

#define ERRNO_PX_FLAG		(1<<15)

/* macro to map module-specific error codes to POSIX if applicable */

#define	_VX_MAP_ERRNO_2_POSIX(errno)	\
	(((errno) & ERRNO_PX_FLAG)? (errno) &= 0x7fff : (errno) )
#if !defined(_POSIX_C_SOURCE) && !defined(_XOPEN_SOURCE) && \
    !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE)
#define	MAP_ERRNO_2_POSIX(errno)	\
	(((errno) & ERRNO_PX_FLAG)? (errno) &= 0x7fff : (errno) )
#endif  /* _POSIX_xxx_SOURCE */

#ifndef _ASMLANGUAGE

extern int *	__errno (void);

#endif	/* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

/* Definition of errno */

#ifndef _ASMLANGUAGE

#ifdef __cplusplus

inline int &__errnoRef()
    {
    return (*__errno());
    }

#define errno   __errnoRef()

#else

#define errno	(*__errno())

#endif  /* __cplusplus */

#endif	/* _ASMLANGUAGE */

#endif /* __INCerrnoh */
