/* 40vxbPiixStorage.cdf - Component Definition file for 
   Intel PIIX sata controller */
                                                                                
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
28mar16,hma  add the sata support (US75803)
09nov15,hma  add fdt component for PIIX
11sep11,e_d  derived from 40vxbIntelIchStorage.cdf/01c.
*/

Component       INCLUDE_DRV_STORAGE_PIIX {
    NAME        Intel PIIX SATA Controller
    SYNOPSIS     Supports 82801 Intel Serial/Parallel ATA controllers
#ifdef _WRS_CONFIG_VXBUS_LEGACY    
    MODULES     vxbPiixStorage.o
    _CHILDREN   FOLDER_BDM
    _INIT_ORDER hardWareInterFaceBusInit
    PROTOTYPE   void vxbIntelIchStorageRegister(void);
    INIT_RTN    vxbPiixStorageRegister();
    REQUIRES    INCLUDE_PCI_BUS \
                INCLUDE_VXBUS \
                INCLUDE_FS_MONITOR \
                INCLUDE_DMA_SYS
    INIT_AFTER  INCLUDE_PCI_BUS
#else
    LINK_SYMS   vxbSataPciDrv
    REQUIRES    INCLUDE_VXBUS
    _CHILDREN   FOLDER_BDM
#endif
}

#if defined (_WRS_CONFIG_LP64) || defined (_WRS_CONFIG_IA32_PAE)
Component       INCLUDE_DRV_STORAGE_PIIX {
    REQUIRES    += INCLUDE_CACHE_DMA32_LIB
}
#endif    /* _WRS_CONFIG_LP64 || _WRS_CONFIG_IA32_PAE */

