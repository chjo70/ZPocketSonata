/* msgQEvLib.h - message queue user events library header file */

/* Copyright 2004, 2010 Wind River Systems, Inc. */

/*
modification history
--------------------
01b,29jul10,pad  Moved extern C statement after include statements.
01a,09mar04,hya  created
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

extern STATUS	msgQEvStart (MSG_Q_ID msgQId, UINT32 events, UINT8 options);
extern STATUS	msgQEvStop  (MSG_Q_ID msgQId);

#endif	/* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCmsgQEvLibh */
