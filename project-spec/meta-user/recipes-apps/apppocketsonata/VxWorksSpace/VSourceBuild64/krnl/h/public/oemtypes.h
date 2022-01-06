/* oemtypes.h - header for m2Lib Migration */

/*
 * Copyright (c) 2005, 2008, 2016 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify, or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */


/*
modification history
--------------------
17may16,chm  Port TSR defect fix forward from vxworks6.9 into vx7. (F6988)
05jun08,zhr  update for GPP 
19apr05,job  update copyright notices
*/

#ifndef _OEMTYPES_H_
#define _OEMTYPES_H_

#include <vxWorks.h>
#include <sys/types.h>

/* The sun compiler doesn't understand the `signed' keyword */

#define __TYPES_HAVE_sbits8_t_ 1
typedef char    sbits8_t;       /* signed 8 bits */
#define __TYPES_HAVE_sbits16_t_ 1
typedef short   sbits16_t;      /* signed 16 bits */
#define __TYPES_HAVE_sbits32_t_ 1
typedef int    sbits32_t;      /* signed 32 bits */

#endif
