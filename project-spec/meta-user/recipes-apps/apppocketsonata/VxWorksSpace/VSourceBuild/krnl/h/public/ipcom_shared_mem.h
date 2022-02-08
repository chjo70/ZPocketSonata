/* ipcom_shared_mem.h - API for shared memory allocation */

/*
 * Copyright (c) 2006-2013 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */
#ifndef IPCOM_SHARED_MEM_H
#define IPCOM_SHARED_MEM_H

/*
 ****************************************************************************
 * 1                    DESCRIPTION
 ****************************************************************************
 * Definition of API for creating, allocating from, and freeing memory to
 * a shared memory pool based upon a shared memory region.
 * It is intended for AMP systems that need to allocate and free shared
 * memory.
 */


/*
 ****************************************************************************
 * 2                    CONFIGURATION
 ****************************************************************************
 */

#include "ipcom_config.h"


/*
 ****************************************************************************
 * 3                    INCLUDE FILES
 ****************************************************************************
 */

#include <ipcom_atomic.h>
#include <ipcom_cstyle.h>
#include <ipcom_type.h>
#include <ipcom_ipc_spinlock.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 ****************************************************************************
 * 4                    DEFINES
 ****************************************************************************
 */

/*
 ****************************************************************************
 * 5                    TYPES
 ****************************************************************************
 */

typedef Ip_size_t Ip_shared_mem_offset;

typedef Ip_size_t Ip_shared_mem_virt_addr;

/* The memory pool type is opaque. */
struct Ipcom_shared_mem_pool_struct;
typedef struct Ipcom_shared_mem_pool_struct Ipcom_shared_mem_pool_t;

typedef struct Ipcom_shared_mem_pool_cfg_s
{
    Ip_shared_mem_virt_addr addr;
    Ip_size_t len;
} Ipcom_shared_mem_pool_cfg_t;

/*
 ****************************************************************************
 * 6                    FUNCTIONS
 ****************************************************************************
 */

IP_PUBLIC Ip_size_t
ipcom_shared_mem_blk_size(Ipcom_shared_mem_pool_t *pool, void *buffer);

IP_PUBLIC void *
ipcom_shared_mem_alloc(Ipcom_shared_mem_pool_t *pool, Ip_size_t size);

IP_PUBLIC void
ipcom_shared_mem_free(Ipcom_shared_mem_pool_t *pool, void *buffer);

IP_PUBLIC int
ipcom_shared_mem_pool_init(Ipcom_shared_mem_pool_t *pool, Ip_size_t size);

#ifdef __cplusplus
}
#endif

#endif /* IPCOM_SHARED_MEM_H */


/*
 ****************************************************************************
 *                      END OF FILE
 ****************************************************************************
 */
