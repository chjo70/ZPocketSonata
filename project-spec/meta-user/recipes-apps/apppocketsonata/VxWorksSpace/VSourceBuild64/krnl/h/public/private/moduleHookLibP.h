/* moduleHookLibP.h - private module hook facility header */

/*
 * Copyright (c) 2006-2007, 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
01f,29apr10,pad  Moved extern C statement after include statements.
01e,23feb10,v_r  Moved to fully qualified function pointers.
01d,12jun07,v_r  Made moduleHookLib available on the host (req
                 CQ:WIND00084355).
01c,16mar07,v_r  Moved to static initialization model (for req
                 CQ:WIND00045277).
01b,26jan06,v_r  Fixed build warning.
01a,16jan06,v_r  Written.
*/

#ifndef __INCmoduleHookLibPh
#define __INCmoduleHookLibPh

/* includes */

#ifdef HOST
#include <host.h>
#include <vmutex.h>
#else
#include <vxWorks.h>
#include <limits.h>
#include <semLib.h>
#endif	/* HOST */

#include <sllLib.h>
#include <moduleLib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Typedefs */

typedef struct moduleHookListStruct	/* module hook list structure */
    {
    SL_LIST moduleLoadHookList;		/* list of loader hooks */
    SL_LIST moduleUnloadHookList;	/* list of unloader hooks */
    SEM_ID  moduleHookListSem;		/* hook lists protection */
    } MOD_HKLST_STRUCT;

typedef MOD_HKLST_STRUCT * MOD_HKLST_STRUCT_ID;

typedef void (* MODULE_HOOK_RTN) (MODULE_ID moduleId, UINT32 options);

typedef struct
    {
    SL_NODE	    node;   /* node for the linked list */
    MODULE_HOOK_RTN func;   /* associated routine */
    } MOD_HKLST_HOOK;

/* Defines */

/* Function declarations */

extern STATUS	moduleHookLibInit	(void);
extern STATUS	moduleLoadHookAdd	(MODULE_HOOK_RTN moduleLoadHookRtn);
extern STATUS	moduleLoadHookDelete	(MODULE_HOOK_RTN moduleLoadHookRtn);
extern STATUS	moduleUnloadHookAdd	(MODULE_HOOK_RTN moduleUnloadHookRtn);
extern STATUS	moduleUnloadHookDelete	(MODULE_HOOK_RTN moduleUnloadHookRtn);

#ifdef __cplusplus
}
#endif

#endif /* __INCmoduleHookListPh */

