/* b_trace_id_t.h - definition of trace_id_t */

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
01c,18may10,pad  Moved extern C statement after include statements.
01b,24jul06,jpb  Removed POSIX condition.
01a,23jun06,tcr  created
*/

#ifndef __INCb_trace_id_th
#define __INCb_trace_id_th

#ifndef _DEFINED_trace_id_t
#define _DEFINED_trace_id_t

#include <types/vxWind.h>

#ifdef __cplusplus
extern "C" {
#endif

#if _WRS_KERNEL
typedef OBJ_HANDLE  trace_id_t;
#else
typedef _Vx_OBJ_HANDLE  trace_id_t;
#endif  /* _WRS_KERNEL */

#ifdef __cplusplus
}
#endif

#endif /* _DEFINED_trace_id_t */

#endif /* __INCb_trace_id_t */
