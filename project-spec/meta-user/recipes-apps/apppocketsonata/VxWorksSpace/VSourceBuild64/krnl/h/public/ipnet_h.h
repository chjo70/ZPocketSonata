/*
 * Copyright (c) 2014-2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01aug17,dlk  Change interpretation of transient_err in Ipnet_pkt_result (F5593)
15jun17,xxy  TSN streams integration into the network stack (F9049).
18aug16,ljl  Add a configure option for ipv4 random id. (V7NET-898)
15aug16,wfl  Fixing can not show ipv6 default route via "ndp -r" (V7NET-908)
06jun16,rjq  Port TSR defect fix forward from vxworks6.9 into vx7. (F6988)
27apr16,rjq  Support ipnet strict mode. (US77183)
23feb16,dlk  Don't clear EINTR socket error set by IP_X_SIOCSINTR ioctl (V7NET-769)
16feb16,wfl  Support bind() of AF_PACKET for (V7NET-764)
02feb16,h_l  Add IEEE1588 timestamp support.
30jun15,h_x  Support asynchronous processing in ipcom_sendmsg() (US60556/V7NET-572)
26mar15,rjq  Fix low performance when sending big UDP packet.
31dec14,zan  ROHC multi instance support
24dec14,zan  Add timeos for ipipsec.
18dec14,rjq  SCTP supported in SMP. (US49491)
09dec14,zan  Add ipsec_input and ipsec_output statistics
15sep14,rjq  Enable firewall support in multiple-instance network stack. (US41480)
10feb14,tlu  Add EPOLL socket updates
*/


#ifndef IPNET_H_H
#define IPNET_H_H

/*
 ****************************************************************************
 * 1                    DESCRIPTION
 ****************************************************************************
 */

/*
 ****************************************************************************
 * 2                    CONFIGURATION
 ****************************************************************************
 */

#include "ipnet_config.h"

#define IPNET_MAX_IF_EVENTCB 8

/*
 ****************************************************************************
 * 3                    INCLUDE FILES
 ****************************************************************************
 */

#include "ipnet.h"
#include "ipnet_netif.h"
#ifdef IPCOM_USE_INET
#include "ipnet_ip4.h"
#endif
#ifdef IPCOM_USE_INET6
#include "ipnet_ip6.h"
#endif
#ifdef IPIPSEC2
#include <ipipsec.h>
#endif
#include "ipnet_nat_h.h"

#ifdef IPNET_USE_DIFFSERV
#include "ipnet_diffserv.h"
#include <ipcom_tree.h>
#endif
#include "ipnet_route.h"
#include "ipnet_signal.h"
#include "ipnet_timeout.h"

#include <ipcom_hash.h>
#include <ipcom_inet.h>
#include <ipcom_list.h>
#include <ipcom_mib2.h>
#include <ipcom_nae.h>
#include <ipcom_os.h>
#include <ipcom_pkt.h>
#include <ipcom_pqueue.h>
#include <ipcom_pqueue.h>
#include <ipcom_route.h>
#include <ipcom_slab.h>
#include <ipcom_sock.h>
#include <ipcom_spinlock.h>
#include <ipcom_rwsem.h>
#include <ipcom_sysvar.h>
#include <ipcom_time.h>

#ifdef IPCOM_USE_JOB_QUEUE
#include <ipcom_job_queue.h>
#endif

#ifdef IPPPP
#include <ipppp_ipstack.h>
#endif

#include "ipnet_netlink_h.h"
#include "ipnet_rtnetlink_h.h"

#if defined(_WRS_CONFIG_EPOLL)
#include <ipcom_epoll.h>
#endif

#ifdef IPSCTP
#include <ipsctp_hash.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*
 ****************************************************************************
 * 4                    DEFINES
 ****************************************************************************
 */

#define IPNET_FD_RANGE_OK(fd) \
    ((unsigned)((fd) - IPNET_SOCKET_STARTFD) < ipnet_conf_max_sockets_offset)

#define IPNET_FD_TO_SOCKET_EX(fd, sock, must_be_open)                   \
    if (IP_UNLIKELY(!IPNET_FD_RANGE_OK(fd))                             \
        || IP_UNLIKELY(IP_NULL == (sock = ipnet_fd_to_sock(fd)))        \
        || (must_be_open && IP_UNLIKELY(IP_BIT_ISSET(sock->flags, IPNET_SOCKET_FLAG_CLOSED)))) \
    {                                                                   \
        IPCOM_WV_MARKER_2 (IPCOM_WV_NETD_IP4_DATAPATH_EVENT, IPCOM_WV_NETD_WARNING, \
                           1, 1, IPCOM_WV_NETDEVENT_WARNING,            \
                           ipcom_socket, IPCOM_WV_NETD_NOSOCK,          \
                           IPCOM_WV_IPNET_SOCK_MODULE, IPCOM_WV_NETD_SOCKET); \
        IPNET_STATS(ipnet_ptr(), sock_ebadf++);                         \
        return IPNET_ERRNO(EBADF);                                      \
    }

#define IPNET_FD_TO_SOCKET(fd, sock)      IPNET_FD_TO_SOCKET_EX(fd, sock, IP_FALSE)
#define IPNET_FD_TO_OPEN_SOCKET(fd, sock) IPNET_FD_TO_SOCKET_EX(fd, sock, IP_TRUE)

#ifdef _WRS_CONFIG_EPOLL
#define IPNET_EPOLL_FD_TO_SOCKET(fd, sock)                              \
    if (IP_UNLIKELY(!IPNET_FD_RANGE_OK(fd))                             \
        || IP_UNLIKELY(IP_NULL == (sock = ipnet_fd_to_sock(fd))))       \
    {                                                                   \
        IPCOM_WV_MARKER_2 (IPCOM_WV_NETD_IP4_DATAPATH_EVENT, IPCOM_WV_NETD_WARNING, \
                           1, 1, IPCOM_WV_NETDEVENT_WARNING,            \
                           ipcom_socket, IPCOM_WV_NETD_NOSOCK,          \
                           IPCOM_WV_IPNET_SOCK_MODULE, IPCOM_WV_NETD_SOCKET); \
        IPNET_STATS(ipnet_ptr(), sock_ebadf++);                         \
    }
#endif

#define IPNET_MAKE_ERRNO(err)      -(err)
#define IPNET_ERRNO(err)           IPNET_MAKE_ERRNO(IP_ERRNO_ ## err)

/*
 * Return value from ipnet_sys_xxx() function move the request to the
 * primary stack instance with all other instances suspended.
 */
#define IPNET_SYS_NEED_TO_UPDATE_SHARED_DATA 0x80000001u

#define IPNET_DATA_SETU16(pkt,off,val16)   *(Ip_u16*)(&(pkt)->data[off]) = (Ip_u16)(val16)

#define IPNET_TIMEVAL_TO_MSEC(tv) (((Ip_s64) (tv).tv_sec * 1000 + (tv).tv_usec / 1000))

/*
 * Return a number N that where (size % align == 0) and N >= size
 * i.e. the smallest size that has the specified alignment
 * requirements
 */
#define IPNET_ALIGNED_SIZE(size, align) (((size) + (align) - 1) & ~((align) - 1))

/*
 * This flag is set when the packet contains urgent data. The flag is
 * used to pass information about MSG_OOB being set in
 * send()/sendto()/sendmsg() while the packet is being transmitted
 * through the stack command pipe.
 */
#define IPNET_PKT_FLAG_URGENT IPCOM_PKT_FLAG_LINK2

/*
 * Store the offset to the urgent data and mark the packet as urgent
 */
#define IPNET_MARK_PKT_AS_URGENT(pkt)                                   \
    do {                                                                \
        ipcom_pkt_set_int(pkt, IPNET_PKT_INFO_URGENT_OFFSET, (pkt)->end - (pkt)->start - 1, Ip_u16); \
        IP_BIT_SET((pkt)->flags, IPNET_PKT_FLAG_URGENT);                \
    } while (0)


#define IPNET_DATA_LOCK(lock)   ipcom_spinlock_lock(&lock)
#define IPNET_DATA_UNLOCK(lock) ipcom_spinlock_unlock(&lock)

#define ipnet_copy_to_user(s1,s2,n) ipcom_copy_to_user(s1,s2,n)
#define ipnet_copy_from_user(s1,s2,n) ipcom_copy_from_user(s1,s2,n)
#define ipnet_in_checksum_memcpy(s1,s2,n) ipcom_in_checksum_memcpy(s1,s2,n)

/*
 *===========================================================================
 *                        IPNET show functions
 *===========================================================================
 */
#if defined(IP_DEBUG)
#define IPNET_USE_SHOW
#endif


/*
 *===========================================================================
 *                        IPNET privilege
 *===========================================================================
 */

#define IPNET_PRIV_CHVR 1    /* Use has privilege to change the
                                current virtual router */

/*
 *===========================================================================
 *                         routing socket optional code
 *===========================================================================
 */
#ifdef IPNET_USE_ROUTESOCK
#define IPNET_ROUTESOCK(x) x
#else
#define IPNET_ROUTESOCK(x) IP_NOOP
#endif

/*
 *===========================================================================
 *                         netlink socket optional code
 *===========================================================================
 */
#ifdef IPNET_USE_NETLINK
#define IPNET_NETLINKSOCK(x) x
#else
#define IPNET_NETLINKSOCK(x) IP_NOOP
#endif

#define IPNET_NETLINK_DEF_BUF_SZ 8192
#define IPNET_NETLINK_EXTRA_PAD 50

/*
 *===========================================================================
 *                         DEBUG/ASSERT
 *===========================================================================
 */

#ifdef IPNET_DEBUG
/* #define IPNET_DEBUG_PRINTF -- Now handled per-file */
#define IPNET_DEBUG_LINE(x)    x
#else
#define IPNET_DEBUG_LINE(x)        IP_NOOP
#endif /* IPNET_DEBUG */


/*
 *===========================================================================
 *                         pkt id
 *===========================================================================
 */
#if defined(IPNET_DEBUG) || defined(IPNET_ASSERT)

#define IPNET_MEM_BEGIN_PAD    0xA110CA7E
#define IPNET_MEM_END_PAD      0x12DADE34

#endif /* IPNET_DEBUG */

/*
 *===========================================================================
 *                         syslog
 *===========================================================================
 */
#ifdef IPCOM_SYSLOG_PRIORITY
#undef IPCOM_SYSLOG_PRIORITY
#endif
#define IPCOM_SYSLOG_PRIORITY    IPNET_SYSLOG_PRIORITY

#ifdef IPCOM_SYSLOG_FACILITY
#undef IPCOM_SYSLOG_FACILITY
#endif
#define IPCOM_SYSLOG_FACILITY    IPCOM_LOG_IPNET


/*
 *===========================================================================
 *                     IPNET event semaphore
 *===========================================================================
 */
/* Select stack daemon configuration */
#ifdef IPCOM_STACKD_POST_IMPL
/*
 *===========================================================================
 *                      IPCOM_STACKD_POST_IMPL
 *===========================================================================
 * Description: Notifies the external stack daemon that a stack event
 *                      has occured.
 * Parameters:  new_timeout - IP_TRUE if called because a new timeout
 *                      has occured.
 *              is_posted - IP_TRUE if this function returned IP_TRUE
 *                      the last call and ipcom_stackd_event() has not
 *                      since the last call.
 * Returns:     IP_TRUE if 'is_posted' should be IP_TRUE in the next
 *                      call if this function is called more times
 *                      from the same ipcom_stackd_event() run.
 *
 */
IP_EXTERN Ip_bool IPCOM_STACKD_POST_IMPL(Ip_bool new_timeout, Ip_bool is_posted);
#define IPCOM_STACKD_POST(net, new_timeout)                             \
    (net)->task_posted = IPCOM_STACKD_POST_IMPL(new_timeout, (net)->task_posted)

#else /* !IPCOM_STACKD_POST_IMPL */

#ifdef IPCOM_USE_JOB_QUEUE
#define IPCOM_STACKD_POST(net, new_timeout)
#else
 /* The built-in daemon process is used */
#define IPCOM_STACKD_POST(net, new_timeout)                             \
    if (!(net)->task.wakeup_pending)                                    \
    {                                                                   \
        (net)->task.wakeup_pending = IP_TRUE;                           \
        ipcom_pipe_try_send((net)->task.pipe, (net)->task.wakeup_sig);  \
    }
#endif /* IPCOM_USE_JOB_QUEUE */
#endif /* IPCOM_STACKD_POST_IMPL */


/*
 * Adjust the checksum to reflect that the TTL had been decremented.
 *
 * Flip the bits on the checksum, decrement the high byte of the
 * checksum, fold in any carry, and then flip the bits back.  Rather
 * than convert the checksum to host byte order and then back to
 * network byte order, just convert the increment to network byte
 * order.  Note: in 1's complement arithmetic, subtracting by x is the
 * same as adding the 1's complement of x.  So, in 16 bit arithmetic,
 * rather than subtracting by (1<<8), we can add by (1<<8)^0xffff.
 * Since it's all constants, that should be evaluated by the compiler
 * at compile time.
 *
 * Doing the ^0xffff to initially flip the bits keeps the upper bits
 * from also being flipped. Using the ~ operation at the end doesn't
 * matter, because the upper bits get tossed when we assign it to the
 * 16 bit sum field, so let the compiler do whatever is fastest.
 */
#define IP_INCREMENTAL_CHECKSUM(ip_hdr)                         \
        do {                                                    \
            int     chksum;                                     \
            /* Calculate the incremental checksum update */     \
            --ip_hdr->ttl;                                      \
            /* increment checksum high byte */                  \
            chksum  = (int)(ip_hdr->sum ^ 0xFFFF) +             \
                      (int)ip_htons((1<<8) ^ 0xFFFF);           \
            /* Fold the carry bit into the checksum */          \
            ip_hdr->sum = (Ip_u16) ~(chksum + (chksum >> 16));  \
        } while((0))


/*
 *===========================================================================
 *                     WindView
 *===========================================================================
 */
#ifdef IPCOM_WV_INSTRUMENTATION
#define IPCOM_WV_MARKER_1(classId, eventLevel, eventOffset, eventTag, eventId, arg1, module, entity) \
    ipcom_wv_marker_1(classId, eventLevel, eventOffset, eventTag, eventId, arg1, module, entity)

#define IPCOM_WV_MARKER_2(classId, eventLevel, eventOffset, eventTag, eventId, arg1, arg2, module, entity) \
    ipcom_wv_marker_2(classId, eventLevel, eventOffset, eventTag, eventId, arg1, arg2, module, entity)

#define IPCOM_WV_EVENT_2(classId, eventLevel, eventOffset, eventTag, eventId, status, arg1, arg2, module, entity) \
    ipcom_wv_event_2(classId, eventLevel, eventOffset, eventTag, eventId, status, arg1, arg2, module, entity)
#define IPCOM_WV_VAR1 wv_what
#define IPCOM_WV_VAR2 wv_tag
#define IPCOM_WV_DECLARE_VARS int IPCOM_WV_VAR1=0, IPCOM_WV_VAR2=0
#define IPCOM_WV_SET_VARS(eventTag, what) do { wv_what = what; wv_tag = eventTag; } while(0)
#else
#define IPCOM_WV_MARKER_1(classId, eventLevel, eventOffset, eventTag, eventId, arg1, module, entity) \
    do {} while (0)

#define IPCOM_WV_MARKER_2(classId, eventLevel, eventOffset, eventTag, eventId, arg1, arg2, module, entity) \
    do {} while (0)

#define IPCOM_WV_EVENT_2(classId, eventLevel, eventOffset, eventTag, eventId, status, arg1, arg2, module, entity) \
    do {} while (0)
#define IPCOM_WV_VAR1
#define IPCOM_WV_VAR2
#define IPCOM_WV_DECLARE_VARS
#define IPCOM_WV_SET_VARS(eventTag, what)
#endif  /* #ifdef IPCOM_WV_INSTRUMENTATION */

/* IPNET packet information types */
#define IPNET_PKT_INFO_SIG                  64 /* Ipnet_sig */
#define IPNET_PKT_INFO_SOCK_SND_BUF         65 /* Ipnet_pkt_info_sock_snd_buf */
#define IPNET_PKT_INFO_URGENT_OFFSET        66 /* Ip_u16 */
#define IPNET_PKT_INFO_TUNNEL_IPSTART       67 /* int */
#define IPNET_PKT_INFO_NETEMU_SEQ_NUM       68 /* Ip_u32 */
#define IPNET_PKT_INFO_DPAF_PQ_INDEX        69 /* unsigned */
#define IPNET_PKT_INFO_TIMEOUT              70 /* Ip_u32 */
#define IPNET_PKT_INFO_PEER_INFO_PTR        71 /* Ipnet_peer_info* */
#define IPNET_PKT_INFO_IPSEC_CATEGORY       72 /* int */
#define IPNET_PKT_INFO_ZONE_ID              73 /* Ip_u32 */
#define IPNET_PKT_INFO_L4_CHKSUM_PTR        74 /* void* */
#define IPNET_PKT_INFO_ENCAP_UDP           (75 | IPCOM_PKT_INFO_COPY)  /* 8 bytes */
#define IPNET_PKT_INFO_ENCAP               (76 | IPCOM_PKT_INFO_COPY)  /* 4 bytes */

#define IPNET_PKT_INFO_GRE_KEY_OUTPUT      (77 | IPCOM_PKT_INFO_COPY) /* Ip_u32 */
#define IPNET_PKT_INFO_SEND_SIG_VERIFIED   (78 | IPCOM_PKT_INFO_COPY) /* void */

#define IPNET_PKT_INFO_DSTOPT_HOA          (79 | IPCOM_PKT_INFO_COPY)/* struct Ip_in6_addr* */
#define IPNET_PKT_INFO_RTHDR2              (80 | IPCOM_PKT_INFO_COPY)/* struct Ip_in6_addr* */

#define IPNET_PKT_INFO_CLONEDPKT            81 /* struct Ipcom_pkt* */
#define IPNET_PKT_INFO_INGRESS_IFINDEX      82 /* unsigned */

#define IPNET_PKT_INFO_ENCAP_FLAGS_SET(v, p)    (((v) << 8) | (p))
#define IPNET_PKT_INFO_ENCAP_FLAGS_GET_PROTO(f) ((f) & 0xFF)
#define IPNET_PKT_INFO_ENCAP_FLAGS_GET_VER(f)   (((v) >> 8) & 0xFF)

#define IPNET_PKT_INFO_FLAGS_GET_SIZE(f)        (((f) >> 24) & 0xFF)

#define IPCOM_INET6_MASK_LEN 16
#define IPCOM_INET_MASK_LEN   4

/*
 ****************************************************************************
 * 5                    TYPES
 ****************************************************************************
 */


/* Forward declaration */
struct Ipnet_data_struct;
struct Ipnet_netif_struct;
struct Ipnet_peer_info_struct;

enum Ipnet_startup_state {
    IPNET_IN_CREATE,   /* ipnet_create() has not finished */
    IPNET_IN_START,    /* ipnet_start() has not finished */
    IPNET_STARTUP_DONE /* stack is running */
};

/*
 *===========================================================================
 *                         Ipnet_pkt_udp
 *===========================================================================
 */
#include "ipcom_align16.h"
typedef IP_PACKED1 struct Ipnet_pkt_udp_struct
{
    Ip_u16   sport;     /* Source port. */
    Ip_u16   dport;     /* Destination port. */
    Ip_u16   ulen;      /* UDP length. */
    Ip_u16   sum;       /* UDP checksum. */
}
IP_PACKED2 Ipnet_pkt_udp;

#define IPNET_UDP_HDR_SIZE   (8)   /* UDP header is 8 octets long */


/*
 * RFC 3828 UDP-Lite packet
 */
typedef IP_PACKED1 struct Ipnet_pkt_udplite_struct
{
    Ip_u16   sport;     /* Source port. */
    Ip_u16   dport;     /* Destination port. */
    Ip_u16   sum_cov;   /* Octes covered by the checksum */
    Ip_u16   sum;       /* UDP-Lite checksum. */
}
IP_PACKED2 Ipnet_pkt_udplite;

#define IPNET_UDPLITE_HDR_SIZE   (8)   /* UDP header is 8 octets long */


/*
 *===========================================================================
 *                         Ipnet_frame
 *===========================================================================
 */
typedef IP_PACKED1 union Ipnet_pkt_union_union
{
#ifdef IPCOM_USE_INET
    Ipnet_pkt_icmp   icmp;
#endif
    Ipnet_pkt_udp    udp;
}
IP_PACKED2 IP_Ipnet_pkt_union;
#include "ipcom_align16.h"


/*
 * Packet information describing how much of the socket send buffer
 * this packet occupies
 */
typedef struct Ipnet_pkt_info_sock_snd_buf_struct
{
    /*
     * Pointer to the socket used to sent this packet. Direct pointer
     * is OK since the socket will not be freed until the send buffer
     * is ==0
     */
    struct Ipnet_socket_struct *sock;
    /*
     * Number of bytes this packet has reserved in the send buffer. Is
     * always >0
     */
    int                         payload_len;
}
Ipnet_pkt_info_sock_snd_buf;


/*
 *===========================================================================
 *                      Ipnet_sock_init_f
 *===========================================================================
 * Description: Called last in the socket creation and can proviced custom
 *              initialization of the socket.  The socket's ipnet file
 *              descriptor value is not available yet when this function is
 *              called. The function may return a number greater than zero,
 *              in which case the return value is to be added to the socket's
 *              reference count.
 * Parameters:  sock - The affected socket.
 *              user_context - IP_TRUE if called in the context of a user process
 *                             IP_FALSE if called in the context of the kernel.
 * Returns:     >=0 success, value is number of additional reference counts
 *                  to the socket.
 *              <0 = error code (-IPNET_ERRNO_xxx)
 */
typedef int (*Ipnet_sock_init_f)(struct Ipnet_socket_struct *sock,
                                 Ip_bool user_context);

/*
 *===========================================================================
 *                      Ipnet_sock_destroy_f
 *===========================================================================
 * Description: Called when the socket is going to be deleted.
 *              Can contain domain specific cleanups.
 * Parameters:  sock - The affected socket.
 * Returns:
 *
 */
typedef void (*Ipnet_sock_destroy_f)(struct Ipnet_socket_struct *sock);


/*
 *===========================================================================
 *                      Ipnet_sock_close_f
 *===========================================================================
 * Description: Called when the socket is beeing closed. Should be defined
 *              if special handling, not done by shutdown(sock, IP_SHUT_RDWR),
 *              is required.
 * Parameters:  sock - The affected socket.
 * Returns:     0 = success, <0 = error code (-IPNET_ERRNO_xxx)
 *
 */
typedef int (*Ipnet_sock_close_f)(struct Ipnet_socket_struct *sock);


/*
 *===========================================================================
 *                      Ipnet_sock_lookup_f
 *===========================================================================
 * Context:     A network stack task.
 *              NOTE: The caller must have locked the reachable sockets
 *                    list before calling this function.
 * Description: Returns the first socket that matches the specified parameters.
 * Parameters:  vr - The virtual route table the socket must match.
 *              proto - the protocol to match.
 *              local_addr - the local address to match or IP_NULL for any address.
 *              local_port - the local port to match or 0 for any port.
 *              peer_addr - the peer address to match or IP_NULL for any address.
 *              peer_port - the peer port to match or 0 for any port.
 * Returns:     The matching socket or IP_NULL if no socket matched.
 *
 */
typedef struct Ipnet_socket_struct *
(*Ipnet_sock_lookup_f)(Ip_u16 vr, int proto,
                       IP_CONST void *local_addr, Ip_u16 local_port,
                       IP_CONST void *peer_addr, Ip_u16 peer_port);

/*
 *===========================================================================
 *                      Ipnet_sock_send_f
 *===========================================================================
 * Description: Send handler for the domain/type/protocol tuple
 * Parameters:  sock - The socket the packet beeing sent on.
 *              msg - Message structure with (unconnected sockets) destination
 *              address and (optional) auxillary data. Can be IP_NULL
 *              if the socket is connected and no auxillary data is
 *                      needed. 'msg_flags' contains the flags passed
 *                      in the 'flags' field to ipcom_sendmsg().
 *
 *              pkt - The
 * Returns:     0 = success, <0 = error code (-IPNET_ERRNO_xxx)
 *
 */
typedef int (*Ipnet_sock_send_f)(struct Ipnet_socket_struct *sock,
                                 IP_CONST struct Ip_msghdr *msg,
                                 Ipcom_pkt *pkt);


/*
 *===========================================================================
 *                      Ipnet_sock_bind_f
 *===========================================================================
 * Description: Binds a socket.
 * Parameters:  sock - The socket to bind.
 *              name - The socket name.
 *              namelen - The length of the name variable.
 *              flags - Combination of bind flags.
 * Returns:     0 = success, <0 = error code (-IPNET_ERRNO_xxx)
 *
 */
typedef int (*Ipnet_sock_bind_f)(struct Ipnet_socket_struct *sock,
                                 IP_CONST struct Ip_sockaddr *name,
                                 Ip_socklen_t namelen,
                                 Ip_u32 flags);

/* Set if the bind should be checked for address reuse */
#define IPNET_SOCK_BIND_FLAG_CHECK_REUSE     1
/* Set if bind to a non-local address should be allowed.  Internal use only. */
#define IPNET_SOCK_BIND_FLAG_ALLOW_NONLOCAL  2

/*
 *===========================================================================
 *                      Ipnet_sock_connect_f
 *===========================================================================
 * Description: Binds a socket.
 * Parameters:  sock - The socket to bind.
 *              name - The socket name.
 *              namelen - The length of the name variable.
 * Returns:     0 = success, <0 = error code (-IPNET_ERRNO_xxx)
 *
 */
typedef int (*Ipnet_sock_connect_f)(struct Ipnet_socket_struct *sock,
                                    IP_CONST struct Ip_sockaddr *to,
                                    Ip_socklen_t tolen);

/*
 *===========================================================================
 *                      Ipnet_sock_shutdown_f
 *===========================================================================
 * Description: Shutdown read and/or write end of the socket, IPNET
 *              takes care of flagging the socket read/write end as shut,
 *              and notifies blocked sockets. Protocol specific things has
 *              to be done in this handler though (like sending FIN for TCP).
 * Parameters:  sock - The socket to shutdown.
 *              how - IP_SHUT_xxx constant.
 * Returns:
 *
 */
typedef void (*Ipnet_sock_shutdown_f)(struct Ipnet_socket_struct *sock, int how);


/*
 *===========================================================================
 *                      Ipnet_sock_accept_f
 *===========================================================================
 * Description: Accepts a socket.
 * Parameters:  sock - The socket to bind.
 *              name - The address of the accepted socket.
 *              namelen - The length of the name variable.
 * Returns:     >=0 = success (file descripto), <0 = error code (-IPNET_ERRNO_xxx)
 *
 */
typedef int (*Ipnet_sock_accept_f)(struct Ipnet_socket_struct *sock,
                                   struct Ip_sockaddr *name,
                                   Ip_socklen_t *namelen);


/*
 *===========================================================================
 *                      Ipnet_sock_listen_f
 *===========================================================================
 * Description: Puts a socket in listen mode.
 * Parameters:  sock - The socket to put in listen mode.
 *              backlog - The size of the socket backlog.
 * Returns:     0 = success, <0 = error code (-IPNET_ERRNO_xxx)
 *
 */
typedef int (*Ipnet_sock_listen_f)(struct Ipnet_socket_struct *sock,
                                   int backlog);


/*
 *===========================================================================
 *                      Ipnet_sock_setopt_f
 *===========================================================================
 * Description: Handles socket option.
 * Parameters:  sock - The socket to set an option on.
 *              level - The protocol level that should be affected by the
 *              option.
 *              optname - The option name.
 *              optval - Data to set for the option.
 *              optlen - The length of the buffer pointed to by optval.
 * Returns:     0 = success,
 *             -IP_ERRNO_EOPNOTSUPP = This handler does not implement this option,
 *                                    try other handlers
 *             <0 = error code (-IPNET_ERRNO_xxx), do not try other handlers
 *
 */
typedef int (*Ipnet_sock_setopt_f)(struct Ipnet_socket_struct *sock,
                                   int level,
                                   int optname,
                                   IP_CONST void *optval,
                                   Ip_socklen_t optlen);


/*
 *===========================================================================
 *                      Ipnet_sock_getopt_f
 *===========================================================================
 * Description: Handles socket option.
 * Parameters:  sock - The socket to get an option from.
 *              level - The protocol level that should be affected by the
 *              option.
 *              optname - The option name.
 *              optval - Data to set for the option.
 *              optlen - The length of 'optval' when calling,
 *                       number of bytes copied to 'optval' when returning.
 * Returns:     0 = success,
 *             -IP_ERRNO_EOPNOTSUPP = This handler does not implement this option,
 *                                    try other handlers
 *             <0 = error code (-IPNET_ERRNO_xxx)
 *
 */
typedef int (*Ipnet_sock_getopt_f)(struct Ipnet_socket_struct *sock,
                                   int level,
                                   int optname,
                                   void *optval,
                                   Ip_socklen_t *optlen);



/*
 *===========================================================================
 *                      Ipnet_sock_getname_f
 *===========================================================================
 * Description: Returns the local name (or address) of the socket.
 * Parameters:  sock - The socket to return the name for.
 *              name - Buffer where the name will be stored.
 *              namelen - The length of the 'name' buffer.
 *              is_local_name - Is set to IP_TRUE of the local name of the
 *              socket should be returned, IP_FALSE means that the peer name
 *              should be returned.
 * Returns:     0 = success, <0 = error code (-IPNET_ERRNO_xxx)
 *
 */
typedef int (*Ipnet_sock_getname_f)(struct Ipnet_socket_struct *sock,
                                    struct Ip_sockaddr *name,
                                    Ip_socklen_t  *namelen,
                                    Ip_bool is_local_name);


/*
 *===========================================================================
 *                      Ipnet_sock_ioctl_f
 *===========================================================================
 * Description: Handles IO control on the socket.
 * Parameters:  sock - The socket to get an option from.
 *              request - The IO control request.
 *              argp - Request specific data.
 * Returns:     0 = success,
 *             <0 = error code (-IPNET_ERRNO_xxx)
 *             -IP_ERRNO_EOPNOTSUPP = This handler does not implement this option,
 *                                    try other handlers
 *
 */
typedef int (*Ipnet_sock_ioctl_f)(struct Ipnet_socket_struct *sock,
                                  unsigned long request, void *argp);


/*
 *===========================================================================
 *                      Ipnet_usr_sock_recv_f
 *===========================================================================
 * Description: Called in context of the receiving task. Proper
 *                      locking must be done by the this function to
 *                      safely extract the data from the socket.
 * Parameters:  sock - The socket to receive from.
 *              msg - 'msg_iov' contains the buffer(s) to where the
 *                      received data should be copied.
 *              flags - IP_MSG_xxx flags.
 * Returns:     0 = success, <0 = error code (-IPNET_ERRNO_xxx)
 *
 */
typedef int (*Ipnet_usr_sock_recv_f)(struct Ipnet_socket_struct *sock,
                                     struct Ip_msghdr *msg,
                                     int flags);

typedef struct Ipnet_pkt_result_struct
{
    Ipcom_pkt * pkt;
    /*
     * The transient_err will generally be 0 for datagram sockets.
     * However, for stream sockets, short writes may be possible if the
     * Ipnet_usr_sock_pkts_from_iov_f function is interrupted by
     * a signal or a deletion attempt.
     *
     * transient_err is a combination of the bit flags
     * IP_TRANSIENT_EDOOM and IP_TRANSIENT_EINTR.
     */
    int         transient_err;

#define IP_TRANSIENT_EDOOM  1
#define IP_TRANSIENT_EINTR  2
} Ipnet_pkt_result;

/*
 *===========================================================================
 *                      Ipnet_usr_sock_pkts_from_iov_f
 *===========================================================================
 * Description: Called in context of the sending task. Proper
 *                      locking must be done by the this function if
 *                      members of the socket are read or modified.
 * Parameters:  sock - The socket that will be use to send.
 *              msg - 'msg_iov' contains the buffer(s) to send.
 *              flags - IP_MSG_xxx flags.
 *              offset - Number of bytes into the msg->msg_iov buffers
 *                      where the copy into packets should start.
 *              total_buf_len - the sum of the length of all
 *                      msg->msg_iov buffers in 'msg'.
 *              prslt - Points to result structure where the constructed packet
 *                      and transient error (if any) are returned.
 *                      prslt->pkt->next points to the next packet in case
 *                      more than one packet was allocated.
 * Returns:     <0 = error code (-IPNET_ERRNO_xxx)
 *               0 = this operation released the socket lock, the
 *                      sendmsg operation must be restarted
 *              >0 = number of bytes that have been allocated in the
 *                      socket send buffer and copied into the
 *                      packet(s) pointed to by prslt->pkt.
 *
 */
typedef int (*Ipnet_usr_sock_pkts_from_iov_f)(struct Ipnet_socket_struct *sock,
                                              IP_CONST struct Ip_msghdr *msg,
                                              int flags,
                                              int offset,
                                              int total_buf_len,
                                              Ipnet_pkt_result *prslt);


/*
 * Socket operations for a domain/type/proto tuple, functions can be
 * left as IP_NULL if that operation is not supported
 */
typedef struct Ipnet_sock_ops_struct
{
    int                   domain;           /* The domain this operations is valid for */
    int                   type;             /* The socket type operations is valid for */
    int                   proto;            /* The protocol or -1 for any protocol */
    Ip_size_t             extra_sock_space; /* Extra space to be allocated at the end of the socket */
    Ip_size_t             hdr_space;        /* Minimum header space needed at by the domain/type/proto */
    Ip_bool               allow_async_send; /* IP_TRUE if this socket type allows asynchronous send */
    Ipnet_sock_accept_f   accept;
    Ipnet_sock_bind_f     bind;
    Ipnet_sock_close_f    close;
    Ipnet_sock_connect_f  connect;
    Ipnet_sock_destroy_f  destroy;
    Ipnet_sock_getname_f  getname;
    Ipnet_sock_getopt_f   getopt;
    Ipnet_sock_init_f     init;
    Ipnet_sock_ioctl_f    ioctl;
    Ipnet_sock_listen_f   listen;
    Ipnet_sock_lookup_f   lookup;
    Ipnet_sock_send_f     send;
    Ipnet_sock_setopt_f   setopt;
    Ipnet_sock_shutdown_f shutdown;

    Ipnet_usr_sock_recv_f          usr_recv;
    Ipnet_usr_sock_pkts_from_iov_f pkts_from_iov;
}
Ipnet_sock_ops;



/*
 * Internal socket structure used by IPNET to implement IP_AF_INET and
 * IP_AF_INET 6
 */
typedef struct Ipnet_sock_inet_ops_struct
{
    Ipnet_sock_ops       sock;
    Ipnet_sock_bind_f    network_bind;
    Ipnet_sock_send_f    network_send;
}
Ipnet_sock_inet_ops;


/*
 *===========================================================================
 *                      Ipnet_dynhdrspc
 *===========================================================================
 * Description: Returns the number of octets that must be allocated to fit
 *              IP options and/or extension headers.
 * Parameters:  sock - The socket used to send the datagram.
 *              msg - The message data passed to ipcom_sendmsg().
 * Returns:     Number of extra octets that must be allocated.
 *
 */
typedef Ip_size_t (*Ipnet_dynhdrspc)(struct Ipnet_socket_struct *sock,
                                     IP_CONST struct Ip_msghdr *msg);


/*
 *===========================================================================
 *                    Ipnet_is_sock_ready_cb
 *===========================================================================
 * Description: Callback that will determine if the specified socket
 *                    is ready or not.
 * Parameters:  sock - a socket.
 *              lowat - minimum number of bytes that has to be
 *                    available in the send/receive buffer in order to
 *                    consider the socket to be writable/readable. 0
 *                    means that the socket default value should be used.
 * Returns:     IP_TRUE if the socket is ready.
 *
 */
typedef Ip_bool (*Ipnet_is_sock_ready_cb)(struct Ipnet_socket_struct *sock,
                                          int lowat);


/*
 *===========================================================================
 *                 Ipnet_transport_layer_rx_func
 *===========================================================================
 * Description: Handler for a specific IPv4/IPv6 payload protcol. The packet
 *              ownership is transfered to the handler.
 * Parameters:  dst - destination cache for the flow used by the packet.
 *              pkt - packat that is being delivered
 * Returns:
 *
 */
typedef void (*Ipnet_transport_layer_rx_func)(struct Ipnet_dst_cache_struct *dst,
                                              Ipcom_pkt *pkt);



/*
 *===========================================================================
 *                         Ipnet_socket
 *===========================================================================
 */
typedef struct Ipnet_socket_struct
{
    Ipcom_socket   ipcom;                /* Generic socket parameters */
    Ip_u32         flags;                /* Socket flags. */
    int            ops_handle;           /* Handle for the socket
                                            operations for this socket */
    /*
     * Pointer to a signal of a deferred socket call or IP_NULL if no
     * such call is pending.
     */
    void           *signal;

    /*
     * Handle to the stack instance that currently controls this
     * socket.  Note that this value might be changed at runtime so it
     * is NOT ok to deference this member on a socket to figure out
     * which network stack instance one is currently executing on.
     */
    int             stack_instance_idx;

    /*
     * fd of next closed socket waiting to be freed by owner stack instance.
     * 0 marks end of list.
     */
    int            free_next_fd;

    /*
     * Address removal notifications cannot be used in a NAE since the
     * address structures are per-NAE and the sockets are shared
     * between NAE:s.
     */
    struct Ipnet_socket_struct *addr_prev;    /* Previous socket bound to the same address */
    struct Ipnet_socket_struct *addr_next;    /* Next socket bound to the same address */
    void                       *addr_entry;   /* Pointer to the address entry for the bind address */

    /*
     * Entry in list of reachable sockets hashing to the same
     * ipnet->reachable_sockets bucket.
     */
    Ipcom_list reachable_list;

    /*
     * Points to the first socket in the 'ipnet->reachable_sockets'
     * bucket that share the same socket lookup tuple. This pointer is
     * IP_NULL if this is the only socket with a specific tuple.
     */
    struct Ipnet_socket_struct *first_sibling;

    Ip_u16   proto;                      /* Protocol */
    Ip_u16   vr_index;                   /* The virtual router to use when sending/receiving packets on this socket */

    Ip_u16   max_hdrspace;               /* Maximum needed header space for network (IP) and transport layer. */
    Ip_u16   chk_offset;                 /* Offset into the transport layer (TCP, UDP, e.t.c) where the
                                           16 bit internet checksum should be stored, used if the flag
                                           IPNET_SOCKET_FLAG_ADDCHECKSUM is set */

    Ip_u16   sport;                      /* Source port. */
    Ip_u16   dport;                      /* Destination port. */
    struct Ip_sockaddr_storage last_to;  /* Address of the node to which something was last sent on this socket */
    Ip_u16   biggest_msg_size_in_sync;   /* The biggest successfully send msg size in using synchronous mode */
    Ip_u8    large_send_countdown;       /* The count of successfully sending large msg on this socket. 
                                                                         If it is 0, must use synchronous send. */

#ifdef IPNET_USE_PER_SOCKET_VLAN_TAG
    Ip_u16   vlan_tag;                   /* Bit 0-2 is priority,
                                            bit 3 is priority tagging on/off
                                            bit 4-15 is the VLAN tag */
#endif
    Ip_u16   udplite_sum_cov;            /* Number of bytes covered by the RFC3828 UDP-Lite
                                            checksum. Must be 0 (all bytes), or >=8 */

    Ip_u8    uni_hop_limit;              /* The hop limit for unicast packtes */
    Ip_u8    multi_hop_limit;            /* The hop limit for multicast packtes */
    Ip_u8    promisc_count;              /* Number of times promisc mode has been entered on this socket */
    Ip_u8    udp_encapsulation;          /* UDP encapsulation method */

    Ip_u32   bind_to_ifindex;         /* The interface this socket is
                                            bound to (with
                                            IP_SO_BINDTODEVICE). ==0
                                            -> not bound */
#ifdef IPNET_USE_RFC2890
    Ip_u32   gre_key;                 /* GRE key for this socket */
#endif
    int      keep_alive_probe_delay;  /* Number of seconds an TCP
                                         connection must be idle
                                         before the first keep-alive
                                         probe is sent */

    Ipcom_pkt_dtor    pkt_dtor;       /* Packet destruction that most
                                         be used for packets sent
                                         using this socket */

    Ipnet_dynhdrspc   dynamic_header_space;

    int               send_max_bytes; /* Max number of bytes that can be stored in the send buffer */
    int               recv_max_bytes; /* Max number of bytes that can be stored in the recieve buffer */

    int               snd_route_cache_id; /* Value of ipnet->route_cache_id at last successful send */
    Ipcom_atomic_t    snd_bytes_ref;   /* Bytes in send buffer : lower 31 bits.
                                          Referenced flag : high bit. */
    Ipcom_atomic_t    waiting_writers; /* Number of waiting writers on this socket */

    Ipcom_pkt        *snd_head;      /* Output queue, only used if IP_MSG_MORE flag is used */
    struct Ip_sockaddr *snd_to;      /* Cached to address specified in a sendmsg() with IP_MSG_MORE */

    /*
     * Variables used by protocols that is datagram based, the TCP
     * receive queue is found in 'tcb'
     */
    Ipcom_spinlock    rcv_lock;      /* Must be locked when modifying
                                        rcv_head, rcv_tail and
                                        ipcom.rcv_bytes  */

    Ipcom_pkt        *rcv_head;      /* Input packet queue head, pkt->start is the offset
                                        to the transport layer header. */
    Ipcom_pkt        *rcv_tail;      /* Input packet queue tail. */

    /*
     * Synchronization objects used when receiving data
     */
    struct Ip_timeval *rcv_timeout;   /* Time that a blocking
                                         ipcom_recv can bloc, IP_NULL
                                         means infinite time */
#ifdef IPNET_USE_SO_CONNTIMEO
    struct Ip_timeval *conn_timeout;  /* Time that for connectWithTimeout */
#endif

    /*
     * List of struct Ipnet_sig_poll instances added by task(s) that
     * are waiting for the socket to become readable, writable and/or
     * exceptional
     */
    Ipcom_list        poll_list_head;
    Ipcom_spinlock    poll_list_lock;      /* Must be used when modifying poll list */

#ifdef IPTCP
    struct Iptcp_tcb_struct *tcb;       /* Transmission control block (used by TCP) */
    void (*notify_cb)(struct Ipnet_socket_struct *sock, int event); /* See Iptcp_notifycb in iptcp.h */
#endif
#ifdef IPSCTP
    struct Ipsctp_instance_struct *sctp_inst;  /* Transmission control block (used by SCTP) */
#endif

#if defined(IP_PORT_VXWORKS) && defined(IPCOM_USE_SOCK_COMPAT)
    void                        *select_ctx;
#ifdef IPNET_SO_WAKEUP_HOOK
    void                        *windnet_so;
#endif
#ifdef _WRS_CONFIG_EPOLL
    void                        *epoll_lst_head[IPCOM_EPOLL_MAX_INSTANCES];
    Ip_u32                       epoll_lst_refCount[IPCOM_EPOLL_MAX_INSTANCES];
    Ip_u32                       epoll_num;
#ifndef _WRS_CONFIG_EPOLL_IPNET_SOCK_USE_SIGNALS
    Ipcom_mutex                  epoll_mutex;
#endif
#endif  /* _WRS_CONFIG_EPOLL */
#endif

    Ip_u32            timestamp_flag;       /* Socket timestamp flag. */

    void *            streamCookie;   /* TSN stream cookie */
    void             *sock_end;    /* The current end of the socket, used to set up layer specific space */

#ifdef IPCOM_USE_INET
    Ipnet_ip4_socket *ip4;
#endif
#ifdef IPCOM_USE_INET6
    Ipnet_ip6_socket *ip6;
#endif
#ifdef IPCOM_USE_PACKET
    Ipnet_packet_socket *ps;
#endif
#ifdef IPNET_USE_NETLINKSOCK
    Ipnet_netlink_socket *nl;
#endif

    /* !NOTE! do not put any struct members below this point */
}
Ipnet_socket;

/* socket flags. */
/* Flags controlled by socket options */
#define IPNET_SOCKET_FLAG_REUSEADDR           (1u << 0)  /* Resuse of address is ok */
#define IPNET_SOCKET_FLAG_REUSEPORT           (1u << 1)  /* Resuse of port and address is ok */
#define IPNET_SOCKET_FLAG_DONTROUTE           (1u << 2)  /* Bypass routing for outgoing messages */
#define IPNET_SOCKET_FLAG_LOOP_MULTICAST      (1u << 3)  /* Loopback multicast packets sent from this host */
#define IPNET_SOCKET_FLAG_TCP_NODELAY         (1u << 4)  /* Nagle algorithm is OFF when this flag is set */
#define IPNET_SOCKET_FLAG_RECV_IF             (1u << 5)  /* Returns the recv if for datagram proto */
#define IPNET_SOCKET_FLAG_RECVPKTINFO         (1u << 6)  /* Returns extra information about received packets */
#define IPNET_SOCKET_FLAG_KEEPALIVE           (1u << 7)  /* Probe idle connection */
#define IPNET_SOCKET_FLAG_NONBLOCKING         (1u << 8)  /* Socket is in non-blocking mode */
#define IPNET_SOCKET_FLAG_ADDCHECKSUM         (1u << 9)  /* Pseudo header checksum should be added to outgoing packets */
#define IPNET_SOCKET_FLAG_OOBINLINE           (1u << 10) /* Out-of-band data should be mixed with normal data */
#define IPNET_SOCKET_FLAG_SENDER_LINK_ADDR    (1u << 11) /* Get link address of sender */

/* Socket long term state */
#define IPNET_SOCKET_FLAG_REACHABLE           (1u << 12) /* Set if the socket can match incoming packets */
#define IPNET_SOCKET_FLAG_BOUND               (1u << 13) /* Socket is bound (explicit or implicit) */
#define IPNET_SOCKET_FLAG_CONNECTING          (1u << 14) /* Asynchronous connect in progress */
#define IPNET_SOCKET_FLAG_CONNECTED           (1u << 15) /* Socket is connected */

#define IPNET_SOCKET_FLAG_READ_CLOSED         (1u << 16) /* The read end of the socket is closed */
#define IPNET_SOCKET_FLAG_WRITE_CLOSED        (1u << 17) /* The write end of the socket is closed */
#define IPNET_SOCKET_FLAG_PEER_WRITE_CLOSED   (1u << 18) /* The peer has closed its write end */
#define IPNET_SOCKET_FLAG_CLOSED              (1u << 19) /* The socket has been closed */
#define IPNET_SOCKET_FLAG_DONT_REBIND         (1u << 20) /* Never rebind the socket regardless of source address */
#define IPNET_SOCKET_FLAG_REUSE_CHECK_EXEMPT  (1u << 21) /* exempt from port reuse check */

#define IPNET_SOCKET_FLAG_MROUTE_CONTROL      (1u << 23) /* This socket is used for multicast routing control */
#define IPNET_SOCKET_FLAG_DRAINABLE           (1u << 24) /* Packets queued on this socket might be freed
                                                            in order to satisfy a packet allocation call */
#define IPNET_SOCKET_FLAG_GRE_KEY             (1u << 25) /* Socket has a RFC 2890 key set */

/* Socket short term state */
#ifdef IPNET_USE_SOCKET_PKTAVAIL_CB
#define IPNET_SOCKET_FLAG_PKTAVAIL_CB_PENDING (1u << 27) /* This socket want an IP_SOEVENT_CB_PKTAVAIL event when
                                                            the next packet is freed */
#endif

/* Misc. */
#define IPNET_SOCKET_FLAG_TIMESTAMPING        (1u << 28)
#define IPNET_SOCKET_FLAG_DEBUG               (1u << 29) /* Debug is enabled */
#define IPNET_SOCKET_FLAG_HAS_STICKY_OPT      (1u << 30) /* At least 1 sticky option is set */
#define IPNET_SOCKET_FLAG_SENDMSG_ASYNCHRONOUS (1u << 31)

/* socket start index (0,1,2 are reserved) */
#define IPNET_SOCKET_STARTFD    3

/*
 * Since we reserve one bit of sock->snd_bytes_ref to indicate whether
 * the socket has references remaining to it, the maximum number of bytes
 * allowed in a socket buffer is 0x7fffffff, i.e. INT_MAX.  This hasn't changed.
 */
#define IPNET_SND_BYTES_REFERENCED_BIT  ((int)(0x80000000U))

IP_INLINE int
IPNET_SND_BYTES_REF_CLOSED(int snd_bytes_ref)
{
    return (snd_bytes_ref >= 0);
}

IP_INLINE int
IPNET_SND_BYTES_COUNT(int snd_bytes_ref)
{
    return (snd_bytes_ref & ~IPNET_SND_BYTES_REFERENCED_BIT);
}

IP_INLINE int
ipnet_sock_snd_bytes(Ipnet_socket *sock)
{
    return (IPNET_SND_BYTES_COUNT(ipcom_atomic_get(&sock->snd_bytes_ref)));
}

/*
 *===========================================================================
 *                    ipnet_alloc_snd_bytes
 *===========================================================================
 * Description: Allocate socket send buffer space.
 * Parameters:  sock - a socket.
 *              total_buf_len - number of bytes of space to allocate in the
 *                              socket send buffer.
 * Returns:     IP_TRUE if successful;
 *              IP_FALSE if there is currently not enough space;
 */
IP_INLINE Ip_bool
ipnet_alloc_snd_bytes(Ipnet_socket *sock, int total_buf_len)
{
    int snd_bytes_ref;
    int count;
    do
    {
        snd_bytes_ref = ipcom_atomic_get(&sock->snd_bytes_ref);
        count = IPNET_SND_BYTES_COUNT(snd_bytes_ref);
        if (count >= sock->send_max_bytes || count + total_buf_len < count)
            return 0;
    } while (!ipcom_atomic_cas(&sock->snd_bytes_ref, snd_bytes_ref,
                               snd_bytes_ref + total_buf_len));
    return 1;
}


/*
 *===========================================================================
 *                         Ipnet_socket_lookup_key
 *===========================================================================
 */
typedef struct Ipnet_socket_lookup_key_struct
{
    Ip_u32  vr;             /* The virtual router the socket must be assigned to */
    Ip_u16  domain;         /* The domain this socket must be part of */
    Ip_u16  proto;          /* The protocol the socket must use */
    Ip_u16  local_port;     /* The local port the socket must bound to */
    Ip_u16  peer_port;      /* The peer port the socket must connected to */
    union Ip_in_addr_union local_addr; /* The local address */
    union Ip_in_addr_union peer_addr;  /* The peer address */
}
Ipnet_socket_lookup_key;


/*
 *===========================================================================
 *                         Ipnet_stats
 *===========================================================================
 * IPNET debug statistics useful for debugging the stack if things go wrong.
 */
#if defined(IPNET_DEBUG) || defined(IPNET_STATISTICS)

/*
 * First, statistics that are incremented in stack context.
 * These are maintained per-stack-instance for performance reasons,
 * and are summed over instances when reporting them.
 */
typedef struct Ipnet_stats_struct
{
    Ip_u32    pkt_num_tcp_out_of_order_seg;
    Ip_u32    pkt_num_ip4_reassembly_list;
    Ip_u32    pkt_num_ip6_reassembly_list;

    Ip_u32    pkt_input;
    Ip_u32    pkt_input_err;
    Ip_u32    pkt_input_opened_err;
    Ip_u32    pkt_input_bound_to_other_if;
    Ip_u32    pkt_input_queue_full;
    Ip_u32    pkt_drain_ip4_reasm;
    Ip_u32    pkt_drain_ip6_reasm;
    Ip_u32    pkt_clone_nomem;
    Ip_u32    pkt_frag_nomem;
    Ip_u32    pkt_reasm_nomem;
    Ip_u32    pkt_reasm_too_big;
    Ip_u32    pkt_queue_enobufs;
    Ip_u32    pkt_queue_emsgsize;

    Ip_u32    pkt_output;
    Ip_u32    pkt_output_drv;
    Ip_u32    pkt_output_ewouldblock;   /* errors other than non-blocking. */
    Ip_u32    pkt_output_err;   /* errors other than non-blocking. */
    Ip_u32    pkt_output_queue;
    Ip_u32    pkt_output_discard;
    Ip_u32    pkt_output_delayed;
    Ip_u32    pkt_output_sleep;
    Ip_u32    pkt_output_requeue;
    Ip_u32    pkt_output_fast_drv_ready;

    Ip_u32    pkt_netif_output_done;
    Ip_u32    pkt_netif_output_done_pkt;
    Ip_u32    pkt_netif_output_done_discard;
    Ip_u32    pkt_netif_output_delayed_queue;
    Ip_u32    pkt_netif_output_delayed_wake;
    Ip_u32    pkt_netif_output_user_wake;
    Ip_u32    pkt_inputd_output;
    Ip_u32    pkt_inputd_output_err;
    Ip_u32    pkt_inputd_output_ewouldblock;
    Ip_u32    pkt_inputd_output_err_nonetif;

    Ip_u32    eth_input;
    Ip_u32    eth_input_down;
    Ip_u32    eth_input_arp;
    Ip_u32    eth_input_arp_unknown;
    Ip_u32    eth_input_arp_bad;
    Ip_u32    eth_input_arp_reperr;
    Ip_u32    eth_input_arp_reqother;
    Ip_u32    eth_input_ip4;
    Ip_u32    eth_input_ip6;
    Ip_u32    eth_input_other;
    Ip_u32    eth_output_ip4;
    Ip_u32    eth_output_ip4_err;
    Ip_u32    eth_output_ip4_drverr;
    Ip_u32    eth_output_ip4_multierr;
    Ip_u32    eth_output_ip6;
    Ip_u32    eth_output_ip6_err;
    Ip_u32    eth_output_ip6_drverr;
    Ip_u32    eth_output_arp_req;
    Ip_u32    eth_output_arp_req_nomem;
    Ip_u32    eth_output_arp_rep;

#if defined(IPNET_USE_VLAN) || defined(IPNET_USE_VLAN_STACKING)
    Ip_u32    vlan_input_no_match;
    Ip_u32    vlan_input_down;
#ifdef IPNET_USE_VLAN_STACKING
    Ip_u32    eth_output_vlan;
    Ip_u32    eth_output_vlan_drverr;
#endif /* IPNET_USE_VLAN_STACKING */
#endif  /* IPNET_USE_VLAN || IPNET_USE_VLAN_STACKING */

#ifdef IPNET_USE_BOND
    Ip_u32    bond_input_no_match;
    Ip_u32    bond_input_down;
#endif /* IPNET_USE_BOND */

    Ip_u32    ip4_input;
    Ip_u32    ip4_input_err;
    Ip_u32    ip4_input_hdr_trunc;
    Ip_u32    ip4_input_hdr_toolong;
    Ip_u32    ip4_input_inval_len;
    Ip_u32    ip4_input_inval_version;
    Ip_u32    ip4_input_not_to_me;
    Ip_u32    ip4_input_iph_badchksum;
    Ip_u32    ip4_input_reasm_enobufs;
    Ip_u32    ip4_input_time_exceeded;
    Ip_u32    ip4_input_need_frag;

    Ip_u32    ip4_output;
    Ip_u32    ip4_output_blackhole;
    Ip_u32    ip4_output_hdr_space;
    Ip_u32    ip4_output_noroute;
    Ip_u32    ip4_output_enobufs;
    Ip_u32    ip4_output_link_err;

    Ip_u32    icmp4_input;
    Ip_u32    icmp4_input_echo_request;
    Ip_u32    icmp4_input_dst_unreach;
    Ip_u32    icmp4_input_dst_unreach_match;
    Ip_u32    icmp4_input_dst_unreach_nomatch;
    Ip_u32    icmp4_input_dst_unreach_badcode;
    Ip_u32    icmp4_input_hdrsize;
    Ip_u32    icmp4_input_badchksum;
    Ip_u32    icmp4_input_hdrsize2;
    Ip_u32    icmp4_send;
    Ip_u32    icmp4_send_nomem;

    Ip_u32    ip6_input;
    Ip_u32    ip6_input_err;
    Ip_u32    ip6_input_hdr_trunc;
    Ip_u32    ip6_input_inval_len;
    Ip_u32    ip6_input_inval_exthdr;
    Ip_u32    ip6_input_not_to_me;
    Ip_u32    ip6_input_too_big;
    Ip_u32    ip6_input_time_exceeded;
    Ip_u32    ip6_input_too_short;
    Ip_u32    ip6_input_tcp_multicast;
    Ip_u32    ip6_input_prot_err;
    Ip_u32    ip6_input_hdr_no_next;
    Ip_u32    ip6_input_raw;

    Ip_u32    ip6_output;
    Ip_u32    ip6_output_err;
    Ip_u32    ip6_output_blackhole;
    Ip_u32    ip6_output_hdr_space;
    Ip_u32    ip6_output_noroute;
    Ip_u32    ip6_output_nomem;
    Ip_u32    ip6_output_enobufs;
    Ip_u32    ip6_output_err_probe;
    Ip_u32    ip6_output_link_err;

    Ip_u32    icmp6_input;
    Ip_u32    icmp6_input_err;
    Ip_u32    icmp6_input_badchksum;
    Ip_u32    icmp6_input_nomem;

    Ip_u32    icmp6_send_nomem;

    Ip_u32    udp4_input;
    Ip_u32    udp4_input_ok;
    Ip_u32    udp4_input_err;

    Ip_u32    tcp4_input;
    Ip_u32    tcp4_input_ok;
    Ip_u32    tcp4_input_err;

    Ip_u32    raw4_input;
    Ip_u32    raw6_input;
    Ip_u32    raw_input_badchksum;

    Ip_u32    udp_input;
    Ip_u32    udp_input_hdr_trunc;
    Ip_u32    udp_input_badchksum;
    Ip_u32    udp_input_sock_multicast;
    Ip_u32    udp_input_sock_match;
    Ip_u32    udp_input_sock_nomatch;
    Ip_u32    udp_input_queue_pkt_ok;
    Ip_u32    udp_input_queue_pkt_err;
    Ip_u32    udp_input_multicast;
    Ip_u32    udp_input_econnrefused;
    Ip_u32    udp_output;
    Ip_u32    udp_output_hdr_trunc;
    Ip_u32    udp_output_eaddrinuse;
    Ip_u32    udp_output_eafnosupport;

    Ip_u32    sock_ebadf;

    Ip_u32    sock_sendmsg;

    Ip_u32    neigh_pending;
    Ip_u32    neigh_pending_drop;

#ifdef IPIPSEC2
    Ip_u32    ipsec_input;
    Ip_u32    ipsec_output;
#endif
	
}
Ipnet_stats;

/*
 * Next, statistics that are incremented in application context
 * (or other non-stack context), or which for some other reason are
 * not maintained per-stack-instance.
 */
typedef struct Ipnet_global_stats_struct
{
    Ipcom_atomic_t   sock_recvmsg;
    Ipcom_atomic_t   sock_recvmsg_tcp_err;
    Ipcom_atomic_t   sock_recvmsg_err; /* unused? */

    Ipcom_atomic_t   usr_sock_recvmsg;
    Ipcom_atomic_t   usr_sock_recvmsg_ewouldblock;

    Ipcom_atomic_t   usr_iov_emsgsize;
    Ipcom_atomic_t   usr_iov_nomem;

    Ipcom_atomic_t   pkt_netif_output_done_nonstack;
}
Ipnet_global_stats;

#define IPNET_STATS(net, xvar)      (net)->stats.xvar
#define IPNET_GLOBAL_STATS_ADD(xvar, v) \
    ipcom_atomic_add(&ipnet_shared()->gstats.xvar, (v))
#define IPNET_GLOBAL_STATS_INC(xvar) \
    ipcom_atomic_inc(&ipnet_shared()->gstats.xvar)
#define IPNET_STAT_LINE(xline)      xline

#else
#define IPNET_STATS(net, xvar)           IP_NOOP
#define IPNET_GLOBAL_STATS_ADD(xvar, v)  IP_NOOP
#define IPNET_GLOBAL_STATS_INC(xvar)     IP_NOOP
#define IPNET_STAT_LINE(xline)           IP_NOOP
#endif

#ifdef IPNET_USE_DIFFSERV
typedef struct Ipnet_diffserv_data_struct
{
    /* Array of diffserv handlers */
    Ipnet_diffserv_handlers *handlers[IPNET_DIFFSERV_MAX_HANDLERS];
#ifdef IPNET_DIFFSERV_CLASSIFIER_MODE_BA
    /* Defines which marker/meter to use for each traffic class */
    Ip_u32                   mapping_active[8];
    Ip_u8                    ds_to_handler_map[256];
#else
    /* The classifier used by diffserv */
    Ipnet_classifier        *classifier;
#endif
}
Ipnet_diffserv_data;
#endif /* IPNET_USE_DIFFSERV */


/*
 *===========================================================================
 *                        Ipnet_inq
 *===========================================================================
 *
 */
typedef struct Ipnet_input_queue_struct
{
    /* Stack input queue. */
    Ipcom_spinlock lock;        /* Protects head, tail and count variables */
    Ipcom_pkt     *head;        /* Head of the input queue (first packet to be processed) */
    Ipcom_pkt     *tail;        /* Tail of the input queue (last packet to be processed) */
    int            count;       /* Number of packets currently in the input queue */
#ifdef IPCOM_USE_JOB_QUEUE
    Ipcom_singleton_job_t job;    /* Job for processing this input queue */
#endif
}
Ipnet_inq;


/*
 *===========================================================================
 *                        Ipnet_task
 *===========================================================================
 * Information that is per IPNET daemon task.
 */
typedef struct Ipnet_task_struct
{
    Ipcom_pipe      *pipe;           /* Pipe the net-task polls for
                                        stack requests */
    Ip_pid_t         pid;            /* PID of the ipnet daemon if
                                        IPCOM_USE_JOB_QUEUE is
                                        undefined. PID of the job
                                        daemon if IPCOM_USE_JOB_QUEUE
                                        is defined */
    Ipnet_inq        inq;            /* Packet inqueue served by this
                                        daemon */
#ifndef IPCOM_USE_JOB_QUEUE
    volatile Ip_bool wakeup_pending; /* IP_TRUE if at least one wakeup
                                        signal is pending */
    Ipnet_sig       *wakeup_sig;
    Ip_u8            wakeup_sig_buf[sizeof(Ipnet_sig) - sizeof(union Ipnet_sig_data_u)];
#endif
}
Ipnet_task;


/*
 *===========================================================================
 *                        Ipnet_slabs
 *===========================================================================
 * All the slab caches used by IPNET
 */
typedef struct Ipnet_shared_slabs_struct
{
#ifdef IPNET_USE_PACKET_POOL
    Ipcom_memory_cache *pkt_hdr;
    Ipcom_memory_cache *pkt_buf_1500;
    Ipcom_memory_cache *pkt_buf_3000;
    Ipcom_memory_cache *pkt_buf_10000;
    Ipcom_memory_cache *pkt_buf_65535;
#endif
    Ipcom_memory_cache *socket;
    Ipcom_memory_cache *bound_port;

    /*
     * The poll structures must be shared to allow migrations of
     * sockets from one stack instance to another.
     */
    Ipcom_memory_cache *poll;
    Ipcom_memory_cache *sig_neigh;
}
Ipnet_shared_slabs;

typedef struct Ipnet_slabs_struct
{
    Ipcom_memory_cache *dst_cache;
    Ipcom_memory_cache *kioevent_softirq;
    Ipcom_memory_cache *neigh;
    Ipcom_memory_cache *timer;
    Ipcom_memory_cache *tcp_segment;
}
Ipnet_slabs;

/* #define IPNET_USE_EVENTLOG */
#ifdef IPNET_USE_EVENTLOG
struct Ipnet_events
{
    Ipcom_eventlog log;
    Ipcom_event    sock;
    Ipcom_event    netif;
    Ipcom_event    drv;
    Ipcom_event    drv_wouldblock;
};
#endif


typedef void (*Ipnet_kioevent_cb) (Ipnet_netif *netif, int event, void *data);

/* Data for kioevent that had to be postponed */
typedef struct Ipnet_kioevent_softirq_struct
{
    Ipnet_softirq              softirq;
    int                        event;
    Ip_u32                     ifindex;
    struct Ipnet_data_struct  *net;
    Ipnet_kioevent_cb          callback;
    unsigned                   datalen;
#define IPNET_KIOEVENT_DATALEN_MAX 16
    char                       data[IPNET_KIOEVENT_DATALEN_MAX];
}
Ipnet_kioevent_softirq;


#ifdef IPNET_USE_PACKET_POOL
/*
 *===========================================================================
 *                       Ipnet_pkt_cache
 *===========================================================================
 */

/*
 * Maximum number of packets that are allowd to be in the packet pool
 * cache. This number is a suggestion, the actual number used is
 * stored in "ipnet->pkt_cache.cnt_mask".
 */
#define IPNET_PKT_CACHE_MAX_COUNT (1 << 5)

typedef struct Ipnet_pkt_cache_entry_struct
{
    /*
     * Protects the 'top' and 'stack' members.
     */
    Ipcom_spinlock lock;
    /*
     * Index to the current top of stack. The stack is empty if 'top'
     * == IPNET_PKT_CACHE_MAX_COUNT and full if 'top' == 0.
     */
    unsigned       top;
    Ipcom_pkt     *stack[IPNET_PKT_CACHE_MAX_COUNT];
}
Ipnet_pkt_cache_entry;

typedef struct Ipnet_pkt_cache_struct
{
    /*
     * Base object (function pointers only)
     */
    Ipcom_pkt_cache       ipcom;

    /*
     * Packets can be alloced by any task, it is therefore not
     * possible to schedule a new timeout directly in
     * ipcom_pkt_malloc() or ipcom_pkt_free() as that must be done
     * from the IPNET task.
     */
    Ipnet_softirq         softirq;
    /*
     * GC timer for the packet pool cache. All cached packets will be
     * freed back to the slab allocator if the packet cache has not
     * been used since the last time this timer expired.
     */
    Ipnet_timeout        *tmo;
    /*
     * Packet header cache
     */
    Ipnet_pkt_cache_entry hdrs;

    /*
     * Only packets with data_freefunc_cookie matching this may
     * be freed into the 'pkts' cache. (Duplicate here for quick access.)
     */
    void *data_freefunc_cookie_1500;

    /*
     * Cache of packet header + packet buffer with an MTU of 1500.
     */
    Ipnet_pkt_cache_entry pkts;
}
Ipnet_pkt_cache;

#ifdef IPNET_USE_PACKET_CACHE_PER_INSTANCE
/*
 * per-stack-instance (or otherwise private) packet caches.
 * These structures assumed to be accessed only from a single
 * context (e.g. a single network task) and are not provided
 * with mutual exclusion.
 */

/*
 * The maximum number of packets per packet stack.
 * This number should be somewhat larger than the maximum
 * number of packets delivered to the stack in a single
 * network job.
 */
#define IPNET_PKT_PRIV_CACHE_LIMIT      128

/*
 * Basic packet stack structure
 */
typedef struct Ipnet_pkt_stack_struct
{
    /*
     * Current top of stack.
     * Stack is empty when tos = IPNET_PKT_PRIV_CACHE_LIMIT,
     * full when tos = 0.
     */
    unsigned tos;

    Ipcom_pkt *stack[IPNET_PKT_PRIV_CACHE_LIMIT];
}
Ipnet_pkt_stack;

/*
 * Private packet cache of bare Ipcom_pkt headers
 * and smallest-sized full packets.
 */
typedef struct Ipnet_pkt_priv_cache_struct
{
    /*
     * Base object (function pointers only)
     */
    Ipcom_pkt_cache       ipcom;

    /*
     * GC timer for the instance-private packet cache. All cached packets
     * will be freed back to the slab allocator if the packet cache has not
     * been used since the last time this timer expired.
     */
    Ipnet_timeout        *tmo;

#undef IPNET_PKT_PRIV_CACHE_STATS
#ifdef IPNET_PKT_PRIV_CACHE_STATS
    Ip_u32 fails;     /* alloc from cache fails */
    Ip_u32 succeeds;  /* alloc from cache succeeds */
    Ip_u32 spills;    /* free to cache results in spill */
#endif

    Ipnet_pkt_stack hdrs;  /* Ipcom_pkt structures only */
#ifndef IPCOM_USE_PORT_PKT_DATA
    Ipnet_pkt_stack pkts;  /* Ipcom_pkt with buffer, mtu=1500 */
#endif
}
Ipnet_pkt_priv_cache;
#endif /* IPNET_USE_PACKET_CACHE_PER_INSTANCE */

#endif /* IPNET_USE_PACKET_POOL */


/*
 *===========================================================================
 *                         Ipnet_conf
 *===========================================================================
 * See <ipnet>/config/ipnet_config.c for a description of each variable.
 */

struct Ipnet_sock_conf
{
    int anon_port_min;
    int anon_port_max;
    int default_send_buf_size;
    int default_recv_buf_size;
    int addr_notify;
    Ip_bool assign_random;
};

struct Ipnet_route_conf
{
    unsigned max_clone_count;
    Ip_bool  neigh_stale_correct;
};

#ifdef IPCOM_USE_INET
struct Ipnet_inet_conf
{
    Ip_bool sock_stream_dont_frag;
    Ip_bool udp_checksum;
    int icmp_rate_limit_bucket_size;
    int icmp_rate_limit_interval;
#ifdef IPNET_USE_RFC3927
    char *ll_if_list;
#endif
    Ip_bool multicast_per_interface_filter;
    Ip_bool random_ip_id;
};
#endif /* IPCOM_USE_INET */

#ifdef IPCOM_USE_INET6
struct Ipnet_inet6_conf
{
    int icmp_rate_limit_bucket_size;
    int icmp_rate_limit_interval;
};
#endif /* IPCOM_USE_INET6 */

struct Ipnet_conf
{
    struct Ipnet_sock_conf  sock;
    struct Ipnet_route_conf route;
#ifdef IPCOM_USE_INET
    struct Ipnet_inet_conf  inet;
#endif
#ifdef IPCOM_USE_INET6
    struct Ipnet_inet6_conf inet6;
#endif
};

/*
 * The forward information base data. All members are protected by
 * 'lock' unless stated otherwise.
 */
typedef struct Ipnet_fib_struct {
    /*
     * Protects access to all members in this structure.
     */
    Ipcom_mutex   lock;

    /*
     * Number of times the lock has been taken by the current
     * owner. Required as IPCOM mutexes does not need to support
     * recursive locking.
     */
    unsigned      lock_nesting_cnt;

    /*
     * Pid of the task currently holding 'lock'
     */
    Ip_pid_t      lock_owner;

    /*
     * Table where all route table head are stored
     */
    Ipcom_hash   *rtabs;

    /*
     * Table with all policy routing lists (one for each
     * domain/virtual router tuple)
     */
    Ipcom_hash   *policy_rules;

    /*
     * Last assigned policy identifier
     */
    Ip_u32        last_policy;
#ifdef IPNET_USE_ROUTE_TABLE_NAMES
    Ipcom_hash   *rtab_names;
#endif /* IPNET_USE_ROUTE_TABLE_NAMES */
#ifdef IPNET_USE_ROUTE_COOKIES
    Ipcom_hash   *rtab_cookies;
#endif /* IPNET_USE_ROUTE_COOKIES */

    /*
     * Incremented each time the route table changes, will never have
     * a value of 0 so that can be used to initialize such an ID to
     * invalid.
     */
    int           modification_id;
    /*
     * Total number of cloned routes
     */
    unsigned      cloned_route_cnt;

#ifdef IPNET_DEBUG
#define IPNET_ROUTE_LOCK_HISTORY_DEPTH 4
    const char   *last_locker_file[IPNET_ROUTE_LOCK_HISTORY_DEPTH];
    int           last_locker_line[IPNET_ROUTE_LOCK_HISTORY_DEPTH];
    const char   *last_unlocker_file[IPNET_ROUTE_LOCK_HISTORY_DEPTH];
    int           last_unlocker_line[IPNET_ROUTE_LOCK_HISTORY_DEPTH];
#endif /* IPNET_DEBUG */
} Ipnet_fib;


/*
 * Data for all attached network interfaces, this information is
 * shared between all stack instances. All data stored in this
 * structure has a very strict access policy:
 *
 * All members are READ-ONLY in the normal case. The members can only
 * only be written to by the primary stack instance and only after the
 * primary stack instance has suspended all the other stack instances.
 */
struct Ipnet_netif_data {
    /*
     * Contans all network interface(s) currently attached to the
     * network stack.
     */
    Ipcom_hash   *db;
#ifdef IPNET_USE_6OVER4
    /*
     * Array of all 6-over-4 tunnenl interfaces currently attached.
     */
    Ipnet_netif **arr_6over4;
    int           cnt_6over4;
#endif
    Ipcom_if_eventcb  eventcb[IPNET_MAX_IF_EVENTCB];
#ifdef IPNET_USE_FAST_IFNAME_LOOKUP
    /*
     * Interface name to Ipnet_netif instance mapping
     */
    Ipcom_hash   *ifname_db;
#endif /* IPNET_USE_FAST_IFNAME_LOOKUP */
    /*
     * Table of network interface pointers, indexed by softix.  Unlike the true interface
     * indices (netif->ifindex) referenced by the MIB, the software index (softix)
     * values always lie in the range 0 <= softix < softix_stop,
     * where softix_stop <= softix_table_size; and empty slots
     * made available when an interface is detached may be reused immediately;
     * generally the lower-numbered slots are reused first.
     * The softix is used only in cases where it is not harmful if an obsolete
     * softix reference to an old detached interface causes an action to be taken
     * on a new interface that reuses the softix.
     * However an interface that remains attached never changes its softix.
     * The table may grow when necessary.
     */
    struct Ipnet_netif_struct  **softix_table;

    /*
     * Maximum number of entries in current ipcom_netif_softix_table.
     * Always a multiple of 32.
     */
    Ip_u32 softix_table_size;

    /*
     * All indices from this onward (up to softix_table_size - 1) are unused.
     */
    Ip_u32 softix_stop;

     /*
      * The next ifindex to use
      */
    Ip_u32        next_ifindex;
};

/*
 *===========================================================================
 *                      Ipnet_socketref
 *===========================================================================
 * Socket table entry. Contains reference count, socket owner and socket 
 * pointer. sizeof (Ipnet_socketref) must be a power of two.
 */

typedef struct Ipnet_socketref_struct
{
    /* 
     * 'ref_owner' indicates the reference count (and so the validity
     * of the socket) and the stack instance owning the socket.
     */
    Ip_ptrdiff_t  ref_owner;

    /*
     * Normally, 'sock' points to the actual Ipnet_socket for a valid
     * entry. However, when the Ipnet_socketref is idle, sock holds
     * the index of the next free Ipnet_socketref, with 0 marking the end
     * of the list.
     */
    Ipnet_socket *sock;
} Ipnet_socketref;

#define IPNET_SOCKETREF_OWNER_BITS (0xfffL)
#define IPNET_SOCKETREF_INC        (0x1000L)

IP_INLINE int
IPNET_SOCKETREF_OWNER(Ip_ptrdiff_t ref_owner)
{
    /* 
     * The owner value is offset by one so that it is nonzero,
     * to distinguish 'idle' from 'transient invalid'.
     */
    return (int)((ref_owner & IPNET_SOCKETREF_OWNER_BITS) - 1);
}

IP_INLINE int
IPNET_SOCKETREF_VALID(Ip_ptrdiff_t ref_owner)
{
    return ((unsigned long)ref_owner >= (unsigned long)IPNET_SOCKETREF_INC);
}

/*
 * This one is used to check not only that the ref_owner value is valid,
 * but that it is not so high that incrementing the reference count will
 * make it roll over past zero (it's OK if it goes into negative values).
 * This test is only done by socket applications; internal protocol code
 * can increment the reference count without this check.
 */
IP_INLINE int
IPNET_SOCKETREF_VALID_INC(Ip_ptrdiff_t ref_owner)
{
    return (ref_owner > IPNET_SOCKETREF_INC);
}

IP_INLINE int
IPNET_SOCKETREF_IDLE(Ip_ptrdiff_t ref_owner)
{
    return (ref_owner == 0L);
}

/*
 *===========================================================================
 *                      Ipnet_shared_data
 *===========================================================================
 * Data shared between all stack instance
 */
#ifdef IPNET_USE_NETLINK
struct Ipnet_rtnetlink_table;
#endif

typedef struct Ipnet_shared_data_struct
{
    /*
     * Dynamic configuration, always updated by the primary stack
     * instance, read-only for all the other
     */
    struct Ipnet_conf conf;

    /*
     * Absolute time when the stack was initialized.
     */
    const Ip_s64    msec_boot;

    /*
     * Size of the largest possible socket structure that this system
     * may use.
     */
    const Ip_size_t largest_socket_size;

    /*
     * Pipe the net-task(s) uses to send responses back to
     * applications that are using the stack through the socket API
     */
    Ipcom_pipe     *response_pipe;

    /*
     * Database with all shared timers currently running.
     *
     * The timeout handler can be run by any network stack instance
     * and there is really no way to know which stack instance that
     * will run a specific shared timeout handler.
     */
    struct Ipnet_timeos_struct *timeos;

    /*
     * Network interface specific information. Not protected by the
     * IPNET critical region, read how to access this structure at the
     * definition of the Ipnet_netif_data structure.
     */
    struct Ipnet_netif_data netif;

    /*
     * Pointer to a dummy interface that will just discard anything
     * sent to it. This member is read-only
     */
    const Ipnet_netif *neigh_netif_discard_singleton;

    /* IP version 4 */
#ifdef IPCOM_USE_INET
    Ipnet_ip4_shared_data ip4;
    /* Multicast routing */
#ifdef IPNET_USE_MCAST_ROUTING
    Ipcom_hash           *ip4_mcast;
#endif
#endif /* IPCOM_USE_INET */

    /* IP version 6 */
#ifdef IPCOM_USE_INET6
    Ipnet_ip6_shared_data ip6;
#ifdef IPNET_USE_MCAST_ROUTING
    Ipcom_hash           *ip6_mcast;
#endif
#endif

    /*
     * Memory pool used for all shared slabs
     */
    Ipcom_memory_pool  *memory_pool;
    Ipnet_shared_slabs  slabs;

#ifdef IPNET_USE_PACKET_POOL
    /* Packet pool */
    Ipcom_spinlock   pkt_pool_lock;     /* Protects the slab caches
                                           used to implement the pool */
    unsigned         pkt_pool_wait_cnt; /* Number of processes waiting
                                           (on pkt_pool_sem) or about
                                           to wait for more free
                                           packets in this pool */
    Ipcom_sem        pkt_pool_sem;      /* Semaphore used to put
                                           processes to sleep while
                                           they wait for more packets
                                           to become available in
                                           this pool. */
    Ipnet_timeout   *pkt_pool_tmo;      /* Protected by the timeout
                                           lock: next wakeup for
                                           processes waiting for more
                                           packets to become
                                           available */
    Ipnet_pkt_cache  pkt_cache;

    Ipnet_softirq    pkt_slab_softirq;  /* Schedules pkt_slab_tmo on
                                           primary stack instance */
    Ipnet_timeout   *pkt_slab_tmo;      /* Timeout to garbage-collect
                                           empty packet slabs */

    /*
     * This softirq must only be run by the stack instance with the ID
     * returned by ipnet_first_instance_idx(). Will notify tasks
     * waiting for more packet to be available that they may try to
     * allocate packet again.
     */
    Ipnet_softirq    pktavail_softirq;
#ifdef IPNET_DEBUG
    Ipcom_pkt       *allocated_pkt_list; /* List of currently allocated packets */
#endif
#endif /* IPNET_USE_PACKET_POOL */

    /*
     * sockets_lock protects the process of claiming new slots in the
     * socket_refs table, and releasing old slots in the table.  That is,
     * it is used during socket creation and closure.  It is not generally
     * used when acquiring a reference to a particular socket or when
     * determining the stack instance owning a socket.
     *
     * In addition to socket_refs, this lock protects the free_fd_head
     * and free_fd_tail members.
     */
    Ipcom_spinlock   sockets_lock;
    /*
     * Mapping from socket descriptor used in the BSD socket API to
     * the corresponding Ipnet_socket instance, as well as owner information
     * and reference count. 'socket_refs' is an array of length
     * 'ipnet_conf_max_sockets'.
     * Note for NAE builds: the memory pointed to by 'sockets' is
     * located in memory shared by all NAE instances.
     * Iterating over all slots in the socket_refs table is discouraged.
     */
    Ipnet_socketref *socket_refs;

    /*
     * The free socket slots list is linked through the Ipnet_socketref
     * 'sock' member (cast as an Ip_fd index into the table), and guarded
     * by the sockets_lock. Free slots are claimed and released in FIFO order
     * to avoid immediate socket fd recycling. A zero value indicates the
     * end of the list.
     */
    Ip_fd            free_fd_head;   /* first slot in free socket_refs list */
    Ip_fd            free_fd_tail;   /* last slot in free socket_refs list */

    /*
     * 'reachable_sockets' is an array of list heads of length
     * 'reachable_socket_len'. Each list contains zero or more
     * Ipnet_socket instances chained with the 'reachable_list'
     * member. A socket lookup is done by calculating a hash value
     * based on source address/port, destination address/port, IP
     * protocol and VR index. That hash value is used as an index into
     * the reachable_sockets array. Each socket in the list is tested
     * until a match is found or all sockets have been investigated (no
     * matching socket).
     * Note for NAE builds: the memory pointed to by
     * 'reachable_sockets' is located in memory shared by all NAE
     * instances.
     *
     * reachable_sockets_lock is a reader/writer semaphore protecting
     * all the reachable sockets hash bucket lists against concurrent
     * access & modification. The reachable_sockets_lock also protects
     * the bound_ports list, the router alert list, and (at bind/unbind time)
     * the list of sockets bound to an address entry.
     * If the reachable sockets lock and the ipnet critical region
     * ever need to be acquired together, the reachable sockets lock
     * should be acquired first. Note also that the reachable sockets
     * lock may be held while queueing RX packets to sockets in some
     * protocols...
     * If reachable_sockets_lock and sockets_lock are acquired together,
     * then reachable_sockets_lock must be aquired first; this is done
     * in ipnet_sock_update_reuse().
     */
    Ipcom_rwsem      reachable_sockets_lock;
    Ipcom_list      *reachable_sockets;
    Ip_size_t        reachable_sockets_len;

    /*
     * 'bound_ports' is a list that contains zero or more
     * Ipnet_bound_port instances chained with the 'list'
     * member. This structure keep track of which ports that are in
     * use for a specific IP-protocol, socket domain and VR-index.
     * Note for NAE builds: the memory pointed to by
     * 'bound_ports' is located in memory shared by all NAE
     * instances. (Ipnet_bound_port is defined privately in ipnet_sock.c.)
     */
    Ipcom_list      *bound_ports;

#ifdef IPNET_USE_ROUTER_ALERT
    /*
     * List of Ipnet_router_alert_sock instances. This is the set of
     * sockets that are interested in packets that carry the router
     * alert option.  This list is protected by the reachable sockets lock.
     */
    Ipcom_list router_alert_list;
#endif

    /*
     * IPNET_FLAG_xxx flags, must only be modified inside the IPNET
     * critical region.
     */
    Ip_u32        flags;

    /*
     * Forward Information Base a.k.a the route table(s).
     */
    Ipnet_fib     fib;

#ifdef IPNET_USE_DIFFSERV
    /*
     * Database of meter/marker constructors, is initialized once at
     * boot and is read-only after that.
     */
    Ipcom_hash   *diffserv_meter_marker_ctor_db;
#endif /* IPNET_USE_DIFFSERV */

#ifdef IPCOM_USE_PACKET
    /*
     * Number of packet sockets currently active
     */
    int          num_packet_sock;
#endif

    /* Route/netlink sockets. */
#ifdef IPNET_USE_ROUTESOCK
    /*
     * Number of routing sockets.
     */
    int          num_route_sock;
#endif
#ifdef IPNET_USE_NETLINKSOCK
    /*
     * Number of netlink sockets.
     */
    int                      num_netlink_sock;

    /*
     * This member is initialized at boot and considered read-only
     * after that. No lock is therefore required to access this
     * member.
     */
    struct Ip_rtnl_link_ops *rtnetlink_ops;
#endif
#ifdef IPNET_USE_NETLINK
    /*
     * This member is initialized at boot and considered read-only
     * after that. No lock is therefore required to access this
     * member.
     */
    void                    *netlink_data[IP_NETLINK_MAX];
#endif

    /* VLAN stacking */
#ifdef IPNET_USE_VLAN_STACKING
    Ip_u16      vlan_s_tpid;
    Ip_u16      vlan_s_tpid_net;   /* S-VLAN TPID in network order format */
#endif

#ifdef IPNET_USE_NAT
    /* NAT */
    Ipnet_nat_data nat;
#endif

#ifdef IPBRIDGE
    /* Bridge control structure */
    struct Ipnet_bridge_st *bridge;
#endif

    /*
     * Collection of queue constructors. All ctors must be added at
     * boot by the ipnet_pkt_queue_init() function. This DB is
     * read-only when the stack is running.
     */
    Ipcom_hash    *queue_db;

    /*
     * State IPNET of the startup
     */
    enum Ipnet_startup_state startup_state;

    /*
     * OS port specific to attach new devices to the stack
     */
    Ipnet_if_attach_handler if_attach_handler;

    /*
     * IPNET observer for sysvar changes, updates are always run by
     * the primary stack instance.
     */
    Ipcom_observer sysvar_observer;

#ifndef IPCOM_HAS_STACK_SUSPEND_RESUME
    /*
     * Semaphores pointed to by each stack instance specific
     * 'sig_suspend' signal used to suspend all but the primary stack
     * instance. The atomic variables is used to keep track on how
     * many stack instances that has not suspended yet.
     */
    Ipcom_sem      suspend_complete_sem;
    Ipcom_sem      suspend_resume_sem;
    Ipcom_atomic_t suspends_pending;
#endif

    Ipnet_softirq  stack_shutdown_softirq;

    /*
     * List of tasks waiting for the stack to finish shutdown. May
     * only be written to or read by the primary stack instance so
     * does not need any additional locking.
     */
    Ipnet_sig     *stack_shutdown_waiters;

    /*
     * Protects modification of all members in this structure unless
     * stated otherwise. Lock/unlock this via
     * ipnet_[enter|exit]_critical_region().
     */
    Ipcom_mutex    mutex;

    /*
     * Protects the broacast_job_* members.
     */
    Ipcom_spinlock broadcast_job_lock;

    /*
     * Queue (fixed sized ring buffer) of Ipnet_broadcast_job jobs that should
     * be run on all stack instances. Each job must be safe to run concurrently,
     * with the job and its data shared among all the instances. Used (for example)
     * in ICMP redirect handling. The last instance to finish deletes
     * the job and any associated resources (e.g. a packet).  Not to be
     * used for performance-critical work due to the global sharing and
     * locking. The jobs run in a softirq handler in each network task.
     *
     * If the ring is full when one attempts to enqueue a job, the job
     * is not enqueued but its free routine is called. Once enqueued,
     * a job may not be re-enqueued.
     */
    Ipnet_broadcast_job ** broadcast_job_ring;

    Ip_u32 broadcast_job_head;  /* head ring buffer index */
    Ip_u32 broadcast_job_tail;  /* tail ring buffer index */

#ifdef IPNET_DEBUG
    /*
     * The PID of the entity currently executing witin the IPNET
     * critical region or 0.
     */
    Ip_pid_t       pid_inside_critical_region;

    /*
     * Must hold 'mutex' while accessing these variables.
     */
    Ip_size_t                     tmo_map_sz;
    Ipnet_cmd_tmo_handler_to_str *tmo_map;
#endif

    /* PPP and PPPoE support */
#ifdef IPPPP
    Ipppp_ipstack_data   ppp;
#endif

#if defined(IPNET_DEBUG) || defined(IPNET_STATISTICS)
    Ipnet_global_stats gstats;
#endif

} Ipnet_shared_data;


/* Ipnet_shared_data flags: */
#define IPNET_FLAG_IPV4_FORWARD_PKT     0x02    /* Set if IPv4 packets should be forward */
#define IPNET_FLAG_IPV6_FORWARD_PKT     0x04    /* Set if IPv6 packets should be forward */
#ifdef IPNET_USE_SOCKET_PKTAVAIL_CB
#define IPNET_FLAG_PKTAVAIL_CB_PENDING  0x10    /* A non-blocking socket call, on a socket with a */
                                                /* callback handler, failed due to no packets in
                                                   the packet pool */
#endif
#define IPNET_FLAG_IPV6_RFC4941_INIT    0x20    /* IPv6 privacy extension has been initialized */

/*
 * Set to put IPNET in strict mode, unset for loose mode.
 * Strict mode requires packet to enter on the correct interface to be
 * considered local. Loose mode will accept the packet if any interface
 * has the unicast address. Most OS:es uses loose mode.
 */
#define IPNET_FLAG_IPV4_STRICT_MODE     0x40    /* Set to enable ipv4 strict mode in ipnet stack */
#define IPNET_FLAG_IPV6_STRICT_MODE     0x80    /* Set to enable ipv6 strict mode in ipnet stack */



/*
 *===========================================================================
 *                        Ipnet_data
 *===========================================================================
 * Data private to a specific stack instance
 */

/*
 * Stack instance to stack instance communication. The stack instances
 * should avoid using the pipe mechanism for comminication as a call
 * to ipcom_pipe_send() may block. It is even illegal for the primary
 * stack instance to ever use a pipe to another stack instance as that
 * might lead to dead-lock.  Use the function ipnet_sendto_instance()
 * to perform stack instance to stack instance communication.
 */
struct Ipnet_intercom {
    /*
     * Lock that protects 'head'
     */
    Ipcom_spinlock lock;

    unsigned       count;             /* current number of enqueued signals */
    unsigned       congestion_limit;  /* number of enqueued signals considered 'congested' */
  
    /*
     * Linked list of pending signals
     */
    Ipnet_sig     *head;

    Ipnet_sig    **ptail;

    /*
     * job or softirq that will fire when there a stack instance needs to
     * check the 'head' list.
     */
#ifdef IPCOM_USE_JOB_QUEUE
    Ipcom_singleton_job_t remote_sig_job;
#else
    Ipnet_softirq  softirq;
#endif
};


/*
 * Per stack instance data for the destination cache.
 */
struct Ipnet_dst_cache_data
{
    /*
     * Hash table where all the destination cache entries are stored.
     */
    Ipcom_hash *db;

    /*
     * Destination cache entry that will discard any packets
     * transmitted or received using that flow.
     */
    Ipnet_dst_cache blackhole_singleton;

    /*
     * Softirq for remote requests to flush this instance's destination
     * cache entries.
     */
    Ipnet_softirq   flush_softirq;

    /*
     * Encodes which destination cache entries should be flushed.
     * Treated cumulatively.
     */
    Ipcom_atomic_t  flush_sched;

    /*
     * Timeout to periodically transfer usage counts from
     * destination cache entries to the underlying (non-cloning)
     * routes.
     */
    Ipnet_timeout   use_xfer_tmo;
};


/*
 * Per stack instance data for TCP
 */
#ifdef IPTCP
struct Ipnet_tcp_data
{
    /*
     * List of TCP finished segments that are waiting to be transmitted.
     * This list points to the last TCP segment to be sent.
     */
    Ipcom_pkt  *iptcp_tx_list;
    /*
     * List of active sockets. All of the sockets in this list must be
     * checked for timeouts each tick.
     */
    Ipcom_list     active_head;
    /*
     * Timer for the closest (in time) TCP timeout.
     */
    Ipnet_timeout *tmo;
    /*
     * Absolute time when the next IPTCP timer expires, valid only if
     * 'tmo' is != IP_NULL.
     */
    Ip_s64 next_timeout_abs_msec;

    /*
     * List of TCBs in states that are short lived under normal
     * operations. SYN_RCV, FIN_WAIT_1 & LAST_ACK. The session that
     * has been in this state for the longest time is sitting at the
     * front of the list. The sysvar iptcp.MaxTransient limits the number
     * of TCBs on this list; if the limit is exceeded, the oldest
     * connection on the transient list is dropped.
     */
    Ipcom_list     transient_head;

    /*
     * List of TCBs for sockets that an application has called close() on.
     * These TCBs may be (for example) in TIME_WAIT state; if the socket
     * table is full and a call to socket() or a new child connection would
     * otherwise fail, a TCB/socket at the start of this list may be
     * sacrificed, terminating the TIME_WAIT state early.
     *
     * Ideally this list would be global, so that the sacrificed socket was
     * the oldest among TCBs of all stack instances (and not just of the
     * current stack instance); and so that if the current stack instance had
     * no TCBs on the list one could sacrifice a TCB from another instance.
     * However, that is presently hard to do safely. With the current syncronous
     * mechanism of trying to sacrifice a closed TCB and then immediately
     * retrying socket allocation, a global list would require one stack
     * instance dropping a TCB (and cancelling timers) owned by another stack
     * instance.  For now we put up with the safer per-stack-instance list.
     */
    Ipcom_list     user_closed_sock_head;

};
#endif

/*
 * Per stack instance data for SCTP
 */
#ifdef IPSCTP
struct Ipnet_sctp_data
{
    /* List of SCTP finished segments that are waiting to be transmitted. 
     * This list points to the last SCTP segment to be sent 
     */
    Ipcom_pkt  *ipsctp_tx_list;
};
#endif


typedef struct Ipnet_data_struct
{
    Ipcom_memory_pool *memory_pool;
    Ipnet_slabs        slabs;

    /*
     * Stack instance intercommunication channel.
     */
    struct Ipnet_intercom intercom;

    /*
     * Number of milliseconds the stack has been running.
     */
    Ip_s64          msec_now_;
    /*
     * Number of seconds the stack has been running
     */
    Ip_u32          sec_now;
    /*
     * Database with all timers currently running on this stack
     * instance.
     */
    Ipcom_pqueue   *timeouts;
    /*
     * IP_TRUE if 'msec_now' and 'sec_now' may be stale and needs an
     * update.
     */
    Ip_bool         update_internal_timer;

    /*
     * Static timeout to update time base.
     */
    Ipnet_timeout   update_time_tmo;

    /*
     * Information for static per-instance timeout used to implement
     * shared timeouts.  This timer is scheduled to the expiration time of the
     * first shared timer each time ipnet_shared_static_tmo_reschedule()
     * is called in the context of this stack instance. This means
     * that this timer might fire and there is nothing to run because
     * some other stack instance has canceled or already run the
     * shared timers.
     */
    Ipnet_timeos_instance shared_timeos_inst;

    /*
     * Destination cache
     */
    struct Ipnet_dst_cache_data dst_cache;

    /*
     * Hash table that contains all the neighbors this stack instance
     * on this node knows about
     */
    Ipcom_hash  *neigh_db;

#ifdef IPCOM_USE_JOB_QUEUE
    Ipcom_singleton_job_t timeout_job;    /* Handle for timeout processing job */
#endif

    /* Soft interrupts, softirq_xxx can only be modified with interrupts disabled */
    Ipcom_spinlock  softirq_lock;       /* Protects all 'softirq_xxx' variables. A restricted spinlock. */
    Ip_bool         softirq_pending;    /* Set to IP_TRUE if at least 1 soft interrupt is pending */
    Ipnet_softirq  *softirq_head;       /* Points to the first soft interrupt to run */
    Ipnet_softirq **softirq_tailp;      /* Points to pointer in which to add another softirq */
#ifdef IPCOM_USE_JOB_QUEUE
    Ipcom_singleton_job_t softirq_job;    /* Handle for softirq processing job */
#endif

    Ipnet_softirq   drain_softirq;      /* Static buffer to signal drain soft interrupts */
    Ipnet_softirq   pktnew_softirq;     /* Static buffer to that more packets must be added to the pool */

    /*
     * List of sockets waiting to be freed as the last reference to
     * them has been released. Note that these members may only be
     * accessed while holding the 'sockets_lock'.
     */
    Ip_bool        socket_free_pending;
    int            free_next_fd;
    int            free_last_fd;
    Ip_u8          socket_free_sig[sizeof(Ipnet_sig) - sizeof(union Ipnet_sig_data_u)];

    /*
     * The PID of the process that sent the signal that we are
     * currently processing. This is needed since the BSD socket API
     * calls is handled by the network stack task on behalf of the
     * task/process using the BSD socket API.
     */
    Ip_pid_t       effective_pid;

#if IPCOM_VR_MAX > 1
    Ip_u16         effective_vr;
#endif

    Ipnet_inq     inq;                  /* Queue for RX packets + task that inputs them to the stack */

    Ipnet_task    task;

    /*
     * Value that can be manipulated via the
     * IP_X_SIOCSDEBUG/IP_X_SIOCGDEBUG ioctl(). This value is not used
     * anywhere in the stack. The indented usage is to create
     * breakpoints that will only trigger if 'debug' has a specific
     * value.
     */
    int debug;

#ifndef IPCOM_HAS_STACK_SUSPEND_RESUME
    /*
     * Set to IP_TRUE if this instance currently is suspended.
     */
    Ip_bool is_suspended;
#endif

    /*
     * Temporary storage to create log messages, anything stored here
     * might be overwritten by any function.
     */
    char          log_buf[256];

#ifdef IPNET_DEBUG
    Ipcom_rwsem_lock_mode reachable_sockets_lock_mode;
#endif

#ifdef IPTCP
    struct Ipnet_tcp_data tcp;
#endif

#ifdef IPSCTP
    struct Ipnet_sctp_data sctp;
#endif

    /* PPP and PPPoE support */
#ifdef IPPPP
    Ipppp_data   ppp;
#endif

#ifdef IPCOM_USE_INET6
     /*
      * Used by ipnet_ip6_get_mapped_ip4_src_addr_ext() to return an
      * IPv4-mapped IPv6 address based on an IPv4 address.
      */
     struct Ip_in6_addr  ip6_addr_buf;
#endif

    /* Differentiated Services */
#ifdef IPNET_USE_DIFFSERV
    Ipnet_diffserv_data diffserv;
#endif /* IPNET_USE_DIFFSERV */

#ifndef IPCOM_HAS_STACK_SUSPEND_RESUME
    /*
     * Signal used to suspend all but the primary stack instance. This
     * operation is performed before data shared between all stack
     * instances must be written to. Examples of such data are all
     * network interfaces (Ipnet_netif instances) and neighbor
     * (Ipnet_neigh instances).
     */
    Ipnet_sig   sig_suspend;
#endif

    /*
     * Stack instance index. View this member as private, mapping a
     * Ipnet_data* to the corresponding index must be done via
     * ipnet_instance_idx(Ipnet_data *)
     */
    int             stack_instance_idx;

#ifdef IPNET_USE_PACKET_POOL
#ifdef IPNET_USE_PACKET_CACHE_PER_INSTANCE
    Ipnet_pkt_priv_cache pkt_priv_cache;
#endif
#endif
#ifdef IPCOM_USE_JOB_QUEUE
    Ipcom_singleton_job_t netif_push_job;
#else
    Ipnet_softirq         netif_push_softirq;
#endif
    Ip_u32               *netif_push_bitmap;
    Ip_bool               netif_push_scheduled;

    Ip_u32        broadcast_job_ix;
    Ipnet_softirq broadcast_job_softirq;

#ifdef IPROHC
    Ipnet_timeos_instance iprohc_timeos_inst;
#endif

#ifdef IPSNTP
    Ipnet_timeos_instance ipsntp_timeos_inst;
#endif


#ifdef IPNET_USE_NAT
    Ipnet_timeos_instance nat_timeos_inst;
#endif

#ifdef IPFIREWALL
    Ipnet_timeos_instance firewall_timeos_inst;
#endif

#ifdef IPIPSEC2
    Ipnet_timeos_instance ipipsec_timeos_inst;
#endif

    /* MIB-2 */
#ifdef IPCOM_USE_MIB2
    Ipcom_mib2_stats mib2; /* per stack instance */
#endif

    /*
     * Statistics (per stack instance)
     */
#if defined(IPNET_DEBUG) || defined(IPNET_STATISTICS)
    Ipnet_stats   stats;
#endif

}
Ipnet_data;


/*
 *===========================================================================
 *                         Ipnet_pmtu_cb_data
 *===========================================================================
 */
typedef struct Ipnet_pmtu_cb_data_struct
{
    /*
     * Note, when IPCOM_USE_INET6 is enabled, we store the IPv4 address
     * as an IPv4-mapped IPv6 address! Use IP_ADDR_UN_IP4() to get the IPv4
     * part.
     */
    union Ip_in_addr_union src;
    union Ip_in_addr_union dst;
    const Ipcom_pkt * pkt;
    Ip_u32 new_path_mtu;
#ifdef IPCOM_USE_INET6
    Ip_u32 src_zone_id;
    Ip_u32 dst_zone_id;
#endif
    Ip_u16 domain;
    Ip_u16 vr_index;
    Ip_u16 src_port;
    Ip_u16 dst_port;
    Ip_u16 proto;
} Ipnet_pmtu_cb_data;

/*
 *===========================================================================
 *                         Ipnet_lock_state
 *===========================================================================
 */
#ifdef IP_PORT_LKM
typedef struct Ipnet_lock_state_struct
{
    Ip_bool       has_write_lock;
    Ip_bool       has_snd_rcv_lock;
    Ipnet_socket *sock;
}
Ipnet_lock_state;
#endif

/*
 ****************************************************************************
 * 6                    PROTOTYPES
 ****************************************************************************
 */

IP_EXTERN IP_FASTDATA Ipnet_sock_ops         **ipnet_sock_ops;
IP_EXTERN Ipcom_cmd_int_str_map    ipnet_bool_map[];

/*
 * These pointers should never be accessed directly, use the ipnet()
 * and ipnet_shared() functions instread. The pointers are declared
 * 'const' to make it easy to detect direct use, the data pointed to
 * is not const.
 */
IP_EXTERN const Ipnet_data       **ipnet_inst;
IP_EXTERN const Ipnet_shared_data *ipnet_shared_data;

IP_EXTERN unsigned ipnet_conf_max_sockets_offset;

/*
 *===========================================================================
 *                         Driver/link upcalls
 *===========================================================================
 */

/*
 * This function can be called outside of the network stack, it will
 * then post an event and run the kioevent() in a stack context.
 */
IP_PUBLIC void ipnet_kioevent(Ipnet_netif *netif, int command,
                              void *data, int fcflags);

/* This is the function used to post an ioevent to the primary stack context */
IP_GLOBAL int  ipnet_kioevent_post(Ipnet_netif *netif, int event,
                                   void *data, unsigned datalen,
                                   Ipnet_kioevent_cb callback);

/* This function must execute only in the primary stack instance */
IP_GLOBAL void ipnet_kioevent_now(Ipnet_netif *netif, int command,
                                  void *data);


/*
 *===========================================================================
 *                    IPNET stack instance functions
 *===========================================================================
 */

/*
 * Returns a pointer to the data that is shared between all IPNET
 * stack instances.
 */
IP_INLINE Ipnet_shared_data * ipnet_shared()
{
    ip_assert(ipnet_shared_data != IP_NULL);
    return (Ipnet_shared_data*)ipnet_shared_data;
}

/*
 * Returns a pointer to an IPNET instance state.
 */
IP_INLINE Ipnet_data * ipnet(int instance_idx)
{
    Ipnet_data **p = (Ipnet_data**) ipnet_inst;
    ip_assert((unsigned)instance_idx < (unsigned)ipnet_conf_max_instances);
    return p[instance_idx];
}

/*
 * Runs a statement with 'net' and 'idx' to each network instance
 * available in this system
 */
#define IPNET_FOR_EACH_INSTANCE(net, idx)                       \
    for (idx = 0; idx < ipnet_conf_max_instances; idx++)        \
        if ((net = ipnet(idx)) != IP_NULL)

/*
 * Returns the index of the currently running stack instance. This
 * function must only be called when running in the context of one of
 * the stack tasks.
 */
IP_GLOBAL int ipnet_this(void);

/*
 * Set the currently running stack index. Used only during stack
 * initialization.
 */
IP_GLOBAL void ipnet_this_is(int stack_idx);

/*
 * Returns the index of the primary stack instance. This stack
 * instance is always present and is the instance that runs functions
 * that need to be handled by exactly one stack instance.
 */
IP_INLINE int ipnet_primary_instance_idx()
{
    return 0;
}


/*
 * Returns the index of the passed stack instance pointer
 */
IP_INLINE int ipnet_instance_idx(const Ipnet_data *net_arg)
{
#ifdef IPNET_DEBUG
    int         idx;
    Ipnet_data *net;

    IPNET_FOR_EACH_INSTANCE(net, idx)
        if (net == net_arg)
            return idx;
    IP_PANIC();
    return -1;
#else
    return net_arg->stack_instance_idx;
#endif
}

IP_INLINE Ipnet_data *ipnet_ptr(void)
{
    return ipnet(ipnet_this());
}

IP_INLINE Ipnet_data *ipnet_pri_ptr(void)
{
    return ipnet(ipnet_primary_instance_idx());
}

/*
 * Returns the stack instance index currently assigned to process this
 * packet.
 */
IP_INLINE int
ipnet_pkt_get_stack_idx(const Ipcom_pkt *pkt)
{
    return (int)pkt->stack_idx;
}

/*
 * Returns the stack instance index that originally received this packet.
 */
IP_INLINE int
ipnet_pkt_get_orig_idx(const Ipcom_pkt *pkt)
{
    return (int)pkt->orig_idx;
}

IP_INLINE int
IPNET_SOCKETREF_FD_VALID(Ip_fd fd)
{
    return IPNET_SOCKETREF_VALID(ipnet_shared()->socket_refs[fd].ref_owner);
}

/*
 * Claim a socketref, incrementing its reference count if possible.
 * inc_safe should be passed as a compile-time constant. When it is
 * nonzero, the reference count must satisfy IPNET_SOCKETREF_VALID_INC()
 * instead of just IPNET_SOCKETREF_VALID().
 * Returns IP_TRUE if successful, IP_FALSE if the socketref was invalid
 * or if inc_safe was true and the reference count was too large to increment.
 * For the 'non-safe' case here used by protocol code, we could use a
 * simple atomic increment here if one was available for Ip_ptrdiff_t ...
 */
IP_INLINE Ip_bool
ipnet_socketref_claim(Ipnet_socketref *pref, Ip_bool inc_safe)
{
    Ip_ptrdiff_t ref;

    do
    {
        ref = *(volatile Ip_ptrdiff_t *)&pref->ref_owner;
        if ((!inc_safe && !IPNET_SOCKETREF_VALID(ref)) ||
            (inc_safe && !IPNET_SOCKETREF_VALID_INC(ref)))
            return IP_FALSE;
    } while (!ipcom_atomic_ptr_cas(&pref->ref_owner, ref, 
                                   ref + IPNET_SOCKETREF_INC));
    return IP_TRUE;
}

/*
 * Protocol code may increment a socket's reference count when the
 * socket pointer is already held.
 */
IP_INLINE void
ipnet_socketref_claim_sock(Ipnet_socket *sock)
{
    Ipnet_socketref *pref = &ipnet_shared()->socket_refs[sock->ipcom.fd];
    Ip_ptrdiff_t ref;
    do
    {
        ref = *(volatile Ip_ptrdiff_t *)&pref->ref_owner;
        ip_assert(IPNET_SOCKETREF_VALID(ref));
    } while (!ipcom_atomic_ptr_cas(&pref->ref_owner, ref, 
                                   ref + IPNET_SOCKETREF_INC));
}

/*
 * Returns IP_TRUE if this call released the last reference count
 * for sock.
 */
IP_INLINE Ip_bool
ipnet_socketref_release(Ipnet_socketref *pref)
{
    Ip_ptrdiff_t ref;

    do
    {
        ref = *(volatile Ip_ptrdiff_t *)&pref->ref_owner;
        ip_assert(IPNET_SOCKETREF_VALID(ref));
    } while (!ipcom_atomic_ptr_cas(&pref->ref_owner, ref, 
                                   ref - IPNET_SOCKETREF_INC));
    return ((unsigned long)ref <  (unsigned long)(2 * IPNET_SOCKETREF_INC));
}

/*
 * Returns IP_TRUE if this call released the last reference count
 * for sock.
 */
IP_INLINE Ip_bool
ipnet_socketref_release_sock(Ipnet_socket *sock)
{
    Ipnet_socketref *pref = &ipnet_shared()->socket_refs[sock->ipcom.fd];
    return ipnet_socketref_release(pref);
}

/*
 * Return the stack instance index of the owner of fd, or -1 if fd is invalid.
 */
IP_INLINE int
ipnet_fd_owner(Ip_fd fd)
{
    Ipnet_socketref *pref;
    Ip_ptrdiff_t ref;
    if (IP_LIKELY(IPNET_FD_RANGE_OK(fd)))
    {
        pref = &ipnet_shared()->socket_refs[fd];
        ref = *(volatile Ip_ptrdiff_t *)&pref->ref_owner;
        if (IPNET_SOCKETREF_VALID(ref))
            return IPNET_SOCKETREF_OWNER(ref);
    }
    return -1;
}

/*
 * Returns the stack instance associated with this packet.
 */
IP_INLINE Ipnet_data *
ipnet_pkt_get_stack_instance(Ipcom_pkt *pkt)
{
    ip_assert((int)pkt->stack_idx == ipnet_this());
    return ipnet(pkt->stack_idx);
}

/*
 * Associate a packet with a specific stack instance.
 */
IP_INLINE void
ipnet_pkt_set_stack_instance(Ipcom_pkt *pkt, Ipnet_data *net)
{
    pkt->stack_idx = (Ip_s16)ipnet_instance_idx(net);
}

/*
 * Set the original RX stack instance of a packet to match the
 * current stack index.
 */
IP_INLINE void
ipnet_pkt_set_orig_instance(Ipcom_pkt *pkt)
{
    pkt->orig_idx = pkt->stack_idx;
}

#ifdef IPNET_USE_PACKET_POOL
#ifdef IPNET_USE_PACKET_CACHE_PER_INSTANCE

IP_GLOBAL void ipnet_pkt_cache_priv_init(Ipnet_pkt_priv_cache *cache);

/*
 *===========================================================================
 *                    ipnet_pkt_stack_malloc
 *===========================================================================
 * Description: Allocates a packet with the requested amount of MTU data.
 *              MTU data is defined as IP + transport + application (not
 *              link header).
 *              Attempts to allocate the packet from the specified stack
 *              instance's private packet cache before, falling back to the
 *              shared ipnet packet pool.
 *              Must be called only from a network stack task context.
 * Parameters:  [in] mtu - The amount of payload the packet must be able to hold.
 *              [in] fcflags - IP_FLAG_FC_xxx flags.
 *              [in] stack_idx - The calling stack instance index.
 * Returns:     An uninitialized packet.
 *
 */
#ifdef IP_DEBUG
#define ipnet_pkt_stack_malloc(m, f, i) \
   ipnet_pkt_stack_dmalloc(m, f, i, __FILE__, __LINE__)

IP_INLINE Ipcom_pkt *
ipnet_pkt_stack_dmalloc(Ip_size_t mtu, int fcflags, unsigned stack_idx, char *file, int line)
#else
IP_INLINE Ipcom_pkt *
ipnet_pkt_stack_malloc(Ip_size_t mtu, int fcflags, unsigned stack_idx)
#endif
{
    Ipnet_data *net = ipnet((int)stack_idx);
#ifdef IP_DEBUG
    return ipcom_pkt_cache_dmalloc(mtu, fcflags, &net->pkt_priv_cache.ipcom, file, line);
#else
    return ipcom_pkt_cache_malloc(mtu, fcflags, &net->pkt_priv_cache.ipcom);
#endif
}

/*
 *===========================================================================
 *                    ipnet_pkt_stack_free
 *===========================================================================
 * Description: Frees a previously allocated packet. When possible, frees
 *              the packet to the specified stack instance's private packet
 *              cache, rather than to the shared ipnet packet pool.
 *              Must be called from a network stack task context.
 * Parameters:  pkt - the packet to free.
 *              stack_idx - the calling stack instance index.
 * Returns:
 *
 */
#ifdef IP_DEBUG
#define ipnet_pkt_stack_free(p, i) \
   ipnet_pkt_stack_dfree(p, i, __FILE__, __LINE__)

IP_INLINE void
ipnet_pkt_stack_dfree(Ipcom_pkt *pkt, unsigned stack_idx, char *file, int line)
#else
IP_INLINE void
ipnet_pkt_stack_free(Ipcom_pkt *pkt, unsigned stack_idx)
#endif
{
    Ipnet_data *net = ipnet((int)stack_idx);
#ifdef IP_DEBUG
    ipcom_pkt_cache_dfree(pkt, &net->pkt_priv_cache.ipcom, file, line);
#else
    ipcom_pkt_cache_free(pkt, &net->pkt_priv_cache.ipcom);
#endif
}

#define IPNET_PKT_PRIV_CACHE(net) (&(net)->pkt_priv_cache.ipcom)

#else /* IPNET_USE_PACKET_CACHE_PER_INSTANCE */

#define ipnet_pkt_stack_malloc(mtu, fcflags, stack_idx) \
     ipcom_pkt_malloc((mtu), (fcflags))

#define ipnet_pkt_stack_free(pkt, stack_idx) ipcom_pkt_free((pkt))

/* Packet cache to use when the per-instance cache is not available: */
#define IPNET_PKT_PRIV_CACHE(net) (&ipnet_shared()->pkt_cache.ipcom)

#endif /* IPNET_USE_PACKET_CACHE_PER_INSTANCE */
#endif /* IPNET_USE_PACKET_POOL */

#ifdef IPNET_DEBUG
IP_GLOBAL Ip_bool ipnet_is_inside_critical_region(void);
#endif
IP_GLOBAL Ip_bool ipnet_is_stack_task(void);

#ifdef IPCOM_HAS_STACK_INDEX_FUNC
IP_INLINE int ipnet_stack_index(void)
{
    return ipcom_stack_index();
}
#else
IP_GLOBAL int ipnet_stack_index();
#endif


/*
 *===========================================================================
 *                         IPNET Internal
 *===========================================================================
 */

IP_INLINE void ipnet_sockets_lock(void)
{
    IPNET_DATA_LOCK(ipnet_shared()->sockets_lock);
}

IP_INLINE void ipnet_sockets_unlock(void)
{
    IPNET_DATA_UNLOCK(ipnet_shared()->sockets_lock);
}


/*
 * Mapping from file descriptor to socket structure.
 *
 * NOTE: these functions are internal and must never be used by
 * application code.
 */

IP_INLINE Ipnet_socket *ipnet_fd_to_sock_unsafe(int fd)
{
    Ipnet_socketref *pref = &ipnet_shared()->socket_refs[fd];
    return pref->sock;
}

IP_INLINE Ipnet_socket *ipnet_fd_to_sock(int fd)
{
    Ipnet_socketref *pref = &ipnet_shared()->socket_refs[fd];
    if (IP_LIKELY(IPNET_SOCKETREF_VALID(pref->ref_owner)))
        return pref->sock;
    return IP_NULL;
}

/*
 * Version of the above that also range-checks fd.
 */
IP_INLINE Ipnet_socket *ipnet_fd_to_sock_checked(int fd)
{
    if (IP_LIKELY(IPNET_FD_RANGE_OK(fd)))
        return ipnet_fd_to_sock(fd);
    return IP_NULL;
}

IP_INLINE void ipnet_reachable_sockets_rdlock(void)
{
    IPNET_DEBUG_LINE(Ipnet_data *net);
    IPNET_DEBUG_LINE(ip_assert(!ipnet_is_inside_critical_region()));
    IPNET_DEBUG_LINE(ip_assert(ipnet_is_stack_task() || 
                     ipnet_shared()->startup_state != IPNET_STARTUP_DONE));
    IPNET_DEBUG_LINE(net = ipnet_ptr());
    IPNET_DEBUG_LINE(ip_assert(net->reachable_sockets_lock_mode ==
                               IPCOM_RWSEM_UNLOCKED));
    ipcom_rwsem_wait_rd(ipnet_shared()->reachable_sockets_lock);
    IPNET_DEBUG_LINE(net->reachable_sockets_lock_mode = IPCOM_RWSEM_READ);
}

IP_INLINE void ipnet_reachable_sockets_wrlock(void)
{
    IPNET_DEBUG_LINE(Ipnet_data *net);
    IPNET_DEBUG_LINE(ip_assert(!ipnet_is_inside_critical_region()));
    IPNET_DEBUG_LINE(ip_assert(ipnet_is_stack_task()));
    IPNET_DEBUG_LINE(net = ipnet_ptr());
    IPNET_DEBUG_LINE(ip_assert(net->reachable_sockets_lock_mode ==
                               IPCOM_RWSEM_UNLOCKED));
    ipcom_rwsem_wait_wr(ipnet_shared()->reachable_sockets_lock);
    IPNET_DEBUG_LINE(net->reachable_sockets_lock_mode = IPCOM_RWSEM_WRITE);
}

IP_INLINE void ipnet_reachable_sockets_rdunlock(void)
{
    IPNET_DEBUG_LINE(Ipnet_data *net = ipnet_ptr());
    IPNET_DEBUG_LINE(ip_assert(net->reachable_sockets_lock_mode ==
                               IPCOM_RWSEM_READ));
    IPNET_DEBUG_LINE(net->reachable_sockets_lock_mode = IPCOM_RWSEM_UNLOCKED);
    ipcom_rwsem_post_rd(ipnet_shared()->reachable_sockets_lock);
}

IP_INLINE void ipnet_reachable_sockets_wrunlock(void)
{
    IPNET_DEBUG_LINE(Ipnet_data *net = ipnet_ptr());
    IPNET_DEBUG_LINE(ip_assert(net->reachable_sockets_lock_mode ==
                               IPCOM_RWSEM_WRITE));
    IPNET_DEBUG_LINE(net->reachable_sockets_lock_mode = IPCOM_RWSEM_UNLOCKED);
    ipcom_rwsem_post_wr(ipnet_shared()->reachable_sockets_lock);
}

IP_INLINE void 
ipnet_socket_poll_lock(Ipnet_socket *sock)
{
    IPNET_DEBUG_LINE(ip_assert(!ipnet_is_inside_critical_region()));
    IPNET_DEBUG_LINE(ip_assert(ipnet_is_stack_task()));
    IPNET_DEBUG_LINE(ip_assert(sock != IP_NULL));
    ipcom_spinlock_lock(&sock->poll_list_lock);
}

IP_INLINE void 
ipnet_socket_poll_unlock(Ipnet_socket *sock)
{
    IPNET_DEBUG_LINE(ip_assert(!ipnet_is_inside_critical_region()));
    IPNET_DEBUG_LINE(ip_assert(ipnet_is_stack_task()));
    IPNET_DEBUG_LINE(ip_assert(sock != IP_NULL));
    ipcom_spinlock_unlock(&sock->poll_list_lock);
}

#ifdef IPNET_USE_SOCKET_PKTAVAIL_CB
#define IPNET_PKTAVAIL_CB_IS_PENDING(net_shrd) \
    (IP_BIT_ISSET((net_shrd)->flags, IPNET_FLAG_PKTAVAIL_CB_PENDING))
#else
#define IPNET_PKTAVAIL_CB_IS_PENDING(net_shrd) (IP_FALSE)
#endif /* IPNET_USE_SOCKET_PKTAVAIL_CB */

/*
 *===========================================================================
 *                          ipnet_ipaddrlen
 *===========================================================================
 * Description: Returns the length of the IP address.
 * Parameters:  domain - domain for the neighbor.
 * Returns:
 *
 */
IP_INLINE Ip_size_t
ipnet_ipaddrlen(int domain)
{
    IPCOM_UNUSED_ARG(domain);
#ifdef IPCOM_USE_INET6
    if (domain == IP_AF_INET6)
        return sizeof(struct Ip_in6_addr);
#endif

    return sizeof(struct Ip_in_addr);
}

IP_GLOBAL Ip_bool ipnet_can_update_shared_data(void);
IP_GLOBAL Ip_bool ipnet_stack_exclusive(void);
IP_GLOBAL void ipnet_enter_critical_region(void);
IP_GLOBAL void ipnet_exit_critical_region(void);

IP_GLOBAL void
ipcom_pause_os_network_daemon(void);
IP_GLOBAL void
ipnet_pause_os_network_daemon(void);
IP_GLOBAL void
ipnet_resume_os_network_daemon(void);

#if IPCOM_VR_MAX > 1
#define ipnet_get_effective_vr(net) (net)->effective_vr
#else
#define ipnet_get_effective_vr(net) 0
#endif

#define ipnet_get_effective_pid(net) (net)->effective_pid

IP_GLOBAL void ipnet_try_free_mem(void);

IP_GLOBAL int ipnet_sysvar_get_as_int_vr(Ipnet_netif *netif,
                                      IP_CONST char *snd,
                                      IP_CONST char *name,
                                      int default_val,
                                      IP_CONST Ipcom_cmd_int_str_map *map,
                                      int vr);
IP_GLOBAL int ipnet_sysvar_netif_get_as_int(int domain,
                                            Ipnet_netif *netif,
                                            IP_CONST char *name,
                                            int default_val);
IP_GLOBAL int ipnet_sysvar_netif_get_as_int_ex(int domain,
                                               Ipnet_netif *netif,
                                               IP_CONST char *name,
                                               int default_val,
                                               IP_CONST Ipcom_cmd_int_str_map *map);

IP_GLOBAL Ipcom_pkt *ipnet_pkt_clone(Ipcom_pkt *pkt, int is_ipstart_valid);

IP_GLOBAL void * ipnet_sysctl_if_add_addrs_one(void *buf, Ipnet_netif *netif,
                                               int domain, void *addrx, Ip_size_t *lenp);

IP_GLOBAL Ip_bool ipnet_has_priv(int priv);
IP_PUBLIC Ip_s64 ipnet_timeval_to_msec(struct Ip_timeval *tv);

#ifdef IPCOM_USE_MIB2
IP_GLOBAL Ipnet_netif *ipnet_ip6_socket_to_netif(struct Ipnet_socket_struct *sock);
#endif

#ifdef IPCOM_USE_MIB2_NEW
IP_GLOBAL void ipnet_eth_update_mib2_lastchange(Ipnet_neigh *n);
#endif

IP_GLOBAL Ip_u16 ipnet_sysctl_create_ifinfo(void *buf, Ipnet_netif *netif);


IP_GLOBAL Ip_u32 ipnet_stats_tcp_established(void);

IP_GLOBAL void
ipnet_loop_pkt_tx(Ipnet_dst_cache *dst,
                  Ipcom_pkt *pkt,
                  Ipnet_dst_cache_domain_ctor dst_cache_local_tx_ctor);

IP_GLOBAL int ipnet_fw_nat_ipsec_tx(Ipnet_dst_cache **dstp,
                                    Ipcom_pkt **pktp,
                                    Ip_bool do_nat);

IP_GLOBAL int ipnet_fw_nat_rx(Ipnet_dst_cache **dstp,
                              Ipcom_pkt **pktp,
                              Ip_bool do_nat);

IP_GLOBAL void ipnet_conf_update(const char *fst,
                                 const char *snd,
                                 const char *name);

IP_GLOBAL int ipnet_ctrl_sig(Ipnet_sig *sig);

IP_GLOBAL void ipnet_mib2_noncounter_init(Ipnet_data *net);

/*
 *===========================================================================
 *                         IPNET socket
 *===========================================================================
 */

/*
 *===========================================================================
 *                ipnet_sock_make_next_sendmsg_synchronous
 *===========================================================================
 * Description: Makes sure that the next call to sendmsg() is
 *              synchronous so that proper error code is returned.
 * Parameters:  sock - a socket
 * Returns:
 *
 */
IP_INLINE void
ipnet_sock_make_next_sendmsg_synchronous(Ipnet_socket *sock)
{
    /*
     * This variable is compared to ipnet->route_cache_id and the
     * sendmsg() call can be asynchronous if they are
     * equal. ipnet->route_cache_id will never have a value of zero.
     */
    sock->snd_route_cache_id = 0;
}

IP_GLOBAL Ipnet_sig *ipnet_pkt_sig_to_stack_idx(int to_stack_idx, Ipcom_pkt *pkt);
IP_GLOBAL Ip_bool ipnet_sig_to_instance(int stack_idx, Ipnet_sig *sig, Ip_bool skip_ok);
IP_GLOBAL void ipnet_sock_update_reuse(Ipnet_socket *sock, Ip_u32 oldflags);
IP_GLOBAL Ip_size_t ipnet_sock_get_bound_port_size(void);
IP_GLOBAL Ipnet_socket *ipnet_sock_get(Ipnet_socket_lookup_key *key, Ipcom_list **head);
IP_GLOBAL Ipnet_socket *ipnet_sock_next(Ipnet_socket *sock);
IP_GLOBAL Ipcom_list *ipnet_sock_reachable_bucket(Ipnet_socket_lookup_key *key);
IP_GLOBAL Ipnet_socket *ipnet_sock_reachable_search(Ipcom_list *bucket, Ipnet_socket_lookup_key *key);

IP_GLOBAL Ip_bool ipnet_sock_has_waiting_writers(Ipnet_socket *sock);
IP_GLOBAL Ip_bool ipnet_is_sock_readable(Ipnet_socket *sock, int lowat);
IP_GLOBAL Ip_bool ipnet_is_sock_writable(Ipnet_socket *sock, int lowat);
IP_GLOBAL Ip_bool ipnet_is_sock_exceptional(Ipnet_socket *sock, int lowat);
IP_GLOBAL Ip_bool ipnet_sock_linger_on_close(Ip_fd fd, void *close_signal);

IP_PUBLIC void ipnet_sock_data_avail(Ipnet_socket *sock, int so_errno, int how);

IP_GLOBAL void ipnet_sock_pkt_drain(void);
IP_GLOBAL void *ipnet_sock_alloc_private_data(Ipnet_socket *sock, Ip_size_t size);
IP_GLOBAL void ipnet_sock_migrate(Ipnet_socket *sock, int stack_idx);

#ifdef IPNET_USE_ROUTER_ALERT
IP_GLOBAL Ip_bool ipnet_sock_in_router_alert_chain(Ipnet_socket *sock);
IP_GLOBAL int ipnet_sock_join_router_alert_chain(Ipnet_socket *sock);
IP_GLOBAL int ipnet_sock_leave_router_alert_chain(Ipnet_socket *sock);
#endif
IP_GLOBAL int ipnet_sock_router_alert_pkt(Ipcom_pkt *pkt);

IP_GLOBAL int ipnet_configd_start(void);
IP_GLOBAL int ipnet_raw_input(Ipcom_pkt *pkt, Ip_bool take_ownership, int proto,
                              IP_CONST void *src_addr, Ip_u16 src_port,
                              IP_CONST void *dst_addr, Ip_u16 dst_port,
                              Ipnet_sock_lookup_f socklookup);

IP_GLOBAL int ipnet_sock_bind(Ipnet_socket *sock, IP_CONST struct Ip_sockaddr *name,
                              Ip_socklen_t namelen, Ip_u32 flags);
IP_GLOBAL Ip_u16 ipnet_next_ephemeral_port(Ipnet_socket *sock);
IP_GLOBAL int  ipnet_queue_received_packet(Ipcom_pkt *pkt, Ipnet_socket *sock);
IP_GLOBAL void ipnet_sock_free(Ipnet_socket *sock);
IP_GLOBAL int ipnet_do_close(Ipnet_socket *sock);
IP_GLOBAL int ipnet_do_socketselect(int nfds,
                                    Ip_fd_set *readfds,
                                    Ip_fd_set *writefds,
                                    Ip_fd_set *exceptfds,
                                    struct Ip_timeval *timeout);
IP_GLOBAL int ipnet_sock_drop_all_multicast_memberships(Ipnet_socket *sock, Ipnet_netif *netif,
                                                        Ip_bool drop_ip4, Ip_bool drop_ip6);
IP_GLOBAL int ipnet_increase_hdr_space(Ipcom_pkt **ppkt, Ip_bool is_iphdr_valid);

IP_GLOBAL Ipnet_route_entry * ipnet_sock_get_route_rtl(Ipnet_socket *sock);

IP_GLOBAL int ipnet_ioctl_move_if_rt_to_vr_rtl(Ipnet_netif *netif, Ip_u16 vr);
IP_GLOBAL int ipnet_sock_create_lookup_tables(void);
IP_GLOBAL int ipnet_sock_set_reachable_prelock(Ipnet_socket *sock, Ip_bool prelocked);
IP_INLINE int ipnet_sock_set_reachable(Ipnet_socket *sock)
{
    return ipnet_sock_set_reachable_prelock(sock, IP_FALSE);
}
IP_GLOBAL void ipnet_sock_set_unreachable_keeplock(Ipnet_socket *sock, Ip_bool staylocked);
IP_INLINE void ipnet_sock_set_unreachable(Ipnet_socket *sock)
{
    ipnet_sock_set_unreachable_keeplock(sock, IP_FALSE);
}
IP_GLOBAL void ipnet_sock_bind_addr_removed(Ipnet_socket *sock_list);
IP_GLOBAL void ipnet_sock_change_addr_entry(Ipnet_socket *old_sock_list,
                                            Ipnet_socket **pnew_sock_list,
                                            void *addr_entry);
IP_GLOBAL int ipnet_sock_unconnect(Ipnet_socket *sock);
IP_GLOBAL int ipnet_sock_bind_to_port(Ipnet_socket *sock,
                                      IP_CONST struct Ip_sockaddr *name,
                                      Ip_bool check_reuse);
IP_GLOBAL void ipnet_sock_unbind(Ipnet_socket *sock);
IP_GLOBAL int ipnet_pkt_get_maxlen(Ipcom_pkt *pkt);

IP_INLINE Ipnet_sock_ops *ipnet_sock_get_ops(Ipnet_socket *sock)
{
    /*
     * For NAE:s
     * The ipnet_sock_ops array is located in local memory, so the
     * returned pointer must not be stored in any shared memory area
     * (like the socket structure for example). This function must be
     * called each time the socket options in needed.
     */
    ip_assert(sock->ops_handle >= 0);
    return ipnet_sock_ops[sock->ops_handle];
}
IP_GLOBAL int
ipnet_sock_get_ops_handle(int domain, int type, int protocol,
                          Ip_bool *no_domain, Ip_bool *no_type);
IP_GLOBAL int ipnet_sock_register_ops(Ipnet_sock_ops *ops);

IP_GLOBAL void ipnet_epoll_done(Ipnet_sig *sig);
IP_GLOBAL int ipnet_epoll_register(void);

#ifdef IPSCTP
IP_GLOBAL int ipnet_sock_sctp_register(void);
#endif
IP_GLOBAL int ipnet_sock_udp_register(void);
#ifdef IPTCP
IP_GLOBAL int ipnet_sock_tcp_register(void);
#endif
#ifdef IPCOM_USE_INET
IP_GLOBAL int ipnet_sock_ip4_register(void);
IP_GLOBAL void ipnet_ip4_reg_transport_layer(Ip_u8 ip_proto,
                                             Ipnet_transport_layer_rx_func trans_rx);
#endif
#ifdef IPCOM_USE_INET6
IP_GLOBAL int ipnet_sock_ip6_register(void);
IP_GLOBAL void ipnet_ip6_reg_transport_layer(Ip_u8 ip_proto,
                                             Ipnet_transport_layer_rx_func trans_rx);
#endif
#ifdef IPNET_USE_ROUTESOCK
IP_GLOBAL int ipnet_sock_route_register(void);
#endif
#ifdef IPNET_USE_NETLINKSOCK
IP_GLOBAL int ipnet_sock_netlink_register(void);
#endif
#ifdef IPCOM_USE_PACKET
IP_GLOBAL int ipnet_sock_packet_register(void);
#endif
#ifdef IPIPSEC2
IP_GLOBAL void ipnet_ipsec_rx(Ipnet_dst_cache *dst, Ipcom_pkt *pkt, Ip_u8 proto);
IP_GLOBAL int ipnet_proto_ah_register(void);
IP_GLOBAL int ipnet_proto_esp_register(void);
IP_GLOBAL int ipnet_sock_key_register(void);
#endif
#ifdef IPNET_USE_SOCKDEV
IP_GLOBAL int ipnet_sock_sockdev_register(void);
#endif

IP_GLOBAL void ipnet_sock_ip4_get_ops(Ipnet_sock_inet_ops *ops);
IP_GLOBAL void ipnet_sock_ip6_get_ops(Ipnet_sock_inet_ops *ops);


/*
 *===========================================================================
 *          socket function callable by IPNET in user context
 *===========================================================================
 */

IP_GLOBAL int ipnet_usr_sock_pkt_recv(Ipnet_socket *sock, struct Ip_msghdr *msg, int flags);


/*
 *===========================================================================
 *                         IPNET packet socket
 *===========================================================================
 */
#ifdef IPCOM_USE_PACKET
IP_GLOBAL Ip_bool ipnet_packet_input(Ipnet_netif *netif, Ipcom_pkt *pkt);
IP_GLOBAL int     ipnet_packet_output(Ipnet_socket *sock, IP_CONST struct Ip_msghdr *msg, Ipcom_pkt *pkt);
IP_GLOBAL Ip_bool ipnet_packet_getsockopt(int optname, IP_CONST struct Ip_packet_mreq *mreq, Ip_socklen_t *optlen);
IP_GLOBAL Ip_bool ipnet_packet_setsockopt(Ipnet_socket *sock, int optname, IP_CONST struct Ip_packet_mreq *mreq, Ip_socklen_t optlen);
#endif /* IPCOM_USE_PACKET */


/*
 *===========================================================================
 *                         Fragmentation & reassembly
 *===========================================================================
 */
typedef Ip_bool (*Ipnet_is_part_of_same_pkt_func)(Ipcom_pkt *frag1, Ipcom_pkt *frag2);
typedef Ip_bool (*Ipnet_more_fragments_func)(Ipcom_pkt *frag);
typedef void (*Ipnet_update_ip_header_func)(Ipcom_pkt *pkt);
typedef void (*Ipnet_reassemble_err_func)(Ipcom_pkt *frag_list);

IP_GLOBAL Ipcom_pkt *
ipnet_reassembly(Ipnet_data *net,
                 struct Ipnet_peer_info_struct *peer_info,
                 Ipcom_pkt *pkt,
                 Ipnet_is_part_of_same_pkt_func is_part_of_same_pkt,
                 Ipnet_more_fragments_func more_fragments);
IP_GLOBAL Ipcom_pkt *
ipnet_create_reassembled_packet(Ipcom_pkt *fragment_list,
                                Ipnet_update_ip_header_func update_ip_header,
                                Ipnet_reassemble_err_func report_reassemble_err);
IP_GLOBAL Ipcom_pkt *
ipnet_fragment_packet(Ipcom_pkt *pkt,
                      int ip_hdr_size,
                      int other_hdr_size,
                      int mtu,
                      Ipnet_more_fragments_func more_fragments);


/*
 *===========================================================================
 *                         ROUTING SOCKET
 *===========================================================================
 *
 */
#ifdef IPNET_USE_ROUTESOCK
IP_GLOBAL void ipnet_routesock_addr_add(struct Ipnet_netif_struct *netif, int domain, void *addr);
IP_GLOBAL void ipnet_routesock_addr_delete(struct Ipnet_netif_struct *netif, int domain, void *addr);
IP_GLOBAL void ipnet_routesock_addr_conflict(Ipnet_netif *netif, int domain, void *addr);
IP_GLOBAL void ipnet_routesock_if_change(struct Ipnet_netif_struct *netif);
IP_GLOBAL void ipnet_routesock_if_announce(Ipnet_netif *netif, Ip_u16 what);
IP_GLOBAL void ipnet_routesock_add_rtl(Ipnet_route_entry *rt);
IP_GLOBAL void ipnet_routesock_delete_rtl(Ipnet_route_entry *rt);
IP_GLOBAL void ipnet_routesock_change_rtl(Ipnet_route_entry *rt);
IP_GLOBAL void ipnet_routesock_miss_rtl(Ipcom_route *rtab, IP_CONST void *key);
IP_GLOBAL void ipnet_routesock_redirect_rtl(Ipcom_route *rtab, Ip_u32 ifindex,
                                            IP_CONST void *dst, IP_CONST void *new_gw);
IP_GLOBAL void ipnet_routesock_neigh_resolve(Ipnet_neigh *neigh);
#endif /* IPNET_USE_ROUTESOCK */




/*
 *===========================================================================
 *                         PACKET POOL FUNCTIONS
 *===========================================================================
 *
 */
#ifdef IPNET_USE_PACKET_POOL
IP_GLOBAL int ipnet_pkt_pool_init(Ipnet_shared_data *shrd_net);
IP_GLOBAL int ipnet_pkt_pool_hdr_count_hint(void);
IP_GLOBAL void ipnet_pkt_pool_drain(const Ipnet_data *caller_net);
#ifdef IPNET_USE_PACKET_CACHE_PER_INSTANCE
IP_GLOBAL void ipnet_pkt_priv_cache_drain(Ipnet_data *caller_net);
#endif
#endif /* IPNET_USE_PACKET_POOL */

/*
 *===========================================================================
 *                         DEBUG FUNCTIONS
 *===========================================================================
 *
 */
#ifdef IPNET_DEBUG
IP_GLOBAL void ipnet_frag_set_peer_info(Ipcom_pkt *frag, Ipnet_peer_info *peer_info);
IP_GLOBAL void ipnet_pkt_remove_from_alloc_list(Ipcom_pkt *pkt, int key);
IP_GLOBAL void ipnet_pkt_add_to_alloc_list(Ipcom_pkt *pkt);
IP_GLOBAL void ipnet_pkt_check(Ipcom_pkt *pkt);
#endif /* IPNET_DEBUG */

/*
 *===========================================================================
 *                         POWER ON SELF-TEST
 *===========================================================================
 *
 */
#ifdef IPNET_USE_POST
IP_GLOBAL void ipnet_post_run(void);
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
