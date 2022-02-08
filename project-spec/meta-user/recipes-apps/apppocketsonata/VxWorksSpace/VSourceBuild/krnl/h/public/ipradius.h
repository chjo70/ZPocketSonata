/* ipradius.h - API of RADIUS client */

/*
 * Copyright (c) 2006-2013, 2016 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
17may16,ghl  Port TSR defect fix forward from vxworks6.9 into vx7. (F6988)
*/


#ifndef IPRADIUS_H
#define IPRADIUS_H

/*
 ****************************************************************************
 * 1                    DESCRIPTION
 ****************************************************************************
 */

/*
DESCRIPTION
This library contains the API for IPRADIUS - Radius client
*/

/*
 **************************************************************************
 * 2                    CONFIGURATION
 ****************************************************************************
 */

#include "ipradius_config.h"

/* Define to make the radius library code reentrant. */
#define IPRADIUS_ENABLE_REENTRANT

/* Size of secret shared between RADIUS server and RADIUS client */
#define IPRADIUS_MAX_SECRET_SIZE           64

/* Max number of specified servers in Ipradius_request */
#define IPRADIUS_MAX_SPECIFIED_SERVERS     3

/* Max size of NAS identifier string */
#define IPRADIUS_MAX_NAS_IDENTIFIER_SIZE   64

/* Max size of user password. */
#define IPRADIUS_MAX_PASSWORD_SIZE         128


/*
 ****************************************************************************
 * 3                    INCLUDE FILES
 ****************************************************************************
 */

#include <ipcom_type.h>
#include <ipcom_sock.h>
#include <ipcom_sock6.h>
#include <ipcom_inet.h>
#include <ipcom_tags.h>
#include <ipcom_auth.h>
#include <ipcom_list.h>
#include <ipcom_tmo.h>
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
 *                         IPRADIUS_RELEASE
 *===========================================================================
 * IPRADIUS release version.
 */
#define IPRADIUS_RELEASE 60701


/*
 *===========================================================================
 *                         Attribute tags
 *===========================================================================
 */

#define IPRADIUS_ATTR_User_Name                 1
#define IPRADIUS_ATTR_User_Password             2
#define IPRADIUS_ATTR_CHAP_Password             3
#define IPRADIUS_ATTR_NAS_IP_Address            4
#define IPRADIUS_ATTR_NAS_Port                  5
#define IPRADIUS_ATTR_Service_Type              6
#define IPRADIUS_ATTR_Framed_Protocol           7
#define IPRADIUS_ATTR_Framed_IP_Address         8
#define IPRADIUS_ATTR_Framed_IP_Netmask         9

#define IPRADIUS_ATTR_Framed_Routing            10
#define IPRADIUS_ATTR_Filter_Id                 11
#define IPRADIUS_ATTR_Framed_MTU                12
#define IPRADIUS_ATTR_Framed_Compression        13
#define IPRADIUS_ATTR_Login_IP_Host             14
#define IPRADIUS_ATTR_Login_Service             15
#define IPRADIUS_ATTR_Login_TCP_Port            16
#define IPRADIUS_ATTR_unassigned_17             17
#define IPRADIUS_ATTR_Reply_Message             18
#define IPRADIUS_ATTR_Callback_Number           19

#define IPRADIUS_ATTR_Callback_Id               20
#define IPRADIUS_ATTR_unassigned_21             21
#define IPRADIUS_ATTR_Framed_Route              22
#define IPRADIUS_ATTR_Framed_IPX_Network        23
#define IPRADIUS_ATTR_State                     24
#define IPRADIUS_ATTR_Class                     25
#define IPRADIUS_ATTR_Vendor_Specific           26
#define IPRADIUS_ATTR_Session_Timeout           27
#define IPRADIUS_ATTR_Idle_Timeout              28
#define IPRADIUS_ATTR_Termination_Action        29

#define IPRADIUS_ATTR_Called_Station_Id         30
#define IPRADIUS_ATTR_Calling_Station_Id        31
#define IPRADIUS_ATTR_NAS_Identifier            32
#define IPRADIUS_ATTR_Proxy_State               33
#define IPRADIUS_ATTR_Login_LAT_Service         34
#define IPRADIUS_ATTR_Login_LAT_Node            35
#define IPRADIUS_ATTR_Login_LAT_Group           36
#define IPRADIUS_ATTR_Framed_AppleTalk_Link     37
#define IPRADIUS_ATTR_Framed_AppleTalk_Network  38
#define IPRADIUS_ATTR_Framed_AppleTalk_Zone     39

#define IPRADIUS_ATTR_Acct_Status_Type          40
#define IPRADIUS_ATTR_Acct_Delay_Time           41
#define IPRADIUS_ATTR_Acct_Input_Octets         42
#define IPRADIUS_ATTR_Acct_Output_Octets        43
#define IPRADIUS_ATTR_Acct_Session_Id           44
#define IPRADIUS_ATTR_Acct_Authentic            45
#define IPRADIUS_ATTR_Acct_Session_Time         46
#define IPRADIUS_ATTR_Acct_Input_Packets        47
#define IPRADIUS_ATTR_Acct_Output_Packets       48
#define IPRADIUS_ATTR_Acct_Terminate_Cause      49

#define IPRADIUS_ATTR_Acct_Multi_Session_Id     50
#define IPRADIUS_ATTR_Acct_Link_Count           51
#define IPRADIUS_ATTR_Acct_Input_Gigawords      52
#define IPRADIUS_ATTR_Acct_Output_Gigawords     53
#define IPRADIUS_ATTR_unassigned_54             54
#define IPRADIUS_ATTR_Event_Timestamp           55

/* RADIUS VLAN attributes, RFC 4675 */
#define IPRADIUS_ATTR_Egress_VLANID		56
#define IPRADIUS_ATTR_Ingress_Filters		57
#define IPRADIUS_ATTR_Egress_VLAN_Name		58
#define IPRADIUS_ATTR_User_Priority_Table	59

#define IPRADIUS_ATTR_CHAP_Challenge            60
#define IPRADIUS_ATTR_NAS_Port_Type             61
#define IPRADIUS_ATTR_Port_Limit                62
#define IPRADIUS_ATTR_Login_LAT_Port            63
#define IPRADIUS_ATTR_Tunnel_Type               64
#define IPRADIUS_ATTR_Tunnel_Medium_Type        65
#define IPRADIUS_ATTR_Tunnel_Client_Endpoint    66
#define IPRADIUS_ATTR_Tunnel_Server_Endpoint    67
#define IPRADIUS_ATTR_Acct_Tunnel_Connection    68
#define IPRADIUS_ATTR_Tunnel_Password           69

#define IPRADIUS_ATTR_ARAP_Password             70
#define IPRADIUS_ATTR_ARAP_Features             71
#define IPRADIUS_ATTR_ARAP_Zone_Access          72
#define IPRADIUS_ATTR_ARAP_Security             73
#define IPRADIUS_ATTR_ARAP_Security_Data        74
#define IPRADIUS_ATTR_Password_Retry            75
#define IPRADIUS_ATTR_Prompt                    76
#define IPRADIUS_ATTR_Connect_Info              77
#define IPRADIUS_ATTR_Configuration_Token       78
#define IPRADIUS_ATTR_EAP_Message               79

#define IPRADIUS_ATTR_Message_Authenticator     80
#define IPRADIUS_ATTR_Tunnel_Private_Group_ID   81
#define IPRADIUS_ATTR_Tunnel_Assignment_ID      82
#define IPRADIUS_ATTR_Tunnel_Preference         83
#define IPRADIUS_ATTR_ARAP_Challenge_Response   84
#define IPRADIUS_ATTR_Acct_Interim_Interval     85
#define IPRADIUS_ATTR_Acct_Tunnel_Packets_Lost  86
#define IPRADIUS_ATTR_NAS_Port_Id               87
#define IPRADIUS_ATTR_Framed_Pool               88
#define IPRADIUS_ATTR_CUI                       89

#define IPRADIUS_ATTR_Tunnel_Client_Auth_ID     90
#define IPRADIUS_ATTR_Tunnel_Server_Auth_ID     91
#define IPRADIUS_ATTR_NAS_IPv6_Address          95
#define IPRADIUS_ATTR_Framed_Interface_Id       96
#define IPRADIUS_ATTR_Framed_IPv6_Prefix        97
#define IPRADIUS_ATTR_Login_IPv6_Host           98
#define IPRADIUS_ATTR_Framed_IPv6_Route         99
#define IPRADIUS_ATTR_Framed_IPv6_Pool          100

/* RADIUS EAP attribute, RFC 5247, section 5.9 */
#define IPRADIUS_ATTR_EAP_Key_Name              102 

/* other attribute constants */
#define IPRADIUS_TUNNEL_MEDIUM_TYPE_IPV4        1
#define IPRADIUS_ACCT_Start                     1
#define IPRADIUS_ACCT_Stop                      2
#define IPRADIUS_ACCT_Interim_Update            3
#define IPRADIUS_ACCT_Accounting_On
#define IPRADIUS_ACCT_Accounting_Off
#define IPRADIUS_ACCT_Failed                    15
#define IPRADIUS_ACCT_Radius                    1

/* RFC 3580, section 3.31, tunnel attribute constants */
#define IPRADIUS_TUNNEL_TYPE_VLAN		13
#define IPRADIUS_TUNNEL_MEDIUM_TYPE_8021X	802


/*
 *===========================================================================
 *                         Microsoft vendor extensions
 *===========================================================================
 * Microsoft attribute vendor extensions used with
 * IPRADIUS_ATTR_Vendor_Specific attribute tag (26).
 */

#define IPRADIUS_VENDOR_MICROSOFT   311

#define IPRADIUS_ATTR_MS_Primary_DNS_Server      28
#define IPRADIUS_ATTR_MS_Secondary_DNS_Server    29
#define IPRADIUS_ATTR_MS_Primary_NBNS_Server     30
#define IPRADIUS_ATTR_MS_Secondary_NBNS_Server   31


/*
 *===========================================================================
 *                         RADIUS packet header codes
 *===========================================================================
 */

#define IPRADIUS_CODE_Access_Request       1
#define IPRADIUS_CODE_Access_Accept        2
#define IPRADIUS_CODE_Access_Reject        3
#define IPRADIUS_CODE_Accounting_Request   4
#define IPRADIUS_CODE_Accounting_Response  5
#define IPRADIUS_CODE_Access_Challenge     11


/*
 *===========================================================================
 *                         C-API error values
 *===========================================================================
 */
#define IPRADIUS_ERROR_BASE                0

#define IPRADIUS_ERR_UNSUPPORTED_TAG                    (IPRADIUS_ERROR_BASE+0)
#define IPRADIUS_ERR_UNKNOWN_PACKET_CODE                (IPRADIUS_ERROR_BASE+1)
#define IPRADIUS_ERR_TOO_MANY_OUTSTANDING_REQUESTS      (IPRADIUS_ERROR_BASE+2)
#define IPRADIUS_ERR_INVAL_PKT_ID                       (IPRADIUS_ERROR_BASE+3)
#define IPRADIUS_ERR_BAD_AUTHENTICATION                 (IPRADIUS_ERROR_BASE+4)
#define IPRADIUS_ERR_BAD_ATTRIBUTE                      (IPRADIUS_ERROR_BASE+5)
#define IPRADIUS_ERR_NO_SESSION                         (IPRADIUS_ERROR_BASE+6)
#define IPRADIUS_ERR_SECRET_TOO_LONG                    (IPRADIUS_ERROR_BASE+7)
#define IPRADIUS_ERR_INVAL_PWD_LEN                      (IPRADIUS_ERROR_BASE+8)
#define IPRADIUS_ERR_NO_SERVER_RESPONSE                 (IPRADIUS_ERROR_BASE+9)
#define IPRADIUS_ERR_INVAL_INTERIM_ACCT_INTERVAL        (IPRADIUS_ERROR_BASE+10)
#define IPRADIUS_ERR_SECRET_TOO_SHORT                   (IPRADIUS_ERROR_BASE+11)
#define IPRADIUS_ERR_MISSING_CHAP_ATTR                  (IPRADIUS_ERROR_BASE+12)
#define IPRADIUS_ERR_INVAL_PWD_TYPE                     (IPRADIUS_ERROR_BASE+13)
#define IPRADIUS_ERR_NO_SERVER                          (IPRADIUS_ERROR_BASE+14)
#define IPRADIUS_ERR_DISCARDED_PACKET                   (IPRADIUS_ERROR_BASE+15)
#define IPRADIUS_ERR_DUPLICATE_INDEX                    (IPRADIUS_ERROR_BASE+16)
#define IPRADIUS_ERR_UNSUPPORTED_PACKET_CODE            (IPRADIUS_ERROR_BASE+17)
#define IPRADIUS_ERR_CLOSED                             (IPRADIUS_ERROR_BASE+18)


/*
 ****************************************************************************
 * 5                    TYPES
 ****************************************************************************
 */

/*
 *===========================================================================
 *                         Ipradius_server
 *===========================================================================
 */

/* Ipradius_server server types: 'server_type' */
#define IPRADIUS_ACCESS_SERVER     1
#define IPRADIUS_ACCOUNTING_SERVER 2
#define IPRADIUS_FULL_SERVER       3

typedef struct Ipradius_server_struct
{
    Ip_u32     index;              /* Must be unique. pick 0 if you want one assigned,
                                      in which case it will be set after the server is added. */
    union Ip_sockaddr_union   server_addr;  /* Server IPv4/v6 socket address union. */

    Ip_u16     server_type;   /* IPRADIUS_ACCESS_SERVER, IPRADIUS_ACCOUNTING_SERVER,
                                 or IPRADIUS_FULL_SERVER. */

    Ip_u16     pollnum;     /* Number of times to poll the server before trying next one. */
    Ip_u16     pollsec;     /* Seconds to wait for a reply from the RADIUS server. */

    /* secret to be shared between the RADIUS client and this server */
    Ip_u8      shared_secret[IPRADIUS_MAX_SECRET_SIZE];

    /* length of the shared secret */
    Ip_u32     shared_secret_len;

    Ip_tag     conf[1];     /* None available, included for future compability. */
}
Ipradius_server;


/*
 *===========================================================================
 *                         Ipradius_header
 *===========================================================================
 */
#define IPRADIUS_HDRSIZE      20

typedef struct Ipradius_header_struct
{
    /* RADIUS packet header. */
    Ip_u8         code;
    Ip_u8         id;
    Ip_u16        length;
    Ip_u8         auth[16];

    Ip_u8         attr[4];     /* variable number/length attribute field. */
}
Ipradius_header;


/*
 *===========================================================================
 *                         Ipradius_request
 *===========================================================================
 */

/* request type */
#define IPRADIUS_ACCESS_REQUEST     0
#define IPRADIUS_ACCOUNT_REQUEST    1

/* pwd_type */
#define IPRADIUS_No_Password        0
#define IPRADIUS_PAP_Password       1
#define IPRADIUS_CHAP_Password      2

typedef struct Ipradius_server_list_struct
{
    Ip_u32     index;          /* Server index. */
    union Ip_sockaddr_union   server_addr;  /* Server IPv4/v6 socket address union. */
    Ip_u16     server_type;    /* IPRADIUS_ACCESS_SERVER, IPRADIUS_ACCOUNTING_SERVER, IPRADIUS_FULL_SERVER */
    Ip_u16     pollnum;        /* Number of times to poll the server before trying next one. */
    Ip_u16     pollsec;        /* Seconds to wait for a reply from the RADIUS server. */
}
Ipradius_server_list;

/* data for one user request for RADIUS service */
typedef struct Ipradius_request_struct
{
    void       *cookie;      /* handle for user callback. */
    Ip_u32      unique;      /* unique ID for each request to avoid spamming. */
    Ip_err      status;      /* IPCOM_SUCCESS or IPCOM_ERR_FAILED. */

    Ip_u32      pwd_type;    /* password type: IPRADIUS_PAP_Password,
                                IPRADIUS_CHAP_Password, IPRADIUS_No_Password */
    char        pwd[IPRADIUS_MAX_PASSWORD_SIZE]; /* password */
    Ip_u32      pwd_len;     /* length of password */
    Ip_u8       chap_ident;  /* CHAP response ID */
    Ip_u8       pad[3];      /* currently unused padding for alignment reasons. */

#ifdef IPCOM_USE_INET
    /* RADIUS client IPv4 UDP socket descriptor.
     * Set to IP_INVALID_SOCKET if request shall not talk to IPv4 servers. */
    Ip_fd       fd;
#endif
#ifdef IPCOM_USE_INET6
    /* RADIUS client IPv6 UDP socket descriptor.
     * Set to IP_INVALID_SOCKET if request shall not talk to IPv6 servers. */
    Ip_fd       fd6;
#endif

    /* Request event callback function pointer. */
    Ip_err    (*event_callback) (int event, struct Ipradius_request_struct *request, Ipradius_header *request_packet, Ipradius_header *response_packet, Ipradius_server *server);

    Ip_u8       num_servers; /* Number of valid entries in 'serv_list' below. 0 if default servers wanted. */
    Ipradius_server_list   serv_list[IPRADIUS_MAX_SPECIFIED_SERVERS];
}
Ipradius_request;

/*
 *===========================================================================
 *                         Ipradius_id
 *===========================================================================
 */
typedef struct Ipradius_id_struct
{
    Ip_s16    num;
    Ip_u8     get;
    Ip_u8     put;
    Ip_u8     ids[256];
}
Ipradius_id;


/*
 *===========================================================================
 *                         Ipradius_ids
 *===========================================================================
 */
typedef struct Ipradius_ids_struct
{
    Ip_s32        ref_count;
    Ipradius_id   access_ids;
    Ipradius_id   account_ids;
}
Ipradius_ids;


/*
 *===========================================================================
 *                         Ipradius_server_entry
 *===========================================================================
 */


typedef struct Ipradius_server_entry_struct
{
    Ipcom_list        server_list;

    /* Packet ids. */
    Ipradius_ids     *pkt_ids;

    /* Reference counts. */
    Ip_s32               ref_count;

    /* radiusAuthServerAddress   - in server. */
    /* radiusAuthClientServerPortNumber - in server. */

    /* Authentication MIB data */
    Ip_u32   AuthRoundTripTime;
    Ip_u32   AuthAccessRequests;
    Ip_u32   AuthAccessRetransmissions;
    Ip_u32   AuthAccessAccepts;
    Ip_u32   AuthAccessRejects;
    Ip_u32   AuthAccessChallenges;
    Ip_u32   AuthMalformedAccessResponses;
    Ip_u32   AuthBadAuthenticators;
    /* Ip_u32 AuthPendingRequests in access ids */
    Ip_u32   AuthTimeouts;
    Ip_u32   AuthUnknownTypes;
    Ip_u32   AuthPacketsDropped;

    /* Accounting MIB data */
    Ip_u32   AccRoundTripTime;
    Ip_u32   AccRequests;
    Ip_u32   AccRetransmissions;
    Ip_u32   AccResponses;
    Ip_u32   AccMalformedResponses;
    Ip_u32   AccBadAuthenticators;
    /* Ip_u32 AccPendingRequests in account ids */
    Ip_u32   AccTimeouts;
    Ip_u32   AccUnknownTypes;
    Ip_u32   AccPacketsDropped;

    Ipradius_server   server;     /* IP-addr, port, time to wait for reply... */
}
Ipradius_server_entry;


/*
 *===========================================================================
 *                         Ipradius_session
 *===========================================================================
 * One for each session. The session starts on ipradius_accounting_start()
 * and terminates when ipradius_end_accounting() is called for the session.
 */
typedef struct Ipradius_session_struct
{
    Ipcom_list               session_list;

    /* seconds since the Epoch when session started (0 if not started) */
    Ip_time_t                start_time;

    /* seconds between interim accounting */
    Ip_u32                   acct_interim_interval;

    /* seconds to next accounting update */
    Ip_s32                   sec_to_next_interim_acct;

    /* interim sequence number */
    int                      interim_int;

    /* IP_TRUE=an accounting request is pending */
    Ip_bool                  request_pending;

    /* the server who initially responded. */
    Ipradius_server_entry   *servent;

    /* Set to IP_TRUE if servent once has been set. */
    Ip_bool                  server_fixed;

    /* Request entry info. */
    Ipradius_request         request;
}
Ipradius_session;


/*
 *===========================================================================
 *                         Ipradius_request_entry
 *===========================================================================
 */
/* One for each user currently requesting service. Will be removed from request
 * list (and thus no longer known to the protocol) once an accept has been
 * received, or all servers have been tried.
*/
#define IPRADIUS_REQUEST_ENTRY_MAGIC   0x23567256

#pragma pack(4)
typedef struct Ipradius_request_entry_struct
{
    Ipcom_list               request_list;

    Ip_u32                   magic;
    Ip_s32                   num_ids;

    Ip_u32                   pollnum;
    Ip_u32                   sec_since_poll;  /* seconds since last poll sent to current server. */

    /* seconds since Epoch when latest request packet sent
       to the currently used server */
    Ip_time_t                request_start_time;

    Ip_u32                   servers_tried;   /* number of servers tried. */
    Ipradius_server_entry   *servent;         /* server currently tried. */
    Ip_bool                  server_fixed;    /* if IP_TRUE, server may not be changed. */

    Ipradius_session        *session;         /* session for accounting requests. */

    Ipradius_request         request;         /* User request structure. */
    
    Ip_s32                   pkt_length;      /* Length of the request packet */

    Ipradius_header          hdr;             /* RADIUS packet header.*/
}
Ipradius_request_entry;
#pragma pack()

/*
 *===========================================================================
 *                         IPRADIUS memory
 *===========================================================================
 */
typedef struct Ipradius_mem_struct
{
    Ip_s32    servers;
    Ip_s32    sessions;
    Ip_s32    requests;
    Ip_s32    ids;
    Ip_s32    id_holders;
}
Ipradius_mem;


/*
 *===========================================================================
 *                   Global IPRADIUS data
 *===========================================================================
 */
typedef struct Ipradius_data_struct
{
    Ip_bool      opened;
    Ip_s32       infunc;

#ifdef IPRADIUS_ENABLE_REENTRANT
    Ipcom_mutex  code_mutex;  /* Mutex to protect IPRADIUS global data. */
#endif

    Ip_bool      same_acct_server;  /* default IP_TRUE. if false, start/interim/stop accounting
                                       may be sent to different accounting servers. */

    Ip_u8 ipradius_NAS_Identifier[IPRADIUS_MAX_NAS_IDENTIFIER_SIZE]; /* Identifier of RADIUS client */
    Ip_u32 ipradius_NAS_Identifier_size;

    /* user config, attribute space */
    Ip_u32       access_request_attribute_size;
    Ip_u32       accounting_request_attribute_size;

    /* tick */
    Ipcom_tmo           tmo; /* data for ipcom timeout function */
    Ip_u32              tick;

    /* servers */
    Ip_u32                   server_num;     /* number of servers. */
    Ip_u32                   server_index;   /* next server index. */
    Ipcom_list               server_head;

    /* requests */
    Ipcom_list               request_head;

    /* Current sessions */
    Ipcom_list               session_head;

    /* Syslog output memory. */
    char                     buf[46];

    /* Memory counters. */
    Ipradius_mem             mem;

    Ip_u32  mib_AuthInvalidServerAddresses;
    Ip_u32  mib_AccInvalidServerAddresses;
    /* mib_ClientIdentifier == ipradius_NAS_Identifier above */
}
Ipradius_data;


/* event_callback() events: */
#define IPRADIUS_EVENT_ACCESS_ACCEPT            1   /* Received access accept. */
#define IPRADIUS_EVENT_ACCESS_REJECT            2   /* Received access reject. */
#define IPRADIUS_EVENT_ACCESS_CHALLENGE         3   /* Received access challenge. */
#define IPRADIUS_EVENT_ACCOUNTING_RESPONSE      4   /* Received accounting response. */
#define IPRADIUS_EVENT_ACCESS_TIMEOUT           5   /* Access request timeout. */
#define IPRADIUS_EVENT_ACCESS_CANCELLED         6   /* Access request was cancelled. */
#define IPRADIUS_EVENT_ACCOUNTING_TIMEOUT       7   /* Accounting request timeout. */
#define IPRADIUS_EVENT_ACCOUNTING_CANCELLED     8   /* Accounting request was cancelled. */
#define IPRADIUS_EVENT_ACCOUNTING_REQUEST       9   /* Sending accounting request. */


/*
 *===========================================================================
 *                         Ipradius_open
 *===========================================================================
 * The ipradius_open structure is used to pass global, i.e. non_interface
 * specific configuration and callback functions to IPRADIUS.
 * No optional global configuration is available yet, hence conf[0] must
 * currently always be set to IPTAG_END.
 */
typedef struct Ipradius_open_struct
{
    /* Identifier of RADIUS client */
    char      ipradius_NAS_Identifier[IPRADIUS_MAX_NAS_IDENTIFIER_SIZE];
    Ip_u32    ipradius_NAS_Identifier_size;

    /* user config, attribute space */
    Ip_u32    access_request_attribute_size;
    Ip_u32    accounting_request_attribute_size;

    Ip_tag    conf[1];   /* None available, included for future compability. */
}
Ipradius_open;


/*
 ****************************************************************************
 * 6                    FUNCTIONS
 ****************************************************************************
 */

/*******************************************************************************
*
* event_callback - handle events resulting from a request
*
* An implementation of this callback routine is required. It is invoked through
* a function pointer in the <event_callback> field of the 'Ipradius_request'
* structure. The event callback handles all incoming RADIUS server reply
* packets, timeouts on access and accounting requests, canceled requests, and
* each sending of a new accounting request. The <event> parameter contains the
* event that caused the event callback routine to be called
*
* SYNOPSIS
* \cs
* Ip_err ipradius_example_event_callback ( )
* \ce
*
* Parameters:
* \is
* \i <event>
* An event code identifying the basis for calling the event_callback() routine.
* The following event codes are available:
* \i 'IPRADIUS_EVENT_ACCESS_ACCEPT'
* Received access accept.
* \i 'IPRADIUS_EVENT_ACCESS_REJECT'
* Received access reject.
* \i 'IPRADIUS_EVENT_ACCESS_CHALLENGE'
* Received access challenge.
* \i 'IPRADIUS_EVENT_ACCOUNTING_RESPONSE'
* Received accounting response.
* \i 'IPRADIUS_EVENT_ACCESS_TIMEOUT'
* Access request timeout.
* \i 'IPRADIUS_EVENT_ACCESS_CANCELLED'
* Access request was cancelled.
* \i 'IPRADIUS_EVENT_ACCOUNTING_TIMEOUT'
* Accounting request timeout.
* \i 'IPRADIUS_EVENT_ACCOUNTING_CANCELLED'
* Accounting request was cancelled.
* \i 'IPRADIUS_EVENT_ACCOUNTING_REQUEST'
* Sending accounting request.
* \i <request>
* A pointer to an 'Ipradius_request' structure supplied by the application when
* it makes a request using the ipradius_access_request() or
* ipradius_accounting_session_start() routines. For a definition of the
* structure, see ipradius_access_request().
* \i <request_packet>
* A pointer to an 'Ipradius_header' structure for either an access or accounting
* request packet. For a definition of the structure, see
* ipradius_access_request().
* \i <response_packet>
* A pointer to an 'Ipradius_header' structure for a packet received from the
* server. For a definition of the structure, see ipradius_access_request().
* \i <server>
* If the event_callback() routine was called to handle a
* response from a RADIUS server, a pointer to a 'server' structure that
* identifies the server. Otherwise, 'IP_NULL'. For a definition of the 'server'
* structure, see the ipradius_access_request() routine.
* \ie
*
* EXAMPLE
* \cs
* Ip_err ipradius_example_event_callback
* {
* 	Ipcom_auth_cookie   *auth_cookie = request->cookie;
* 	Ip_u8 *attrp;
* 	Ip_u8  attrlen;
*
* 	switch(event)
* 	{
* 	case IPRADIUS_EVENT_ACCESS_ACCEPT :
* 		auth_cookie->retval = IPCOM_SUCCESS;
* 		attrp = ipradius_attr_find(request_packet,
* 			IPRADIUS_ATTR_User_Name, &attrlen);
* 		if(attrp)
* 			ipcom_strncpy(auth_cookie->userinfo.username, (char *)attrp,
* 				attrlen - 2);
* 		auth_cookie->userinfo.userid = 0; /@!!@/
* 		break;
*
* 	case IPRADIUS_EVENT_ACCESS_REJECT :
* 	case IPRADIUS_EVENT_ACCESS_TIMEOUT :
* 	case IPRADIUS_EVENT_ACCESS_CANCELLED :
* 		auth_cookie->retval = IPCOM_ERR_AUTH_FAILED;
* 		break;
*
* 	default:
* 		IP_PANIC();
* 		break;
* 	}
*
* 	/@ Wake up process waiting for auth reply. @/
* 	if(auth_cookie->auth_login_hook)
* 	{
* 		/@ Non-blocking mode. @/
* 		auth_cookie->auth_login_hook(auth_cookie->retval,
* 			&auth_cookie->userinfo,
* 			auth_cookie->auth_login_cookie);
* 		ipcom_free(auth_cookie);
* 	}
* 	else
* 	{
* 		/@ blocking mode. @/
* 		ipcom_sem_post(auth_cookie->sem);
* 	}
*
* 	return IPCOM_SUCCESS;
* }
* \ce
*
* RETURNS: Return value is currently ignored. Always return IPCOM_SUCCESS.
*
* ERRNO:
*
* SEE ALSO: ipradius_accounting_session_start()
*/


/*******************************************************************************
*
* ipradius_attr_find - return a pointer to an attribute of specified type
*
* This routine returns a pointer to the value of a specified attribute
* type. The pointer points to the first data byte after the attribute\'s
* type and length fields. The routine returns 'IP_NULL' if the specified
* attribute type is not found in the packet. If there is more than one
* attribute of the same type in the packet, the pointer points to the initial
* data byte of the first attribute.
*
* Parameters:
* \is
* \i <packet>
* A pointer to the 'Ipradius_header' structure for the packet containing the
* specified type. For a definition of the structure, see
* ipradius_access_request().
* \i <type>
* The attribute type. The available types are listed under Attribute tags in
* 'ipradius.h'.
* \i <len>
* A pointer to a location for receiving the packet\'s attr field.
* \ie
*
* EXAMPLE
* \cs
* void example(Ipradius_header *packet,
* Ipradius_request *request)
* {
*   char *attrp;
*
*   attrp = ipradius_attr_find(packet,
*           IPRADIUS_ATTR_CHAP_Password, &attrlen);
*   if (attrp != 0)
*   {
* 	*attrp++ = IPRADIUS_ATTR_CHAP_Password;
* 	*attrp++ = IPRADIUS_CHAP_LEN + 3;
* 	*attrp++ = request.chap_ident;
*   }
* }
* \ce
*
* RETURNS: A pointer to the first data byte after the attribute\'s type and
* length fields in the packet. The routine returns 'IP_NULL' if the
* specified attribute type is not found in the packet. If there is more
* than one attribute of the same type in the packet, the pointer points to the
* initial data byte of the first attribute.
*
* ERRNO:
*/
IP_PUBLIC void *ipradius_attr_find
(
    Ipradius_header *hdr,
    Ip_u8 type,
    Ip_u8 *len
);


/*******************************************************************************
*
* ipradius_attr_add_u32 - add a 32-bit attribute to a packet
*
* This routine adds a 32-bit attribute to a RADIUS packet. The routine converts
* the attribute from host to network byte order.
*
* Parameters:
* \is
* \i <packet>
* A pointer to an 'Ipradius_header' structure for a RADIUS packet. For a
* definition of the structure, see ipradius_access_request().
* \i <type>
* The attribute type. The types are listed under Attribute tags in 'ipradius.h'.
* \i <data>
* The 32-bit attribute being added.
* \ie
*
* EXAMPLE
* \cs
* Ip_err example(Ipradius_header *packet)
* {
*   return ipradius_attr_add_u32(packet,
*       IPRADIUS_ATTR_Tunnel_Medium_Type,
*       IPRADIUS_TUNNEL_MEDIUM_TYPE_IPV4);
* }
* \ce
*
* RETURNS: Either 'IPCOM_SUCCESS' or an error code (see 'err.h').
*
* ERRNO:
*/
IP_PUBLIC Ip_err ipradius_attr_add_u32
(
    Ipradius_header *hdr,
    Ip_u8 type,
    Ip_u32 data
);


/*******************************************************************************
*
* ipradius_attr_add_array - add a byte-array attribute to a packet
*
* This routine adds a byte-array attribute to a RADIUS packet.
*
* Parameters:
* \is
* \i <packet>
* A pointer to an 'Ipradius_header' structure for a RADIUS packet. For a
* definition of the structure, see ipradius_access_request().
* Make sure you have allocated enough space in the 'Ipradius_header' for
* 2 + the 'len' bytes you are about to add.
* \i <type>
* The attribute type. The types are listed under Attribute tags in 'ipradius.h'.
* \i <data>
* A pointer to the byte-array attribute to add to the packet.
* \i <len>
* The number of bytes in the byte-array.
* \ie
*
* EXAMPLE
* \cs
* Ip_err example(Ipradius_header *packet,
* Ipradius_request *request)
* {
*   Vars *vars;
*   vars = request->cookie;
*
*   return ipradius_attr_add_array(packet,
*       IPRADIUS_ATTR_User_Name, (Ip_u8*)vars->user,
*       strlen(vars->user));
* }
* \ce
*
* RETURNS: Either 'IPCOM_SUCCESS' or an error code (see 'err.h').
*
* ERRNO:
*/
IP_PUBLIC Ip_err ipradius_attr_add_array
(
    Ipradius_header *hdr,
    Ip_u8 type,
    Ip_u8 *data,
    Ip_u8 len
);


/*******************************************************************************
*
* ipradius_attr_get_u32 - get first 32-bit value of specified attribute type
*
* Gets the 32-bit value of the first attribute in <packet> of the requested type
* <type> and store it in host byte order in the variable pointed to by <data>.
*
* Parameters:
* \is
* \i <packet>
* Pointer to RADIUS packet.
* \i <type>
* Type of RADIUS attribute.
* \i <data>
* Location where the 32-bit data will be placed.
* \ie
*
* EXAMPLE
* \cs
* Ip_err example(Ipradius_header *packet)
* {
*   Ip_err retval;
*   Ip_u32 type;
*
*   retval = ipradius_attr_get_u32(packet,
*            IPRADIUS_ATTR_Acct_Status_Type, &type);
*
*   if (retval != IPCOM_SUCCESS)
*   {
* 	return retval;
*   }
*
*   if (type == IPRADIUS_ACCT_Start)
*   {
* 	Vars *vars;
* 	vars = request->cookie;
*
* 	/@ place to add attributes from vars @/
*
* 	ipcom_mem_freep((void **)&vars);
*   }
*
*   return IPCOM_SUCCESS;
* }
* \ce
*
* RETURNS: 'IPCOM_SUCCESS' or one of the following errors:
*  Call completed successfully.
* \is
* \i 'IPCOM_ERR_NOT_FOUND'
*   No attribute of this type.
* \i 'IPCOM_ERR_FAILED'
*   the attribute did not contain an Ip_u32.
* \ie
*
* ERRNO:
*/
IP_PUBLIC Ip_err ipradius_attr_get_u32
(
    Ipradius_header *hdr,
    Ip_u8 type,
    Ip_u32 *data
);


/*******************************************************************************
*
* ipradius_attr_get_array - get data array for specified attribute type
*
* This routine gets array data for the first a specified attribute type. It
* returns a pointer to the array. If there is than one attribute with array data
* for the specified type, the pointer points to the array data for the first
* attribute.
*
* Parameters:
* \is
* \i <packet>
* A pointer to the 'Ipradius_header' structure for the packet containing the
* specified type. For a definition of the structure, see
* ipradius_access_request().
* \i <type>
* The attribute type. The available types are listed under Attribute tags in
* 'ipradius.h'.
* \i <len>
* A pointer to a location for receiving the length of the packet\'s attr field.
* \ie
*
* EXAMPLE
* \cs
* void example(Ipradius_header *packet,
* Ipradius_request_entry *reqent)
* {
*   char *attrp;
*
*   attrp = ipradius_attr_get_array(packet,
*           IPRADIUS_ATTR_CHAP_Password, &attrlen);
*   if (attrp != IP_NULL)
*   {
* 	*attrp++ = IPRADIUS_ATTR_CHAP_Password;
* 	*attrp++ = IPRADIUS_CHAP_LEN + 3;
* 	*attrp++ = reqent->request.chap_ident;
*   }
* }
* \ce
*
* RETURNS: A pointer to the array data. If there is than one attribute with
* array data for the specified type, the pointer points to the array data for
* the first attribute. The routine returns 'IP_NULL' if the specified attribute
* type is not found in the packet.
*
* ERRNO:
*/
IP_PUBLIC Ip_u8 *ipradius_attr_get_array
(
    Ipradius_header *hdr,
    Ip_u8 type,
    Ip_u8 *len
);


/*******************************************************************************
*
* ipradius_attr_get_next - return a pointer to the next attribute
*
* Given a pointer to the start of the current attribute, this routine gets a
* pointer to the value of the next attribute in the packet pointed to by
* <packet>.
*
* Parameters:
* \is
* \i <packet>
* A pointer to the 'Ipradius_header' structure for the packet containing the
* attribute. For a definition of the structure, see ipradius_access_request().
* \i <attr>
* A pointer to the start of current attribute or 'IP_NULL', if there is no
* current attribute.
* \ie
*
* EXAMPLE
* \cs
* void example(Ipradius_header *packet)
* {
*   static char buf[1024];
*   int len;
*   Ip_u8 *data;
*
*   len = sprintf(buf, "Attributes: \n");
*
*   /@ Print attributes. @/
*   for(data = ipradius_attr_get_next(packet, IP_NULL);
* 	  data && len < 1000;
* 	  data = ipradius_attr_get_next(packet, data))
* 	{
* 	  len += sprintf(buf + len, "attr #%3d   len %3d"LF,
*              data[0], data[1]);
* 	}
*
*   printf(buf);
* }
* \ce
*
* RETURNS: A pointer to the start of next attribute. If there is no attribute or
* if the current attribute is the last attribute in the packet, 'IP_NULL'
*
* ERRNO:
*/
IP_PUBLIC void *ipradius_attr_get_next
(
    Ipradius_header *hdr,
    Ip_u8 *attr
);


/*******************************************************************************
*
* ipradius_attr_change_u32 - change the value of a 32-bit attribute
*
* This routine changes the value of a 32-bit attribute contained in a
* RADIUS packet.
*
* Parameters:
* \is
* \i <packet>
* A pointer to the 'Ipradius_header' structure for the packet containing the
* value that is to be changed. For a definition of the structure, see
* ipradius_access_request().
* \i <type>
* The attribute type whose value is to be changed. The available types are
* listed under Attribute tags in 'ipradius.h'.
* \i <data>
* The 32-bit attribute value that is replacing the old value.
* \ie
*
* EXAMPLE
* \cs
* void example(Ipradius_header *packet)
* {
*   /@ change this attributes if present, else add it @/
*   if (!ipradius_attr_change_u32(packet,
*       IPRADIUS_ATTR_NAS_IP_Address, client_ip_n))
* 	ipradius_attr_add_u32(packet,
*         IPRADIUS_ATTR_NAS_IP_Address, client_ip_n);
* }
* \ce
*
* RETURNS: Either 'IPCOM_SUCCESS' or the following error:
* \is
* \i 'IPCOM_ERR_NOT_FOUND'
*  Attribute of type type not found.
* \ie
*
* ERRNO:
*/
IP_PUBLIC Ip_err ipradius_attr_change_u32
(
    Ipradius_header *hdr,
    Ip_u8 type,
    Ip_u32 data
);


/*
 *===========================================================================
 *                    ipradius_attr_verify_message_auth
 *===========================================================================
 * Description: Verify message authenticator attribute.
 * Parameters: pkt - the radius packet
 *             secret - buffer with the shared secret
 *             secret_len - lenght of shared secret buffer
 * Returns: IPCOM_SUCCESS or IPCOM_ERR_xx from ipcom_err.h
 *
 */
IP_PUBLIC Ip_err
ipradius_attr_verify_message_auth(Ipradius_header *pkt, Ip_u8 *secret, Ip_u32 secret_len);


/*******************************************************************************
*
* ipradius_access_request_pkt_malloc - allocate an access request packet
*
* Allocate and initialize a RADIUS access request packet.
*
* After allocating a packet with ipradius_access_request_pkt_malloc(), add
* access request attributes using ipradius_attr_add_array() or
* ipradius_attr_add_u32() and then send an access request by calling the
* ipradius_access_request() routine.
*
* Parameters:
*
* None.
*
* EXAMPLE
* \cs
* int example(char *username)
* {
*   Ipradius_header  *packet;
*
*   packet = ipradius_access_request_pkt_malloc();
*   if (packet == IP_NULL)
*   {
* 	ipcom_fprintf(ip_stderr,
*         "<radiusc> : error - out of heap memory'"LF);
* 	return -1;
*   }
*
*   /@**** Add username attribute ****@/
*   ipradius_attr_add_array(packet, IPRADIUS_ATTR_User_Name,
*       (Ip_u8*)username, strlen(username));
*
*   /@ next prepare a request structure and send the packet
*    * (see complete example in ipradius_access_request())
*    @/
* 	  ETC ETC
*
*    return 0;
* }
* \ce
*
* RETURNS: A pointer to an 'Ipradius_header' structure, on success; 'IP_NULL' on
* failure. For a definition of the 'Ipradius_header' structure, see the
* ipradius_access_request() routine.
*
* ERRNO:
*
* SEE ALSO: ipradius_access_request_pkt_free()
*/
IP_PUBLIC Ipradius_header *ipradius_access_request_pkt_malloc
(
    void
);

/********************************************************************************
*
* ipradius_access_request_pkt_malloc_with_len - allocate an access request packet
*
* Allocate and initialize a RADIUS access request packet.
*
* After allocating a packet with ipradius_access_request_pkt_malloc_with_len(),
* add access request attributes using ipradius_attr_add_array() or
* ipradius_attr_add_u32() and then send an access request by calling the
* ipradius_access_request() routine.
*
* Parameters:
*
* \is
* \i <length>
* Length of the access request packet.
* \ie
*
* EXAMPLE
* \cs
* int example(char *username)
* {
*   Ipradius_header  *packet;
*
*   packet = ipradius_access_request_pkt_malloc_with_len(1024);
*   if (packet == IP_NULL)
*   {
* 	ipcom_fprintf(ip_stderr,
*         "<radiusc> : error - out of heap memory'"LF);
* 	return -1;
*   }
*
*   /@**** Add username attribute ****@/
*   ipradius_attr_add_array(packet, IPRADIUS_ATTR_User_Name,
*       (Ip_u8*)username, strlen(username));
*
*   /@ next prepare a request structure and send the packet
*    * (see complete example in ipradius_access_request())
*    @/
* 	  ETC ETC
*
*    return 0;
* }
* \ce
*
* RETURNS: A pointer to an 'Ipradius_header' structure, on success; 'IP_NULL' on
* failure. For a definition of the 'Ipradius_header' structure, see the
* ipradius_access_request() routine.
*
* ERRNO:
*
* SEE ALSO: ipradius_access_request_pkt_free()
*/
IP_PUBLIC Ipradius_header *ipradius_access_request_pkt_malloc_with_len
(
	Ip_u16 length
);

/*******************************************************************************
*
* ipradius_access_request_pkt_free - free unused access request packet
*
* This routine frees a RADIUS access request packet that did not get passed to
* the ipradius_access_request() routine.
*
* Parameter:
* \is
* \i <Packet>
* A pointer to the 'Ipradius_header' structure for the packet that is to be
* freed. For the definition of the structure, see ipradius_access_request().
* \ie
*
* EXAMPLE
* \cs
* int example(char *username)
* {
*   Ipradius_header  *packet;
*
*   packet = ipradius_access_request_pkt_malloc();
*   if (packet == IP_NULL)
*   {
* 	ipcom_fprintf(ip_stderr,
*         "<radiusc> : error - out of heap memory'"LF);
* 	return -1;
*   }
* /@ Changed my mind, release packet without sending a RADIUS access request @/
* (void)ipradius_access_request_pkt_free(packet);
*
*    return 0;
* }
* \ce
*
* RETURNS: 'IPCOM_SUCCESS' or the following error:
* \is
* \i 'IPCOM_ERR_INVALID_ARG'
* Invalid packet pointer.
* \ie
*
* ERRNO:
*
* SEE ALSO: ipradius_access_request_pkt_malloc()
*/
IP_PUBLIC Ip_err ipradius_access_request_pkt_free
(
    Ipradius_header *packet
);


/*******************************************************************************
*
* ipradius_access_request - send access request packet to server
*
* Send an access request to the RADIUS server. Prior to calling this function,
* ipradius_access_request_pkt_malloc() must be called to allocate a RADIUS
* packet.
*
* Applications must add any request attributes prior to calling this function
* using ipradius_attr_add_array() or ipradius_attr_add_u32().
*
* The ipradius_access_request() function always consumes the RADIUS access
* request packet pointed to by <packet>, hence the user must never try to free
* the packet if an error is returned.
*
* Parameters:
* \is
* \i <packet>
* A pointer to an 'Ipradius_header' structure for a RADIUS access request
* packet. The structure is defined as follows:
* \cs
* typedef struct Ipradius_header_struct
* {
*     /@ RADIUS packet header. @/
*     Ip_u8 code;
*     Ip_u8 id;
*     Ip_u16 length;
*     Ip_u8 auth[16];
*
*     Ip_u8 attr[4];     /@ variable number/length attribute field. @/
* }
* Ipradius_header;
* \ce
*
* \i <request>
* A pointer to an 'Ipradius_request' structure, which must be filled in by the
* application. The structure is copied by the RADIUS client and passed in
* the event callback in the. The 'Ipradius_request' structure contains the
* following fields:
*
* \is
* \i 'cookie'
* A 32-bit handle that the application can take advantage of, since it can be
* used to carry application information to callbacks.
* \i 'unique'
* A 32-bit value used to uniquely identify an outstanding request. It is the
* responsibility of the application to make sure this value is unique per user.
* \i 'status'
* Set by the RADIUS client to inform the application of the status of the
* request response.
* \i 'pwd_type, pwd, pwd_len, type, chap_ident'
* These fields are set by the  application to inform the RADIUS client of the
* password and its length and type. The password types available for the
* 'pwd_types' parameter are:
*
* 'IPRADIUS_No_Password'
*
* 'IPRADIUS_PAP_Password'
*
* 'IPRADIUS_CHAP_Password'
* \i 'fd'
* The socket descriptor of a bound IPv4 UDP socket that is used to send RADIUS
* IPv4 request packets to the server. If IPv6 is being used, set this parameter
* to 'IP_INVALID_SOCKET.'
* \i 'fd6'
* the Socket descriptor of a bound IPv6 UDP socket that is used to send RADIUS
* IPv6 request packets to the server. If IPv4 is being used, set this parameter
* to 'IP_INVALID_SOCKET.'
* \i 'event_callback'
* A function pointer to a user-implemented callback function for handling events
* resulting from a request (for example: server reply packets, timeouts on
* access and accounting requests, cancelled requests).
* \i 'num_servers'
* The number of servers in the 'server_list' parameter. If it does not matter what
* servers should be tried, the application must set 'num_servers' to 0.
* \i 'server_list'
* An array of 'server_list' structures containing the specific servers that the
* access request can be sent to. The definition of the 'server_list' structure is:
* \ie
* \ie
* \cs
* typedef struct Ipradius_server_list_struct
* {
*     Ip_u32     index;                    /@ Server index. @/
*
*     union Ip_sockaddr_union server_addr; /@ Union of server IPv4 and IPv6
*                                           *socket addresses @/
*
*     Ip_u16     server_type;              /@ IPRADIUS_ACCESS_SERVER,
*                                           * IPRADIUS_ACCOUNTING_SERVER,
*                                           * Or IPRADIUS_FULL_SERVER @/
*
*     Ip_u16     pollnum;                  /@ Number times to poll a server
*                                           * before trying the next one. @/
*
*     Ip_u16     pollsec;                  /@ Seconds to wait for a reply
*                                           *from the RADIUS server. @/
* }
* Ipradius_server_list;
* \ce
*
* \is
* \i <errattr>
* In the event of an attribute error, a pointer to an integer indicating the
* last attribute type inspected or indicating the attribute type that caused
* the error. If there is no error, the integer value is '0'.
* \ie
*
* EXAMPLE
* \cs
* int example(Vars *vars)
* {
*   Ip_err retval;
*   Ipradius_request  request;
*   Ipradius_header  *packet;
*   Ip_u8 errattr;
*
*   if(!*vars->user)
*   {
* 	fprintf(stderr,
*         "<radiusc> : missing modifier '-user'"LF);
* 	return -1;
*   }
*
*   packet = ipradius_access_request_pkt_malloc();
*   if (packet == IP_NULL)
*   {
* 	fprintf(stderr,
*         "<radiusc> : error - out of heap memory'"LF);
* 	return -1;
*   }
*
*   /@ Add user attributes here! @/
*   ipradius_attr_add_array(packet, IPRADIUS_ATTR_User_Name,
*       (Ip_u8*)vars->user, strlen(vars->user));
*
*   if (vars->pwd_type == IPRADIUS_CHAP_Password)
*   {
* 	ipradius_attr_add_array(packet,
*         IPRADIUS_ATTR_CHAP_Challenge,
*         (Ip_u8*)vars->challenge, 16);
*   }
*
*   ipradius_attr_add_u32(packet,
*       IPRADIUS_ATTR_Tunnel_Medium_Type,
*       IPRADIUS_TUNNEL_MEDIUM_TYPE_IPV4);
*
*   /@ Fill in request structure and send access request. @/
*   request.unique = vars->id;
*   request.pwd_type = vars->pwd_type;
*   strcpy(request.pwd, vars->pwd);
*   request.pwd_len = strlen(request.pwd);
*   request.chap_ident = vars->chap_ident;
*   request.fd = my_radius_ipv4_udp_fd;
*   request.fd6 = IP_INVALID_SOCKET; /@ I only want IPv4. @/
*   request.event_callbackt = my_event_callback_function;
*   request.num_servers = 0;
*
*   retval = ipradius_access_request(packet, &request,
*                                    &errattr);
*   if (retval != IPCOM_SUCCESS)
*   {
* 	fprintf(stderr,
*         "radius access request failed : '%s' (attr=%d)"LF,
* 		   ipradius_errname(retval), errattr);
* 	return -1;
*   }
*   else
* 	fprintf(stdout, "ok"LF);
*
*   return 0;
* }
* \ce
*
* RETURNS: 'IPCOM_SUCCESS' or one of the following errors:
* \is
* \i 'IPCOM_ERR_PENDING'
* An access request is required to have a unique identifier (see the <unique>
* parameter), but an access request with the same identifier is already pending.
* \i 'IPCOM_ERR_INVALID_ARG'
*  Invalid function argument.
* \i 'IPRADIUS_ERR_INVAL_PWD_LEN'
*  Invalid password length.
* \i 'IPRADIUS_ERR_INVAL_PWD_TYPE'
*  Invalid password type.
* \i 'IPRADIUS_ERR_MISSING_CHAP_ATTR'
*  Missing CHAP attribute.
* \i 'IPCOM_ERR_NO_MEMORY'
*  Not enough memory to create the request.
* \i 'IPCOM_ERR_IPTIME_NOT_OPENED'
*  The IPCOM timer utility has not been started.
* \ie
*
* ERRNO:
*
* SEE ALSO: event_callback()
*/
IP_PUBLIC Ip_err ipradius_access_request
(
    Ipradius_header *packet,
    Ipradius_request *request,
    Ip_u8 *errattr
);


/*******************************************************************************
*
* ipradius_accounting_session_start - start app accounting session on client
*
* This  routine starts a new accounting session and sends the initial RADIUS
* accounting request to the RADIUS server.
*
* If the server does not acknowledge the accounting session after the configured
* number of retries, the session is stopped and the application is notified of
* the event through the event callback in the <request> parameter. In the callback,
* the <event> parameter is set to 'IPRADIUS_EVENT_ACCOUNTING_TIMEOUT' and the
* <response_packet> and <server> parameters are set to 'IP_NULL':
* \cs
* request->event_callback(IPRADIUS_EVENT_ACCOUNTING_TIMEOUT, <request>,
* equest_packet, IP_NULL, IP_NULL)
* \ce
*
* The event callback is called for each accounting response packet. As a result,
* for interim accounting, the event callback gets called repeatedly until the
* session is stopped by calling ipradius_accounting_session_stop().
*
* The default behavior of the RADIUS client is to send interim accounting
* requests as well as the accounting stop request to the server that initially
* replied to the accounting start request. If necessary, this behavior can be
* disabled through the ipradius_ctrl() routine.
*
* Parameters:
* \is
* \i <request>
* A pointer to an 'Ipradius_request' structure, which must be filled in by the
* application. The structure is copied by the RADIUS client and passed in the
* event callback. For the fields in the 'Ipradius_request' structure, see
* ipradius_access_request().
* \i <acct_interim_interval>
* The number of seconds between each interim accounting update to the RADIUS
* server. If this parameter is set to '0', no interim accounting is used and
* only an initial accounting request is sent.
* \ie
*
* EXAMPLE
* \cs
* Int example(Vars *vars)
* {
*   Ip_err retval;
*   Ipradius_request  request;
*
*   request.cookie = vars;
*   request.unique = vars->id;
*   request.pwd_type = vars->pwd_type;
*   strcpy(request.pwd, vars->pwd);
*   request.pwd_len = strlen(request.pwd);
*   request.chap_ident = vars->chap_ident;
*   request.num_servers = 0;
*
*   retval = ipradius_accounting_session_start(&request, 0);
*   if (retval != IPCOM_SUCCESS)
*   {
* 	fprintf(stderr, "radius accounting start failed"LF);
* 	ipcom_mem_freep((void **)&vars_handle);
* 	return -1;
*   }
* }
* \ce
*
* RETURNS: 'IPCOM_SUCCESS' or one of the following errors:
* \is
* \i 'IPCOM_ERR_PENDING'
* An accounting session is required to have a unique identifier (see the
* <unique> field of the <request> parameter), but there is another accounting
* session that has the same identifier.
* \i 'IPCOM_ERR_NO_MEMORY'
*  Not enough memory to create the request.
* \i 'IPRADIUS_ERR_INVAL_INTERIM_ACCT_INTERVAL'
*  The accounting interval was outside the configured limits, see iradius_config.h
* \i 'IPCOM_ERR_IPTIME_NOT_OPENED'
*  The IPCOM timer utility was not active.
* \ie
*
* ERRNO:
*
* SEE ALSO: ipradius_accounting_session_stop(), and ipradius_access_request()
*/
IP_PUBLIC Ip_err ipradius_accounting_session_start
(
    Ipradius_request *request,
    Ip_u32 acct_interim_interval
);


/*******************************************************************************
*
* ipradius_accounting_session_stop - stop an accounting session on client
*
* This routine sends an accounting-session stop request to a RADIUS server and
* stops the session on the client when the client receives an acknowledgment of
* the request from the server. If no acknowledgement is received within a
* configured number of retries by the client, the client stops the session and
* notifies the application of this through the event callback in the <request>
* parameter. In the callback, the <event> parameter is set to
* 'IPRADIUS_EVENT_ACCOUNTING_TIMEOUT' and the <response_packet> and <server>
* parameters are set to 'IP_NULL':
* \cs
* request->event_callback(IPRADIUS_EVENT_ACCOUNTING_TIMEOUT, <request>,
* equest_packet, IP_NULL, IP_NULL)
* \ce
*
* If the server responds before the timeout, the client stops the session and
* notifies the application of the response through the event callback in the
* <request> parameter, with the callback\'s <event> parameter set to
* 'IPRADIUS_EVENT_ACCOUNTING_RESPONSE'.
*
* The default behavior of the RADIUS client is to send interim accounting
* requests as well as the accounting stop request to the server that initially
* replied to the accounting start request. If necessary, this behavior can be
* disabled through the ipradius_ctrl() routine.
*
* Parameters:
*
* The 32-bit value unique, which was specified in the request structure upon
* starting the session, is used to identify the accounting session to stop. The
* terminate_cause value is passed on to the RADIUS server in the
* 'IPRADIUS_ATTR_Acct_Terminate_Cause' attribute.
* \is
* \i <unique>
* The session ID, as initially given in ipradius_accounting_session_start() to
* start the session.
* \i <terminate_cause>
* The reason for terminating the session.
* \ie
*
* EXAMPLE
* \cs
* int example(void)
* {
*   Ip_err retval;
*
*   retval = ipradius_accounting_session_stop(vars->id,
*            1 /@ User Request @/);
*   if (retval != IPCOM_SUCCESS)
*   {
* 	fprintf(stderr, "radius accounting stop failed"LF);
* 	  return -1;
*   }
*   return 0;
* }
* \ce
*
* RETURNS: 'IPCOM_SUCCESS' or one of the following errors:
* \is
* \i 'IPRADIUS_ERR_NO_SERVER'
*  No server found to send the request to.
* \i 'IPRADIUS_ERR_NO_SESSION'
* No session with the identifier specified in the <unique> parameter was found.
* \i 'IPCOM_ERR_NO_MEMORY'
*  Not enough memory to create the request.
* \i 'IPCOM_ERR_IPTIME_NOT_OPENED'
*  The IPCOM timer utility has not been started.
* \ie
*
* ERRNO:
*/
IP_PUBLIC Ip_err ipradius_accounting_session_stop
(
    Ip_u32 unique,
    Ip_u32 terminate_cause
);


/*
 *===========================================================================
 *                    ipradius_accounting_session_update
 *===========================================================================
 * Description:  Force an accounting session update, i.e. make an interim
 *               accounting session send a RADIUS accounting update message.
 * Parameters:   unique - 32-bit session identifier.
 * Returns:      IPCOM_SUCCESS or IPCOM_ERR_xx from ipcom_err.h
 *
 */
IP_PUBLIC Ip_err
ipradius_accounting_session_update(Ip_u32 unique);


/*******************************************************************************
*
* ipradius_init - initialize global RADIUS data
*
* Initialize global RADIUS data. To start a RADIUS client, call ipradius_init()
* first, then call ipradius_open().
*
* Parameters:
*
* None.
*
* EXAMPLE
* \cs
* void example(void)
* {
*   ipradius_init();
* }
* \ce
*
* RETURNS: N/A
*
* ERRNO:
*/
IP_PUBLIC void ipradius_init
(
    void
);


/*******************************************************************************
*
* ipradius_exit - exit the RADIUS client
*
* This routine exits the RADIUS client. Before calling ipradius_exit(), close
* the client by calling ipradius_close(). [* Following sentence is not
* clear--either: no cleanup operations are defined for closing and exiting OR:
* cleanup operations are performed, but there is no definition of which
* operations.] It is undefined which cleanups are performed by the RADIUS client
* during these calls.
*
* Parameters:
*
* None
*
* EXAMPLE
* \cs
* void example(void)
* {
*   ipradius_exit(void);
* }
* \ce
*
* RETURNS: N/A
*
* ERRNO:
*/
IP_PUBLIC void ipradius_exit
(
    void
);


/*******************************************************************************
*
* ipradius_open - open and configure the RADIUS client
*
* Open and configure the RADIUS client. To start a RADIUS client, call
* ipradius_init() first, then call ipradius_open().
*
* Parameter:
* \is
* \i <conf>
* A pointer to an 'Ipradius_open' structure. The definition of the structure is:
* \ie
* \cs
* typedef struct Ipradius_open_struct
* {
*     /@ Identifier of RADIUS client @/
*     char      ipradius_NAS_Identifier[IPRADIUS_MAX_NAS_IDENTIFIER_SIZE];
*     Ip_u32    ipradius_NAS_Identifier_size;
*
*     /@ user config, attribute space @/
*     Ip_u32    access_request_attribute_size;
*     Ip_u32    accounting_request_attribute_size;
*
*     Ip_tag    conf[1]; /@ None available, included for future compability @/
* }
* Ipradius_open;
*
* \ce
*
* EXAMPLE
* \cs
* Int example(void)
* {
*   Ipradius_open conf;
*   Ip_socklen_t len;
*   struct sockaddr_in  addr;
*
*   /@ open IPRADIUS @/
*   strcpy(conf.ipradius_NAS_Identifier,"IP NAS");
*   conf.ipradius_NAS_Identifier_size =
*       strlen(conf.ipradius_NAS_Identifier);
*
*   conf.access_request_attribute_size = 500;
*   conf.accounting_request_attribute_size = 500;
*
*   conf.conf[0] = IPTAG_END;
*
*   if (ipradius_open(&conf) != IPCOM_SUCCESS)
*   {
* 	printf(stderr, "failed to open IPRADIUS");
* 	return -1;
*   }
*
*   return 0;
* }
* \ce
*
* RETURNS: 'IPCOM_SUCCESS' or one of the following errors:
* \is
* \i 'IPCOM_ERR_ALREADY_OPEN'
*  ipradius_open() should only be called once.
* \i 'IPCOM_ERR_UNSUPPORTED_TAG'
*   No optional configuration is in use and 'conf[0]' must be set to
* 'IPTAG_END'.
* \i 'IPCOM_ERR_IPTIME_NOT_OPENED'
*  The IPCOM timer utility has not been started.
* \ie
*
* ERRNO:
*
* SEE ALSO: ipradius_close()
*/
IP_PUBLIC Ip_err ipradius_open
(
    Ipradius_open *config
);


/*******************************************************************************
*
* ipradius_close - close the RADIUS client
*
* The routine closes the RADIUS client.
*
* [* Following sentence is not clear--either: no cleanup operations are defined
* for closing and exiting OR: cleanup operations are performed, but there is no
* definition of which operations.] It is undefined which cleanups are performed
* by the RADIUS client during these calls.
*
* Parameters:
*
* None.
*
* EXAMPLE
* \cs
* void example(void)
* {
*    ipradius_close();
* }
* \ce
*
* RETURNS: Either 'IPCOM_SUCCESS' or 'IPCOM_ERR_ALREADY_CLOSED'.
*
* ERRNO:
*/
IP_PUBLIC Ip_err ipradius_close
(
    void
);


/*******************************************************************************
*
* ipradius_ctrl - get or set global control tags
*
* Get or set system control tags for global RADIUS information. Parameter:
* \is
* \i <ctrltags>
* A pointer to a tag array, terminated by 'IPTAG_END', containing the control
* tags of interest and their values. The following control tags are available:
*
* \is
* \i 'IPRADIUS_CTRLT_SET_SAME_ACCT_SERVER'
* Specifies whether all Accounting-Requests of an accounting session should be
* sent to the same accounting server (see ipradius_accounting_session_start()).
* Set 'IPRADIUS_CTRLT_SET_SAME_ACCT_SERVER' as follows:
*
* 'IP_TRUE'     The accounting server may not be changed during a session
* (default).
*
* 'IP_FALSE'     Multiple accounting servers can be accessed during a single
* session.
* \ie
* \i 'IPRADIUS_CTRLT_GET_NEXT_SERVER'
* Get the next server entry, based on the tag value entered for
* 'IPRADIUS_CTRLT_GET_NEXT_SERVER'. The tag value is always one less
* than the index of the server entry that is retrieved. For example, to get the
* first server entry, set the tag value to '0'; to get the second server entry,
* set the tag value to '1'.
* \i 'IPRADIUS_CTRLT_GET_AuthInvalidServerAddresses'
* Get RFC2618 MIB variable 'radiusAuthClientInvalidServerAddresses'.
* \i 'IPRADIUS_CTRLT_GET_AccInvalidServerAddresses'
* Get RFC2620 MIB variable 'radiusAccClientInvalidServerAddresses'.
* \i 'IPRADIUS_CTRLT_GET_AuthIdentifier'
* Get RFC2618 MIB variable 'radiusAuthClientIdentifier'.
* \i 'IPRADIUS_CTRLT_GET_AccIdentifier'
* Get RFC2620 MIB variable 'radiusAccClientIdentifier'.
* \ie
*
* EXAMPLE
* \cs
* Ip_err example(void)
* {
*   Ip_tag  ctrltag[3];
*
*   ctrltag[0] = IPRADIUS_CTRLT_SET_SAME_ACCT_SERVER;
*   ctrltag[1] = IP_FALSE;
*   ctrltag[2] = IPTAG_END;
*
*   return ipradius_ctrl(ctrltag);
* }
* \ce
*
* RETURNS: 'IPCOM_SUCCESS' or one of the following errors:
* \is
* \i 'IPRADIUS_ERR_UNSUPPORTED_TAG'
*   The global configuration tag array contained an unknown tag.
* \i 'IPCOM_ERR_INVALID_TAG_VALUE'
*  Invalid tag value.
* \i 'IPCOM_ERR_NOT_OPENED'
*  Radius client not opened.
* \ie
*
* ERRNO:
*/
IP_PUBLIC Ip_err ipradius_ctrl
(
    Ip_tag *ctrltags
);


/* ctrl tags: */

/* Used to specify whether the same accounting server must be used for
 * an accounting session.
 * Values:
 * IP_TRUE = accounting server may not be changed for one session (default)
 * IP_FALSE = multiple accounting servers may be accessed for a single session
 */
#define IPRADIUS_CTRLT_SET_SAME_ACCT_SERVER         0xff060001

/* Get first/next lexicographic RADIUS server entry (index > tag value).
 * The tag value should be set to 0 for the first server get. Setting the tag
 * value to a server index results in the retrieval of the next lexicographic
 * server entry or 0 if none available, i.e. 0 is not a valid server index.
 */
#define IPRADIUS_CTRLT_GET_NEXT_SERVER                  0xff060002

/* Get RFC2618 MIB variable radiusAuthClientInvalidServerAddresses */
#define IPRADIUS_CTRLT_GET_AuthInvalidServerAddresses   0xff060003

/* Get RFC2618 MIB variable radiusAuthClientIdentifier */
#define IPRADIUS_CTRLT_GET_AuthIdentifier               0xff060004

/* Get RFC2620 MIB variable radiusAccClientInvalidServerAddresses */
#define IPRADIUS_CTRLT_GET_AccInvalidServerAddresses    0xff060005

/* Get RFC2620 MIB variable radiusAccClientIdentifier */
#define IPRADIUS_CTRLT_GET_AccIdentifier                0xff060006


/*******************************************************************************
*
* ipradius_server_add - add a server to the client list of RADIUS servers
*
* This routine adds a server to the RADIUS client\'s set of available servers.
* You can add the same RADIUS server more than once with separate calls to
* ipradius_server_add(). If an identical server is added, a reference counter
* will be increased. To remove a server, call ipradius_server_remove().
*
* Parameters:
* \is
* \i <server>
* A pointer to an 'Ipradius_server' structure containing information about the
* server to be added. The definition of the structure is:
* \ie
* \cs
* typedef struct Ipradius_server_struct
* {
*     /@ Unique index for the server. Set to 0, if you want the system to
*      * assign it @/
*     Ip_u32 index;
*
*     /@ Server IPv4/v6 socket address union. @/
*     union Ip_sockaddr_union server_addr;
*
*     Ip_u16 server_type; /@ IPRADIUS_ACCESS_SERVER,
*                          * IPRADIUS_ACCOUNTING_SERVER,
*                          * or IPRADIUS_FULL_SERVER. @/
*
*     Ip_u16 pollnum;     /@ Number of times to poll the server before trying
*                          * the next one. @/
*
*     Ip_u16 pollsec;	     /@ Seconds to wait for a reply from the server. @/
*
*     /@ secret to be shared between the RADIUS client and the server @/
*     Ip_u8 shared_secret[IPRADIUS_MAX_SECRET_SIZE];
*
*     /@ length of the shared secret @/
*     Ip_u32 shared_secret_len;
*
*     Ip_tag conf[1];     /@ None available, included for future compability @/
* }
* Ipradius_server;
* \ce
*
* EXAMPLE
* \cs
* void example(void)
* {
*   Ipradius_server server;
*
* server.server_addr.sin.sin_family = IP_AF_INET;
* server.server_addr.sin.sin_len = sizeof(struct Ip_sockaddr_in);
* server.server_addr.sin.sin_port = ip_htons(1812);
* server.server_addr.sin.sin_addr.s_addr = read_server_ip();
*
*   server.server_type = IPRADIUS_ACCESS_SERVER;
*
*   server.pollnum = 3;     /@ Times to poll server
*                              before trying next one. @/
*   server.pollsec = 3;     /@ Seconds to wait for
*                              a reply from server. @/
*
*   /@ secret between client and server @/
*   strcpy(server.shared_secret,"BigSecret");
*   server.shared_secret_len = 9;
*
*   /@ Add the server. @/
*   retval = ipradius_server_add(&server);
*   if (retval != IPCOM_SUCCESS)
*   {
* 	fprintf(stderr,
*         "radiusc() :: ipradius_server_add() failed"LF);
*   }
* }
* \ce
*
* RETURNS: 'IPCOM_SUCCESS' or one of the following errors:
* \is
* \i 'IPRADIUS_ERR_SECRET_TOO_SHORT'
*  Password too short.
* \i 'IPRADIUS_ERR_SECRET_TOO_LONG'
*  Password to long.
* \i 'IPCOM_ERR_NO_MEMORY'
*  Not enough memory to create entry.
* \i 'IPCOM_ERR_NOT_OPENED'
*  Radius client not opened.
* \ie
*
* ERRNO:
*/
IP_PUBLIC Ip_err ipradius_server_add
(
    Ipradius_server *server
);


/*******************************************************************************
*
* ipradius_server_remove - remove a server from the RADIUS server list
*
* This routine removes a server from the list of servers maintained by the
* client. If the same server has been added more than once, you need to make
* separate calls to ipradius_server_remove() for each addition of the server.
*
* Parameters:
* \is
* \i <server>
* A pointer to an 'Ipradius_server' structure identifying the server to remove.
* \ie
*
* 'EXAMPLE'
* \cs
* void example(void)
* {
* 		Ipradius_server server;
*
* server.server_addr.sin.sin_family = IP_AF_INET;
* server.server_addr.sin.sin_len = sizeof(struct Ip_sockaddr_in);
* server.server_addr.sin.sin_port = ip_htons(1812);
* server.server_addr.sin.sin_addr.s_addr = read_server_ip();
*
* server.server_type = IPRADIUS_ACCESS_SERVER;
* server.pollnum = 3;
* server.pollsec = 3
*
* ipradius_server_remove(&server);
* }
* \ce
*
* RETURNS: 'IPCOM_SUCCESS' or one of the following errors:
* \is
* \i 'IPCOM_ERR_NOT_FOUND'
*  Server was not found in server list.
* \i 'IPCOM_ERR_NOT_OPENED'
*  Radius client not opened.
* \ie
*
* ERRNO:
*/
IP_PUBLIC Ip_err ipradius_server_remove
(
    Ipradius_server *server
);


/*******************************************************************************
*
* ipradius_server_ctrl - get or set server-specific control tags
*
* Get or set server-specific  information. The server is identified by its
* socket address structure ('server-\>server_addr') or its index
* ('server-\>index').
* \is
* \i <ctrltags>
* A pointer to a tag array, terminated by 'IPTAG_END', containing the control
* tags of interest and their values. The following control tags are available:
* \ie
*
* Parameters:
* \is
* \i <server>
* A pointer to the 'Ipradius_server' structure for the RADIUS server.
* \i <ctrltags>
* A pointer to a tag array, terminated by 'IPTAG_END', containing the control
* tags of interest and their values. The following control tags are available:
* \i 'IPRADIUS_SCTRLT_GET_AuthAccessRequests'
* Get RFC2618 MIB variable 'radiusAuthClientAccessRequests'.
* \i 'IPRADIUS_SCTRLT_GET_AuthRoundTripTime'
* Get RFC2618 MIB variable 'radiusAuthClientRoundTripTime'.
* \i 'IPRADIUS_SCTRLT_GET_AccRoundTripTime'
* Get RFC2620 MIB variable 'radiusAccClientRoundTripTime'.
* \i 'IPRADIUS_SCTRLT_GET_AuthServerAddress'
* Get RFC2618 MIB variable 'radiusAuthClientServerAddress'.
* \i 'IPRADIUS_SCTRLT_GET_AccServerAddress'
* Get RFC2620 MIB variable 'radiusAccClientServerAddress'.
* \i 'IPRADIUS_SCTRLT_GET_AuthServerPortNumber'
* Get RFC2618 MIB variable 'radiusAuthClientServerPortNumber'.
* \i 'IPRADIUS_SCTRLT_GET_AccServerPortNumber'
* Get RFC2620 MIB variable 'radiusAccClientServerPortNumber'.
* \i 'IPRADIUS_SCTRLT_GET_AccRequests'
* Get RFC2620 MIB variable 'radiusAccClientRequests'.
* \i 'IPRADIUS_SCTRLT_GET_AuthAccessRetransmissions'
* Get RFC2618 MIB variable 'radiusAuthClientAccessRetransmissions'.
* \i 'IPRADIUS_SCTRLT_GET_AccRetransmissions'
* Get RFC2620 MIB variable 'radiusAccClientRetransmissions'.
* \i 'IPRADIUS_SCTRLT_GET_AuthAccessAccepts'
* Get RFC2618 MIB variable 'radiusAuthClientAccessAccepts'.
* \i 'IPRADIUS_SCTRLT_GET_AccResponses'
* Get RFC2620 MIB variable 'radiusAccClientResponses'.
* \i 'IPRADIUS_SCTRLT_GET_AuthAccessRejects'
* Get RFC2618 MIB variable 'radiusAuthClientAccessRejects'.
* \i 'IPRADIUS_SCTRLT_GET_AuthAccessChallenges'
* Get RFC2618 MIB variable 'radiusAuthClientAccessChallenges'.
* \i 'IPRADIUS_SCTRLT_GET_AuthMalformedAccessResponses'
* Get RFC2618 MIB variable 'radiusAuthClientMalformedAccessResponses'.
* \i 'IPRADIUS_SCTRLT_GET_AccMalformedAccessResponses'
* Get RFC2620 MIB variable 'radiusAccClientMalformedAccessResponses'.
* \i 'IPRADIUS_SCTRLT_GET_AuthBadAuthenticators'
* Get RFC2618 MIB variable 'radiusAuthClientBadAuthenticators'.
* \i 'IPRADIUS_SCTRLT_GET_AccBadAuthenticators'
* Get RFC2620 MIB variable 'radiusAccClientBadAuthenticators'.
* \i 'IPRADIUS_SCTRLT_GET_AuthPendingRequests'
* Get RFC2618 MIB variable 'radiusAuthClientPendingRequests'.
* \i 'IPRADIUS_SCTRLT_GET_AccPendingRequests'
* Get RFC2620 MIB variable 'radiusAccClientPendingRequests'.
* \i 'IPRADIUS_SCTRLT_GET_AuthTimeouts'
* Get RFC2618 MIB variable 'radiusAuthClientTimeouts'.
* \i 'IPRADIUS_SCTRLT_GET_AccTimeouts'
* Get RFC2620 MIB variable 'radiusAccClientTimeouts'.
* \i 'IPRADIUS_SCTRLT_GET_AuthUnknownTypes'
* Get RFC2618 MIB variable 'radiusAuthClientUnknownTypes'.
* \i 'IPRADIUS_SCTRLT_GET_AccUnknownTypes'
* Get RFC2620 MIB variable 'radiusAccClientUnknownTypes'.
* \i 'IPRADIUS_SCTRLT_GET_AuthPacketsDropped'
* Get RFC2618 MIB variable 'radiusAuthClientPacketsDropped'.
* \i 'IPRADIUS_SCTRLT_GET_AccPacketsDropped'
* Get RFC2620 MIB variable 'radiusAccClientPacketsDropped'.
* \ie
*
* EXAMPLE
* \cs
* Ip_err example(void)
* {
*   Iptag ctrltag[3];
*   Ipradius_server server;
*
*   server.index = 1;
*
*   ctrltag[0] = IPRADIUS_SCTRLT_GET_ServerAddress;
*   ctrltag[2] = IPTAG_END;
*
*   return ipradius_server_ctrl(&server, ctrltag);
* }
* \ce
*
* RETURNS: 'IPCOM_SUCCESS' or one of the following errors:
* \is
* \i 'IPRADIUS_ERR_UNSUPPORTED_TAG'
*  The server configuration tag array contained an unknown tag.
* \i 'IPCOM_ERR_INVALID_TAG_VALUE'
*  Invalid tag value.
* \i 'IPCOM_SUCCESS'
*  Call completed successfully.
* \i 'IPCOM_ERR_NOT_OPENED'
*  Radius client not opened.
* \ie
*
* ERRNO:
*/
IP_PUBLIC Ip_err ipradius_server_ctrl
(
    Ipradius_server *server,
    Ip_tag *ctrltags
);

/* RFC2618 MIB server variables. (GET = read-only) */
#define IPRADIUS_SCTRLT_GET_AuthServerAddress              0xff060101
#define IPRADIUS_SCTRLT_GET_AuthServerPortNumber           0xff060102
#define IPRADIUS_SCTRLT_GET_AuthRoundTripTime              0xff060103
#define IPRADIUS_SCTRLT_GET_AuthAccessRequests             0xff060104
#define IPRADIUS_SCTRLT_GET_AuthAccessRetransmissions      0xff060105
#define IPRADIUS_SCTRLT_GET_AuthAccessAccepts              0xff060106
#define IPRADIUS_SCTRLT_GET_AuthAccessRejects              0xff060107
#define IPRADIUS_SCTRLT_GET_AuthAccessChallenges           0xff060108
#define IPRADIUS_SCTRLT_GET_AuthMalformedAccessResponses   0xff060109
#define IPRADIUS_SCTRLT_GET_AuthBadAuthenticators          0xff06010a
#define IPRADIUS_SCTRLT_GET_AuthPendingRequests            0xff06010b
#define IPRADIUS_SCTRLT_GET_AuthTimeouts                   0xff06010c
#define IPRADIUS_SCTRLT_GET_AuthUnknownTypes               0xff06010d
#define IPRADIUS_SCTRLT_GET_AuthPacketsDropped             0xff06010e

/* RFC2620 MIB server variables. (GET = read-only) */
#define IPRADIUS_SCTRLT_GET_AccServerAddress               0xff060101
#define IPRADIUS_SCTRLT_GET_AccServerPortNumber            0xff060102
#define IPRADIUS_SCTRLT_GET_AccRoundTripTime               0xff060113
#define IPRADIUS_SCTRLT_GET_AccRequests                    0xff060114
#define IPRADIUS_SCTRLT_GET_AccRetransmissions             0xff060115
#define IPRADIUS_SCTRLT_GET_AccResponses                   0xff060116
#define IPRADIUS_SCTRLT_GET_AccMalformedResponses          0xff060119
#define IPRADIUS_SCTRLT_GET_AccBadAuthenticators           0xff06011a
#define IPRADIUS_SCTRLT_GET_AccPendingRequests             0xff06011b
#define IPRADIUS_SCTRLT_GET_AccTimeouts                    0xff06011c
#define IPRADIUS_SCTRLT_GET_AccUnknownTypes                0xff06011d
#define IPRADIUS_SCTRLT_GET_AccPacketsDropped              0xff06011e


/*
 *===========================================================================
 *                    ipradius_request
 *===========================================================================
 * Description:   Send a RADIUS access or account request.
 * Parameters:
 * Returns:
 *
 */
IP_PUBLIC Ip_err
ipradius_request(Ipradius_request *request);


/*******************************************************************************
*
* ipradius_check_request - check for a pending request
*
* This routine checks to see if there is a pending access or accounting request
* (access or accounting) associated with a specified request ID.
*
* Parameter:
* \is
* \i <unique>
* The request ID.
* \ie
*
* EXAMPLE
* \cs
* Ip_err example(Ip_u32 unique)
* {
*   /@ Check if identical request is pending. @/
*   if (ipradius_check_request(unique) == IP_TRUE)
* 	return IPCOM_ERR_PENDING;
*   else
* 	return IPCOM_SUCCESS;
* }
* \ce
*
* RETURNS: Either 'IP_TRUE', if a request is pending, or 'IP_FALSE', if no
* request is pending.
*
* ERRNO:
*/
IP_PUBLIC Ip_bool ipradius_check_request
(
    Ip_u32 unique
);


/*******************************************************************************
*
* ipradius_read - read a packet from the RADIUS server
*
* This routine reads a packet from the RADIUS server.
*
* Parameters:
* \is
* \i <buf>
* A pointer to a buffer to store the packet.
* \i <len>
* The length, in bytes of the buffer where the packet should be stored.
* \i <from_addr>
* The IP address of the sending RADIUS server.
* \ie
*
* EXAMPLE
* \cs
* void example(void)
* {
* Ip_err  retval;
* 	  Ip_ssize_t    length;
* 	  Ip_socklen_t  addrlen;
* 	  union Ip_sockaddr_union  from_addr;
*
* 	  /@ Read the packet (IPv4 only) @/
* 	  addrlen = sizeof(struct Ip_sockaddr_in);
* 		length = ipcom_recvfrom(vars->fd, vars->pkt,
*        IPRADIUS_PKT_SIZE, 0, &from_addr.sa, &addrlen);
*
* if(length <= 0)
* 	  {
* 		   ipcom_printf("ipcom_recvfrom() failed, errno = %d"IP_LF,
* pcom_errno);
* 		   return;
* 	  }
*
*   /@ Pass packet to RADIUS for input parsing. @/
*   retval = ipradius_read(vars->pkt, length, &from_addr.sa);
*   if(retval != IPCOM_SUCCESS)
*   {
* 	ipcom_fprintf(ip_stderr, "radiusc() :: ipradius_read() failed\n");
*   }
* }
* \ce
*
* RETURNS: 'IPCOM_SUCCESS' or one of the following errors:
* \is
* \i 'IPRADIUS_ERR_UNKNOWN_PACKET_CODE'
*  The received packet had an unknown packet code and has been discarded.
* \i 'IPRADIUS_ERR_BAD_AUTHENTICATION'
*   The received packet had a bad authentication field and was discarded.
* \i 'IPCOM_ERR_NOT_OPENED'
*  Radius Client not opened.
* \ie
*
* ERRNO:
*/
IP_PUBLIC Ip_err ipradius_read
(
    void *buf,
    Ip_size_t len,
    struct Ip_sockaddr *from_addr
);


/*******************************************************************************
*
* ipradius_get_numattempts - get number of send attempts for a packet
*
* This routine gets the number of attempts that have been made to send a
* specified packet to the RADIUS server.
*
* Parameters:
* \is
* \i <packet>
* A pointer to the RADIUS packet.
* \i <attempts>
* A pointer to an 'Ip_u32' integer for receiving the number of send attempts.
* \ie
*
* EXAMPLE
* \cs
* Ip_u32 example(Ipradius_header *packet)
* {
*   Ip_u32  num_attempts;
*
*   if (ipradius_get_numattempts(packet, &num_attempts) ==
*       IPCOM_SUCCESS)
* 	return num_attempts;
*   else
* 		return -1;
* }
* \ce
*
* RETURNS: 'IPCOM_SUCCESS' or one of the following errors:
* \is
* \i 'IPCOM_ERR_INVALID_ARG'
*  Invalid function argument.
* \i 'IPCOM_ERR_NOT_OPENED'
*  Radius client not opened.
* \ie
*
* ERRNO:
*/
IP_PUBLIC Ip_err ipradius_get_numattempts
(
    Ipradius_header *packet,
    Ip_u32 *attempts
);


#ifdef __cplusplus
}
#endif

#endif
/* IPRADIUS_H */


/*
 ****************************************************************************
 *                      END OF FILE
 ****************************************************************************
 */


