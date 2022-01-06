/* Copyright (c) 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

#ifndef INChpc_e500DriverEventConfig_h
#define INChpc_e500DriverEventConfig_h

#include <hpc/drv_evt_cfg/hpcDrvEvtCfg.h>

#ifdef __cplusplus
extern "C" {
#endif

/* note: the first variable must be eventVtStr because struct hpcEventDescriptor
 * is overlaid on this data structure. */
struct e500EventDescription
    {
    const char * eventVtStr;
    const struct hpcEventSettingsConst hpcEventSettingsConst;
    const char * eventDescStr;
    };

#ifdef __cplusplus
}
#endif
#endif /* INChpc_e500DriverEventConfig_h */
