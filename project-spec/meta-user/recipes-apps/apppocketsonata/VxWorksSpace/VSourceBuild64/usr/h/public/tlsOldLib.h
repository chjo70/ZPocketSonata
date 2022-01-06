/* tlsOldLib.h - task local storage header file - To be deprecated */

/*
 * Copyright (c) 2003-2004, 2007, 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement. 
 */

/*
modification history
--------------------
01h,29jul10,pad  Moved extern C statement after include statements.
01g,25apr07,gls  readied for deprecation
01f,21oct04,kk   fixed warning
01e,18may04,kk   added errno values for TLS
01d,08dec03,kk   made TLS_KEY type int
01c,29sep03,kk   fixed TLS macro to check for rtpTlsCurrent pointer
01b,24sep03,aeg  moved tlsCurrentOfTaskRegister() to h/private/tlsLibP.h
01a,19sep03,kk   written
*/

/*
 * WARNING:  
 *
 * This library is to be deprecated and will be removed in a future release.
 *
 * Also note that the rtpTlsCurrent task variable has been removed.
 */

#ifndef __INCtlsOldLibh
#define __INCtlsOldLibh

#include <vxWorks.h>
#include <errno.h>

#ifdef __cplusplus
extern "C" {
#endif

/* defines */

#define S_tlsLib_INVALID_KEY	(M_tlsLib | 1)
#define S_tlsLib_MAX_KEYS	(M_tlsLib | 2)
#define S_tlsLib_NO_TLS		(M_tlsLib | 3)

typedef int	TLS_KEY;	

/* variable declarations */

extern UINT    maxTlsNumSlots;

/* function declarations */

extern int 	tlsSizeGet        (void);
extern TLS_KEY  tlsKeyCreate      (void);
extern STATUS   tlsValueOfTaskSet (int tid, TLS_KEY key, void * value);
extern STATUS   tlsValueOfTaskGet (int tid, TLS_KEY key, void ** value);
extern void *   tlsValueGet       (TLS_KEY key);
extern STATUS   tlsValueSet       (TLS_KEY key, void * value);

/* macro routines */

/*******************************************************************************
*
* TLS_VALUE_GET - Get the TLS value associated with the specified TLS key
*
* This macro has been deprecated.
*
* This routine takes a TLS key and returns the value associated with this
* key in the TLS array of the current task.
*
* RETURNS: value or NULL
*
* NOMANUAL
*/

#define TLS_VALUE_GET tlsValueGet

/*******************************************************************************
*
* TLS_VALUE_SET - Set value in the specified TLS key slot
*
* This macro has been deprecated.
*
* This routine takes a TLS key and a value and stores the value 
* in the TLS key slot of the current task's TLS array.
*
* RETURNS: OK or ERROR
*
* NOMANUAL
*/

#define TLS_VALUE_SET tlsValueSet

#ifdef __cplusplus
}
#endif

#endif /* _INCtlsOldLibh */
