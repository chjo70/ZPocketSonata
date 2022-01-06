/* unistd.h - RTP POSIX standard symbolic constants and types header file */

/*
 * Copyright (c) 1991-1994, 2000-2001, 2003-2007, 2010-2017
 * Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
05jan17,mcm  Defined mulitple-definition macro for intptr_t
06jul16,dlk  _dup() system call now takes a second argument (startFd).
13jun16,ajt  Removed the const declaration on environ (V7COR-3617)
14apr16,dlk  Rename dup, dup2, unlink, link, rename, fpathconf, pathconf,
             and access system calls for user mode I/O system (F6848).
20feb15,jpb  Removed comment on SC_BARRIERS not being supported (V7COR-2159)
08oct14,pad  Applied same changes as for V7SEC84 to _seteuid() and _setegid().
01oct14,jpb  V7SEC84: _setuid and _setgid need to have ints as parameters
16sep14,pad  Added getgroups(), getlogin() and getlogin_r() (US44416)
26aug14,pad  Added seteuid(), geteuid(), setegid() and getegid() (US44512).
04jul14,pad  Added setuid(), getuid(), setgid() and getgid() (US40207).
14may14,h_k  added pipe2() and _pipe(). (US35006)
14oct13,mcm  Made environ 'const char *'
13jun11,mcm  Fix for WIND00264593 - preventing multiple definition of
             intptr_t.
12oct11,jpb  Include b_swab.h for definition of swab().
29jul10,pad  Moved extern C statement after include statements.
13jan10,pad  Added inclusion of vsbConfig.h
08jan10,mcm  Fixing intptr_t definition for ILP32.
06jan10,mcm  Fixing the definition for intptr_t.
16aug07,jlk  WIND00100511. Fixed prototype of pipe() for POSIX
05oct06,md   add declaration for pipe(), WIND00058691
29jul06,jln  support _SC_THREAD_SORADIC_SERVER
12jun06,pcm  made pthread cancellation point modifications
18jun06,pcm  added _SC_POSIX_26_VERSION
30mar06,jlk  SPR 119715. Fixed prototype of getcwd()
05mar06,mil  Added the NULL macro.  Moved optreset and environ into
             conditional block for non-POSIX use.
01mar06,pes  Move typedefs out to base type files.
17feb06,pes  Move suseconds_t typedef. Move pid_t typedef, also
             change type from unsigned short to int, per POSIX
             mandate.
10feb06,mcm  Fixing type of suseconds_t - should be signed.
30jan06,mil  Collected feature macros and moved into sys/unistd.h.
             Updated for POSIX namespace conformance.
32jan06,md   Adjust POSIX parameters
11jan06,pad  Added confstr()'s prototype and symbolic constants.
21dec05,pad  Turned on _POSIX_THREAD_SPORADIC_SERVER option.
09dec05,pad  Changed supported state for several POSIX "options" required
             by the PSE52 profile.
28nov05,pad  Added macros for all the _SC_ constants, as per POSIX.1.
             Changed supported state for POSIX Trace options.
10nov05,zl   enabled memory management options.
04nov05,kk   enabled various PSE52 features
07sep05,pad  Applied POSIX prototypes for read() and write() (SPR 112005).
24aug05,pad  Added POSIX prototypes for dup() and dup2().
24aug05,mcm  Removing check for macros _TYPE_ssize_t etc. that are
             actually undefined after use.
23aug05,mcm  Adding missing type definitions, changed return type of
             getOptServ from STATUS to int.
19aug05,pad  Removed inclusion of vxWorks.h which brings conflicting types
             for POSIX. Made some routine prototypes POSIX.
19aug05,kk   updated prototypes for kernel APIs to be POSIX conformant
14aug05,pad  Added STDxxx_FILENO macros.
30jul05,pad  Now use POSIX prototype for _exit() (SPR #110875). Fixed some
             macro definitions.
15jul05,pad  Added symbolic constants required by sysconf().
04jul05,hya  Added more _POSIX macros.
02jun05,pad  Added more standard symbolic constants.
18apr05,pcm  moved _PC_xxx macros for pathconf() from hrFsLib.h to here
18apr05,hya  Added file system posix prototypes.
17mar05,dlk  Make 'place' a member of the GETOPT type.
25feb05,niq  Added definitions for reentrant version of getopt
06oct04,pad  Added declaration of the environ array for the user side.
01oct04,yvp  Change lseek args to use off_t (for Posix).
13sep04,yvp  Added prorotype for _exit().
09jun04,kk   added getpid() & getppid() prototypes SPR#98109
29mar04,job  Added getopt prototype. Removed non-STDC function prototypes
08dec03,dat  adding const to unlink and chdir
20jul00,jgn  add POSIX version information + removed old style prototypes
24sep01,jkf  added const to rmdir()
19aug94,ism  added getcwd() prototypes (SPR #3536)
12nov93,dvs  added prototype for ftruncate.
08feb93,smb  changed int to size_t in protype for read() and write()
22sep92,rrr  added support for c++
18sep92,smb  added the rmdir prototype.
04jul92,jcf  cleaned up.
26may92,rrr  the tree shuffle
05dec91,rrr  added SEEK_ macros (was in ioLib.h)
19nov91,rrr  written.
*/

#ifndef __INCunistdh
#define __INCunistdh

/* Definition of macros derived from VSB options */

#include <vsbConfig.h>	/* needed for _WRS_CONFIG_LP64 */

/* POSIX defines */

#include <sys/unistd.h>		/* POSIX version and features */

#ifdef __cplusplus
extern "C" {
#endif

/* Constants for sysconf() */

typedef enum {
    _SC_AIO_LISTIO_MAX,
#define _SC_AIO_LISTIO_MAX	_SC_AIO_LISTIO_MAX
    _SC_AIO_MAX,
#define _SC_AIO_MAX		_SC_AIO_MAX
    _SC_AIO_PRIO_DELTA_MAX,
#define _SC_AIO_PRIO_DELTA_MAX	_SC_AIO_PRIO_DELTA_MAX
    _SC_ADVISORY_INFO,		/* the Advisory Information is not supported */
#define _SC_ADVISORY_INFO	_SC_ADVISORY_INFO
    _SC_ARG_MAX,
#define _SC_ARG_MAX		_SC_ARG_MAX
    _SC_ASYNCHRONOUS_IO,
#define _SC_ASYNCHRONOUS_IO	_SC_ASYNCHRONOUS_IO
    _SC_ATEXIT_MAX,
#define _SC_ATEXIT_MAX		_SC_ATEXIT_MAX
    _SC_BARRIERS,
#define _SC_BARRIERS		_SC_BARRIERS
    _SC_BC_BASE_MAX,		/* the 'bc' utility is not supported */
#define _SC_BC_BASE_MAX		_SC_BC_BASE_MAX
    _SC_BC_DIM_MAX,		/* the 'bc' utility is not supported */
#define _SC_BC_DIM_MAX		_SC_BC_DIM_MAX
    _SC_BC_SCALE_MAX,		/* the 'bc' utility is not supported */
#define _SC_BC_SCALE_MAX	_SC_BC_SCALE_MAX
    _SC_BC_STRING_MAX,		/* the 'bc' utility is not supported */
#define _SC_BC_STRING_MAX	_SC_BC_STRING_MAX
    _SC_CHILD_MAX,
#define _SC_CHILD_MAX		_SC_CHILD_MAX
    _SC_CLK_TCK,
#define _SC_CLK_TCK		_SC_CLK_TCK
    _SC_CLOCK_SELECTION,
#define _SC_CLOCK_SELECTION	_SC_CLOCK_SELECTION
    _SC_COLL_WEIGHTS_MAX,
#define _SC_COLL_WEIGHTS_MAX	_SC_COLL_WEIGHTS_MAX
    _SC_CPUTIME,		/* Process CPU-Time Clocks unsupported */
#define _SC_CPUTIME		_SC_CPUTIME
    _SC_DELAYTIMER_MAX,
#define _SC_DELAYTIMER_MAX	_SC_DELAYTIMER_MAX
    _SC_EXPR_NEST_MAX,		/* the 'expr' utility is not supported */
#define _SC_EXPR_NEST_MAX	_SC_EXPR_NEST_MAX
    _SC_FSYNC,
#define _SC_FSYNC		_SC_FSYNC
    _SC_GETGR_R_SIZE_MAX,	/* POSIX System Database unsupported */
#define _SC_GETGR_R_SIZE_MAX	_SC_GETGR_R_SIZE_MAX
    _SC_GETPW_R_SIZE_MAX,	/* POSIX System Database unsupported */
#define _SC_GETPW_R_SIZE_MAX	_SC_GETPW_R_SIZE_MAX
    _SC_HOST_NAME_MAX,
#define _SC_HOST_NAME_MAX	_SC_HOST_NAME_MAX
    _SC_IOV_MAX,
#define _SC_IOV_MAX		_SC_IOV_MAX
    _SC_IPV6,			/* POSIX IPV6 is not a supported feature */
#define _SC_IPV6		_SC_IPV6
    _SC_JOB_CONTROL,		/* POSIX Job Control is not supported */
#define _SC_JOB_CONTROL		_SC_JOB_CONTROL
    _SC_LINE_MAX,		/* unsupported */
#define _SC_LINE_MAX		_SC_LINE_MAX
    _SC_LOGIN_NAME_MAX,
#define _SC_LOGIN_NAME_MAX	_SC_LOGIN_NAME_MAX
    _SC_MAPPED_FILES,		/* POSIX Mapped File is not supported */
#define _SC_MAPPED_FILES	_SC_MAPPED_FILES
    _SC_MEMLOCK,
#define _SC_MEMLOCK		_SC_MEMLOCK
    _SC_MEMLOCK_RANGE,
#define _SC_MEMLOCK_RANGE	_SC_MEMLOCK_RANGE
    _SC_MEMORY_PROTECTION,
#define _SC_MEMORY_PROTECTION	_SC_MEMORY_PROTECTION
    _SC_MESSAGE_PASSING,
#define _SC_MESSAGE_PASSING	_SC_MESSAGE_PASSING
    _SC_MONOTONIC_CLOCK,
#define _SC_MONOTONIC_CLOCK	_SC_MONOTONIC_CLOCK
    _SC_MQ_OPEN_MAX,
#define _SC_MQ_OPEN_MAX		_SC_MQ_OPEN_MAX
    _SC_MQ_PRIO_MAX,
#define _SC_MQ_PRIO_MAX		_SC_MQ_PRIO_MAX
    _SC_NGROUPS_MAX,
#define _SC_NGROUPS_MAX		_SC_NGROUPS_MAX
    _SC_OPEN_MAX,
#define _SC_OPEN_MAX		_SC_OPEN_MAX
    _SC_PAGE_SIZE,
#define _SC_PAGE_SIZE		_SC_PAGE_SIZE
    _SC_PAGESIZE,
#define _SC_PAGESIZE		_SC_PAGESIZE
    _SC_PRIORITIZED_IO,		/* POSIX Prioritized IO is not supported */
#define _SC_PRIORITIZED_IO	_SC_PRIORITIZED_IO
    _SC_PRIORITY_SCHEDULING,	/* Process scheduling is not supported */
#define _SC_PRIORITY_SCHEDULING	_SC_PRIORITY_SCHEDULING
    _SC_RAW_SOCKETS,		/* POSIX Raw Sockets is not supported */
#define _SC_RAW_SOCKETS		_SC_RAW_SOCKETS
    _SC_RE_DUP_MAX,		/* POSIX Regexp is not a supported feature */
#define _SC_RE_DUP_MAX		_SC_RE_DUP_MAX
    _SC_READER_WRITER_LOCKS,
#define _SC_READER_WRITER_LOCKS	_SC_READER_WRITER_LOCKS
    _SC_REALTIME_SIGNALS,
#define _SC_REALTIME_SIGNALS	_SC_REALTIME_SIGNALS
    _SC_REGEXP,			/* POSIX Regexp is not a supported feature */
#define _SC_REGEXP		_SC_REGEXP
    _SC_RTSIG_MAX,
#define _SC_RTSIG_MAX		_SC_RTSIG_MAX
    _SC_SAVED_IDS,		/* POSIX Saved IDs is not a supported feature */
#define _SC_SAVED_IDS		_SC_SAVED_IDS
    _SC_SEM_NSEMS_MAX,
#define _SC_SEM_NSEMS_MAX	_SC_SEM_NSEMS_MAX
    _SC_SEM_VALUE_MAX,
#define _SC_SEM_VALUE_MAX	_SC_SEM_VALUE_MAX
    _SC_SEMAPHORES,
#define _SC_SEMAPHORES		_SC_SEMAPHORES
    _SC_SHARED_MEMORY_OBJECTS,
#define _SC_SHARED_MEMORY_OBJECTS	_SC_SHARED_MEMORY_OBJECTS
    _SC_SHELL,			/* POSIX Shell is not a supported feature */
#define _SC_SHELL		_SC_SHELL
    _SC_SIGQUEUE_MAX,
#define _SC_SIGQUEUE_MAX	_SC_SIGQUEUE_MAX
    _SC_SPAWN,			/* POSIX Spawn is not a supported feature */
#define _SC_SPAWN		_SC_SPAWN
    _SC_SPIN_LOCKS,		/* POSIX Spin Locks is not supported */
#define _SC_SPIN_LOCKS		_SC_SPIN_LOCKS
    _SC_SPORADIC_SERVER,	/* POSIX Sporadic Server is not supported */
#define _SC_SPORADIC_SERVER	_SC_SPORADIC_SERVER
    _SC_SS_REPL_MAX,
#define _SC_SS_REPL_MAX		_SC_SS_REPL_MAX
    _SC_STREAM_MAX,
#define _SC_STREAM_MAX		_SC_STREAM_MAX
    _SC_SYMLOOP_MAX,		/* POSIX Symbolic Links is not supported */
#define _SC_SYMLOOP_MAX		_SC_SYMLOOP_MAX
    _SC_SYNCHRONIZED_IO,
#define _SC_SYNCHRONIZED_IO	_SC_SYNCHRONIZED_IO
    _SC_THREAD_ATTR_STACKADDR,
#define _SC_THREAD_ATTR_STACKADDR	_SC_THREAD_ATTR_STACKADDR
    _SC_THREAD_ATTR_STACKSIZE,
#define _SC_THREAD_ATTR_STACKSIZE	_SC_THREAD_ATTR_STACKSIZE
    _SC_THREAD_CPUTIME,
#define _SC_THREAD_CPUTIME	_SC_THREAD_CPUTIME
    _SC_THREAD_DESTRUCTOR_ITERATIONS,
#define _SC_THREAD_DESTRUCTOR_ITERATIONS _SC_THREAD_DESTRUCTOR_ITERATIONS
    _SC_THREAD_KEYS_MAX,
#define _SC_THREAD_KEYS_MAX	_SC_THREAD_KEYS_MAX
    _SC_THREAD_PRIO_INHERIT,
#define _SC_THREAD_PRIO_INHERIT	_SC_THREAD_PRIO_INHERIT
    _SC_THREAD_PRIO_PROTECT,
#define _SC_THREAD_PRIO_PROTECT	_SC_THREAD_PRIO_PROTECT
    _SC_THREAD_PRIORITY_SCHEDULING,
#define _SC_THREAD_PRIORITY_SCHEDULING	_SC_THREAD_PRIORITY_SCHEDULING
    _SC_THREAD_PROCESS_SHARED,	/* Thread Process-Shared Protection unsupp. */
#define _SC_THREAD_PROCESS_SHARED	_SC_THREAD_PROCESS_SHARED
    _SC_THREAD_SAFE_FUNCTIONS,	/* Thread-Safe Functions is not supported */
#define _SC_THREAD_SAFE_FUNCTIONS	_SC_THREAD_SAFE_FUNCTIONS
    _SC_THREAD_SPORADIC_SERVER,
#define _SC_THREAD_SPORADIC_SERVER	_SC_THREAD_SPORADIC_SERVER
    _SC_THREAD_STACK_MIN,
#define _SC_THREAD_STACK_MIN	_SC_THREAD_STACK_MIN
    _SC_THREAD_THREADS_MAX,
#define _SC_THREAD_THREADS_MAX	_SC_THREAD_THREADS_MAX
    _SC_THREADS,
#define _SC_THREADS		_SC_THREADS
    _SC_TIMEOUTS,
#define _SC_TIMEOUTS		_SC_TIMEOUTS
    _SC_TIMER_MAX,
#define _SC_TIMER_MAX		_SC_TIMER_MAX
    _SC_TIMERS,
#define _SC_TIMERS		_SC_TIMERS
    _SC_TRACE,
#define _SC_TRACE		_SC_TRACE
    _SC_TRACE_EVENT_FILTER,
#define _SC_TRACE_EVENT_FILTER	_SC_TRACE_EVENT_FILTER
    _SC_TRACE_EVENT_NAME_MAX,
#define _SC_TRACE_EVENT_NAME_MAX	_SC_TRACE_EVENT_NAME_MAX
    _SC_TRACE_INHERIT,		/* POSIX Trace Inherit is not supported */
#define _SC_TRACE_INHERIT	_SC_TRACE_INHERIT
    _SC_TRACE_LOG,
#define _SC_TRACE_LOG		_SC_TRACE_LOG
    _SC_TRACE_NAME_MAX,
#define _SC_TRACE_NAME_MAX	_SC_TRACE_NAME_MAX
    _SC_TRACE_SYS_MAX,
#define _SC_TRACE_SYS_MAX	_SC_TRACE_SYS_MAX
    _SC_TRACE_USER_EVENT_MAX,
#define _SC_TRACE_USER_EVENT_MAX	_SC_TRACE_USER_EVENT_MAX
    _SC_TTY_NAME_MAX,
#define _SC_TTY_NAME_MAX	_SC_TTY_NAME_MAX
    _SC_TYPED_MEMORY_OBJECTS,	/* POSIX Types Memory Objects is unsupported */
#define _SC_TYPED_MEMORY_OBJECTS	_SC_TYPED_MEMORY_OBJECTS
    _SC_TZNAME_MAX,
#define _SC_TZNAME_MAX		_SC_TZNAME_MAX
    _SC_V6_ILP32_OFF32,		/* Unsupported C99 programming environment */
#define _SC_V6_ILP32_OFF32	_SC_V6_ILP32_OFF32
    _SC_V6_ILP32_OFFBIG,
#define _SC_V6_ILP32_OFFBIG	_SC_V6_ILP32_OFFBIG
    _SC_V6_LP64_OFF64,		/* Unsupported C99 programming environment */
#define _SC_V6_LP64_OFF64	_SC_V6_LP64_OFF64
    _SC_V6_LPBIG_OFFBIG,	/* Unsupported C99 programming environment */
#define _SC_V6_LPBIG_OFFBIG	_SC_V6_LPBIG_OFFBIG
    _SC_VERSION,
#define _SC_VERSION		_SC_VERSION
    _SC_XBS5_ILP32_OFF32,	/* C89 programming environment unsupported */
#define _SC_XBS5_ILP32_OFF32	_SC_XBS5_ILP32_OFF32
    _SC_XBS5_ILP32_OFFBIG,	/* C89 programming environment unsupported */
#define _SC_XBS5_ILP32_OFFBIG	_SC_XBS5_ILP32_OFFBIG
    _SC_XBS5_LP64_OFF64,	/* C89 programming environment unsupported */
#define _SC_XBS5_LP64_OFF64	_SC_XBS5_LP64_OFF64
    _SC_XBS5_LPBIG_OFFBIG,	/* C89 programming environment unsupported */
#define _SC_XBS5_LPBIG_OFFBIG	_SC_XBS5_LPBIG_OFFBIG
    _SC_XOPEN_CRYPT,		/* X/Open Encryption is not supported */
#define _SC_XOPEN_CRYPT		_SC_XOPEN_CRYPT
    _SC_XOPEN_ENH_I18N,		/* X/Open Internationalization not supported */
#define _SC_XOPEN_ENH_I18N	_SC_XOPEN_ENH_I18N
    _SC_XOPEN_LEGACY,		/* X/Open Legacy is not a supported feature */
#define _SC_XOPEN_LEGACY	_SC_XOPEN_LEGACY
    _SC_XOPEN_REALTIME,		/* X/Open Realtime is not a supported feature */
#define _SC_XOPEN_REALTIME	_SC_XOPEN_REALTIME
    _SC_XOPEN_REALTIME_THREADS,
#define _SC_XOPEN_REALTIME_THREADS	_SC_XOPEN_REALTIME_THREADS
    _SC_XOPEN_SHM,		/* X/Open Shared Memory is unsupported */
#define _SC_XOPEN_SHM		_SC_XOPEN_SHM
    _SC_XOPEN_STREAMS,		/* X/Open Streams is not a supported feature */
#define _SC_XOPEN_STREAMS	_SC_XOPEN_STREAMS
    _SC_XOPEN_UNIX,		/* X/Open XSI extension is not supported */
#define _SC_XOPEN_UNIX		_SC_XOPEN_UNIX
    _SC_XOPEN_VERSION,		/* X/Open Conformance is not supported */
#define _SC_XOPEN_VERSION	_SC_XOPEN_VERSION
    _SC_2_C_BIND,		/* C Binding is not supported */
#define _SC_2_C_BIND		_SC_2_C_BIND
    _SC_2_C_DEV,
#define _SC_2_C_DEV		_SC_2_C_DEV
    _SC_2_CHAR_TERM,		/* No terminal is supported */
#define _SC_2_CHAR_TERM		_SC_2_CHAR_TERM
    _SC_2_FORT_DEV,		/* Fortran is not supported */
#define _SC_2_FORT_DEV		_SC_2_FORT_DEV
    _SC_2_FORT_RUN,		/* Fortran is not supported */
#define _SC_2_FORT_RUN		_SC_2_FORT_RUN
    _SC_2_LOCALEDEF,		/* the 'localedef' utility is not supported */
#define _SC_2_LOCALEDEF		_SC_2_LOCALEDEF
    _SC_2_PBS,			/* Batch Environment Services unsupported */
#define _SC_2_PBS		_SC_2_PBS
    _SC_2_PBS_ACCOUNTING,	/* Batch Environment Services unsupported */
#define _SC_2_PBS_ACCOUNTING	_SC_2_PBS_ACCOUNTING
    _SC_2_PBS_CHECKPOINT,	/* Batch Environment Services unsupported */
#define _SC_2_PBS_CHECKPOINT	_SC_2_PBS_CHECKPOINT
    _SC_2_PBS_LOCATE,		/* Batch Environment Services unsupported */
#define _SC_2_PBS_LOCATE	_SC_2_PBS_LOCATE
    _SC_2_PBS_MESSAGE,		/* Batch Environment Services unsupported */
#define _SC_2_PBS_MESSAGE	_SC_2_PBS_MESSAGE
    _SC_2_PBS_TRACK,		/* Batch Environment Services unsupported */
#define _SC_2_PBS_TRACK		_SC_2_PBS_TRACK
    _SC_2_SW_DEV,
#define _SC_2_SW_DEV		_SC_2_SW_DEV
    _SC_2_UPE,			/* User Portability Utilities unsupported */
#define _SC_2_UPE		_SC_2_UPE
    _SC_2_VERSION,		/* POSIX2 Conformance is not supported */
#define _SC_2_VERSION		_SC_2_VERSION
    _SC_POSIX_26_VERSION        /* POSIX .26 supported */
#define _SC_POSIX_26_VERSION    _SC_POSIX_26_VERSION
    } _VX_SYSCONF_VALUE;


/* the NULL pointer */
#ifndef NULL
#define NULL 0
#endif

/* Execution-time symbolic constants */

#define _POSIX_ASYNC_IO		0
#define _POSIX_PRIO_IO		0
#define _POSIX_SYNC_IO		0

/* Symbolic constants for the "access" routine: */

#define R_OK	4	/* Test for Read permission */
#define W_OK	2	/* Test for Write permission */
#define X_OK	1	/* Test for eXecute permission */
#define F_OK	0	/* Test for existence of File */

/* command names for POSIX pathconf, fpathconf */

#define _PC_2_SYMLINKS		1
#define _PC_ALLOC_SIZE_MIN	2
#define _PC_ASYNC_IO		3
#define _PC_CHOWN_RESTRICTED	4
#define _PC_FILESIZEBITS	5
#define _PC_LINK_MAX		6
#define _PC_MAX_CANON		7
#define _PC_MAX_INPUT		8
#define _PC_NAME_MAX		9
#define _PC_NO_TRUNC		10
#define _PC_PATH_MAX		11
#define _PC_PIPE_BUF		12
#define _PC_PRIO_IO		13
#define _PC_REC_INCR_XFER_SIZE	14
#define _PC_REC_MAX_XFER_SIZE	15
#define _PC_REC_MIN_XFER_SIZE	16
#define _PC_REC_XFER_ALIGN	17
#define _PC_SYMLINK_MAX		18
#define _PC_SYNC_IO		19
#define _PC_VDISABLE		20

#ifndef SEEK_SET
#define SEEK_SET           0       /* absolute offset, was L_SET */
#define SEEK_CUR           1       /* relative to current offset, was L_INCR */
#define SEEK_END           2       /* relative to end of file, was L_XTND */
#endif

#define STDIN_FILENO	0	/* standard input */
#define STDOUT_FILENO	1	/* standard ouput */
#define STDERR_FILENO	2	/* standard error */

extern char *optarg;
extern int optind, opterr, optopt;

#if !defined(_POSIX_C_SOURCE) && !defined(_XOPEN_SOURCE) && \
    !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE)
extern int optreset;
extern char ** environ;

struct getopt_s
    {
    int	 opterr;       		/* if error message should be printed */
    int  optind;    		/* index into parent argv vector */
    int  optopt;		/* character checked for validity */
    int  optreset;		/* reset getopt */
    char *optarg;		/* argument associated with option */
    char *place;
    };

typedef struct getopt_s GETOPT;
typedef struct getopt_s * GETOPT_ID;
#endif  /* _POSIX_xxx_SOURCE */

#ifdef __cplusplus
}
#endif

/* typedef ssize_t */
#include <base/b_ssize_t.h>

/* typedef size_t */
#include <base/b_size_t.h>

/* typedef uid_t */
#include <base/b_uid_t.h>

/* typedef gid_t */
#include <base/b_gid_t.h>

/* typedef pid_t */
#include <base/b_pid_t.h>

/* typedef off_t */
#include <base/b_off_t.h>

/* typedef suseconds_t */
#include <base/b_suseconds_t.h>

/* swab declaration */
#include <base/b_swab.h>

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_INTPTR_T) && !defined(_INTPTR_T_DEFINED)
#define _INTPTR_T
#define _INTPTR_T_DEFINED
#ifndef _WRS_CONFIG_LP64
typedef int intptr_t;
#else
typedef long intptr_t;
#endif /* _WRS_CONFIG_LP64 */
#endif /* _INTPTR_T */

/* function declarations */

extern int		access (const char *, int);
extern int		_access (const char *, int);
extern unsigned 	alarm (unsigned);
extern int 		chdir (const char *);
extern int 		close (int);
extern size_t		confstr (int, char *, size_t);
extern int		dup (int);
extern int		dup2 (int, int);
extern int		_dup (int, int);
extern int		_dup2 (int, int);
#if !defined(_POSIX_C_SOURCE) && !defined(_XOPEN_SOURCE) && \
    !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE)
extern int		pipe (int fildes[2]);
#else
extern int		pipe (int [2]);
#endif
extern int		pipe2 (int [2], int);

extern int		_pipe (int [2], int);
extern void		_exit (int);
extern int		fdatasync (int);
extern int		_fdatasync (int);
extern long		fpathconf (int, int);
extern long		_fpathconf (int, int);
extern int		fsync (int);
extern int		_fsync (int);
extern int    		ftruncate (int, off_t);
extern char *		getcwd (char *, size_t);
extern int              getopt (int, char * const [], const char *);
#if !defined(_POSIX_C_SOURCE) && !defined(_XOPEN_SOURCE) && \
    !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE)
extern int 		getopt_r (int, char * const [], const char *,
                                  GETOPT_ID);
extern void 		getoptInit (GETOPT_ID);
extern int		getOptServ (char *, const char *,
			  	    int *, char *argvloc[], int);
#endif  /* _POSIX_xxx_SOURCE */
extern pid_t		getpid(void);
extern pid_t		getppid(void);
extern int 		isatty (int);
extern int		link (const char *, const char *);
extern int		_link (const char *, const char *);
extern off_t 		lseek (int, off_t, int);
extern long             pathconf (const char *, int);
extern long             _pathconf (const char *, int);
extern int 		pause (void);
extern int 		_pause (void);
extern ssize_t 		read (int, void *, size_t);
#if !defined(_POSIX_C_SOURCE) && !defined(_XOPEN_SOURCE) && \
    !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE)
extern int		rename (const char *, const char *);
extern int		_rename (const char *, const char *);
#endif  /* _POSIX_xxx_SOURCE */
extern int 		rmdir (const char *);
extern unsigned 	sleep (unsigned);
extern long		sysconf (int);
extern int 		unlink (const char *);
extern int 		_unlink (const char *);
extern ssize_t 		write (int, const void *, size_t);

extern int              setuid (uid_t uid);
extern uid_t            getuid (void);
extern int              setgid (gid_t gid);
extern gid_t            getgid (void);
extern int              _setuid (int uid);
extern uid_t            _getuid (void);
extern int              _setgid (int gid);
extern gid_t            _getgid (void);

extern int              seteuid (uid_t uid);
extern uid_t            geteuid (void);
extern int              setegid (gid_t gid);
extern gid_t            getegid (void);
extern int              _seteuid (int uid);
extern uid_t            _geteuid (void);
extern int              _setegid (int gid);
extern gid_t            _getegid (void);

extern int              getgroups (int, gid_t []);
extern char *           getlogin (void);
extern int              getlogin_r (char * loginName, size_t nameSz);

#ifdef __cplusplus
}
#endif

#endif /* __INCunistdh */
