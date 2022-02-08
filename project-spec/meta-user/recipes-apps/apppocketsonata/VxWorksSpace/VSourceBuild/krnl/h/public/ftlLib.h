/* ftlLib.h - generic ftl private header */

/*
 * Copyright (c) 2012-2013, 2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
11dec15,ffu  clean up GNU build warning of issue V7STO-386
13may15,txu  fix V7STO-358 : wrong include after extern "C"
09sep13,jxu  adapted path of includes for vx7
08jun13,jxu  added a format option to support preserving runtime
             bad block information when formatting.
08nov12,jxu  added ftlCheckSanity().
29feb12,jxu  written.
*/

#ifndef __INCftlLibh
#define __INCftlLibh


/* includes */

#include <private/ftlOsIf.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* defines */

#define S_ftlLib_INVALID_PARAM          (M_ftlLib | 1)
#define S_ftlLib_NO_DEV                 (M_ftlLib | 2)
#define S_ftlLib_DEV_TOO_SMALL          (M_ftlLib | 3)
#define S_ftlLib_NO_VALID_FTL_ID        (M_ftlLib | 4)
#define S_ftlLib_NO_VALID_BBMT          (M_ftlLib | 5)
#define S_ftlLib_DATA_ERROR_ECC_UNRECV  (M_ftlLib | 6)
#define S_ftlLib_BAD_BLOCK_MAP          (M_ftlLib | 7)
#define S_ftlLib_BAD_PAGE_MAP           (M_ftlLib | 8)
#define S_ftlLib_NO_FREE_REPL_BLK       (M_ftlLib | 9)

/* format options */

#define FTL_FMT_OPT_PRESERVE_BBM        0x1     /* preserve bad block information */

/* typedefs */

typedef struct ftl_fmt_arg_t
    {
    /* 
     * The <sizeGC> field spcifies the size (in percentage of the total size) 
     * of the flash space that could be reserved by FTL to faciliate GC 
     * and WL. Giving a appropriate value would bring performance gain at 
     * the expense of usable flash space. In most cases, the larger this 
     * value, the better the performance. However, it is limited up to 30% 
     * because the management overhead would grow as the value gets larger. 
     * The acceptable range of this parameter is from 3 to 30 (means 3% to 
     * 30%).
     */

    int sizeGC;         /* in percent */

    /* 
     * The following <sizeBBM> field gives the size (in percentage of the 
     * total size) of the flash space that could be reserved by FTL to 
     * replace runtime bad blocks. Because the blocks in NAND Flash could 
     * not be guaranteed to have the same P/E cycles and even the best WL 
     * algorithm can not make all the blocks be erased the same times as 
     * system running, it is necessary to provide some spare blocks for
     * emergency of handling runtime bad blocks or erronous blocks. The 
     * minimum value that is acceptable is 1 (1%), while the maximum is 
     * 10 (%10).
     */

    int sizeBBM;        /* in percent */

    /*
     * Additional options for future extension. User should set it to 
     * zero if no options are speicified. Currently only the option
     * FTL_FMT_OPT_PRESERVE_BBM is defined and supported.
     */

    int options;
    }FTL_FMT_ARG_T;

/* forward declarations */

STATUS ftlAdvFormat (const char * flashDevName, FTL_FMT_ARG_T * pFmtArg);
STATUS ftlFormat (const char * flashDevName, int sizeGC, int sizeBBM, 
            int options);
STATUS ftlMount (const char * flashDevName, int options);
STATUS ftlCheckSanity (const char * pDevName, int flags);
#if defined (INCLUDE_FTL_DISCARD)
STATUS ftlDiscardLibInit (void);
#endif
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __INCftlLibh */

