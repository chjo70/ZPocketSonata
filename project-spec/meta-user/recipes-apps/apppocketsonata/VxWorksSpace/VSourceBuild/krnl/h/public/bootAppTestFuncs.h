/* bootAppTestFuncs.h - Bootrom Application Test Function Library */

/* 
*  Copyright (c) 2006 Wind River Systems, Inc.
* 
* The right to copy, distribute, modify or otherwise make use
* of this software may be licensed only pursuant to the terms
* of an applicable Wind River license agreement.
*/

/*
modification history
--------------------
01a,23aug06,jmt  written
*/

/*
DESCRIPTION
This module provides the vxWorks Bootrom Application test functions.

To use these functions to run a test on the bootApp, do the following:
    /@ Setup for testing @/
    if (bootAppTestSetup () == ERROR)
        {
        vxTestMsg(V_ABORT, "bootAppTestSetup call returned ERROR.");
        return VXTEST_ABORT;
        }

    /@ for each command tested @/
    bootAppTestOutputClear();
    bootAppTestInputSend("Command");
    char * output = bootAppTestOutputGet();
    /@ check the output @/

    /@ Cleanup after testing @/
    bootAppTestCleanup ();
     
INCLUDE FILES: 
*/ 

#ifndef INCbootAppTestFuncsh
#define INCbootAppTestFuncsh

/* defines */

#define BOOT_APP_TEST_OUTPUT_SIZE   (10240)

/* typedefs */

/* global declarations */

STATUS bootAppTestSetup ();
STATUS bootAppTestCleanup ();
char * bootAppTestOutputGet ();
void bootAppTestOutputClear ();
void bootAppTestInputSend ( char * input );


#endif /* INCbootAppTestFuncsh */

