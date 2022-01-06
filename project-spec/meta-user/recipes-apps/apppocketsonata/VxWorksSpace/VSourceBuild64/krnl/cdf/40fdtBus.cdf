/* 40fdtBus.cdf - Flat Device Tree component description file */

/*
 * Copyright (c) 2012, 2013, 2016-2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify, or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
14jun17,mjn  text updates (F8862)
26apr16,emj  CERT: Update to produce partially linked objects
01a,23may13,x_z  created
*/

Component DRV_BUS_FDT_ROOT {
    NAME            FDT bus
    SYNOPSIS        This component implements the Flat Device Tree (FDT) bus driver.
#ifndef _WRS_CONFIG_CERT_KERNEL_OBJECT
    MODULES         vxbFdtBus.o
    LINK_SYMS       vxbFdtBusDrv
#else
        _REQUIRES INCLUDE_KERNEL
#endif
    _CHILDREN       FOLDER_DRIVERS_BUS
    REQUIRES        INCLUDE_FDT_LIB \
                    INCLUDE_VXBUS
}

Component DRV_BUS_FDT_SIMPLE {
    NAME            Simple bus
    SYNOPSIS        This component implements the simple bus driver.
#ifndef _WRS_CONFIG_CERT_KERNEL_OBJECT
    MODULES         vxbSimpleBus.o
    LINK_SYMS       vxbSimpleBusDrv
#else
        _REQUIRES INCLUDE_KERNEL
#endif
    _CHILDREN       FOLDER_DRIVERS_BUS
    REQUIRES        INCLUDE_FDT_LIB \
                    INCLUDE_VXBUS   \
                    DRV_BUS_FDT_ROOT
}

