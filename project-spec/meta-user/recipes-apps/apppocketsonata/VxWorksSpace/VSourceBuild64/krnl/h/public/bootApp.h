/* bootApp.h - Bootrom Application Library */

/* 
 *  Copyright (c) 2005-2010,2012,2018 Wind River Systems, Inc.
 * 
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
08mar18,zl   made start delay configurable (V7PRO-4367)
06jan12,pgh  Remove USB definitions which are local to one file.
04jan12,d_c  Fix warning in bootUsbFsLoad.c
02mar10,pgh  Add ELF class to bootGoPrototype
11dec09,pgh  Remove LOCAL_MEM_LOCAL_ADRS from bootAppInit().
27feb08,jmt  Add support for BSP defined go routines
06feb07,jmt  Add bootAppPrintf to optimize size
29jan07,jmt  Add prototype for bootDevFormatHelpAdd
14nov06,jmt  Defect 81462: Need to disable MMU before booting new image
             for some BSPs
27jul05,jmt  Fix PPC compile error
28apr05,jmt  written
*/

/*
DESCRIPTION
This module provides the vxWorks Bootrom Application framework.

INCLUDE FILES: 
*/

#ifndef INCbootApph
#define INCbootApph

/* defines */

#define BOOT_CMD_MAX_LINE   255        /* default boot line size */

/* Boot Command Handler Status Return values */
#define BOOT_STATUS_COMPLETE        1    /* cmd proc complete */
#define BOOT_STATUS_CONTINUE        2    /* continue proc command */

/* Boot Loader Status Return values 
 *
 * OK - Image loaded successfully
 * ERROR - Error occurred during image loading
 * BOOT_STATUS_CONTINUE - Valid boot device not found yet
 */

/* Command String matching rules */
#define BOOT_CMD_MATCH_STRICT    0    /* full name followed by space or EOS */
#define BOOT_CMD_MATCH_LOOSE    1    /* full name, no space required */

#define DEC     FALSE   /* bootGetArg() parameters */
#define HEX     TRUE
#define OPT     TRUE

/* typedefs */

typedef int bootCmdHandlerPrototype (char * commandLine);
typedef STATUS bootLoaderPrototype (char *, void **);
typedef void bootShellPrintfPrototype(char * x, 
                                      _Vx_usr_arg_t a, 
                                      _Vx_usr_arg_t b, 
                                      _Vx_usr_arg_t c, 
                                      _Vx_usr_arg_t d, 
                                      _Vx_usr_arg_t e, 
                                      _Vx_usr_arg_t f);
typedef void bootVoidPrototype ();
typedef void bootGoPrototype (void *, int startType, int);

/* global declarations */

STATUS bootAppInit(BOOL disableMmuBeforeEntry, unsigned int startDelay); 
void bootApp();
STATUS bootLoad (char *, void **);
void executeImage (void *);
void bootAppPrintf (char * x, 
                    _Vx_usr_arg_t a, 
                    _Vx_usr_arg_t b, 
                    _Vx_usr_arg_t c, 
                    _Vx_usr_arg_t d, 
                    _Vx_usr_arg_t e, 
                    _Vx_usr_arg_t f);

STATUS bootCommandHandlerAdd(char * commandString, 
                             bootCmdHandlerPrototype * handler, 
                             int matchingRule, 
                             char * helpProto, 
                             char * helpDesc);
STATUS bootLoaderAdd(bootLoaderPrototype * loader);
STATUS bootCommandHelpAdd (char * helpProto, char * helpDesc);
STATUS bootDevFormatHelpAdd (char * helpDesc);
STATUS bootFlagHelpAdd (UINT32 flag, char * helpDesc);
STATUS bootPrintDevsFuncAdd(bootVoidPrototype * pPrintDevFunc);
void bootGoOverrideFuncAdd(void * bootOverrideGo);

/* utility functions */
void bootCmdNameSkip(FAST char **strptr, char cmdNameLength);
void bootSpaceSkip(FAST char **strptr);
STATUS bootGetArg (char **ppString, _Vx_usr_arg_t *pValue, BOOL defaultHex, 
                    BOOL optional);


#endif /* INCbootApph */

