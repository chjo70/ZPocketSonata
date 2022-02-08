/* netBufLib.h - network buffers header file */

/*
 * Copyright (c) 1984-2010, 2012, 2014, 2016-2017  Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
08dec17,xxy  Add I350 support for PTP and TSN clock (F9650)
15jun17,xxy  TSN streams integration into the network stack (F9049).
15aug16,xxy  Add support for IEEE 802.1 QAV/QBV.(F6820)
06jun16,xxy  Fix spell error.(V7NET-828)
27may16,dlk  Include base/b_struct_timespec.h header.
08mar16,mca  Enable user-space build.
17feb16,rjq  Fix compiler and static analysis warnings
02feb16,h_l  Add IEEE1588 timestamp support.
20jan14,rjq  Replace FFS macro with ffsMsb(x) - 1
15jul12,ggz  WIND00306857 - Add _ALLOC_ALIGN_SIZE alignment support.
10nov10,dlk  Move extern "C" after last header file include. WIND00240828.
27oct09,dlk  Merge LP64 support.
30jul09,dlk  WIND00168645 - use deterministic spin locks by default.
16jun08,dlk  Remove _pNullPoolFuncTbl; rename nullPoolInit() to
             vxmux_null_buf_init().
21may08,dlk  Remove include of <private/memPartLib.h>.
22mar08,dlk  Split 16-bit offset1 into 8-bits each offset1 and offset2,
             to support CSUM_IPHDR_OFFSET(). Preliminary MUX2 redesign.
16jan08,dlk  Rename spinLockFastLib --> spinlockIsrNdLib.
20dec07,dlk  For SMP performance patch only, pad fast spin lock so that
             size of NET_POOL does not change.
10dec07,dlk  Use fast spin lock for mutual exclusion in SMP case.
31aug07,dlk  Increase stack size for NET_REL_IN_TASK tasks to avoid
             stack overflow (WIND00102321).
21feb07,dlk  Revert prototype change for netBufLibInit(); add
             netBufLibInitialize() routine instead, and deprecate
             netBufLibInit().
09mar07,kch  Merged from base6_iter12_smp-dev - Add spinlocks for SMP
             support.
12feb07,dlk  Make leading pad space configurable.
26dec06,wap  Add support for leading pad space
12sep06,kch  Replaced (struct ifnet *) with (void *) in M_PKT_HDR.
12jun06,dlk  Add nullBufPool support for IPCOM.
10may06,dlk  Correct dbgClFree() prototype.
06mar06,kch  Removed ALTQ_RED that protects altq_hdr from M_PKT_HDR
             (SPR#118453).
06feb06,kch  Rename hdr pointer in mBlkPktHdr to altq_hdr.
04feb06,kch  Added hdr pointer to save header position to mBlkPktHdr
             for ALTQ support.
30jan06,dlk  Replace clTotAlloc with clAllocFail. Use FFS() rather than
             ffsMsb().
14oct05,niq  Debugging changes
25aug05,dlk  Add section tags.
12aug05,dlk  Added M_HEADER flag, overloading M_PROMISC.
25jul05,dlk  Move some routines from netBufLib to netBufAdvLib for better
             scalability.  Some previously LOCAL routines given external
             linkage as a result.
             Add vlan and qnum members to mBlkPktHdr.
22jul05,vvv  removed duplicate macro definitions (SPR #107343)
01arp05,dlk  Replace 'bestFit' with 'noSmaller'.
07feb05,wap  Allow sysctl init routines to be scaled out
18oct04,dlk  Added CL_ALIGN_MIN definition and pNetMemReq function
             (SPRs #102569, #102771).
23aug04,rp   merged from COMP_WN_IPV6_BASE6_ITER5_TO_UNIFIED_PRE_MERGE
19jul04,niq  Move sysctl initialization to the component init routine
16jun04,wap  Add support for netBufRelease
24nov03,wap  Merge in changes from Snowflake
05nov03,cdw  Removal of unnecessary _KERNEL guards.
04nov03,rlm  Ran batch header path update for header re-org.
03nov03,rlm  Removed wrn/coreip/ prefix from #includes for header re-org.
20nov03,rhe  UBM Base 6 Itn 3 Merge from WRAMP branch
17nov03,rhe  Updated errno values.
             Removed redundant MACROs TUP_MPOOL_GET & TUP_CPOOL_GET
             Modified poolFunc table for plug in methods
             netPoolDelete(), netPoolDestroy(), netPoolRelease(),
             netTupleGet(), netTupleFree(), netTupleListGet(),
             netTupleListFree() & netTupleMigrate()
             Modified struct netPool to support attributes and binding.
             Updated prototypes.
23Oct03,rhe  reintroduced linkbuf support. (M_LINK and M_LINKID)
             Added external reference for _pNetPoolFuncTbl &
             _pLinkPoolFuncTbl.
24sep03,kkz  Rebase with Base6 ITER2 FRZ7 (from ver 01q,05sep03,rhe)
15sep03,vvv  updated path for new headers
08sep03,vvv  merged from ACCORDION_BASE6_MERGE_BASELINE
10jun03,vvv  include netVersion.h
01may03,spm  Tornado 2.2 CP1 merge (from ver 01p,13jan03,rae:
             TOR2_2-CP1-F label, tor2_2-patch branch, /wind/river VOB)
08apr03,ann  added the prototypes for the SHOW routines - SPR# 86899
26mar03,vvv  conditionally define *_MIN parameters (SPR #87113)
01feb03,pas  added MT_TAG for FreeBSD 4.7 changes
13jan03,ann  merged Team-F1's ipsec changes
             - changed the NUM_DAT for the larger clusters to zero
             - added support for large clusters (4K to 64K)
25jun02,pas  conditionally re-enable MSIZE for old drivers
12jun02,pas  changed minimum cluster size to 16
             added stats for cluster min/max/avg size request
04jun02,pas  changed NUM_nn to NUM_DAT_nn
14jan00,ham  changed struct poolFunc.pInitRtn's API, poolInit()'s API
             as well for PD support.
27aug03,rae  add large block sizes
29jul03,wap  add linkbuf support
24jun03,rae  add #include netVersion.h
05sep03,rhe  Base6 Iteration2 Merge from WRAMP sandbox
28aug03,rhe  Base 6, Iteration 2. Added Tuple MACROs and netPool attributes.
             Also added prototypes for netPoolAttach(), netPoolCreate(),
             netPoolDetach(), netTupleChainGet(), netTupleListGet(),
             netTupleListFree(), netTuplePhysAddrMap(), netPoolIdGet() and
             netPoolNameGet().
             Also modified netPool to support attributes and knowledge to
             delete its memory should the netPool need to be destroyed.
             Structures NETBUF_CL_DESC and NETBUF_CFG were added for
             netPoolCreate() and structure BUF_VTOP is required for
             netTuplePhysAddrMap().
13jan03,rae  Merged from velocecp branch (SPR 73393)
05jun02,vvv  added M_EOB flag (SPR #72213)
26mar02,vvv  added M_PROXY flag (SPR #74518)
10oct01,rae  merge from truestack ver 01q base 01l
24mar99,ann  protected some #defines by #ifndefs due to conflicts
             in project facility (all the ones defined in 00network.cdf)
16mar99,spm  recovered orphaned code from tor1_0_1.sens1_1 (SPR #25770)
08oct98,gnn	 updated system network buffer allocations
11dec97,vin  added prototype for netMblkOffsetToBufCopy part of SPR 9563.
08dec97,vin  added prototype for netMblkChainDup SPR 9966.
03dec97,vin  added prototype for netTupleGet(), added NUM_SYS_xxx defines
13nov97,vin  added error codes and cleanup.
08oct97,vin  corrected clBlkFree()
30sep96,vin  added M_BLK_SZ.
26sep97,vin  added NUM_XXX_MIN macros for bootroms.
19sep97,vin  added cluster Blk typedef, optimized mBlk structure.
             moved mExt structure out of the mBlk structure.
08aug97,vin  written.
*/

#ifndef __INCnetBufLibh
#define __INCnetBufLibh

#include <vxWorks.h>
#include <vsbConfig.h>

/* include cfgDefs for CFG_DATA_HDR */
#include <cfgDefs.h>

/* includes */
#include <memLib.h>
#include <sys/uio.h>
#include <ffsLib.h>


/*
 * Depending on the configuration, we need only one of
 * these three headers; but we used to include at least
 * the first two unconditionally.  To avoid problems with
 * code that has come to rely on netBufLib.h providing these
 * indirect includes, we keep all three headers. Hmm.
 */
#ifdef _WRS_KERNEL
#include <spinLockLib.h>
#include <spinlockIsrNdLib.h>
#include <intLib.h>
#else /* _WRS_KERNEL */
#include <private/semLibP.h>
#endif /* !_WRS_KERNEL */

#include <base/b_struct_timespec.h>

/*
 * The network stack in user space uses the various netBufLib-related
 * code, which uses NOWAIT_LOG macros. However, logLib is not yet enabled
 * in user space. So we defined these macros as no-OPs in user space.
 */

#ifndef _WRS_KERNEL

#define NOWAIT_LOG0(fmt) do {} while ((0))
#define NOWAIT_LOG1(fmt, a1) do {} while ((0))
#define NOWAIT_LOG2(fmt, a1, a2) do {} while ((0))
#define NOWAIT_LOG3(fmt, a1, a2, a3) do {} while ((0))
#define NOWAIT_LOG4(fmt, a1, a2, a3, a4) do {} while ((0))
#define NOWAIT_LOG5(fmt, a1, a2, a3, a4, a5) do {} while ((0))
#define NOWAIT_LOG6(fmt, a1, a2, a3, a4, a5, a6) do {} while ((0))

#define WAIT_LOG0(fmt) do {} while ((0))
#define WAIT_LOG1(fmt, a1) do {} while ((0))
#define WAIT_LOG2(fmt, a1, a2) do {} while ((0))
#define WAIT_LOG3(fmt, a1, a2, a3) do {} while ((0))
#define WAIT_LOG4(fmt, a1, a2, a3, a4) do {} while ((0))
#define WAIT_LOG5(fmt, a1, a2, a3, a4, a5) do {} while ((0))
#define WAIT_LOG6(fmt, a1, a2, a3, a4, a5, a6) do {} while ((0))

#endif /* ! _WRS_KERNEL */

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Notes for LP64 support:
 *
 * As netBufLib is at present primarily a legacy interface,
 * we value backwards compatibility more heavily than future-proofing.
 * Since the maximum cluster size is 64KB, and since M_BLKs and CL_BLKs
 * are used primarily for network packets of modest size, we continue
 * to represent the sizes of clusters and data segments with 32-bit
 * quantities, even in LP64 builds, rather than (say) changing to
 * the size_t type.  Even the total length of a multi-segment M_BLK
 * tuple chain describing a packet is still represented as an int.
 *
 * However, we change quantities representing the length of blocks
 * containing multiple clusters to size_t, and memory requirements
 * functions now return a ssize_t value.  We change the arguments
 * of the cluster free function to type _Vx_usr_arg_t (i.e.
 * int for ILP32, long for LP64).  Further, we reorder members in
 * some structures for better packing.
 */

/* defines  */

/* status codes */

#define	S_netBufLib_MEMSIZE_INVALID		(M_netBufLib | 1)
#define	S_netBufLib_CLSIZE_INVALID		(M_netBufLib | 2)
#define	S_netBufLib_NO_SYSTEM_MEMORY		(M_netBufLib | 3)
#define	S_netBufLib_MEM_UNALIGNED		(M_netBufLib | 4)
#define	S_netBufLib_MEMSIZE_UNALIGNED		(M_netBufLib | 5)
#define	S_netBufLib_MEMAREA_INVALID		(M_netBufLib | 6)
#define S_netBufLib_MBLK_INVALID		(M_netBufLib | 7)
#define S_netBufLib_NETPOOL_INVALID		(M_netBufLib | 8)
#define S_netBufLib_INVALID_ARGUMENT		(M_netBufLib | 9)
#define S_netBufLib_NO_POOL_MEMORY		(M_netBufLib | 10)
#define S_netBufLib_LIB_NOT_INITIALIZED		(M_netBufLib | 11)
#define S_netBufLib_POOL_FEATURE_NOT_SUPPORTED	(M_netBufLib | 12)
#define S_netBufLib_DUPLICATE_POOL 		(M_netBufLib | 13)
#define S_netBufLib_POOL_RELEASED 		(M_netBufLib | 14)
#define S_netBufLib_POOL_RELEASE_IGNORE		(M_netBufLib | 15)

/* usage MACRO's */
/* Tuple Length related MACROS */

#define TUP_LEN_GET(pMblk)	     ((int) (pMblk)->mBlkHdr.mLen)
#define TUP_LEN_SET(pMblk,length)    ((pMblk)->mBlkHdr.mLen = (length))
#define TUP_LEN_ZERO(pMblk)          ((pMblk)->mBlkHdr.mLen = 0)
#define TUP_CL_LEN_GET(pMblk)        ((int) (pMblk)->pClBlk->clSize)
#define TUP_CL_AVIL_LEN_GET(pMblk)   ((int) (pMblk)->pClBlk->clSize - \
                                      ((int) (pMblk)->mBlkHdr.mLen) - \
                                      (((int) (pMblk)->mBlkHdr.mData) - \
                                       ((int)(pMblk)->pClBlk->clNode.pClBuf)))

/* Next refers to the next Tuple in a Tuple chain */

#define TUP_NEXT_GET(pMblk)		((M_BLK_ID) (pMblk)->mBlkHdr.mNext)
#define TUP_NEXT_SET(pMblk,pNext)	((pMblk)->mBlkHdr.mNext = \
                                         (M_BLK_ID) (pNext))
#define TUP_NEXT_NULL(pMblk)		((pMblk)->mBlkHdr.mNext = \
                                         (M_BLK_ID) NULL)

/* Next Packet refers to the next Tuple (List of Tuples) */

#define TUP_NEXT_PK_GET(pMblk)		((M_BLK_ID) (pMblk)->mBlkHdr.mNextPkt)
#define TUP_NEXT_PK_SET(pMblk,pNext)	((pMblk)->mBlkHdr.mNextPkt = \
                                         (M_BLK_ID) (pNext))
#define TUP_NEXT_PK_NULL(pMblk)		((pMblk)->mBlkHdr.mNextPkt = \
                                         (M_BLK_ID) NULL)


/* mBlk type */

#define TUP_TYPE_GET(pMblk)		((pMblk)->mBlkHdr.mType)
#define TUP_TYPE_SET(pMblk,type)	((pMblk)->mBlkHdr.mType = type)

/* Cluster Buffer Address */

#define TUP_BUF_GET(pMblk)		((pMblk)->mBlkHdr.mData)
#define TUP_BUF_SET(pMblk,addr)		((pMblk)->mBlkHdr.mData = addr)

#define NET_POOL_NAME_SZ	(16) /* Length of pool name */

/* netBufLib Attributes required for buffer migration */

#define NB_ALIGN_OFFSET		0U			/* Bits 0, 1 & 2 */
#define NB_ALIGN_MASK		(0x7U << NB_ALIGN_OFFSET)
#define NB_ALIGN_NONE		(0x0U << NB_ALIGN_OFFSET)
#define NB_ALIGN_INT		(0x1U << NB_ALIGN_OFFSET)
#define NB_ALIGN_CACHE		(0x2U << NB_ALIGN_OFFSET)
#define NB_ALIGN_PAGE		(0x3U << NB_ALIGN_OFFSET)

#define NB_SHARABLE		0x0400U			/* Bit 10 */
#define NB_ISR_SAFE		0x0800U			/* Bit 11 */

#define NB_MODE_OFFSET		12U			/* Bits 12, 13 */
#define NB_MODE_MASK		(0x3U << NB_MODE_OFFSET)
#define NB_MODE_5_5BKWRDS	(0x0U << NB_MODE_OFFSET)

/*
 * Pseudo-attribute bit, not saved with other attributes.
 * If this bit is on in a call to netBufCreate(), the implicit
 * leading cluster pad space is not added for qualifying
 * driver pools.
 */
#define NB_NO_LEADING_SPACE	(1U << 15)

/* Flag bits used in pNetPool->flag */

#define NB_CREATE		0x01	/* netPool created via netPoolCreate */
#define NB_RELEASE		0x02	/* netPool is in a release state */
#define NB_RELEASE_START	0x04	/* started the release state */
#define NB_DESTROY_START	0x08	/* started the delete process */

/* netPoolRlease() MACROs */

#define NET_REL_IN_TASK		0x00	/* Release netPool in task context */
#define NET_REL_IN_CONTEXT	0x01	/* Release netPool in call context */
#define NET_REL_NAME		"tPoolRel"	/* Task name */
#define NET_REL_PRI		netPoolRelPri	/* see: netBufLib.c */
#define NET_REL_OPT		0		/* task options */
#define NET_REL_STACK		5000		/* task stack */



/* Valid attribute combinations */

/* Int Aligned, Sharable, ISR Safe */

#define ATTR_AI_SH_ISR 		(NB_ALIGN_INT   | NB_ISR_SAFE | NB_SHARABLE | \
                                 NB_MODE_5_5BKWRDS)

#define ATTR_AC_SH_ISR 		(NB_ALIGN_CACHE | NB_ISR_SAFE | NB_SHARABLE | \
                                 NB_MODE_5_5BKWRDS)

/* Int Aligned, Private, ISR Safe */

#define ATTR_AI_ISR    		(NB_ALIGN_INT   | NB_ISR_SAFE | \
                                 NB_MODE_5_5BKWRDS)

#define ATTR_AC_ISR    		(NB_ALIGN_CACHE | NB_ISR_SAFE | \
                                 NB_MODE_5_5BKWRDS)

/* Buffer types for pMemReqRtn function */

#define NB_BUFTYPE_CLUSTER	0  /* clusters */
#define NB_BUFTYPE_M_BLK	1  /* M_BLKs */
#define NB_BUFTYPE_CL_BLK	2  /* CL_BLKs */

#define MAX_MBLK_TYPES			256	/* max number of mBlk types */

/* cluster defines */

#define CL_LOG2_16			4
#define CL_LOG2_32			5
#define CL_LOG2_64			6
#define CL_LOG2_128			7
#define CL_LOG2_256			8
#define CL_LOG2_512			9
#define CL_LOG2_1024			10
#define CL_LOG2_2048			11
#define CL_LOG2_4096	 		12
#define CL_LOG2_8192 			13
#define CL_LOG2_16384			14
#define CL_LOG2_32768			15
#define CL_LOG2_65536			16

#define CL_SIZE_16			16
#define CL_SIZE_32			32
#define CL_SIZE_64			64
#define CL_SIZE_128			128
#define CL_SIZE_256			256
#define CL_SIZE_512			512
#define CL_SIZE_1024			1024
#define CL_SIZE_2048			2048
#define CL_SIZE_4096			4096
#define CL_SIZE_8192			8192
#define CL_SIZE_16384			16384
#define CL_SIZE_32768			32768
#define CL_SIZE_65536			65536

#define CL_LOG2_MIN			CL_LOG2_16
#define CL_LOG2_MAX			CL_LOG2_65536
#define CL_SIZE_MAX			(1 << CL_LOG2_MAX)
#define CL_SIZE_MIN			(1 << CL_LOG2_MIN)
#define CL_INDX_MIN			0
#define CL_INDX_MAX			(CL_LOG2_MAX - CL_LOG2_MIN)
#define CL_TBL_SIZE			(CL_INDX_MAX + 1)


#define CL_LOG2_TO_CL_INDEX(x)		((x) - CL_LOG2_MIN)
#define CL_LOG2_TO_CL_SIZE(x)		(1 << (x))
#define SIZE_TO_LOG2(size)		(FFS_MSB(((UINT32)(size))) - 1)
#define CL_SIZE_TO_CL_INDEX(clSize) 	(SIZE_TO_LOG2(clSize) - CL_LOG2_MIN)

/*
 * Minimum cluster alignment
 * Some network data structures stored in clusters
 * contain 8-byte members of types such as unsigned long long,
 * which require 8-byte alignment on some architectures (SPR 102569).
 * However, for backwards comptibilty, we only ensure 4-byte
 * alignment by default.  Clients needing the 8-byte alignment can
 * use netPoolCreate(), or replace the default pool's memory requirements
 * function (see uipc_mbuf.c for an example).
 * This value must be a power of two.
 */

#define CL_ALIGN_MIN	4

/* mBlk types */
#define	MT_FREE		0	/* should be on free list */
#define	MT_DATA		1	/* dynamic (data) allocation */
#define	MT_HEADER	2	/* packet header */
#define	MT_SOCKET	3	/* socket structure */
#define	MT_PCB		4	/* protocol control block */
#define	MT_RTABLE	5	/* routing tables */
#define	MT_HTABLE	6	/* IMP host tables */
#define	MT_ATABLE	7	/* address resolution tables */
#define	MT_SONAME	8	/* socket name */
#define MT_ZOMBIE       9       /* zombie proc status */
#define	MT_SOOPTS	10	/* socket options */
#define	MT_FTABLE	11	/* fragment reassembly header */
#define	MT_RIGHTS	12	/* access rights */
#define	MT_IFADDR	13	/* interface address */
#define MT_CONTROL	14	/* extra-data protocol message */
#define MT_OOBDATA	15	/* expedited data  */
#define	MT_IPMOPTS	16	/* internet multicast options */
#define	MT_IPMADDR	17	/* internet multicast address */
#define	MT_IFMADDR	18	/* link-level multicast address */
#define	MT_MRTABLE	19	/* multicast routing tables */
#define	MT_TAG		20	/* volatile metadata associated to pkts */

#define NUM_MBLK_TYPES	21	/* number of mBlk types defined */

/* mBlk flags */

#define	M_EXT		0x0001	/* has an associated cluster */
#define	M_PKTHDR	0x0002	/* start of record */
#define	M_EOR		0x0004	/* end of record */

/* flags 0x0008 - 0x0080 are used in mbuf.h */

/* mBlk pkthdr flags, also in mFlags */

#define	M_BCAST		0x0100	/* send/received as link-level broadcast */
#define	M_MCAST		0x0200	/* send/received as link-level multicast */

/* flags 0x0400 - 0x1000 are used in mbuf.h */

#define M_FORWARD       0x2000  /* to be fast forwarded */
#define M_PROXY         0x4000  /* broadcast forwarded through proxy */
#define M_PROMISC	0x8000	/* indicates unipromisc for multi receive */
#define M_HEADER	M_PROMISC /* NPT transmit, full header present */

/*
 * M_EOB is set when the mblk contains the last part of a large block of
 * data sent by an application using TCP (a large block of data is one
 * which causes sosend to issue multiple protocol send requests).
 * M_EOB and M_EOR can be used together since M_EOB is only used for TCP
 * and M_EOR is only used for datagram protocols (UDP, raw IP).
 */

#define M_EOB           M_EOR

/* flags to mClGet/mBlkGet */

#define	M_DONTWAIT	1	/* don't wait if buffers not available */
#define	M_WAIT		0	/* wait if buffers not available */

/* length to copy to copy all data from the mBlk chain*/

#define	M_COPYALL	1000000000

/* check to see if an mBlk is associated with a cluster */

#define M_HASCL(pMblk)	((pMblk)->mBlkHdr.mFlags & M_EXT)

#define	M_BLK_SZ	sizeof(struct mBlk) 	/* size of an mBlk */
#define M_BLK_SZ_ALIGNED	64		/* See linkBufPool */
 #ifndef MSIZE
#define	MSIZE		M_BLK_SZ	/* size of an mBlk */
#endif

#define CL_BLK_SZ	sizeof(struct clBlk)	/* size of cluster block */
#define CL_BLK_SZ_ALIGNED	64		/* See linkBufPool */

/* macro to get to the netPool pointer from the mBlk */

#define MBLK_TO_NET_POOL(pMblk) \
    (*(NET_POOL_ID *)((char *)pMblk - sizeof(NET_POOL_ID *)))
#define CLBLK_TO_NET_POOL(pClBlk) 	(pClBlk->pNetPool)

/* macro to get to the cluster pool ptr from the cluster buffer */

#define CL_BUF_TO_CL_POOL(pClBuf) \
    (*(CL_POOL_ID *)((char *)pClBuf - sizeof(CL_POOL_ID *)))

/* macros for accessing the functions of net pool directly */

#define poolInit(poolId,pMclBlkConfig,pClDescTbl,tblNumEnt,fromKheap)	\
    		(*(((NET_POOL_ID)(poolId))->pFuncTbl->pInitRtn)) 	\
                 ((poolId), (pMclBlkConfig), (pClDescTbl), (tblNumEnt), \
		  (fromKheap))

#define mBlkFree(poolId,pMblk)						\
    		(*(((NET_POOL_ID)(poolId))->pFuncTbl->pMblkFreeRtn)) 	\
                 ((poolId), (pMblk))

#define clBlkFree(poolId,pClBlk)					\
    		(*(((NET_POOL_ID)(poolId))->pFuncTbl->pClBlkFreeRtn)) 	\
                 ((pClBlk))

#define mBlkClFree(poolId,pMblk)					\
    		(*(((NET_POOL_ID)(poolId))->pFuncTbl->pMblkClFreeRtn)) 	\
                 ((poolId), (pMblk))

#define mBlkGet(poolId,canWait,type)					\
                 (*(((NET_POOL_ID)(poolId))->pFuncTbl->pMblkGetRtn)) 	\
                 ((poolId), (canWait), (type))

#define clBlkGet(poolId,canWait)					\
                 (*(((NET_POOL_ID)(poolId))->pFuncTbl->pClBlkGetRtn)) 	\
                 ((poolId), (canWait))

#ifdef NETBUF_DEBUG
#define clusterGet(poolId,pClPool)					\
	  _dbgClusterGet (poolId, pClPool, FID, __FILE__, __LINE__)

#define clFree(poolId,pClBuf)					\
	  _dbgClFree (poolId, pClBuf, FID, __FILE__, __LINE__)
#else
#define clusterGet(poolId,pClPool)					\
    		(*(((NET_POOL_ID)(poolId))->pFuncTbl->pClGetRtn)) 	\
                 ((poolId), (pClPool))

#define clFree(poolId,pClBuf)						\
    		(*(((NET_POOL_ID)(poolId))->pFuncTbl->pClFreeRtn)) 	\
                 ((poolId), (pClBuf))
#endif /* NETBUF_DEBUG */


#define mClGet(poolId,pMblk,bufSize,canWait,noSmaller)			\
    		(*(((NET_POOL_ID)(poolId))->pFuncTbl->pMblkClGetRtn)) 	\
                 ((poolId), (pMblk), (bufSize), (canWait), (noSmaller))

#define clPoolIdGet(poolId,bufSize,noSmaller)				\
    		(*(((NET_POOL_ID)(poolId))->pFuncTbl->pClPoolIdGetRtn))	\
                 ((poolId), (bufSize), (noSmaller))

#define netMemReq(poolId, type, num, size)				\
		(((NET_POOL_ID)(poolId))->pFuncTbl->pMemReqRtn		\
		 ((type), (num), (size)))

#define ML_SIZE \
    ROUND_UP(sizeof(M_BLK) + sizeof(CL_BLK) + sizeof(NET_POOL_ID), \
             NETBUF_ALIGN)
#define CL_SIZE(x) (ROUND_UP((x), NETBUF_ALIGN))

#ifndef NB_FULL_BKWARD_MODE
#define NB_FULL_BKWARD_MODE
#endif

#ifdef _WRS_KERNEL
#ifdef _WRS_CONFIG_SMP
#ifdef _WRS_CONFIG_DETERMINISTIC
#define NET_POOL_LOCK(x, k) do { (void)(k); SPIN_LOCK_ISR_TAKE ((x)); } while ((0))
#define NET_POOL_UNLOCK(x, k) do { SPIN_LOCK_ISR_GIVE ((x)); (void)(k); } while ((0))
#define NET_POOL_LOCK_INIT(x) do { SPIN_LOCK_ISR_INIT ((x), 0); } while ((0))
#else
#define NET_POOL_LOCK(x, k) do { k = spinLockIsrNdTake (x); } while ((0))
#define NET_POOL_UNLOCK(x, k) do { spinLockIsrNdGive ((x), (k)); } while ((0))
#define NET_POOL_LOCK_INIT(x) do { spinLockIsrNdInit ((x)); } while ((0))
#endif /* _WRS_CONFIG_DETERMINISTIC */
#else
#define NET_POOL_LOCK(x, k) do {k = INT_CPU_LOCK ();} while ((0))
#define NET_POOL_UNLOCK(x, k) do {INT_CPU_UNLOCK (k);} while ((0))
#define NET_POOL_LOCK_INIT(x) do { } while ((0))
#endif /* _WRS_CONFIG_SMP */
#else /* _WRS_KERNEL */
#define NET_POOL_SEM_OPTS SEM_Q_PRIORITY | SEM_DELETE_SAFE | SEM_INVERSION_SAFE
#define NET_POOL_LOCK(x, k) do {k = (int)semUMTake (x, WAIT_FOREVER);} while ((0))
#define NET_POOL_UNLOCK(x, k) do {(void)semUMGive (x); (void)k;} while ((0))
#define NET_POOL_LOCK_INIT(x) do {(void)semMInit (x, NET_POOL_SEM_OPTS);} while ((0))
#endif /* !_WRS_KERNEL */


/* typedefs */

/*
 * This structure is used to configure the number of mBlks and cluster blocks
 * that are allocated in a netPool. Each cluster has a corresponding cluster
 * block which manages it. An mBlk manages a cluster block and the cluster.
 * When a netPool is configured there should as many cluster blocks as the
 * cumulative number of clusters. The defaults are defined above, but the
 * structure is defined and filled in usrConfig.c. For TCP applications it is
 * good to have two mBlks for every cluster block.
 */

typedef struct
    {
    int		mBlkNum;		/* number of mBlks */
    int		clBlkNum;		/* number of cluster Blocks */
    char * 	memArea;		/* pre allocated memory area */
    size_t	memSize;		/* pre allocated memory size */
    } M_CL_CONFIG;

/*
 *  This structure defines the way the networking code utilizes clusters.
 *  A table of type CL_DESC is filled in usrNetwork.c.
 *  Clusters are also used to hold network data structures other than the
 *  regular data. The network data structures are routing table entries,
 *  interface address structures, multicast address structures etc.
 */

typedef struct clDesc
    {
    int		clSize;			/* cluster size */
    int		clNum;			/* number of clusters */
    char *	memArea;		/* pre allocated memory area */
    size_t	memSize;		/* pre allocated memory size */
    } CL_DESC;

/*
 * this structure is used to pass the config parameters to mbinit and is
 * used to define the configuration of the system and data network memory
 * pools.
 */

typedef struct netPoolParams
    {
    CFG_DATA_HDR  cfgh;                  /* standard cfg header */

    M_CL_CONFIG * sysMblkClBlkConf;      /* mblks and clblks for system pool */
    CL_DESC *     sysClDesc;             /* cluster info for system pool */
    unsigned int  sysClDescNum;          /* no. of clDesc for system pool */

    M_CL_CONFIG * pktMblkClBlkConf;      /* mblks and clblks for data pool */
    CL_DESC *     pktClDesc;             /* cluster info for data pool */
    unsigned int  pktClDescNum;          /* no. of clDesc for data pool */
    FUNCPTR       cfg_privInitSysctl;    /* Do sysctl initialization ? */
    } NET_POOL_CONFIG_PARAMS;

/* this structure defines the cluster */

typedef struct clBuff
    {
    struct clBuff *	pClNext; 	/* pointer to the next clBuff */
    } CL_BUF;

typedef CL_BUF * CL_BUF_ID;

/* This structure defines the each cluster pool */

typedef struct clPool
    {
    int			clSize;		/* cluster size */
    int			clLg2;		/* cluster log 2 size */
    int			clNum; 		/* number of clusters */
    int			clNumFree; 	/* number of clusters free */
    unsigned int	clUsage;	/* number of times used */
    int			clMinAlloc;	/* smallest block size requested */
    int			clMaxAlloc;	/* largest block size requested */
    unsigned long	clAllocFail;	/* # of cluster allocation failures */
    CL_BUF_ID		pClHead;	/* pointer to the cluster head */
    struct netPool *	pNetPool;	/* pointer to the netPool */

    /*
     * Define the following unconditionally so that we don't run into
     * problems if some part of the code is compiled with NETBUF_DEBUG and
     * other part without.
     */

#if 1 /* NETBUF_DEBUG */
    CL_BUF_ID		pClTail;	/* pointer to the last free cluster */
    char *		pBackPointer;	/* back pointer to pool */
    char *		pStartMem;	/* points to start of first cluster */
    char *		pEndMem;	/* points to start of last cluster */
    char *		pLoanedOut;	/* array of cluster loan status */
    unsigned int        clPaddedSize;   /* size of padded cluster */
#endif /* NETBUF_DEBUG */
    } CL_POOL;

#if 1 /* NETBUF_DEBUG */
#define IS_CLPOOL_OK(cp) \
    ((cp) != NULL && (cp)->pBackPointer == (char *)(cp) && \
     (((cp)->pClHead == NULL && (cp)->pClTail == NULL) ||\
      ((cp)->pClHead != NULL && (cp)->pClTail != NULL && \
       (cp)->pClTail->pClNext == NULL)))


/*
 * Check if cluster is in range. It qualifies if it lies between the
 * start and end of the pool and is on the cluster boundary
 */

#define IS_CLUSTER_IN_RANGE(cp, cl) ((char *)(cl) >= (cp)->pStartMem && \
                                  (char *)(cl) <= (cp)->pEndMem && \
                                  ((((char *)(cl) - (cp)->pStartMem) % \
				    (cp)->clPaddedSize == 0)))

/* Given the cluster address, get an index into the loanedOut array */

#define CL_NDX(cp, cl) (((char *)cl - (cp)->pStartMem) / (cp)->clPaddedSize )

#endif

typedef CL_POOL * CL_POOL_ID;

/* header at beginning of each mBlk */

typedef struct mHdr
    {
    struct mBlk *	mNext;		/* next buffer in chain */
    struct mBlk *	mNextPkt;	/* next chain in queue/record */
    char *		mData;		/* location of data */
    int			mLen;		/* amount of data in this mBlk */
    UINT16		mType;		/* type of data in this mBlk */
    UINT16		mFlags;		/* flags; see below */
    UINT16		reserved;
    UINT8		offset1;	/* network service offset */
    UINT8		offset2;	/* TX checksum offload: offset from
					   start of IP header to TL header */
    } M_BLK_HDR;

/* record/packet header in first mBlk of chain; valid if M_PKTHDR set */

typedef struct mBlk     M_BLK;
typedef M_BLK * 	M_BLK_ID;

typedef struct	pktHdr
    {
    void *              rcvif;		/* rcv interface */
    void *              header;         /* pointer to packet header */

    int			len;		/* total packet length */
    UINT32              csum_flags;     /* checksum flags */
    UINT32              csum_data;      /* used by csum routines */
    UINT16		qnum;		/* priority queueing number */
    UINT16		vlan;		/* vlan control information */

    M_BLK_ID            aux;            /* extra data buffer */
    /*
     * This is a private field to save (IPv4/v6) header position in mbuf for
     * fast access by altq later.
     */
    void	*altq_hdr;

#ifndef PKT_TSN_FLAGS
#define PKT_TSN_FLAGS
#define PKT_TSN_TIME_STAMP_DISABLE      0x0
#define PKT_TSN_TIME_STAMP_FETCH_EN     0x1
#define PKT_TSN_TIME_STAMP_OFFSET_EN    0x2
#define PKT_TSN_TIME_LAUNCH_EN          0x4
#endif /* PKT_TSN_FLAGS */
    UINT32  time_flags;

    /* The time Stamp returned with the packet */

    struct timespec timestamp_fetch; /* With sec, nsec */

    /*
     * Queue Priority
     * 
     * Specific the queue number or the priority.
     * 
     * 31 | 30        16 | 15      0 
     *  |                      |- specific the priority
     *  |        |- specific the Queue number 
     *  |- 1: Use queue number, 0: using priority  
     *
     */
    
#ifndef PKT_PRIORITY_FLAGS
#define PKT_PRIORITY_FLAGS
#define PKT_PRIORITY_FLAGS_QNUM_EN (0x1 << 31)/* Enable to use queue number */
#define PKT_PRIORITY_FLAGS_QNUM_OFFSET  (16)         /* queue number offset */
#define PKT_PRIORITY_FLAGS_QNUM_MASK    (0x7FFF0000) /* queue number mask */
#define PKT_PRIORITY_FLAGS_SR        0x1 /* Stream Reservation */
#define PKT_PRIORITY_FLAGS_SP        0x2 /* Strict Priority */
#define PKT_PRIORITY_FLAGS_BE        0x3 /* Best Effort */
#define PKT_PRIORITY_FLAGS_SR2       0x4 /* Stream Reservation 2 */
#endif /* PKT_PRIORITY_FLAGS */ 
        
       UINT32 queue_priority;  

       void * streamCookie;   /* TSN stream cookie */
#if defined (_WRS_CONFIG_IPNET_STREAM) || defined (_WRS_CONFIG_IEEE_802_1_QBV)
       UINT64 launch_time;  /* used to set the launch time */
#endif

    } M_PKT_HDR;

typedef union clBlkList
    {
    struct clBlk * 	pClBlkNext;	/* pointer to the next clBlk */
    char * 		pClBuf;		/* pointer to the buffer */
    } CL_BLK_LIST;

/* description of external storage mapped into mBlk, valid if M_EXT set */

typedef struct clBlk
    {
    CL_BLK_LIST 	clNode;		/* union of next clBlk, buffer ptr */
    UINT		clSize;		/* cluster size */
    int			clRefCnt;	/* reference count of the cluster */
    FUNCPTR		pClFreeRtn;	/* pointer to cluster free routine */
    _Vx_usr_arg_t	clFreeArg1;	/* free routine arg 1 */
    _Vx_usr_arg_t	clFreeArg2;	/* free routine arg 2 */
    _Vx_usr_arg_t	clFreeArg3;	/* free routine arg 3 */
    struct netPool *	pNetPool;	/* pointer to the netPool */
    } CL_BLK;

/* mBlk structure */

struct mBlk
    {
    M_BLK_HDR 	mBlkHdr; 		/* header */
    M_PKT_HDR	mBlkPktHdr;		/* pkthdr */
    CL_BLK *	pClBlk;			/* pointer to cluster blk */
    };

/* mBlk statistics used to show data pool by show routines */

typedef struct mbstat
    {
    ULONG	mNum;			/* mBlks obtained from page pool */
    ULONG	mDrops;			/* times failed to find space */
    ULONG	mWait;			/* times waited for space */
    ULONG	mDrain;			/* times drained protocols for space */
    ULONG	mTypes[256];		/* type specific mBlk allocations */
    } M_STAT;

typedef struct _M_LINK
    {
    M_BLK	mBlk;
    CL_BLK	clBlk;
    } M_LINK;

#define CL_BLK_TO_M_LINK(pClBlk) \
        (M_LINK *) ((char *)(pClBlk) - OFFSET (M_LINK, clBlk))

#define NETBUF_ALIGN 64
#define NETBUF_LEADING_SPACE 64

typedef CL_BLK *		CL_BLK_ID;	/* Cluster Block ID */
typedef struct netPool 		NET_POOL;	/* Pool ID */
typedef struct poolFunc 	POOL_FUNC;	/* Pool Function Table */
typedef NET_POOL * 		NET_POOL_ID;	/* Pool ID (pointer) */
typedef M_LINK *		M_LINK_ID;	/* mBlk Cluster Block set */
typedef struct poolAttr * 	ATTR_ID;	/* Pool Attribute ID */
typedef struct iovec 	 	IOV;		/* IOV structure (See uio.h) */
typedef struct poolRel	 	POOL_REL;	/* netPoolRelease Support */


typedef struct bufVirToPhy
    {
    M_BLK_ID	pMBlk;		/* Associated mBlk */
    char *	pVAddr;		/* Virtual Address */
    char *	pPAddr;		/* Physical Address */
    int		length;		/* length of segment */
    } BUF_VTOP;


struct	poolFunc			/* POOL_FUNC */
    {
    /* pointer to the pool initialization routine */
    STATUS	(*pInitRtn) (NET_POOL_ID pNetPool, M_CL_CONFIG * pMclBlkConfig,
                             CL_DESC * pClDescTbl, int clDescTblNumEnt,
			     BOOL fromKheap);

    /* pointer to mBlk free routine */
    void	(*pMblkFreeRtn) (NET_POOL_ID pNetPool, M_BLK_ID pMblk);

    /* pointer to cluster Blk free routine */
    void	(*pClBlkFreeRtn) (CL_BLK_ID pClBlk);

    /* pointer to cluster free routine */
    void	(*pClFreeRtn) (NET_POOL_ID pNetPool, char * pClBuf);

    /* pointer to mBlk/cluster pair free routine */
    M_BLK_ID 	(*pMblkClFreeRtn) (NET_POOL_ID pNetPool, M_BLK_ID pMblk);

    /* pointer to mBlk get routine */
    M_BLK_ID	(*pMblkGetRtn) (NET_POOL_ID pNetPool, int canWait, UCHAR type);

    /* pointer to cluster Blk get routine */
    CL_BLK_ID	(*pClBlkGetRtn) (NET_POOL_ID pNetPool, int canWait);

    /* pointer to a cluster buffer get routine */
    char *	(*pClGetRtn) (NET_POOL_ID pNetPool, CL_POOL_ID pClPool);

    /* pointer to mBlk/cluster pair get routine */
    STATUS	(*pMblkClGetRtn) (NET_POOL_ID pNetPool, M_BLK_ID pMblk,
                                  int bufSize, int canWait, BOOL noSmaller);

    /* pointer to cluster pool Id get routine */
    CL_POOL_ID	(*pClPoolIdGetRtn) (NET_POOL_ID pNetPool, int	bufSize,
                                    BOOL noSmaller);

    /* netBuf 6.0 Pluggable API */

    /* pointer to pool delete routine */
    STATUS (*pNetPoolDeleteRtn)       (NET_POOL_ID pNetPool);

    /* pointer to pool destroy routine */
    STATUS (*pNetPoolDestroyRtn)      (NET_POOL_ID pNetPool);


    /* pointer to pool release routine */
    STATUS (*pNetPoolReleaseRtn)      (NET_POOL_ID pNetPool);


    /* pointer to Tuple get routine */
    M_BLK_ID (*pNetTupleGetRtn)       (NET_POOL_ID pNetPool,
                                       int	bufSize,
                                       int	canWait,
                                       UCHAR type,
                                       BOOL noSmaller);

    /* pointer to Tuple get routine */
    M_BLK_ID (*pNetTupleFreeRtn)      (M_BLK_ID pMblk);

    /* pointer to Tuple List Get routine */
    int (*pNetTupleListGetRtn)        (NET_POOL_ID pNetPool,
                                       CL_POOL_ID pClPool,
                                       int count,
                                       int type,
                                       M_BLK_ID * pMblk);

    /* pointer to Tuple List Free routine */
    STATUS (*pNetTupleListFreeRtn)    (M_BLK_ID pMblk);


    /* pointer to Tuple Migrate routine */
    M_BLK_ID (*pNetTupleMigrateRtn)   (NET_POOL_ID pDstNetPool,
                                       M_BLK_ID pMblk);

    /* pointer to memory requirement function */
    ssize_t (*pMemReqRtn) (int type, int num, int size);
    };

struct	poolRel				/* POOL_REL */
    {
    SEM_ID	releaseSemId;               /* Release Semaphore ID */
    TASK_ID	releaseTaskId;              /* Release task ID */

    /* pointer to Tuple netPoolReleaseStart routine */
    STATUS (*pNetPoolReleaseStartRtn) (NET_POOL_ID pNetPool,
                                       POOL_FUNC * pReleaseFunc);

    /* pointer to Tuple netPoolReleaseEnd routine */
    STATUS (*pNetPoolReleaseEndRtn)   (NET_POOL_ID pNetPool);

    };

/* Attribute Set */

typedef struct poolAttr
    {
    UINT32	attribute;	/* Attribute Bits */
    int		refCount;	/* Registered objects sharing this set */
    PART_ID     ctrlPartId;	/* Memory partition for control structures */
    PART_ID 	bMemPartId;	/* Memory partition for clusters */
    void *	pDomain;	/* NULL = Kernel */
    int 	ctrlAlign;	/* Alignment Control Structures */
    int		clusterAlign;	/* Alignment Clusters (Buffers) */
    struct poolAttr * pNext;	/* Next in Link List */
    } POOL_ATTR;


struct netPool				/* NET_POOL */
    {
    M_BLK_ID	pmBlkHead;		    /* head of mBlks */
    CL_BLK_ID	pClBlkHead;	    	    /* head of cluster Blocks */
    int		mBlkCnt;        	    /* number of mblks */
    int		mBlkFree;	            /* number of free mblks -
                                               deprecated, use
                                               pPoolStat->mTypes[MT_FREE]
                                               instead */
    unsigned	clOffset;		    /* leading pad space in cluster */
    int		clBlkOutstanding;	    /* Number of clBlks in use */
    int		clMask;			    /* cluster availability mask */
    int		clLg2Max;		    /* cluster log2 maximum size */
    int		clSizeMax;		    /* maximum cluster size */
    int		clLg2Min;		    /* cluster log2 minimum size */
    int		clSizeMin;		    /* minimum cluster size */
    CL_POOL * 	clTbl [CL_TBL_SIZE];	    /* pool table */
    M_STAT *	pPoolStat;		    /* pool statistics */
    POOL_FUNC *	pFuncTbl;		    /* ptr to function ptr table */
    int 	flag;			    /* Pool Flag */
    ATTR_ID  	pAttrSet;		    /* Attribute Reference */
    PART_ID     poolPartId;		    /* Pool Struct Memory Partition */
    int		attachRefCount;		    /* Attach Ref Count */
    int		bindRefCount;		    /* Attach Ref Count */
    char *	pControlMemArea;	    /* Memory Area for mClBlk */
    PART_ID	controlMemPartId;	    /* memory partition for mClBlk */
    char *	pClusterMemArea;	    /* Memory Area for clusters */
    PART_ID	clusterMemPartId;	    /* memory partition for clusters */
    char        poolName[NET_POOL_NAME_SZ]; /* Pool name */
    POOL_REL    poolRelease;                /* netPoolRelease Support */
    struct netPool * pParent;		    /* Parent netPool */
    struct netPool * pNext;		    /* next in link list */
#ifdef _WRS_KERNEL
#ifdef _WRS_CONFIG_SMP
#ifdef _WRS_CONFIG_DETERMINISTIC
    spinlockIsr_t poolLock;
#else
    spinlockIsrNd_t poolLock;
#endif
#endif
#else  /* _WRS_KERNEL */
    SEMAPHORE   poolLock;
#endif /* !_WRS_KERNEL */
    };

/* Cluster description structure for a buffer pool see netPoolCreate () */

typedef struct netBufClDesc
    {
    int clSize;				/* Cluster Size */
    int clNum;				/* Number of clusters in pool */
    } NETBUF_CL_DESC;

/* Pool configuration structure see netPoolCreate () */

typedef struct netBufCfg
    {
    char *          pName;	     /* Pool Name */
    UINT32          attributes;	     /* pool attributes */
    void *          pDomain;         /* RTP ID or NULL for kernel */
    int             ctrlNumber;	     /* # of ctrl structures to pre-allocate */
    PART_ID         ctrlPartId;	     /* Mem Partition for Control structures */
                                     /*     NULL = use Kernel partition */
    int             bMemExtraSize;   /* Additional memory for runtime buffers */
    PART_ID         bMemPartId;	     /* Mem Partition for buffers */
                                     /*     NULL = default for kernel or RTP */
    NETBUF_CL_DESC * pClDescTbl;     /* desired cluster sizes and count */
    int             clDescTblNumEnt; /* num of entries in cluster table */
    } NETBUF_CFG;

/*
* NET_POOL_CFG:
* Optimized allocation and freeing for netPool and function table
*/

typedef struct netPoolCfg
    {
    NET_POOL	netPool;	/* netPool - Must be 1st Entry */
    POOL_FUNC 	funcTbl;	/* Function ptr table */
    } NET_POOL_CFG, *pNET_POOL_CFG;

/* CLTAG:
*    Cluster Prefix and appended tags
*    NB_BUF_SANITY - Optional buffer corruption check
*    NB_BUF_USRTAG - Used by drivers to associate a cluster
*                    address with an Tuple.
*
*/

typedef struct clPreTag
    {
#ifdef NB_BUF_SANITY
    uint32_t 	tag;		/* Used to validate cluster */
#endif		/* NB_BUF_SANITY */
#ifdef NB_BUF_USRTAG
    uint32_t 	usrTag;		/* User tag */
#endif		/* NB_BUF_USRTAG */
#ifdef NB_FULL_BKWARD_MODE
    NET_POOL_ID	poolId;		/* Pool ID. Req for 5.5 compatibility */
#endif		/* NB_BUF_USRTAG */
    } CL_PRE_TAG;

typedef struct clPostTag
    {
    uint32_t 	tag;		/* Used to validate cluster */
    } CL_POST_TAG;

#ifdef NETBUF_DEBUG

#define GCC_VERSION \
	(__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)

/* XXX verify exact version numbers for _HAVE__FUNCTION__ and _HAVE__func__ */

#if defined (__GNUC__) || (defined (__DCC__) && __VERSION_NUMBER__ >= 5200)
#define _HAVE__FUNCTION__
#endif

#if (GCC_VERSION >= 30200)
#define _HAVE__func__
#endif

#ifdef _HAVE__func__
#define FID __func__
#elif defined (_HAVE__FUNCTION__)
#define FID __FUNCTION__
#else
#define FID ""
#endif

#define netClusterGet(pNetPool, pClPool) \
	_netClusterGet (pNetPool, pClPool, FID, __FILE__, __LINE__)
#define netClFree(pNetPool, pClBuf) \
	_netClFree (pNetPool, pClBuf, FID, __FILE__, __LINE__)
#endif /* NETBUF_DEBUG */

/* external declarations */

_WRS_INITTEXT
IMPORT STATUS 		netBufLibInitialize (int drvClOffset);
IMPORT STATUS 		netBufLibInit (void)
			  _WRS_DEPRECATED("Use netBufLibInitialize() instead");
_WRS_INITTEXT
IMPORT STATUS 		netBufPoolInit (void);
_WRS_INITTEXT
IMPORT STATUS 		linkBufPoolInit (void);
IMPORT STATUS 		vxmux_null_buf_init (void);
IMPORT STATUS 		netPoolInit (NET_POOL_ID pNetPool,
                                     M_CL_CONFIG * pMclBlkConfig,
                                     CL_DESC * pClDescTbl, int clDescTblNumEnt,
                                     POOL_FUNC * pFuncTbl);
IMPORT STATUS		netPoolDelete (NET_POOL_ID);
IMPORT void		netMblkFree (NET_POOL_ID pNetPool, M_BLK_ID pMblk);
IMPORT void		netClBlkFree (NET_POOL_ID pNetPool, CL_BLK_ID pClBlk);
#ifdef NETBUF_DEBUG
IMPORT void 		_netClFree (NET_POOL_ID pNetPool, UCHAR * pClBuf,
				    char *, char *, int);
IMPORT char *	 	_netClusterGet (NET_POOL_ID pNetPool, CL_POOL_ID pClPool,
					char *, char *, int);
#else
IMPORT void 		netClFree (NET_POOL_ID pNetPool, UCHAR * pClBuf);
IMPORT char *	 	netClusterGet (NET_POOL_ID pNetPool,
                                       CL_POOL_ID pClPool);

#endif /* NETBUF_DEBUG */
_WRS_FASTTEXT
IMPORT M_BLK_ID 	netMblkClFree (M_BLK_ID pMblk);
_WRS_FASTTEXT
IMPORT void		netMblkClChainFree (M_BLK_ID pMblk);
IMPORT M_BLK_ID 	netMblkGet (NET_POOL_ID pNetPool, int canWait,
                                    UCHAR type);
IMPORT CL_BLK_ID	netClBlkGet (NET_POOL_ID pNetPool, int canWait);
IMPORT STATUS 	 	netMblkClGet (NET_POOL_ID pNetPool, M_BLK_ID pMblk,
                                      int bufSize, int canWait,
				      BOOL noSmaller);
_WRS_FASTTEXT
IMPORT M_BLK_ID		netTupleGet (NET_POOL_ID pNetPool, int bufSize,
                                     int canWait, UCHAR type, BOOL noSmaller);

IMPORT M_BLK_ID 	netTupleGet2 (NET_POOL_ID, int, int);

IMPORT CL_BLK_ID  	netClBlkJoin (CL_BLK_ID pClBlk, char * pClBuf,
                                      int size, FUNCPTR pFreeRtn, _Vx_usr_arg_t arg1,
                                      _Vx_usr_arg_t arg2, _Vx_usr_arg_t arg3);
IMPORT M_BLK_ID  	netMblkClJoin (M_BLK_ID pMblk, CL_BLK_ID pClBlk);
IMPORT CL_POOL_ID 	netClPoolIdGet (NET_POOL_ID pNetPool, int bufSize,
                                        BOOL noSmaller);

IMPORT int 		netMblkToBufCopy (M_BLK_ID pMblk, char * pBuf,
                                          FUNCPTR pCopyRtn);
IMPORT int		netMblkOffsetToBufCopy (M_BLK_ID pMblk, int offset,
                                                char * pBuf, int len,
                                                FUNCPTR	pCopyRtn);
IMPORT M_BLK_ID 	netMblkDup (M_BLK_ID pSrcMblk, M_BLK_ID	pDestMblk);
IMPORT M_BLK_ID 	netMblkChainDup (NET_POOL_ID pNetPool, M_BLK_ID	pMblk,
                                         int offset, int len, int canWait);
IMPORT UINT32           netMblkFromBufCopy(M_BLK_ID pMblk, char* pBuf,
					   UINT32 offset, UINT32 len,
					   INT32 canWait, FUNCPTR pCopyRtn);
IMPORT void             netPoolShow (NET_POOL_ID pNetPool);
IMPORT void 	        mbufShow (void);
IMPORT void             netStackSysPoolShow (void);
IMPORT void             netStackDataPoolShow (void);

/* NetBuf enhanced functions */
IMPORT NET_POOL_ID netPoolCreate          (NETBUF_CFG * pnetBufCfg,
                                           POOL_FUNC * pFuncTbl);
IMPORT STATUS	   netBufAdvLibInit	  (void);
IMPORT NET_POOL_ID netPoolAttach	  (const char * pName);
IMPORT STATUS      netPoolDetach	  (NET_POOL_ID pNetPool);
IMPORT STATUS      netPoolBind            (NET_POOL_ID pNetPoolChild,
                                           const char *pParentName);
IMPORT STATUS      netPoolUnbind          (NET_POOL_ID pNetPool);
IMPORT STATUS      netPoolRelease	  (NET_POOL_ID pNetPool,
                                           int destroyContext);
IMPORT M_BLK_ID    netTupleFree           (M_BLK_ID pMblk);
IMPORT int         netTupleListGet	  (NET_POOL_ID pNetPool,
                                           CL_POOL_ID pClPool,
                                           int count,
                                           int type,
                                           M_BLK_ID * pMblk);
IMPORT STATUS      netTupleListFree	  (M_BLK_ID);
IMPORT M_BLK_ID    netTupleMigrate        (NET_POOL_ID pDstNetPool,
                                           M_BLK_ID pMblk);
IMPORT STATUS      netTuplePhysAddrMap	  (M_BLK_ID pMblk,
                                           BUF_VTOP * pVtopTbl,
                                           int * pElementCount);
IMPORT NET_POOL_ID netPoolIdGet		  (const char * pPoolName);
IMPORT char *      netPoolNameGet	  (NET_POOL_ID pNetPool);
IMPORT ssize_t	   _netMemReqDefault	  (int type, int num, int size);
#ifdef NETBUF_DEBUG
IMPORT char *	_dbgClusterGet (NET_POOL_ID pNetPool, CL_POOL_ID pClPool,
					char *, char *, int);
IMPORT void 	_dbgClFree (NET_POOL_ID pNetPool, char * pClBuf,
				    char *, char *, int);
#endif /* NETBUF_DEBUG */


extern POOL_FUNC * _pNetPoolFuncTbl;
extern POOL_FUNC * _pLinkPoolFuncTbl;
extern POOL_FUNC * _pNetPoolFuncAlignTbl;
extern void (*_func_netPoolShow) (NET_POOL_ID pNetPool);

/*
 * The following routines and variables are considered private and should
 * not be used outside of the netBufLib/netBufAdvLib implementation.
 */
extern STATUS      netPoolCreateValidate (NET_POOL_ID pNetPool);
extern POOL_ATTR * (*_func_netAttrReg) (UINT32 attribute, PART_ID ctrlPartId,
					PART_ID bMemPartId, void * pDomain);
extern STATUS      (*_func_netAttrDeReg) (POOL_ATTR * pBufAttr);
extern SEM_ID      netBufLock;
extern NET_POOL_ID netPoolIdGetWork (const char * pPoolName);

/* End private routines/variables */

#ifdef __cplusplus
}
#endif

#endif /* __INCnetBufLibh */
