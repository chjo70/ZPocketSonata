/* hpcHwDrvApi.h - Hardware Performance Counters Hardware Driver Interface */

/*
 * Copyright (c) 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

#ifndef INChpc_hpcHardwareDriver_h
#define INChpc_hpcHardwareDriver_h

#ifdef __VXWORKS__
#include <vxWorks.h>
#include <vxCpuLib.h>
#else
#include <hpc/hpc_drv/test_mock/hpc_hw_drv_api_mock.h>
#endif

#include <hpc/hpc_drv/hpcHwDrvUtils.h>

#ifdef __cplusplus
extern "C" {
#endif

/* type used to hold a hardware performance counter value */
typedef unsigned long long HPC_COUNTER;

/*
 * low-level driver initialization data. This data structure is passed to
 * the drivers initialization function.
 */
struct hpcHwDriverInitData
    {
    /* The client hpc overflow callback function, called at ISR level. The
     * callback function is not required to be reentrant */
    void (*pPerfIntCallback)
        (
        void *		pClientData,	/* client callback handle */
        void *		pContext,	/* CPU context if available else NULL */
        HPC_COUNTER	value,		/* counter value */
	int		core		/* current cpu core id */
	);

    /*
     * if the low level driver needs dynamic memory, this function should be
     * used to allocate it.
     */
    void * (*pMallocFunc)
        (
        size_t size /* number of bytes to allocate */
        );

    /* used to free memory that was allocated by pMallocFunc */
    void (*pFreeFunc)(void *);
    };

/*
 * drivers Hardware Counter (private) Data area (HCD). Defined by the
 * low-level driver implementation. This data structure contains enough
 * information on how to count an event. It is passed as a handle to the low
 * level driver.
 */
struct hpcHwCtrData;

typedef struct hpcHwCtrData * (*HPC_EVENT_ITER_FUNC)(void *pIterArg);

/* low level driver interface routines */
struct hpcHwDriverFuncs
    {
    /*
     * Start the counter described by the HCD.
     *
     * This routine is called once for each CPU core that the low level driver
     * is configured for. CPU affinity is set to the CPU before it is called.
     *
     * This routine is only called from task level and does not need to be
     * reentrant.
     *
     * On success OK is returned. If the counter cannot be started for any
     * reason ERROR is returned.
     */
    STATUS (*hpcHwCtrStart)
	(
	void *			pDrvInst, /* the driver instance data */
	struct hpcHwCtrData *	pCtr /* the HCD handle */
	);

    /*
     * Stop the counter described by the HCD and return the stopped counter
     * value in *pCount.
     *
     * This routine is called once for each CPU core that the low level driver
     * is configured for. CPU affinity is set to the CPU before it is called.
     *
     * The stop function will save any data necessary in the HCD so that
     * a subsequent call to hpchwDrvStart will result in the counter resuming
     * from where it was stopped.
     *
     * This routine is only called from task level and does not need to be
     * reentrant.
     *
     * On success OK is returned. If the counter cannot be stopped for any
     * reason ERROR is returned.
     */
    STATUS (*hpcHwCtrStop)
	(
	void *			pDrvInst, /* the driver instance data */
	struct hpcHwCtrData *	pCtr, /* the HCD handle */
	HPC_COUNTER *		pCount
	);

    /*
     * Read a counter that has been scheduled to run, that is hpcHwCtrStart()
     * has been called on the counter. If possible the counter is not stopped
     * in order to read it. If it is stopped, the counter will be resumed.
     *
     * This routine is called on the core where the counter value is expected
     * to be read from.
     *
     * This routine can be called from within the pPerfIntCallback() ISR. It
     * is not required to call this routine from task level.
     *
     * On success OK is returned. If the counter cannot be read for any
     * reason ERROR is returned.
     */
    STATUS (*hpcHwCtrRead)
	(
	void *			pDrvInst, /* the driver instance data */
	struct hpcHwCtrData *	pCtr, /* the HCD handle */
	HPC_COUNTER *		pCount
	);

    /*
     * Change the reload value of the counter described by the HCD.
     *
     * A requested reload value of 0 will force the driver to select a reload
     * value which takes the longest time to overflow. This value will also
     * be returned in *pReload. The function will return ERROR if the requested
     * reload is out of bounds.
     *
     * This routine assumes the counter is in the stopped state. It can be
     * called from within the pPerfIntCallback() ISR and also from task
     * context.
     *
     * On success OK is returned.
     */
    STATUS (*hpcHwUpdateCtrReload)
	(
	void *			pDrvInst, /* the driver instance data */
	struct hpcHwCtrData *	pCtr, /* the HCD handle */
	HPC_COUNTER *		pReload
	);

    /*
     * The low level driver configures the HCD that is pointed to by pCtr, so
     * that the event described by pEvtSettings can be counted. This
     * routine must also ensure that all hardware resources
     * are available. To do this, the pEventIterFunc iterator function
     * must be called until it returns NULL. This iterator function will
     * return a HCD for all event counters that are scheduled to run
     * simultaneously. The function can use this information to decide what
     * hardware resources remain in order to be able to count this event.
     * This routine should not read and write tho HPC registers. It should
     * just configure data within the HCD so that Start/Stop which do
     * read/write to registers execute efficiently.
     *
     * A requested reload value of 0 will make the driver select a reload
     * value which takes the longest time to overflow. This value will also
     * be returned in *pReload. The function will return ERROR if the requested
     * reload is out of bounds.
     *
     * This routine is only called from task level and does not need to be
     * reentrant.
     *
     * On success OK is returned. If no resources are available to count the
     * event, ERROR is returned.
     */
    STATUS (*hpcHwCreateCtrForEvent)
	(
	void *			pDrvInst, /* the driver instance data */
	void *			pEvtSettings, /* drivers event settings */
	HPC_COUNTER *		pReload, /* reload value */
	struct hpcHwCtrData *	pCtr, /* the HCD handle to configure */
	void *			pClient, /* client callback handle for */
					 /* pPerfIntCallback */
	HPC_EVENT_ITER_FUNC	pEventIterFunc, /* get hpcHwCtrData callback */
	void *			pIterArg /* param arg for pEventIterFunc */
	);

    /*
     * Free any resources allocated by hpcHwCreateCtrForEvent.
     *
     * On success OK is returned.
     */
    STATUS (*hpcHwDeleteCtrForEvent)
	(
	void *			pDrvInst, /* the driver instance data */
	struct hpcHwCtrData *	pCtr /* the HCD handle */
	);

    /*
     * Initialize the low level driver. The data structure pointed to by
     * pDrvInstInitData contains the initialization data. The size of
     * the drivers HCD must be returned in *pSizeOfHwCtrData.
     *
     * This routine can be used to initialize performance counter interrupts.
     *
     * This routine is only called from task level and does not need to be
     * reentrant.
     *
     * On success OK is returned, on error, ERROR is returned.
     */
    STATUS (*hpcHwDriverInit)
	(
	void *			pDrvInst, /* the driver instance data */
	struct hpcHwDriverInitData * pDrvInstInitData,
	size_t *		pSizeOfHwCtrData
	);

    /*
     * Free any resources used by hpcHwDriverInit.
     *
     * On success OK is returned, on error, ERROR is returned.
     */
    STATUS (*hpcHwDriverFinit)
	(
	void *			pDrvInst /* the driver instance data */
	);

    /*
     * Initialize any resources per CPU core.
     *
     * This routine is called once for each CPU core that the low level driver
     * is configured for. CPU affinity is set to the CPU before it is called.
     *
     * This routine is only called from task level and does not need to be
     * reentrant.
     *
     * On success OK is returned, on error, ERROR is returned.
     */
    STATUS (*hpcHwPerCoreInit)
	(
	void *			pDrvInst /* the driver instance data */
	);

    /*
     * Free any resources used by hpcHwPerCoreInit.
     *
     * This routine is called once for each CPU core that the low level driver
     * is configured for. CPU affinity is set to the CPU before it is called.
     *
     * The force parameter is used to force shutdown. This is used when the
     * driver in not shutdown cleanly. Counters may still be counting when this
     * routine is called with force non zero.
     *
     * This routine is only called from task level and does not need to be
     * reentrant.
     *
     * On success OK is returned, on error, ERROR is returned.
     */
    STATUS (*hpcHwPerCoreFinit)
	(
	void *			pDrvInst, /* the driver instance data */
	int			force /* non zero value to force shutdown */
	);

    /*
     * Display any useful driver information, like the value of the hardware
     * registers.
     *
     * This routine is only called from task level and does not need to be
     * reentrant.
     *
     * On success OK is returned, on error, ERROR is returned.
     */
    STATUS (*hpcHwDriverShow)
	(
	void *			pDrvInst /* the driver instance data */
	);
    };

#define NOT(X) (~X)

#ifdef __cplusplus
}
#endif
#endif /* INChpc_hpcHardwareDriver_h */
