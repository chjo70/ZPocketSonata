/* m2Lib.h - VxWorks MIB-II interface to SNMP Agent */

/*
 * Copyright (c) 1993, 1997-1999, 2001-2006, 
 *                    2008, 2010, 2012, 2014, 2016 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
20jul16,brk  include vxTypesOld.h so sysV types defined without VxWorks.h
05may14,rjq  Decouple COREIP with END. (V7NET-105)
13jan14,h_s      Remove MPLS support. (US19989)
21mar12,swg  support sysOR* group in RFC 3418(WIND00000597) 
23jun10,h_x  Fix WIND00219677
18jun10,h_x  Modify MIB2 structures to adapt rfc and SNMP on 64-bit system.
29apr10,pad  Moved extern C statement after include statements.
02feb10,h_x  Support 64bit
22may08,dlk  Added m2IfTblInit() prototype.
28sep06,kch  Removed references to struct ifnet.
09sep06,kch  Cleanup for IPNet integration
19jun06,jpb  Removed I960 check.
19apr05,rp   merged from comp_wn_ipv6_mld_interim-dev
07feb05,vvv  _KERNEL cleanup
19sep04,spm  updated virtual stack startup: restored use of published
             init routines and removed packing/unpacking of parameters
23aug04,rp   merged from COMP_WN_IPV6_BASE6_ITER5_TO_UNIFIED_PRE_MERGE
28may04,niq  Merging from base6 label POST_ITER5_FRZ16_REBASE (ver
             /main/vdt/base6_itn5_networking-int/1)
09feb04,niq  define socket to remove rtp compile errors.
02dec03,zl   use avlUintLib instead of avlLib
20nov03,niq  Remove copyright_wrs.h file inclusion
04nov03,rlm  Ran batch header path update for header re-org.
03nov03,rlm  Removed wrn/coreip/ prefix from #includes for header re-org.
24oct03,cdw  update include statements post header re-org.
15sep03,vvv  updated path for new headers
08sep03,vvv  merged from ACCORDION_BASE6_MERGE_BASELINE
15may03,spm  Tornado 2.2 FCS update (from ver 01i,22apr02,rae:
             TOR2_2-FCS-COPY label, tor2 branch, /wind/river VOB)
15may03,spm  fixed IGMP prototypes missed in CP1 merge (SPR #70643)
01may03,spm  Tornado 2.2 CP1 merge (from ver 01k,27jan03,vvv:
             TOR2_2-CP1-F label, tor2_2-patch branch, /wind/river VOB)
11oct02,ham  added m2LibInit(), m2Ipv6LibInit() (SPR 83041).
01oct02,ham  added m2IfMgtLibInit().
30sep02,vvv  fixed MAXOIDLENGH typo (SPR #73303)
06aug02,ann  added the prototype for m2If8023PacketCount
17jun02,ann  adding some flags to accomplish IPv4/IPv6 separation
16may02,ann  added the changes described in the generic MIB interface
             design document
02feb02,ham  changed for tornado build.
13sep01,ann  correcting the M2_ctrId_ifOutNUcastPkts counter
25feb01,rae  merged 01k tor2_0.barney (base 01e):
24mar99,ead  added m2SetIfLastChange() declaration (SPR #23290)
10sep98,ann  added doc to M2_INTERFACETBL fields spr# 21078
11apr97,rjc  fixed bad value of error define
05feb97,rjc  added new error codes to support phase-2 ospf mib  
08dec93,jag  written
*/

#ifndef __INCm2Libh
#define __INCm2Libh

#include <types/vxTypesOld.h>
#include <m2Lib_type.h>

#ifdef __cplusplus
extern "C" {
#endif

/* function declarations */
 
#if defined(__STDC__) || defined(__cplusplus)

extern STATUS m2SysInit (char *	mib2SysDescr, char * mib2SysContact,
		         char *	mib2SysLocation, M2_OBJECTID * pObjectId);

extern STATUS m2SysGroupInfoGet (M2_SYSTEM * pSysInfo);
extern STATUS m2SysGroupInfoSet (unsigned int varToSet, M2_SYSTEM * pSysInfo);
extern STATUS m2SysDelete (void);

extern STATUS mibIfAlloc (M2_ID **, ULONG, UCHAR *, ULONG, ULONG, 
			  ULONG, char *, int);
extern M2_ID * m2IfAlloc (ULONG, UCHAR *, ULONG, ULONG, ULONG, char *, int);
extern STATUS  m2IfFree (M2_ID *);
extern STATUS  m2IfTblInit (M2_ID *, ULONG, UCHAR *, ULONG,
			    ULONG, ULONG, char *, int);
extern STATUS  m2CounterUpdate (M2_ID *, UINT, UINT, UCHAR *);
extern STATUS  m2VariableUpdate (M2_ID *, UINT, caddr_t);
extern STATUS  m2If8023PacketCount (M2_ID *, UINT, UCHAR *, UINT);
extern STATUS  m2IfPktCountRtnInstall (M2_ID *, M2_PKT_COUNT_RTN);
extern STATUS  m2IfCtrUpdateRtnInstall (M2_ID *, M2_CTR_UPDATE_RTN);
extern STATUS  m2IfVarUpdateRtnInstall (M2_ID *, M2_VAR_UPDATE_RTN);

extern STATUS m2IfInit (FUNCPTR pTrapRtn, void * pTrapArg);

#if 0
extern STATUS m2IfTableUpdate (struct ifnet * pIfNet, UINT status,
			int (*func) (struct socket*,u_long,caddr_t),
			STATUS (func2) (struct ifnet*, M2_IFINDEX*), 
            UINT mibsSupported);
#endif
extern STATUS m2IfGroupInfoGet (M2_INTERFACE * pIfInfo);
extern STATUS m2IfTblEntryGet (int search, void * pIfTblEntry);
extern STATUS m2IfTblEntrySet (void *);
extern STATUS m2IfStackTblUpdate (UINT lowerIndex, UINT higherIndex, int action);
extern STATUS m2IfStackEntryGet (int, int *,  M2_IFSTACKTBL *);
extern STATUS m2IfStackEntrySet (int, M2_IFSTACKTBL *);
extern STATUS m2IfRcvAddrEntryGet (int, int *, M2_IFRCVADDRTBL *);
extern STATUS m2IfRcvAddrEntrySet (int, int, M2_IFRCVADDRTBL *);
extern STATUS m2IfDelete (void);

extern STATUS m2IpInit (int maxRouteTableSize);
extern STATUS m2IpGroupInfoGet (M2_IP * pIpInfo);
extern STATUS m2IpGroupInfoSet (unsigned int varToSet, M2_IP * pIpInfo);

extern STATUS
	   m2IpAddrTblEntryGet (int search, M2_IPADDRTBL * pIpAddrTblEnry);

extern STATUS
m2IpRouteTblEntryGet (int   search, M2_IPROUTETBL * pIpRouteTblEntry);

extern STATUS
m2IpRouteTblEntrySet (int varToSet, M2_IPROUTETBL * pIpRouteTblEntry);

extern STATUS
    m2IpAtransTblEntryGet (int search, M2_IPATRANSTBL * pIpAtEntry);
extern STATUS
    m2IpAtransTblEntrySet (M2_IPATRANSTBL * pIpAtEntry);
extern STATUS m2IpDelete (void);

extern STATUS m2IcmpInit (void);
extern STATUS m2IcmpGroupInfoGet (M2_ICMP * pIcmpInfo);

extern STATUS m2TcpInit (void);
extern STATUS m2TcpGroupInfoGet (M2_TCPINFO * pTcpInfo);

extern STATUS m2TcpConnEntryGet (int search, M2_TCPCONNTBL * pTcpConnEntry);
extern STATUS m2TcpConnEntrySet (M2_TCPCONNTBL * pTcpConnEntry);

extern STATUS m2UdpInit (void);
extern STATUS m2UdpGroupInfoGet (M2_UDP * pUdpInfo);

extern STATUS m2UdpTblEntryGet (int search, M2_UDPTBL * pUdpEntry);

STATUS m2Init (char * pMib2SysDescr, char * pMib2SysContact,
               char * pMib2SysLocation,
               M2_OBJECTID * pMib2SysObjectId, FUNCPTR pTrapRtn,
               void * pTrapArg, int maxRouteTableSize);

extern STATUS m2Delete (void);
extern STATUS m2TcpDelete (void);
extern STATUS m2UdpDelete (void);
extern STATUS m2IcmpDelete (void);
extern STATUS m2SetIfLastChange (int ifIndex);
extern STATUS m2IgmpInit ();
extern STATUS m2IgmpInterfaceEntrySet(M2_IGMP *data, int varsToSet);
extern STATUS m2IgmpInterfaceEntryGet(M2_IGMP *data);
extern STATUS m2IgmpInterfaceEntryNextGet(M2_IGMP *data);
extern STATUS m2IgmpCacheEntryGet(M2_IGMP_CACHE *data);
extern STATUS m2IgmpCacheEntryNextGet(M2_IGMP_CACHE *data);
extern M2_IGMP_CACHE * igmpCacheEntry_first(void);
extern M2_IGMP_CACHE * igmpCacheEntry_next_inst(M2_IGMP_CACHE * data);
extern unsigned igmpCacheEntry_build_instance(M2_IGMP_CACHE * data, int * inst);
extern STATUS m2IgmpTreeAdd ();
extern STATUS m2IfMgtLibInit(void);
extern STATUS m2LibInit (void);
extern STATUS m2Ipv6LibInit (void);

#else   /* __STDC__ */

extern STATUS m2SysInit ();
extern STATUS m2SysGroupInfoGet ();
extern STATUS m2SysGroupInfoSet ();
extern STATUS m2SysDelete ();
extern M2_ID * m2IfAlloc ();
extern STATUS m2IfFree ();
extern STATUS m2IfGenericPacketCount ();
extern STATUS m2IfCounterUpdate ();
extern STATUS m2IfVariableUpdate ();
extern STATUS m2IfPktCountRtnInstall ();
extern STATUS m2IfCtrUpdateRtnInstall ();
extern STATUS m2IfVarUpdateRtnInstall ();
extern STATUS m2If8023PacketCount ();
extern STATUS m2IfInit ();
extern STATUS m2IfTableUpdate ();
extern STATUS m2IfGroupInfoGet ();
extern STATUS m2IfTblEntryGet ();
extern STATUS m2IfTblEntrySet ();
extern STATUS m2IfStackTblUpdate ();
extern STATUS m2IfStackEntryGet ();
extern STATUS m2IfStackEntrySet ();
extern STATUS m2IfRcvAddrEntryGet ();
extern STATUS m2IfRcvAddrEntrySet ();
extern STATUS m2IfDelete ();
extern STATUS m2IpInit ();
extern STATUS m2IpGroupInfoGet ();
extern STATUS m2IpGroupInfoSet ();
extern STATUS m2IpAddrTblEntryGet ();
extern STATUS m2IpRouteTblEntryGet ();
extern STATUS m2IpRouteTblEntrySet ();
extern STATUS m2IpAtransTblEntryGet ();
extern STATUS m2IpAtransTblEntrySet ();
extern STATUS m2IpDelete ();
extern STATUS m2IcmpInit ();
extern STATUS m2IcmpGroupInfoGet ();
extern STATUS m2TcpInit ();
extern STATUS m2TcpGroupInfoGet ();
extern STATUS m2TcpConnEntryGet ();
extern STATUS m2TcpConnEntrySet ();
extern STATUS m2UdpInit ();
extern STATUS m2UdpGroupInfoGet ();
extern STATUS m2UdpTblEntryGet ();
extern STATUS m2Init ();
extern STATUS m2Delete ();
extern STATUS m2TcpDelete ();
extern STATUS m2UdpDelete ();
extern STATUS m2IcmpDelete ();
extern STATUS m2SetIfLastChange ();
extern STATUS m2IgmpInit ();
extern STATUS m2IgmpInterfaceEntrySet();
extern STATUS m2IgmpInterfaceEntryGet();
extern STATUS m2IgmpInterfaceEntryNextGet();
extern STATUS m2IgmpCacheEntryGet();
extern STATUS m2IgmpCacheEntryNextGet();
extern M2_IGMP_CACHE * igmpCacheEntry_first();
extern M2_IGMP_CACHE * igmpCacheEntry_next_inst();
extern unsigned igmpCacheEntry_build_instance();
extern STATUS m2IgmpTreeAdd ();
extern STATUS m2IfMgtLibInit();
extern STATUS m2LibInit();
extern STATUS m2Ipv6LibInit();
#endif  /* __STDC__ */

#ifdef __cplusplus
}
#endif

#endif /* __INCm2Libh */
