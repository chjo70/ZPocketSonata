/* if_var.h - network interface variable header file */
 
/*
 * Copyright (c) 2001-2006 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */
 
/*
 * Copyright (c) 1982, 1986, 1989, 1993
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
 *	From: @(#)if.h	8.1 (Berkeley) 6/10/93
 * $FreeBSD: src/sys/net/if_var.h,v 1.98.2.5 2005/10/07 14:00:05 glebius Exp $
 * $FreeBSD: src/sys/net/if_var.h,v 1.62 2003/11/12 03:14:29 rwatson Exp $
 * $FreeBSD: src/sys/net/if_var.h,v 1.18.2.15 2002/06/28 12:36:54 luigi Exp $
 */
/*
modification history
--------------------
02p,09jan12,h_x  Move extern "C" after last header file include.
02o,25oct06,kch  Removed unused forward declarations.
02n,28sep06,kch  Removed struct ifnet since it is not supported by IPNet.
02m,10sep06,kch  Temporarily restore the ifnet structure.
02l,10sep06,kch  Restore all IF_XXX queue related macros. 
02k,09sep06,kch  Cleanup for IPNet integration.
02j,08feb06,kch  Added IFQ_LOCK_ASSERT() macro and define it as noop.
02i,06jan06,kch  Integrated FreeBSD 6.0 ALTQ implementation.
02h,21sep05,kch  Added if_xname[] to ifnet structure, introduced if_name() 
                 macro to replace if_name() routine for backward compatibility.
                 Also added if_initname() prototype (merged from FreeBSD 5.x
                 if_var.h,v 1.84.2.6) (SPR #112724).
02g,29aug05,kch  Added if_nvlans counter to ifnet structure (SPR #112068).
02f,26aug05,dlk  Add section tags.
02e,26aug05,kch  Removed pTagData pointer from ifnet structure.
02d,12aug05,kch  Moved ifclone prototypes to if_clone.h.
02c,04aug05,vvv  clarified comments for if_index and ifIndex (SPR #106657)
02b,16jul05,dlk  Added intrqFlush() declaration for VIRTUAL_STACK case.
02a,25jun05,dlk  Added INTRQ_QJOB definition.
01z,24jun05,wap  Add link state support
01y,09may05,vvv  added include for if.h
01x,19apr05,rp   merged from comp_wn_ipv6_mld_interim-dev
01w,07feb05,vvv  _KERNEL cleanup
01v,10sep04,kc   Added VLAN_TAG define to protect pTagData in ifnet structure.
01u,12jul04,vvv  fixed compiler warning
01t,28may04,niq  Merging from base6 label POST_ITER5_FRZ16_REBASE (ver
                 /main/vdt/base6_itn5_networking-int/1)
01s,14may04,kc   Added pTagData to struct ifnet for L2 VLAN Tagging support.
01r,25feb04,nee  Adding if6_resolve to ifnet
01q,24feb04,dlk  Add closing brace if __cplusplus is defined.
01p,03feb04,wap  Add extra structure fields for checksum offload support
01o,02feb04,dlk  Restore interface output queues (repair IF_ENQUEUE()).
01n,20nov03,niq  osdep.h cleanup
01m,04nov03,rlm  Ran batch header path update for header re-org.
01l,03nov03,rlm  Removed wrn/coreip/ prefix from #includes for header re-org.
01k,23oct03,rlm  updated #includes for header re-org
01j,24sep03,kkz  Rebasing with BASE6_ITER2_FRZ7 - added IF_DEQUEUEIF macro
01i,08aug03,nee  Merging from label ACCORDION_BASE6_MERGE_BASELINE in
                 accordion codeline to Base6
01h,01feb03,pas  merge from FreeBSD 4.7 - added clone support, polling;
                 changed if_queue_drop() to if_handoff()
01g,18sep02,nee  removed ifr_type from ifreq structure
01f,09sep02,hsh  add c++ protection
01e,24aug02,nee  extended ifnet for admin control;defined admin states for
                 boot/up/down
01d,13feb02,ham  changed for tornado build.
01c,06oct01,ann  removing the prototypes for ether_output and
                 ether_output_frame
01b,11sep01,ann  adding the if_resolve func pointer that is missing
01a,16jul01,ham  created from FreeBSD4.3.
*/

#ifndef	_NET_IF_VAR_H_
#define	_NET_IF_VAR_H_

#include <sys/queue.h>	/* get TAILQ macros */
#include <net/mbuf.h>

#ifdef __cplusplus
 extern "C" {
#endif

/*
 * Structure defining a queue for a network interface.
 */
struct ifqueue {
	struct	mbuf *ifq_head;
	struct	mbuf *ifq_tail;
	int	ifq_len;
	int	ifq_maxlen;
	int	ifq_drops;
};

/*
 * Output queues (ifp->if_snd) and slow device input queues (*ifp->if_slowq)
 * are queues of messages stored on ifqueue structures
 * (defined above).  Entries are added to and deleted from these structures
 * by these macros, which should be called with ipl raised to splimp().
 */
#define	IF_QFULL(ifq)		((ifq)->ifq_len >= (ifq)->ifq_maxlen)
#define	IF_DROP(ifq)		((ifq)->ifq_drops++)

#define	IF_ENQUEUE(ifq, m) \
    do  { \
	(m)->m_nextpkt = 0; \
	if ((ifq)->ifq_tail == 0) \
		(ifq)->ifq_head = m; \
	else \
		(ifq)->ifq_tail->m_nextpkt = m; \
	(ifq)->ifq_tail = m; \
	(ifq)->ifq_len++; \
        } while (0)

#define	IF_PREPEND(ifq, m) { \
	(m)->m_nextpkt = (ifq)->ifq_head; \
	if ((ifq)->ifq_tail == 0) \
		(ifq)->ifq_tail = (m); \
	(ifq)->ifq_head = (m); \
	(ifq)->ifq_len++; \
}

#define	IF_DEQUEUE(ifq, m) { \
	(m) = (ifq)->ifq_head; \
	if (m) { \
		if (((ifq)->ifq_head = (m)->m_nextpkt) == 0) \
			(ifq)->ifq_tail = 0; \
		(m)->m_nextpkt = 0; \
		(ifq)->ifq_len--; \
	} \
}


#ifdef _WRS_KERNEL

/*
 * #define _IF_QFULL for compatibility with -current
 */
#define	_IF_QFULL(ifq)			IF_QFULL(ifq)

/*
 * The following macros are defined to eliminate direct references to the
 * interface output queue 
 */
#define	IFQ_IS_EMPTY(ifq)		((ifq)->ifq_len == 0)
#define	IFQ_INC_LEN(ifq)		((ifq)->ifq_len++)
#define	IFQ_DEC_LEN(ifq)		(--(ifq)->ifq_len)
#define	IFQ_INC_DROPS(ifq)		IF_DROP(ifq)
#define	IFQ_SET_MAXLEN(ifq, len)	((ifq)->ifq_maxlen = (len))

/*
 * 72 was chosen below because it is the size of a TCP/IP
 * header (40) + the minimum mss (32).
 */
#define	IF_MINMTU	72
#define	IF_MAXMTU	65535

#endif /* _WRS_KERNEL */


#ifdef __cplusplus
}
#endif

#endif /* !_NET_IF_VAR_H_ */
