/* pxTraceLibCommon.h - header for shared POSIX trace */

/* Copyright (c) 2006 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use 
 * of this software may be licensed only pursuant to the terms 
 * of an applicable Wind River license agreement. 
 */ 

/*
modification history
--------------------
01a,07jul06,tcr  created
*/

#ifndef __INCpxTraceLibCommonh
#define __INCpxTraceLibCommonh

#ifdef __cplusplus
extern "C" {
#endif


/* defines */
    
/*
 * The <trace.h> header shall define the following symbols:
 */

/* allowed values for posix_stream_flush_status */

#define POSIX_TRACE_NOT_FLUSHING        0
#define POSIX_TRACE_FLUSHING            1

/* allowed values for posix_stream_full_status and posix_log_full_status */

#define POSIX_TRACE_NOT_FULL            0
#define POSIX_TRACE_FULL                1


/* allowed values for posix_stream_status */

#define POSIX_TRACE_SUSPENDED           0
#define POSIX_TRACE_RUNNING             1


/*
 * allowed values for posix_stream_overrun_status and
 * posix_log_overrun_status
 */

#define POSIX_TRACE_NO_OVERRUN          0
#define POSIX_TRACE_OVERRUN             1

/* allowed values for stream_full_policy */

#define POSIX_TRACE_LOOP                1
#define POSIX_TRACE_UNTIL_FULL          2
#define POSIX_TRACE_FLUSH               3


/* allowed values for log_full_policy */

#define POSIX_TRACE_APPEND              3


/* allowed values for inheritance */

#if _POSIX_TRACE_INHERIT > 0
#define POSIX_TRACE_CLOSE_FOR_CHILD     0
#define POSIX_TRACE_INHERITED           1
#endif /* _POSIX_TRACE_INHERIT */


/* allowed values for posix_truncation_status */

#define POSIX_TRACE_NOT_TRUNCATED       0
#define POSIX_TRACE_TRUNCATED_RECORD    1
#define POSIX_TRACE_TRUNCATED_READ      2


#define POSIX_TRACE_WOPID_EVENTS        0
#define POSIX_TRACE_SYSTEM_EVENTS       1
#define POSIX_TRACE_ALL_EVENTS          2

/* options for manipulating event sets */
#define POSIX_TRACE_SET_EVENTSET        1    
#define POSIX_TRACE_ADD_EVENTSET        2
#define POSIX_TRACE_SUB_EVENTSET        3



/* These definitions must track the definitions in target/usr/h/limits.h */

#ifndef TRACE_USER_EVENT_MAX
#define TRACE_USER_EVENT_MAX    256
#endif
    
#ifndef TRACE_EVENT_NAME_MAX
#define TRACE_EVENT_NAME_MAX  64
#endif
    
#ifndef TRACE_NAME_MAX
#define TRACE_NAME_MAX  64
#endif

/*
 * These are the range of ids for each event range. Note the values in
 * base/b_trace_event_set_t.h too.
 */

#define _TRACE_IMPLDEF_SYS_EVENTS_START 256
#define _TRACE_SYS_EVENTS_START         512
#define _TRACE_USR_EVENTS_START         1024
#define _TRACE_FIRST_USER_EVENT         (_TRACE_USR_EVENTS_START + 1)



#define POSIX_TRACE_ERROR       _TRACE_SYS_EVENTS_START
#define POSIX_TRACE_START       (_TRACE_SYS_EVENTS_START+1)
#define POSIX_TRACE_STOP        (_TRACE_SYS_EVENTS_START+2)
#define POSIX_TRACE_OVERFLOW    (_TRACE_SYS_EVENTS_START+3)
#define POSIX_TRACE_RESUME      (_TRACE_SYS_EVENTS_START+4)
#define POSIX_TRACE_FILTER      (_TRACE_SYS_EVENTS_START+5)
#define POSIX_TRACE_FLUSH_START (_TRACE_SYS_EVENTS_START+6)
#define POSIX_TRACE_FLUSH_STOP  (_TRACE_SYS_EVENTS_START+7)

#define POSIX_TRACE_UNNAMED_USEREVENT   _TRACE_USR_EVENTS_START



#ifdef __cplusplus
}
#endif


#endif /* __INCpxTraceLibCommonh */
