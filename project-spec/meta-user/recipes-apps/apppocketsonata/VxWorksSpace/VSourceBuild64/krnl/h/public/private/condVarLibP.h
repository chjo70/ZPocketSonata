/* condVarLibP.h - private condition variable library header file */

/*
 * Copyright (c) 2013-2014 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
05feb14,h_k  removed _WRS_DATA_ALIGN_BYTES to clean up compiler warnings.
             (VXW7-1586)
             reordered members in the CONDVAR structure.
             corrected the offset comments in LP64.
08oct13,cww  added condVarShowInit
21aug13,rfr  written
*/

#ifndef __INCcondVarLibPh
#define __INCcondVarLibPh

#ifndef	_ASMLANGUAGE
#include <vxWorks.h>
#include <vwModNum.h>
#include <condVarLib.h>
#include <semLib.h>
#include <private/qLibP.h>
#include <private/classLibP.h>
#include <private/objLibP.h>
#include <private/eventLibP.h>
#include <stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct cond_var
    {
    OBJ_CORE	objCore;	/* 0x00/0x00: Object Management */
    Q_HEAD	qHead;		/* 0x44/0x80: Pend Queue */
    SEM_ID	mutexId;	/* 0x54/0xa0: Condvar Mutex */
    atomic_t	waitCnt;	/* 0x58/0xa8: Count of waiters */
    int		options;	/* 0x5c/0xb0: Condvar options */
    } CONDVAR;


/* variable declarations */

extern OBJ_CLASS	condVarClass;	/* condition variable object class */
extern CLASS_ID		condVarClassId;	/* condition variable class id */


STATUS		condVarLibInit (void);
void		condVarShowInit (void);

#ifdef __cplusplus
}
#endif

#endif /* _ASMLANGUAGE */
#endif /* __INCcondVarLibPh */
