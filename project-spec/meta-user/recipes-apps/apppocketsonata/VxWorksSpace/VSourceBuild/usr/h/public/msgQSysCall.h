/* msgQSysCall.h - Wind message queue system call definitions */

/*
 * Copyright (c) 2003-2004, 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01f,12nov10,zl   added MSG_Q_ID_ERROR definition
01e,07may10,cww  Made numMsg type params size_t
01d,28apr10,pad  Moved extern C statement after include statements.
01c,10feb10,jpb  Updated for LP64 adaptation.
01b,22apr04,dcc  added 'context' parameter to _msgQOpen().
01a,27nov03,aeg  written
*/

#ifndef __INCmsgQSysCallh
#define __INCmsgQSysCallh

#include <vxWorks.h>

#ifdef __cplusplus
extern "C" {
#endif

/* return value for unsuccessful _msgQOpen() */

#define MSG_Q_ID_ERROR	((MSG_Q_ID) (-1))


/* system call function prototypes */

extern MSG_Q_ID	_msgQOpen (const char * name, size_t maxMsgs,
			   size_t maxMsgLength, int options, int mode,
			   void * context);

#ifdef __cplusplus
}
#endif

#endif /* __INCmsgQSysCallh */
