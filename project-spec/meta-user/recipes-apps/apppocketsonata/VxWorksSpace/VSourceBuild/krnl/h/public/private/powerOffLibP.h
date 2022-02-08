/* powerOffLibP.h - private power off header files */

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

#ifndef __INCpowerOffLibPh
#define __INCpowerOffLibPh

#ifdef __cplusplus
extern "C" {
#endif

/* defines */

/* typedefs */

/* externals */

void (**pPowerOffHookTbl)(void);
int powerOffHookTblSize;

/* function declarations */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __INCpowerOffLibPh */
