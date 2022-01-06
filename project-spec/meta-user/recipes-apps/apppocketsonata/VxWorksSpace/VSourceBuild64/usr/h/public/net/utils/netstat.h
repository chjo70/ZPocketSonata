/* netstat.h - network information display header file */
 
/*
 * Copyright (c) 1984-2005 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement. No license to Wind River intellectual property rights
 * is granted herein. All rights not licensed by Wind River are reserved
 * by Wind River.
 */
  
/*
modification history
--------------------
01o,05sep06,kch  Cleanup for IPNet integration.
01n,29jun05,kch  Added sctp_protopr() and sctp_stats() prototypes.
01m,19apr05,rp   merged from comp_wn_ipv6_mld_interim-dev
01l,25feb05,niq  merge mroute changes from comp_wn_ipv6_multicast_interim-dev
                 branch  (ver 1)
01k,07feb05,vvv  _KERNEL cleanup
01j,20nov03,niq  Remove copyright_wrs.h file inclusion
01i,05nov03,cdw  Removal of unnecessary _KERNEL guards.
01h,04nov03,rlm  Ran batch header path update for header re-org.
01g,03nov03,rlm  Removed wrn/coreip/ prefix from #includes for header re-org.
01f,10jun03,vvv  include netVersion.h
01e,11apr03,ijm  fixed diab compiler warnings
01d,03apr03,vvv  modified for componentization (SPR #87352)
01c,26sep02,ppp  changing the return type for routepr from void to int
01b,09apr02,ppp  changing/ enabling a few prototypes; adding the prototype for 
		 netstat 
01a,02feb02,ppp  ported from kame
*/

/*
 * Copyright (c) 1992, 1993
 *	Regents of the University of California.  All rights reserved.
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
 *	@(#)netstat.h	8.2 (Berkeley) 1/4/94
 * $FreeBSD: src/usr.bin/netstat/netstat.h,v 1.16.2.4 2001/08/10 09:07:09 ru Exp $
 */

#ifndef  __INCnetstath
#define  __INCnetstath
 
#ifdef __cplusplus
extern "C" {
#endif

#ifdef _WRS_KERNEL
extern int netstat (char * options);
#endif /* _WRS_KERNEL*/

#ifdef __cplusplus
}
#endif
#endif /* __INCnetstath */
