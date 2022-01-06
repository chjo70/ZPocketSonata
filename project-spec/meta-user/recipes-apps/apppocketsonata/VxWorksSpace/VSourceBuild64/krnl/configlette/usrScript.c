/* usrScript.c - startup script module */

/*
 * Copyright 1992,1996,2001,2003,2005,2008,2010,2012-2013,2015-2016 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use of this 
 * software may be licensed only pursuant to the terms of an applicable Wind 
 * River license agreement.
 */

/*
modification history
--------------------
31oct16,mw1  Apply open retry to other devices besides USB device (V7STO-666)
13apr16,jmp  Added close of startup script file on error (V7COR-4229).
24apr15,j_x  add USB GEN2 MSC support (V7CON-146)
18oct13,j_x  remove usb GEN1 components (WIND00439658)
23feb12,rlp  CQ:WIND00335153: Added tftpLib header file.
08nov10,jmp  No longer hardcode BULK_DRIVE_NAME length (CQ:WIND00239662).
23oct08,pgh  Add retry for USB device
06sep05,bpn  Configure shell using usrShellConfigure() (SPR#106622).
09feb05,bpn  Fixed for backward compatibility (SPR#106114).
27oct03,bpn  Added conditionnal compilation on the network initialisation.
31mar03,bpn  Fixed build error.
18feb03,bpn  Adapted for the new shell component.
08nov01,cmf  fix undeclared params
22oct01,cmf  add support for tftp for SPR 34476
18nov96,dbt  ANSIfied function headers (SPR #7427.)
		 Replaced variable named new with newFdIn for C++ compatibility.
18sep92,jcf  written.
*/

/*
DESCRIPTION
This file is used to execute a startup script of VxWorks shell commands.
This file is included by usrConfig.c. The component INCLUDE_STARTUP_SCRIPT
should be included.

SEE ALSO: usrExtra.c

NOMANUAL
*/

/* includes */

#if defined(INCLUDE_NET_INIT) && defined(INCLUDE_TFTP_CLIENT)
#include <tftpLib.h>
#endif /* defined(INCLUDE_NET_INIT) && defined(INCLUDE_TFTP_CLIENT) */

/* forward declarations */

static void usrShellConfigure (void);

/******************************************************************************
*
* usrStartupScript - make shell read initial startup script file
*
* This routine reads a startup script before the VxWorks
* shell comes up interactively.
*
* NOMANUAL
*/

void usrStartupScript 
    (
    char * fileName
    )
    {
#if defined(INCLUDE_NET_INIT) && defined(INCLUDE_TFTP_CLIENT)
    BOOT_PARAMS params;
#endif
    char *	shellTaskName;
    int		fd;
    int		fdOut;
    int		fdErr;

    if (fileName == NULL || fileName[0] == EOS)
	return;	/* no valid file name */
   
#if defined(INCLUDE_NET_INIT) && defined(INCLUDE_TFTP_CLIENT)

    /* If TFTP defined, get boot params to check boot method */

    bootStringToStruct (BOOT_LINE_ADRS, &params);
    sysFlags = params.flags;

    if (sysFlags & SYSFLG_TFTP)		/* if tftp used for booting */
	{
	int		errFd;

	/* TFTP used for booting: use tftpXfer to open file */

	if (tftpXfer (params.hostName, 0, fileName, "get",\
	              "binary", &fd, &errFd) == ERROR)
    	    return;
	}

    else
#endif	/* !INCLUDE_NET_INIT || !INCLUDE_TFTP_CLIENT */

    {
    #define RETRY_COUNT 10

    int     try = 0;

    fd = ERROR;

    while ((++try <= RETRY_COUNT) && (fd == ERROR))
        {
        fd = open (fileName, O_RDONLY, 0);

        if (fd == ERROR)
            {
            /* First try? */
            if (try == 1)
                {
                printf ("Waiting for device to mount\n");
                }
            else if (try == RETRY_COUNT)
                {
                printf("\n");
                }
            else
                {
                printf(".");

                /* wait and try again */
                taskDelay(sysClkRateGet());
                }
            }
        else
            {
            if (try > 2)
                printf("\n");
            }
        }
    }

    if (fd == ERROR)
        {
        printErr ("Error: unable to open startup script '%s'.\n", fileName);
        return;
        }

    printf ("Executing startup script '%s'...\n", fileName);

    taskDelay (sysClkRateGet () / 2);

    /* Set default configuration */
    
    usrShellConfigure ();

#if SHELL_COMPATIBLE == TRUE
    /* 
     * WRS_XXX bpn - Using the standard I/O (STD_IN, STD_OUT, STD_ERR), this
     * "attaches" the target shell to the console. Any changes of the 
     * global standard I/O modified also the I/O of the shell task.
     */

    fdOut = STD_OUT;
    fdErr = STD_ERR;
#else
    /* 
     * WRS_XXX bpn - Using the file descriptor behind the standard I/O, this
     * "detach" the target shell on the console from changes of the 
     * global standard I/O.
     */

    
    fdOut = ioGlobalStdGet (STD_OUT);
    fdErr = ioGlobalStdGet (STD_ERR);

#endif /* SHELL_COMPATIBLE == TRUE */

    /* Execute script */

    if (shellGenericInit (SHELL_FIRST_CONFIG, SHELL_STACK_SIZE, NULL,
			  &shellTaskName, FALSE, FALSE,
			  fd, fdOut, fdErr) != OK)
	{
        printErr ("Error: unable to execute startup script '%s'.\n", fileName);
        close (fd);
        return;
	}

    /* Wait for shell to finish */

    do
	taskDelay (sysClkRateGet ());
    while (taskNameToId (shellTaskName) != TASK_ID_ERROR);

    close (fd);

    printf ("\nDone executing startup script '%s'.\n", fileName);
    taskDelay (sysClkRateGet () / 2);
    }
