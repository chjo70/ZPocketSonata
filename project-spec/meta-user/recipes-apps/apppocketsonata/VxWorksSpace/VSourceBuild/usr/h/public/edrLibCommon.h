/* edrLibCommon.h - Error Detection and Reporting subsystem */

/* Copyright (c) 2004 Wind River Systems, Inc. */

/*
modification history
--------------------
01d,23aug04,md  add additional errno values
01c,07jun04,md  add memory map option flag
01b,21may04,md  add option flags
01a,02feb04,md  created
*/

#ifndef __INCedrLibCommon_h
#define __INCedrLibCommon_h

#include <stdlib.h>
#include "vxWorks.h"

#ifdef __cplusplus
extern "C" {
#endif


/* defines */

/* severity levels */

#define EDR_SEVERITY_FATAL	     0x00001
#define EDR_SEVERITY_NONFATAL	     0x00002
#define EDR_SEVERITY_WARNING	     0x00003
#define EDR_SEVERITY_INFO	     0x00004

#define EDR_SEVERITY_MASK	     0x0000f

/* facilities for system/kernel space use */

#define EDR_FACILITY_KERNEL	     0x00010	/* VxWorks kernel events    */
#define EDR_FACILITY_INTERRUPT	     0x00020	/* interrupt handler events */
#define EDR_FACILITY_INIT	     0x00030	/* system startup events    */ 
#define EDR_FACILITY_BOOT	     0x00040	/* system boot events       */
#define EDR_FACILITY_REBOOT	     0x00050	/* system restart events    */

/* facilities for user-level (RTP) space use */

#define EDR_FACILITY_RTP	     0x00100	/* RTP system events	    */
#define EDR_FACILITY_USER	     0x00200	/* user generated events    */

#define EDR_FACILITY_MASK	     0x00ff0

/* error injection options */

#define EDR_EXCLUDE_REGISTERS	     0x01000	/* don't include registers   */
#define EDR_EXCLUDE_TRACEBACK	     0x02000	/* don't include stack trace */
#define EDR_EXCLUDE_EXCINFO	     0x04000	/* don't include exc info    */
#define EDR_EXCLUDE_DISASSEMBLY	     0x08000	/* don't include code dis.   */
#define EDR_EXCLUDE_MEMORYMAP	     0x10000	/* don't include memory map  */

#define EDR_OPTIONS_MASK	     0xff000

/* error codes */

#define S_edrLib_NOT_INITIALIZED	(M_edrLib | 1)
#define S_edrLib_ERRLOG_CORRUPTED	(M_edrLib | 2)
#define S_edrLib_ERRLOG_INCOMPATIBLE	(M_edrLib | 3)
#define S_edrLib_PROTECTION_FAILURE	(M_edrLib | 4)
#define S_edrLib_PMREGION_ERROR		(M_edrLib | 5)
#define S_edrLib_INVALID_OPTION		(M_edrLib | 6)
#define S_edrLib_INJECT_HOOK_TABLE_FULL	(M_edrLib | 7)
#define S_edrLib_INJECT_HOOK_NOT_FOUND	(M_edrLib | 8)
#define S_edrLib_TEXT_HOOK_TABLE_FULL	(M_edrLib | 9)
#define S_edrLib_TEXT_HOOK_NOT_FOUND	(M_edrLib | 10)
#define S_edrLib_PP_HOOK_TABLE_FULL	(M_edrLib | 11)
#define S_edrLib_PP_HOOK_NOT_FOUND	(M_edrLib | 12)

/* ED&R mode flags */

#define	EDR_FLAG_DEBUG		0x01
#define	EDR_FLAG_MASK		0x7fffffff

extern int edrFlagsGet(void);

#ifdef __cplusplus
}
#endif

#endif /* __INCedrLibCommon_h */
