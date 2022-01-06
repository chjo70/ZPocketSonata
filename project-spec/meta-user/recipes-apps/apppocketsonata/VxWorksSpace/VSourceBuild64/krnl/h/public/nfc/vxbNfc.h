/* vxbNfc.h -  header file for NFC driver */

/*
 * Copyright (c) 2014-2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify, or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
07mar16,ffu  Wait hardware process use pull mode for V7STO-295,V7STO-297,
             and V7STO-450
10feb15,lxj  added K70 support (US50342)
17aug14,e_d  written
*/

#ifndef __INCvxbNfch
#define __INCvxbNfch

#ifdef  __cplusplus
 extern "C" {
#endif

#define NFC_DRV_NAME           "nfc"

#define NFC_SECSZ_INIT         0x841
#define NFC_CFG_INIT           0x1A681
#define NFC_WAIT_PULL

/* platform type*/

typedef enum nfc_plat_type
    {
    NFC_PLAT_FSL_VYBIRD = 1,  /* freescale vybird board */
    NFC_PLAT_FSL_K70    = 2,  /* freescale K70twr board */
    } NFC_PLAT_TYPE;

#ifdef  __cplusplus
}
#endif

#endif /* __INCvxbNfch */

