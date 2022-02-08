/* ifLib.h - network interface library header */

/* Copyright 1984-2003, 2014 Wind River Systems, Inc. */

/*
modification history
--------------------
01l,07nov08,brg  added arpResolve for now.
01k,15nov07,brg  reinstated after 'ipnetifying' it.
01j,14dec03,ijm  merged SPR#85896, interface based proxy ARP services;
                 removed obsolete prototypes
01i,05nov03,cdw  Removal of unnecessary _KERNEL guards.
01h,04nov03,rlm  Ran batch header path update for header re-org.
01g,03nov03,rlm  Removed wrn/coreip/ prefix from #includes for header re-org.
01f,08sep03,vvv  merged from ACCORDION_BASE6_MERGE_BASELINE
01e,10jun03,vvv  include netVersion.h
01d,06may03,ijm  added ifAddrDelete
01c,01feb03,pas  fixed ifunit() to agree with dlink/if_var.h (from FreeBSD 4.7)
01b,06mar02,ham  added ifLibInit.
01a,02feb02,ppp  ported from A.E. 1.1.
*/


#ifndef __INCifLibh
#define __INCifLibh


#ifdef __cplusplus
extern "C" {
#endif


extern void	    ifLibInit (void);
extern STATUS   ifAddrAdd (char *interfaceName, char *interfaceAddress,
                           char *broadcastAddress, int subnetMask);
extern STATUS   ifAddrDelete (char *interfaceName, char *interfaceAddress);
extern STATUS 	ifAddrSet (char *interfaceName, char *interfaceAddress);
extern STATUS 	ifAddrGet (char *interfaceName, char *interfaceAddress);
extern STATUS 	ifBroadcastSet (char *interfaceName, char *broadcastAddress);
extern STATUS 	ifBroadcastGet (char *interfaceName, char *broadcastAddress);
extern STATUS 	ifDstAddrSet (char *interfaceName, char *dstAddress);
extern STATUS 	ifDstAddrGet (char *interfaceName, char *dstAddress);
extern STATUS 	ifMaskSet (char *interfaceName, int netMask);
extern STATUS 	ifMaskGet (char *interfaceName, int *netMask);
extern STATUS 	ifFlagChange (char *interfaceName, int flags, BOOL on);
extern STATUS 	ifFlagSet (char *interfaceName, int flags);
extern STATUS 	ifFlagGet (char *interfaceName, int *flags);
extern STATUS 	ifMetricSet (char *interfaceName, int metric);
extern STATUS 	ifMetricGet (char *interfaceName, int *pMetric);

extern STATUS   ifProxyArpDisable (char *interfaceName);
extern STATUS   ifProxyArpEnable (char *interfaceName);

extern STATUS   ifAllRoutesDelete(char *ifName, int unit);

extern STATUS   ifIndexToIfName (unsigned short ifIndex, char * ifname);
extern unsigned short ifNameToIfIndex (char * ifname);

extern STATUS arpResolve ( char  *targetAddr, char  *pHwAddr, int   numTries, int   numTicks);

/*

Obsoleted API:

extern int 	ifRouteDelete (char *ifName, int unit);
extern struct 	ifnet *ifunit (const char *ifname);
extern STATUS	ifUnnumberedSet (char *, char *, char *, char *);
extern struct ifnet * ifIndexToIfp (int ifIndex);

 */


#ifdef __cplusplus
}
#endif

#endif /* __INCifLibh */
