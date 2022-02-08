/* usrMmuArchInit.c - memory management unit initialization */

/*
 * Copyright (c) 2013, 2015-2016 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
08sep16,d_l  call aimMmuBaseLibInit directly in UNIFIED_MMU_LIB. (V7PRO-3317)
10jun16,y_y  add extern function to avoid build warnings. (V7PRO-3173)
16jul15,w_x  Rename new MMU library VSB option to UNIFIED_MMU_LIB (F2518)
16mar15,w_x  Integrated new MMU library to VxWorks 7 for PPC64 (F2518)
12oct13,x_z  Added support for new memory model.
25sep13,pcs  Moved the arch specific code from usrMmuInit to here.
*/

/*
DESCRIPTION
This file is used to initialize the architecture portion of the memory
management unit.  This file is included by usrMmuInit.c 

SEE ALSO: usrMmuInit.c

NOMANUAL
*/

#ifndef  __INCusrMmuArchInitc
#define  __INCusrMmuArchInitc

#include <vsbConfig.h>
#include <arch/ppc/mmuE500Lib.h>


/* defines */

/*
 * Check to see if MMU support exists (one of _WRS_TLB_MISS_CLASS_* is defined).
 */

#if ((CPU_FAMILY == PPC) && \
    (defined(_WRS_TLB_MISS_CLASS_SW) || defined(_WRS_TLB_MISS_CLASS_HW)))

 /*
  * MMU support is available for this CPU. Set PPC_MMU_TYPE to identify
  * the CPU-specific code expected by mmuXxxLibInit corresponding to
  * USER_I_MMU_ENABLE and USER_D_MMU_ENABLE.
  * Also INCLUDE_ADR_SPACE_LIB requires both I&D MMU enabled.
  */

# if ((defined(USER_I_MMU_ENABLE) && defined(USER_D_MMU_ENABLE)) || \
      defined(INCLUDE_ADR_SPACE_LIB))
#  define PPC_MMU_TYPE	(MMU_INST | MMU_DATA)
# elif (defined(USER_I_MMU_ENABLE))
#  define PPC_MMU_TYPE	(MMU_INST)
# elif (defined(USER_D_MMU_ENABLE))
#  define PPC_MMU_TYPE	(MMU_DATA)
# else
#  define PPC_MMU_TYPE	(0)
# endif /* USER_I_MMU_ENABLE, USER_D_MMU_ENABLE */

#endif /* CPU_FAMILY == PPC && _WRS_TLB_MISS_CLASS_* */

/* externals */

IMPORT PHYS_MEM_DESC sysPhysMemDesc [];
IMPORT int sysPhysMemDescNumEnt;

IMPORT STATUS mmuGlobalLibInit (void);
IMPORT STATUS mmuBaseLibInit (void);
IMPORT STATUS mmuCtxLibInit (void);

#ifdef _WRS_CONFIG_COMPAT69_ADR_SPACE
#if (SW_MMU_ENABLE == FALSE)
IMPORT TLB_ENTRY_DESC sysStaticTlbDesc [];
IMPORT int sysStaticTlbDescNumEnt;
#endif
#endif /* _WRS_CONFIG_COMPAT69_ADR_SPACE */

/*******************************************************************************
*
* usrMmuArchInit - initialize the memory management unit
*
* This routine calls the architecture MMU library initialization routine.
*
* RETURNS: OK, or ERROR if the MMU library initialization failed.
*
* NOMANUAL
*/

STATUS usrMmuArchInit (void)
    {
#ifndef _WRS_CONFIG_UNIFIED_MMU_LIB    
#ifndef _WRS_CONFIG_COMPAT69_ADR_SPACE
    if (mmuE500LibInit (PPC_MMU_TYPE) != OK)
#else /* _WRS_CONFIG_COMPAT69_ADR_SPACE */
    if (mmuE500LibInit (PPC_MMU_TYPE, sysStaticTlbDescNumEnt,
                        &sysStaticTlbDesc[0]) != OK)
#endif /* !_WRS_CONFIG_COMPAT69_ADR_SPACE */
	    return (ERROR);
    else
        return (OK);
#else /* _WRS_CONFIG_UNIFIED_MMU_LIB */
    if (mmuGlobalLibInit () != OK)
	    return (ERROR);
    if (mmuBaseLibInit () != OK)
	    return (ERROR);
    if (mmuCtxLibInit () != OK)
	    return (ERROR);
    if (aimMmuBaseLibInit () != OK)
	    return (ERROR);
    return OK;
#endif /* _WRS_CONFIG_UNIFIED_MMU_LIB */
    }

#endif	/* __INCusrMmuArchInitc */
