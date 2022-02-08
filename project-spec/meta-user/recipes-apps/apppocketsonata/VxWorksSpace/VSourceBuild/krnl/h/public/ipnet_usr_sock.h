/*
 * Copyright (c) 2006-2016 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
12mar16,wfl  Port TSR defect fix forward from vxworks6.9 into vx7. (F6988)
23feb16,dlk  Don't clear EINTR socket error set by IP_X_SIOCSINTR ioctl
             (V7NET-769)
*/


#ifndef IPNET_USR_SOCK_H
#define IPNET_USR_SOCK_H

/*
 ****************************************************************************
 * 1                    DESCRIPTION
 ****************************************************************************
 *
 * The user socket module handles the calls from the user-land socket
 * applications and dispatches them to the proper network stack
 * daemon.
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

#include <ipcom_cstyle.h>
#include <ipcom_pipe.h>
#include <ipcom_type.h>

#include "ipnet_h.h"
#include "ipnet_signal.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 ****************************************************************************
 * 4                    DEFINES
 ****************************************************************************
 */
 
#define IPNET_MIN_RCVBUF_SIZE 2000
#ifdef IP_PORT_OSE5
#define IPNET_MIN_SNDBUF_SIZE 2000
#else
#define IPNET_MIN_SNDBUF_SIZE 3000
#endif

#ifdef IP_PORT_LKM
/* Linux always doubles the socket buffer value */
#define IPNET_SOCKBUF_MULTIPLIER 2
#else
#define IPNET_SOCKBUF_MULTIPLIER 1
#endif
/*
 ****************************************************************************
 * 5                    TYPES
 ****************************************************************************
 */

/*
 ****************************************************************************
 * 6                    FUNCTIONS
 ****************************************************************************
 */

IP_GLOBAL Ip_err ipnet_usr_sock_init(void);
IP_GLOBAL void ipnet_usr_sock_get_ops(Ipnet_sock_ops *ops);
IP_GLOBAL Ipnet_socket * ipnet_get_sock(int fd);
IP_GLOBAL void ipnet_release_sock(Ipnet_socket *sock);
IP_GLOBAL void ipnet_usr_sock_free_remote(Ipnet_socket *sock);
IP_GLOBAL Ipcom_pipe *ipnet_usr_sock_get_pipe(int stack_instance_idx);
IP_GLOBAL Ipcom_pipe *ipnet_usr_sock_get_response_pipe(void);
IP_GLOBAL void ipnet_usr_sock_init_sig(int stack_instance_idx,
                                       Ipnet_sig *sig,
                                       enum Ipnet_sig_type sig_type);
IP_GLOBAL volatile int *ipnet_usr_sock_get_route_cache_id(void);
IP_GLOBAL void ipnet_usr_sock_poll_free(Ipnet_sig *poll_sig);
IP_GLOBAL int ipnet_usr_sock_wait_until_writable(Ipnet_socket *sock,
                                                 int lowat,
                                                 struct Ip_timeval *timeout);
IP_GLOBAL int ipnet_usr_sock_recvmsg(Ipnet_socket *sock,
                                     struct Ip_msghdr *msg,
                                     int flags);
IP_GLOBAL void ipnet_shutdown_stack(void);

/*
 * Handler for all the socket API system calls, the following
 * function can only be called by the stack daemon process or by the
 * NAE when built IPCOM_FORWARDER_NAE defined.
 */
IP_GLOBAL int ipnet_sys_accept(Ip_fd fd,
                               struct Ip_sockaddr *name,
                               Ip_socklen_t *namelen);
IP_GLOBAL int ipnet_sys_bind(Ip_fd fd,
                             IP_CONST struct Ip_sockaddr *name,
                             Ip_socklen_t namelen);
IP_GLOBAL int ipnet_sys_connect(Ip_fd fd,
                                IP_CONST struct Ip_sockaddr *to,
                                Ip_socklen_t tolen);
IP_GLOBAL int ipnet_sys_get_ancillary_data(Ipnet_sig *sig);
IP_GLOBAL int ipnet_sys_getname(Ip_fd fd,
                                struct Ip_sockaddr *name,
                                Ip_socklen_t *namelenp,
                                Ip_bool local);
IP_GLOBAL int ipnet_sys_getsockopt(Ip_fd fd,
                                   int level,
                                   int optname,
                                   void *optval,
                                   Ip_socklen_t *optlen);
IP_GLOBAL int ipnet_sys_listen(Ip_fd fd,
                               int backlog);
IP_GLOBAL void ipnet_sys_poll(struct Ipnet_data_struct *net, Ipnet_sig *sig);
IP_GLOBAL void ipnet_sys_poll_async(Ipnet_sig *sig);
IP_GLOBAL Ip_ssize_t ipnet_sys_sendmsg(struct Ipnet_data_struct *net,
                                       Ip_fd fd,
                                       IP_CONST struct Ip_msghdr *msg,
                                       Ipcom_pkt *pkt);
IP_GLOBAL int ipnet_sys_setsockopt(Ip_fd fd,
                                   int level,
                                   int optname,
                                   IP_CONST void *optval,
                                   Ip_socklen_t optlen);
IP_GLOBAL int ipnet_sys_shutdown(Ip_fd fd,
                                 int how,
                                 Ip_bool from_user_signal);
IP_GLOBAL int ipnet_sys_socketclose(Ip_fd fd);
IP_GLOBAL int ipnet_sys_socket(struct Ipnet_data_struct *net,
                               int domain,
                               int type,
                               int protocol,
                               Ip_bool user_context);
IP_GLOBAL int ipnet_sys_socketioctl(Ip_fd fd,
                                    Ip_bool check_update,
                                    unsigned long request,
                                    void *argp);
IP_GLOBAL int ipnet_sys_sysctl(struct Ipnet_sig_sysctl *sig_sysctl);

IP_GLOBAL int ipnet_sys_if_attach(Ipcom_netif *ipcomif);
IP_GLOBAL int ipnet_sys_if_detach(Ipcom_netif *ipcomif);
IP_GLOBAL int ipnet_sys_if_free(Ipcom_netif *ipcomif);
IP_GLOBAL Ipcom_netif *ipnet_sys_if_malloc(Ip_u16 type);
IP_GLOBAL void ipnet_sys_if_indexname(struct Ipnet_data_struct *net, Ipnet_sig *sig);
IP_GLOBAL void ipnet_sys_if_nametonetif(Ipnet_sig *sig);
IP_PUBLIC void ipcom_if_changelinkaddr(Ipcom_netif *ipcomif,
                                       Ip_u8 *lladdr,
                                       Ip_u16 lladdr_sz);
IP_GLOBAL void ipnet_sys_if_changename(Ipcom_netif *ipcomif,
                                       const char *new_name);
IP_GLOBAL void ipnet_sys_if_changemtu(Ipcom_netif *ipcomif,
                                     Ip_u32 new_mtu);
IP_GLOBAL void ipnet_sys_if_changelinkaddr(Ipcom_netif *ipcomif,
                                           Ip_u8 *lladdr,
                                           Ip_u16 size);
IP_GLOBAL void ipnet_sys_poll_cancel_timeout(Ipnet_sig *poll_sig);
IP_GLOBAL void ipnet_sock_init(void);

IP_GLOBAL Ip_bool ipnet_socketioctl_write_suspend(unsigned long request);

#ifdef IPCOM_FORWARDER_NAE
IP_GLOBAL int ipnet_sock_set_nae_ctx(Ip_fd fd, void *ctx);
IP_GLOBAL int ipnet_sock_set_nae_rx_action(Ip_fd fd,
                                           const char *nae_rx_action);
IP_GLOBAL int ipnet_sock_set_nae_rx_notifier(Ip_fd fd,
                                             const char *nae_rx_notifier);
IP_GLOBAL int ipnet_sock_set_nae_child_rx_action(Ip_fd fd,
                                                 const char *nae_rx_action);
IP_GLOBAL void ipnet_sock_rx_action(Ipnet_socket *sock, Ipcom_pkt *pkt);
IP_GLOBAL void ipnet_sock_rx_notifier(Ipnet_socket *sock, Ipcom_pkt *pkt);
#endif

#ifdef __cplusplus
}
#endif

#endif

/*
 ****************************************************************************
 *                      END OF FILE
 ****************************************************************************
 */
