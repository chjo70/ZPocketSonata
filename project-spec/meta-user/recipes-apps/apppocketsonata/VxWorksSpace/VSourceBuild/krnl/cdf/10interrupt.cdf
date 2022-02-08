/* 10interrupt.cdf - Component configuration file */

/*
 * Copyright (c) 2013-2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */
 
/*
modification history
-------------------
15jun17,mjn  text updates (F8862)
05aug16,wap  Add component for vxbIntLib and a VXB_MAX_INTR_DEFER
             parameter to control the size of the vxbIntDeferTbl
             array (V7PRO-3177)
26apr16,emj  CERT: Update to produce partially linked objects
15apr16,l_z  fix typo for FOLDER_SUBSYSTEM. (V7PRO-3016)
02feb16,wap  Add extra argument to vxbIsrHandlerInit()
26jan16,wap  Add INCLUDE_INT_SHOW component
08sep15,wap  use INCLUDE_WHEN to bring in INCLUDE_INTCTLR_DYNAMIC_LIB when
             INCLUDE_PCI_MSI is present
09apr14,ylu  added INCLUDE_ISR_HANDLER_INIT component.
14sep13,y_y  add INCLUDE_INTCTLR_DYNAMIC_LIB component
16jul13,l_z  created for VxBus GEN2
*/

Folder FOLDER_SUB_INTERRUPT {
    NAME            Interrupt
    SYNOPSIS        This folder contains the VxBus dynamic interrupt controller that supports Message Signaled Interrupts (MSI).
    _CHILDREN       FOLDER_SUBSYSTEM
}      

Component INCLUDE_ISR_HANDLER_INIT {
    NAME            VxBus ISR handler module initialization
    SYNOPSIS        This component supports provides the VxBus ISR handler module \
                    initialization function.
    HDR_FILES       subsys/int/vxbIsrHandler.h
    PROTOTYPE       STATUS vxbIsrHandlerInit (UINT32, UINT32);
    INIT_RTN        vxbIsrHandlerInit (VXB_MAX_INTR_VEC, VXB_MAX_INTR_CHAIN);
    CFG_PARAMS      VXB_MAX_INTR_VEC \
                    VXB_MAX_INTR_CHAIN
    INCLUDE_WHEN    INCLUDE_VXBUS
    _INIT_ORDER     usrRoot
    INIT_BEFORE     INCLUDE_VXBUS
    _CHILDREN       FOLDER_SUB_INTERRUPT
}

Component INCLUDE_INT_LIB_INIT {
    NAME            VxBus interrupt library initialization
    SYNOPSIS        This component includes support for VxBus interrupt library \
                    initialization.
    HDR_FILES       subsys/int/vxbIntLib.h
    PROTOTYPE       STATUS vxbIntLibInit (UINT32);
    INIT_RTN        vxbIntLibInit (VXB_MAX_INTR_DEFER);
    CFG_PARAMS      VXB_MAX_INTR_DEFER
    INCLUDE_WHEN    INCLUDE_VXBUS
    _INIT_ORDER     usrRoot
    INIT_BEFORE     INCLUDE_VXBUS
    _CHILDREN       FOLDER_SUB_INTERRUPT
    }

Parameter VXB_MAX_INTR_VEC {
    NAME            Maximum interrupt vector table slots
    SYNOPSIS        This parameter specifies the maximum number of interrupt \
                    vector table slots.
    TYPE            UINT32
    DEFAULT         1024
}

Parameter VXB_MAX_INTR_CHAIN {
    NAME            Maximum interrupt chaining entries
    SYNOPSIS        This parameter specifies the maximum number of interrupt \
                    chaining entries.
    TYPE            UINT32
    DEFAULT         256
}

Parameter VXB_MAX_INTR_DEFER {
    NAME            Maximum interrupt operation deferral entries
    SYNOPSIS        This parameter specifies the maximum number of interrupt \
                    operation deferral entries.
    TYPE            UINT32
    DEFAULT         256
}

Component INCLUDE_INT_SHOW {
    NAME            VxBus interrupt library show routines
    SYNOPSIS        This component includes the vxbIntShow routine in your \
                    project. It provides the interfaces that can be used for \
                    displaying information about the interrupt subsystem.
    LINK_SYMS       vxbIntShowInit
    REQUIRES        INCLUDE_VXBUS
    _CHILDREN       FOLDER_SUB_INTERRUPT
}

Component INCLUDE_ISR_HANDLER_SHOW {
    NAME            VxBus ISR handler show routines
    SYNOPSIS        This component includes the VxBus ISR handler show routines \
                    in your system. 
    LINK_SYMS       vxbIsrHandlerShowInit
    REQUIRES        INCLUDE_VXBUS
    _CHILDREN       FOLDER_SUB_INTERRUPT
}

Component INCLUDE_INTCTLR_DYNAMIC_LIB {
    NAME            VxBus dynamic interrupt controller library
    SYNOPSIS        This component includes the VxBus dynamic interrupt controller \
                    that supports Message Signaled Interrupts (MSI). 
    PROTOTYPE       STATUS vxDyncIntLibInit (void);
    INCLUDE_WHEN    INCLUDE_PCI_MSI
    INIT_RTN        vxDyncIntLibInit();
    _INIT_ORDER     usrRoot
    INIT_BEFORE     INCLUDE_VXBUS
    _CHILDREN       FOLDER_SUB_INTERRUPT
}

Component INCLUDE_VXIPI {
    NAME            VxBus IPI library
    SYNOPSIS        This component includes inter-processor interrupts for symmetric \
                    multiprocessing (SMP) and asymmetric multiprocessing (AMP).
    PROTOTYPE       STATUS vxIpiLibInit (void);
    INIT_RTN        vxIpiLibInit ();
#ifndef _WRS_CONFIG_CERT_KERNEL_OBJECT
    MODULES         vxIpiLib.o
#else
    _REQUIRES       INCLUDE_KERNEL
#endif
    INCLUDE_WHEN    INCLUDE_CPC
    _INIT_ORDER     usrRoot
    INIT_BEFORE     INCLUDE_VXBUS
    _CHILDREN       FOLDER_SUB_INTERRUPT
}

