/* usrFtl.c - user configuration for ftl library */

/*
 * Copyright 2005 - 2006, 2009 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
11dec15,ffu  clean up GNU build warning of issue V7STO-386
01c,04sep13,jxu  adapted path of includes for vx7 
01b,13jun13,jxu  calls mtdAttach only when MTD component is included.
01a,10oct12,jxu  written.
*/

/*
DESCRIPTION
*/

/* includes */

#include <vxWorks.h>
#include <ftlLib.h>
#include <flash.h>
#include <mtd.h>
#include <private/ftlLibP.h>
#include <private/ftlBm.h>
#include <private/ftlCacheP.h>

/* defines */

/* typedefs */

/* globals */

MEM_BUDGET_T ftlMemBudgetCfg    = MEM_BDGT_MODEST; /* modest memory usage */

BOOL ftlBgSvcTaskEnabled        = TRUE; 
BOOL ftlAutoMountEnabled        = TRUE;

BOOL ftlCacheEnabled            = FALSE;
BOOL ftlDiscardEnabled          = FALSE;

size_t ftlCacheSize             = 0x100000;

/* externs */
#if defined (INCLUDE_FTL_FORMAT)
extern STATUS ftlFormatLibInit (void);
#endif
#if defined (INCLUDE_FTL_SHOW)
extern STATUS ftlShowLibInit (void);
#endif
#if defined (INCLUDE_FTL_DISCARD)
extern STATUS usrFtlDiscardInit (void);
#endif

/***************************************************************************
*
* usrFtlInit -
*/

STATUS usrFtlInit
    (
    int         memBudget,
    BOOL        bSvcTaskEnabled,
    BOOL        bAutoMount,
    int         reserved
    )
    {
    int  error = OK;

    if (memBudget == 0)
        {
        ftlMemBudgetCfg = MEM_BDGT_TIGHT;
        }
    else if (memBudget == 1)
        {
        ftlMemBudgetCfg = MEM_BDGT_MODEST;
        }
    else
        {
        ftlMemBudgetCfg = MEM_BDGT_ABUNDANT;
        }

    ftlBgSvcTaskEnabled         = bSvcTaskEnabled;
    ftlAutoMountEnabled         = bAutoMount;

#if defined (INCLUDE_FTL_FORMAT)
    ftlFormatLibInit ();
#endif
#if defined (INCLUDE_FTL_SHOW)
    ftlShowLibInit ();
#endif
#if defined (INCLUDE_FTL_DISCARD)
    usrFtlDiscardInit ();
#endif
#if defined (INCLUDE_MTD)
    error = mtdAttach (FLASH_USAGE_FTL, ftlBmNotify, 0); 
#endif

    return ((error != OK) ? ERROR : OK);
    }

/***************************************************************************
*
* usrFtlDiscardInit -
*/

STATUS usrFtlDiscardInit
    (
    void
    )
    {
#if defined (INCLUDE_FTL_DISCARD)
    ftlDiscardEnabled           = TRUE;
    _func_ftlDiscardInit        = ftlDiscardInit;
    _func_ftlDiscardCleanup     = ftlDiscardCleanup;
    _func_ftlDiscard            = ftlDiscard;
    _func_ftlDiscardBlk         = ftlDiscardBlk;
    _func_ftlDiscardUpdate      = ftlDiscardUpdate;
    _func_ftlDiscardFind        = ftlDiscardFind;
#endif

    return (OK);
    }


/***************************************************************************
*
* usrFtlInit -
*/

STATUS usrFtlCacheInit
    (
    unsigned cacheSize
    )
    {
#if defined (INCLUDE_FTL_CACHE)
    ftlCacheEnabled             = TRUE;
    ftlCacheSize                = cacheSize;
    _func_ftlCacheInit          = ftlCacheInit;
    _func_ftlCacheCleanup       = ftlCacheCleanup;
    _func_ftlCacheBlkRW         = ftlCacheBlkRW;
    _func_ftlCacheFlush         = ftlCacheFlush;
    _func_ftlCacheDiscard       = ftlCacheDiscard;
    _func_ftlCacheCheckFlush    = ftlCacheCheckFlush;
#endif

    return (OK);
    }

