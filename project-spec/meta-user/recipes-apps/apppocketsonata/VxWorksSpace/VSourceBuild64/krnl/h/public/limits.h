/* limits.h - limits header file */

/*
 * Copyright (c) 1992-2005, 2009-2013, 2015-2016 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
05apr16,dlk  Correct comment: PATH_MAX is the maximum pathname length
             _including_ EOS.
07oct15,lau  Corrected the value of LLONG_MIN (V7COR-3575)
27sep13,h_k  added IOV_MAX definition.
13jan12,pad  Set SSIZE_MAX appropriately depending on the data model
             (defect 315132).
19dec11,jpb  Defect 00145128.  Added SEM_VALUE_MAX and SEM_NSEMS_MAX.
             Increased value of SEM_VALUE_MAX from 100 to 32767 and
             SEM_NSEMS_MAX to 256.
30mar10,pad  Moved declaration of extern C block for C++ after the
             inclusion of header files.
05mar09,zly  remove PIPE_BUF(WIND00088829)
24oct05,md   changed PATH_MAX count to include null terminator
02aug05,kk   added DELAYTIMER_MAX
04jul05,hya  Added more macros.
01mar05,gls  added _POSIX macros definitins from time.h (SPR #105358)
05may04,pad  set NGROUPS_MAX and SSIZE_MAX to, respectively,
             _POSIX_NGROUPS_MAX and _POSIX_SSIZE_MAX (SPR 94100).
07dec01,sn   use toolchain specific limits.h
01may94,kdl added missing mod hist for 01f.
06dec93,dvs  added POSIX AIO defines.
24sep92,smb  removed POSIX ifdef.
22sep92,rrr  added support for c++
04jul92,jcf  cleaned up.
03jul92,smb  merged ANSI limits
29jul91,rrr  written.
*/

#ifndef __INClimitsh
#define __INClimitsh

#include <types/vxANSI.h>

/* include the toolchain's notion of limits.h */

#ifndef TOOL_FAMILY
#   define TOOL_FAMILY gnu
#endif

#define _TOOL_HDR_STRINGIFY(x)  #x
#define _TOOL_HDR(tc, file) _TOOL_HDR_STRINGIFY(tool/tc/file)
#define _TOOL_HEADER(file) _TOOL_HDR(TOOL_FAMILY,file)

#include _TOOL_HEADER(limits.h)

#ifdef __cplusplus
extern "C" {
#endif

#define NGROUPS_MAX	_POSIX_NGROUPS_MAX		/* POSIX extensions */
#define LLONG_MIN       (-9223372036854775807LL-1LL)
#define LLONG_MAX       +9223372036854775807LL
#define ULLONG_MAX      18446744073709551615ULL
#ifndef _WRS_CONFIG_LP64
#define SSIZE_MAX       INT_MAX         /* max value for 32-bit ssize_t */
#else
#define SSIZE_MAX       LONG_MAX	/* max value for 64-bit ssize_t */
#endif /* _WRS_CONFIG_LP64 */
#define DATAKEYS_MAX		_PARM_DATAKEYS_MAX
#define AIO_LISTIO_MAX		10	/* needs _PARM in types/vxParams.h */
#define AIO_PRIO_DELTA_MAX	254	/* needs _PARM in types/vxParams.h */

#define _POSIX_AIO_LISTIO_MAX	2
#define _POSIX_AIO_MAX		1
#define _POSIX_ARG_MAX		4096
#define _POSIX_CHILD_MAX	6
#define	_POSIX_CLOCKRES_MIN	20
#define _POSIX_DATAKEYS_MAX     16
#define	_POSIX_DELAYTIMER_MAX	32
#define _POSIX_LINK_MAX		8
#define _POSIX_MAX_CANON	255
#define _POSIX_MAX_INPUT	255
#define _POSIX_NAME_MAX		14
#define _POSIX_NGROUPS_MAX	0
#define _POSIX_OPEN_MAX		16
#define _POSIX_PATH_MAX		256
#define _POSIX_PIPE_BUF		512
#define _POSIX_SEM_NSEMS_MAX    256
#define _POSIX_SEM_VALUE_MAX	32767
#define _POSIX_SSIZE_MAX	32767
#define _POSIX_STREAM_MAX	8
#define	_POSIX_TIMER_MAX	32
#define _POSIX_TZNAME_MAX	3

#define FILESIZEBITS    63		/* max bits to represent file size */
#define NAME_MAX        _PARM_NAME_MAX	/* max filename length excluding EOS */
#define PATH_MAX        _PARM_PATH_MAX	/* max pathname length including EOS */
#define SYMLINK_MAX     0		/* max symbolic link to a file */
#define	MAX_CANON	_POSIX_MAX_CANON /* max bytes in line in tty line mode */
#define	MAX_INPUT	_POSIX_MAX_INPUT /* max size of a tty char input buffer */
#define	LINK_MAX	_POSIX_LINK_MAX	 /* max # of links to a single file */
#define SEM_VALUE_MAX	_POSIX_SEM_VALUE_MAX /* maximum value to initialize a 
                                                semaphore */
#define SEM_NSEMS_MAX 	_POSIX_SEM_NSEMS_MAX /* maximum number of semaphores 
                                                 in the system */

#define	DELAYTIMER_MAX	_POSIX_DELAYTIMER_MAX	/* required by POSIX */

#define IOV_MAX		1024		/* max 1K of iov's */

#ifdef __cplusplus
}
#endif

#endif /* __INClimitsh */
