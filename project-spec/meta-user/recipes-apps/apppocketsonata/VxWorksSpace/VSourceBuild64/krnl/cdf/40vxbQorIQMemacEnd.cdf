/* 40vxbQorIQMemacEnd.cdf - Component configuration file */

/*
 * Copyright (c) 2014-2015, 2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River License agreement.
 */

/*
modification history
--------------------
25may17,wch remove dependency on DRV_FSL_LAW for ARM (F8333)
29oct15,p_x remove dependency on DRV_FPGA_FDT_FSL_QORIQ. (V7PRO-2482)
05aug14,x_z replaced DRV_FSL_QIXIS with DRV_FPGA_FDT_FSL_QORIQ. (F804)
06jun14,fao add DRV_QORIQMEMAC_MDIO (V7PRO-972)
25apr14,fao created
*/

#ifdef _WRS_CONFIG_ARCH_ppc
Component   DRV_VXBEND_QORIQMEMAC {
    NAME        mEMAC VxBus Enhanced Network Driver
    SYNOPSIS    Use this component to add support for QORIQ mEMAC END.
    _CHILDREN   FOLDER_NET_END_DRV
    MODULES     vxbQorIQMemacEnd.o
    LINK_SYMS   memacDrv
    REQUIRES    INCLUDE_DMA_SYS         \
                INCLUDE_END             \
                DRV_RESOURCE_QORIQBMAN  \
                DRV_RESOURCE_QORIQQMAN  \
                DRV_RESOURCE_QORIQFMAN  \
                DRV_FSL_LAW
}
#endif /* _WRS_CONFIG_ARCH_ppc */

#ifdef _WRS_CONFIG_ARCH_arm
Component   DRV_VXBEND_QORIQMEMAC {
    NAME        mEMAC VxBus Enhanced Network Driver
    SYNOPSIS    Use this component to add support for QORIQ mEMAC END.
    _CHILDREN   FOLDER_NET_END_DRV
    MODULES     vxbQorIQMemacEnd.o
    LINK_SYMS   memacDrv
    REQUIRES    INCLUDE_DMA_SYS         \
                INCLUDE_END             \
                DRV_RESOURCE_QORIQBMAN  \
                DRV_RESOURCE_QORIQQMAN  \
                DRV_RESOURCE_QORIQFMAN  
}
#endif /* _WRS_CONFIG_ARCH_arm */
 
Component   DRV_QORIQMEMAC_MDIO {
     NAME        mEMAC MDIO driver
     SYNOPSIS    Use this component to add support for QORIQ mEMAC MDIO.
     _CHILDREN   FOLDER_NET_END_DRV
     MODULES     vxbQorIQMemacMdio.o
     LINK_SYMS   vxbMemacMdioDrv
     REQUIRES    INCLUDE_VXBUS          \
                 INCLUDE_MII_SYS
}
