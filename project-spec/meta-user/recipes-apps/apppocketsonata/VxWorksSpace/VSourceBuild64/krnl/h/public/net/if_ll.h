/* if_ll.h - layer 2 link level structure header file */
 
/*
 * Copyright (c) 2006,2013 Wind River Systems, Inc.
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
13jan14,h_s      Remove MPLS support. (US19989)
01a,30nov06,kch  Created.
 */

#ifndef _NET_IF_LL_H_
#define _NET_IF_LL_H_

#ifdef __cplusplus
 extern "C" {
#endif
 
/*
 * Frame Values
 * Used for 3rd argument to when creating packet sockets.
 */    
#define NET_ETH_P_ALL            0
#define NET_ETH_P_IP             0x0800
#define NET_ETH_P_ARP            0x0806
#define NET_ETH_P_RARP           0x8035
#define NET_ETH_P_IPV6           0x86DD
#define NET_ETH_P_PPPOE_DIS      0x8863
#define NET_ETH_P_PPPOE_SES      0x8864
#define NET_ETH_P_8021Q_VLAN     0x8100

/* Packet types 'sll_pkttype'.    Packet is addressed to: */
#define PACKET_HOST       1    /* this host */
#define PACKET_BROADCAST  2    /* all hosts on this link */
#define PACKET_MULTICAST  3    /* a multicast group this host is a member of */
#define PACKET_OTHERHOST  4    /* someone else */
#define PACKET_OUTGOING   5    /* Packet was sent and read back */


/*
 * The link level sockaddr is a device independent physical layer address.
 * It is used for packet socket to receive or send raw packets at the
 * Layer 2. 
 * 
 * When using the packet socket, the socket type is either SOCK_RAW for 
 * raw packets including the link level header or SOCK_DGRAM for cooked 
 * packets with the link level header removed. The link level header 
 * information is available in a common format in an sockaddr_ll. Allowed 
 * values for Ethernet are any of the NET_ETH_P_xxx constants in network 
 * 
 * When protocol is set to htons(NET_ETH_P_ALL), then all protocols are 
 * received. All incoming packets of that protocol type will be passed to 
 * the packet socket before they are passed to the protocols implemented in 
 * SOCK_RAW packets are passed to and from the device driver without any 
 * changes in the packet data. When receiving a packet, the address is still 
 * parsed and passed in a standard sockaddr_ll address structure. When 
 * transmitting a packet, the user-supplied buffer must contain the physical 
 * layer header. That packet is then queued, unmodified, to the network 
 * driver of the interface defined by the destination address.
 *
 * SOCK_DGRAM operates on a slightly higher level. The physical header is
 * removed before the packet is passed to the user. Packets sent through a
 * SOCK_DGRAM packet socket get a suitable physical layer header based on
 * the information in the sockaddr_ll destination address before they are 
 * queued.
 *
 * When sending packets using a packet socket, it is enough to specify
 * sll_family, sll_addr, sll_halen and sll_ifindex. All other fields
 * should be set to 0. The sll_hatype and sll_pkttype are set on
 * received packets.
 *
 * The connect() operation is not supported on packet sockets.
 */

struct sockaddr_ll
{
    u_int8_t    sll_len;        /* Length of this structure */
    u_int8_t    sll_family;     /* Always AF_PACKET */

    /* 
     * Link layer protocol (frame type) in network order, not used when 
     * sending frames on an SOCK_RAW type socket 
     */
    u_int16_t   sll_protocol;  
    u_int32_t   sll_ifindex;    /* Interface index, must not be zero */

    /* Link layer type (IFT_xxx), only used for received frames */
    u_int16_t   sll_hatype;     

    /* 
     * Packet type (PACKET_xxx), only used for received frames. Valid
     * types are:
     * PACKET_HOST - for packets addressed to the local host
     * PACKET_BROADCAST  - for physical layer broadcast packets to all 
     *                     hosts on this link
     * PACKET_MULTICAST - for packets sent to a physical layer multicast
     *                   address
     * PACKET_OTHERHOST - for packets send to some other host that has
     *                    been caught by a device driver in promiscuous
     *                    mode
     * PACKET_OUTGOING - for packets originated from local host that
     *                   is looped back to a packet socket.
     */
    u_int8_t    sll_pkttype;  
    
    u_int8_t    sll_halen;      /* Length of link layer address */
    u_int8_t    sll_addr[8];    /* Link layer address */
};


#ifdef __cplusplus
}
#endif
    
#endif /* _NET_IF_LL_H_ */
