/* ipProto.h - defines for the bsd protocol pseudo-device driver */

/* Copyright 1996 - 2006 Wind River Systems, Inc. */

/*
modification history
--------------------
02f,09jan12,h_x  Move extern "C" after last header file include.
02e,05sep06,kch  Cleanup for IPNet integration.
02d,07sep05,dlk  Add ipBcastAddrGet() prototype.
02c,24jun05,wap  Add ifmedia support
02b,07feb05,vvv  _KERNEL cleanup
02a,23aug04,rp   merged from COMP_WN_IPV6_BASE6_ITER5_TO_UNIFIED_PRE_MERGE
01z,28may04,niq  Merging from base6 label POST_ITER5_FRZ16_REBASE (ver
                 /main/vdt/base6_itn5_networking-int/1)
01y,24nov03,wap  Merge changes from Snowflake
01x,20nov03,niq  Remove copyright_wrs.h file inclusion
01w,04nov03,rlm  Ran batch header path update for header re-org.
01v,03nov03,rlm  Removed wrn/coreip/ prefix from #includes for header re-org.
01u,27oct03,cdw  update include statements post header re-org.
01t,08sep03,vvv  merged from ACCORDION_BASE6_MERGE_BASELINE
01s,09may03,vvv  added prototypes for ipDetach() and ip6Detach()
01r,29apr03,syy  Added #ifdef for __cplusplus
01q,11jul02,ann  added a new structure to hold the interface identifier info
01p,13jun02,ann  making some changes for IPv4/IPv6 attach issue
01o,03feb02,ham  changes for tornado build.
01n,25feb01,rae  merged 01o tor2_0.barney (base 01m):
		 moved nptFlag from END_OBJ for T2 END compatibility
01m,19apr00,spm  Merging NPT changes.
01l,05apr00,spm  cleanup: removing unused fields from control structure
01k,02mar99,pul  protoType for ipAttach(), SPR# 24253
01j,08aug98,ann  Included if_ether.h to reference idr
01i,08dec97,gnn  END code review fixes.
01h,25sep97,gnn  SENS beta feedback fixes
01g,19aug97,gnn  changes due to new buffering scheme.
01f,12aug97,gnn  changes necessitated by MUX/END update.
01e,02jun97,gnn  Added added memWidth to structure.
01d,21mar97,map  Added pRefCntHead, removed nLoan from BSD_DRV_CTRL.
01c,22jan97,gnn  Added new private flags that is seperate from if flags.
01b,21jan97,gnn  Removed buffer loaning stuff.
                 Added reference count information.
                 Added minFirstBuf for scatter/gather.
01a,17dec96,gnn	 written.

*/
 
#ifndef __INCipProtoh
#define __INCipProtoh

/* includes */

#include <net/if_arp.h>
#include <netinet/if_ether.h>

#ifdef __cplusplus
extern "C" {
#endif

/* defines */

/* Define the length for EUI 64 id storage */

#define EUI_64_LEN              8


/* 
 * Structure to hold the interface identifier information. This is used in
 * the alloction of global and link/site local addresses.
 */

typedef struct if_id_s
    {
    unsigned char   interfaceId[EUI_64_LEN];  /* EUI 64 based id */
    unsigned long   interfaceIdLen;           /* Length of id */
    /* The following field could change later */
    unsigned long   expireTimer;              /* Reserved for future use */
    } IF_ID_T;


/* forward declarations */

/* globals */
IMPORT int ipAttach (int unit, char * pDevice);

IMPORT int ipDetach (int unit, char * pDevice);

IMPORT int ip6Attach (int unit, char * pDevice);

IMPORT int ip6Detach (int unit, char * pDevice);

/* locals */

/* forward declarations */

#ifdef __cplusplus
}
#endif

#endif /* __INCipProtoh */
