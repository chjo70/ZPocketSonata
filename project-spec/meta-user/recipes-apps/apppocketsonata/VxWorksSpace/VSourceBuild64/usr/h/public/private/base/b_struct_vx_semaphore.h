/* b_struct_vx_semaphore.h - struct _Vx_semaphore header file */

/* Copyright 1984-2006, 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use 
 * of this software may be licensed only pursuant to the terms 
 * of an applicable Wind River license agreement. 
 */ 

/*
modification history
--------------------
01b,29jul10,pad  Moved extern C statement after include statements.
01a,18jan06,mil  Updated for POSIX namespace conformance (P1).
                 Created from private/semLibP.h.
*/

#ifndef __INCb_struct_vx_semaphoreh
#define __INCb_struct_vx_semaphoreh

#include <private/base/b_struct_vx_eventsResourceCb.h> /* for _Vx_EVENT_RSRC */
#include <types/vxWind.h>           /* definition of _Vx_SEM_ID_KERNEL */
#include <base/e_vxTypesOld.h>      /* definition of _Vx_UINT */

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _ASMLANGUAGE

typedef struct _Vx_semaphore        /* SEMAPHORE */
    {
    _Vx_UINT          magic;        /* 0x00: magic number for identification */
    _Vx_UINT          semType;      /* 0x04: semaphore type */
    _Vx_UINT          options;      /* 0x08: semaphore options */
    _Vx_UINT          recurse;      /* 0x0c: semaphore recursive take count */
    volatile _Vx_UINT owned_k;      /* 0x10: kernel semaphore is owned*/
    _Vx_SEM_ID_KERNEL semId_k;      /* 0x14: kernel semaphore id */
    union
        {
        volatile _Vx_UINT count;    /* 0x18: current state */
        volatile _Vx_UINT owner;    /* 0x18: current state */
        } state;
    _Vx_EVENTS_RSRC events;         /* 0x1c: VxWorks events */
    } _Vx_SEMAPHORE;

#endif  /* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif  /* __INCb_struct_vx_semaphoreh */
