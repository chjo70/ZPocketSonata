/* Copyright (c) 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

#ifndef INChpc_i86ArchPmEventConfig_h
#define INChpc_i86ArchPmEventConfig_h

#include <hpc/hpc_drv/i86/i86ArchPm1Drv.h>
#include <hpc/hpc_drv/i86/i86ArchPm2Drv.h>

#ifdef __cplusplus
extern "C" {
#endif

#define NUM_ARCH_V1_EVENTS 7

/* note: the first variable must be eventVtStr because struct hpcEventDescriptor
 * is overlaid on this data structure. */
struct i86Arch1EventDescription
    {
    const char * eventVtStr;
    struct hpcEventSettingsConst hpcEventSettingsConst;
    struct i86Arch1Settings eventSettings;
    };

/* note: the first variable must be eventVtStr because struct hpcEventDescriptor
 * is overlaid on this data structure. */
struct i86Arch2EventDescription
    {
    const char * eventVtStr;
    struct hpcEventSettingsConst hpcEventSettingsConst;
    struct i86Arch2Settings eventSettings;
    };

extern void hpcI86ArchPerfMonShow(void);
extern void hpcI86ArchPerfMonFreezeWhileSmmSet(void);
extern void hpcI86ArchPerfMonFreezeWhileSmmClear(void);

extern STATUS hpcI86ArchPerfMonInit
    (
    void * (*pMallocFunc)(size_t),
    void (*pFreeFunc)(void *),
    int errata,
    unsigned int edxErrata
    );

extern STATUS i86ArchPmV1Free
    (
    struct hpcDriverConfig * pConfig
    );

extern struct hpcDriverConfig * i86ArchPmV1Configure
    (
    int		  numCores,
    unsigned int  numNonArchEvents,
    struct i86Arch1EventDescription *pEventDesc
    );

extern STATUS i86ArchPmV2Free
    (
    struct hpcDriverConfig * pConfig
    );

extern struct hpcDriverConfig * i86ArchPmV2Configure
    (
    int	numCores
    );

extern STATUS i86UncoreFree (void);

extern STATUS i86UncoreConfigure
    (
    unsigned int intCore
    );

#ifdef __cplusplus
}
#endif
#endif /* INChpc_i86ArchPmEventConfig_h */
