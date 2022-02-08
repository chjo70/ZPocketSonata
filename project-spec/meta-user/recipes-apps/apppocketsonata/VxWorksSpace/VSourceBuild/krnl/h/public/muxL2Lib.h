/* muxL2Lib.h - definitions for the L2 MUX library */

/*
 * Copyright (c) 1996-2005, 2016 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
20may16,jxy  Clean coverity issue.
30sep05,kch  Added cfi to MUX_L2_PORT_VLAN.
27sep05,kch  Fixed documentation. Also removed the unsupported (unused)
                 MUXL2IOCSFLAGS and MUXL2IOCGFLAGS defines (SPR #112935).
15sep05,kch  Added MAX_VID, MIN_VID, MAX_VID, MIN_USER_PRIORITY,
                 MAX_USER_PRIORITY, IS_VALID_VID and IS_VALID_PRORITY macros
                 (SPR #112513).
31aug05,kch  Removed the non-standard global vlan id ioctl commands. Added
                 MUXL2IOCGPORTINFO ioctl command and MUX_L2_PORT_PARAMS 
                 structure definition (SPR #112068).
26aug05,kch  Added EGRESS_FRAME_TYPE enum. Renamed MUX_L2_VLAN structure 
                 to MUX_L2_PORT_VLAN. Replaced isEgressUntagged boolean with
                 etype EGRESS_FRAME_TYPE enumeration to handle the default
                 egress tagging state for pvid and other vids correctly. 
25aug05,kch  Added prototypes muxL2PortAltAttach() and 
                 muxL2PortTos2UpriorityRegister() for backward compatibility.
24aug05,kch  Added muxL2StatShow() and muxL2VlanStatShow() prototypes.
23aug05,kch  Added vlan tag related macros.
18aug05,kch  Added MUXL2IOCSGLOBALVIDJOIN and MUXL2IOCSGLOBALVIDLEAVE
                 commands.
17aug05,kch  Added muxL2VlanShow() prototype. Removed argument
                 'verbose' from muxL2Show() prototype.
17aug05,kch  Added argument 'verbose' to muxL2Show() prototype.
28jul05,kch  written.
*/

/*
DESCRIPTION
This file includes function prototypes for the Layer 2 MUX.

INCLUDE FILES:
*/

#ifndef __INCmuxL2Libh
#define __INCmuxL2Libh

#include <cfgDefs.h>
#include <muxLib.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct mux_l2_config_params {
    CFG_DATA_HDR cfgh;

    /* the number of ports that the device has */
    int cfg_priv_muxL2NumPorts;

    /* maximum number of 802.1Q VLANs that the device supports */
    int cfg_priv_muxL2MaxVlanSupport;

} MUX_L2_CONFIG_PARAMS;

/*
 * The length of 802.1Q VAN encapsulation
 */
#define	ETHER_VLAN_ENCAP_LEN	4

#define VLAN_ID_MASK             0x0fff  /* 12 bits vlan id */
#define PRIORITY_BITS            0xe000  /* bits 15..13 in the tag */     
#define PRIORITY_MASK            0x0007  /* 3 bit priority field */

#define GET_VLAN_ID(qTag)      ((qTag) & VLAN_ID_MASK)
#define GET_VLAN_USER_PRIORITY(qTag)   (((qTag) >> 13) & PRIORITY_MASK)

/*
 * 802.1Q VLAN definitions
 */
#define NULL_VID             0        /* for priority-tagged frame */
#define MIN_VID              1        
#define MAX_VID              4094

/*
 * The following defines defines the acceptable priority-level for 802.1Q
 * priority-tagged frame
 */
#define MIN_USER_PRIORITY    0
#define MAX_USER_PRIORITY    7

/*
 * Macros for 802.1Q vlan-tag boundary checking 
 */
#define IS_VALID_VID(pvid)      ((pvid) <= MAX_VID)
#define IS_VALID_PRORITY(up)    ((up) <= MAX_USER_PRIORITY)

/*
 * Ingress Acceptable Frame Type 
 */
typedef enum {
    ADMIT_ALL_FRAMES = 1,     /* default */
    ADMIT_TAGGED_ONLY_FRAMES
} ACCEPT_FRAME_TYPE;

/*
 * Per 802.1Q 8.11.9 (note 2), the default tagging state for the pvid
 * is untagged, and for all other vids are tagged, unless otherwise
 * configured.
 */
typedef enum {
    EGRESS_NOT_SPECIFIED = 0, /* not specified */
    EGRESS_TAGGED_FRAMES,     /* send vlan-tagged frame for the given vlan */
    EGRESS_UNTAGGED_FRAMES    /* send untagged frame for the given vlan */
} EGRESS_FRAME_TYPE;

/* 
 * <l2Attached> sets to true if a port is attached to the layer 2, false
 * if the port is detached from layer 2. If <l2Attached> is true for END
 * device, the interface's if_output routine is expected to use the  
 * pEnd->pFuncTable->formAddress to construct its ethernet header. For
 * NPT-style device, the <l2Attached> should be ignore for now (actual
 * bahavior is currently not defined).
 *
 * <newMtu> indicates the mtu size upper layer protocols (e.g. IP) should 
 * apply to the interface. The value of the <newMtu>will be set to the 
 * existing hardware mtu size if one of the following applies:
 * 1) hardware indicates it supports hardware VLAN tagging (e.g. the 
 *    IFCAP_VLAN_HWTAGGING in if_capabilities is set), or
 * 2) hardware doesn't support hardware VLAN tagging but capable of handling 
 *    larger mtu that may include a software-appended VLAN header (e.g. the
 *    IFCAP_VLAN_MTU flag is set in if_capabilities)
 * If none of the above is true, the existing hardware mtu size will be
 * reduced by 4 bytes and reflects in <newMtu>.
 */
typedef struct mux_l2_port_params {
    BOOL l2Attached;  /* true if port is attached to layer 2, false if detach */
    unsigned long newMtu; 
} MUX_L2_PORT_PARAMS;

typedef struct mux_l2_port_vlan {
    unsigned short   vid;        /* Valid Vid: 1..4094 */
    unsigned short   upriority;  /* User Priority, Valid Priority: 0..7 */
    unsigned short   cfi;        /* canonical format indicator, 0 or 1 */
    EGRESS_FRAME_TYPE etype;     /* default to untagged if not specified */
} MUX_L2_PORT_VLAN;

typedef struct mux_l2_port_vlan_membership {
    unsigned short  vid; /* VLAN to join/leave/modify */
    EGRESS_FRAME_TYPE etype;   /* default to vlan-tagged if not specified */
} MUX_L2_PORT_VLAN_MEMBERSHIP;
    
typedef struct mux_l2_port_vlan_member_info {
    unsigned short      vid;
    BOOL isMember;       /* TRUE if port is a member of the vlan */
    EGRESS_FRAME_TYPE etype;   /* egress frame type, tagged or untagged */
} MUX_L2_PORT_VLAN_MEMBER_INFO;

/*
 * structure passed for SIOCMUXL2PASSTRHU ioctl.
 * 
 * Required data field for MUX L2 SET ioctl commands:
 * 
 * MUXL2IOCSPORTATTACH - none
 * MUXL2IOCSPORTDETACH - none
 * MUXL2IOCSPORTVLAN - portDefaultVlan.vid, portDefaultVlan.upriority, 
 *                     portDefaultVlan.etype (optional)
 * MUXL2IOCSINGRESSFRAMETYPE - portIngressAcceptFrameType
 * MUXL2IOCSINGRESSFILTER - portIngressFilter
 * MUXL2IOCSEGRESSFRAMETYPE - portVlanMember.vid, portVlanMember.etype
 * MUXL2IOCSVLANJOIN - portVlanMember.vid, portVlanMember.etype
 * MUXL2IOCSVLANLEAVE - portVlanMember.vid, portVlanMember.etype not used
 *
 * The following data field(s) are required and will be filled in by the 
 * MUX L2 GET ioctl commands:
 * 
 * MUXL2IOCGPORTINFO - portInfo.l2Attached portInfo.newMtu
 * MUXL2IOCGPORTVLAN - portDefaultVlan.vid, portDefaultVlan.upriority,
 *                     portDefaultVlan.etype
 * MUXL2IOCGINGRESSFRAMETYPE - portIngressAcceptFrameType
 * MUXL2IOCGINGRESSFILTER - portIngressFilter
 * MUXL2IOCGVLANINFO - portVlanInfo.isMember, portVlanInfo.etype if port is 
 *                     a member of the specified vid (portVlanInfo.vid 
 *                     must be provided)
 */
typedef struct mux_l2_ioctl_req {
    union {
        /* layer 2 port parameters */
        MUX_L2_PORT_PARAMS  portInfo;

        /* port-based vlan configuration */
        MUX_L2_PORT_VLAN portDefaultVlan;       

        /*  per-port Ingress Acceptable Frame Type */
        ACCEPT_FRAME_TYPE portIngressAcceptFrameType;

        /* per-port Ingress Rules */ 
        BOOL portIngressFilter;

        /* per-port per-VLAN membership configuration */
        MUX_L2_PORT_VLAN_MEMBERSHIP   portVlanMember;

         /* per-port per-VLAN membership information */
        MUX_L2_PORT_VLAN_MEMBER_INFO portVlanInfo;
    } data; 
} MUX_L2_IOCTL_REQ;

/*
 * Supported MUX ioctl command for L2 on a per-port basis
 *
 * MUXL2IOCSPORTATTACH - create a binding between an END device and L2 MUX
 * MUXL2IOCSPORTDETACH - detach the specified END device from L2 MUX
 * MUXL2IOCGPORTINFO - get the device layer 2 port information
 * MUXL2IOCSPORTVLAN - set the per-port default vid and user priority
 * MUXL2IOCGPORTVID - get the per-port default vid and user priority
 * MUXL2IOCSINGRESSFRAMETYPE - set the port Ingress Acceptable Frame Type
 * MUXL2IOCGINGRESSFRAMETYPE - get the port Ingress Acceptable Frame Type
 * MUXL2IOCSINGRESSFILTER - set the port Ingress Frame Filtering state
 * MUXL2IOCGINGRESSFILTER - get the port Ingress Frame Filtering state
 * MUXL2IOCSEGRESSFRAMETYPE - set Egress Acceptable Frame Type
 * MUXL2IOCSVLANJOIN - join VLAN membership on a port 
 * MUXL2IOCSVLANLEAVE - leave VLAN membership on a port
 * MUXL2IOCGVLANINFO - get VLAN membership for a port
 */

#define MUXL2IOCSPORTATTACH     _IOW('m', 1, MUX_L2_IOCTL_REQ)
#define MUXL2IOCSPORTDETACH     _IOW('m', 2, MUX_L2_IOCTL_REQ)
#define MUXL2IOCGPORTINFO       _IOR('m', 3, MUX_L2_IOCTL_REQ)

/* port-based vlan get and set commands */
#define MUXL2IOCSPORTVLAN       _IOW('m', 4, MUX_L2_IOCTL_REQ)
#define MUXL2IOCGPORTVLAN       _IOR('m', 5, MUX_L2_IOCTL_REQ)

/* per-port ingress acceptable frame type get and set commands */
#define MUXL2IOCSINGRESSFRAMETYPE  _IOW('m', 6, MUX_L2_IOCTL_REQ)
#define MUXL2IOCGINGRESSFRAMETYPE  _IOR('m', 7, MUX_L2_IOCTL_REQ)

/* per-port ingress filter get and set commands */
#define MUXL2IOCSINGRESSFILTER     _IOW('m', 8, MUX_L2_IOCTL_REQ)
#define MUXL2IOCGINGRESSFILTER     _IOR('m', 9, MUX_L2_IOCTL_REQ)

#define MUXL2IOCSEGRESSFRAMETYPE   _IOW('m', 10, MUX_L2_IOCTL_REQ)

/* per-port vlan membership join/leave get and set commands */
#define MUXL2IOCSVLANJOIN          _IOW('m', 11, MUX_L2_IOCTL_REQ)
#define MUXL2IOCSVLANLEAVE         _IOW('m', 12, MUX_L2_IOCTL_REQ)
#define MUXL2IOCGVLANINFO          _IOR('m', 13, MUX_L2_IOCTL_REQ)

#ifdef _WRS_KERNEL

/* globals */
IMPORT MUX_FUNCS _func_mux_l2;
IMPORT MUX_L2_CONFIG_PARAMS  muxL2DefaultConfigParams;


/* prototypes */

IMPORT STATUS muxL2LibInit (void *muxL2InitValues);
IMPORT STATUS muxL2Ioctl (void* pCookie, int cmd, caddr_t data);
IMPORT void * muxL2EndTake (const char * pDevName, int unit);
IMPORT void muxL2EndGive (void * pCookie);
IMPORT STATUS muxL2PortAttach (char * pDevName, int unit);
IMPORT STATUS muxL2PortDetach (char * pDevName, int unit);
IMPORT void muxL2Show (char *pDevName, int unit);
IMPORT void muxL2VlanShow (unsigned short vid);
IMPORT void muxL2StatShow (char *pDevName, int unit);
IMPORT void muxL2VlanStatShow (unsigned short vid);

/* the following prototypes are provided for backward compatibility */
IMPORT STATUS muxL2PortAltAttach (char * pDevName, int unit, 
                                  BOOL updateNetFuncs, 
                                  M_BLK_ID (*formAddress)(),
                                  STATUS (*packetDataGet)(), 
                                  STATUS (*ingressVlanTagCheck)());
#ifdef VLAN_TAG
IMPORT STATUS muxL2PortTos2UpriorityRegister (char * pDevName, int unit, 
                     unsigned char (*tos2UpriorityConvRtn) (unsigned char));
#endif /* VLAN_TAG */

#endif /* _WRS_KERNEL */

#ifdef __cplusplus
}
#endif

#endif /* __INCmuxL2Libh */
