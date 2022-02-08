/*
 * Copyright (c) 2006-2013 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

#ifndef VXMUX_SLAB_H
#define VXMUX_SLAB_H

/*
 ****************************************************************************
 * 1                    DESCRIPTION
 ****************************************************************************
 */

/*
 * Fixed size allocator.
 */


/*
 ****************************************************************************
 * 2                    CONFIGURATION
 ****************************************************************************
 */

/*
 ****************************************************************************
 * 3                    INCLUDE FILES
 ****************************************************************************
 */

#include <vxWorks.h>
#include <vx_list.h>
#include <vxAtomicLib.h>

#include <ipcom_cstyle.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 ****************************************************************************
 * 4                    DEFINES
 ****************************************************************************
 */

/* Slab cache flags */
#define VXMUX_SLAB_F_NO_LOCKING (1U << 0) /* Do not lock/unlock the
                                             slab cache in alloc/free
                                             operations. The caller
                                             must make sure that
                                             alloc/free is run by only
                                             one context at any
                                             specific moment in time. Does
                                             not affect garbage collection. */

#define VXMUX_SLAB_F_ZERO       (1U << 1) /* Buffers are cleared before
                                             in ipcom_slab_alloc() */
#define VXMUX_SLAB_F_POISON     (1U << 2) /* Buffer are fill with a
                                             pattern when freed */

#define VXMUX_SLAB_F_AVERAGE    (0U << 30) /* Allocate an average
                                              amount of objects per
                                              slab, this is the
                                              default */
#define VXMUX_SLAB_F_ONE        (1U << 30) /* Allocate one object per
                                              slab, this should only be
                                              used for very big objects
                                              that are used very
                                              seldom */
#define VXMUX_SLAB_F_FEW        (2U << 30) /* Allocate just a few
                                              objects per slab */
#define VXMUX_SLAB_F_MANY       (3U << 30) /* Allocate a large amount
                                              of objects, use this for
                                              objects that are
                                              performance critical and
                                              used in great numbers */



/*
 ****************************************************************************
 * 5                    TYPES
 ****************************************************************************
 */

typedef struct Vxmux_memory_pool_struct
{
    Circ_list         list;  /* node to link into list of pools */
    const char       *name;  /* Human readable name of the memory
                                limit */
    const size_t      limit; /* Maximum number of bytes that can be
                                allocated from this memory pool */
    atomic_t          low;   /* low water mark: the smallest number of bytes
				remaining in this pool at any time so far */
    atomic_t          bytes; /* Bytes left in this pool */
    Circ_list         memory_caches; /* List of all slab caches using
                                        this pool */
}
Vxmux_memory_pool;

/* Incomplete type. Full definition is hidden (see vxmux_slab_h.h) */
typedef struct Vxmux_memory_cache_struct Vxmux_memory_cache;


/*
 *===========================================================================
 *                     Vxmux_slab_ctor
 *===========================================================================
 * Description: Constructor for slab objects. Is run once per object when
 *              objects are added to the memory cache.
 * Parameters:  mc - The slab cache the object is going to be part of.
 *              obj - The object to initialize.
 * Returns:     IP_TRUE - the object was initialized successfully
 *              IP_FALSE - the initialization failed, this will make the
 *                         adding any object to the slab cache fail.
 */
typedef BOOL (*Vxmux_slab_ctor)(Vxmux_memory_cache *mc, void *obj);


/*
 *===========================================================================
 *                     Vxmux_slab_dtor
 *===========================================================================
 * Description: Destructor for slab objects. Is run once per object when
 *              objects are removed from the memory cache.
 * Parameters:  mc - The slab cache the object was part of.
 *              obj - The object to destroy.
 * Returns:
 */
typedef void (*Vxmux_slab_dtor)(Vxmux_memory_cache *mc, void *obj);


/*
 ****************************************************************************
 * 6                    PUBLIC FUNCTIONS
 ****************************************************************************
 */

/*
 *===========================================================================
 *                       vxmux_memory_pool_new
 *===========================================================================
 * Description: Allocates a new memory pool. The slab caches uses a
 *              specific memory pool will in total never exceed the
 *              limit of the pool
 * Parameters:  name - User defined memory pool name.
 *              limit - Maximum number of bytes that can be allocated
 *                       from this pool.
 * Returns:     A newly created memory pool.
 *
 */
IP_PUBLIC Vxmux_memory_pool *
vxmux_memory_pool_new(const char *name, size_t limit);


/*
 *===========================================================================
 *                       vxmux_slab_cache_new
 *===========================================================================
 * Description: Creates a new memory cache
 * Parameters:  name - User defined name if the cache
 *              flags - VXMUX_SLAB_F_xxx flags.
 *              lock - pointer to spinlock used by this cache
 *                     (type depends upon _WRS_CONFIG_DETERMINISTIC)
 *              obj_size - size of the objects stored in this
 *              obj_alignment - minimal alignment of objects returned
 *                       from this slab cache
 *              ctor - Constructor for objects added to this slab.
 *              dtor - Desctructor for objects deleted from this slab.
 *              memory_pool - a memory pool from which this slab cache
 *                       will allocate its memory
 * Returns:     The newly create slab cache object.
 *
 */
IP_PUBLIC Vxmux_memory_cache *
vxmux_slab_cache_new(const char *name,
                     uint32_t flags,
                     void * lock,
                     size_t obj_size,
                     size_t obj_alignment,
                     Vxmux_slab_ctor ctor,
                     Vxmux_slab_dtor dtor,
                     Vxmux_memory_pool *memory_pool);


/*
 *===========================================================================
 *                       vxmux_slab_add
 *===========================================================================
 * Description: Allocates a new slab for a memory cache. Returns the new
 *              slab, does not actually add it to the memory cache.
 * Parameters:  mc - memory cache the slab can be added to.
 * Returns:     A pointer to the new slab to be added, or IP_NULL if
 *              allocation fails.
 *
 */
IP_PUBLIC void *
vxmux_slab_add(Vxmux_memory_cache *mc);


/*
 *===========================================================================
 *                       vxmux_slab_alloc_try
 *===========================================================================
 * Description: Allocates an object from the slab cache
 * Parameters:  mc - slab cache to allocate from.
 *              retry - if true, attempt to allocate more memory
 *                      from underlying pool if initial allocation attempt
 *                      fails.
 * Returns:     The newly created object or IP_NULL if out of memory.
 *
 */
IP_PUBLIC void *
vxmux_slab_alloc_try(Vxmux_memory_cache *mc, BOOL retry);


/*
 *===========================================================================
 *                       vxmux_slab_alloc
 *===========================================================================
 * Description: Allocates an object from the slab cache, retrying if necessary
 * Parameters:  mc - slab cache to allocate from.
 * Returns:     The newly created object or IP_NULL if out of memory.
 *
 */
IP_INLINE void *
vxmux_slab_alloc(Vxmux_memory_cache *mc)
{
    return vxmux_slab_alloc_try (mc, TRUE);
}


/*
 *===========================================================================
 *                       vxmux_slab_alloc_from
 *===========================================================================
 * Description: Allocate an object from new slab, add slab to memory cache.
 *              Do not use slab subsequently, it has been added to the cache.
 * Parameters: mc - memory cache to add slab to (minus one object)
 *             slab - new slab returned from vxmux_slab_add()
 * Returns: A pointer to the object allocated out of slab.
 */
IP_PUBLIC void *
vxmux_slab_alloc_from(Vxmux_memory_cache *mc, void * slab);


/*
 *===========================================================================
 *                       vxmux_slab_free
 *===========================================================================
 * Description: Returns an object to a slab cache
 * Parameters:  mc - slab cache to return the object to
 *              obj - the object to free
 * Returns:
 *
 */
IP_PUBLIC void
vxmux_slab_free(Vxmux_memory_cache *mc, void *obj);


/*
 *===========================================================================
 *                     vxmux_slab_get_objects_per_slab
 *===========================================================================
 * Description: Returns the number of objects per slab in the passed slab
 *              cache.
 * Parameters:  mc - a slab cache
 * Returns:     Number of objects per slab
 *
 */
IP_PUBLIC unsigned
vxmux_slab_get_objects_per_slab(Vxmux_memory_cache *mc);

#ifdef __cplusplus
}
#endif

#endif /* VXMUX_SLAB_H */

/*
 ****************************************************************************
 *                      END OF FILE
 ****************************************************************************
 */
