/* m2IfLib.h - VxWorks MIB-II interface to SNMP Agent */

/* Copyright 1984 - 2005, 2010 Wind River Systems, Inc. */

/*
modification history
--------------------
02m,29apr10,pad  Moved extern C statement after include statements.
02l,07feb05,vvv  _KERNEL cleanup
02k,20nov03,niq  Remove copyright_wrs.h file inclusion
02j,04nov03,rlm  Ran batch header path update for header re-org.
02i,03nov03,rlm  Removed wrn/coreip/ prefix from #includes for header re-org.
02h,24oct03,cdw  update include statements post header re-org.
02g,30jul03,vvv  backed out previous change
02f,24jul03,vvv  modified include for endLib.h
02e,01may03,spm  Tornado 2.2 CP1 merge (from ver 01h,27jan03,vvv:
                 TOR2_2-CP1-F label, tor2_2-patch branch, /wind/river VOB)
02d,21may02,ann  changed the include of end.h to endLib.h
02c,28mar02,ppp  modifying it as part of the cleanup for installation script
02b,03feb02,ham  renamed dummyend.h to end.h
02a,12sep01,ann  ported to clarinet
01a,29mar01,spm  file creation: copied from version 01b of tor2_0.open_stack
                 branch (wpwr VOB) for unified code base
*/

#ifndef __INCm2IfLibh
#define __INCm2IfLibh

#include <m2Lib.h>
#include <endLib.h>

#ifdef __cplusplus
extern "C" {
#endif

extern STATUS m2PollStatsIfPoll (END_IFDRVCONF *);
extern STATUS m2IfUsrCountersInstall (M2_ID *, void *);
extern STATUS m2IfUsrCountersRemove (M2_ID *);

#ifdef __cplusplus
}
#endif

#endif /* __INCm2Libh */
