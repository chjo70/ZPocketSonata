/*
 * Copyright (c) 2006-2013 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */
#ifndef IPCOM_NAE_H
#define IPCOM_NAE_H

/*
 ****************************************************************************
 * 1                    DESCRIPTION
 ****************************************************************************
 * This contains definitions and functions that are only used when
 * building a Network Acceleration Engining (NAE) system.
 * A NAE system will also have a number of OS and/or board specific
 * parts as well. One example is that NAE:s might very well run
 * without any kind of interrupts, which means that they are dependent
 * on getting notifications about the current time by some OS and/or
 * board specific mean. The implementation must make sure that
 * ipcom_nae_tick() is called on regular intervals.
 */

/*
 ****************************************************************************
 * 2                    CONFIGURATION
 ****************************************************************************
 */

#include "ipcom_config.h"


/*
 ****************************************************************************
 * 3                    INCLUDE FILES
 ****************************************************************************
 */

#if defined(IPCOM_FORWARDER_NAE)
/*
 * Put everthing within #ifdef IPCOM_FORWARDER_NAE since none of these functions
 * make sens to call in a non NAE environment.
 */

#include <ipcom_cstyle.h>
#include <ipcom_type.h>


#ifdef __cplusplus
extern "C" {
#endif

/*
 ****************************************************************************
 * 4                    DEFINES
 ****************************************************************************
 */
#define NAE_IFSHOW (1)
#define NAE_NEIGHSHOW (2)
#define NAE_FIBSHOW (3)
#define NAE_DSTSHOW (4)
#define NAE_PEERINFOSHOW (5)

/*
 ****************************************************************************
 * 5                    TYPES
 ****************************************************************************
 */

/*
 * Modules can use this structure +
 * ipcom_time_nae_tick_insert_handler() register a function that will
 * be run each time the tick counter changes within a NAE.
 */
struct Ipcom_nae_tick_handler
{
    /*
     * Pointer to the next handler in the list. Leave uninitialized
     * before calling ipcom_time_nae_tick_insert_handler().
     */
    struct Ipcom_nae_tick_handler *next;

    /*
     * Pointer to the function to run each tick.
     */
    void (*action)(void);
};


/*
 ****************************************************************************
 * 6                    FUNCTIONS
 ****************************************************************************
 */

IP_PUBLIC void ipcom_nae_wmb(void);
IP_PUBLIC void ipcom_nae_rmb(void);

IP_PUBLIC Ip_bool ipcom_nae_is_primary(void);
IP_PUBLIC unsigned ipcom_nae_ix(void);

IP_PUBLIC Ip_bool ipcom_nae_is_atomic(Ip_u32 tag);
IP_PUBLIC void ipcom_nae_switch_to_atomic(Ip_u32);
IP_PUBLIC void ipcom_nae_switch_to_ordered(Ip_u32);
IP_PUBLIC void ipcom_nae_switch_to_null(void);

IP_PUBLIC void ipcom_nae_tick(unsigned long ticks, unsigned hz);
IP_PUBLIC void ipcom_nae_tick_get(unsigned long *ticks, unsigned *hz);

IP_PUBLIC int ipcom_nae_get_debug_data(void *debug_data, int max_debug_data_size);
IP_PUBLIC int  ipcom_nae_set_debug_data(int nae, void *debug_data, int debug_data_size);
/*
 * Note: the memory pointer to by 'h' must never be freed
 */
IP_PUBLIC void ipcom_nae_tick_insert_handler(struct Ipcom_nae_tick_handler *h);

#ifndef IP_PORT_UNIX
struct Ipcom_netif_struct;
IP_PUBLIC int ipcom_nae_ioctl(struct Ipcom_netif_struct *netif, Ip_u32 command, void *data);
#endif

typedef void (*Ipcom_func_ptr)(void);
IP_PUBLIC Ipcom_func_ptr ipcom_sym_from_name(const char *sym_name);

#ifdef __cplusplus
}
#endif
#endif /* IPCOM_FORWARDER_NAE */
#endif

/*
 ****************************************************************************
 *                      END OF FILE
 ****************************************************************************
 */
