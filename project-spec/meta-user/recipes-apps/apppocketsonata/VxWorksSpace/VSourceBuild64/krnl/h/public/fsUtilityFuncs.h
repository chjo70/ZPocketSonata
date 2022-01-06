
/* fsUtilityFuncs.h - File system utility funcs header */

/*
 * Copyright (c) 2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
22may15,jdw  Created

*/

#ifndef __INCiosInitFuncsh
#define __INCiosInitFuncsh

#include <vxWorks.h>

extern STATUS fsDeviceValidateMount( const char *pDevName, 
                                     UINT32 timeOut_s );

extern STATUS fsDeviceRename( const char *pOrigDevName,
                              const char *pNewDevName, 
                              UINT32 timeOut_s );

#endif /* __INCiosInitFuncsh */
