/* Copyright (c) 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

#if !defined(__st_regs_h_)
#define __st_regs_h_

#if defined(__VXWORKS__)
#  include <vxWorks.h>
#  include <regs.h>
#else

/* linux */
#if defined(ST_TARGETARCH_i86)
#  include <arch/i86_regs.h>
#elif defined(ST_TARGETARCH_ppc)
#  include <arch/ppc_regs.h>
#elif defined(ST_TARGETARCH_arm)
#  include <arch/arm_regs.h>
#elif defined(ST_TARGETARCH_mips)
#  include <arch/mips_regs.h>
#else
#  error Compiling for unknown architecture
#endif
#endif


#endif /* if !defined(__st_regs_h_) */
