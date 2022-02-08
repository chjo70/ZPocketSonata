/* 20bsp.cdf - BSP component description file */

/*
 * Copyright (c) 2003-2010, 2013-2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
21nov15,l_z  Add fast warm boot require for PM. (F3387)
20nov14,ylu  LP64 adaptation to support PPC64.(F2518)
07jun14,ylu  fixed legacy T4240QDS BSP build failed with SMP. (V7PRO-998)
10may14,ylu  added SMT (multi-threading) support for PPCE6500.(US34958)
07mar14,x_z  removed AIM components(US18830); added detailed SYNOPSIS for 
             KERNEL_LOAD_ADRS.
22feb14,x_z  removed ARCH components and fixed FP components.
05dec13,r_y  update RAM_HIGH_ADRS parameter value (WIND00444983).
18oct13,x_z  added BSP default configuration.
26aug13,x_z  removed dependency with source directories. 
13jan10,cwl  Remove the dummy function aimMmuShowInit() from the component
             INCLUDE_AIM_MMU_SHOW. (WIND00184839)
12aug09,cww  Updated aimMmuShowInit location in usrRoot
04sep08,gls  divided task hook component
26aug08,jpb  Removed LAYER from components.
29nov07,dtr  Change default DATA_SEG_AKLIGN.
26apr06,ajc	 Added INCLUDE_ANSI_STRCAT and INCLUDE_ANSI_STRLEN for
	 mmuPpcLib.c (SPR #119277)
23feb06,h_k  removed INCLUDE_MMU_ARCH. (SPR #118027)
13oct05,yvp  INCLUDE_HW_SP gets pulled in for ANSI_STRTOD and ANSI_ATOF.
06oct05,h_k  changed INCLUDE_WHEN to _REQUIRES attribute for HW_FP. (SPR
             #113387) also added PPC60X specific POOL component. (SPR
             #112394) added FP_TYPE as a _REQUIRES comp for HW_FP.
             (SPR #113210)
19sep05,mil  Added INCLUDE_MMU_ARCH_COMMON_ALIB.
             Removed INCLUDE_AIM_CACHE_PPC60X.
14sep05,h_k  updated HW_FP. (SPR #112320) and COPROCESSOR.
26aug05,mil  Added source build support for MMU and cache.
22apr05,dr   SPR108100 - adding aimFppLib.o and fppArchLib.o to INCLUDE_HW_FP
09mar05,pch  adjust for PPC32 builds
17dec04,to   PPC970 does not use AIM MMU.
10nov04,dtr  SPR 103997.
30sep04,rlg  fix for SPR 100750 change INCLUDE_WHEN to REQUIRES in
             INCLUDE_COPROCESSOR, for future scaling issues.
29sep04,dtr  Add AIM MMU show routines.SPR 101412
18aug04,dtr  Pull in conditional AIM folder.
03sep03,dbt  Added _INIT_ORDER directory to INCLUDE_COPROCESSOR component.
07jul03,pch  separated from 20vxWorks.cdf vn 01a

DESCRIPTION

This file contains updated descriptions for some vxWorks components
defined in 00bsp.cdf. It updates those definitions with new ones needed
to support the coprocessor abstraction.
*/

#if (defined _WRS_CONFIG_SMP)
#ifndef _WRS_CONFIG_PPC_COMPAT69
#ifdef _WRS_CONFIG_SMP_SCHED_SMT_POLICY
/*
 * enable SMT scheduling policy by overriding the MODULES definition.
 * The scheduling policy requires SMT support; both are available only
 * for SMP builds, and both are included for default SMP configurations.
 */

Component INCLUDE_SMP_SCHED_SMT_POLICY {
    MODULES         readyQDeltaSmtLib.o
}

Api API_SMP_SCHED_POLICIES {
    DEFAULTS        INCLUDE_SMP_SCHED_SMT_POLICY
}

#endif  /* _WRS_CONFIG_SMP_SCHED_SMT_POLICY */
#else   /* _WRS_CONFIG_PPC_COMPAT69 */
#ifdef _ppc85XX_e6500
/*
 * enable SMT scheduling policy by overriding the MODULES definition.
 * The scheduling policy requires SMT support; both are available only
 * for SMP builds, and both are included for default SMP configurations.
 *
 * Note: we cannot make INCLUDE_SMT required for INCLUDE_SMP_SCHED_SMT_POLICY
 * because by doing so the removal of INCLUDE_SMT would result of the removal
 * of most kernel components.
 */

Component INCLUDE_SMP_SCHED_SMT_POLICY {
        MODULES         readyQDeltaSmtLib.o
}

Api API_SMP_SCHED_POLICIES {
        DEFAULTS        INCLUDE_SMP_SCHED_SMT_POLICY
}

Component INCLUDE_SMT {
        NAME            Threading support
        SYNOPSIS        Simultaneous Multi-Threading support
        _CHILDREN       FOLDER_BSP_CONFIG
        INCLUDE_WHEN    INCLUDE_SMP_INIT
}

Component DRV_INTCTLR_EPIC {
        CONFIGLETTES    hwif/vxbEpicIntCtlr.dc
        INIT_RTN        vxbEpicIntCtlrPreInit ();
        PROTOTYPE       void vxbEpicIntCtlrPreInit (void);
}
#endif  /* _ppc85XX_e6500 */
#endif  /* _WRS_CONFIG_PPC_COMPAT69 */
#endif  /* _WRS_CONFIG_SMP */

Parameter VEC_BASE_ADRS {
    NAME        Vector base address
    SYNOPSIS    Vector base address
    DEFAULT     (LOCAL_MEM_LOCAL_ADRS + 0x0)
}

Parameter EXC_MSG_OFFSET {
    NAME        exception message offset
    SYNOPSIS    Exception message offset
    DEFAULT     0x4300
}

Parameter EXC_MSG_ADRS {
    NAME        exception message address
    SYNOPSIS    Exception message address
    DEFAULT     (LOCAL_MEM_LOCAL_ADRS + EXC_MSG_OFFSET)
}

Parameter BOOT_LINE_SIZE {
    NAME        boot line size (bytes)
    SYNOPSIS    Boot line size (bytes)
    DEFAULT     255
}

Parameter BOOT_LINE_ADRS {
    NAME        Boot line address
    SYNOPSIS    Boot line address
    DEFAULT     (LOCAL_MEM_LOCAL_ADRS + BOOT_LINE_OFFSET)
}

Parameter BOOT_LINE_OFFSET {
    NAME        boot line offset
    SYNOPSIS    Boot line offset
    DEFAULT     0x4200
}

Parameter RESERVED {
    NAME        reserved
    SYNOPSIS    Reserved
    DEFAULT     0x4400
}

Parameter STACK_SAVE {
	NAME		Stack size
	SYNOPSIS	Amount of stack to reserve (bytes) for rom code
	DEFAULT		0x1000
}

#ifndef _WRS_CONFIG_PPC_COMPAT69
Parameter LOCAL_MEM_LOCAL_ADRS {
    DEFAULT     KERNEL_SYS_MEM_RGN_BASE
}

Parameter LOCAL_MEM_SIZE {
    DEFAULT     KERNEL_SYS_MEM_RGN_SIZE   
}

#ifdef _WRS_CONFIG_LP64
 Component INCLUDE_PAGE_SIZE_OPTIMIZATION {
	NAME		Optimize page tables
	SYNOPSIS	Enable page size optimization. On 32-bit VxWorks the \
			kernel context is optimized at the end of the \
			initialization sequence. On 64-bit VxWorks all \
			mappings (kernel and RTP) are performed automatically \
			with page size optimization when this component is \
			included. Not every architecture and CPU family \
			supports this feature. See the respective \
			Architecture Supplement for details.
 INCLUDE_WHEN INCLUDE_MMU_OPTIMIZE
}
#endif /* _WRS_CONFIG_LP64 */

Parameter KERNEL_LOAD_ADRS {
    SYNOPSIS    The address for VxWorks kernel load address of uVxWorks image. \
                It should be equal with ((VxWorks kernel load base address of  \
                uVxWorks image) +  (RAM_LOW_ADRS - LOCAL_MEM_LOCAL_ADRS)). And \
                the VxWorks kernel load base address should be equal with the  \
                address of the first RAM bank. Note that the kernel image must \
                be placed into the first RAM bank. 
}

Parameter RAM_HIGH_ADRS {
    NAME        RAM high Address (obsoleted)
    SYNOPSIS    The value should be large enough for VxWorks kernel image.
#   ifdef _WRS_CONFIG_LP64          
    DEFAULT     0xffffffff90000000
#   else /* !_WRS_CONFIG_LP64 */
    DEFAULT     0x80000000
#   endif /* _WRS_CONFIG_LP64 */  
}
#endif /* !_WRS_CONFIG_PPC_COMPAT69 */

#ifndef _WRS_CONFIG_PPC_COMPAT69
Component INCLUDE_EDR_PM {
    REQUIRES += INCLUDE_WARM_BOOT
}
#endif /* _WRS_CONFIG_PPC_COMPAT69 */

