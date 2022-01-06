/* ping6Lib.h - Packet InterNet Grouper (PING) library header */

/*
 * Copyright (c) 2001-2003,2005-2006  Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01i,27jul06,kch  Removed unsupported ping6LibInit() and ping6Parse()
                 prototypes.
01h,23feb05,dlk  Added ping6Parse() function prototype.
01g,20nov03,niq  Remove copyright_wrs.h file inclusion
01f,05nov03,cdw  Removal of unnecessary _KERNEL guards.
01e,04nov03,rlm  Ran batch header path update for header re-org.
01d,03nov03,rlm  Removed wrn/coreip/ prefix from #includes for header re-org.
01c,10jun03,vvv  include netVersion.h
01b,01mar02,ant  added ping6LibInit
01a,14sep01,ant  written

*/

#ifndef __INCping6Libh
#define __INCping6Libh

#ifdef __cplusplus
extern "C" {
#endif

/* function declarations */

extern STATUS 	ping6 (char *, int);

#ifdef __cplusplus
}
#endif

#endif /* __INCping6Libh */
