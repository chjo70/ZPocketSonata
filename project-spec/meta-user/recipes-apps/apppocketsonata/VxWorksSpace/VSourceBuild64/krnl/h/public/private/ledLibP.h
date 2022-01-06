/* ledLibP.h - private header file for ledLib.c */

/*
 * Copyright (c) 2003-2004, 2007, 2009-2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
01r,29apr10,pad  Moved extern C statement after include statements.
01q,02mar10,jmp  Added ledRead2() (CQ:WIND00182940).
01p,30jul09,sdt  Host only - Added cmdAcqAbort field to managed CTRL+C event
01p,27feb09,v_r  Fixed issues brought up by the LP64 review process.
		 Moved private routines and structures from ledLib.h
01o,16jul07,v_r  Added ledHistResize() prototype.
01n,06jul04,bpn  Added ledHistCurrentNumGet() prototype (SPR#98947).
01m,26apr04,bpn  Added inactivity timeout feature.
01l,21jan04,bpn  Added lineBuf field to LED structure to avoid memory leaks.
01k,14nov03,bpn  Changed CTX_HIST structure.
01j,24oct03,bpn  Added ledDfltComplete() prototype. Added completionRtn
                 field to LED structure.
01i,23sep03,bpn  Moved LED_MODE_FUNCS structure to ledLib.h.
01h,29aug03,bpn  Cleaned up. Added necessary fields to HIST and CTX_HIST 
                 structures to implement historical line pre-allocation.
01g,05aug03,bpn  Updated function prototypes.
01f,08jul03,bpn  Updated ledNameComplete() API.
01e,25jun03,bpn  Changes structures in order to have on command history list
                 by interpreter.
01d,28mar03,lcs  Reworked some APIs.
01c,18mar03,lcs  Add led mode registry.
01b,14mar03,bpn  Changed LED structure.
01a,17feb03,bpn  Written from version "01c,26apr00,jmp" of ledLib.h of the 
                 tor3_1 branch.
*/

#ifndef __INCledLibPh
#define __INCledLibPh

/* Includes */

#ifdef HOST
#include <host.h>
#include <sys/time.h>
#else
#include <sys/times.h>
#endif	/* HOST */

#include <lstLib.h>
#include <ledLib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Defines */

#define	LED_BACKWARD	(-1)
#define	LED_FORWARD	1

/* Typedefs */

typedef STATUS	(* LED_COMPL_RTN) (LED_ID ledId, char * line, UINT lineSize,
				   UINT* pCursorPos, char completionChar);
typedef STATUS	(* LED_PREEMPT_RTN) (FAST char ch, char * curLine, UINT * pCurPs,
				     int * pNumber, LED_ID ledId);

typedef struct	/* HIST */
    {
    NODE    node;
    char *  line;
    UINT    lineSize;
    } HIST;

typedef struct ctx_hist
    {
    HIST *	pCurrentHist;	/* current history node */
    LIST	histList;	/* command history list */
    int		histNum;	/* current history number */
    UINT	histSize;	/* command history size */
    int		nodeNumber;	/* current historical line node number */
    } CTX_HIST;

typedef struct  /* LED_MODE_FUNCS */
    {
    NODE                node;
    const char *        ledModeName;            /* led mode name */
    int			(* ledModeReadFunc) (LED_ID ledId, char * string,
					     UINT maxBytes);
    } LED_MODE_FUNCS;

typedef struct led /* LED */
    {
    CTX_HIST *		pHistory;
    CTX_HIST *		pInitialHistory;

    /*
     * WRS_XXX the following are not needed between ledRead's
     * but are used in support routines.
     */

    char *		lineBuf;	/* line buffer pointer */
    char *		deleteBuf;	/* hold deletions from curLn */
    LED_MODE_FUNCS *	pLedModeFuncs; /* indicates led mode of this ledId */
    LED_COMPL_RTN	completionRtn;	/* completion rtn or NULL for default */
    int			inFd;		/* fd to get characters from */
    int			outFd;		/* fd to put characters to */
    UINT		deleteBufSize;
    BOOL		cmdMode;	/* insert or command mode */
    struct timeval	timeout;	/* inactivity timeout or polling period */
#ifdef HOST
    int			idle;		/* whether we're sitting in read () */
    BOOL		cmdAcqAbort;	/* TRUE when user interrupts the command
					   line acquisition using CTRL+C */
    /* the following is needed for select loop support */
    void		(* callback) (void);
    fd_set		readfds;
#endif
    } LED;

/* Function declarations */

STATUS		ledLibInit (void);
#ifdef HOST
extern LED_ID	ledHostOpen (int inFd, int outFd, int histSize,
			     struct timeval * pTimeout, 
			     void (* callback) (void));
extern int 	ledIdle (LED * ledId);
extern void 	ledModeAllUnregister ();
#endif

extern int	ledRead2 (LED_ID ledId, char * string, UINT maxBytes,
			  void (*ledReadCallBackRtn) (void * callBackArg),
			  void * callBackArg);
extern int	ledNWrite (int fd, char ch, UINT nbytes);
extern void	ledPreemptSet (LED_PREEMPT_RTN * catchFunc, 
			       LED_PREEMPT_RTN func);
extern int	ledPreempt (LED_PREEMPT_RTN * catchFunc, char ch, char * curLn,
			    UINT * curPs, int * number, LED * ledId);
extern void	ledRedraw (int outFd, char * oldLn, UINT lastPs, char * curLn,
			   UINT * curPs);
extern void	ledBeep (int outFd);
extern STATUS	ledHistResize (LED_HIST histId, int size);
extern void     ledHistAdd (LED_ID ledId, char * line);
extern LED_HIST ledHistoryCreate (UINT histSize, UINT lineSize);
extern LED_HIST ledHistoryClone (LED_HIST history);
extern void     ledHistorySet (LED_ID ledId, LED_HIST history);
extern STATUS   ledHistoryLineAllocate (LED_HIST history, UINT lineSize);
extern void     ledHistoryFree (LED_HIST history);
extern void     ledHistoryAdd (LED_HIST history, char * line);
extern int	ledHistCurrentNumGet (LED_ID ledId);
extern BOOL	ledHistNumGet (LED * ledId, int n, char * line, UINT lineSize);
extern BOOL	ledHistFind (LED * ledId, char * match, char * line, 
			     UINT lineSize);
extern STATUS	ledHistPrevGet (LED * ledId, char * line, UINT lineSize);
extern STATUS	ledHistNextGet (LED * ledId, char * line, UINT lineSize);
extern void	ledSearch (BOOL ignorePunct, BOOL endOfWord, char * curLn,
			   UINT * curPs, int dir);
extern STATUS	ledFwdFind (char ch, char * curLn, UINT * curPs, int * number,
			    LED_ID ledId);
extern STATUS	ledBwdFind (char ch, char * curLn, UINT * curPs, int * number,
			    LED_ID ledId);
extern STATUS	ledReplace (char ch, char * curLn, UINT * curPs, int * number,
			    LED_ID ledId);
extern STATUS	ledChange (char ch, char * curLn, UINT * curPs, int * number,
			   LED * ledId);
extern STATUS	ledCDelete (char ch, char * curLn, UINT * curPs, int * number,
			    LED * ledId);

extern void     ledCompletionSet (LED_ID ledId, LED_COMPL_RTN completionRtn);
extern STATUS   ledModeRegister (STATUS (* ledModeInitFunc)
					    (LED_MODE_FUNCS * pLedModeFuncs));
extern STATUS   ledModeSet (LED_ID ledId, const char * name);
extern const char *     ledModeDefaultNameGet (void);
extern const char *     ledModeNameGet (LED_ID ledId);

/* Functions call at boot time */

extern STATUS   emacsLedLibInit (LED_MODE_FUNCS * pLedModeFuncs);
extern STATUS   viLedLibInit (LED_MODE_FUNCS * pLedModeFuncs);

/* Functions available for the different LED mode modules */

extern STATUS   ledComplete (LED_ID ledId, char * line, UINT lineSize,
                             UINT * pCursorPos, char completionChar);

#ifndef HOST
extern void	ledInactivityDelaySet (LED_ID ledId, UINT delay);
extern STATUS	ledDfltComplete (LED_ID ledId, char * line, UINT lineSize, 
				 UINT * pCursorPos, char completionChar);
#endif

#ifdef __cplusplus
}
#endif

#endif /* __INCledLibPh */
