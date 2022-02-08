/* trace.h - tracing definitions */

/* Copyright 2005,2006, 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use 
 * of this software may be licensed only pursuant to the terms 
 * of an applicable Wind River license agreement. 
 */ 

/*
modification history
--------------------
01c,29jul10,pad  Moved extern C statement after include statements.
01b,01aug06,tcr  update to follow coding conventions
01a,25oct05,tcr  created

*/

#ifndef __INCtraceh
#define __INCtraceh

#include <sys/cdefs.h>          /* for _Restrict */

#include <base/b_trace_attr_t.h>
#include <base/b_pid_t.h>
#include <base/b_pthread_t.h>
#include <base/b_trace_id_t.h>
#include <base/b_trace_event_id_t.h>
#include <base/b_trace_event_set_t.h>
#include <base/b_struct_posix_trace_event_info.h>
#include <base/b_struct_posix_trace_status_info.h>

#include <pxTraceLibCommon.h>

#ifdef __cplusplus
extern "C" {
#endif

    

/*
 * The following shall be declared as functions and may also be defined as
 * macros. Function prototypes shall be provided.
 */

int posix_trace_attr_destroy (trace_attr_t * attr);
    
int posix_trace_attr_getclockres (const trace_attr_t * attr,
                                   struct timespec * resolution);
    
int posix_trace_attr_getcreatetime (const trace_attr_t * attr,
                                    struct timespec * createtime);
int posix_trace_attr_getgenversion (const trace_attr_t * attr,
                                    char * genversion);

#if _POSIX_TRACE_INHERIT > 0
int  posix_trace_attr_getinherited (const trace_attr_t * _Restrict attr,
                                    int * _Restrict inheritancepolicy);
#endif /* _POSIX_TRACE_INHERIT */

int posix_trace_attr_getlogfullpolicy (const trace_attr_t * _Restrict attr,
                                        int * _Restrict logpolicy);
    
int posix_trace_attr_getlogsize (const trace_attr_t * _Restrict attr,
                                  size_t * _Restrict logsize);
    
int posix_trace_attr_getmaxdatasize (const trace_attr_t * _Restrict attr,
                                     size_t * _Restrict maxdatasize);
    
int posix_trace_attr_getmaxsystemeventsize (const trace_attr_t * _Restrict attr,
                                            size_t * _Restrict maxdatasize);
    
int posix_trace_attr_getmaxusereventsize (const trace_attr_t * _Restrict attr,
                                          size_t, size_t * _Restrict eventsize);
        
int posix_trace_attr_getname (const trace_attr_t * attr,
                              char * tracename);

int posix_trace_attr_getstreamfullpolicy (const trace_attr_t * _Restrict attr,
                                          int * _Restrict streampolicy);

int posix_trace_attr_getstreamsize (const trace_attr_t * _Restrict attr,
                                    size_t * _Restrict streamsize);
    
int posix_trace_attr_init (trace_attr_t * attr);

#if _POSIX_TRACE_INHERIT > 0
int posix_trace_attr_setinherited (trace_attr_t * attr, int inheritancepolicy);
#endif /* _POSIX_TRACE_INHERIT */

int posix_trace_attr_setlogfullpolicy (trace_attr_t * attr, int logpolicy);
 
int posix_trace_attr_setlogsize (trace_attr_t * attr, size_t logsize);
    
int posix_trace_attr_setmaxdatasize (trace_attr_t * attr, size_t maxdatasize);
    
int posix_trace_attr_setname (trace_attr_t * attr, const char * tracename);
    
int posix_trace_attr_setstreamsize (trace_attr_t * attr, size_t streamsize);

int posix_trace_attr_setstreamfullpolicy (trace_attr_t * attr,
                                          int streampolicy);
 
int posix_trace_clear (trace_id_t trid);

int posix_trace_close (trace_id_t trid);
 
int posix_trace_create (pid_t pid,const trace_attr_t * _Restrict attr,
                        trace_id_t * _Restrict trid);

int posix_trace_create_withlog (pid_t pid,const trace_attr_t * _Restrict attr,
                                int fd, trace_id_t * _Restrict  trid);
 
void posix_trace_event (trace_event_id_t event_id,
                        const void * _Restrict data_ptr, size_t data_size);
 
int posix_trace_eventid_equal (trace_id_t trid, trace_event_id_t event1,
                               trace_event_id_t event2);
 
int posix_trace_eventid_get_name (trace_id_t trid, trace_event_id_t event,
                                  char * event_name);
 
int posix_trace_eventid_open (const char * _Restrict event_name,
                              trace_event_id_t * _Restrict event_id);

int posix_trace_eventset_add (trace_event_id_t event_id,
                              trace_event_set_t * set);
 
int posix_trace_eventset_del (trace_event_id_t event_id,
                              trace_event_set_t * set);
 
int posix_trace_eventset_empty (trace_event_set_t * set);
 
int posix_trace_eventset_fill (trace_event_set_t * set, int what);
 
int posix_trace_eventset_ismember (trace_event_id_t event_id,
                                   const trace_event_set_t * _Restrict set,
                                   int * _Restrict  ismember);

int posix_trace_eventtypelist_getnext_id (trace_id_t trid,
                                          trace_event_id_t * _Restrict event,
                                          int * _Restrict unavailable);
 
int posix_trace_eventtypelist_rewind (trace_id_t trid);

int posix_trace_flush (trace_id_t trid);
 
int posix_trace_get_attr (trace_id_t trid, trace_attr_t * attr);
 
int posix_trace_get_filter (trace_id_t trid, trace_event_set_t * set);
 
int posix_trace_get_status (trace_id_t trid,
                            struct posix_trace_status_info * status);
 
int posix_trace_getnext_event (trace_id_t trid,
                               struct posix_trace_event_info * _Restrict event,
                               void * _Restrict data, size_t num_bytes,
                               size_t * _Restrict data_len,
                               int * _Restrict unavailable);
 
int posix_trace_open (int fd, trace_id_t * trid);
 
int posix_trace_rewind (trace_id_t trid);
 
int posix_trace_set_filter (trace_id_t trid, const trace_event_set_t * set,
                            int how);
 
int posix_trace_shutdown (trace_id_t trid);
 
int posix_trace_start (trace_id_t trid);
 
int posix_trace_stop (trace_id_t trid);

int posix_trace_timedgetnext_event (trace_id_t trid,
                                    struct posix_trace_event_info * _Restrict
                                    event, void * _Restrict data,
                                    size_t num_bytes,
                                    size_t * _Restrict data_len,
                                    int * _Restrict unavailable,
                                    const struct timespec * _Restrict timeout);
 
int posix_trace_trid_eventid_open (trace_id_t trid,
                                   const char * _Restrict event_name,
                                   trace_event_id_t * _Restrict  event);
 
int posix_trace_trygetnext_event (trace_id_t trid,
                                  struct posix_trace_event_info * _Restrict
                                  event, void * _Restrict data,
                                  size_t num_bytes, size_t * _Restrict data_len,
                                  int * _Restrict unavailable);

#endif /* __INCtraceh */

