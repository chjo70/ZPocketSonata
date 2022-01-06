/* st_vxutils.h - VxWorks-specific utility routines */

/* Copyright (c) 2010, 2014-2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
16jan15,wzc  ppc64 support.(US49903)
*/

#if !defined(__st_vxutils_h)
#define __st_vxutils_h

#ifdef __cplusplus
    extern "C" {
#endif

static inline
unsigned long ST_get_thread_id(void)
{
    return (unsigned long)taskIdSelf();
}


#ifdef __cplusplus
    }	/* extern "C" */
#endif

#endif  /* if !defined(__st_vxutils_h) */
