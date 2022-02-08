/* l2config.h - header file for l2config utility */

/*
 * Copyright (c) 2005 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01b,26aug05,kch  Added l2configInit() prototype.
01a,12aug05,kch  written.
*/

#ifndef __INCl2configh
#define __INCl2configh

#ifdef __cplusplus
extern "C" {
#endif

IMPORT STATUS l2configInit (void);
IMPORT int l2config (char *);

#ifdef __cplusplus
}
#endif

#endif /* ! __INCl2configh */
