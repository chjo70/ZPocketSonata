/* Copyright (c) 2011 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

#ifndef INChpc_e500DeviceDriverConfig_h
#define INChpc_e500DeviceDriverConfig_h

#include <hpc/drv_evt_cfg/ppc/e500DrvEvtCfg.h>

#ifdef __cplusplus
extern "C" {
#endif

extern STATUS hpcCafeE500DeviceDrvCfgInit
    (
    void * (*pMallocFunc)(size_t),
    void   (*pFreeFunc)(void *),
    struct e500EventDescription *pEvtDesc,
    const unsigned int numEvents,
    struct driverInstE500 *pDrvInst,
    EVENT_SETTING_GET_FUNC pSettingGetFunc
    );

extern STATUS hpcCafeE500DeviceDrvCfgFinit
    (
    struct hpcDriverConfig *pHpcDriverConfig
    );

extern struct hpcDriverConfig * hpcCafeE500DeviceDrvCfgGet(void);

#ifdef __cplusplus
}
#endif
#endif /* INChpc_e500DeviceDriverConfig_h */
