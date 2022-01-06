/* wvLib.h - event log header */

/*
 * Copyright (c) 1993-2008, 2010-2011, 2013-2014 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind RIver License agreement.
 */

/*
modification history
--------------------
23oct14,wzc  support RTP for Memory Analyzer.(US46321)
13nov13,wzc  Add usb filter.(WIND00443227)
03jun13,wzc  Added stacktrace for system viewer.
27jul11,wzc  PPM for SV (WIND00214625)
10feb10,tcr  update for 64bit
09jul08,tcr  add wvEdrInst
11jan07,tcr  add new instrumentation functions for cpc and spinlocks
             add enum for instrumentation mode
29apr04,ymz  added definition of wvSalInst.
25mar04,tcr  add wvObjInstModeSet(), backward compatible OBJ_ defines
05nov03,tcr  add parameter to wvObjNameBuffAdd()
17oct03,tcr  code review changes
15oct03,tcr  add wvAllObjsSet() prototype; change INSTRUMENT_xx defines
             change prototype for wvObjInst() and similar
01oct03,tcr  wvEvtLogStart() verifies evtBuffer; add wvLogCountGet()
18sep03,tcr  modify prototypes
10sep03,tcr  change prototype of wvObjInst(), fix obj type defines
17jul03,tcr  make hash table more generic, base6 changes
13may98,cth  added protype for wvUploadTaskConfig
20apr98,cth  added protypes for wvLogHeaderCreate/Upload, modified 
             wvEvtLogInit definition, changed wvUploadTaskPriority to 01l
17apr98,cth  changed prototype of wvEvtLogInit
15apr98,cth  added prototypes for task name storage, and wvEvtBufferGet,
             renamed wvContinuousUploadStop to wvUploadStop
17mar98,pr   added memory instrumentation support
27jan98,cth  added wvEvtLogInit function declaration, updated copyright
18dec97,cth  removed temporary references used for WV2.0 integration, 
             updated include files, removed wvOn/Off, fixed prototypes
16nov97,cth  more work for WindView 2.0
30jul97,nps  major rework for WindView 2.0.
08mar94,smb  changed prototype for OSE functionality
             removed PASSIVE_MODE
04mar94,smb  changed prototype for wvHostInfoInit (SPR #3089)
22feb94,smb  changed typedef EVENT_TYPE to event_t (SPR #3064)
15feb94,smb  renamed collection modes
19jan94,smb  removed wvEvtLog, added wvEvtLogEnable and wvEvtLogEnable
             removed ALL_LEVELS and changed OBJECT_STATE to OBJECT_STATUS
             added wvOn(), wvOff(), and wvEvtLogStop().
30dec93,c_s  changed prototype of wvServerInit ().  SPR #2790.
10dec93,smb  written.
*/

#ifndef __INCwvlibh
#define __INCwvlibh

#include "vxWorks.h"

#include "rBuffLib.h"

#include "private/wvLibP.h"
#include "private/wvBufferP.h"
#include "private/wvUploadPathP.h"

#include "private/eventP.h"


#ifdef __cplusplus
extern "C" {
#endif

/* defines */

/* define the old object types in terms of the new ones */
    
#define OBJ_TASK        windTaskClass	        /* task objects */
#define OBJ_SEM         windSemClass	        /* semaphore objects */
#define OBJ_MSG         windMsgQClass	        /* message queue objects */
#define OBJ_WD          windWdClass	        /* watch-dog timer objects */
#define OBJ_MEM         windMemPartClass	/* memory objects */


/* types */

typedef struct wvUploadTaskDescriptor *         WV_UPLOADTASK_ID;

typedef enum wv_instrumentation
    {
    INSTRUMENT_REPORT = -1,     /* report current instrumentation state */
    INSTRUMENT_OFF  = 0,        /* instrumentation off */
    INSTRUMENT_ON   = 1	        /* instrumentation on */
    } WV_INSTRUMENTATION_MODE;

typedef enum wv_stacktrace
    {
    STACKTRACE_REPORT = -1,     /* report current stacktrace state */
    STACKTRACE_OFF  = 0,        /* stacktrace off */
    STACKTRACE_ON   = 1	        /* stacktrace on */
    } WV_STACKTRACE_MODE;

/* globals */
    
extern char *           wvLogMsgString1;
extern char *           wvLogMsgString2;
extern char *           wvUploadName;

extern int              wvMaximumLogs;
    
extern UPLOAD_ID  (*_func_wvOnUploadPathCreate)();
extern STATUS (*_func_wvOnUploadPathClose)(UPLOAD_ID upId);
    
/* function declarations */

extern void   		wvLibInit (void);
extern void   		wvLibInit2 (void);
extern STATUS		wvEvtLogInit (WV_LOG *  pWvLog);

extern STATUS 		wvEvtLogStart (void);
extern void   		wvEvtLogStop (void);

extern void   		wvEvtClassSet (UINT32 classDescription);
extern UINT32  		wvEvtClassGet (void);
extern void   		wvEvtClassClear (UINT32 classDescription);
extern void   		wvEvtClassClearAll (void);
extern int 		wvObjInst (enum windObjClassType type, void *objId,
                                   BOOL evtLoggingOn);
extern int              wvEventInst (WV_INSTRUMENTATION_MODE mode);
extern int              wvSigInst (WV_INSTRUMENTATION_MODE mode);
extern int              wvSalInst (WV_INSTRUMENTATION_MODE mode);
extern void             wvAllObjsSet (WV_INSTRUMENTATION_MODE mode);
extern STATUS           wvObjInstModeSet (WV_INSTRUMENTATION_MODE mode);
extern int              wvEdrInst (WV_INSTRUMENTATION_MODE mode);
extern int              wvMemScopeInst (WV_INSTRUMENTATION_MODE mode);

extern int 		wvObjStacktrace (enum windObjClassType type, void *objId,
                                   BOOL evtLoggingOn);
extern void             wvAllObjsStacktraceSet (WV_STACKTRACE_MODE mode);
extern STATUS           wvObjStacktraceModeSet (WV_STACKTRACE_MODE mode);

extern int              wvPowerInst (WV_INSTRUMENTATION_MODE mode);
extern int              wvUsbInst (WV_INSTRUMENTATION_MODE mode);

#if defined _WV_SPINLOCK_INSTRUMENTATION
extern int              wvSpinLockInst (WV_INSTRUMENTATION_MODE mode);
#endif /* _WV_SPINLOCK_INSTRUMENTATION */

#if defined _WV_CPC_INSTRUMENTATION
extern int              wvCpcInst (WV_INSTRUMENTATION_MODE mode);
#endif /* _WV_CPC_INSTRUMENTATION */
    
extern BUFFER_ID	wvEvtBufferGet (void);
extern void		wvUploadTaskConfig (size_t stackSize, int priority);
extern STATUS 		wvUploadStop (WV_UPLOADTASK_ID upTaskId);
extern WV_UPLOADTASK_ID wvUploadStart (WV_LOG * bufId, UPLOAD_ID pathId, 
                                       BOOL uploadContinuously);
    
extern PART_ID          wvPartitionGet (void);
extern void             wvPartitionSet (PART_ID part);
    
extern WV_LOG_LIST *    wvCurrentLogListGet (void);
extern void             wvCurrentLogListSet (WV_LOG_LIST * pWvLogList);

extern WV_LOG *         wvLogCreate (BUFFER_ID evtBuffer);
extern STATUS           wvLogDelete (WV_LOG_LIST * pWvLogList,
                                     WV_LOG * pWvLog);
extern WV_LOG *         wvCurrentLogGet (void);
extern void             wvCurrentLogSet (WV_LOG * pWvLog);

extern WV_LOG *         wvLogFirstGet (void);
extern WV_LOG *         wvLogNextGet (WV_LOG * pWvLog);
extern int              wvLogCountGet (void);


    
extern WV_LOG_LIST *    wvLogListCreate (void);
extern STATUS           wvLogListDelete (WV_LOG_LIST *  pLogList);

    
extern STATUS 		wvEvent (event_t usrEventId, char *buffer, 
				 size_t bufSize);

extern STATUS wvCallStackDepthSet(unsigned int depth);

extern STATUS wvCallStackSetLevel(int level,
                                  int callStackEnable);

extern STATUS wvCallStackSetEvent(event_t evtId, int callStackEnable);

extern STATUS wvTaskCallStackSet(TASK_ID *tid, int num);

extern STATUS wvTaskCallStackClear(void);

extern STATUS wvCallStackFilterSet(int enable);

extern int wvLogVersionGet();

#ifdef _WRS_CONFIG_RTP
extern int wvRtpMemInst (WV_INSTRUMENTATION_MODE mode);
#endif

#ifdef __cplusplus
}
#endif

#endif /* __INCwvlibh*/

