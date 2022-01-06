/* 40vxbFslSpi.cdf - Component Definition file for Freescale SPI */

/*
 * Copyright (c) 2015, 2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
14jun17,mjn  text updates (F8862)
14oct15,wqi  created (US66526)
*/

Component       DRV_FSL_SPI {
    NAME        Freescale SPI controller
    SYNOPSIS    This component imeplements the VxBus driver for the Freescale SPI controller.
    MODULES     vxbFdtFslSpi.o
    LINK_SYMS   vxbFdtFslSpiDrv
    REQUIRES    INCLUDE_VXBUS
    _CHILDREN   FOLDER_DRIVERS_SPI
}
