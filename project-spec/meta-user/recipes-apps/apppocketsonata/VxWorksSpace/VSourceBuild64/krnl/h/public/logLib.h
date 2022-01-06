/* logLib.h - message logging library header */

/*
 * Copyright (c) 1990-1993, 2009-2010, 2014-2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify, or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
23jan17,cww  added const char * version of logMsg for C++ (V7COR-4711)
02apr16,dlk  Adding logMsgNoWait() and NOWAIT_LOGX and WAIT_LOGX macros
             (V7NET-535).
28apr15,h_k  removed logInit prototype. ((F2865)
31jan14,to   move assembly file protection before include statements
14apr10,jpb  Added _func_logMsg prototype.
01may09,jpb  Updated for LP64 support.
11feb93,jcf  added __PROTOTYPE_5_0 for compatibility.
22sep92,rrr  added support for c++
17jul92,gae  undid 01e.
04jul92,jcf  cleaned up.
26may92,rrr  the tree shuffle
05mar92,gae  changed logMsg() to be true variable args.
04oct91,rrr  passed through the ansification filter
              -changed VOID to void
              -changed copyright notice
19oct90,shl  changed logMsg() to use variable length argument list.
05oct90,shl  added ANSI function prototypes.
             made #endif ANSI style.
             added copyright notice.
10aug90,dnw  written
*/

#ifndef __INClogLibh
#define __INClogLibh

#ifndef	_ASMLANGUAGE
#include <vsbConfig.h>		/* for _Vx_usr_arg_t */
#include <types/vxTypesOld.h>	/* for STATUS */

#ifdef __cplusplus
extern "C" {
#endif

/* function declarations */

extern STATUS 	logFdAdd (int fd);
extern STATUS 	logFdDelete (int fd);
extern void 	logFdSet (int fd);
extern void 	logShow (void);
extern void 	logTask (void);

/* __PROTOTYPE_5_0 is used for the tools */
#ifdef	__PROTOTYPE_5_0
extern int	logMsg (char *fmt, ...);
extern int	logMsgNoWait (char *fmt, ...);
#else
extern int	logMsg (char *fmt, _Vx_usr_arg_t arg1, _Vx_usr_arg_t arg2,
	                _Vx_usr_arg_t arg3, _Vx_usr_arg_t arg4, 
	                _Vx_usr_arg_t arg5, _Vx_usr_arg_t arg6);
extern int	logMsgNoWait (char *fmt, _Vx_usr_arg_t arg1, _Vx_usr_arg_t arg2,
                              _Vx_usr_arg_t arg3, _Vx_usr_arg_t arg4, 
                              _Vx_usr_arg_t arg5, _Vx_usr_arg_t arg6);
#endif /* __PROTOTYPE_5_0 */

/* function pointer prototypes */

extern int (*_func_logMsg)(char *fmt, _Vx_usr_arg_t arg1, 
                           _Vx_usr_arg_t arg2, _Vx_usr_arg_t arg3,
                           _Vx_usr_arg_t arg4, _Vx_usr_arg_t arg5,
                           _Vx_usr_arg_t arg6);
extern int (*_func_logMsgNoWait)(char *fmt, _Vx_usr_arg_t arg1, 
                                _Vx_usr_arg_t arg2, _Vx_usr_arg_t arg3,
                                _Vx_usr_arg_t arg4, _Vx_usr_arg_t arg5,
                                _Vx_usr_arg_t arg6);

/* Non-blocking logging macros. Useful for logging from a network task. */
#define NOWAIT_LOG6(fmt, a1, a2, a3, a4, a5, a6)             \
  do { if (_func_logMsgNoWait != NULL)                       \
           (void)_func_logMsgNoWait ((fmt),                  \
                   (_Vx_usr_arg_t)(a1), (_Vx_usr_arg_t)(a2), \
                   (_Vx_usr_arg_t)(a3), (_Vx_usr_arg_t)(a4), \
                   (_Vx_usr_arg_t)(a5), (_Vx_usr_arg_t)(a6)); } while ((0))

#define NOWAIT_LOG0(fmt) NOWAIT_LOG6(fmt, 0,0,0,0,0,0)
#define NOWAIT_LOG1(fmt, a1) NOWAIT_LOG6(fmt, a1,0,0,0,0,0)
#define NOWAIT_LOG2(fmt, a1, a2) NOWAIT_LOG6(fmt, a1, a2, 0,0,0,0)
#define NOWAIT_LOG3(fmt, a1, a2, a3) NOWAIT_LOG6(fmt, a1, a2, a3, 0,0,0)
#define NOWAIT_LOG4(fmt, a1, a2, a3, a4) NOWAIT_LOG6(fmt, a1, a2, a3, a4, 0,0)
#define NOWAIT_LOG5(fmt, a1, a2, a3, a4, a5) NOWAIT_LOG6(fmt, a1, a2, a3, a4, a5, 0)

#define WAIT_LOG6(fmt, a1, a2, a3, a4, a5, a6)               \
  do { if (_func_logMsg != NULL)                             \
           (void)_func_logMsg ((fmt),                        \
                   (_Vx_usr_arg_t)(a1), (_Vx_usr_arg_t)(a2), \
                   (_Vx_usr_arg_t)(a3), (_Vx_usr_arg_t)(a4), \
                   (_Vx_usr_arg_t)(a5), (_Vx_usr_arg_t)(a6)); } while ((0))

#define WAIT_LOG0(fmt) WAIT_LOG6(fmt, 0,0,0,0,0,0)
#define WAIT_LOG1(fmt, a1) WAIT_LOG6(fmt, a1,0,0,0,0,0)
#define WAIT_LOG2(fmt, a1, a2) WAIT_LOG6(fmt, a1, a2, 0,0,0,0)
#define WAIT_LOG3(fmt, a1, a2, a3) WAIT_LOG6(fmt, a1, a2, a3, 0,0,0)
#define WAIT_LOG4(fmt, a1, a2, a3, a4) WAIT_LOG6(fmt, a1, a2, a3, a4, 0,0)
#define WAIT_LOG5(fmt, a1, a2, a3, a4, a5) WAIT_LOG6(fmt, a1, a2, a3, a4, a5, 0)


#ifdef __cplusplus
}

inline int logMsg (const char * fmt, _Vx_usr_arg_t arg1, _Vx_usr_arg_t arg2,
	           _Vx_usr_arg_t arg3, _Vx_usr_arg_t arg4, 
	           _Vx_usr_arg_t arg5, _Vx_usr_arg_t arg6)
    {
    return logMsg (const_cast<char *>(fmt), arg1, arg2, arg3, arg4, arg5, arg6);
    }
#endif

#endif /* !_ASMLANGUAGE */
#endif /* __INClogLibh */
