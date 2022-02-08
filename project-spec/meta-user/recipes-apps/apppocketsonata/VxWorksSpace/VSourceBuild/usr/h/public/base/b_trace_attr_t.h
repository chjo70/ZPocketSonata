/* b_trace_attr_t.h - definition of trace_attr_t for POSIX trace */

/*
 * Copyright (c) 2006, 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement. 
*/

/*
modification history
--------------------
01e,18may10,pad  Moved extern C statement after include statements.
01d,11aug06,tcr  fix POSIX_TRACE_NAME_MAX for namespace isolation
01c,08aug06,pad  Make use of _Timespec type instead of timespec in order to be
		 compatible with the namespace isolation rules.
01b,11jul06,tcr  correct include for timespec
01a,21jun06,tcr  created
*/

#ifndef __INCb_trace_attr_th
#define __INCb_trace_attr_th

#ifndef _DEFINED_trace_attr_t
#define _DEFINED_trace_attr_t

#include <base/b_size_t.h>
#include <base/b_struct__Timespec.h>

/* This must match the definition in limits.h */

#define _TRACE_NAME_MAX      64

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Note: we can't simply use the timespec stucture here because this conflicts
 * with the namespace isolation rules when users of the trace_attr_t structure
 * type other than trace.h are included directly or indirectly by an
 * application.
 */

typedef struct
    {
    int                 _Trace_attr_magic;
    char                _Generation_version [_TRACE_NAME_MAX];
    char                _Trace_name [_TRACE_NAME_MAX];
    struct _Timespec    _Creation_time;
    struct _Timespec    _Clock_resolution;
    size_t              _Stream_min_size;
    int                 _Stream_full_policy;
    size_t              _Max_data_size;
    int                 _Log_full_policy;
    size_t              _Log_max_size;
    } trace_attr_t;

#ifdef __cplusplus
}
#endif

#undef _TRACE_NAME_MAX

#endif /* _DEFINED_trace_attr_t */

#endif /* __INCb_trace_attr_th */
