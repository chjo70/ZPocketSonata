/* envLib.h - environment varable library header file */

/*
 * Copyright (c) 1990-2005, 2009-2010, 2014-2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement. 
 */

/*
modification history
--------------------
05mar15,pad  Added certification considerations comment for 'environ'.
05feb14,cww  added declaration for ppGlobalEnviron (VXW7-1322)
29apr10,pad  Moved extern C statement after include statements.
26aug09,cww  Add LP64 support
27apr05,kk   add NOMANUAL to environ macro for apigen (SPR# 108372)
17mar04,pad  Added envGet() prototype.
22sep92,rrr  added support for c++
19jul92,smb  moved prototype for getenv to stdlib.h
                 added include stdlib.h
04jul92,jcf  cleaned up.
26may92,rrr  the tree shuffle
09dec91,rrr  fixed bad prototype (envShow).
04oct91,rrr  passed through the ansification filter
		  -changed copyright notice
05oct90,shl  added copyright notice.
                 made #endif ANSI style.
01aug90,jcf  cleanup.
12jul90,rdc  written.
*/

#ifndef __INCenvLibh
#define __INCenvLibh

#include <vxWorks.h>
#include <taskLib.h>

#ifdef __cplusplus
extern "C" {
#endif

extern char ** ppGlobalEnviron;

/*******************************************************************************
*
* environ - environment pointer
*
* The following macro is provided for code that manipulates the environment
* variable array directly.
*
* CERTIFICATION CONSIDERATIONS
* The use of a ternary operator here is an accepted exception to the coding
* convention for certified code due to both the traditional definition and use
* of the 'environ' symbol (as a 'char **' it can be directly set as well as
* read) and the requirement for referencing either of two different environment
* variables sets (global or task-specific) in the kernel environment.
*
* \NOMANUAL
*/

#define environ 							\
    (								      	\
    (taskIdCurrent->ppEnviron == NULL) ? 				\
    ppGlobalEnviron : taskIdCurrent->ppEnviron 				\
    )

extern STATUS 	envLibInit (BOOL installHooks);
extern STATUS 	envPrivateCreate (TASK_ID taskId, _Vx_usr_arg_t envSource);
extern STATUS 	envPrivateDestroy (TASK_ID taskId);
extern char **	envGet (TASK_ID taskId);
extern STATUS 	putenv (char * pEnvString);
extern void 	envShow (TASK_ID taskId);

#ifdef __cplusplus
}
#endif

#endif /* __INCenvLibh */

