/* eventLib.h - events library header file */

/* Copyright 2001-2004, 2010, 2017 Wind River Systems, Inc. */

/*
modification history
--------------------
20may17,dlk  Remove redundant declarations found in eventLibCommon.h.
29jul10,pad  Moved extern C statement after include statements.
16jun10,pcs  Change data type of timeout from an int to _Vx_ticks_t
09feb04,hya  Included eventSysCall.h.
18nov02,bwa  Added EVENTS_KEEP_UNWANTED option (SPR 84417).
15jan02,bwa  Removed events 25 to 32 from list of events available to user.
13nov01,bwa  Changed EVENTxx defs to VXEVxx.
17oct01,bwa  Added #include "vwModNum.h". Added 2 errnos.
20sep01,bwa  Created
*/

#ifndef __INCeventLibh
#define __INCeventLibh

#include "vxWorks.h"
#include "vwModNum.h"
#include "eventLibCommon.h"
#include "eventSysCall.h"

#ifdef __cplusplus
extern "C" {
#endif


#ifdef __cplusplus
}
#endif

#endif /* __INCeventLibh */

