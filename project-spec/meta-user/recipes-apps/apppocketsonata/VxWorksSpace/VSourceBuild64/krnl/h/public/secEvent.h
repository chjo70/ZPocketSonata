/*secEvent.h  - Security Event Handler */

/*
 * Copyright (c) 2016 - 2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement. 
 */
 
/*
modification history
--------------------
31jul17,ljl  Add typedef SEC_EVENT_OPS (V7SEC-447)
15mar16,ljl  Written
*/

/*
DESCRIPTION:
The changes to this CORE_KERNEL provided header file should be kept to 
an absolute minimum to prevent up-leveling the version of the CORE_KERNEL 
layer due to a change/improvement to the security event handler functionality.
*/

#ifndef __INCsecEventh
#define __INCsecEventh

#include <vsbConfig.h>

#ifdef __cplusplus
extern "C" {
#endif

/* defines */
extern void secEventCoreInject
    (
    unsigned int eventId, /* security violation event ID */
    void *    arg1,
    void *    arg2,
    void *    arg3,
    void *    arg4,
    void *    arg5,
    void *    arg6 
    );

#define SEC_NUM_ARGS_(_0, _1, _2, _3, _4, _5, _6, _7, ...) _7

#define SEC_NUM_ARGS(...)                                     \
       SEC_NUM_ARGS_(__VA_ARGS__, 7, 6, 5, 4, 3, 2, 1, 0)

#define _SEC_EVENT_INJECT_ARGS_1(NAME, eventId)                      \
       eventId, NAME ## _default_arg(), NAME ## _default_arg(),     \
       NAME ## _default_arg(), NAME ## _default_arg(),                     \
       NAME ## _default_arg(), NAME ## _default_arg()
       
#define _SEC_EVENT_INJECT_ARGS_2(NAME, eventId, a)                   \
       eventId, a, NAME ## _default_arg(),                          \
       NAME ## _default_arg(), NAME ## _default_arg(),                     \
       NAME ## _default_arg(), NAME ## _default_arg()

#define _SEC_EVENT_INJECT_ARGS_3(NAME, eventId, a, b)                \
       eventId, a, b, NAME ## _default_arg(),                       \
       NAME ## _default_arg(), NAME ## _default_arg(),                     \
       NAME ## _default_arg()

#define _SEC_EVENT_INJECT_ARGS_4(NAME, eventId, a, b, c)             \
       eventId, a, b, c, NAME ## _default_arg(),                    \
       NAME ## _default_arg(), NAME ## _default_arg()

#define _SEC_EVENT_INJECT_ARGS_5(NAME, eventId, a, b, c, d)          \
       eventId, a, b, c, d, NAME ## _default_arg(),                 \
       NAME ## _default_arg()

#define _SEC_EVENT_INJECT_ARGS_6(NAME, eventId, a, b, c, d, e)             \
       eventId, a, b, c, d, e, NAME ## _default_arg()

#define _SEC_EVENT_INJECT_ARGS_7(NAME, eventId, a, b, c, d, e, f)    \
       eventId, a, b, c, d, e, f


#define __SEC_EVENT_INJECT_ARGS(NAME, N, ...)                        \
       _SEC_EVENT_INJECT_ARGS_ ## N (NAME, __VA_ARGS__) 
 
#define _SEC_EVENT_INJECT_ARGS(NAME, N, ...)                         \
       __SEC_EVENT_INJECT_ARGS(NAME, N, __VA_ARGS__)

#define SEC_EVENT_INJECT_ARGS(NAME, ...)                             \
       NAME(_SEC_EVENT_INJECT_ARGS(NAME, SEC_NUM_ARGS(__VA_ARGS__),        \
       __VA_ARGS__))


#ifdef _WRS_CONFIG_SEC_EVENT
#define SEC_EVENT_INJECT(...)                                        \
       SEC_EVENT_INJECT_ARGS(secEventCoreInject, __VA_ARGS__)
#else
#define SEC_EVENT_INJECT(...) ((void)0)
#endif

/* inlined function to provide default argument when none is specified */
static __inline__ void * secEventCoreInject_default_arg (void) 
    {
    return (void*)0;
    }

#ifdef _WRS_CONFIG_SEC_EVENT
typedef struct
    {
    void (*secEventInjectFunc)
        (
        unsigned int eventId, /* security violation event ID */
        void *    arg1,
        void *    arg2,
        void *    arg3,
        void *    arg4,
        void *    arg5,
        void *    arg6
        );
    } SEC_EVENT_OPS;
#endif

#ifdef __cplusplus
}
#endif

#endif /* __INCsecEventh */
