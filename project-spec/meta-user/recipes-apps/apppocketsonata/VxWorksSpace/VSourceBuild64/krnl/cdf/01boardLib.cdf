/* 00boardLib.cdf - Board library component description file */

/*
 * Copyright (c) 2012-2014, 2016-2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify, or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
18oct17,wap  Clean up initialization order dependency (V7COR-5320)
16aug17,mze  resolving issue with multi version layers and cdf Folder changes
14jun17,mjn  text updates (F8862)
27oct16,c_l  added missing call sysIntEnableFlagSet (V7PRO-3373)
21apr16,emj  CERT: Update to produce partially linked objects (US79607)
03jul14,j_l  US41956 - Implement GEN2 bootApp network boot
21may14,cww  added missing folders from previous change (V7COR-1176)
27mar14,cww  added required components from 00bsp.cdf (V7COR-907)
06mar14,j_l  US18115 - additional changes for IA
24feb14,x_z  added KERNEL_LOAD_ADRS. (VXW7-1416)
20feb14,x_z  removed unused VSB option.
09oct13,x_z  cleaned.
23may13,x_z  created
*/

Folder  FOLDER_BOARD_LIB {
        NAME        Board library
        SYNOPSIS    This folder contains the board subsystem to supply interfaces to BSP \
                    for other OS components.
        _CHILDREN   FOLDER_KERNEL
}

#if defined (_WRS_CONFIG_PPC_BASE__FOLDER_PERIPHERALS_PPC) || \
    defined(_WRS_CONFIG_VXBUS_DRV__FOLDER_PERIPHERALS_VXBUS) || \
    defined(_WRS_CONFIG_VXBUS_LEGACY__FOLDER_PERIPHERALS_VXBUS_LEGACY) || \
    defined(_WRS_CONFIG_ARM_ARMBASE__FOLDER_PERIPHERALS_ARM) || \
    defined(_WRS_CONFIG_IA_KERNEL__FOLDER_PERIPHERALS_IA) || \
    defined(_WRS_CONFIG_VXSIM_KERNEL__FOLDER_PERIPHERALS_VXSIM)
Folder FOLDER_PERIPHERALS {
    NAME        Peripherals
    SYNOPSIS    Peripheral components
    _CHILDREN   FOLDER_FPP
}
#endif

Folder  FOLDER_HARDWARE {
    NAME        Hardware
    SYNOPSIS    This folder contains hardware components.
    CHILDREN    FOLDER_MEMORY       \
                FOLDER_BSP_CONFIG
    DEFAULTS    FOLDER_MEMORY       \
                FOLDER_BSP_CONFIG
}

Folder  FOLDER_BSP_CONFIG {
    NAME            BSP configuration variants
    CHILDREN        INCLUDE_BSP_MACROS
    DEFAULTS        INCLUDE_BSP_MACROS
}


Folder FOLDER_FPP {
    NAME        Floating point libraries
	SYNOPSIS	This folder contains floating point libraries.
    CHILDREN    INCLUDE_SW_FP INCLUDE_HW_FP
    _CHILDREN   FOLDER_SUBSYSTEM
}

Component INCLUDE_BOARD_LIB_INIT {
    NAME            Initialize board library
    SYNOPSIS        This component provides a function to initialize the board subsystem, supplying BSP access APIs.
    CONFIGLETTES    usrBoardLibInit.c
#ifndef _WRS_CONFIG_CERT_KERNEL_OBJECT
    MODULES         boardLib.o
#else
        _REQUIRES INCLUDE_KERNEL
#endif
    HDR_FILES       boardLib.h
    PROTOTYPE       void usrBoardLibInit (void );
    INIT_RTN        usrBoardLibInit();
    _CHILDREN       FOLDER_BOARD_LIB
    REQUIRES        INCLUDE_BOARD_INIT
    _REQUIRES       INCLUDE_KERNEL
    _INIT_ORDER     usrInit
    INIT_AFTER      INCLUDE_SYS_START
    INIT_BEFORE     INCLUDE_CPU_INIT
}

Component INCLUDE_BOARD_INIT {
    NAME        Initialize board
    SYNOPSIS	This component provides a function to initialize the board.
    INIT_RTN	boardInit();
    HDR_FILES	sysLib.h
    _CHILDREN   FOLDER_BOARD_LIB
    _REQUIRES       INCLUDE_KERNEL
    _INIT_ORDER     usrRoot
#if (defined _WRS_CONFIG_ARCH_i86)
    INIT_AFTER      INCLUDE_SYSHW_INIT_1
#endif /* (defined _WRS_CONFIG_ARCH_i86) */
    INIT_BEFORE     INCLUDE_VXBUS
}

Component INCLUDE_BSP_MACROS {
    NAME            General BSP macros
    SYNOPSIS        This component acts as a placeholder for general BSP macros.
    CFG_PARAMS      DEFAULT_BOOT_LINE
    INCLUDE_WHEN    INCLUDE_KERNEL
}

Component INCLUDE_MEMORY_CONFIG {
    NAME            BSP memory configuration
    SYNOPSIS        This component provides a memory configuration parameter for the BSP.
    INCLUDE_WHEN    INCLUDE_KERNEL
    CFG_PARAMS      LOCAL_MEM_LOCAL_ADRS    \
                    LOCAL_MEM_SIZE          \
                    LOCAL_MEM_AUTOSIZE      \
                    LOCAL_MEM_PHYS_ADRS     \
                    VEC_BASE_ADRS           \
                    EXC_MSG_OFFSET          \
                    EXC_MSG_ADRS            \
                    BOOT_LINE_SIZE          \
                    BOOT_LINE_ADRS          \
                    BOOT_LINE_OFFSET        \
                    RESERVED                \
                    FREE_RAM_ADRS           \
                    ROM_WARM_ADRS           \
                    STACK_SAVE              \
                    RAM_HIGH_ADRS           \
                    RAM_LOW_ADRS            \
                    ROM_BASE_ADRS           \
                    ROM_TEXT_ADRS           \
                    ROM_SIZE
}

#ifdef _WRS_CONFIG_FDT
Parameter KERNEL_LOAD_ADRS {
    NAME        Runtime kernel load address
    SYNOPSIS    This parameter defines the address for the VxWorks kernel to load the uVxWorks image.
    DEFAULT     0x00100000
    _CFG_PARAMS INCLUDE_MEMORY_CONFIG 
}
#endif /* _WRS_CONFIG_FDT */

Parameter STACK_SAVE {
    NAME        Stack size
    SYNOPSIS    This parameter specifies the amount of stack to reserve (bytes) for rom code.
    DEFAULT     0x40
}

Parameter RAM_LOW_ADRS {
    NAME        RAM low address
    SYNOPSIS    This parameter specifies the address at which to load VxWorks.
    DEFAULT     0x01000
}

Parameter EXC_MSG_OFFSET {
    NAME        Exception message offset
    SYNOPSIS    This parameter specifies the exception message offset.
    DEFAULT     0x800
}

Parameter EXC_MSG_ADRS {
    NAME        Exception message address
    SYNOPSIS    This parameter specifies the exception message address.
    DEFAULT     (LOCAL_MEM_LOCAL_ADRS + EXC_MSG_OFFSET)
}

/* Components to support post-kernel hardware init */

#if (defined _WRS_CONFIG_ARCH_i86)
Component INCLUDE_DEFERRED_INTERRUPT_ENABLE {
    NAME            Deferred interrupt enable
    SYNOPSIS        This component enables interrupts at an appropriate point in the root task.
    _CHILDREN       FOLDER_NOT_VISIBLE
    HDR_FILES       private/intLibP.h
#ifndef _WRS_CONFIG_VXBUS_LEGACY
    PROTOTYPE void sysIntEnableFlagSet();
    INIT_RTN        intStartupUnlock (); sysIntEnableFlagSet();
#else /* _WRS_CONFIG_VXBUS_LEGACY */
    INIT_RTN        intStartupUnlock ();
#endif /* !_WRS_CONFIG_VXBUS_LEGACY */
    INCLUDE_WHEN    INCLUDE_KERNEL
}

Component INCLUDE_SYSHW_INIT_1 {
    NAME            Post-kernel BSP hardware initialization
    SYNOPSIS        This component provides an initialization function which is executed during system startup.
    _CHILDREN       FOLDER_NOT_VISIBLE
    HDR_FILES       sysLib.h
    INIT_RTN        sysHwInit1 ();
    INCLUDE_WHEN    INCLUDE_KERNEL
}
#endif /* (defined _WRS_CONFIG_ARCH_i86)     */
