/*
 * Copyright (c) 2006-2013 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
 *===========================================================================
 *                    Definitions
 *===========================================================================
 */

#define MIPC_AUTOMATIC_NODE      (127)

#define MIPC_MGMT_NODE             (0)
#define MIPC_CNAE_NODE             (1)

#define MIPC_GET_SHARED_DATA_REQ   (0)
#define MIPC_GET_SHARED_DATA_RSP   (1)

/* Control messages */
#define FW_MSG_CONTROL_BASE        (48)    /* RIME: the value must be larger than the largest value HW may write, i.e. >35 */

#define FW_MSG_DROP_PKT            (FW_MSG_CONTROL_BASE + 1)
#define FW_MSG_HW_TICK             (FW_MSG_CONTROL_BASE + 2)
#define FW_MSG_TICK                (FW_MSG_CONTROL_BASE + 3)

#define FW_MSG_MIPC_POW_BASE       (FW_MSG_CONTROL_BASE + 4)

#define FW_MSG_MIPC_POW            (FW_MSG_MIPC_POW_BASE + 1)
#define FW_MSG_TRIGGER_PIPE_READ   (FW_MSG_MIPC_POW_BASE + 2)
#define FW_MSG_GET_SHARED_DATA     (FW_MSG_MIPC_POW_BASE + 3)
#define FW_MSG_NETLINK             (FW_MSG_MIPC_POW_BASE + 4)
#define FW_MSG_CMD                 (FW_MSG_MIPC_POW_BASE + 5)
#define FW_MSG_EVENT               (FW_MSG_MIPC_POW_BASE + 6)
#define FW_MSG_DEBUG_DATA          (FW_MSG_MIPC_POW_BASE + 7)
#define FW_MSG_GET_SHARED_DATA_ACK (FW_MSG_MIPC_POW_BASE + 8)
#define FW_MSG_LOG                 (FW_MSG_MIPC_POW_BASE + 9)


#define FW_EVENT_BASE            (1)
#define FW_EVENT_LINK_UP         (FW_EVENT_BASE + 1)
#define FW_EVENT_LINK_DOWN       (FW_EVENT_BASE + 2)

/* MIPC */
#define MIPC_MAXSOCKETS           255

#define MIPC_CMD_UDATA              0 /* Unreliable data, i.e. MIPC_SOCK_DGRAM */
#define MIPC_CMD_RDATA              1 /* Reliable data type 0 */
#define MIPC_CMD_RDATA_1            2 /* Reliable data type 1 */
#define MIPC_CMD_CONNECT_REQ        5 /* Connection request
                                         MIPC_SOCK_[STREAM|SEQPACKET] */
#define MIPC_CMD_CONNECT_ACK        6 /* Connection accepted */
#define MIPC_CMD_CONNECT_NAK        7 /* Connection rejected */
#define MIPC_CMD_DISCONNECT_REQ     8 /* Disconnect a connected
                                         socket */
#define MIPC_CMD_DISCONNECT_ACK     9 /* Disconnect accepted */
#define MIPC_CMD_START_UP          10 /* Start up */
#define MIPC_CMD_TICK              11 /* Tick */
#define MIPC_CMD_RIME              12 /* rime command */
#define MIPC_NCMDS                 13

/*
 *===========================================================================
 *                    Types
 *===========================================================================
 */

enum {
    NAE_PING,
    NAE_ENABLE,
    NAE_DISABLE,
    NAE_EXTENDED,
    NAE_TOPPLE,
    NAE_UTIL,
    NAE_LAST
};

/* Asyncronous event reported by NAE */
typedef struct mipc_pow_event_s
{
    Ip_u16 fw_msg;
    Ip_u16 event;
    Ip_u32 ifindex;

} mipc_pow_event_t;


/*
 *===========================================================================
 *                    Prototypes
 *===========================================================================
 */

IP_EXTERN void ipcom_mipc_start_up(void);
IP_EXTERN void ipcom_mipc_check_port_status(void);
IP_EXTERN void ipcom_mipc_nae_aux_message(int nae, void *msg, int msg_len);
IP_EXTERN void ipcom_mipc_pending_work(void);

/*
 *===========================================================================
 * End of file
 *===========================================================================
 */
