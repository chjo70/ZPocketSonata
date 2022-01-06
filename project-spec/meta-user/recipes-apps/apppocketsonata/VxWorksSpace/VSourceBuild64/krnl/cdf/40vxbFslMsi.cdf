/* 40vxbFslMsi.cdf - Freescale MSIi controller */

/*
 * Copyright (c) 2013-2014, 2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River License agreement.
 */

/*
modification history
--------------------
14jun17,mjn  text updates (F8862)
28apr14,y_y  fix comment issue. (US37630)
23may13,y_y  created
*/

Component DRV_FSL_MSI {
    NAME        VxBus Freescale MSI
    SYNOPSIS    This component provides the VxBus Freescale MSI driver.
    MODULES     vxbFslMsi.o
    LINK_SYMS   vxbFslMsiDrv
    REQUIRES    DRV_BUS_FDT_ROOT \
                INCLUDE_INTCTLR_DYNAMIC_LIB
    _CHILDREN   FOLDER_DRIVERS_INTERRUPT
}
