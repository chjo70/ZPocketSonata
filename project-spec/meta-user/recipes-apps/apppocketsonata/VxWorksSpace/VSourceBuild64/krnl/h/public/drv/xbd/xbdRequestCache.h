/* xbdRequestCache.h -  xbd request cache header file */

/*
 * Copyright (c) 2012 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify, or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01a,30nov12,w_x   written.
*/

#ifndef __INCxbdRequestCacheh
#define __INCxbdRequestCacheh

#include <vxWorks.h>
#include <poolLib.h>

#ifdef __cplusplus
extern "C" {
#endif

#define XBD_REQ_CACHE_DEFAULT_NUM_REQS 50
#define XBD_REQ_CACHE_DEFAULT_INCREASE 50

POOL_ID xbdRequestCacheCreate
    (
    size_t uNumReqs,
    size_t uReqSize
    );

STATUS xbdRequestCacheDestroy 
    (
    POOL_ID xbdRequestCachePool
    );

STATUS xbdRequestCacheLibInit (void);
STATUS xbdRequestCacheLibFini (void);

#ifdef __cplusplus
}
#endif

#endif /* __INCxbdRequestCacheh */

