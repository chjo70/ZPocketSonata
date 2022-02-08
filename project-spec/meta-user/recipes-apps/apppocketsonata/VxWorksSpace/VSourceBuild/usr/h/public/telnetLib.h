/* telnetLib.h - telnet library header */

/*
 * Copyright (c) 1984-2005, 2006, 2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement. No license to Wind River intellectual property rights
 * is granted herein. All rights not licensed by Wind River are reserved
 * by Wind River.
 */

/*
modification history
-------------------
09nov17,chm  merge rtnet module telnetdLib.h to telnetLib.h and fixed a rtnet
             build error defect. (V7NET-1483)
03jul16,dlk  Fix compiler warnings.  Basic 64-bit safety.
             Introduce telnet_shell_parser_ctrl function pointer type.
             Rename header as telnetdLib.h and keep it private for now.
02o,11aug06,tkf  Cleanup for IPNET integration.
02o,20jun06,jpb  Removed I960 check.
02n,20jan06,dlk  Make telnet session shutdown more graceful & reliable.
02m,05apr05,vvv  added per-session semaphore, removed parserControl
                 (SPR #106456)
02l,23aug04,rp   merged from COMP_WN_IPV6_BASE6_ITER5_TO_UNIFIED_PRE_MERGE
02k,15mar04,rp   merged from orion
02j,17feb04,zhr  Added function prototypes for telnet client
02i,05nov03,cdw  Removal of unnecessary _KERNEL guards.
02h,04nov03,rlm  Ran batch header path update for header re-org.
02g,03nov03,rlm  Removed wrn/coreip/ prefix from #includes for header re-org.
02f,10jun03,vvv  include netVersion.h
02e,15may02,elr  Added more option definitions
02d,30apr02,elr  Changed session data structure to include all allocated  
                 resources for reliable cleanup during logout
02c,14feb01,spm  merged from version 02c of tor2_0_x branch (base 02b):
                 general overhaul of telnet server (SPR #28675)
02b,22sep92,rrr  added support for c++
02a,04jul92,jcf  cleaned up.
01e,26may92,rrr  the tree shuffle
01d,04oct91,rrr  passed through the ansification filter
		  -fixed #else and #endif
		  -changed VOID to void
		  -changed copyright notice
01c,05oct90,shl  added ANSI function prototypes.
                 made #endif ANSI style.
                 added copyright notice.
01b,08aug90,shl  added INCtelnetLibh to #endif.
01a,10oct86,dnw  written
*/

#ifndef __INCtelnetLibh
#define __INCtelnetLibh

#include <lstLib.h>
#include <semLib.h>
#include <taskLib.h>

#ifdef __cplusplus
extern "C" {
#endif

#define PTY_DEVICE_NAME_MAX_LEN 128 /* The maximum string length of a pty device */
#define TELNET_BUF_SIZE     512       /* size of scratch buffer */


typedef struct
    {
    NODE        node;                /* for link-listing */
    char        ptyRemoteName[PTY_DEVICE_NAME_MAX_LEN];  /* name of the pty for this session */
    int         socket;              /* socket connection */
    int         inputFd;             /* input to command interpreter */
    int         outputFd;            /* output to command interpreter */
    int         slaveFd;             /* command interpreter side fd of pty */
    TASK_ID     outputTask;          /* Task ID to send data to socket */
    TASK_ID     inputTask;           /* Task ID to send data to socket */
    SEM_ID      startInput;          /* begin reading from socket connection */
    SEM_ID      startOutput;         /* begin writing to socket connection */
    BOOL        busyFlag;            /* Is slot in use (static tasks)? */
    int         loggedIn;            /* Has shell been started on this slot? */
    UINT32	refs;		     /* Reference flags */
    UINT32      userData;            /* A storage for application developers */
    TASK_ID     shellTaskId;         /* Task ID of the shell for session */   
    BOOL        shuttingDown;        /* Is session shutting down? */
    } TELNETD_SESSION_DATA;

typedef struct 
     {
     int    state;
#define SCTD_EMPTY 1
#define SCTD_USED  2
     int    hostFd;                  /* remote host's socket */
     BOOL   echoIsDone;              /* TRUE when echo transaction complete */
     BOOL   sgaIsDone;               /* TRUE when SGA transaction complete */
     int    hostStreamState;         /* state of host input stream */
     char   cmd;
     int    saveOpts;
     char   pBuf[TELNET_BUF_SIZE];
     } TELNETC_SESSION_DATA;

typedef struct
    {
    TELNETD_SESSION_DATA *pSession; 	/* link to session data for tasks */
    } TELNETD_TASK_DATA;

/* type of telnet parser control function pointer (like shellParserControl()) */

typedef STATUS (* telnet_shell_parser_ctrl)
                        (UINT32 remoteEvent,
                         ULONG   sessionId,
                         UINT32  slaveFd,
                         VOIDFUNCPTR logoutFunc,
                         char *  usrLogin);

/* command interpreter control operations */

#define REMOTE_START 0
#define REMOTE_STOP 1
#define REMOTE_INIT 2

/* Definitions for the TELNET protocol. */

#define	IAC	255		/* interpret as command: */
#define	DONT	254		/* you are not to use option */
#define	DO	253		/* please, you use option */
#define	WONT	252		/* I won't use option */
#define	WILL	251		/* I will use option */
#define	SB	250		/* interpret as subnegotiation */
#define	GA	249		/* you may reverse the line */
#define	EL	248		/* erase the current line */
#define	EC	247		/* erase the current character */
#define	AYT	246		/* are you there */
#define	AO	245		/* abort output--but let prog finish */
#define	IP	244		/* interrupt process--permanently */
#define	BREAK	243		/* break */
#define	DM	242		/* data mark--for connect. cleaning */
#define	NOP	241		/* nop */
#define	SE	240		/* end sub negotiation */
#define EOR     239             /* end of record (transparent mode) */

#define SYNCH	242		/* for telfunc calls */


/* telnet options - as defined by IANA */

#define TELOPT_BINARY	0	/* 8-bit data path */
#define TELOPT_ECHO	1	/* echo  RFC857 */
#define	TELOPT_RCP	2	/* prepare to reconnect */
#define	TELOPT_SGA	3	/* suppress go ahead */
#define	TELOPT_NAMS	4	/* approximate message size */
#define	TELOPT_STATUS	5	/* give status */
#define	TELOPT_TM	6	/* timing mark */
#define	TELOPT_RCTE	7	/* remote controlled transmission and echo */
#define TELOPT_NAOL 	8	/* negotiate about output line width */
#define TELOPT_NAOP 	9	/* negotiate about output page size */
#define TELOPT_NAOCRD	10	/* negotiate about CR disposition */
#define TELOPT_NAOHTS	11	/* negotiate about horizontal tabstops */
#define TELOPT_NAOHTD	12	/* negotiate about horizontal tab disposition */
#define TELOPT_NAOFFD	13	/* negotiate about formfeed disposition */
#define TELOPT_NAOVTS	14	/* negotiate about vertical tab stops */
#define TELOPT_NAOVTD	15	/* negotiate about vertical tab disposition */
#define TELOPT_NAOLFD	16	/* negotiate about output LF disposition */
#define TELOPT_XASCII	17	/* extended ascic character set */
#define	TELOPT_LOGOUT	18	/* force logout */
#define	TELOPT_BM	19	/* byte macro */
#define	TELOPT_DET	20	/* data entry terminal */
#define	TELOPT_SUPDUP	21	/* supdup protocol */
#define	TELOPT_SUPDUPOUTPUT 22	/* supdup output */
#define	TELOPT_SNDLOC	23	/* send location */
#define	TELOPT_TTYPE	24	/* terminal type */
#define	TELOPT_EOR	25	/* end or record */
#define	TELOPT_TACACS	26	/* TACACS User Identification */
#define	TELOPT_OUTPUT_MARK 27	/* Output marking */
#define	TELOPT_TLN	28	/* Terminal location number RFC933 */
#define	TELOPT_3270	29	/* Telnet 3270 regime RFC1041 */
#define TELOPT_X_3_PAD  30 
#define TELOPT_NAWS     31      /* Negotiate about window size */
#define TELOPT_TERM_SPD 32      /* Terminal speed */
#define TELOPT_RFC      33      /* Remote flow control RFC1372 */
#define TELOPT_LINEMODE 34      /* Linemode RFC1184  */
#define TELOPT_XDL      35      /* X display location */
#define TELOPT_ENVIRON  36      /* Environment RFC1408 */
#define TELOPT_AUTHENTION 37    /* authentication */
#define TELOPT_ENCRYPTION 38    /* encryption */
#define TELOPT_NEW_ENV  39      /* New environment RFC 1572 */
#define TELOPT_TN3270E  40      /* RFC1647 */
#define TELOPT_XAUTH    41      
#define TELOPT_CHARSET  42      /* RFC2066 */
#define TELOPT_RSP      43      /* Remote serial port */
#define TELOPT_CPC      44      /* Com port control RFC 2217 */
#define TELOPT_SLE      45      /* Suppress local echo */
#define TELOPT_STLS     46      /* Start TLS */
#define TELOPT_KERMIT   47      /* RFC2840 */
#define TELOPT_SEND_URL 48      
#define TELOPT_FORWARDX 49      

#define TELOPT_PRAGMA_LOGON 138
#define TELOPT_SSPI_LOGON   139
#define TELOPT_PRAGMA_HEART 140

#define TELOPT_EXOPL	255	/* extended-options-list */

/* sub-option qualifiers */

#define	TELQUAL_IS	0	/* option is... */
#define	TELQUAL_SEND	1	/* send option */

/* function declarations */

extern void 	telnetInTask (TELNETD_SESSION_DATA *pSlot);
extern void 	telnetOutTask (TELNETD_SESSION_DATA *pSlot);
extern void 	telnetd (void);
extern STATUS 	telnetdInit (int numClients, BOOL staticFlag);
extern STATUS 	telnetdStart (int port);
extern STATUS 	telnetdParserSet (telnet_shell_parser_ctrl pParserCtrlRtn);
extern void 	telnetdExit (ULONG sessionId);
extern BOOL     telnetdStaticTaskInitializationGet();
extern STATUS   telnetcInit ();
extern STATUS   telnet (char *pHostName, int port);

#ifdef __cplusplus
}
#endif

#endif /* __INCtelnetLibh */
