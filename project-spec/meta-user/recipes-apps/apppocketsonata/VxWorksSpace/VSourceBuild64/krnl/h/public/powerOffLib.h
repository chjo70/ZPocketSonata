/* powerOffLib.h - header for power off libary */

/*
 * Copyright (c) 2016 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
05dec16,y_h  created for system level power off, support ACPI
             event feature (F6446)
*/

#ifndef __INCpowerOffLibh
#define __INCpowerOffLibh

#ifdef __cplusplus
extern "C" {
#endif

/* defines */

/* typedefs */

typedef void (* POWER_OFF_HOOK)(void);

/* externals */

/* function declarations */

extern STATUS powerOffHookAdd(POWER_OFF_HOOK powerHook);
extern STATUS powerOffHookDelete(POWER_OFF_HOOK powerHook);
extern STATUS powerOff(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __INCpowerOffLibh */
