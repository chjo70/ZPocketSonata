/* vsbConfig.h - VSB Configuration header for User side*/

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
24feb14,mze  make the default into a warning
27jan12,mze  change default vsb config location
17jan11,mze  changes to default
29jul10,pad  Moved extern C statement after include statements.
21may10,mze  add case for 64bit
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
 * the default UP 32 bit 64 bit vsbConfig.h header file.  If it is defined, use the file 
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

/* Any C keywords must be added here */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /*__INCvsbConfig_h */

