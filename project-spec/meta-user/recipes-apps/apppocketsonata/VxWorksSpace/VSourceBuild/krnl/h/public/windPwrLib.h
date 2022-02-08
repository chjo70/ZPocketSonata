/* windPwrLib.h - Power Management header file */

/*
 * Copyright (c) 2002-2004,2011 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
01h,22aug11,j_l  WIND00255353: IA PPM integration.
01g,10aug11,rbc  WIND00238999 - Fix build error for windPwrDown()
01f,01aug11,rbc  WIND00238999 - Add VSB _WRS_CONFIG_PWR_MGMT
01e,07jul11,j_l  WIND00255353 PwrMgmt: VxWorks Tickless operating mode for IA
01d,19oct04,rec  SPR 10255 - move POWER_MGMT_DEFAULT_MODE here
                 add sysCpuPwrEnable prototype
01c,06nov03,rec  make WIND_PWR_DOWN_RTN void fct
01b,26jun03,rec  code review comments
01a,26apr02,rec  written.
*/

/*
* DESCRIPTION
* This header contains the datatype and prototype declarations for
* power management
*/

#ifndef __INCwindPwrLibh
#define __INCwindPwrLibh

#ifdef __cplusplus
extern "C" {
#endif

#include <private/windPwrLibP.h>

#ifdef _WRS_CONFIG_PWR_MGMT

/* POWER MANAGEMENT DEFAULT MODE */

#ifdef INCLUDE_CPU_SLEEP_MODE_OFF
#define POWER_MGMT_DEFAULT_MODE windPwrModeOff
#elif defined INCLUDE_CPU_SLEEP_MODE_SHORT
#define POWER_MGMT_DEFAULT_MODE windPwrModeShort
#elif defined INCLUDE_CPU_SLEEP_MODE_LONG
#define POWER_MGMT_DEFAULT_MODE windPwrModeLong
#else
#define POWER_MGMT_DEFAULT_MODE windPwrModeLong
#endif /* INCLUDE_CPU_SLEEP_MODE_OFF */

/*
* windPwrModeShort is the CPU power mode where the CPU sleeps between
* system clock ticks but always wakes up for every tick.  In other
* words, the tick interrupt source is not turned off when this CPU
* power mode is set.
*
* windPwrModeLong is the CPU power mode where the CPU sleeps for
* multiple ticks at a time or until an external interrupt wakes
* the system.  With this mode, the BSP turns off the tick interrupt
* source and schedules an interrupt to occur some number of ticks
* in the future.
*/

typedef enum windPwrMode
    {
        windPwrModeOff      = 0,
        windPwrModeShort    = 1,
        windPwrModeLong     = 2
    } WIND_PWR_MODE;

typedef void (*WIND_PWR_DOWN_RTN)( WIND_PWR_MODE mode, _Vx_ticks_t nTicks);
typedef void (*WIND_PWR_UP_RTN)( WIND_PWR_MODE mode, _Vx_ticks_t * nTicks);
typedef void (*WIND_PWR_PPM_RTN)(void);

/* function prototypes */

extern void             sysCpuPwrEnable   (void);
extern void             windPwrModeSet    (WIND_PWR_MODE mode);
extern WIND_PWR_MODE    windPwrModeGet    (void);
extern void             windPwrTicklessThresholdSet (_Vx_ticks_t threshold);
extern _Vx_ticks_t      windPwrTicklessThresholdGet (void);
extern void             windPwrDownRtnSet (WIND_PWR_DOWN_RTN dRtn);
extern void             windPwrUpRtnSet   (WIND_PWR_UP_RTN   uRtn);
extern void             windPwrPpmRtnSet  (WIND_PWR_PPM_RTN  uRtn);

#endif /* _WRS_CONFIG_PWR_MGMT */


#ifdef __cplusplus
}
#endif

#endif  /* __INCwindPwrLibh */
