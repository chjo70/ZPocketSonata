/* errnoLib.h - error status library header */

/* 
 * Copyright (c) 1984-1992, 2009-2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01l,28apr10,pad  Moved extern C statement after include statements.
01k,24feb09,cww  Add support for LP64
01j,22sep92,rrr  added support for c++
01i,18jul92,smb  added include errno.h.
01i,09jul92,smb  move function declarations from errno.h
01h,04jul92,jcf  cleaned up.
01g,26may92,rrr  the tree shuffle
01f,26nov91,llk  added S_errnoLib_NO_STAT_SYM_TBL.
		 removed errno and function prototypes (already in errno.h).
01e,04oct91,rrr  passed through the ansification filter
		  -fixed #else and #endif
		  -changed copyright notice
01d,05oct90,shl  added ANSI function prototypes.
                 made #endif ANSI style.
                 added copyright notice.
01c,02mar90,jcf  changed to support _errno.
01b,05jun88,dnw  changed stsLib to errnoLib.
01a,29apr88,gae  written.
*/

/*
 * Note: This file contains definitions that must be maintained in both kernel
 * and user space
 */

#ifndef __INCerrnoLibh
#define __INCerrnoLibh

#include "vxWorks.h"
#include "errno.h"

#ifdef __cplusplus
extern "C" {
#endif

/* status codes */

#define S_errnoLib_NO_STAT_SYM_TBL      (M_errnoLib | 1)

#if defined(__STDC__) || defined(__cplusplus)

extern STATUS   errnoOfTaskSet (TASK_ID taskId, int errorValue);
extern STATUS   errnoSet (int errorValue);
extern int      errnoGet (void);
extern int      errnoOfTaskGet (TASK_ID taskId);

#else   /* __STDC__ */

extern STATUS   errnoOfTaskSet ();
extern STATUS   errnoSet ();
extern int      errnoGet ();
extern int      errnoOfTaskGet ();

#endif  /* __STDC__ */

#ifdef __cplusplus
}
#endif

#endif /* __INCerrnoLibh */
