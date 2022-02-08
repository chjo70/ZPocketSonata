/* timexLib.h - header for execution timer facilities */

/* Copyright 1990-1992, 2009 Wind River Systems, Inc. */

/*
modification history
--------------------
02c,26may09,jmp  Adapted for 64-bit support.
02b,22sep92,rrr  added support for c++
02a,04jul92,jcf  cleaned up.
01e,26may92,rrr  the tree shuffle
01d,04oct91,rrr  passed through the ansification filter
		  -changed VOID to void
		  -changed copyright notice
01c,19oct90,shl  changed timexFunc(), etc, to use variable length argument list.
01b,05oct90,shl  added ANSI function prototypes.
                 made #endif ANSI style.
                 added copyright notice.
01a,10aug90,dnw  written
*/

#ifndef __INCtimexLibh
#define __INCtimexLibh

#ifdef __cplusplus
extern "C" {
#endif

/* function declarations */

extern void 	timex		(FUNCPTR func,
				 _Vx_usr_arg_t arg1, _Vx_usr_arg_t arg2,
				 _Vx_usr_arg_t arg3, _Vx_usr_arg_t arg4,
				 _Vx_usr_arg_t arg5, _Vx_usr_arg_t arg6,
				 _Vx_usr_arg_t arg7, _Vx_usr_arg_t arg8);
extern void 	timexClear	(void);
extern void 	timexFunc	(int i, FUNCPTR func,
				 _Vx_usr_arg_t arg1, _Vx_usr_arg_t arg2,
				 _Vx_usr_arg_t arg3, _Vx_usr_arg_t arg4,
				 _Vx_usr_arg_t arg5, _Vx_usr_arg_t arg6,
				 _Vx_usr_arg_t arg7, _Vx_usr_arg_t arg8);
extern void 	timexHelp	(void);
extern void 	timexInit	(void);
extern void 	timexN		(FUNCPTR func,
				 _Vx_usr_arg_t arg1, _Vx_usr_arg_t arg2,
				 _Vx_usr_arg_t arg3, _Vx_usr_arg_t arg4,
				 _Vx_usr_arg_t arg5, _Vx_usr_arg_t arg6,
				 _Vx_usr_arg_t arg7, _Vx_usr_arg_t arg8);
extern void 	timexPost	(int i, FUNCPTR func,
				 _Vx_usr_arg_t arg1, _Vx_usr_arg_t arg2,
				 _Vx_usr_arg_t arg3, _Vx_usr_arg_t arg4,
				 _Vx_usr_arg_t arg5, _Vx_usr_arg_t arg6,
				 _Vx_usr_arg_t arg7, _Vx_usr_arg_t arg8);
extern void 	timexPre	(int i, FUNCPTR func,
				 _Vx_usr_arg_t arg1, _Vx_usr_arg_t arg2,
				 _Vx_usr_arg_t arg3, _Vx_usr_arg_t arg4,
				 _Vx_usr_arg_t arg5, _Vx_usr_arg_t arg6,
				 _Vx_usr_arg_t arg7, _Vx_usr_arg_t arg8);
extern void 	timexShow	(void);

#ifdef __cplusplus
}
#endif

#endif /* __INCtimexLibh */
