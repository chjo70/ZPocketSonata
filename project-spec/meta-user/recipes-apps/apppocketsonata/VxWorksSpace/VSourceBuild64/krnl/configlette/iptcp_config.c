/*
 * Copyright (c) 2006-2013, 2015-2016 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
06jun16,rjq  Port TSR defect fix forward from vxworks6.9 into vx7. (F6988)
15dec15,h_x  TCP delay ack time configurable, US71092
07jan15,ljl  Add TCP_USE_RFC6528_SECURE_ISN parameter,V7NET-499
*/

/*
 ****************************************************************************
 * 1                    DESCRIPTION
 ****************************************************************************
 * User IPTCP configuration file.
 */

/*
 ****************************************************************************
 * 2                    CONFIGURATION
 ****************************************************************************
 */

#include "iptcp_config.h"

#include <ipcom_cstyle.h>
#include <ipcom_err.h>
#include <ipcom_sysvar.h>


/*
 ****************************************************************************
 * 3                    INCLUDE FILES
 ****************************************************************************
 */

/*
 ****************************************************************************
 * 4                    DEFINES
 ****************************************************************************
 */
#ifndef TCP_CONN_TIMEOUT
#define TCP_CONN_TIMEOUT 300
#endif
#ifndef TCP_MAX_RETRANSMITS
#define TCP_MAX_RETRANSMITS 10
#endif
#ifndef TCP_MSL
#define TCP_MSL 30
#endif
#ifndef TCP_WUPW
#define TCP_WUPW 300
#endif
#ifndef TCP_LAND_ATTACK_PROTECTION
#define TCP_LAND_ATTACK_PROTECTION 1
#endif
#ifndef TCP_ALLOW_ZERO_WINDOW
#define TCP_ALLOW_ZERO_WINDOW 0
#endif
#ifndef TCP_ALLOW_TINY_WINDOW
#define TCP_ALLOW_TINY_WINDOW 1
#endif
#ifndef TCP_MAX_MSS
#define TCP_MAX_MSS 0
#endif
#ifndef TCP_USE_TIMESTAMP
#define TCP_USE_TIMESTAMP 1
#endif
#ifndef TCP_ALLOW_SACK
#define TCP_ALLOW_SACK 1
#endif
#ifndef TCP_USE_RFC1122_URGENT_DATA
#define TCP_USE_RFC1122_URGENT_DATA 0
#endif
#ifndef TCP_SEGMENT_MULTIPLIER
#define TCP_SEGMENT_MULTIPLIER 2
#endif
#ifndef TCP_PERSIST_TMO
#define TCP_PERSIST_TMO 0
#endif
#ifndef TCP_CLAMP_MSS
#define TCP_CLAMP_MSS 0
#endif
#ifndef TCP_DEFAULT_BACKLOG_SIZE
#define TCP_DEFAULT_BACKLOG_SIZE 5
#endif
#ifndef TCP_KEEP_CNT
#define TCP_KEEP_CNT 10
#endif
#ifndef TCP_KEEP_INTVL
#define TCP_KEEP_INTVL 75
#endif
#ifndef TCP_KEEP_IDLE
#define TCP_KEEP_IDLE 7200
#endif
#ifndef IPTCP_MAX_RETRAMSMITS_IN_TRANSIENT
#define IPTCP_MAX_RETRAMSMITS_IN_TRANSIENT 2
#endif
#ifndef IPTCP_MAX_TRANSIENT
#define IPTCP_MAX_TRANSIENT 20
#endif
#ifndef IPTCP_TRANSIENT_THRESH
#define IPTCP_TRANSIENT_THRESH 5
#endif
#ifndef TCP_USE_RFC6528_SECURE_ISN
#define TCP_USE_RFC6528_SECURE_ISN 1
#endif
#ifndef TCP_DELAY_ACK_TIME
#define TCP_DELAY_ACK_TIME 200
#endif
#ifndef TCP_IMMEDIATE_ACK_FOR_PSH
#define TCP_IMMEDIATE_ACK_FOR_PSH 1
#endif

/*
 ****************************************************************************
 * 5                    TYPES
 ****************************************************************************
 */

/*
 ****************************************************************************
 * 6                    EXTERN PROTOTYPES
 ****************************************************************************
 */

/*
 ****************************************************************************
 * 7                    LOCAL PROTOTYPES
 ****************************************************************************
 */

IP_PUBLIC Ip_err iptcp_configure(void);

/*
 *===========================================================================
 *                         SYSTEM VARIABLES
 *===========================================================================
 */
IP_STATIC IP_CONST Ipcom_sysvar iptcp_conf_sysvar[] =
{
    /*
     * Define the number of seconds IPNET will try to create a TCP
     * connection before giving up. Must be 300 or larger when running
     * the Ixia ANVL suite, several tests will fail otherwise
     */
    { "iptcp.ConnectionTimeout", IPCOM_MAKE_STR(TCP_CONN_TIMEOUT) },

    /*
     * Maximum number of times a TCP segment will be resent before
     * giving up with an IPTCP_ERRNO_ETIMEDOUT error. Exponential back
     * off is applied before each resend (max time between two resend
     * is 1 minute).
     */
    { "iptcp.MaxRetransmits", IPCOM_MAKE_STR(TCP_MAX_RETRANSMITS) },

     /*
      * Number of retransmissions that is allowed for sessions in transient
      * states when the total number of session in transient states is
      * greater than IPTCP_THRESH_TRANSIENT
      */
    { "iptcp.MaxRetransmitsTransientStates", IPCOM_MAKE_STR(IPTCP_MAX_RETRAMSMITS_IN_TRANSIENT) },

    /*
     * Maximum number of TCP sockets that are allowed to be in a state
     * that is very short-lived under normal conditions. Large number of
     * sockets in this states is an strong indication that this node is
     * under some form of DoS attack. The session that spent the most time
     * in a transient state will be dropped if this count is exceeded.
     */
    { "iptcp.MaxTransient", IPCOM_MAKE_STR(IPTCP_MAX_TRANSIENT) },

    /*
     * This node will decrease the number of resend attempts for session
     * in states that are normally very short-lived when the total amount
     * of session in transient states exceeds IPTCP_TRANSIENT_THRESH
     */
    { "iptcp.TransientTresh", IPCOM_MAKE_STR(IPTCP_TRANSIENT_THRESH) },

    /*
     * Maximum segment lifetime. TCP sockets that enter the TIME_WAIT
     * state will be in that state for 2 times this value.  Should be
     * 120 sec (2 min) according to RFC 793, but most TCP/IP stacks
     * sets this value to 30 sec
     */
    { "iptcp.Msl", IPCOM_MAKE_STR(TCP_MSL) },

    /*
     * If the tcp receiver never announces a window greater than MSS, the sender 
     * won't want to send anything smaller to avoid silly window syndrome. This 
     * value is the maximum waiting time in milliseconds of the receiver update its 
     * window size. If it is timeout, just send the data anyway to make forward progress.
     * 300 milliseconds by default.
     */
    { "iptcp.Wupw", IPCOM_MAKE_STR(TCP_WUPW) },

    /*
     * Set to !=0 to enable LAND attack protection
     */
    { "iptcp.LandAttackProtection", IPCOM_MAKE_STR(TCP_LAND_ATTACK_PROTECTION) },

    /*
     * Set to !=0 to allow zero window in ACK of a SYN/ACK.
     */
    { "iptcp.AllowZeroWindow", IPCOM_MAKE_STR(TCP_ALLOW_ZERO_WINDOW) },

    /*
     * Set to !=0 to allow a window less than one MSS in ACK of a
     * SYN/ACK.
     */
    { "iptcp.AllowTinyWindow", IPCOM_MAKE_STR(TCP_ALLOW_TINY_WINDOW) },

    /*
     * Defines the largest Maximum Segment Size that TCP will ever
     * suggest.  The actual MSS suggested might be smaller than this
     * number if depending on MTU for the interface. Set to 0 if the
     * largest MSS allowed by the MTU should be used
     */
    { "iptcp.MaxMss", IPCOM_MAKE_STR(TCP_MAX_MSS) },

#ifdef IPTCP_USE_TIMESTAMP_OPT
    /*
     * Set to 0 to make IPTCP not include the timestamp option in TCP
     * segments.
     */
    { "iptcp.opt.Timestamp", IPCOM_MAKE_STR(TCP_USE_TIMESTAMP) },
#endif

#ifdef IPTCP_USE_SACK_OPT
    /*
     * Set to 1 to allow the use of selective ACK.
     */
    { "iptcp.opt.AllowSack", IPCOM_MAKE_STR(TCP_ALLOW_SACK) },
#endif

    /*
     * Set to 1 to use urgent data as described in RFC 1122 chapter 4.2.2.4
     * set to 0 to use urgent data as described in RFC 793
     * Should be set to 0 since that is how most stacks works, must be set
     * to 1 in order successfully pass Ixia ANVL TCP-CORE group 19 tests
     */
    { "iptcp.urg.Rfc1122", IPCOM_MAKE_STR(TCP_USE_RFC1122_URGENT_DATA) },

#ifdef IPCOM_USE_TSO
    /*
     * The size multiplier that will be used on outgoing segments when
     * the outgoing interface support TCP Segmentation Offload. Higher
     * value will generally give better performance, but any factor
     * higher than 2 is not guaranteed to work on all network cards
     */
    { "iptcp.tso.Factor", IPCOM_MAKE_STR(TCP_SEGMENT_MULTIPLIER) },
#endif

    /*
     * Duration, in seconds, that a TCP peer node can keep its receive
     * window closed before this node will abort the session. A value
     * of "0" is used for no limit.
     */
    { "iptcp.PersistTimeout", IPCOM_MAKE_STR(TCP_PERSIST_TMO) },

    /*
     * Maximum MSS that TCP will use for sessions to peers that is not
     * link local to thise node. 0 will disable MSS clamping.
     */
    { "iptcp.ClampMss", IPCOM_MAKE_STR(TCP_CLAMP_MSS) },

    /*
     * The default time a TCP connection must be idle before the first
     * keep-alive packet is sent (in seconds).
     */
    { "iptcp.KeepIdle", IPCOM_MAKE_STR(TCP_KEEP_IDLE) },

    /* The time between each keep-alive probe.
     */
    { "iptcp.KeepIntvl", IPCOM_MAKE_STR(TCP_KEEP_INTVL) },

    /* Number of unsuccessful keep-alive probes that will be sent
     * before dropping the connection.
     */
    { "iptcp.KeepCnt", IPCOM_MAKE_STR(TCP_KEEP_CNT) },

    /* Use secure Initial Sequence Number as described in RFC6528 or not.
     * Set to "1" to enable, otherwise, set to "0".
     */
    { "iptcp.SecureISN", IPCOM_MAKE_STR(TCP_USE_RFC6528_SECURE_ISN) },

    { "iptcp.DelayAckTime", IPCOM_MAKE_STR(TCP_DELAY_ACK_TIME) },
    
    { "iptcp.ImmediateAckForPush", IPCOM_MAKE_STR(TCP_IMMEDIATE_ACK_FOR_PSH) },

    { IP_NULL, IP_NULL }
};


/* The default size of the backlog (backlog == 0 when calling ipcom_listen()) */
IP_CONST int iptcp_conf_default_backlog = TCP_DEFAULT_BACKLOG_SIZE;

/*
 ****************************************************************************
 * 7                    PUBLIC FUNCTIONS
 ****************************************************************************
 */


/*
 *===========================================================================
 *                    iptcp_configure
 *===========================================================================
 * Description: Configure IPTCP
 * Parameters:
 * Returns:
 *
 */
IP_PUBLIC Ip_err
iptcp_configure(void)
{
    /* Set IPTCP system variables. */
    (void)ipcom_sysvar_setv(iptcp_conf_sysvar, 0);

    return IPCOM_SUCCESS;
}


/*
 ****************************************************************************
 *                      END OF FILE
 ****************************************************************************
 */


