/* ethernet.h - ethernet header file */

/* Copyright 2001-2003, 2005-2006, 2012, 2014, 2016 Wind River Systems, Inc. */

/*
 * Fundamental constants relating to ethernet.
 *
 * $FreeBSD: src/sys/net/ethernet.h,v 1.12.2.5 2000/07/19 21:43:52 archie Exp $
 *
 */

/*
modification history
--------------------
08mar16,mca  Enable user-space build.
02feb16,h_l  Add PTP ethertype definition
05may14,rjq  Decouple COREIP with END. (V7NET-105)
09jan12,h_x  Move extern "C" after last header file include.
12sep06,kch  Removed reference to struct ifnet.
09sep06,kch  Cleanup for IPNet integration.
07feb05,vvv  _KERNEL cleanup
20nov03,niq  Remove copyright_wrs.h file inclusion
05nov03,cdw  Removal of unnecessary _KERNEL guards.
04nov03,rlm  Ran batch header path update for header re-org.
03nov03,rlm  Removed wrn/coreip/ prefix from #includes for header re-org.
20aug03,niq  Include cdefs.h for __BEGIN_DECLS definition (to correct
                 compilation issues
10jun03,vvv  include netVersion.h
09sep02,hsh  add c++ protection
12sep01,ann  adding a definition for ETHERSMALL
07aug01,ham  created from FreeBSD4.3-RELEASE(July-17-01).
 */

#ifndef _NET_ETHERNET_H_
#define _NET_ETHERNET_H_

#ifdef __cplusplus
extern "C" {
#endif

/*
 * The number of bytes in an ethernet (MAC) address.
 */
#define	ETHER_ADDR_LEN		6

/*
 * The number of bytes in the type field.
 */
#define	ETHER_TYPE_LEN		2

/*
 * The number of bytes in the trailing CRC field.
 */
#define	ETHER_CRC_LEN		4

/*
 * The length of the combined header.
 */
#define	ETHER_HDR_LEN		(ETHER_ADDR_LEN*2+ETHER_TYPE_LEN)

/*
 * The minimum packet length.
 */
#define	ETHER_MIN_LEN		64

/*
 * The maximum packet length.
 */
#define	ETHER_MAX_LEN		1518

/*
 * A macro to validate a length with
 */
#define	ETHER_IS_VALID_LEN(foo)	\
	((foo) >= ETHER_MIN_LEN && (foo) <= ETHER_MAX_LEN)

/*
 * Structure of a 10Mb/s Ethernet header.
 */
struct	ether_header {
	u_char	ether_dhost[ETHER_ADDR_LEN];
	u_char	ether_shost[ETHER_ADDR_LEN];
	u_short	ether_type;
};

/*
 * Structure of a 48-bit Ethernet address.
 */
struct	ether_addr {
	u_char octet[ETHER_ADDR_LEN];
};

#define	ETHERTYPE_PUP		0x0200	/* PUP protocol */
#define	ETHERTYPE_IP		0x0800	/* IP protocol */
#define	ETHERTYPE_ARP		0x0806	/* Addr. resolution protocol */
#define	ETHERTYPE_REVARP	0x8035	/* reverse Addr. resolution protocol */
#define	ETHERTYPE_VLAN		0x8100	/* IEEE 802.1Q VLAN tagging */
#define	ETHERTYPE_IPV6		0x86dd	/* IPv6 */
#define	ETHERTYPE_PTP		0x88f7	/* PTP */
#define	ETHERTYPE_LOOPBACK	0x9000	/* used to test interfaces */
/* XXX - add more useful types here */

/*
 * The ETHERTYPE_NTRAILER packet types starting at ETHERTYPE_TRAIL have
 * (type-ETHERTYPE_TRAIL)*512 bytes of data followed
 * by an ETHER type (as given above) and then the (variable-length) header.
 */
#define	ETHERTYPE_TRAIL		0x1000		/* Trailer packet */
#define	ETHERTYPE_NTRAILER	16

#define	ETHERMTU	(ETHER_MAX_LEN-ETHER_HDR_LEN-ETHER_CRC_LEN)
#define	ETHERMIN	(ETHER_MIN_LEN-ETHER_HDR_LEN-ETHER_CRC_LEN)

/*
 * Clarinet
 * The following macros are required as they are used in all the
 * driver header files which include if_ether.h
 */

/*
 * for compilers that have 4-bytes structure alignment rule,
 * it is understood that sizeof (ether_header) is 0x10
 */
#define SIZEOF_ETHERHEADER      0xe

 /* For tagged Ethernet headers */
#define SIZEOF_TAG_ETHERHEADER      0x12

 /* minimal size of an ethernet frame including the headers supported
  * by most ethernet chips.
  */
#define ETHERSMALL      60

/* End of Clarinet introduced macros */


/*
 * For device drivers to specify whether they support BPF or not
 */
#define ETHER_BPF_UNSUPPORTED	0
#define ETHER_BPF_SUPPORTED	1

#ifdef __cplusplus
}
#endif
#endif /* !_NET_ETHERNET_H_ */
