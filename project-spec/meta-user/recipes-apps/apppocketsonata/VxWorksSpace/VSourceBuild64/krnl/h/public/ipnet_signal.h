/*
 * Copyright (c) 2014-2015, 2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01aug17,dlk  Mods for EDOOM mechanism. Indicate poll result via
             value in Ipnet_sig_reply return_code rather than by
             separate poll reply signal types (F5593)
13mar15,rjq  Bug in hanlding ipsctp active head. (VXWRAD-191)
10feb14,tlu  Add EPOLL signal type
*/


#ifndef IPNET_SIGNAL_H
#define IPNET_SIGNAL_H

/*
 ****************************************************************************
 * 1                    DESCRIPTION
 ****************************************************************************
 */
/*
   Definition of all signals that can be sent and received from the
   IPNET socket daemon.
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

#include <ipcom_atomic.h>
#include <ipcom_cstyle.h>
#include <ipcom_netif.h>
#include <ipcom_pipe.h>
#include <ipcom_pkt.h>
#include <ipcom_sock.h>
#include <ipcom_type.h>

#ifdef IPIPSEC2
#include <ipipsec.h>
#endif

#include "ipnet_dst_cache.h"
#include "ipnet_timeout.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 ****************************************************************************
 * 4                    DEFINES
 ****************************************************************************
 */

/*
 ****************************************************************************
 * 5                    TYPES
 ****************************************************************************
 */

struct Ipnet_socket_struct;
struct Ipnet_sig_struct;

enum Ipnet_sock_poll
{
    IPNET_SOCK_POLL_READ,
    IPNET_SOCK_POLL_WRITE,
    IPNET_SOCK_POLL_EXCEPT
};

enum Ipnet_poll_result
{
    IPNET_POLL_ONGOING,  /* not ready to send result yet... */
    IPNET_POLL_DONE,
    IPNET_POLL_TIMEOUT,
    IPNET_POLL_OWNER_CHANGED,
    IPNET_POLL_DISCARD
};

enum Ipnet_sig_type
{
    IPNET_SIG_NONE = -1,  /* no signal match */
    IPNET_SIG_ACCEPT = 0,
    IPNET_SIG_BIND,
    IPNET_SIG_BROADCAST_JOB,
    IPNET_SIG_CLEANUP,
    IPNET_SIG_CLOSE,
    IPNET_SIG_CONNECT,
    IPNET_SIG_CTRL,
    IPNET_SIG_CTRL_SOCK_RX,
    IPNET_SIG_DATA_SOCK_RX,
    IPNET_SIG_DST_RX,
    IPNET_SIG_ETH_RX,
    IPNET_SIG_GETANCILLARYDATA,
    IPNET_SIG_GETNAME,
    IPNET_SIG_GETSOCKOPT,
    IPNET_SIG_IF_ATTACH,
    IPNET_SIG_IF_CHANGELINKADDR,
    IPNET_SIG_IF_CHANGEMTU,
    IPNET_SIG_IF_CHANGENAME,
    IPNET_SIG_IF_DETACH,
    IPNET_SIG_IF_FREE,
    IPNET_SIG_IF_INDEXTONAME,
    IPNET_SIG_IF_MALLOC,
    IPNET_SIG_IF_NAMETOINDEX,
    IPNET_SIG_IF_NAMETONETIF,
    IPNET_SIG_IOCTL,
    IPNET_SIG_IPSEC,
    IPNET_SIG_LISTEN,
    IPNET_SIG_NEIGH_RESOLVE,
    IPNET_SIG_NEIGH_UPDATE,
    IPNET_SIG_POLL,
    IPNET_SIG_POLL_ASYNC,
    IPNET_SIG_POLL_CANCEL_TIMEOUT,
    IPNET_SIG_PORT_SPECIFIC,
    IPNET_SIG_SCTP_NEW_UDP,
    IPNET_SIG_SCTP_SET_STATE,
    IPNET_SIG_SCTP_WINDOW_UPDATE,
    IPNET_SIG_SENDMSG,
    IPNET_SIG_SETSOCKOPT,
    IPNET_SIG_SHUTDOWN,
    IPNET_SIG_SOCKET,
    IPNET_SIG_SOCKETFREE,
    IPNET_SIG_STATS,
    IPNET_SIG_SUSPEND,
    IPNET_SIG_SYSCTL,
    IPNET_SIG_TCP_MIGRATE,
    IPNET_SIG_WAKEUP,
    IPNET_SIG_WINDOW_UPDATE,
    IPNET_SIG_EPOLL_REGISTER,

    /*
     * Now start pseudo-signals; these indicate cases where a signal
     * specifying a socket updates global state.
     */
    IPNET_SIG_TOP,   /* all pseudo-signals must be >= IPNET_SIG_TOP */
    IPNET_SIG_IOCTL_UPDATE = IPNET_SIG_TOP + IPNET_SIG_IOCTL,
    IPNET_SIG_SETSOCKOPT_UPDATE = IPNET_SIG_TOP + IPNET_SIG_SETSOCKOPT
};

struct Ipnet_sig_accept
{
    struct Ip_sockaddr_storage from;
    Ip_socklen_t               fromlen;
};

struct Ipnet_sig_ancillary_data
{
    struct Ip_msghdr *msg;
    Ipcom_pkt        *pkt;
};

struct Ipnet_sig_bind
{
    struct Ip_sockaddr_storage name;
    Ip_socklen_t               namelen;
};

struct Ipnet_sig_broadcast_job
{
    union
    {
        Ipnet_broadcast_job job;
        Ipnet_softirq       softirq;
    } u;
};

struct Ipnet_sig_connect
{
    struct Ip_sockaddr_storage to;
    Ip_socklen_t               tolen;
};

struct Ipnet_sig_cookie
{
    /*
     * Value to recognize a reply signal corresponding
     * to a particular request, in cases where one of several
     * reply signals might be used (currently only multi-poll
     * for ipcom_socketselect()).
     * Overlays 'multi' member in Ipnet_sig_poll;
     * all the signals subordinate to the same 'multi'
     * signal have the same 'cookie' (i.e. multi) value.
     */
    void * cookie;
};

struct Ipnet_sig_getname
{
    Ip_bool                    get_local_name;
    struct Ip_sockaddr_storage name;
};

struct Ipnet_sig_if_indexname
{
    /* Total number of attached interfaces */
    Ip_u32 num_attached;
    /* The highest ifindex assigned to any interface */
    Ip_u32 highest_assigned_ifindex;
    Ip_u32 ifindex;
    char   ifname[IP_IFNAMSIZ+1];
};

struct Ipnet_sig_dst_rx
{
    /*
     * Flow specification that 'pkt' matches
     */
    Ipnet_flow_spec             flow_spec;
    /*
     * Packet that must be processed on a specific stack instance.
     */
    Ipcom_pkt                  *pkt;
    /*
     * Packet RX handler
     */
    Ipnet_dst_cache_rx_func     fun;
    /*
     * Flow constructor needed for this packet.
     */
    Ipnet_dst_cache_domain_ctor ctor;
};

#ifdef IPCOM_USE_INET6
#define IPNET_NEIGH_KEY_UNION_SIZE 16
#else
#define IPNET_NEIGH_KEY_UNION_SIZE 8
#endif

struct Ipnet_sig_neigh_resolve
{
    /*
     * IPv4/IPv6 address of for this neighbor
     */
    Ip_u8         addr [IPNET_NEIGH_KEY_UNION_SIZE];

    Ipcom_pkt     *pkt;
    int            domain;
};

struct Ipnet_sig_netif
{
    Ipcom_netif *netif;
    Ip_u16       type;
    Ip_u16       vr;
    Ip_u32       mtu;
    Ip_bool      locked;
    Ip_u8       *link_addr;
    Ip_u16       size;
    char         ifname[IP_IFNAMSIZ+1];
};

struct Ipnet_sig_ioctl
{
    /*
     * In spite of nominally specifying a single socket, many ioctls have
     * broader effects; for those we can set the fd in Ipnet_sig to -1,
     * to allow sending to the primary stack instance, and keep the
     * actual socket fd here.
     */
    Ip_fd         fd;
    unsigned long request;
    void         *argp;
};

struct Ipnet_sig_listen
{
    int   backlog;
};

struct Ipnet_sig_reply
{
    int return_code;
    int sock_errno;
};

struct Ipnet_sig_poll
{
    /*
     * If this poll is part of a larger poll operation affecting
     * multiple stack instances, then multi is non-NULL.
     */
    struct Ipnet_sig_struct *multi;

    /*
     * What to poll for
     */
    Ip_u8                what;

    /*
     * We need to record which stack instance scheduled the timeout,
     * so that it can be cancelled properly.
     */
    Ip_u16               tmo_instance;

    /*
     * Minimum number of bytes the caller want to receive/send. 0 will
     * use the low watermark setting from the socket.
     */
    int                  lowat;

    /*
     * Maximum time the client wants to wait for the socket to become
     * ready
     */
    struct Ip_timeval   *timeout;

    /*
     * Storage of the timeout handle variable that all struct
     * Ipnet_sig_poll structures referes to via 'ptmo'
     */
    Ipnet_timeout       *tmo;

    /*
     * Pointer to the next poll signal that belongs to the same
     * session.
     * NOTE: This list is circular, so this pointer points to
     * this signal in the case where the session only contains a
     * single signal.
     * NOTE: All of the poll signals in the 'session' must correspond
     * to sockets owned by the same network stack instance!
     * NOTE: This list is never used after it has been traversed
     * by ipnet_sys_poll(). Poll signals are freed by
     * ipnet_usr_sock_poll_free() without de-linking them from this list.
     */
    struct Ipnet_sig_struct *next;

    /*
     * List of receivers/senders waiting to receive/send on the same
     * socket. The list contains Ipnet_sig instances, one entry for
     * each waiting (task/process, what) combination. The head of this
     * list is Ipnet_socket::poll_list for socket identified by "fd".
     */
    Ipcom_list           list;

    /*
     * Must be the last element in this structure, used to figure out
     * the size needed to create an IPNET_SIG_POLL signal
     */
    int                  last;
};

struct Ipnet_sig_poll_external
{
    /*
     * File descriptor for the socket this external poll is done for
     */

    /* IP_TRUE -> start poll; IP_FALSE -> stop poll */
    Ip_bool              poll;

    /*
     * ebdata points to the poll signal itself for a start-poll operation;
     * it is a buffer provided for our use by the external epoll implementation.
     * We can use this space however we want, subject to size limits.
     * For a stop-poll signal, this points to the original ebdata of the
     * start-poll signal, and identifies the poll instance both to ipnet
     * and to the external epoll implementation.
     */
    void *               ebdata;
};


/* multi-stack-instance poll control structure */
struct Ipnet_sig_multi_poll
{
    /*
     * Number of signals involved in the poll.
     * Decreases to 0 as signals are disposed of.
     */
    Ipcom_atomic_t num_sigs;

    /*
     * Total number of stack instances involved in the multi-instance
     * poll.
     */
    int n_instances;

    /*
     * Index into the 'instance' array to the 'struct Ipnet_sig_poll'
     * structure that will hold any timer associated with this poll
     * session.
     */
    int tmo_instance;

    /*
     * Number of ready events on this select set
     * Only the first takes action
     */
    Ipcom_atomic_t ready_events;

    /*
     * Array of (variable) length ipnet_conf_max_instances poll
     * instances (or IP_NULL), indexed by stack index.
     */
    struct Ipnet_sig_struct *instance[1];
};


struct Ipnet_sig_sendmsg
{
    Ipcom_pkt                 *pkt;
    struct Ip_msghdr           msg;
    struct Ip_sockaddr_storage to;
    struct Ipnet_sig_struct   *rsig; /* Response signal for synchronous
                                        calls */
};

struct Ipnet_sig_socket
{
    int domain;
    int type;
    int protocol;
};

struct Ipnet_sig_sockopt
{
    int          level;
    int          optname;
    void        *optval;
    Ip_socklen_t optlen;
};

#ifndef IPCOM_HAS_STACK_SUSPEND_RESUME
struct Ipnet_sig_suspend
{
    /*
     * Number of stack instances that has not reached their suspend
     * point yet. The stack instance that decrement this counter from
     * 1 to 0 must post the 'complete' semaphore.
     */
    Ipcom_atomic_t *suspends_pending;

    /*
     * The context that issuing the suspend will wait on this
     * semaphore until all stack instances has reached their suspend
     * point.
     */
    Ipcom_sem      *complete;

    /*
     * Number of stack instances that has not resumed. The stack
     * instance that decrements this counter from 1 to 0 must free the
     * 'resume' semaphore and free the signal.
     */
    Ipcom_atomic_t *resumes_pending;

    /*
     * All stack instances will wait on this semaphore while
     * suspended. The suspending context must post this semaphore once
     * for each suspended stack instance to complete the
     * suspend/resume cycle.
     */
    Ipcom_sem      *resume;
};
#endif /* IPCOM_HAS_STACK_SUSPEND_RESUME */

struct Ipnet_sig_shutdown
{
    int   how;
};

struct Ipnet_sig_sysctl
{
    int         *name;
    unsigned int namelen;
    void        *oldp;
    Ip_size_t   *oldlenp;
    void        *newp;
    Ip_size_t    newlen;
};

#ifdef IPSCTP
struct Ipnet_sig_sctp_new_udp
{
    Ip_fd         fd;
    void         *tcb;
    const struct Ip_msghdr  *msg;
};

struct Ipnet_sig_sctp_set_state
{
    Ip_u32 vtag;
    int    state;
};

struct Ipnet_sig_sctp_wu
{
    void  *tcb;
    Ip_u32 delay_msec;
    Ip_u32 send_tsn_next;
    Ip_u32 send_peerwnd;
    Ip_u32 recv_tsn_next;
};
#endif

#ifdef IPIPSEC2
enum Ipipsec_sig_type
{
    IPIPSEC_SIG_DECRYPT,       /* IPSEC daemon pipe */
    IPIPSEC_SIG_ENCRYPT,       /* IPSEC daemon pipe */
    IPIPSEC_SIG_LOCK,          /* IPSEC daemon pipe */
    IPIPSEC_SIG_UNLOCK,        /* IPSEC daemon pipe */
    IPIPSEC_SIG_ACK,           /* Response pipe */
    IPIPSEC_SIG_PKTINPUT,      /* IPNET pipe */
    IPIPSEC_SIG_PKTOUTPUT,     /* IPNET pipe */
    IPIPSEC_SIG_PKTFREE,       /* IPNET pipe */
    IPIPSEC_SIG_CONTROL,       /* IPNET pipe */
    IPIPSEC_SIG_SOFTEXPIRE,    /* IPSEC control pipe */
    IPIPSEC_SIG_HARDEXPIRE,    /* IPSEC control pipe */
    IPIPSEC_SIG_REGISTERUSE,   /* IPSEC control pipe */
    IPIPSEC_SIG_TRAP,          /* IPSEC control pipe */
#ifdef IPIPSEC_USE_EVENT_LOG
    IPIPSEC_SIG_EVENT,
#endif /* IPIPSEC_USE_EVENT_LOG */
};

struct Ipnet_sig_ipsec
{
    enum Ipipsec_sig_type ipsec_sig_type;
    union
    {
        struct Ipnet_sig_ipsec_packet
        {
            Ipcom_pkt *pkt;
            Ip_u8      domain;
            Ip_u8      proto;
        } packet;
        struct Ipnet_sig_ipsec_crypto
        {
            Ipcom_pkt     *pkt;
            Ipipsec_param  param;
        } crypto;
        struct Ipnet_sig_ipsec_expire
        {
            void *sa;
        } expire;
        struct Ipnet_sig_ipsec_trap
        {
            void          *sa;
            Ipipsec_param  param;
            Ip_u32         traptype;
            Ip_u32         errors;
        } trap;
#ifdef IPIPSEC_USE_EVENT_LOG
        struct Ipnet_sig_ipsec_event
        {
            void          *sa;
            Ipipsec_key    key;
            Ip_u16         type;
            Ip_u16         reason;
        } event;
#endif /* IPIPSEC_USE_EVENT_LOG */
    } t;
};
#endif /* #ifdef IPIPSEC2 */

struct Ipnet_sig_stats
{
    int proto;
    int sig_errno;
    union
    {
        struct
        {
            Ip_u32 in_receives;
            Ip_u32 in_hdr_errors;
            Ip_u32 in_addr_errors;
            Ip_u32 forw_datagrams;
            Ip_u32 in_unknown_protos;
            Ip_u32 in_discards;
            Ip_u32 in_delivers;
            Ip_u32 out_requests;
            Ip_u32 out_discards;
            Ip_u32 out_no_routes;
            Ip_s32 reasm_timeout;
            Ip_u32 reasm_reqds;
            Ip_u32 reasm_oks;
            Ip_u32 reasm_fails;
            Ip_u32 frag_oks;
            Ip_u32 frag_fails;
            Ip_u32 frag_creates;
        } ip;
        struct
        {
            Ip_u32 in_msgs;
            Ip_u32 in_errors;
            Ip_u32 in_dest_unreachs;
            Ip_u32 in_time_excds;
            Ip_u32 in_parm_probs;
            Ip_u32 in_src_quenchs;
            Ip_u32 in_redirects;
            Ip_u32 in_echos;
            Ip_u32 in_echo_reps;
            Ip_u32 in_timestamps;
            Ip_u32 in_timestamp_reps;
            Ip_u32 in_addr_masks;
            Ip_u32 in_addr_mask_reps;
            Ip_u32 out_msgs;
            Ip_u32 out_errors;
            Ip_u32 out_dest_unreachs;
            Ip_u32 out_time_excds;
            Ip_u32 out_parm_probs;
            Ip_u32 out_src_quenchs;
            Ip_u32 out_redirects;
            Ip_u32 out_echos;
            Ip_u32 out_echo_reps;
            Ip_u32 out_timestamps;
            Ip_u32 out_timestamp_reps;
            Ip_u32 out_addr_masks;
            Ip_u32 out_addr_mask_reps;
        } icmp;
        struct
        {
            Ip_u32 active_opens;
            Ip_u32 passive_opens;
            Ip_u32 attempt_fails;
            Ip_u32 estab_resets;
            Ip_u32 curr_estab;
            Ip_u32 in_segs;
            Ip_u32 out_segs;
            Ip_u32 retrans_segs;
            Ip_u32 in_errs;
            Ip_u32 out_rsts;
        } tcp;
        struct
        {
            Ip_u32 in_datagrams;
            Ip_u32 no_ports;
            Ip_u32 in_errors;
            Ip_u32 out_datagrams;
        } udp;
#ifdef IPSCTP
        struct
        {
            /* Begin: mib in RFC3873 */
            Ip_u32      sctp_Curr_Estab;             /* Gauge32 */
            Ip_u32      sctp_Active_Estabs;
            Ip_u32      sctp_Passive_Estabs;
            Ip_u32      sctp_Aborteds;
            Ip_u32      sctp_Shutdowns;
            Ip_u32      sctp_OutOfBlues;
            Ip_u32      sctp_Checksum_Errors;
            Ip_u64      sctp_Out_Ctrl_Chunks;
            Ip_u64      sctp_Out_Order_Chunks;
            Ip_u64      sctp_Out_Unorder_Chunks;
            Ip_u64      sctp_In_Ctrl_Chunks;
            Ip_u64      sctp_In_Order_Chunks;
            Ip_u64      sctp_In_Unorder_Chunks;
            Ip_u64      sctp_Frag_UsrMsgs;
            Ip_u64      sctp_Reasm_UsrMsgs;
            Ip_u64      sctp_Out_SCTP_Packs;
            Ip_u64      sctp_In_SCTP_Packs;
            Ip_u32      sctp_Discontinuity_Time;
            /* End: mib in RFC3873 */
        }sctp;
#endif
       struct
       {
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
       }ip6;

       struct
       {
            Ip_u32    icmp6_input;
            Ip_u32    icmp6_input_err;
            Ip_u32    icmp6_input_badchksum;
            Ip_u32    icmp6_input_nomem;
            Ip_u32    icmp6_send_nomem;
       }
       icmp6;
    } p;
};


/*
 * Data-area for the different signal. The member used is determinied
 * by the signal type
 */
union Ipnet_sig_data_u
{
    struct Ipnet_sig_accept         accept;
    struct Ipnet_sig_ancillary_data ancillary_data;
    struct Ipnet_sig_bind           bind;
    struct Ipnet_sig_broadcast_job  broadcast_job;
    struct Ipnet_sig_connect        connect;
    struct Ipnet_sig_cookie         cookie;
    struct Ipnet_sig_dst_rx         dst_rx;
    struct Ipnet_sig_getname        getname;
    struct Ipnet_sig_if_indexname   indexname;
    struct Ipnet_sig_ioctl          ioctl;
    struct Ipnet_sig_listen         listen;
    struct Ipnet_sig_multi_poll     mpoll;
    struct Ipnet_sig_neigh_resolve  neigh_resolve;
    struct Ipnet_sig_netif          netif;
    struct Ipnet_sig_poll           poll;
    struct Ipnet_sig_sendmsg        sendmsg;
    struct Ipnet_sig_shutdown       shutdown;
    struct Ipnet_sig_socket         socket;
    struct Ipnet_sig_sockopt        sockopt;
#ifndef IPCOM_HAS_STACK_SUSPEND_RESUME
    struct Ipnet_sig_suspend        suspend;
#endif
    struct Ipnet_sig_sysctl         sysctl;
#ifdef IPIPSEC2
    struct Ipnet_sig_ipsec          ipsec;
#endif
    struct Ipnet_sig_stats          stats;
#ifdef IPSCTP
    struct Ipnet_sig_sctp_new_udp   sctp_new_udp;
    struct Ipnet_sig_sctp_set_state sctp_set_state;
    struct Ipnet_sig_sctp_wu        sctp_wu;
#endif
    void                           *ctrl_tag;
};


typedef struct Ipnet_sig_struct
{
    enum Ipnet_sig_type sig_type;

    /*
     * Socket file descriptor, or -1 if not applicable.
     */
    Ip_fd fd;

    /*
     * Used for stack instance to stack instance communication
     */
    struct Ipnet_sig_struct *next;

    /*
     * Function that knows how to free this signal
     */
    void (*free)(struct Ipnet_sig_struct *sig);
    /*
     * Argument to "free"
     */
    struct Ipnet_sig_struct *freesig;

    /*
     * The pipe the response must be sent through. This pointer might
     * be IP_NULL in which case the global IPNET pipe will be used
     */
    Ipcom_pipe         *response_pipe;
    /*
     * PID of signal sender, this value must be the original sender
     * for packets sent between stack instances.
     */
    Ip_pid_t            sender_pid;
    /* PID of signal receiver */
    Ip_pid_t            receiver_pid;
#if IPCOM_VR_MAX > 1
    Ip_u16              sender_vr;
#endif

    /*
     * Will hold the return code from operations performed by a stack
     * instance.
     */
    struct Ipnet_sig_reply reply;

    union Ipnet_sig_data_u d;
}
Ipnet_sig;

/*
 ****************************************************************************
 * 6                    FUNCTIONS
 ****************************************************************************
 */

IP_GLOBAL void ipnet_sig_free(Ipnet_sig *sig);

#ifdef IPCOM_USE_PORT_SPECIFIC_SIGNALS
#define IPCOM_PORT_SIG_NO_REPLY 0
#define IPCOM_PORT_SIG_DO_REPLY 1
IP_PUBLIC int ipcom_handle_port_specific_sig(void* sig);

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
