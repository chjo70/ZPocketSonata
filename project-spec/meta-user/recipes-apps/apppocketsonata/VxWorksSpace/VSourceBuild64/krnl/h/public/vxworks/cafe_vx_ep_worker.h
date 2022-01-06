/* cafe_vx_ep_worker.h - VxWorks-specific worker thread implementation */

/* Copyright (c) 2012 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

#if !defined(__cafe_vx_ep_worker_h)
#define __cafe_vx_ep_worker_h

#include <cafe/ep_worker.h>


#if defined(__cplusplus)
extern "C" {
#endif


extern STATUS vx_ep_worker_priority_set(struct cafe_ep_worker *worker,
					int new_priority);

extern STATUS vx_ep_worker_options_set(struct cafe_ep_worker *worker,
                    int mask, int options);

#if defined(__cplusplus)
}	/* extern "C" */
#endif

#endif  /* if !defined(__cafe_vx_types_h) */
