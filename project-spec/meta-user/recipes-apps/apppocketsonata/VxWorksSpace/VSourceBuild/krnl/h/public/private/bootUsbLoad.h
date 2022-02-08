/* bootUsbLoad.h - Bootrom Application USB Load Support */

/* 
*  Copyright (c) 2010 Wind River Systems, Inc.
* 
* The right to copy, distribute, modify or otherwise make use
* of this software may be licensed only pursuant to the terms
* of an applicable Wind River license agreement.
*/

/*
modification history
--------------------
01a,01jul10,j_x   written
*/

/*
DESCRIPTION

This module holds the vxWorks Bootrom Application USB Load Support definitions.

INCLUDE FILES: 
*/ 

#ifndef INCbootUsbLoadh
#define INCbootUsbLoadh

/* USB boot prototypes */

typedef void bootUsbStopAllPrototype (int startType);


/* global function declarations */

extern bootUsbStopAllPrototype * bootUsbStopAllFunc;

#endif
