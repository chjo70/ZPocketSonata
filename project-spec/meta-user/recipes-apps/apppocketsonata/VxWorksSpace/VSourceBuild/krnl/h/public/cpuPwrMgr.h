/* cpuPwrMgr.h - CPU power Manager library header file */

/*
 * Copyright (c) 2005, 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01a,22feb10,rec  ACPI power management support - remove cpuPwrUtilMgrInit
01a,04sep05,mmi  created
*/

#ifndef __INCcpuPwrMrgh
#define __INCcpuPwrMgrh

#ifdef __cplusplus
extern "C" {
#endif

/* typedef's */

/* function prototypes */

/* Routines to Enable/Disable CPU power Manager */

extern BOOL cpuPwrMgrIsEnabled (void);
extern STATUS cpuPwrMgrEnable (BOOL enable);

/* Initialization routines */

extern STATUS  cpuPwrLightMgrInit (void);

#ifdef __cplusplus
}
#endif

#endif /* __INCcpuPwrMgr */


