/* muxLib.h - definitions for the MUX library */

/*
 * Copyright (c) 2001-2008, 2010, 2014, 2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
06sep17,xxy  Add support for timestamp transmission (F9714)
15jun17,xxy  TSN streams integration into the network stack (F9049).
17mar16,mca  Enable user-space build of END.
04sep14,wap  Add muxEndQnumSet()
05may14,rjq  Decouple COREIP with END. (V7NET-105)
24Feb14,h_s  Cleanup warnings for diab.
30oct13,tlu  Added an error code for network stack suspending failure
10nov10,dlk  Move extern "C" after last header file include. WIND00240828.
28mar08,dlk  Added muxProtoInfoGet()/muxProtoListGet().
                 Pass the PROTO_COOKIE also to mux2Bind() protocol shutdown
                 routines.
26feb08,dlk  MUX2 redesign.
12oct07,dlk  Made muxEndRxJobQueue() public. Added muxEndQnumGet().
                 Added muxErrorPost(). muxIfFuncBase scalability.
20sep07,dlk  Added muxLinkUpNotify() and muxLinkDownNotify().
02jan07,kch  Added muxIterate() prototype.
05aug06,kch  Cleanup.
25aug05,dlk  Add section tags.
28jul05,dlk  Added muxErrorSkip() declaration.
20feb05,dlk  Added MUX_FUNCS, muxEndTake(), muxEndGive(), MUX_PASSTHRU.
23aug04,rp   merged from COMP_WN_IPV6_BASE6_ITER5_TO_UNIFIED_PRE_MERGE
28may04,niq  Merging from base6 label POST_ITER5_FRZ16_REBASE (ver
                 /main/vdt/base6_itn5_networking-int/1)
24nov03,wap  Merge in changes from Snowflake
20nov03,niq  Remove copyright_wrs.h file inclusion
04nov03,rlm  Ran batch header path update for header re-org.
03nov03,rlm  Removed wrn/coreip/ prefix from #includes for header re-org.
27oct03,cdw  update include statements post header re-org.
08sep03,vvv  merged from ACCORDION_BASE6_MERGE_BASELINE
06feb03,vvv  merged from tor2_2-patch.alameda, ver02c (SPR #83258)
03feb02,ham  renamed dummyend.h to end.h.
20feb02,ham  changed for tornado build.
09jan02,ann  adding the field for the output function in MUX_ADDR_REC
15may01,ann  major changes as per MUX design doc for clarinet.
                 added some prototypes. code inherited from AE ver 02c.
*/

/*
DESCRIPTION
This file includes function prototypes for the MUX.

INCLUDE FILES:
*/

#ifndef __INCmuxLibh
#define __INCmuxLibh

/* includes */

#include <vsbConfig.h>
#include <end.h>

#ifdef __cplusplus
extern "C" {
#endif

/* defints */

/* MUX_MAX_IFTYPE associates with IFT_MAX_TYPE as default. If the user wants
 * to add a resource function, verify it's smaller than MUX_MAX_IFTYPE.
 */

#define MUX_MAX_IFTYPE M2_ifType_pmp

/* Error defines. */
#define S_muxLib_LOAD_FAILED                  (M_muxLib | 1)
#define S_muxLib_NO_DEVICE                    (M_muxLib | 2)
#define S_muxLib_INVALID_ARGS                 (M_muxLib | 3)
#define S_muxLib_ALLOC_FAILED                 (M_muxLib | 4)
#define S_muxLib_ALREADY_BOUND                (M_muxLib | 5)
#define S_muxLib_UNLOAD_FAILED                (M_muxLib | 6)
#define S_muxLib_NOT_A_TK_DEVICE              (M_muxLib | 7)
#define S_muxLib_NO_TK_DEVICE                 (M_muxLib | 8)
#define S_muxLib_END_BIND_FAILED              (M_muxLib | 9)
#define S_muxLib_MISSING_WRAPPERS             (M_muxLib | 10)
#define S_muxLib_END_SUSPEND_FAILED           (M_muxLib | 11)
#define S_muxLib_NO_LAUNCH_CAPABILITY         (M_muxLib | 12)
#define S_muxLib_LAUNCH_OVERFLOW              (M_muxLib | 13)
#define S_muxLib_LAUNCH_MISSED                (M_muxLib | 14)
#define S_muxLib_LAUNCH_SETUP_FAILED          (M_muxLib | 15)


/* These are above all SAPs but still in the ethernet size range */
/* so won't interfere with RFC 1700 */
#define MUX_PROTO_PROMISC	0x100
#define MUX_PROTO_SNARF         0x101
#define MUX_PROTO_OUTPUT        0x102

/*
 * Note that these bind styles are correlated in number
 * and order with the END styles in endCommon.h
 */
#define BIND_STYLE_MUX2BIND	0
#define BIND_STYLE_MUXBIND	1
#define BIND_STYLE_MUXTKBIND	2

/* NUM_BIND_STYLES is defined as 3 in end.h */

/*
 * The following defines are used for the various if-protocol functions
 * that are maintained by the MUX function table.
 */

#define ADDR_RES_FUNC           1
#define IF_OUTPUT_FUNC          2
#define MULTI_ADDR_RES_FUNC     4

/* typedefs */

/* structure passed for SIOCMUXPASSTRHU ioctl */

typedef struct _MUX_PASSTHRU
    {
    char name[END_NAME_MAX];	/* device name, without unit number */
    int unit;			/* unit number. */
    u_int cmd;			/* Tunnelled ioctl command. Must properly
				   encode size and IOC_IN/IOC_OUT/IOC_VOID,
				   and IOC_USER must be set if RTP access is
				   allowed. */
    void * pData;		/* Tunnelled ioctl data argument */
    } MUX_PASSTHRU;

/*
 * These data structures define the 2D list of address resolution
 * functions.  This list is ordered by ifType and the protocol.
 */
typedef struct mux_addr_rec
    {
    NODE node;
    long protocol;
    int  setFuncs;
    FUNCPTR addrResFunc;
    FUNCPTR ifOutputFunc;
    FUNCPTR multiAddrResFunc;
    } MUX_ADDR_REC;

/* function pointers for scalability */

typedef struct _MUX_FUNCS
    {
    void * (*endTake) (const char * pName, int unit);
    void   (*endGive) (void * pCookie);
    int    (*ioctl) (void* pCookie, int cmd, caddr_t data);
    /* ADD MORE HERE AS NEEDED */
    } MUX_FUNCS;

/*
 * PROTO_COOKIE is the opaque pointer type returned by mux2Bind(),
 * muxBind(), and muxTkBind().  It represents the binding of a protocol
 * to a network device.  It is used in calls to muxIoctl(), muxUnbind(),
 * muxSend(), muxPollSend(), muxPollReceive(), muxTkSend(), muxTkPollSend(),
 * muxTkPollReceive(), muxMCastAddrAdd(), muxMCastAddrDel(),
 * muxMCastAddrGet(), muxLinkHeaderCreate(), muxAddressForm(),
 * muxPacketDataGet(), and muxPacketAddrGet().
 *
 * Note that mux2Send(), mux2PollSend(), and mux2PollReceive() require
 * a DEV_COOKIE, not a PROTO_COOKIE.
 */
typedef void * PROTO_COOKIE;

/*
 * DEV_COOKIE is the opaque pointer type returned by muxDevLoad() and
 * muxDevAcquire(), and passed to muxDevRelease(), muxDevStart(), and
 * muxDevStop(), muxError(), mux2Send(), mux2PollSend(), and mux2PollReceive().
 * It represents the network device. (Pssst: it's an END_OBJ *)
 *
 * For VxWorks 6.7 and later: a DEV_COOKIE may be used a fake
 * PROTO_COOKIE, for the purposes of calling muxSend(), muxIoctl(),
 * muxPollSend(), muxPollReceive(), muxTkSend(), muxTkPollSend(),
 * muxMCastAddrAdd(), muxMCastAddrDel(), muxMCastAddrGet(),
 * muxLinkHeaderCreate(), muxAddressForm(), muxPacketDataGet(), and
 * muxPacketAddrGet().
 *
 * Don't use a DEV_COOKIE for a call to muxUnbind() or muxTkPollReceive();
 * they work only with a real PROTO_COOKIE.
 */
typedef void * DEV_COOKIE;

/*
 * Protocol information. Returned by muxProtoInfoGet().  Note that
 * the actual signatures of the callback functions depends upon the
 * binding style.
 */
typedef struct _MUX_PROTO_INFO
    {
    char name[END_PROTO_NAME_MAX];  /* String name for this protocol */
    int netSvcType;                 /* Network service type */
    int bindStyle;		    /* MUX bind style (BIND_STYLE_* above) */
    BOOL (*stackRcvRtn) ();         /* Protocol's receive routine */
    STATUS (*stackTxRestartRtn) (); /* Callback for restarting blocked tx. */
    STATUS (*stackShutdownRtn) ();  /* The routine to call to shut down */
    void (*stackErrorRtn) ();       /* Callback for device errors/events */
    DEV_COOKIE pEnd;
    void * callbackArg;
    } MUX_PROTO_INFO;

typedef struct _MUX_PROTOS_INFO
    {
    int nprotos;		/* Number of PROTO_INFOs in plist */
    MUX_PROTO_INFO * plist;		/* Array of PROTO_INFO structures */
    } MUX_PROTOS_INFO;

/* globals */

IMPORT MUX_FUNCS _func_mux;

/* locals */

/* function declarations */

/* common routines shared by all device styles and protocol binding styles */

IMPORT STATUS muxCommonInit (void);
IMPORT DEV_COOKIE muxDevAcquire (const char * name, int unit);
IMPORT void       muxDevRelease (DEV_COOKIE pEnd);

IMPORT END_OBJ  * endFindByName (char* pName, int unit);

IMPORT DEV_COOKIE muxDevLoad (int unit, END_OBJ* (*endLoad) (char *, void*),
                              char *initString, BOOL loaning, void*pBSP);
IMPORT STATUS muxDevUnload (char* pName, int unit);

IMPORT STATUS muxDevStart (DEV_COOKIE pEnd);
IMPORT STATUS muxDevStop (DEV_COOKIE pEnd);
IMPORT STATUS muxDevStopAll (int timeout);

IMPORT int  muxEndListGet (END_OBJ ** pEnds, int nSlots);
IMPORT void muxShow (char* pDevName, int unit);

IMPORT STATUS muxUnbind(PROTO_COOKIE cookie, long type,
			FUNCPTR stackShutdownRtn);

IMPORT STATUS muxIoctl (PROTO_COOKIE cookie, int cmd, caddr_t data);

IMPORT STATUS muxMCastAddrAdd (PROTO_COOKIE cookie, char* pAddress);
IMPORT STATUS muxMCastAddrDel (PROTO_COOKIE cookie, char* pAddress);
IMPORT STATUS muxMCastAddrGet (PROTO_COOKIE cookie, MULTI_TABLE* pTable);

IMPORT void muxTxRestart(void * pEnd);

IMPORT void muxErrorSkip (DEV_COOKIE pEnd, END_ERR * pError,
			  PROTO_COOKIE skipProtoCookie);
IMPORT void muxErrorPost(END_OBJ * pEnd, INT32 errCode,
			 char * pMesg, void * pSpare);

IMPORT JOB_QUEUE_ID muxEndRxJobQueue (END_OBJ * pEnd);
IMPORT int muxEndQnumGet (char * instName, int unit);
IMPORT STATUS muxEndQnumSet (char * instName, int unit, int qNum);

IMPORT int    muxProtoListGet (END_OBJ * pEnd, MUX_PROTOS_INFO * pInfo);
IMPORT STATUS muxProtoInfoGet (PROTO_COOKIE cookie, MUX_PROTO_INFO * pInfo);

/* routines for END-style devices and muxBind() protocols */

IMPORT STATUS muxLibInit (void);

IMPORT PROTO_COOKIE muxBind (char * pName, int unit,
                  BOOL (*stackRcvRtn) (void*, long,M_BLK_ID, LL_HDR_INFO *,
                                       void*),
                  STATUS (*stackShutdownRtn) (void*, void*),
                  STATUS (*stackTxRestartRtn) (void*, void*),
                  void (*stackErrorRtn) (END_OBJ*, END_ERR*, void*),
                  long type, char* pProtoName, void* pSpare);

IMPORT STATUS muxSend (PROTO_COOKIE cookie, M_BLK_ID pMblk);
IMPORT STATUS muxPollSend (PROTO_COOKIE cookie, M_BLK_ID pMblk);
IMPORT STATUS muxPollReceive (PROTO_COOKIE cookie, M_BLK_ID pMblk);

IMPORT M_BLK_ID muxLinkHeaderCreate(PROTO_COOKIE cookie, M_BLK_ID pPacket,
				    M_BLK_ID pSrcAddr, M_BLK_ID pDstAddr,
				    BOOL bcastFlag);

IMPORT M_BLK_ID muxAddressForm (PROTO_COOKIE cookie, M_BLK_ID pMblk,
				M_BLK_ID pSrcAddr, M_BLK_ID pDstAddr);
IMPORT STATUS muxPacketDataGet(PROTO_COOKIE cookie, M_BLK_ID pMblk,
			       LL_HDR_INFO *);
IMPORT STATUS muxPacketAddrGet (PROTO_COOKIE cookie, M_BLK_ID pMblk,
                                M_BLK_ID pSrc,
                                M_BLK_ID pDst,
                                M_BLK_ID pESrc,
                                M_BLK_ID pEDst);

IMPORT BOOL muxDevExists (char* pName, int unit);

/* These functions are deprecated */
IMPORT STATUS muxAddrResFuncDel (long ifType, long protocol);
IMPORT FUNCPTR muxAddrResFuncGet (long ifType, long protocol);
IMPORT STATUS muxAddrResFuncAdd (long ifType, long protocol,
				 FUNCPTR addrResFunc);

IMPORT STATUS muxIfFuncBaseInit (void);
IMPORT STATUS muxIfFuncDel (long ifType, long protocol, int funcType);
IMPORT FUNCPTR muxIfFuncGet (long ifType, long protocol, int funcType);
IMPORT STATUS muxIfFuncAdd (long ifType, long protocol, int funcType,
			    FUNCPTR ifFunc);
IMPORT END_OBJ* endFirstUnitFind (char* pDevName);

/* Routines called (mostly) by network device drivers */

IMPORT STATUS muxReceive (void * pEnd, M_BLK_ID pMblk);

IMPORT void muxError (DEV_COOKIE pEnd, END_ERR * pError);
IMPORT void muxLinkUpNotify (END_OBJ * pEnd);
IMPORT void muxLinkDownNotify (END_OBJ * pEnd);

/* utility routines (deprecate these?) */

IMPORT STATUS muxIterate (FUNCPTR pCallbackRtn, void * pCallbackArg);
IMPORT STATUS muxIterateByName (char * pName, FUNCPTR pCallbackRtn,
				void * pCallbackArg);

#ifdef __cplusplus
}
#endif

#endif /* __INCmuxLibh */
