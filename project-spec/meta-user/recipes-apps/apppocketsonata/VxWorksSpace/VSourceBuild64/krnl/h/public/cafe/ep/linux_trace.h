/* linux_trace.h - EP exposing linux trace events */

/*
 * Copyright (c) 2010-2011 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

#if !defined(__linux_trace_h)
#define __linux_trace_h

#include <cafe/cafe.h>

#if defined(__cplusplus)
extern "C" {
#endif


#define PERF_STACK_TRACE_VT_DEF "S[perf.stacktrace,v[stack,a[Q]," \
	cafe_ADDRESS_VT_NAT "]]"
#define PERF_STACK_TRACE_VT_REF "t[perf.stacktrace]"

extern int linux_trace_register(void);
extern void linux_trace_unregister(void);


#if defined(__cplusplus)
}
#endif	/* __cplusplus */

#endif /* __linux_trace_h */
