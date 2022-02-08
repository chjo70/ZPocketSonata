/* semEvLib.h - semaphore user events library header file */

/* Copyright 2004, 2010 Wind River Systems, Inc. */

/*
modification history
--------------------
01b,29jul10,pad  Moved extern C statement after include statements.
01a,09mar04,hya  created
*/

#ifndef __INCsemEvLibh
#define __INCsemEvLibh

#include "vxWorks.h"
#include "semLib.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef	_ASMLANGUAGE

/* function declarations */

extern STATUS 	semEvStart (SEM_ID semId, UINT32 events, UINT8 options);
extern STATUS	semEvStop  (SEM_ID semId);

#endif	/* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCsemEvLibh */
