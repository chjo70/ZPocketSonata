/* tickLib.h - user-level tick library header file */

/*
 * Copyright (c) 2003-2004, 2014 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
18nov14,gls  Added tickRateGet()
08jul10,pcs  Change the return type of API tickGet from an ULONG to
             _Vx_ticks_t
22may04,job  Added prototype for tick64Get.
31oct03,aeg  written 
*/

#ifndef __INCtickLibh
#define __INCtickLibh

#ifdef __cplusplus
extern "C" {
#endif

extern _Vx_ticks_t   tickGet (void);
extern _Vx_ticks64_t tick64Get (void);
extern int           tickRateGet (void);

#ifdef __cplusplus
}
#endif

#endif /* __INCtickLibh */
