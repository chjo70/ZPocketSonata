/* ifaddrs.h - structure and routines for interface addresses */

/* Copyright 2001-2005 Wind River Systems, Inc. */

/*	$KAME: ifaddrs.h,v 1.3 2001/01/26 08:14:55 itojun Exp $	*/

/*
 * Copyright (c) 1995, 1999
 *	Berkeley Software Design, Inc.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * THIS SOFTWARE IS PROVIDED BY Berkeley Software Design, Inc. ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL Berkeley Software Design, Inc. BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	BSDI ifaddrs.h,v 2.5 2000/02/23 14:51:59 dab Exp
 */

/*
modification history
--------------------
01f,20nov06,kch  Added ifu_dstaddr to ifaddrs struct for compatibility with
                 IPNET. Also restored getifaddrs and freeifaddrs prototypes.
01e,28sep06,kch  Removed unsupported prototypes for IPNet integration.
01d,24may05,vvv  updated for user-side builds
01c,20nov03,niq  Remove copyright_wrs.h file inclusion
01b,06nov03,rlm  Ran batch header update for header re-org.
01a,29apr03,syy  Added #ifdef for __cplusplus
*/

#ifndef	__INCifaddrsh
#define	__INCifaddrsh

#include <sys/socket.h>

#ifdef __cplusplus
extern "C" {
#endif

struct ifaddrs {
	struct ifaddrs  *ifa_next;
	char		*ifa_name;
	u_int		 ifa_flags;
	struct sockaddr	*ifa_addr;
	struct sockaddr	*ifa_netmask;
    union {
        struct sockaddr *ifu_broadaddr;
        struct sockaddr *ifu_dstaddr;
    } ifa_ifu;
#ifndef ifa_broadaddr
#define ifa_broadaddr   ifa_ifu.ifu_broadaddr    
#endif
#ifndef ifa_dstaddr
#define ifa_dstaddr	ifa_ifu.ifu_dstaddr
#endif    
	void		*ifa_data;
};

/*
 * This may have been defined in <net/if.h>.  Note that if <net/if.h> is
 * to be included it must be included before this header file.
 */
#ifndef	ifa_broadaddr
#define	ifa_broadaddr	ifa_dstaddr	/* broadcast address interface */
#endif

extern int getifaddrs __P((struct ifaddrs **));
extern void freeifaddrs __P((struct ifaddrs *));

#ifdef __cplusplus
}
#endif

#endif /* ! __INCifaddrsh */
