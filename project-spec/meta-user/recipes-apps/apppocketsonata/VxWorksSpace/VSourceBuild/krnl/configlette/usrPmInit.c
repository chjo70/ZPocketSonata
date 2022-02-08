/* usrPmInit.c - ED&R pmLib configurable initialization */

/*
 * Copyright (c) 2003-2005, 2009-2011, 2014-2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
18feb15,rr   Updated to use VM_PAGE_SIZE_GET() only for MMU systems(V7COR-2398).
20oct14,pcs  Updated to use pmapGlobalMap() instead of adrSpacePageAlloc()
             (V7COR-1717).
13aug14,wap  Fix V7COR-1497, correct compiler warning
18jan11,cww  Fix compiler warning
10jan11,zl   remove pmDefaultAddr from text segment (WIND00247975).
29mar10,cww  LP64 adaptation
07dec09,pcs  For 64bit vxWorks temporarily allocate the memory required
             for the persistant memory from the heap.
03jun09,pcs  Updated to add support for LP64 data model.
19aug05,md   emit error if PM_RESERVED_MEM is zero
17aug04,md   use VM_PAGE_SIZE macro to get page size
14may04,md   make arena location and size be on a page boundary
10sep03,aim  reorderd layout to be: K|URM|PM layout
10sep03,aim  updated to use PM_RESERVED_MEM
05aug03,dbs  allow more than one PM arena
04aug03,dbs  written
*/

/*
DESCRIPTION

This module provides the default arena for pmLib. The arena is the memory space
from which pmLib can carve out 'regions'. A region is the unit of memory
consumed by clients of pmLib, for example ED&R or WindView use a region each to
store their persistent data.

All the pmLib public APIs require an arena definition as their first argument,
and this module provides a default arena definition, placed in PM_RESERVED_MEM
space, above the main kernel memory space.

An arena definition is simply a function, as defined in pmLib.h, which returns
the start address of an arena. It must also take a pointer to a size_t as its
only argument, and if that argument is non-NULL, it should write the size of
the arena to the variable pointed to by that argument.

To use a different default PM arena, the definition of the function
'pmDefaultArena' must be changed, in this file.

To use multiple arenas within the same system, each 'client' must ensure that
pmInit() is called for their arena of choice.

To share a single arena between multiple clients, at least one of them must
call pmInit() on the arena, with the same arena-definition argument -- calling
pmInit() more than once for the same arena is perfectly safe, and has no
side-effects.
*/

#include <vxWorks.h>
#include <stdlib.h>
#include <memLib.h>
#include <pmLib.h>

#ifdef _WRS_CONFIG_USE_MEMDESC
#include <sysLib.h>			/* sysMemDescGet */
#include <vmLib.h>
#include <pmapLib.h>
#include <private/pmapLibP.h>	
#endif

/* ensure we have defined some memory if pmLib is included */

#if (PM_RESERVED_MEM == 0)
# error Persistent memory size is zero!  \
	Please set the "PM_RESERVED_MEM" parameter to a value greater than zero.
#endif

#ifdef _WRS_CONFIG_USE_MEMDESC
/*
 * pmDefaultAddr contains the virtual address of the default PM arena. 
 * Note that this variable is not protected, and therefore it may get
 * corrupted. However this is not weaker than the implementation that is 
 * based on sysMemTop(), which caches an address value in a static
 * variable, <memTop> (see also WIND00247975).
 */

LOCAL void * pmDefaultAddr = NULL;

/* local prototypes */

LOCAL STATUS pmDefaultArenaInit (void);

#endif /* _WRS_CONFIG_USE_MEMDESC */

/**************************************************************************
*
* usrPmInit - pulls pmLib into the build
*
* Since pmLib is entirely 'stateless' it does not need an explicit
* initialization routine, but this function (along with pmLibInit())
* serves to ensure that pmLib gets linked into the system image when
* the macro INCLUDE_EDR_PM is defined.
*
* If _WRS_CONFIG_USE_MEMDESC is defined, this routine also initializes the
* default PM arena.
*
* SEE ALSO: usrConfig.c
*
* NOMANUAL
*/
void usrPmInit (void)
    {
    pmLibInit ();

#ifdef _WRS_CONFIG_USE_MEMDESC
    if (pmDefaultArenaInit () == ERROR)
	strcat (sysExcMsg, "usrPmInit: pmDefaultArenaInit() failed\n");
#endif
    }

#ifdef _WRS_CONFIG_USE_MEMDESC
/**************************************************************************
*
* pmDefaultArenaInit - initializes the default PM arena in PM_RESERVED_MEM
*
* This routine reads the memory descriptors from the BSP and populates
* pmDefaultAddr.
*
* NOMANUAL
*/

LOCAL STATUS pmDefaultArenaInit (void)
    {
    PHYS_MEM_DESC	memDesc;
    void *		virtAddr;
    PHYS_ADDR		physAddr;
#ifndef _WRS_CONFIG_MMULESS_KERNEL
    size_t		pageSize;
#endif
    size_t		numBytes;
   
    /* only 1 PM descriptor is currently supported */

    if (sysMemDescGet (MEM_DESC_PM_RAM, 0, &memDesc) != ERROR)
	{
#ifndef _WRS_CONFIG_MMULESS_KERNEL
        pageSize = VM_PAGE_SIZE_GET();
        numBytes = ROUND_DOWN (memDesc.physicalAddr + memDesc.len, pageSize) -
                   ROUND_UP (memDesc.physicalAddr, pageSize);
        physAddr = ADDR_ROUND_UP (memDesc.physicalAddr, pageSize);
#else
        numBytes = memDesc.len;
        physAddr = memDesc.physicalAddr;
#endif
        virtAddr = pmapGlobalMap (physAddr, numBytes, (memDesc.initialState &
                                  memDesc.initialStateMask));
        if (virtAddr != PMAP_FAILED)
            {
	    /* Update default PM arena addr */

	    pmDefaultAddr = virtAddr;

	    return (OK);
	    }
	}

    return (ERROR);
    }
#endif

/**************************************************************************
*
* pmDefaultArena - defines the default PM arena in PM_RESERVED_MEM
*
* The arena is located directly above sysMemTop and any USER_RESERVED_MEM.
* We ensure the arena is page aligned and a multiple of a page size.  If
* there isn't enough memory to do the page alignment, the region is deemed
* to be unusable and a size of zero is returned.
*
* NOMANUAL
*/

void * pmDefaultArena
    (
    size_t * pSize
    )
    {
#ifdef _WRS_CONFIG_USE_MEMDESC

    if (pSize != NULL)
	*pSize = PM_RESERVED_MEM;
    return pmDefaultAddr;

#else /* !_WRS_CONFIG_USE_MEMDESC */

    volatile size_t size;
    unsigned long   addr;

    /* location of arena */

    addr = (unsigned long) sysMemTop () + USER_RESERVED_MEM;
    size = PM_RESERVED_MEM;

    /* ensure we have at least one page to work with */

    if (size < VM_PAGE_SIZE)
	{
	size = 0;
	addr = 0;
	}
    else
	{
	long frag;

	/* align the start of the buffer to the next highest page boundary */

	if ((frag = addr % VM_PAGE_SIZE) != 0)
	    {
	    frag = VM_PAGE_SIZE - frag;
	    addr += frag;
	    }

	/* adjust size and account for failure if too small */

	if ((size -= frag) < VM_PAGE_SIZE)
	    {
	    size = 0;
	    addr = 0;
	    }
	else
	    {
	    /* round size to the lowest page multiple */

	    size = (size / VM_PAGE_SIZE) * VM_PAGE_SIZE;
	    }
	}

    /* return size if requested */

    if (pSize != NULL)
	*pSize = size;
    
    return ((void *) addr);
#endif /* _WRS_CONFIG_USE_MEMDESC */
    }
