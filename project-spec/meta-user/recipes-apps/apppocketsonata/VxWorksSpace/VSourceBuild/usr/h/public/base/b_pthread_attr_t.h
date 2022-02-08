/* b_pthread_attr_t.h - base type pthread_attr_t definition header */

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
01c,28apr10,pad  Moved extern C statement after include statements.
01b,01aug06,pad  Replaced use of sched_param structure with _Sched_param to
                 allow signal event support to abide with namespace isolation.
01a,16feb06,pes  Created.
*/

#ifndef __INCb_pthread_attr_th
#define __INCb_pthread_attr_th

/* Includes */

#include <base/b_size_t.h>		/* size_t type definition */
#include <base/b_struct__Sched_param.h>	/* struct _Sched_param type def */

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _DEFINED_pthread_attr_t
#define _DEFINED_pthread_attr_t

#if defined(_POSIX_C_SOURCE) || defined(_XOPEN_SOURCE) || \
    defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE)

#undef threadAttrStatus
#undef threadAttrStacksize
#undef threadAttrStackaddr
#undef threadAttrGuardsize
#undef threadAttrDetachstate
#undef threadAttrContentionscope
#undef threadAttrInheritsched
#undef threadAttrSchedpolicy
#undef threadAttrName
#undef threadAttrOptions
#undef threadAttrSchedparam
#endif /* _POSIX_xxxx_SOURCE */

/*
 * Note: we can't simply use the sched_param stuctures here because this
 * conflicts with the namespace isolation rules when users of the
 * pthread_attr_t structure type other than pthread.h (such as signal.h)
 * are included directly or indirectly by an application.
 */

typedef struct {
      int    threadAttrStatus;			/* status flag              */
      size_t threadAttrStacksize;		/* stack size               */
      void * threadAttrStackaddr;		/* stack address            */
      size_t threadAttrGuardsize;		/* guard address (RTP only) */
      int    threadAttrDetachstate;		/* detach state             */
      int    threadAttrContentionscope;		/* contention scope         */
      int    threadAttrInheritsched;		/* inherit scheduler        */
      int    threadAttrSchedpolicy;		/* scheduling policy        */
      char * threadAttrName;		/* task name - VxWorks extension    */
      int    threadAttrOptions;		/* task options - VxWorks extension  */
      struct _Sched_param threadAttrSchedparam; /* sched param struct */
    } pthread_attr_t;

#endif /* _DEFINED_pthread_attr_t */

#ifdef __cplusplus
}
#endif

#endif /* __INCb_pthread_attr_th */

