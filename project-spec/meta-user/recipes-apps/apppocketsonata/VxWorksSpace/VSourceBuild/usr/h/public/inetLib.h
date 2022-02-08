/* inetLib.h - header for Internet address manipulation routines */

/* 
 * Copyright (c) 1987-2006 Wind River Systems, Inc. 
 * 
 * The right to copy, distribute, modify or otherwise make use 
 * of this software may be licensed only pursuant to the terms 
 * of an applicable Wind River license agreement. 
 */

/*
modification history
--------------------
02a,17aug12,h_x  Fix WIND00370053
01z,09jan12,h_x  Move extern "C" after last header file include.
01y,08nov06,kch  Removed prototypes already declared in arpa/inet.h.
01x,07feb05,vvv  _KERNEL cleanup
01w,23aug04,rp   merged from COMP_WN_IPV6_BASE6_ITER5_TO_UNIFIED_PRE_MERGE
01v,28may04,niq  Merging from base6 label POST_ITER5_FRZ16_REBASE (ver
                 /main/vdt/base6_itn5_networking-int/1)
01u,25nov03,ppp  added a comment based on code review
01t,21nov03,ppp  rtp work
01s,20nov03,niq  Remove copyright_wrs.h file inclusion
01r,05nov03,cdw  Removal of unnecessary _KERNEL guards.
01q,04nov03,rlm  Ran batch header path update for header re-org.
01p,03nov03,rlm  Removed wrn/coreip/ prefix from #includes for header re-org.
01o,23oct03,rlm  updated #includes for header re-org
01n,21apr03,ppp  vwModNum.h should be picked up from target/h
01m,14sep01,hgo  Added definition for inet_ntop and inet_pton
                 IPv6 support
01l,16dec93,jag  Added definition for inet_aton.
01k,09aug93,elh  removed definitions of inet_addr, inet_ntoa, 
		 inet_makeaddr, and inet_network (SPR 2268). 
01j,22sep92,rrr  added support for c++
01i,04jul92,jcf  cleaned up.
01h,26may92,rrr  the tree shuffle
		  -changed includes to have absolute path from h/
01g,04oct91,rrr  passed through the ansification filter
		  -changed includes to have absolute path from h/
		  -changed VOID to void
		  -changed copyright notice
01f,19oct90,shl  added #include <netinet/in.h>.
01e,05oct90,shl  added ANSI function prototypes.
                 made #endif ANSI style.
                 added copyright notice.
01d,10aug90,dnw  added declaration of inet_ntoa_b().
01c,24mar88,ecs  added include of types.h.
01b,15dec87,gae  added INET_ADDR_LEN; used IMPORTs on function decl's.
01a,01nov87,llk  written
*/

#ifndef __INCinetLibh
#define __INCinetLibh

#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <vwModNum.h>

#ifdef __cplusplus
extern "C" {
#endif

/* status codes */

#define S_inetLib_ILLEGAL_INTERNET_ADDRESS		(M_inetLib | 1)
#define S_inetLib_ILLEGAL_NETWORK_NUMBER		(M_inetLib | 2)

/* length of ASCII represention of inet addresses, eg. "90.0.0.0" */

#define	INET_ADDR_LEN	18
#define INET6_ADDR_LEN  46

#define INETLIB         5 /* first available node */

/* function declarations */


#if defined(__STDC__) || defined(__cplusplus)

extern int inet_lnaof (int inetAddress);
extern int inet_netof (struct in_addr inetAddress);
extern unsigned long inet_network (char *);
extern struct in_addr inet_makeaddr (int, int);
extern void inet_makeaddr_b (int netAddr, int hostAddr, 
                             struct in_addr *pInetAddr);
extern void inet_ntoa_b (struct in_addr inetAddress, char *pString);
extern int inet_aton (const char * pString, struct in_addr * inetAddress);
extern void inet_netof_string(char *inetString, char *netString);

#else	/* __STDC__ */

extern int inet_lnaof ();
extern int inet_netof ();
extern unsigned long 	inet_network ();
struct in_addr inet_makeaddr();
extern void inet_makeaddr_b ();
extern void inet_ntoa_b ();
extern int inet_aton ();
extern void inet_netof_string();

#endif	/* __STDC__ */

#ifdef __cplusplus
}
#endif

#endif /* __INCinetLibh */
