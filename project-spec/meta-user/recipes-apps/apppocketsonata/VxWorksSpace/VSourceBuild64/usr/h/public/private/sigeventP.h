/* sigevent.h - private sigevent header file */

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
01b,29jul10,pad  Moved extern C statement after include statements.
01a,02oct03,gls  written
*/

#ifndef __INCsigeventPh
#define __INCsigeventPh

#include <sigevent.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct sigevent * SIGEVENT_ID;

extern SIGEVENT_ID sigeventCreate (struct sigevent * sigevId);
extern int sigeventDelete (struct sigevent * sigevId);

#ifdef __cplusplus
}
#endif

#endif /* __INCsigeventPh */
