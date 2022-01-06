/* vxbFslQixis.h -  Qixis drv for FreeScale  */

/*
 * Copyright (c) 2014 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
15jun14,fao  created. (US20169) 
*/

/*
DESCRIPTION
This library provides board-specific routines for the
Freescale BSP
*/

#ifndef __INCvxbFslQixish
#define __INCvxbFslQixish

#ifdef __cplusplus
extern "C" {
#endif
 
/* QIXIS registers and bits field defines */

#define QX_CLKSPD1          (0x30)
#define QX_BRDCFG4          (0x54)

#define NGP_BRDCFG1         (0x9)
#define NGP_BRDCFG2         (0xb)

#define QX_SYSCLK_MASK      (0x0F)
#define QX_BRDCFG4_EMISEL   (0xE0)
#define QX_EMI(x)           (((x) << 5) & QX_BRDCFG4_EMISEL)

/* PIXIS registers and bits field defines */

#define PX_SPD              (0x07)
#define PX_SYSCLK_MASK      (0x07)

IMPORT VIRT_ADDR qixisBase;

#define FPGA_CSR_READ_8(x)        \
    vxbRead8 ((void *)VXB_HANDLE_ORDERED , (UINT8 *)((char *)qixisBase + x))

#define FPGA_CSR_WRITE_8(x, y)    \
    vxbWrite8 ((void *)VXB_HANDLE_ORDERED , (UINT8 *)((char *)qixisBase + x), (y))

#ifdef __cplusplus
}
#endif

#endif /* __INCvxbFslQixish */
