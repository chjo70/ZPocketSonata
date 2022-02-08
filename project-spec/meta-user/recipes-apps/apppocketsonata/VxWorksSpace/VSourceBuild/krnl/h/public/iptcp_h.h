/*
 * Copyright (c) 2006-2013, 2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
19jan15,ljl  Add support for rfc6528 secure sequence number, V7NET-499
*/

#ifndef IPTCP_H_H
#define IPTCP_H_H

/*
 ****************************************************************************
 * 1                    DESCRIPTION
 ****************************************************************************
 */
/* Definitions that are private to the TCP module */

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

#ifdef IPNET
#include <ipnet.h>
#include <ipnet_h.h>
#endif

#ifdef IPLITE
#include <iplite.h>
#include <iplite_h.h>
#endif

#include "iptcp.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 ****************************************************************************
 * 4                    DEFINES
 ****************************************************************************
 */

/*
 *===========================================================================
 *                         syslog
 *===========================================================================
 */
#ifdef IPCOM_SYSLOG_PRIORITY
#undef IPCOM_SYSLOG_PRIORITY
#endif
#define IPCOM_SYSLOG_PRIORITY    IPTCP_SYSLOG_PRIORITY

#ifdef IPCOM_SYSLOG_FACILITY
#undef IPCOM_SYSLOG_FACILITY
#endif
#define IPCOM_SYSLOG_FACILITY    IPCOM_LOG_IPTCP


/*
 *===========================================================================
 *                         DEBUG/ASSERT
 *===========================================================================
 */

#ifdef IPTCP_DEBUG
#define IPTCP_DEBUG_LINE(x)    x
#else
#define IPTCP_DEBUG_LINE(x)    IP_NOOP
#endif /* IPTCP_DEBUG */


/* Stack specific defines */
# define IP_STACK(x)                         ipnet_ ## x
# define IP_STACK_CONST(x)                   IPNET_ ## x
# define IPTCP_SOCK_VR(s)                    ((s)->vr_index)
# define IPTCP_SOCK_MRIO(s)                  ((s)->mprio)
# define IPTCP_SOCK_ADD_WAITING_RECEIVER(s)  IPNET_SOCK_ADD_WAITING_RECEIVER(s)
# define IPTCP_SOCK_DEL_WAITING_RECEIVER(s)  \
    do { \
        if (IPTCP_SOCK_HAS_WAITING_RECEIVERS(s)) \
            IPNET_SOCK_DEL_WAITING_RECEIVER(s); \
    } while (0)
# define IPTCP_SOCK_HAS_WAITING_RECEIVERS(s) IPNET_SOCK_HAS_WAITING_RECEIVERS(s)


/*
 *===========================================================================
 *                         IPTCP code lock
 *===========================================================================
 */
#ifdef IPNET
# define IPTCP_DATA_LOCK(sl)            IPNET_DATA_LOCK(sl)
# define IPTCP_DATA_UNLOCK(sl)          IPNET_DATA_UNLOCK(sl)
# define IPTCP_DATA_ISLOCKED(sl)        IPNET_DATA_ISLOCKED(sl)
# define IPTCP_DATA_ISLOCKED_ASSERT(sl) IPNET_DATA_ISLOCKED_ASSERT(sl)
#else /* IPLITE */
# define IPTCP_CODE_LOCK_READ()         IPLITE_CODE_LOCK()
# define IPTCP_CODE_LOCK_WRITE()        IPLITE_CODE_LOCK()
# define IPTCP_CODE_LOCK()              IPTCP_CODE_LOCK_WRITE()
# define IPTCP_CODE_UNLOCK()            IPLITE_CODE_UNLOCK()
# define IPTCP_DATA_LOCK(x)             IP_NOOP
# define IPTCP_DATA_UNLOCK(x)           IP_NOOP
# define IPTCP_DATA_ISLOCKED(x)         IP_FALSE
# define IPTCP_DATA_ISLOCKED_ASSERT(sl) IP_NOOP
#endif


/*
 ****************************************************************************
 * 5                    TYPES
 ****************************************************************************
 */

/*
 *===========================================================================
 *                   Parameters for one TCP segment
 *===========================================================================
 */
typedef struct Iptcp_segment_struct
{
    struct Iptcp_segment_struct  *next;
                             /* Next packet in resend list for outgoing and next
                                out-of-order package for incoming */
    Ipcom_pkt   *pkt;        /* Pointer to the packet that holds the TCP segment data */
    Ip_u32       seq_start;  /* First sequence number for segment */
    Ip_u32       seq_end;    /* Last sequence number for segment */
    int          app_start;  /* (Only send) Start of application data */
    int          app_end;    /* (Only send) End of application data */
    Ip_u16       flags_n;    /* The TCP flags for this segment */
#ifdef IPTCP_USE_SACK_OPT
    Ip_u8        is_sacked;  /* (Only send) IP_TRUE if the segment has
                                been ACK:ed in a selective ACK option
                                (Only receiver) IP_FALSE if this segment
                                has not been included in a SACK option yet */
#endif
    Ip_s64       last_msec;  /* Last timestamp this segment was processed */
}
Iptcp_segment;


/*
 *===========================================================================
 *                         Iptcp_stats
 *===========================================================================
 * IPTCP debug statistics useful for debugging the TCP module if things go wrong.
 */
#ifdef IPNET_STATISTICS
#define IPTCP_STATISTICS
#endif

#if defined(IPTCP_DEBUG) || defined(IPTCP_STATISTICS)
typedef struct Iptcp_stats_struct
{
    int    tcp_input;
    int    tcp_input_hdr_trunc;
    int    tcp_input_badchksum;
#ifdef IPTCP_USE_AO
    int    tcp_input_badauth;
#endif
    int    tcp_input_sock_match;
    int    tcp_input_sock_nomatch;
    int    tcp_input_sock_closed;
    int    tcp_input_sock_closed2;
    int    tcp_input_sock_data_in_close_wait;
    int    tcp_input_rst_listen;
    int    tcp_input_nosyn_listen;
    int    tcp_input_backlog_enobufs;
    int    tcp_input_qrecv_enobufs;
    int    tcp_input_syn_inval_state;
    int    tcp_input_syn_inval_option;
    int    tcp_input_inval_win;
    int    tcp_input_rst;
    int    tcp_input_must_have_ack;
    int    tcp_input_must_not_have_ack;
    int    tcp_input_toohigh_ack;
    int    tcp_input_fin;
    int    tcp_input_fin_err;
    int    tcp_input_fin_ok;
    int    tcp_input_queue_pkt_ok;
    int    tcp_input_queue_pkt_outoforder;
    int    tcp_input_queue_pkt_err;
    int    tcp_input_state_err;
    int    tcp_input_listen_invalid_src_addr;

    int    tcp_output;
    int    tcp_output_err;
    int    tcp_output_pkt_nomem;
    int    tcp_output_pkt_enobufs2;

    int    tcp_send;
    int    tcp_send_err;
    int    tcp_send_slept;
    int    tcp_send_sock_errno;
    int    tcp_send_enotconn;
    int    tcp_send_ewouldblock;
    int    tcp_sendto;
    int    tcp_timer_nomem;
    int    tcp_timer_enobufs;
    int    tcp_state_enobufs;
    int    tcp_sock_enobufs;
    int    tcp_listen_backlog_enobufs;

    int    tcp_pkt_drain_outoforder;
}
Iptcp_stats;

#define IPTCP_STATS(xvar)      iptcp->stats.xvar

#define IPTCP_STAT_LINE(xline) xline

#else /* No TCP stats */
#define IPTCP_STATS(xvar)      IP_NOOP
#define IPTCP_STAT_LINE(xline) IP_NOOP
#endif /* defined(IPTCP_DEBUG) || defined(IPTCP_STATISTICS) */

#if defined(IPTCP_USE_AO)
typedef struct Iptcp_ao_inst_struct
{
    Ip_u32             local_isn;        /* local Initial sequence number, this is
                                            needed when changed to new MKT, net-byte */
    Ip_u32             remote_isn;       /* remote Initial sequence number, this is
                                            needed when changed to new MKT, net-byte */
    Iptcp_ao_mkt_inst *current_key;      /* current MKT instance for this TCB */
    Iptcp_ao_mkt_inst *rnext_key;        /* next received MKT instance for this TCB */
    Iptcp_ao_mkt_inst *snext_key;        /* next send MKT instance for this TCB */
    Iptcp_ao_mkt_inst *backup_key;       /* backup MKT instance rnext_key or snext_key */
    Iptcp_ao_keyids   *keyids;
    Ip_u8             *tkey[2];          /* 0 for send, 1 for receive
                                            CONNECTION INIT
                                            0 - Send_SYN_traffic_key
                                            1 - Receive_SYN_traffic_key
                                            ESTABLISHED
                                            0 - Send_other_traffic_key
                                            1 - Receive_other_traffic_key */
    Ip_u32             sne[2];           /* 0/1 for send/receive, detailed in RFC5925 6.2 */
    Ip_u32             prev_seq[2];      /* 0/1 for send/receive, detailed in RFC5925 6.2 */
    Ip_u8              sne_flag[2];      /* 0/1 for send/receive, detailed in RFC5925 6.2 */
    Ip_u8              accept_icmp_flag; /* whether accept the 'hard error' */
}
Iptcp_ao_inst;

typedef struct Iptcp_ao_mkt_list_struct
{
    Iptcp_ao_mkt  mkt;
    Ipcom_list    next;   /* MKT(Master Key Tuple) list next pointer,
                             head in struct Ipsctp_ao_infor.mkt_head[x] */
}
Iptcp_ao_mkt_list;

typedef struct Ipsctp_ao_infor_struct
{
    Ipcom_list mkt_head[2];            /* MKT(Master Key Tuple) list
                                          [domain: 0=inet,1=inet6]
                                          for struct Iptcp_ao_mkt_list */
    Ip_u32     log_rate_limit_val;     /* current remained log rate limit number */
    Ip_bool    log_rate_limit_restart; /* flag for restart log rate limit timer */
}
Ipsctp_ao_infor;
#endif /* defined(IPTCP_USE_AO) */


typedef struct Iptcp_data_struct
{
    /*
     * TCP initial send sequence number
     */
    Ip_u32         iss;
     /*
      * The time a socket was last created
      */
    Ip_s64         msec_last_sock_create;

#ifdef IPTCP_USE_AO
    Ipsctp_ao_infor ao;
#endif

#if defined(IPTCP_DEBUG) || defined(IPTCP_STATISTICS)
    Iptcp_stats        stats;              /* Statistics */
#endif

    /*Secret key for generating initial sequnce number*/
    Ip_u32 key[4];
}
Iptcp_data;


IP_EXTERN Iptcp_data   *iptcp;


/*
 ****************************************************************************
 * 6                    PROTOTYPES
 ****************************************************************************
 */

IP_GLOBAL int iptcp_send_reset(IP_CONST void *peer_addr,
                               IP_CONST void *local_addr,
                               Iptcp_socket *sock,
                               Iptcp_segment *seg);

IP_GLOBAL IP_CONST char *iptcp_state_to_str(int state);
IP_GLOBAL IP_CONST char *iptcp_timer_to_str(int type);

IP_GLOBAL int iptcp_tick_to_string(void *unused, char *buf, Ip_size_t buf_len);
IP_GLOBAL int iptcp_pers_to_string(Iptcp_socket *sock, char *buf, Ip_size_t buf_len);
IP_GLOBAL int iptcp_keep_to_string(Iptcp_socket *sock, char *buf, Ip_size_t buf_len);
IP_GLOBAL int iptcp_conn_to_string(Iptcp_socket *sock, char *buf, Ip_size_t buf_len);
IP_GLOBAL int iptcp_dack_to_string(Iptcp_socket *sock, char *buf, Ip_size_t buf_len);
IP_GLOBAL int iptcp_retr_to_string(Iptcp_socket *sock, char *buf, Ip_size_t buf_len);
IP_GLOBAL int iptcp_tiwa_to_string(Iptcp_socket *sock, char *buf, Ip_size_t buf_len);
IP_GLOBAL int iptcp_lope_to_string(Iptcp_socket *sock, char *buf, Ip_size_t buf_len);
IP_GLOBAL int iptcp_lngr_to_string(Iptcp_socket *sock, char *buf, Ip_size_t buf_len);
IP_GLOBAL int iptcp_zwp_to_string(Iptcp_socket *sock, char *buf, Ip_size_t buf_len);

#ifdef __cplusplus
}
#endif

#endif /* IPTCP_H */

/*
 ****************************************************************************
 *                      END OF FILE
 ****************************************************************************
 */
