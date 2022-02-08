/* ioctl.h - ioctl header file */

/*
 * Copyright (c) 1984-2007, 2010, 2014 Wind River Systems, Inc. 
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement. 
 */

/*
modification history
--------------------
29jan15,wap  minor cleanups from review (V7COR-996)
26jan15,wap  added documentation about ioctl groups (V7COR-996)
12mar14,pad  added #include to get net/ioctl.h (issue VXW7-2554).
19feb14,cww  moved socket content to net/ioctl.h
28apr10,pad  Moved extern C statement after include statements.
04sep07,h_k  fixed an apigen error.
15jan07,jlk  Defect WIND00064397 - macro _IOC now has type int
12dec06,kch  Added <ipnet/ioctl.h> include.
30nov06,kch  Removed all network stack ioctl commands.
26sep06,kch  Added SIOCGIFLLADDR to retrieve interface MAC Address.
22jul05,kch  Added SIOCMUXL2PASSTHRU for Layer 2 support.
24feb05,dlk  Added SIOCMUXPASSTHRU support. Increase maximum
                 ioctl argument size to 4095 bytes. Added IOCPARM_MAX
		 and IOCPARM_LEN macros, and other items from ioccom.h.
12oct01,rae  merge from truestack (SIOCGMTU)
29apr99,pul  Upgraded NPT phase3 code to tor2.0.0
18mar99,sj   added SIOCSIFASYNCFLAGS
11aug93,jmm  Changed ioctl.h and socket.h to sys/ioctl.h and sys/socket.h
22sep92,rrr  added support for c++
04jul92,jcf  cleaned up.
26may92,rrr  the tree shuffle
04oct91,rrr  passed through the ansification filter
		  -changed copyright notice
19aug91,rrr  changed to work with ansi compiler
24mar91,del  changes to work with gnu960 compiler for i960 port.
05oct90,shl  fixed copyright notice.
29apr87,dnw  removed unnecessary junk.
		 added header and copyright.
*/

#ifndef __INCioctlh
#define __INCioctlh

/*
 * Ioctl's have the command encoded in the lower word,
 * and the size of any in or out parameters in the upper
 * word.  The high 2 bits of the upper word are used
 * to encode the in/out status of the parameter; for now
 * we restrict parameters to at most 4095 bytes, reserving
 * the 0x10000000 bit for other use.
 */

#define	IOCPARM_MASK	0xfff		/* parameters must be < 4096 bytes */
#define IOCPARM_MAX	0xfff		/* absolute maximum param size */
#define	IOC_VOID	0x20000000	/* no parameters */
#define	IOC_OUT		0x40000000	/* copy out parameters */
#define	IOC_IN		0x80000000	/* copy in parameters */
#define	IOC_INOUT	(IOC_IN|IOC_OUT)
/* the 0x20000000 is so we can distinguish new ioctl's from old */

#define IOCPARM_LEN(x)  ((((u_long)(x)) >> 16) & IOCPARM_MAX)
#define	IOCBASECMD(x)	((x) & ~(IOCPARM_MASK << 16))
#define	IOCGROUP(x)	(((x) >> 8) & 0xff)

#define	_IOC(inout,group,num,len) \
	((int)(inout | ((len & IOCPARM_MASK) << 16) | \
			 ((group) << 8) | (num)))
#define	_IO(g,n)	_IOC(IOC_VOID,	(g), (n), 0)
#define	_IOR(g,n,t)	_IOC(IOC_OUT,	(g), (n), sizeof(t))
#define	_IOW(g,n,t)	_IOC(IOC_IN,	(g), (n), sizeof(t))
/* this should be _IORW, but stdio got there first */
#define	_IOWR(g,n,t)	_IOC(IOC_INOUT,	(g), (n), sizeof(t))

/*
 * These definitions are primarily to support SIOCMUXPASSTHRU.
 * It's assumed that tunnellable IOCTLs will have IOC_USER set.
 * Note that IOC_USER overlaps the high bit of the type (x) byte.
 * When this byte is an ASCII character, its high bit will be 0;
 * but if the high bit of the type byte x is set, _IOR(x,y,t)
 * and _IORU(x,y,t) (for instance) will be indistinguishable.
 */

#define IOC_USER        0x8000 /* tunnellable from RTP space */
#define	_IOU(g,n)	(IOC_USER|_IO(g,n))
#define	_IORU(g,n,t)	(IOC_USER|_IOR(g,n,t))
#define	_IOWU(g,n,t)	(IOC_USER|_IOW(g,n,t))
#define	_IOWRU(g,n,t)	(IOC_USER|_IOWR(g,n,t))

/*
 * Note: there are several different ioctl APIs defined throughout the
 * OS. Typically each ioctl interfaces uses a different group code, and
 * there may be some concern about what might happen if two ioctls use
 * the same group code value.
 *
 * As it stands, there isn't much negative impact if two ioctl interfaces
 * use the same interface since the ioctls are routed to drivers based
 * on the file descriptor on which the ioctl is issued rather than the
 * group code. This means it's entirely possible to have two drivers
 * using the same group code without any issues (other than maybe some
 * confusion to the reader).
 *
 * However, for clarity, presented below are the ioctl groups which are
 * already defined in various places in VxWorks. Any new additions should
 * be documented here.
 *
 * net/ioctl.h
 * -----------
 * Defines the ioctl group 's'
 * These are legacy socket ioctls. The bulk of the networking ioctls have
 * been movied into the ipnet stack. Note that this header also defines
 * two special socket passthrough ioctls that allow an application to
 * invoke the ioctls in an END driver (see below). The END driver ioctl
 * command is specially encoded in the argument field.
 *
 * ipcom_sock.h
 * ------------
 * Defines the following group IDs:
 * IP_IOCG_BASE        1
 * IP_IOCG_SOCK        2
 * IP_IOCG_NETIF       3
 * IP_IOCG_ARP         4
 * IP_IOCG_INET        5
 * IP_IOCG_INET6       6
 * IP_IOCG_ETH         7
 * IP_IOCG_PPP         8
 * IP_IOCG_WLAN        9
 * IP_IOCG_MCAST       10
 * IP_IOCG_MCAST_IN6   11
 * IP_IOCG_RTAB        13
 * IP_IOCG_DS          14
 * IP_IOCG_POLICY_RT   15
 * These are used with the IPNET ioctls. Typically only the SOCK ones may be
 * used by application code. Note that the IPNET ioctl encoding scheme uses
 * only 4 bits for the group while VxWorks proper uses 7.
 *
 * endCommon.h
 * -----------
 * Defines the ioctl groups 'e' and 'i'
 * These are END ioctls. They're implemented in END drivers, but are only
 * called from the muxIoctl() routine. They aren't accessible via the ioctl()
 * interface in ioLib. (Usually only a networking protocol invokes these
 * using the muxIoctl() interface.)
 *
 * The 'i' ioctls are obsolete definitions preserved for compatibility.
 *
 * muxL2Lib.h
 * ----------
 * Defines the ioctl group 'm'
 * These are special MUX ioctls for L2 switch management (such as handling
 * VLANs).
 *
 * ntp_datum.h
 * -----------
 * Defines the ioctl group 'X'
 * These are two special ioctls for use with the NTP protocol server.
 *
 * timepps-SunOS.h
 * ---------------
 * Defines the ioctl group 'C'
 * This is used with the 'Pulse Per Second' API library used in conjunction
 * with NTP. It's unclear if this ioctl is used in VxWorks.
 * 
 * dot1xCommonIoctls.h
 * -------------------
 * Defines the ioctl groups 'd' 'w' and 'x'
 * These ioctls are used by the wireless network driver infrastructure.
 * They are called through the END driver interface and as such are not
 * exposed via the ioLib ioctl() API. 
 */

/*
 * This inclusion should work the other way, that file including this one at
 * the beginning.  This is here so that the transition to net/ioctl.h can be
 * gradual - it should be removed once all the include statements are fixed.
 */

#ifdef _WRS_CONFIG_SOCKET
#include <net/ioctl.h>
#endif

#endif /* __INCioctlh */

