/* realtime_ep - delay replay of events to realtime */

/*
 * Copyright (c) 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

#ifndef INCrealtime_ep_h
#define INCrealtime_ep_h

#ifdef __cplusplus
extern "C" {
#endif

extern int cafe_realtime_ep_register(void);
extern void cafe_realtime_ep_unregister(void);

#ifdef __cplusplus
}
#endif	/* __cplusplus */

#endif	/* INCrealtime_ep_h */
