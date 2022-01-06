/* taskVarLib.h - header for task variables */

/*
 * Copyright (c) 1984-1992, 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
02c,04mar10,zl   disabled declarations for SMP and LP64
02b,22sep92,rrr  added support for c++
02a,04jul92,jcf  cleaned up.
01f,26may92,rrr  the tree shuffle
01e,04oct91,rrr  passed through the ansification filter
		  -fixed #else and #endif
		  -changed copyright notice
01d,05oct90,shl  added ANSI function prototypes.
                 made #endif ANSI style.
                 added copyright notice.
01c,08aug90,shl  added INCtaskVarLibh to #endif.
01b,01aug90,jcf  cleanup.
01a,25jan88,jcf  written by extracting from vxLib.h v02l.
*/

#ifndef __INCtaskVarLibh
#define __INCtaskVarLibh

#include <vxWorks.h>
#include <vsbConfig.h>


#ifdef __cplusplus
extern "C" {
#endif

/* task variable descriptor */

typedef struct taskVar	/* TASK_VAR */
    {
    struct taskVar *	next;	/* ptr to next task variable */
    int *		address;/* address of variable to swap */
    int			value;	/* when task is not running: */
				/*      save of task's val; */
				/* when task is running:  */
				/*      save of orig. val */
    } TASK_VAR;

/* function declarations */

#if !defined (_WRS_CONFIG_SMP) && !defined (_WRS_CONFIG_LP64)

extern STATUS 	taskVarAdd (TASK_ID tid, int *pVar);
extern STATUS 	taskVarDelete (TASK_ID tid, int *pVar);
extern STATUS 	taskVarInit (void);
extern STATUS 	taskVarSet (TASK_ID tid, int *pVar, int value);
extern int 	taskVarGet (TASK_ID tid, int *pVar);
extern int 	taskVarInfo (TASK_ID tid, TASK_VAR varList [], int maxVars);

#endif /* SMP / LP64 */

#ifdef __cplusplus
}
#endif

#endif /* __INCtaskVarLibh */
