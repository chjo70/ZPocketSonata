/* intrinsics.c - force-link of toolchain dependent C intrinsics */

/*
 * Copyright (c) 2002, 2009, 2010, 2014, 2016 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
06may16,mcm  Update for LLVM
16may14,rlp  Removed WDB references (WB4-1735).
10mar10,gvm  updates for icc
22jan10,v_r  Enabled back intrinsics support now that updated libgcc is
             available.
03jun09,v_r  LP64 adaptation: disabled intrinsics support until libgcc is
             compatible with kernel code model.
22apr02,sn   SPR 76106 - added common (toolchain independent) intrinsics
04feb02,sn   wrote
*/

/*
DESCRIPTION
This file is used to include support for toolchain dependent 
intrinsics.
 
NOMANUAL
*/

#include <vxWorks.h>

/* pull in intrinsics if dynamic module downloading is enabled */
#if (defined(INCLUDE_DEBUG_AGENT) || defined(INCLUDE_LOADER))
#define INCLUDE_INTRINSICS
#endif

#include TOOL_HEADER(intrinsics.h)

extern char __common_intrinsicsInit;

#ifdef INCLUDE_GNU_INTRINSICS
extern char __gcc_intrinsicsInit;

char * __includeGnuIntrinsics [] = 
    {
    &__gcc_intrinsicsInit,
    &__common_intrinsicsInit
    };
#endif

#ifdef INCLUDE_DIAB_INTRINSICS
extern char __diab_intrinsics_impfpInit;
extern char __diab_intrinsics_implInit;
extern char __diab_intrinsics_tornInit;

char * __includeDiabIntrinsics [] =
    {
    &__diab_intrinsics_impfpInit,
    &__diab_intrinsics_implInit,
    &__diab_intrinsics_tornInit,
    &__common_intrinsicsInit
    };
#endif

#ifdef	INCLUDE_ICC_INTRINSICS
extern char __icc_intrinsicsInit;
char * __includeIccIntrinsics [] = 
    {
    &__icc_intrinsicsInit,
    &__common_intrinsicsInit
    };
#endif

#ifdef	INCLUDE_LLVM_INTRINSICS
extern char __llvm_intrinsicsInit;
char * __includeLLvmIntrinsics [] = 
    {
    &__llvm_intrinsicsInit,
    &__common_intrinsicsInit
    };
#endif
