/* 40vxbQorIQDtsecEnd.cdf - Component configuration file */

/*
 * Copyright (c) 2014 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River License agreement.
 */

/*
modification history
--------------------
25jun14,fao created
*/

Component   DRV_VXBEND_QORIQDTSEC {
    NAME        DTSEC VxBus Enhanced Network Driver
    SYNOPSIS    DTSEC VxBus Enhanced Network Driver
    _CHILDREN   FOLDER_NET_END_DRV
    MODULES     vxbQorIQDtsecEnd.o
    LINK_SYMS   vxbDtsecEndDrv
    REQUIRES    INCLUDE_DMA_SYS         \
                INCLUDE_END             \
                DRV_RESOURCE_QORIQBMAN  \
                DRV_RESOURCE_QORIQQMAN  \
                DRV_RESOURCE_QORIQFMAN  \
                DRV_FSL_LAW 
}
 
Component   DRV_QORIQDTSEC_MDIO {
     NAME        DTSEC MDIO driver
     SYNOPSIS    DTSEC MDIO driver
     _CHILDREN   FOLDER_NET_END_DRV
     MODULES     vxbQorIQDtsecMdio.o
     LINK_SYMS   vxbDtsecMdioDrv
     REQUIRES    INCLUDE_VXBUS          \
                 DRV_FPGA_FDT_FSL_QORIQ \
                 INCLUDE_MII_SYS
}
