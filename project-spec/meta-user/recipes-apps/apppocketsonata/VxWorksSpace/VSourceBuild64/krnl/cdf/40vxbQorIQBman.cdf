/* 40QorIQBman.cdf - Freescale QorIQ Buffer Manager driver file */

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
02may17,wch  added support for ARM (F8333)
25apr14,fao  created
*/

Component DRV_RESOURCE_QORIQBMAN {
    NAME        Freescale QORIQ Buffer Manager (BMan) resource driver
    SYNOPSIS    Use this component to add support for QORIQ BMan.
    _CHILDREN   FOLDER_NET_END_DRV
    MODULES     vxbQorIQBman.o vxbQorIQBmanPortal.o
    LINK_SYMS   bmanDrv bportalDrv
}
