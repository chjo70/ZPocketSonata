/* wvLib - VxWorks user WindView library interface header */

/* Copyright (c) 2004, 2010 Wind River Systems, Inc. */

/*
modification history
--------------------
01b,29jul10,pad  Moved extern C statement after include statements.
01a,23feb04,tcr  created
*/

#ifndef __INCwvLib_h
#define __INCwvLib_h

#include "vxWorks.h"		/* common definitions for all VxWorks libs */

#ifdef __cplusplus
extern "C" {
#endif

/* function declarations */

extern STATUS   wvEvent (int eventId, const char * pData, unsigned int dataSize);

#ifdef __cplusplus
}
#endif

#endif /* __INCwvLib_h */
