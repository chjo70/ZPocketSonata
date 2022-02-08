/* vxPortableP.h - Portable defines for the user-mode libraries */

/*
 * Copyright (c) 2007, 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement. 
 */

/*
modification history
--------------------
01d,29jul10,pad  Moved extern C statement after include statements.
01c,11nov09,cww  added _WRS_PORTABLE_ffs64Lib
01b,16may07,jmg  Added _WRS_PORTABLE_vxAtomicLib
01a,03may07,zl   created.
*/

/*
DESCRIPTION
This header contains the portable defines for specific libraries. A 
library or routine defined as PORTABLE will use the shared C implementation 
of the library or routine.

All libraries that provides portable implementation must define the 
portable macro here, and include this file:

  #include <vxWorks.h>
  #include <private/vxPortableP.h>

  #ifdef _WRS_PORTABLE_foo
  ...
  #endif
  

An architecture that wishes to provide a special implementation of a 
routine or library should undefine the specific macro in it's own 
<arch/<arch_dir>/private/vxPortableArchP.h>:

  #ifndef PORTABLE
  #undef _WRS_PORTABLE_foo
  #undef _WRS_PORTABLE_foo
  #endif

The source file that provides the architecture specific implementation
also has to include <private/vxPortableP.h>:

  #include <vxWorks.h>
  #include <private/vxPortableP.h>

  #ifndef _WRS_PORTABLE_foo
  ...
  #endif
*/

#ifndef __INCuserVxPortablePh
#define __INCuserVxPortablePh

#define _WRS_PORTABLE_bLib
#define _WRS_PORTABLE_dllLib
#define _WRS_PORTABLE_ffsLib
#define _WRS_PORTABLE_ffs64Lib
#define _WRS_PORTABLE_ffsTbl
#define _WRS_PORTABLE_sllLib
#define _WRS_PORTABLE_swab
#define _WRS_PORTABLE_trcLib
#define _WRS_PORTABLE_vxAtomicLib

#include ARCH_HEADER(private/vxPortableArchP.h)

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

#endif /* __INCuserVxPortablePh */
