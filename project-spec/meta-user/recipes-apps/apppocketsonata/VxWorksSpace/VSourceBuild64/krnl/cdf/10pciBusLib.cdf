/* 10pciBusLib.cdf - Component Definition file for m85xx timer */

/*
 * Copyright (c) 2013-2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
16jun17,mjn  text updates (F8862)
08jan16,y_y  add INCLUDE_PCIE_AER component. (F4655)
07jan16,l_z  add initialize order for PCI component. (V7PRO-2529)
08sep15,wap  break forced component dependency between VXB_PCI_MSI and
             INCLUDE_INTCTLR_DYNAMIC_LIB
10aug15,wap  add components for PCI bus and MSI components
08jun15,wap  add INCLUDE_PCI_BUS_AUTOCONF component (F3973)
08may14,l_z  change the init routine name. (US37630)
09apr14,ylu  corrected the LINK_SYMS of INCLUDE_PCI_SHOW.
23oct13,l_z  created
*/

Folder FOLDER_BUSLIB_PCI {                    
    NAME            VxBus PCI bus
    SYNOPSIS        This folder contains PCI bus support components.
    _CHILDREN       FOLDER_SUBSYSTEM
}  

Component INCLUDE_PCI_BUS {
    NAME            VxBus PCI subsystem library
    SYNOPSIS        This component provides the VxBus PCI subsystem library, which provides \
                    platform-independent bus scan and helper functions used by \
                    the PCI host controller drivers and individual function drivers.
    MODULES         vxbPci.o
    PROTOTYPE       STATUS vxbPciInit (void);
    INIT_RTN        vxbPciInit ();
    _INIT_ORDER     usrRoot
    INIT_BEFORE     INCLUDE_VXBUS
    _CHILDREN       FOLDER_BUSLIB_PCI
}

Component INCLUDE_PCI_SHOW {
    NAME            Bus show 
    SYNOPSIS        This component provides support for the PC show functions: \
                    vxbPciCtrlShow(), vxbPciDeviceShow(), vxbPciFuncShow(), \
                    and vxbPciTopoShow().
    MODULES         vxbPciShow.o
    PROTOTYPE       void vxbPciShowInit (void);
    INIT_RTN        vxbPciShowInit ();
    _INIT_ORDER     usrRoot
    REQUIRES        INCLUDE_PCI_BUS
    _CHILDREN       FOLDER_BUSLIB_PCI
}

Component INCLUDE_PCI_MSI {
    NAME            MSI/MSI-X interrupt library
    SYNOPSIS        This component provides The VxBus PCI MSI/MSI-X library, which provides support routines \
                    for handling MSI and MSI-X interrupts with PCI devices.
    MODULES         vxbPciMsi.o
    PROTOTYPE       STATUS vxbPciMsiInit (void);
    INIT_RTN        vxbPciMsiInit ();
    _INIT_ORDER     usrRoot
    INIT_BEFORE     INCLUDE_VXBUS
    REQUIRES        INCLUDE_PCI_BUS
    _CHILDREN       FOLDER_BUSLIB_PCI
}

Component INCLUDE_PCI_AUTOCONF {
    NAME            Auto-configuration library
    SYNOPSIS        This component provides the VxBus PCI auto-configuration library,
                    which allows VxBus to \
                    allocate and assign BAR and IRQ values for PCI devices \
                    on platforms where this operation is not already performed \
                    by the system firmware.
    MODULES         vxbPciAutoCfg.o
    PROTOTYPE       STATUS vxbPciConfigInit (void);
    INIT_RTN        vxbPciConfigInit ();
    _INIT_ORDER     usrRoot
    INIT_BEFORE     INCLUDE_PCI_BUS
    REQUIRES        INCLUDE_PCI_BUS
    _CHILDREN       FOLDER_BUSLIB_PCI
}

Component INCLUDE_PCIE_AER {
    NAME            Express advanced error reporting capability
    SYNOPSIS        This component includes PCI Express root port advanced \
                    error reporting capability support.
    MODULES         vxbPcieAer.o
    PROTOTYPE       void vxbPcieAerInit (void);
    INIT_RTN        vxbPcieAerInit ();
    _INIT_ORDER     usrRoot
    REQUIRES        INCLUDE_PCI_BUS         \
                    INCLUDE_ISR_DEFER
    _CHILDREN       FOLDER_BUSLIB_PCI
    INIT_AFTER      INCLUDE_PCI_BUS
}

