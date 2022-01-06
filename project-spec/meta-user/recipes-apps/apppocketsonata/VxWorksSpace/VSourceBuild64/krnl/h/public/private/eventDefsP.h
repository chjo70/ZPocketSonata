/* eventdefsP.h - definitions of eventpoint ids and structures */

/*
 * Copyright (c) 2008, 2010-2011, 2013 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01o,25sep13,h_k  renamed taskIdCurrent to taskCurrentId to prevent from
                 conflicting with the macro defined in taskLib.h in SMP.
01n,21aug13,rfr  Added condition variable events
01m,03jun13,wzc  Added stacktrace for system viewer.
01l,28jan13,wzc  WIND00399400 - Fix EVENT_RTP_LOAD_T.
01k,29aug11,wzc  Update to support dynamic power management (WIND00295115)
01j,27jul11,wzc  Support dynamic power management (WIND00214625)
01i,13may10,tcr  Improve lock level tracking for SV (WIND00209730)
01h,10feb10,tcr  update for 64bit
01g,30sep08,tcr  add event for dynamic printf
01f,28aug08,tcr  add missing typedef
01e,25jul08,tcr  add objId to SYSCALL_RETURN_OK and SYSCALL_RETURN_ERROR
                 make them available from asm
01d,02jul08,tcr  update structure layouts
01c,22may08,tcr  add EVENT_CTX_NODISP_T and EVENT_CTX_NODISP_PI_T
01b,09may08,tcr  fix syscall instrumentation
01a,13mar08,tcr  created
*/

/*
DESCRIPTION
This file describes the structures associated with each eventpoint
definition. These structures are the data passed from an eventpoint to the
dataCollector.

Given the name of an eventId, the type passed to the dataCollector would be the
name, with an _T suffix.

So a dataCollector which has registered to receive EVENT_INT_ENTER events, would
be passed an EVENT_INT_ENTER_T *. 

*/

#ifndef __eventdefsPh
#define __eventdefsPh

#ifdef __cplusplus
extern "C" {
#endif


/* EVENT Ids */

/*
* These need event ids defined here because they are used from assembler. The
* structures (if any) are described below.
*/
    
/* Interrupt events */

#define EVENT_INT_ENT(k) 		((k) + MIN_INT_ID)

#define EVENT_INT_ENTER                 EVENT_INT_ENT(0)

#define EVENT_INT_EXIT 	 		(MIN_INT_ID - 1)

#define EVENT_INT_EXIT_K                (MIN_INT_ID - 2)

/* scheduler events */
    
#define EVENT_WIND_EXIT_DISPATCH        	CLASS1_EVENT(2)

#define EVENT_WIND_EXIT_DISPATCH_PI        	CLASS1_EVENT(4)

#define EVENT_WIND_EXIT_NODISPATCH        	CLASS1_EVENT(3)

#define EVENT_WIND_EXIT_NODISPATCH_PI        	CLASS1_EVENT(5)


/* syscall events */

#define EVENT_SYSCALL_BASE                      CLASS3_EVENT(65)

#define EVENT_SYSCALL_ENTER                     EVENT_SYSCALL_BASE

#define EVENT_SYSCALL_RETURN_OK                 CLASS3_EVENT(74)

#define EVENT_SYSCALL_RETURN_ERR                CLASS3_EVENT(75)

#define EVENT_SYSCALL_BAD_ID                    CLASS3_EVENT(76)

/* power management event */
/* Set power consume state */
#define   EVENT_POWER_CSTATE_SET      CLASS3_EVENT(248)

#ifndef _ASMLANGUAGE

typedef unsigned short event_t;

/* EVENT_INT_ENTER */

typedef struct event_int_enter
    {
    long	interruptId;
    } EVENT_INT_ENTER_T;
    


/*
 * EVENT_BEGIN
 * There is no eventpoint associated with this event
 */
    
#define EVENT_BEGIN                     CONTROL_EVENT(0)


/* EVENT_TIMER_ROLLOVER */
    
#define EVENT_TIMER_ROLLOVER            CONTROL_EVENT(2)

/* No structure */
    

/* EVENT_TASKNAME */
    
#define	EVENT_TASKNAME			CONTROL_EVENT(3)
    
typedef struct event_taskname
    {
    long	state;
    long	priority;
    long	lockCnt;
    TASK_ID     tid;
    void *      entryPt;
    RTP_ID      rtp;
    long	affinity;
    char *      name;
    } EVENT_TASKNAME_T;


/*
 * EVENT_CONFIG
 * There is no eventpoint associated with this event
 */

#define EVENT_CONFIG              	CONTROL_EVENT(4)

 
/*
 * EVENT_LOGCOMMENT
 * There is no eventpoint associated with this event
 */

#define EVENT_LOGCOMMENT                CONTROL_EVENT(7)


/*
 * EVENT_TIMESTAMP_CONFIG
 * There is no eventpoint associated with this event
 */

#define EVENT_TIMESTAMP_CONFIG          CONTROL_EVENT(8)

    
/*
 * EVENT_ISR_INFO
 * There is no eventpoint associated with this event
 */
    
#define EVENT_ISR_INFO                  CONTROL_EVENT(9)

typedef struct event_isr_info
    {
    ISR_ID      isrId;
    void *      handler;
    const char *name;
    } EVENT_ISR_INFO_T;


/*
 * EVENT_RTPNAME
 */
    
#define	EVENT_RTPNAME			CONTROL_EVENT(16)

typedef struct event_rtpname
    {
    long	options;
    OBJ_ID      ownerId;
    RTP_ID      rtpId;
    const char *pRtpName;
    } EVENT_RTPNAME_T;
    

/*
 * EVENT_CPU_ID
 * There is no eventpoint associated with this event
 */
    
#define	EVENT_CPU_ID			CONTROL_EVENT(10)


/*
 * EVENT_NUM_CPU
 * There is no eventpoint associated with this event
 */
    
#define	EVENT_NUM_CPU			CONTROL_EVENT(17)
    
       
/*
 * EVENT_OS_REVISION
 * There is no eventpoint associated with this event
 */
    
#define	EVENT_OS_REVISION                CONTROL_EVENT(18)
    
    
/*
 * EVENT_IDLE_TASK_ID
 * There is no eventpoint associated with this event
 */
    
#define EVENT_IDLE_TASK_ID              CONTROL_EVENT(19)

/*
 * EVENT_MODULE_MAP
 */

#define EVENT_MODULE_MAP              CONTROL_EVENT(20)

typedef struct event_module_map
    {
    RTP_ID      rtpId;
    void *      startAddr;
    size_t      textSize; 
    unsigned long fileTextOffset;
    const char * fileName;
    } EVENT_MODULE_MAP_T;

/*
 * EVENT_ANY_EVENT
 * There is no eventpoint associated with this event. This is added for
 * triggering, when no particular event is required 
 */
    
#define EVENT_ANY_EVENT			CONTROL_EVENT(48)

/* No structure */



/* CLASS3 events */

/* EVENT_TASKSPAWN */
   
#define	EVENT_TASKSPAWN		        CLASS3_EVENT(0)

typedef struct event_taskspawn
    {
    TASK_ID     taskId;
    long	priority;
    size_t      stackSize;
    void *	entryPoint;
    long	options;
    } EVENT_TASKSPAWN_T;
    

/* EVENT_TASKDESTROY */

#define	EVENT_TASKDESTROY		CLASS3_EVENT(1)

typedef struct event_taskdestroy
    {
    TASK_ID     pTcb;
    long	safeCnt;
    } EVENT_TASKDESTROY_T;

    
/* EVENT_TASKDELAY */

#define	EVENT_TASKDELAY			CLASS3_EVENT(2)

typedef struct event_taskdelay
    {
    long	ticks;
    } EVENT_TASKDELAY_T;


/* EVENT_TASKPRIORITYSET */
    
#define	EVENT_TASKPRIORITYSET	        CLASS3_EVENT(3)

typedef struct event_taskpriorityset
    {
    TASK_ID     pTcb;
    long        newPri;
    long        oldPri;
    } EVENT_TASKPRIORITYSET_T;
    

/* EVENT_TASKSUSPEND */

#define	EVENT_TASKSUSPEND			CLASS3_EVENT(4)

typedef struct event_tasksuspend
    {
    TASK_ID     pTcb;
    } EVENT_TASKSUSPEND_T;
    

/* EVENT_TASKRESUME */

#define	EVENT_TASKRESUME			CLASS3_EVENT(5)

typedef struct event_taskresume
    {
    TASK_ID	tid;
    long	priority;
    } EVENT_TASKRESUME_T;
    

/* EVENT_TASKSAFE */

#define	EVENT_TASKSAFE				CLASS3_EVENT(6)

typedef struct event_tasksafe
    {
    TASK_ID   	taskCurrentId;
    long	safeCnt;
    } EVENT_TASKSAFE_T;
    

/* EVENT_TASKUNSAFE */

#define	EVENT_TASKUNSAFE			CLASS3_EVENT(7)

typedef struct event_taskunsafe
    {
    TASK_ID   	taskCurrentId;
    long	safeCnt;
    } EVENT_TASKUNSAFE_T;
    

/* EVENT_SEMBCREATE */

#define	EVENT_SEMBCREATE			CLASS3_EVENT(8)

typedef struct event_sembcreate
    {
    SEM_ID       semId;
    long         options;
    TASK_ID      owner;
    } EVENT_SEMBCREATE_T;
    

/* EVENT_SEMCCREATE */

#define	EVENT_SEMCCREATE			CLASS3_EVENT(9)

typedef struct event_semccreate
    {
    SEM_ID      semId;
    long	options;
    long	initialCount;
    } EVENT_SEMCCREATE_T;
    

/* EVENT_SEMDELETE */

#define	EVENT_SEMDELETE				CLASS3_EVENT(10)

typedef struct event_semdelete
    {
    SEM_ID      semId;
    TASK_ID     owner;
    long	recurse;
    TASK_ID     qHead;
    } EVENT_SEMDELETE_T;
    

/* EVENT_SEMFLUSH */

#define	EVENT_SEMFLUSH				CLASS3_EVENT(11)

typedef struct event_semflush
    {
    SEM_ID      semId;
    TASK_ID     owner;
    long	recurse;
    TASK_ID     qHead;
    } EVENT_SEMFLUSH_T;
    

/* EVENT_SEMGIVE */

#define	EVENT_SEMGIVE				CLASS3_EVENT(12)

typedef struct event_semgive
    {
    SEM_ID      semId;
    TASK_ID     owner;
    long	recurse;
    } EVENT_SEMGIVE_T;
    

/* EVENT_SEMMCREATE */

#define	EVENT_SEMMCREATE			CLASS3_EVENT(13)

typedef struct event_semmcreate
    {
    SEM_ID      semId;
    long	options;
    TASK_ID     owner;
    } EVENT_SEMMCREATE_T;


/* EVENT_SEMMGIVEFORCE */

#define	EVENT_SEMMGIVEFORCE			CLASS3_EVENT(14)

typedef struct event_semmgiveforce
    {
    SEM_ID      semId;
    long	options;
    TASK_ID     owner;
    } EVENT_SEMMGIVEFORCE_T;


/* EVENT_SEMTAKE */

#define	EVENT_SEMTAKE				CLASS3_EVENT(15)

typedef struct event_semtake
    {
    SEM_ID      semId;
    TASK_ID     owner;
    long        recurse;
    } EVENT_SEMTAKE_T;


/* EVENT_WDCREATE */

#define	EVENT_WDCREATE				CLASS3_EVENT(16)

typedef struct event_wdcreate
    {
    WDOG_ID     wdId;
    } EVENT_WDCREATE_T;
    

/* EVENT_WDDELETE */

#define	EVENT_WDDELETE				CLASS3_EVENT(17)

typedef struct event_wddelete
    {
    WDOG_ID     wdId;
    } EVENT_WDDELETE_T;
    

/* EVENT_WDSTART */

#define	EVENT_WDSTART				CLASS3_EVENT(18)

typedef struct event_wdstart
    {
    WDOG_ID     wdId;
    long        delay;
    } EVENT_WDSTART_T;
    

/* EVENT_WDCANCEL */

#define	EVENT_WDCANCEL				CLASS3_EVENT(19)

typedef struct event_wdcancel
    {
    WDOG_ID     wdId;
    } EVENT_WDCANCEL_T;
    

/* EVENT_MSGQCREATE */

#define	EVENT_MSGQCREATE			CLASS3_EVENT(20)

typedef struct event_msgqcreate
    {
    MSG_Q_ID    msgQId;
    long        maxMsgs;
    long        maxMsgLength;
    long        options;
    } EVENT_MSGQCREATE_T;
    

/* EVENT_MSGQDELETE */

#define	EVENT_MSGQDELETE			CLASS3_EVENT(21)

typedef struct event_msgqdelete
    {
    MSG_Q_ID    msgQId;
    } EVENT_MSGQDELETE_T;
    

/* EVENT_MSGQRECEIVE */

#define	EVENT_MSGQRECEIVE			CLASS3_EVENT(22)

typedef struct event_msgqreceive
    {
    MSG_Q_ID            msgQId;
    char *              buffer;
    long	        maxNBytes;
    long                timeout;
    } EVENT_MSGQRECEIVE_T;
    

/* EVENT_MSGQSEND */

#define	EVENT_MSGQSEND				CLASS3_EVENT(23)

typedef struct event_msgqsend
    {
    MSG_Q_ID            msgQId;
    char *              buffer;
    long                nBytes;
    long                timeout;
    long                priority;
    } EVENT_MSGQSEND_T;
    

/* EVENT_SIGNAL */

#define	EVENT_SIGNAL				CLASS3_EVENT(24)

typedef struct event_signal
    {
    void *              handler;
    long                signo;
    } EVENT_SIGNAL_T;
    

/* EVENT_SIGSUSPEND */

#define	EVENT_SIGSUSPEND			CLASS3_EVENT(25)

typedef struct event_sigsuspend
    {
    long                sigset;
    } EVENT_SIGSUSPEND_T;
    

/* EVENT_PAUSE */

#define	EVENT_PAUSE				CLASS3_EVENT(26)

typedef struct event_pause
    {
    TASK_ID      pTcb;
    } EVENT_PAUSE_T;


/* EVENT_KILL */

#define	EVENT_KILL				CLASS3_EVENT(27)

typedef struct event_kill
    {
    long                        signo;
    TASK_ID      pTcb;
    } EVENT_KILL_T;


/* EVENT_SAFE_PEND */

#define EVENT_SAFE_PEND                         CLASS3_EVENT(28)

typedef struct event_safe_pend
    {
    TASK_ID      pTcb;
    } EVENT_SAFE_PEND_T;


/* EVENT_SIGWRAPPER */

#define EVENT_SIGWRAPPER                        CLASS3_EVENT(29)

typedef struct event_sigwrapper
    {
    long         signo;
    TASK_ID      pTcb;
    } EVENT_SIGWRAPPER_T;


/* EVENT_MEMALLOC */

#define EVENT_MEMALLOC                          CLASS3_EVENT(30)

typedef struct event_memalloc
    {
    PART_ID             partId;
    void *              pBlock;
    unsigned long       nBytesPlusHeaderAlign;
    unsigned long       nBytes;
    } EVENT_MEMALLOC_T;
    

/* EVENT_MEMFREE */

#define EVENT_MEMFREE                           CLASS3_EVENT(31)

typedef struct event_memfree
    {
    PART_ID                     partId;
    void *                      pBlock;
    unsigned long               nBytesPlusHeaderAlign;
    } EVENT_MEMFREE_T;
    

/* EVENT_MEMPARTCREATE */

#define EVENT_MEMPARTCREATE                     CLASS3_EVENT(32)

typedef struct event_mempartcreate
    {
    PART_ID                     partId;
    unsigned long               poolSize;
    } EVENT_MEMPARTCREATE_T;
    

/* EVENT_MEMREALLOC */

#define EVENT_MEMREALLOC                        CLASS3_EVENT(33)

typedef struct event_memrealloc
    {
    PART_ID                     partId;
    void *                      pNewBlock;
    long                        nBytesPlusHeaderAlign;
    void *                      pBlock;
    size_t                      nBytes;
    } EVENT_MEMREALLOC_T;
    

/* EVENT_MEMADDTOPOOL */

#define EVENT_MEMADDTOPOOL                      CLASS3_EVENT(34)

typedef struct event_memaddtopool
    {
    PART_ID	              	partId;
    size_t      	      	poolSize;
    } EVENT_MEMADDTOPOOL_T;
    

/* EVENT_MSGCCREATE */

#define EVENT_MSGCCREATE                        CLASS3_EVENT(35)
    /* Param:
     */

/* EVENT_MSGCSEND */

#define EVENT_MSGCSEND                          CLASS3_EVENT(36)
    /* Param:
     */

/* EVENT_MSGCREPLYGET */

#define EVENT_MSGCREPLYGET                      CLASS3_EVENT(37)
    /* Param:
     */

/* EVENT_MSGCDELETE */

#define EVENT_MSGCDELETE                        CLASS3_EVENT(38)
    /* Param:
     */

/* EVENT_MSGSCREATE */

#define EVENT_MSGSCREATE                        CLASS3_EVENT(39)
    /* Param:
     */

/* EVENT_MSGSREPLY */

#define EVENT_MSGSREPLY                         CLASS3_EVENT(40)
    /* Param:
     */

/* EVENT_MSGSRECEIVE */

#define EVENT_MSGSRECEIVE                       CLASS3_EVENT(41)
    /* Param:
     */

/* EVENT_MSGSDELETE */

#define EVENT_MSGSDELETE                        CLASS3_EVENT(42)
    /* Param:
     */

/* EVENT_TASKSTOP */

#define	EVENT_TASKSTOP				CLASS3_EVENT(43)

typedef struct event_taskstop
    {
    TASK_ID     taskId;
    } EVENT_TASKSTOP_T;
    

/* EVENT_CONT */

#define	EVENT_TASKCONT				CLASS3_EVENT(44)

typedef struct event_taskcont
    {
    TASK_ID     taskId;
    long	priority;
    } EVENT_TASKCONT_T;
    

/* EVENT_IOOPEN */

#define EVENT_IOOPEN				CLASS3_EVENT(48)

typedef struct event_ioopen
    {
    long                fd;
    long		flags;
    size_t		nameLength;
    const char *        pFileName;
    } EVENT_IOOPEN_T;
    
 
/* EVENT_IOREAD */

#define EVENT_IOREAD				CLASS3_EVENT(49)

typedef struct event_ioread
    {
    long                fd;
    size_t              bytesRead;
    const char *        buffer;
    size_t              strLen;
    const char *        strData;
    } EVENT_IOREAD_T;
    
 
/* EVENT_IOWRITE */

   
#define EVENT_IOWRITE				CLASS3_EVENT(50)

typedef struct event_iowrite
    {
    long                fd;
    size_t              nBytes;
    const char *        buffer;
    size_t              strLen;
    const char *        strData;
    } EVENT_IOWRITE_T;

 
/* EVENT_IOIOCTL */

#define EVENT_IOIOCTL				CLASS3_EVENT(51)

typedef struct event_ioioctl
    {
    long                arg;
    long                cmd;
    long                fd;
    } EVENT_IOIOCTL_T;
    
 
/* EVENT_IOCLOSE */
    
#define EVENT_IOCLOSE				CLASS3_EVENT(52)

typedef struct event_ioclose
    {
    long                fd;
    } EVENT_IOCLOSE_T;

 
/* EVENT_IOCREAT */
    
#define EVENT_IOCREAT				CLASS3_EVENT(53)

typedef struct event_iocreat
    {
    long                fd;
    long                flags;
    size_t              nameLength;
    const char *        pFileName;
    } EVENT_IOCREAT_T;


/* EVENT_IODELETE */
    
#define EVENT_IODELETE				CLASS3_EVENT(54)

typedef struct event_iodelete
    {
    size_t              nameLength;
    const char *        pFileName;
    } EVENT_IODELETE_T;

    
/* EVENT_EVENTSEND */
    
#define EVENT_EVENTSEND				CLASS3_EVENT(57)

typedef struct event_eventsend
    {
    TASK_ID     taskId;
    long	events;
    } EVENT_EVENTSEND_T;


/* EVENT_EVENTRECEIVE */
    
#define EVENT_EVENTRECEIVE			CLASS3_EVENT(58)

typedef struct event_eventreceive
    {
    long	events;
    long	timeout;
    long	options;
    } EVENT_EVENTRECEIVE_T;


/* EVENT_OWNERSET */
    
#define EVENT_OWNERSET				CLASS3_EVENT(59)

typedef struct event_ownerset
    {
    OBJ_ID      objId;
    OBJ_ID      objOwnerId;
    } EVENT_OWNERSET_T;


/* EVENT_ISR_DISPATCHER_INVOKE */
    
#define EVENT_ISR_DISPATCHER_INVOKE             CLASS3_EVENT(60)

typedef struct event_isr_dispatcher_invoke
    {
    ISR_ID      isrId;
    } EVENT_ISR_DISPATCHER_INVOKE_T;
    

/* EVENT_ISR_DISPATCHER_DONE */
    
#define EVENT_ISR_DISPATCHER_DONE               CLASS3_EVENT(61)

typedef struct event_isr_dispatcher_done
    {
    ISR_ID      isrId;
    } EVENT_ISR_DISPATCHER_DONE_T;


/* EVENT_ISR_CREATE */
    
#define EVENT_ISR_CREATE                        CLASS3_EVENT(62)

typedef struct event_isr_create
    {
    ISR_ID              isrId;
    long                isrTag;
    FUNCPTR             handlerRtn;
    long                parameter;
    long                options;
    } EVENT_ISR_CREATE_T;

    
/* EVENT_ISR_DESTROY */
    
#define EVENT_ISR_DESTROY                       CLASS3_EVENT(64)

typedef struct event_isr_destroy
    {
    ISR_ID              isrId;
    } EVENT_ISR_DESTROY_T;


/* EVENT_SYSCALL_ENTER */
      
typedef struct event_syscall_enter
    {
    RTP_ID                              rtpId;
    int                                 nParams;
    const struct syscall_entry_state *  pState;
    } EVENT_SYSCALL_ENTER_T;


/* These do not have eventpoints, but are synthesized by the collector */

#define EVENT_SYSCALL_0                         CLASS3_EVENT(65)    
#define EVENT_SYSCALL_1                         CLASS3_EVENT(66)
#define EVENT_SYSCALL_2                         CLASS3_EVENT(67)
#define EVENT_SYSCALL_3                         CLASS3_EVENT(68)
#define EVENT_SYSCALL_4                         CLASS3_EVENT(69)
#define EVENT_SYSCALL_5                         CLASS3_EVENT(70)
#define EVENT_SYSCALL_6                         CLASS3_EVENT(71)
#define EVENT_SYSCALL_7                         CLASS3_EVENT(72)
#define EVENT_SYSCALL_8                         CLASS3_EVENT(73)
    


/* EVENT_SYSCALL_RETURN_OK */

typedef struct event_syscall_return_ok
    {
    RTP_ID      rtpId;
    long        result;
    } EVENT_SYSCALL_RETURN_OK_T;


/* EVENT_SYSCALL_RETURN_ERR */

typedef struct event_syscall_return_err
    {
    RTP_ID      rtpId;
    long        errnoResult;
    } EVENT_SYSCALL_RETURN_ERR_T;


/* EVENT_SYSCALL_BAD_ID */

typedef struct event_syscall_bad_id
    {
    RTP_ID      rtpId;
    long        group;
    long        routine;
    } EVENT_SYSCALL_BAD_ID_T;

    
/* EVENT_OBJ_VERIFY_FAIL */

#define EVENT_OBJ_VERIFY_FAIL                   CLASS3_EVENT(77)

typedef struct event_obj_verify_fail
    {
    OBJ_ID      objId;
    CLASS_ID    classId;
    } EVENT_OBJ_VERIFY_FAIL_T;


/* EVENT_RTP_SPAWN */

#define EVENT_RTP_SPAWN                         CLASS3_EVENT(78)

typedef struct event_rtp_spawn
    {
    RTP_ID      rtpId;
    long        priority;
    size_t      stacksize;
    long        options;
    } EVENT_RTP_SPAWN_T;


/* EVENT_RTP_DELETE */

#define EVENT_RTP_DELETE                        CLASS3_EVENT(79)

typedef struct event_rtp_delete
    {
    RTP_ID      rtpId;    
    } EVENT_RTP_DELETE_T;


/* EVENT_RTP_INIT_TASK */

#define EVENT_RTP_INIT_TASK                     CLASS3_EVENT(80)

typedef struct event_rtp_init_task
    {
    const char *        pInitialStack;
    const char *        pEnv;
    const char *        pArgv;
    long                numArgs;
    RTP_ID              rtpId;
    } EVENT_RTP_INIT_TASK_T;


/* EVENT_RTP_LOAD */

#define EVENT_RTP_LOAD                          CLASS3_EVENT(81)

typedef struct event_rtp_load
    {
    size_t              dataSize;
    const char *        pDataStart;
    size_t              textSize;
    const char *        pTextStart;
    void *              entrAddr;
    RTP_ID              rtpId;    
    } EVENT_RTP_LOAD_T;


/* EVENT_EDR_ERR_INJECT */
    
#define EVENT_EDR_ERROR_INJECT                  CLASS3_EVENT(82)

typedef struct event_edr_err_inject
    {
    int                 kind;
    const char *        filename;
    int                 linenumber;
    void *              address;
    const char *        message;
    } EVENT_EDR_ERR_INJECT_T;


/* EVENT_RTPKILL */

#define EVENT_RTPKILL                           CLASS3_EVENT(83)

typedef struct event_rtpkill
    {
    long                signo;
    RTP_ID              rtpId;
    } EVENT_RTPKILL_T;
   

/* EVENT_RTPSIGNAL */

#define EVENT_RTPSIGNAL                         CLASS3_EVENT(84)

typedef struct event_rtpsignal
    {
    const struct sigaction *    pAct;
    long                        signo;
    RTP_ID                      rtpId;
    } EVENT_RTPSIGNAL_T;


/* EVENT_RTPSUSPEND */

#define EVENT_RTPSUSPEND                        CLASS3_EVENT(85)

typedef struct event_rtpsuspend
    {
    long        sigset;
    } EVENT_RTPSUSPEND_T;


/* EVENT_RTPPAUSE */

#define EVENT_RTPPAUSE                          CLASS3_EVENT(86)

typedef struct event_rtppause
    {
    RTP_ID      rtpId;
    } EVENT_RTPPAUSE_T;


/* EVENT_RTPTASKKILL */

#define EVENT_RTPTASKKILL                       CLASS3_EVENT(87)

typedef struct event_rtptaskkill
    {
    long        signo;
    TASK_ID     taskId;
    } EVENT_RTPTASKKILL_T;


/* EVENT_RTPSIGQUEUE */

#define EVENT_RTPSIGQUEUE                       CLASS3_EVENT(88)

typedef struct event_rtpsigqueue
    {
    long        sival;
    long        signo;
    RTP_ID      rtpId;
    } EVENT_RTPSIGQUEUE_T;


/* EVENT_RTPTASKSIGQUEUE */

#define EVENT_RTPTASKSIGQUEUE                   CLASS3_EVENT(89)

typedef struct event_rtptasksigqueue
    {
    long        sival;
    long        signo;
    TASK_ID     taskId;
    } EVENT_RTPTASKSIGQUEUE_T; 


/* EVENT_RTPCHILDWAIT */

#define EVENT_RTPCHILDWAIT                      CLASS3_EVENT(90)

typedef struct event_rtpchildwait
    {
    RTP_ID      childRtpId;
    long        options;
    } EVENT_RTPCHILDWAIT_T;


/* EVENT_RTPSIGTIMEDWAIT */

#define EVENT_RTPSIGTIMEDWAIT                   CLASS3_EVENT(91)

typedef struct event_rtpsigtimedwait
    {
    long        pInfo;
    long        pSet;
    RTP_ID      childRtpId;
    } EVENT_RTPSIGTIMEDWAIT_T;


/* EVENT_RTPSIGWRAPPER */

#define EVENT_RTPSIGWRAPPER                     CLASS3_EVENT(92)

typedef struct event_rtpsigwrapper
    {
    long        type;
    RTP_ID      rtpId;
    } EVENT_RTPSIGWRAPPER_T;


/* EVENT_RTPSIGWRAPPER_DONE */

#define EVENT_RTPSIGWRAPPER_DONE                CLASS3_EVENT(93)

typedef struct event_rtpsigwrapper_done
    {
    RTP_ID      rtpId;
    } EVENT_RTPSIGWRAPPER_DONE_T;


/* EVENT_RTPSIGPROCMASK */

#define EVENT_RTPSIGPROCMASK                    CLASS3_EVENT(94)

typedef struct event_rtpsigprocmask
    {
    long        pOset;
    long        pSet;
    long        how;
    RTP_ID      rtpId;
    } EVENT_RTPSIGPROCMASK_T;


/* EVENT_RTPSIGPENDING */

#define EVENT_RTPSIGPENDING                     CLASS3_EVENT(95)

typedef struct event_rtpsigpending
    {
    long        pSet;
    RTP_ID      rtpId;
    } EVENT_RTPSIGPENDING_T;


/* EVENT_SALOPEN */

#define EVENT_SALOPEN                           CLASS3_EVENT(96)

typedef struct event_salopen
    {
    long                sockFd;
    const char *        name;
    } EVENT_SALOPEN_T;


/* EVENT_SALCALL_SENDREQ */
    
#define EVENT_SALCALL_SENDREQ                   CLASS3_EVENT(97)
    
typedef struct event_salcall_sendreq
    {
    long                sendLen;
    const void *        pSendBuf;
    long                sockFd;
    } EVENT_SALCALL_SENDREQ_T;


/* EVENT_SALCALL_REPLY */

#define EVENT_SALCALL_REPLY                     CLASS3_EVENT(98)

typedef struct event_salcall_reply
    {
    long                replySize;
    const void *        pRecvBuf;
    long                sockFd;
    } EVENT_SALCALL_REPLY_T;


/* EVENT_SALCREATE */
    
#define EVENT_SALCREATE                         CLASS3_EVENT(99)

typedef struct event_salcreate
    {
    long                serverId;
    const char *        name;
    } EVENT_SALCREATE_T;


/* EVENT_SALDELETE */

#define EVENT_SALDELETE                         CLASS3_EVENT(100)

typedef struct event_saldelete
    {
    long                serverId;
    } EVENT_SALDELETE_T;


/* EVENT_SALRUN_WAIT */

#define EVENT_SALRUN_WAIT                       CLASS3_EVENT(101)

typedef struct event_salrun_wait
    {
    long                serverId;
    } EVENT_SALRUN_WAIT_T;


/* EVENT_SALRUN_READREQ */

#define EVENT_SALRUN_READREQ                    CLASS3_EVENT(102)

typedef struct event_salrun_readreq
    {
    long        currFd;
    long        serverId;
    } EVENT_SALRUN_READREQ_T;


/* EVENT_SALRUN_SOCKCLOSE */

#define EVENT_SALRUN_SOCKCLOSE                  CLASS3_EVENT(103)

typedef struct event_salrun_sockclose
    {
    long        currFd;
    long        serverId;
    } EVENT_SALRUN_SOCKCLOSE_T;


/* EVENT_SALRUN_SOCKIGNORE */

#define EVENT_SALRUN_SOCKIGNORE                 CLASS3_EVENT(104)

typedef struct event_salrun_sockignore
    {
    long        currFd;
    long        serverId;
    } EVENT_SALRUN_SOCKIGNORE_T;


/* EVENT_SALRUN_ACCEPT */

#define EVENT_SALRUN_ACCEPT                     CLASS3_EVENT(105)

typedef struct event_salrun_accept
    {
    long        currFd;
    long        serverId;
    } EVENT_SALRUN_ACCEPT_T;


/* EVENT_SALRUN_CONNECT */

#define EVENT_SALRUN_CONNECT                    CLASS3_EVENT(106)

typedef struct event_salrun_connect
    {
    long        currFd;
    long        serverId;
    } EVENT_SALRUN_CONNECT_T;


/* EVENT_SALRUN_TERMINATE */

#define EVENT_SALRUN_TERMINATE                  CLASS3_EVENT(107)

typedef struct event_salrun_terminate
    {
    long        serverId;
    } EVENT_SALRUN_TERMINATE_T;


/* EVENT_TASKROTATE */

#define	EVENT_TASKROTATE			CLASS3_EVENT(108)

typedef struct event_taskrotate
    {
    long        priority;
    } EVENT_TASKROTATE_T;

/* EVENT_CONDVAR_CREATE */

#define EVENT_CONDVAR_CREATE			CLASS3_EVENT(109)

typedef struct event_condvar_create
    {
    CONDVAR_ID	condVar;
    int		options;
    } EVENT_CONDVAR_CREATE_T;

/* EVENT_CONDVAR_WAIT */

#define EVENT_CONDVAR_WAIT			CLASS3_EVENT(110)

typedef struct event_condvar_wait
    {
    CONDVAR_ID	condVar;
    SEM_ID	mutex;
    TASK_ID	owner;
    } EVENT_CONDVAR_WAIT_T;


#define EVENT_CONDVAR_SIGNAL			CLASS3_EVENT(111)

typedef struct event_condvar_signal
    {
    CONDVAR_ID	condVar;
    SEM_ID	mutex;
    TASK_ID	owner;
    } EVENT_CONDVAR_SIGNAL_T;

#define EVENT_CONDVAR_FLUSH			CLASS3_EVENT(112)

typedef struct event_condvar_flush
    {
    CONDVAR_ID	condVar;
    } EVENT_CONDVAR_FLUSH_T;


/* EVENT_TASK_CPU_AFFINITY_SET */

#define EVENT_TASK_CPU_AFFINITY_SET             CLASS3_EVENT(230)

typedef struct event_task_cpu_affinity_set
    {
    long        newAffinity;
    long        cpuId;
    } EVENT_TASK_CPU_AFFINITY_SET_T;


/* CPC and spinlock events not used */

#define EVENT_CPC_INVOKE                        CLASS3_EVENT(231)
    
#define EVENT_CPC_ENTER                         CLASS3_EVENT(232)
    
#define EVENT_CPC_DONE                          CLASS3_EVENT(233)
    
#define EVENT_CPC_ACK                           CLASS3_EVENT(234)   

#define EVENT_SPINLOCK_ERROR                    CLASS3_EVENT(238)
    

/* EVENT_DPRINTF_LOG */

#define EVENT_DPRINTF_LOG                       CLASS3_EVENT(239)

typedef struct
    {
    const char *        data;
    size_t              length;
    } EVENT_DPRINTF_LOG_T;


/*
 * USB Event Ids
 * These are CLASS3 events, from 120 - 149 for peripheral,
 * and 150 - 199 for host
 */

/* EVENT_SD_CREATE */
    
#define EVENT_SD_CREATE                         CLASS3_EVENT(200)

typedef struct event_sd_create
    {
    SD_ID               sdId;
    long                options;
    size_t              size;
    long                attr;
    long                virtAddr;
    size_t              nameLength;
    const char *        name;
    } EVENT_SD_CREATE_T;


/* EVENT_SD_DELETE */
    
#define EVENT_SD_DELETE                         CLASS3_EVENT(201)

typedef struct event_sd_delete
    {
    long                options;
    SD_ID               sdId;
    } EVENT_SD_DELETE_T;


/* EVENT_SD_MAP */
   
#define EVENT_SD_MAP                            CLASS3_EVENT(202)

typedef struct event_sd_map
    {
    long                options;
    long                attr;
    SD_ID               sdId;
    } EVENT_SD_MAP_T;


/* EVENT_SD_UNMAP */

#define EVENT_SD_UNMAP                          CLASS3_EVENT(203)

typedef struct event_sd_unmap
    {
    long                options;
    SD_ID               sdId;
    } EVENT_SD_UNMAP_T;


/* EVENT_SEMRWCREATE */
    
#define EVENT_SEMRWCREATE                       CLASS3_EVENT(204)

typedef struct event_semrwcreate
    {
    SEM_ID      semId;
    long        maxReaders;
    long        options;
    TASK_ID     owner;
    } EVENT_SEMRWCREATE_T;


/* EVENT_SEMRTAKE */
    
#define EVENT_SEMRTAKE                          CLASS3_EVENT(205)

typedef struct event_semrtake
    {
    SEM_ID      semId;
    TASK_ID     owner;
    long        recurse;
    } EVENT_SEMRTAKE_T;


/* EVENT_SEMWTAKE */
    
#define EVENT_SEMWTAKE                          CLASS3_EVENT(206)

typedef struct event_semwtake
    {
    SEM_ID      semId;
    TASK_ID     owner;
    long        recurse;
    } EVENT_SEMWTAKE_T;
    
/* set the system power policy */
#define   EVENT_PPM_POLICY_SET_SYS      CLASS3_EVENT(240)

/* set the cpu power policy */
#define   EVENT_PPM_POLICY_SET_CPU      CLASS3_EVENT(241)

/* set the device power policy */
#define   EVENT_PPM_POLICY_SET_DEV      CLASS3_EVENT(242)

/* disable power policy management */
#define   EVENT_PPM_POLICY_DISABLE      CLASS3_EVENT(243)

/* enable power policy management*/
#define   EVENT_PPM_POLICY_ENABLE      CLASS3_EVENT(244)

/* CPU power down when it is detected to be idle */
#define   EVENT_POWERDOWN      CLASS3_EVENT(245)

/* CPU power up from down */
#define   EVENT_POWERUP      CLASS3_EVENT(246)

/* Set cpu power performance state */
#define   EVENT_POWER_PSTATE_SET      CLASS3_EVENT(247)

/* Set power consume state    move top to make ASMLANGUAGE*/
/*#define   EVENT_POWER_CSTATE_SET      CLASS3_EVENT(248)*/

/* Set power device state */
#define   EVENT_POWER_DSTATE_SET      CLASS3_EVENT(249)

/* Set power device enable flags */
#define   EVENT_POWER_DEV_ENABLE_SET      CLASS3_EVENT(250)

/* Set power device capability */
#define   EVENT_POWER_DEV_CAPABILITY_SET  CLASS3_EVENT(251)

/* set device power timeout */
#define   EVENT_POWER_DEV_TIMEOUT_SET      CLASS3_EVENT(252)

/* configure a cpu load monitor */
#define   EVENT_CPU_LOAD_MON_CONF      CLASS3_EVENT(253)

/* set current task errno */
#define   EVENT_SET_ERRNO              CLASS3_EVENT(254)

/* set task errno */
#define   EVENT_SET_TASK_ERRNO         CLASS3_EVENT(255)

/* CLASS2 events */



/* EVENT_WINDSPAWN */
    
#define	EVENT_WINDSPAWN				CLASS2_EVENT(0)

typedef struct event_windspawn
    {
    TASK_ID     pTcb;
    long        priority;
    } EVENT_WINDSPAWN_T;


/* EVENT_WINDDELETE */
    
#define	EVENT_WINDDELETE			CLASS2_EVENT(1)

typedef struct event_winddelete
    {
    TASK_ID     pTcb;
    } EVENT_WINDDELETE_T;


/* EVENT_WINDSUSPEND */
    
#define	EVENT_WINDSUSPEND			CLASS2_EVENT(2)

typedef struct event_windsuspend
    {
    TASK_ID     pTcb;
    } EVENT_WINDSUSPEND_T;


/* EVENT_WINDRESUME */
    
#define	EVENT_WINDRESUME			CLASS2_EVENT(3)

typedef struct event_windresume
    {
    TASK_ID     pTcb;
    } EVENT_WINDRESUME_T;


/* EVENT_WINDPRIORITYSETRAISE */
    
#define	EVENT_WINDPRIORITYSETRAISE		CLASS2_EVENT(4)

typedef struct event_windprioritysetraise
    {
    TASK_ID     pTcb;
    long        oldPriority;
    long        priority;
    } EVENT_WINDPRIORITYSETRAISE_T;


/* EVENT_WINDPRIORITYSETLOWER */
    
#define	EVENT_WINDPRIORITYSETLOWER		CLASS2_EVENT(5)

typedef struct event_windprioritysetlower
    {
    TASK_ID     pTcb;
    long        oldPriority;
    long        priority;
    } EVENT_WINDPRIORITYSETLOWER_T;


/* EVENT_WINDSEMDELETE */
    
#define	EVENT_WINDSEMDELETE			CLASS2_EVENT(6)

typedef struct event_windsemdelete
    {
    SEM_ID      semId;
    } EVENT_WINDSEMDELETE_T;


/* EVENT_WINDTICKANNOUNCETMRSLC */

#define	EVENT_WINDTICKANNOUNCETMRSLC		CLASS2_EVENT(7)



/* EVENT_WINDTICKANNOUNCETMRSLC */
    
#define	EVENT_WINDTICKANNOUNCETMRWD		CLASS2_EVENT(8)

typedef struct event_windtickannouncetmrslc
    {
    WDOG_ID     wdId;
    } EVENT_WINDTICKANNOUNCETMRWD_T;


/* EVENT_WINDDELAY */
    
#define	EVENT_WINDDELAY				CLASS2_EVENT(9)

typedef struct event_winddelay
    {
    long        timeout;
    } EVENT_WINDDELAY_T;


/* EVENT_WINDUNDELAY */
    
#define	EVENT_WINDUNDELAY			CLASS2_EVENT(10)

typedef struct event_windundelay
    {
    struct windTcb *    pTcb;
    } EVENT_WINDUNDELAY_T;


/* EVENT_WINDWDSTART */
    
#define	EVENT_WINDWDSTART			CLASS2_EVENT(11)

typedef struct event_windwdstart
    {
    WDOG_ID     wdId;
    } EVENT_WINDWDSTART_T;


/* EVENT_WINDWDCANCEL */

#define	EVENT_WINDWDCANCEL			CLASS2_EVENT(12)

typedef struct event_windwdcancel
    {
    WDOG_ID     wdId;
    } EVENT_WINDWDCANCEL_T;


/* EVENT_WINDPENDQGET */

#define	EVENT_WINDPENDQGET			CLASS2_EVENT(13)

typedef struct event_windpendqget
    {
    struct wind_tcb *   pTcb;
    } EVENT_WINDPENDQGET_T;


/* EVENT_WINDPENDQFLUSH */

#define	EVENT_WINDPENDQFLUSH			CLASS2_EVENT(14)

typedef struct event_windpendqflush
    {
    struct wind_tcb *   pTcb;
    } EVENT_WINDPENDQFLUSH_T;


/* EVENT_WINDPENDQGET */

#define	EVENT_WINDPENDQPUT			CLASS2_EVENT(15)

/* No structure */


/* EVENT_WINDPENDQTERMINATE */

#define	EVENT_WINDPENDQTERMINATE		CLASS2_EVENT(17)

typedef struct event_windpendqterminate
    {
    struct wind_tcb *   pTcb;
    } EVENT_WINDPENDQTERMINATE_T;


/* EVENT_WINDTICKUNDELAY */

#define	EVENT_WINDTICKUNDELAY			CLASS2_EVENT(18)

typedef struct event_windtickundelay
    {
    struct wind_tcb *   pTcb;
    } EVENT_WINDTICKUNDELAY_T;


/* EVENT_OBJ_TASK */

#define EVENT_OBJ_TASK				CLASS2_EVENT(19)

typedef struct event_obj_task
    {
    struct wind_tcb *   pTcb;
    } EVENT_OBJ_TASK_T;


/* EVENT_OBJ_SEMGIVE */

#define EVENT_OBJ_SEMGIVE			CLASS2_EVENT(20)

typedef struct event_obj_semgive
    {
    SEM_ID      semId;
    } EVENT_OBJ_SEMGIVE_T;


/* EVENT_OBJ_SEMTAKE */

#define EVENT_OBJ_SEMTAKE			CLASS2_EVENT(21)

typedef struct event_obj_semtake
    {
    SEM_ID      semId;
    } EVENT_OBJ_SEMTAKE_T;


/* EVENT_OBJ_SEMFLUSH */

#define EVENT_OBJ_SEMFLUSH			CLASS2_EVENT(22)
    
typedef struct event_obj_semflush
    {
    SEM_ID      semId;
    } EVENT_OBJ_SEMFLUSH_T;


/* EVENT_OBJ_MSGSEND */

#define EVENT_OBJ_MSGSEND			CLASS2_EVENT(23)

typedef struct event_obj_msgsend
    {
    MSG_Q_ID    msgQId;
    } EVENT_OBJ_MSGSEND_T;


/* EVENT_OBJ_MSGRECEIVE */

#define EVENT_OBJ_MSGRECEIVE			CLASS2_EVENT(24)

typedef struct event_obj_msgreceive
    {
    MSG_Q_ID    msgQId;
    } EVENT_OBJ_MSGRECEIVE_T;


/* EVENT_OBJ_MSGDELETE */

#define EVENT_OBJ_MSGDELETE			CLASS2_EVENT(25)

typedef struct event_obj_msgdelete
    {
    MSG_Q_ID    msgQId;
    } EVENT_OBJ_MSGDELETE_T;


/* EVENT_OBJ_SIGPAUSE */

#define EVENT_OBJ_SIGPAUSE			CLASS2_EVENT(26)

typedef struct event_obj_sigpause
    {
    TASK_ID	task;
    } EVENT_OBJ_SIGPAUSE_T;


/* EVENT_OBJ_SIGSUSPEND */

#define EVENT_OBJ_SIGSUSPEND			CLASS2_EVENT(27)

typedef struct event_obj_sigsuspend
    {
    long        set;
    } EVENT_OBJ_SIGSUSPEND_T;


/* EVENT_OBJ_SIGKILL */

#define EVENT_OBJ_SIGKILL			CLASS2_EVENT(28)

typedef struct event_obj_sigkill
    {
    TASK_ID     task;
    } EVENT_OBJ_SIGKILL_T;


/* EVENT_WINDSTOP */

#define	EVENT_WINDSTOP				CLASS2_EVENT(29)

typedef struct event_windstop
    {
    TASK_ID     task;
    } EVENT_WINDSTOP_T;


/* EVENT_WINDCONT */

#define	EVENT_WINDCONT				CLASS2_EVENT(30)
    
typedef struct event_windcont
    {
    TASK_ID     task;
    } EVENT_WINDCONT_T;


/* EVENT_WINDTICKTIMEOUT */

#define EVENT_WINDTICKTIMEOUT                   CLASS2_EVENT(31)

typedef struct event_windticktimeout
    {
    TASK_ID     task;
    } EVENT_WINDTICKTIMEOUT_T;


/* EVENT_OBJ_SIGWAIT */

#define EVENT_OBJ_SIGWAIT                       CLASS2_EVENT(32)

typedef struct event_obj_sigwait
    {
    TASK_ID     task;
    } EVENT_OBJ_SIGWAIT_T;


/* EVENT_OBJ_EVENTSEND */

#define	EVENT_OBJ_EVENTSEND			CLASS2_EVENT(35)

/* No structure */


/* EVENT_OBJ_EVENTRECEIVE */

#define	EVENT_OBJ_EVENTRECEIVE			CLASS2_EVENT(36)

/* No structure */


/* EVENT_OBJ_MSGCDELETE */

#define EVENT_OBJ_MSGCDELETE                    CLASS2_EVENT(37)

/* Not referenced */


/* EVENT_OBJ_MSGCSEND */

#define EVENT_OBJ_MSGCSEND                      CLASS2_EVENT(38)

/* Not referenced */


/* EVENT_OBJ_MSGCREPLYGET */

#define EVENT_OBJ_MSGCREPLYGET                  CLASS2_EVENT(39)

/* Not referenced */


/* EVENT_OBJ_MSGCACKSEND */

#define EVENT_OBJ_MSGCACKSEND                   CLASS2_EVENT(40)

/* Not referenced */


/* EVENT_OBJ_MSGCREPLYSEND */

#define EVENT_OBJ_MSGCREPLYSEND                 CLASS2_EVENT(41)

/* Not referenced */


/* EVENT_OBJ_MSGSDELETE*/

#define EVENT_OBJ_MSGSDELETE                    CLASS2_EVENT(42)

/* Not referenced */

    
/* EVENT_OBJ_MSGSRECEIVE */

#define EVENT_OBJ_MSGSRECEIVE                   CLASS2_EVENT(43)

/* Not referenced */


/* EVENT_OBJ_MSGSREPLY */

#define EVENT_OBJ_MSGSREPLY                     CLASS2_EVENT(44)

/* Not referenced */


/* EVENT_OBJ_MSGSSEND */

#define EVENT_OBJ_MSGSSEND                      CLASS2_EVENT(45)

/* Not referenced */


/* EVENT_OBJ_WINDROTATE */
    
#define EVENT_OBJ_WINDROTATE                    CLASS2_EVENT(46)

typedef struct
    {
    long	priority;
    } EVENT_OBJ_WINDROTATE_T;


/* EVENT_OBJ_SEMRTAKE */
    
#define EVENT_OBJ_SEMRTAKE                      CLASS2_EVENT(47)

typedef struct
    {
    SEM_ID      semId;
    } EVENT_OBJ_SEMRTAKE_T;


/* EVENT_OBJ_SEMWTAKE */
    
#define EVENT_OBJ_SEMWTAKE                      CLASS2_EVENT(48)

typedef struct
    {
    SEM_ID      semId;
    } EVENT_OBJ_SEMWTAKE_T;
    

/* CLASS1 events */


/* EVENT_WIND_EXIT_NODISPATCH */

typedef struct
    {
    struct windTcb *    taskId;
    } EVENT_WIND_EXIT_NODISPATCH_T;



/* EVENT_WIND_EXIT_NODISPATCH_PI */

typedef struct
    {
    struct windTcb *    taskId;
    } EVENT_WIND_EXIT_NODISPATCH_PI_T;



/* EVENT_WIND_EXIT_NODISPATCH */

typedef struct
    {
    struct windTcb *    taskIdNew;
    long		priority;
    } EVENT_WIND_EXIT_DISPATCH_T;



/* EVENT_WIND_EXIT_DISPATCH_PI */

typedef struct
    {
    struct windTcb *    taskIdNew;
    long                priority;
    } EVENT_WIND_EXIT_DISPATCH_PI_T;


/* EVENT_WIND_EXIT_IDLE */
    
#define	EVENT_WIND_EXIT_IDLE			CLASS1_EVENT(6)


/* EVENT_TASKLOCK */

#define	EVENT_TASKLOCK				CLASS1_EVENT(7)

/* No structure */


/* EVENT_TASKUNLOCK */

#define	EVENT_TASKUNLOCK			CLASS1_EVENT(8)

/* No structure */


/* EVENT_TICKANNOUNCE */

#define	EVENT_TICKANNOUNCE			CLASS1_EVENT(9)

/* No structure */


/* EVENT_EXCEPTION */

#define	EVENT_EXCEPTION				CLASS1_EVENT(10)

typedef struct
    {
    long        arg1;
    } EVENT_EXCEPTION_T;
    

/* EVENT_TASK_STATECHANGE */

#define EVENT_TASK_STATECHANGE                  CLASS1_EVENT(11)


/* EVENT_TASKUNLOCK_ZERO */

/* No structure */

#define EVENT_TASKUNLOCK_ZERO			CLASS1_EVENT(24)


/* EVENT_TASKUNLOCK_NONZERO */

/* No structure */

#define EVENT_TASKUNLOCK_NONZERO		CLASS1_EVENT(25)

/* Not referenced */


/* EVENT_WVEVENT */

 typedef struct
    {
    event_t             userEventId;
    const void *        pc;
    const void *        data;
    size_t              length;
    } EVENT_WVEVENT_T;
    
    
#endif /* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif


#endif /* __eventdefsPh */

