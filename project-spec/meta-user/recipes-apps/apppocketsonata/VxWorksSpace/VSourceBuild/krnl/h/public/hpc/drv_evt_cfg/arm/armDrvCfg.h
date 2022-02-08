/* Copyright (c) 2014 Wind River Systems, Inc.
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

#ifndef INChpc_arm_h
#define INChpc_arm_h

#include <hpc/drv_evt_cfg/arm/armDrvEvtCfg.h>

#ifdef __cplusplus
extern "C" {
#endif

extern STATUS hpcCafeArmDrvCfgInit
    (
    void * (*pMallocFunc)(size_t),
    void   (*pFreeFunc)(void *),
    int    numCores,
    struct armEventDescription *pEvtDesc,
    const unsigned int numEvents,
    struct driverInstArm *pDrvInst
    );

extern STATUS hpcCafeArmDrvCfgFinit
    (
    struct hpcDriverConfig *pHpcDriverConfig
    );

extern struct hpcDriverConfig * hpcCafeArmDrvCfgGet(void);

#ifdef __cplusplus
}
#endif
#endif /* INChpc_arm_h */
