/* wvTmrLib.h - timer library header */

/*
 * Copyright 1993,2006,2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01c,08sep10,tcr  Provide timestamp for Cafe
01c,15nov10,tcr  Allow Cafe to use timestamp
01b,28jun06,tcr  add POSIX trace support
01a,10dec93,smb  written.
*/

#ifndef __INCwvtmrlibh
#define __INCwvtmrlibh

#include <vxWorks.h>
#include <time.h>

/* typedefs */

typedef unsigned int             (*UINTFUNCPTR) ();

#ifdef __cplusplus
extern "C" {
#endif

#if defined(__STDC__) || defined(__cplusplus)

/* Description of each timestamp type: WV, TRACE, and CAFE */

typedef struct ts_desc
    {
    /* These functions are for clients to use */

    unsigned int	(*ts)(void);
    unsigned int	(*tsLock)(void);
    STATUS		(*enable)(void);
    STATUS		(*disable)(void);
    unsigned int	(*period)(void);
    unsigned int	(*frequency)(void);
    STATUS		(*connect)(void (*handler)(_Vx_usr_arg_t), _Vx_usr_arg_t);

    /* These are for the timetamp multiplexing */

    STATUS		(*source_enable)(void);
    STATUS		(*source_disable)(void);
    STATUS		(*source_connect)(void (*handler)(_Vx_usr_arg_t),
					  _Vx_usr_arg_t);
    BOOL		enabled;
    void		(*local_handler)(_Vx_usr_arg_t);
    void		(*client_handler)(_Vx_usr_arg_t);
    BOOL		useWd;
    volatile unsigned long long		lastRollover0;
    volatile unsigned long long 	lastRollover1;
    volatile unsigned int		lastTimestamp;
    } TS_DESC;


void wvTmrRegister (UINTFUNCPTR wvTmrRtn, UINTFUNCPTR wvTmrLockRtn,
		    FUNCPTR wvTmrEnable, FUNCPTR wvTmrDisable,
		    FUNCPTR wvTmrConnect, UINTFUNCPTR wvTmrPeriod,
		    UINTFUNCPTR wvTmrFreq);

void traceTmrRegister (UINTFUNCPTR traceTmrRtn, FUNCPTR traceTmrEnable,
		       FUNCPTR traceTmrDisable, FUNCPTR traceTmrConnect,
		       UINTFUNCPTR traceTmrPeriod, UINTFUNCPTR traceTmrFreq);

TS_DESC * cafeTmrRegister (UINTFUNCPTR tmrRtn, UINTFUNCPTR tmrLockRtn,
			   FUNCPTR tmrEnable, FUNCPTR tmrDisable,
			   FUNCPTR tmrConnect, UINTFUNCPTR tmrPeriod,
			   UINTFUNCPTR tmrFreq);

STATUS wvTmrTimestamp64Get (TS_DESC * ts, unsigned long long * result);

STATUS wvTmrEnable (TS_DESC * ts);
STATUS wvTmrDisable (TS_DESC * ts);

STATUS wvTmrFrequency64Get (TS_DESC * ts, unsigned long long * result);

STATUS wvTmrTimestamp64ToTime (UINT64 ticks, struct ts_desc * ts_desc,
			       struct timespec * now);

void traceTmrMuxEnable (void);
void traceTmrMuxDisable (void);
STATUS traceTmrResolutionGet (struct timespec * pTimestamp);

STATUS traceTimestampGet (struct timespec * pTimestamp);


#else   /* __STDC__ */

void wvTmrRegister ();
void traceTmrRegister ();
void traceTmrResolutionGet ();
void traceTimestampGet ();

#endif  /* __STDC__ */

#ifdef __cplusplus
}
#endif

#endif /* __INCwvtmrlibh*/

