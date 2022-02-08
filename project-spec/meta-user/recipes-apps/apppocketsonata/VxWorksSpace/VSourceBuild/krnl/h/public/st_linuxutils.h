/* Copyright (c) 2003-2011 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

#if !defined(__st_linuxutils_h)
#define __st_linuxutils_h

#if defined(__cplusplus)
    extern "C" {
#endif


#if defined(__MODULE__)
/**
 * ST_context_convert
 * Public API implementation: Converts the context created by linux kernel to 
 *                            generic REG_SET context
 * Preconditions: pregs != NULL, regs != NULL
 * Returns: none
 */
extern void ST_context_convert(const RTI_pt_regs_p pregs, REG_SET * regs);

#else

#include <st_stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>

#define MAX_MAP_NAME_LENGTH        (256)


typedef struct {
    unsigned long start;
    unsigned long end;
    unsigned long fileOffset;
    bool executable;
    char name[MAX_MAP_NAME_LENGTH];
} MemoryRegion;

typedef struct {
    unsigned int regionCount;
    MemoryRegion * regions;
} MemoryMap;


extern void MemoryRegionPrint(const MemoryRegion * const reg);


extern void MemoryMapPrint(const MemoryMap * const map);


/**
 *  Populates the given MemoryRegion object with the specification
 * beginning at the current read pointer of the given FILE pointer.
 */
extern bool getNextMemoryRegion(FILE * f, MemoryRegion * r);


/**
 *  Populate the given MemoryMap with data corresponding to the current
 * process.  If it was previously populated, the MemoryMap object passed
 * should be deleted with MemoryMapDestroy() before calling this function to
 * avoid memory leaks.
 */
extern bool getSelfMap(MemoryMap * const map);


/**
 *  Discover which region within a given memory map contains the requested
 * address.  Returns a pointer to the appropriate region object if found,
 * and 0 if the address doesn not belong to a region in this map.
 */
extern MemoryRegion * MemoryMapFindAddress(const MemoryMap * const map,
                                           const unsigned long address);


/**
 *  Free all memory associated with a MemoryMap object.
 */
extern void MemoryMapDestroy(MemoryMap * map);


extern unsigned int MemoryMapCountRegions(FILE * f);


static inline
unsigned long ST_get_thread_id(void)
{
    return syscall(__NR_gettid);
}
#endif  /* if defined(__MODULE__) */


#if defined(__cplusplus)
    }	/* extern "C" */
#endif

#endif  /* if !defined(__st_linuxutils_h) */
