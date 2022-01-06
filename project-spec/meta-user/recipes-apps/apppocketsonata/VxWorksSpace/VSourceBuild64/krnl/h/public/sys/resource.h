/* resource.h - process resource access header file */

/* Copyright 2004, 2010 Wind River Systems, Inc. */

/*
modification history
--------------------
28apr10,pad  Moved extern C statement after include statements.
23sep04,yvp  written.
*/

#ifndef __INCresourceh
#define __INCresourceh

/* includes */

#include <types/vxTypesOld.h>

#ifdef __cplusplus
extern "C" {
#endif

    /* defines */

#define P_PID           0

/* Resource limits */

#define RLIMIT_CPU      0               /* cpu time in seconds */
#define RLIMIT_FSIZE    1               /* maximum file size */
#define RLIMIT_DATA     2               /* data size */
#define RLIMIT_STACK    3               /* stack size */
#define RLIMIT_CORE     4               
#define RLIMIT_RSS      5               
#define RLIMIT_MEMLOCK  6               
#define RLIMIT_NPROC    7               /* number of processes */
#define RLIMIT_NOFILE   8               /* number of open files */
#define RLIMIT_OFILE    RLIMIT_NOFILE   /* compat */
 
#define RLIM_NLIMITS    9               /* number of resource limits */
        
#define RLIM_INFINITY   (((UINT64)1 << 63) - 1)
        
struct rlimit {
        size_t  rlim_cur;               /* current (soft) limit */
        size_t  rlim_max;               /* maximum value for rlim_cur */
};

#ifdef __cplusplus
}
#endif

#endif /* __INCresourceh */
