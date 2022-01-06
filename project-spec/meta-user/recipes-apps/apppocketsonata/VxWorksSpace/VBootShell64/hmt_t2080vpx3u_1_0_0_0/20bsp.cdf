/* 20board.cdf - Board component description file */

/*
 * Copyright (c) 2014-2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
03feb17,syt  added dependency for DRV_FSL_I2C on DRV_I2C_RTC. (V7PRO-3520)
12sep16,syt  add T2080RDB support. (US85017)
02jun16,l_z  fix INCLUDE_FSL_SGMII_PHY component typo. (V7PRO-3110)
28mar16,wap  Update some component names
16mar16,wap  Add support for 10 gigabit interfaces on T4240 QDS and
             T2080 QDS board, and SGMII interfaces on the T4240 QDS
             board (F1921)
22dec15,syt  disable INCLUDE_BOOT_ETH_MAC_HANDLER. (V7PRO-2656)
29oct15,p_x  Add dependency for INCLUDE_BOOT_APP and BSP_DEFAULT 
             on DRV_FPGA_FDT_FSL_QORIQ. (V7PRO-2482)
24jul15,w_x  Add dependency for INCLUDE_TIMESTAMP on DRV_TIMER_OPENPIC (F2518)
10fen15,y_y  remove INCLUDE_T4240QDS_DTB_VXBOOT component.
11nov14,syt  added LP64 support and BOOTAPP required components. (US15027)
16mar15,l_z  Fix the DTB component display issue. (V7PRO-1861)
23sep14,l_z  fix the DTB select issue when use workBench. (V7PRO-1193)
24jul14,x_z  added SMP support. (US40508)
18jul14,x_z  added BSP REQUIRES;
             added multipile FMAN microcode support. (US40507)
11jun14,syt  added suport for T4240QDS. (US15742)
21may14,my_  add bootapp support(V7PRO-855)
10may14,ylu  added SMT (multi-threading) support to BSP for PPCE6500.
             (US34958)
29apr14,ylu  fixed SMP task schedule issue.(V7PRO-743)
10apr14,ylu  added support for SMP.(US34480)
28feb14,ylu  created
*/

Bsp hmt_t2080vpx3u {
    REQUIRES    INCLUDE_KERNEL          \
                INCLUDE_CPU_INIT        \
                INCLUDE_MEM_DESC        \
                DRV_BUS_FDT_SIMPLE      \
                DRV_INTCTLR_FDT_MPIC    \
                DRV_TIMER_FSL_BOOKE     \
                DRV_QORIQ_CLK           \
                DRV_FPGA_FDT_FSL_QORIQ  \
                DRV_SIO_FDT_NS16550
}

Parameter CONSOLE_TTY {
    DEFAULT     0
}

Parameter CONSOLE_BAUD_RATE {
    DEFAULT     115200
}

Parameter RAM_LOW_ADRS {
    NAME        Runtime kernel entry address
#ifndef  _WRS_CONFIG_LP64 
    DEFAULT     (INCLUDE_BOOT_APP)::(0x01000000) \
                0x00100000
#else  /* _WRS_CONFIG_LP64 */
    DEFAULT     (INCLUDE_BOOT_APP)::(0xffffffff81000000) \
                0xffffffff80100000
#endif /* _WRS_CONFIG_LP64 */
}

Parameter KERNEL_LOAD_ADRS {
    NAME        Runtime kernel load address
    DEFAULT     (INCLUDE_BOOT_APP)::(0x01000000) \
                0x00100000
}

Parameter VXB_MAX_INTR_VEC {
    NAME         maximum number of interrupt vector
    SYNOPSIS     Maximum number of interrupt vector
    TYPE         UINT32
    DEFAULT      4096
}

/*
 * VX_SMP_NUM_CPUS is a SMP parameter only and only available for SMP
 * builds. Due to a limitation of the project tool at the time this
 * parameter is created where the tool can not recognize the ifdef SMP
 * selection, this parameter is set up such that _CFG_PARAMS is not
 * specified here. In the 00vxWorks.cdf file, where the parameter
 * VX_SMP_NUM_CPUS is defined, the _CFG_PARAMS is specified only for
 * VxWorks SMP. Hence the redefining of VX_SMP_NUM_CPUS here should only
 * override the value and not the rest of the properties. And for UP, the
 * parameter is ignored since the parameter is not tied to any component
 * (_CFG_PARAMS is not specified).
 */

Parameter VX_SMP_NUM_CPUS {
    NAME            Number of CPUs available to be enabled for VxWorks SMP
    TYPE            UINT
#ifdef _WRS_CONFIG_SMP_SMT
    DEFAULT         24
#else /* _WRS_CONFIG_SMP_SMT */
    DEFAULT         12
#endif /* !_WRS_CONFIG_SMP_SMT */
}

Component       DRV_TIMER_OPENPIC {
    INCLUDE_WHEN   INCLUDE_AUX_CLK
}

Component INCLUDE_TIMESTAMP {
    REQUIRES    += DRV_TIMER_OPENPIC
}

Component DRV_I2C_RTC {
    REQUIRES    += DRV_FSL_I2C
}

Component       INCLUDE_BOOT_APP {
    REQUIRES       INCLUDE_GENERICPHY    \
                   DRV_VXBEND_QORIQMEMAC \
                   DRV_QORIQMEMAC_MDIO   \
                   INCLUDE_GENERIC_MMD_PHY \
                   INCLUDE_FSL_SGMII_PHY  \
                   DRV_FPGA_FDT_FSL_QORIQ
}

Component INCLUDE_BOOT_ETH_MAC_HANDLER {
    REQUIRES        COMPONENT_NOT_SUPPORTED
}

Profile BSP_DEFAULT {
    NAME            default BSP profile
    SYNOPSIS        profile to include default BSP components and parameters
    COMPONENTS      INCLUDE_DEBUG_KPRINTF \
                    DRV_CORENET_L2_CACHE \
                    DRV_CORENET_L3_CACHE \
                    INCLUDE_GENERICPHY \
                    DRV_VXBEND_QORIQMEMAC \
                    DRV_QORIQMEMAC_MDIO \
                    INCLUDE_GENERIC_MMD_PHY \
                    INCLUDE_FSL_SGMII_PHY \
                    DRV_FPGA_FDT_FSL_QORIQ
    PROFILES        PROFILE_OS_DEFAULT \
                    PROFILE_ARCH_DEFAULT \
                    PROFILE_BSP_NETWORK_DEFAULT
}

Parameter QORIQ_FMAN_UCODE_PHYS_ADRS {
    NAME            physical address for Freescale QorIQ Frame Manager microcode
    DEFAULT         0xFEFF00000
    _CFG_PARAMS     DRV_RESOURCE_QORIQFMAN

}

Parameter QORIQ_FMAN_UCODE_SIZE {
    NAME            size for Freescale QorIQ Frame Manager microcode
    DEFAULT         0x40000
    _CFG_PARAMS     DRV_RESOURCE_QORIQFMAN
}

#ifdef _WRS_CONFIG_STANDALONE_DTB

Bsp hmt_t2080vpx3u {
    REQUIRES += SELECT_STANDALONE_DTB_SRC
}

/*
 * DTB could be built into VxWorks kernel image if
 * _WRS_CONFIG_STANDALONE_DTB option is defined. For this mode:
 *
 *  1. DTB couldn't be fixed by U-Boot automatically;
 *  2. IMA_SIZE need be set to one value that is large enough for entire VxWorks
 *  image.
 *
 */

Selection SELECT_STANDALONE_DTB_SRC {
    NAME        select standalone DTB source
    COUNT       1-1
    CHILDREN    INCLUDE_T2080VPX3U_DTB
    DEFAULTS    INCLUDE_T2080VPX3U_DTB
    _CHILDREN   FOLDER_BSP_CONFIG
    }

Component INCLUDE_T2080VPX3U_DTB {
    NAME        T2080VPX3U DTB source for u-boot
    CFG_PARAMS  DTS_FILE IMA_SIZE
}

Parameter DTS_FILE {
    NAME    DTS file for DTB
    DEFAULT (INCLUDE_T2080VPX3U_DTB)::(t2080rdb.dts) \
            t2080vpx3u.dts
}

Parameter IMA_SIZE {
    NAME        IMA(Initial Mapped Area) size
    SYNOPSIS    IMA(Initial Mapped Area) will be mapped to MMU for \
                the early initialization phase before usrMmuInit(), \
                so the size should be large enough to hold the entire VxWorks Kernel image.
    DEFAULT     0x10000000
}
#endif /* _WRS_CONFIG_STANDALONE_DTB */

