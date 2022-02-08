/* tlsLib.h - generic Thread Local Storage interface header */

/*
 * Copyright (c) 2006-2007, 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01c,28apr10,pad  Moved extern C statement after include statements.
01b,25apr07,gls  ported to user side
01a,19oct06,dbt  Written
*/

/*
 * Note: This file contains definitions that must be maintained in both kernel
 * and user space
 */

#ifndef __INCtlsLibh
#define __INCtlsLibh

#ifndef _WRS_KERNEL

/* included until library removal */

#include <tlsOldLib.h>

#endif

#ifdef __cplusplus
extern "C" {
#endif

/* function declarations */

#ifdef _WRS_KERNEL
extern STATUS	tlsTaskInit		(void);
#endif

#ifdef __cplusplus
}
#endif

#endif /* __INCtlsLibh */
