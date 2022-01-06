/* Copyright (c) 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

#ifndef INChpc_e500CoreEventConfig_h
#define INChpc_e500CoreEventConfig_h

#include <hpc/drv_evt_cfg/ppc/e500DrvEvtCfg.h>

#ifdef __cplusplus
extern "C" {
#endif

extern struct e500EventDescription hpcDrvEvtDescE500[];
extern struct driverInstE500 hpcHwDrvE500Core;
extern const unsigned int hpcE500NumEvents;

#ifdef __cplusplus
}
#endif
#endif /* INChpc_e500CoreEventConfig_h */
