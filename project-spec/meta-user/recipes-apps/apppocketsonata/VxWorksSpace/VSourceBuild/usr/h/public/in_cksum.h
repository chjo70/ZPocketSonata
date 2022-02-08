/* 
 * Copyright 1984-2006, 2014 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
13feb14,ylu  Updated the includes path. (VXW7-1325) 
19jun06,jpb  Updated for POSIX namespace conformance.  
		 Changed C preprocessor macro CPU_FAMILY to _VX_CPU_FAMILY.
14jan05,vvv  osdep.h cleanup
23sep04,kc   Added coldfire arch support.
28may04,niq  Merging from base6 label POST_ITER5_FRZ16_REBASE (ver
                 /main/vdt/base6_itn5-int/2)
08dec03,dat  fix CPU_FAMILY names
04dec03,xli  creation
*/

/*
DESCRIPTION
This file is a wrapper of in_cksum.h which include specific in_cksum.h  
depend on the CPU_FAMILY
*/

#include <vxWorks.h>

/* The following includes are from target/h/arch */

#if(_VX_CPU_FAMILY==_VX_ARM)
#include <in_cksum_arm.h>

#elif (_VX_CPU_FAMILY==_VX_I80X86)
#include <in_cksum_ia.h>

#elif (_VX_CPU_FAMILY==_VX_PPC)
#include <in_cksum_ppc.h>

#elif (_VX_CPU_FAMILY==_VX_SIMNT)
#include <in_cksum_sim.h>

#elif (_VX_CPU_FAMILY==_VX_SIMLINUX)
#include <in_cksum_sim.h>

#endif


