/* ftp6Lib.h -File Transfer Protocol Client library header */

/*
 * Copyright (c) 2001-2006 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement. No license to Wind River intellectual property rights
 * is granted herein. All rights not licensed by Wind River are reserved
 * by Wind River.
 */

/*
modification history
--------------------
01n,09jan12,h_x  Move extern "C" after last header file include.
01m,29sep10,h_x  Add extern FUNCPTR _func_ftpLs.
01l,12jul06,rpb  defined FTP6_FORBID_LOCAL_OVERWRITE: Fix for SPR#117576 and
                 Updated copyright.
01k,20jun05,vvv  added hostLib.h (SPR #110024)
01j,31jul04,kc   Modified FTP6_CLIENT_DATA structure to use char array for
                 hostname.
01i,20nov03,niq  Remove copyright_wrs.h file inclusion
01h,05nov03,cdw  Removal of unnecessary _KERNEL guards.
01g,04nov03,rlm  Ran batch header path update for header re-org.
01f,03nov03,rlm  Removed wrn/coreip/ prefix from #includes for header re-org.
01e,06jun02,ant  added ftp6LibInit ()
01d,14feb02,ant  added routines ftp6UserPassSet, ftp6UserPassPrint
01c,01feb02,ant  FTP6_PASSIVEMODE changed to FTP6_PASSIVEOFF. Passive
		 mode is default.
01b,15jan02,ant  sockunion moved to apps/common/sockunion.h
01a,14sep01,ant  written

*/

#ifndef __INCftp6Libh
#define __INCftp6Libh

/* includes */

#include <stdio.h>
#include <hostLib.h>
#include <netinet/sockunion.h>

#ifdef _WRS_KERNEL
#include <sys/times.h>
#else
#include <time.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* defines */

#define FTP6_AFAMILY4		0x1
#define FTP6_AFAMILY6		0x2
#define FTP6_PASSIVEOFF		0x4
#define FTP6_RESTRICTEDDATAP	0x8
#define FTP6_TRYEPSV		0x10
#define FTP6_FORBID_LOCAL_OVERWRITE         0x80

#ifndef __INCftpLibh

/* For FTP specification see RFC-765 */

/* Reply codes. */

#define FTP_PRELIM	1	/* positive preliminary */
#define FTP_COMPLETE	2	/* positive completion */
#define FTP_CONTINUE	3	/* positive intermediate */
#define FTP_TRANSIENT	4	/* transient negative completion */
#define FTP_ERROR	5	/* permanent negative completion */

#define FTP_NOACTION    550     /* requested action not taken */

/* Type codes */

#define	TYPE_A		1	/* ASCII */
#define	TYPE_E		2	/* EBCDIC */
#define	TYPE_I		3	/* image */
#define	TYPE_L		4	/* local byte size */

/* Form codes */

#define	FORM_N		1	/* non-print */
#define	FORM_T		2	/* telnet format effectors */
#define	FORM_C		3	/* carriage control (ASA) */

/* Structure codes */

#define	STRU_F		1	/* file (no record structure) */
#define	STRU_R		2	/* record structure */
#define	STRU_P		3	/* page structure */

/* Mode types */

#define	MODE_S		1	/* stream */
#define	MODE_B		2	/* block */
#define	MODE_C		3	/* compressed */

/* Record Tokens */

#define	REC_ESC		'\377'	/* Record-mode Escape */
#define	REC_EOR		'\001'	/* Record-mode End-of-Record */
#define REC_EOF		'\002'	/* Record-mode End-of-File */

/* Block Header */

#define	BLK_EOR		0x80	/* Block is End-of-Record */
#define	BLK_EOF		0x40	/* Block is End-of-File */
#define BLK_ERRORS	0x20	/* Block is suspected of containing errors */
#define	BLK_RESTART	0x10	/* Block is Restart Marker */

#define	BLK_BYTECOUNT	2	/* Bytes in this block */

#endif	/* __INCftpLibh */

/*typedef struct sockaddr_in SOCKADDR_IN;*/

/* typedefs */

typedef struct
    {
    union sockunion 	myctladdr;		/* Client address */
    union sockunion 	hisctladdr;		/* peer address */
    union sockunion 	data_addr;		/* data connection address*/
    ulong_t 		options;
    char  		hostname[MAXHOSTNAMELEN];		/* remote host name */
    int		code;				/* code of reply */
    char		pasv[BUFSIZ];		/* reply string of PASV command*/
    char 		reply_string[BUFSIZ];	/* first line of previous reply */
    } FTP6_CLIENT_DATA;

/* externals */

extern BOOL ftpErrorSupress;	/* TRUE = don't print error messages */
extern FUNCPTR     _func_ftpLs;

/* function declarations */

#if defined(__STDC__) || defined(__cplusplus)

extern STATUS 	ftp6Login (int ctrlSock, FTP6_CLIENT_DATA *pData, char *user, char *passwd,
			  char *account);
extern STATUS 	ftp6Xfer (char *host, char *user, char *passwd, char *acct,
			 char *cmd, char *dirname, char *filename,
			 int *pCtrlSock, int *pDataSock, FTP6_CLIENT_DATA **pData, ulong_t options);
extern int 	ftp6Command (int ctrlSock, FTP6_CLIENT_DATA *pData, const char *fmt, ...);
extern int 	ftp6DataConnGet (int dataSock, FTP6_CLIENT_DATA *pData);
extern int 	ftp6DataConnInit (int, FTP6_CLIENT_DATA *pData);
extern int 	ftp6Hookup (char *host, FTP6_CLIENT_DATA *pData);
extern int 	ftp6ReplyGet (int ctrlSock, FTP6_CLIENT_DATA *pData, BOOL expecteof);

extern STATUS 	ftp6Ls (char *dirName, ulong_t options);
extern STATUS 	ftp6FileGet (char *remDirName, char *locDirName, ulong_t options);
extern time_t 	ftp6RemoteModTime (int ctrlSock, FTP6_CLIENT_DATA *pData, const char *file);
extern STATUS 	ftp6FileSend (char *locDirName, char *remDirName, ulong_t options);
extern STATUS   ftp6LibInit (long timeout);

#else	/* __STDC__ */

extern STATUS 	ftp6Login ();
extern STATUS 	ftp6Xfer ();
extern int 	ftp6Command ();
extern int 	ftp6DataConnGet ();
extern int 	ftp6DataConnInit ();
extern int 	ftp6Hookup ();
extern int 	ftp6ReplyGet ();
extern STATUS 	ftp6Ls ();
extern STATUS 	ftp6FileGet ();
extern time_t 	ftp6RemoteModTime ();
extern STATUS 	ftp6FileSend ();
extern STATUS   ftp6LibInit ();

#endif	/* __STDC__ */

#ifdef __cplusplus
}
#endif

#endif /* __INCftp6Libh */
