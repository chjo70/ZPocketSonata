/* bootFsLoad.h - Bootrom Application Filesystem Load Support */

/* 
*  Copyright (c) 2005, 2007-2009, 2014 Wind River Systems, Inc.
* 
* The right to copy, distribute, modify, or otherwise make use
* of this software may be licensed only pursuant to the terms
* of an applicable Wind River license agreement.
*/

/*
modification history
--------------------
14feb14,to   remove devSplit() (VXW7-1860)
16dec09,pgh  64-bit conversion
02dec08,pgh  Add prototype for bootFsLoad().
06feb07,jmt  Add default file load routine
12may05,jmt   written
*/

/*
DESCRIPTION
This module holds the vxWorks Bootrom Application Filesystem Load Support routines.

INCLUDE FILES: 
*/ 

#ifndef INCbootFsLoadh
#define INCbootFsLoadh

/* defines */

/* typedefs */

/* global function declarations */

STATUS bootFsFileLoad (char *fileName, void **pEntry);
STATUS bootFsLoad (char *, void **);

#endif /* INCbootFsLoadh */
