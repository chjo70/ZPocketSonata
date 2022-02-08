/* sysctlLib.h - Header file for the sysctl library */

/*
 * Copyright (c) 2001-2007 Wind River Systems, Inc.
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
01x,09jan12,h_x  Move extern "C" after last header file include.
01w,22jan07,tkf  Add mbufSysctlInit() prototype (WIND00085249). Also
                 changed copyright notice.
01v,09dec06,tkf  Cleanup for IPNET integration.
01u,02mar06,dlk  Remove reference to ipFlowSysctlInit() (SPR #104107).
01t,20jul05,vvv  added sctpSysctlInit() and sctp6SysctlInit() prototypes
01s,20may05,kch  Added mip6ProtoSysctlInit() and ip6MrouteSysctlInit()
                 prototypes.
01r,29apr05,kch  Added mldSysctlInit().
01q,21apr05,kch  Removed in6RmxSysctlInit() prototype.
01p,07feb05,wap  Allow sysctl init routines to be scaled out
01o,24jan05,vvv  osdep.h cleanup
01n,20jan05,sar  Removal of divert, dummynet and fw code.
01m,17sep04,niq  Fix a typo
01l,23aug04,rp   merged from COMP_WN_IPV6_BASE6_ITER5_TO_UNIFIED_PRE_MERGE
01k,28may04,niq  Merging from base6 label POST_ITER5_FRZ16_REBASE (ver
                 /main/vdt/base6_itn5-int/1)
01j,20nov03,niq  Remove copyright_wrs.h file inclusion
01i,04nov03,rlm  Ran batch header path update for header re-org.
01h,03nov03,rlm  Removed wrn/coreip/ prefix from #includes for header re-org.
01g,24oct03,cdw  update include statements post header re-org.
01f,08sep03,vvv  merged from ACCORDION_BASE6_MERGE_BASELINE
01e,17jul02,ppp  adding an extern to the defination for sysctlLibInit
01d,03feb02,ham  changes for tornado build.
01c,12dec01,ann  Adding the changes from testing
01b,03dec01,niq  Add prototypes for sysctlInit routines
01a,22oct01,ann  written
*/

#ifndef __INCsysctllibh
#define __INCsysctllibh

#define INCLUDE_SYSCTL

#ifdef INCLUDE_SYSCTL

#include <sys/sysctl.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Extern */

/* Prototypes */

STATUS sysctlInit (void);
IMPORT STATUS sysctlLibInit (void);
IMPORT STATUS mbufSysctlInit (void);

#ifdef _WRS_KERNEL
void   sysctl_sysctl_debug_dump_node (struct sysctl_oid_list *, int);
#endif

#ifdef __cplusplus
}
#endif

#endif    /* #ifdef SYSCTL */

#endif /* __INCsysctllibh */

