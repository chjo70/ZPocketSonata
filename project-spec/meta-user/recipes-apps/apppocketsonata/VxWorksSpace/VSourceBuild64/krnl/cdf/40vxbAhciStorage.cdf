/* 40vxbAhciStorage.cdf - Component Definition file for AHCI sata controller */

/*
 * Copyright (c) 2011, 2015-2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*

modification history

--------------------
23jan17,mw1  add INCLUDE_CACHE_DMA32_LIB in IA32_PAE (V7STO-764)
19may16,hma  add the description for DRV_STORAGE_ATA_HOST (V7STO-628)
28mar16,hma  add the sata support (US75803)
06mar14,m_y  add fsl ahci component
13feb14,m_y  add LP64 support for VXW7-1642
23may13,m_y  created

*/

Component       INCLUDE_DRV_STORAGE_AHCI {
    NAME        AHCI SATA controller
    SYNOPSIS    Supports Ahci controllers
    MODULES     vxbAhciStorage.o
    _CHILDREN   FOLDER_BDM
    _INIT_ORDER hardWareInterFaceBusInit
    PROTOTYPE   void vxbAhciStorageRegister(void);
    INIT_RTN    vxbAhciStorageRegister();
    REQUIRES    INCLUDE_PCI_BUS      \
                INCLUDE_VXBUS_DISK   \
                INCLUDE_FS_MONITOR
    INIT_AFTER  INCLUDE_PCI_BUS
}

#if defined (_WRS_CONFIG_LP64) || defined (_WRS_CONFIG_IA32_PAE)
Component INCLUDE_DRV_STORAGE_AHCI {
    REQUIRES += INCLUDE_CACHE_DMA32_LIB
}
#endif    /* _WRS_CONFIG_LP64 || _WRS_CONFIG_IA32_PAE */

Component       PCI_DRV_STORAGE_AHCI {
    NAME        AHCI SATA Controller
    SYNOPSIS    Ahci PCI controller driver
    LINK_SYMS   vxbSataPciDrv
    REQUIRES    INCLUDE_VXBUS
    _CHILDREN   FOLDER_BDM
}

#if defined (_WRS_CONFIG_LP64) || defined (_WRS_CONFIG_IA32_PAE)
Component PCI_DRV_STORAGE_AHCI {
    REQUIRES += INCLUDE_CACHE_DMA32_LIB
}
#endif    /* _WRS_CONFIG_LP64 || _WRS_CONFIG_IA32_PAE */

Component FDT_DRV_STORAGE_FSLAHCI
    {
    NAME        FSL AHCI SATA Controller
    SYNOPSIS    FSL AHCI Serial ATA controllers
    LINK_SYMS   vxbSataFdtDrv
    REQUIRES    INCLUDE_VXBUS \
                INCLUDE_WATCHDOGS_CREATE_DELETE
    _CHILDREN   FOLDER_BDM
    }

#if defined (_WRS_CONFIG_LP64) || defined (_WRS_CONFIG_IA32_PAE)
Component FDT_DRV_STORAGE_FSLAHCI {
    REQUIRES += INCLUDE_CACHE_DMA32_LIB
}
#endif    /* _WRS_CONFIG_LP64 || _WRS_CONFIG_IA32_PAE */


Component DRV_STORAGE_ATA_HOST
    {
    NAME        SATA controller
    SYNOPSIS    Serial ATA controllers includes the following components: \
                DRV_STORAGE_SI31XX , FDT_DRV_STORAGE_FSLSATA, \
                FDT_DRV_STORAGE_FSLAHCI, PCI_DRV_STORAGE_AHCI .\
                The device name may change depending on the port index.
    LINK_SYMS   vxbSataPciDrv 
    REQUIRES    INCLUDE_VXBUS \
                INCLUDE_WATCHDOGS_CREATE_DELETE
    _CHILDREN   FOLDER_BDM
    }

#ifdef _WRS_CONFIG_FDT      
Component DRV_STORAGE_ATA_HOST {
    LINK_SYMS += vxbSataFdtDrv
}
#endif                

#if defined (_WRS_CONFIG_LP64) || defined (_WRS_CONFIG_IA32_PAE)
Component DRV_STORAGE_ATA_HOST {
    REQUIRES += INCLUDE_CACHE_DMA32_LIB
}
#endif    /* _WRS_CONFIG_LP64 || _WRS_CONFIG_IA32_PAE */

