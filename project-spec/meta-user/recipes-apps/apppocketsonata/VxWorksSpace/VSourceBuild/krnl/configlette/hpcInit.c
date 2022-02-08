/* Copyright (c) 2010-2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
26may15,gxu  Support HPC on itl_64_vx7 new-style BSP.(US50880)
09sep14,wzc  support arm hpc events.(US17715)
13mar14,wzc  support arm hpc(US17715)
*/

#include <vxWorks.h>
#include <hpc/hpc_ep.h>

static const int num_virt_ctrs = 50; /* WRS_TODO: this could be a CDF setting */

#if defined(INCLUDE_HPC_ARM_CORTEX_A8)
#include <hpc/drv_evt_cfg/arm/armCtxA8EvtCfg.h>
#include <hpc/drv_evt_cfg/arm/armDrvCfg.h>
#include <hpc/drv_evt_cfg/arm/armDrvSet.h>
#endif

#if defined(INCLUDE_HPC_ARM_CORTEX_A9)
#include <hpc/drv_evt_cfg/arm/armCtxA9EvtCfg.h>
#include <hpc/drv_evt_cfg/arm/armDrvCfg.h>
#include <hpc/drv_evt_cfg/arm/armDrvSet.h>
#endif

#if defined(INCLUDE_HPC_ARM_CORTEX_A15)
#include <hpc/drv_evt_cfg/arm/armCtxA15EvtCfg.h>
#include <hpc/drv_evt_cfg/arm/armDrvCfg.h>
#include <hpc/drv_evt_cfg/arm/armDrvSet.h>
#endif

#if defined(INCLUDE_HPC_E500_CORE)
#include <hpc/drv_evt_cfg/ppc/e500CoreEvtCfg.h>
#include <hpc/drv_evt_cfg/ppc/e500CoreDrvCfg.h>
#endif

#if defined(INCLUDE_HPC_E500MC_CORE)
#include <hpc/drv_evt_cfg/ppc/e500CoreDrvCfg.h>
#include <hpc/drv_evt_cfg/ppc/e500McCoreEvtCfg.h>
#endif

#if defined(INCLUDE_HPC_MPC8548_DEVICE)
#define ENABLE_E500_DEVICE
#include <hpc/drv_evt_cfg/ppc/mpc8548EvtCfg.h>
#endif

#if defined(INCLUDE_HPC_MPC8540_DEVICE)
#define ENABLE_E500_DEVICE
#include <hpc/drv_evt_cfg/ppc/mpc8540EvtCfg.h>
#endif

#if defined(INCLUDE_HPC_FSL_P2020_DEVICE)
#define ENABLE_E500_DEVICE
#include <hpc/drv_evt_cfg/ppc/fslP2020EvtCfg.h>
#endif

#ifdef ENABLE_E500_DEVICE
#include <hpc/drv_evt_cfg/ppc/e500DeviceDrvCfg.h>
#include <hpc/drv_evt_cfg/ppc/e500DrvSet.h>
#endif

#if defined(INCLUDE_HPC_I86_ARCH_PM)
#include <hpc/drv_evt_cfg/i86/i86ArchPmEvtCfg.h>
static struct hpcDriverConfig *pArchV1DrvCfg;
static struct hpcDriverConfig *pArchV2DrvCfg;
#endif

#if defined(INCLUDE_HPC_I86_CORE2)
#include <hpc/drv_evt_cfg/i86/i86core2EvtCfg.h>
#elif defined(INCLUDE_HPC_I86_COREI7)
#include <hpc/drv_evt_cfg/i86/i86NehalemEvtCfg.h>
#endif

#if defined(INCLUDE_HPC_I86_COREI7_UNCORE)
#include <hpc/drv_evt_cfg/i86/i86NehalemUncEvtCfg.h>
#endif

void hpcCfgInit(void)
    {
#if defined(INCLUDE_HPC_I86_ARCH_PM)  \
    || defined(INCLUDE_HPC_E500_CORE) \
    || defined(INCLUDE_HPC_ARM_CORTEX_A8)   \
    || defined(INCLUDE_HPC_ARM_CORTEX_A9)   \
    || defined(INCLUDE_HPC_ARM_CORTEX_A15)  \
    || defined(INCLUDE_HPC_E500MC_CORE) \
    || defined(ENABLE_E500_DEVICE)
    STATUS status;
#endif
    int rc;
#if defined(INCLUDE_HPC_I86_ARCH_PM)
    unsigned int numNonArchEvents;
    struct i86Arch1EventDescription *pArchV1EvtDesc = NULL;
    pArchV1DrvCfg = pArchV2DrvCfg = NULL;

#  if defined(INCLUDE_HPC_I86_CORE2)
    numNonArchEvents = HPC_NUM_I86_CORE2_EVENTS;
    pArchV1EvtDesc = x86core2EvtDesc;
#  elif defined(INCLUDE_HPC_I86_COREI7)
    numNonArchEvents = HPC_NUM_I86_COREI7_EVENTS;
    pArchV1EvtDesc = x86NehalemEvtDesc;
#  else
    numNonArchEvents = 0;
#  endif
#endif
#if defined(INCLUDE_HPC_MPC8540_DEVICE)
    struct e500EventDescription *pE500DeviceEvtDesc = hpcDrvEvtDescMpc8540;
    struct driverInstE500 *pE500DeviceDrvInst = &hpcHwDrvMpc8540;
    EVENT_SETTING_GET_FUNC pSettingsGetFunc = e500DevEventSettingsGet;
    unsigned int e500DeviceNumEvents = hpcMpc8540NumEvents;
#endif
#if defined(INCLUDE_HPC_MPC8548_DEVICE)
    struct e500EventDescription *pE500DeviceEvtDesc = hpcDrvEvtDescMpc8548;
    struct driverInstE500 *pE500DeviceDrvInst = &hpcHwDrvMpc8548;
    EVENT_SETTING_GET_FUNC pSettingsGetFunc = e500DevEventSettingsGet;
    unsigned int e500DeviceNumEvents = hpcMpc8548NumEvents;
#endif
#if defined(INCLUDE_HPC_FSL_P2020_DEVICE)
    struct e500EventDescription *pE500DeviceEvtDesc = hpcDrvEvtDescFslP2020;
    struct driverInstE500 *pE500DeviceDrvInst = &hpcHwDrvP2020;
    unsigned int e500DeviceNumEvents = hpcHwDrvP2020NumEvents;
    /* the p2020 device counters does not use the offset of 64 for counter
     * specific events */
    EVENT_SETTING_GET_FUNC pSettingsGetFunc = e500CoreEventSettingsGet;
#endif

    rc = hpc_init(malloc, free, num_virt_ctrs);

    if (rc != CAFE_OK)
        {
        printf ("hpc_init returned error %d\n", rc);
        return;
        }

#if defined(INCLUDE_HPC_I86_ARCH_PM)
#ifndef _WRS_CONFIG_VXBUS
    hpcI86Init();
#endif
#if (I86_CORE2_HPC_ERRATA_CPUID_EDX==0)
    status = hpcI86ArchPerfMonInit(malloc, free, 0, 0);
#else
    status = hpcI86ArchPerfMonInit(malloc, free, 1, I86_CORE2_HPC_ERRATA_CPUID_EDX);
#endif
    if (status != OK)
        printf ("unable to init I86 Arch PM config %d\n", status);

    status = hpcHwI86ArchPm1DriverInit();
    if (status != OK)
        printf ("unable to init I86 Arch PM 1 hpc driver %d\n", status);

    status = hpcHwI86ArchPm2DriverInit();
    if (status != OK)
        printf ("unable to init I86 Arch PM 2 hpc driver %d\n", status);

    pArchV1DrvCfg = i86ArchPmV1Configure(vxCpuConfiguredGet(),
			numNonArchEvents, pArchV1EvtDesc);
    if (pArchV1DrvCfg == NULL)
        printf ("unable to configure i86 pmon arch1 driver\n");

    pArchV2DrvCfg = i86ArchPmV2Configure(vxCpuConfiguredGet());
    if (pArchV2DrvCfg == NULL)
        printf ("unable to configure i86 pmon arch2 driver\n");

    if (pArchV2DrvCfg != NULL)
        {
        rc = hpc_hw_driver_register(pArchV2DrvCfg);
        if (rc != CAFE_OK)
            printf ("unable to register x86 arch2 hpc driver %d\n", rc);
        }

    if (pArchV1DrvCfg != NULL)
        {
        rc = hpc_hw_driver_register(pArchV1DrvCfg);
        if (rc != CAFE_OK)
            printf ("unable to register x86 arch1 hpc driver %d\n", rc);
        }
#endif

#ifdef INCLUDE_HPC_I86_COREI7_UNCORE
    status = hpcI86NehalemUncInit(0); /* uncore perf counter ISR mapped to core0 */
    if (status != OK)
        printf ("unable to init corei7 (uncore) hpc driver config %d\n", status);
    rc = hpc_hw_driver_register(hpcI86NehalemUncDrvCfgGet());
    if (rc != CAFE_OK)
        printf ("unable to register corei7 (uncore, general purpose) device hpc driver %d\n", rc);
    rc = hpc_hw_driver_register(hpcI86NehalemUncFixedDrvCfgGet());
    if (rc != CAFE_OK)
        printf ("unable to register corei7 (uncore, fixed) device hpc driver %d\n", rc);
#endif

#if defined(INCLUDE_HPC_E500_CORE) || defined(ENABLE_E500_DEVICE) || \
    defined(INCLUDE_HPC_E500MC_CORE)
    status = hpcHwE500DriverInit();
    if (status != OK)
        printf ("unable to init e500 core hpc driver %d\n", status);
#endif

#if defined(ENABLE_E500_DEVICE)
    status = hpcCafeE500DeviceDrvCfgInit(malloc, free, pE500DeviceEvtDesc,
		    e500DeviceNumEvents, pE500DeviceDrvInst, pSettingsGetFunc);
    if (status != OK)
        printf ("unable to init e500 device hpc driver config %d\n", status);
    /* register driver with HPC framework */
    rc = hpc_hw_driver_register(hpcCafeE500DeviceDrvCfgGet());
    if (rc != CAFE_OK)
        printf ("unable to register e500 device hpc driver %d\n", rc);
#endif

#ifdef INCLUDE_HPC_E500_CORE
    status = hpcCafeE500CoreDrvCfgInit(malloc, free, vxCpuConfiguredGet(),
		    hpcDrvEvtDescE500, hpcE500NumEvents, &hpcHwDrvE500Core);
    if (status != OK)
        printf ("unable to init e500 core hpc driver config %d\n", status);
    /* register drivers with HPC framework */
    rc = hpc_hw_driver_register(hpcCafeE500DrvCfgGet());
    if (rc != CAFE_OK)
        printf ("unable to register e500 core hpc driver %d\n", rc);
#endif

#ifdef INCLUDE_HPC_E500MC_CORE
    status = hpcCafeE500CoreDrvCfgInit(malloc, free, vxCpuConfiguredGet(),
		    hpcEvtDescE500Mc, hpcE500McNumEvents, &hpcHwDrvE500McCore);
    if (status != OK)
        printf ("unable to init e500mc core hpc driver config %d\n", status);
    /* register drivers with HPC framework */
    rc = hpc_hw_driver_register(hpcCafeE500DrvCfgGet());
    if (rc != CAFE_OK)
        printf ("unable to register e500mc core hpc driver %d\n", rc);
#endif

#if defined(INCLUDE_HPC_ARM_CORTEX_A8)
    status = hpcCafeArmDrvCfgInit(malloc, free, vxCpuConfiguredGet(),
             hpcDrvEvtDescArmCtxA8, hpcArmCtxA8NumEvents, &hpcHwDrvArmCtxA8);
    if (status != OK)
        printf ("unable to init arm pmu driver config %d\n", status);
    /* register drivers with HPC framework */
    rc = hpc_hw_driver_register(hpcCafeArmDrvCfgGet());
    if (rc != CAFE_OK)
        printf ("unable to register arm pmu driver %d\n", rc);
#endif

#if defined(INCLUDE_HPC_ARM_CORTEX_A9)
    status = hpcCafeArmDrvCfgInit(malloc, free, vxCpuConfiguredGet(),
             hpcDrvEvtDescArmCtxA9, hpcArmCtxA9NumEvents, &hpcHwDrvArmCtxA9);
    if (status != OK)
        printf ("unable to init arm pmu driver config %d\n", status);
    /* register drivers with HPC framework */
    rc = hpc_hw_driver_register(hpcCafeArmDrvCfgGet());
    if (rc != CAFE_OK)
        printf ("unable to register arm pmu driver %d\n", rc);
#endif

#if defined(INCLUDE_HPC_ARM_CORTEX_A15)
    status = hpcCafeArmDrvCfgInit(malloc, free, vxCpuConfiguredGet(),
             hpcDrvEvtDescArmCtxA15, hpcArmCtxA15NumEvents, &hpcHwDrvArmCtxA15);
    if (status != OK)
        printf ("unable to init arm pmu driver config %d\n", status);
    /* register drivers with HPC framework */
    rc = hpc_hw_driver_register(hpcCafeArmDrvCfgGet());
    if (rc != CAFE_OK)
        printf ("unable to register arm pmu driver %d\n", rc);
#endif

    CAFE_LOCK();
    rc = hpc_register_configuration();
    CAFE_UNLOCK();
    if (rc != CAFE_OK)
        printf ("hpc_register_configuration returned error %d\n", rc);
    }

void hpcCfgFinit(void)
    {
#if defined(INCLUDE_HPC_I86_ARCH_PM)  \
    || defined(INCLUDE_HPC_E500_CORE) \
    || defined(INCLUDE_HPC_ARM_CORTEX_A8)   \
    || defined(INCLUDE_HPC_ARM_CORTEX_A9)   \
    || defined(INCLUDE_HPC_ARM_CORTEX_A15)  \
    || defined(INCLUDE_HPC_E500MC_CORE) \
    || defined(ENABLE_E500_DEVICE) \
    || defined (INCLUDE_HPC_I86_COREI7_UNCORE)
    STATUS status;
#endif
    int rc;

#if defined(INCLUDE_HPC_I86_ARCH_PM)
    if (pArchV1DrvCfg != NULL)
        {
        rc = hpc_hw_driver_unregister(pArchV1DrvCfg);
        if (rc != CAFE_OK)
            printf ("unable to unregister i86 arch v1 hpc driver %d\n", rc);
        status = i86ArchPmV1Free(pArchV1DrvCfg);
        if (status != OK)
            printf ("i86ArchPmV1Free error\n");
        else
            pArchV1DrvCfg = NULL;
        }

    if (pArchV2DrvCfg != NULL)
        {
        rc = hpc_hw_driver_unregister(pArchV2DrvCfg);
        if (rc != CAFE_OK)
            printf ("unable to unregister i86 arch v2 hpc driver %d\n", rc);
        status = i86ArchPmV2Free(pArchV2DrvCfg);
        if (status != OK)
            printf ("i86ArchPmV2Free error\n");
        else
            pArchV1DrvCfg = NULL;
        }

    status = hpcHwI86ArchPm1DriverFinit();
    if (status != OK)
        printf ("unable to finalize I86 Arch PM 1 hpc driver %d\n", status);
    status = hpcHwI86ArchPm2DriverFinit();
    if (status != OK)
        printf ("unable to finalize I86 Arch PM 2 hpc driver %d\n", status);
#endif

#ifdef INCLUDE_HPC_I86_COREI7_UNCORE
    rc = hpc_hw_driver_unregister(hpcI86NehalemUncDrvCfgGet());
    if (rc != CAFE_OK)
        printf ("unable to unregister corei7 (uncore, general purpose) device hpc driver %d\n", rc);
    rc = hpc_hw_driver_unregister(hpcI86NehalemUncFixedDrvCfgGet());
    if (rc != CAFE_OK)
        printf ("unable to unregister corei7 (uncore, fixed) device hpc driver %d\n", rc);
    status = hpcI86NehalemUncFinit();
    if (status != OK)
        printf ("unable to finit corei7 (uncore) hpc driver config %d\n", status);
#endif

#ifdef INCLUDE_HPC_E500_CORE
    rc = hpc_hw_driver_unregister(hpcCafeE500DrvCfgGet());
    if (rc != CAFE_OK)
        printf ("unable to unregister e500 core hpc driver %d\n", rc);
    status = hpcCafeE500CoreDrvCfgFinit(hpcCafeE500DrvCfgGet());
    if (status != OK)
        printf ("error from hpcCafeE500CoreDrvCfgFinit %d\n", status);
#endif

#ifdef INCLUDE_HPC_E500MC_CORE
    rc = hpc_hw_driver_unregister(hpcCafeE500DrvCfgGet());
    if (rc != CAFE_OK)
        printf ("unable to unregister e500mc core hpc driver %d\n", rc);
    status = hpcCafeE500CoreDrvCfgFinit(hpcCafeE500DrvCfgGet());
    if (status != OK)
        printf ("error from hpcCafeE500CoreDrvCfgFinit %d\n", status);
#endif

#ifdef ENABLE_E500_DEVICE
    rc = hpc_hw_driver_unregister(hpcCafeE500DeviceDrvCfgGet());
    if (rc != CAFE_OK)
        printf ("unable to unregister e500 device hpc driver %d\n", rc);
    status = hpcCafeE500DeviceDrvCfgFinit(hpcCafeE500DeviceDrvCfgGet());
    if (status != OK)
        printf ("error from hpcCafeE500DeviceDrvCfgInit %d\n", status);
#endif

#if defined(INCLUDE_HPC_E500_CORE) || defined(INCLUDE_HPC_E500MC_CORE) || \
    defined(ENABLE_E500_DEVICE)
    status = hpcHwE500DriverFinit();
    if (status != OK)
        printf ("unable to finit e500 core hpc driver %d\n", status);
#endif

#if defined(INCLUDE_HPC_ARM_CORTEX_A8) || defined(INCLUDE_HPC_ARM_CORTEX_A9) || defined(INCLUDE_HPC_ARM_CORTEX_A15)
    rc = hpc_hw_driver_unregister(hpcCafeArmDrvCfgGet());
    if (rc != CAFE_OK)
        printf ("unable to unregister arm pmu driver %d\n", rc);
    status = hpcCafeArmDrvCfgFinit(hpcCafeArmDrvCfgGet());
    if (status != OK)
        printf ("error from hpcCafeArmDrvCfgFinit %d\n", status);
#endif

    rc = hpc_finit();
    if (rc != CAFE_OK)
        printf ("hpc_finit returned error %d\n", rc);

    CAFE_LOCK();
    rc = hpc_unregister_configuration();
    CAFE_UNLOCK();
    if (rc != CAFE_OK)
        printf ("hpc_unregister_configuration returned error %d\n", rc);
    }

#if defined(INCLUDE_ANALYSIS_HPC_TEST_HW)
#include <hpc/hpc_ep_test.h>

void hpcCfgTestInit(void)
    {
#if defined(INCLUDE_HPC_E500_CORE) && defined(INCLUDE_HPC_FSL_P2020_DEVICE)
    hpc_init_fsl_p2020_tests();
#elif defined(INCLUDE_HPC_E500MC_CORE)
    hpc_init_e500mc_tests();
#elif defined(INCLUDE_HPC_E500_CORE) && defined(INCLUDE_HPC_MPC8540_DEVICE)
    hpc_init_mpc_8540_tests();
#elif defined(INCLUDE_HPC_E500_CORE) && defined(INCLUDE_HPC_MPC8548_DEVICE)
    hpc_init_mpc_8548_tests();
#elif defined(INCLUDE_HPC_I86_CORE2)
    hpc_init_core2_tests();
#elif defined(INCLUDE_HPC_I86_COREI7_UNCORE)
    hpc_init_corei7_tests();
#elif defined(INCLUDE_HPC_ARM_CORTEX_A8)
    hpc_init_arm_cortex_a8_tests();
#elif defined(INCLUDE_HPC_ARM_CORTEX_A9)
    hpc_init_arm_cortex_a9_tests();
#elif defined(INCLUDE_HPC_ARM_CORTEX_A15)
    hpc_init_arm_cortex_a15_tests();
#endif
    }
#endif /* INCLUDE_ANALYSIS_HPC_TEST_HW */

#if defined(INCLUDE_ANALYSIS_HPC_API_TEST_HW)
#include <hpc/hpcHwDrvTest.h>

void hpcCfgHpcHwApiTestInit(void)
    {
#if defined(INCLUDE_HPC_E500_CORE) && defined(INCLUDE_HPC_FSL_P2020_DEVICE)
    hpcHwDrvApiTestPpcE500Init(vxCpuConfiguredGet(), HPC_HW_DRV_TEST_P2020,
        hpcDrvEvtDescFslP2020, &hpcHwDrvP2020, hpcHwDrvP2020NumEvents);
#elif defined(INCLUDE_HPC_E500_CORE) && defined(INCLUDE_HPC_MPC8540_DEVICE)
    hpcHwDrvApiTestPpcE500Init(vxCpuConfiguredGet(), HPC_HW_DRV_TEST_MPC8540,
        hpcDrvEvtDescMpc8540, &hpcHwDrvMpc8540, hpcMpc8540NumEvents);
#elif defined(INCLUDE_HPC_E500_CORE) && defined(INCLUDE_HPC_MPC8548_DEVICE)
    hpcHwDrvApiTestPpcE500Init(vxCpuConfiguredGet(), HPC_HW_DRV_TEST_MPC8548,
        hpcDrvEvtDescMpc8548, &hpcHwDrvMpc8548, hpcMpc8548NumEvents);
#elif defined(INCLUDE_HPC_E500MC_CORE)
    hpcHwDrvApiTestPpcE500McInit(vxCpuConfiguredGet());
#elif defined(INCLUDE_HPC_I86_CORE2)
    hpcHwDrvApiTestCore2Init(vxCpuConfiguredGet());
#elif defined(INCLUDE_HPC_I86_COREI7_UNCORE)
    hpcHwDrvApiTestCorei7UncoreInit(vxCpuConfiguredGet());
#elif defined(INCLUDE_HPC_ARM_CORTEX_A8)
    hpcHwDrvApiTestArmCtxA8Init();
#elif defined(INCLUDE_HPC_ARM_CORTEX_A9)
    hpcHwDrvApiTestArmCtxA9Init();
#elif defined(INCLUDE_HPC_ARM_CORTEX_A15)
    hpcHwDrvApiTestArmCtxA15Init();
#endif
    }
#endif /* INCLUDE_ANALYSIS_HPC_TEST_HW */
