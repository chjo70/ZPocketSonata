/* umaskLibP.h - private header for VxWorks file mode creation mask */

/*
 * Copyright (c) 2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
20mar15,txu  Created (US55492)
*/

#ifndef __INCumaskLibPh
#define __INCumaskLibPh



#include <vxWorks.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Defines */

#define TASK_FILE_CREATION_MASK(tid)  ((WIND_TCB *)(tid))->cmask

#ifdef _WRS_CONFIG_RTP
#define RTP_FILE_CREATION_MASK(pid)  ((WIND_RTP *)(pid))->cmask
#endif /* _WRS_CONFIG_RTP */


/* Typedefs */


/* Function declarations */

extern STATUS umaskLibInit (int mask);
extern mode_t umaskGet(void);
extern STATUS umaskSet(mode_t cmask);
extern mode_t globalUmaskGet(void);


#ifdef __cplusplus
}
#endif

#endif /* __INCumaskLibPh */

