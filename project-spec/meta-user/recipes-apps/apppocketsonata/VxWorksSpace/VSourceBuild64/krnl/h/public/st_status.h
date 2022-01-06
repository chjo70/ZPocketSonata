/* st_status.h - a head file */

/*
 * Copyright (c) 2014-2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use 
 * of this software may be licensed only pursuant to the terms 
 * of an applicable Wind River license agreement. 
 */

/*
modification history
--------------------
mar15,gxu  Add function for discovering interruption top.(V7COR-2171)
16jan15,wzc  ppc64 support.(US49903)
23dec14,wzc   created
*/

#if !defined(__st_status_h)
#define __st_status_h

/* Return status for stacktrace */
typedef enum {
    ST_CONTEXT_OK,
    ST_CONTEXT_TOP,
    ST_CONTEXT_ERROR,
    ST_CONTEXT_INTERRUPT_TOP,
    ST_CONTEXT_EXCEPTION_TOP,
    ST_CONTEXT_KERNEL_OK,
    ST_CONTEXT_INT_SECONDARY_TOP
} context_status;
  
#endif /* if !defined(__st_status_h) */
