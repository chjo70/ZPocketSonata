/* vxbRtcLib.h - VxBus RTC interfaces header file */

/*
 * Copyright (c) 2012,2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
07sep17,mpc  Added function declaration (F9286)
03feb17,syt  Added function declaration vxbAlarmTypeCheck().(F6376)
16jan17,syt  Added a macro RTC_ALARM_FULL_SUPPORT.(F6376)
25nov13,hll  Remove redundant definiton of vxbFdtLib.h(WIND00445019).
14may12,y_y  changed alarmSet routine, added alarm unit, callback 
             and callback paramete.
24feb12,l_z  written
*/

/*
DESCRIPTION

This library provides the RTC specific interfaces

*/

#ifndef __INCvxbRtcLibh
#define __INCvxbRtcLibh 

#ifdef __cplusplus
extern "C" {
#endif

#include <hwif/vxBus.h>
#include <hwif/util/vxbIsrDeferLib.h>

#define  MAX_ALARMS                2  /* The maximum number of the hardware alarm */

#define  RTC_ALARM_SEC_SUPPORT     0x01
#define  RTC_ALARM_FULL_SUPPORT    0x02

/* alarm callback */

typedef STATUS (*RTC_ALARM_FUNC) (VOID *pArg); 

/* structure to be used and updated RTC time and Alarm */

typedef struct vxbRtcFunctionality
    {
    char   timerName[MAX_DRV_NAME_LEN + 1];
    UINT8  alarmNum;                  /* Alarm numbers */
    UINT8  alarmCap[MAX_ALARMS];      /* Alarm attribute */
    STATUS (*rtcGet)(VXB_DEV_ID pInst, struct tm * rtc_time);
    STATUS (*rtcSet)(VXB_DEV_ID pInst, struct tm * rtc_time);
    STATUS (*alarmSet)(VXB_DEV_ID pInst, UINT8, struct tm * rtc_time, 
                       RTC_ALARM_FUNC rtcAlarmFunc, void *pArg);
    STATUS (*alarmGet)(VXB_DEV_ID pInst, UINT8, struct tm * rtc_time); 
    } VXB_I2C_RTC_FUNC;

struct vxbRtcHandle
    {
    struct vxbRtcFunctionality *pRtcFunc;
    VXB_DEV_ID                  pInst;
    };

/* IMPORT */

IMPORT STATUS vxbRtcGet (struct tm * rtcTime);
IMPORT STATUS vxbRtcSet (struct tm * rtcTime);
IMPORT STATUS sysRtcSet (void);
IMPORT UINT8  vxbAlarmTypeCheck (void);
IMPORT STATUS vxbAlarmGet (UINT8 unit, struct tm * alarmTime); 
IMPORT STATUS vxbAlarmSet (UINT8 unit, struct tm * alarmTime, 
                    RTC_ALARM_FUNC rtcAlarmFunc, void * pRtcAlarmArg); 
IMPORT STATUS vxbRtcTimeVerify (struct tm * pTime, UINT32 minYear, 
                                UINT32 maxYear); 

/* 0: simple show; 1: full show */

IMPORT STATUS sysRtcGet (int level);

IMPORT void rtcRegister
    (
    VXB_DEV_ID pDev,
    VXB_I2C_RTC_FUNC * rtc
    );
    
#ifdef __cplusplus
}
#endif

#endif /* __INCvxbRtcLibh */

