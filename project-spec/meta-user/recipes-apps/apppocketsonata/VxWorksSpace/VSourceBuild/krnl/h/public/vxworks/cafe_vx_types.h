/* cafe_vx_types.h - VxWorks type abstractions */

/* Copyright (c) 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

#if !defined(__cafe_vx_types_h)
#define __cafe_vx_types_h

#include <version.h>

#if defined(__cplusplus)
extern "C" {
#endif


#if (_WRS_VXWORKS_MAJOR < 6)					\
	|| (_WRS_VXWORKS_MAJOR == 6) && (_WRS_VXWORKS_MINOR < 9)

#include <vxAtomicLib.h>  /* for vxCas() */
#define TASK_ID_ERROR (ERROR)
#define TASK_ID_TYPE  int

#define MSG_Q_ID_NULL (NULL)

/* Vx 6.9 fixes a long-standing issue with the VxWorks APIs, where "generic"
   parameters were defined as int-types, by promoting them to the more
   portable void*-type. */
typedef int vx_handle_t;

typedef int _Vx_usr_arg_t;
typedef unsigned int _Vx_event_t;


/* td: reconcile this with cafe/src/atomic_vxworks.c; do we really need two wrappers around *Cas()? */
static inline
bool vxAtomicCas(atomic_t *target, atomicVal_t old_val, atomicVal_t new_val)
{
	return vxCas(target, old_val, new_val);
}


#else

#define TASK_ID_TYPE  TASK_ID
typedef void * vx_handle_t;

#endif


#if defined(__cplusplus)
}	/* extern "C" */
#endif

#endif  /* if !defined(__cafe_vx_types_h) */
