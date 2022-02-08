/* msgQEvLib.h - message queue events library header file */

/* Copyright 2001, 2010 Wind River Systems, Inc. */

/*
modification history
--------------------
01b,29apr10,pad  Moved extern C statement after include statements.
01a,20sep01,bwa  Written.
*/

#ifndef __INCmsgQEvLibh
#define __INCmsgQEvLibh

#include "vxWorks.h"
#include "msgQLib.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef	_ASMLANGUAGE

/* function declarations */

#if defined(__STDC__) || defined(__cplusplus)

extern STATUS	msgQEvStart (MSG_Q_ID msgQId, UINT32 events, UINT8 options);
extern STATUS	msgQEvStop  (MSG_Q_ID msgQId);

#else /* __STDC__ */

extern STATUS	msgQEvStart ();
extern STATUS	msgQEvStop  ();

#endif /* __STDC__ */

#endif	/* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCmsgQEvLibh */
