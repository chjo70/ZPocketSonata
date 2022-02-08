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
28mar14,sdt  fixed build issue in tcf-tools env.
13mar14,wzc  support arm hpc(US17715)
*/

/*
DESCRIPTION
*/

#ifndef INChpc_armDriverEventConfig_h
#define INChpc_armDriverEventConfig_h

#include <hpc/drv_evt_cfg/hpcDrvEvtCfg.h>

#ifdef __cplusplus
extern "C" {
#endif

struct armEventDescription
    {
    const char * eventVtStr;
    const struct hpcEventSettingsConst hpcEventSettingsConst;
    struct armSettings evtSettings;
    };

#ifdef __cplusplus
}
#endif
#endif /* INChpc_armDriverEventConfig_h */
