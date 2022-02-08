/* usrKernelStack.c - interrupt stack protection support */

/*
 * Copyright (c) 2005-2008, 2010, 2014 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
03apr14,h_k  added usrKernelIntStkProtectNonCore0() for SMP. (VXW6-19208)
29jun10,jpb  Updated for LP64 adaptation.
25aug08,jpb  Renamed _WRS_VX_SMP to _WRS_CONFIG_SMP.
24mar08,jpb  Defect: 112923.  Changed the casting for 2nd parameter 
             in vmStateSet.
13sep07,pch  CQ102745: remove obsolete usrKernelIntStkSizeAdj()
01dec06,dbt  Fixed for SMP.
04feb05,pch  written, for SPR 102772.
*/

/*
DESCRIPTION
This file supports the INCLUDE_PROTECT_INTERRUPT_STACK component.

\NOMANUAL
*/

#ifndef  __INCusrKernelStack_c
#define  __INCusrKernelStack_c

#include <vsbConfig.h>
#include <private/kernelLibP.h>
#include <private/vxCpuLibP.h>

#ifdef  _ARCH_SUPPORTS_PROTECT_INTERRUPT_STACK
# ifdef  INCLUDE_PROTECT_INTERRUPT_STACK
#include <errno.h>

/* globals imported from kernelLib.c */

#ifndef	_WRS_CONFIG_SMP
IMPORT	char *    vxIntStackEnd;		/* end of interrupt stack */
IMPORT	char *    vxIntStackBase;		/* base of interrupt stack */
#endif	/* !_WRS_CONFIG_SMP */
IMPORT	size_t  vxIntStackOverflowSize;		/* size of overflow region */
IMPORT	size_t  vxIntStackUnderflowSize;	/* size of underflow region */

/* errnos from applying protection */
int	intStackOverflowProtectErrno = 0;
int	intStackUnderflowProtectErrno = 0;


/*******************************************************************************
*
* usrKernelIntStkProtect - apply protection to interrupt stack guard regions
*                          on primary core
*
* DESCRIPTION
* This function calls vmStateSet() to map the interrupt stack guard regions
* as VM_STATE_VALID_NOT on the primary core.
*
* \NOMANUAL
*/

void usrKernelIntStkProtect (void)
    {
#  if  ((INTERRUPT_STACK_OVERFLOW_SIZE > 0) || \
	(INTERRUPT_STACK_UNDERFLOW_SIZE > 0))
    STATUS	vmStat;

#   ifdef _WRS_CONFIG_SMP
    char * vxIntStackEnd = _WRS_KERNEL_CPU_GLOBAL_GET (0, vxIntStackEnd);
    char * vxIntStackBase = _WRS_KERNEL_CPU_GLOBAL_GET (0, vxIntStackBase);
#   endif /* _WRS_CONFIG_SMP */

#   if  (INTERRUPT_STACK_OVERFLOW_SIZE > 0)
    vmStat =
#    if  (_STACK_DIR == _STACK_GROWS_DOWN)
	vmStateSet (NULL,
		    (VIRT_ADDR) (vxIntStackEnd - vxIntStackOverflowSize),
		    vxIntStackOverflowSize,
		    VM_STATE_MASK_VALID | MMU_ATTR_SPL_MSK,
		    VM_STATE_VALID_NOT | MMU_ATTR_NO_BLOCK);
#    else   /* _STACK_DIR */
	vmStateSet (NULL,
		    (VIRT_ADDR) vxIntStackEnd,
		    vxIntStackOverflowSize,
		    VM_STATE_MASK_VALID | MMU_ATTR_SPL_MSK,
		    VM_STATE_VALID_NOT | MMU_ATTR_NO_BLOCK);
#    endif  /* _STACK_DIR */

    if (vmStat == ERROR)
	intStackOverflowProtectErrno = errno;
#   endif  /* INTERRUPT_STACK_OVERFLOW_SIZE > 0 */

#   if  (INTERRUPT_STACK_UNDERFLOW_SIZE > 0)
    vmStat =
#    if  (_STACK_DIR == _STACK_GROWS_DOWN)
	vmStateSet (NULL,
		    (VIRT_ADDR) vxIntStackBase,
		    vxIntStackUnderflowSize,
		    VM_STATE_MASK_VALID | MMU_ATTR_SPL_MSK,
		    VM_STATE_VALID_NOT | MMU_ATTR_NO_BLOCK);
#    else   /* _STACK_DIR */
	vmStateSet (NULL,
		    (VIRT_ADDR) (vxIntStackBase - vxIntStackUnderflowSize),
		    vxIntStackUnderflowSize,
		    VM_STATE_MASK_VALID | MMU_ATTR_SPL_MSK,
		    VM_STATE_VALID_NOT | MMU_ATTR_NO_BLOCK);
#    endif  /* _STACK_DIR */

    if (vmStat == ERROR)
	intStackUnderflowProtectErrno = errno;
#   endif  /* INTERRUPT_STACK_UNDERFLOW_SIZE > 0 */
#  endif /* (INTERRUPT_STACK_OVERFLOW_SIZE > 0) ||
	  * (INTERRUPT_STACK_UNDERFLOW_SIZE > 0)
	  */
    }
# endif  /* INCLUDE_PROTECT_INTERRUPT_STACK */

# ifdef INCLUDE_PROTECT_INTERRUPT_STACK_NON_CORE0
/*******************************************************************************
*
* usrKernelIntStkProtectNonCore0 - apply protection to interrupt stack guard
*                                  regions on non-primary cores
*
* DESCRIPTION
* This function calls vmStateSet() to map the interrupt stack guard regions
* as VM_STATE_VALID_NOT on the non-primary cores.
*
* \NOMANUAL
*/

void usrKernelIntStkProtectNonCore0 (void)
    {
#  if  ((INTERRUPT_STACK_OVERFLOW_SIZE > 0) || \
	(INTERRUPT_STACK_UNDERFLOW_SIZE > 0))
    UINT	cpuIx;
    char *	vxIntStackEnd;
    char *	vxIntStackBase;
    STATUS	vmStat;
    UINT	cpuConfigured = _WRS_CPU_CONFIGURED ();

    for (cpuIx = 1; cpuIx < cpuConfigured; cpuIx++)
	{
	vxIntStackEnd = _WRS_KERNEL_CPU_GLOBAL_GET (cpuIx, vxIntStackEnd);
	vxIntStackBase = _WRS_KERNEL_CPU_GLOBAL_GET (cpuIx, vxIntStackBase);

#   if  (INTERRUPT_STACK_OVERFLOW_SIZE > 0)
	vmStat =
#    if  (_STACK_DIR == _STACK_GROWS_DOWN)
	    vmStateSet (NULL,
			(VIRT_ADDR) (vxIntStackEnd - vxIntStackOverflowSize),
			vxIntStackOverflowSize,
			VM_STATE_MASK_VALID | MMU_ATTR_SPL_MSK,
		 	VM_STATE_VALID_NOT | MMU_ATTR_NO_BLOCK);
#    else   /* _STACK_DIR */
	    vmStateSet (NULL,
			(VIRT_ADDR) vxIntStackEnd,
			vxIntStackOverflowSize,
			VM_STATE_MASK_VALID | MMU_ATTR_SPL_MSK,
			VM_STATE_VALID_NOT | MMU_ATTR_NO_BLOCK);
#    endif  /* _STACK_DIR */

	if (vmStat == ERROR)
	    intStackOverflowProtectErrno = errno;
#   endif  /* INTERRUPT_STACK_OVERFLOW_SIZE > 0 */

#   if  (INTERRUPT_STACK_UNDERFLOW_SIZE > 0)
	vmStat =
#    if  (_STACK_DIR == _STACK_GROWS_DOWN)
	    vmStateSet (NULL,
			(VIRT_ADDR) vxIntStackBase,
			vxIntStackUnderflowSize,
			VM_STATE_MASK_VALID | MMU_ATTR_SPL_MSK,
			VM_STATE_VALID_NOT | MMU_ATTR_NO_BLOCK);
#    else   /* _STACK_DIR */
	    vmStateSet (NULL,
			(VIRT_ADDR) (vxIntStackBase - vxIntStackUnderflowSize),
			vxIntStackUnderflowSize,
			VM_STATE_MASK_VALID | MMU_ATTR_SPL_MSK,
			VM_STATE_VALID_NOT | MMU_ATTR_NO_BLOCK);
#    endif  /* _STACK_DIR */

	if (vmStat == ERROR)
	    intStackUnderflowProtectErrno = errno;
#   endif  /* INTERRUPT_STACK_UNDERFLOW_SIZE > 0 */
	}
#  endif /* (INTERRUPT_STACK_OVERFLOW_SIZE > 0) ||
	   * (INTERRUPT_STACK_UNDERFLOW_SIZE > 0)
	   */
    }
# endif /* INCLUDE_PROTECT_INTERRUPT_STACK_NON_CORE0 */
#endif  /* _ARCH_SUPPORTS_PROTECT_INTERRUPT_STACK */

#endif	/* __INCusrKernelStack_c */
