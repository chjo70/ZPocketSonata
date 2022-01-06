/* ipsctp_config.c - IPNET SCTP Configuration File */

/*
 * Copyright (c) 2008 Wind River Systems, Inc.
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
01a,27nov07,kch  Created.
*/

/*
 ****************************************************************************
 * 1                    DESCRIPTION
 ****************************************************************************
 * User IPSCTP configuration file.
 */

/*
 ****************************************************************************
 * 2                    CONFIGURATION
 ****************************************************************************
 */
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
/*
 *===========================================================================
 *                         IPSCTP SYSVAR
 *===========================================================================
 * Define IPSCTP SYSVARS which not configued by kernel configuration.
 * TBD:proper values tbd
 */ 
#define SCTP_MAX_SEGMENT_DEFAULT        "0"       
#define SCTP_PARTIAL_DELIVERY_POINT     "65536"
#define SCTP_SACK_FREQ_DEFAULT          "2"
#define SCTP_IN_STREAMS                 "10"
#define SCTP_OPTIMIZATION_TCB_LOOKUP    "0"
#define SCTP_MAX_VTAG_TIMEWAIT          "10000"
#define SCTP_ABORT_ONE2ONE_HITLIMIT     "1"
#define SCTP_MAX_RETR_PER_PATH          "5"
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

/*
 ****************************************************************************
 * 8                    DATA
 ****************************************************************************
 */

/*
 *===========================================================================
 *                         ipsctp_conf_sysvar
 *===========================================================================
 * IPSCTP Configuration Variables. The first seven configuration parameters 
 * are based on the SCTP MIB model as specified in RFC3873. The remaining
 * configuration parameters are for backwards compatibility with the previous
 * VxWorks 6.4 SCTP implementation.
 */

IP_CONST Ipcom_sysvar ipsctp_conf_sysvar[] =
{
    /*
     * The minimum value permitted by a SCTP implementation for the
     * retransmission timeout value, measured in milliseconds. A
     * retransmission time value of zero means immediate retransmission.
     * The configured value has to be lower than or equal to stcpRtoMax.
     * The default value is 1000 milliseconds.
     */
    IP_SYSVAR("ipsctp.Rto.Min", "1000", SCTP_RTO_MIN),
    
    /*
     * The maximum value permitted by a SCTP implementation for the
     * retransmission timeout value, measured in milliseconds. A
     * retransmission time value of zero means immediate retransmission.
     * The configured value has to be greater than or equal to
     * stcpRtoMin. The default value is 60000 milliseconds.
     */
    IP_SYSVAR("ipsctp.Rto.Max", "60000", SCTP_RTO_MAX),

    /*
     * The initial value for the retransmission timer. A retransmission time
     * value of zero means immediate retransmission. The default value is
     * 3000 milliseconds.
     */
    IP_SYSVAR("ipsctp.Rto.Initial", "3000", SCTP_RTO_INITIAL),

    /*
     * The limit on the total number of associations the system can
     * support. For system where the maximum number of associations
     * is dynamic, this object should contain the value -1."
     */
    IP_SYSVAR("ipsctp.Max.Associations", "-1", SCTP_MAX_ASSOCS),

    /*
     * Valid cookie life in the 4-way start-up handshake procedure. The
     * default value is 60000 milliseconds.
     */
    IP_SYSVAR("ipsctp.Valid.Cookie.Life", "60000", SCTP_VALID_COOKIE_LIFE_TIME),

    /*
     * The maximum number of retransmissions at the start-up phase for
     * INIT and COOKIE ECHO chunks. The recommended value is 8 number of
     * attempts.
     */
    IP_SYSVAR("ipsctp.Max.Init.Retransmits", "8", SCTP_MAX_INIT_RETR),

    /*** Additional RFC4960 SCTP Protocol parameters ***/

    /*** VxWorks 6.4 SCTP backwards compatibility parameters ***/

    /*
     * Maximum number of burst for SCTP endpoints. The default value is 4.
     */
    IP_SYSVAR("ipsctp.Max.Burst", "4", SCTP_MAX_BURST),
        
    IP_SYSVAR("ipsctp.Max.Segment", "0", SCTP_MAX_SEGMENT_DEFAULT),

    /*
     * Maximum number of chunks on queue per association. The default value 
     * is 512.
     */
    IP_SYSVAR("ipsctp.Max.ChunksPerAssoc", "4294967295", SCTP_MAX_CHUNKS_PER_ASSOC),

    /*
     * Default delayed SACK timer. The default value is 200 milliseconds.
     */
    IP_SYSVAR("ipsctp.Sack.DelayedTime", "200", SCTP_DELAYED_SACK_TIME),
        
    /*
     * Default SACK frequency. The default value is 2.
     */
    IP_SYSVAR("ipsctp.Sack.Freq", "2", SCTP_SACK_FREQ_DEFAULT),

    /*
     * Default heartbeat interval. The default value is 30000 milliseconds.
     */
    IP_SYSVAR("ipsctp.HB.Interval", "30000", SCTP_HEARTBEAT_INTERVAL),

    /*
     * Default shutdown guard timer in seconds. The default value is 180
     * seconds.
     */
    IP_SYSVAR("ipsctp.Default.ShutdownGuardTime", "180", SCTP_DEFAULT_SHUTDOWN_GUARD_TIME),

    /*
     * Default secret lifetime in seconds. The default value is 3600 seconds.
     */
    IP_SYSVAR("ipsctp.Default.SecretLifeTime", "3600", SCTP_SECRET_LIFE_TIME),

    /*
     * Maximum number of retransmissions per association. The default value 
     * is 10 number of attempts.
     */
    IP_SYSVAR("ipsctp.Max.RetrPerAssoc", "10", SCTP_MAX_RETR_PER_ASSOC),

    /*
     * Default number of outgoing streams. The default value is 10.
     */
    IP_SYSVAR("ipsctp.Default.NumOutStreams", "10", SCTP_OUT_STREAMS),
    /*
     * Default number of incoming streams. The default value is 10.
     */
    IP_SYSVAR("ipsctp.Default.NumInStreams", "10", SCTP_IN_STREAMS),

    IP_SYSVAR("ipsctp.Max.Vtag.TimeWait", "10000", SCTP_MAX_VTAG_TIMEWAIT),
        
    IP_SYSVAR("ipsctp.Max.RetrPerPath", "5", SCTP_MAX_RETR_PER_PATH),
#if 0

    /*
     * Time (in seconds) to wait before trying to increase PMTU again.
     * The default value is 600 seconds.
     */
    { "ipsctp.Default.PmtuRaiseTime", SCTP_PMTU_RAISE_TIME},
        /*
     * Do not compute/validate checksum on packets that go through loopback.
     * The default is TRUE.
     */
    { "ipsctp.Default.NoLoopbackCksum", SCTP_NO_LOOPBACK_CKSUM},

    /*
     * Enable strict INIT/INIT-ACK singleton enforcement. The default is TRUE.
     */
    { "ipsctp.Default.StrictInit", SCTP_STRICT_INIT},
    /*
     * Size of socket send buffer in bytes. The default value is (128 * 1024)
     */
    { "ipsctp.Default.SockSendBufSize", SCTP_SOCK_SEND_BUF_SIZE},

    /*
     * Size of socket receive buffer. The default value is 
     * 128 * (1024 + sizeof(struct sockaddr_in))
     */
    { "ipsctp.Default.SockRecvBufSize", SCTP_SOCK_RECV_BUF_SIZE},
    /*
     * The algorithm used to determine the timeout value (T3-rtx) used for
     * retransmitting unacknowledged chunks. In SCTP, only options 'other'
     * and 'vanj' are valid since SCTP defines Van Jacobson's algorithm
     * (vanj) as the one to be used to calculate RTO. 'Other' is left for
     * future use.
     */
    { "ipsctp.Rto.Algorithm", SCTP_RTO_ALGORITHM},

    /*
     * Maximum number of heartbeat burst for SCTP endpoints. The default 
     * value is 1.
     */
    { "ipsctp.HB.Max.Burst", SCTP_MAX_HEARTBEAT_BURST},

    /*
     * Enable SCTP Strict SACK checking. The default is FALSE.
     */
    { "ipsctp.Sack.EnableStrict", SCTP_ENABLE_STRICT_SACKS},

    /* This point is the size of a message where the partial delivery API will
     * be invoked to help free up rwnd space for the peer. 
     */
    { "ipsctp.PartialDelivery.Point", SCTP_PARTIAL_DELIVERY_POINT},

    { "ipsctp.Optimization.TCB.Lookup", SCTP_OPTIMIZATION_TCB_LOOKUP},

    { "ipsctp.Abort.One2one.HitLimit", SCTP_ABORT_ONE2ONE_HITLIMIT},
#endif
    { IP_NULL, IP_NULL }
};

/* The default size of the backlog (backlog == 0 when calling ipcom_listen()) */
IP_CONST int ipsctp_conf_default_backlog = 5;

/*
 ****************************************************************************
 * 9                    LOCAL FUNCTIONS
 ****************************************************************************
 */

/*
 ****************************************************************************
 * 10                   PUBLIC FUNCTIONS
 ****************************************************************************
 */

/*
 *===========================================================================
 *                    ipsctp_configure
 *===========================================================================
 * Description: Configure hook for IPSCTP.
 * Parameters:
 * Returns:
 *
 */
IP_PUBLIC Ip_err
ipsctp_configure(void)
{
    /* Set IPSCTP system variables. */
    (void)ipcom_sysvar_setv(ipsctp_conf_sysvar, 0);

    return IPCOM_SUCCESS;
}

/*
 ****************************************************************************
 *                      END OF FILE
 ****************************************************************************
 */

