/* sysLib.c - Freescale T2/T4 board system-dependent library */

/*
 * Copyright (c) 2014-2016 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
12sep16,syt  add T2080RDB support. (US85017)
15mar16,r_w  add INCLUDE_DEBUG_KPUTS for BOARD_DESC_FLAG_DBG. (V7COR-3896)
31dec15,y_y  typo corrected. (V7PRO-1864)
09jul15,l_z  add fast warm boot support. (F3387)
19aug14,x_z  fixed static analysis issues and compiler warnings. (V7PRO-1186)
18jul14,x_z  added multiple FMAN microcode support. (US40507)
11jun14,syt  added support for T4240QDS. (US15742)
15may14,l_z  fix typo issue. (V7PRO-793)
14may14,ylu  added support for boardInfoShow. (US35954)
28feb14,ylu  created.
*/

/*
DESCRIPTION
This library provides board-specific routines for Freescale T2/T4 board BSP.

INCLUDE FILES:

SEE ALSO:
\tb VxWorks Programmer's Guide: Configuration
*/

/* includes */

#include <vxWorks.h>
#include <fslQoriq.h>

#ifdef INCLUDE_SHOW_ROUTINES
# include <stdio.h>
# include <arch/ppc/vxPpcLib.h>
#endif /* INCLUDE_SHOW_ROUTINES */

#include <private/kwriteLibP.h> /* _func_kprintf */

#ifdef DRV_RESOURCE_QORIQFMAN
#   if (!defined(_WRS_CONFIG_STANDALONE_DTB)) || \
        (!defined(INCLUDE_T4240QDS_DTB_VXBOOT))

/* used to fix FMAN microcode address */

#       include <prjParams.h>
#       include <pmapLib.h>

#   endif /* !_WRS_CONFIG_STANDALONE_DTB || !INCLUDE_T4240QDS_DTB_VXBOOT */
#endif /* DRV_RESOURCE_QORIQFMAN */

/* defines */

#define T2080_MSG(fmt, args...)    \
    do    {                        \
    if (_func_kprintf != NULL)            \
        _func_kprintf (fmt"hmt_t2080vxp3u: ", ##args);    \
    } while (FALSE)

#if defined(INCLUDE_DEBUG_KPRINTF) || defined(INCLUDE_DEBUG_KPUTS)
#   define T2080_DESC_FLAG_DBG BOARD_DESC_FLAG (BOARD_DESC_FLAG_DBG, 0x00)
#else
#   define T2080_DESC_FLAG_DBG 0
#endif

#define T2080_DESC_FLAG_DEF BOARD_DESC_FLAG (0, QORIQ_BOARD_DESC_FLAG_CORENET) | T2080_DESC_FLAG_DBG

/* SOC Revision SVR defines */

#define BOARD_T2080_SVR    0x853000

/* extern */

IMPORT void vxCpuUsDelay (int);

/* forward */

#ifdef INCLUDE_SHOW_ROUTINES
LOCAL void bspInfoShow (void);
#endif /* INCLUDE_SHOW_ROUTINES */

#ifdef DRV_RESOURCE_QORIQFMAN
LOCAL void t2t4QdsInit (void);

#   if (!defined(_WRS_CONFIG_STANDALONE_DTB)) || \
        (!defined(INCLUDE_T4240QDS_DTB_VXBOOT))
UINT8 *         UCODE_START = (UINT8 *) NULL;
#   else /* _WRS_CONFIG_STANDALONE_DTB && INCLUDE_T4240QDS_DTB_VXBOOT */
IMPORT UINT8    fman_ucode_t4240_r2_0_start[];
UINT8 *         UCODE_START = fman_ucode_t4240_r2_0_start;
#   endif /* !_WRS_CONFIG_STANDALONE_DTB || !INCLUDE_T4240QDS_DTB_VXBOOT */
#endif /* DRV_RESOURCE_QORIQFMAN */

/* locals */

LOCAL BOARD_FUNC_TBL bspFuncTbl = {
    .earlyInit  = qoriqEarlyInit,

#ifdef DRV_RESOURCE_QORIQFMAN
    .init       = t2t4QdsInit,
#else /* !DRV_RESOURCE_QORIQFMAN */
    .init       = qoriqInit,
#endif /* DRV_RESOURCE_QORIQFMAN */

    .reset      = qoriqReset,
    .model      = qoriqModel,
    .usDelay    = vxCpuUsDelay,
#ifdef _WRS_CONFIG_SMP
    .cpuEn      = qoriqCpuEnable,
    .cpuAvail   = qoriqCpuAvailGet,
    .cpuDis     = qoriqCpuDisable,
#endif /*_WRS_CONFIG_SMP*/

#ifdef INCLUDE_SHOW_ROUTINES
    .infoShow   = bspInfoShow
#endif /* INCLUDE_SHOW_ROUTINES */
};

LOCAL BOARD_DESC hmt_t2080vpx3u = {
    BOARD_DESC_VER_DEF,     /* uVer       */
    "hmt,t2080vpx3u",         /* pCompat    */
	T2080_DESC_FLAG_DEF,     /* uFlag      */
    qoriqProbe,             /* probe      */
    &bspFuncTbl         /* pFuncTbl   */
};

BOARD_DEF(hmt_t2080vpx3u)


#ifdef DRV_RESOURCE_QORIQFMAN
/*******************************************************************************
*
* t4240qdsInit - initialize board
*
* This routine initializes various feature of BSP. It sets up the features that
* can only be enabled in usrRoot().
*
* NOTE: This routine should not be called directly by the user.
*
* RETURNS: N/A
*
* ERRNO: N/A
*/

LOCAL void t2t4QdsInit (void)
    {
    
    /* initializes general features */

    qoriqInit ();

#if (!defined(_WRS_CONFIG_STANDALONE_DTB)) || \
    (!defined(INCLUDE_T4240QDS_DTB_VXBOOT))
    UCODE_START = 
        (UINT8 *) pmapGlobalMap ((PHYS_ADDR) QORIQ_FMAN_UCODE_PHYS_ADRS, 
                                 (size_t) QORIQ_FMAN_UCODE_SIZE, 
                                 MMU_ATTR_SUP_RW | MMU_ATTR_CACHE_OFF | 
                                 MMU_ATTR_CACHE_GUARDED);
    if ((void *) UCODE_START == PMAP_FAILED)
        {
    	T2080_MSG ("failed to map FMAN micro code space\n");
        UCODE_START = (UINT8 *) NULL;
        }
#endif /* !_WRS_CONFIG_STANDALONE_DTB || !INCLUDE_T4240QDS_DTB_VXBOOT */
    }
#endif /* DRV_RESOURCE_QORIQFMAN */

#ifdef INCLUDE_SHOW_ROUTINES
/*******************************************************************************
*
* socModelGet - get the SOC model name
*
* This routine returns the model name of the CPU board.
*
* RETURNS: A pointer to the string or NULL when the processor is a unknown type.
*
* ERRNO: N/A
*/

LOCAL char * socModelGet
    (
    UINT32  uSvr
    )
    {
    char* retChar;

    switch(QORIQ_SVR_ID(uSvr))
        {
        case BOARD_T2080_SVR:
            retChar = "T2080";
            break;
        default:
            retChar = NULL;
            break;
        }

    return (retChar);
    }

/*******************************************************************************
*
* coreModelGet - get the core name
*
* This routine returns the core name of the CPU board.
*
* RETURNS: A pointer to the string or NULL when the CORE is a unknown type.
*
* ERRNO: N/A
*/

LOCAL char * coreModelGet
    (
    UINT32  uPvr
    )
    {
    char* retChar = NULL;

    switch(_PPC_PVR_ID(uPvr))
        {
        case _PPC_PVR_VER_E6500:
            retChar = "E6500";
            break;
        default:
            retChar = NULL;
            break;
        }

    return (retChar);
    }

/*****************************************************************************
*
* t2t4CoreInfoShow - display T2T4 core information
*
* This routine displays the information of T2T4 core.
*
* ERRNO: N/A
*
* RETURNS: N/A
*/

LOCAL void t2t4CoreInfoShow (void)
    {
    UINT32 uPvr;
    char * pCoreModel;

    uPvr = vxPvrGet ();

    pCoreModel = coreModelGet(uPvr);

    if (pCoreModel != NULL)
        (void) printf ("CORE:%s Rev %d.%d\n",pCoreModel, _PPC_PVR_MAJ (uPvr), _PPC_PVR_MIN (uPvr));
    else
        (void) printf ("(Core is unknown revision)\n");
    }

/*****************************************************************************
*
* bspInfoShow - display T2/T4QDS board information
*
* This routine displays the board/cpu/core information of T2/T4QDS board.
*
* ERRNO: N/A
*
* RETURNS: N/A
*/

LOCAL void bspInfoShow (void)
    {
    UINT32  uSvr;
    char  * socMod;

    uSvr = vxSvrGet();

    socMod = socModelGet (uSvr);

    if (socMod != NULL)
        {
        (void) printf("FreeScale %sQDS (unknown revision), CPU:%s", socMod, socMod);

        if (QORIQ_SVR_SEC(uSvr))
            (void) printf("E ");
        (void) printf("Rev %d.%d, ", QORIQ_SVR_MAJ (uSvr), QORIQ_SVR_MIN (uSvr));
        }
    else
        (void) printf("FreeScale unknown board, CPU:unknown processor ");

    /* no method to obtain board revision */

    t2t4CoreInfoShow ();
    }
#endif /* INCLUDE_SHOW_ROUTINES */

