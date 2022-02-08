/* sctp_socket.h - IPNET SCTP socket header file */

/*
 * Copyright (c) 2007 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement. No license to Wind River intellectual property rights
 * is granted herein. All rights not licensed by Wind River are reserved
 * by Wind River.
 */

/*
modification history
--------------------
01a,18jul07,fei  Created,base on draft-ietf-tsvwg-sctpsocket-16.
*/

#ifndef SCTP_SOCKET_H
#define SCTP_SOCKET_H
/*
 ****************************************************************************
 * 1                    DESCRIPTION
 ****************************************************************************
 *
 * This is the header file for SCTP module.
 */

/*
 ****************************************************************************
 * 2                    CONFIGURATION
 ****************************************************************************
 */

/*
 ****************************************************************************
 * 3                    INCLUDE FILES
 ****************************************************************************
 */
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 ****************************************************************************
 * 4                    DEFINES
 ****************************************************************************
 */

/* ancillary data types */
typedef enum sctp_cmsg_t_enum
{
    SCTP_INIT	= 0x0001,
    SCTP_SNDRCV,
    SCTP_EXTRCV
}
sctp_cmsg_t;

typedef uint32_t sctp_assoc_t;

/*
 *===========================================================================
 *                  IPSCTP sctp  parameters
 *===========================================================================
 * All options that support specific settings on an association by
 * filling in either an association id variable or a sockaddr_storage
 * SHOULD also support setting of the same value for the entire endpoint
 * (i.e. future associations).  To accomplish this the following logic
 * is used when setting one of these options:
 *
 * a) If an address is specified via a sockaddr_storage that is included
 *    in the structure, the address is used to lookup the association
 *    and the settings are applied to the specific address (if
 *    appropriate) or to the entire association.
 * b) If an association identification is filled in but not a
 *    sockaddr_storage (if present), the association is found using the
 *    association identification and the settings should be applied to
 *    the entire association (since a specific address is not
 *    specified).  Note this also applies to options that hold an
 *    association identification in their structure but do not have a
 *    sockaddr_storage field.
 * c) If neither the sockaddr_storage or association identification is
 *    set, i.e. the sockaddr_storage is set to all 0's (INADDR_ANY) and
 *    the association identification is 0, the settings are a default
 *    and to be applied to the endpoint (all future associations).
 *
 * For the one-to-many style sockets, an sctp_assoc_t structure
 * (association ID) is used to identify the association instance that
 * the operation affects.  So it must be set when using this style.
 *
 * For the one-to-one style sockets and branched off one-to-many style
 * sockets (see Section 8.2) this association ID parameter is ignored.
 *
 * Note that socket or IP level options are set or retrieved per socket.
 * This means that for one-to-many style sockets, those options will be
 * applied to all associations belonging to the socket.  And for one-to-
 * one style, those options will be applied to all peer addresses of the
 * association controlled by the socket.  Applications should be very
 * careful in setting those options.
 */
enum sctp_optname
{
    SCTP_OPTNAME_BASE           = 0,          
    SCTP_RTOINFO                = 1,               
    SCTP_ASSOCINFO              = 2,             
    SCTP_DEFAULT_SEND_PARAM     = 3,    
    SCTP_GET_PEER_ADDR_INFO     = 4,    
    SCTP_PRIMARY_ADDR           = 5,
    SCTP_ADAPTATION_LAYER       = 6,
    SCTP_PEER_ADDR_PARAMS       = 7,      
    SCTP_STATUS                 = 8,                
    SCTP_CONTEXT                = 9,               
    SCTP_AUTH_ACTIVE_KEY        = 10,
    SCTP_AUTH_CHUNK             = 11,       
    SCTP_AUTH_KEY               = 12,       
    SCTP_AUTH_DEACTIVATE_KEY    = 13,       
    SCTP_AUTH_DELETE_KEY        = 14,       
    SCTP_PEER_AUTH_CHUNKS       = 15,
    SCTP_LOCAL_AUTH_CHUNKS      = 16,     
    SCTP_EVENTS                 = 17,    
    SCTP_INITMSG                = 18,
    SCTP_AUTOCLOSE              = 19,
    SCTP_DISABLE_FRAGMENTS      = 20,
    SCTP_FRAGMENT_INTERLEAVE    = 21,
    SCTP_PARTIAL_DELIVERY_POINT = 22,
    SCTP_MAXSEG                 = 23,
    SCTP_NODELAY                = 24,
    SCTP_SET_PEER_PRIMARY_ADDR  = 25,
    SCTP_I_WANT_MAPPED_V4_ADDR  = 26,
    SCTP_DELAYED_SACK           = 27,
    SCTP_USE_EXT_RCVINFO        = 28,
    SCTP_AUTO_ASCONF            = 29,
    SCTP_EXPLICIT_EOR           = 30,
    SCTP_REUSE_PORT             = 31,
    SCTP_GET_ASSOC_NUMBER       = 32,
    SCTP_GET_ASSOC_ID_LIST      = 33,
    SCTP_GET_PEER_ADDRS         = 34,
    SCTP_GET_LOCAL_ADDRS        = 35,
    SCTP_GET_PEER_ADDRS_SIZE    = 36,
    SCTP_GET_LOCAL_ADDRS_SIZE   = 37,
    SCTP_BINDX_ADD_ADDR         = 38,
    SCTP_BINDX_REM_ADDR         = 39,
    SCTP_GET_ADDR_LEN           = 40,
    SCTP_CONNECTX               = 41,
    SCTP_CONNECTX_DELAY         = 42,
    SCTP_CONNECTX_COMPLETE      = 43,
    SCTP_MAX_BURST              = 44,
    SCTP_GET_PEELOFF            = 45,
    SCTP_OPTNAME_MAX    
};


/*
 ****************************************************************************
 * 5                    TYPES
 ****************************************************************************
 */

/*
 *===========================================================================
 *                  IPSCTP sctp init message parameters
 *===========================================================================
 * 5.2.1.  SCTP Initiation Structure (SCTP_INIT)
 * This cmsghdr structure provides information for initializing new SCTP
 * associations with sendmsg().  The SCTP_INITMSG socket option uses
 * this same data structure.  This structure is not used for recvmsg().
 * 
 * cmsg_level    cmsg_type      cmsg_data[]
 * ------------  ------------   ----------------------
 * IPPROTO_SCTP  SCTP_INIT      struct sctp_initmsg
 */
struct sctp_initmsg
{
    uint16_t sinit_num_ostreams;  /* the number of streams that the application
                                   wishes to be able to send to */
    uint16_t sinit_max_instreams; /* the maximum number of inbound streams the
                                   application is prepared to support */
    uint16_t sinit_max_attempts;  /* how many attempts the SCTP endpoint should
                                   make at resending the INIT. This value 
                                   overrides the system SCTP
                                   'Max.Init.Retransmits' value. */
    uint16_t sinit_max_init_timeo;/* the largest Time-Out or RTO value (in
                                   milliseconds) to use in attempting an INIT.
                                   Normally the 'RTO.Max'is used to limit the
                                   doubling of the RTO upon timeout. For the
                                   INIT message this value MAY override 
                                   'RTO.Max'(60 seconds).*/
};

/*
 *===========================================================================
 *       IPSCTP sinfo_flags member of structure sctp_sndrcvinfo
 *===========================================================================
 * sinfo_flags: 16 bits (unsigned integer)
 * 
 * This field may contain any of the following flags and is composed of
 * a bitwise OR of these values.
 * 
 * recvmsg() flags:
 * SCTP_UNORDERED -  This flag is present when the message was sent non-
 *    ordered.
 * 
 * 
 * sendmsg() flags:
 * SCTP_UNORDERED -  This flag requests the un-ordered delivery of the
 *    message.  If this flag is clear the datagram is considered an
 *    ordered send.
 * 
 * SCTP_ADDR_OVER -  This flag, in the one-to-many style, requests the
 *    SCTP stack to override the primary destination address with the
 *    address found with the sendto/sendmsg call.
 * 
 * SCTP_ABORT -  Setting this flag causes the specified association to
 *    abort by sending an ABORT message to the peer (one-to-many style
 *    only).  The ABORT chunk will contain an error cause 'User
 *    Initiated Abort' with cause code 12.  The cause specific
 *    information of this error cause is provided in msg_iov.
 * 
 * SCTP_EOF -  Setting this flag invokes the SCTP graceful shutdown
 *    procedures on the specified association.  Graceful shutdown
 *    assures that all data enqueued by both endpoints is successfully
 *    transmitted before closing the association (one-to-many style
 *    only).
 * 
 * SCTP_SENDALL -  This flag, if set, will cause a one-to-many model
 *    socket to send the message to all associations that are currently
 *    established on this socket.  For the one-to-one socket, this flag
 *    has no effect.
 */
#define SCTP_UNORDERED              0x0001
#define SCTP_ADDR_OVER              0x0002
#define SCTP_ABORT                  0x0004
#define SCTP_EOF                    0x0008
#define SCTP_SENDALL                0x0010
#define SCTP_EOR                    0x0020

#define SCTP_DATA_FRAG_MASK    0x03
#define SCTP_DATA_MIDDLE_FRAG  0x00
#define SCTP_DATA_LAST_FRAG    0x01
#define SCTP_DATA_FIRST_FRAG   0x02
#define SCTP_DATA_NOT_FRAG     0x03
#define SCTP_DATA_UNORDERED    0x04

/*
 *===========================================================================
 *                  IPSCTP sctp sndrcvinfo parameters
 *===========================================================================
 * 5.2.2.  SCTP Header Information Structure (SCTP_SNDRCV)
 *
 * This cmsghdr structure specifies SCTP options for sendmsg() and
 * describes SCTP header information about a received message through
 * recvmsg().
 * 
 * cmsg_level    cmsg_type      cmsg_data[]
 * ------------  ------------   ----------------------
 * IPPROTO_SCTP  SCTP_SNDRCV    struct sctp_sndrcvinfo
 */
struct sctp_sndrcvinfo 
{
    uint16_t         sinfo_stream;     /* number of streams */
    uint16_t         sinfo_ssn;        /* stream sequence number */
    uint16_t         sinfo_flags;      /* flags for sendmsg() and recvmsg() */
    uint16_t         sinfo_pr_policy;  /*  */
    uint32_t         sinfo_ppid;       /* payload protocol id */
    uint32_t         sinfo_context;    /* context data for sendmsg() only */
    uint32_t         sinfo_pr_value;   /*  */
    uint32_t         sinfo_tsn;        /* transmission sequence number */
    uint32_t         sinfo_cumtsn;     /* cumulative transmission sequence number */
    sctp_assoc_t sinfo_assoc_id;   /* association id */
};

typedef struct sctp_sctp_sndrcvinfo_struct 
{
    uint16_t       sinfo_stream;     /* number of streams */
    uint16_t       sinfo_ssn;        /* stream sequence number */
    uint16_t       sinfo_flags;      /* flags for sendmsg() and recvmsg() */
    uint16_t       sinfo_pr_policy;  /*  */
    uint32_t       sinfo_ppid;       /* payload protocol id */
    uint32_t       sinfo_context;    /* context data for sendmsg() only */
    uint32_t       sinfo_pr_value;   /*  */
    uint32_t       sinfo_tsn;        /* transmission sequence number */
    uint32_t       sinfo_cumtsn;     /* cumulative transmission sequence number */
}
sctp_sctp_sndrcvinfo;

/*
 *===========================================================================
 *       IPSCTP serinfo_next_flags member of structure sctp_extrcvinfo
 *===========================================================================
 * serinfo_next_flags: 16 bit (unsigned integer)
 * 
 * This bitmask will hold one or more of the following values:
 * SCTP_NEXT_MSG_AVAIL -  This bit, when set to 1, indicates that next
 *    message information is available i.e.: next_stream, next_asocid,
 *    next_length and next_ppid fields all have valid values.  If this
 *    bit is set to 0, then these fields are not valid and should be
 *    ignored.
 * 
 * SCTP_NEXT_MSG_ISCOMPLETE -  This bit, when set, indicates that the
 *    next message is completely in the receive buffer.  The next_length
 *    field thus contains the entire message size.  If this flag is set
 *    to 0, then the next_length field only contains part of the message
 *    size since the message is still being received (it is being
 *    partially delivered).
 * 
 * SCTP_NEXT_MSG_IS_UNORDERED -  This bit, when set, indicates that the
 *    next message to be received was sent by the peer as unordered.  If
 *    this bit is not set (i.e the bit is 0) the next message to be read
 *    is an ordered message in the stream specified.
 * 
 * SCTP_NEXT_MSG_IS_NOTIFICATION -  This bit, when set, indicates that
 *    the next message to be received is not a message from the peer,
 *    but instead is a MSG_NOTIFICATION from the local SCTP stack.
 */
#define SCTP_NEXT_MSG_AVAIL              0x0001
#define SCTP_NEXT_MSG_ISCOMPLETE         0x0002
#define SCTP_NEXT_MSG_IS_UNORDERED       0x0004
#define SCTP_NEXT_MSG_IS_NOTIFICATION    0x0008

/*
 *===========================================================================
 *                  IPSCTP sctp parameters
 *===========================================================================
 * 5.2.3.  Extended SCTP Header Information Structure (SCTP_EXTRCV)
 *
 * This cmsghdr structure specifies SCTP options for SCTP header
 * information about a received message via recvmsg().  Note that this
 * structure is an extended version of SCTP_SNDRCV (see Section 5.2.2)
 * and will only be received if the user has set the socket option
 * SCTP_USE_EXT_RCVINFO to true in addition to any event subscription
 * needed to receive ancillary data.  Note that next message data is not
 * valid unless the current message is completely read, i.e. the MSG_EOR
 * is set, in other words if you have more data to read from the current
 * message then no next message information will be available.
 * 
 * cmsg_level    cmsg_type      cmsg_data[]
 * ------------  ------------   ----------------------
 * IPPROTO_SCTP  SCTP_EXTRCV    struct sctp_extrcvinfo
 */
struct sctp_extrcvinfo
{
    struct sctp_sndrcvinfo serinfo_sinfo;
    uint16_t                   serinfo_next_flags;   /* next message bitmask flags */
    uint16_t                   serinfo_next_stream;  /* next stream numbers */
    uint32_t                   serinfo_next_aid;     /* next association id to receive */
    uint32_t                   serinfo_next_length;  /* length of next message */
    uint32_t                   serinfo_next_ppid;    /* next message payload protocol id */
};

/*
 *===========================================================================
 *                  IPSCTP sctp  parameters
 *===========================================================================
 * 5.3.1.1.  SCTP_ASSOC_CHANGE
 *
 * Communication notifications inform the ULP that an SCTP association
 * has either begun or ended.  The identifier for a new association is
 * provided by this notification.
 */
struct sctp_assoc_change 
{
    uint16_t         sac_type;             /* SCTP_ASSOC_CHANGE */
    uint16_t         sac_flags;            /* unused */
    uint32_t         sac_length;           /* total length, including sn_header */
    uint16_t         sac_state;            /* state of the event */
    uint16_t         sac_error;            /* error condition */
    uint16_t         sac_outbound_streams; /* max outbound streams allowed */
    uint16_t         sac_inbound_streams;  /* max inbound streams allowed */
    sctp_assoc_t sac_assoc_id;         /* association id */
    uint8_t          sac_info[0];          /* variable chunk information */
};

/*
 *===========================================================================
 *                  IPSCTP sctp parameters
 *===========================================================================
 * sac_state: 16 bits (signed integer)
 * 
 * This field holds one of a number of values that communicate the event
 * that happened to the association.  They include:
 * 
 * Event Name Description
 *
 * ---------------- ---------------
 *
 * SCTP_COMM_UP -  A new association is now ready and data may be
 *    exchanged with this peer.
 * SCTP_COMM_LOST -  The association has failed.  The association is now
 *    in the closed state.  If SEND FAILED notifications are turned on,
 *    a SCTP_COMM_LOST is followed by a series of SCTP_SEND_FAILED
 *    events, one for each outstanding message.
 * SCTP_RESTART -  SCTP has detected that the peer has restarted.
 * SCTP_SHUTDOWN_COMP -  The association has gracefully closed.
 * SCTP_CANT_STR_ASSOC -  The association failed to setup.  If non
 *    blocking mode is set and data was sent (in the udp mode), a
 *    SCTP_CANT_STR_ASSOC is followed by a series of SCTP_SEND_FAILED
 *    events, one for each outstanding message.
 */
enum sctp_sac_state 
{
    SCTP_COMM_UP         = 1,
    SCTP_COMM_LOST       = 2,
    SCTP_RESTART         = 3,
    SCTP_SHUTDOWN_COMP   = 4,
    SCTP_CANT_STR_ASSOC  = 5,
    SCTP_SAC_STATE_MAX   = 6
};

/*
 *===========================================================================
 *                  IPSCTP sctp  parameters
 *===========================================================================
 * 5.3.1.2.  SCTP_PEER_ADDR_CHANGE
 *
 * When a destination address on a multi-homed peer encounters a change
 * an interface details event is sent.
 */
struct sctp_paddr_change
{
    uint16_t                     spc_type;     /* SCTP_PEER_ADDR_CHANGE */
    uint16_t                     spc_flags;    /* unused */
    uint32_t                     spc_length;   /* total length, including sn_header */
    struct sockaddr_storage spc_aaddr;    /* affected remove peer addr */
    uint32_t                     spc_state;    /* state of the event */
    uint32_t                     spc_error;    /* error condition */
    sctp_assoc_t             spc_assoc_id; /* association id */
};

/*
 *===========================================================================
 *                  IPSCTP sctp  parameters
 *===========================================================================
 * spc_state: 32 bits (signed integer)
 *
 * This field holds one of a number of values that communicate the event
 * that happened to the address.  They include:
 *
 * Event Name Description
 *
 * ---------------- ---------------
 *
 * SCTP_ADDR_AVAILABLE -  This address is now reachable.
 * SCTP_ADDR_UNREACHABLE -  The address specified can no longer be
 *    reached.  Any data sent to this address is rerouted to an
 *    alternate until this address becomes reachable.
 * SCTP_ADDR_REMOVED -  The address is no longer part of the
 *    association.
 * SCTP_ADDR_ADDED -  The address is now part of the association.
 * SCTP_ADDR_MADE_PRIM -  This address has now been made to be the
 *    primary destination address.
 * SCTP_ADDR_CONFIRMED -  This address has now been confirmed as a valid
 *    address.
 */
enum sctp_spc_state 
{
    SCTP_ADDR_AVAILABLE         = 1,
    SCTP_ADDR_UNREACHABLE       = 2,
    SCTP_ADDR_REMOVED           = 3,
    SCTP_ADDR_ADDED             = 4,
    SCTP_ADDR_MADE_PRIM         = 5,
    SCTP_ADDR_CONFIRMED         = 6,
    SCTP_SPC_STATE_MAX          = 7
};

/*
 *===========================================================================
 *                  IPSCTP sctp  parameters
 *===========================================================================
 * 5.3.1.3.  SCTP_REMOTE_ERROR
 * 
 * A remote peer may send an Operational Error message to its peer.
 * This message indicates a variety of error conditions on an
 * association.  The entire ERROR chunk as it appears on the wire is
 * included in a SCTP_REMOTE_ERROR event.  Please refer to the SCTP
 * specification [RFC4960] and any extensions for a list of possible
 * error formats.
 */
struct sctp_remote_error 
{
    uint16_t         sre_type;     /* SCTP_REMOTE_ERROR */
    uint16_t         sre_flags;    /* unused */
    uint32_t         sre_length;   /* total length, including sn_header */
    uint16_t         sre_error;    /* error condition */
    sctp_assoc_t sre_assoc_id; /* association id */
    uint8_t          sre_data[0];  /* ERROR chunk */
};

/*
 *===========================================================================
 *                  IPSCTP sctp  sctp_send_failed
 *===========================================================================
 * ssf_flags: 16 bits (unsigned integer)
 * 
 * The flag value will take one of the following values:
 * 
 * SCTP_DATA_UNSENT -  Indicates that the data was never put on the
 *    wire.
 * SCTP_DATA_SENT -  Indicates that the data was put on the wire.  Note
 *    that this does not necessarily mean that the data was (or was not)
 *    successfully delivered.
 */
#define SCTP_DATA_UNSENT              0x0001
#define SCTP_DATA_SENT                0x0002

/*
 *===========================================================================
 *                  IPSCTP sctp  parameters
 *===========================================================================
 * 5.3.1.4.  SCTP_SEND_FAILED
 * 
 * If SCTP cannot deliver a message it may return the message as a
 * notification.
 */
struct sctp_send_failed 
{
    uint16_t                   ssf_type;     /* SCTP_SEND_FAILED */
    uint16_t                   ssf_flags;    /* flags */
    uint32_t                   ssf_length;   /* total length, including sn_header */
    uint32_t                   ssf_error;    /* error condition */
    struct sctp_sndrcvinfo ssf_info;     /* undelivered msg send info */
    sctp_assoc_t           ssf_assoc_id; /* association id */
    uint8_t                    ssf_data[0];  /* the original undelivered message */
};


/*
 *===========================================================================
 *                  IPSCTP sctp  parameters
 *===========================================================================
 * 5.3.1.5.  SCTP_SHUTDOWN_EVENT
 * When a peer sends a SHUTDOWN, SCTP delivers this notification to
 * inform the application that it should cease sending data.
 */
struct sctp_shutdown_event 
{
    uint16_t         sse_type;      /* SCTP_SHUTDOWN_EVENT */
    uint16_t         sse_flags;     /* unused */
    uint32_t         sse_length;    /* total length, including sn_header */
    sctp_assoc_t sse_assoc_id;  /* association id */
};

/*
 *===========================================================================
 *                  IPSCTP sctp  parameters
 *===========================================================================
 * 5.3.1.6.  SCTP_ADAPTATION_INDICATION
 * 
 * When a peer sends a Adaptation Layer Indication parameter , SCTP
 * delivers this notification to inform the application that of the
 * peers requested adaptation layer.
 */
struct sctp_adaptation_event
{
    uint16_t         sai_type;           /* SCTP_ADAPTATION_INDICATION */
    uint16_t         sai_flags;          /* unused */
    uint32_t         sai_length;         /* total length, including sn_header */
    uint32_t         sai_adaptation_ind; /* bit array for adaptation parameter */
    sctp_assoc_t sai_assoc_id;       /* association id */
};

/*
 *===========================================================================
 *                  IPSCTP sctp  sctp_pdapi_event
 *===========================================================================
 * pdapi_indication: 32 bits (unsigned integer)
 * 
 * This field holds the indication being sent to the application
 * possible values include:
 * 
 * SCTP_PARTIAL_DELIVERY_ABORTED
 */
#define SCTP_PARTIAL_DELIVERY_ABORTED       0x0001

/*
 *===========================================================================
 *                  IPSCTP sctp  parameters
 *===========================================================================
 * 5.3.1.7.  SCTP_PARTIAL_DELIVERY_EVENT
 * 
 * When a receiver is engaged in a partial delivery of a message this
 * notification will be used to indicate various events.
 */
struct sctp_pdapi_event
{
    uint16_t         pdapi_type;        /* SCTP_PARTIAL_DELIVERY_EVENT */
    uint16_t         pdapi_flags;       /* unused */
    uint32_t         pdapi_length;      /* total length, including sn_header */
    uint32_t         pdapi_indication;  /* indication values */
    uint32_t         pdapi_stream;      /* partially delivered stream */
    uint32_t         pdapi_seq;         /* stream sequence number */
    sctp_assoc_t pdapi_assoc_id;    /* association id */
};

/*
 *===========================================================================
 *                  IPSCTP sctp  sctp_authkey_event
 *===========================================================================
 * auth_indication: 32 bits (unsigned integer)
 *
 * This field hold the error or indication being reported.  The
 * following values are currently defined:
 * SCTP_AUTH_NEWKEY -  this report indicates that a new key has been
 *    made active (used for the first time by the peer) and is now the
 *    active key.  The auth_keynumber field holds the user specified key
 *    number.
 */
#define SCTP_AUTH_NEWKEY              0x0001

/*
 *===========================================================================
 *                  IPSCTP sctp  parameters
 *===========================================================================
 * 5.3.1.8.  SCTP_AUTHENTICATION_EVENT
 * 
 * When a receiver is using authentication this message will provide
 * notifications regarding new keys being made active as well as errors.
 */
struct sctp_authkey_event
{
    uint16_t         auth_type;          /* SCTP_AUTHENTICATION_EVENT */
    uint16_t         auth_flags;         /* unused */
    uint32_t         auth_length;        /* total length, including sn_header */
    uint16_t         auth_keynumber;     /* keynumber for the effected key */
    uint16_t         auth_altkeynumber;  /* alternate keynumber */
    uint32_t         auth_indication;    /* error or indication being reported */
    sctp_assoc_t auth_assoc_id;      /* association id */
};

/*
 *===========================================================================
 *                  IPSCTP sctp  parameters
 *===========================================================================
 * 5.3.1.9.  SCTP_AUTHENTICATION_EVENT
 * 
 * When an association is set up and the peer does not support SCTP-AUTH
 * this notification is provided by the kernel to the user.
 */
struct sctp_no_auth_event
{
    uint16_t         no_auth_type;
    uint16_t         no_auth_flags;
    uint32_t         no_auth_length;
    sctp_assoc_t no_auth_assoc_id;
};

/*
 *===========================================================================
 *                  IPSCTP sctp  parameters
 *===========================================================================
 * 5.3.1.  SCTP Notification Structure
 * 
 * The notification structure is defined as the union of all
 * notification types.
 */
union sctp_notification {
    struct 
    {
        uint16_t sn_type;         /* Notification type. */
        uint16_t sn_flags;        /* notification-specific flags */
        uint32_t sn_length;       /* notification length, including sn_type,
                                   sn_flags, and sn_length fields */
    } sn_header;
    struct sctp_assoc_change     sn_assoc_change;
    struct sctp_paddr_change     sn_paddr_change;
    struct sctp_remote_error     sn_remote_error;
    struct sctp_send_failed      sn_send_failed;
    struct sctp_shutdown_event   sn_shutdown_event;
    struct sctp_adaptation_event sn_adaptation_event;
    struct sctp_pdapi_event      sn_pdapi_event;
    struct sctp_authkey_event    sn_auth_event;
    struct sctp_no_auth_event    sn_no_auth_event;
};

/*
 *===========================================================================
 *                  IPSCTP sctp  sctp_notification
 *===========================================================================
 * sn_type: 16 bits (unsigned integer)
 *
 * The following list describes the SCTP notification and event types
 * for the field sn_type.
 *
 * SCTP_ASSOC_CHANGE:  This tag indicates that an association has either
 *    been opened or closed.  Refer to Section 5.3.1.1 for details.
 * SCTP_PEER_ADDR_CHANGE:  This tag indicates that an address that is
 *    part of an existing association has experienced a change of state
 *    (e.g. a failure or return to service of the reachability of a
 *    endpoint via a specific transport address).  Please see
 *    Section 5.3.1.2 for data structure details.
 * SCTP_REMOTE_ERROR:  The attached error message is an Operational
 *    Error received from the remote peer.  It includes the complete TLV
 *    sent by the remote endpoint.  See Section 5.3.1.3 for the detailed
 *    format.
 * SCTP_SEND_FAILED:  The attached datagram could not be sent to the
 *    remote endpoint.  This structure includes the original
 *    SCTP_SNDRCVINFO that was used in sending this message i.e. this
 *    structure uses the sctp_sndrecvinfo per Section 5.3.1.4.
 * SCTP_SHUTDOWN_EVENT:  The peer has sent a SHUTDOWN.  No further data
 *    should be sent on this socket.
 * SCTP_ADAPTATION_INDICATION:  This notification holds the peers
 *    indicated adaptation layer.  Please see Section 5.3.1.6.
 * SCTP_PARTIAL_DELIVERY_EVENT:  This notification is used to tell a
 *    receiver that the partial delivery has been aborted.  This may
 *    indicate the association is about to be aborted.  Please see
 *    Section 5.3.1.7
 * SCTP_AUTHENTICATION_EVENT:  This notification is used to tell a
 *    receiver that either an error occurred on authentication, or a new
 *    key was made active.  Section 5.3.1.8
 * SCTP_NO_AUTHENTICATION_EVENT:  This notification is used to tell a
 *    receiver that the peer does not support SCTP-AUTH.
 *    Section 5.3.1.9
 *
 * All standard values for sn_type are greater than 2^15.  Values from
 * 2^15 and down are reserved.
 */
enum sctp_sn_type 
{
    SCTP_SN_TYPE_MIN              = (1<<15),
    SCTP_ASSOC_CHANGE             = (1<<15) + 1,
    SCTP_PEER_ADDR_CHANGE         = (1<<15) + 2,
    SCTP_REMOTE_ERROR             = (1<<15) + 3,
    SCTP_SEND_FAILED              = (1<<15) + 4,
    SCTP_SHUTDOWN_EVENT           = (1<<15) + 5,
    SCTP_ADAPTATION_INDICATION    = (1<<15) + 6,
    SCTP_PARTIAL_DELIVERY_EVENT   = (1<<15) + 7,
    SCTP_AUTHENTICATION_EVENT     = (1<<15) + 8,
    SCTP_NO_AUTHENTICATION_EVENT  = (1<<15) + 9
};

/*
 *===========================================================================
 *                  IPSCTP sctp  parameters
 *===========================================================================
 * 7.1.1.  Retransmission Timeout Parameters (SCTP_RTOINFO)
 * 
 * The protocol parameters used to initialize and bound retransmission
 * timeout (RTO) are tunable.  See [RFC4960] for more information on how
 * these parameters are used in RTO calculation.
 */
struct sctp_rtoinfo 
{
    sctp_assoc_t        srto_assoc_id;     /* association id */
    uint32_t                srto_initial;      /* initial RTO value */
    uint32_t                srto_max;          /* max RTO */
    uint32_t                srto_min;          /* min RTO */
};

typedef struct sctp_rtoinfo_struct 
{
    uint32_t                srto_initial;      /* initial RTO value */
    uint32_t                srto_max;          /* max RTO */
    uint32_t                srto_min;          /* min RTO */
}
sctp_sctp_rtoinfo;


/*
 *===========================================================================
 *                  IPSCTP sctp  parameters
 *===========================================================================
 * 7.1.2.  Association Parameters (SCTP_ASSOCINFO)
 * 
 * This option is used to both examine and set various association and
 * endpoint parameters.
 *
 * Note: When configuring the SCTP endpoint, the user should avoid
 * having the value of 'Association.Max.Retrans' larger than the
 * summation of the 'Path.Max.Retrans' of all the destination addresses
 * for the remote endpoint.  Otherwise, all the destination addresses
 * may become inactive while the endpoint still considers the peer
 * endpoint reachable.
 */
struct sctp_assocparams 
{
    sctp_assoc_t  sasoc_assoc_id;                  /* association id */
    uint16_t          sasoc_asocmaxrxt;                /* max retransmission attempts */
    uint16_t          sasoc_number_peer_destinations;  /* num of peer's dest addr */
    uint32_t          sasoc_peer_rwnd;                 /* current peers rwnd */
    uint32_t          sasoc_local_rwnd;                /* last reported rwnd  */
    uint32_t          sasoc_cookie_life;               /* cookie life value */
};

typedef struct sctp_sctp_assocparams_struct 
{
    uint16_t          sasoc_asocmaxrxt;  /* max retransmission attempts */
    uint32_t          sasoc_cookie_life; /* cookie life value */
}
sctp_sctp_assocparams;

/*
 *===========================================================================
 *                  IPSCTP sctp  parameters
 *===========================================================================
 * 7.1.9.  Set Peer Primary Address (SCTP_SET_PEER_PRIMARY_ADDR)
 * 
 * Requests that the peer mark the enclosed address as the association
 * primary.  The enclosed address must be one of the association's
 * locally bound addresses.
 */
struct sctp_setpeerprim
{
    sctp_assoc_t             sspp_assoc_id; /* association id */
    struct sockaddr_storage sspp_addr;     /* peer address to set as primary */
};

/*
 *===========================================================================
 *                  IPSCTP sctp  parameters
 *===========================================================================
 * 7.1.10.  Set Primary Address (SCTP_PRIMARY_ADDR)
 * 
 * Requests that the local SCTP stack use the enclosed peer address as
 * the association primary.  The enclosed address must be one of the
 * association peer's addresses.
 */
struct sctp_setprim 
{
    sctp_assoc_t             ssp_assoc_id; /* association id */
    struct sockaddr_storage ssp_addr;     /* address to set as primary */
};

/*
 *===========================================================================
 *                  IPSCTP sctp  parameters
 *===========================================================================
 * 7.1.11.  Set Adaptation Layer Indicator (SCTP_ADAPTATION_LAYER)
 * 
 * Requests that the local endpoint set the specified Adaptation Layer
 * Indication parameter for all future INIT and INIT-ACK exchanges.
 */
struct sctp_setadaptation 
{
    uint32_t   ssb_adaptation_ind; /* adaptation layer indicator */
};

/*
 *===========================================================================
 *                  IPSCTP sctp  sctp_paddrparams
 *===========================================================================
 * spp_flags -  These flags are used to control various features on an
 * association.  The flag field is a bit mask which may contain zero
 * or more of the following options:
 *
 * SPP_HB_ENABLE -  Enable heartbeats on the specified address.  Note
 *    that if the address field is empty all addresses for the
 *    association have heartbeats enabled upon them.
 * SPP_HB_DISABLE -  Disable heartbeats on the specified address.
 *    Note that if the address field is empty all addresses for the
 *    association will have their heartbeats disabled.  Note also
 *    that SPP_HB_ENABLE and SPP_HB_DISABLE are mutually exclusive,
 *    only one of these two should be specified.  Enabling both
 *    fields will have undetermined results.
 * SPP_HB_DEMAND -  Request a user initiated heartbeat to be made
 *    immediately.
 * SPP_HB_TIME_IS_ZERO -  Specify's that the time for heartbeat delay
 *    is to be set to the value of 0 milliseconds.
 * SPP_PMTUD_ENABLE -  This field will enable PMTU discovery upon the
 *    specified address.  Note that if the address field is empty
 *    then all addresses on the association are effected.
 * SPP_PMTUD_DISABLE -  This field will disable PMTU discovery upon
 *    the specified address.  Note that if the address field is empty
 *    then all addresses on the association are effected.  Not also
 *    that SPP_PMTUD_ENABLE and SPP_PMTUD_DISABLE are mutually
 *    exclusive.  Enabling both will have undetermined results.
 * SPP_IPV6_FLOWLABEL -  Setting this flag enables setting of the
 *    IPV6 flowlabel value associated with either the association or
 *    the specific address.  If the address field is filled in, then
 *    the specific destination address has this value set upon it.
 *    If the association is specified, but not the address, then the
 *    flowlabel value is set for any future destination addresses
 *    that may be added.  The value is obtained in the
 *    spp_ipv6_flowlabel field.
 *    Upon retrieval, this flag will be set to indicate that the
 *    spp_ipv6_flowlabel field has a valid value returned.  If a
 *    specific destination addresses is set (in the spp_address
 *    field) when called then the value returned is that of the
 *    address.  If just an association is specified (and no address)
 *    then the association default flowlabel is returned.  If neither
 *    an association nor an destination is specified, then the
 *    sockets default flowlabel is returned.  For non IPv6 sockets,
 *    then this flag will be left cleared.
 * SPP_IPV4_TOS -  Setting this flag enables setting of the IPV4 tos
 *    value associated with either the association or specific
 *    address.  If the address field is filled in, then the specific
 *    destination address has this value set upon it.  If the
 *    association is specified, but not the address, then the tos
 *    value is set for any future destination addresses that may be
 *    added.  The value is obtained in the spp_ipv4_tos field.
 * 
 *    Upon retrieval, this flag will be set to indicate that the
 *    spp_ipv4_tos field has a valid value returned.  If a specific
 *    destination addresses is set when called (in the spp_address
 *    field) then that specific destination addresses tos value is
 *    returned.  If just an association is specified then the
 *    association default tos is returned.  If neither an association
 *    nor an destination is specified, then the sockets default tos
 *    is returned.  For non IPv4 sockets, then this flag will be left
 *    cleared.
 */
#define IPSPP_HB_ENABLE             0x00000001
#define IPSPP_HB_DISABLE            0x00000002
#define IPSPP_HB_DEMAND             0x00000004
#define IPSPP_PMTUD_ENABLE          0x00000008
#define IPSPP_PMTUD_DISABLE         0x00000010
#define IPSPP_HB_TIME_IS_ZERO       0x00000020
#define IPSPP_IPV6_FLOWLABEL        0x00000040
#define IPSPP_IPV4_TOS              0x00000080

#define IPSPP_HB       (IPSPP_HB_ENABLE | IPSPP_HB_DISABLE)
#define IPSPP_PMTUD    (IPSPP_PMTUD_ENABLE | IPSPP_PMTUD_DISABLE)

/*
 *===========================================================================
 *                  IPSCTP sctp  parameters
 *===========================================================================
 * 7.1.13.  Peer Address Parameters (SCTP_PEER_ADDR_PARAMS)
 * 
 * Applications can enable or disable heartbeats for any peer address of
 * an association, modify an address's heartbeat interval, force a
 * heartbeat to be sent immediately, and adjust the address's maximum
 * number of retransmissions sent before an address is considered
 * unreachable.
 */
struct sctp_paddrparams 
{
    sctp_assoc_t             spp_assoc_id;         /* association id */
    struct sockaddr_storage spp_address;          /* specifies address of interest */
    uint32_t                     spp_hbinterval;       /* heartbeat interval */
    uint16_t                     spp_pathmaxrxt;       /* max retransmissions */
    uint32_t                     spp_pathmtu;          /* address path mtu */
    uint32_t                     spp_flags;            /* control flags */
    uint32_t                     spp_ipv6_flowlabel;   /* IPv6 flow label */
    uint8_t                      spp_ipv4_tos;         /* IPv4 TOS */
};
typedef struct sctp_sctp_paddrparams_struct 
{
    uint32_t                  spp_hbinterval;       /* heartbeat interval */
    uint16_t                  spp_pathmaxrxt;       /* max retransmissions */
    uint32_t                  spp_pathmtu;          /* address path mtu */
    uint32_t                  spp_flags;            /* control flags */
    uint32_t                  spp_ipv6_flowlabel;   /* IPv6 flow label */
    uint8_t                   spp_ipv4_tos;         /* IPv4 TOS */
}
sctp_sctp_paddrparams;


/*
 *===========================================================================
 *                  IPSCTP sctp  parameters
 *===========================================================================
 * 7.1.17.  Get or set the maximum fragmentation size (SCTP_MAXSEG)
 * 
 * This option will get or set the maximum size to put in any outgoing
 * SCTP DATA chunk.  If a message is larger than this size it will be
 * fragmented by SCTP into the specified size.  Note that the underlying
 * SCTP implementation may fragment into smaller sized chunks when the
 * PMTU of the underlying association is smaller than the value set by
 * the user.  The default value for this option is '0' which indicates
 * the user is NOT limiting fragmentation and only the PMTU will effect
 * SCTP's choice of DATA chunk size.  Note also that values set larger
 * than the maximum size of an IP datagram will effectively let SCTP
 * control fragmentation (i.e. the same as setting this option to 0).
 *
 * 7.1.28.  Set or Get the maximum burst (SCTP_MAX_BURST)
 * 
 * This option will allow a user to change the maximum burst of packets
 * that can be emitted by this association.  Note that the default value
 * is 4, and some implementations may restrict this setting so that it
 * can only be lowered.
 *
 * 7.1.29.  Set or Get the default context (SCTP_CONTEXT)
 * 
 * The context field in the sctp_sndrcvinfo structure is normally only
 * used when a failed message is retrieved holding the value that was
 * sent down on the actual send call.  This option allows the setting of
 * a default context on an association basis that will be received on
 * reading messages from the peer.  This is especially helpful in the
 * one-2-many model for an application to keep some reference to an
 * internal state machine that is processing messages on the
 * association.  Note that the setting of this value only effects
 * received messages from the peer and does not effect the value that is
 * saved with outbound messages.
 */
struct sctp_assoc_value 
{
    sctp_assoc_t          assoc_id;       /* association id */
    uint32_t                  assoc_value;    /* maximum size in bytes */
};

/*
 *===========================================================================
 *                  IPSCTP sctp  parameters
 *===========================================================================
 * 7.1.18.  Add a chunk that must be authenticated (SCTP_AUTH_CHUNK)
 * 
 * This set option adds a chunk type that the user is requesting to be
 * received only in an authenticated way.  Changes to the list of chunks
 * will only effect future associations on the socket.
 */
struct sctp_authchunk 
{
    uint8_t    sauth_chunk;  /* chunk type to be authenticated */
};

/*
 *===========================================================================
 *                  IPSCTP sctp  sctp_hmacalgo
 *===========================================================================
 * shmac_idents -  This parameter contains an array of HMAC Identifiers
 *    that the local endpoint is requesting the peer to use, in priority
 *    order.  The following identifiers are valid:
 *
 *    1) SCTP_AUTH_HMAC_ID_SHA1
 *    2) SCTP_AUTH_HMAC_ID_SHA256 (optional)
 *    3) SCTP_AUTH_HMAC_ID_SHA224 (optional)
 *    4) SCTP_AUTH_HMAC_ID_SHA384 (optional)
 *    4) SCTP_AUTH_HMAC_ID_SHA512 (optional)
 */
#define SCTP_AUTH_HMAC_ID_SHA1          0x0001
#define SCTP_AUTH_HMAC_ID_SHA256        0x0002  /* optional */
#define SCTP_AUTH_HMAC_ID_SHA224        0x0003  /* optional */
#define SCTP_AUTH_HMAC_ID_SHA384        0x0004  /* optional */
#define SCTP_AUTH_HMAC_ID_SHA512        0x0005  /* optional */

/*
 *===========================================================================
 *                  IPSCTP sctp  parameters
 *===========================================================================
 * 7.1.19.  Get or set the list of supported HMAC Identifiers(SCTP_HMAC_IDENT)
 * 
 * This option gets or sets the list of HMAC algorithms that the local
 * endpoint requires the peer to use.
 */
struct sctp_hmacalgo 
{
    uint32_t                shmac_number_of_idents; /* number of HMAC Identifiers */
    uint16_t                shmac_idents[0];        /* an array of HMAC Identifiers */
};

/*
 *===========================================================================
 *                  IPSCTP sctp  parameters
 *===========================================================================
 * 7.1.20.  Set a shared key (SCTP_AUTH_KEY)
 * 
 * This option will set a shared secret key which is used to build an
 * association shared key.
 */
struct sctp_authkey 
{
    sctp_assoc_t        sca_assoc_id;   /* association id */
    uint16_t                sca_keynumber;  /* shared key identifier */
    uint16_t                sca_keylength;  /* shared key length */
    uint8_t                 sca_key[0];     /* array of bytes for shared secret key */
};

/*
 *===========================================================================
 *                  IPSCTP sctp  parameters
 *===========================================================================
 * 7.1.21.  Get or set the active shared key (SCTP_AUTH_ACTIVE_KEY)
 * 
 * This option will get or set the active shared key to be used to build
 * the association shared key.
 *
 * 7.1.22.  Delete a shared key (SCTP_AUTH_DELETE_KEY)
 * 
 * This set option will delete a shared secret key from use.
 */
struct sctp_authkeyid 
{
    sctp_assoc_t        scact_assoc_id;     /* association id */
    uint16_t                scact_keynumber;    /* active shared key identifier */
};

/*
 *===========================================================================
 *                  IPSCTP sctp  parameters
 *===========================================================================
 * 7.1.23.  Get or set delayed ack timer (SCTP_DELAYED_SACK)
 * 
 * This option will effect the way delayed acks are performed.  This
 * option allows you to get or set the delayed ack time, in
 * milliseconds.  It also allows changing the delayed ack frequency.
 * Changing the frequency to 1 disables the delayed sack algorithm.  If
 * the assoc_id is 0, then this sets or gets the endpoints default
 * values.  If the assoc_id field is non-zero, then the set or get
 * effects the specified association for the one to many model (the
 * assoc_id field is ignored by the one to one model).  Note that if
 * sack_delay or sack_freq are 0 when setting this option, then the
 * current values will remain unchanged.
 */
struct sctp_sack_info 
{
    sctp_assoc_t        sack_assoc_id;  /* association id */
    uint32_t                sack_delay;     /* delayed ACK timer in milliseconds */
    uint32_t                sack_freq;      /* number of packets to be received */
};

typedef struct sctp_sctp_sack_info_struct 
{
    uint32_t                sack_delay;     /* delayed ACK timer in milliseconds */
    uint32_t                sack_freq;      /* number of packets to be received */
}
sctp_sctp_sack_info;


/*
 *===========================================================================
 *                  IPSCTP sctp  parameters
 *===========================================================================
 * 7.2.2.  Peer Address Information (SCTP_GET_PEER_ADDR_INFO)
 * 
 * Applications can retrieve information about a specific peer address
 * of an association, including its reachability state, congestion
 * window, and retransmission timer values.  This information is read-
 * only.  The following structure is used to access this information:
 */
struct sctp_paddrinfo
{
    sctp_assoc_t             spinfo_assoc_id;   /* association id */
    struct sockaddr_storage spinfo_address;    /* peer address of interest */
    int32_t                     spinfo_state;      /* the peer addresses's state */
    uint32_t                     spinfo_cwnd;       /* current congestion window */
    uint32_t                     spinfo_srtt;       /* current smoothed round-trip time in ms */
    uint32_t                     spinfo_rto;        /* current retransmission timeout in ms */
    uint32_t                     spinfo_mtu;        /* current P-MTU of this address */
};

/*
 *===========================================================================
 *                  IPSCTP sctp  parameters
 *===========================================================================
 * 7.2.1.  Association Status (SCTP_STATUS)
 * 
 * Applications can retrieve current status information about an
 * association, including association state, peer receiver window size,
 * number of unacked data chunks, and number of data chunks pending
 * receipt.  This information is read-only.  The following structure is
 * used to access this information:
 */
struct sctp_status
{
    sctp_assoc_t          sstat_assoc_id;             /* association id */
    int32_t                  sstat_state;                /* the association's current state */
    uint32_t                  sstat_rwnd;                 /* current receiver window size */
    uint16_t                  sstat_unackdata;            /* number of unacked data chunks */
    uint16_t                  sstat_penddata;             /* number of data chunks pending receipt */
    uint16_t                  sstat_instrms;              /* number of inbound streams */
    uint16_t                  sstat_outstrms;             /* number of endpoint outbound streams */
    uint32_t                  sstat_fragmentation_point;  /* SCTP fragmentation point */
    struct sctp_paddrinfo sstat_primary;              /* current primary peer address */
};

/*
 *===========================================================================
 *                  IPSCTP sctp  parameters
 *===========================================================================
 * 7.2.3.  Get the list of chunks the peer requires to be authenticated
 *         (SCTP_PEER_AUTH_CHUNKS)
 * 
 * This option gets a list of chunks for a specified association that
 * the peer requires to be received authenticated only.
 *
 * 7.2.4.  Get the list of chunks the local endpoint requires to be
 *         authenticated (SCTP_LOCAL_AUTH_CHUNKS)
 * 
 * This option gets a list of chunks for a specified association that
 * the local endpoint requires to be received authenticated only.
 */
struct sctp_authchunks
{
    sctp_assoc_t gauth_assoc_id;         /* association id */
    uint32_t         gauth_number_of_chunks; /*  */
    uint8_t          gauth_chunks[0];        /* array of chunks to be authenticated */
};

/*
 *===========================================================================
 *                  IPSCTP sctp  parameters
 *===========================================================================
 * 7.2.6.  Get the current identifiers of associations
 *         (SCTP_GET_ASSOC_ID_LIST)
 * 
 * This option gets the current list of SCTP association identifiers of
 * the SCTP associations handled by a one-to-many style socket.  The
 * option value has the structure
 */
struct sctp_assoc_ids
{
    uint32_t         gaids_number_of_ids;  
    sctp_assoc_t gaids_assoc_id[0];    /* buffer to hold all association ids */
};

/*
 *===========================================================================
 *                  IPSCTP sctp  parameters
 *===========================================================================
 * 7.3.  Ancillary Data and Notification Interest Options
 * 
 * Applications can receive per-message ancillary information and
 * notifications of certain SCTP events with recvmsg().
 * 
 * The following optional information is available to the application:
 * 
 * 1.  SCTP_SNDRCV (sctp_data_io_event): Per-message information (i.e.
 *     stream number, TSN, SSN, etc. described in Section 5.2.2)
 * 2.  SCTP_ASSOC_CHANGE (sctp_association_event): (described in
 *     Section 5.3.1.1)
 * 3.  SCTP_PEER_ADDR_CHANGE (sctp_address_event): (described in
 *     Section 5.3.1.2)
 * 4.  SCTP_SEND_FAILED (sctp_send_failure_event): (described in
 *     Section 5.3.1.4)
 * 5.  SCTP_REMOTE_ERROR (sctp_peer_error_event): (described in
 *     Section 5.3.1.3)
 * 6.  SCTP_SHUTDOWN_EVENT (sctp_shtudown_event): (described in
 *     Section 5.3.1.5)
 * 7.  SCTP_PARTIAL_DELIVERY_EVENT (sctp_partial_delivery_event):
 *     (described in Section 5.3.1.7)
 * 8.  SCTP_ADAPTATION_INDICATION (sctp_adaptation_layer_event):
 *     (described in Section 5.3.1.6)
 * 9.  SCTP_AUTHENTICATION_INDICATION (sctp_authentication_event):
 *     (described in Section 5.3.1.8)
 * 
 * To receive any ancillary data or notifications, first the application
 * registers it's interest by calling the SCTP_EVENTS setsockopt() with
 * the following structure.
 */
struct sctp_event_subscribe
{
    uint8_t sctp_data_io_event;          /* 1 for receive SCTP_SNDRCV 
                                          information on a per message basis. */
    uint8_t sctp_association_event;      /* 1 for receive association 
                                          event notifications. */
    uint8_t sctp_address_event;          /* 1 for receive address event 
                                          notifications. */
    uint8_t sctp_send_failure_event;     /* 1 for receive send failure 
                                          event notifications. */
    uint8_t sctp_peer_error_event;       /* 1 for receive peer error event 
                                          notifications. */
    uint8_t sctp_shutdown_event;         /* 1 for receive shutdown event 
                                          notifications. */
    uint8_t sctp_partial_delivery_event; /* 1 for receive partial delivery 
                                          notifications. */
    uint8_t sctp_adaptation_layer_event; /* 1 for receive adaption layer 
                                          notifications. */
    uint8_t sctp_authentication_event;   /* 1 for receive authentication 
                                          layer notifications. */
};

/* for get local and peer address */
struct sctp_getaddrs 
{
    sctp_assoc_t        sget_assoc_id;
    struct sockaddr    sget_addrs[1];
};
struct sctp_peeloff 
{
    sctp_assoc_t          assoc_id;       /* association id */
    int                   fd;             /* socket descriptor */
    void                 *ret;
};

#define IPSOL_SCTP	132

/*===========================================================================
 *                  IPSCTP sctp  parameters
 *===========================================================================
 * 8.1.20.  Get or Set Fragmented Interleave (SCTP_FRAGMENT_INTERLEAVE)
 * 
 *    Fragmented interleave controls how the presentation of messages
 *    occurs for the message receiver.  There are three levels of fragment
 *    interleave defined.  Two of the levels effect the one-to-one model,
 *    while the one-to-many model is effected by all three levels.
 * 
 *    This option takes an integer value.  It can be set to a value of 0, 1
 *    or 2.  Attempting to set this level to other values will return an
 *    error.
 * 
 *    Setting the three levels provides the following receiver
 *    interactions:
 * 
 *    level 0:  Prevents the interleaving of any messages.  This means that
 *       when a partial delivery begins, no other messages will be received
 *       except the message being partially delivered.  If another message
 *       arrives on a different stream (or association) that could be
 *       delivered, it will be blocked waiting for the user to read all of
 *       the partially delivered message.
 *    level 1:  Allows interleaving of messages that are from different
 *       associations.  For the one-to-one model, level 0 and level 1 thus
 *       have the same meaning since a one-to-one socket always receives
 *       messages from the same association.  Note that setting the one-to-
 *       many model to this level may cause multiple partial delivers from
 *       different associations but for any given association, only one
 *       message will be delivered until all parts of a message have been
 *       delivered.  This means that one large message, being read with an
 *       association identification of "X", will block other messages from
 *       association "X" from being delivered.
 *    level 2:  Allows complete interleaving of messages.  This level
 *       requires that the sender carefully observe not only the peer
 *       association identification (or address) but also must pay careful
 *       attention to the stream number.  With this option enabled a
 *       partially delivered message may begin being delivered for
 *       association "X" stream "Y" and the next subsequent receive may
 *       return a message from association "X" stream "Z".  Note that no
 *       other messages would be delivered for association "X" stream "Y"
 *       until all of stream "Y"'s partially delivered message was read.
 *       Note that this option also effects the one-to-one model.  Also
 *       note that for the one-to-many model not only may another streams
 *       message from the same association be delivered from the next
 *       receive, some other associations message may be delivered upon the
 *       next receive.
 * 
 *    An implementation should default the one-to-many model to level 1.
 *    The reason for this is that otherwise it is possible that a peer
 *    could begin sending a partial message and thus block all other peers
 *    from sending data.  However a setting of level 2 requires the
 *    application to not only be aware of the association (via the
 *    association id or peers address) but also the stream number.  The
 *    stream number is NOT present unless the user has subscribed to the
 *    sctp_data_io_events (see Section 8.4).  This is also why we recommend
 *    that the one-to-one model be defaulted to level 0 (level 1 for the
 *    one-to-one model has no effect).  Note that an implementation should
 *    return an error if a application attempts to set the level to 2 and
 *    has NOT subscribed to the sctp_data_io_events.
 */
#define SCTP_FRAG_LEVEL_0        0x0000
#define SCTP_FRAG_LEVEL_1        0x0001
#define SCTP_FRAG_LEVEL_2        0x0002

#ifndef SOL_SCTP
#define SOL_SCTP	 132
#endif
#ifndef IPPROTO_SCTP
#define IPPROTO_SCTP 132
#endif

int
sctp_bindx(int fd,
           struct sockaddr *addrs,
           int addrcnt,
           int flags);

int
sctp_connectx(int fd,
              struct sockaddr *addrs,
              int addrcnt,
              sctp_assoc_t *id);

ssize_t
sctp_send(int fd,
          const void *pbuf,
          size_t len,
          const struct sctp_sndrcvinfo *sinfo,
          int flags);

ssize_t
sctp_sendx(int fd,
           const void *msg,
           size_t len,
           struct sockaddr *addrs,
           int addrcnt,
           struct sctp_sndrcvinfo *sinfo,
           int flags);

ssize_t
sctp_sendmsg(int fd,
             const void *pbuf,
             size_t len,
             const struct sockaddr *to,
             socklen_t tolen,
             uint32_t ppid,
             uint32_t flags,
             uint32_t stream_no,
             uint32_t pr_value,
             uint32_t context);

ssize_t
sctp_recvmsg(int fd,
             void *pbuf,
             size_t len,
             struct sockaddr *from,
             socklen_t *fromlen,
             struct sctp_sndrcvinfo *sinfo,
             int *msg_flags);

int
sctp_getaddrlen(int domain);

int
sctp_getpaddrs(int fd,
               sctp_assoc_t id,
               struct sockaddr **addrs);

void
sctp_freepaddrs(struct sockaddr *addrs);

int
sctp_getladdrs(int fd,
               sctp_assoc_t id,
               struct sockaddr **addrs);

void
sctp_freeladdrs(struct sockaddr *addrs);

int
sctp_opt_info(int fd,
              sctp_assoc_t id,
              int optname,
              void *optval,
              socklen_t  *optlen);
int sctp_peeloff
    (
    int          sd,              /* socket descriptor */
    sctp_assoc_t assoc_id         /* association identifier */
    );

/*
 ****************************************************************************
 * 6                 PUBLIC FUNCTIONS
 ****************************************************************************
 */


#ifdef __cplusplus
}
#endif

#endif /* SCTP_SOCKET_H */
