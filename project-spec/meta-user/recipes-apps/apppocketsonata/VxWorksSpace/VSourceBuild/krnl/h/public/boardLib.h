/* boardLib.h - board subsystem header */

/*
 * Copyright (c) 2013-2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
05dec16,y_h  added board level power off, support ACPI event feature (F6446)
11sep15,syt  make struct spinTblEntry align with cache line size. (F3387)
09jul15,l_z  add fast warm boot support. (F3387)
23apr14,x_z  fixed no-probe method.
22apr14,x_z  updated BOARD_FUNC_TBL to add infoShow(). (US35954)
20feb14,x_z  removed ramVirtTop() from BOARD_FUNC_TBL. (VXW7-1838)
18dec13,cww  made dataset header private
18dec13,ylu  replaced regPpc.h with regs.h and surrounded
             it with _WRS_CONFG_SMP. (WIND00448367).
12dec13,ylu  added support for vx7 SMP feature.
18oct13,x_z  fixed boardLibInit().
09oct13,x_z  cleaned.
26jun13,l_z  created.
*/

#ifndef _INC_BOARDLIB_H
#define _INC_BOARDLIB_H

#include <vxWorks.h>
#include <vsbConfig.h>
#include <private/datasetP.h>

#ifdef _WRS_CONFIG_SMP
#   include <regs.h>
#endif /* _WRS_CONFIG_SMP */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* board define method */

#define BOARD_DEF(boardInst)    DATA_SET(board, 0, boardInst);

/* board defines */

/*
 * version defines
 *
 * The version of board descriptor must be updated if board function table or
 * board descriptor is updated:
 *
 * 1) the major version must be updated while adding elements to the 2
 * structures;
 * 2) the minor version must be updated while changing usage of elements.
 *
 * Note that any elements MUST not be removed from the 2 structures.
 */

#define BOARD_LIB_VER(major, minor)     \
    ((((major) & 0xFFFF) << 16) | ((minor) & 0xFFFF))
#define BOARD_LIB_VER_MAJOR(ver)        (((ver) >> 16) & 0xFFFF)
#define BOARD_LIB_VER_MINOR(ver)        ((ver)& 0xFFFF)

/* board function table define */

typedef struct board_func_tbl {
#ifdef _WRS_CONFIG_BOARDLIB_NO_PROBE
    UINT32  uVer;
#endif /* !_WRS_CONFIG_BOARDLIB_NO_PROBE */

    void    (*earlyInit) (void);
    void    (*init) (void); /* optional */
    void    (*reset) (int);
    char *  (*model) (void);
    void    (*usDelay) (int); /* optional */
#ifdef _WRS_CONFIG_SMP
    STATUS  (*cpuEn) (unsigned int, WIND_CPU_STATE *);
    UINT32  (*cpuAvail) (void);
    STATUS  (*cpuDis) ();
#endif  /* _WRS_CONFIG_SMP */

    /*
     * The following information format should be used for infoShow():
     *
     * <board name> <board revision>, CPU: <cpu name> <cpu rev>, CORE: <core name> <core rev>
     *
     * Example 1:
     *  Freescale P2020RDB Rev C, CPU:P2020E Rev 1.0, CORE:E500V2 Rev 1.0
     *
     * Example 2:
     *  Freescale P2020RDB (unknown revision), CPU:P2020E (unknown revision), CORE:E500V2 (unknown revision)
     */

    void    (*infoShow) (void);
#ifdef _WRS_CONFIG_SYS_PWR_OFF
    STATUS  (*powerOff) (void); /* optional */
#endif /* _WRS_CONFIG_SYS_PWR_OFF */
} BOARD_FUNC_TBL;

#ifndef _WRS_CONFIG_BOARDLIB_NO_PROBE

/* board descriptor define */

typedef struct board_desc {
    UINT32              uVer;
    char *              pCompat;
    UINT32              uFlag;
    BOOL                (*probe) (char * pCompat);
    BOARD_FUNC_TBL *    pFuncTbl;
} BOARD_DESC;
#endif /* !_WRS_CONFIG_BOARDLIB_NO_PROBE */

/*
 * version defines:
 *
 *  1.0 - initial version
 *  2.0 - added infoShow() to board function table for boardInfoShow() support
 */

#define BOARD_DESC_VER_1_0      BOARD_LIB_VER (1, 0)
#define BOARD_DESC_VER_2_0      BOARD_LIB_VER (2, 0)
#define BOARD_DESC_VER_DEF      BOARD_DESC_VER_1_0

#ifndef _WRS_CONFIG_BOARDLIB_NO_PROBE

/* flag defines */

#define BOARD_DESC_FLAG_MASK    0xFFFF
#define BOARD_DESC_FLAG_SHIFT   16
#define BOARD_DESC_FLAG(comFlag, privFlag)    \
    ((((comFlag) & BOARD_DESC_FLAG_MASK) << BOARD_DESC_FLAG_SHIFT) | \
    ((privFlag) & BOARD_DESC_FLAG_MASK))

/* common flags */

#define BOARD_DESC_FLAG_DBG             0x0100  /* debug enable */
#endif /* !_WRS_CONFIG_BOARDLIB_NO_PROBE */

/* board routines */

STATUS boardLibInit ();
void boardInit ();
void boardReset ();
void boardInfoShow ();
#ifndef _WRS_CONFIG_BOARDLIB_NO_PROBE
BOOL boardFlagCheck
    (
    UINT32  uFlag,  /* flag to be checked */
    BOOL    bPriv   /* private flag check */
    );
#endif /* !_WRS_CONFIG_BOARDLIB_NO_PROBE */

typedef struct spinTblEntry {
    void * pc;
    void * sp;
    void * initRtn;
    unsigned int cpuId;
    unsigned int enable;
#ifndef _WRS_CONFIG_LP64
    unsigned int reserve[3];
#endif /* _WRS_CONFIG_LP64 */
} SPIN_TBL_ENTRY _WRS_DATA_ALIGN_BYTES(32);

extern STATUS (*sysWarmBootLibInit) (void);
extern void (*sysWarmBootFunc) (void * entryPoint);
#ifdef _WRS_CONFIG_SMP
extern void (*sysWarmBootSlaveDisable) (UINT32 cpuId);
extern void (*sysWarmBootSlaveEnable) (UINT32 cpuId,void * initFunc,WIND_CPU_STATE * cpuState);
#endif /* _WRS_CONFIG_SMP */

#ifdef __cplusplus
    }
#endif /* __cplusplus */

#endif /* _INC_BOARDLIB_H */

