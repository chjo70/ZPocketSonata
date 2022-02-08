/* 40vxbGpmc.cdf - Component Definition file for GPMC NAND Flash controller */

/*
 * Copyright (c) 2012, 2014 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01d,10feb14,ywu  fix improper use of _WRS_CONFIG_FDT
01c,21jan14,ywu  adopt to vxBus gen2
01b,16jan14,ywu  disabled for vxBus gen2 temporarily
01a,22sep12,x_z  written.
*/

Component DRV_VXB_GPMC {
    NAME        GPMC NAND Flash controller VxBus Driver
    SYNOPSIS    GPMC NAND Flash controller VxBus Driver
    MODULES     vxbGpmc.o
    _CHILDREN   FOLDER_FLASH
#ifndef _WRS_CONFIG_VXBUS_LEGACY
    LINK_SYMS   vxbFdtGpmcDrv
    _INIT_ORDER usrRoot
    REQUIRES    INCLUDE_VXBUS
#else
    INIT_RTN    vxbGpmcRegister();
    PROTOTYPE   void vxbGpmcRegister (void);
    _INIT_ORDER hardWareInterFaceBusInit
    REQUIRES    INCLUDE_PLB_BUS     \
                INCLUDE_PARAM_SYS
    INIT_AFTER  INCLUDE_PLB_BUS
#endif
}

