/* 40vxbFdtFslSataStorage.cdf - Component Definition file for Freescale sata controller */

/*
 * Copyright (c) 2013-2016 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */


/*

modification history

--------------------
28mar16,hma  add the sata support (US75803)
07may15,yjl Fix V7STO-310 "Freescale" is spelled wrong
23apr15,m_y  add LP64 support (V7RAD-68)
22feb14,m_y  remove modules to make the component avaliable
10feb14,m_y  modify definition.
23may13,m_y  created

*/


Component DRV_STORAGE_FSLSATA
    {
    NAME        FSL SATA Controller
    SYNOPSIS    FSL Serial ATA controllers
    MODULES	    vxbFslSataStorage.o
    _CHILDREN   FOLDER_BDM
    _INIT_ORDER hardWareInterFaceBusInit
    PROTOTYPE	void vxbFslSataStorageRegister(void);
    INIT_RTN    vxbFslSataStorageRegister();
    REQUIRES    INCLUDE_VXBUS \
                INCLUDE_PLB_BUS
    }

Component FDT_DRV_STORAGE_FSLSATA
    {
    NAME        FSL SATA Controller
    SYNOPSIS    FSL Serial ATA controllers
    LINK_SYMS   vxbSataFdtDrv
    REQUIRES    INCLUDE_VXBUS \
                INCLUDE_SEM_READ_WRITE
    _CHILDREN   FOLDER_BDM
    }



#ifdef    _WRS_CONFIG_LP64
Component FDT_DRV_STORAGE_FSLSATA {
    REQUIRES += INCLUDE_CACHE_DMA32_LIB
}
#endif    /* _WRS_CONFIG_LP64 */
