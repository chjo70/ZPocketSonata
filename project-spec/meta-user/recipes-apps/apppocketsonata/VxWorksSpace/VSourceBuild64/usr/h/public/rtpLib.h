/* rtpLib.h - VxWorks user Real Time Process interface header file */

/* Copyright 2003, 2010 Wind River Systems, Inc. */

/*
modification history
--------------------
01d,29jul10,pad  Moved extern C statement after include statements.
01c,13sep04,yvp Added alias for rtpExit.
01b,22sep03,kk  move rtpSpawn to rtpLibCommon.h
01a,15sep03,kk  created based on rtpLib.h
*/

#ifndef __INCrtpLibh
#define __INCrtpLibh

#include "vxWorks.h"
#include "rtpLibCommon.h"

#ifdef __cplusplus
extern "C" {
#endif

/* These aliases provide consistent meaning in both kernel & user modes */

#define rtpExit(exitCode)	exit((exitCode))

#ifdef __cplusplus
}
#endif

#endif /* __INCrtpLibh */
