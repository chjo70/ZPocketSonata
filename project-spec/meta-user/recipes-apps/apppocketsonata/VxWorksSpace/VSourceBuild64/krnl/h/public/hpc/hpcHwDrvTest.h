/* Copyright (c) 2010, 2014 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
12sep14,sdt  Correctly handle cores number in Core2 and Corei7Uncore API tests
09sep14,wzc  support arm hpc events.(US17715)
13mar14,wzc  Created (US17715)
*/

#ifndef INChpcHardwareDriverTest_h
#define INChpcHardwareDriverTest_h

#include <hpc/drv_evt_cfg/ppc/e500DrvEvtCfg.h>
#include <hpc/hpc_drv/ppc/e500Drv.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
	HPC_HW_DRV_TEST_P2020,
	HPC_HW_DRV_TEST_MPC8548,
	HPC_HW_DRV_TEST_MPC8540
} hpc_hw_drv_test_e500_type;

extern void hpcHwDrvApiTestPpcE500Init(int cores,
	hpc_hw_drv_test_e500_type type,
	struct e500EventDescription *pEvtDescDevice,
	struct driverInstE500 *pDrvInstDevice,
	const unsigned int numEventsDevice
	);

extern void hpcHwDrvApiTestCorei7UncoreInit(int cores);
extern void hpcHwDrvApiTestCore2Init(int cores);
extern void hpcHwDrvApiTestPpcE500McInit(int cores);
extern void hpcHwDrvApiTestArmCtxA8Init(void);
extern void hpcHwDrvApiTestArmCtxA9Init(void);
extern void hpcHwDrvApiTestArmCtxA15Init(void);

#ifdef __cplusplus
}
#endif
#endif /* INChpcHardwareDriverTest_h */
