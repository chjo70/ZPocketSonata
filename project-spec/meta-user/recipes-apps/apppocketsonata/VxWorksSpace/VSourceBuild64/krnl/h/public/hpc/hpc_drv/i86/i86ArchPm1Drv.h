/* Copyright (c) 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

#ifndef INChpc_i86ArchPm1Drv_h
#define INChpc_i86ArchPm1Drv_h

#ifdef __cplusplus
extern "C" {
#endif

enum i86ArchPm1RegType
    {
    I86_ARCH_PM_DRV1_V1,
    I86_ARCH_PM_DRV1_V3,
    I86_ARCH_PM_DRV1_UNCORE
    };

struct i86Arch1Settings
    {
    unsigned int	eventNum;		/* Event Select */
    unsigned int	eventUmask; 		/* Unit Mask (UMASK) */
    unsigned int	restrictedCtrMask; 	/* PMC restriction mask */
    unsigned int	ctrMask;		/* Counter mask (CMASK) */
    unsigned int	inv;			/* INVert counter mask */
    };

struct driverInstArchV1
    {
    const char *	pDriverName;
    int			numCounters;
    int			numCounterBits;
    struct hpcHwCtrData ** ppDrvHwCtrData;	/* counter specific data */
    void		(*pHandler)(void *, void *, HPC_COUNTER, int); /* event rollover callback */
    STATUS		(*enablePerfIsrPerCore)(int (*)(struct driverInstArchV1 *, void *, int, long long int));
    STATUS		(*disablePerfIsrPerCore)(int force);
    enum i86ArchPm1RegType archPerfMonVer;
    int			msrPmc;
    int			msrPerfEvtSel;
    STATUS		(*enablePerfIsr)(int (*)(struct driverInstArchV1 *, void *, int, long long int));
    STATUS		(*disablePerfIsr)(int force);
    HPC_COUNTER		pmcRollover;
    unsigned int	pmcCounterMask;
    };

extern struct hpcHwDriverFuncs hpcHwDrvI86Arch1Rtns;

extern STATUS hpcHwI86ArchPm1DriverInit(void);
extern STATUS hpcHwI86ArchPm1DriverFinit(void);

#ifdef __cplusplus
}
#endif
#endif /* INChpc_i86ArchPm1Drv_h */
