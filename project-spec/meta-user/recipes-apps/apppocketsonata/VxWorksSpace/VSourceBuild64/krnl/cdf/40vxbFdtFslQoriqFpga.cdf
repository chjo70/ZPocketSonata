/* 40vxbFdtFslQoriqFpga.cdf - Freescale Qoriq FPGA driver */

/*
 * Copyright (c) 2014, 2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
20jul17,mjn  text updates (F8862)
05ayg14,x_z  updated file name and added DRV_FPGA_FDT_FSL_QORIQ. (F804)
23apr14,fao  created
*/

Component       DRV_FPGA_FDT_FSL_QORIQ {
    NAME        Freescale QorIQ FPGA driver
    SYNOPSIS    VxBus Driver for Freescale Qoriq Qixis/ngPixis FPGA
    MODULES     vxbFdtFslQoriqFpga.o
    LINK_SYMS   vxbFdtFslQoriqFpgaDrv
    REQUIRES    INCLUDE_VXBUS
    _CHILDREN   FOLDER_DRIVERS_OTHER
}

Component       DRV_FSL_QIXIS {
    NAME        Freescale QIXIS driver (obsoleted)
    SYNOPSIS    vxBus Driver for QIXIS driver
    MODULES     vxbFdtFslQoriqFpga.o
    LINK_SYMS   vxbFdtFslQoriqFpgaDrv
    REQUIRES    INCLUDE_VXBUS
    _CHILDREN   FOLDER_DRIVERS
}
