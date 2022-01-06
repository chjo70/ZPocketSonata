/* bootAppShell.h - Bootrom Application Shell Library */

/* 
 *  Copyright (c) 2005,2007 Wind River Systems, Inc.
 * 
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01b,29jan07,jmt  Add prototype for bootShellDevFormatHelpAddPrototype
01a,13jul05,jmt  written
*/

/*
DESCRIPTION
This module provides the vxWorks Bootrom Application Shell.

INCLUDE FILES: 
*/ 

#ifndef INCbootAppShellh
#define INCbootAppShellh

/* defines */

/* typedefs */

typedef char * bootShellProcPrototype (char * commandLine, int length);
typedef STATUS bootPrintHeaderPrototype (int startType);
typedef void bootShellAutobootPrototype (int timeout);
typedef void bootShellHelpAddPrototype (char * helpProto, char * helpDesc);
typedef void bootShellDevFormatHelpAddPrototype (char * helpDesc);
typedef void bootShellFlagHelpAddPrototype (UINT32 flag, char * helpDesc);
typedef void bootShellPrintDevsAddPrototype(bootVoidPrototype * pPrintDevFunc);

/* global declarations */


#endif /* INCbootAppShellh */

