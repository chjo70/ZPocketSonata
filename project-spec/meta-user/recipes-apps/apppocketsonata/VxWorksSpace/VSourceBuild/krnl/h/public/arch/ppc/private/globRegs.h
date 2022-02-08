/* globRegs.h - PowerPC portable library configuration */

/*
 * Copyright (c) 2014 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
04dec14,ylu   created
*/

/*
 * #pragma global_register can be used to force the diab compiler to avoid specific
 * registers in code generation by defining dummy variables as global registers
 * in all modules. This is useful to reserve a register for use with the linker
 * REGISTER specification
 */

#ifndef __INCglobRegsh
#define __INCglobRegsh

#if defined(__DCC__)
#ifdef _WRS_CONFIG_SMP
#pragma global_register ppc64Smp=r13
#endif /* _WRS_CONFIG_SMP */
#endif /* __DCC__ */

#endif /* __INCglobRegsh */

