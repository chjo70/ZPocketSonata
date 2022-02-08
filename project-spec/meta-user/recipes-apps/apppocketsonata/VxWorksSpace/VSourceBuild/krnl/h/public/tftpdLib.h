/* tftpdLib.h - vxWorks Trival File Transfer protocol header file */

/*
 * Copyright (c) 1992-2006 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
02l,09jan12,h_x  Move extern "C" after last header file include.
02k,27dec06,kch  Removed references to the obsolete coreip virtual stack.
02j,28may04,niq  Merging from base6 label POST_ITER5_FRZ16_REBASE (ver
                 /main/vdt/base6_itn5_networking-int/1)
02i,15mar04,rp   merged from orion
02h,20nov03,niq  Remove copyright_wrs.h file inclusion
02g,04nov03,rlm  Ran batch header path update for header re-org.
02f,03nov03,rlm  Removed wrn/coreip/ prefix from #includes for header re-org.
02e,24oct03,cdw  update include statements post header re-org.
02d,21apr03,ppp  vwModNum.h should be picked up from target/h
02c,11feb02,hgo  modifications for IPv6
02b,22sep92,rrr  added support for c++
02a,04jul92,jcf  cleaned up.
01b,26may92,rrr  the tree shuffle
		  -changed includes to have absolute path from h/
01a,06Feb92,jmm  written.
*/

#ifndef __INCtftpdLibh
#define __INCtftpdLibh

#include <lstLib.h>
#include <ioLib.h>
#include <netinet/in.h>
#include <tftpLib.h>
#include <cfgDefs.h>
#include <vwModNum.h>

#ifdef __cplusplus
extern "C" {
#endif 

typedef struct tftpd_dir
    {
    NODE	node;
    char	dirName [MAX_FILENAME_LENGTH];
    } TFTPD_DIR;



typedef struct tftpd_config_params {
    CFG_DATA_HDR        cfgh;

    int                 cfg_tftpdTaskStackSize;       /* stack size for the tftpdTask */
    BOOL                cfg_tftpdNoControl;           /* TRUE if no access control required */
    int                 cfg_tftpdMaxConnections;      /* max concurrent connections */
    char *              cfg_tftpdDirectoryNames;      /* TFTP server directories */
    } TFTPD_CONFIG_PARAMS;

#if defined(__STDC__) || defined(__cplusplus)

extern STATUS 	tftpdInstInit (void *noparams);
extern STATUS 	tftpdInit (int stackSize, int nDirectories,
			   char ** directoryNames, BOOL noControl,
			   int maxConnections);
extern STATUS 	tftpdDirectoryAdd (char *fileName);
extern STATUS 	tftpdDirectoryRemove (char *fileName);

#else	/* __STDC__ */

extern STATUS 	tftpdInstInit ();
extern STATUS 	tftpdInit ();
extern STATUS 	tftpdDirectoryAdd ();
extern STATUS 	tftpdDirectoryRemove ();

#endif	/* __STDC__ */

#ifdef __cplusplus
}
#endif

#endif /* __INCtftpdLibh */
