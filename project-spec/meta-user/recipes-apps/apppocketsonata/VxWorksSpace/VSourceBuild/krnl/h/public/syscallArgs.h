/* syscallArgs.h - Top-level file to include the syscall argument structures */

/* 
Copyright (c) 2003-2005, 2009-2011 Wind River Systems, Inc. 

The right to copy, distribute, modify or otherwise make use 
of this software may be licensed only pursuant to the terms 
of an applicable Wind River license agreement. 
*/

/*
modification history
--------------------
01l,26sep11,mze  use generic name
01k,16sep11,mze  grab files from VSB
01j,08oct10,elp  updated for 64-bits simulator.
01i,29apr10,pad  Moved extern C statement after include statements.
01h,28jan10,jpb  Edited syscallArgs.h path.
01g,19jun09,mze  replacing PAD64
01f,15apr09,jb  64-bit version is premature - removing
01e,20jan09,jb   Adding 64-bit support
01d,18may05,rec  add coldfire support
01c,27apr04,mil  Fixed names for MIPS include files.
01b,15dec03,yvp  Changed arch-specific header file names.
01a,10dec03,yvp	 written.
*/

#ifndef __INCsyscallArgsh
#define __INCsyscallArgsh


#if (CPU_FAMILY==MIPS)
# if (_WRS_INT_REGISTER_SIZE == 8)
#   if (_BYTE_ORDER == _LITTLE_ENDIAN)
#     include <arch/vsb_gen_syscallArgsMIPS64LE.h>
#   elif (_BYTE_ORDER == _BIG_ENDIAN)
#     include <arch/vsb_gen_syscallArgsMIPS64BE.h>
#   else  /* _BYTE_ORDER */
#     error "Byte order cannot be determined\n"
#   endif  /* _BYTE_ORDER */
# elif (_WRS_INT_REGISTER_SIZE == 4)
#   include <arch/vsb_gen_syscallArgs.h>
# else  /* _WRS_INT_REGISTER_SIZE */
#   error "Register size cannot be determined\n"
# endif  /* _WRS_INT_REGISTER_SIZE */
#else
#include <arch/vsb_gen_syscallArgs.h>
#endif  /* CPU_FAMILY!=MIPS */


#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

#endif /* __INCsyscallArgsh */
