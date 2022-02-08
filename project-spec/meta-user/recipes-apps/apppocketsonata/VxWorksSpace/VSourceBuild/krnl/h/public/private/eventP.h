/* eventP.h - event log header */

/*
 * Copyright (c) 1994-2011, 2013-2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */
 
/*
modification history
--------------------
20oct15,gxu  dataCollectorLib cannot log without System Viewer(US68020).
07jul15,dee  EVT_STORE_S compiler warning etoa:5386 removed
04nov14,jpb  removed funcBindP.h (V7COR-910)
06jan15,wzc  fix atomic operations to 32bit.(V7COR-2424)
02jul14,wzc  clear static analysis warning.(WB4-3827)
05mar14,wzc  remove WRS_FIXME because it has processed in filter.(WB4-2879)
03jun13,wzc  Support stacktrace for system viewer.
29aug11,wzc  Update to support dynamic power management (WIND00295115)
27jul11,wzc  PPM for SV (WIND00214625)
31jan11,jpb  Defect WIND00253474. Fixed build warning.
22nov10,wzc  Fix the LITTLE_ENDIAN issue of EVT_STORE(WIND00242104)
01oct10,vhe  Fix shifts in LP64 for unaligned support
24sep10,jpb  Added global variable evtAction.  Moved from funcBindP.h
21jun10,vhe  Add cast to PC for different arch
31may10,wzc  Moved EVT_CTX_BUF_T to EVT_WVEVENT (WIND00214658).
26may10,pad  Moved extern C statement after include statements.
26may10,tcr  add EVT_CTX_NODISP back
10feb10,tcr  Update for LP64 System Viewer
26may09,tcr  create optimized CTX_DISP event
29sep08,tcr  change intrumentation test if OBJECT_CLASS_LIST excluded
16sep08,tcr  Fix WIND00130140: Change while(0) to while((0))
16jul08,to   rename _WRS_EXPECT_UNLIKELY to _WRS_UNLIKELY
25jul08,tcr  update macro
04jul08,tcr  update structures
13jun08,tcr  change evtAction modifiers to atomic
09may08,tcr  fix tasknames preservation
02may08,tcr  move event definitions out
01may08,aim  call eventPointSwHandle in EVT_CTX_TASKINFO
17mar08,tcr  change macros to function calls
12may08,to   use _WRS_EXPECT_UNLIKELY for logging path
21sep07,tcr  correct EVT_CTX_RTPINFO macro (WIND00105753)
12jun07,tcr  more SMP updates
19dec06,tcr  add revision id for SMP
15feb07,jmg  Added level 2 event EVENT_WINDROTATE for windRotate
09jan07,jmg  Added EVENT_TASKROTATE (Req. WIND00071010)
23jan06,tcr  Change log revision ID to track syscall changes
             Split EVT_CTX_0 for taskLock logging (SPR 115859)
14jun05,tcr  add events for ioLib
23feb05,tcr  update comments for apigen
17sep04,tcr  add sdLib events
03aug04,pch  Add PPC_WD_INT_ID for ppc4xx/ppc85xx hardware watchdog timer
06oct04,pch  renumbered history
17sep04,tcr  add sdLib events
03aug04,pch  Add PPC_WD_INT_ID for ppc4xx/ppc85xx hardware watchdog timer
04may04,ymz  modified SAL event ID to resolve clashes.
28apr04,ymz  added SAL event ID and macro.
26apr04,tcr  include code review comments for rtpSigLib.c
15apr04,tcr  add macros and events for rtpLib
18mar04,tcr  add RTP signal events
25mar04,cpd  Re-add a State Change event
04mar04,aim  renumbered EVENT_EDR_ERROR_INJECT to CLASS3(80)
18feb04,tcr  add events for rtpLib
24nov03,tcr  update EVENT_MEMREALLOC
17nov03,tcr  add OBJ_VERIFY fail handling
03nov03,tcr  add syscall events; add rtp to EVENT_TASKNAME;
             validate objects in macros
25sep03,tcr  always preserve tasknames
16sep03,tcr  add events for isrLib
09sep03,tcr  changes to event formats, change class instrumentation
08sep03,tcr  change event formats
05sep03,tcr  fix merge error
05sep03,tcr  fix merge error
02sep03,tcr  Base6 changes for obj instrumentation
04dec03,aim  updated EVT_EDR
04aug03,elg  Add support for new task status: define events related to new
             status for instrumentation.
19sep03,aim  added ED&R events
13may03,pes  PAL conditional compilation cleanup. Phase 2.
04jun03,bwa  Added macros for message channels and services.
09may03,to   changed OBJ_ID to OBJ_CORE * in OBJ_EVT_RTN and TASK_EVT_RTN,
	     deleted condition code for OBJ_INST_RTN.
09may02,tcr  Fix for SPR 74987 (add #ifdef __cplusplus)
31oct01,tcr  add event range for RTI
18oct01,tcr  add support for VxWorks Events, move to VxWorks 5.5
27sep01,tcr  Fix SPR 24971 - instrument PPC interrupts
13sep01,tcr  Fix SPR 29673 - macro for msgQSmLib events
09sep98,cjtc reverting to byte ordering based on _BYTE_ORDER macro
04sep98,cjtc porting for ARM architechture
02sep98,nps  corrected WV2.0 -> T2 merge.
24aug98,cjtc intEnt logging for PPC is now performed in a single step
	     instead of the two-stage approach which gave problems with
	     out-of-order timestamps in the event log (SPR 21868)
17aug98,pr   replaced OBJ_VERIFY check with check on NULL pointer
08may98,pr   added number of params for EVT_OBJ_SIG macro
08may98,pr   added argument for wv logging in SIG and SM_MSGQ macros
15apr98,cth  added event class WV_CLASS_TASKNAMES_PRESERVE/ON, and call to
	     _func_evtLogReserveTaskName
08apr98,pr   reordered the definition of EVENT_SEMFLUSH and EVENT_SEMDELETE
07apr98,cjtc added () to EVENT_INT_ENT to prevent problem with macro
	     expansion.
22mar98,pr   modified EVT_CTX_BUF to accept TRG_USER_INDEX events.
	     modified definition of EVENT_SEMFLUSH and EVENT_SEMDELETE.
04mar98,nps  modified xxx_CLASS_n_ON macros so they can be used by
             inadequate assmblers.
17feb98,pr   added number of params to EVT_OBJ macros.
17feb98,dvs  added events for memory instrumentation. (pr)
27jan98,cth  removed EVENT_BUFFER, CONFIG, BEGIN, END _SIZE definitions,
	     updated copyright
22jan98,pr   made some macros readable also by the assembly.
	     added extra bit to evtAction.
	     added EVT_CTX_IDLE, EVT_CTX_NODISP macros.
12jan98,dbs  added EVENT_NIL and EVENT_VALUE to pseudo-events.
13dec97,pr   reduced the number of args passed to _func_trgCheck
             moved some extern declaration in funcBindP.h
20nov97,pr   added some event triggering defines and modified event
             logging macros
17nov97,cth  added EVENT_CONFIG_SIZE, _BEGIN_SIZE, _END_SIZE, _BUFFER_SIZE
27oct97,pr   redefined levels as classes.
	     redesigned all the macros for managing classes.
28aug97,pr   modified WV_OFF to reflect new levels.
26aug97,pr   replaced WV_IS_ON with proper LEVEL
18aug97,pr   added trigger calls.
24jun97,pr   Added declarations for WindView 2.0 variables
	     modified macros to include new variable and triggers
11Apr96,pr   changed if statement in EVT_OBJ_SM_MSGQ, SPR #6048, #6271
22feb95,rdc  added EVENT_TASK_STATECHANGE.
01feb95,rdc  added EVENT_TIMER_SYNC.
27jan95,rdc  added processor number to EVENT_CONFIG.
28nov94,rdc  changed 32 bit store macros for x86.
02nov94,rdc  added protocol revision to EVENT_CONFIG.
	     added lockCnt param to EVT_CTX_TASKINFO.
02nov94,rdc  added 960 macros.
27may94,pad  added alignment macros. Corrected some parameter comments.
14apr94,smb  optimised EVT_OBJ_ macros.
04mar94,smb  added EVENT_INT_EXIT_K
	     changed parameters for EVENT_WIND_EXIT_NODISPATCH
	     removed EVENT_WIND_EXIT_IDLENOT
	     level 1 event optimisations
	     added macro for shared memory objects
22feb94,smb  changed typedef EVENT_TYPE to event_t (SPR #3064)
16feb94,smb  introduced new OBJ_ macros, SPR #2982
26jan94,smb  redid pseudo events - generated host side
24jan94,smb  added EVENT_WIND_EXIT_DISPATCH_PI and
	     EVENT_WIND_EXIT_NODISPATCH_PI
	     added event logging macros
17dec93,smb  changed typedef of EVENT_TYPE
10dec93,smb  modified MAX_LEVEL3_ID to include interrupt events
	     renamed EVENT_CLOCK_CONFIG to EVENT_CONFIG
08dec93,kdl  added include of classLibP.h; made def of OBJ_INST_FUNC
       +smb  conditional on OBJ_INST_RTN; reformatted macro comments;
             made includes and obj macros depend on CPU (i.e. not host).
07dec93,smb  written.
*/

#ifndef __INCeventph
#define __INCeventph

/*
 * This file contains windview logging macros, and structures
 * representing generic event formats. Event ids, and the Event-specific
 * structures are defined in eventDefsP.h
 */

/* Triggering and Windview events definitions and macros.
 * They correspond to the old levels and are the only classes we
 * identify for the moment. They are also used by the architecture
 * dependent files, therefore are defined also for assembly languages.
 */

#ifdef	CPU				/* only for target, not host */

/* this is used by both WV and TRG */

#define WV_CLASS_NONE    		0x00000000

#define WV_CLASS_1    			0x00000001   /* Context Switch */
#define WV_CLASS_2    			0x00000003   /* Task State Transition */
#define WV_CLASS_3    			0x00000007   /* Object and System Libraries */
#define WV_CLASS_TASKNAMES_PRESERVE	0x00001000
#define WV_ON           		0x10000000
#define WV_CLASS_1_ON  			0x10000001
#define WV_CLASS_2_ON 			0x10000003
#define WV_CLASS_3_ON  			0x10000007
#define WV_CLASS_TASKNAMES_PRESERVE_ON	0x10001000

#define TRG_CLASS_1     		0x00000001
#define TRG_CLASS_2     		0x00000010
#define TRG_CLASS_3     		0x00000100
#define TRG_CLASS_4     		0x00001000
#define TRG_CLASS_5     		0x00010000
#define TRG_CLASS_6     		0x01111111
#define TRG_ON          		0x10000000
#define TRG_CLASS_1_ON  		0x10000001
#define TRG_CLASS_2_ON  		0x10000010
#define TRG_CLASS_3_ON  		0x10000100
#define TRG_CLASS_4_ON  		0x10001000
#define TRG_CLASS_5_ON  		0x10010000
#define TRG_CLASS_6_ON  		0x11111111

#define TRG_CLASS1_INDEX	0
#define TRG_CLASS2_INDEX	1
#define TRG_CLASS3_INDEX	2
#define TRG_USER_INDEX		3
#define TRG_INT_ENT_INDEX	4
#define TRG_ANY_EVENT_INDEX	5
#define TRG_CONTROL_INDEX	6

#endif /* CPU */

#include <vsbConfig.h>
#include <private/eventDefsP.h>
    
/* types */

#ifndef _ASMLANGUAGE


#ifdef	CPU				/* only for target, not host */

#include <private/classLibP.h>
#include <private/objLibP.h>
#include <private/eventPointStubLibP.h>
#include <vxAtomicLib.h>

#ifdef __cplusplus
extern "C" {
#endif

extern UINT32 evtAction;

/*
 * All logging macros use this test to minimize overhead when logging is
 * disabled
 */

/*
 * evtAction bits: bit0 trgLib, bit8 system viewer, bit16 user-specific dataCollector, bit31 TOP
 */
#define EVT_TRG_ENABLED            0x00000001
#define EVT_WV_ENABLED             0x00000100
#define EVT_DC_ENABLED             0x00020000
#define EVT_TOP_ENABLED            0x80000000

#define ACTION_IS_SET			    _WRS_UNLIKELY(evtAction != 0)

#define TRG_ACTION_IS_SET          ( (evtAction&0x000000ff) == EVT_TRG_ENABLED )
#define WV_ACTION_IS_SET           ( (evtAction&0x0000ff00) == EVT_WV_ENABLED )
#define DC_ACTION_IS_SET           ( (evtAction&EVT_DC_ENABLED) == EVT_DC_ENABLED )
#define TOP_ACTION_IS_SET          ( (evtAction&EVT_TOP_ENABLED) == EVT_TOP_ENABLED )

#define TRG_ACTION_SET                  \
        {                               \
        (void)vxAtomic32Or ((atomic32_t*)&evtAction, EVT_TRG_ENABLED);      \
        }

#define TRG_ACTION_UNSET                \
        {                               \
        (void)vxAtomic32And ((atomic32_t*)&evtAction, ~(EVT_TRG_ENABLED));  \
        }

#define WV_ACTION_SET                   \
        {                               \
        (void)vxAtomic32Or ((atomic32_t*)&evtAction, EVT_WV_ENABLED);      \
        }

#define WV_ACTION_UNSET                 \
        {                               \
        (void)vxAtomic32And ((atomic32_t*)&evtAction, ~(EVT_WV_ENABLED));  \
        }

#define DC_ACTION_SET                  \
        {                               \
        (void)vxAtomic32Or ((atomic32_t*)&evtAction, EVT_DC_ENABLED);      \
        }

#define DC_ACTION_UNSET                \
        {                               \
        (void)vxAtomic32And ((atomic32_t*)&evtAction, ~(EVT_DC_ENABLED));  \
        }

#define TOP_ACTION_SET                  \
        {                               \
        (void)vxAtomic32Or ((atomic32_t*)&evtAction, EVT_TOP_ENABLED);      \
        }

#define TOP_ACTION_UNSET                \
        {                               \
        (void)vxAtomic32And ((atomic32_t*)&evtAction, ~(EVT_TOP_ENABLED));  \
        }

/*
*
* OBJ_INSTRUMENTED - get instrumentation status for an object
*
* If _WRS_CONFIG_OBJECT_CLASS_LIST not defined, we just test the object class.
* I.e., we cannot instrument individual instances in that case
* 
* RETURNS: non-zero if instrumentation for this object is enabled
*/

#ifdef _WRS_CONFIG_OBJECT_CLASS_LIST

#define OBJ_INSTRUMENTED(objId)					\
    ((((OBJ_CORE *)(objId))->handle.attributes) & WIND_OBJ_INSTRUMENTED)	

#define OBJ_STACKTRACE(objId)					\
    ((((OBJ_CORE *)(objId))->handle.attributes) & WIND_OBJ_STACKTRACE)	

#else /* _WRS_CONFIG_OBJECT_CLASS_LIST */

#define OBJ_INSTRUMENTED(objId)					\
    ((((OBJ_CORE *)(objId))->pObjClass->handle.attributes) & WIND_CLASS_INSTRUMENTED)

#define OBJ_STACKTRACE(objId)					\
    ((((OBJ_CORE *)(objId))->pObjClass->handle.attributes) & WIND_CLASS_STACKTRACE)

#endif /* _WRS_CONFIG_OBJECT_CLASS_LIST */    


/*
*
* EVT_CTX_0_BH - context switch event logging with event id, bottom half
* This macro doesn't test ACTION_IS_SET, for speed, as this will already have
* been done.
*/
    
#define EVT_CTX_0_BH(evtId)                                                 \
    eventPointSwHandle (evtId, NULL, 0)

    
/*
*
* EVT_CTX_0 - context switch event logging with event id
*
*/
    
#define EVT_CTX_0(evtId)                                                    \
do { \
    if (ACTION_IS_SET)					                    \
        eventPointSwHandle (evtId, NULL, 0); \
} while ((0))

/*
*
* EVT_CTX_1 - context switch event logging with one parameter
*
*/

typedef struct
    {
    _Vx_usr_arg_t args [1];
    } EVT_CTX_1_T;


#define EVT_CTX_1(evtId, ARG1)                                               \
do { \
    if ( ACTION_IS_SET )			\
        { \
        EVT_CTX_1_T evt_ctx_1; \
        evt_ctx_1.args [0] = (_Vx_usr_arg_t)ARG1; \
        eventPointSwHandle (evtId, &evt_ctx_1, sizeof evt_ctx_1); \
        } \
} while ((0))


/*
*
* EVT_CTX_IDLE - log EVENT_WIND_EXIT_IDLE event
*
* This macro stores information into the event buffer if the system is idle.
*
*/

#define EVT_CTX_IDLE(evtId)               EVT_CTX_0(evtId)

/*
*
* EVT_CTX_DISP - context switch event logging for reschedule
*
* This macro stores information into the event buffer about rescheduling tasks
* in the system. In order to determine the right event type, it first checks the
* two last args. It is used to log the DISPATCH event. Therefore the two last 
* args are the current priority and the normal priority.
*
* The macro comes in two flavors: One where the evAction test is included, one
* where it is assumed to have already been done
*
*/

#define EVT_CTX_DISP_NOTEST(ARG1, PRI, NORMAL_PRI)      \
do {                                                    \
    EVENT_WIND_EXIT_DISPATCH_T evt_ctx_disp;            \
    evt_ctx_disp.taskIdNew = ARG1;		        \
    evt_ctx_disp.priority = PRI;                        \
    if (NORMAL_PRI > PRI)				\
        eventPointSwHandle (EVENT_WIND_EXIT_DISPATCH_PI,\
                            &evt_ctx_disp, 		\
                            sizeof evt_ctx_disp);       \
    else						\
        eventPointSwHandle (EVENT_WIND_EXIT_DISPATCH,   \
                            &evt_ctx_disp, 		\
                            sizeof evt_ctx_disp);       \
} while ((0))


#define EVT_CTX_DISP(ARG1, PRI, NORMAL_PRI)    	        \
do {                                                    \
    if ( ACTION_IS_SET )			        \
        EVT_CTX_DISP_NOTEST(ARG1, PRI, NORMAL_PRI);     \
} while ((0))


/*
*
* EVT_CTX_NODISP - context switch event logging for reschedule
*/

#define EVT_CTX_NODISP(TASKID, PRI, PRI_NORMAL)       \
do { \
   if (ACTION_IS_SET) \
       { \
       EVENT_WIND_EXIT_NODISPATCH_T evt_ctx_nodisp; \
       evt_ctx_nodisp.taskId = TASKID; \
       eventPointSwHandle((PRI_NORMAL > PRI ? EVENT_WIND_EXIT_NODISPATCH_PI : \
                           EVENT_WIND_EXIT_NODISPATCH), \
                           &evt_ctx_nodisp, sizeof evt_ctx_nodisp); \
       } \
 } while ((0))

/*
*
* EVT_CTX_TASKINFO - context switch event logging with task information
*
* This macro stores information into the event buffer about a task
* in the system.
*
*/

#define EVT_CTX_TASKINFO(evtId, STATE, PRIORITY, LOCKCNT, TID, ENTRYPT, RTP,   \
                         AFFINITY, NAME)                                      \
do { \
    if ( ACTION_IS_SET )						      \
       { \
       EVENT_TASKNAME_T evt_ctx_taskinfo; \
       evt_ctx_taskinfo.state = STATE; \
       evt_ctx_taskinfo.priority = PRIORITY; \
       evt_ctx_taskinfo.lockCnt = LOCKCNT; \
       evt_ctx_taskinfo.tid = TID; \
       evt_ctx_taskinfo.entryPt = ENTRYPT; \
       evt_ctx_taskinfo.rtp = RTP; \
       evt_ctx_taskinfo.affinity = AFFINITY; \
       evt_ctx_taskinfo.name = NAME; \
       eventPointSwHandle (evtId, &evt_ctx_taskinfo, sizeof evt_ctx_taskinfo); \
       } \
} while ((0))

 
/*
*
* EVT_CTX_RTPINFO - context switch event logging with RTPinformation
*
* This macro stores information into the event buffer about an RTP
* in the system.
*
*/

#define EVT_CTX_RTPINFO(evtId, OPTIONS, OWNERID, RTPID, NAME) \
do { \
    if (ACTION_IS_SET) \
        { \
        EVENT_RTPNAME_T evt_ctx_rtpinfo; \
        evt_ctx_rtpinfo.options = OPTIONS; \
        evt_ctx_rtpinfo.ownerId = OWNERID; \
        evt_ctx_rtpinfo.rtpId = RTPID; \
        evt_ctx_rtpinfo.pRtpName = NAME; \
        eventPointSwHandle (evtId, &evt_ctx_rtpinfo, sizeof evt_ctx_rtpinfo); \
        } \
} while ((0))

/*
*
* EVT_TASK_0 - task state transition event logging with event id.
*
*/

#define EVT_TASK_0(evtId)                                                   \
do { \
    if ( ACTION_IS_SET )					            \
        eventPointSwHandle(evtId, NULL, 0); \
} while ((0)) 


/*
*
* EVT_TASK_1 - task state transition event logging with one argument.
*
*/

typedef struct
    {
    _Vx_usr_arg_t  args [1];
    } EVT_TASK_1_T;


#define EVT_TASK_1(evtId, ARG)                                              \
do { \
    if ( ACTION_IS_SET )					            \
        { \
        EVT_TASK_1_T evt_task_1; \
        evt_task_1.args [0] = (_Vx_usr_arg_t)ARG; \
        eventPointSwHandle(evtId, &evt_task_1, sizeof evt_task_1); \
        } \
} while ((0))


/*
*
* EVT_TASK_2 - task state transition event logging with two arguments.
*
*/

typedef struct
    {
    _Vx_usr_arg_t  args [2];
    } EVT_TASK_2_T;

#define EVT_TASK_2(evtId, ARG1, ARG2)                                       \
do { \
   if ( ACTION_IS_SET )					            \
        { \
        EVT_TASK_2_T evt_task_2; \
        evt_task_2.args [0] = (_Vx_usr_arg_t)ARG1; \
        evt_task_2.args [1] = (_Vx_usr_arg_t)ARG2; \
        eventPointSwHandle(evtId, &evt_task_2, sizeof evt_task_2); \
        } \
} while ((0))

/*
*
* EVT_TASK_3 - task state transition event logging with three arguments.
*
*/

typedef struct
    {
    _Vx_usr_arg_t  args [3];
    } EVT_TASK_3_T;

#define EVT_TASK_3(evtId, ARG1, ARG2, ARG3)                                 \
do { \
    if ( ACTION_IS_SET )					            \
        { \
        EVT_TASK_3_T evt_task_3; \
        evt_task_3.args [0] = (_Vx_usr_arg_t)ARG1; \
        evt_task_3.args [1] = (_Vx_usr_arg_t)ARG2; \
        evt_task_3.args [2] = (_Vx_usr_arg_t)ARG3; \
        eventPointSwHandle(evtId, &evt_task_3, sizeof evt_task_3); \
        } \
} while ((0))

/*
*
* EVT_SYSCALL_ENTRY - record syscall event with params
*
*/

/* typedef EVENT_SYSCALL_ENTER_T EVT_SYSCALL_ENTRY_T; */
    
#define EVT_SYSCALL_ENTRY(RTPID, NPARAMS, PSTATE) \
do { \
    if (ACTION_IS_SET) \
        { \
        EVENT_SYSCALL_ENTER_T evt_syscall_entry; \
        evt_syscall_entry.rtpId = RTPID; \
        evt_syscall_entry.nParams = NPARAMS; \
        evt_syscall_entry.pState = PSTATE; \
        eventPointSwHandle(EVENT_SYSCALL_ENTER, &evt_syscall_entry, \
                               sizeof evt_syscall_entry); \
        } \
} while ((0))
    
/*
*
* EVT_OBJ_6 - object status event logging with six arguments.
*
*/

typedef struct
    {
    OBJ_ID      objId;
    CLASS_ID    classId;
    _Vx_usr_arg_t args [6];
    } EVT_OBJ_6_T;
        
#define EVT_OBJ_6(OBJ, CLASS, evtId, ARG1, ARG2, ARG3,          \
                  ARG4, ARG5, ARG6)			        \
do { \
    if ( ACTION_IS_SET ) \
        { \
        EVT_OBJ_6_T evt_obj_6; \
        evt_obj_6.objId = OBJ; \
        evt_obj_6.classId = CLASS; \
        evt_obj_6.args [0] = (_Vx_usr_arg_t)ARG1; \
        evt_obj_6.args [1] = (_Vx_usr_arg_t)ARG2; \
        evt_obj_6.args [2] = (_Vx_usr_arg_t)ARG3; \
        evt_obj_6.args [3] = (_Vx_usr_arg_t)ARG4; \
        evt_obj_6.args [4] = (_Vx_usr_arg_t)ARG5; \
        evt_obj_6.args [5] = (_Vx_usr_arg_t)ARG6; \
        eventPointSwHandle(evtId, &evt_obj_6, sizeof evt_obj_6); \
        } \
} while ((0))


/*
*
* EVT_OBJ_5 - object status event logging with five arguments.
*
*/

typedef struct
    {
    OBJ_ID      objId;
    CLASS_ID    classId;
    _Vx_usr_arg_t args [5];
    } EVT_OBJ_5_T;
    
#define EVT_OBJ_5(OBJ, CLASS, evtId, ARG1, ARG2, ARG3,                  \
		     ARG4, ARG5)					    \
do { \
    if ( ACTION_IS_SET )			         		    \
        { \
        EVT_OBJ_5_T evt_obj_5; \
        evt_obj_5.objId = OBJ; \
        evt_obj_5.classId = CLASS; \
        evt_obj_5.args [0] = (_Vx_usr_arg_t)ARG1; \
        evt_obj_5.args [1] = (_Vx_usr_arg_t)ARG2; \
        evt_obj_5.args [2] = (_Vx_usr_arg_t)ARG3; \
        evt_obj_5.args [3] = (_Vx_usr_arg_t)ARG4; \
        evt_obj_5.args [4] = (_Vx_usr_arg_t)ARG5; \
        eventPointSwHandle(evtId, &evt_obj_5, sizeof evt_obj_5); \
        } \
} while ((0))


/*
*
* EVT_OBJ_4 - object status event logging with four arguments.
*
*/

typedef struct
    {
    OBJ_ID      objId;
    CLASS_ID    classId;
    _Vx_usr_arg_t args [4];
    } EVT_OBJ_4_T;
        
#define EVT_OBJ_4(OBJ, CLASS, evtId, ARG1, ARG2, ARG3,                  \
		     ARG4)					            \
do { \
    if ( ACTION_IS_SET )			         		    \
        { \
        EVT_OBJ_4_T evt_obj_4; \
        evt_obj_4.objId = OBJ; \
        evt_obj_4.classId = CLASS; \
        evt_obj_4.args [0] = (_Vx_usr_arg_t)ARG1; \
        evt_obj_4.args [1] = (_Vx_usr_arg_t)ARG2; \
        evt_obj_4.args [2] = (_Vx_usr_arg_t)ARG3; \
        evt_obj_4.args [3] = (_Vx_usr_arg_t)ARG4; \
        eventPointSwHandle(evtId, &evt_obj_4, sizeof evt_obj_4); \
        } \
} while ((0))

/*
*
* EVT_OBJ_3 - object status event logging with three arguments.
*
*/

typedef struct
    {
    OBJ_ID      objId;
    CLASS_ID    classId;
    _Vx_usr_arg_t args [3];
    } EVT_OBJ_3_T;
        
#define EVT_OBJ_3(OBJ, CLASS, evtId, ARG1, ARG2, ARG3)                  \
do { \
     if ( ACTION_IS_SET )			         		    \
        { \
        EVT_OBJ_3_T evt_obj_3; \
        evt_obj_3.objId = OBJ; \
        evt_obj_3.classId = CLASS; \
        evt_obj_3.args [0] = (_Vx_usr_arg_t)ARG1; \
        evt_obj_3.args [1] = (_Vx_usr_arg_t)ARG2; \
        evt_obj_3.args [2] = (_Vx_usr_arg_t)ARG3; \
        eventPointSwHandle(evtId, &evt_obj_3, sizeof evt_obj_3); \
        } \
} while ((0))

/*
*
* EVT_OBJ_2 - object status event logging with two arguments.
*
*/

typedef struct
    {
    OBJ_ID      objId;
    CLASS_ID    classId;
    _Vx_usr_arg_t args [2];
    } EVT_OBJ_2_T;

#define EVT_OBJ_2(OBJ, CLASS, evtId, ARG1, ARG2)                        \
do { \
    if ( ACTION_IS_SET )			         		    \
        { \
        EVT_OBJ_2_T evt_obj_2; \
        evt_obj_2.objId = OBJ; \
        evt_obj_2.classId = CLASS; \
        evt_obj_2.args [0] = (_Vx_usr_arg_t)ARG1; \
        evt_obj_2.args [1] = (_Vx_usr_arg_t)ARG2; \
        eventPointSwHandle(evtId, &evt_obj_2, sizeof evt_obj_2); \
        } \
} while ((0))


/*
*
* EVT_OBJ_1 - object status event logging with an argument.
*
*/

typedef struct
    {
    OBJ_ID      objId;
    CLASS_ID    classId;
    _Vx_usr_arg_t args [1];
    } EVT_OBJ_1_T;
        
#define EVT_OBJ_1(OBJ, CLASS, evtId, ARG1)                        \
do { \
    if ( ACTION_IS_SET )			         		    \
        { \
        EVT_OBJ_1_T evt_obj_1; \
        evt_obj_1.objId = OBJ; \
        evt_obj_1.classId = CLASS; \
        evt_obj_1.args [0] = (_Vx_usr_arg_t)ARG1; \
        eventPointSwHandle(evtId, &evt_obj_1, sizeof evt_obj_1); \
        } \
} while ((0))

    
typedef struct
    {
    CLASS_ID classId;
    unsigned int length;
    const char * string;
    } EVT_STR_CLASS_0_T;

#define EVT_STR_CLASS_0(CLASS, evtId,                                \
                      LENGTH, STRING)                           \
do { \
    if (ACTION_IS_SET) \
        { \
        EVT_STR_CLASS_0_T evt_str_class_0; \
        evt_str_class_0.length = LENGTH; \
        evt_str_class_0.string = STRING; \
        evt_str_class_0.classId = CLASS; \
        eventPointSwHandle (evtId, &evt_str_class_0, sizeof evt_str_class_0); \
        } \
} while ((0))


/*
*
* EVT_OBJ_STR_2 - object event logging with 2 params and a binary argument.
*
*/

typedef struct
    {
    OBJ_ID              objId;
    CLASS_ID            classId;
    size_t              length;
    const char *        pData;
    } EVT_OBJ_STR_T;

typedef struct
    {
    EVT_OBJ_STR_T       evt_obj_str;
    _Vx_usr_arg_t       args [2];
    } EVT_OBJ_STR_ARGS_2_T;

#define EVT_OBJ_STR_2(OBJ, CLASS, evtId,                                \
                      ARG1, ARG2, LENGTH, STRING)                           \
do { \
    if (ACTION_IS_SET) \
        { \
        EVT_OBJ_STR_ARGS_2_T evt_obj_str_args_2; \
        evt_obj_str_args_2.evt_obj_str.objId = OBJ; \
        evt_obj_str_args_2.evt_obj_str.classId = CLASS; \
        evt_obj_str_args_2.evt_obj_str.pData = STRING; \
        evt_obj_str_args_2.evt_obj_str.length = LENGTH; \
        evt_obj_str_args_2.args [0] = (_Vx_usr_arg_t)ARG1; \
        evt_obj_str_args_2.args [1] = (_Vx_usr_arg_t)ARG2; \
        eventPointSwHandle (evtId, &evt_obj_str_args_2, sizeof evt_obj_str_args_2); \
        } \
} while ((0))


    
/*
*
* EVT_OBJ_STR_3 - object event logging with 3 params and a binary argument.
*
*/

typedef struct
    {
    EVT_OBJ_STR_T       evt_obj_str;
    _Vx_usr_arg_t       args [3];
    } EVT_OBJ_STR_ARGS_3_T;
    
#define EVT_OBJ_STR_3(OBJ, CLASS, evtId,                                \
                      ARG1, ARG2, ARG3, LENGTH, STRING)                     \
do { \
    if (ACTION_IS_SET) \
        { \
        EVT_OBJ_STR_ARGS_3_T evt_obj_str_args_3; \
        evt_obj_str_args_3.evt_obj_str.objId = OBJ; \
        evt_obj_str_args_3.evt_obj_str.classId = CLASS; \
        evt_obj_str_args_3.evt_obj_str.pData = STRING; \
        evt_obj_str_args_3.evt_obj_str.length = LENGTH; \
        evt_obj_str_args_3.args [0] = (_Vx_usr_arg_t)ARG1; \
        evt_obj_str_args_3.args [1] = (_Vx_usr_arg_t)ARG2; \
        evt_obj_str_args_3.args [2] = (_Vx_usr_arg_t)ARG3; \
        eventPointSwHandle (evtId, &evt_obj_str_args_3, sizeof evt_obj_str_args_3); \
        } \
} while ((0))


/*
*
* EVT_OBJ_STR_5 - object event logging with 5 params and a binary argument.
*
*/

typedef struct
    {
    EVT_OBJ_STR_T       evt_obj_str;
    _Vx_usr_arg_t       args [5];
    } EVT_OBJ_STR_ARGS_5_T;
    
#define EVT_OBJ_STR_5(OBJ, CLASS, evtId,                                \
                      ARG1, ARG2, ARG3, ARG4, ARG5, LENGTH, STRING)         \
do { \
    if (ACTION_IS_SET) \
        { \
        EVT_OBJ_STR_ARGS_5_T evt_obj_str_args_5; \
        evt_obj_str_args_5.evt_obj_str.objId = OBJ; \
        evt_obj_str_args_5.evt_obj_str.classId = CLASS; \
        evt_obj_str_args_5.evt_obj_str.pData = STRING; \
        evt_obj_str_args_5.evt_obj_str.length = LENGTH; \
        evt_obj_str_args_5.args [0] = (_Vx_usr_arg_t)ARG1; \
        evt_obj_str_args_5.args [1] = (_Vx_usr_arg_t)ARG2; \
        evt_obj_str_args_5.args [2] = (_Vx_usr_arg_t)ARG3; \
        evt_obj_str_args_5.args [3] = (_Vx_usr_arg_t)ARG4; \
        evt_obj_str_args_5.args [4] = (_Vx_usr_arg_t)ARG5; \
        eventPointSwHandle (evtId, &evt_obj_str_args_5, sizeof evt_obj_str_args_5); \
        } \
} while ((0))


typedef struct
    {
    EVT_OBJ_STR_T       evt_obj_str;
    } EVT_OBJ_STR_0_T;
    
#define EVT_OBJ_STR_0(OBJ, CLASS, evtId, LENGTH, STRING)         \
do { \
    if (ACTION_IS_SET) \
        { \
        EVT_OBJ_STR_0_T evt_obj_str_0; \
        evt_obj_str_args_0.evt_obj_str.objId = OBJ; \
        evt_obj_str_args_0.evt_obj_str.classId = CLASS; \
        evt_obj_str_args_0.evt_obj_str.pData = STRING; \
        evt_obj_str_args_0.evt_obj_str.length = LENGTH; \
        eventPointSwHandle (evtId, &evt_obj_str_0, sizeof evt_obj_str_0); \
        } \
} while ((0))


/*
*
* EVT_OBJ_TASKSPAWN - object status event logging for a spawned task.
*
*/

#define EVT_OBJ_TASKSPAWN(evtId, TID, PRI, STACKSIZE, ENTRYPT, OPT) \
do { \
    if ( ACTION_IS_SET )					            \
        {                                                                   \
        EVENT_TASKSPAWN_T evt_obj_taskspawn; \
        evt_obj_taskspawn.taskId = (TASK_ID)TID; \
        evt_obj_taskspawn.priority = PRI; \
        evt_obj_taskspawn.stackSize = STACKSIZE; \
        evt_obj_taskspawn.entryPoint = ENTRYPT; \
        evt_obj_taskspawn.options = OPT; \
        eventPointSwHandle (evtId, &evt_obj_taskspawn, sizeof evt_obj_taskspawn); \
        } \
} while ((0))

    
/*
*
* EVT_OBJ_SIG_0 - signal event logging with no parameter
*
*/

#define EVT_OBJ_SIG_0(evtId)			                            \
        EVT_OBJ_SIG_N(evtId, 0, 0, 0, 0, 0, 0)


/*
*
* EVT_OBJ_SIG_1 - signal event logging with 1 parameter
*
*/

typedef struct
    {
    _Vx_usr_arg_t args [1];
    } EVT_OBJ_SIG_1_T;

#define EVT_OBJ_SIG_1(evtId, ARG1)			            \
do { \
    if (ACTION_IS_SET) \
        { \
        EVT_OBJ_SIG_1_T evt_obj_sig_1; \
        evt_obj_sig_1.args [0] = (_Vx_usr_arg_t)ARG1; \
        eventPointSwHandle (evtId, &evt_obj_sig_1, sizeof evt_obj_sig_1);\
        } \
} while ((0))
 

/*
*
* EVT_OBJ_SIG - signal event logging
*
*/

#define EVT_OBJ_SIG(evtId, nParam, arg1, arg2) \
        EVT_OBJ_SIG_N(evtId, nParam, arg1, arg2, 0, 0, 0)


/*
*
* EVT_OBJ_SIG_2 - signal event logging
*
*/

typedef struct
    {
    _Vx_usr_arg_t args [2];
    } EVT_OBJ_SIG_2_T;

#define EVT_OBJ_SIG_2(evtId, ARG1, ARG2)			            \
do { \
    if (ACTION_IS_SET) \
        { \
        EVT_OBJ_SIG_2_T evt_obj_sig_2; \
        evt_obj_sig_2.args [0] = (_Vx_usr_arg_t)ARG1; \
        evt_obj_sig_2.args [1] = (_Vx_usr_arg_t)ARG2; \
        eventPointSwHandle (evtId, &evt_obj_sig_2, sizeof evt_obj_sig_2);\
        } \
} while ((0))
 

/*
*
* EVT_OBJ_SIG_3 - signal event logging with 3 parameters
*
*/

typedef struct
    {
    _Vx_usr_arg_t args [3];
    } EVT_OBJ_SIG_3_T;

#define EVT_OBJ_SIG_3(evtId, ARG1, ARG2, ARG3) \
do { \
    if (ACTION_IS_SET) \
        { \
        EVT_OBJ_SIG_3_T evt_obj_sig_3; \
        evt_obj_sig_3.args [0] = (_Vx_usr_arg_t)ARG1; \
        evt_obj_sig_3.args [1] = (_Vx_usr_arg_t)ARG2; \
        evt_obj_sig_3.args [2] = (_Vx_usr_arg_t)ARG3; \
        eventPointSwHandle (evtId, &evt_obj_sig_3, sizeof evt_obj_sig_3);\
        } \
} while ((0))


/*
*
* EVT_OBJ_SIG_4 - signal event logging with 4 parameters
*
*/

typedef struct
    {
    _Vx_usr_arg_t args [4];
    } EVT_OBJ_SIG_4_T;

#define EVT_OBJ_SIG_4(evtId, ARG1, ARG2, ARG3, ARG4) \
do { \
    if (ACTION_IS_SET) \
        { \
        EVT_OBJ_SIG_4_T evt_obj_sig_4; \
        evt_obj_sig_4.args [0] = (_Vx_usr_arg_t)ARG1; \
        evt_obj_sig_4.args [1] = (_Vx_usr_arg_t)ARG2; \
        evt_obj_sig_4.args [2] = (_Vx_usr_arg_t)ARG3; \
        evt_obj_sig_4.args [3] = (_Vx_usr_arg_t)ARG4; \
        eventPointSwHandle (evtId, &evt_obj_sig_4, sizeof evt_obj_sig_4);\
        } \
} while ((0))



/*
*
* EVT_OBJ_SAL_1 - SAL event logging with 1 parameter
*
*/

typedef struct
    {
    _Vx_usr_arg_t         args [1];
    } EVT_OBJ_SAL_1_T;
    
    
#define EVT_OBJ_SAL_1(evtId, ARG1)                                          \
do { \
    if (ACTION_IS_SET) \
        { \
        EVT_OBJ_SAL_1_T evt_obj_sal_1; \
        evt_obj_sal_1.args [0] = (_Vx_usr_arg_t)ARG1; \
        eventPointSwHandle (evtId, &evt_obj_sal_1, sizeof evt_obj_sal_1); \
        } \
} while ((0))


/*
*
* EVT_OBJ_SAL_2 - SAL event logging with 2 parameters
*
*/


typedef struct
    {
    _Vx_usr_arg_t         args [2];
    } EVT_OBJ_SAL_2_T;
    
#define EVT_OBJ_SAL_2(evtId, ARG1, ARG2)                                    \
do { \
    if (ACTION_IS_SET) \
        { \
        EVT_OBJ_SAL_2_T evt_obj_sal_2; \
        evt_obj_sal_2.args [0] = (_Vx_usr_arg_t)ARG1; \
        evt_obj_sal_2.args [1] = (_Vx_usr_arg_t)ARG2; \
        eventPointSwHandle (evtId, &evt_obj_sal_2, sizeof evt_obj_sal_2); \
        } \
} while ((0))



/*
*
* EVT_OBJ_SAL_3 - SAL event logging with 3 parameters
*
*/

typedef struct
    {
    _Vx_usr_arg_t         args [3];
    } EVT_OBJ_SAL_3_T;
    
#define EVT_OBJ_SAL_3(evtId, ARG1, ARG2, ARG3)                              \
do { \
    if (ACTION_IS_SET) \
        { \
        EVT_OBJ_SAL_3_T evt_obj_sal_3; \
        evt_obj_sal_3.args [0] = (_Vx_usr_arg_t)ARG1; \
        evt_obj_sal_3.args [1] = (_Vx_usr_arg_t)ARG2; \
        evt_obj_sal_3.args [2] = (_Vx_usr_arg_t)ARG3; \
        eventPointSwHandle (evtId, &evt_obj_sal_3, sizeof evt_obj_sal_3); \
        } \
} while ((0))


/*
*
* EVT_OBJ_SAL_STR_2 - SAL event logging with 2 parameters
*
*/
    
typedef struct
    {
    _Vx_usr_arg_t       args [1];
    const char *        pData;
    size_t              length;
    } EVT_OBJ_SAL_STR_2_T;


#define EVT_OBJ_SAL_STR_2(EVTID, NAME, FD) \
do { \
    if (ACTION_IS_SET) \
        { \
        EVT_OBJ_SAL_STR_2_T evt_obj_sal_str_2; \
        evt_obj_sal_str_2.args [0] = (_Vx_usr_arg_t)FD; \
        evt_obj_sal_str_2.length = strlen (name); \
        evt_obj_sal_str_2.pData = name; \
        eventPointSwHandle (EVTID, &evt_obj_sal_str_2, sizeof(evt_obj_sal_str_2)); \
        } \
} while ((0)) 



/*
*
* EVT_OBJ_EVENT - events (from eventLib) event logging
*
*/

typedef struct
    {
    _Vx_usr_arg_t     args [3];
    } EVT_OBJ_EVENT_3_T;

#define EVT_OBJ_EVENT_3(evtId, ARG1, ARG2, ARG3)	                    \
do { \
    if ( ACTION_IS_SET )					            \
        { \
        EVT_OBJ_EVENT_3_T evt_obj_event_3; \
        evt_obj_event_3.args [0] = (_Vx_usr_arg_t)ARG1; \
        evt_obj_event_3.args [1] = (_Vx_usr_arg_t)ARG2; \
        evt_obj_event_3.args [2] = (_Vx_usr_arg_t)ARG3; \
        eventPointSwHandle(evtId, &evt_obj_event_3, sizeof evt_obj_event_3); \
    } \
} while ((0))

typedef struct
    {
    _Vx_usr_arg_t         args [2];
    } EVT_OBJ_EVENT_2_T;

#define EVT_OBJ_EVENT_2(evtId, ARG1, ARG2)	                    \
do { \
    if ( ACTION_IS_SET )					            \
        { \
        EVT_OBJ_EVENT_2_T evt_obj_event_2; \
        evt_obj_event_2.args [0] = (_Vx_usr_arg_t)ARG1; \
        evt_obj_event_2.args [1] = (_Vx_usr_arg_t)ARG2; \
        eventPointSwHandle(evtId, &evt_obj_event_2, sizeof evt_obj_event_2); \
    } \
} while ((0))


/*
*
* EVT_EDR_ERR_INJECT - events (from edrLib) event logging
*
*/

#define EVT_EDR_ERR_INJECT(EVTID, KIND, FILENAME, LINE, ADDRESS, MSG)	\
do { \
    if ( ACTION_IS_SET )						\
        { \
        EVENT_EDR_ERR_INJECT_T evt_edr_err_inject; \
        evt_edr_err_inject.kind = KIND; \
        evt_edr_err_inject.filename = FILENAME; \
        evt_edr_err_inject.linenumber = LINE; \
        evt_edr_err_inject.address = ADDRESS; \
        evt_edr_err_inject.message = MSG; \
        eventPointSwHandle (EVTID, &evt_edr_err_inject, sizeof (evt_edr_err_inject)); \
        } \
} while ((0))
    

/* Generic struct for shared memory msgq events */

typedef struct
    {
    _Vx_usr_arg_t       args [5];
    int                 nParams;
    } EVT_SM_MSGQ_T;


/*
*
* EVT_OBJ_SM_MSGQ - object status event logging for SMO message queues.
*
*/

#define EVT_OBJ_SM_MSGQ(EVTID, ARG1, ARG2, ARG3, ARG4, ARG5, NPARAMS)         \
do { \
    if ( ACTION_IS_SET )					            \
        { \
        EVT_SM_MSGQ_T evt_sm_msgq; \
        evt_sm_msgq.args [0] = (_Vx_usr_arg_t)ARG1; \
        evt_sm_msgq.args [1] = (_Vx_usr_arg_t)ARG2; \
        evt_sm_msgq.args [2] = (_Vx_usr_arg_t)ARG3; \
        evt_sm_msgq.args [3] = (_Vx_usr_arg_t)ARG4; \
        evt_sm_msgq.args [4] = (_Vx_usr_arg_t)ARG5; \
        evt_sm_msgq.nParams = NPARAMS; \
        eventPointSwHandle(EVTID, &evt_sm_msgq, sizeof evt_sm_msgq); \
    } \
} while ((0))
    
/*
*
* EVT_STR_N - record an event with a timestamps, N-params and a string
*
*/


typedef struct
    {
    _Vx_usr_arg_t       args[6];
    int                 nParams;
    size_t              length;
    const char *        data;
    } EVT_STR_N_T;


#define EVT_STR_N(evtId, NPARAMS, ARG1, ARG2, ARG3, ARG4, ARG5, ARG6,   \
                  LENGTH, DATA)                                         \
do { \
     if (ACTION_IS_SET) \
        { \
        EVT_STR_N_T evt_str_n; \
        evt_str_n.args [0] = (_Vx_usr_arg_t)ARG1; \
        evt_str_n.args [1] = (_Vx_usr_arg_t)ARG2; \
        evt_str_n.args [2] = (_Vx_usr_arg_t)ARG3; \
        evt_str_n.args [3] = (_Vx_usr_arg_t)ARG4; \
        evt_str_n.args [4] = (_Vx_usr_arg_t)ARG5; \
        evt_str_n.args [5] = (_Vx_usr_arg_t)ARG6; \
        evt_str_n.nParams = NPARAMS; \
        evt_str_n.data = DATA; \
        evt_str_n.length = LENGTH; \
        eventPointSwHandle (evtId, &evt_str_n, sizeof evt_str_n); \
        } \
} while ((0))


    
/******************************************************************************
*
* EVT_NOOBJ_STR_0 - event logging with strings 
*
* This macro stores object level string information for places where the objId
* is not available.  The string must be arg1.
*
* NOMANUAL
*/

typedef struct
    {
    const void * data;
    size_t length;
    } EVT_NOOBJ_STR_0_T;

#define EVT_NOOBJ_STR_0(evtId, LENGTH, DATA) \
do { \
    if (ACTION_IS_SET) \
        { \
        EVT_NOOBJ_STR_0_T evt_noobj_str_0; \
        evt_noobj_str_0.data = DATA; \
        evt_noobj_str_0.length = LENGTH; \
        eventPointSwHandle (evtId, &evt_noobj_str_0, sizeof evt_noobj_str_0); \
        } \
} while ((0))


/* Generic struct for network events */

typedef struct
    {
    _Vx_usr_arg_t       args [5];
    int                 nParams;
    event_t             evtId;
    const char *        pData;
    size_t              length;
    } EVT_STR_NET_T;


/*
* Store a TIMER_ROLLOVER event
*/

#define EVT_TIMER_ROLLOVER(evtId) \
          EVT_CTX_0(evtId)

/*
*
* EVT_WVEVENT - context switch event logging which logs a buffer,
*
* This macro stores eventpoint and user events into the event buffer.
*
*/

#define EVT_WVEVENT(USR_EVENT, ADDR, DATA, LENGTH) \
do { \
    if (ACTION_IS_SET) \
        { \
        EVENT_WVEVENT_T   event; \
        event.userEventId = USR_EVENT; \
        event.data = DATA; \
        event.length = LENGTH; \
        event.pc = (void *) ADDR; \
        eventPointSwHandle (MIN_USER_ID, &event, sizeof (event)); \
        } \
} while ((0))


#endif	/* CPU */			/* end target-only section */

#ifdef __cplusplus
}
#endif

#endif  /* _ASMLANGUAGE */

#define WV_REV_ID_T2    0xb0b00000
#define WV_REV_ID_T3    0xcdcd0000
#define WV_REV_ID_BASE6 0xb1b10000      /* based on VxWorks 5 */

#define WV_REV_ID_VXWORKS_6_6_SMP     0xb1b20000      /* VxWorks 6, with SMP */
#define WV_REV_ID_VXWORKS_6_6         0xb1b30000      /* VxWorks 6, without SMP */
    
#define WV_REV_ID_VXWORKS_6_7_SMP     0xb1b40000      /* VxWorks 6, with SMP */
#define WV_REV_ID_VXWORKS_6_7         0xb1b50000      /* VxWorks 6, without SMP */

#define WV_REV_ID_VXWORKS_6_9  	      0xb1c00000      /* VxWorks 6.9 */
#define WV_REV_ID_SMP		      0x8000
#define WV_REV_ID_64BIT		      0x4000

#define WV_REV_ID_VXWORKS_6_9_2        0xb1c10000      /* VxWorks 6.9 */

#define WV_REV_ID_VXWORKS_7_0_0        0xb1c20000      /* VxWorks 7.0 */

#define WV_EVT_PROTO_REV_1_0_FCS 1

#define WV_EVT_PROTO_REV_2_0_FCS 2
#define WV_EVT_PROTO_REV_3_0_FCS 3
#define WV_EVT_PROTO_REV_3_1_FCS 4
#define WV_EVT_PROTO_REV_2_2_FCS 5

/* Base6 parser revisions */
    
#define WV_EVT_PROTO_REV_1_EAR   1
#define WV_EVT_PROTO_REV_6_3_FCS 2

/* Indicate new syscall group/id split */
/* 6.6 and above have extra param in taskname for affinity */
    
#define WV_EVT_PROTO_REV_6_6     3

#define WV_EVT_PROTO_REV_6_7     3
#define WV_EVT_PROTO_REV_6_9	 0

#define WV_REV_ID_CURRENT_SMP           (WV_REV_ID_VXWORKS_7_0_0 | WV_REV_ID_SMP)
#define WV_REV_ID_CURRENT               WV_REV_ID_VXWORKS_7_0_0

#define WV_EVT_PROTO_REV_CURRENT        WV_EVT_PROTO_REV_6_9



/* ranges for the different classes of events */

#define MIN_CONTROL_ID 	0
#define MAX_CONTROL_ID	49
#define MIN_CLASS1_ID	50
#define MAX_CLASS1_ID	599
#define MIN_INT_ID	102
#define PPC_WD_INT_ID	598
#define PPC_DECR_INT_ID	599
#define MAX_INT_ID	599
#define MIN_CLASS2_ID	600
#define MAX_CLASS2_ID	9999
#define MIN_CLASS3_ID	10000
#define MAX_CLASS3_ID	19999 
#define MIN_RESERVE_ID	20000

/*
 * Network event IDs can go from 20000 - 20292
 * These are present in 5.x and AE
 */
    
/*
 * Dual-stack network event IDs go from 20400 - 20475
 * though they go in steps of 15
 */
    
/* range for synthetic syscall event Ids */

#define MIN_SYSCALL_ID  21000
#define MAX_SYSCALL_ID  21999
    
#define MIN_RTI_RESERVE_ID      39000
#define MAX_RTI_RESERVE_ID      39999
#define MAX_RESERVE_ID	39999 
#define MIN_USER_ID	40000
#define MAX_USER_ID	65535

#define INT_LEVEL(eventNum) ((eventNum)-MIN_INT_ID)

#define IS_CLASS1_EVENT(event) \
    ((event >= MIN_CLASS1_ID) && (event <= MAX_CLASS1_ID))

#define IS_CLASS2_EVENT(event) \
    ((event >= MIN_CLASS2_ID) && (event <= MAX_CLASS2_ID))

#define IS_CLASS3_EVENT(event) \
    ((event >= MIN_CLASS3_ID) && (event <= MAX_CLASS3_ID))

#define IS_INT_ENT_EVENT(event) \
    ((event >= MIN_INT_ID) && (event <= MAX_INT_ID))

#define IS_CONTROL_EVENT(event) \
    ((event >= MIN_CONTROL_ID) && (event <= MAX_CONTROL_ID))

#define IS_USER_EVENT(event) \
    ((event >= MIN_USER_ID) && (event <= MAX_USER_ID))

/*
 * This test determines whether the parser should translate
 * the event into the correct syscall
 */
    
#define IS_SYSCALL_EVENT(event) \
    ((event >= EVENT_SYSCALL_0) && (event <= EVENT_SYSCALL_8))

#define CONTROL_EVENT(id) (MIN_CONTROL_ID + id)
#define CLASS1_EVENT(id)  (MIN_CLASS1_ID + id)
#define CLASS2_EVENT(id)  (MIN_CLASS2_ID + id)
#define CLASS3_EVENT(id)  (MIN_CLASS3_ID + id)
#define INT_EVENT(id)     (MIN_INT_ID + id)


/*
 * String and binary parameters are stored with a preceding length. This allows
 * variable length payload without compromising alignment. The amount of padding
 * is written into the top part of the length word, and the remainder contains
 * the length of the significant data, i.e. without padding 
 */
    
#define PADDING_SHIFT_COUNT             (29)
    

/* length of BLOB data including padding */

#define BLOB_PADDED_LENGTH(dataLength,alignment) \
    ((dataLength + (1<<alignment) - 1) & ~((1<<alignment)-1))


/* amount of padding required, after binary payload, to satisfy alignment */

#define BLOB_PADDING(dataLength,alignment) \
    (BLOB_PADDED_LENGTH(dataLength,alignment) - dataLength)


#define BLOB_LENGTH_WORD(dataLength,alignment) \
    (dataLength | (BLOB_PADDING(dataLength,alignment) << PADDING_SHIFT_COUNT))



#ifdef CPU   /* This is for target side build only */

#ifndef _BYTE_ORDER
#error _BYTE_ORDER must be defined
#endif /* _BYTE_ORDER */

#ifndef _BIG_ENDIAN
#error _BIG_ENDIAN must be defined
#endif /* _BIG_ENDIAN */

/*
 * Alignment macros used to store unaligned short (16 bits) and unaligned
 * int (32 bits).
 */

/*
 * If _WRS_BLIB_ALIGNMENT is defined as 1, arch can do non-aligned word writes,
 * otherwise we need to handle it ourselves.
 */
      
#if defined (_WRS_BLIB_ALIGNMENT)
    #if (_WRS_BLIB_ALIGNMENT == 1 || _WRS_BLIB_ALIGNMENT == 0)
        #define WV_UNALIGNED_SUPPORT
    #endif
#endif      /* defined (_WRS_BLIB_ALIGNMENT) */

#define EVT_STORE_UINT16(pBuf, event_id) \
    *pBuf++ = (event_id)

#if (_BYTE_ORDER==_BIG_ENDIAN)

#   if defined  WV_UNALIGNED_SUPPORT
    	/* unaligned access supported */
#   	define EVT_STORE(pBuf, value)                    \
    		*pBuf++ = (value);
#   else
	/* unaligned access not supported */
#ifndef _WRS_CONFIG_LP64
#	define EVT_STORE(pBuf, value)                    	\
    		do { *((short *) pBuf) = (value) >> 16;         \
	 	     *(((short *) pBuf) + 1) = (value);         \
	 	     pBuf++; } while ((0))
#else /* _WRS_CONFIG_LP64  */
#define EVT_STORE(pBuf, value) \
        EVT_STORE_S(pBuf, (long)(value), sizeof(value))

#       define EVT_STORE_S(pBuf, value, vsize)                	    \
    	do {                                           		    \
             if(vsize==4) {                              	    \
		 *((short *) pBuf) = (short)(value >> 16); 	    \
		 *(((short *) pBuf) + 1) = (short)value; 	    \
             } else {                                      	    \
	         *((short *) pBuf) = (short)(value >> 48);          \
	 	 *(((short *) pBuf) + 1) = (short)(value >> 32);    \
	 	 *(((short *) pBuf) + 2) = (short)(value >> 16);    \
	 	 *(((short *) pBuf) + 3) = (short)value;            \
	     }                                              	    \
 	     pBuf++;						    \
        } while ((0))
#    endif /* _WRS_CONFIG_LP64 */
#endif /* WV_UNALIGNED_SUPPORT */

#else	/* (_BYTE_ORDER==_BIG_ENDIAN) */

#   if defined  WV_UNALIGNED_SUPPORT
    	/* unaligned access supported */
#   	define EVT_STORE(pBuf, value)                    \
    		*pBuf++ = (value)
#   else
	/* unaligned access not supported */
#ifndef _WRS_CONFIG_LP64
#       define EVT_STORE(pBuf, value)                    \
    		do { *((short *) pBuf) = (value);               \
	 	     *(((short *) pBuf) + 1) = (value) >> 16;   \
	 	     pBuf++; } while ((0))
#else /* #ifndef _WRS_CONFIG_LP64  */
#define EVT_STORE(pBuf, value) \
        EVT_STORE_S(pBuf, (long)(value), sizeof(value))

#define EVT_STORE_S(pBuf, value, vsize)                    	        \
    	do {                                           		        \
            if(vsize==4) {                     	                        \
                *((short *) pBuf) = (short)value; 	                \
	        *(((short *) pBuf) + 1) = (short)(value >> 16);         \
            } else {                                      	        \
	        *((short *) pBuf) = (short)(value);                     \
	 	*(((short *) pBuf) + 1) = (short)(value >> 16);         \
	 	*(((short *) pBuf) + 2) = (short)(value >> 32);         \
	 	*(((short *) pBuf) + 3) = (short)(value >> 48);         \
	    }                                                           \
            pBuf++;                                                     \
        } while ((0))

#endif /* _WRS_CONFIG_LP64 */

#endif	/* (_BYTE_ORDER==_BIG_ENDIAN) */

#endif

#endif /* CPU */

#endif /* __INCeventph*/
