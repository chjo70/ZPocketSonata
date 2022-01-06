/* uio.h - i/o vectors for reading and writing */

/* Copyright (c) 2001-2006, 2009, 2012, 2013, 2016 Wind River Systems, Inc. */

/*
 * Copyright (c) 1982, 1986, 1993, 1994
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	@(#)uio.h	8.5 (Berkeley) 2/22/94
 * $FreeBSD: src/sys/sys/uio.h,v 1.11.2.1 2001/09/28 16:58:35 dillon Exp $
 */

/*
modification history
--------------------
20apr16,dlk  Declare uiomove() for in-kernel use.
18feb16,zl   updated for shared user/kernel space
20sep13,h_k  added sys/uio.h in vxcore.
             removed UIO_SMALLIOV macro.
             moved readv and writev externs from ioLib.h.
             added limits.h header inclusion and defined UIO_MAXIOV as
             IOV_MAX.
09jan12,h_x  Move extern "C" after last header file include.
03jul09,zly  LP64-bit support
06apr06,jlk  SPR 119965. Changed uio->uio_offset to an off_t64.
15feb05,vvv  include cdefs.h only in kernel
24jan05,vvv  osdep.h cleanup
23aug04,rp   merged from COMP_WN_IPV6_BASE6_ITER5_TO_UNIFIED_PRE_MERGE
20nov03,niq  Remove copyright_wrs.h file inclusion
04nov03,rlm  Ran batch header path update for header re-org.
03nov03,rlm  Removed wrn/coreip/ prefix from #includes for header re-org.
27oct03,cdw  update include statements post header re-org.
01feb03,pas  merge from FreeBSD 4.7 - added uio_yield()
06sep02,hsh  add c++ protection
02feb02,ham  changed for tornado build.
15aug01,ann  ported to clarinet from FreeBSD 4.3 ver 1.11
*/

#ifndef _SYS_UIO_H_
#define	_SYS_UIO_H_

#include <sys/types.h>
#ifdef _WRS_KERNEL
#include <limits.h>
#include <sys/cdefs.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*
 * kernel definitions and declarations are different for backward
 * compatibility
 */

struct iovec
    {
#ifdef _WRS_KERNEL
    char	*iov_base;	/* Base address. */
#else
    void 	*iov_base;	/* Base address. */
#endif
    size_t	 iov_len;	/* Length. */
    };

#if !defined(_POSIX_C_SOURCE) && !defined(_XOPEN_SOURCE) && \
    !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE)

/*
 * Limits. Note, the maximum size of cluster in the network stack system
 * buffer pool may impose a more stringent limit than UIO_MAXIOV.
 */

#define UIO_MAXIOV	IOV_MAX		/* max number of iov's */

enum uio_rw
    {
    UIO_READ,
    UIO_WRITE
    };

/* Segment flag values. */

enum uio_seg
    {
    UIO_USERSPACE,		/* from user data space */
    UIO_SYSSPACE,		/* from system space */
    UIO_USERISPACE,		/* from user I space */
    UIO_NOCOPY			/* don't copy, already in object */
    };

struct uio
    {
    struct	iovec *uio_iov;
    int		uio_iovcnt;
#ifdef _WRS_KERNEL
    off64_t	uio_offset;
#else
    off_t	uio_offset;
#endif
    size_t	uio_resid;
    enum	uio_seg uio_segflg;
    enum	uio_rw uio_rw;
    struct	proc *uio_procp;
    };

#endif  /* _POSIX_xxx_SOURCE */


#ifdef _WRS_KERNEL

extern ssize_t  readv (int fd, struct iovec * iov, int iovcnt);
extern ssize_t  writev (int fd, struct iovec * iov, int iovcnt);
extern int	uiomove (caddr_t cp, size_t n, struct uio * uio);

#else /* _WRS_KERNEL */

extern ssize_t  readv (int fd, const struct iovec * iov, int iovcnt);
extern ssize_t  writev (int fd, const struct iovec * iov, int iovcnt);
extern int	uiomove (caddr_t cp, size_t n, struct uio * uio);

#endif /* _WRS_KERNEL */

#ifdef __cplusplus
}
#endif

#endif /* !_SYS_UIO_H_ */
