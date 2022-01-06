/* timerstamp_normalizer - normalize timestamp values w.r.t clock rollovers */

/*
 * Copyright (c) 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

#ifndef INCtimestamp_normalizer_h
#define INCtimestamp_normalizer_h

#ifdef __cplusplus
extern "C" {
#endif

extern void cafe_timestamp_normalizer_ep_unregister(void);
extern int cafe_timestamp_normalizer_ep_register(void);

#ifdef __cplusplus
}
#endif	/* __cplusplus */

#endif	/* INCtimestamp_normalizer_h */
