/* Copyright (c) 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

#ifndef INChpc_e500Drv_h
#define INChpc_e500Drv_h
#ifdef __cplusplus
extern "C" {
#endif


/*****************************************************************************
 * e500 HW Driver specific
 */

struct e500Settings
    {
    unsigned int	evtCode;
    unsigned int	ctrMask;
    };

struct driverInstE500
    {
    const char *	pDriverName;
    int			perCore;		/* 0=single core, 1=multiple cores */
    int			numCounters;
    unsigned int	counterSizeMask;	/* 1=64bit, 0=32bit counter */
    struct hpcHwCtrData ** ppDrvHwCtrData;	/* driver data */
    void		(*pHandler)(void *, void *, HPC_COUNTER, int); /* event rollover callback */
    void		(*pmcRegSet)(int, unsigned long long);
    unsigned long long	(*pmcRegGet)(int);
    void		(*pmlcaRegSet)(int, unsigned int);
    unsigned int	(*pmlcaRegGet)(int);
    void		(*pmlcbRegSet)(int, unsigned int);
    unsigned int	(*pmlcbRegGet)(int);
    void		(*pmgc0RegSet)(unsigned int);
    unsigned int	(*pmgc0RegGet)(void);
    STATUS		(*enablePerfIsr)(int (*)(struct driverInstE500 *, void *, int));
    STATUS		(*disablePerfIsr)(void);
    };

extern STATUS hpcHwE500DriverInit(void);
extern STATUS hpcHwE500DriverFinit(void);
extern struct hpcHwDriverFuncs hpcHwDrvE500Rtns;

#ifdef __cplusplus
}
#endif
#endif /* INChpc_e500Drv_h */
