/*
 * Copyright (c) 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

 
/* THIS IS GENERATED CODE. DO NOT MODIFY */
/*
 * Copyright (c) 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

 
/* THIS IS GENERATED CODE. DO NOT MODIFY */

#ifndef INCperformance_profiler_h
#define INCperformance_profiler_h

#ifdef __cplusplus
extern "C" {
#endif
#define PERFORMANCE_PROFILER___ADDRESS_VT_DEF "N[ADDRESS]"

#define PERFORMANCE_PROFILER___SAMPLE_VT_DEF "S[performance_profiler.sample,v[cpu_id,I]v[tid,L]v[pid,L]v[stack,a[L],n[ADDRESS]]]"
#define PERFORMANCE_PROFILER___SAMPLE_VT_REF "t[performance_profiler.sample]"

#define PERFORMANCE_PROFILER___NEW_THREAD_VT_DEF "S[performance_profiler.new_thread,v[tid,L]v[pid,L]v[type,I]v[name,s]]"
#define PERFORMANCE_PROFILER___NEW_THREAD_VT_REF "t[performance_profiler.new_thread]"

#define PERFORMANCE_PROFILER___CONNECT_VT_DEF "S[performance_profiler.connect,v[cpus,I]]"
#define PERFORMANCE_PROFILER___CONNECT_VT_REF "t[performance_profiler.connect]"

#define PERFORMANCE_PROFILER___MISSED_INTERRUPTS_VT_DEF "S[performance_profiler.missed_interrupts,v[count,L]]"
#define PERFORMANCE_PROFILER___MISSED_INTERRUPTS_VT_REF "t[performance_profiler.missed_interrupts]"

#define PERFORMANCE_PROFILER___IDLE_SAMPLE_VT_DEF "S[performance_profiler.idle_sample,v[cpu_id,I]]"
#define PERFORMANCE_PROFILER___IDLE_SAMPLE_VT_REF "t[performance_profiler.idle_sample]"

#define PERFORMANCE_PROFILER___KERNEL_SAMPLE_VT_DEF "S[performance_profiler.kernel_sample,v[cpu_id,I]]"
#define PERFORMANCE_PROFILER___KERNEL_SAMPLE_VT_REF "t[performance_profiler.kernel_sample]"

#ifdef __cplusplus
}
#endif	/* __cplusplus */

#endif /* INCperformance_profiler_h */
