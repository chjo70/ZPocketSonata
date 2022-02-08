/* muxTkLib.h - definitions for muxTkLib.c */

/*
 * Copyright 1998-2001, 2003, 2005, 2008, 2010, 2014 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
05may14,rjq  Decouple COREIP with END. (V7NET-105)
10nov10,dlk  Move extern "C" after last header file include. WIND00240828.
03mar08,dlk  Update for MUX2.
25aug05,dlk  Add section tags.
16may05,dlk  Remove unsupported routine muxTkPktsReceive() unless
                 END_STYLE_MULTI_SUPPORT is defined.
24nov03,wap  Merge in changes from Snowflake
20nov03,niq  Remove copyright_wrs.h file inclusion
04nov03,rlm  Ran batch header path update for header re-org.
03nov03,rlm  Removed wrn/coreip/ prefix from #includes for header re-org.
22jul03,ann  changed 6th argument of muxTkBind to VOIDFUNCPTR.
01may03,spm  Tornado 2.2 CP1 merge (from version 01k,14nov02,wap:
                 TOR2_2-CP1-F label, tor2_2-patch branch, /wind/river VOB)
06feb03,vvv  merged from tor2_2-patch.alameda, ver01k (SPR #83032)
02may01,ann  made major changes for Clarinet based on MUX design doc
19apr00,ham  merged TOR2_0-NPT-FCS(01h,29apr99,pul).
29apr99,pul  Upgraded NPT phase3 code to tor2.0.0
30mar99,pul  removed all muxMCastMap and muxSvcFunc function declarations
24feb99,sj   added muxTkPollReceive
23feb99,sj   added spare data last argument for muxTkSend and muxTkPollSend
06nov98,sj   removed prototypes for muxTkReceive and nptHookRtn
27oct98,pul  changed nptHookRtn declaration to return STATUS.
09oct98,sj   fixed bad prototype for muxMCastMapFuncGet
07oct98,pul  written.
*/

/*
DESCRIPTION
This file includes function prototypes for the MUX.

INCLUDE FILES: muxLib.h
*/

#ifndef __INCmuxTkLibh
#define __INCmuxTkLibh

/* includes */
#include <muxLib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* defines */

/* typedefs */

/* locals */

/* globals */
IMPORT int muxMaxBinds;

/* forward declarations */

/* Toolkit functions */
IMPORT STATUS muxTkLibInit (void);
IMPORT int muxTkDrvCheck (char * pDevName);

IMPORT PROTO_COOKIE muxTkBind (char * pName, int unit,
			       FUNCPTR stackRcvRtn,
			       FUNCPTR stackShutdownRtn,
			       FUNCPTR stackTxRestartRtn,
			       VOIDFUNCPTR stackErrorRtn,
			       long type, char * pProtoName,
			       void * pNetCallbackId,
			       void * pNetSvcInfo, void * pNetDrvInfo);

IMPORT STATUS muxTkSend (PROTO_COOKIE cookie, M_BLK_ID pNBuff, char *,
                         USHORT, void *);
IMPORT STATUS muxTkPollSend (PROTO_COOKIE cookie, M_BLK_ID pNBuff, char *,
                             USHORT, void *);
IMPORT STATUS muxTkPollReceive (PROTO_COOKIE cookie, M_BLK_ID pNBuff,
				void *pSpare);

STATUS muxTkReceive (void * pEndCookie, M_BLK_ID pMblk, long netSvcOffset,
		     long netSvcType, BOOL uniPromiscuous, void * pSpareData);

IMPORT STATUS muxTkPollReceive2 (void *, M_BLK_ID  pNBuff);

IMPORT void * muxTkCookieGet (char *, int);

#ifdef END_STYLE_MULTI_SUPPORT
STATUS muxTkPktsReceive (void* pEndCookie, M_BLK_ID pMblk);
#endif

IMPORT void muxTkOverEndInit (void);

#ifdef __cplusplus
}
#endif

#endif /* __INCmuxTkLibh */

