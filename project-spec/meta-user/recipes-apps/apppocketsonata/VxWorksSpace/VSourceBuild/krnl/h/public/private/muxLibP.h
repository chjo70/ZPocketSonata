/* muxLibP.h - private definitions for the MUX library */

/* Copyright 1998-2001, 2003, 2005, 2007-2008, 2010, 2012-2013, 2015
   Wind River Systems, Inc.
 */

/*
modification history
--------------------
08aug15,m_w  Added muxEndExecute(). (V7PRO-2249)
30oct13,tlu  Modified for suspending network stack
29may12,xhs  Fix memory leak, defect WIND00340041
10nov10,dlk  Move extern "C" after last header file include. WIND00240828.
28mar08,dlk  Moved BIND_STYLE_* macros to muxLib.h for muxProtoInfoGet().
22mar08,dlk  MUX2 redesign. 1st checkin.
12oct07,dlk  Made muxEndRxJobQueue() public.
25aug05,dlk  Add section tags.
27jul05,dlk  Added muxEndRxJobQueue(). May be temporary.
21nov03,wap  Merge in changes from Snowflake
20nov03,niq  Remove copyright_wrs.h file inclusion
04nov03,rlm  Ran batch header path update for header re-org.
03nov03,rlm  Removed wrn/coreip/ prefix from #includes for header re-org.
01jul03,ann  removed obsoleted code
10sep01,ann  correcting the directory paths
15may01,ann  major changes as per the MUX design doc for clarinet
             - obsoleted the BIB and all its associated routines.
25feb01,rae  RFC2233 changes
19apr00,ham  merged TOR2_0-NPT-FCS (01a,06oct98,sj-01p,05oct99,pul).
05oct99,pul  removing rtRequest and mCastMap
29apr99,pul  Upgraded NPT phase3 code to tor2.0.0
24mar99,sj   changed tkFlag field in muxBindEntry to flags; added defines
24mar99,sj   added defines for flags field of NET_PROTOCOL structure
18mar99,sj   cleaned up: completed the cleanup postponed in 01j,05mar99,sj
08mar99,sj   added place holder for stackrcv routine in BIB entry
05mar99,sj   eliminated hooks; not cleanly though. next version will do that
24feb99,sj   added netSvcType and netDrvType fields to the BIB entry
26jan99,sj   moved BIB entry definition from muxTkLib.c to here
05nov98,sj   PCOOKIE_TO_ENDOBJ must check if pCookie is NULL
03nov98,pul  modified IPPROTO_MCAST_MAP_GET
03nov98,sj   doc update
20oct98,pul	 don't return ERROR if hook is not valid
15oct98,pul	 added ipProto Hooks
12oct98,sj 	 changed MUX_TK_ADDR_RES_FUNC_UPDATE, added WRS_*_MODULE
06oct98,sj 	 written.
*/

/*
DESCRIPTION
This file includes macros used by muxLib to avail features of the NPT
architecture if it is installed.


INCLUDE FILES:
*/

#ifndef __INCmuxLibPh
#define __INCmuxLibPh

#include <vxWorks.h>
#include <muxLib.h>

#ifndef MUX_NDEBUG
#include <assert.h>

#define MUX_ASSERT(x) \
    do  { \
        if (!(x)) \
	    __assert("Assertion failed: "#x", file " 	\
		     __FILE__ ", line "_ASSERT_STR(__LINE__)"\n"); \
        } while ((0))
#else
#define MUX_ASSERT(x) do {} while ((0))
#endif /* MUX_NDEBUG */

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _MUX_END_STYLE_INFO
    {
    void * sendWrappers [NUM_BIND_STYLES];
    void * pollSendWrappers [NUM_BIND_STYLES];
    void * pollReceiveWrappers [NUM_BIND_STYLES];
    void * rxRtn;
    } MUX_END_STYLE_INFO;

extern MUX_END_STYLE_INFO muxEndStyles [NUM_END_STYLES];


typedef struct _MUX_BIND_STYLE_INFO
    {
    void * sendFilter [NUM_END_STYLES];
    void * rxWrappers [NUM_END_STYLES];
    void * snarfWrappers [NUM_END_STYLES];
    } MUX_BIND_STYLE_INFO;

extern MUX_BIND_STYLE_INFO muxBindStyles [NUM_BIND_STYLES];

/*
 * This structure is a row in our run time END table.
 * Each row contains all the units started on a particular named device.
 * I.e. all devices that are Lance 7990 Ethernet will be in the list
 * off of the row with the name "ln".
 */

typedef struct end_tbl_row
    {
    NODE node;                  /* Needed by our list processing library. */
    char name[END_NAME_MAX];	/* Name of the devices in row. (ln, etc.) */
    LIST units;                 /* List of devices, i.e. 0, 1, etc..  */
    } END_TBL_ROW;

/* MUX-private bit flags for the muxFlags member in a DEV_OBJ: */

#define MUX_END_FLAG_LOADING	0x00000001
#define MUX_END_FLAG_UNLOADING	0x00000002

/* we steal these defines from a END driver */

#define END_IOCTL(pEnd)                                             \
		(pEnd->pFuncTable->ioctl)

#define END_ALT_HADDR(pEnd) \
                ((pEnd)->pMib2Tbl->m2Data.mibIfTbl.ifPhysAddress.phyAddress)
#define END_ALT_HADDR_LEN(pEnd) \
                ((pEnd)->pMib2Tbl->m2Data.mibIfTbl.ifPhysAddress.addrLength)


#define END_HADDR(pEnd)                                                 \
                ((pEnd)->mib2Tbl.ifPhysAddress.phyAddress)

#define END_HADDR_LEN(pEnd)                                             \
                ((pEnd)->mib2Tbl.ifPhysAddress.addrLength)

#define END_MIB2_TYPE(pEnd)                                             \
                ((pEnd)->mib2Tbl.ifType)

typedef struct proto_entry PROTO_ENTRY; /* forward declaration typedef */

struct Ipcom_pkt_struct;

typedef int  (* MUX_END_JOBQ_DO_FUNC) (END_OBJ * pEnd, void * arg);

typedef BOOL (* MUXBIND_PROTO_RX_RTN) (PROTO_COOKIE cookie, long type,
                    M_BLK_ID pMblk,
                    LL_HDR_INFO * pLinkHdrInfo,
                    void * callbackArg);
typedef BOOL (* MUXTKBIND_PROTO_RX_RTN) (void * callbackArg, long type,
                    M_BLK_ID pMblk, void * pSpareData);
typedef BOOL (* MUX2BIND_PROTO_RX_RTN) (void * callbackArg,
					struct Ipcom_pkt_struct * pkt);

typedef void (* MUX_END_EXEC_FUNC) (END_OBJ * pEnd,
                    _Vx_usr_arg_t arg2,
                    _Vx_usr_arg_t arg3,
                    _Vx_usr_arg_t arg4);

/*
 * The PROTOCOL_BINDING structure represents the binding of a protocol to
 * an END or NPT device. Additional or duplicate information, particularly
 * that needed for receive, is stored in the PROTO_ENTRY structure in the
 * interface's protocol table. The PROTO_ENTRY structure in turn contains
 * a pointer back to this structure.
 */

typedef struct protocol_binding
    {
    END_OBJ * pEnd;		    /* Interface to which protocol is bound */
    PROTO_ENTRY * pEntry;	    /* information needed by receive */
    UINT16 netSvcType;              /* Network service type */
    UINT8 flags;
    UINT8 bindStyle;                /* BIND_STYLE_{MUXBIND|MUXTKBIND|MUX2} */
    void * netCallbackId;	    /* Callback ID passed to muxBind */
    BOOL (*stackRcvRtn) ();         /* protocol's receive routine */
    STATUS (*stackTxRestartRtn) (); /* Callback for restarting blocked tx. */
    STATUS (*stackShutdownRtn) ();  /* The routine to call to shutdown */
				    /* the protocol stack. */
    void (*stackErrorRtn) ();       /* Callback for device errors/events */
    long netIfType;		    /* Interface type */
    END_OUTPUT_FILTER outFilter;    /* Used for MUX_PROTO_OUTPUT protocols */
    char name[END_PROTO_NAME_MAX];  /* String name for this protocol. */
    } PROTOCOL_BINDING;

/*
 * Each device has a table of PROTO_ENTRY structures corresponding to
 * the protocols bound to it. This structure contains information needed
 * for receive, as well as a pointer to the corresponding PROTOCOL_BINDING
 * structure. The caching of information needed for receive in the small
 * PROTO_ENTRY structure is done purely for performance reasons.
 *
 * The protocol receive routine stored in the PROTO_ENTRY is in certain
 * cases a wrapper function around the actual protocol receive routine.
 */

struct proto_entry
    {
    UINT16 type;
    UINT16 reserved;

    union	/* protocol receive routine */
	{
	void * generic;
	MUXBIND_PROTO_RX_RTN endRcv;
	MUXTKBIND_PROTO_RX_RTN nptRcv;
	MUX2BIND_PROTO_RX_RTN end2Rcv;
	} rr;

    void * recvRtnArg;

    PROTOCOL_BINDING * pBinding;
    };

/* A little bit of backwards compatibility */

typedef PROTOCOL_BINDING * MUX_ID;

/*
 * Convert from a void * cookie (which is a PROTOCOL_BINDING) to an
 * END_OBJ pointer:
 */

#define PCOOKIE_TO_ENDOBJ(pCookie) ((pCookie) ? ((MUX_ID)pCookie)->pEnd : NULL)

/*
 * Note, a device cookie returned by muxDevLoad(), passed to muxDevStart(),
 * etc., is not the same as a binding cookie returned by muxBind().
 * Presently, a device cookie is just a pointer to the END_OBJ.
 */

#define PDEVCOOKIE_TO_ENDOBJ(pCookie) ((END_OBJ *)(pCookie))

/*
 * These macros are used by muxAddrRecFuncXXX functions
 */
 #define TK_ADDR_RES_GET 1
 #define TK_ADDR_RES_ADD 2
 #define TK_ADDR_RES_DEL 3

/* global variables */ /* XXX dlk - needed? */

extern SEM_ID muxLock;

/* prototypes */

extern STATUS  muxTkLibInit (void);
extern void *  muxBindCommon (int bindStyle, char * pName, int unit,
                            BOOL (*stackRcvRtn) (),
                            STATUS (*stackShutdownRtn) (),
                            STATUS (*stackTxRestartRtn) (),
                            void   (*stackErrorRtn) (), long type,
                            char * pProtoName, void * pNetCallbackId,
                            void * pNetSvcInfo, void * pNetDrvInfo);
extern long    muxIfTypeGet (END_OBJ * pEnd);
extern int     muxEndJobQDo (END_OBJ * pEnd, JOB_QUEUE_ID qId,
                            MUX_END_JOBQ_DO_FUNC func,
                            void * arg);
extern STATUS  muxEndExecute (MUX_END_EXEC_FUNC pFunc,
                            _Vx_usr_arg_t arg2,
                            _Vx_usr_arg_t arg3,
                            _Vx_usr_arg_t arg4);

extern struct Ipcom_pkt_struct * muxMblkToIpcomPktTx (M_BLK * pMblk);
extern struct Ipcom_pkt_struct * muxMblkToIpcomPktRx (M_BLK * pMblk,
                                                      unsigned stack_idx);
extern M_BLK * muxIpcomPktToMblkTx (struct Ipcom_pkt_struct * pkt);
extern void    muxRestoreIpcomPktFromMblkTx(M_BLK * pMblk,
                            struct Ipcom_pkt_struct *pkt);
extern M_BLK * muxRestoreMblkFromIpcomPkt (struct Ipcom_pkt_struct *pkt,
                            unsigned stack_idx);
extern void    muxIpcomPktFreeMblk (void * buf, M_BLK * pMblk);
extern void    vxmux_mux_mblk_init (void);

#ifdef __cplusplus
}
#endif

#endif /* __INCmuxLibPh */
