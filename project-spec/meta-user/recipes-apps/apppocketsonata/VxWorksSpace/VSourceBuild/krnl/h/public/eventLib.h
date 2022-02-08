/* eventLib.h - events library header file */

/*
 * Copyright (c) 2001-2003, 2008-2010, 2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
20may17,dlk  Make this file include <eventLibCommon.h> for most of its
             content, to reduce redundancy somewhat.
16jun10,pcs  Change data type of timeout from an int to _Vx_ticks_t
29apr10,pad  Moved extern C statement after include statements.
15may09,pcs  Add new datatype _Vx_event_t.
12mar09,pcs  Updated to add support for the LP64 data model.
23oct08,zl   added interruptible events options.
18nov02,bwa  Added EVENTS_KEEP_UNWANTED option (SPR 84417).
15jan02,bwa  Removed events 25 to 32 from list of events available to user.
13nov01,bwa  Changed EVENTxx defs to VXEVxx.
17oct01,bwa  Added #include "vwModNum.h". Added 2 errnos.
20sep01,bwa  Created
*/

#ifndef __INCeventLibh
#define __INCeventLibh

#include <vxWorks.h>
#include <vwModNum.h>
#include <eventLibCommon.h>

#ifdef __cplusplus
extern "C" {
#endif

/* configuration options */

#define EVENTS_NONINTERRUPTIBLE	0x00	/* signals don't wake up RTP tasks */
#define EVENTS_INTERRUPTIBLE	0x01	/* signals wake up RTP tasks */



#ifdef __cplusplus
}
#endif

#endif /* __INCeventLibh */

