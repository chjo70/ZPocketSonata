/* end.h - Structure for the MUX and END API*/

/*
 * Copyright (c) 1996-2007, 2010, 2013, 2016 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
07aug16,dlk  Adding END_PKTDROP_INJECT facility, disabled by default.
04apr16,dlk  Making END_OBJ flags member specifically an INT32 (V7PRO-2981)
12jun13,dlk  Adding END_INFO structure.
02feb10,h_k  changed flags type to int from long.
23jul08,dlk  To avoid problems with redundant Ipcom_pkt typedefs, use
                 'struct Ipcom_pkt_struct *' rather than 'Ipcom_pkt *' args.
11may08,dlk  END2 polled mode support.
08apr08,dlk  END2 drivers use END2_NET_FUNCS extension of NET_FUNCS, and
                 move header parsing to hdrParse callback.
28mar08,dlk  Added unloadInfo member to END_OBJ for asynchronous shutdown
                 support.
03s,22Mar08,dlk  MUX2 redesign. 1st checkin.
20jul07,kch  Added END_ERR_L2VID_NOTIFY and END_ERR_L2PVID_NOTIFY layer 2
                 notifications and the required l2vid_notify_params structure.
31aug05,kch  Renamed END_ERR_IFMTU_CHANGE to END_ERR_L2NOTIFY. Added
                 l2notify_params structure definition (SPR #112068).
29aug05,dlk  Move END_RCVJOBQ_INFO definition here from endCommon.h, as
                 it is not usable from user space. Add jobQueueLib.h include.
23aug05,kch  Added END_ERR_IFMTU_CHANGE define.
14aug05,niq  Add parameters for ingress QOS support
03aug05,kch  Added endObjId to END_OBJ. Also modified formAddress and
                 packetDataGet function pointers in NET_FUNCS to have
                 unspecified argument list.
24jun05,wap  Add ifmedia support
21feb05,dlk  Move selected parts of this file to endCommon.h, to support
		 tunnelled END ioctls.
25nov03,wap  Merge in changes from Snowflake
29sep03,rp   merged from base6_networking_itn2-int
13jan03,rae  Merged from velocecp branch
23oct01,rae  merge from truestack (fix some ioctl values)
16oct01,rcs  added END_ERR_NO_BUF flag to notify mux of driver cluster
                 exhaustion. SPR# 70545
13jul01,ann  added a flag for RFC2233 driver support to eliminate the
                 global mibStyle variable
09nov00,spm  removed pNptCookie from END_OBJ for binary compatibility
07nov00,spm  removed nptFlag from END_OBJ for T2 END binary compatibility
25oct00,niq  Merge RFC2233 changes from open_stack-p1-r1 branch
                 10mar00,ead  Modifed the END object to support RFC
                 variables
16oct00,spm  merged version 01v from tor3_0_x branch (base version 01r):
                 adds backward compatibility fixes and support for multiple
                 snarf protocols and link-level broadcasts
29apr99,pul  Upgraded NPT phase3 code to tor2.0.0
29mar99,pul  altered END_QUERY struct to conform to WRS coding standard
24mar99,sj   NET_PROTOCOL flags field is used by MUX
05mar99,sj   added END_QUERY; added END_ERR_FLAGS
02mar99,sj   fixed IOCTL values so that last byte of IOCTL cmd is <255
22feb99,sj   added EIOCGBCASTADDR, EIOCGADDRLEN, EIOCGBIND ioctls
15oct98,pul  changed the call back routines not to specify argument list
08oct98,sj   EIOCGNPT ioctl command for NPT
29sep98,fle  doc : made it refgen parsable
10sep98,pul  added endBind  and EIOCGNPT command
25aug98,n_s  update comments for DEV_OBJ. spr 21546.
17jan98,gnn  fixed a bug in output filtering.
08dec97,gnn  END code review fixes.
17oct97,vin  added llHdrInfo, changed prototypes.
03oct97,gnn  fixed SPR 8986, added proper function prototypes
25sep97,gnn  SENS beta feedback fixes
19aug97,gnn  changes due to new buffering scheme.
12aug97,gnn  changes necessitated by MUX/END update.
02jun97,gnn  added EIOCGMWIDTH to get memory width from driver.
15may97,gnn  added outputFilter element to device structure.
07apr97,gnn  added END_TBL_ENTRY for new boot loading code.
26feb97,gnn  Added END_BUF_MUX and END_BUF_DRIVER defines.
21jan97,gnn  removed all buffer loaning stuff.
                 added buffer pool variables and calls.
                 added a IOCTL to get the minimumb first buffer in a
                 scatter/gather system.
27nov96,gnn  added MIB 2 Ioctl.
07nov96,gnn  fixed the flags fields to be int.
23oct96,gnn  name changes to follow coding standards.
22oct96,gnn  added pragmas for the i960.
                 removed netVector structure and added a pNext pointer
                 to the NET_BUFFER.
                 added function pointers for the start and stop routines.
                 changed the ioctls to be noun->verb
18apr96,gnn	 written.

*/

/*
DESCRIPTION

This file defines all the structures uses by the MUX and any END.  These
structures are either passed by functions in either the MUX or END
or stored by the MUX.
*/

#ifndef __INCendh
#define __INCendh

#include <endCommon.h>
#include <semLib.h>
#include <memLib.h>
#include <netBufLib.h>
#include <net/if_llc.h>
#include <jobQueueLib.h> /* For JOB_QUEUE_ID */

#ifdef __cplusplus
extern "C" {
#endif

/*
 * There are 3 bind styles (mux2Bind(), muxBind(), muxTkBind()).
 * These are also identified with 3 different APIs for
 * send/poll send/poll receive, e.g. mux2Send(), muxSend(), muxTkSend().
 * Each of these may be used for any END style device, but 'cross-combinations'
 * require wrapper code (& some wrappers might not be provided).
 */
#define NUM_BIND_STYLES	3

/*
 * ERROR Return for device blocked on transmit.
 */

#define END_ERR_BLOCK -2

/*
 * ERROR protocol defines.  These are stored in a 32 bit word in the
 * end_err structure.  User apps can have the upper 16 bits, we get the
 * lower 16.
 *
 * Note that the LINKDOWN and LINKUP error codes are semantically
 * different from UP and DOWN. The former indicate a link change event
 * due to cable disconnection, remote end fault or signal loss, while
 * the latter indicate administrative changes in the interface state,
 * such as the stop/start routines in the driver being manually invoked
 * by the user. It is possible for the interface to be administratively
 * up (chip is turned on and running) but still issue a link down event
 * (e.g. if the cable is suddenly unplugged).
 */
#define END_ERR_INFO     1   /* Information only */
#define END_ERR_WARN     2   /* Warning */
#define END_ERR_RESET    3   /* Device has reset. */
#define END_ERR_DOWN     4   /* Device has gone down. */
#define END_ERR_UP       5   /* Device has come back on line. */
#define END_ERR_FLAGS	 6   /* Device flags changed */
#define END_ERR_NO_BUF   7   /* Device's cluster pool exhausted. */
#define END_ERR_LINKDOWN 8   /* Device's link is down */
#define END_ERR_LINKUP   9   /* Device's link is up */

/*
 * Layer 2 notifications
 */
#define END_ERR_L2NOTIFY       10  /* Layer 2 port notification */
#define END_ERR_L2VID_NOTIFY   11  /* Layer 2 vlan notification */
#define END_ERR_L2PVID_NOTIFY  12  /* Layer 2 port-based vlan notification */

typedef struct end_err
    {
    INT32 errCode;           /* Error code, see above. */
    char* pMesg;             /* NULL terminated error message */
    void* pSpare;            /* Pointer to user defined data. */
    } END_ERR;

/*
 * The L2NOTIFY_PARAMS is used for the END_ERR_L2NOTIFY. When the message
 * END_ERR_L2NOTIFY is sent, it is the pSpare pointer in the END_ERR
 * which points to an L2NOTIFY_PARAMS.
 *
 * <l2Attached> sets to true if a port is attached to the layer 2, false
 * if the port is detached from layer 2. If <l2Attached> is true for END
 * device, the interface's if_output routine is expected to use the
 * pEnd->pFuncTable->formAddress to construct its ethernet header. For
 * NPT-style device, the <l2Attached> should be ignore for now (actual
 * bahavior is currently not defined).
 *
 * <newMtu> indicates the mtu size upper layer protocols (e.g. IP) should
 * apply to the interface. The newMtu size will be set to the existing
 * hardware mtu size if the following applies:
 * 1) hardware indicates it supports hardware VLAN tagging (e.g. the
 *    IFCAP_VLAN_HWTAGGING in if_capabilities is set), or
 * 2) hardware doesn't support hardware VLAN tagging but capable of handling
 *    larger mtu that may include a software-appended VLAN header (e.g. the
 *    IFCAP_VLAN_MTU flag is set in if_capabilities)
 * If none of the above is true, the existing hardware mtu size will be
 * reduced by 4 bytes and reflects in <newMtu>.
 */
typedef struct l2notify_params {
    BOOL l2Attached;  /* true if port is attached to layer 2, false if detach */
    unsigned long newMtu;
} L2NOTIFY_PARAMS;

/*
 * Structure used by END_ERR_L2VID_NOTIFY and END_ERR_L2PVID_NOTIFY to support
 * network stack that builds its own link header (including the vlan tag).
 * These layer 2 notifications are sent whenever the tagging decision for a
 * given vlan is changed. A structure of L2VID_NOTIFY_PARAMS type is what
 * is pointed to by the <pSpare> member of the END_ERR.
 *
 * 802.1Q specifies that a port may transmit untagged frames for some VLANs and
 * VLAN-tagged frames for other VLANs for a given port, but can't transmit
 * using both formats for the same VLAN.
 *
 * <sendVlanTag> sets to true if the linker header for the outgoing frame
 * transmitting from the port is expected to include a vlan tag. When
 * receiving the notification, upper layer (e.g. network stack) should adjust
 * the link header for the outgoing frame to include a properly constructed
 * vlan tag.
 *
 * <vid> indicates the vlan id associated with the port
 * <pri> indicates the 3-bit priority associated with the vlan
 */
typedef struct l2vid_notify_params {
    BOOL sendVlanTag;     /* true if vlan-tagged frame is expected */
    UINT16  vid;   /* vlan id */
    UINT8   pri;   /* 3-bit vlan priority */
} L2VID_NOTIFY_PARAMS;

/* A specific instance of an Ethernet multicast address. */
typedef struct
    {
    NODE node;		     /* How we stay in a list. */
    char  addr[6];	     /* address */
    long   refcount;	     /* no. claims to this addr*/
    } ETHER_MULTI;

typedef struct
    {
    long len;		/* Length of table in bytes. */
    char *pTable;		/* Pointer to entries. */
    } MULTI_TABLE;

/* structure used as a vehicle to move data during a EIOCQUERY ioctl */

typedef struct
    {
    int query;		/* the query */
    int queryLen;	/* length of data expected/returned */
    char queryData[4]; /* allocate a minimum of 4 bytes; expandable upto 120 */
    } END_QUERY;

/* Query system Query commands */

#define END_BIND_QUERY 0x1

/*
 *
 * DEV_OBJ - device specific control object
 *
 * The DEV_OBJ contains the means for looking up the END by name and unit
 * number in the MUX.
 *
 * Since the END_OBJ is allocated by drivers, typically it is embedded
 * in a larger driver structure, and so the pDevice pointer is not very
 * useful. Historically, pEnd->devObject.pDevice is what muxDevUnload()
 * has freed if the device unload routine returns OK. One way that drivers
 * could prevent the END_OBJ from being freed is to clear this pointer
 * in their unload routine. (Another is for the unload routine to return
 * EALREADY.)
 *
 * We put the dummyBinding member at the start of the DEV_OBJ, and
 * the DEV_OBJ at the start of the END_OBJ, so that* muxSend(),
 * muxIoctl() et. al. can be passed an END_OBJ as a pseudo-protocol binding.
 *
 */

typedef struct dev_obj
    {
    struct end_object * dummyBinding;	/* dummy protocol binding */
    unsigned int refs;			/* reference count */
    unsigned int muxFlags;		/* Load or unload in progress? */
    void * pDevice;			/* Pointer back to the device data. */
    NODE  node;				/* linking into lists */
    int   unit;
    char  name[END_NAME_MAX];
    char  description[END_DESC_MAX];
    } DEV_OBJ;

/*
 *
 * LL_HDR_INFO - link level Header info
 *
 * This data structure defines information that is only relevant to
 * a stack receive routine for a service bound with muxBind().
 *
 */

typedef struct llHdrInfo
    {
    int		destAddrOffset;		/* destination addr offset in mBlk */
    int		destSize; 		/* destination address size */
    int		srcAddrOffset;		/* source address offset in mBlk */
    int		srcSize;		/* source address size */
    int		ctrlAddrOffset;		/* control info offset in mBlk */
    int		ctrlSize;		/* control info size */
    int		pktType;		/* type of the packet */
    int		dataOffset;		/* data offset in the mBlk */
    } LL_HDR_INFO;

struct proto_entry;
struct protocol_binding;

struct Ipcom_pkt_struct; /* see ipcom/include/ipcom_pkt.h */

typedef struct _END_CLOSURE
    {
    void * func;
    void * arg;
    } END_CLOSURE;

typedef struct _END_OUTPUT_FILTER
    {
    struct _END_OUTPUT_FILTER * pNext;
    END_CLOSURE origSend;
    } END_OUTPUT_FILTER;

typedef struct end_object END_OBJ;

typedef int (* END_MUX2SEND_RTN) (void * sendArg,
                                  struct Ipcom_pkt_struct * pkt);
typedef int (* END_MUXSEND_RTN) (END_OBJ * pEnd, M_BLK_ID pMblk);
typedef int (* END_TKSEND_RTN) (END_OBJ * pEnd, M_BLK_ID pMblk,
				char * pDstAddr, UINT16 netType, void * spare);

typedef void (* END2_RCV_RTN) (END_OBJ * pEnd, struct Ipcom_pkt_struct * pkt);
typedef STATUS (* END_RCV_RTN) (void * cookie, M_BLK_ID pMblk);
typedef void (* NPT_RCV_RTN) (void * cookie, M_BLK_ID pkt,
			      long netSvcOffset, long netSvcType,
			      BOOL uniPromiscuous, void * pSpare);

typedef int (* END2_POLLRCV_RTN) (END_OBJ * pEnd,
				  struct Ipcom_pkt_struct * pkt);

typedef int (* END_POLLRCV_RTN) (END_OBJ * pEnd, M_BLK_ID pkt);
typedef int (* NPT_POLLRCV_RTN) (END_OBJ * pEnd, M_BLK_ID pMblk,
				 long * pNetSvc, long * pNetOffset,
				 void * pSpareData);

typedef int (* END2_FORM_LINKHDR_RTN) (END_OBJ * pEnd,
				       struct Ipcom_pkt_struct * pkt,
				       UINT8 * dstAddr, UINT8 * srcAddr,
				       UINT16 netType);


/*
 *
 * endObject - the basic end object that everyone derives from
 *
 * This data structure defines a device independant amount of state
 * that is maintained by all drivers/devices.
 * Each specific device (Lance, Intel, etc.) derives from this object
 * first and then incorporates it's own data structures after it.
 *
 */
struct end_object
    {
    DEV_OBJ devObject;		/* Root of the device heirarchy. */

    SEM_ID txSem;		/* Transmitter semaphore, or NULL */
    END_CLOSURE send [NUM_BIND_STYLES]; /* send routines & args for the
					   different bind/call styles */

    END_OUTPUT_FILTER * outputFilter;	/* Optional output filters */

    STATUS (*receiveRtn) ();	/* receive routine; return value unused */
    void * rxArg;	/* receive routine argument (needed?) */

    int (*hdrParse) (struct end_object * pEnd, struct Ipcom_pkt_struct * pkt);

    struct proto_entry * pSnarf;   /* First snarf protocol */
    struct proto_entry * pTyped;   /* First typed protocol */
    struct proto_entry * pPromisc; /* First promiscuous protocol */
    struct proto_entry * pStop;          /* End of protocols */
    UINT32 nProtoSlots;               /* Number of slots in protocol table */

    int endStyle;             /* END, NPT, END2, ... */

    INT32 flags;			/* Various flags. */

#undef END_PKTDROP_INJECT
#ifdef END_PKTDROP_INJECT
    UINT32 dropMap;
#endif

    struct net_funcs *pFuncTable;	/* Function table. */

    /* legacy network pool */
    NET_POOL_ID pNetPool;       /* Memory cookie used by MUX buffering. */

    M2_ID * pMib2Tbl;           /* backwards compat; deprecated;
				   if non-NULL, points to following member */
    M2_ID end_m2Id;
#define mib2Tbl end_m2Id.m2Data.mibIfTbl

#if 0
    M2_INTERFACETBL mib2Tbl;	/* MIBII counters. */
#endif

    BOOL attached;		/* backwards compatibility, deprecated */

    LIST multiList;		/* Head of the multicast address list */
    int	nMulti;			/* Number of elements in the list. */

    END2_FORM_LINKHDR_RTN formLinkHdr;
    struct Ipcom_pkt_struct * pollPkt;  /* Packet reserved for polled send */

    END_CLOSURE pollSend [NUM_BIND_STYLES];
    END_CLOSURE pollRecv [NUM_BIND_STYLES];

    void * unloadInfo;		/* used for unload completion notification */

    unsigned short endObjId;     /* END/NPT device ID for Layer 2 */
/* #ifdef QOS */
    STATUS (*origReceiveRtn) (); /*Original MUX routine to call on reception.*/
    int (*qosHookRtn) ();        /* Packet classifier hook routine. */
/* #endif /@ QOS @/ */
    };

#define END_MIB_STATS(pEnd, mbr) \
    pEnd->end_m2Id.m2Data.mibIfTbl.mbr
#define END_MIB_2233_STATS(pEnd, mbr) \
    pEnd->end_m2Id.m2Data.mibXIfTbl.mbr

/*
 *
 * NET_FUNCS - driver function table
 *
 * This is a table that is created, one per driver, to hold all the
 * function pointers for that driver.  In this way we can have only one
 * instance to this structer, but one pointer per netDevice structure.
 *
 * This structure's layout (member order) is assumed by a lot of drivers.
 * Don't change it.
 */

typedef struct net_funcs
    {
    STATUS (*start) (END_OBJ*);		   /* Driver's start func. */
    STATUS (*stop) (END_OBJ*);		   /* Driver's stop func. */
    STATUS (*unload) (END_OBJ*);		   /* Driver's unload func. */
    int (*ioctl) (END_OBJ*, int, caddr_t);    /* Driver's ioctl func. */
    STATUS (*send) (END_OBJ* , M_BLK_ID);	   /* Driver's send func. */
    STATUS (*mCastAddrAdd) (END_OBJ*, char*); /* Driver's mcast add func. */
    STATUS (*mCastAddrDel) (END_OBJ*, char*); /* Driver's mcast delete func. */
    STATUS (*mCastAddrGet) (END_OBJ*, MULTI_TABLE*);
                                           /* Driver's mcast get fun. */
    STATUS (*pollSend) (END_OBJ*, M_BLK_ID);  /* Driver's polling send func. */
    STATUS (*pollRcv) (END_OBJ*, M_BLK_ID);   /* Driver's polling recv func. */

    /*
     * The minimum required arguments for (*formAddress)() are:
     * (*formAddress)(M_BLK_ID, M_BLK_ID, M_BLK_ID, BOOL)
     */
    M_BLK_ID (*formAddress) ();         /* Driver's addr formation func. */

    /*
     * The minimum required arguments for (*packetDataGet)() are
     * (*packetDataGet)(M_BLK_ID, LL_HDR_INFO *)
     */
    STATUS (*packetDataGet) ();         /* Driver's packet data get func. */
    STATUS (*addrGet) (M_BLK_ID, M_BLK_ID, M_BLK_ID, M_BLK_ID, M_BLK_ID);
                                           /* Driver's packet addr get func. */
    int (*endBind) (void*, void*, void*, long type);
					/* information exchange between */
					/* network service and network driver */
    } NET_FUNCS;

typedef struct _END2_NET_FUNCS
    {
    NET_FUNCS funcs;
    void (*llhiComplete) (struct Ipcom_pkt_struct * pkt, LL_HDR_INFO * llhi);
    } END2_NET_FUNCS;


/* This is the structure that is used by the BSP to build up a table
 * of END devices to be started at boot time.
 */
typedef struct end_tbl_entry
    {
    int unit;                                /* This device's unit # */
    END_OBJ* (*endLoadFunc) (char*, void*);         /* The Load function. */
    char* endLoadString;                     /* The load string. */
    BOOL endLoan;                            /* Do we loan buffers? */
    void* pBSP;                              /* BSP private */
    BOOL processed;                          /* Has this been processed? */
    } END_TBL_ENTRY;

#define END_TBL_END NULL

/*
 * Definitions and structures for polled stats counters.
 */

typedef unsigned long long endCounter;

typedef struct /*endIfCounters*/
    {
    endCounter		ifInErrors;
    endCounter		ifInDiscards;
    endCounter		ifInUnknownProtos;
    endCounter		ifInOctets;
    endCounter		ifInUcastPkts;
    endCounter		ifInMulticastPkts;
    endCounter		ifInBroadcastPkts;

    endCounter		ifOutErrors;
    endCounter		ifOutDiscards;
    endCounter		ifOutOctets;
    endCounter		ifOutUcastPkts;
    endCounter		ifOutMulticastPkts;
    endCounter		ifOutBroadcastPkts;
    } END_IFCOUNTERS;

#define END_IFINERRORS_VALID		0x00000001
#define END_IFINDISCARDS_VALID		0x00000002
#define END_IFINUNKNOWNPROTOS_VALID	0x00000004
#define END_IFINOCTETS_VALID		0x00000008
#define END_IFINUCASTPKTS_VALID		0x00000010
#define END_IFINMULTICASTPKTS_VALID	0x00000020
#define END_IFINBROADCASTPKTS_VALID	0x00000040

#define END_IFOUTERRORS_VALID		0x00010000
#define END_IFOUTDISCARDS_VALID		0x00020000
#define END_IFOUTUNKNOWNPROTOS_VALID	0x00040000
#define END_IFOUTOCTETS_VALID		0x00080000
#define END_IFOUTUCASTPKTS_VALID	0x00100000
#define END_IFOUTMULTICASTPKTS_VALID	0x00200000
#define END_IFOUTBROADCASTPKTS_VALID	0x00400000

typedef struct /*endIfDrvConf*/
    {
    int			ifPollInterval;
    UINT32		ifValidCounters;
    void *		ifWatchdog;
    END_OBJ *		ifEndObj;
    void *		ifMuxCookie;
    FUNCPTR		ifPollRtn;
    } END_IFDRVCONF;

/*
 * Structure used by EIOCGRCVJOBQ ioctl to retrieve the IDs of job queues
 * used by an END interface to deliver packets to the stack.  In the
 * future we may support multiple job queues per interface; at present,
 * there is a limit of just one.  However, the ioctl interface is capable
 * of reporting more than one.
 *
 * The MUX initializes numRcvJobQs with the number of available slots
 * in the array qIds.  The driver checks numRcvJobQs; if this is less
 * than the actual number of job queues used by the interface to deliver
 * received packets to the stack, the driver sets numRcvJobQs to the actual
 * number of queues it uses, returns ENOSPC, and does not modify the array
 * qIds. Otherwise, numRcvJobQs is greater than or equal to the number of
 * receive job queues used by the interface, and the driver should write
 * the actual number of queues into numRcvJobQs, write the JOB_QUEUE_IDs
 * of the queues into the initial elements of the array qIds in any convenient
 * order, and return OK.
 *
 * AT PRESENT, ONLY ONE RECEIVE JOB QUEUE IS PERMITTED PER INTERFACE.
 *
 * Defined here rather than in endCommon.h since the job queue IDs aren't
 * usable in user space.
 */

typedef struct _END_RCVJOBQ_INFO
    {
    UINT32 numRcvJobQs;    /* # job qs on which interface delivers packets */
    JOB_QUEUE_ID qIds [1]; /* variable length array of job queue IDs. */
    } END_RCVJOBQ_INFO;


/*
 * The vxbEndInfo method supported by some VxBus END drivers
 * (presently only DPAA drivers) may retrieve a value of this type.
 */
typedef struct _END_INFO
    {
    END_OBJ *pEnd;
    END_CAPABILITIES *pEndCaps;
    void * (*physToVirt) (UINT64); /* for cluster buffers */
    UINT clusterSize;
    }
END_INFO;

#ifdef __cplusplus
}
#endif

#endif /* __INCendh */
