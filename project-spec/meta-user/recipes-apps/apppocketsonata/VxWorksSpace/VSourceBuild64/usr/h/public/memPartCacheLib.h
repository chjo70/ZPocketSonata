/* memPartCacheLib.h - User side memory cache management library header file */

/* 
 * Copyright (c) 2016 Wind River Systems, Inc. 
 *
 * The right to copy, distribute, modify or otherwise make use 
 * of this software may be licensed only pursuant to the terms 
 * of an applicable Wind River license agreement. 
 */

/*
modification history
--------------------
10aug16,ajt  Added support for SMP-optimized memory allocator (F3925)
*/

#ifndef __INCmemPartCacheLibh
#define __INCmemPartCacheLibh

#ifdef __cplusplus
extern "C" {
#endif

/* Any C declaration should be added here */

extern STATUS memPartCacheCreate (void);

#ifdef __cplusplus
}
#endif

#endif /* __INCmemPartCacheLibh */

