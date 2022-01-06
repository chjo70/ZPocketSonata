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
06jun16,rjq  Port TSR defect fix forward from vxworks6.9 into vx7. (F6988)
31dec15,h_x  Remove sysvar process in iptcp_input()
*/

#ifndef IPTCP_H
#define IPTCP_H

/*
 ****************************************************************************
 * 1                    DESCRIPTION
 ****************************************************************************
 */

/*
 * TCP functions and types required by IPNET
 */

/*
 ****************************************************************************
 * 2                    CONFIGURATION
 ****************************************************************************
 */

#include "iptcp_config.h"

/*
 ****************************************************************************
 * 3                    INCLUDE FILES
 ****************************************************************************
 */

#include <ipcom_list.h>
#include <ipcom_spinlock.h>

#include <ipnet.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 ****************************************************************************
 * 4                    DEFINES
 ****************************************************************************
 */

/* IPTCP release XYyZz,
   X  = major version
   Yy = minor version (two different versions might be incompatible)
   Zz = patch version (two different versions are always compatible)  */
#define IPTCP_RELEASE 60701


/* TCP control flags */
#define IPTCP_TCPC_FLAG_PASSIVE_OPEN   (1 << 0)  /* This is a listen socket */
#define IPTCP_TCPC_FLAG_SOCK_CLOSED    (1 << 1)  /* The TCP module has closed the socket */
#define IPTCP_TCPC_FLAG_CONNABORTED    (1 << 2)  /* User process has called close, but data was present */
#define IPTCP_TCPC_FLAG_SMALL_PKT_OUT  (1 << 3)  /* 1 small (less that MSS) packet outstanding */

#define IPTCP_TCPC_FLAG_NO_SMDE        (1 << 6)  /* No Smooth mean deviation estimator calculated yet */
#define IPTCP_TCPC_FLAG_RTT            (1 << 7)  /* Round Trip Time mesurement in progress */

#define IPTCP_TCPC_FLAG_FIN_PENDING    (1 << 12) /* User process has called close, but data was present */
#define IPTCP_TCPC_FLAG_TIMESTAMP_OPT  (1 << 13) /* Include timestamp option */
#define IPTCP_TCPC_FLAG_WND_SCALE_OPT  (1 << 14) /* Include window scaling option */
#define IPTCP_TCPC_FLAG_RESENDING      (1 << 15) /* A resend timer has expired, send packets from the
                                                    resend queue instead of the send queue */
#define IPTCP_TCPC_FLAG_FAST_RETRANS   (1 << 16) /* The oldest non-acked segment has been fast retransmitted */
#define IPTCP_TCPC_FLAG_SENDER_URG     (1 << 18) /* The this socket is in sender urgent mode */
#define IPTCP_TCPC_FLAG_RECEIVER_URG   (1 << 19) /* The this socket is in receiver urgent mode */
#define IPTCP_TCPC_FLAG_SACK           (1 << 20) /* Selective ACK option can be sent */
#define IPTCP_TCPC_FLAG_CORK           (1 << 21) /* Do not send any frames less than a MSS if this is set */
#define IPTCP_TCPC_FLAG_RFC_1122_URG   (1 << 24) /* Use the definition of urgen data described in RFC 1122, else use RFC 793*/
#define IPTCP_TCPC_FLAG_KCLOSE_PENDING (1 << 25) /* iptcp_sock_kclose() function must be called
                                                    when user closes socket */
#define IPTCP_TCPC_FLAG_USER_REF       (1 << 26) /* This socket has been given to a user via
                                                    socket() or accept() */
#define IPTCP_TCPC_USER_CLOSED         (1 << 27) /* A user task has called close() on this socket.
                                                    The TCB will is on the user_closed_sock list. */
#define IPTCP_TCPC_ACK_FOR_PUSH        (1 << 28)
#ifdef IPTCP_USE_AO
#define IPTCP_TCPC_USE_AO              (1 << 31) /* indicate if this socket MUST use RFC5925 option */
#endif

/* Size of a TCP header without options */
#define IPTCP_TCP_HDR_SIZE   20  /* Default/minimum TCP header is 20 octets long */

/* Stack specific types */
#define IP_STACK(x)                    ipnet_ ## x
#define ipstack                        ipnet_pri_ptr()
#define Iptcp_socket                   struct Ipnet_socket_struct
#define Iptcp_netif                    struct Ipnet_netif_struct
#define Iptcp_timeout                  struct Ipnet_timeout_struct
#define Iptcp_timeout_handler          struct Ipnet_timeout_handler_struct


/* This socket has an exceptional event pending */
#define IP_SHUT_EX (IP_SHUT_RDWR + 10)


/*
 * Partial lock, protects that last TCP segment in the send queue if
 * that segment is less than a MSS is size. The ipcom_sendmsg()
 * function might append data on that segment until it contains MSS
 * bytes of data
 */
#ifdef IPCOM_FORWARDER_NAE
/*
 * NAE:s does not need the partial lock since the socket is always
 * protected by other means
 */
#define Iptcp_partial_lock_t      No_type_t
#define iptcp_partial_create(pl)  IPCOM_SUCCESS
#define iptcp_partial_delete(pl)  IPCOM_SUCCESS
#define iptcp_partial_lock(l)     IP_NOOP
#define iptcp_partial_unlock(l)   IP_NOOP
#elif defined(IP_PORT_VXWORKS)
/*
 *  The partial lock can be a spinlock on VxWorks since it possible to
 *  hold this lock while copy data from userland on this port
 */
#define Iptcp_partial_lock_t      Ipcom_spinlock
#define iptcp_partial_create(pl)  ipcom_spinlock_create(pl)
#define iptcp_partial_delete(pl)  ipcom_spinlock_delete(pl)
#define iptcp_partial_lock(l)     ipcom_spinlock_lock(&l)
#define iptcp_partial_unlock(l)   ipcom_spinlock_unlock(&l)
#else
#define Iptcp_partial_lock_t      Ipcom_mutex
#define iptcp_partial_create(pl)  ipcom_mutex_create(pl)
#define iptcp_partial_delete(pl)  ipcom_mutex_delete(pl)
#define iptcp_partial_lock(l)     ipcom_mutex_lock(l)
#define iptcp_partial_unlock(l)   ipcom_mutex_unlock(l)
#endif


/*
 ****************************************************************************
 * 5                    TYPES
 ****************************************************************************
 */

/* Forward declarations */
struct Ipnet_data_struct;
struct Ipnet_netif_struct;
struct Ipnet_socket_struct;
struct Ipnet_timeout_handler_struct;
struct Ipnet_timeout_struct;
struct Ipnet_pmtu_cb_data_struct;

/* TCP states (numeric values match those in RFC2452) */
typedef enum Iptcp_state_enum
{
    IPTCP_STATE_CLOSED      = 1,
    IPTCP_STATE_LISTEN      = 2,
    IPTCP_STATE_SYN_SENT    = 3,
    IPTCP_STATE_SYN_RCVD    = 4,
    IPTCP_STATE_ESTABLISHED = 5,
    IPTCP_STATE_CLOSE_WAIT  = 6,
    IPTCP_STATE_FIN_WAIT_1  = 7,
    IPTCP_STATE_CLOSING     = 8,
    IPTCP_STATE_LAST_ACK    = 9,
    IPTCP_STATE_FIN_WAIT_2  = 10,
    IPTCP_STATE_TIME_WAIT   = 11,
    IPTCP_STATE_DELETE_TCB  = 12
}
Iptcp_state_t;


/*
 *===========================================================================
 *                      Iptcp_notifycb
 *===========================================================================
 * Description: Is called when an event happens that can affect any of
 *              socket parameters
 * Parameters:  sock - The affected socket.
 *              event - One of the IPNET_SOCKET_EVENT_xxx constants
 * Returns:
 *
 */
typedef void (*Iptcp_notifycb)(Iptcp_socket *sock, int event);

/* Possible socket events */
#define IPTCP_SOCKET_EVENT_PATH_MTU    1       /* The path MTU has changed               */
#define IPTCP_SOCKET_EVENT_KICKSTART   2       /* Try 'kickstart' this particular socket */
#define IPTCP_SOCKET_EVENT_KEEP_ALIVE  3       /* Keep-alive status has changed */

/*
 * Timer types
 */
typedef enum Iptcp_timer_type_enum {
    IPTCP_TMRT_NONE,  /* Do not add a timer, use by resend */
    IPTCP_TMRT_CONN,  /* Connection Establishment */
    IPTCP_TMRT_DACK,  /* Delayed Acknowledge */
    IPTCP_TMRT_KEEP,  /* Keep-alive */
    IPTCP_TMRT_LNGR,  /* Linger timer */
    IPTCP_TMRT_LOPE,  /* Lost peer (used during shutdown to avoid dead sockets) */
    IPTCP_TMRT_PERS,  /* Persist */
    IPTCP_TMRT_RCON,  /* Retry connect */
    IPTCP_TMRT_RETR,  /* Retransmission */
    IPTCP_TMRT_RSRT,  /* Restart the 'send-FIN' call */
    IPTCP_TMRT_TIWA,  /* TIME_WAIT */
    IPTCP_TMRT_ZWP,   /* Time the peer has left to open its receive window */
    IPTCP_TMRT_WUPW,  /* Time the tcp sender wait for peer to update window */
    IPTCP_TMRT_MAX
} Iptcp_timer_type;

#ifdef IPTCP_USE_AO
struct Iptcp_ao_inst_struct;

typedef void (*Iptcp_ao_cmd_dump_func)(void *data, void *cookie);

typedef enum Iptcp_ao_alg_type_enum
{
    IPTCP_AO_ALG_NONE = 0,
#ifdef IPTCP_USE_AO_SHA
    IPTCP_AO_ALG_SHA1,
#endif
#ifdef IPTCP_USE_AO_AESCMAC
    IPTCP_AO_ALG_AESCMAC,
#endif
    IPTCP_AO_ALG_MAX
}
Iptcp_ao_alg_type;

#define IPTCP_AO_MKT_FLAGS_DEL            (0X0001)
#define IPTCP_AO_MKT_FLAGS_UPDATE_AUTH    (0X0010)
#define IPTCP_AO_MKT_FLAGS_UPDATE_KDF     (0X0020)
#define IPTCP_AO_MKT_FLAGS_UPDATE_MKEY    (0X0040)
#define IPTCP_AO_MKT_FLAGS_UPDATE_OPTFLAG (0X0080)
#define IPTCP_AO_MKT_FLAGS_UPDATE_RCVID   (0X0100)

#if 0 /* FIXME : do not check the max length of master-key */
#define IPTCP_AO_MKT_MKEY_LEN_MAX         (512)
#endif

typedef struct Iptcp_ao_mkt_key_struct
{
    Ip_u8   domain;                          /* IP_AF_INET or IP_AF_INET6
                                              * MUST be the first one, RTNETLINK will
                                              * use this filed as the first */
    union
    {
        Ip_u8 pad[3];
        struct
        {
            Ip_u8   snd_id;                  /* used for setting */
            Ip_u16  flags;                   /* used for setting */
        } infor;
    } ext;

    union Ip_in_addr_union   src;            /* Source address in network endian. */
    union Ip_in_addr_union   dst;            /* Destination address in network endian. */
    Ip_u16                   src_port;       /* source port */
    Ip_u16                   dst_port;       /* destination port */
    Ip_u32                   srcscope_n;     /* IPv6 only */
    Ip_u32                   dstscope_n;     /* IPv6 only */

    struct mkt_key_mask_struct
    {
        union Ip_in_addr_union   src;        /* Source mask */
        union Ip_in_addr_union   dst;        /* Destination mask */
        Ip_u32                   srcscope_n;
        Ip_u32                   dstscope_n;
    } mask;

    /* Port and address range */
    union Ip_in_addr_union   src_max;
    union Ip_in_addr_union   dst_max;
    Ip_u16                   src_max_port;
    Ip_u16                   dst_max_port;
}
Iptcp_ao_mkt_key;

typedef struct Iptcp_ao_mkt_inst_struct
{
    Ip_u8              snd_id;    /* the valude to filled AO KeyId field */
    Ip_u8              rcv_id;    /* local recv_id to match received KeyId */
    Ip_u8              opt_flag;  /* whether include other TCP option when calc MAC */
    Ip_u8              auth_len;  /* the authentication length, default is 12 bytes,
                                     it can be 12-16 byte, RFC5925 2.2 */
    Iptcp_ao_alg_type  auth;      /* authentication algorithm, SHA1/AESCMAC/... */
    Iptcp_ao_alg_type  kdf;       /* authentication algorithm, SHA1/AESCMAC/... */
    char              *mkey;      /* Master key string */
    Ip_u32             mkey_len;  /* Master key string length */
}
Iptcp_ao_mkt_inst;

typedef struct Iptcp_ao_mkt_struct
{
    Iptcp_ao_mkt_key   key;
    Iptcp_ao_mkt_inst  inst;
}
Iptcp_ao_mkt;

typedef struct Iptcp_ao_keyid_pair_struct
{
    Ip_u8              snd_id;
    Ip_u8              rcv_id;
}
Iptcp_ao_keyid_pair;

typedef struct Iptcp_ao_keyids_struct
{
    Ip_u32              max_len;         /* in implementation, 2 bytes used for current
                                            postion, 2 bytes used for the max length,
                                            for user only see the max length */
    Iptcp_ao_keyid_pair key_pairs[1];
}
Iptcp_ao_keyids;
#endif

/*
 * TCP timer structure.
 */
typedef struct Iptcp_timer_struct
{
    /*
     * Required so the timer can be part of the 'timers' list in the
     * TCB structure.
     */
    Ipcom_list list;

    /*
     * Absolute time when this timer expires.
     */
    Ip_s64 msec_expires;

    /*
     * Type of timer. A direct pointer to the timeout is not kept
     * since each NAE must call the timeout handler that is part of
     * its code segment.
     */
    Iptcp_timer_type type;
} Iptcp_timer;



/*
 *===========================================================================
 *                      Iptcp_socklookup
 *===========================================================================
 * Context:     A network task. The ipnet reachable sockets lock must be held
 *              before calling this routine.
 * Description: Returns the first socket that matches the specified parameters.
 * Parameters:  vr - The virtual router the matching socket must be part of.
 *              proto - the protocol to match.
 *              local_addr - the local address to match or IP_NULL for any address.
 *              local_port - the local port to match or 0 for any port.
 *              peer_addr - the peer address to match or IP_NULL for any address.
 *              peer_port - the peer port to match or 0 for any port.
 * Returns:     The matching socket or IP_NULL if no socket matched.
 */
typedef Iptcp_socket * (*Iptcp_socklookup)(Ip_u16 vr, int proto,
                                           IP_CONST void *local_addr,
                                           Ip_u16 local_port,
                                           IP_CONST void *peer_addr,
                                           Ip_u16 peer_port);


/*
 *===========================================================================
 *                  TCB sending parameters
 *===========================================================================
 */
struct Iptcp_send
{
    Ip_u32      seq_next;   /* The sequence number of next byte to
                               send */
    Ip_u32      seq_small;  /* The last +1 sequence number in the last
                               packet sent smaller than MSS */
    Ip_u32      uack_bytes; /* Number of unacknowledged data bytes
                               outstanding */
    Ip_u32      peerwnd;    /* Maximum number of bytes that the peer
                               is ready to receive */
    Ip_u32      cwnd;       /* Congestion windows in bytes */
    Ip_u32      ssthresh;   /* Slow Start Threshold size (in bytes) */
#ifdef IPTCP_USE_TIMESTAMP_OPT
    Ip_u32      ts_last_ack;/* The latest ACK:ed timestamp */
#endif
    Ip_u32      lowat;      /* The low water mark for sending */
    Ip_u32      urg_ptr;    /* Urgent pointer, only valid if in send
                               urgent mode () */
    Ip_u16      last_wnd;   /* Value of the last sent recv window size */
    Ip_u8       wnd_scale;  /* RFC1323 window scale shift, == 0 on
                               <SYN,ACK> means to not use window
                               scaling option */
#ifdef IP_ASSERT
    Ip_u8       partial_locked;  /* 1 if the partial_lock is held by owner
                                  * network task. 0 otherwise.
                                  */
#endif
    Ipcom_pkt  *head;       /* The send buffer, can contain multiple
                               unsent packets, pkt->start is the
                               offset to the application layer
                               data. Head of send queue */
    Ipcom_pkt  *tail;       /* Tail of send queue */
    Ipcom_pkt  *partial;    /* Last sent packet that does not contain
                               a full MSS of data */
#ifndef IPCOM_FORWARDER_NAE
    Iptcp_partial_lock_t partial_lock; /* Lock that protects the
                                 'partial' member */
#endif

    struct Iptcp_segment_struct *resend_head; /* List of sent segments
                                                 for which an ack has
                                                 not been received. */
    struct Iptcp_segment_struct *resend_tail; /* The list is sorted on
                                                 increasing sequence
                                                 number */
#ifdef IPTCP_USE_SACK_OPT
    Ip_bool     resend_gap_exists;   /* gap detected */
    Ip_u32      resend_gap_start;    /* beginning of gap */
    Ip_u32      resend_gap_end;      /* last resent data byte */
    Ip_u32      resent_last;         /* last resent data byte */
#endif /* IPTCP_USE_SACK_OPT */
};


/*
 *===========================================================================
 *                  TCB receiving parameters
 *===========================================================================
 */
struct Iptcp_recv
{
    Ip_u32      seq_next;       /* The start sequence number of the
                                   next expected TCP segment sent from
                                   the peer */
    Ip_u32      last_ack_sent;  /* The last received sequence number
                                   that an ACK has been sent for */
#ifdef IPTCP_USE_TIMESTAMP_OPT
    Ip_u32      ts_recent;      /* The timestamp to echo back to the
                                 * sender */
    Ip_u32      last_ts_sec;    /* Absolute time in seconds when
                                 * ts_resent was lasted updated */
#endif
    Ip_u32      lowat;          /* The low water mark for receiving */
    Ip_u32      urg_ptr;        /* Urgent pointer, only valid if in
                                   receive urgent mode () */
    Ip_u8       wnd_scale;      /* RFC1323 window scale shift, == 0 on
                                   <SYN,ACK> means to not use window
                                   scaling option */
    Ip_s16      last_stack_idx; /* stack index that originally received
                                   the last segment from the peer */
    struct Iptcp_segment_struct *out_of_order_seg; /* Segments
                             received, but was out of order.  Will be
                             moved to the received queue when the
                             missing segment(s) are received */
};

/*
 *===========================================================================
 *                  TCB (Transmission Control Block)
 *===========================================================================
 */
typedef struct Iptcp_tcb_struct
{
    Iptcp_socket  *sock;         /* The socket associated with this TCB */
    Ipcom_list     transient;    /* List of TCB:s in transient states */
    Ipcom_list     closed;       /* List of TCP sockets for which the
                                    user application has called close() */
#ifndef IPCOM_FORWARDER_NAE
    Ipcom_list     active;       /* List of active TCP TCB:s */
#endif

    Ip_u32         flags;        /* IPTCP_TCPC_FLAG_xxx flags */
    Iptcp_state_t  state;        /* The current state of the TCP connection */
    Ip_u8          duplicate_ack;/* Number of duplicate acks received */
    Ip_u8          retr_count;   /* Number of retransmission timeouts */
    Ip_u8          peer_responded_to_pers; /* The peer has responded at least one time
                                              since the presist timer was last reset */
    Ip_u8          migrate;      /* hint to migrate */
#define IPTCP_NOT_MIGRATING          0
#define IPTCP_MIGRATE_NOW            1
#define IPTCP_MIGRATION_IN_PROGRESS  2

    Ip_u16         mss;          /* Maximum Segment Size for the connection */
    Ip_u16         peer_mss;     /* Maximum Segment Size presented by the peer */
    Ip_u16         max_mss;      /* User set maximum mss or 0 to use the largest possible MSS */
    Ip_u16         recv_mss;     /* Maximum Recv Segment Size negotiated in handshake for the connection */
#ifdef IPCOM_USE_TSO
    Ip_u16         tso_factor;   /* The number of MSS each packet can hold when
                                  * passed to the driver. */
#endif
    long         sec_to_linger;/* Time this socket will linger after close */

    Ip_u16         keepintvl;    /* Interval between keep-alive probes */
    Ip_u16         keepcnt;      /* Number of keep-alive probes before dropping connection */

    Ip_u32         persist_timeout; /* Number of seconds before the session is
                                       dropped if the peer never stops announcing
                                       receive windows of zero octets */

    Ipcom_list     timers;       /* List of active TCP timers for this
                                    session. NOTE: timers are not
                                    sorted in any way in this
                                    list. The reson for that is: most
                                    TCP timers will be canceled, so
                                    the most critical operations are
                                    starting and cancel a timer */
    /*
     * This are the set of possible timers that can be in the 'timers'
     * list
     */
    Iptcp_timer    tmr;          /* Connect, time wait, lost peer
                                    timer. Can use the same structure
                                    since they cannot run at the same
                                    time */
    Iptcp_timer    tmr_dack;     /* Delayed or immediate ACK timer */
    Iptcp_timer    tmr_retrans;  /* Retransmission, keep-alive or
                                    persist timer */
    Iptcp_timer    tmr_retry;    /* Retry timer, used to retry
                                    allocating packet for pure SYN
                                    and pure FIN packets in case
                                    ipcom_pkt_malloc() returns
                                    IP_NULL */
    Iptcp_timer    tmr_lngr;     /* Linger timer */
    Iptcp_timer    tmr_keep;     /* Keep alive timer */
    Iptcp_timer    tmr_pers;     /* Persist timer */
    Iptcp_timer    tmr_zwp;      /* Time left to open rcv window */
    Iptcp_timer    tmr_wupw;     /* Wait for peer to send update window timer */

    Ip_s32         srtt;         /* Smoothed Round Trip Time in microseconds */
    Ip_s32         smde;         /* Smooth mean deviation estimator in ticks (scaled as srtt) */
    Ip_s32         rto;          /* Retransmission timeout (scaled as srtt) */
    Ip_u32         msec_sent;    /* Absolute time when a timed data segment was sent */
    Ip_u32         seq_timed;    /* A sequence number of the first data byte in the timed segment */
    struct Iptcp_send send;
    struct Iptcp_recv recv;
    int            soft_error;   /* Error code to use if this connections timeout */

    Iptcp_socket  *parent;       /* The listen socket that was used to create this socket */
    Ip_u16         backlog_len;  /* Maximum number of entries in the backlog */
    Ip_u16         backlog_used; /* Number of used entries (pending + done) in the backlog */
    int           *backlog_pending;/* Connections that are doing the three-way handshake */
    int           *backlog_done; /* Connections that have finished the three-way handshake */

    Ip_u32 (*get_mss)(Iptcp_socket *sock, Ip_bool *is_link_local);

#ifdef IPTCP_USE_MD5_SIGNATURE_OPT
    void          *md5_key;
    Ip_size_t      md5_key_len;
#endif /* IPTCP_USE_MD5_SIGNATURE_OPT */

#ifdef IPTCP_USE_AO
    struct Iptcp_ao_inst_struct *ao;
#endif

    Ip_u32      max_peerwnd;     /* Maximum peerwnd, used for tiny window support */

#ifdef IPTCP_DEBUG
    /* The last tick when the calculated roundtrip time was printed */
    Ip_s64         rtt_last_printed;
#endif /* IPTCP_DEBUG */

}
Iptcp_tcb;


/*
 ****************************************************************************
 * 6                    PROTOTYPES
 ****************************************************************************
 */

IP_GLOBAL void iptcp_create_instance(int stack_instance);
IP_PUBLIC int  iptcp_create(void);
IP_PUBLIC int  iptcp_start(void);
IP_PUBLIC const char *iptcp_version(void);

IP_PUBLIC Iptcp_state_t iptcp_get_state(Iptcp_socket *sock);
IP_PUBLIC void iptcp_sock_init(Iptcp_socket *sock);
IP_PUBLIC int  iptcp_connect(Iptcp_socket *sock);
IP_PUBLIC void iptcp_shutdown(Iptcp_socket *sock, int how);
IP_PUBLIC int  iptcp_close(Iptcp_socket *sock);
IP_PUBLIC void iptcp_sock_free(Iptcp_socket *sock);
IP_PUBLIC int  iptcp_send(Iptcp_socket *sock,
                          IP_CONST struct Ip_msghdr *msg,
                          Ipcom_pkt *pkt);
IP_PUBLIC int  iptcp_usr_recv(Iptcp_socket *sock, void *buf, Ip_size_t len, int flags);
IP_PUBLIC int  iptcp_listen(Iptcp_socket *sock, int backlog);
IP_PUBLIC int  iptcp_accept(Iptcp_socket *sock, struct Ip_sockaddr *name, Ip_socklen_t *addrlen);
IP_PUBLIC int  iptcp_getsockopt(Iptcp_socket *sock, int level, int optname, void *optval, Ip_socklen_t *optlen);
IP_PUBLIC int  iptcp_setsockopt(Iptcp_socket *sock, int level, int optname, IP_CONST void *optval, Ip_socklen_t optlen);
IP_PUBLIC int  iptcp_drop_connection(Iptcp_socket *sock, int error_code);
IP_PUBLIC void iptcp_migration_complete_sig(Ip_fd fd);
IP_PUBLIC void iptcp_window_update(int fd);
IP_PUBLIC void iptcp_pkt_drain(struct Ipnet_data_struct *net);

#ifdef IPCOM_USE_INET
IP_PUBLIC void iptcp_icmp4_report(Iptcp_socket *sock, int type, int code, void *tcp_hdr);
#endif
#ifdef IPCOM_USE_INET6
IP_PUBLIC void iptcp_icmp6_report(Iptcp_socket *sock, int type, int code, void *tcp_hdr);
#endif

IP_GLOBAL void iptcp_net_pmtu_update(struct Ipnet_data_struct *net,
                                     const struct Ipnet_pmtu_cb_data_struct *data);

IP_PUBLIC int iptcp_ioctl(Iptcp_socket *sock, unsigned long request, void *argp);

#ifdef IPCOM_USE_MIB2
IP_PUBLIC int  iptcp_get_rto(Ip_bool min);
IP_PUBLIC int  iptcp_change_state_global(Iptcp_socket *sock, int new_state);
#endif /* IPCOM_USE_MIB2 */

#ifdef IPTCP_DEBUG
IP_PUBLIC void iptcp_pkt_freecheck(Ipcom_pkt *pkt);

IP_PUBLIC Ip_fd iptcp_ctrl_verify_retransq(Ipcom_pkt *pkt);
IP_PUBLIC Ip_fd iptcp_ctrl_verify_sockrecvq(Ipcom_pkt *pkt);
IP_PUBLIC Ip_fd iptcp_ctrl_verify_sockooorecvq(Ipcom_pkt *pkt);
#endif

#ifdef IPTCP_USE_AO
/*******************************************************************************
*
* iptcp_ao_api_mkt_add - add a MKT
*
* add a MKT(Master Key Tuple).
*
* Parameters:
* \is
* \i <mkt>
* The information of 'Iptcp_ao_mkt' structure for adding.
* \ie
*
* RETURNS:
* OK or one of the following errors:
* 'IP_ERRNO_EINVAL', 'IP_ERRNO_ENOMEM', 'IP_ERRNO_EEXIST'
*/
IP_PUBLIC int iptcp_ao_api_mkt_add(Iptcp_ao_mkt *mkt);
/*******************************************************************************
*
* iptcp_ao_api_mkt_delete - delete a MKT
*
* delete a MKT(Master Key Tuple).
*
* Parameters:
* \is
* \i <mkt>
* The information of 'Iptcp_ao_mkt' structure for deleting.
* \ie
*
* RETURNS:
* OK or one of the following errors:
* 'IP_ERRNO_EINVAL', 'IP_ERRNO_ENOMEM', 'IP_ERRNO_ENOENT'
*/
IP_PUBLIC int iptcp_ao_api_mkt_delete(Iptcp_ao_mkt *mkt);
/*******************************************************************************
*
* iptcp_ao_api_mkt_update - update a MKT
*
* update a MKT(Master Key Tuple).
*
* Parameters:
* \is
* \i <mkt>
* The information of 'Iptcp_ao_mkt' structure for updating.
* \ie
*
* RETURNS:
* OK or one of the following errors:
* 'IP_ERRNO_EINVAL', 'IP_ERRNO_ENOMEM', 'IP_ERRNO_ENOENT'
*/
IP_PUBLIC int iptcp_ao_api_mkt_update(Iptcp_ao_mkt *mkt);
/*******************************************************************************
*
* iptcp_ao_api_mkt_update - dump all MKTs
*
* dump all MKTs(Master Key Tuple).
*
* Parameters:
* \is
* \i <family>
* the address family(IP_AF_INET or IP_AF_INET6 or IP_AF_UNSPEC) that dumping.
* \i <dump_func>
* The callback function, it will be called when dump each MKT.
* \i <cookie>
* The cookie parameter, it will be passed to the callback function.
* \ie
*
* RETURNS:
* OK or one of the following errors:
* 'IP_ERRNO_EINVAL', 'IP_ERRNO_ENOMEM', 'IP_ERRNO_ENOENT'
*/
IP_PUBLIC int iptcp_ao_api_mkt_dump(Ip_u8 family, Iptcp_ao_cmd_dump_func dump_func, void *cookie);
/*******************************************************************************
*
* iptcp_ao_api_mkt_update - get a MKT
*
* get a MKT(Master Key Tuple).
*
* Parameters:
* \is
* \i <mkt>
* The information of 'Iptcp_ao_mkt' structure for geting.
* \ie
*
* RETURNS:
* OK or one of the following errors:
* 'IP_ERRNO_EINVAL', 'IP_ERRNO_ENOMEM', 'IP_ERRNO_ENOENT'
*/
IP_PUBLIC int iptcp_ao_api_mkt_get(Iptcp_ao_mkt *mkt);
/*******************************************************************************
*
* iptcp_ao_api_mkt_update - flush all MKTs
*
* flush all MKTs(Master Key Tuple).
*
* Parameters:
* \is
* \i <family>
* the address family(IP_AF_INET or IP_AF_INET6 or IP_AF_UNSPEC) that flushing.
* \ie
*
* RETURNS:
* OK or one of the following errors:
* 'IP_ERRNO_EINVAL', 'IP_ERRNO_ENOMEM', 'IP_ERRNO_ENOENT'
*/
IP_PUBLIC int iptcp_ao_api_mkt_flush(Ip_u8 family);
#endif

#ifdef __cplusplus
}
#endif

#endif /* IPTCP_H */

/*
 ****************************************************************************
 *                      END OF FILE
 ****************************************************************************
 */
