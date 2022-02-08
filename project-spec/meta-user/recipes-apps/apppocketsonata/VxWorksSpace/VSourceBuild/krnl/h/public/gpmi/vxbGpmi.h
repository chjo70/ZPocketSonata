/* vxbGpmi.h -  header for vxbGpmi driver */

/*
 * Copyright (c) 2014 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify, or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
05may14,ywu  add NAND flash support for imx6 AI. (US34699)
*/

#ifndef __INCvxbGpmih
#define __INCvxbGpmih

#ifdef  __cplusplus
 extern "C" {
#endif

#define GPMI_DRV_NAME   "gpmi"

/* platform type*/

typedef enum gpmi_plat_type
   {
   GPMI_PLAT_FSL_IMX6_AI = 1,  /* freescale IMX6 AI board */
   } GPMI_PLAT_TYPE;

#ifdef  __cplusplus
}
#endif

#endif /* __INCvxbGpmih */
