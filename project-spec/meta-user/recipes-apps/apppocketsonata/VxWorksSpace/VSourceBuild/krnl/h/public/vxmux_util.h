/* vxmux_util.h - conventional utility macros for VxWorks */

/*
 * Copyright (c) 2014 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
05may14,rjq  Decouple COREIP with END. (V7NET-105)
*/

/*
DESCRIPTION
This file includes util for the MUX.

INCLUDE FILES:
*/


#ifndef VXMUX_UTIL_H
#define VXMUX_UTIL_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define member_to_object(pMember, type, memberName) \
    ((type *)((char *)(pMember) - offsetof (type, memberName)))


#ifdef __cplusplus
}
#endif

#endif /* VXMUX_UTIL_H */
