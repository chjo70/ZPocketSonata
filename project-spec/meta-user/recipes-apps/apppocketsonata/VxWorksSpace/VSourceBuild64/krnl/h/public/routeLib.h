/* routeLib.h - header file for the network routing library */

/* Copyright 1987-2004 Wind River Systems, Inc. */

/*
modification history
--------------------
02n,21jun10,h_x  Fix WIND00217113
02m,23aug04,rp   merged from COMP_WN_IPV6_BASE6_ITER5_TO_UNIFIED_PRE_MERGE
02l,28may04,niq  Merging from base6 label POST_ITER5_FRZ16_REBASE (ver
                 /main/vdt/base6_itn5_networking-int/1)
02k,20nov03,niq  Remove copyright_wrs.h file inclusion
02j,05nov03,cdw  Removal of unnecessary _KERNEL guards.
02i,04nov03,rlm  Ran batch header path update for header re-org.
02h,03nov03,rlm  Removed wrn/coreip/ prefix from #includes for header re-org.
02g,19dec01,hgo  modification of header files
02f,26jun98,spm  added mRouteEntryDelete prototype
02e,10jul97,rjc  added flag param to mRouteDelete.
02d,11apr97,rjc  changed interface of m2RouteEntryAdd
i02c,14feb97,rjc added mask versions of route add etc
02d,11jul94,dzb  added prototype for routeNetAdd() (SPR #3395).
02c,22sep92,rrr  added support for c++
02b,27jul92,elh  moved routeShow to netShow.
02a,04jul92,jcf  cleaned up.
01g,26may92,rrr  the tree shuffle
01f,02mar92,elh  added routeCmd.
01e,04oct91,rrr  passed through the ansification filter
		  -changed VOID to void
		  -changed copyright notice
01d,05oct90,shl  added ANSI function prototypes.
                 added copyright notice.
01c,07aug90,shl  added IMPORT type to function declarations.
01b,16nov87,llk  documentation
01a,01nov87,llk  written
*/

#ifndef __INCrouteLibh
#define __INCrouteLibh

#ifdef __cplusplus
extern "C" {
#endif

#include <vwModNum.h>
#include <ipcom_type.h>
/* status codes */

#define S_routeLib_ILLEGAL_INTERNET_ADDRESS		(M_routeLib | 1)
#define S_routeLib_ILLEGAL_NETWORK_NUMBER		(M_routeLib | 2)

/* function declarations */

extern STATUS 	routeAdd (char *destination, char *gateway);
extern STATUS 	routeDelete (char *destination, char *gateway);
extern STATUS 	routeNetAdd (char *destination, char *gateway);
extern STATUS 	routeCmd (int destInetAddr, int gateInetAddr, int ioctlCmd);
extern STATUS   mRouteAdd (char *, char *, Ip_u32, int, int);
extern STATUS   mRouteEntryAdd (Ip_u32 , Ip_u32, Ip_u32, int, int, int);
extern STATUS   mRouteEntryDelete (Ip_u32 , Ip_u32, Ip_u32, int, int, int);
extern STATUS   mRouteDelete (char *, Ip_u32, int, int);
extern void     oldRouteLibInit(void);

#ifdef __cplusplus
}
#endif

#endif /* __INCrouteLibh */
