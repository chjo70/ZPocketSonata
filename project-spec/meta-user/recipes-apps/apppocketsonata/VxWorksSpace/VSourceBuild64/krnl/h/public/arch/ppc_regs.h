/* Copyright (c) 2005-2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
16jan15,wzc  ppc64 support.(US49903)
*/

#ifndef ppc_regs_h
#define ppc_regs_h

#if defined(MODULE)
#  include <linux/types.h>
#else
#  if defined(__VXWORKS__) && (_WRS_VXWORKS_MAJOR == 6) && (_WRS_VXWORKS_MINOR >= 9)
#    include <stdint.h>
#  endif
#endif

#ifdef __cplusplus 
    extern "C" {
#endif

typedef unsigned long ppc_reg_t;

#if !defined(__VXWORKS__)
typedef struct {
    ppc_reg_t lr;
    ppc_reg_t pc;
    ppc_reg_t gpr[13];
} REG_SET;
      
#define reg_sp gpr[1]
#define reg_dp ebp
#define reg_pc pc

typedef struct fpregSet
{
  double fpr[32];   /* 32 doubles     : 256 bytes */
  int fpcsr;        /* control/status :   4 bytes */
  int pad;          /* pad to 8 byte boundary     */
} FPREG_SET;

#endif  /* if !defined(__VXWORKS__) */

#if defined(__cplusplus) 
}
#endif

#endif
