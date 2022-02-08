/* wdLib.h - watchdog timer library header */

/*
 * Copyright (c) 1984-2005, 2009-2011 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
02l,18jan11,gls  added S_wdLib_INVALID_PARAMETER (WIND00196769)
02k,07jul10,pcs  change the data type of timeout from an int to _Vx_ticks_t
02j,19jan10,cww  Revert wdStart to using FUNCPTR
02i,29apr09,cww  LP64 update
02h,07oct05,yvp  Used VX_OBJ_ALIGN_SIZE to align statically instantiated
                 objects (SPR 113405).
02g,30aug05,yvp  Reworked VX_WDOG macro to undo struct workaround.
02f,08aug05,yvp  Added VX_WDOG macro for static instantiation of watchdogs.
                 Added prototype for wdInitialize().
                 Updated copyright. #include now with angle brackets.
02e,04aug05,yvp  Added prototype for create/delete library init.
02d,26jun03,dcc  removed non-ANSI prototypes
02c,14mar03,dcc  moved WDOG_ID definition to types/vxWind.h
02b,22sep92,rrr  added support for c++
02a,04jul92,jcf  cleaned up.
01h,26may92,rrr  the tree shuffle
01g,04oct91,rrr  passed through the ansification filter
		  -changed copyright notice
01f,23oct90,shl  changed wdStart()'s third parameter type to VOIDFUNCPTR.
01e,05oct90,dnw  deleted private functions.
01d,05oct90,shl  added ANSI function prototypes.
                 added copyright notice.
01c,26jun90,jcf  removed generic status codes.
01b,17apr90,jcf  subsumed into wind 2.0.
01a,21may84,dnw  written
*/

#ifndef __INCwdLibh
#define __INCwdLibh

#include <vxWorks.h>
#include <vwModNum.h>

#ifdef __cplusplus
extern "C" {
#endif

/* errno definitions */

#define S_wdLib_INVALID_PARAMETER (M_wdLib | 1)

#ifndef	_ASMLANGUAGE

/* macro used to statically declare watchdogs */

/*******************************************************************************
*
* VX_WDOG - declare storage for a watchdog
*
* This macro declares storage for a watchdog having name <name>. It only 
* generates data declarations for the watchdog. To fully instantiate the 
* watchdog and make it ready for use, function wdInitialize() must be called
* after using this macro. This macro is useful for declaring watchdogs 
* statically (i.e. at compile time, without using any dynamic memory 
* allocation at runtime).
*
* Sample usage of this macro is as follows:
* \cs
*      #include <vxWorks.h>
*      #include <wdLib.h>
* 
*      VX_WDOG(myWdog);    /@ declare the watchdog @/
*      WDOG_ID myWdogId;   /@ watchdog ID for further operations @/
* 
*      STATUS initializeFunction (void)
*          {
*          if ((myWdogId = wdInitialize (myWdog)) == NULL) 
*               return (ERROR);       /@ initialization failed @/
*          else
*               return (OK);
*          }
* \ce
* 
* SEE ALSO: wdInitialize()
* \NOMANUAL
*/

#define VX_WDOG(name) \
	 _WRS_DATA_ALIGN_BYTES(VX_OBJ_ALIGN_SIZE) char name [VX_WDOG_SIZE]

/* Watchdog routine type */

typedef FUNCPTR WD_RTN;

/* function declarations */

extern STATUS 	wdLibInit (void);
extern WDOG_ID  wdInitialize (char * pWdMem);
extern void     wdCreateLibInit (void);
extern WDOG_ID 	wdCreate (void);
extern STATUS 	wdDelete (WDOG_ID wdId);
extern STATUS 	wdStart (WDOG_ID wdId, _Vx_ticks_t delay, FUNCPTR pRoutine,
			 _Vx_usr_arg_t parameter);
extern STATUS 	wdCancel (WDOG_ID wdId);
extern void 	wdShowInit (void);
extern STATUS 	wdShow (WDOG_ID wdId);
#endif	/* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif /*__cplusplus */

#endif /* __INCwdLibh */
