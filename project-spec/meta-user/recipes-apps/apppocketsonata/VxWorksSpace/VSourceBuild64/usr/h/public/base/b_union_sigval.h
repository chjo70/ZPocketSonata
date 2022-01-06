/* b_union_sigval.h - base type union sigval definition header */

/*
 * Copyright (c) 2006 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement. 
*/

/*
modification history
--------------------
01a,18jal06,mil  Updated for POSIX namespace conformance (P2).
                 Created from sigeventCommon.h.
*/

#ifndef __INCb_union_sigvalh
#define __INCb_union_sigvalh

#ifdef __cplusplus
extern "C" {
#endif

union sigval
    {
    int                 sival_int;
    void                *sival_ptr;
    };

#ifdef __cplusplus
}
#endif

#endif /* __INCb_union_sigvalh */
