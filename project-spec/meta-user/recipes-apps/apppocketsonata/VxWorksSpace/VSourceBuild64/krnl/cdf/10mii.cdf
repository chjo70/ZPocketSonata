/* 10mii.cdf - mii bus CDF file */

/*
 * Copyright (c) 2013-2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River License agreement.
 */

/*
modification history
--------------------
31oct17,g_x  added INCLUDE_MARVELL_PHY (V7PRO-4024)
19dec16,swu  added TI DP83867IR support (F7388)
11oct16,g_x  Add INCLUDE_RTL8211PHY. (F6411)
28mar16,wap  Update component names for improved readability
15mar16,wap  Add INCLUDE_GENERICMMDPHY and INCLUDE_FSLSGMII_PHY (F1921)
13oct15,fao  add INCLUDE_RTL8169PHY (US65600)
26aug15,m_w  added INCLUDE_MII_MONITOR_TASK. (V7PRO-2370)
10oct14,y_y  add INCLUDE_BITBANG_MDIO,INCLUDE_BCM52XXPHY (US41759)
22sep14,m_w  add INCLUDE_MICREL_PHY (V7PRO-1195)
27aug14,sye  added INCLUDE_AR803X_PHY. (US44767)
22aug14,yjw  add freescale FEC MDIO (US40534)
06jun14,fao  remove DRV_QORIQMEMAC_MDIO (V7PRO-972)
12may14,l_z  add GEI support. (US33490)
25apr14,fao  correct the components INCLUDE_DUMMY_MDIO and 
             INCLUDE_TSEC_MDIO.
09apr14,ylu  changed the MODULES of INCLUDE_GENERICPHY.
23jan14,ylu  fixed coverity and compling issues.
20dec13,hll  Add _CHILDREN for INCLUDE_GENERICPHY, INCLUDE_DUMMY_MDIO and
             INCLUDE_TSEC_MDIO.(VXW7-1219)
23may13,x_z  created
*/

Component   INCLUDE_MII_SYS {
        NAME            MII bus subsystem
        SYNOPSIS        Includes the MII bus subsystem. 
        PROTOTYPE       extern void miiBusLibInit (void);
        _CHILDREN       FOLDER_NOT_VISIBLE
        INIT_RTN        miiBusLibInit();
        MODULES         vxbMiiLib.o
        _INIT_ORDER     usrRoot
        REQUIRES        INCLUDE_VXBUS \
                        INCLUDE_MII_MONITOR_TASK
        INIT_BEFORE     INCLUDE_VXBUS
}

Component   INCLUDE_MII_FDT_SYS {
        NAME            MII bus FDT subsystem
        SYMOPSIS        Includes the MII bus flattened device tree (FDT) \
                        support routines.
        _CHILDREN       FOLDER_NOT_VISIBLE
        INIT_RTN        miiBusFdtLibInit();
        HDR_FILES       miiBus.h
        MODULES         miiBus.o
        _INIT_ORDER     usrRoot
        INCLUDE_WHEN    INCLUDE_FDT_LIB
        INIT_BEFORE     INCLUDE_MII_SYS
}

Component   INCLUDE_MII_MONITOR_TASK {
        NAME            MII bus monitor task
        SYNOPSIS        This component spawns the MII bus monitor task.
        PROTOTYPE       extern void miiBusMonitorTaskInit (void);
        _CHILDREN       FOLDER_NOT_VISIBLE
        INIT_RTN        miiBusMonitorTaskInit();
        _INIT_ORDER     usrRoot  
        INIT_AFTER      usrClkInit 
        INIT_BEFORE     usrNetworkInit
}

Component   INCLUDE_GENERICPHY {
        NAME            Generic Ethernet PHY driver
        SYNOPSIS        This component implements the VxBus driver for a generic \
                        Ethernet PHY device.
        _CHILDREN       FOLDER_NET_END_DRV
        MODULES         vxbGenericPhy.o
        LINK_SYMS       genPhyDrv
        REQUIRES        INCLUDE_MII_SYS
}

Component   INCLUDE_GENERIC_MMD_PHY {
        NAME            Generic clause 45 Ethernet PHY Driver
        SYNOPSIS        This component implements the VxBus driver for a generic \
                        clause 45 Ethernet PHY device. 
        _CHILDREN       FOLDER_NET_END_DRV
        MODULES         vxbGenericMmdPhy.o
        LINK_SYMS       vxbMmdDrv
        REQUIRES        INCLUDE_MII_SYS 
}

Component   INCLUDE_FSL_SGMII_PHY {
        NAME            Freescale SGMII PHY driver
        SYNOPSIS        This component implements the VxBus driver for a Freescale \
                        SGMII PHY device.
        _CHILDREN       FOLDER_NET_END_DRV
        MODULES         vxbFslSgmiiPhy.o
        LINK_SYMS       vxbFslSgmiiDrv
        REQUIRES        INCLUDE_MII_SYS 
}          

Component   INCLUDE_AR803X_PHY {
        NAME            Qualcomm AR803X Ethernet PHY driver
        SYNOPSIS        This component implements the VxBus driver for the \
                        Qualcomm AR803X Ethernet PHY device.
        _CHILDREN       FOLDER_NET_END_DRV
        MODULES         vxbQcomAr803xPhy.o
        LINK_SYMS       ar803xPhyDrv
        REQUIRES        INCLUDE_MII_SYS
}

Component   INCLUDE_DUMMY_MDIO {
        NAME            FDT dummy MDIO Driver
        SYNOPSIS        This component implements the VxBus driver for a flattened \
                        device tree (FDT) dummy MDIO device.
        _CHILDREN       FOLDER_NET_END_DRV
        MODULES         vxbDummyMdio.o
        LINK_SYMS       dummyDrv
        REQUIRES        INCLUDE_VXBUS \
                        INCLUDE_MII_SYS
}

Component   INCLUDE_TSEC_MDIO {
        NAME            FDT tsec MDIO driver
        SYNOPSIS        This component implements the VxBus driver for a flattened \
                        device tree (FDT) tsec MDIO device.
        _CHILDREN       FOLDER_NET_END_DRV
        MODULES         vxbTsecMdio.o
        LINK_SYMS       tmDrv
        REQUIRES        INCLUDE_VXBUS \
                        INCLUDE_MII_SYS
}

Component   INCLUDE_FEC_MDIO {
        NAME            Freescale FEC MDIO driver
        SYNOPSIS        This component implements the VxBus driver for a Freescale \
                        FEC MDIO device.
        _CHILDREN       FOLDER_NET_END_DRV
        MODULES         vxbFecMdio.o
        LINK_SYMS       fecMdioDrv
        REQUIRES        INCLUDE_VXBUS \
                        INCLUDE_MII_SYS
}

Component   INCLUDE_BITBANG_MDIO {
        NAME            FDT parallel I/O port pins MDIO driver
        SYNOPSIS        This component implements the VxBus driver for a flattened \
                        device tree (FDT) parallel I/O port pins MDIO device.
        _CHILDREN       FOLDER_NET_END_DRV
        MODULES         vxbBitBangMdio.o
        LINK_SYMS       bitbangMiiDrv
        REQUIRES        INCLUDE_VXBUS \
                        INCLUDE_MII_SYS
}

Component   INCLUDE_MICREL_PHY {
        NAME            Micrel PHY driver
        SYNOPSIS        This component implements the VxBus driver for a Micrel PHY \
                        device.
        _CHILDREN       FOLDER_NET_END_DRV
        MODULES         vxbMicrelPhy.o
        LINK_SYMS       micrelPhyDrv
        REQUIRES        INCLUDE_VXBUS \
                        INCLUDE_MII_SYS
}

Component   INCLUDE_BCM52XXPHY {
        NAME            Broadcom 52xx driver
        SYNOPSIS        This component implements the VxBus driver \
                        for a Broadcom bcm52xx Ethernet PHY device. \
                        It provides the initialization and \
                        functionality routines for this device.
        _CHILDREN       FOLDER_NET_END_DRV
        MODULES         vxbBcm52xxPhy.o
        LINK_SYMS       bmtPhyDrv
        REQUIRES        INCLUDE_VXBUS \
                        INCLUDE_MII_SYS
}

Component INCLUDE_RTL8169PHY {
        NAME        RealTek RTL8169 driver
        SYNOPSIS    This component implements the VxBus driver for a \
                    RealTek RTL8169 C+ 10/100 Ethernet PHY device. 
        _CHILDREN   FOLDER_NET_END_DRV
        MODULES     vxbRtl8169Phy.o
        LINK_SYMS   rtgPhyDrv
        REQUIRES    INCLUDE_VXBUS \
                    INCLUDE_MII_SYS
}

Component INCLUDE_REALTEK_PHY {
        NAME        RealTek PHY driver
        SYNOPSIS    This component implements the VxBus driver for a \
                    RealTek 10/100/1000 Ethernet PHY device.
        _CHILDREN   FOLDER_NET_END_DRV
        MODULES     vxbRtlPhy.o
        LINK_SYMS   rtlPhyDrv
        REQUIRES    INCLUDE_VXBUS \
                    INCLUDE_MII_SYS
}

Component INCLUDE_TI_DP_PHY {
        NAME        TI DP PHY driver
        SYNOPSIS    This component implements the VxBus driver for a TI \
                    DP 10/100/1000 Ethernet PHY device.
        _CHILDREN   FOLDER_NET_END_DRV
        MODULES     vxbTiDpPhy.o
        LINK_SYMS   tiDpPhyDrv
        REQUIRES    INCLUDE_VXBUS \
                    INCLUDE_MII_SYS
}

Component INCLUDE_MARVELL_PHY {
        NAME        Marvell PHY driver
        SYNOPSIS    This component implements the VxBus driver for a \
                    Marvell Ethernet PHY device.
        _CHILDREN   FOLDER_NET_END_DRV
        MODULES     vxbMarvellPhy.o
        LINK_SYMS   marvellPhyDrv
        REQUIRES    INCLUDE_VXBUS \
                    INCLUDE_MII_SYS
}
