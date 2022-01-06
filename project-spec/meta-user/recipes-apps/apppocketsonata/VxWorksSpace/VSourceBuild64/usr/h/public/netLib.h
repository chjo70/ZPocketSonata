/* netLib.h - header file for the tNetTask */

/* 
 * Copyright 2001-2003, 2005-2007, 2010, 2013, 2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */


/*
modification history
--------------------
11may15,zan  Configuration of affinity and priority for networking task.
17nov13,dlk  Adding netDaemonsSuspend() / netDaemonsResume() /
                 netDaemonsExclusive() and netTaskDaemonIndex().
10nov10,dlk  Move extern "C" after last header file include. WIND00240828.
12oct07,dlk  Changed netDaemonQ() to take an signed int argument;
                 add the inverse function netDaemonQnum().
09jun07,dlk  Make netDaemonQ() public. Add netDaemonsCount().
                 netLibInitialize() takes additional netTaskFunc() argument.
06mar07,dlk  Remove references to netJobInfo.
09sep06,kch  Added string.h include.
20jun06,jpb  Removed I960 check.
25aug05,dlk  Added section tags.
08jul05,dlk  Implement netJobAdd() using jobQueueLib.
25nov03,wap  Merge in changes for Snowflake
20nov03,niq  Remove copyright_wrs.h file inclusion
05nov03,cdw  Removal of unnecessary _KERNEL guards.
04nov03,rlm  Ran batch header path update for header re-org.
03nov03,rlm  Removed wrn/coreip/ prefix from #includes for header re-org.
15aug03,nee  Merging from ACCORDION_BASE6_MERGE_BASELINE
10jun03,vvv  include netVersion.h
13may03,vvv  deleted TCP_MSL_CFG to avoid duplicate definitions
01may03,spm  Tornado 2.2 CP1 merge (from ver 01p,22jan03,wap:
                 TOR2_2-CP1-F label, tor2_2-patch branch, /wind/river VOB)
30dec02,ann  changing the value of IP_PROTO_NUM_MAX to 16
26feb02,ham  renamed to netLib.h
23aug01,ann  correcting the references to netlibh after the rename
15aug01,ann  ported to clarinet from AE1.1 version 01o.
*/

#ifndef __INCnetLibh
#define __INCnetLibh

#include <string.h>    

#include <jobQueueLib.h>

#ifdef __cplusplus
extern "C" {
#endif

#define NET_TASK_QJOB_PRI	16

/* For convenience only. Using &netJobInfo avoids a dereference. */

extern JOB_QUEUE_ID netJobQueueId;

extern void * netGtfTickInformation; /* read only */

/* function declarations */

extern STATUS   netJobAdd (FUNCPTR routine,
			   _Vx_usr_arg_t param1,
			   _Vx_usr_arg_t param2,
			   _Vx_usr_arg_t param3,
                           _Vx_usr_arg_t param4,
			   _Vx_usr_arg_t param5);

extern STATUS   netLibInitialize (unsigned int numDaemons, BOOL affinityLock,
			  int (*netTaskFunc) (JOB_QUEUE_ID qId, int qIndex),
			  unsigned int priorities_configured[],
			  unsigned int affinities_configured[]);
extern unsigned int netDaemonsCount (void);
extern JOB_QUEUE_ID netDaemonQ (int i);
extern int netDaemonQnum (JOB_QUEUE_ID qId);

extern void     netErrnoSet (int status);
extern void     mbinit (void * pNetPoolCfg);
extern STATUS	netJobAlloc (u_int numJobs);
_WRS_FASTTEXT
extern void	netGtfTickFunc (void * pTm, void * arg);

extern void netDaemonsSuspend (void);
extern void netDaemonsResume (void);
extern BOOL netDaemonsExclusive (void);
extern int  netTaskDaemonIndex (TASK_ID tid);


/* backwards compatibility */
#define netJobAdd(f, a1, a2, a3, a4, a5) \
    (jobQueueStdPost (netJobQueueId, NET_TASK_QJOB_PRI,		    \
		      (VOIDFUNCPTR)(f), (void *)(a1), (void *)(a2), \
		      (void *)(a3), (void *)(a4), (void *)(a5)))

#ifdef __cplusplus
}
#endif

#endif /* __INCnetLibh */

