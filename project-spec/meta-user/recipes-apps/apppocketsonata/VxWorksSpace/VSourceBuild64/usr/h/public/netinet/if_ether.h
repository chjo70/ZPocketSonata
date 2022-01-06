/* if_ether.h - network interface Ethernet header file */

/* Copyright 2001 - 2006, 2014 Wind River Systems, Inc. */

/*
 * Copyright (c) 1982, 1986, 1993
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
 *	@(#)if_ether.h	8.3 (Berkeley) 5/2/95
 * $FreeBSD: src/sys/netinet/if_ether.h,v 1.24.2.1 2002/02/13 21:38:56 fjoe Exp $
 */

/*
modification history
--------------------
05may14,rjq  Decouple COREIP with END. (V7NET-105)
25oct06,kch  Removed unsupported sockaddr_inarp and llinfo_arp structures.
09sep06,kch  Cleanup for IPNet integration.
23feb05,vvv  restored ether_tag_header definition for
                 backward-compatibility (SPR #102773)
18feb05,wap  Allow sysctl init routines to be scaled out
08feb05,vvv  _KERNEL cleanup
23aug04,rp   merged from COMP_WN_IPV6_BASE6_ITER5_TO_UNIFIED_PRE_MERGE
28may04,niq  Merging from base6 label POST_ITER5_FRZ16_REBASE (ver
                 /main/vdt/base6_itn5_networking-int/2)
24feb04,nee  Adding the prototype for ipEtherResolvRtn 
20nov03,niq  Remove copyright_wrs.h file inclusion
04nov03,rlm  Ran batch header path update for header re-org.
03nov03,rlm  Removed wrn/coreip/ prefix from #includes for header re-org.
23oct03,rlm  updated #includes for header re-org
15sep03,vvv  updated path for new headers
13aug03,niq  Fix definition of la_rt (Part of Accordion Base6 merge)
15may03,spm  Tornado 2.2 FCS merge (SPR #63006; ver 01h,24may02,vvv:
                 TOR2_2-FCS-COPY label, tor2 branch, /wind/river VOB)
09may03,vvv  changed include order to fix build
01may03,spm  Tornado 2.2 CP1 merge (from ver 01i,13jan03,rae:
                 TOR2_2-CP1-F label, tor2_2-patch branch, /wind/river VOB)
01feb03,pas  merge from FreeBSD 4.7 - changed arp_rtrequest(),
                 arp_ifinit() calls
09sep02,hsh  add c++ protection
13feb02,ham  changed for tornado build
09dec01,ppp  adding llinfo_arp structure  
03oct01,ann  commenting the prototype for arpintr
17sep01,ppp  Commenting out the static declaration of in_arpinput
10sep01,ann  adding some macros that could be helpful
24aug01,ann  moving the forward declaration of arpintr here from
                 if_ether.c
14aug01,ppp  Commenting out two definations.
01aug01,ppp  Created from FreeBSD 4.3
*/

#ifndef _NETINET_IF_ETHER_H_
#define _NETINET_IF_ETHER_H_


#include <cfgDefs.h>
#include <netinet/in.h>
#include <net/ethernet.h>
#include <net/if_arp.h>
#include <cfgDefs.h>

#ifdef __cplusplus
 extern "C" {
#endif
     
/* Ether header for tagged frames */

struct ether_tag_header
    {
    u_char   ether_dhost [6];
    u_char   ether_shost [6];
    u_char   etherTag [4];
    u_short  ether_type;
    };

/*
 * Macro to map an IP multicast address to an Ethernet multicast address.
 * The high-order 25 bits of the Ethernet address are statically assigned,
 * and the low-order 23 bits are taken from the low end of the IP address.
 */
#define ETHER_MAP_IP_MULTICAST(ipaddr, enaddr) \
	/* struct in_addr *ipaddr; */ \
	/* u_char enaddr[ETHER_ADDR_LEN];	   */ \
{ \
	(enaddr)[0] = 0x01; \
	(enaddr)[1] = 0x00; \
	(enaddr)[2] = 0x5e; \
	(enaddr)[3] = ((u_char *)ipaddr)[1] & 0x7f; \
	(enaddr)[4] = ((u_char *)ipaddr)[2]; \
	(enaddr)[5] = ((u_char *)ipaddr)[3]; \
}
/*
 * Macro to map an IP6 multicast address to an Ethernet multicast address.
 * The high-order 16 bits of the Ethernet address are statically assigned,
 * and the low-order 32 bits are taken from the low end of the IP6 address.
 */
#define ETHER_MAP_IPV6_MULTICAST(ip6addr, enaddr)			\
/* struct	in6_addr *ip6addr; */					\
/* u_char	enaddr[ETHER_ADDR_LEN]; */				\
{                                                                       \
	(enaddr)[0] = 0x33;						\
	(enaddr)[1] = 0x33;						\
	(enaddr)[2] = ((u_char *)ip6addr)[12];				\
	(enaddr)[3] = ((u_char *)ip6addr)[13];				\
	(enaddr)[4] = ((u_char *)ip6addr)[14];				\
	(enaddr)[5] = ((u_char *)ip6addr)[15];				\
}

#define ETHER_MULTICAST(enaddr) \
      ((enaddr)[0] == 0x1) && ((enaddr)[1] == 0x0) && ((enaddr)[2] == 0x5e) 

/*
 * Ethernet Address Resolution Protocol.
 *
 * See RFC 826 for protocol description.  Structure below is adapted
 * to resolving internet addresses.  Field names used correspond to
 * RFC 826.
 */
struct	ether_arp {
	struct	arphdr ea_hdr;	/* fixed-size header */
	u_char	arp_sha[ETHER_ADDR_LEN];	/* sender hardware address */
	u_char	arp_spa[4];	/* sender protocol address */
	u_char	arp_tha[ETHER_ADDR_LEN];	/* target hardware address */
	u_char	arp_tpa[4];	/* target protocol address */
};
#define	arp_hrd	ea_hdr.ar_hrd
#define	arp_pro	ea_hdr.ar_pro
#define	arp_hln	ea_hdr.ar_hln
#define	arp_pln	ea_hdr.ar_pln
#define	arp_op	ea_hdr.ar_op

#ifdef __cplusplus
}
#endif

#endif  /* _NETINET_IF_ETHER_H_ */
