/*
 * Copyright (c) 2006-2013 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */
#ifndef IPNET_TIMEOUT_H
#define IPNET_TIMEOUT_H

/*
 ****************************************************************************
 * 1                    DESCRIPTION
 ****************************************************************************
 * IPNET timeout machinery.
 * Timeouts can not be scheduled from interrupt context.
 * Timeout handlers is always run with the IPNET code lock taken.
 *
 * IPNET soft interrupt machinery.
 * Soft timeouts should be scheduled by code running in interrupt context
 * and have code that what to update the internal state of IPNET.
 * Soft interrupt handlers is always run with the IPNET code lock taken.
 * The only IPNET functions that can safly be called from interrupt context are:
 * - ipnet_schedule_soft_interrupt()
 * - ipcom_pkt_malloc()
 * - ipcom_pkt_free()
 *
 */

/*
 ****************************************************************************
 * 2                    CONFIGURATION
 ****************************************************************************
 */

#include "ipnet_config.h"


/*
 ****************************************************************************
 * 3                    INCLUDE FILES
 ****************************************************************************
 */

#include <ipcom_type.h>
#include <ipcom_cstyle.h>


#ifdef __cplusplus
extern "C" {
#endif

/*
 ****************************************************************************
 * 4                    DEFINES
 ****************************************************************************
 */

/*
 * set/get the timeout structure (if any) used for this fragment
 */
#define IPNET_PKT_GET_TMO_PTR(pkt)     ((Ipnet_timeout **) &(pkt)->link_cookie)
#define IPNET_PKT_GET_TMO(pkt)         ((Ipnet_timeout *) (pkt)->link_cookie)
#define IPNET_PKT_SET_TMO(pkt, timeo)  ((pkt)->link_cookie = (Ip_ptrdiff_t) (timeo))

/*
 * set/get the absolute time (in seconds) when this fragment times out.
 */
#define IPNET_PKT_GET_TIMEOUT(net, pkt)                     \
    (IPNET_PKT_GET_TIMEOUT_ABS(pkt) - ipnet_sec_now(net))
#define IPNET_PKT_GET_TIMEOUT_ABS(pkt)                      \
    ipcom_pkt_get_int(pkt, IPNET_PKT_INFO_TIMEOUT, Ip_u32)
#define IPNET_PKT_SET_TIMEOUT_ABS(pkt, timeo)                       \
    ipcom_pkt_set_int(pkt, IPNET_PKT_INFO_TIMEOUT, timeo, Ip_u32)


/*
 * Evaluates to a pointer where the soft interrupt structure can be stored
 * inside the packet
 */
#define IPNET_PKT_TO_SOFTIRQ_STRUCT(pkt) ((Ipnet_softirq *) ((pkt)->data))


/*
 ****************************************************************************
 * 5                    TYPES
 ****************************************************************************
 */

/* Forward declaration of the stack instance data */
struct Ipnet_data_struct;

/* Signature of timeout handler */
typedef void (*Ipnet_timeout_handler)(void *cookie);

typedef struct Ipnet_timeout_struct
{
    int                           pq_index;  /* The index this timout has in the priority queue */
    Ip_s64                        msec;      /* The absolute time when this timeout is triggered */
    Ipnet_timeout_handler         handler;   /* The function that will be called when
                                                the current time is equal to 'timeout_msec',
                                                this member can be IP_NULL if no action should be taken */
    void                         *cookie;    /* The (user specified) argument to the handler */
    struct Ipnet_timeout_struct **ptmo;      /* Pointer to the location the caller has stored the
                                                Ipnet_timeout handler, that location will be set to
                                                IP_NULL when the timer expires or is cancled. */
    void                         *imp;       /* For internal timer implementation use */
}
Ipnet_timeout;

/* opaque declaration of Ipnet_timeos structure */
struct Ipnet_timeos_struct;

typedef void (*Ipnet_timeos_lock_func)(void);
typedef void (*Ipnet_timeos_unlock_func)(void);
typedef Ip_bool (*Ipnet_timeos_is_locked_func)(void);

/*
 * Per-stack-instance data for a shared timeouts set.
 */
typedef struct Ipnet_timeos_instance_struct
{
    /*
     * The shared timeouts set this instance belongs to.
     */
    struct Ipnet_timeos_struct *timeos;

    /*
     * The per-stack-instance static timeout used to implement
     * the shared timeout set.
     */
    Ipnet_timeout              tmo;
}
Ipnet_timeos_instance;

typedef Ipnet_timeos_instance * (*Ipnet_timeos_per_inst_data_func)(unsigned stack_idx);

/* Signature of soft IRQ handler */
typedef void (*Ipnet_softirq_handler)(void *cookie);

typedef struct Ipnet_softirq_struct
{
    struct Ipnet_softirq_struct *next;    /* Points to the next soft interrupt */
    volatile Ip_bool             pending; /* IP_TRUE if this is currently in the list
                                             of pending soft interrupts */
    Ipnet_softirq_handler        handler; /* The function that will handle this soft interrupt */
    void                        *cookie;  /* The argument to the handler */
}
Ipnet_softirq;

/* Broadcast Jobs */

struct Ipnet_broadcast_job_struct;

typedef void (*Ipnet_broadcast_job_rtn) (struct Ipnet_data_struct *, struct Ipnet_broadcast_job_struct *);

typedef struct Ipnet_broadcast_job_struct
{
    Ipnet_broadcast_job_rtn func;  /* Main handler routine. Must be safe to call concurrently
                                      in multiple network tasks for this job and its data. */
    Ipnet_broadcast_job_rtn free;  /* how to free this job and any associated resources */
    void                  * ptr;   /* data that func can use */
    int                     flags; /* more data that func can use */
    int                     refs;  /* reference count */
}
Ipnet_broadcast_job;


/*
 ****************************************************************************
 * 6                    FUNCTIONS
 ****************************************************************************
 */

IP_GLOBAL void ipnet_softirq_init(Ipnet_softirq *soft_irq);
IP_GLOBAL void ipnet_softirq_schedule(struct Ipnet_data_struct *net,
                                      Ipnet_softirq *soft_irq,
                                      Ipnet_softirq_handler handler,
                                      void *cookie);

IP_GLOBAL void ipnet_timeout_cancel(Ipnet_timeout *tmo);
IP_GLOBAL int ipnet_timeout_schedule(struct Ipnet_data_struct *net,
                                     Ip_s64 msec_to_timeout,
                                     Ipnet_timeout_handler handler,
                                     void *cookie,
                                     Ipnet_timeout **ptmo);

IP_GLOBAL int ipnet_shared_timeout_schedule(struct Ipnet_data_struct *net,
                                            Ip_s64 msec_to_timeout,
                                            Ipnet_timeout_handler handler,
                                            void *cookie,
                                            Ipnet_timeout **ptmo);

IP_GLOBAL Ip_s64 ipnet_timeout_msec_until(struct Ipnet_data_struct *net,
                                          Ipnet_timeout *tmo);
IP_GLOBAL Ip_s64 ipnet_msec_now(struct Ipnet_data_struct *net);
IP_GLOBAL Ip_u32 ipnet_sec_now(struct Ipnet_data_struct *net);
IP_GLOBAL Ip_s64 ipnet_fetch_msec_now(void);

#ifdef IPNET_DEBUG
typedef int (*Ipnet_timeout_to_string_f)(void *tmo_elem, char *buf, Ip_size_t buf_len);
typedef struct Ipnet_cmd_tmo_handler_to_str_struct
{
    Ipnet_timeout_handler     key;
    Ipnet_timeout_to_string_f to_str_func;
}
Ipnet_cmd_tmo_handler_to_str;

IP_GLOBAL Ipnet_timeout_to_string_f ipnet_timeout_handler_to_string(Ipnet_timeout_handler handler);
IP_GLOBAL void   ipnet_timeout_to_string(Ipnet_timeout_handler handler,
                                         Ipnet_timeout_to_string_f to_str);
#endif


/*
 *===========================================================================
 *                     NEW 'STATIC' TIMEOUTS ROUTINES
 *===========================================================================
 *
 */

IP_INLINE void
ipnet_shared_static_timeout_init(Ipnet_timeout *tmo, 
                                 Ipnet_timeout_handler handler,
                                 void *cookie,
                                 struct Ipnet_timeos_struct *timeos)
{
    ip_assert(handler != IP_NULL);
    tmo->handler = handler;
    tmo->cookie  = cookie;
    tmo->pq_index = 0;
    tmo->ptmo = IP_NULL;
    tmo->imp = timeos;
}


IP_INLINE void
ipnet_per_inst_static_timeout_init(Ipnet_timeout *tmo, 
                                   Ipnet_timeout_handler handler,
                                   struct Ipnet_data_struct *net)
{
    ip_assert(handler != IP_NULL);
    tmo->handler = handler;
    tmo->cookie  = tmo;  /* (tmo->cookie == tmo) marks this as a static timeout */
    tmo->pq_index = 0;
    tmo->ptmo = IP_NULL;
    tmo->imp = net;
}


IP_GLOBAL void ipnet_static_timeout_reschedule(Ip_s64 msec_to_timeout,
                                               Ipnet_timeout *tmo);
IP_GLOBAL Ip_bool ipnet_static_timeout_cancel(Ipnet_timeout *tmo);

#ifdef IP_DEBUG
#define IPNET_TIMEOS_CREATE(lock, unlock, is_locked, per_inst, name)       \
    (ipnet_timeos_create_dbg((lock), (unlock), (is_locked), (per_inst), (name)))

IP_GLOBAL struct Ipnet_timeos_struct * ipnet_timeos_create_dbg(Ipnet_timeos_lock_func lock,
                                                               Ipnet_timeos_unlock_func unlock,
                                                               Ipnet_timeos_is_locked_func is_locked,
                                                               Ipnet_timeos_per_inst_data_func per_inst,
                                                               const char *tmo_cache_name);
#else
#define IPNET_TIMEOS_CREATE(lock, unlock, is_locked, per_inst, name)       \
    (ipnet_timeos_create((lock), (unlock), (per_inst), (name)))

IP_GLOBAL struct Ipnet_timeos_struct * ipnet_timeos_create(Ipnet_timeos_lock_func lock,
                                                           Ipnet_timeos_unlock_func unlock,
                                                           Ipnet_timeos_per_inst_data_func per_inst,
                                                           const char *tmo_cache_name);
#endif

IP_GLOBAL void ipnet_shared_static_tmo_reschedule(struct Ipnet_data_struct *net,
                                                  Ip_s64         msec_to_timeout,
                                                  Ipnet_timeout *tmo);
IP_GLOBAL Ip_bool ipnet_shared_static_tmo_cancel(Ipnet_timeout *tmo);

IP_GLOBAL int ipnet_shared_dyn_tmo_schedule(struct Ipnet_timeos_struct *timeos,
                                            struct Ipnet_data_struct *net,
                                            Ip_s64 msec_to_timeout,
                                            Ipnet_timeout_handler handler,
                                            void *cookie,
                                            Ipnet_timeout **ptmo);
IP_GLOBAL Ip_bool ipnet_shared_dyn_tmo_cancel(Ipnet_timeout *tmo);

IP_INLINE void
ipnet_shared_timeout_cancel(Ipnet_timeout *tmo)
{
    (void)ipnet_shared_dyn_tmo_cancel(tmo);
}

/* broadcast jobs */

IP_GLOBAL void ipnet_job_broadcast(Ipnet_broadcast_job *job);

IP_GLOBAL void ipnet_pkt_broadcast_job(Ipcom_pkt * pkt,
                                       Ipnet_broadcast_job_rtn func,
                                       Ipnet_broadcast_job_rtn free,
                                       int  flags);
IP_GLOBAL void ipnet_pkt_broadcast_job_free(struct Ipnet_data_struct * net,
                                            Ipnet_broadcast_job * job);


#ifdef __cplusplus
}
#endif

#endif

/*
 ****************************************************************************
 *                      END OF FILE
 ****************************************************************************
 */
