/* Copyright (c) 2011 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

#ifndef INChpc_e500Core_h
#define INChpc_e500Core_h

#include <hpc/drv_evt_cfg/ppc/e500DrvEvtCfg.h>

#ifdef __cplusplus
extern "C" {
#endif

extern STATUS hpcCafeE500CoreDrvCfgInit
    (
    void * (*pMallocFunc)(size_t),
    void   (*pFreeFunc)(void *),
    int    numCores,
    struct e500EventDescription *pEvtDesc,
    const unsigned int numEvents,
    struct driverInstE500 *pDrvInst
    );

extern STATUS hpcCafeE500CoreDrvCfgFinit
    (
    struct hpcDriverConfig *pHpcDriverConfig
    );

extern struct hpcDriverConfig * hpcCafeE500DrvCfgGet(void);

#ifdef __cplusplus
}
#endif
#endif /* INChpc_e500Core_h */
