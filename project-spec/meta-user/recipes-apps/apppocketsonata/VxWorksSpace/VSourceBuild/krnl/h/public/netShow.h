/* netShow.h - header file for netShow.c */

/* Copyright 1984-2004, 2014 Wind River Systems, Inc. */

/*
modification history
--------------------
01p,09jan12,h_x  Move extern "C" after last header file include.
01o,08dec08,ggz  Added ifShow() wrapper 
01n,08sep06,kch  Cleanup for IPNet integration
01m,20sep04,spm  changed init routine prototypes to prevent build warnings;
                 removed obsolete __STDC__ support for old compilers
01l,19sep04,spm  updated virtual stack startup and shutdown for TCP and UDP
                 show routines: restored use of published initialization
                 routines and removed unused destructors
01k,23aug04,rp   merged from COMP_WN_IPV6_BASE6_ITER5_TO_UNIFIED_PRE_MERGE
01j,28may04,niq  Merging from base6 label POST_ITER5_FRZ16_REBASE (ver
                 /main/vdt/base6_itn5_networking-int/1)
01i,05nov03,cdw  Removal of unnecessary _KERNEL guards.
01h,04nov03,rlm  Ran batch header path update for header re-org.
01g,03nov03,rlm  Removed wrn/coreip/ prefix from #includes for header re-org.
01f,08sep03,vvv  merged from ACCORDION_BASE6_MERGE_BASELINE
01e,10jun03,vvv  include netVersion.h
01d,08apr03,ann  moved netBufShow prototypes to netBufLib.h and
                 moved some definitions from netShow.c to here. SPR# 86899
01c,18jan02,ppp  adding INET6 protection to a routine
01b,09jan02,ppp  adding support for ipv6
01a,08dec01,ppp  porting from A.E. 1.1
*/

#ifndef __INCnetShowh
#define __INCnetShowh


#ifdef __cplusplus
extern "C" {
#endif

/* externs */

/* function declarations */

extern void 	arpShow (void);
extern void 	hostShow (void);
extern void     hostShowInit (void);
extern void 	ifShow (char *ifName);

#ifdef __cplusplus
}
#endif

#endif /* __INCnetShowh */
