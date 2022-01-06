/* ledLib.h - header file for ledLib.c */

/*
 * Copyright (c) 2003, 2009-2011 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify, or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
01n,07jan11,sdt  Fix support of hostShell integration into IDE (CQ:WIND00247523)
01m,29apr10,pad  Moved extern C statement after include statements.
01l,07jul09,sdt  Added support of CTRL-R and CTRL-S (req: CQ:WIND00156842)
01l,27feb09,v_r  Moved private routines to ledLibP.h
01k,10nov03,bpn  Added ledModeDefaultNameGet() and ledModeNameGet() prototypes.
01j,24oct03,bpn  Added ledCompletionSet() and ledComplete() prototypes.
01i,23sep03,bpn  Added LED_MODE_FUNCS structure and prototype of the 
                 initialization functions for the vi and emacs mode style.
01h,29aug03,bpn  Added ledHistoryLineAllocate(), ledHistoryFree(), 
                 ledHistoryAdd(), ledHistAdd() prototypes.
01g,25jun03,bpn  Added ledHistoryCreate(), ledHistoryClone() and 
                 ledHistorySet() prototypes.
01f,28mar03,bpn  Changed ledRead() declaration.
01e,20mar03,bpn  Changed ledRegister() to ledModeRegister().
01d,17mar03,lcs  Add function declarations for new led registry functionality.
01c,14mar03,bpn  Removed MAX_SHELL_LINE. Changed ledOpen() declaration.
01b,28feb03,lcs  Port to host.
01a,17feb03,bpn  Created from version "01c,26apr00,jmp" of the tor3_1 branch.
*/

#ifndef __INCledLibh
#define __INCledLibh

/* includes */

#ifndef HOST
#include <vxWorks.h>
#else
#include <host.h>
#endif

#include <lstLib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* defines */

#define STA_CHAR	0x01	/* go to the start of the line CTRL-A	*/
#define LEFT_CHAR	0x02	/* move cursor back one char CTRL-B	*/
#define	CMP_CHAR	0x04	/* symbol name & path completion CTRL-D	*/
#define SYN_CHAR	0x04	/* print synopsis of the function	*/
#define END_CHAR	0x05	/* go to the end of the line CTRL-E	*/
#define RIGHT_CHAR	0x06	/* move cursor forward one char CTRL-F	*/
#define BEL_CHAR	0x07	/* bell					*/
#define BKS_CHAR	0x08	/* Back Space char			*/
#define DEN_CHAR	0x0b	/* delete from cursor to the end CTRL-K	*/
#define RDW_CHAR	0x0c	/* redraw CTRL-L			*/
#define DOWN_CHAR	0x0e	/* Get next command in the history	*/
#define UP_CHAR		0x10	/* Get previous command in the history	*/
#define RSEARCH_CHAR	0x12	/* ^R reverse interactive search in his.*/
#define SEARCH_CHAR	0x13	/* ^S interactive search in history	*/
#define DLI_CHAR	0x15	/* delete line char CTRL-U		*/
#define HTM_CHAR	0x17	/* ^W ask Web Browser to display help	*/
#define ESC_CHAR	0x1b	/* escape				*/
#define BRK_CHAR	0x5b	/* bracket [ (escape sequence)		*/
#define RET_CHAR	'\n'	/* return				*/
#define TAB_CHAR	'\t'	/* symbol name and path completion 	*/
#define NON_CHAR	'?'	/* non-printable char. representation	*/

#ifndef	WIN32
#define DEL_KEY		0x7f	/* Del char (termcap=kD)		*/
#define INS_KEY		0x32	/* Insert key				*/
#define UP_KEY		0x41	/* Up key (termcap=ku)			*/
#define DOWN_KEY	0x42	/* Down key (termcap=kd)		*/
#define RIGHT_KEY	0x43	/* Right key (termcap=kr)		*/
#define LEFT_KEY	0x44	/* Left key (termcap=kl)		*/
#define END_KEY		0x46	/* End key				*/
#define HOME_KEY	0x48	/* Home key				*/
#else	/* WIN32 */
#define	BKS_KEY		0x08	/* Back Space				*/
#define END_KEY		0x23	/* End key				*/
#define HOME_KEY	0x24	/* Home key				*/
#define	LEFT_KEY	0x25	/* Left key				*/
#define UP_KEY		0x26	/* Up key				*/
#define	RIGHT_KEY	0x27	/* Right key				*/
#define	DOWN_KEY	0x28	/* Down key				*/
#define	DEL_KEY		0x2e	/* Del char				*/
#endif	/* WIN32 */

#ifdef HOST
#define CTRLC_CHAR	0x03	/* Ctrl-c key code (AKA end-of-text)	*/
#define REBOOT_CHAR	0x18	/* reboot character			*/
#define PAGEDOWN_KEY	0x47	/* Page Down key			*/
#define PAGEUP_KEY	0x49	/* Page Up key				*/
#define BRK_CHAR_2 	0x4f	/* O (another escape sequence (Home key)*/
#endif	/* HOST */

/* Typedefs */

typedef struct led * LED_ID;
typedef struct ctx_hist * LED_HIST;

/* Function Declarations */

extern LED_ID	ledOpen (int inFd, int outFd, int histSize);
extern STATUS 	ledClose (LED_ID ledId);
extern int 	ledRead (LED_ID ledId, char * string, UINT maxBytes);
extern void 	ledControl (LED_ID ledId, int inFd, int outFd, int histSize);

#ifdef __cplusplus
}
#endif

#endif /* __INCledLibh */
