/* sysctlP.h - private sysctl library header */
                                                                                
/*
 * Copyright (c) 2007, 2010, 2013 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */
                                                                                
/*
modification history
--------------------
01d,10oct13,h_k  added _netSysctl and _netSysctlCli prototypes.
01c,29apr10,pad  Moved extern C statement after include statements.
01b,02apr10,jpb  Added prototype for sysctlScLibInit.
01a,31may07,pad  Created.
*/

/*
 * This private header file is meant for inclusion in all files with routines
 * creating OIDs at system initialization time. In those files this header
 * file should be used as a replacement for sys/sysctl.h.
 *
 * When this private header file is included all calls to sysctl_add_oid()
 * become calls to sysctl_add_oid_internal() which is functionally identical
 * to sysctl_add_oid() but does not acquire a protection mutex (unnecessary
 * at initialization time).
 */

#ifndef __INCsysctlPh
#define __INCsysctlPh
                                                                                
#ifndef  _ASMLANGUAGE

/* includes */

#include <sys/sysctl.h>

#ifdef __cplusplus
extern "C" {
#endif

/* defines */

#define sysctl_add_oid	sysctl_add_oid_internal

/* prototypes */

struct sysctl_oid *
    sysctl_add_oid_internal (struct sysctl_ctx_list * clist, 
                             struct sysctl_oid_list * parent,
			     int nbr, const char * name,
			     int kind, void * arg1, int arg2,
			     int (*handler) (SYSCTL_HANDLER_ARGS),
			     const char * fmt,
			     const char * descr);

extern STATUS sysctlScLibInit (void);

extern STATUS (* _netSysctlCli) (int argc, char ** pArgv, int nextLevelOid,
				 char * pOpts);

extern STATUS (* _netSysctl) (struct sysctl_oid * pOid, void * pArg1, int arg2,
			      struct sysctl_req * pReq);

#ifdef __cplusplus
    }
#endif
                                                                                
#endif  /* _ASMLANGUAGE */
                                                                                
#endif  /* __INCsysctlPh */
