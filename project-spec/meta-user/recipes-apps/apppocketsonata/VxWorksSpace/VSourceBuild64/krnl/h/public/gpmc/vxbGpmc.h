/* vxbGpmc.h -  header for GPMC driver */

/*
 * Copyright (c) 2012 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify, or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01e,07nov12,x_z  added support for TI AM335X EVM board.
01d,23nov12,x_z  added control flags and removed CS type.
01c,07nov12,x_z  added support for Mistral OMAP3530 EVM board.
01b,20aug12,x_z  moved driver private defines to vxbGpmcCore.h.
01a,31may12,m_y  written.
*/

#ifndef __INCvxbGpmch
#define __INCvxbGpmch

#ifdef  __cplusplus
 extern "C" {
#endif

#define GPMC_DRV_NAME   "gpmc"

/* platform type*/

typedef enum gpmc_plat_type
   {
   GPMC_PLAT_TI_DM81XX_EVM = 1, /* TI DM81XX EVM board */
   GPMC_PLAT_MST_OMAP3530_EVM,  /* Mistral OMAP3530 EVM board */
   GPMC_PLAT_TI_AM335X_EVM      /* TI AM335X EVM board */
   } GPMC_PLAT_TYPE;

/* flag defines */

/*
 * Note:
 *
 *  1. DMA engine is connected to Prefecth/Postwrite engine, so DMA engine
 *  must be enabled with Prefecth/Postwrite engine enabled, and must be disabled
 *  if Prefecth/Postwrite engine is disabled;
 *  2. Zero-copy function can be enabled only if DMA engine is disabled.
 */

#define GPMC_FLAG_PFPWDIS   0x01    /* Prefecth/Postwrite engine disabled */
#define GPMC_FLAG_DMADIS    0x02    /* DMA disabled */
#define GPMC_FLAG_CACHEDIS  0x04    /* NAND Cache disabled */
#define GPMC_FLAG_ZCOPYDIS  0x08    /* zero-copy disabled */

#ifdef  __cplusplus
}
#endif

#endif /* __INCvxbGpmch */

