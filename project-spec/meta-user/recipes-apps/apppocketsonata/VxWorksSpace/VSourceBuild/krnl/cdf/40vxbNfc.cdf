/* 40vxbNfc.cdf - Component Definition file for vybrid NFC NAND controller */

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
12aug14,e_d  written.
*/

Component DRV_VXB_NFC {
    NAME        VYBRID NAND controller VxBus Driver
    SYNOPSIS    VYBRID NAND controller VxBus Driver
    MODULES     vxbNfc.o
    _CHILDREN   FOLDER_FLASH
    LINK_SYMS   vxbFdtNfcDrv
    _INIT_ORDER usrRoot
    REQUIRES    INCLUDE_VXBUS
}

