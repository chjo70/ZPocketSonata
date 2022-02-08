/* evtLogLibP.h - event log header */

/*
 * Copyright (c) 1994-2008, 2010-2011, 2013, 2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */
 

/*
modification history
--------------------
23apr15,wzc  remove MAX_WV_TASKS.(V7COR-2837)
03jun13,wzc  Added stacktrace for system viewer.
29aug11,wzc  Update to support dynamic power management (WIND00295115)
27jul11,wzc  PPM for SV (WIND00214625)
10feb10,tcr  update for 64bit
29apr10,pad  Moved extern C statement after include statements.
08apr08,tcr  add log routine for perfMon
20dec06,tcr  add functions for SMP support
21apr04,tcr  add parameter to logging function
05mar04,tcr  add evtEdrErrorInject()
11sep03,tcr  tidy up function prototypes
18jul03,tcr  updates for Base6
29apr03,pes  PAL conditional compilation cleanup.
09may02,pcm  added preceding underscore to ASMLANGUAGE
18oct01,tcr  update for VxWorks 5.5
17feb98,pr   changed prototype for evtLogO and evtLogOInt.
02feb98,nps  Allow inclusion in (68k) assembler source.
27jan98 cth  added BEGIN, CONFIG, BUFFER, END sizes, added function 
		 declarations, updated copyright
31jul97 nps  WindView 2.0 -
             EVTLOG_STR_SIZE was incorrectly defined as 18, should be 22.
14dec94 rdc  mods for am29k.
28nov94 rdc  mods for x86.
05may94,smb  corrected macro name EVTLOG_T1_SIZE
12jan94,c_s  made EVTLOG_*_SIZE constants architecture-specific; commented
           +maf    them, and added definition of MAX_KERNEL_EVENT_SIZE.
	           SPR #2840.
10dec93,smb  written.
*/

#ifndef __INCevtloglibph
#define __INCevtloglibph

#ifndef _ASMLANGUAGE

#include <dataCollectorLib.h>
#include <private/eventP.h> /* for event_t */
#include <private/wvBufferP.h>

#ifdef __cplusplus
extern "C" {
#endif

#endif	/* !_ASMLANGUAGE */

/* defines */

/* sizes of events with timestamps */
    
#define EVTLOG_TN_SIZE(nParam)  (sizeof (short) + \
                                 sizeof (int) + nParam *sizeof(_Vx_usr_arg_t))

/* sizes of events without timestamps */
    
#define EVTLOG_MN_SIZE(nParam)  (sizeof (short) + \
                                 nParam * sizeof(_Vx_usr_arg_t))

#ifndef	_ASMLANGUAGE

/* function declarations */

extern STATUS evtLogLibInit (void);
extern void evtObjLogFuncBind (void);
extern void evtLogFuncBind (void);
extern void evtBufferBind (BUFFER_ID bufId);
extern void evtLogO (event_t action, int nParam, _Vx_usr_arg_t arg1,
		     _Vx_usr_arg_t arg2,_Vx_usr_arg_t arg3,
		     _Vx_usr_arg_t arg4, _Vx_usr_arg_t arg5,
		     _Vx_usr_arg_t arg6);
extern int evtLogPoint (event_t action, void *addr, size_t nbytes, char *buf);

extern void evtEdrErrorInject (event_t action, int kind, const char * fileName,
                               int lineNumber, const void * address,
                               const char * textPayload, int st);
extern STATUS evtLogPayload (event_t action, int withTimestamp, const void * addr,
                             size_t nbytes, int st);
extern STATUS evtLogPayloadString (event_t action, int withTimestamp,
                                   const void * addr, size_t nbytes,
                                   const void * stringAddr, size_t stringSize, int st);

#ifdef _WV_SPINLOCK_INST
extern void evtSpinLockEventIdLog (event_t eventId, const void * pLock);
extern void evtSpinLockEventLog (event_t eventId, const void * pLock);
#endif
    
#ifdef __cplusplus
}
#endif
#endif	/* !_ASMLANGUAGE */

#endif /* __INCevtloglibph*/

