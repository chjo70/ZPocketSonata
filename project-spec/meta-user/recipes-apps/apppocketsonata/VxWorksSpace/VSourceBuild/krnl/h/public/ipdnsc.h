/* ipdnsc.h - Public API of Wind River DNS client */

/*
 * Copyright (c) 2006-2013 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */
#ifndef IPDNSC_H
#define IPDNSC_H

/*
 ****************************************************************************
 * 1                    DESCRIPTION
 ****************************************************************************
 */

/*
DESCRIPTION
This library contains the APIs provided by the WindRiver DNS client.
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

#define IPCOM_USE_CLIB_PROTO
#include <ipcom_type.h>
#include <ipcom_cstyle.h>
#include <ipcom_clib.h>
#include <ipcom_sock.h>
#include <ipcom_tags.h>
#include <ipcom_os.h>
#include <ipcom_err.h>

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
 *                         release
 *===========================================================================
 */

#define IPDNSC_RELEASE 60500


/*  Error codes for lookup functions */
#define IPDNSC_HOST_NOT_FOUND       1
#define IPDNSC_TRY_AGAIN            2
#define IPDNSC_NO_RECOVERY          3
#define IPDNSC_NO_DATA              4
#define IPDNSC_NO_ADDRESS           IPDNSC_NO_DATA

/* Error codes returned by DNS update API */
#define IPDNSC_UPDATE_OK                      0       /* success */
#define IPDNSC_UPDATE_ERR_GENERAL             -1      /* An unexpected general error */
#define IPDNSC_UPDATE_ERR_INVALID             -2	  /* Invalid argument */
#define IPDNSC_UPDATE_ERR_MSGSIZE       	  -3      /* An invalid message length */
#define IPDNSC_UPDATE_ERR_EPROTOTYPE          -4      /* The answer to a query had the wrong domain name */
#define IPDNSC_UPDATE_ERR_NOTSUPPORT_TYPE     -5      /* Update type is not supported */
#define IPDNSC_UPDATE_ERR_NOTSUPPORT_ALG      -6      /* Not supported Algorithm */
#define IPDNSC_UPDATE_ERR_MD5_DISABLED        -7      /* MD5 lib is disabled */
#define IPDNSC_UPDATE_ERR_NO_TSIG             -8      /* No TSIG */
#define IPDNSC_UPDATE_ERR_TSIG_NO_SPACE       -9      /* No enough space fro TSIG */
#define IPDNSC_UPDATE_ERR_TSIG_BADFORMAT      -10     /* Bad TSIG format */
#define IPDNSC_UPDATE_ERR_TSIG_BADKEY         -11     /* Bad TSIG KEY */
#define IPDNSC_UPDATE_ERR_TSIG_SERVER_BADKEY  -12     /* Reply key from the server is bad */
#define IPDNSC_UPDATE_ERR_TSIG_SERVER_BADTIME -13     /* Reply time from the server is bad */
#define IPDNSC_UPDATE_ERR_YXRRSET			  -14

/* used by dynamic dns RFC2136 */
#define IPDNSC_MAXDNAME         1025	/* maximum domain name */
#define IPDNSC_MAXCDNAME	    255	    /* maximum compressed domain name */
#define IPDNSC_MAX_ALG_NAME     128  	/* maximum Algorithm name */
/* DNS TSIG Algorithm */
#define IPDNSC_TSIG_ALG_HMAC_MD5    "HMAC-MD5.SIG-ALG.REG.INT"

/* Flags for lookup functions */
#define IPDNSC_AI_V4MAPPED          0x00000008
#define IPDNSC_AI_ALL               0x00000010
#define IPDNSC_AI_ADDRCONFIG        0x00000020
#define IPDNSC_AI_DEFAULT           (IPDNSC_AI_V4MAPPED | IPDNSC_AI_ADDRCONFIG)


/*
 ****************************************************************************
 * 5                    TYPES
 ****************************************************************************
 */

/* defined section field */
typedef enum Ipdnsc_section_enum {
	IPDNSC_SECTION_QD = 0,		/* Query: Question. */
	IPDNSC_SECTION_ZN = 0,		/* Update: Zone. */
	IPDNSC_SECTION_AN = 1,		/* Query: Answer. */
	IPDNSC_SECTION_PR = 1,		/* Update: Prerequisites. */
	IPDNSC_SECTION_NS = 2,		/* Query: Name servers. */
	IPDNSC_SECTION_UP = 2,		/* Update: Update. */
	IPDNSC_SECTION_AR = 3,		/* Query|Update: Additional records. */
	IPDNSC_SECTION_MAX = 4
}
Ipdnsc_section;

/* Query class codes  */
typedef enum Ipdnsc_qclass_enum {
	IPDNSC_QCLASS_INVALID = 0,	/* Cookie. */
	IPDNSC_QCLASS_INET = 1,		/* Internet. */
	/* Query class values which do not appear in resource records */
	IPDNSC_QCLASS_NONE = 254,	/* for prereq. sections in update requests */
	IPDNSC_QCLASS_ANY = 255,	/* Wildcard match. */
	IPDNSC_QCLASS_MAX = 65536
}
Ipdnsc_qclass;

/* Query type codes for resources and queries. */
typedef enum Ipdnsc_qtype_enum {
	IPDNSC_QTYPE_INVALID = 0,	/* Cookie. */
	IPDNSC_QTYPE_A = 1,		    /* Host address. */
	IPDNSC_QTYPE_NS = 2,		/* Authoritative server. */
	IPDNSC_QTYPE_MD = 3,		/* Mail destination. */
	IPDNSC_QTYPE_MF = 4,		/* Mail forwarder. */
	IPDNSC_QTYPE_CNAME = 5,		/* Canonical name. */
	IPDNSC_QTYPE_SOA = 6,		/* Start of authority zone. */
	IPDNSC_QTYPE_MB = 7,		/* Mailbox domain name. */
	IPDNSC_QTYPE_MG = 8,		/* Mail group member. */
	IPDNSC_QTYPE_MR = 9,		/* Mail rename name. */
	IPDNSC_QTYPE_NULL = 10,		/* Null resource record. */
	IPDNSC_QTYPE_WKS = 11,		/* Well known service. */
	IPDNSC_QTYPE_PTR = 12,		/* Domain name pointer. */
	IPDNSC_QTYPE_HINFO = 13,	/* Host information. */
	IPDNSC_QTYPE_MINFO = 14,	/* Mailbox information. */
	IPDNSC_QTYPE_MX = 15,		/* Mail routing information. */
	IPDNSC_QTYPE_TXT = 16,		/* Text strings. */
	IPDNSC_QTYPE_RP = 17,		/* Responsible person. */
	IPDNSC_QTYPE_AFSDB = 18,	/* AFS cell database. */
	IPDNSC_QTYPE_X25 = 19,		/* X_25 calling address. */
	IPDNSC_QTYPE_ISDN = 20,		/* ISDN calling address. */
	IPDNSC_QTYPE_RT = 21,		/* Router. */
	IPDNSC_QTYPE_NSAP = 22,		/* NSAP address. */
	IPDNSC_QTYPE_NSAP_PTR = 23,	/* Reverse NSAP lookup (deprecated). */
	IPDNSC_QTYPE_SIG = 24,		/* Security signature. */
	IPDNSC_QTYPE_KEY = 25,		/* Security key. */
	IPDNSC_QTYPE_PX = 26,		/* X.400 mail mapping. */
	IPDNSC_QTYPE_GPOS = 27,		/* Geographical position (withdrawn). */
	IPDNSC_QTYPE_AAAA = 28,		/* Ip6 Address. */
	IPDNSC_QTYPE_LOC = 29,		/* Location Information. */
	IPDNSC_QTYPE_NXT = 30,		/* Next domain (security). */
	IPDNSC_QTYPE_EID = 31,		/* Endpoint identifier. */
	IPDNSC_QTYPE_NIMLOC = 32,	/* Nimrod Locator. */
	IPDNSC_QTYPE_SRV = 33,		/* Server Selection. */
	IPDNSC_QTYPE_ATMA = 34,		/* ATM Address */
	IPDNSC_QTYPE_NAPTR = 35,	/* Naming Authority PoinTeR */
	IPDNSC_QTYPE_KX = 36,		/* Key Exchange */
	IPDNSC_QTYPE_CERT = 37,		/* Certification record */
	IPDNSC_QTYPE_A6 = 38,		/* IPv6 address (deprecates AAAA) */
	IPDNSC_QTYPE_DNAME = 39,	/* Non-terminal DNAME (for IPv6) */
	IPDNSC_QTYPE_SLINK = 40,	/* Kitchen sink (experimentatl) */
	IPDNSC_QTYPE_OPT = 41,		/* EDNS0 option (meta-RR) */
	IPDNSC_QTYPE_APL = 42,		/* Address prefix list (RFC3123) */
	IPDNSC_QTYPE_TKEY = 249,	/* Transaction key */
	IPDNSC_QTYPE_TSIG = 250,	/* Transaction signature. */
	IPDNSC_QTYPE_IXFR = 251,	/* Incremental zone transfer. */
	IPDNSC_QTYPE_AXFR = 252,	/* Transfer zone of authority. */
	IPDNSC_QTYPE_MAILB = 253,	/* Transfer mailbox records. */
	IPDNSC_QTYPE_MAILA = 254,	/* Transfer mail agent records. */
	IPDNSC_QTYPE_ANY = 255,		/* Wildcard match. */
	IPDNSC_QTYPE_ZXFR = 256,	/* BIND-specific, nonstandard. */
	IPDNSC_QTYPE_MAX = 65536
} 
Ipdnsc_qtype;

/* defined response codes. */
typedef	enum Ipdnsc_rcode_enum {
	IPDNSC_RCODE_NOERROR = 0,	/* No error occurred. */
	IPDNSC_RCODE_FORMERR = 1,	/* Format error. */
	IPDNSC_RCODE_SERVFAIL = 2,	/* Server failure. */
	IPDNSC_RCODE_NXDOMAIN = 3,	/* Name error. */
	IPDNSC_RCODE_NOTIMPL = 4,	/* Unimplemented. */
	IPDNSC_RCODE_REFUSED = 5,	/* Operation refused. */
	/* these are for BIND_UPDATE */
	IPDNSC_RCODE_YXDOMAIN = 6,	/* Name exists */
	IPDNSC_RCODE_YXRRSET = 7,	/* RRset exists */
	IPDNSC_RCODE_NXRRSET = 8,	/* RRset does not exist */
	IPDNSC_RCODE_NOTAUTH = 9,	/* Not authoritative for zone */
	IPDNSC_RCODE_NOTZONE= 10,	/* Zone of record different from zone section */
	/* 11-15 available for assignment */
	/* The following are TSIG errors */
	IPDNSC_RCODE_BADSIG = 16,
	IPDNSC_RCODE_BADKEY = 17,
	IPDNSC_RCODE_BADTIME = 18,
	IPDNSC_RCODE_BADMODE = 19,
	IPDNSC_RCODE_BADNAME = 20,
	IPDNSC_RCODE_BADALG = 21,
	IPDNSC_RCODE_MAX = 22
} 
Ipdnsc_rcode;

/* DNS update operation */
typedef enum Ipdnsc_update_operation_enum {
	IPDNSC_UPOP_DELETE = 0,
	IPDNSC_UPOP_ADD = 1,
	IPDNSC_UPOP_MAX = 2
} 
Ipdnsc_update_operation;

/*
 * This structure is used for TSIG authenticated messages
 */
typedef struct Ipdnsc_tsig_key_struct {
        char name[IPDNSC_MAXDNAME];      /* the name of key must also exist on the DNS server */
		char alg[IPDNSC_MAX_ALG_NAME];   /* DNS TSIG Algorithm */
        Ip_u8 *secret;                   /* base64 secret must also be same with the DNS server */
        Ip_u32 len;                      /* the length of secret */
}
Ipdnsc_tsig_key;

/*
 * This RR-like structure is particular to UPDATE.
 */
typedef struct Ipdnsc_updrec_struct {
	struct Ipdnsc_updrec_struct *next;             /* next update record defined by caller */
	struct Ipdnsc_updrec_struct *samezone_next;    /* point the next update record belongs to a same zone on the nameserver.
	                                                  It should be initialized by NULL. */
	Ipdnsc_section	r_section;	/* ZONE/PREREQUISITE/UPDATE */
	char       *r_dname;	/* owner of the RR */
	Ip_u16	    r_class;	/* class number */
	Ip_u16		r_type;		/* type number */
	Ip_u32	    r_ttl;   	/* time to live */
	Ip_u8      *r_data;		/* rdata fields as text string */
	Ip_u32		r_size;		/* size of r_data field */
	Ip_s32    	r_opcode;	/* type of operation */
}
Ipdnsc_updrec;

/*
 *===========================================================================
 *                         Ipdnsc_api
 *===========================================================================
 * For better binary scalability at image build time, access to
 * the DNS resolver interface may be done through the following
 * set of function pointers:
 */
typedef struct Ipdnsc_api_struct
{
    struct Ip_hostent *(*getipnodebyname)(const char *name, int af,
                                          int flags, int *error_num);
    struct Ip_hostent *(*getipnodebyaddr)(const void *src, Ip_size_t len,
                                          int af, int *error_num);
    void (*freehostent)(struct Ip_hostent *he);
    void (*cache_flush)(void);

}
Ipdnsc_api;


/*
 ****************************************************************************
 * 6                    LOCAL FUNCTIONS
 ****************************************************************************
 */

/*
 ****************************************************************************
 * 10                   PUBLIC FUNCTIONS
 ****************************************************************************
 */

/*******************************************************************************
*
* ipdnsc_getipnodebyname - get host information by node name
*
* This routine can be used instead of the older standard gethostbyname() routine.
* gethostbyname() is inadequate for many applications, first because it provides
* no way for the caller to specify anything about the types of addresses desired
* (IPv4 only, IPv6 only, IPv4-mapped IPv6 are 'OK', and so forth), and second because
* many implementations of this function are not thread safe.
*
* Parameters:
* \is
* \i <name>
* A pointer to either a node name or a numeric address string (for example, a
* dotted-decimal IPv4 address or an IPv6 hex address).
* \i <af>
* Specifies the address family, either 'IPDNSC_AF_INET' or 'IPDNSC_AF_INET6'.
* \i <flags>
* Specifies the types of addresses that are searched for and the types of
* addresses that are returned. Applications desiring finer control over the
* types of addresses searched for and returned  can specify other combinations
* of the <flags> parameter. A <flags> parameter of '0' implies a strict
* interpretation of the <af> parameter:
*
* If <flags> is '0' and <af> is 'AF_INET', then the caller wants only IPv4
* addresses. A query is made for A records.  If successful,  the IPv4 addresses
* are returned and the <h_length> member of the hostent structure is '4',
* otherwise the function returns a NULL pointer.
*
* If <flags> is '0' and if< af> is 'AF_INET6', then the caller wants only IPv6
* addresses.  A query is made for AAAA records. If successful, the IPv6
* addresses are returned and the <h_length> member of the hostent structure is
* 16, otherwise the function returns a NULL pointer.
*
* Other constants can be logically-ORed into the <flags> parameter to modify the
* behavior of the function.
*
* If the 'AI_V4MAPPED' flag is specified along with an <af> of 'AF_INET6', then
* the caller will accept IPv4-mapped IPv6 addresses.  That is, if no AAAA
* records are found then a query is made for A records and any found are
* returned as IPv4-mapped IPv6 addresses (<h_length> is 16). The 'AI_V4MAPPED'
* flag is ignored unless af equals 'AF_INET6'.
*
* The 'AI_ALL' flag is used in conjunction with the 'AI_V4MAPPED' flag, and is
* only used with the IPv6 address family. When 'AI_ALL' is logically or'd with
* 'AI_V4MAPPED' flag then the caller wants all addresses: IPv6 and IPv4-mapped
* IPv6.  A query is first made for AAAA records and if successful, the IPv6
* addresses are returned. Another query is then made for A records and any found
* are returned as IPv4-mapped IPv6 addresses. <h_length> is 16. Only if both
* queries fail does the function return a NULL pointer. This flag is ignored
* unless af equals 'AF_INET6'.
*
*  The 'AI_ADDRCONFIG' flag specifies that a query for AAAA records should occur
* only if the node has at least one IPv6 source address configured and a query
* for A records should occur only if the node has at least one IPv4 source
* address configured. For example, if the node has no IPv6 source addresses
* configured and <af> equals 'AF_INET6', and if the node name being looked up
* has both AAAA and A records, then:
*
* \ml
* \m -
* If only 'AI_ADDRCONFIG' is specified, the function returns a NULL pointer.
* \m -
* If 'AI_ADDRCONFIG' \| 'AI_V4MAPPED' is specified, the A records are returned
* as IPv4-mapped IPv6 addresses.
* \me
* \i <error_num>
* A pointer to an error code. <error_num> value is returned to the caller, via a
* pointer, with the appropriate error code in <error_num> to support thread safe
* error code returns.
*
* <error_num> is set to one of the following values:
*
* \is
* \i 'IPDNSC_HOST_NOT_FOUND'
* No such host is known.
* \i 'IPDNSC_NO_ADDRESS'
* The server recognized the request and the name but address is available.
* Another type of request to the name server for the domain might return an
* answer.
* \i 'IPDNSC_NO_RECOVERY'
* An unexpected server failure occurred which cannot be recovered.
* \i 'IPDNSC_TRY_AGAIN'
* A temporary and possibly transient error occurred, such as a failure of a
* server to respond.
* \ie
* \ie
*
* RETURNS:
*
* ERRNO:
*/
IP_PUBLIC struct Ip_hostent* ipdnsc_getipnodebyname
(
	const char *name,
	int af,
	int flags,
	int *error_num
);


/*******************************************************************************
*
* ipdnsc_getipnodebyaddr - get host information by IP address
*
* This routine gets host information based on the host\'s IP address. It is
* similar to the older standard gethostbyaddr() routine but adds an error number
* and is thread safe.
*
* Parameters:
* \is
* \i <src>
* A pointer to an IPv4 address or an IPv6 address in network endian.
* \i <len>
* The length of the address, in bytes.
* \i <af>
* The address family, either 'IPDNSC_AF_INET' or 'IPDNSC_AF_INET6'.
* \i <error_num>
* A pointer to an error code. <error_num> value is returned to the caller, via a
* pointer, with the appropriate error code in <error_num>, to support thread
* safe error code returns. The following error conditions may be returned for
* <error_num>:
*
* \is
* \i 'IPDNSC_HOST_NOT_FOUND'
* No such host is known.
* \i 'IPDNSC_NO_ADDRESS'
* The server recognized the request and the name but no address is available.
* Another type of request to the name server for the domain might return an
* answer.
* \i 'IPDNSC_NO_RECOVERY'
* An unexpected server failure occurred which cannot be recovered.
* \i 'IPDNSC_TRY_AGAIN'
* A temporary and possibly transient error occurred, such as a failure of a
* server to respond.
* \ie
* \ie
*
* RETURNS:
*
* ERRNO:
*/
IP_PUBLIC struct Ip_hostent* ipdnsc_getipnodebyaddr
(
	const void *src,
	Ip_size_t len,
	int af,
	int *error_num
);


/*******************************************************************************
*
* ipdnsc_freehostent - free memory allocated for an 'ip_hostent' structure
*
* This routine frees memory allocated for an 'ip_hostent' structure.  An
* 'ip_hostent' structure is dynamically allocated by the
* ipdnsc_getipnodebyname() and ipdnsc_getipnodebyaddr() functions and must
* therefore be freed after use.
*
* Parameter:
* \is
* \i <he>
* A pointer to an 'ip_hostent' structure.
* \ie
*
* RETURNS:
*
* ERRNO:
*/
IP_PUBLIC void ipdnsc_freehostent
(
	struct Ip_hostent *he
);


/*******************************************************************************
*
* ipdnsc_cache_flush - remove all entries in the resolver cache.
*
* This routine removes all entries in the resolver cache. It is useful after
* the name server has been updated with new information about a specific host.
*
* RETURNS:
*
* ERRNO:
*/
IP_PUBLIC void ipdnsc_cache_flush(void);

/*******************************************************************************
*
* ipdnsc_do_update - build and send Dynamic Updates to correct name server
*
* This routine handle a complete DNS update process.It separates the linked list of 
* update records into groups so that all records in a group will belong to a single
* zone on the nameserver. It creates a dynamic update packet for each zone and sends
* it to the nameservers for that zone. Then it will receive and parse the response.
*
* Parameter:
* \is
* \i <update_records>
* The pointer to the linked list of update records.
* \i <r_buf>
* The pointer to the buffer to be filled with the update response packet.
* \i <r_buflen>
* The length of the r_buf, in bytes.
* \i <key>
* The pointer to the key to use for authentication. This key must exist on the name server..
* \i <error>
* error code returned.
* \ie
*
* RETURNS:
* n (successful), where n is the number of zones updated or -1 (unsuccessful) 
*
* ERRNO:
*/
IP_PUBLIC Ip_s32 ipdnsc_do_update
(
    Ipdnsc_updrec *update_records, Ip_u8 *r_buf, Ip_s32* r_buflen, Ipdnsc_tsig_key *key, Ip_s32 *error
);



#ifdef __cplusplus
}
#endif

#endif

/*
 ****************************************************************************
 *                      END OF FILE
 ****************************************************************************
 */
