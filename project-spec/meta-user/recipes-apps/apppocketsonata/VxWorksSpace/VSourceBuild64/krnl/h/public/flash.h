/* flash.h - Flash Public Head File */

/*
 * Copyright (c) 2012, 2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
13may15,txu  fix V7STO-358 : wrong include after extern "C"
22oct12,x_z  added Flash usage type.
22sep12,x_z  changed column address from UINT16 to UINT32 for NOR Flash;
             changed type of uLen of FLASH_SGBUF_T type;
             updated FLASH_CELL_T.
19sep12,x_z  adjusted general address defines for NAND Flash.
18sep12,jxu  integration with FTL.
03sep12,x_z  added private information for scatter-gather buffer;
             added Flash bad block descriptor define
20aug12,x_z  fixed compatibility issue with old Flash type defines.
07aug12,x_z  updated scatter-gather buffer interface.
31jul12,x_z  created.
*/

#ifndef __INCflashh
#define __INCflashh

#include <dllLib.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef UINT32  FLASH_BLK_ADDR_T;   /* block address type */
typedef UINT32  FLASH_BLK_SIZE_T;   /* block size type */

typedef UINT16  FLASH_PAGE_ADDR_T;  /* page address type */
typedef UINT16  FLASH_PAGE_SIZE_T;  /* page size type */
typedef UINT16  FLASH_OOB_SIZE_T;   /* OOB size type */
typedef UINT32  FLASH_COL_ADDR_T;   /* column address type */

typedef UINT64 FLASH_FLAT_ADDR_T;

/*
 * 1. Page Address must be 0 if no page support, such as NOR Flash;
 * 2. Some types of Flash has the additional spare part called as OOB after
 * the data part of each page, then Column Address is the offset to the entire
 * page including data and OOB.
 */

typedef struct flash_norm_addr_t
    {
    FLASH_BLK_ADDR_T    blkAddr;
    FLASH_PAGE_ADDR_T   pageAddr;
    FLASH_COL_ADDR_T    colAddr;
    } FLASH_NORM_ADDR_T, *pFLASH_NORM_ADDR_T;

typedef struct flash_norm_addr_al_t
    {
    FLASH_BLK_ADDR_T    blkAddr;
    FLASH_PAGE_ADDR_T   pageAddr;
    } FLASH_NORM_ADDR_AL_T, *pFLASH_NORM_ADDR_AL_T;

/*
 * General Address type
 *
 *  1. If OOB is valid for the chip, then page must be valid, such as NAND
 *  Flash, and Column Address will exceed Page Size a little, so
 *
 *  General Address =
 *      Block Address * Block Size + Page Address * (Page Size * 2) +
 *      Column Address
 *
 *  2. If OOB is invalid but Page is valid for the chip, such as SPI Flash,
 *
 *  General Address =
 *      Block Address * Block Size + Page Address * Page Size + Column Address
 *
 * 3. If both OOB and Page are invalid for the chip,
 *
 * General Address =
 *      Block Address * Block Size + Column Address
 */

#ifndef __INCvxbFlashh
typedef FLASH_FLAT_ADDR_T   FLASH_ADDR_T, *pFLASH_ADDR_T;

 /* general size type */

#undef FLASH_SIZE_T
typedef UINT64              FLASH_SIZE_T;
#else
typedef FLASH_ADDR_T *      pFLASH_ADDR_T;
#endif /* !__INCvxbFlashh */

/* Flash type */

typedef enum flash_type_t
    {
    FLASH_TYPE_NOR = 1,
    FLASH_TYPE_NAND
    } FLASH_TYPE_T;

typedef enum flash_cell_t
    {
    FLASH_CELL_NONE = 0,
    FLASH_CELL_SLC,
    FLASH_CELL_MLC
    } FLASH_CELL_T;

/*
 * scatter-gather buffer
 *
 * Note:
 *
 * 1. Every buffer can be only for page data or OOB;
 * 2. The length to be accessed in one buffer must not exceed one page if page
 * is supported.
 */

struct flash_sgbuf_t;
typedef struct flash_sgbuf_t FLASH_SGBUF_T, *pFLASH_SGBUF_T;
struct flash_sgbuf_t
    {
    FLASH_NORM_ADDR_T   addr;   /* start address */
    FLASH_PAGE_SIZE_T   uLen;   /* length to be accessed */
    UINT8 *             pBuf;   /* pointer to buffer */
    FLASH_SGBUF_T *     pNext;  /* next buffrer */
    void *              pPriv;  /* private */
    void *              pOp;    /* opinion */
    };

/* Flash usage type */

typedef enum flash_usage_type_t
    {
    FLASH_USAGE_FTL = 0,
    FLASH_USAGE_NVRAM
    } FLASH_USAGE_TYPE_T;

#ifdef __cplusplus
}
#endif

#endif /* __INCflashh */

