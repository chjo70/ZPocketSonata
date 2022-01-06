/*
 * Copyright (c) 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

 
/* THIS IS GENERATED CODE. DO NOT MODIFY */

#ifndef INCcafe_timer_types_h
#define INCcafe_timer_types_h

#ifdef __cplusplus
extern "C" {
#endif
#define CAFE_TIMER___TIMER_VT_DEF "S[cafe_timer.timer]"
#define CAFE_TIMER___TIMER_VT_REF "t[cafe_timer.timer]"

#define CAFE_TIMER___INTERVAL_CHANGED_VT_DEF "S[cafe_timer.interval_changed,v[interval,q]]"
#define CAFE_TIMER___INTERVAL_CHANGED_VT_REF "t[cafe_timer.interval_changed]"



#define CAFE_TIMER___ALL_TYPE_DEFS \
    CAFE_TIMER___TIMER_VT_DEF \
    CAFE_TIMER___INTERVAL_CHANGED_VT_DEF

#define CAFE_TIMER___ALL_TYPE_REFS \
    CAFE_TIMER___TIMER_VT_REF \
    CAFE_TIMER___INTERVAL_CHANGED_VT_REF

#ifndef CAFE_TIMER___TIMER_STRUCT_DEF
#define CAFE_TIMER___TIMER_STRUCT_DEF
struct cafe_timer___timer;
#endif /* CAFE_TIMER___TIMER_STRUCT_DEF */

#ifndef CAFE_TIMER___INTERVAL_CHANGED_STRUCT_DEF
#define CAFE_TIMER___INTERVAL_CHANGED_STRUCT_DEF
struct cafe_timer___interval_changed {
    long long interval; 
};
#endif /* CAFE_TIMER___INTERVAL_CHANGED_STRUCT_DEF */

#ifdef __cplusplus
}
#endif	/* __cplusplus */

#endif /* INCcafe_timer_types_h */
