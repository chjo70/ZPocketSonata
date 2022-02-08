/* b_struct_posix_trace_status_info.h - header defining struct posix_trace_status_info */

/*
 * Copyright (c) 2006 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement. 
*/

/*
modification history
--------------------
01a,04jul06,tcr  created
*/

#ifndef __INCb_posix_trace_status_infoh
#define __INCb_posix_trace_status_infoh

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _DEFINED_posix_trace_status_info
#define _DEFINED_posix_trace_status_info

/*
 * The <trace.h> header shall define the posix_trace_status_info structure that
 * includes at least the following members:
 */

struct posix_trace_status_info
    {
    int                 posix_stream_status;
    int                 posix_stream_full_status;
    int                 posix_stream_overrun_status;
    int                 posix_stream_flush_status;
    int                 posix_stream_flush_error;
    int                 posix_log_overrun_status;
    int                 posix_log_full_status;
    };
    
#ifdef _WRS_KERNEL
typedef struct posix_trace_status_info POSIX_TRACE_STATUS_INFO;
#endif
    
#endif /* _DEFINED_posix_trace_status_info */

#ifdef __cplusplus
}
#endif

#endif  /*  __INCb_posix_trace_status_info_h */
