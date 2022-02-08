/* schedP.h - sched private header file */

/* Copyright 2003, 2010 Wind River Systems, Inc. */

/*
modification history
--------------------
01b,29jul10,pad  Moved extern C statement after include statements.
01a,24nov03,pad  Created, based on kernel version "01c,11sep00,jgn".
*/

#ifndef __INCschedPh
#define __INCschedPh

#include "sched.h"

#ifdef __cplusplus
extern "C" {
#endif

#define VXWORKS_LOW_PRI         255     /* low priority VxWorks numbering */
#define VXWORKS_HIGH_PRI        0       /* high priority VxWorks numbering */
#define POSIX_LOW_PRI           0       /* low priority POSIX numbering */
#define POSIX_HIGH_PRI          255     /* high priority POSIX numbering */

/* conversion macro */
#define PX_VX_PRIORITY_CONVERT(prior) (posixPriorityNumbering ? \
                                           POSIX_HIGH_PRI - prior : prior)
#define PX_NUMBER_CONVERT(prior) (posixPriorityNumbering ? \
				  prior : POSIX_HIGH_PRI - prior )

extern BOOL posixPriorityNumbering;

extern BOOL _schedPxKernelIsTimeSlicing (ULONG * pPeriod);

#ifdef __cplusplus
}
#endif

#endif /* __INCschedPh */

