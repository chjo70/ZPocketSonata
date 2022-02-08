/* cafe_vx_timestamp.h - */

/*
 * Copyright (c) 2010-2012 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */


#ifndef __cafe_vx_timestamph
#define __cafe_vx_timestamph

#ifdef __cplusplus
extern "C" {
#endif

extern int cafe_vx_timestamp64(unsigned long long *t);

extern int cafe_vx_timestamp_freq64(unsigned long long *f);

extern STATUS cafe_vx_timestamp_init(void);

#ifdef __cplusplus
}
#endif


#endif /* __cafe_vx_timestamph */
