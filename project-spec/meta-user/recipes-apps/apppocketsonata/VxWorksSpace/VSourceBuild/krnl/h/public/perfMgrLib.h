 /* perfMgrLib.h - CPU dynamic power management */

/*
 * Copyright (c) 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01b,27may10,pad  Moved extern C statement after include statements.
01a,25Feb2010,rec  created

*/
#ifndef __INCperfMgrLibh
#define __INCperfMgrLibh

#ifndef _ASMLANGUAGE

#include <private/qLibP.h>  /* for Q_PRI_BMAP_MAX_PRIORITIES */

#ifdef __cplusplus
extern "C" {
#endif

#define PRIORITY_PWR_MGMT   TRUE
#define TASK_PWR_MGMT       FALSE

/* use this define for the size of a profile table (288 entries) */

#define PERF_MGR_PROFILE_TABLE_SIZE Q_PRI_BMAP_MAX_PRIORITIES

/* depricated power states - definitions provided for backward compatibility */

typedef UINT32 CPU_PWR_P_STATE;
#define cpuPwrP0State 0
#define cpuPwrP1State 1
#define cpuPwrP2State 2
#define cpuPwrP3State 3
#define cpuPwrP4State 4
#define cpuPwrP5State 5
#define cpuPwrP6State 6

/* typedef's */

/* globals */

IMPORT UINT16 perfMgrEventCategory;
IMPORT UINT16 perfMgrUpEvent;
IMPORT UINT16 perfMgrDownEvent;

/* function prototypes */

IMPORT STATUS   perfMgrInit             
    (
    BOOL priorityPerformace,
    UINT32  intContextPState,   
    int     profileIndex,       /* initial profile index */
    char *  profileString0,     /* string used to create profile-0 */
    char *  profileString1,     /* string used to create profile-1 */
    char *  profileString2,     /* string used to create profile-2 */
    char *  profileString3      /* string used to create profile-3 */
    );

IMPORT STATUS cpuPwrTaskPStateSet 
    (
    TASK_ID tid,        /* Task ID for which P-State is to be set */ 
    UINT32 pwrPstate    /* P-State for task */
    );

IMPORT UINT32 cpuPwrTaskPStateGet 
    (
    TASK_ID tid    /* Task ID for which task get P-State */ 
    );

IMPORT STATUS   perfMgrEnable (void);         

IMPORT STATUS   perfMgrDisable (void);          

IMPORT STATUS   perfMgrProfileSelect
    (
    int profile /* profile number */
    );

IMPORT STATUS   perfMgrProfileDown (void); /* select lower profile */

IMPORT STATUS   perfMgrProfileUp (void);   /* select higher profile */

IMPORT UINT32   perfMgrNumProfilesGet (void);

IMPORT UINT8   *perfMgrProfileGet (void);

IMPORT STATUS   perfMgrProfileSet 
    (
    UINT8 **profileTable, 
    UINT32  numPerfProfiles
    );

IMPORT void     perfMgrShow (void);

#ifdef __cplusplus
}
#endif

#endif /* _ASMLANGUAGE */

#endif /* __INCperfMgrLib */

