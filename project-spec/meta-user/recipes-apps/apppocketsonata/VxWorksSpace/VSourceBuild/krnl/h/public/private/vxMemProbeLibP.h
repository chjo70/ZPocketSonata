/* vxMemProbeLibP.h - vxMemProbe architecture  header file */

/*
 * Copyright (c) 2006, 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
*/

/*
modification history
--------------------
01b,17mar10,zl   removed vxMemCommonProbe()
01a,14sep06,slk  created
*/

#ifndef __INCvxMemProbeLibPh
#define __INCvxMemProbeLibPh

#ifdef __cplusplus
extern "C" {
#endif

/* function declarations */

extern STATUS   vxMemArchProbe (void * adrs, int mode, int length, void * pVal);
extern STATUS   vxMemArchProbeInit (void);
extern STATUS   vxMemProbeSup (int, char *src, char *dest);

#ifdef __cplusplus
}
#endif

#endif /* __INCvxMemProbeLibPh */

