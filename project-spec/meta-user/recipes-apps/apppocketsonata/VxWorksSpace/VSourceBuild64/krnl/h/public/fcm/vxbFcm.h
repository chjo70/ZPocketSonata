/* vxbFcm.h -  header for FCM driver */

/*
 * Copyright (c) 2013 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify, or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01a,30jul13,ywu  written
*/

#ifndef __INCvxbFcmh
#define __INCvxbFcmh

#ifdef  __cplusplus
 extern "C" {
#endif

#define FCM_DRV_NAME   "fcm"

/* platform type*/

typedef enum fcm_plat_type
   {
   FCM_PLAT_FSL_P2020_RDB = 1,  /* freescale p2020 rdb board */
   FCM_PLAT_FSL_P5040_DS = 2,   /* freescale p5040 ds board */
   } FCM_PLAT_TYPE;

#ifdef  __cplusplus
}
#endif

#endif /* __INCvxbFcmh */

