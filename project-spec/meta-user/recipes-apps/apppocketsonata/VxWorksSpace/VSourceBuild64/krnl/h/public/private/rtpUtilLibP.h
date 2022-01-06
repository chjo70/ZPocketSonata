/* rtpUtilLibP.h - real time process utility library header */

/* 
 * Copyright 2003-2004, 2007, 2009-2010, 2013-2014 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
22apr14,rlp  Added rtpStatusStrGet and rtpOptionsStrGet prototypes.
16oct13,h_k  removed symLib.h header inclusion if OSTOOLS is uninstalled.
07aug13,jmp  Added rtpTaskEach() signature.
29apr10,pad  Moved extern C statement after include statements.
03dec09,cww  LP64 adaptation
10may07,v_r  Added rtpSymTblIdGet() signature.
12oct04,kk   removed kernelBaseLib.h include
27sep04,ans  code inspection comments.
10aug04,kk   renamed rtpBaseLib to kernelBaseLib
14jul04,job  Added prototype for rtpNameTruncate() (SPR#99331)
11may04,dms  Use the new small-integer SHL_IDs.
22mar04,pad  Some more fiddling with rtpShlSymbolsRegister() and
             rtpShlSymbolsUnregister()'s APIs.
16mar04,pad  Changed some parameter names for rtpShlSymbolsRegister.
12mar04,pad  Added prototypes of rtpShlSymbolsRegister() and
             rtpShlSymbolsUnregister() API.
25nov03,nrj  code review mods
10nov03,nrj  removed typedef in front of func decl.
23oct03,nrj  created.
*/

#ifndef	__INCrtpUtilLibPh
#define	__INCrtpUtilLibPh

#ifdef	_ASMLANGUAGE
#else	/* _ASMLANGUAGE */

/* includes */

#include <vxWorks.h>
#include <rtpLib.h>
#include <classLib.h>
#include <dllLib.h>
#include <lstLib.h>
#include <shlLib.h>
#ifdef	_WRS_CONFIG_OSTOOLS
#include <symLib.h>
#endif	/* _WRS_CONFIG_OSTOOLS */
#include <private/objLibP.h>
#include <private/rtpSigLibP.h>

#ifdef __cplusplus
extern "C" {
#endif

/* macros */

/*
 * Macros for traversing tasks of the RTP 
 * Note that RTP should be locked to use FOR/END_FOR macros
 *
 *The FOR and END_FOR should always be coupled.
 */

#define FOR_EACH_TASK_OF_RTP(rtpId, tid)                                    \
	{                                                                   \
	int oldErrno;                                                       \
	DL_NODE * pNode ;                                                   \
	pNode = DLL_FIRST (&((OBJ_CORE *)rtpId)->ownerList);                \
	while (pNode != NULL)                                               \
	    {                                                               \
	    tid = (WIND_TCB *) ((long)pNode - OFFSET (OBJ_CORE, ownerNode)); \
            oldErrno = errno;                                               \
	    pNode = DLL_NEXT (pNode);                                       \
	    if (TASK_ID_VERIFY (tid) != OK)                                 \
		{                                                           \
                errno = oldErrno;                                            \
		continue;                                                   \
		}

#define END_FOR_EACH_TASK_OF_RTP } }

/* defines */

#define RTP_TRUNC_NAME_LENGTH   20  /* max RTP name len display in summary */

#define RTP_STATUS_STR_LENGTH   14	/* max RTP type len string */

/* typedefs */

/* externs */

extern void	    rtpNameTruncate (RTP_ID rtpId, char *rtpName);
extern STATUS	    rtpTaskAllStop (RTP_ID rtpId);
extern STATUS	    rtpTaskAllCont (RTP_ID rtpId);
extern STATUS	    rtpShlSymbolsRegister (char * filePath, RTP_ID rtpId, 
					   SHL_ID shlId, void * textBase, 
					   void * database, UINT32 options);
extern STATUS	    rtpShlSymbolsUnregister (RTP_ID rtpId, SHL_ID shlId, 
					     UINT32 scope);
extern void	    rtpStatusStrGet (RTP_ID rtpId, char * rtpStatusStr);
extern void	    rtpOptionsStrGet (RTP_ID rtpId, char * rtpOptsStr);
#ifdef	_WRS_CONFIG_OSTOOLS
extern SYMTAB_ID    rtpSymTblIdGet (RTP_ID rtpId);
#endif	/* _WRS_CONFIG_OSTOOLS */
extern STATUS       rtpTaskEach (RTP_ID rtpId,
                                 BOOL (*routine) (RTP_ID rtpId, TASK_ID taskId,
                                                  _Vx_usr_arg_t arg),
                                 _Vx_usr_arg_t routineArg,
                                 TASK_ID * pLastTask);
#ifdef __cplusplus
}
#endif

#endif	/* _ASMLANGUAGE */

#endif	/* __INCrtpUtilLibPh */
