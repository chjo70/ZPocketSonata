/* sysLib.h - system dependent routines header */

/*
 * Copyright (c) 1984-2010,2012, 2014-2016 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
05dec16,y_h  added sysPowerOff declare, support ACPI event feature (F6446)
24mar16,cma  Add definition for extern <sysStartType> (V7COR-3894). 
17apr15,rr   Removed NETIF structure (V7COR-1168). 
24mar14,pcs  added prototype for routine sysMemSizeGet.
09may12,dee  Fix typo added when WIND00212450 was fixed by WIND00327558
09jan12,pgh  Add comments to flags
03may10,h_k  changed sysInLong() return val for LP64.
29apr10,pad  Moved extern C statement after include statements.
20jan10,dbt  Added sysUserSmInfoGet() VxSim specific routine.
21sep09,cww  Added sysHwInit1
03sep09,scm  add MEM_DESC_ADDR_KERNEL_ASSIGNED...
24aug09,sru  add sysMemDesc* feature
23oct08,kab  Update sysAmpCpuPrep to new sig per design mod
15oct08,kab  Adding sysSymPhysMemBottom/Size (wrload and hv support)
06jun08,pgh  Merge DHCP fixes
13jul07,kk   remove _WRS_VX_SMP usage, added sysCpuAvailableGet()
08mar06,lei  removed __STDC__ stuff.
25may05,md   added SMP support
21may04,dtr  Fix SPR 96824.
04feb04,elp  added VxSim sysNetIfConfig().
19aug03,dbs  add ED&R system debug mode flag
07may03,pes  PAL conditional compilation cleanup. Phase 2.
24apr02,pai  Removed sysHwInit0() prototype.  A generic interface of this
             name is not yet defined.
15apr02,pai  added sysHwInit0() prototype (SPR 74951).
10oct01,dat  SPR 70855, adding sysNanoDelay as an optional BSP API
09jun98,dat  rework of optional BSP routine declarations
14nov97,db   added functions forward declarations for PPC family.
05nov96,hdn  moved NETIF structure from bootConfig.c.
18sep96,dat  added sysBspRev, sysPhysMemTop, sysScsiConfig,
             sysSerialHwInit, sysSerialHwInit2, sysSerialReset
06aug96,dat  using #include timerDev.h to declare timer functions
13jun96,hdn  added sysInLong() sysInLongString() sysOutLong()
             sysOutLongString().
15jun95,ms   updated for new serial driver
14jun95,hdn  added x86 specific prototypes.
22may95,ms   added sysSerialDevGet() prototype.
22sep92,rrr  added support for c++
15sep92,jcf  cleaned up.
31jul92,ccc  added tyCoDrv() and tyCoDevCreate() prototypes.
27jul92,ccc  added prototypes to clean up os warnings.
09rdc92,rdc  moved PHYS_MEM_DESC struct to vmLib.c.
08rdc92,rdc  added PHYS_MEM_DESC struct.
04jul92,jcf  cleaned up.
26jun92,wmd  modified prototype for sysFaultTableInit().
16jun92,ccc  removed function declarations for sysLib break-up.
26may92,rrr  the tree shuffle
23apr92,wmd  added sysFaultVecSet() prototype declaration for i960.
21apr92,ccc  added SCSI declarations.
16apr92,elh  added SYSFLG_PROXY.
04apr92,elh  added SYSFLG_TFTP.
18dec91,wmd  added mre ANSI prototypes for i960.
04oct91,rrr  passed through the ansification filter
             -fixed #else and #endif
             -changed VOID to void
             -changed ASMLANGUAGE to _ASMLANGUAGE
             -changed copyright notice
23oct90,shl  added a set of generic system dependent function prototypes.
05oct90,dnw  added some ANSI prototypes.
05oct90,shl  added copyright notice.
             made #endif ANSI style.
10aug90,dnw  added SYSFLG_BOOTP
28jul90,dnw  removed BOOT_FIELD_LEN to bootLib.h
             added declaration of sysBootParams
             added include of bootLib.h
20jun90,gae  changed start types to be bit fields and renamed types.
             added import of sysModel.
24apr90,shl  added SYSFLG_NO_SECURITY.
23may89,dnw  added SYSFLG_NO_STARTUP_SCRIPT.
02may89,dnw  added SYSFLG_VENDOR_{0,1,2,3}.
15oct88,dnw  added SYSFLG_NO_AUTOBOOT, SYSFLG_QUICK_AUTOBOOT,
             and BOOT_WARM_QUICK_AUTOBOOT.
24mar88,ecs  added declaration of sysExcMsg.
13nov87,jcf  changed names of boot types.
29oct87,dnw  added SYSFLG_DEBUG.
14oct87,dnw  added SYSFLG_NO_SYS_CONTROLLER.
14jul87,dnw  added more system global varaibles.
	     deleted sysLocalToBusAdrs().
             added system restart types.
14feb87,dnw  added sysBus, sysCpu, sysLocalToBusAdrs
18dec86,llk  added BOOT_FIELD_LEN.
04aug84,dnw  written
*/

#ifndef __INCsysLibh
#define __INCsysLibh

#ifndef	_ASMLANGUAGE
#include "bootLib.h"
#include "ttyLib.h"
#include "sioLib.h"
#include <timerDev.h>

#ifdef __cplusplus
extern "C" {
#endif

struct phys_mem_desc;

#endif	/* _ASMLANGUAGE */

/* system restart types */

#define	BOOT_NORMAL		0x00	/* normal reboot with countdown */
#define BOOT_NO_AUTOBOOT	0x01	/* no autoboot if set */
#define BOOT_CLEAR		0x02	/* clear memory if set */
#define BOOT_QUICK_AUTOBOOT	0x04	/* fast autoboot if set */

/* for backward compatibility */

#define BOOT_WARM_AUTOBOOT		BOOT_NORMAL
#define BOOT_WARM_NO_AUTOBOOT		BOOT_NO_AUTOBOOT
#define BOOT_WARM_QUICK_AUTOBOOT	BOOT_QUICK_AUTOBOOT
#define BOOT_COLD			BOOT_CLEAR

/* system configuration flags in sysFlags */

/* Some targets have system controllers that can be enabled in software.
 * By default, the system controller is enabled for processor 0.
 * When set this flag inhibits enabling the system controller even
 * for processor 0.
 */

#define SYSFLG_NO_SYS_CONTROLLER 0x01

/* System debug option:
 * load kernel symbol table with all symbols (not just globals)
 */

#define SYSFLG_DEBUG             0x02   /* Load all symbols (use with */
                                        /* downloadable symbol table only). */
#define SYSFLG_NO_AUTOBOOT	 0x04	/* Don't start autoboot sequence */
#define SYSFLG_QUICK_AUTOBOOT	 0x08	/* Fast auto-boot (short countdown). */
#define SYSFLG_UNUSED1           0x10   /* unused bit */
#define SYSFLG_NO_SECURITY	 0x20   /* Don't ask passwd on network login */
#define SYSFLG_AUTOCONFIG	 0x40   /* Use bootp or DHCP to get IP address */
#define SYSFLG_TFTP		 0x80   /* Use tftp to get boot image */
#define SYSFLG_PROXY		 0x100	/* Not supported */
#define SYSFLG_UNUSED2           0x200  /* unused bit */
#define SYSFLG_SYS_MODE_DEBUG	 0x400	/* System is in 'debug' mode */
#define SYSFLG_AUTOFILE          0x800  /* Use BOOTP or DHCP to get boot file */
    
#define SYSFLG_VENDOR_0		 0x1000	/* vendor defined flag 0 */
#define SYSFLG_VENDOR_1		 0x2000	/* vendor defined flag 1 */
#define SYSFLG_VENDOR_2		 0x4000	/* vendor defined flag 2 */
#define SYSFLG_VENDOR_3		 0x8000	/* vendor defined flag 3 */

#define _MEM_DESC_RAM		     1  /* kernel RAM */
#define _MEM_DESC_USER_RESERVED_RAM  2  /* user RAM */
#define _MEM_DESC_PM_RAM	     3  /* persistent memory RAM */
#define _MEM_DESC_DMA32_RAM	     4  /* <4G DMA buffer RAM */

#define MEM_DESC_ADDR_KERNEL_ASSIGNED (VIRT_ADDR) -1 /* kernel assigned */

/* system parameters */

#ifndef	_ASMLANGUAGE

extern int  	sysStartType;
extern int 	sysBus;		/* system bus type (VME_BUS, MULTI_BUS, etc) */
extern int 	sysCpu;		/* system cpu type (MC680x0, SPARC, etc.) */
extern int 	sysProcNum;	/* processor number of this cpu */
extern char *	sysBootLine;	/* address of boot line */
extern char *	sysExcMsg;	/* address of exception message area */
extern int	sysFlags;	/* configuration flags */
extern BOOT_PARAMS sysBootParams; /* parameters from boot line */

/*
 * sysSymPhysMemBottom/Size are defined at build time and used
 * by wrload and other multicore utilities to discover runtime footprint of the
 * image prior to download and start.
 */
extern const char * sysSymPhysMemBottom;  /* addr or lowest RAM used */
extern const long sysSymPhysMemSize;      /* total bytes of RAM used */

/* memory type descriptors for sysMemDescGet() */

typedef enum mem_desc_type
    {
      MEM_DESC_RAM		  = _MEM_DESC_RAM,
      MEM_DESC_USER_RESERVED_RAM  = _MEM_DESC_USER_RESERVED_RAM,
      MEM_DESC_PM_RAM             = _MEM_DESC_PM_RAM,
      MEM_DESC_DMA32_RAM          = _MEM_DESC_DMA32_RAM
    } MEM_DESC_TYPE;

/* obsolete - but remain for backward compatiblity */

extern char	sysBootHost[];	/* name of host from which system was booted */
extern char	sysBootFile[];	/* name of file from which system was booted */

/* function declarations */

extern char *	sysModel (void);
extern char *	sysBspRev (void);
extern void 	sysHwInit (void);
extern void 	sysHwInit2 (void);
extern void	sysMemDescInit (void);
extern STATUS	sysMemDescGet (MEM_DESC_TYPE, int, struct phys_mem_desc *);
extern char *	sysMemTop (void);
extern char *	sysPhysMemTop (void);
extern UINT64	sysMemSizeGet (void);
extern STATUS 	sysToMonitor (int startType);
#ifdef _WRS_CONFIG_SYS_PWR_OFF
extern STATUS   sysPowerOff (void);
#endif /* _WRS_CONFIG_SYS_PWR_OFF */
extern int 	sysProcNumGet (void);
extern void 	sysProcNumSet (int procNum);
extern BOOL 	sysBusTas (char *adrs);
extern STATUS 	sysNvRamGet (char *string, int strLen, int offset);
extern STATUS 	sysNvRamSet (char *string, int strLen, int offset);
extern STATUS 	sysScsiInit (void);
extern STATUS 	sysScsiConfig (void);
extern void	sysSerialHwInit (void);
extern void	sysSerialHwInit2 (void);
extern SIO_CHAN * sysSerialChanGet (int channel);
extern void	sysSerialReset (void);
extern STATUS	sysLocalToBusAdrs (int adrsSpace, char *localAdrs,
				   char **pBusAdrs);
extern STATUS	sysBusToLocalAdrs (int adrsSpace, char *busAdrs,
				   char **pLocalAdrs);
extern STATUS	sysIntDisable (int intLevel);
extern STATUS	sysIntEnable (int intLevel);
extern int	sysBusIntAck (int intLevel);
extern STATUS	sysBusIntGen (int level, int vector);
extern STATUS	sysMailboxConnect (FUNCPTR routine, int arg);
extern STATUS	sysMailboxEnable (char *mailboxAdrs);
extern int	tyCoDrv (void);
extern int	tyCoDevCreate (char *name, int channel, int rdBufSize,
			       int wrtBufSize);
extern STATUS   sysAmpCpuPrep (UINT cpuId, void * arg);

#ifdef _WRS_CONFIG_DELAYED_HW_INIT
extern void 	sysHwInit1 (void);
#endif

/* For all architectures, except X86, the arguments are unsigned.  */
#if defined (_WRS_SIGNED_IO_ARGS)
#define _WRS_IOLONG	int
#define _WRS_IOSHORT	short
#define _WRS_IOCHAR	char
#else /* _WRS_SIGNED_IOARGS */
#define _WRS_IOLONG	ULONG
#define _WRS_IOSHORT	UINT16
#define _WRS_IOCHAR	UCHAR
#endif	/* _WRS_SIGNED_IO_ARGS */

extern UCHAR	sysInByte		(_WRS_IOLONG port);
extern USHORT	sysInWord		(_WRS_IOLONG port);
#ifdef	_WRS_CONFIG_LP64
extern UINT32	sysInLong		(_WRS_IOLONG port);
#else
extern ULONG	sysInLong		(_WRS_IOLONG port);
#endif	/* _WRS_CONFIG_LP64 */
extern void	sysInWordString		(_WRS_IOLONG port, _WRS_IOSHORT *pData, int count);
extern void	sysInLongString		(_WRS_IOLONG port, _WRS_IOLONG *pData, int count);
extern void	sysOutByte		(_WRS_IOLONG port, _WRS_IOCHAR data);
extern void	sysOutWord		(_WRS_IOLONG port, _WRS_IOSHORT data);
extern void	sysOutLong		(_WRS_IOLONG port, _WRS_IOLONG data);
extern void	sysOutWordString	(_WRS_IOLONG port, _WRS_IOSHORT *pData, int count);
extern void	sysOutLongString	(_WRS_IOLONG port, _WRS_IOLONG *pData, int count);

/* optional support routines used by several architectures */

extern void	sysNanoDelay		(UINT32 nanoseconds);
extern void	sysReboot		(void);
extern void	sysDelay		(void);
extern void	sysWait			(void);
extern STATUS	sysIntDisablePIC	(int intLevel);
extern STATUS	sysIntEnablePIC		(int intLevel);

/* i960 special routines */

extern void 	sysFaultTableInit	(void (*func)(void));
extern UINT32 	sysFaultVecSet		(INSTR *vector, UINT32 faultNo, 
					 UINT32 type);
extern void 	sysExcInfoPrint		(UINT32 type);
extern UINT32   sysCpuAvailableGet	(void);

/* X86 special routines */

extern void	sysLoadGdt		(char *sysGdtr);

/* VxSim special routines */

#ifdef _WRS_ARCH_IS_SIMULATOR
extern void	sysNetIfConfig		(void);
extern void	sysUserSmInfoGet	(size_t * pSize, void ** pAddr);
#endif /* _WRS_ARCH_IS_SIMULATOR */

#endif	/* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCsysLibh */
