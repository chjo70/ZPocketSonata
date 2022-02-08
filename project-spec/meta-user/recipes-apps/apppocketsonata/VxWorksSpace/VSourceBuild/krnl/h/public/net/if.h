/* if.h - network interface header file */

/* Copyright 2001-2007, 2012, 2016, 2018 Wind River Systems, Inc. */

/*
 * Copyright (c) 1982, 1986, 1989, 1993
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
 *	@(#)if.h	8.1 (Berkeley) 6/10/93
 * $FreeBSD: src/sys/net/if.h,v 1.58.2.9 2002/08/30 14:23:38 sobomax Exp $
 */

/*
modification history
--------------------
17jan18,xxy  Fix END_MIB_2233 flag lost error (V7PRO-4181)
03jan17,dlk  include vxTypesOld.h so sysV types defined without VxWorks.h (F972)
11aug16,mca  Enable if_nametoindex() and if_indextoname() for user space.
26may16,dlk  Make ifi_ibytes and ifi_obytes unsigned.
24mar16,dlk  Fix build warnings.
16feb16,ply  Ipnet_if_data structure doesn't match if_data, V7NET-743
12jan12,h_x  Move extern "C" after last header file include.
20dec07,dlk  Add IFF_END_MODIFIABLE mask.
04dec06,kch  Changed ifru_flags in ifreq to u_short.
25oct06,kch  Comment out ifi_hwassist in if_data structure for now.
03oct06,kch  Removed unsupported IFF flags for IPNet integration. Also
                 changed the type for index associated with an ifp from
                 u_short to u_long.
26sep06,kch  Added ifru_ifindex, ifru_vr and ifru_opt members to ifreq
                 structure. Changed ifru_flags from long to u_short.
12sep06,kch  Restore if_nameindex structure definition and prototypes
                 for if_nametoindex(), if_indextoname(), if_nameindex()
                 and if_freenameindex().
09sep06,kch  Cleanup for IPNet integration.
30aug05,kch  Added ifdeladdrreq structure (moved from if.c) (SPR #112068).
17aug05,mcm  Including sys/time.h for struct timeval
26jul05,kch  Move if_clone structure definition to if_clone.h.
30jun05,wap  Move ifi_link_state for binary compatibility
24jun05,wap  Add link state support
18feb05,wap  Allow sysctl init routines to be scaled out
07feb05,vvv  _KERNEL cleanup
14jan05,vvv  osdep.h cleanup
23aug04,rp   merged from COMP_WN_IPV6_BASE6_ITER5_TO_UNIFIED_PRE_MERGE
19jul04,niq  Move sysctl initialization from configelette to the component
                 init routine
28may04,niq  Merging from base6 label POST_ITER5_FRZ16_REBASE (ver
                 /main/vdt/base6_itn5_networking-int/2)
09feb04,niq  Include if_var.h only in kernel context
14dec03,ijm  added IFF_PROXY_ALL for spr#85896,for interface based proxy
20nov03,niq  osdep.h cleanup
04nov03,rlm  Ran batch header path update for header re-org.
03nov03,rlm  Removed wrn/coreip/ prefix from #includes for header re-org.
24oct03,rlm  updated #includes for header re-org
15sep03,vvv  updated path for new headers
18aug03,nee  Merging from ACCORDION_BASE6_MERGE_BASELINE
15may03,spm  Tornado 2.2 FCS merge (SPR #69683; ver 01m,10oct01,rae:
                 TOR2_2-FCS-COPY label, tor2 branch, /wind/river VOB)
09may03,vvv  included socket.h
08may03,vvv  fixed value for IFF_PPROMISC (SPR #88237)
01may03,spm  Tornado 2.2 CP1 merge (from ver 01n,17jan03,vvv:
                 TOR2_2-CP1-F label, tor2_2-patch branch, /wind/river VOB)
01feb03,pas  merge from FreeBSD 4.7 - clone, announce interfaces
17sep02,nee  added admin control macros
09sep02,hsh  add c++ protection
24aug02,nee  extended ifnet for admin control;defined admin states for
                 boot/up/down
12jul02,hsh  fix head file for ppc
03feb02,ham  modified for tornado build.
16dec01,ann  temporarily moving the if_name* declerations out the _KERNEL
                 condition
24sep01,ppp  adding the prototype for if_name and the macro for IFAREF
12sep01,ann  adding some IFF flags
11sep01,ann  uncomment ifi_lastchange
09sep01,ham  changed header file's path, made ifi_lastchange obsolete.
16jul01,ham  created from FreeBSD4.3-RELEASE(July-17-01).
*/

#ifndef __INCifh
#define	__INCifh

#ifdef _WRS_KERNEL
#include <sys/queue.h>
#include <sys/times.h>
#else
#include <sys/time.h>
#endif

#include <cfgDefs.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <types/vxTypesOld.h>


#ifdef __cplusplus
 extern "C" {
#endif

#ifndef VX_IOCG_NETIF
#define VX_IOCG_NETIF       3
#endif

/*
 * For user-space stack build. If IPNET_COREIP or IPNET_USRSPACE is enabled,
 * these ioctl codes are defined in ipnet/ipioctl.h.
 * Would like a better way to handle this.
 */
#if !defined (_WRS_CONFIG_IPNET_COREIP) && !defined(_WRS_CONFIG_IPNET_USRSPACE)
/* Get (sub)net address mask. */
#define SIOCGIFNETMASK  _IOWR(VX_IOCG_NETIF,  5, struct ifreq)

/* Get interface list. */
#define SIOCGIFCONF     _IOWR(VX_IOCG_NETIF, 21, struct ifconf)

/* Get interface index */
#define SIOCGIFINDEX	_IOWR(VX_IOCG_NETIF, 22, struct ifreq)

/* Get interface name */
#define SIOCGIFNAME     _IOWR(VX_IOCG_NETIF, 24, struct ifreq)
#endif

/*
 * Length of interface external name, including terminating '\0'.
 * Note: this is the same size as a generic device's external name.
 */
#define		IFNAMSIZ	16
#define		IF_NAMESIZE	IFNAMSIZ

/*
 * Structure describing information about an interface
 * which may be of interest to management entities.
 */
struct if_data {
	/* generic interface information */
	u_char	ifi_type;		/* ethernet, tokenring, etc */
	u_char	ifi_addrlen;		/* media address length */
	u_char	ifi_hdrlen;		/* media header length */
	u_char	ifi_link_state;		/* current link state */
	u_long	ifi_mtu;		/* maximum transmission unit */
	u_long	ifi_metric;		/* routing metric (external only) */
	u_long	ifi_baudrate;		/* linespeed */
	/* volatile statistics */
	u_long	ifi_ipackets;		/* packets received on interface */
	u_long	ifi_ierrors;		/* input errors on interface */
	u_long	ifi_opackets;		/* packets sent on interface */
	u_long	ifi_oerrors;		/* output errors on interface */
	u_long	ifi_collisions;		/* collisions on csma interfaces */
	uint64_t ifi_ibytes;		/* total number of octets received */
	uint64_t ifi_obytes;		/* total number of octets sent */
	u_long	ifi_imcasts;		/* packets received via multicast */
	u_long	ifi_omcasts;		/* packets sent via multicast */
	u_long	ifi_iqdrops;		/* dropped on input, this interface */
	u_long	ifi_noproto;		/* destined for unsupported protocol */
#if 0
	u_long	ifi_hwassist;		/* HW offload capabilities */
#endif
	struct	timeval ifi_lastchange;	/* time of last administrative change */
};

#define	IFF_UP		0x1		/* interface link is up */
#define	IFF_BROADCAST	0x2		/* broadcast address valid */
#define	IFF_DEBUG	0x4		/* turn on debugging */
#define	IFF_LOOPBACK	0x8		/* is a loopback net */
#define	IFF_POINTOPOINT	0x10		/* interface is point-to-point link */
#define	IFF_RUNNING	0x40		/* resources allocated */
#define	IFF_NOARP	0x80		/* no address resolution protocol */
#define	IFF_PROMISC	0x100		/* receive all packets */
#define	IFF_ALLMULTI	0x200		/* receive all multicast packets */
#define	IFF_OACTIVE	0x400		/* transmission in progress */
#define	IFF_SIMPLEX	0x800		/* can't hear own transmissions */
#define	IFF_LINK0	0x1000		/* forwarding disabled */
#define	IFF_LINK1	0x2000		/* per link layer defined bit */
#define	IFF_LINK2	0x4000		/* per link layer defined bit */
#define	IFF_ALTPHYS	IFF_LINK2	/* use alternate physical connection */
#define	IFF_MULTICAST	0x8000		/* supports multicast */
#define IFF_NOTRAILERS  0x20000         /* avoid use of trailers */

/*
 * These bits are modifiable for END devices via EIOCSFLAGS.
 * For now, we allow modifying some unallocated bits and the IFF_LINK* bits.
 * IFF_UP is explicitly NOT modifiable; to start or stop an interface
 * at the END level, one must use muxDevStart()/muxDevStop(). The END driver
 * controls its own IFF_UP flag in pEnd->flags.
 */
#define IFF_END_MODIFIABLE \
 (IFF_DEBUG | IFF_PROMISC | IFF_ALLMULTI |	\
  IFF_LINK0 | IFF_LINK1 | IFF_LINK2 |		\
  0xfffc0000)

/*
 * Values for if_link_state.
 */
#define LINK_STATE_UNKNOWN	0	/* link invalid/unknown */
#define LINK_STATE_DOWN		1	/* link is down */
#define LINK_STATE_UP		2	/* link is up */

/* Capabilities that interfaces can advertise. */
#define IFCAP_RXCSUM		0x0001  /* can offload checksum on RX */
#define IFCAP_TXCSUM		0x0002  /* can offload checksum on TX */
#define IFCAP_NETCONS		0x0004  /* can be a network console */

#define IFCAP_HWCSUM		(IFCAP_RXCSUM | IFCAP_TXCSUM)


/*
 * Message format for use in obtaining information about interfaces
 * from getkerninfo and the routing socket
 */
struct if_msghdr {
	u_short	ifm_msglen;	/* to skip over non-understood messages */
	u_char	ifm_version;	/* future binary compatability */
	u_char	ifm_type;	/* message type */
	int	ifm_addrs;	/* like rtm_addrs */
	int	ifm_flags;	/* value of if_flags */
	u_long	ifm_index;	/* index for associated ifp */
	struct	if_data ifm_data;/* statistics and other data about if */
};

/*
 * Message format for use in obtaining information about interface addresses
 * from getkerninfo and the routing socket
 */
struct ifa_msghdr {
	u_short	ifam_msglen;	/* to skip over non-understood messages */
	u_char	ifam_version;	/* future binary compatability */
	u_char	ifam_type;	/* message type */
	int	ifam_addrs;	/* like rtm_addrs */
	int	ifam_flags;	/* value of ifa_flags */
	u_long  ifam_index;	/* index for associated ifp */
	int	ifam_metric;	/* value of ifa_metric */
};

/*
 * Message format announcing the arrival or departure of a network interface.
 */
struct if_announcemsghdr {
	u_short	ifan_msglen;	/* to skip over non-understood messages */
	u_char	ifan_version;	/* future binary compatibility */
	u_char	ifan_type;	/* message type */
	u_long	ifan_index;	/* index for associated ifp */
	char	ifan_name[IFNAMSIZ]; /* if name, e.g. "en0" */
	u_short	ifan_what;	/* what type of announcement */
};

#define	IFAN_ARRIVAL	0	/* interface arrival */
#define	IFAN_DEPARTURE	1	/* interface departure */

/*
 * Interface request structure used for socket
 * ioctl's.  All interface ioctl's must have parameter
 * definitions which begin with ifr_name.  The
 * remainder may be interface specific.
 */
struct sockaddr;

struct	ifreq {
	char	ifr_name[IFNAMSIZ];		/* if name, e.g. "en0" */
	union {
		struct	sockaddr ifru_addr;
		struct	sockaddr ifru_dstaddr;
		struct	sockaddr ifru_broadaddr;
		u_short	ifru_flags;
		int	ifru_metric;
		int	ifru_mtu;
		int     ifru_ivalue;
		int     ifru_ifindex;
		int	ifru_phys;
		int	ifru_media;
		void *	ifru_data;   /* interface dependent data */
		u_short ifru_vr;     /* virtual router */
		int	ifru_opt;    /* option: enable=1, disable=0 */
		int	ifru_cap[2];
                char    ifru_newname[IFNAMSIZ]; /* if name, e.g. "eth0" */
                char    ifru_slave[IFNAMSIZ];   /* if name, e.g. "eth0" */

	} ifr_ifru;
#define	ifr_addr	ifr_ifru.ifru_addr	/* address */
#define	ifr_dstaddr	ifr_ifru.ifru_dstaddr	/* other end of p-to-p link */
#define	ifr_broadaddr	ifr_ifru.ifru_broadaddr	/* broadcast address */
#define	ifr_flags	ifr_ifru.ifru_flags	/* flags */
#define	ifr_metric	ifr_ifru.ifru_metric	/* metric */
#define ifr_ifindex     ifr_ifru.ifru_ifindex   /* Interface index */
#define	ifr_mtu		ifr_ifru.ifru_mtu	/* mtu */
#define ifr_phys	ifr_ifru.ifru_phys	/* physical wire */
#define ifr_media	ifr_ifru.ifru_media	/* physical media */
#define	ifr_data	ifr_ifru.ifru_data	/* for use by interface */
#define ifr_vr          ifr_ifru.ifru_vr /* Interpeak virtual router extension*/
#define ifr_opt         fr_ifru.ifru_opt   /* Interpeak option extension */
#define	ifr_reqcap	ifr_ifru.ifru_cap[0]	/* requested capabilities */
#define	ifr_curcap	ifr_ifru.ifru_cap[1]	/* current capabilities */
};

#define	_SIZEOF_ADDR_IFREQ(ifr) \
	((ifr).ifr_addr.sa_len > sizeof(struct sockaddr) ? \
	 (sizeof(struct ifreq) - sizeof(struct sockaddr) + \
	  (ifr).ifr_addr.sa_len) : sizeof(struct ifreq))

struct ifaliasreq {
	char	ifra_name[IFNAMSIZ];		/* if name, e.g. "en0" */
	struct	sockaddr ifra_addr;
	struct	sockaddr ifra_broadaddr;
	struct	sockaddr ifra_mask;
};

struct ifmediareq {
	char	ifm_name[IFNAMSIZ];	/* if name, e.g. "en0" */
	int	ifm_current;		/* current media options */
	int	ifm_mask;		/* don't care mask */
	int	ifm_status;		/* media status */
	int	ifm_active;		/* active options */
	int	ifm_count;		/* # entries in ifm_ulist array */
	int	*ifm_ulist;		/* media words */
};

/*
 * Structure used in SIOCGIFCONF request.
 * Used to retrieve interface configuration
 * for machine (useful for programs which
 * must know all networks accessible).
 */
struct	ifconf {
	int	ifc_len;		/* size of associated buffer */
	union {
		caddr_t	ifcu_buf;
		struct	ifreq *ifcu_req;
	} ifc_ifcu;
#define	ifc_buf	ifc_ifcu.ifcu_buf	/* buffer address */
#define	ifc_req	ifc_ifcu.ifcu_req	/* array of structures returned */
};

struct if_nameindex {
	u_int	if_index;	/* 1, 2, ... */
	char	*if_name;	/* null terminated name: "le0", ... */
};

u_int	 if_nametoindex __P((const char *));
char	*if_indextoname __P((u_int, char *));
#ifdef _WRS_KERNEL
struct	 if_nameindex *if_nameindex __P((void));
void	 if_freenameindex __P((struct if_nameindex *));
#endif /* _WRS_KERNEL */

#ifdef __cplusplus
}
#endif

#ifdef _WRS_KERNEL
#include <net/if_var.h>
#endif /* _WRS_KERNEL */

#endif /* !__INCifh */
