/* Copyright (c) 2014 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
09sep14,wzc  support arm hpc events.(US17715)
*/

/*
DESCRIPTION
*/
#ifndef INChpc_armCtxA15EventConfig_h
#define INChpc_armCtxA15EventConfig_h

#include <hpc/drv_evt_cfg/arm/armDrvEvtCfg.h>

#ifdef __cplusplus
extern "C" {
#endif

extern struct armEventDescription hpcDrvEvtDescArmCtxA15[];
extern struct driverInstArm hpcHwDrvArmCtxA15;
extern const unsigned int hpcArmCtxA15NumEvents;

#ifdef __cplusplus
}
#endif
#endif /* INChpc_armCtxA15EventConfig_h */
