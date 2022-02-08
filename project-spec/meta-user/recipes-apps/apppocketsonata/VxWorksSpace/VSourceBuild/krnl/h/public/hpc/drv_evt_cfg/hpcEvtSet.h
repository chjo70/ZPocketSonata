/* Copyright (c) 2010, 2014 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
13mar14,wzc  support arm hpc(US17715)
*/

/*
DESCRIPTION
*/

#ifndef INChpc_hpcEventSettings_h
#define INChpc_hpcEventSettings_h

#include <hpc/hpc_drv/ppc/e500Drv.h>
#include <hpc/hpc_drv/arm/armDrv.h>
#include <hpc/hpc_drv/i86/i86ArchPm1Drv.h>
#include <hpc/hpc_drv/i86/i86ArchPm2Drv.h>

#ifdef __cplusplus
extern "C" {
#endif

union eventSettings
    {
    struct armSettings		arm;
    struct e500Settings		e500;
    struct i86Arch1Settings	i86Arch1;
    struct i86Arch2Settings	i86Arch2;
    };

#ifdef __cplusplus
}
#endif
#endif /* INChpc_hpcEventSettings_h */
