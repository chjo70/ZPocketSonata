/* hpcDrvEvtCfg.h - HPC Driver Event Configuration */

/*
 * Copyright (c) 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

#ifndef INChpcDriverEventConfig_h
#define INChpcDriverEventConfig_h

#include <cafe/cafe.h>
#include <hpc/drv_evt_cfg/hpcEvtSet.h>

#ifdef __cplusplus
extern "C" {
#endif

/* HPC counter event settings that are common to all counters. */
struct hpcEventSettings
    {
    HPC_COUNTER	reload;	/* The counter increments reload times before */
			/* triggering a HPC interrupt */
    unsigned long long samplePeriod; /* Sample period in Hz */
    };

/*
 * Constant HPC counter event settings that are common to all counters. These
 * are not described in the event value type definition.
 */
struct hpcEventSettingsConst
    {
    const HPC_COUNTER reloadMin; /* minimum reload value for event */
    };

/*
 * This data structure is used to describe a HPC event. There are three parts
 * to the descriptor: a value type event description string, common constant
 * settings and hardware specific constant settings.
 * Note: the first variable must be eventVtStr because struct hpcEventDescriptor
 * is overlaid on arch specific data structures which also must define
 * pEventNameDef as the first variable in the struct.
 */
struct hpcEventDescriptor
    {
    /*
     * Cafe Value Type (refer to include/cafe/value_type.h) event definition
     * string. This defines the event name, the event parameters (which is
     * count), and the event settings. Common event settings like reload,
     * muxed and group are defined, as well as any other hardware specific
     * event settings (for example, event mask). Event settings described here
     * in Value Type can have their values overridden in the Cafe configuration
     * language.
     */
    const char * pEventNameDef;

    /* Constant common event settings. */
    const struct hpcEventSettingsConst hpcEvtSettingsConst;

    /* Constant hardware specific event settings */
    const union eventSettings	evtSettings;
    };

typedef int (*EVENT_SETTING_GET_FUNC)
	(
	/* event name value type */
	struct cafe_value_type *          pType,
	/* hw-specific driver settings, filled in by this function. */
	union eventSettings *             pDrvSettings,
	/*  */
	struct hpcEventSettings *         pHpcSettings,
	const struct hpcEventDescriptor * pEvtDesc
	);

/*
 * HPC Event Processor driver configuration.
 */
struct hpcDriverConfig
    {
    int				numEvents;  /* Number of events */
    int				numCpuCores; /* Number of CPU Cores */
    void *			pDrvInst;   /* Low-level hpc driver data */
    struct hpcHwDriverFuncs *   pFuncs;	    /* Low-level hpc driver functions */

    /*
     * HW specific callback to get the event setting data. The event settings
     * are copied from the event descriptor pointed to by pEvtDesc to the data
     * structures pointed to by pDrvSettings (hw specific) and
     * pHpcSettings (common). The reload value requested is checked against
     * the minimum reload value.
     */
    EVENT_SETTING_GET_FUNC pEventSettingsGet;
    size_t	eventSettingSize; /* size of hw specific event descriptor */
    void *	pEventDesc; /* array of hw specific event descriptors */
    };

#ifdef __cplusplus
}
#endif
#endif /* INChpcDriverEventConfig_h */
