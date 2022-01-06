/* b_struct_vx_eventsResourceCb.h - struct _Vx_eventsResourceCb header file */

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
                 Created from private/eventLibP.h.
*/

#ifndef __INCb_struct_vx_eventsresourcecbh
#define __INCb_struct_vx_eventsresourcecbh

#include <base/e_vxTypesOld.h>          /* for _Vx_UINT32 and _Vx_UINT8 */

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _ASMLANGUAGE

typedef struct _Vx_eventsResourceCb
    {
    _Vx_UINT32 registered;  /* 0x00: events registered for that resource    */
    int        taskId;      /* 0x04: task registered for that resource      */
    _Vx_UINT8  options;     /* 0x08: user options                           */
    _Vx_UINT8  pad[3];      /* 0x09: alignment on 32bit, possible extension */
    } _Vx_EVENTS_RSRC;      /* 0x0c: total size                             */

#endif  /* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCb_struct_vx_eventsresourcecbh */
