/* Copyright (c) 2001-2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

#ifndef _CONTEXT_ARCH_H_
#define _CONTEXT_ARCH_H_

#if defined(__VXWORKS__)
#include <vxWorks.h>  /* needed for some arches to provide definition of
                         CPU_FAMILY */
#if (CPU_FAMILY == PPC)
#  include "arch/ppc.h"
#elif (CPU_FAMILY == COLDFIRE)
#  include "arch/mcf.h"
#elif (CPU_FAMILY == MC680X0)
#  include "arch/m68k.h"
#elif (CPU_FAMILY == I80X86)
#  include "arch/i86.h"
#elif (CPU_FAMILY == MIPS)
#  include "arch/mips.h"
#elif (CPU_FAMILY == ARM)
#  include "arch/arm.h"
#elif (CPU_FAMILY == SH)
#  include "arch/sh.h"
#elif (CPU_FAMILY == SIMNT) || (CPU_FAMILY == SIMLINUX)
#  include "arch/i86.h"
#elif (CPU_FAMILY == SIMSPARCSOLARIS)
#  include "arch/simso.h"
#else
#  error "Unknown CPU_FAMILY"
#endif /* CPU_FAMILY == */

#else
/* linux or cross-compile */

#if defined(ST_TARGETARCH_i86)
#  include "arch/i86.h"
#elif defined(ST_TARGETARCH_ppc)
#  include "arch/ppc.h"
#elif defined(ST_TARGETARCH_mcf)
#  include "arch/mcf.h"
#elif defined(ST_TARGETARCH_arm)
#  include "arch/arm.h"
#elif defined(ST_TARGETARCH_mips)
#  include "arch/mips.h"
#elif defined(ST_TARGETARCH_sh)
#  include "arch/sh.h"
#elif defined(ST_TARGETARCH_simso)
#  include "arch/simso.h"
#else
#  error "Unknown target"
#endif
#endif /* if linux */

#endif /* _CONTEXT_ARCH_H_ */
