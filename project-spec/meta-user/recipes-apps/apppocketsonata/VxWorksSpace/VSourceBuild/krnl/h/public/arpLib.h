/* arpLib.h - VxWorks ARP table manipulation header file */

/*
 * Copyright (c) 2006 Wind River Systems, Inc.
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
01n,09jan12,h_x  Move extern "C" after last header file include.
01m,30aug05,tkf  Cleanup for integration with IPNET.
01l,09feb05,sar  Move gtf include files per GTF code inspection of 10/26/2004
01k,07feb05,vvv  _KERNEL cleanup
01j,28may04,niq  Merging from base6 label POST_ITER5_FRZ16_REBASE (ver
                 /main/vdt/base6_itn5_networking-int/1)
01i,20nov03,niq  Remove copyright_wrs.h file inclusion
01h,05nov03,cdw  Removal of unnecessary _KERNEL guards.
01g,04nov03,rlm  Ran batch header path update for header re-org.
01f,03nov03,rlm  Removed wrn/coreip/ prefix from #includes for header re-org.
01e,23oct03,rlm  updated #includes for header re-org
01d,08sep03,vvv  merged from ACCORDION_BASE6_MERGE_BASELINE
01c,09may03,vvv  included vwModNum.h and in.h
01b,07feb02,ppp  re-enabling arpLibInit
01a,14dec01,ppp  ported from A.E. 1.1
*/

#ifndef __INCarpLibh
#define __INCarpLibh

#include <vwModNum.h>

#ifdef __cplusplus
extern "C" {
#endif

#if defined(__STDC__) || defined(__cplusplus)
extern STATUS 	arpAdd (char *host, char *eaddr, int flags);
extern STATUS 	arpDelete (char *host);
extern STATUS   arpResolve(char *targetAddr, char *pHwAddr, int numTries,int numTicks);
extern void     arpFlush (void);
#else	/* __STDC__ */
extern STATUS 	arpAdd ();
extern STATUS 	arpDelete ();
extern STATUS   arpResolve();
extern void     arpFlush();
#endif	/* __STDC__ */

/* error values */

#define S_arpLib_INVALID_ARGUMENT		(M_arpLib | 1)
#define S_arpLib_INVALID_HOST 			(M_arpLib | 2)
#define S_arpLib_INVALID_ENET_ADDRESS 		(M_arpLib | 3)
#define S_arpLib_INVALID_FLAG			(M_arpLib | 4)

#ifdef __cplusplus
}
#endif

#endif /* __INCarpLibh */
