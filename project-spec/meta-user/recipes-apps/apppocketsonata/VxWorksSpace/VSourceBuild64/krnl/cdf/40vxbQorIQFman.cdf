/* 40QorIQFman.cdf - Freescale QorIQ Frame Manager driver file */

/*
 * Copyright (c) 2014, 2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River License agreement.
 */

/*
modification history
--------------------
06jun17,wch added support for ARM (F8333)
25apr14,fao created
*/

Component DRV_RESOURCE_QORIQFMAN {
    NAME        Freescale QORIQ Frame Manager (FMan) resource driver
    SYNOPSIS    Use this component to add support for QORIQ FMan.
    _CHILDREN   FOLDER_NET_END_DRV
    MODULES     vxbQorIQFman.o
    LINK_SYMS   fmanDrv
}
