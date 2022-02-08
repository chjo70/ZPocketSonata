/* vsbConfig.h - VSB Configuration header for Kernel side */

/*
 * Copyright (c) 2008, 2010-2012, 2014 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
24feb14,mze  change default to a warning
27jan12,mze  change location of default vsb config file
17jan11,mze  change default
06oct10,mze  change vsb default
27may10,mze  lp64 not lp46
21may10,mze  add case for 64bit
29apr10,pad  Moved extern C statement after include statements.
16sep08,jpb  Defect 133519.  Added check for _VSB_CONFIG_FILE.
04sep08,jpb  Added ignore macro.
15aug08,kk  created base on private/vsbConfigP.h
*/

/*
 * This file is used by any source code which utilizes VSB configuration
 * macros such as _WRS_CONFIG_SMP.
 */

#ifndef __INCvsbConfig_h
#define __INCvsbConfig_h

/* 
 * If the macro _VSB_CONFIG_FILE is not defined (in a case such as where a user
 * application is built not using WorkBench), include 
 * the default UP 32 bit or 64 bit vsbConfig.h header file.  If it is defined, use the file 
 * set to _VSB_CONFIG_FILE. 
 */

#ifndef _VSB_CONFIG_FILE

$(error "VSB configuration not associated properly")


#else
#include _VSB_CONFIG_FILE
#endif /* ! _VSB_CONFIG_FILE */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /*__INCvsbConfig_h */

