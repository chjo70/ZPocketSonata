/* 40vxbEmif16.cdf - Component Definition file for EMIF16 NAND Flash controller */

/*
 * Copyright (c) 2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
20may15,sye  written. (US54319)
*/

Component DRV_VXB_EMIF16_NAND {
    NAME        TI EMIF16 NAND Flash controller VxBus Driver
    SYNOPSIS    TI EMIF16 NAND Flash controller VxBus Driver
    MODULES     vxbEmif16.o
    _CHILDREN   FOLDER_FLASH
    LINK_SYMS   vxbFdtEmif16Drv
    _INIT_ORDER usrRoot
    REQUIRES    INCLUDE_VXBUS 
}

