/* 40vxbFdtFslQoriqGpio.cdf - FDT Freescale Qoriq Serail GPIO controller */

/*
 * Copyright (c) 2013, 2014, 2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River License agreement.
 */

/*
modification history
--------------------
20jul17,mjn  text updates (F8862)
16jan14,s_z  code clean up
29oct13,s_z  created
*/

Component DRV_GPIO_FDT_FSL_QORIQ {
        NAME            FDT Freescale Qoriq GPIO Controller driver
        SYNOPSIS        This model is the FDT GPIO Controller driver for Freescale Qoriq serial SOC
        MODULES         vxbFdtFslQoriqGpio.o
        LINK_SYMS       vxbFdtFslQoriqGpioDrv
        REQUIRES        DRV_BUS_FDT_ROOT \
                        INCLUDE_GPIO_SYS
        _CHILDREN       FOLDER_DRIVERS_GPIO
}
