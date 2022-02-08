/* shellCmdP.h - private header file for shell commands */

/*
 * Copyright (c) 2009,2011, 2014 Wind River Systems, Inc.  
 *
 * The right to copy, distribute, modify or otherwise make use of this 
 * software may be licensed only pursuant to the terms of an applicable Wind 
 * River license agreement.
 */

/*
modification history
--------------------
30apr14,rlp  Used new OpenSSL configuration macro (V7COR-1070).
29jan14,pad  Added userMgtShellCmdInit() prototype (US19799).
27sep11,rlp  Added spy support to command interpreter - CQID: WIND00285819.
12may11,rlp  Added agentShellCmdInit and agentSslShellCmdInit prototypes.
01apr11,jmp  Added tipShellCmdInit() and wrloadShellCmdInit() (CQ:WIND00144662).
15sep09,jmp  Written
*/

#ifndef __INCshellCmdPh
#define __INCshellCmdPh

#ifdef __cplusplus
extern "C" {
#endif

extern	STATUS	adrSpaceShellCmdInit	(void);
extern	STATUS	agentShellCmdInit	(void);
extern	STATUS	dbgShellCmdInit		(void);
extern	STATUS	edrShellCmdInit		(void);
extern	STATUS	histShellCmdInit	(void);
extern	STATUS	memEdrRtpShellCmdInit	(void);
extern	STATUS	memEdrShellCmdInit	(void);
extern	STATUS	mmanShowShellCmdInit	(void);
extern	STATUS	moduleShellCmdInit	(void);
extern	STATUS	rtpShellCmdInit		(void);
extern	STATUS	rtpShowShellCmdInit	(void);
extern	STATUS	sdShowShellCmdInit	(void);
extern	STATUS	shellCmdInit		(void);
extern	STATUS	shlShellCmdInit		(void);
extern	STATUS	spyShellCmdInit		(void);
extern	STATUS	symShellCmdInit		(void);
extern	STATUS	taskShellCmdInit	(void);
extern	STATUS	unloadShellCmdInit	(void);
extern	STATUS	usrFsShellCmdInit	(void);
extern	STATUS	vmShowShellCmdInit	(void);
extern	STATUS	tipShellCmdInit		(void);
extern	STATUS	wrloadShellCmdInit	(void);

#ifdef  _WRS_CONFIG_OPENSSL
extern	STATUS	agentSslShellCmdInit	(void);
#endif  /* _WRS_CONFIG_OPENSSL */

#ifdef  _WRS_CONFIG_USER_MANAGEMENT
extern STATUS userMgtShellCmdInit (void);
#endif /* _WRS_CONFIG_USER_MANAGEMENT */

#ifdef __cplusplus
}
#endif

#endif	/* __INCshellCmdPh */
