/* ftlFlashIf.h - interfaces between ftl and underlying flash drivers */ 

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
13may15,txu  fix V7STO-358 : wrong include after extern "C"
04sep13,jxu  adapted path of includes for vx7 
15jun12,jxu  written.
*/

#ifndef __INCftlFlashIfh
#define __INCftlFlashIfh


/* includes */

#include <private/ftlOsIf.h>
#include <private/ftlBm.h>
#include <private/ftlLibP.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* defines */

/* declarations */

/* ftl flash interfaces */

int ftlFlashErase (FTL_BM_DESC * pBm, fblock_t blkNo, int option);
int ftlFlashRW (FTL_BM_DESC * pBm, FTL_ADDR * pFromAddr, 
            size_t dataLen, char * pBuf, FTL_ADDR * pErrorAddr, 
            size_t * pRetIoLen, int rwFlag);
BOOL ftlIsFactBadBlk (FTL_BM_DESC * pBm, fblock_t blkNo);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __INCftlFlashIfh */

