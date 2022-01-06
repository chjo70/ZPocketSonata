/* in_var.h - in_var header file */

/*
 * Copyright (c) 2001-2006, 2014 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify, or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
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
 *	@(#)in_var.h	8.2 (Berkeley) 1/9/95
 * $FreeBSD: src/sys/netinet/in_var.h,v 1.33.2.3 2001/12/14 20:09:34 jlemon Exp $
 */
 
/*
 * Copyright (c) 2002 INRIA. All rights reserved.
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
 *	This product includes software developed by INRIA and its
 *	contributors.
 * 4. Neither the name of INRIA nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */
/*
 * Implementation of Internet Group Management Protocol, Version 3.
 *
 * Developed by Hitoshi Asaeda, INRIA, February 2002.
 */

/*
modification history
--------------------
31jan14,to   remove inclusion of obsolete fnv_hash.h for C99
02d,30nov06,kch  Added netinet6/in6_var.h include.
02c,09sep06,kch  Cleanup for IPNet integration
02b,02mar06,dlk  Remove references to ipflow* functions (SPR #104107).
02a,25aug05,dlk  Add section tags.
01z,13jul05,dlk  Added ipintrqJob declaration.
01y,29jun05,spm  updated for IGMPv3 support
01x,19apr05,rp   merged from comp_wn_ipv6_mld_interim-dev
01w,02mar05,niq  Make router alert support scalable
01v,25feb05,niq  merge from niqbal.tor3.mroute for IP router alert changes
01u,07feb05,vvv  _KERNEL cleanup
01t,31jan05,niq  virtual stack changes for sysctl
01s,24jan05,vvv  osdep.h cleanup
01r,23aug04,rp   merged from COMP_WN_IPV6_BASE6_ITER5_TO_UNIFIED_PRE_MERGE
01q,28may04,niq  Merging from base6 label POST_ITER5_FRZ16_REBASE (ver
                 /main/vdt/base6_itn5_networking-int/2)
01p,25nov03,ppp  added a comment around the inclusion of in6_var.h
01o,21nov03,ppp  rtp work
01n,20nov03,niq  Remove copyright_wrs.h file inclusion
01m,04nov03,rlm  Ran batch header path update for header re-org.
01l,03nov03,rlm  Removed wrn/coreip/ prefix from #includes for header re-org.
01k,23oct03,rlm  updated #includes for header re-org
01j,07aug03,niq  Merging from Accordion label ACCORDION_BASE6_MERGE_BASELINE
01i,23jul03,vvv  added _KERNEL protection to fix warnings (SPR #89813)
01h,09may03,vvv  included if.h
01g,01feb03,pas  merge from FreeBSD 4.7 - added hash table for IP addresses
01f,09sep02,hsh  add c++ protection
01e,28mar02,ppp  modified it for backward compatibilty with A.E. 1.1
01d,03dec01,niq  Sysctl changes for Clarinet
01c,02oct01,ppp  removing the guaed for in6_var.h
01b,18sep01,ppp  temporarily guarding in6_var.h by INET6 for the link process
01a,27aug01,hsh  Created from FreeBSD 4.3
*/


#ifndef _NETINET_IN_VAR_H_
#define _NETINET_IN_VAR_H_

#include <sys/queue.h>
#include <net/if.h>

#ifdef __cplusplus
 extern "C" {
#endif

struct	in_aliasreq {
	char	ifra_name[IFNAMSIZ];		/* if name, e.g. "en0" */
	struct	sockaddr_in ifra_addr;
	struct	sockaddr_in ifra_broadaddr;
#define ifra_dstaddr ifra_broadaddr
	struct	sockaddr_in ifra_mask;
};

#ifdef __cplusplus
}
#endif
    
#ifdef INET6
#include <netinet6/in6_var.h>
#endif /* INET6 */

#endif /* _NETINET_IN_VAR_H_ */
