/* arch.cdf - PPC E500 arch components */

/*
 * Copyright (c) 2013-2014, 2016-2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
19jul17,mjn  text updates (F8862)
16dec16,cfm  removed X mmu attribute in SYS_DMA32_MEM_ATTR (F7142)
25sep14,l_z  remove INCLUDE_MMU_E500_SHOW component. (V7PRO-1164)
25apr14,cww  moved SYS_MEM_DESC_NUM to boardlib
22feb14,x_z  fixed FP option for PPC E500V2. (VXW7-1901)
16dec13,d_l  add INCLUDE_SPE_EXC_HDLR component.
11dec13,x_z  created from ppc/arch.cdf 04f.
*/

/*
This cdf file defines the PPC E500 arch specific component units, and could
override 00arch.cdf of PPC_KERNEL_BASE layer.
*/

Profile PROFILE_ARCH_DEFAULT {
    COMPONENTS  +=  INCLUDE_AIM_MMU_MEM_POOL_CONFIG \
                    INCLUDE_AIM_MMU_PT_PROTECTION
}

Profile PROFILE_ARCH_DEFAULT {
}

#ifdef _WRS_CONFIG_PPCE500_SPE
Component INCLUDE_HW_FP {
    _REQUIRES -=    INCLUDE_ANSI_TIME   \
                    INCLUDE_ANSI_ATOF   \
                    INCLUDE_ANSI_STRTOD \
                    INCLUDE_FP_TYPE
}
#endif	/* _WRS_CONFIG_PPCE500_SPE */

Component INCLUDE_CACHE_SUPPORT {
	REQUIRES	INCLUDE_MMU_GLOBAL_MAP
   _REQUIRES    INCLUDE_KERNEL_ARCH
}

Parameter USER_D_CACHE_MODE {
	DEFAULT		(CACHE_COPYBACK | CACHE_SNOOP_ENABLE)
}

Parameter USER_I_CACHE_MODE {
	DEFAULT		(CACHE_COPYBACK | CACHE_SNOOP_ENABLE)
}

#ifdef _WRS_CONFIG_USE_MEMDESC
Parameter SYS_DMA32_MEM_ATTR {
    DEFAULT     MMU_ATTR_VALID | MMU_ATTR_SUP_RW | MMU_ATTR_CACHE_DEFAULT | \
                MMU_ATTR_CACHE_COHERENCY
    _CFG_PARAMS INCLUDE_MEMORY_CONFIG
}

Parameter SYS_DMA32_MEM_ATTR_MASK {
    DEFAULT     MMU_ATTR_VALID_MSK | MMU_ATTR_PROT_MSK | MMU_ATTR_CACHE_MSK
    _CFG_PARAMS INCLUDE_MEMORY_CONFIG
}
#endif /* _WRS_CONFIG_USE_MEMDESC */

#ifdef _WRS_CONFIG_PPCE500_SPE
Component INCLUDE_SPE {
	NAME		Spe runtime support
	SYNOPSIS	Spe register save/restore routines
	_CHILDREN	FOLDER_SUBSYSTEM
	HDR_FILES	speLib.h
	REQUIRES	INCLUDE_COPROCESSOR
#ifdef _WRS_CONFIG_FP_hard
    _REQUIRES	INCLUDE_ANSI_TIME   \
                INCLUDE_ANSI_ATOF   \
                INCLUDE_ANSI_STRTOD \
                INCLUDE_FP_TYPE
#endif
}

Component INCLUDE_SPE_EXC_HDLR {
	NAME		PPC E500 v2 SPE exception handler
	SYNOPSIS	Handle (some) IEEE 754 exceptions for E500 v2
	_CHILDREN	FOLDER_SUBSYSTEM
	PROTOTYPE	void speExcInit (void);
	INIT_RTN	speExcInit ();
	_INIT_ORDER	usrIosExtraInit
	INIT_BEFORE	INCLUDE_FLOATING_POINT
	REQUIRES	INCLUDE_SPE
	_REQUIRES	INCLUDE_SPE
}

Component INCLUDE_SPE_SHOW {
	NAME		    Spe show routine
	SYNOPSIS	    task Spe registers
	_CHILDREN	    FOLDER_SHOW_ROUTINES
	INCLUDE_WHEN	INCLUDE_SPE \
			        INCLUDE_SHOW_ROUTINES
}

Component INCLUDE_ANSI_MATH {
	REQUIRES	INCLUDE_SPE	\
			INCLUDE_FP_TYPE
}
#endif	/* _WRS_CONFIG_PPCE500_SPE */

