/* endCommon.h - MUX/END API shared between kernel and user space */

/* Copyright 2005-2007, 2008-2011, 2014-2017 Wind River Systems, Inc. */

/*
modification history
--------------------
25jan17,xxy  Add support for TSN Clocks and Timers (F6548)
08sep16,xxy  Add network QAV/QBV and sycn time stamp support. (F6820)
04apr16,dlk  Make EIOCGFLAGS type be INT32 rather than int (V7PRO-2981)
             (For explicitness only.)
17nov15,h_l  Add network time stamp support
03sep14,wap  Add EIOCSRCVJOBQ ioctl
08jul14,d_l added EIOCGPOLLSTATE. (VXW6-80632)
05may14,rjq  Decouple COREIP with END. (V7NET-105)
06jul11,jjk  Support for Wake-On-Lan capabilities.
07apr11,tlu  Added EIOCGTPID and EIOCSTPID
13dec10,rme  Added EIOCSFWPORT
28jun10,tlu  Added EIOCSVLANFILTER, EIOCSVIDFILTER, and EIOCCVIDFILTER
28apr10,pad  Moved extern C statement after include statements.
09sep09,dlk  Added EIOCGFWPORT.
22mar08,dlk  MUX2 redesign. 1st checkin.
07dec06,wap  Add jumbo frame support
28apr06,dtr  SPR#120464 increase max end name size.
07feb06,rb   Added IOCTLs for VLAN management
29aug05,dlk  Move END_RCVJOBQ_INFO definition into end.h, as it is
		 not usable from user space.
12aug05,dlk  Removed IPv6 checksumming capabilities bits. Use the
		 (previously) IPv4-only capabilities for both IPv4 and IPv6.
26jul05,dlk  Added EIOCGRCVJOBQ. Recoded IFMEDIA ioctls to use structure
		 rather than pointer to structure as type.
		 Decreased cap_available and cap_enabled to 32 bits in
		 END_CAPABILITIES; it doesn't make sense for these to be
		 larger than the csum_flags members.
24jun05,wap  Add ifmedia support
21feb05,dlk  Extracted from end.h. Corrected ioctl codes.
*/

/*
DESCRIPTION

This file defines the parts of the MUX/END API visible to RTP
space, primarily via the SIOCMUXPASSTHRU ioctl. It also defines
all END ioctl codes, even those not presently usable from an RTP.

SEE ALSO: end.h
*/

#ifndef __INCendCommonh
#define __INCendCommonh

#include "vxWorks.h"
#include "m2Lib_type.h"	/* For MIBII counters. */
#include "lstLib.h"	/* List library for linked structures. */
#include "sys/ioctl.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * END driver/interface variants.  Note that these END styles are
 * correlated in number and order with the 'bind styles' in
 * muxLibP.h.
 */

#define END_STYLE_END2  0
#define END_STYLE_END   1
#define END_STYLE_NPT   2

#define NUM_END_STYLES	3

/*
 *
 * Flags defined for the END.
 *
 */

#define END_DEBUG 0x1000

/* Flag denoting the support for RFC 2233 MIB variables */

#define END_MIB_2233   0x10000  /* RFC2233 supported - value chosen to
				 * prevent conflict with IFF_* flags in if.h
				 */

#define END_INIT_STR_MAX 255
#define END_PROTO_NAME_MAX 32
/* The maximum length of a device name can't be increased any further
 * unless other changes in stack are made
 */
#define END_NAME_MAX 16
#define END_DESC_MAX 80         /* The maximum length of device desription. */

/*
 * This structure is used by the EIOCGIFCAP and EIOCSIFCAP ioctls.
 *
 * For EIOCGIFCAP, the driver returns all fields according to its
 * current settings. The stack need not initialize any of the fields.
 *
 * For EIOCSIFCAP, the stack sets cap_enabled, and the driver then
 * sets all fields accordingly. The bits on in cap_enabled on exit
 * should be a subset of the bits set by the stack (and of course a
 * subset of cap_available). It is not an error if the stack
 * requests in cap_enabled capabilities which the interface doesn't
 * have; it just won't get them. csum_flags_tx and csum_flags_rx
 * contain the translation of cap_enabled into CSUM flags for tx
 * and rx, and provide more detailed information about the particular
 * operations supported. For example, if IFCAP_TXCSUM and IFCAP_TCPSEG
 * are on in cap_enabled, the driver might set csum_flags_tx to a
 * subset of (CSUM_IP|CSUM_TCP|CSUM_UDP|CSUM_FRAGMENT|CSUM_TCP_SEG).
 *
 * See mbuf.h for CSUM flags. XXX - mbuf.h is a BSD-specific file,
 * whereas these flags should be defined for all protocols, even
 * though they are protocol specific. Consider moving them here.
 */

typedef struct _END_CAPABILITIES
    {
    uint32_t cap_available; /* supported capabilities (RO) */
    uint32_t cap_enabled;   /* subset of above which are enabled (RW) */
    uint32_t csum_flags_tx; /* cap_enabled mapped to CSUM flags for TX (RO) */
    uint32_t csum_flags_rx; /* cap_enabled mapped to CSUM flags for RX (RO) */
    } END_CAPABILITIES;

/* Interface capabilities flags for cap_available, cap_enabled fields: */

#define IFCAP_RXCSUM            0x0001  /* can offload cksum on RX (IPv4) */
#define IFCAP_TXCSUM            0x0002  /* can offload cksum on TX (IPv4) */
#define IFCAP_NETCONS           0x0004  /* can be a network console */
#define IFCAP_VLAN_MTU          0x0008  /* VLAN-compatible MTU */
#define IFCAP_VLAN_HWTAGGING    0x0010  /* hardware VLAN tag support */
#define IFCAP_JUMBO_MTU         0x0020  /* 9000 byte MTU supported */
#define IFCAP_TCPSEG            0x0040  /* can do IPv4/TCP segmentation */
#define IFCAP_IPSEC             0x0080  /* can do IPsec */
#define IFCAP_WOL_UCAST         0x0100  /* wake on any unicast frame */
#define IFCAP_WOL_MCAST         0x0200  /* wake on any multicast frame */   
#define IFCAP_WOL_MAGIC         0x0400  /* wake on any Magic packet */
#define IFCAP_WOL_ARP4          0x0800  /* wake on any IPV4 ARP request */
#define IFCAP_WOL_IPV4          0x1000  /* wake on directed IPV4 packet */
#define IFCAP_WOL_IPV6          0x2000  /* wake on directed IPV6 packet */
#define IFCAP_WOL   (IFCAP_WOL_UCAST | IFCAP_WOL_MCAST | IFCAP_WOL_MAGIC \
                     | IFCAP_WOL_ARP4 | IFCAP_WOL_IPV4 | IFCAP_WOL_IPV6)

/*
 * Removed IPv6 checksumming capabilities bits. Administratively, we
 * use IFCAP_RXCSUM, IFCAP_TXCSUM, and IFCAP_TCPSEG to control the
 * capabilities for both IPv4 and IPv6.
 */

#define IFCAP_IPCOMP            0x0800  /* can do IPcomp */

#define IFCAP_CAP0              0x1000 /* Vendor specific capability #0 */
#define IFCAP_CAP1              0x2000 /* Vendor specific capability #1 */
#define IFCAP_CAP2              0x4000 /* Vendor specific capability #2 */
#define IFCAP_CAP3              0x8000 /* Vendor specific capability #3 */

#define IFCAP_IEEE1588          0x00010000 /* Support IEEE1588 */
#define IFCAP_IEEE1588_ONE_STEP 0x00020000 /* Support IEEE1588 one step mode*/
#define IFCAP_RX_HW_TIMESTAMP   0x00040000 /* Support RX hw timestamp */
#define IFCAP_TX_HW_TIMESTAMP   0x00080000 /* Support TX hw timestamp*/
#define IFCAP_TSIP_MODE         0x00100000 /* Support timestamp in packet*/
#define IFCAP_TIMER_INTERRUPT   0x00200000 /* Support timer-interrupt*/
#define IFCAP_LAUNCH_TIME       0x00400000 /* Support launch time*/

/*
 * This structure is used by the EIOCGIFMEDIA and EIOCSIFMEDIA ioctls.
 */

typedef struct _END_MEDIA
    {
    UINT32                      endMediaActive;
    UINT32                      endMediaStatus;
    } END_MEDIA;

/*
 * This structure is used by the EIOCGMEDIALIST ioctl. It returns
 * the default media setting and a variable length list of media
 * types that the driver supports.
 */

typedef struct _END_MEDIALIST
    {
    UINT32                      endMediaListDefault;
    UINT32                      endMediaListLen;
    UINT32                      endMediaList[1];
    } END_MEDIALIST;

/*
 * This structure is used by EIOCVLANGET to return a list of VLANs configured
 * for the interface
 */

typedef struct _END_VLAN_REQ
    {
	int vlanCount;    		    /* # of configured VLAN tags */
	int vlanTagCount;			/* # of VLAN tags in pVlanTagData */
	UINT16 * pVlanTagData; 		/* Array of VLAN tags */
    } END_VLAN_REQ;

/*
 *
 * End Specific IOCTL commands.
 *
 * The following are the end specific IOCTL commands.  This is a place
 * holder for them until we places them into the system ioctl.h file.
 *
 * EIOC stands for END ioctl, just as SIOC stands for socket ioctl.
 *
 * User defined IOCTLS should use the command byte 'e' (for END) and should
 * start at 128. Numbers 0 through 127 are reserved by Wind River Systems.
 */

#undef END_IOCTL_BIN_COMPAT

#ifdef END_IOCTL_BIN_COMPAT

/*
 * Obsoleted END IOCTL codes.  These codes are incorrect for one
 * or more reasons:
 * - Some are group 'i' when they should be 'e'.
 * - Many specify the type of the pointer rather than the thing pointed to.
 * - Some use _IOW(..,..,NULL) rather than _IO(..,..).
 * - Some we wish to make usable from RTP space, so they need IOC_USER.
 *
 * The original set of END IOCTL commands started with number 260 and continued
 * upwards. The value 260 or higher cannot be accomodated within the LSByte
 * reserved for it by the _IO[RW] macros(sys/ioctl.h).
 *
 * However the numbers, 260 through 274, that were used did not
 * alter the value of the command byte('i') in the IOCTL command and
 * are equivalent to the numbers 4 through 18 used below. This preserves
 * binary compatibility with END drivers that were built using the old defines.
 *
 * This list of IOCTLS with command byte 'i' SHOULD NOT BE EXTENDED BEYOND 18
 *
 */

/* Device commands */
#define OEIOCSFLAGS _IOW('i', 4, int) /* Set device flag */
#define OEIOCGFLAGS _IOR('i', 5, int)	/* Get device flag */
#define OEIOCSADDR _IOW('i', 6, char *)	/* Set device address */
#define OEIOCGADDR _IOR('i', 7, char *)	/* Get device address */
#define OEIOCGFBUF _IOR('i', 8, int)   /* Get min 1st buf for chaining. */
#define OEIOCGMWIDTH _IOR('i', 9, int)   /* Get device memory width. */

/* Multicast commands */
#define OEIOCMULTIADD _IOW('i', 10, char *)	/* add m'cast addr */
#define OEIOCMULTIDEL _IOW('i', 11, char *)	/* del m'cast addr */
#define OEIOCMULTIGET _IOWR('i', 12, MULTI_TABLE)/* get m'cast addr */

/* Miscellaneous functions */
#define OEIOCSRCVCB _IOW('i', 13, FUNCPTR)	/* Set receive callback */
#define OEIOCPOLLSTART _IOW('i', 14, NULL)	/* Start polling. */
#define OEIOCPOLLSTOP _IOW('i', 15, NULL)	/* Stop polling. */

/* MibII functions */
#define OEIOCGMIB2 _IOR('i', 16, M2_INTERFACETBL *)

/* Name function. */
#define OEIOCGNAME _IOR('i', 17, char *)     /* get the device name */

/* Header length fucntion. */
#define OEIOCGHDRLEN _IOR('i', 18, int)     /* get the header length */

/*
 * The IOCTL commands below were introduced by the Network Protocol Toolkit
 * The command byte is set to 'e' for END and numbers 1 thro' 127 are reserved
 * for WRS.
 * Below we start at 20 to allow room for the above 'i' based IOCTLS to be
 * converted to 'e' based IOCTLS sometime in the future.
 */

/* Toolkit device or not */
#define OEIOCGNPT _IOR('e', 20, NULL) /* return true for toolkit device*/

/* Broadcast address */
#define OEIOCGBCASTADDR _IOR('e', 21, char *) /* return Broadcast addr */

/* More MibII functions */
#define OEIOCSMIB2233 _IOW('e', 24, IF_SETENTRY *)

/* MTU for Point to Multipoint */
#define OEIOCGMTU _IOR('e', 26, MTU_QUERY *)

/* MIB allocation for RFC2233 */
#define OEIOCSMIBINIT _IOW('e', 29, NULL)

/* Obtain END Style of driver */
#define OEIOCGSTYLE _IOR('e', 30, int)

/* Obtain or set interface capabilities (e.g. hardware offload) */
#define OEIOCGIFCAP _IOR('e', 31, END_CAPABILITIES *)
#define OEIOCSIFCAP _IOWR('e', 32, END_CAPABILITIES *)

#endif /* END_IOCTL_BIN_COMPAT */

typedef unsigned char END_PHYADDR [MAXIFPHYADDR];
typedef char END_NAME [END_NAME_MAX];

/*
 * Ioctls EIOCSFLAGS through EIOCGHDRLEN were initially misdefined
 * as 'i' group ioctls.  Also several END ioctls specified an incorrect
 * type for the argument, frequently the type of the pointer rather than
 * the thing pointed to. We correct them here. The old values are
 * above.
 *
 * Certain of these ioctls have been marked with IOC_USER to enable
 * use from an RTP via SIOCMUXPASSTHRU. We do this only for ioctls
 * not requiring access to kernel structurs, and only for 'read only'
 * ioctls (for now). It may be desirable in the future to allow
 * some sorts of 'write' access from RTP space.
 */

/* Device commands */
#define EIOCSFLAGS _IOW('e', 4, int) /* Set device flag */
#define EIOCGFLAGS _IORU('e', 5, INT32)	/* Get device flag */
#define EIOCSADDR _IOW('e', 6, END_PHYADDR) /* Set device address */
#define EIOCGADDR _IORU('e', 7, END_PHYADDR) /* Get device address */
#define EIOCGFBUF _IORU('e', 8, int)   /* Get min 1st buf for chaining. */
#define EIOCGMWIDTH _IORU('e', 9, int)   /* Get device memory width. */

/* Multicast commands */
#define EIOCMULTIADD _IOW('e', 10, END_PHYADDR)	/* add m'cast addr */
#define EIOCMULTIDEL _IOW('e', 11, END_PHYADDR)	/* del m'cast addr */
#define EIOCMULTIGET _IOWR('e', 12, MULTI_TABLE)/* get m'cast addr */

/* Miscellaneous functions */
#define EIOCSRCVCB	_IOW('e', 13, FUNCPTR)	/* Set receive callback */
#define EIOCPOLLSTART	_IO('e', 14)		/* Start polling. */
#define EIOCPOLLSTOP	_IO('e', 15)		/* Stop polling. */

/* MibII functions */
#define EIOCGMIB2 _IORU('e', 16, M2_INTERFACETBL)

/* Name function. */
#define EIOCGNAME _IORU('e', 17, END_NAME)     /* get the device name */

/* Header length fucntion. */
#define EIOCGHDRLEN _IORU('e', 18, int)     /* get the header length */

/* Toolkit device or not */
#define EIOCGNPT _IOU('e', 20) /* return true in case of toolkit device*/

/* Broadcast address */
#define EIOCGBCASTADDR _IORU('e', 21, END_PHYADDR) /* return Broadcast addr */

/* Query IOCTL command */
#define EIOCQUERY _IOWR('e', 22, END_QUERY)

/* More MibII functions */

#define EIOCGMIB2233 _IOR('e', 23, M2_ID *)		/* pointer */
#define EIOCSMIB2233 _IOW('e', 24, IF_SETENTRY)
#define EIOCGMCASTLIST _IOR('e', 25, LIST *)		/* pointer */

/* MTU for Point to Multipoint */
#define EIOCGMTU _IOWR('e', 26, MTU_QUERY)

/* Access driver's internal 2233 stats counters */
#define EIOCGPOLLCONF _IOR('e', 27, END_IFDRVCONF *)   /* pointer */
#define EIOCGPOLLSTATS _IOR('e', 28, END_IFCOUNTERS *) /* pointer */

/* MIB allocation for RFC2233 */
#define EIOCSMIBINIT _IO('e', 29)

/* Obtain END Style of driver */
#define EIOCGSTYLE _IORU('e', 30, int)

/* Obtain or set interface capabilities (e.g. hardware offload) */
#define EIOCGIFCAP _IORU('e', 31, END_CAPABILITIES)
#define EIOCSIFCAP _IOWR('e', 32, END_CAPABILITIES)

/* Obtain or set media status */
#define EIOCGMEDIALIST _IOR('e', 33, END_MEDIALIST)
#define EIOCGIFMEDIA _IOR('e', 34, END_MEDIA)
#define EIOCSIFMEDIA _IOWR('e', 35, END_MEDIA)

/* Obtain list of receive job queues for interface */
#define EIOCGRCVJOBQ _IOWR('e', 36, END_RCVJOBQ_INFO)

/* Make the interface a member of the specified VLAN */
#define EIOCVLANJOIN _IOU('e', 37)

/* Remove the specified VLAN from this interface */
#define EIOCVLANLEAVE _IOU('e', 38)

/* Remove all VLANs from the specified interface */
#define EIOCVLANFLUSH _IOU('e', 39)

/* Get a list of all VLANs the interface belongs to */
#define EIOCVLANGET _IOWRU('e', 40, END_VLAN_REQ)

/* Jumbo frame support -- get/set interface MTU */
#define EIOCGIFMTU _IOR('e', 42, int)
#define EIOCSIFMTU _IOW('e', 43, int)

/* Get pointer to forwarder offload port, if supported */
#define EIOCGFWPORT _IOR('e', 44, void *)

/* Enable/disable VLAN filtering (Intel NIC 82576, 82599, hardware offload) */
#define EIOCSVLANFILTER _IOW('e', 45, int)
#define EIOCSVIDFILTER _IOW('e', 46, int)   	/* Set VID filtering */
#define EIOCCVIDFILTER _IOW('e', 47, int)   	/* Clr VID filtering */
#define EIOCSFWPORT _IOW('e', 48, int)

/* Read/write S-TPID (P4080, hardware offload) */
#define EIOCGTPID _IOW('e', 49, int)
#define EIOCSTPID _IOW('e', 50, int)


/* Get polled or interrupt mode */
#define EIOCGPOLLSTATE _IOR('e', 51, int)

/* Set list of receive job queues for interface */
#define EIOCSRCVJOBQ _IOWR('e', 52, END_RCVJOBQ_INFO)


/* Set the IEEE1588 system time interval */
typedef struct ieee1588_timer_sync
    {
    void * ethCookie;
    long * interval;
    } IEEE1588_TIMER_SYNC;

/* Set the QBV time slot */
typedef struct qbvTimeSlot
    {
    int    slotId;
    int    slotStart;
    size_t slotLen;
    struct qbvTimeSlot * next;
    } QBV_TIME_SLOT;


#define HW1588TS_TX_OFF     0
#define HW1588TS_TX_EN      1

#define HW1588TS_RX_FILTER_OFF    0
#define HW1588TS_RX_FILTER_ALL    1

/* IEEE1588 timer support */

/* Set the system time */
#define EIOCS1588SYSTIM   _IOW('e', 61, struct timespec *)

/* Get the system time */
#define EIOCG1588SYSTIM   _IOR('e', 62, struct timespec *)

/* Adjust the system time */
#define EIOCS1588TIMADJ   _IOW('e', 63, INT64)

/* Adjust the frequency */
#define EIOCS1588FREQADJ  _IOW('e', 64, INT32)

/* Get the time cost of reading the system time */
#define EIOCG1588SYSTIMEDELAY _IOW('e', 65, long *)

/* Set the time offset of master to slave in boundary clocks  */
#define EIOCS1588SYSTIMEINTERVAL _IOW('e', 66, struct IEEE1588_TIMER_SYNC *)

/* Get 1588 timer func */
#define EIOCG1588TIMFUNC    _IOR('e', 67, struct vxbTimerFunctionality **)

/* Set 1588 timer use the Software-Defined Pin to emit pulse */
#define EIOCS1588SDPCONFIG _IOW('e', 68, UINT32)

/* Get the max 1588 timers of END device */
#define EIOCG1588TIMERSMAX   _IOR('e', 69, UINT32 *)

/* Set 1588 time stamp Tx configuration */
#define EIOCS1588TSTXCONFIG _IOW('e', 70, UINT32)

/* Set 1588 time stamp Rx configuration */
#define EIOCS1588TSRXFILTER _IOW('e', 71, UINT32)

/* Get the tx time stamp */
#define EIOCG1588TXTIMSTAMP   _IOR('e', 72, struct timespec *)

/* Set 1588 time stamp Tx 1588 OFFSET configuration */
#define EIOCS1588TSTXOFFSETCONFIG _IOW('e', 73, UINT32)

/* Get the time offset of master to slave in boundary clocks  */
#define EIOCG1588SYSTIMEINTERVAL _IOW('e', 74, struct IEEE1588_TIMER_SYNC *)

/* Add the system time with offset */
#define EIOCS1588TIMEADD   _IOW('e', 75, INT64 *)




#ifdef __cplusplus
}
#endif

#endif /* __INCendCommonh */
