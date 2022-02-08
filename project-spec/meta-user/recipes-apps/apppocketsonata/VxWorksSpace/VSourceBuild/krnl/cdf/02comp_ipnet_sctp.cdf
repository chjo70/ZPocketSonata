/* 00comp_ipnet_sctp.cdf - IPNet Protocols Component configuration file */

/*
 * Copyright (c) 2006-2007 Wind River Systems, Inc.
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
01a,04dec08,j_y  created.
*/

#ifdef _WRS_CONFIG_COMPONENT_IPSCTP
Component INCLUDE_IPSCTP {
    NAME            SCTP
    SYNOPSIS        Stream Control Transmission Protocol
    REQUIRES        INCLUDE_IPCOM INCLUDE_IPNET
    MODULES         ipsctp_input.o \
                    ipsctp_output.o \
                    ipsctp.o \
                    ipsctp_sock.o \
                    ipsctp_ip4.o
    CONFIGLETTES    ipsctp_config.c
    CFG_PARAMS      SCTP_RTO_MIN \
                    SCTP_RTO_MAX \
                    SCTP_RTO_INITIAL \
                    SCTP_MAX_ASSOCS \
                    SCTP_VALID_COOKIE_LIFE_TIME \
                    SCTP_MAX_INIT_RETR \
                    SCTP_MAX_BURST \
                    SCTP_MAX_CHUNKS_PER_ASSOC \
                    SCTP_DELAYED_SACK_TIME \
                    SCTP_HEARTBEAT_INTERVAL \
                    SCTP_DEFAULT_SHUTDOWN_GUARD_TIME \
                    SCTP_SECRET_LIFE_TIME \
                    SCTP_MAX_RETR_PER_ASSOC \
                    SCTP_OUT_STREAMS
	_CHILDREN       FOLDER_NET_L4_TRANSPORT
}


Parameter SCTP_RTO_MAX {
    NAME        Maximum retransmission timeout
    SYNOPSIS    Maximum allowable value for retransmission timeout (in ms)
    TYPE        char *
    DEFAULT     "60000"
}

Parameter SCTP_RTO_MIN {
    NAME        Minimum retransmission timeout
    SYNOPSIS    Minimum allowable value for retransmission timeout (in ms)
    TYPE        char *
    DEFAULT     "1000"
}

Parameter SCTP_RTO_INITIAL {
    NAME        Initial retransmission timeout
    SYNOPSIS    Initial retransmission timeout (in ms)
    TYPE        char *
    DEFAULT     "3000"
}

Parameter SCTP_MAX_ASSOCS {
    NAME        Maximum value of associations in the system
    SYNOPSIS    The limit on the total number of associations the system can \
                support. For system where the maximum number of associations \
                is dynamic, this object should contain the value -1.
    TYPE        char *
    DEFAULT     "-1"
}

Parameter SCTP_VALID_COOKIE_LIFE_TIME {
    NAME        Default cookie lifetime (in ms)
    SYNOPSIS    Valid cookie life in the 4-way start-up handshake procedure. The \
                default value is 60000 milliseconds.
    TYPE        char *
    DEFAULT     "60000"
}

Parameter SCTP_MAX_INIT_RETR {
    NAME        Maximum number of retransmission for INIT chunks
    SYNOPSIS    The maximum number of retransmissions at the start-up phase for \
                INIT and COOKIE ECHO chunks. The recommended value is 8 number of \
                attempts.
    TYPE        char *
    DEFAULT     "8"
}

Parameter SCTP_MAX_BURST {
    NAME        Default max burst for SCTP endpoints
    SYNOPSIS    Maximum number of burst for SCTP endpoints. The default value is 4.
    TYPE        char *
    DEFAULT     "4"
}

Parameter SCTP_MAX_CHUNKS_PER_ASSOC {
    NAME        Max chunks on queue per association
    SYNOPSIS    Maximum number of chunks on queue per association. The default value is 512.
    TYPE        char *
    DEFAULT     "512"
}

Parameter SCTP_DELAYED_SACK_TIME {
    NAME        Default delayed SACK timer
    SYNOPSIS    Default delayed SACK timer in ms. The default value is 200 milliseconds.
    TYPE        char *
    DEFAULT     "200"
}

Parameter SCTP_HEARTBEAT_INTERVAL {
    NAME        Default heartbeat interval
    SYNOPSIS    Default heartbeat interval in ms. The default value is 30000 milliseconds.
    TYPE        char *
    DEFAULT     "30000"
}


Parameter SCTP_DEFAULT_SHUTDOWN_GUARD_TIME {
    NAME        Default shutdown guard timer
    SYNOPSIS    Default shutdown guard timer in seconds. The default value is 180 seconds.
    TYPE        char *
    DEFAULT     "180"
}

Parameter SCTP_SECRET_LIFE_TIME {
    NAME        Default secret lifetime
    SYNOPSIS    Default secret lifetime in seconds. The default value is 3600 seconds.
    TYPE        char *      
    DEFAULT     "3600"
}

Parameter SCTP_MAX_RETR_PER_ASSOC {
    NAME        Maximum number of retransmissions per association
    SYNOPSIS    Maximum number of retransmissions per association. The default value is 10 number of attempts.
    TYPE        char *
    DEFAULT     "10"
}

Parameter SCTP_OUT_STREAMS {
    NAME        Default number of outgoing streams
    SYNOPSIS    Default number of outgoing streams. The default value is 10.
    TYPE        char *
    DEFAULT     "10"
}


/*
CFG_PARAMS  
      SCTP_RTO_ALGORITHM \
      SCTP_STRICT_SACKS_CFG \
      SCTP_NO_CKSUM_ON_LOOPBACK_CFG \
      SCTP_STRICT_INIT_CFG \
      SCTP_PEER_CHUNK_OH_CFG \
      SCTP_SOCK_SEND_BUF_SIZE \
      SCTP_SOCK_RECV_BUF_SIZE \
      SCTP_NO_LOOPBACK_CKSUM \
      SCTP_STRICT_INIT \
      SCTP_MAX_BURST_DEF_CFG \
      SCTP_MAX_CHUNKS_ON_QUEUE_CFG \
      SCTP_DELAYED_SACK_TIME_DEF_CFG \
      SCTP_HEARTBEAT_INTERVAL_DEF_CFG \
      SCTP_DEF_PMTU_RAISE_SEC_CFG \
      SCTP_DEF_MAX_SHUTDOWN_SEC_CFG \
      SCTP_DEF_SECRET_LIFE_SEC_CFG \
      SCTP_DEFAULT_COOKIE_LIFE_CFG \
      SCTP_DEF_MAX_INIT_CFG \
      SCTP_DEF_MAX_SEND_CFG \
      SCTP_OSTREAM_INITIAL_CFG \
      SCTP_DEBUG_CFG

Parameter SCTP_AUTO_ASCONF_CFG {
        NAME		Enable Auto-ASCONF
        SYNOPSIS	Enable Auto-ASCONF
        DEFAULT		FALSE
        TYPE		bool
}

Parameter SCTP_ECN_CFG {
        NAME		Enable ECN
        SYNOPSIS	Enable ECN
        DEFAULT		TRUE
        TYPE		bool
}

Parameter SCTP_ECN_NONCE_CFG {
        NAME		Enable ECN Nonce
        SYNOPSIS	Enable ECN Nonce
        DEFAULT		FALSE
        TYPE		bool
}


Parameter SCTP_NO_CKSUM_ON_LOOPBACK_CFG {
        NAME		Disable checksum on loopback
        SYNOPSIS	Do not compute/validate checksum on packets that go through loopback
        DEFAULT		TRUE
        TYPE		bool
}

Parameter SCTP_STRICT_INIT_CFG {
        NAME		Enable strict INIT/INIT-ACK singleton enforcement
        SYNOPSIS	Enable strict INIT/INIT-ACK singleton enforcement
        DEFAULT		TRUE
        TYPE		bool
}

Parameter SCTP_PEER_CHUNK_OH_CFG {
        NAME		Amount to debit rwnd of peer per chunk sent
        SYNOPSIS	Amount to debit receive window of peer per chunk sent
        DEFAULT		sizeof(struct mbuf)
        TYPE		uint
}

Parameter SCTP_DEF_PMTU_RAISE_SEC_CFG {
        NAME		PMTU increase time
        SYNOPSIS	Time (in seconds) to wait before trying to increase PMTU again
        DEFAULT		600
        TYPE		uint
}


Parameter SCTP_DEFAULT_COOKIE_LIFE_CFG {
        NAME		
        SYNOPSIS	Default cookie lifetime in sec
        DEFAULT		60
        TYPE		uint
}


Parameter SCTP_DEBUG_CFG {
        NAME		SCTP debugging
        SYNOPSIS	Turn on/off SCTP debugging
        DEFAULT		FALSE
        TYPE		bool
}

Component INCLUDE_NETSTAT_SCTP {
	NAME		netstat for SCTP
	SYNOPSIS	netstat for SCTP
	INIT_RTN	netstatSctpInit ();
	MODULES		netstat_sctp.o
	REQUIRES	INCLUDE_SCTP
}


Parameter SCTP_RTO_ALGORITHM {
    NAME        Algorithm for retransmission timeout
    SYNOPSIS    The algorithm used to determine the timeout value (T3-rtx) used for \
                retransmitting unacknowledged chunks. In SCTP, only options 'other' \
                and 'vanj' are valid since SCTP defines Van Jacobson's algorithm \
                (vanj) as the one to be used to calculate RTO. 'Other' is left for \
                future use.
    TYPE        char *            
    DEFAULT     "vanj"
}

Parameter SCTP_NO_LOOPBACK_CKSUM {
    NAME        No checksum or CRC for Loopback interface
    SYNOPSIS    Do not compute/validate checksum or CRC on packets that go through loopback. \
                The default is TRUE.
    TYPE        char *
    DEFAULT     "1"
}

Parameter SCTP_STRICT_INIT {
    NAME        Strict INIT/INIT-ACK
    SYNOPSIS    Enable strict INIT/INIT-ACK singleton enforcement. The default is TRUE.
    TYPE        char *
    DEFAULT     "1"
}

Parameter SCTP_SOCK_SEND_BUF_SIZE {
    NAME        Size of SCTP socket send buffer
    SYNOPSIS    Size of socket send buffer in bytes. The default value is (128 * 1024).
    TYPE        char *
    DEFAULT     "131072"
}

Parameter SCTP_SOCK_RECV_BUF_SIZE {
    NAME        Size of SCTP socket receive buffer
    SYNOPSIS    Size of socket receive buffer. The default value is (128 * 1024).
    TYPE        char *
    DEFAULT     "131072"
}

Parameter SCTP_MAX_HEARTBEAT_BURST {
    NAME        Max hearbeat burst for SCTP endpoints
    SYNOPSIS    Maximum number of heartbeat burst for SCTP endpoints. The default \
                value is 1.
    TYPE        char *
    DEFAULT     "1"
}

Parameter SCTP_ENABLE_STRICT_SACKS {
    NAME        Enable Strict SACK checking
    SYNOPSIS    Enable SCTP Strict SACK checking
    TYPE        char *
    DEFAULT     "0"
}
*/

#endif  /* _WRS_CONFIG_COMPONENT_IPSCTP */
