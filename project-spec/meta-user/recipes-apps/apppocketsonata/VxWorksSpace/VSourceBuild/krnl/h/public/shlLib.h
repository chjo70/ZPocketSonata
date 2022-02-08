/* shlLib.h - shared library support library header file */

/*
 * Copyright (c) 2004, 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01h,27may10,pad  Added 'extern C' statement.
01g,21sep04,bpn  Added shlShow() and rtpShlShow() prototypes.
01f,09sep04,job  Added shlLibInit() prototype
01e,14may04,kk   added shlShowInit() & shlShellCmdInit() prototype 
01d,10may04,dms  Switch to an integral type for SHL_ID in the kernel.
01c,03may04,kk   added SHL_XXX verbosity levels for shlShow()
01b,20apr04,pad  Moved declarations of shlLibInit() and shlRtpDeleteAll() in
                 private/shlLibP.h
01a,26mar04,dms  created based on sdLib.h
*/

#ifndef __INCshlLibh
#define	__INCshlLibh

#include <vxWorks.h>

/* defines */

#define SHL_SHOW_VERBOSE_ALL    3		/* for shlShow() */
#define SHL_SHOW_ALL            2
#define SHL_SHOW_VERBOSE        1
#define SHL_SHOW_DEFAULT        0

#ifdef __cplusplus
extern "C" {
#endif

/* typedefs */

typedef int	SHL_ID;

#ifdef __cplusplus
}
#endif

#include <shlLibCommon.h>	/* requires SHL_ID type definition */

#ifdef __cplusplus
extern "C" {
#endif

/* prototypes */

extern STATUS	shlLibInit (void);
extern STATUS	shlShowInit (void);	/* initialize show routines for SHL */
extern BOOL	shlShow (SHL_ID shlId, int level);
extern STATUS	rtpShlShow (RTP_ID rtpId);
extern STATUS	shlShellCmdInit (void);	/* initialize cmd shell rtns for SHL */

#ifdef __cplusplus
}
#endif

#endif /* __INCshlLibh */
