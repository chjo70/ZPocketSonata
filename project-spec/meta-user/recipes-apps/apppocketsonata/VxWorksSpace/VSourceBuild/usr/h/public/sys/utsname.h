/* utsname.h - system name header file */

/*
 * Copyright (c) 2005-2006 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01f,08mar06,pad  Fixed wrong size for endian field of utsname structure (SPR
                 #118725).
01e,06feb06,mil  Updated for POSIX namespace conformance (PN).
01d,27aug05,pad  Added processor field.
01c,24aug05,pad  Removed the maintenance field. Changed length of release and
		 version fields.
01b,22aug05,pad  Added bspmodel and endian fields.
01a,13aug05,pad  Created
*/

#ifndef __INCutsnameh
#define __INCutsnameh

#ifdef __cplusplus
extern "C" {
#endif

#define _UTSNAME_SHORT_NAME_SIZE        80
#define _UTSNAME_LONG_NAME_SIZE         256
#define _UTSNAME_NUMBER_SIZE            8

#if !defined(_POSIX_C_SOURCE) && !defined(_XOPEN_SOURCE) && \
    !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE)
#define UTSNAME_SHORT_NAME_SIZE     _UTSNAME_SHORT_NAME_SIZE
#define UTSNAME_LONG_NAME_SIZE      _UTSNAME_LONG_NAME_SIZE
#define UTSNAME_NUMBER_SIZE         _UTSNAME_NUMBER_SIZE
#endif  /* _POSIX_xxx_SOURCE */


#if defined(_POSIX_C_SOURCE) || defined(_XOPEN_SOURCE) || \
    defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE)
#undef endian
#undef kernelversion
#undef processor
#undef bsprevision
#undef builddate
#endif  /* _POSIX_xxx_SOURCE */

struct utsname
    {
    char sysname[_UTSNAME_SHORT_NAME_SIZE];	/* operating system name */
    char nodename[_UTSNAME_LONG_NAME_SIZE];	/* network node name */
    char release[_UTSNAME_SHORT_NAME_SIZE];	/* OS release level */
    char version[_UTSNAME_LONG_NAME_SIZE];	/* operating system version */
    char machine[_UTSNAME_LONG_NAME_SIZE];	/* hardware type (BSP model) */
    char endian[_UTSNAME_SHORT_NAME_SIZE];	/* architecture endianness */
    char kernelversion[_UTSNAME_SHORT_NAME_SIZE];/* VxWorks kernel version */
    char processor[_UTSNAME_SHORT_NAME_SIZE];	/* CPU type */
    char bsprevision[_UTSNAME_SHORT_NAME_SIZE];	/* VxWorks BSP revision */
    char builddate[_UTSNAME_SHORT_NAME_SIZE];	/* VxWorks kernel build date */
    };

extern int uname (struct utsname *);

#ifdef __cplusplus
    }
#endif

#endif /* __INCutsnameh */

