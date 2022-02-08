/* in6_var.h - IPv6 interface definitions */

/*
 * Copyright (c) 2001-2005 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*	$KAME: in6_var.h,v 1.107 2005/03/14 08:53:36 suz Exp $	*/
/*	$KAME: in6_var.h,v 1.103 2004/08/17 10:18:58 jinmei Exp $	*/
/*	$FreeBSD: src/sys/netinet6/in6_var.h,v 1.3.2.3 2002/04/28 05:40:27 suz Exp $	*/
/*	$KAME: in6_var.h,v 1.56 2001/03/29 05:34:31 itojun Exp $	*/

/*
 * Copyright (C) 1995, 1996, 1997, and 1998 WIDE Project.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the project nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE PROJECT AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE PROJECT OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

/*
 * Copyright (c) 1985, 1986, 1993
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
 *	@(#)in_var.h	8.1 (Berkeley) 6/10/93
 */

/*
modification history
--------------------
01r,09jan12,h_x  Move extern "C" after last header file include.
01q,30nov06,kch  Cleanup for IPNet integration.
01p,25jun05,dlk  Add ip6intrqJob declaration.
01o,20jun05,kch  Do not guard IN6_IFF_HOME and IN6_IFF_DEREGISTERING defines
                 with MIP6 build flag.
01n,24may05,vvv  updated for Kame merge
01m,13may05,nee  Add a IPv6 address flag IN6_IFF_SUBNETANYCAST.
01o,10may05,kch  Merged from Kame v 1.107.
01n,28apr05,kch  Moved addrsel_policyent structure definition here from
                 in6_src.c.
01m,20apr05,kch  Merged from comp_wn_ipv6_mld_interim-dev branch.
01l,16mar05,nee  Add SIOCSIFINFO_IN6
01k,07feb05,vvv  _KERNEL cleanup
01j,25jan05,vvv  fixed bitfield definitions (SPR #92171)
01i,21nov03,vvv  protected in6_prflags and in6_rrenumreq structures with INET6
01h,20nov03,niq  Remove copyright_wrs.h file inclusion
01g,05nov03,cdw  Removal of unnecessary _KERNEL guards.
01f,04nov03,rlm  Ran batch header path update for header re-org.
01e,03nov03,rlm  Removed wrn/coreip/ prefix from #includes for header re-org.
01d,12aug03,nee  Merging from label ACCORDION_BASE6_MERGE_BASELINE in
                 accordion codeline to Base6
01c,10jun03,vvv  include netVersion.h
01b,30apr03,syy  Added #ifdef for __cplusplus
01a,24jun02,ism  created new structure to hold the IPv6 MIB information
*/

#ifndef _NETINET6_IN6_VAR_H_
#define _NETINET6_IN6_VAR_H_

#ifdef _WRS_KERNEL
#include <net/if_var.h>    /* needed for struct ifaddr */
#else
#include <net/if.h>        /* needed for IFNAMSIZ */
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*
 * pltime/vltime are just for future reference (required to implements 2
 * hour rule for hosts).  they should never be modified by nd6_timeout or
 * anywhere else.
 *	userland -> kernel: accept pltime/vltime
 *	kernel -> userland: throw up everything
 *	in kernel: modify preferred/expire only
 */
struct in6_addrlifetime {
	time_t ia6t_expire;	/* valid lifetime expiration time */
	time_t ia6t_preferred;	/* preferred lifetime expiration time */
	u_int32_t ia6t_vltime;	/* valid lifetime */
	u_int32_t ia6t_pltime;	/* prefix lifetime */
};

struct	in6_ifreq {
	char	ifr_name[IFNAMSIZ];          /* if name, e.g. "eth0" */
	union {
		struct	sockaddr_in6 ifru_addr;     /* address */
		struct	sockaddr_in6 ifru_dstaddr;  /* other end of p-to-p link */
		unsigned	ifru_prefixlen;         /* address prefix length */
	} ifr_ifru;
};

struct	in6_aliasreq {
	char	ifra_name[IFNAMSIZ];
	struct	sockaddr_in6 ifra_addr;      /* The address to set */
	struct	sockaddr_in6 ifra_dstaddr;   /* Peer address for PPP interfaces */
	struct	sockaddr_in6 ifra_prefixmask; /* Mask to get the nework ID */
	int	ifra_flags;                       /* IN6_IFF_xxx flags */
	struct in6_addrlifetime ifra_lifetime;
};


#define IN6_IFF_TEMPORARY	0x01	/* temporary (anonymous) address. */
#define IN6_IFF_TENTATIVE	0x02	/* tentative address */
#define IN6_IFF_HOMEADDRESS	0x04	/* MIP6 home address */
#define IN6_IFF_DEPRECATED	0x08	/* deprecated address */
#define IN6_IFF_AUTOMATIC	0x10	/* create automatically by IPNET */ 
#define IN6_IFF_AUTONOMOUS	0x20	/* create based on prefix adv */ 
#define IN6_IFF_ANYCAST		0x40	/* anycast address */

#ifdef __cplusplus
}
#endif

#endif /* _NETINET6_IN6_VAR_H_ */
