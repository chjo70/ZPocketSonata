/* muxL2VlanLibP.h - private definitions for the L2 VLAN MUX library */

/*
 * Copyright (c) 1996-2007 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01i,30jul07,kch  Added MUX-L2 hardware capabilities macros.
01h,30sep05,kch  Added portCfi member to MUX_L2_PORT.
01g,15sep05,kch  Moved MAX_VID, MIN_VID, MAX_VID, MIN_USER_PRIORITY,
                 MAX_USER_PRIORITY, IS_VALID_VID and IS_VALID_PRORITY macros
                 to muxL2Lib.h (SPR #112513).
01f,14sep05,kch  Changed MUX_L2_VLAN_STATISTICS define to MUX_L2_VLAN_STAT.
                 Also renamed MUX_L2_VLAN_STAT structure tag to 
                 MUX_L2_VLAN_PORT_STAT (SPR #112513).
01e,07sep05,kch  Replaced vlanHwTaggingSupport and vlanMtuSupport booleans
                 with hwCaps that uses bit fields.
01d,27aug05,kch  Renamed vlan id defines to reflect its actual usage.
01c,24aug05,kch  Added MUX_L2_VLAN_STAT data structure and related macros.
                 Also added muxL2PortInDiscards and muxL2PortOutDiscards
                 to MUX_L2_PORT. 
01b,23aug05,kch  Added hwMtu as well as pointer to END_OBJ and NET_FUNCS 
                 to MUX_L2_PORT. Moved vlan tag related macros to muxL2Lib.h.
01a,20jul05,kch  written.
*/

#ifndef __INCmuxL2VlanLibPh
#define __INCmuxL2VlanLibPh

#include <muxL2Lib.h>
#include <endLib.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _WRS_KERNEL

/* possible ethernet frame format */
typedef enum {
    ETHER_TYPE2_FRAME_FORMAT = 0x01,
    ETHER_8023_FRAME_FORMAT,
    UNKNOWN_FRAME_FORMAT 
} ETHER_FRAME_FORMAT;

typedef enum {
    VLAN_TAGGED_FRAME = 1,
    PRIORITY_TAGGED_FRAME,
    UNTAGGED_FRAME,
    INVALID_TAGGED_FRAME
} ETHER_FRAME_TYPE;

/* defines */ 
#define LLC_SNAP_FRAME_LEN    8

/* 
 * LLC with DSAP and SSAP of 0x42 is reserved for IEEE 802.1 use. 
 * These 802.3 ethernet encapsulation is used by Layer 2 protocols
 * such as STP, GVRP, and GMRP.
 */
#define LLC_SAP         0x42

#define RESERVED_VID         4095     /* for internal use */


/* 
 * The following defines are the default port-base vlan setting maintained
 * by the Layer 2 MUX. 
 */
#define DEFAULT_PORT_VID                1
#define DEFAULT_PORT_USER_PRIORITY      0
#define DEFAULT_PORT_INGRESS_TYPE       ADMIT_ALL_FRAMES
#define DEFAULT_PORT_INGRESS_FILTER     FALSE
#define DEFAULT_PORT_EGRESS_TYPE        UNTAGGED_FRAME

/* 
 * Marco for MUX-L2 Hardware L2 capabilities (used internally). These
 * hardware capabilities macros are added to provide additional flexbility 
 * to MUX-L2 to distinguish the hardware (vlan tagging) capabilities for 
 * ingress and egress.
 */

/* hardware supports VLAN-compatible MTU */
#define MUX_L2_HW_CAP_VLAN_MTU           0x01

/* 
 * hardware supports extracting vlan tag from the received frame and stores
 * the vlan tag information in m_pkthdr.vlan in host-byte order with the
 * CSUM_VLAN CSUM flags set. The ethernet header from the received frame will 
 * be untagged. 
 */
#define MUX_L2_HW_CAP_TAGGING_RX         0x02

/*
 * hardware supports inserting vlan tag to ethernet header on egress using
 * vlan tag information that is stored in m_pkthdr.vlan (in host-byte order)
 * if the CSUM_VLAN CSUM flags is set.
 */
#define MUX_L2_HW_CAP_TAGGING_TX         0x04

#ifdef MUX_L2_VLAN_STATS
typedef struct mux_l2_vlan_port_stat
    {
    /*
     * The number of valid frames received by this port which were classified
     * as belonging to this vlan.
     * RFC2674 MIB object: dot1qTpVlanPortInFrames
     */
    unsigned long muxL2VlanPortInFrames;

    /*
     * The number of valid frames transmitted by this port for this vlan.
     * RFC2674 MIB object: dot1qTpVlanPortOutFrames
     */
    unsigned long muxL2VlanPortOutFrames;

    /*
     * The number of valid frames received by this port which were classified
     * as belonging to this vlan but were discarded due to vlan related
     * reasons. Specifically, the IEEE 802.1Q counters for Discard Inbound.
     * RFC2674 MIB object: dot1qTpVlanPortInDiscards
     * The description for the MIB object specifies that this object also
     * implements the IEEE 802.1Q counter for Discard Ingress Filtering.
     * We don't keep track that here because if a frame is discarded by
     * ingress filtering, the port is not a member of the vlan, hence,
     * the MUX_L2_VLAN_STAT is not allocated for that vlan for the port.
     */
    unsigned long muxL2VlanPortInDiscards;

    } MUX_L2_VLAN_PORT_STAT;

#endif /* MUX_L2_VLAN_STATS */


/*
 * L2 per-port configuration
 */
typedef struct mux_l2_port
    {
    END_OBJ  *pEnd;   /* pointer back to the device's (END_OBJ *) */

    /* 
     * The Port VLAN ID that is assigned to untagged frames or priority-tagged 
     * frames received on this port. Default: 1
     * RFC2674 MIB object: dot1qPvid
     */
    unsigned short portVid;  /* Valid Vid: 1..4094 */

    /*
     * The default ingress User Priority for this port (assuming Ethernet 
     * media). Default: 0
     * RFC2674 MIB object: dot1dPortDefaultUserPriority
     */
    unsigned short portUpriority;  /* Valid Priority: 0..7 */

    /*
     * Canonical format indicator (CFI), 0 or 1.
     * - in token ring/source-routed FDDI MAC methods, this field is used
     *   to signal the bit order of address information carried in the
     *   encapsulated frame;
     * - in 802.3/Ethernet and transparent FDDI MAC methods, this field is
     *   used to signal the presence or absence of an Embedded Souce-Routing
     *   Information Field (E-RIF), and in combination with the Non-canonical
     *   Format Indicator (NCFI) carried in the RIF, to signal the bit order
     *   of address information carried in the encapsulated frame.
     * NOTE: For 802.3/Ethernet, MUX-L2 assumes this bit is always 0. That
     *       is, the received/transmitted tagged frame does not carry any
     *       embedded source routing information.
     */
    unsigned short portCfi;   

    /*
     * When set to ADMIT_TAGGED_ONLY_FRAMES(2), the device will discard 
     * untagged frames or priority-tagged frames received on this port. 
     * When set to ADMIT_ALL_FRAMES(1), untagged frames or priority-tagged 
     * frames received on this port will be accepted and assigned to the 
     * portPvid for this port.  
     * The setting does not affect VLAN independent BPDU frames, such as
     * GVRP and STP but it does affect VLAN dependent BPDU frames, such as
     * GMRP. Default: ADMIT_ALL_FRAMES(1)
     * RFC2674 MIB object: dot1qPortAcceptableFrameTypes
     */
    ACCEPT_FRAME_TYPE  portIngressAcceptFrameType;

    /* 
     * When this is true(1) the device will discard incoming frame for
     * VLANs which do not include this Port in its Member set. When
     * false(2), the port will accept all incoming frames. Default: false
     * RFC2674 MIB object: dot1qPortIngressFiltering. 
     */
    BOOL portIngressFilter;

#ifdef VLAN_TAG
    /* Function pointer for user-defined conversion function to convert
     * IP TOS field to the 3-bit 802.1Q user priority. The conversion 
     * routine takes the IP TOS value as its input and returns the vlan
     * user priority value (0-7) that needs to be inserted to the outgoing 
     * vlan tag header.
     */
    unsigned char (*portTos2UpConvRtn) (unsigned char); 
#endif /* VLAN_TAG */

    /*
     * VLAN membership for this L2 port. Each array element is a bit map
     * represents a set of 8 unique VLAN IDs, with the first octet specifies
     * VID 1 through 8, the second octet specifying VID 9 through 16, etc.
     * Within each octet, the most significant bit represents the highest
     * numbered VID. Thus, each VID is represented by a single bit. If that
     * bit has a value of 1, then this L2 port is the member for that VID;
     * the port is not a member its bit has a value of 0.
     */
    unsigned char portVidMemberMap[512];

    unsigned int  numVid;  /* number of vids configured for this port */

    /* hardware layer 2 capabilities flags */
    unsigned long hwCapabilities;

    /* original driver's NET_FUNCS table */
    NET_FUNCS *pEndNetFuncs;
    
    /* driver's address format - Ethernet Type 2 or 802.3 addressing */
    ETHER_FRAME_FORMAT endAddressFormat;

    int hwMtu;  /* hardware mtu size */

#ifdef MUX_L2_VLAN_STATS
    MUX_L2_VLAN_PORT_STAT **muxL2VlanStat;

    /*
     * The number of valid frames received by this port which were discarded
     * due to reasons such as vlan membership problem or invalid ingress
     * frame type. Specifically, this implements the IEEE 802.1Q counter for 
     * Discard Ingress Filtering.
     */
    unsigned long muxL2PortInDiscards;

    /*
     * The number of valid frames transmitted by this port which were
     * discarded due to reasons such as vlan membership problem or invalid 
     * egress frame type
     */
    unsigned long muxL2PortOutDiscards;
#endif /*  MUX_L2_VLAN_STATS */

    } MUX_L2_PORT;
 
#ifdef MUX_L2_VLAN_STATS

/*
 * Macros for MUX_L2_VLAN_STAT statistics that apply to the port/vlan pairing
 */
#define MUX_L2_VLAN_PORT_IN_FRAMES_COUNT(vlps) \
    { \
    if ((vlps) != NULL) \
        (vlps)->muxL2VlanPortInFrames++; \
    }

#define MUX_L2_VLAN_PORT_OUT_FRAMES_COUNT(vlps) \
    { \
    if ((vlps) != NULL) \
        (vlps)->muxL2VlanPortOutFrames++; \
    }

#define MUX_L2_VLAN_PORT_IN_DISCARDS_COUNT(vlps) \
    { \
    if ((vlps) != NULL) \
        (vlps)->muxL2VlanPortInDiscards++; \
    }

/*
 * Macro for MUX_L2_PORT statistics that apply to the port
 */
#define MUX_L2_PORT_IN_DISCARDS_COUNT(vlp)    vlp->muxL2PortInDiscards++;
#define MUX_L2_PORT_OUT_DISCARDS_COUNT(vlp)   vlp->muxL2PortOutDiscards++

#else /* MUX_L2_VLAN_STATS not defined */ 

#define MUX_L2_VLAN_PORT_IN_FRAMES_COUNT(vlps)
#define MUX_L2_VLAN_PORT_OUT_FRAMES_COUNT(vlps) 
#define MUX_L2_VLAN_PORT_IN_DISCARDS_COUNT(vlps)
#define MUX_L2_PORT_IN_DISCARDS_COUNT(vlp) 
#define MUX_L2_PORT_OUT_DISCARDS_COUNT(vlp)

#endif /* MUX_L2_VLAN_STATS */

#endif /* _WRS_KERNEL */

#ifdef __cplusplus
}
#endif

#endif /* __INCmuxL2VlanLibPh */
