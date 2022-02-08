/* timer_ep - expirable timer event processor */

/*
 * Copyright (c) 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

#ifndef INCtimer_ep_h
#define INCtimer_ep_h

#ifdef __cplusplus
extern "C" {
#endif

#define TIMER_DEF	"S[cafe_timer.timer]"
#define TIMER_REF	"t[cafe_timer.timer]"

#define TIMER_SET_INTERVAL_DEF	"S[cafe_timer.set_interval,v[interval,q]]"
#define TIMER_SET_INTERVAL_REF	"t[cafe_timer.set_interval]"

#define TIMER_SET_DEBUG_DEF	"S[cafe_timer.set_debug,v[debug,I]]"
#define TIMER_SET_DEBUG_REF	"t[cafe_timer.set_debug]"

#define TIMER_INTERVAL_CHANGED_DEF	"S[cafe_timer.interval_changed,v[interval,q]]"
#define TIMER_INTERVAL_CHANGED_REF	"t[cafe_timer.interval_changed]"

#define TIMER_DEBUG_CHANGED_DEF	"S[cafe_timer.debug_changed,v[debug,I]]"
#define TIMER_DEBUG_CHANGED_REF	"t[cafe_timer.debug_changed]"

extern int cafe_timer_ep_register(void);
extern void cafe_timer_ep_unregister(void);

#ifdef __cplusplus
}
#endif	/* __cplusplus */

#endif	/* INCtimer_ep_h */
