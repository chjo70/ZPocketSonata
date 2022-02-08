/* types.h - basic unix types header */

/*
* Copyright (c) 1987-1988, 1990-1992, 2003-2004, 2006, 2009-2012,
*  2014, 2016 Wind River Systems, Inc.
*
* The right to copy, distribute, modify or otherwise make use
* of this software may be licensed only pursuant to the terms
* of an applicable Wind River license agreement.
*/

/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * and the VxWorks Software License Agreement specify the terms and
 * conditions for redistribution.
 *
 *	@(#)types.h	7.1 (Berkeley) 6/4/86
 */

/*
modification history
--------------------
19sep16,brk  Add useconds_t 
19sep14,sas  Added header files for rwlocks (US46077).
06feb12,kk   fix comment block to avoid issues with refgen. (WIND00259043)
31oct11,mze  fix comment for docs
25jan11,pad  No longer includes non-POSIX headers (POSIX namespace
		 conformance, defect #218143).
18may10,pad  Moved extern C statement after include statements.
26jan09,pcs  Updated to add support for LP64 data model.
23jun06,tcr  add POSIX trace types
10mar06,mil  Removed duplicate include of b_pthread_t.h.
01mar06,pes  Add more base types.
16feb06,pes  Move definitions here from other headers for POSIX namespace
                 conformance.
28jan06,mil  Updated for POSIX namespace conformance.
20sep04,job  Fix for SPR#96712
09feb04,mcm  Fix for SPR:93253
16sep03,mcm  included vxTypesBase.h and vxTypesOld.h header files to 
                 make it a "complete" header file and enable its use as 
                 "sys/types.h" for the libc build.
22sep92,rrr  added support for c++
03jul92,smb  moved typedefs to types/vxTypes.h.
26may92,rrr  the tree shuffle
04oct91,rrr  passed through the ansification filter
		  -fixed #else and #endif
		  -changed copyright notice
25oct90,dnw  added test for SunOS 4.1 sys/types.h.
05oct90,dnw  added ifdef around size_t.
05oct90,shl  added copyright notice.
                 made #endif ANSI style.
21feb90,dab  added typedef for addr_t.
29mar88,gae  added necessary junk BSD4.3 style select().
29apr87,dnw  removed unnecessary junk.
		 added header and copyright.
*/

/*
 * #####################  IMPORTANT NOTE #################################
*
* This is a POSIX header file. Any changes to this file must be done with care
* to maintain the POSIX conformance. Symbols (macros, types, parameter names,
* etc.) must all follow the POSIX naming conventions (symbol names prefixed
* with one underscore followed with an upper case letter, or two underscores
* followed with a lower case letter).
*
* Ideally, NO VxWorks-native symbols should be defined here and NO VxWorks-
* native header files should be included in this header file. If it turns
* impractical to avoid using VxWorks-native elements then make sure to use the
* following exclusion logic around the offending elements:
*
* #if !defined (_POSIX_C_SOURCE) && !defined (_XOPEN_SOURCE) && \
*     !defined (_POSIX_AEP_RT_CONTROLLER_C_SOURCE)
* ...
* #endif  /@ _POSIX_xxx_SOURCE @/
 */

#ifndef __INCtypesh
#define __INCtypesh

#if !defined(_POSIX_C_SOURCE) && !defined(_XOPEN_SOURCE) && \
        !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE)

#ifndef _WRS_KERNEL
#include "types/vxCpu.h"
#include <types/vxCpuX.h>
#include "types/vxArch.h"
#endif /* _WRS_KERNEL */

#include "types/vxTypesBase.h"
#include "types/vxTypes.h"
#include "types/vxTypesOld.h"

#endif /* _POSIX_xxx_SOURCE */

/*
 * vxWorks doesn't define types for these POSIX types:
 *
 * fsblkcnt_t
 * fsfilcnt_t
 * id_t
 * pthread_barrier_t
 * pthread_barrierattr_t
 * pthread_rwlock_t
 * pthread_rwlockattr_t
 * pthread_spinlock_t
 * trace_attr_t
 * trace_event_id_t
 * trace_event_set_t
 * trace_id_t
 */

#include <base/b_pthread_attr_t.h>
#include <base/b_time_t.h>
#include <base/b_blkcnt_t.h>
#include <base/b_blksize_t.h>
#include <base/b_dev_t.h>
#include <base/b_gid_t.h>
#include <base/b_ino_t.h>
#include <base/b_mode_t.h>
#include <base/b_nlink_t.h>
#include <base/b_off_t.h>
#include <base/b_pid_t.h>
#include <base/b_size_t.h>
#include <base/b_uid_t.h>
#include <base/b_clock_t.h>
#include <base/b_key_t.h>
#include <base/b_ssize_t.h>
#include <base/b_timer_t.h>
#include <base/b_ptrdiff_t.h>
    
#ifndef _WRS_KERNEL
#include <base/b_clockid_t.h>
#include <base/b_pthread_t.h>
#include <base/b_pthread_cond_t.h>
#include <base/b_pthread_condattr_t.h>
#include <base/b_pthread_key_t.h>
#include <base/b_pthread_mutex_t.h>
#include <base/b_pthread_mutexattr_t.h>
#include <base/b_pthread_rwlockattr_t.h>
#include <base/b_pthread_rwlock_t.h>
#include <base/b_pthread_once_t.h>
#include <base/b_suseconds_t.h>
#include <base/b_trace_attr_t.h>
#include <base/b_trace_id_t.h>
#include <base/b_trace_event_id_t.h>
#include <base/b_trace_event_set_t.h>
#include <base/b_useconds_t.h>
#endif /* _WRS_KERNEL */

#ifdef __cplusplus
extern "C" {
#endif

/* This is were any symbol with C linkage should be added */

#ifdef __cplusplus
}
#endif

#endif /* __INCtypesh */
