/* erfShow.h - Event Reporting Framework Library Show routines header */

/* 
 * Copyright (c) 2005, 2010, 2017 Wind River Systems, Inc.
 * 
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
25sep17,ghs  Clean build warning
29jan10,h_k  cleaned up compiler warnings in LP64.
22jul05,jmt  Allow multiple tasks and auto unregistration
30mar05,jmt  written
*/

/*
DESCRIPTION
This module provides an Event Reporting Framework Show and debug routines.

INCLUDE FILES: 
*/ 

#ifndef INCerfShowh
#define INCerfShowh

/* defines */

/* typedefs */

/* forward declarations */

#ifdef __cplusplus
extern "C" {
#endif

void erfShow (void);
UINT16 erfMaxCategoriesGet (void);
UINT16 erfMaxTypesGet (void);
UINT16 erfDefaultQueueSizeGet (void);

#ifdef __cplusplus
}
#endif

#endif /* INCerfShowh */
