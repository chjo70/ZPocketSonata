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

/*
DESCRIPTION
*/
#ifndef INChpc_armvxw_h
#define INChpc_armvxw_h
#ifdef __cplusplus
extern "C" {
#endif

typedef int (*ARM_PMU_HANDLER)(void *);

typedef struct arm_pmu_info {
unsigned int imp;
unsigned int idcode;
int numCounters;
int state;
} ARM_PMU_INFO;

typedef int ARM_PMU_EVENT_TYPE;

extern void getArmPmuInfo(ARM_PMU_INFO *info);
extern void resetArmPmuAllCounters(void);
extern void enableArmPmu(void);
extern void disableArmPmu(void);

extern STATUS configArmPmuCounterEvent(int counter, int event);
extern STATUS getArmPmuCounterEvent(int counter, int *event);
extern STATUS enableArmPmuCounter(int counter);
extern STATUS disableArmPmuCounter(int counter);
extern STATUS getArmPmuCounterState(int counter, int * enable);
extern STATUS getArmPmuEvtCount(int counter, unsigned int *value);
extern STATUS setArmPmuEvtCount(int counter, unsigned int value);
extern STATUS enableArmPmuCounterInt(int counter);
extern STATUS disableArmPmuCounterInt(int counter);
extern STATUS getArmPmuCounterIntState(int counter, int *enable);
extern STATUS getArmPmuCounterOverflow(int counter, int *overflow);
extern STATUS clearArmPmuCounterOverflow(int counter);

extern STATUS vxwArmPmuIsrEnable(int (*pHandler)(void *));
extern STATUS vxwArmPmuIsrDisable(int (*pHandler)(void *));

#ifdef __cplusplus
}
#endif
#endif /* INChpc_armvxw_h */

