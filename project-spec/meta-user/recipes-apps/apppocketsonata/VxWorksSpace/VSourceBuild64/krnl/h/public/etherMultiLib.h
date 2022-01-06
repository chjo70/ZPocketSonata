/* etherMultiLib.h - definitions for the Ethernet multicast library */

/*
 * Copyright (c) 1996-2006 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */


/*
modification history
--------------------
02j,09jan12,h_x  Move extern "C" after last header file include.
02i,21aug06,kch  cleaned up header files.
02h,20nov03,niq  Remove copyright_wrs.h file inclusion
02g,04nov03,rlm  Ran batch header path update for header re-org.
02f,03nov03,rlm  Removed wrn/coreip/ prefix from #includes for header re-org.
02e,23oct03,rlm  updated #includes for header re-org
02d,28mar02,ppp  Making changes to be compatible with AE 1.1
02c,03mar02,ham  renamed dummyend.h to end.h
02b,18sep01,ann  correcting the inclusion of if_ether.h
02a,18sep01,ann ported to clarinet from 01d AE1.1
01d,12aug97,gnn cleaned up dependencies for multicast handling.
01c,23oct96,gnn name changes to follow coding standards.
01b,07may96,gnn added routines to handle non-IP based multicast
		addresses.
		Added list handling library.
01a,15apr96,gnn	written.

*/

/*
DESCRIPTION

This header file describes data structures and function prototypes for
the ethernet multicast library.

INCLUDE FILES:
*/

#ifndef __INCetherMultiLibh
#define __INCetherMultiLibh

/* includes */
#include <end.h>
#include <netinet/if_ether.h>

#ifdef __cplusplus
extern "C" {
#endif

/* defints */

/* typedefs */

/* globals */

/* locals */

/* forward declarations */

#if defined(__STDC__) || defined(__cplusplus)

extern int etherMultiAdd(LIST *pList, char* pAddress );
extern int etherMultiDel(LIST* pList, char* pAddress);
extern int etherMultiGet(LIST *pList, MULTI_TABLE* pTable);
#else	/* __STDC__ */

extern int etherMultiAdd();
extern int etherMultiDel();
extern int etherMultiGet();
#endif /* __STDC__ */

#ifdef __cplusplus
}
#endif

#endif /* __INCetherMultiLibh */
