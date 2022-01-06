/* if6Lib.h - IPv6 interface address library header */

/* Copyright 2003 - 2005, 2014 Wind River Systems, Inc. */

/*
modification history
--------------------
01j,21jun10,h_x  Fix WIND00217113
01i,27Nov07,brg  Reinstated after ipnet integration
01h,07feb05,vvv  _KERNEL cleanup
01g,19jan05,vvv  removed include of clarinet.h
01f,04nov03,rlm  Ran batch header path update for header re-org.
01e,03nov03,rlm  Removed wrn/coreip/ prefix from #includes for header re-org.
01d,10jun03,vvv  include netVersion.h
01c,09may03,vvv  included clarinet.h
01b,06may03,ijm  changed if6AddrDel to if6AddrDelete
01a,01mar03,pas  wrote
*/

#ifndef __INCif6Libh
#define __INCif6Libh

#ifdef __cplusplus
extern "C" {
#endif

#include <ipcom_type.h>

/* function declarations */

#if defined(__STDC__) || defined(__cplusplus)
extern void if6LibInit(void);
extern STATUS if6AddrGet(char *interfaceName, char *interfaceAddress);
extern STATUS if6AddrAdd(char *interfaceName, char *interfaceAddress,
			 int prefixLen, int flags);
extern STATUS if6AddrDelete(char *interfaceName, char *interfaceAddress);
extern STATUS if6DstAddrGet(char *interfaceName, char *interfaceAddress,
			    char *dstAddress);
extern STATUS if6DstAddrSet(char *interfaceName, char *interfaceAddress,
			    char *dstAddress);
extern STATUS if6PrefixlenGet(char *interfaceName, char *interfaceAddress,
			      int *prefixLen);
extern STATUS if6PrefixlenSet(char *interfaceName, char *interfaceAddress,
			      int prefixLen);
extern STATUS if6FlagGet(char *interfaceName, char *interfaceAddress,
			 int *flags);
extern STATUS if6FlagSet(char *interfaceName, char *interfaceAddress,
			 int flags);
extern STATUS if6FlagChange(char *interfaceName, char *interfaceAddress,
			    int flags, BOOL on);
extern STATUS if6LifetimeGet(char *interfaceName, char *interfaceAddress,
			     Ip_time_t *vltime, Ip_time_t *pltime);
extern STATUS if6LifetimeSet(char *interfaceName, char *interfaceAddress,
			     Ip_time_t vltime, Ip_time_t pltime);
#else	/* __STDC__ */
extern void if6LibInit();
extern STATUS if6AddrGet();
extern STATUS if6AddrAdd();
extern STATUS if6AddrDelete();
extern STATUS if6DstAddrGet();
extern STATUS if6DstAddrSet();
extern STATUS if6PrefixlenGet();
extern STATUS if6PrefixlenSet();
extern STATUS if6FlagGet();
extern STATUS if6FlagSet();
extern STATUS if6FlagChange();
extern STATUS if6LifetimeGet();
extern STATUS if6LifetimeSet();
#endif	/* __STDC__ */

#ifdef __cplusplus
}
#endif

#endif /* __INCif6Libh */
