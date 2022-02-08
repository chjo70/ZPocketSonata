/* ipcom_forward_svlan.h - VLAN stacking MNT head file */

/*
 * Copyright (c) 2010 Wind River Systems, Inc.
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
01b,11jan11,tlu  Added macro to remove VLAN tags
01a,17nov10,tlu  Moved inline functions from ipcom_forwarder_svlan.c
*/

#ifndef IPCOM_FORWARDER_SVLAN_H
#define IPCOM_FORWARDER_SVLAN_H

/*
 ****************************************************************************
 * 1                    DESCRIPTION
 ****************************************************************************
 */

/*
 ****************************************************************************
 * 2                    CONFIGURATION
 ****************************************************************************
 */

#include "ipcom_config.h"


#if defined(IPCOM_USE_FORWARDER_VLAN_STACKING)

#include "ipcom_forwarder.h"
#include "ipcom_nae.h"


#ifdef IPCOM_USE_NEHALEM_FORWARDER
#include "ipcom_vxworks_nehalem_svlan.h"
#endif

#ifdef IPCOM_USE_OCTEON_FORWARDER
#include "ffsLib.h"
#endif


/*
 ****************************************************************************
 * 3                    INCLUDE FILES
 ****************************************************************************
 */


#ifdef __cplusplus
extern "C" {
#endif

/*
 ****************************************************************************
 * 4                    DEFINES
 ****************************************************************************
 */

#define FWD_SVLAN_RX(pkt, msg, ipprt, fw, ret) \
{ \
    switch (ipcom_fw->port_type[ipprt]) \
    { \
        case IPCOM_FWD_VLAN_PORT_CS: \
            ret = ipcom_svlan_cs_rx(pkt, msg, ipprt, fw); \
            break; \
        case IPCOM_FWD_VLAN_PORT_SC: \
            ret = ipcom_svlan_sc_rx(pkt, msg, ipprt, fw); \
            break; \
        case IPCOM_FWD_VLAN_PORT_S: \
            ret = ipcom_svlan_s_rx(pkt, msg, ipprt, fw); \
	    break; \
    } \
}


#define FWD_SVLAN_FMT(ipprt, fw_msg, ix_num) \
{ \
    switch (ipcom_fw->port_type[ipprt]) \
    { \
        case IPCOM_FWD_VLAN_PORT_CS: \
            ipcom_svlan_cs_fmt(fw_msg, ix_num); \
	    break; \
        case IPCOM_FWD_VLAN_PORT_SC: \
            ipcom_svlan_sc_fmt(fw_msg, ix_num); \
	    break; \
    } \
}

#define FWD_SVLAN_REMOVE_TAGS(fw_msg) \
{ \
    /* remove VLAN tags */ \
    switch ((fw_msg->pkt_flags & IPCOM_FWD_VLAN_PKT_SVTAG) | \
            (fw_msg->pkt_flags & IPCOM_FWD_VLAN_PKT_CVTAG)) \
    { \
        case 1: \
            /* 01: S-VLAN tag */ \
        case 2: \
            /* 10: C-VLAN tag */ \
            /* remove S-VLAN/C-VLAN tag */ \
            *(Ip_u64 *)(fw_msg->packet+8) = *(Ip_u64 *)(fw_msg->packet+4); \
            *(Ip_u32 *)(fw_msg->packet+4) = *(Ip_u32 *)(fw_msg->packet); \
            fw_msg->packet += 4; \
	    fw_msg->len_mod = -4; \
            break; \
        case 3: \
            /* 11: S-VLAN tag + C-VLAN tag */ \
            /* remove S-VLAN + C-VLAN tags */ \
            *(Ip_u64 *)(fw_msg->packet+12) = *(Ip_u64 *)(fw_msg->packet+4); \
            *(Ip_u32 *)(fw_msg->packet+8) = *(Ip_u32 *)(fw_msg->packet); \
            fw_msg->packet += 8; \
	    fw_msg->len_mod = -8; \
    } \
}


/* Define the following flag to build debug msg into image */
/* #define FW_VLAN_DEBUG */


/*
 ****************************************************************************
 * 5                    TYPES
 ****************************************************************************
 */

typedef struct fw_mac_station_s
{
    Ip_u16      last_used_time;
    Ip_u8       macAddr_svid[8];      /* MAC address + S-VID (last 2 bytes) */
    Ip_u8       ipprt;                /* input physical port */
}
fw_mac_station_t;

IP_EXTERN  fw_mac_station_t  *mac_stations;
IP_EXTERN  Ip_time_t svlan_time;

IP_EXTERN int (*ipcom_forwarder_vlan_hw_tx[MAX_FW_PORTS])
                        (fw_msg_t *fw_msg, void *fw_cookie);



IP_INLINE unsigned
ipcom_vlan_hash_update(const void *key_param, int key_len, unsigned initval, int type) 
{
    unsigned a , b;
    unsigned len;
    const Ip_u8 *key = key_param;

   /* Set up the internal state */
   len = (unsigned) key_len;
   a = initval;
   b = len;

   while (len >= 4)
   {
       a += key[0] + (key[1] << 8) + (key[2] << 16) + (key[3] << 24);
       b +=  (a << 3);
       a += ~(b << 11);
       b ^=  (a >> 16);
       key += 4; len -= 4;
   }

   /* All the case statements fall through */
   switch (len)
   {
       case 3 : a += key[2] << 16;
       case 2 : b ^= key[1] << 8;
       case 1 : a += key[0];
       default: break;
   }

   a ^=  (b >> 6);
   b += ~(a << 15);
   a ^=  (b >> 10);
   return a + b;
}


/*
 *===========================================================================
 *                    ipcom_svlan_copy_pkt
 *===========================================================================
 * Description: Copy a pkt, first 64 bits, then 32, then 16, last 8
 * Parameters:  copy_to  : the pkt to copy to
 *              copy_from: the pkt to copy from
 *              len   : the copy length in bytes
 */
IP_STATIC __inline__ void
ipcom_svlan_copy_pkt(Ip_u8 *copy_to, Ip_u8 *copy_from, Ip_u16 len)
{
    Ip_u16  num, i = len & 0x7;
    Ip_u16  rem = len - i;

    for (num = 0; num < rem; num += 8)
        *(Ip_u64 *)(&(copy_to[num])) = *(Ip_u64 *)(&(copy_from[num]));

    if (i >= 4)
    {
        *(Ip_u32 *)(&(copy_to[num])) = *(Ip_u32 *)(&(copy_from[num]));
        num += 4;
        i -= 4;
    }

    if (i >= 2)
    {
        *(Ip_u16 *)(&(copy_to[num])) = *(Ip_u16 *)(&(copy_from[num]));
        num += 2;
        i -= 2;
    }

    if (i >= 1)
        *(Ip_u8 *)(&(copy_to[num])) = *(Ip_u8 *)(&(copy_from[num]));
}


/*
 *===========================================================================
 *                      ipcom_forwarder_mac_learning
 *===========================================================================
 * Description: Add a MAC address to station list
 * Parameters:
 * Returns:
 *
 */
IP_INLINE void
ipcom_forwarder_mac_learning(int port, Ip_u8 *mac, Ip_u16 svid)
{
    fw_mac_station_t  *station, *new_station = IP_NULL;
    Ip_u8  key[8], i;
    unsigned  hash_val;
    Ip_u16    hash_bucket;
    Ip_bool not_found = IP_TRUE;


#ifdef FW_VLAN_DEBUG
ipcom_printf("mac_learning: port %d, mac: %x %x %x %x %x %x, svid %d\n",
        port, *mac, *(mac+1), *(mac+2), *(mac+3), *(mac+4), *(mac+5), svid);
#endif

    /* form the hash key: mac address + svid */
    *(Ip_u16 *)key = *(Ip_u16 *)mac;
    *(Ip_u32 *)(&(key[2])) = *(Ip_u32 *)(&(mac[2]));
    *(Ip_u16 *)(&(key[6])) = svid;

    /* calculate hash value */
    hash_val = ipcom_vlan_hash_update(key, 8, 0, 0);

    /* record the MAC station */
    hash_bucket = (hash_val & 0x3ff) << 2;
    station = &(mac_stations[hash_bucket]);

    for (i = 0; i < 4; i++, station++)
    {
        if (*(Ip_u64 *)key == *(Ip_u64 *)(station->macAddr_svid))
        {
            /* station already recorded, update the last used time and port */
            station->last_used_time = svlan_time;
            station->ipprt = port;
#ifdef FW_VLAN_DEBUG
ipcom_printf("mac_learning: station exist already\n");
#endif
            return;
        }
        else if ((*(Ip_u16 *)(&(station->macAddr_svid[6])) == 0) && not_found)
        {
            /* an open slot, to record the new MAC station */
            new_station = station;
            not_found = IP_FALSE;
        }
    }

    if (new_station == IP_NULL)
        /* all slots are currently used, overwrite a random slot */
        new_station = &(mac_stations[hash_bucket+(svlan_time & 0x3)]);

    /* Record the new MAC station info */
    new_station->last_used_time = svlan_time;
    new_station->ipprt = port;
    *(Ip_u64 *)(new_station->macAddr_svid) = *(Ip_u64 *)key;

#ifdef FW_VLAN_DEBUG
ipcom_printf("mac_learning: added new station\n");
#endif
}


/*
 *===========================================================================
 *                      ipcom_forwarder_get_mac
 *===========================================================================
 * Description: Search a MAC address in station lists
 * Parameters:
 * Returns:
 *
 */
IP_STATIC __inline__ fw_mac_station_t *
ipcom_forwarder_get_mac(fw_msg_t *msg)
{
    fw_mac_station_t  *station;
    Ip_u8  key[8], i;
    unsigned  hash_val;

#ifdef FW_VLAN_DEBUG
ipcom_printf("ipcom_forwarder_get_mac, mac: %x %x %x %x %x %x, svid %d\n",
        msg->packet[0], msg->packet[1], msg->packet[2],
        msg->packet[3], msg->packet[4], msg->packet[5],
        msg->evlan->s_vlan_id);
#endif

    /* form the hash key: mac address + svid */
    *(Ip_u64 *)key = *(Ip_u64 *)msg->packet;
    *(Ip_u16 *)(&(key[6])) = msg->evlan->s_vlan_id;

    /* calculate hash value */
    hash_val = ipcom_vlan_hash_update(key, 8, 0, 1);

    /* search the MAC station */
    station = &(mac_stations[(hash_val & 0x3ff) << 2]);
    for (i = 0; i < 4; i++, station++)
    {
        if (*(Ip_u64 *)key == *(Ip_u64 *)(station->macAddr_svid))
            return station;
    }
    return IP_NULL;
}


/*
 *===========================================================================
 *                      ipcom_forwarder_lkup_mac
 *===========================================================================
 * Description: Search a MAC address in station lists
 * Parameters:
 * Returns:
 *
 */
IP_STATIC __inline__ int
ipcom_forwarder_lkup_mac(fw_msg_t *msg)
{
    fw_mac_station_t *station;


#ifdef FW_VLAN_DEBUG
ipcom_printf("ipcom_forwarder_lkup_mac, mac: %x %x %x %x %x %x, svid %d\n",
        msg->packet[0], msg->packet[1], msg->packet[2],
        msg->packet[3], msg->packet[4], msg->packet[5],
        msg->evlan->s_vlan_id);
#endif

    station = ipcom_forwarder_get_mac(msg);
    if (station)
    {
        /* found the station, update the last used time */
        station->last_used_time = svlan_time;

        /* check whether the port is one of tx ports */
        if (msg->evlan->tx_ports[station->ipprt>>5] &
                (1 << (station->ipprt&0x1f)))
        {
#ifdef FW_VLAN_DEBUG
ipcom_printf("ipcom_forwarder_lkup_mac, station rtn %d\n", station->ipprt);
#endif
            return station->ipprt;
        }
    }

#ifdef FW_VLAN_DEBUG
ipcom_printf("ipcom_forwarder_lkup_mac, no station found, rtn -1\n");
#endif
    return -1;
}


/*
 *===========================================================================
 *                    ipcom_svlan_cs_fmt
 *===========================================================================
 * Context:
 * Description:  Format output VLAN stacking frame from CS port to SC port.
 *               Insert S-VLAN tag.
 * Parameters:
 * Returns:
 *
 */
IP_STATIC __inline__ void
ipcom_svlan_cs_fmt(fw_msg_t *fw_msg, Ip_u8 ix)
{
    Ip_u8  *pkt_ptr;


#ifdef FW_VLAN_DEBUG
ipcom_printf("Enter ipcom_svlan_cs_fmt, ix %d, fw_msg->packet %x\n",
          ix, fw_msg->packet);
/*
{
int i;
for (i = 0; i < 40; i++)
    printf("%x ", *((Ip_u8 *)(fw_msg->packet + i)));
printf("\n");
}
*/
#endif

    /* Re-map the rx pkt's priority */
    if (!(fw_msg->pkt_flags & IPCOM_FWD_VLAN_PKT_MAPED))
    {
        fw_msg->pkt_flags |= IPCOM_FWD_VLAN_PKT_MAPED;
        if (fw_msg->stci)
          fw_msg->spri = fw_msg->evlan->pri_mapping[(fw_msg->stci&0xe000)>>13];
        else if (fw_msg->ctci)
          fw_msg->spri = fw_msg->evlan->pri_mapping[(fw_msg->ctci&0xe000)>>13];
        else
          fw_msg->spri = fw_msg->evlan->pri_mapping[0];
    }

    /* Check on the VLAN tags */
    switch ((fw_msg->pkt_flags & IPCOM_FWD_VLAN_PKT_SVTAG) |
            (fw_msg->pkt_flags & IPCOM_FWD_VLAN_PKT_CVTAG) |
            (ipcom_fw->rule_flags[ix] & IPCOM_FWD_VLAN_ADD_CVLAN))
    {
    case 2:
        /* 010: C-VLAN + egress rule as remove C-VLAN */
        /* modify C-VLAN to S-VLAN */
        *(Ip_u32 *)(fw_msg->packet+LL_ETH_ADDRS_SZ) =
                                fw_msg->evlan->s_vlan_tag +
                                ip_htonl((fw_msg->spri << 13) & 0xe000);
#ifdef IPCOM_USE_OCTEON_FORWARDER
        fw_msg->pkt_flags &= ~IPCOM_FWD_VLAN_PKT_CVTAG;
        fw_msg->pkt_flags |= IPCOM_FWD_VLAN_PKT_SVTAG;
#endif
        return;

    case 4:
        /* 100: egress rule as add C-VLAN */
        /* add two VLAN tags: S-VLAN + C-VLAN */
        /* copy dst + src MAC addresses: add space for 2 VLAN tags */
        *(Ip_u64 *)(fw_msg->packet-8) = *(Ip_u64 *)(fw_msg->packet);
        *(Ip_u32 *)(fw_msg->packet) = *(Ip_u32 *)(fw_msg->packet+8);

        /* Insert S-VLAN */
        *(Ip_u32 *)(fw_msg->packet+4) = fw_msg->evlan->s_vlan_tag +
                                ip_htonl((fw_msg->spri << 13) & 0xe000);

        /* insert C-VLAN tag */
        *(Ip_u32 *)(fw_msg->packet+8) = fw_msg->evlan->c_vlan_tag;

        fw_msg->packet -= 8;
	fw_msg->len_mod = 8;
#ifdef IPCOM_USE_OCTEON_FORWARDER
        fw_msg->pkt_flags|=(IPCOM_FWD_VLAN_PKT_SVTAG|IPCOM_FWD_VLAN_PKT_CVTAG);
#endif
        return;

    case 0:
        /* 000: egress rule as no C-VLAN */
    case 6:
        /* 110: C-VLAN + egress rule as keep C-VLAN */
        /* add S-VLAN */
        /* copy dst + src MAC addresses: add space for one VLAN tag */
        *(Ip_u64 *)(fw_msg->packet-4) = *(Ip_u64 *)(fw_msg->packet);
        *(Ip_u32 *)(fw_msg->packet+4) = *(Ip_u32 *)(fw_msg->packet+8);

        /* Insert S-VLAN */
        *(Ip_u32 *)(fw_msg->packet+8) = fw_msg->evlan->s_vlan_tag +
                                ip_htonl((fw_msg->spri << 13) & 0xe000);

        fw_msg->packet -= 4;
	fw_msg->len_mod = 4;
#ifdef IPCOM_USE_OCTEON_FORWARDER
        fw_msg->pkt_flags |= IPCOM_FWD_VLAN_PKT_SVTAG;
#endif
        return;

    case 3:
        /* 011: S-VLAN + C-VLAN + egress rule as remove C-VLAN */
        /* remove C-VLAN */
        /* copy dst+src MAC addr + S-VLAN: remove space for one VLAN tag */
        pkt_ptr = fw_msg->packet+LL_ETH_ADDRS_SZ;
        *(Ip_u64 *)pkt_ptr = *(Ip_u64 *)(pkt_ptr - 4);
        *(Ip_u64 *)(pkt_ptr-8) = *(Ip_u64 *)(pkt_ptr - 12);

        /* modify S-VLAN */
        fw_msg->packet += 4;
        *(Ip_u32 *)(fw_msg->packet+LL_ETH_ADDRS_SZ) =
                                fw_msg->evlan->s_vlan_tag +
                                ip_htonl((fw_msg->spri << 13) & 0xe000);
	fw_msg->len_mod = -4;
#ifdef IPCOM_USE_OCTEON_FORWARDER
        fw_msg->pkt_flags &= ~IPCOM_FWD_VLAN_PKT_CVTAG;
#endif
        return;

    case 5:
        /* 101: S-VLAN + egress rule as add C-VLAN */
        /* insert C-VLAN */
        /* copy dst+src MAC addr + S-VLAN: add space for one VLAN tag */
        *(Ip_u64 *)(fw_msg->packet-4) = *(Ip_u64 *)(fw_msg->packet);
        *(Ip_u64 *)(fw_msg->packet+4) = *(Ip_u64 *)(fw_msg->packet + 8);

        /* insert C-VLAN tag */
        *(Ip_u32 *)(fw_msg->packet+12) = fw_msg->evlan->c_vlan_tag;

        /* modify S-VLAN */
        fw_msg->packet -= 4;
        *(Ip_u32 *)(fw_msg->packet+LL_ETH_ADDRS_SZ) =
                                fw_msg->evlan->s_vlan_tag +
                                ip_htonl((fw_msg->spri << 13) & 0xe000);
	fw_msg->len_mod = 4;
#ifdef IPCOM_USE_OCTEON_FORWARDER
        fw_msg->pkt_flags |= IPCOM_FWD_VLAN_PKT_CVTAG;
#endif
        return;

    case 1:
        /* 001: S-VLAN + egress rule as no C-VLAN */
    case 7:
        /* 111: S-VLAN + C-VLAN + egress rule as keep C-VLAN */
        /* modify S-VLAN */
        *(Ip_u32 *)(fw_msg->packet+LL_ETH_ADDRS_SZ) =
                                fw_msg->evlan->s_vlan_tag +
                                ip_htonl((fw_msg->spri << 13) & 0xe000);
        return;
    }
}


/*
 *===========================================================================
 *                    ipcom_svlan_sc_fmt
 *===========================================================================
 * Context:
 * Description:  Format output VLAN stacking frame from SC port to CS port.
 *               Remove S-VLAN tag.
 * Parameters:
 * Returns:
 *
 */
IP_STATIC __inline__ void
ipcom_svlan_sc_fmt(fw_msg_t *fw_msg, Ip_u8 ix)
{
    Ip_u8  *pkt_ptr;


#ifdef FW_VLAN_DEBUG
ipcom_printf("Enter ipcom_svlan_sc_fmt, ix %d, fw_msg->packet %x\n",
          ix, fw_msg->packet);
/*
{
int i;
for (i = 0; i < 40; i++)
    printf("%x ", *((Ip_u8 *)(fw_msg->packet + i)));
printf("\n");
}
*/
#endif

    /* Check on the VLAN tags and egress rule */
    switch ((fw_msg->pkt_flags & IPCOM_FWD_VLAN_PKT_SVTAG) |
            (fw_msg->pkt_flags & IPCOM_FWD_VLAN_PKT_CVTAG) |
            (ipcom_fw->rule_flags[ix] & IPCOM_FWD_VLAN_ADD_CVLAN))
    {
    case 5:
        /* 101: S-VLAN + egress rule as add C-VLAN */
        /* modify S-VLAN to C-VLAN */
        *(Ip_u32 *)(fw_msg->packet+LL_ETH_ADDRS_SZ) =
                                fw_msg->evlan->c_vlan_tag;
#ifdef IPCOM_USE_OCTEON_FORWARDER
        fw_msg->pkt_flags |= IPCOM_FWD_VLAN_PKT_CVTAG;
        fw_msg->pkt_flags &= ~IPCOM_FWD_VLAN_PKT_SVTAG;
#endif
        return;

    case 3:
        /* 011: S-VLAN + C-VLAN + egress rule as remove C-VLAN */
        /* remove two VLAN tags: S-VLAN + C-VLAN */
        /* copy dst + src MAC addresses: remove space for 2 VLAN tags */
        pkt_ptr = fw_msg->packet+LL_ETH_ADDRS_SZ;
        *(Ip_u64 *)pkt_ptr = *(Ip_u64 *)(pkt_ptr-8);
        *(Ip_u32 *)(pkt_ptr-4) = *(Ip_u32 *)(pkt_ptr-12);

        fw_msg->packet += 8;
	fw_msg->len_mod = -8;
#ifdef IPCOM_USE_OCTEON_FORWARDER
        fw_msg->pkt_flags &= ~IPCOM_FWD_VLAN_PKT_CVTAG;
        fw_msg->pkt_flags &= ~IPCOM_FWD_VLAN_PKT_SVTAG;
#endif
        return;

    case 1:
        /* 001: S-VLAN + egress rule as no C-VLAN */
    case 7:
        /* 111: S-VLAN + C-VLAN + egress rule as keep C-VLAN */
        /* remove S-VLAN */
        /* copy dst + src MAC addresses: remove space for one VLAN tag */
        pkt_ptr = fw_msg->packet+LL_ETH_ADDRS_SZ;
        *(Ip_u64 *)(pkt_ptr-4) = *(Ip_u64 *)(pkt_ptr-8);
        *(Ip_u32 *)(pkt_ptr-8) = *(Ip_u32 *)(pkt_ptr-12);

        fw_msg->packet += 4;
	fw_msg->len_mod = -4;
#ifdef IPCOM_USE_OCTEON_FORWARDER
        fw_msg->pkt_flags &= ~IPCOM_FWD_VLAN_PKT_SVTAG;
#endif
        return;

    case 0:
        /* 000: egress rule as no C-VLAN */
    case 6:
        /* 110: C-VLAN + egress rule as keep  C-VLAN */
        /* nothing to do */
        return;

    case 2:
        /* 010: C-VLAN + egress rule as remove C-VLAN */
        /* remove C-VLAN */
        /* copy dst + src MAC addresses: remove space for one VLAN tag */
        pkt_ptr = fw_msg->packet+LL_ETH_ADDRS_SZ;
        *(Ip_u64 *)(pkt_ptr-4) = *(Ip_u64 *)(pkt_ptr-8);
        *(Ip_u32 *)(pkt_ptr-8) = *(Ip_u32 *)(pkt_ptr-12);

        fw_msg->packet += 4;
	fw_msg->len_mod = -4;
#ifdef IPCOM_USE_OCTEON_FORWARDER
        fw_msg->pkt_flags &= ~IPCOM_FWD_VLAN_PKT_CVTAG;
#endif
        return;

    case 4:
        /* 100: egress rule as add C-VLAN */
        /* add C-VLAN */
        /* copy dst + src MAC addresses: add space for one VLAN tag */
        *(Ip_u64 *)(fw_msg->packet-4) = *(Ip_u64 *)(fw_msg->packet);
        *(Ip_u32 *)(fw_msg->packet+4) = *(Ip_u32 *)(fw_msg->packet+8);

        *(Ip_u32 *)(fw_msg->packet+8) = fw_msg->evlan->c_vlan_tag;
        fw_msg->packet -= 4;
	fw_msg->len_mod = 4;
#ifdef IPCOM_USE_OCTEON_FORWARDER
        fw_msg->pkt_flags |= IPCOM_FWD_VLAN_PKT_CVTAG;
#endif
        return;
    }
}


/*
 *===========================================================================
 *                    ipcom_forwarder_vlan_tx
 *===========================================================================
 * Context:
 * Description:  Transmit a VLAN stacking frame
 * Parameters:
 * Returns:
 *
 */
IP_STATIC __inline__ int
ipcom_forwarder_vlan_tx(fw_msg_t *fw_msg, void *fw_cookie)
{
    int  ix_num = 0;
    fw_mac_station_t *station;

#ifdef FW_VLAN_DEBUG
ipcom_printf("Enter ipcom_forwarder_vlan_tx, ipprt %d\n", fw_msg->ipprt);
#endif


    /* Check whether dst MAC is on the receiving link */
    station = ipcom_forwarder_get_mac(fw_msg);
    if (station && (station->ipprt == fw_msg->ipprt))
    {
        /* dst MAC on the same link, don't forward, drop the pkt */
        ipcom_forwarder_drop_fw_msg(fw_msg, fw_cookie);
#ifndef SVLAN_SC_FWD_TABLE
        if (ipcom_fw->port_type[fw_msg->ipprt] & IPCOM_FWD_VLAN_PORT_SC)
            ipcom_free(fw_msg->evlan);
#endif
        return 0;
    }

#ifdef FW_VLAN_DEBUG
ipcom_printf("ipcom_forwarder_vlan_tx: pkt_flags %x, MBCAST %x, & %d\n",
                fw_msg->pkt_flags, IPCOM_FWD_VLAN_PKT_BMCAST,
                fw_msg->pkt_flags & IPCOM_FWD_VLAN_PKT_BMCAST);
#endif

    fw_msg->len_mod = 0;
    if (!(fw_msg->pkt_flags & IPCOM_FWD_VLAN_PKT_BMCAST))
    {
        if (fw_msg->evlan->tx_ports_num == 1)
        {
            /* only one tx port, get the port number */
#ifdef IPCOM_USE_OCTEON_FORWARDER
	    ix_num = FFS_LSB(fw_msg->evlan->tx_ports[0]?
		             fw_msg->evlan->tx_ports[0]:
			     fw_msg->evlan->tx_ports[1]) - 1;
#else
            while ((fw_msg->evlan->tx_ports[ix_num>>5]&(1<<(ix_num&0x1f)))==0)
                ix_num ++;
#endif
        }
        else
        {
            /* get the port with dst MAC in station list */
            ix_num = ipcom_forwarder_lkup_mac(fw_msg);
            if (IP_LIKELY(ix_num < 0))   goto multi_tx;
        }

#ifdef FW_VLAN_DEBUG
ipcom_printf("ipcom_forwarder_vlan_tx: ix_num %d, tx_ports_num %d\n",
                ix_num, fw_msg->evlan->tx_ports_num);
#endif

        /* output to one port */
	FWD_SVLAN_FMT(fw_msg->ipprt, fw_msg, ix_num);

#ifdef FW_VLAN_DEBUG
ipcom_printf("ipcom_forwarder_vlan_tx: single port %d, to forwarder_tx_fw\n",
        ix_num);
#endif

#ifndef SVLAN_SC_FWD_TABLE
        if (ipcom_fw->port_type[fw_msg->ipprt] & IPCOM_FWD_VLAN_PORT_SC)
            ipcom_free(fw_msg->evlan);
#endif
        return ipcom_forwarder_tx_fw(ix_num, fw_msg, fw_cookie);
    }

    /* output to multiple ports */
  multi_tx:
#ifdef FW_VLAN_DEBUG
ipcom_printf("ipcom_forwarder_vlan_tx: multi ports, tx_ports_num %d\n",
        fw_msg->evlan->tx_ports_num);
#endif

#ifdef SVLAN_SC_FWD_TABLE
    return ipcom_forwarder_vlan_hw_tx[fw_msg->ipprt](fw_msg, fw_cookie);
#else
    ipcom_forwarder_vlan_hw_tx[fw_msg->ipprt](fw_msg, fw_cookie);
    if (ipcom_fw->port_type[fw_msg->ipprt] & IPCOM_FWD_VLAN_PORT_SC)
        ipcom_free(fw_msg->evlan);
    return 0;
#endif
}


#ifdef __cplusplus
}
#endif

#endif

#endif
/*
 ****************************************************************************
 *                      END OF FILE
 ****************************************************************************
 */
