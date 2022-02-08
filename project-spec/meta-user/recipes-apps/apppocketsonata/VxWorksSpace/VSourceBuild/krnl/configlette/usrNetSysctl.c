/* usrNetSysctl.c - Network default configuration */

/*
 * Copyright (c) 1992-2007, 2013, 2016 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement. No license to Wind River intellectual property rights
 * is granted herein. All rights not licensed by Wind River are reserved
 * by Wind River.
 */

/*
modification history
--------------------
29jun16,jxy  fix incompatible pointer type. (V7NET-874)
09oct13,h_k  added sysctlP.h inclusion for _netSysctl and _netSysctlCli
                 prototypes.
13feb07,dlk  Remove 'foreign' argument to netCoreSysctlInit().
26dec06,kch  Added hostnameSysctlSetup().
06dec06,tkf  Cleanup for IPNET integration.
13apr05,kch  Corrected virtualization problem.
16sep04,vvv  fixed warning
31aug04,vvv  fixed sysctl initialization
06sep02,kal  should be VS Non opt component, not application
05sep02,kal  fixed prototypes for vsLib
20aug02,hgo  virtualization
05feb02,ham  wrote.
*/

/*
DESCRIPTION

This configlette contains the initialization routine for the INCLUDE_NET_SYSCTL
component.

NOMANUAL
*/

/* includes */
#include <sys/sysctl.h>

#if defined(INCLUDE_IPNET) || defined(INCLUDE_SYSCTL_CLI)
#include <private/sysctlP.h>
#endif /* INCLUDE_IPNET || INCLUDE_SYSCTL_CLI */

IMPORT STATUS netCoreSysctlInit (void);
IMPORT STATUS netSysctlInit (BOOL);

#ifdef	INCLUDE_IPNET
IMPORT STATUS netSysctl (struct sysctl_oid * pOid, void * pArg1, int arg2,
			 struct sysctl_req * pReq);
# ifdef INCLUDE_SYSCTL_CLI
IMPORT int netSysctlCli (int argc, char ** pArgv, int nextLevelOid, char *  pOpts);
# endif /* INCLUDE_SYSCTL_CLI */
#endif	/* INCLUDE_IPNET */

#ifdef INCLUDE_NET_HOST_SETUP
IMPORT void hostnameSysctlSetup (void);
#endif /* INCLUDE_NET_HOST_SETUP */


void usrNetSysctlInit (void)
{
#ifdef INCLUDE_IPNET
    _netSysctl = netSysctl;

#ifdef INCLUDE_SYSCTL_CLI
    _netSysctlCli = netSysctlCli;
#endif
#endif

    netCoreSysctlInit ();

#ifdef  INCLUDE_NET_HOST_SETUP
    hostnameSysctlSetup();
#endif /* INCLUDE_NET_HOST_SETUP */
}
