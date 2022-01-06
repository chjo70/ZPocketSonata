/* 40vxbGpmi.cdf - Component Definition file for IMX GPMI NAND controller */

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
05may14,ywu  add NAND flash support for imx6 AI. (US34699)
*/

Component DRV_VXB_GPMI {
    NAME        IMX GPMI NAND controller VxBus Driver
    SYNOPSIS    IMX GPMI NAND controller VxBus Driver
    MODULES     vxbGpmi.o
    _CHILDREN   FOLDER_FLASH
#ifndef _WRS_CONFIG_VXBUS_LEGACY
    LINK_SYMS   vxbFdtGpmiDrv
    _INIT_ORDER usrRoot
    REQUIRES    INCLUDE_VXBUS
#endif
}

