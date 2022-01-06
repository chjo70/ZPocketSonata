/* socket.h - public socket structures and definitions */

/*
 * Copyright (c) 2001-2010, 2013-2014, 2016-2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
 * Copyright (c) 1982, 1985, 1986, 1988, 1993, 1994
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	@(#)socket.h	8.4 (Berkeley) 2/21/94
 * $FreeBSD: src/sys/sys/socket.h,v 1.39.2.7 2001/07/03 11:02:01 ume Exp $
 */

/*
modification history
--------------------
15jun17,xxy  TSN streams integration into the network stack (F9049).
26oct16,rjq  Changing _SS_MAXSIZE to be 128. (V7NET-1133)
18mar16,rjq  Support ipnet strict mode. (US77183)
31dec14,brk  Move POSIX functions from sockLib.h to here (F972)
13jan14,h_s  Remove MPLS support. (US19989)
16jan13,dlk  Adding SO_X_STACK_IDX.
09jan12,h_x  Move extern "C" after last header file include.
17mar11,fei  WIND00258872 : _ALIGNBYTES does not compliance with
             IP_CMSG_ALIGN_SIZE.
10jan10,h_w  Add AF_MIPC support
09jun09,dlk  LP64 conversion and socket API POSIXification.
27may09,kjn  Add missing "struct gre_key"
16oct08,dlk  Adding SO_X_VR definition (WIND00137543), and other SO_X
             options from ipcom.
28may08,jre  Adding fix for defect WIND00122519
23jan08,jbl  Adding NET_RT definitions back in (Defect WIND00110881)
12dec06,kch  Moved ipnet/ipioctl.h include to <sys/ioctl.h>.
30nov06,kch  Added ipnet/ipioctl.h include.
25oct06,kch  Changed __ss_align in sockaddr_storage from int64_t to int32_t.
03oct06,kch  Removed unsupported AF type for IPNet integration. Also
             updated the value assigned to the socket options.
15sep05,kch  Added priority_tagged boolean to sovlan structure for
             priority-tagged frames support (SPR #112513).
29aug05,kch  Added on/off option to sovlan structure. Corrected
             SO_VLAN define to use value that falls in the range
             for socket option that is kept in so_options (SPR #112068).
09aug05,kch  Added SO_VLAN socket level option and sovlan structure
             definition for socket-based vlan support.
12jul05,vvv  merged MSG_NOTIFICATION from kame-20050404-freebsd411
16may05,kch  Added MOBILITY address & protocol family.
12may05,als  Add AF_TIPC support
05mar05,dlk  Move SO_VSNUM and SO_VSID out of so_options flags.
             Add SO_LINGERRESET option.
07feb05,vvv  _KERNEL cleanup
12jan05,vvv  osdep.h cleanup
14oct04,nee  include osdep.h and machdep.h when _KERNEL is defined
             (SPR #102593)
23aug04,rp   merged from COMP_WN_IPV6_BASE6_ITER5_TO_UNIFIED_PRE_MERGE
19jul04,spm  enabled socket operations from different virtual stacks
15jun04,nee  adding the SOCKADDR typedef
12jan04,bwa  turned-on MSG_EXP option
02jan04,vvv  added socket option SO_CONNTIMEO
21nov03,bwa  added COMP protocol-specific socket flags and options
20nov03,niq  Remove copyright_wrs.h file inclusion
05nov03,cdw  Removal of unnecessary _KERNEL guards.
04nov03,rlm  Ran batch header path update for header re-org.
03nov03,rlm  Removed wrn/coreip/ prefix from #includes for header re-org.
27sep03,vvv  made SOCKADDR_STORAGE_T definition consistent between
             kernel and non-kernel builds
06aug03,nee  Accordion Base6 merge from ACCORDION_BASE6_MERGE_BASELINE
             label
10jun03,vvv  include netVersion.h
09may03,vvv  included vxWorks.h
06sep02,hsh  add c++ protection
03feb02,ham  changes for tornado build.
13sep01,ann  enabling the cmsg defines
14aug01,ann  correcting the header file inclusions
02aug01,ann  performed the initial-port from FreeBSD 4.3 v 1.39.2.7
*/


#ifndef _SYS_SOCKET_H_
#define	_SYS_SOCKET_H_

#include <vxWorks.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Definitions related to sockets: types, address families, options.
 */

/*
 * Data types.
 */
typedef u_char		sa_family_t;

/*
 * The socklen_t type is used in the POSIX-compatible socket APIs
 * to denote the lengths of buffers containing such things as socket
 * addresses, socket options, and control messages. All of these
 * are generally fairly short.  In previous VxWorks versions,
 * the socklen_t type was not used in the prototypes of most socket
 * functions; instead, the 'int' type was used. To decrease the number
 * of potential build failures resulting from the conversion to the
 * POSIX-compatible prototypes, in particular the change of certain
 * arguments from 'int *' to 'socklen_t *', the socklen_t type
 * is changed in this release from 'unsigned int' to 'int',
 * provided that SOCKLEN_T_UNSIGNED is not defined when this header
 * is read. It is not defined by default.  Note, however, that
 * VxWorks socket layer code <is> compiled with SOCKLEN_T_UNSIGNED
 * defined.  Since the socket layer expects and returns socklen_t
 * values that are always positive when viewed as signed 'int',
 * no run-time problems are expected when operating the socket layer
 * with applications compiled without SOCKLEN_T_UNSIGNED.  While
 * some build-time issues may occur, they are expected to be fairly
 * uncommon.
 *
 * In a future release, socklen_t will be restored to an unsigned
 * type. Application code is encouraged to use variables of the
 * socklen_t type (and use them in ways that are insensitive to
 * the type's signedness), to avoid conversion issues when this
 * occurs.  In the interim, application code may define the macro
 * SOCKLEN_T_UNSIGNED to restore the same unsigned socklen_t type
 * as the socket layer uses, and as in previous VxWorks versions.
 */
#ifdef SOCKLEN_T_UNSIGNED
typedef	unsigned int socklen_t;
#else
typedef	int socklen_t;
#endif

/*
 * Types
 */
#define	SOCK_STREAM	1		/* stream socket */
#define	SOCK_DGRAM	2		/* datagram socket */
#define	SOCK_RAW	3		/* raw-protocol interface */
#define	SOCK_RDM	4		/* reliably-delivered message */
#define	SOCK_SEQPACKET	5	/* sequenced packet stream */
#define	SOCK_PACKET	10		/* linux packet socket API. */

/*
 * Option flags per-socket.
 */
#define	SO_DEBUG	0x0001		/* turn on debugging info recording */
#define	SO_REUSEADDR	0x0004		/* allow local address reuse */
#define	SO_KEEPALIVE	0x0008		/* keep connections alive */
#define	SO_DONTROUTE	0x0010		/* just use interface addresses */
#define	SO_RCVLOWAT     0x0012		/* receive low-water mark */
#define	SO_SNDLOWAT     0x0013		/* send low-water mark */
#define SO_SNDTIMEO	0x1005		/* send timeout */
#define	SO_ACCEPTCONN	0x001e		/* socket has had listen() */
#define	SO_BROADCAST	0x0020		/* permit sending of broadcast msgs */
#define	SO_USELOOPBACK	0x0040		/* bypass hardware when possible */
#define	SO_LINGER	0x0080		/* linger on close if data present */
#define	SO_REUSEPORT	0x0200		/* allow local address & port reuse */

#define SO_VLAN         0x8000      /* get/set VLAN ID and user priority */

/*
 * Additional options, not kept in so_options.
 */
#define SO_SNDBUF	0x1001		/* send buffer size */
#define SO_RCVBUF	0x1002		/* receive buffer size */
#define SO_RCVTIMEO	0x1006		/* receive timeout */
#define	SO_ERROR	0x1007		/* get error status and clear */
#define	SO_TYPE		0x1008		/* get socket type */
#define	SO_BINDTODEVICE	0x1010		/* bind to specific device */
#define	SO_OOBINLINE	0x1011		/* leave received OOB data in line */
#define SO_CONNTIMEO    0x100a          /* connection timeout for */

/* Various SOL_SOCKET options from ipcom. See ipcom_sock.h. */

#define SO_X_VR           0x1020  /* int; Set virtual router */
#define SO_X_PROBEDELAY   0x1021  /* int; number of seconds a connection
				          (with keep-alive active) must be idle
					  before the first probe is sent */
#define SO_X_COOKIE       0x1022  /* void *; socket IPCOM port specific
				             cookie */

/* SO_X_EVENTCB_RO is not usable in VxWorks. */

#define SO_X_PKT_MPRIO    0x1025  /* int; ipcom_pkt_malloc() priority */
#define SO_X_BYPASS_FLOW  0x1026  /* int; Turn on/off bypass flow */
#define SO_X_DRAINABLE    0x1027  /* int;
				     ==0 packets in the receive queue must not
				         be freed even in low memory situations
					 (default)
                                     !=0 the stack might discard already queued
				         packets in low memory situations */
#define SO_X_GRE_KEY      0x1028  /* struct gre_key;
				     set the GRE flow key for traffic sent from
				     this socket */

/* SO_X_WINDNET_SO is not usable in VxWorks */
#define SO_X_STACK_IDX    0x1030  /* int; set/get the stack instance
                                   * the socket is assigned to */

#define SO_X_QBV          0x1031  /* char[TSN_STREAMNAMESIZ]; send with launch
                                time defined by Qbv stream*/
#define TSN_STREAMNAMSIZ      16

#define SO_TIMESTAMP     0x0400
#define SO_TIMESTAMPING  0x0800

#define SOF_TIMESTAMPING_TX_HARDWARE   (1<<0)
#define SOF_TIMESTAMPING_TX_SOFTWARE   (1<<1)
#define SOF_TIMESTAMPING_RX_HARDWARE   (1<<2)
#define SOF_TIMESTAMPING_RX_SOFTWARE   (1<<3)
#define SOF_TIMESTAMPING_SOFTWARE      (1<<4)
#define SOF_TIMESTAMPING_RAW_HARDWARE  (1<<5)

/*
 * Structure used for manipulating linger option.
 */
struct linger {
	int	l_onoff;		/* option on/off */
	int	l_linger;		/* linger time */
};

/*
 * Structure used for manipulating GRE key option
 */
struct gre_key {
    int      gk_onoff;  /* Option on/off */
    uint32_t gk_key;    /* RFC 2890 GRE key in host byte order */
};

/*
 * VxWorks-specific socket structure for manipulating SO_VLAN option
 */
struct sovlan {

    /*
     * If so_onff is set, the vlan id and/or user priority will be copied
     * to the socket structure and SO_VLAN so_option will be set. If so_onff
     * is not set, the SO_VLAN so_option for the given socket will be cleared.
     */
    int	vlan_onoff;		/* option on/off */

    /*
     * The priority_tagged boolean must be set to true if application using
     * socket-based vlan requires to egress 802.1P priority-tagged frame
     * (i.e. the value of vid is zero). Defaults to false. If set to true,
     * the value specified by the vid will be ignored.
     */
    BOOL priority_tagged;

    unsigned short vid;  /* VLAN ID, valid vid: 1..4094 */
    unsigned short upriority;   /* User Priority, valid priority: 0..7 */
};

/*
 * Level number for (get/set)sockopt() to apply to socket itself.
 */
#define	SOL_SOCKET	0xffff		/* options for socket level */

/*
 * Address families.
 */
#define	AF_UNSPEC	0		/* unspecified */
#define	AF_LOCAL	1		/* local to host (pipes, portals) */
#define	AF_UNIX		AF_LOCAL	/* backward compatibility */
#define	AF_INET		2		/* internetwork: UDP, TCP, etc. */
#define	AF_NETLINK	16		/* Linux Netlink, RFC 3549 */
#define	AF_ROUTE	17		/* Internal Routing Protocol */
#define	AF_LINK		18		/* Link layer interface */
#define	AF_PACKET	19		/* Linux packet family */
#define	pseudo_AF_KEY	27		/* Internal key-management function */
#define	AF_KEY		pseudo_AF_KEY	/* backward compatibility */
#define	AF_INET6	28		/* IPv6 */
#define	AF_SOCKDEV	31		/* Socket connected to a network interface */
#define AF_TIPC		33		/* Tranparent Inter-Process Communic. */
#define	AF_MIPC		34		/* Multi-OS Inter-Processor Communic. */
#define AF_MIPC_SAFE    35              /* SafeIPC */
#define AF_MAX          36

/*
 * Structure used by kernel to store most
 * addresses.
 */
struct sockaddr {
	u_char		sa_len;		/* total length */
	sa_family_t	sa_family;	/* address family */
	char		sa_data[14];	/* actually longer; address value */
};

typedef struct sockaddr SOCKADDR;

/*
 * RFC 2553: protocol-independent placeholder for socket addresses
 */
#define _SS_MAXSIZE     128
#define _SS_ALIGNSIZE   (sizeof(uint32_t))
#define _SS_PAD1SIZE	(_SS_ALIGNSIZE - sizeof(u_char) - sizeof(sa_family_t))
#define _SS_PAD2SIZE	(_SS_MAXSIZE - sizeof(u_char) - sizeof(sa_family_t) - \
                         _SS_PAD1SIZE - _SS_ALIGNSIZE)

struct sockaddr_storage {
	u_char		ss_len;		/* address length */
	sa_family_t	ss_family;	/* address family */
	char		__ss_pad1[_SS_PAD1SIZE];
	int32_t		__ss_align;	/* force desired structure storage alignment */
	char		__ss_pad2[_SS_PAD2SIZE];
};

typedef struct sockaddr_storage SOCKADDR_STORAGE_T;
#define SOCK_MAXADDRLEN         (sizeof (SOCKADDR_STORAGE_T))


/*
 * Protocol families, same as address families for now.
 */
#define	PF_UNSPEC	AF_UNSPEC
#define	PF_LOCAL	AF_LOCAL
#define	PF_UNIX		PF_LOCAL	/* backward compatibility */
#define	PF_INET		AF_INET
#define	PF_NETLINK	AF_NETLINK
#define	PF_ROUTE	AF_ROUTE
#define	PF_LINK		AF_LINK
#define	PF_PACKET	AF_PACKET
#define	PF_KEY		AF_KEY
#define	PF_INET6	AF_INET6
#define	PF_SOCKDEV	AF_SOCKDEV
#define	PF_TIPC		AF_TIPC
#define PF_MIPC		AF_MIPC
#define PF_MIPC_SAFE	AF_MIPC_SAFE
#define	PF_MAX		AF_MAX

/*
 * Maximum queue length specifiable by listen.
 */
#define	SOMAXCONN	128


/* Networking sysctl's */

#define NET_RT_DUMP     1               /* dump; may limit to a.f. */
#define NET_RT_FLAGS    2               /* by flags, e.g. RESOLVING */
#define NET_RT_IFLIST   3               /* survey interface list */
#define NET_RT_MAXID    4
#define IPCTL_STRICT_MODE    6          /* IPv4 or IPv6 strict mode on/off */


/*
 * Message header for recvmsg and sendmsg calls.
 * Used value-result for recvmsg, value only for sendmsg.
 */
struct msghdr {
	void		*msg_name;		/* optional address */
	socklen_t	 msg_namelen;		/* size of address */
	struct iovec	*msg_iov;		/* scatter/gather array */
	int		 msg_iovlen;		/* # elements in msg_iov */
	void		*msg_control;		/* ancillary data, see below */
	socklen_t	 msg_controllen;	/* ancillary data buffer len */
	int		 msg_flags;		/* flags on received message */
};

#define	MSG_OOB		0x1		/* process out-of-band data */
#define	MSG_PEEK	0x2		/* peek at incoming message */
#define	MSG_DONTROUTE	0x4		/* send without using routing tables */
#define	MSG_EOR		0x8		/* data completes record */
#define	MSG_TRUNC	0x10		/* data discarded before delivery */
#define	MSG_CTRUNC	0x20		/* control data lost before delivery */
#define	MSG_WAITALL	0x40		/* wait for full request or error */
#define	MSG_DONTWAIT	0x80		/* this message should be nonblocking */
#define	MSG_EOF		0x100		/* data completes connection */
#define MSG_EXP         0x200           /* COMP-only: send express message */
#define MSG_MBUF        0x400           /* WRS extension */
#define MSG_NOTIFICATION 0x800          /* notification message */
#define MSG_COMPAT      0x8000		/* used in sendit() */


/*
 * Header for ancillary data objects in msg_control buffer.
 * Used for additional information with/about a datagram
 * not expressible by flags.  The format is a sequence
 * of message elements headed by cmsghdr structures.
 */
struct cmsghdr {
	socklen_t	cmsg_len;		/* data byte count, including hdr */
	int		cmsg_level;		/* originating protocol */
	int		cmsg_type;		/* protocol-specific type */
/* followed by	u_char  cmsg_data[]; */
};

#define _ALIGNBYTES (sizeof (long) - 1)
#define _ALIGN(p)   (((unsigned long) (p) + _ALIGNBYTES) & ~_ALIGNBYTES)

/* given pointer to struct cmsghdr, return pointer to data */
#define	CMSG_DATA(cmsg)		((u_char *)(cmsg) + \
				 _ALIGN(sizeof(struct cmsghdr)))

/* given pointer to struct cmsghdr, return pointer to next cmsghdr */
#define	CMSG_NXTHDR(mhdr, cmsg)	\
	(((caddr_t)(cmsg) + _ALIGN((cmsg)->cmsg_len) + \
	  _ALIGN(sizeof(struct cmsghdr)) > \
	    (caddr_t)(mhdr)->msg_control + (mhdr)->msg_controllen) ? \
	    (struct cmsghdr *)NULL : \
	    (struct cmsghdr *)((caddr_t)(cmsg) + _ALIGN((cmsg)->cmsg_len)))

#define	CMSG_FIRSTHDR(mhdr)	((struct cmsghdr *)(mhdr)->msg_control)

/* RFC 2292 additions */

#define	CMSG_SPACE(l)		(_ALIGN(sizeof(struct cmsghdr)) + _ALIGN(l))
#define	CMSG_LEN(l)		(_ALIGN(sizeof(struct cmsghdr)) + (l))

#ifdef _WRS_KERNEL
#define	CMSG_ALIGN(n)	_ALIGN(n)
#endif

/*
 * howto arguments for shutdown(2), specified by Posix.1g.
 */
#define	SHUT_RD		0		/* shut down the reading side */
#define	SHUT_WR		1		/* shut down the writing side */
#define	SHUT_RDWR	2		/* shut down both sides */

extern int 	accept (int s, struct sockaddr *addr, socklen_t *addrlen);
extern STATUS 	bind (int s, const struct sockaddr *name, socklen_t namelen);
extern STATUS 	connect (int s, const struct sockaddr *name,
			 socklen_t namelen);

extern STATUS 	getpeername (int s, struct sockaddr *name, socklen_t *namelen);
extern STATUS 	getsockname (int s, struct sockaddr *name, socklen_t *namelen);
extern STATUS 	getsockopt (int s, int level, int optname, void *optval,
			    socklen_t *optlen);
extern STATUS 	listen (int s, int backlog);
extern ssize_t 	recv (int s, void *buf, size_t bufLen, int flags);
extern ssize_t 	recvfrom (int s, void *buf, size_t bufLen, int flags,
			  struct sockaddr *from, socklen_t *pFromLen);
extern ssize_t	recvmsg (int sd, struct msghdr *mp, int flags);
extern ssize_t 	send (int s, const void *buf, size_t bufLen, int flags);
extern ssize_t 	sendmsg (int sd, const struct msghdr *mp, int flags);
extern ssize_t 	sendto (int s, const void *buf, size_t bufLen, int flags,
			const struct sockaddr *to, socklen_t tolen);
extern int 	setsockopt (int s, int level, int optname, const void *optval,
			    socklen_t optlen);
extern STATUS 	shutdown (int s, int how);
extern int 	socket (int domain, int type, int protocol);


#ifdef __cplusplus
}
#endif

#endif /* !_SYS_SOCKET_H_ */
