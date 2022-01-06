/* mbuf.h - mbuf header file */

/* Copyright 2001-2006, 2008 Wind River Systems, Inc. */

/*
 * Copyright (c) 1982, 1986, 1988, 1993
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
 *	@(#)mbuf.h	8.5 (Berkeley) 2/19/95
 * $FreeBSD: src/sys/sys/mbuf.h,v 1.44.2.26 2004/06/17 00:08:21 fjoe Exp $
 */

/*
modification history
--------------------
    08mar16,mca  Enable user-space build.
02p,22may12,dhe  M_COPY_PKTHDR() now copies also offset2 field.
02o,09jan12,h_x  Move extern "C" after last header file include.
02n,18mar08,dlk  Added CSUM_IPHDR_OFFSET(). Modified CSUM_IPHDR_LEN() to
                 use mBlkHdr.offset2 instead of mBlkHdr.offset1.
02m,27dec06,kch  Removed references to the obsolete coreip virtual stack.
02l,12sep06,kch  Replaced (struct ifnet *) with (void *) for m_devget()
                 prototype.
02k,15sep05,kch  Added CSUM_PTAGGED for 802.1P priority-tagged frame support
                 (SPR #112513).
02j,07sep05,kch  Removed CSUM_NOVLAN (SPR #112068).
02i,01sep05,sar  Add M_WRITEABLE check to M_LEADINGSPACE and
                 M_TRAILINGSPACE to ensure we don't overwrite
                 part of a buffer that we shouldn't.
02h,28jul05,dlk  Added CSUM_VLAN and CSUM_NOVLAN.
02g,12jul05,vvv  merged M_NOTIFICATION from kame-20050404-freebsd411
02f,17jun05,dlk  Make m_copym(), m_copypacket(), and m_copydata() macros also.
02e,16may05,dlk  Make m_freem() and m_free() macros for better performance.
02d,22apr05,kch  Fixed diab compilation error for MCLGET1() macro.
02c,07feb05,vvv  _KERNEL cleanup
02b,24jan05,vvv  osdep.h cleanup
02a,20jan05,sar  Removal of unused m_dup routine.
01z,23aug04,rp   merged from COMP_WN_IPV6_BASE6_ITER5_TO_UNIFIED_PRE_MERGE
01y,01jul04,vvv  fixed warnings
01x,28may04,niq  Merging from base6 label POST_ITER5_FRZ16_REBASE (ver
                 /main/vdt/base6_itn5_networking-int/1)
01w,05feb04,wap  Make M_COPY_PKTHDR() preserve extra fields in mBlkHdr
01v,06jan04,vvv  removed dtom, modified allocation macros to not store mbuf
		 back-pointer (SPR #88742)
01u,20nov03,niq  Remove copyright_wrs.h file inclusion
01t,04nov03,rlm  Ran batch header path update for header re-org.
01s,03nov03,rlm  Removed wrn/coreip/ prefix from #includes for header re-org.
01r,27oct03,cdw  update include statements post header re-org.
01q,18aug03,nee  Merging from ACCORDION_BASE6_MERGE_BASELINE. Only
                 virtualixation related changes are being merged in.
01p,09jul03,syy  Back out the previous fix to SPR#88742
01o,06jun03,pas  fix M_LEADINGSPACE to account for hidden back-ptr (SPR#88742)
01n,14may03,vvv  make routines available when _KERNEL is not defined
01m,01may03,spm  Tornado 2.2 CP1 merge (from ver 01n,21mar02,vvv:
                 TOR2_2-CP1-F label, tor2_2-patch branch, /wind/river VOB)
01l,15apr03,syy  Fixed Diab compiler warnings
01k,01feb03,pas  merge from FreeBSD 4.7 - added packet tags
01j,30sep02,sar  Add M_SECURE_PKT to the list of mflags
01i,23aug02,ann  extended MGETHDR1 and MGET1 to recognize bestfit and closefit
01h,20jun02,ann  redefined MGET1/MGETHDR1/MCLGET1
01g,07jun02,pas  new version of MGET/MGETHDR/MCLGET takes size argument
01f,29apr02,deg  back to old netBufLib
01e,22mar02,deg  MFREE auxiliary chain freeing removed (moved to _mBlkFree())
01d,06feb02,ham  changed for tornado build.
01c,05feb02,deg  bugfix in MCLGET()
01b,11dec01,ppp  correcting m_pktdat
01a,08sep01,qli  fixed mtod
01a,09aug01,deg  written.
*/

#ifndef __INCNewMbufh
#define __INCNewMbufh

#include <netBufLib.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Note that any file which uses _pNetDpool or _pNetSysPool, either directly
 * or via the macros (MGET1 etc) MUST include vsNetCore.h for Virtual Stack.
 */

extern NET_POOL_ID   _pNetDpool;		/* network data pool */
extern NET_POOL_ID	 _pNetSysPool;		/* network system pool */

extern M_CL_CONFIG       pktMblkClBlkDesc;	/* mBlk, clBlk configuration */
extern CL_DESC 	         pktClDescTbl [];	/* cluster configuration */
extern UINT		 pktClDescTblNumEnt;    /* no. elements in the table */

extern M_CL_CONFIG       sysMblkClBlkDesc;	/* mBlk, clBlk configuration */
extern CL_DESC 	         sysClDescTbl [];	/* cluster configuration */
extern UINT		 sysClDescTblNumEnt;    /* no. elements in the table */


/*
 * Mbufs are of a single size, MSIZE (machine/param.h), which
 * includes overhead.  An mbuf may add a single "mbuf cluster" of size
 * MCLBYTES (also in machine/param.h), which has no additional overhead
 * and is used instead of the internal data area; this is done when
 * at least MINCLSIZE of data must be stored.
 */

#define SIMCLSIZE      128       /* cluster size to simulate mbuf data space */

#define MCLBYTES       2048      /* mbuf cluster size */


#define	MLEN	       SIMCLSIZE
#define	MHLEN	       MLEN
#define	MINCLSIZE      (MHLEN + 1) /* smallest amount to put in cluster */

/*
 * Macro for type conversion
 * mtod(m, t) -	convert mbuf pointer to data pointer of correct type
 */

#define	mtod(m, t)    ((t)((m)->m_data))

/* Clarinet defs */
#define mbuf            mBlk
#define	m_next		mBlkHdr.mNext
#define	m_len		mBlkHdr.mLen
#define	m_data		mBlkHdr.mData
#define	m_type		mBlkHdr.mType
#define	m_flags		mBlkHdr.mFlags
#define	m_nextpkt	mBlkHdr.mNextPkt
#define	m_act		m_nextpkt
#define	m_pkthdr	mBlkPktHdr
#define	m_ext		pClBlk

#define m_hdr           mHdr
#define mh_next         mNext
#define mh_nextpkt      mNextPkt
#define mh_data         mData
#define mh_len          mLen
#define mh_type         mType
#define mh_flags        mFlags

#define m_extBuf	m_ext->clNode.pClBuf
#define m_extSize	m_ext->clSize
#define m_extRefCnt	m_ext->clRefCnt
#define m_extFreeRtn	m_ext->pClFreeRtn
#define m_extArg1	m_ext->clFreeArg1
#define m_extArg2	m_ext->clFreeArg2
#define m_extArg3	m_ext->clFreeArg3


/*
 * It is not possible to port m_ext.ext_buf and m_ext.ext_free
 * Change your code :
 * m_ext.ext_buf to m_extBuf
 * m_ext.ext_free to m_extFreeRtn
 */
#define	m_pktdat	m_ext->clNode.pClBuf
#define	m_dat		m_ext->clNode.pClBuf

#define	M_PROTO1	0x0008	/* protocol-specific */
#define	M_PROTO2	0x0010	/* protocol-specific */
#define	M_PROTO3	0x0020	/* protocol-specific */
#define	M_PROTO4	0x0040	/* protocol-specific */

/* The M_PROTO5 flag has been removed to allow the bit to be
 * used as the SECURE_PKT bit.  The define has been left in
 * as part of the history of the file and should be removed
 * in the future.
 * sar
 */
#if 0
#define	M_PROTO5	0x0080	/* protocol-specific */
#endif
#define M_SECURE_PKT    0x0080  /* For use by Wind River IPSec product */

#define	M_FRAG		0x0400	/* packet is a fragment of a larger packet */
#define	M_FIRSTFRAG	0x0800	/* packet is first fragment */
#define	M_LASTFRAG	0x1000	/* packet is last fragment */

#define M_NOTIFICATION	0x8000	/* notification event */

/* flags copied when copying m_pkthdr */
#define	M_COPYFLAGS	(M_PKTHDR|M_EOR|M_PROTO1|M_PROTO1|M_PROTO2|M_PROTO3 | \
			    M_PROTO4|M_SECURE_PKT|M_BCAST|M_MCAST|M_FRAG)

/* flags indicating hw checksum support and sw checksum requirements */
#define CSUM_IP			0x0001		/* will csum IP */
#define CSUM_TCP		0x0002		/* will csum TCP */
#define CSUM_UDP		0x0004		/* will csum UDP */
#define CSUM_IP_FRAGS		0x0008		/* will csum IP fragments */
#define CSUM_FRAGMENT		0x0010		/* will do IP fragmentation */
#define CSUM_TCP_SEG		0x0020		/* will segment TCP/IPv4 */
#define CSUM_TCPv6		0x0040		/* will csum TCP/IPv6 */
#define CSUM_UDPv6		0x0080		/* will csum UDP/IPv6 */
#define CSUM_TCPv6_SEG		0x0100		/* will csum TCP/IPv6 */
#define CSUM_VLAN		0x0200		/* insert or extracted VLAN */
#define CSUM_PTAGGED		0x0400          /* send priority-tagged frame */

#define CSUM_IP_CHECKED		0x1000		/* did csum IP */
#define CSUM_IP_VALID		0x2000		/*   ... the csum is valid */
#define CSUM_DATA_VALID		0x4000		/* csum_data field is valid */
#define CSUM_PSEUDO_HDR		0x8000		/* csum_data has pseudo hdr */

#define CSUM_DELAY_DATA		(CSUM_TCP | CSUM_UDP)
#define CSUM_DELAY_IP		(CSUM_IP)	/* XXX add ipv6 here too? */
#define CSUM_DELAY_DATA6        (CSUM_TCPv6 | CSUM_UDPv6)

#define CSUM_RESULTS            (CSUM_IP_CHECKED | CSUM_IP_VALID | \
                                 CSUM_DATA_VALID | CSUM_PSEUDO_HDR)

/*
 * CSUM_IPHDR_OFFSET() is the network service offset, i.e. the
 * offset from the start of the link header to the start of the
 * network layer (IP) header. It includes LLC/SNAP if present.
 */
#define CSUM_IPHDR_OFFSET(pMblk) ((pMblk)->mBlkHdr.offset1)
#define CSUM_IP_HDRLEN(pMblk) ((pMblk)->mBlkHdr.offset2)
#define CSUM_XPORT_HDRLEN(pMblk) \
        (((pMblk)->mBlkPktHdr.csum_data & 0xff00) >> 8)
#define CSUM_XPORT_CSUM_OFF(pMblk) ((pMblk)->mBlkPktHdr.csum_data & 0xff)


/* malloc flags (sys/malloc.h) */
#define	M_NOWAIT       M_DONTWAIT
#define	M_WAITOK       M_WAIT
#define M_CLOSEFIT     0x02

/*
 * mbuf allocation/deallocation macros:
 *
 *	MGET(struct mbuf *m, int how, int type)
 * allocates an mbuf and initializes it to contain internal data.
 *
 *	MGETHDR(struct mbuf *m, int how, int type)
 * allocates an mbuf and initializes it to contain a packet header
 * and internal data.
 */

/* Clarinet: This one gets an mbuf with attached cluster, to replace
 * the MGET()/MCLGET() paired calls.  This should save some time by
 * avoiding allocating a 128-byte cluster, freeing it, allocating a
 * larger cluster, and joining it to the clBlk.
 */
#define	MGET1(m, size, how, type)                                          \
                    {                                                      \
                    (m) = netTupleGet (_pNetDpool, size < SIMCLSIZE ? SIMCLSIZE : size, \
				       (how & M_NOWAIT), (type),           \
				       ((how & M_CLOSEFIT) ?               \
                                        FALSE : TRUE));                    \
                    }

/* Following change is to eliminate Diab compiler warning 1606 */

#define	MGET(m, how, type)	                                           \
                    {                                                      \
                    (m) = netTupleGet (_pNetDpool, SIMCLSIZE,              \
				       (how & M_NOWAIT), (type),           \
				       ((how & M_CLOSEFIT) ?               \
                                        FALSE : TRUE));                    \
                    }

#define	MGETHDR1(m, size, how, type)                                       \
                    {                                                      \
		    int i = size;                                          \
                                                                           \
                    (m) = netTupleGet(_pNetDpool, i < SIMCLSIZE ? SIMCLSIZE : i, \
				      (how & M_NOWAIT), (type),             \
				      ((how & M_CLOSEFIT) ? FALSE : TRUE)); \
		    if ((m) != NULL)                                        \
		        (m)->m_flags |= M_PKTHDR;                           \
                    }

/* Following change is to eliminate Diab compiler warning 1606 */

#define	MGETHDR(m, how, type)	                                        \
                    {                                                   \
                    (m) = netTupleGet (_pNetDpool, SIMCLSIZE,           \
				       (how & M_NOWAIT), (type),             \
				       ((how & M_CLOSEFIT) ? FALSE : TRUE)); \
		    if ((m) != NULL)                                        \
		        (m)->m_flags |= M_PKTHDR;                           \
                    }

#define	MCLGET1(m, size, how)                                           \
                    {                                                   \
                      char *    pClBuf;                                 \
		      CL_POOL_ID pClPool;                               \
                                                                        \
                      if ((m)->m_flags & M_EXT)                         \
			{                                  	  	\
	  		  netClFree((m)->pClBlk->pNetPool,              \
			            (UCHAR *)(m)->pClBlk->clNode.pClBuf);        \
                          (m)->m_flags &= ~M_EXT;                       \
			}                                               \
                                                                        \
                      if ((pClPool = netClPoolIdGet(_pNetDpool,         \
                                                   (size),              \
						   TRUE)) != NULL)      \
             		  {                                             \
                          if ((pClBuf = netClusterGet(_pNetDpool,       \
				  		     pClPool)) != NULL) \
			      {                                         \
			      netClBlkJoin((m)->m_ext,                  \
                                           pClBuf,                      \
                                           (size),                      \
					   0,0,0,0);                    \
                              netMblkClJoin((m), (m)->m_ext);           \
			      }                                         \
                          }                                             \
                    }

#define MCLGET(m, how) MCLGET1(m, MCLBYTES, how)

/*
 * MFREE(struct mbuf *m, struct mbuf *n)
 * Free a single mbuf and associated external storage.
 * Place the successor, if any, in n.
 *
 * we do need to check non-first mbuf for m_aux, since some of existing
 * code does not call M_PREPEND properly.
 * (example: call to bpf_mtap from drivers)
 */
#define	MFREE(m, n) (n) = netMblkClFree((m))

/*
 * Copy mbuf pkthdr from "from" to "to".
 * from must have M_PKTHDR set, and to must be empty.
 * aux pointer will be moved to `to'.
 */
#define	M_COPY_PKTHDR(to, from)                                         \
                    {                                                   \
                      struct mbuf *_mfrom = (from);		        \
	              struct mbuf *_mto = (to);	                        \
                      _mto->mBlkHdr.reserved = _mfrom->mBlkHdr.reserved;\
                      _mto->mBlkHdr.offset1 = _mfrom->mBlkHdr.offset1;	\
                      _mto->mBlkHdr.offset2 = _mfrom->mBlkHdr.offset2;	\
                      _mto->m_flags = _mfrom->m_flags;   	        \
	              _mto->m_pkthdr = _mfrom->m_pkthdr;                \
                      _mfrom->m_pkthdr.aux = (struct mbuf *)NULL;       \
		    }

/*
 * Set the m_data pointer of a newly-allocated mbuf (m_get/MGET) to place
 * an object of the specified size at the end of the mbuf, longword aligned.
 */
#define	M_ALIGN(m, len) ((m)->m_data +=                                   \
			 ((m)->m_extSize - (len)) &~ (sizeof(long) - 1))

/*
 * As above, for mbufs allocated with m_gethdr/MGETHDR
 * or initialized by M_COPY_PKTHDR.
 */
#define	MH_ALIGN(m, len) (M_ALIGN((m),(len)))

/*
 * Check if we can write to an mbuf.
 */
#define M_WRITABLE(m) ((m)->m_extRefCnt == 1)

/* For M_LEADINGSPACE and M_TRAILINGSPACE the
 * M_WRITABLE() is a conservative safety measure. */

/*
 * Compute the amount of space available
 * before the current start of data in an mbuf.
 */
#define	M_LEADINGSPACE(m) \
  (M_WRITABLE(m) ? ((m)->m_data - (m)->m_extBuf) : 0)
/*
 * Compute the amount of space available
 * after the end of data in an mbuf.
 */
#define	M_TRAILINGSPACE(m) \
  (M_WRITABLE(m) ? ((m)->m_extBuf + (m)->m_extSize - \
                    (m)->m_data - (m)->m_len) \
                    : 0)

/*
 * Arrange to prepend space of size plen to mbuf m.
 * If a new mbuf must be allocated, how specifies whether to wait.
 * If how is M_DONTWAIT and allocation fails, the original mbuf chain
 * is freed and m is set to NULL.
 */

#ifndef	STANDALONE_AGENT
#define	M_PREPEND(m, plen, how)                                         \
                    {                                                   \
                    if (M_LEADINGSPACE(m) >= (plen))   			\
		      { 		                                \
                        (m)->m_data -= (plen);       		     	\
		        (m)->m_len += (plen); 			        \
	              }    					        \
                    else                                                \
                      (m) = m_prepend((m), (plen), (how)); 		\
	            if ((m) && (m)->m_flags & M_PKTHDR) 		\
		      (m)->m_pkthdr.len += (plen);                      \
    	            }
#else	/* STANDALONE_AGENT */
/*
 * for standalone agent, the M_PREPEND routine does no try to allocate
 * a new buffer (there is no available). Anyway, this is not needed since
 * all the WDB packets can be stored in one buffer.
 */

#define	M_PREPEND(m, plen, how)					\
    { 								\
	if (M_LEADINGSPACE(m) >= (plen)) { 			\
		(m)->m_data -= (plen); 				\
		(m)->m_len += (plen); 				\
	} else 							\
		(m) = NULL;			 		\
	if ((m) && (m)->m_flags & M_PKTHDR) 			\
		(m)->m_pkthdr.len += (plen); 			\
    }
#endif	/* STANDALONE_AGENT */

/* change mbuf to new type */
#define	MCHTYPE(m, t) (_pNetDpool->mBlkStat.types[(m)->m_type]--;       \
                       _pNetDpool->mBlkStat.types[(t)]++;               \
                       (m)->m_type = (t))

/* compatibility with 4.3 */

/*
 * pkthdr.aux type tags.
 */
struct mauxtag {
	int	af;
	int	type;
	void*	p;
};

/*
 * Some packet tags to identify different mbuf annotations.
 *
 * Eventually, these annotations will end up in an appropriate chain
 * (struct m_tag or similar, e.g. as in NetBSD) properly managed by
 * the mbuf handling routines.
 *
 * As a temporary and low impact solution to replace the even uglier
 * approach used so far in some parts of the network stack (which relies
 * on global variables), these annotations are stored in MT_TAG
 * mbufs (or lookalikes) prepended to the actual mbuf chain.
 *
 *	m_type	= MT_TAG
 *	m_flags	= m_tag_id
 *	m_next	= next buffer in chain.
 *
 * BE VERY CAREFUL not to pass these blocks to the mbuf handling routines.
 *
 */

#define	m_tag_id	m_flags

/* Packet tag types -- first ones are from NetBSD */

#define	PACKET_TAG_NONE				0  /* Nadda */
#define	PACKET_TAG_IPSEC_IN_DONE		1  /* IPsec applied, in */
#define	PACKET_TAG_IPSEC_OUT_DONE		2  /* IPsec applied, out */
#define	PACKET_TAG_IPSEC_IN_CRYPTO_DONE		3  /* NIC IPsec crypto done */
#define	PACKET_TAG_IPSEC_OUT_CRYPTO_NEEDED	4  /* NIC IPsec crypto req'ed */
#define	PACKET_TAG_IPSEC_IN_COULD_DO_CRYPTO	5  /* NIC notifies IPsec */
#define	PACKET_TAG_IPSEC_PENDING_TDB		6  /* Reminder to do IPsec */
#define	PACKET_TAG_BRIDGE			7  /* Bridge processing done */
#define	PACKET_TAG_GIF				8  /* GIF processing done */
#define	PACKET_TAG_GRE				9  /* GRE processing done */
#define	PACKET_TAG_IN_PACKET_CHECKSUM		10 /* NIC checksumming done */
#define	PACKET_TAG_ENCAP			11 /* Encap.  processing */
#define	PACKET_TAG_IPSEC_SOCKET			12 /* IPSEC socket ref */
#define	PACKET_TAG_IPSEC_HISTORY		13 /* IPSEC history */
#define	PACKET_TAG_IPV6_INPUT			14 /* IPV6 input processing */

/* Packet tags used in the FreeBSD network stack
 * We don't support dummynet or divert, they are included for consistency */
#define	PACKET_TAG_DUMMYNET			15 /* dummynet info */
#define	PACKET_TAG_IPFW				16 /* ipfw classification */
#define	PACKET_TAG_DIVERT			17 /* divert info */
#define	PACKET_TAG_IPFORWARD			18 /* ipforward info */

#define	PACKET_TAG_MAX				19


extern	int		 max_linkhdr;	/* largest link-level header */
extern	int		 max_protohdr;	/* largest protocol header */
extern	int		 max_hdr;	/* largest link+protocol header */

void	m_adj (struct mbuf *, int);
void	m_cat (struct mbuf *,struct mbuf *);

void	m_copyback (struct mbuf *, int, int, caddr_t);
void	m_copydata (struct mbuf *,int,int,caddr_t);
struct	mbuf *m_copypacket (struct mbuf *, int);
struct	mbuf *m_devget (char *, int, int, void *,
    void (*copy)(char *, caddr_t, u_int));
/* Removed m_dup as it wasn't being used */
struct	mbuf *m_free (struct mbuf *);
void	m_freem (struct mbuf *);

struct	mbuf *m_get (int, int);
struct	mbuf *m_getclr (int, int);
struct	mbuf *m_gethdr (int, int);
struct	mbuf *m_getm (struct mbuf *, int, int, int);

struct	mbuf *m_prepend (struct mbuf *,int,int);
struct	mbuf *m_pulldown (struct mbuf *, int, int, int *);

struct	mbuf *m_pullup (struct mbuf *, int);

struct	mbuf *m_split (struct mbuf *,int,int);

struct	mbuf *m_aux_add2 (struct mbuf *, int, int, void *);
struct	mbuf *m_aux_find2 (struct mbuf *, int, int, void *);
struct	mbuf *m_aux_add (struct mbuf *, int, int);
struct	mbuf *m_aux_find (struct mbuf *, int, int);
void	m_aux_delete (struct mbuf *, struct mbuf *);

struct	mbuf *m_copym (struct mbuf *, int, int, int);

/* Make m_freem() and m_free() macros for better performance */
#define m_freem(m) (netMblkClChainFree (m))
#define m_free(m) (netMblkClFree (m))

/* Make m_copydata(), m_copypacket(), and m_copym() macros also */
#define m_copydata(m, off, len, cp) \
    ((void)(netMblkOffsetToBufCopy((m), (off), (cp), (len), 0)))
#define m_copym(m, off0, len, wait) \
    (netMblkChainDup(_pNetDpool, (m), (off0), (len), (wait)))
#define m_copypacket(m, how) \
    (netMblkChainDup(_pNetDpool, (m), 0, M_COPYALL, (how)))
#define	m_copy(m, o, l)	m_copym((m), (o), (l), M_DONTWAIT)

#ifdef __cplusplus
}
#endif

#endif /* __INCNewMbufh */
