/* schedP.h - sched private header file */

/*
 * Copyright 1993-1994, 2000, 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01e,18may10,jpb  Added prototype for schedPxScLibInit.
01d,29apr10,pad  Moved extern C statement after include statements.
01c,11sep00,jgn  add extern for posixPriorityNumbering
01b,05jan94,kdl  added include of sched.h.
01a,09nov93,dvs  written
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

extern STATUS schedPxScLibInit (void);

#ifdef __cplusplus
}
#endif

#endif /* __INCschedPh */

