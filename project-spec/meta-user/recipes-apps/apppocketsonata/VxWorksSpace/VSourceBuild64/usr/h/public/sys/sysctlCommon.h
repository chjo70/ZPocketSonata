/* sysctlCommon.h - sysctl definitions common between user & kernel mode */

/*
 * Copyright (c) 2004-2007, 2009-2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use 
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Mike Karels at Berkeley Software Design, Inc.
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
 *	@(#)sysctl.h	8.1 (Berkeley) 6/2/93
 * $FreeBSD: src/sys/sys/sysctl.h,v 1.81.2.6 2001/05/17 17:59:53 ru Exp $
 */

/*
modification history
--------------------
01o,23aug10,pad  Added inclusion of vsbConfig.h
01n,22jun10,jpb  Removed references to KERN_MEMTOP and KERN_PHYSMEMTOP for
                 LP64.
01m,09jun10,pcs  Add DEVMEM device name.
01l,05mar10,pcs  Add VM_DEVMEM_DEV_NAME
01l,28apr10,pad  Moved extern C statement after include statements.
01k,16nov09,jpb  Updated for LP64 support.
01j,18jun08,jmp  added KERN_COREDUMPFILTER[ADD|DELETE] for RTP Core Dump
		 memory filtering facility.
02i,05oct07,zl   added KERN_SHL_GOTT
02h,08jun07,pad  Introduced the CTL_USR_EXT identifier for user-specific OIDs.
02g,11apr07,pad  Added the KERN_SYSINFO identifier.
02f,22aug06,jpb  Removal of KERN_RTP_PTHREAD_INFO
02e,02nov05,h_k  added VM_SHM_DEV_NAME to get SHM device name.
02d,24aug05,pad  Updated a few comments.
02c,18aug05,pad  Added KERN_OSBUILDDATE identifier. Reset KERN_VERSION to be
                 linked with the kernel version proper. Activated KERN_OSTYPE,
		 KERN_OSRELEASE and KERN_OSREV (via rtpLib). Changed type of
		 KERN_OSREV and KERN_OSRELDATE from integer to string.
02b,11apr05,wap  Add definition for CTL_MAXNAME (SPR #106195)
02a,28oct04,to   Added HSR definitions for PPC970
01z,17aug04,pad  Added KERN_RTP_PTHREAD_INFO identifier.
01y,14jun04,job  Added MMU_BLOCKSIZE and MMU_PAGESIZE entries.
		 Created block of HSR values & created processor specific
		 overlaps.
01x,11jun04,dcc  Added clock macros
01w,07jun04,job  Added a number of new definitions
01v,11may04,job  Moved common definitions to this file
                 Removed __P macro around sysctl() prototype.
01u,24feb04,vvv  updated based on review comments
01t,20feb04,vvv  added support for transparent nodes
01t,23feb04,kkz  added #defines for remlib
01t,12feb04,asr  added new defines for loginLib
01s,24nov03,vvv  added include for logLib.h
01r,20nov03,niq  Remove copyright_wrs.h file inclusion
01q,20nov03,vvv  updated for RTP support
01p,05nov03,cdw  Removal of unnecessary _KERNEL guards.
01o,04nov03,rlm  Ran batch header path update for header re-org.
01n,03nov03,rlm  Removed wrn/coreip/ prefix from #includes for header re-org.
01m,08sep03,vvv  merged from ACCORDION_BASE6_MERGE_BASELINE
01l,10jun03,vvv  include netVersion.h
01k,14may03,vvv  made sysctlbyname() available when _KERNEL is not defined
01j,11apr03,syy  Fixed Diab compiler warnings
01i,10mar03,ann  removed the preceding ## from the macros.
01h,09sep02,hsh  add c++ protection
01g,18mar02,ann  adding the prototype for sysctlnametomib
01f,11mar02,ann  fixing compilation warnings
01e,22feb02,ham  changed for tornado build.
01d,21feb02,ann  removed the references to MGMT_LOCK
01c,10jan02,ann  adding the prototype for sysctl
01b,12dec01,ann  corrected the LOG message in SYSCTL_NODE_CHILDREN
01a,05dec01,niq  Created from BSD 4.3
*/

#ifndef _SYS_SYSCTLCOMMON_H_
#define	_SYS_SYSCTLCOMMON_H_

#include <vsbConfig.h>
#include <types/vxTypesOld.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef CTL_MAXNAME
#define CTL_MAXNAME	12	/* Largest number of component levels supported
				   in a MIB-style name vector */
#endif
      
/*
 * Top-level identifiers
 */
#define	CTL_UNSPEC               0  /* reserved. Do not use */
#define	CTL_KERN                 1  /* "high kernel": proc, limits */
#define	CTL_VM                   2  /* virtual memory */
#define	CTL_VFS                  3  /* file system. Currently unused */
#define	CTL_NET                  4  /* network, see socket.h */
#define	CTL_DEBUG                5  /* debugging parameters. Currently unused */
#define	CTL_HW                   6  /* generic cpu/io */
#define	CTL_MACHDEP              7  /* machine dependent. Currently unused */
#define	CTL_USER                 8  /* user-level (RTP). Currently unused */
#define	CTL_P1003_1B             9  /* POSIX 1003.1B. Currently unused */
#define	CTL_USR_EXT		10  /* made available for user extensions */
#define	CTL_MAXID               11  /* number of valid top-level ids */

#ifdef _WRS_KERNEL
#define CTL_NAMES { \
	{ 0, 0 }, \
	{ "kern", CTLTYPE_NODE }, \
	{ "vm", CTLTYPE_NODE }, \
	{ "vfs", CTLTYPE_NODE }, \
	{ "net", CTLTYPE_NODE }, \
	{ "debug", CTLTYPE_NODE }, \
	{ "hw", CTLTYPE_NODE }, \
	{ "machdep", CTLTYPE_NODE }, \
	{ "user", CTLTYPE_NODE }, \
	{ "p1003_1b", CTLTYPE_NODE }, \
}
#endif /* _WRS_KERNEL */

/*
 * CTL_KERN identifiers
 */
#define	KERN_OSTYPE              1  /* string: system name */
#define	KERN_OSRELEASE           2  /* string: system release (maj.min.maint) */
#define	KERN_OSREV               3  /* string: system version (reserved) */
#define	KERN_VERSION             4  /* string: kernel version */
#define	KERN_MAXVNODES           5  /* int: max vnodes */
#define	KERN_MAXPROC             6  /* int: max processes */
#define	KERN_MAXFILES            7  /* int: max open files */
#define	KERN_ARGMAX              8  /* int: max arguments to exec */
#define	KERN_SECURELVL           9  /* int: system security level */
#define	KERN_HOSTNAME           10  /* string: hostname */
#define	KERN_HOSTID             11  /* int: host identifier */
#define	KERN_CLOCKRATE          12  /* int: system clockrate */
#define	KERN_VNODE              13  /* struct: vnode structures */
#define	KERN_PROC               14  /* struct: process entries */
#define	KERN_FILE               15  /* struct: file entries */
#define	KERN_PROF               16  /* node: kernel profiling info */
#define	KERN_POSIX1             17  /* int: POSIX.1 version */
#define	KERN_NGROUPS            18  /* int: # of supplemental group ids */
#define	KERN_JOB_CONTROL        19  /* int: is job control available */
#define	KERN_SAVED_IDS          20  /* int: saved set-user/group-ID */
#define	KERN_BOOTTIME           21  /* struct: time kernel was booted */
#define KERN_NISDOMAINNAME      22  /* string: YP domain name */
#define KERN_UPDATEINTERVAL     23  /* int: update process sleep time */
#define KERN_OSRELDATE          24  /* string: OS release date */
#define KERN_NTP_PLL            25  /* node: NTP PLL control */
#define	KERN_BOOTFILE           26  /* string: name of booted kernel */
#define	KERN_MAXFILESPERPROC    27  /* int: max open files per proc */
#define	KERN_MAXPROCPERUID      28  /* int: max processes per uid */
#define KERN_DUMPDEV            29  /* dev_t: device to dump on */
#define	KERN_IPC                30  /* node: anything related to IPC */
#define	KERN_LOGINVERIFY        31  /* login user verification */
#define	KERN_PS_STRINGS         32  /* int: address of PS_STRINGS */
#define	KERN_USRSTACK           33  /* int: address of USRSTACK */
#define	KERN_LOGSIGEXIT         34  /* int: do we log sigexit procs? */
#define	KERN_USERID             35  /* string: target-wide username */
#define	KERN_PASSWORD           36  /* string: target-wide password */

/* These ones are defined by rtpSysctl.c at run time */

#define KERN_TICKGET            37  /* long: current tick count */
#define KERN_TICK64GET          38  /* quad: current tick count (64 bit) */
#define KERN_SYSCALL            39  /* node: is a system call present */
#define KERN_AUXCLOCKRATE       40  /* int: auxilary clock rate */
#ifndef _WRS_CONFIG_LP64
#define KERN_MEMTOP             41  /* int: top of logical memory */
#define KERN_PHYSMEMTOP         42  /* int: top of physical memory */
#endif /* ! _WRS_CONFIG_LP64 */
#define KERN_PROCESSORNUM       43  /* int: processor number for CPU board */
#define KERN_CLOCK_GETRES	44  /* node: clock resolution */
#define KERN_CLOCK_TIME		45  /* node: set/get clock time */
#define KERN_SYSINFO		46  /* struct: misc system information */
#define	KERN_OSBUILDDATE	47  /* string: OS build date (compile time) */
#define	KERN_SHL_GOTT		48  /* uint: shared library GOTT */

/* Core Dump memory filtering sysctl commands */

#define KERN_COREDUMPFILTERADD	 49 /* coreDumpMemFilterAdd() */
#define KERN_COREDUMPFILTERDELETE 50 /* coreDumpMemFilterDelete() */

#define KERN_MAXID              51  /* number of valid kern ids */

/*
 * KERN_PROC subtypes
 */
#define KERN_PROC_ALL		0	/* everything */
#define	KERN_PROC_PID		1	/* by process id */
#define	KERN_PROC_PGRP		2	/* by process group id */
#define	KERN_PROC_SESSION	3	/* by session of pid */
#define	KERN_PROC_TTY		4	/* by controlling tty */
#define	KERN_PROC_UID		5	/* by effective uid */
#define	KERN_PROC_RUID		6	/* by real uid */
#define	KERN_PROC_ARGS		7	/* get/set arguments/proctitle */

/*
 * KERN_IPC identifiers
 */
#define KIPC_MAXSOCKBUF		1	/* int: max size of a socket buffer */
#define	KIPC_SOCKBUF_WASTE	2	/* int: wastage factor in sockbuf */
#define	KIPC_SOMAXCONN		3	/* int: max length of connection q */
#define	KIPC_MAX_LINKHDR	4	/* int: max length of link header */
#define	KIPC_MAX_PROTOHDR	5	/* int: max length of network header */
#define	KIPC_MAX_HDR		6	/* int: max total length of headers */
#define	KIPC_MAX_DATALEN	7	/* int: max length of data? */
#define	KIPC_MBSTAT		8	/* struct: mbuf usage statistics */
#define	KIPC_NMBCLUSTERS	9	/* int: maximum mbuf clusters */

/* The System call node is organized into various functions, where the
 * OID is KERN.SYSCALL.<syscallNum|groupNum>.identifier
 */

#define KERN_SYSCALL_NAME           0  /* string: system call name */
#define KERN_SYSCALL_NARGS          1  /* int: number of arguments taken */
#define KERN_SYSCALL_GROUP          2  /* string: system call group name */
#define KERN_SYSCALL_GROUP_NROUTINE 3  /* int: number of routines in group */
#define KERN_SYSCALL_MAX            3

#ifdef _WRS_KERNEL
#define CTL_KERN_NAMES { \
	{ 0, 0 }, \
	{ "ostype", CTLTYPE_STRING }, \
	{ "osrelease", CTLTYPE_STRING }, \
	{ "osrevision", CTLTYPE_STRING }, \
	{ "version", CTLTYPE_STRING }, \
	{ "maxvnodes", CTLTYPE_INT }, \
	{ "maxproc", CTLTYPE_INT }, \
	{ "maxfiles", CTLTYPE_INT }, \
	{ "argmax", CTLTYPE_INT }, \
	{ "securelevel", CTLTYPE_INT }, \
	{ "hostname", CTLTYPE_STRING }, \
	{ "hostid", CTLTYPE_INT }, \
	{ "clockrate", CTLTYPE_INT }, \
	{ "vnode", CTLTYPE_STRUCT }, \
	{ "proc", CTLTYPE_STRUCT }, \
	{ "file", CTLTYPE_STRUCT }, \
	{ "profiling", CTLTYPE_NODE }, \
	{ "posix1version", CTLTYPE_INT }, \
	{ "ngroups", CTLTYPE_INT }, \
	{ "job_control", CTLTYPE_INT }, \
	{ "saved_ids", CTLTYPE_INT }, \
	{ "boottime", CTLTYPE_STRUCT }, \
	{ "nisdomainname", CTLTYPE_STRING }, \
	{ "update", CTLTYPE_INT }, \
	{ "osreldate", CTLTYPE_STRING }, \
	{ "ntp_pll", CTLTYPE_NODE }, \
	{ "bootfile", CTLTYPE_STRING }, \
	{ "maxfilesperproc", CTLTYPE_INT }, \
	{ "maxprocperuid", CTLTYPE_INT }, \
	{ "dumpdev", CTLTYPE_STRUCT }, /* we lie; don't print as int */ \
	{ "ipc", CTLTYPE_NODE }, \
	{ "loginverify", CTLTYPE_INT }, \
	{ "ps_strings", CTLTYPE_INT }, \
	{ "usrstack", CTLTYPE_INT }, \
	{ "logsigexit", CTLTYPE_INT }, \
	{ "userid", CTLTYPE_STRING }, \
	{ "password", CTLTYPE_STRING }, \
	{ "tickGet", CTLTYPE_LONG }, \
	{ "tick64Get", CTLTYPE_QUAD }, \
	{ "syscall", CTLTYPE_NODE }, \
	{ "auxclockrate", CTLTYPE_INT }, \
	{ "memtop", CTLTYPE_INT }, \
	{ "physmemtop", CTLTYPE_INT }, \
	{ "processornum", CTLTYPE_INT }, \
	{ "clock_getres", CTLTYPE_NODE }, \
	{ "clock_time", CTLTYPE_NODE }, \
	{ "osbuilddate", CTLTYPE_STRING }, \
	{ "shlGott", CTLTYPE_UINT }, \
	{ "coreDumpMemFilterAdd", CTLTYPE_INT }, \
	{ "coreDumpMemFilterDelete", CTLTYPE_INT }, \
}
#endif	/* _WRS_KERNEL */

/*
 * CTL_VM identifiers
 */
#define	VM_SHM_DEV_NAME		1	/* string: SHM device name */
#define	VM_DEVMEM_DEV_NAME	2	/* string: DEVMEM device name */

#ifdef	_WRS_KERNEL
#define CTL_VM_NAMES { \
	{ "shmdevname", CTLTYPE_STRING }, \
	{ "devMemdevname", CTLTYPE_STRING }, \
}
#endif	/* _WRS_KERNEL */

/*
 * CTL_VFS identifiers
 */
#ifdef	_WRS_KERNEL
#define CTL_VFS_NAMES { \
	{ "vfsconf", CTLTYPE_STRUCT }, \
}
#endif /* _WRS_KERNEL */

/*
 * CTL_HW identifiers
 */
#define	HW_MACHINE               1  /* string: machine class */
#define	HW_MODEL                 2  /* string: specific machine model */
#define	HW_NCPU                  3  /* int: number of cpus */
#define	HW_BYTEORDER             4  /* int: machine byte order */
#define	HW_PHYSMEM               5  /* long: total memory */
#define	HW_USERMEM               6  /* long: non-kernel memory */
#define	HW_PAGESIZE              7  /* int: software page size */
#define	HW_DISKNAMES             8  /* strings: disk drive names */
#define	HW_DISKSTATS             9  /* struct: diskstats[] */
#define HW_FLOATINGPT           10  /* int: has HW floating point? */
#define HW_MACHINE_ARCH         11  /* string: machine architecture */
#define HW_ENDIAN               12  /* string: endianness (big/little) */
#define HW_BSP                  13  /* node: bsp information */
#define HW_PAL                  14  /* node: pal information */
#define HW_CACHE                15  /* node: cache information */
#define HW_MMU                  16  /* node: mmu information */
#define	HW_MAXID                16  /* number of valid hw ids */

/* CTL_HW.BSP identifiers */

#define HW_BSP_MODEL             0  /* string: model name of CPU board */
#define HW_BSP_REVISION          1  /* string: BSP revision */

/* CTL_HW.PAL identifiers */

#define HW_PAL_CPU               0  /* node: cpu information */
#define HW_PAL_VERSION           1  /* string: PAL version */

/* CTL_HW.PAL.CPU identifiers */

/* A set of generic Hardware Specific Registers. Different architectures
 * can map specific registers onto this set of OIDs 
 */

#define HW_PAL_CPU_HSR0          0  /* long: Hardware Specific Register 0 */
#define HW_PAL_CPU_HSR1          1  /* long: Hardware Specific Register 1 */
#define HW_PAL_CPU_HSR2          2  /* long: Hardware Specific Register 2 */
#define HW_PAL_CPU_HSR3          3  /* long: Hardware Specific Register 3 */
#define HW_PAL_CPU_HSR4          4  /* long: Hardware Specific Register 4 */
#define HW_PAL_CPU_HSR5          5  /* long: Hardware Specific Register 5 */
#define HW_PAL_CPU_HSR6          6  /* long: Hardware Specific Register 6 */
#define HW_PAL_CPU_HSR7          7  /* long: Hardware Specific Register 7 */
#define HW_PAL_CPU_HSR8          8  /* long: Hardware Specific Register 8 */
#define HW_PAL_CPU_HSR9          9  /* long: Hardware Specific Register 9 */
#define HW_PAL_CPU_HSR10        10  /* long: Hardware Specific Register 10 */
#define HW_PAL_CPU_HSR11        11  /* long: Hardware Specific Register 11 */
#define HW_PAL_CPU_HSR12        12  /* long: Hardware Specific Register 12 */
#define HW_PAL_CPU_HSR13        13  /* long: Hardware Specific Register 13 */
#define HW_PAL_CPU_HSR14        14  /* long: Hardware Specific Register 14 */
#define HW_PAL_CPU_HSR15        15  /* long: Hardware Specific Register 15 */
#define HW_PAL_CPU_HSR16        16  /* long: Hardware Specific Register 16 */
#define HW_PAL_CPU_HSR17        17  /* long: Hardware Specific Register 17 */
#define HW_PAL_CPU_HSR18        18  /* long: Hardware Specific Register 18 */
#define HW_PAL_CPU_HSR19        19  /* long: Hardware Specific Register 19 */
#define HW_PAL_CPU_HSR20        20  /* long: Hardware Specific Register 20 */
#define HW_PAL_CPU_HSR21        21  /* long: Hardware Specific Register 21 */
#define HW_PAL_CPU_HSR22        22  /* long: Hardware Specific Register 22 */
#define HW_PAL_CPU_HSR23        23  /* long: Hardware Specific Register 23 */
#define HW_PAL_CPU_HSR24        24  /* long: Hardware Specific Register 24 */
#define HW_PAL_CPU_HSR25        25  /* long: Hardware Specific Register 25 */
#define HW_PAL_CPU_HSR26        26  /* long: Hardware Specific Register 26 */
#define HW_PAL_CPU_HSR27        27  /* long: Hardware Specific Register 27 */
#define HW_PAL_CPU_HSR28        28  /* long: Hardware Specific Register 28 */
#define HW_PAL_CPU_HSR29        29  /* long: Hardware Specific Register 29 */
#define HW_PAL_CPU_HSR30        30  /* long: Hardware Specific Register 30 */
#define HW_PAL_CPU_HSR31        31  /* long: Hardware Specific Register 31 */

/* PAL generic information */

#define HW_PAL_CPU_PROCESSOR    32  /* string: processor chip name */
#define HW_PAL_CPU_FAMILY       33  /* string: CPU family */
#define HW_PAL_CPU_TLBENTRIES   34  /* int: number of TLB entries */

/* ARM/XScale Hardware Specific Registers: These map onto specific HSR values */

#define HW_PAL_CPU_ARM_MMUID     0  /* int: processor ID register */

/* PPC Hardware Specific Registers: These map onto specific HSR values */

#define HW_PAL_CPU_PPC_PVR       0  /* long: processor version register */
#define HW_PAL_CPU_PPC_HID0      1  /* long: hardware specific register 0 */
#define HW_PAL_CPU_PPC_HID1      2  /* long: hardware specific register 0 */

#define HW_PAL_CPU_PPC_HID0L     1  /* long: hardware specific register 0 */
#define HW_PAL_CPU_PPC_HID0H     2  /* long: hardware specific register 0 */
#define HW_PAL_CPU_PPC_HID1L     3  /* long: hardware specific register 0 */
#define HW_PAL_CPU_PPC_HID1H     4  /* long: hardware specific register 0 */
#define HW_PAL_CPU_PPC_HID4L     5  /* long: hardware specific register 0 */
#define HW_PAL_CPU_PPC_HID4H     6  /* long: hardware specific register 0 */
#define HW_PAL_CPU_PPC_HID5L     7  /* long: hardware specific register 0 */
#define HW_PAL_CPU_PPC_HID5H     8  /* long: hardware specific register 0 */

/* MIPS Hardware Specific Registers: These map onto specific HSR values */

#define HW_PAL_CPU_MIPS_WIRED    0  /* long: processor WIRED register */
#define HW_PAL_CPU_MIPS_PRID     1  /* long: processor PRID register */
#define HW_PAL_CPU_MIPS_CONFIG   2  /* long: processor CONFIG register */
#define HW_PAL_CPU_MIPS_CONFIG1  3  /* long: processor CONFIG1 register */
#define HW_PAL_CPU_MIPS_CONFIG2  4  /* long: processor CONFIG2 register */
#define HW_PAL_CPU_MIPS_CONFIG3  5  /* long: processor CONFIG3 register */

/* CTL_HW.CACHE identifiers */

#define HW_CACHE_INSTR_LINE_SIZE      0  /* int: instruction cache line size */
#define HW_CACHE_DATA_LINE_SIZE       1  /* int: data cache line size */
#define HW_CACHE_BRANCH_LINE_SIZE     2  /* int: branch cache line size */
#define HW_CACHE_L2_LINE_SIZE         3  /* int: L2 cache line size */
#define HW_CACHE_L3_LINE_SIZE         4  /* int: L3 cache line size */
#define HW_CACHE_INSTR_TLB_LINE_SIZE  5  /* int: instr. TLB cache line size */
#define HW_CACHE_DATA_TLB_LINE_SIZE   6  /* int: data TLB cache line size */
#define HW_CACHE_ALTPRI_LINE_SIZE     7  /* int: alt. primary cache line size */

#define HW_CACHE_INSTR_SIZE          10  /* int: instruction cache size */
#define HW_CACHE_DATA_SIZE           11  /* int: data cache size */
#define HW_CACHE_BRANCH_SIZE         12  /* int: branch cache size */
#define HW_CACHE_L2_SIZE             13  /* int: L2 cache size */
#define HW_CACHE_L3_SIZE             14  /* int: L3 cache size */
#define HW_CACHE_INSTR_TLB_SIZE      15  /* int: instr. TLB cache size */
#define HW_CACHE_DATA_TLB_SIZE       16  /* int: data TLB cache size */
#define HW_CACHE_ALTPRI_SIZE         17  /* int: alt. primary cache size */

/* CTL_HW.MMU identifiers */

#define HW_MMU_TLBSIZE                0  /* int: TLB size */
#define HW_MMU_BLOCKSIZE              1  /* int: block size */
#define HW_MMU_PAGESIZE               2  /* int: page size */

#ifdef _WRS_KERNEL
#define CTL_HW_NAMES { \
	{ 0, 0 }, \
	{ "machine", CTLTYPE_STRING }, \
	{ "model", CTLTYPE_STRING }, \
	{ "ncpu", CTLTYPE_INT }, \
	{ "byteorder", CTLTYPE_INT }, \
	{ "physmem", CTLTYPE_LONG }, \
	{ "usermem", CTLTYPE_LONG }, \
	{ "pagesize", CTLTYPE_INT }, \
	{ "disknames", CTLTYPE_STRUCT }, \
	{ "diskstats", CTLTYPE_STRUCT }, \
	{ "floatingpoint", CTLTYPE_INT }, \
	{ "machine_arch", CTLTYPE_STRING }, \
	{ "endian", CTLTYPE_STRING }, \
	{ "bsp", CTLTYPE_NODE }, \
	{ "pal", CTLTYPE_NODE }, \
	{ "cache", CTLTYPE_NODE }, \
	{ "mmu", CTLTYPE_NODE }, \
}
#endif /* _WRS_KERNEL */

/*
 * CTL_USER definitions
 */
#define	USER_CS_PATH		 1	/* string: _CS_PATH */
#define	USER_BC_BASE_MAX	 2	/* int: BC_BASE_MAX */
#define	USER_BC_DIM_MAX		 3	/* int: BC_DIM_MAX */
#define	USER_BC_SCALE_MAX	 4	/* int: BC_SCALE_MAX */
#define	USER_BC_STRING_MAX	 5	/* int: BC_STRING_MAX */
#define	USER_COLL_WEIGHTS_MAX	 6	/* int: COLL_WEIGHTS_MAX */
#define	USER_EXPR_NEST_MAX	 7	/* int: EXPR_NEST_MAX */
#define	USER_LINE_MAX		 8	/* int: LINE_MAX */
#define	USER_RE_DUP_MAX		 9	/* int: RE_DUP_MAX */
#define	USER_POSIX2_VERSION	10	/* int: POSIX2_VERSION */
#define	USER_POSIX2_C_BIND	11	/* int: POSIX2_C_BIND */
#define	USER_POSIX2_C_DEV	12	/* int: POSIX2_C_DEV */
#define	USER_POSIX2_CHAR_TERM	13	/* int: POSIX2_CHAR_TERM */
#define	USER_POSIX2_FORT_DEV	14	/* int: POSIX2_FORT_DEV */
#define	USER_POSIX2_FORT_RUN	15	/* int: POSIX2_FORT_RUN */
#define	USER_POSIX2_LOCALEDEF	16	/* int: POSIX2_LOCALEDEF */
#define	USER_POSIX2_SW_DEV	17	/* int: POSIX2_SW_DEV */
#define	USER_POSIX2_UPE		18	/* int: POSIX2_UPE */
#define	USER_STREAM_MAX		19	/* int: POSIX2_STREAM_MAX */
#define	USER_TZNAME_MAX		20	/* int: POSIX2_TZNAME_MAX */
#define	USER_MAXID		21	/* number of valid user ids */

#ifdef _WRS_KERNEL
#define	CTL_USER_NAMES { \
	{ 0, 0 }, \
	{ "cs_path", CTLTYPE_STRING }, \
	{ "bc_base_max", CTLTYPE_INT }, \
	{ "bc_dim_max", CTLTYPE_INT }, \
	{ "bc_scale_max", CTLTYPE_INT }, \
	{ "bc_string_max", CTLTYPE_INT }, \
	{ "coll_weights_max", CTLTYPE_INT }, \
	{ "expr_nest_max", CTLTYPE_INT }, \
	{ "line_max", CTLTYPE_INT }, \
	{ "re_dup_max", CTLTYPE_INT }, \
	{ "posix2_version", CTLTYPE_INT }, \
	{ "posix2_c_bind", CTLTYPE_INT }, \
	{ "posix2_c_dev", CTLTYPE_INT }, \
	{ "posix2_char_term", CTLTYPE_INT }, \
	{ "posix2_fort_dev", CTLTYPE_INT }, \
	{ "posix2_fort_run", CTLTYPE_INT }, \
	{ "posix2_localedef", CTLTYPE_INT }, \
	{ "posix2_sw_dev", CTLTYPE_INT }, \
	{ "posix2_upe", CTLTYPE_INT }, \
	{ "stream_max", CTLTYPE_INT }, \
	{ "tzname_max", CTLTYPE_INT }, \
}
#endif /* _WRS_KERNEL */

#define CTL_P1003_1B_ASYNCHRONOUS_IO		1	/* boolean */
#define CTL_P1003_1B_MAPPED_FILES		2	/* boolean */
#define CTL_P1003_1B_MEMLOCK			3	/* boolean */
#define CTL_P1003_1B_MEMLOCK_RANGE		4	/* boolean */
#define CTL_P1003_1B_MEMORY_PROTECTION		5	/* boolean */
#define CTL_P1003_1B_MESSAGE_PASSING		6	/* boolean */
#define CTL_P1003_1B_PRIORITIZED_IO		7	/* boolean */
#define CTL_P1003_1B_PRIORITY_SCHEDULING	8	/* boolean */
#define CTL_P1003_1B_REALTIME_SIGNALS		9	/* boolean */
#define CTL_P1003_1B_SEMAPHORES			10	/* boolean */
#define CTL_P1003_1B_FSYNC			11	/* boolean */
#define CTL_P1003_1B_SHARED_MEMORY_OBJECTS	12	/* boolean */
#define CTL_P1003_1B_SYNCHRONIZED_IO		13	/* boolean */
#define CTL_P1003_1B_TIMERS			14	/* boolean */
#define CTL_P1003_1B_AIO_LISTIO_MAX		15	/* int */
#define CTL_P1003_1B_AIO_MAX			16	/* int */
#define CTL_P1003_1B_AIO_PRIO_DELTA_MAX		17	/* int */
#define CTL_P1003_1B_DELAYTIMER_MAX		18	/* int */
#define CTL_P1003_1B_MQ_OPEN_MAX		19	/* int */
#define CTL_P1003_1B_PAGESIZE			20	/* int */
#define CTL_P1003_1B_RTSIG_MAX			21	/* int */
#define CTL_P1003_1B_SEM_NSEMS_MAX		22	/* int */
#define CTL_P1003_1B_SEM_VALUE_MAX		23	/* int */
#define CTL_P1003_1B_SIGQUEUE_MAX		24	/* int */
#define CTL_P1003_1B_TIMER_MAX			25	/* int */

#define CTL_P1003_1B_MAXID		26

#ifdef _WRS_KERNEL
#define	CTL_P1003_1B_NAMES { \
	{ 0, 0 }, \
	{ "asynchronous_io", CTLTYPE_INT }, \
	{ "mapped_files", CTLTYPE_INT }, \
	{ "memlock", CTLTYPE_INT }, \
	{ "memlock_range", CTLTYPE_INT }, \
	{ "memory_protection", CTLTYPE_INT }, \
	{ "message_passing", CTLTYPE_INT }, \
	{ "prioritized_io", CTLTYPE_INT }, \
	{ "priority_scheduling", CTLTYPE_INT }, \
	{ "realtime_signals", CTLTYPE_INT }, \
	{ "semaphores", CTLTYPE_INT }, \
	{ "fsync", CTLTYPE_INT }, \
	{ "shared_memory_objects", CTLTYPE_INT }, \
	{ "synchronized_io", CTLTYPE_INT }, \
	{ "timers", CTLTYPE_INT }, \
	{ "aio_listio_max", CTLTYPE_INT }, \
	{ "aio_max", CTLTYPE_INT }, \
	{ "aio_prio_delta_max", CTLTYPE_INT }, \
	{ "delaytimer_max", CTLTYPE_INT }, \
	{ "mq_open_max", CTLTYPE_INT }, \
	{ "pagesize", CTLTYPE_INT }, \
	{ "rtsig_max", CTLTYPE_INT }, \
	{ "nsems_max", CTLTYPE_INT }, \
	{ "sem_value_max", CTLTYPE_INT }, \
	{ "sigqueue_max", CTLTYPE_INT }, \
	{ "timer_max", CTLTYPE_INT }, \
}
#endif /* _WRS_KERNEL */

int	sysctl (int *, u_int, void *, size_t *, void *, size_t);

#ifdef __cplusplus
}
#endif
    
#endif	/* !_SYS_SYSCTLCOMMON_H_ */
