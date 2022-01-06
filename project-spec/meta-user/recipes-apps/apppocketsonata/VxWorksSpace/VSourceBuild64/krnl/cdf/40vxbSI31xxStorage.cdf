/* 40vxbSI31xxStorage.cdf - Component Definition file for 
   Silicon Image 3124/3132 Sata controller */
                                                                                
/*
 * Copyright (c) 2007,2014, 2016 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

                                                                                
/*
modification history
--------------------
28mar16,hma  add the sata support (US75803)
31mar14,m_y add DRV_STORAGE_SI31XX component for new vxbus driver 
13feb14,m_y clean cdf 
01b,15sep08,pmr  fix typo in SYNOPSIS (WIND00130404)
01a,01mar07,dee  written

*/

#ifdef _WRS_CONFIG_VXBUS_LEGACY
Component       DRV_STORAGE_SI31XX {
    NAME             Silicon Image 31xx SATA Controller
    SYNOPSIS         Supports 3124 and 3132 Silicon Image Serial ATA controllers
    MODULES          vxbSI31xxStorage.o
    _CHILDREN        FOLDER_BDM
    _INIT_ORDER      hardWareInterFaceBusInit
    PROTOTYPE	     void vxbSI31xxStorageRegister(void);
    INIT_RTN         vxbSI31xxStorageRegister();
    REQUIRES         INCLUDE_PCI_BUS \
                     INCLUDE_VXBUS
    INIT_AFTER       INCLUDE_PCI_BUS
}
#endif


#ifdef _WRS_CONFIG_VXBUS
Component       DRV_STORAGE_SI31XX 
    {
    NAME        Silicon Image 31xx SATA Controller
    SYNOPSIS    Supports 3124 and 3132 Silicon Image Serial ATA controllers
    LINK_SYMS   vxbSataPciDrv
    REQUIRES    INCLUDE_VXBUS \
                INCLUDE_SEM_READ_WRITE
    _CHILDREN   FOLDER_BDM
    }
#endif
