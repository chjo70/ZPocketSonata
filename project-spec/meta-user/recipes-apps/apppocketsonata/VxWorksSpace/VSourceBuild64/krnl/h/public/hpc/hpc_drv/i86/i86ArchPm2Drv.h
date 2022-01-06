/* Copyright (c) 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

#ifndef INChpc_i86ArchPm2Driver_h
#define INChpc_i86ArchPm2Driver_h

#ifdef __cplusplus
extern "C" {
#endif

enum i86ArchPm2RegType
    {
    I86_ARCH_PM_DRV2_V2,
    I86_ARCH_PM_DRV2_V3,
    I86_ARCH_PM_DRV2_UNCORE
    };

struct i86Arch2Settings
    {
    unsigned int	counter;
    };

struct driverInstArchV2
    {
    const char *	pDriverName;
    int			numCounters;
    int			numCounterBits;
    struct hpcHwCtrData ** ppDrvHwCtrData;	/* counter specific data */
    void		(*pHandler)(void *, void *, HPC_COUNTER, int); /* event rollover callback */
    STATUS		(*enablePerfIsrPerCore)(int (*)(struct driverInstArchV2 *, void *, int, long long int));
    STATUS		(*disablePerfIsrPerCore)(int force);
    enum i86ArchPm2RegType archPerfMonVer;
    int			msrFixedCtr;		/* Fixed counter MSR */
    int			msrFixedCtrCtrl;	/* Fixed counter control MSR */
    int			msrGlobalStatus;	/* Global status MSR */
    int			msrGlobalCtrl;		/* Global Control MSR */
    int			msrGlobalOvfCtrl;	/* Global Overflow control MSR */
    STATUS		(*enablePerfIsr)(int (*)(struct driverInstArchV2 *, void *, int, long long int));
    STATUS		(*disablePerfIsr)(int force);
    HPC_COUNTER		ctrRollover;
    unsigned int	ctrCounterMask;
    };

extern struct hpcHwDriverFuncs hpcHwDrvI86Arch2Rtns;

extern STATUS hpcHwI86ArchPm2DriverInit(void);
extern STATUS hpcHwI86ArchPm2DriverFinit(void);

#ifdef __cplusplus
}
#endif
#endif /* INChpc_i86ArchPm2Driver_h */
