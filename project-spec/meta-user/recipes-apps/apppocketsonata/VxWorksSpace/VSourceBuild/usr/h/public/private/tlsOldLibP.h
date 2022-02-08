/* tlsOldLib.h - task local storage header file */

/*
 * Copyright (c) 2003-2005 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement. 
 */

/*
modification history
--------------------
01d,13sep10,jpb  Renamed header macros
01c,03jun05,kk   fix syntax error (SPR# 109861)
01b,24sep03,aeg  written
*/

#ifndef __INCtlsOldLibPh
#define __INCtlsOldLibPh

#ifdef __cplusplus
extern "C" {
#endif

/* function declarations */

extern STATUS	tlsCurrentOfTaskRegister   (int tid, char *pTls);
extern STATUS	tlsCurrentOfTaskUnregister (int tid);

#ifdef __cplusplus
}
#endif

#endif /* __INCtlsOldLibPh */
