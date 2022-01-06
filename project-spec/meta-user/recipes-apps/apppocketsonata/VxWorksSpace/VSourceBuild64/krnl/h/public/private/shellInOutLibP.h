/* shellInOutLibP.h - private header file for the shell IO management module */

/*
 * Copyright (c) 2004-2007, 2009-2010, 2014 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
09sep14,vhe  Changed prototype of shellPrintErr and shellPrint
01h,29apr10,pad  Moved extern C statement after include statements.
01g,26feb09,v_r  Fixed issues brought up by the LP64 review process.
01f,23feb07,v_r  Implemented shell output locking (req CQ:WIND00045277).
01e,22sep04,bpn  Added some definitions from shellInOutLib.h.
01d,30jun04,bpn  Fixed SPR#97937: removed shellInOutCompatible...() functions.
01c,15apr04,bpn  Added background structure definition.
01b,26mar04,bpn  Added structure definitions for shellInOutBlockingXxx()
                 functions.
01a,17feb04,bpn  Written.
*/

#ifndef __INCshellInOutLibPh
#define __INCshellInOutLibPh

/* Includes */

#include <lstLib.h>
#include <shellLib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Defines */
#ifndef HOST
#define SHELL_OUTPUT_LOCK(shellId)	(void) shellOutputLock (shellId)
#define SHELL_OUTPUT_UNLOCK(shellId)	(void) shellOutputUnlock (shellId)
#else /* !HOST */
#define SHELL_OUTPUT_LOCK(shellId)
#define SHELL_OUTPUT_UNLOCK(shellId)
#endif /* HOST */

/* Typedefs */

enum ioType
    {
    SHELL_IO_REDIR = 1,
    SHELL_IO_BLOCKING,
    SHELL_IO_BACKGROUND
    };

struct redirection
    {
    BOOL	isRedirected;	/* TRUE if redirected */
    int		curInFd;	/* input before redirection */
    int		curOutFd;	/* output before redirection */
    int		curErrFd;	/* error before redirection */
    int		inFd;		/* input for redirection */
    int		outFd;		/* output for redirection */
    int		errFd;		/* error for redirection */
#ifdef HOST
    int		haveTerminal;	/* for host shell */
#endif	
    };

struct blocking
    {
    char *  name;
    void *  data;
    SEM_ID  stateMutexId;
    SEM_ID  structMutexId;
    int	    masterFd;
    int	    slaveFd;
    BOOL    isBlocked;
    };

struct background
    {
    char *  name;
#ifdef HOST
    char *  masterFilename;
    char *  slaveFilename;
#endif
    int	    masterFd;
    int	    slaveFd;
    };

union ioData
    {
    struct blocking	blocking;
    struct redirection	redirection;
    struct background 	background;
    };

typedef struct shell_io_fd_node
    {
    NODE	    node;
    enum ioType	    type;
    union ioData    data;
    } SHELL_IO_FD_NODE;

extern STATUS	shellInOutInputHookSet (SHELL_ID shellId);
extern STATUS	shellInOutInputHookUnset (SHELL_ID shellId);
extern BOOL	shellInOutInputUniqueCheck (int shellInputFd);

extern STATUS	shellOutputLock (SHELL_ID shellId);
extern STATUS	shellOutputUnlock (SHELL_ID shellId);

/* WRS_XXX bpn - define this function here because they are used by edrStub.c */

extern void 	shellPrint (SHELL_ID shellId, const char * fmt, ...);
extern void	shellPrintErr (SHELL_ID shellId, const char * fmt, ...);

/* WRS_XXX bpn - define this function here because they are used by IMPORTal files */

extern void	shellInOutUse (SHELL_ID shellId);

#ifdef __cplusplus
}
#endif

#endif /* __INCshellInOutLibPh */
