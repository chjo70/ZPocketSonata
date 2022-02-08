/* taskPxLib.h - user-side pthread scheduler support in VxWork */

/*
 * Copyright (c) 2005-2006, 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
*/
 
/*
modification history
--------------------
01d,29jul10,pad  Moved extern C statement after include statements.
01c,14apr10,jpb  Updated for LP64 adaptation.
01b,28feb06,jln  added taskPxAttrCreate()
01a,25jun05,jln  Created
*/

#ifndef __INCtaskPxLibh
#define __INCtaskPxLibh

#include <vxWorks.h>		/* common definitions for all VxWorks libs */
#include <private/taskPxLibCommonP.h>

#ifdef __cplusplus
extern "C" {
#endif

/* function declaration */

extern STATUS taskPxAttrSet (TASK_ID tid, TASK_PX_ATTR * pAttr); 
extern STATUS taskPxAttrGet (TASK_ID tid, TASK_PX_ATTR * pAttr);
extern STATUS taskPxAttrCreate (TASK_ID tid, TASK_PX_ATTR * pAttr); 

#ifdef __cplusplus
}
#endif

#endif /* __INCtaskPxLibh */
