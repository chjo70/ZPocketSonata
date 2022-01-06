/* rtpVarLib.h - header for RTP variables */

/* Copyright 2004, 2010 Wind River Systems, Inc. */

/*
modification history
--------------------
01b,29jul10,pad  Moved extern C statement after include statements.
01a,02mar04,kk  written
*/

#ifndef __INCrtpVarLibh
#define __INCrtpVarLibh

#include "rtpLib.h"
#include "rtpVarLibCommon.h"

#ifdef __cplusplus
extern "C" {
#endif

/* function declarations */

extern STATUS 	rtpVarAdd (RTP_VAR_ADDR pVar, RTP_VAR value);

#ifdef __cplusplus
}
#endif

#endif /* __INCrtpVarLibh */
