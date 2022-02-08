/* Copyright (c) 2014 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
28mar14,sdt  fixed build issue in tcf-tools env.
13mar14,wzc  support arm hpc(US17715)
*/

#ifndef INChpc_armDrv_h
#define INChpc_armDrv_h
#ifdef __cplusplus
extern "C" {
#endif

#include <hpc/drv_evt_cfg/arm/armvxw.h>

/*****************************************************************************
 * arm HW Driver specific
 */

struct armSettings
    {
    unsigned int	evtCode;
    unsigned int	ctrMask;
    };

struct driverInstArm
    {
    const char *	pDriverName;
    int			perCore;		/* 0=single core, 1=multiple cores */
    int			numCounters;
    struct hpcHwCtrData ** ppDrvHwCtrData;	/* driver data */
    void		(*pHandler)(void *, void *, HPC_COUNTER, int); /* event rollover callback */

    void (*getArmPmuInfo)(ARM_PMU_INFO *info);
    void (*resetArmPmuAllCounters)(void);
    void (*enableArmPmu)(void);
    void (*disableArmPmu)(void);

    STATUS (*configCounterEvent)(int counter, int event);
    STATUS (*getCounterEvent)(int counter, int *event);
    STATUS (*enableCounter)(int counter);
    STATUS (*disableCounter)(int counter);
    STATUS (*getCounterState)(int counter, int * enable);
    STATUS (*getEvtCount)(int counter, unsigned int *value);
    STATUS (*setEvtCount)(int counter, unsigned int value);
    STATUS (*enableCounterInt)(int counter);
    STATUS (*disableCounterInt)(int counter);
    STATUS (*getCounterIntState)(int counter, int *enable);
    STATUS (*getCounterOverflow)(int counter, int *overflow);
    STATUS (*clearCounterOverflow)(int counter);

    STATUS		(*enablePmuIsr)(int (*)(struct driverInstArm *, void *, int));
    STATUS		(*disablePmuIsr)(int (*)(struct driverInstArm *, void *, int));
    };

extern STATUS hpcHwArmDriverInit(void);
extern STATUS hpcHwArmDriverFinit(void);
extern struct hpcHwDriverFuncs hpcHwDrvArmRtns;

#ifdef __cplusplus
}
#endif
#endif /* INChpc_armDrv_h */
