/* cplusgnuLang.c - force-link of C++ compiler support  */

/* Copyright 2000,2001,2003,2014 Wind River Systems, Inc. */

/*
modification history
--------------------
10mar14,mcm  Fix for VXW7-2567 ; ensuring future GCC versions are also handled
07mar14,mcm  Fix for VXW7-2495 ; excluding libgcc_eh intrinsic for 4.3.3
03jun03,sn   added gcc 3.x support
04apr03,dtr  Changes for GCC3.x.
06nov01,sn   use new prefixed names
24jan01,sn   use wrapper symbols
11oct00,sn   wrote
*/

/*
DESCRIPTION
This file pulls in C++ compiler (libgcc) support.
 
NOMANUAL
*/

#ifndef __INCcplusLibgccC
#define __INCcplusLibgccC

extern char __gplusplus_intrinsicsInit;
#if (__GNUC___ >= 5) || ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 8))
extern char __gcc_eh_intrinsicsInit;
#endif

char * __cplusLangObjs [] =
{
    &__gplusplus_intrinsicsInit,
#if (__GNUC__ >= 5) || ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 8))
    &__gcc_eh_intrinsicsInit,
#endif
    0
};
#endif /* __INCcplusLibgccC */
