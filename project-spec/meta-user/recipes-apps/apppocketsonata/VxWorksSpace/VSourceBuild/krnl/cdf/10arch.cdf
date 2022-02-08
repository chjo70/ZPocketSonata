/* 01arch.cdf - PPC arch base components */

/*
 * Copyright (c) 2013-2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify, or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
19jul17,mjn  text updates (F8862)
26apr17,val  added hypot under INCLUDE_ANSI_MATH (V7COR-4843)
16dec16,cfm  removed X mmu attribute in SYS_DMA32_MEM_ATTR and moved
             INCLUDE_PROTECT_INTERRUPT_STACK to FOLDER_KERNEL_HARDENING (F7142)
31aug16,l_z  disable AIM MMU when UNIFIED_MMU_LIB is enabled. (V7PRO-3279)
16oct15,d_l  added PPC603 compat69 support. (F5384)
03mar15,jpb  increase interrupt stack size for LP64
12sep14,syt  added support for _WRS_CONFIG_PPC_60x.(F2505)
22aug14,sye  added system interrupt flag set for
             INCLUDE_DEFERRED_INTERRUPT_ENABLE. (V7PRO-1197)
30may14,h_k  added missing INCLUDE_SW_FP component definition. (V7COR-1229)
21may14,ylu  used _WRS_CONFIG_SHELL wrap the INCLUDE_ALTIVEC_MREGS component.
             (V7PRO-880)
16may14,rlp  Removed WDB references (WB4-1735).
25apr14,cww  moved SYS_MEM_DESC_NUM to boardlib
10may14,ylu  removed the SMT related components, rollback the file.(US34958)
20apr14,ylu  added the components for PPCE6500 SMT feature.(US34480)
17apr14,ylu  fixed the E6500 altivec issue.
07mar14,x_z  added AIM components. (US18830) 
24feb14,x_z  fixed orphan components.
22feb14,x_z  moved ARCH components from 20bsp.cdf and fixed INCLUDE_HW_FP. 
             (VXW7-1901)
15feb14,to   remove SaveRestVR.c configlette (VXW7-1860)
11dec13,x_z  created from ppc/arch.cdf 04f.
*/

/*
This cdf file defines the PPC arch base component units, and could be overridden
by arch.cdf of PPC_KERNEL_E500 layer or other speical CPU layers.
*/

Profile PROFILE_ARCH_DEFAULT {
    NAME                default ARCH profile
    SYNOPSIS            profile to include default ARCH components and parameters
    COMPONENTS
    PROFILES
    PARAMETER_VALUES
}

/*
 * This will override parts of INCLUDE_ATOMIC_OPERATORS the
 * component in 00vxworks.cdf
*/

#ifdef _WRS_CONFIG_SMP
Component INCLUDE_ATOMIC_OPERATORS {
    MODULES         vxAtomicALib.o
}


/*
 * Specify initialization sequence for generic
 * component, and make it visible/selectable.
 */

Component INCLUDE_PROTECT_IDLE_TASK_STACK {
    _CHILDREN       FOLDER_KERNEL
    _INIT_ORDER     usrRoot
    REQUIRES        INCLUDE_OSM
    INIT_AFTER      INCLUDE_OSM
    INIT_BEFORE     INCLUDE_PROTECT_TASK_STACK
}
#endif  /* SMP */

Component INCLUDE_LOCK_TEXT_SECTION {
    REQUIRES    INCLUDE_MMU_OPTIMIZE
}

Parameter TLB_CACHE_MODE {
    DEFAULT     (VM_STATE_CACHEABLE | VM_STATE_MEM_COHERENCY)
}

Parameter VM_PAGE_SIZE {
    DEFAULT        4096
}

Component INCLUDE_OSM {
    NAME            Overflow Stopgap Mode
    SYNOPSIS        Handler for Exception Stack Overflow
    PROTOTYPE       void excOsmInit (int, int);
    INIT_RTN        excOsmInit (TASK_USER_EXC_STACK_OVERFLOW_SIZE, VM_PAGE_SIZE);
    _CHILDREN       FOLDER_NOT_VISIBLE
    REQUIRES        INCLUDE_MMU_BASIC
    INCLUDE_WHEN    INCLUDE_PROTECT_TASK_STACK
    _INIT_ORDER     usrRoot
    INIT_AFTER      INCLUDE_MMU_BASIC
    INIT_BEFORE     INCLUDE_PROTECT_TASK_STACK
}

Component INCLUDE_DEFERRED_INTERRUPT_ENABLE {
    NAME            Deferred Interrupt Enable
    SYNOPSIS        Enable interrupts at appropriate point in root task
#ifndef _WRS_CONFIG_VXBUS_LEGACY
    HDR_FILES       arch/ppc/archPpc.h  \
                    arch/ppc/vxPpcLib.h \
                    subsys/int/vxbIntLib.h
#else /* _WRS_CONFIG_VXBUS_LEGACY */
    HDR_FILES       arch/ppc/archPpc.h  \
                    arch/ppc/vxPpcLib.h
#endif /* !_WRS_CONFIG_VXBUS_LEGACY */
    PROTOTYPE       void excIntNestLogInit (void); \
                    IMPORT _RType taskMsrDefault;   /* from taskArchLib.c */
#ifndef _WRS_CONFIG_VXBUS_LEGACY
    INIT_RTN        excIntNestLogInit(); \
                    vxMsrSet(vxMsrGet() | taskMsrDefault); \
                    sysIntEnableFlagSet ();
#else /* _WRS_CONFIG_VXBUS_LEGACY */
    INIT_RTN        excIntNestLogInit(); \
                    vxMsrSet(vxMsrGet() | taskMsrDefault);
#endif /* !_WRS_CONFIG_VXBUS_LEGACY */
    _CHILDREN       FOLDER_NOT_VISIBLE
    INCLUDE_WHEN    INCLUDE_KERNEL          /* always */
    _INIT_ORDER     usrRoot
    INIT_AFTER      usrKernelCoreInit   \
                    INCLUDE_MMU_BASIC
#ifndef _WRS_CONFIG_VXBUS_LEGACY
    INIT_BEFORE     usrClkInit
#else /* _WRS_CONFIG_VXBUS_LEGACY */
    INIT_BEFORE     INCLUDE_SYSCLK_INIT
#endif /* !_WRS_CONFIG_VXBUS_LEGACY */
}

/*
 * Make generic definition visible in GUI by placing it in a visible folder,
 * and specify initialization sequence.
 */

Component INCLUDE_PROTECT_INTERRUPT_STACK {
    _CHILDREN       FOLDER_KERNEL_HARDENING
    INCLUDE_WHEN    INCLUDE_KERNEL_HARDENING
    _INIT_ORDER     usrRoot
    REQUIRES        INCLUDE_OSM
    INIT_AFTER      INCLUDE_OSM
    INIT_BEFORE     INCLUDE_PROTECT_TASK_STACK
}

Component INCLUDE_LOADER_CODE {
    NAME            ELF loader
    SYNOPSIS        ELF loader
    MODULES         loadLib.o loadElfLib.o
    INIT_RTN        loadElfInit ();
    HDR_FILES       loadElfLib.h
}

Component INCLUDE_EXC_EXTENDED_VECTORS {
    NAME            Allow 32-bit branches to handlers
    SYNOPSIS        Extended 32-bit vector branches to handlers
    _CHILDREN       FOLDER_KERNEL
    HDR_FILES       private/excLibP.h
    CFG_PARAMS      EXC_EXTENDED_VECTORS_ENABLED
    INIT_RTN        excExtendedVectors = EXC_EXTENDED_VECTORS_ENABLED;
    _INIT_ORDER     usrInit
    INIT_BEFORE     INCLUDE_EXC_HANDLING
}

/* Component is already defined, just insert the module names for PPC */

Component INCLUDE_RTP_ARCH {
    MODULES         syscallArchLib.o syscallALib.o \
                    rtpALib.o rtpSigArchLib.o
}

Component INCLUDE_CACHE_SUPPORT {
    NAME            cache support
    SYNOPSIS        include cache support
    INIT_RTN        cacheLibInit (USER_I_CACHE_MODE, USER_D_CACHE_MODE);
    MODULES         cacheLib.o
    CFG_PARAMS      USER_I_CACHE_MODE USER_D_CACHE_MODE
    HDR_FILES       cacheLib.h
}

Component INCLUDE_SIGNAL_ARCH {
    NAME            architecture dependent code for signals
    SYNOPSIS        architecture dependent code for signals
    MODULES         sigCtxALib.o sigCtxLib.o
    REQUIRES        INCLUDE_KERNEL \
                    INCLUDE_ANSI_LONGJMP
    INCLUDE_WHEN    INCLUDE_SIGNALS
    _CHILDREN       FOLDER_NOT_VISIBLE
}

Parameter EXC_EXTENDED_VECTORS_ENABLED {
    NAME            Enables Extended 32-bit exception vector
    TYPE            bool
#ifdef _WRS_CONFIG_WRHV_GUEST
    DEFAULT         FALSE
#else /* _WRS_CONFIG_WRHV_GUEST */
    DEFAULT         TRUE
#endif /* _WRS_CONFIG_WRHV_GUEST */
}

Parameter USER_I_MMU_ENABLE {
    NAME            enable instruction MMU
    TYPE            exists
    DEFAULT         TRUE
    _CFG_PARAMS     INCLUDE_MMU_GLOBAL_MAP
}

Parameter INT_LOCK_LEVEL {
    NAME            INT lock level
    SYNOPSIS        Interrupt lock level
    DEFAULT         0x0
}

Parameter ROOT_STACK_SIZE {
    NAME            Root stack size
    SYNOPSIS        Root task stack size (bytes)
    DEFAULT         24000
}

Parameter SHELL_STACK_SIZE {
    NAME            Shell stack size
    SYNOPSIS        Shell stack size (bytes)
    DEFAULT         0x10000
}

Parameter ISR_STACK_SIZE {
    NAME            ISR stack size
    SYNOPSIS        ISR Stack size (bytes)
#ifdef _WRS_CONFIG_LP64
    DEFAULT	    0x2000
#else
    DEFAULT         5000
#endif /* _WRS_CONFIG_LP64 */
}

#ifdef _WRS_CONFIG_USE_MEMDESC
Parameter SYS_DMA32_MEM_ATTR {
    NAME            System DMA32 Memory Desciptior Attribute
    SYNOPSIS        VM attribute for DMA32 memory descriptors used to provide
                    DMA memory block below 4G physical address if
                    INCLUDE_DMA32_MEM is defined.
    DEFAULT         MMU_ATTR_VALID | MMU_ATTR_SUP_RW | \
                    MMU_ATTR_CACHE_OFF | MMU_ATTR_CACHE_GUARDED
    _CFG_PARAMS     INCLUDE_MEMORY_CONFIG
}

Parameter SYS_DMA32_MEM_ATTR_MASK {
    NAME            System DMA32 Memory Desciptior Attribute Mask
    SYNOPSIS        VM attribute mask for DMA32 memory descriptors used to
                    provide DMA memory block below 4G physical address if
                    INCLUDE_DMA32_MEM is defined.
    DEFAULT         MMU_ATTR_VALID_MSK | MMU_ATTR_PROT_MSK | \
                    MMU_ATTR_CACHE_MSK
    _CFG_PARAMS INCLUDE_MEMORY_CONFIG
}
#endif /* _WRS_CONFIG_USE_MEMDESC */

#ifdef _WRS_CONFIG_PPC_ALTIVEC
Component INCLUDE_ALTIVEC {
    NAME            AltiVec runtime support
    SYNOPSIS        AltiVec register save/restore routines
    _CHILDREN       FOLDER_SUBSYSTEM
    HDR_FILES       altivecLib.h
    CONFIGLETTES    usrAltivec.c
    CFG_PARAMS      ALTIVEC_NON_JAVA_MODE
    REQUIRES        INCLUDE_COPROCESSOR
#ifdef _WRS_CONFIG_FP_hard
    _REQUIRES	INCLUDE_ANSI_TIME   \
                INCLUDE_ANSI_ATOF   \
                INCLUDE_ANSI_STRTOD \
                INCLUDE_FP_TYPE
#endif
}

Component INCLUDE_ALTIVEC_SHOW {
    NAME            AltiVec show routine
    SYNOPSIS        task AltiVec registers
    MODULES         altivecShow.o
    _CHILDREN       FOLDER_SHOW_ROUTINES
    INCLUDE_WHEN    INCLUDE_ALTIVEC \
                    INCLUDE_SHOW_ROUTINES
    REQUIRES        INCLUDE_ALTIVEC \
                    INCLUDE_COPROCESSOR_SHOW
}

#ifdef _WRS_CONFIG_SHELL
Component INCLUDE_ALTIVEC_MREGS {
    NAME            altivec registers modification
    SYNOPSIS        Provides ability to modify altivec registers from the
                    kernel shell.
    MODULES         altivecRegsLib.o
    INCLUDE_WHEN    INCLUDE_ALTIVEC_SHOW \
                    INCLUDE_SHELL
    REQUIRES        INCLUDE_ALTIVEC_SHOW \
                    INCLUDE_SHELL
    _CHILDREN       FOLDER_NOT_VISIBLE
}
#endif /* _WRS_CONFIG_SHELL */

Parameter ALTIVEC_NON_JAVA_MODE {
    NAME            Altivec non-java mode
    TYPE            exists
    DEFAULT         FALSE
}

#endif  /* _WRS_CONFIG_PPC_ALTIVEC */

Component INCLUDE_KERNEL_ARCH {
    NAME            Architecture Specific Kernel Components
#ifndef _WRS_CONFIG_WRHV_GUEST
        REQUIRES    INCLUDE_VXCPULIB
#endif /* _WRS_CONFIG_WRHV_GUEST */
    _CHILDREN       FOLDER_NOT_VISIBLE
}

Component INCLUDE_BLIB_ARCH {
    NAME            Architecture specific blib implementation
    REQUIRES        INCLUDE_BLIB
    INCLUDE_WHEN    INCLUDE_BLIB
    _CHILDREN       FOLDER_NOT_VISIBLE
}

Component INCLUDE_OBJ_LIB_ARCH {
    NAME            object management
    SYNOPSIS        architecture dependent portion of OBJ_LIB
    REQUIRES        INCLUDE_OBJ_LIB
    INCLUDE_WHEN    INCLUDE_OBJ_LIB
    _CHILDREN       FOLDER_NOT_VISIBLE
}

Component INCLUDE_ANSI_MATH {
    NAME            ANSI math
    SYNOPSIS        ANSI mathematical functions
    LINK_SYMS       acos asin atan atan2 ceil cos cosh exp fabs floor \
                    fmod frexp hypot ldexp log log10 modf pow sin sinh \
                    sqrt tan tanh
#ifdef _WRS_CONFIG_FP_hard
    REQUIRES        INCLUDE_HW_FP   \
                    INCLUDE_FP_TYPE
#endif

#ifdef _WRS_CONFIG_FP_soft
    REQUIRES        INCLUDE_SW_FP   \
                    INCLUDE_FP_TYPE
#endif 
    HELP            ansiMath
}

#ifdef _WRS_CONFIG_WRLOAD
Component INCLUDE_WRLOAD {
    REQUIRES        += INCLUDE_MMU_BASIC
}
#endif /* _WRS_CONFIG_WRLOAD */

Component INCLUDE_COPROCESSOR {
    NAME            coprocessor
    SYNOPSIS        generalized coprocessor support
    MODULES         coprocLib.o
    INIT_RTN        coprocLibInit();
    CONFIGLETTES    usrCoprocs.c
    _CHILDREN       FOLDER_SUBSYSTEM
    REQUIRES        INCLUDE_KERNEL \
                    INCLUDE_TASK_CREATE_HOOKS \
                    INCLUDE_TASK_SWAP_HOOKS   \
                    INCLUDE_MEM_MGR_FULL    /* for calloc */
    _INIT_ORDER     usrIosCoreInit
}

Component INCLUDE_HW_FP {
    NAME            hardware fpp support
    SYNOPSIS        Architecture common modules for hardware floating point
    INIT_RTN
    HDR_FILES
    REQUIRES        INCLUDE_COPROCESSOR
#ifdef _WRS_CONFIG_FP_hard
    _REQUIRES       INCLUDE_ANSI_TIME   \
                    INCLUDE_ANSI_ATOF   \
                    INCLUDE_ANSI_STRTOD \
                    INCLUDE_FP_TYPE
#endif
}

Component INCLUDE_SW_FP {
    NAME        software fpp support
    MODULES     mathSoftLib.o
    INIT_RTN    mathSoftInit ();
    HDR_FILES   math.h
}

Parameter DATA_SEG_ALIGN {
    NAME            kernel data segment alignment
    _CFG_PARAMS    INCLUDE_MEMORY_CONFIG
    DEFAULT        (INCLUDE_LOCK_TEXT_SECTION)::(0x00040000) \
                    1
}

Component INCLUDE_CACHE_ARCH {
    NAME            PPC common cache library
    SYNOPSIS        PPC common cache library
    MODULES         cacheArchSysctl.o
    _CHILDREN       FOLDER_NOT_VISIBLE
}

Component INCLUDE_MMU_ARCH_COMMON_ALIB {
    NAME            PPC MMU common assembly function library
    SYNOPSIS        PPC MMU common assembly function library
    MODULES         mmuPpcALib.o
    _CHILDREN       FOLDER_NOT_VISIBLE
}


#if defined (_WRS_CONFIG_PPC_BOOKE) || defined (_WRS_CONFIG_PPC_60x)

Component INCLUDE_AIM_CACHE {
    NAME            AIM Cache Library
    SYNOPSIS        PPC common AIM cache library
    MODULES         aimCacheLib.o
    _CHILDREN       FOLDER_NOT_VISIBLE
}

#ifdef _WRS_CONFIG_PPC_BOOKE
#ifndef _WRS_CONFIG_UNIFIED_MMU_LIB
Folder  FOLDER_AIM_CONFIG {
    NAME            AIM MMU configuration 
    CHILDREN        INCLUDE_AIM_MMU_CONFIG          \
                    INCLUDE_AIM_MMU_MEM_POOL_CONFIG \
                    INCLUDE_AIM_MMU_PT_PROTECTION
    _CHILDREN       FOLDER_MMU 
}

Component INCLUDE_AIM_MMU_CONFIG {
    NAME            AIM MMU configlette
    CONFIGLETTES    usrAimMmu.c
    INIT_RTN        usrAimMmuConfig ();
    REQUIRES        INCLUDE_MMU_BASIC
}

Component INCLUDE_AIM_MMU_MEM_POOL_CONFIG {
    NAME            Page table and region table memory pool configuration
    REQUIRES        INCLUDE_MMU_BASIC INCLUDE_AIM_MMU_CONFIG
    CFG_PARAMS      AIM_MMU_INIT_PT_NUM     \
                    AIM_MMU_INIT_PT_INCR    \
                    AIM_MMU_INIT_RT_NUM     \
                    AIM_MMU_INIT_RT_INCR
}

Parameter AIM_MMU_INIT_PT_NUM {
    NAME            AIM MMU page table pool init size
    SYNOPSIS        Sets the size of the mem pool for page tables
    DEFAULT         0x40
}

Parameter AIM_MMU_INIT_PT_INCR {
    NAME            AIM MMU page table pool init size
    SYNOPSIS        Sets the size of the increment when need more memory
    DEFAULT         0x20
}

Parameter AIM_MMU_INIT_RT_NUM {
    NAME            AIM MMU region table pool init size
    SYNOPSIS        Sets the size of the mem pool for region tables
    DEFAULT         0x10
}

Parameter AIM_MMU_INIT_RT_INCR {
    NAME            AIM MMU region table pool increment size
    SYNOPSIS        Sets the size of the increment when need more memory
    DEFAULT         0x10
}

Component INCLUDE_AIM_MMU_PT_PROTECTION {
    NAME            write-protect page tables
    REQUIRES        INCLUDE_MMU_BASIC INCLUDE_AIM_MMU_CONFIG
}

Component INCLUDE_AIM_MMU_SHOW {
    NAME            AIM MMU Show Routines
    MODULES         aimMmuShow.o
    _CHILDREN       FOLDER_SHOW_ROUTINES
    REQUIRES        INCLUDE_MMU_BASIC
    LINK_SYMS       aimMmuMapShow
}

Component INCLUDE_AIM_MMU_BASIC {
    NAME            AIM MMU basic configuration
    SYNOPSIS        AIM MMU basic configuration
    MODULES         aimMmuBaseLib.o
    _CHILDREN       FOLDER_NOT_VISIBLE
}
#endif /* _WRS_CONFIG_UNIFIED_MMU_LIB */
#endif /* _WRS_CONFIG_PPC_BOOKE */
#endif /* _WRS_CONFIG_PPC_60x || _WRS_CONFIG_PPC_BOOKE */

