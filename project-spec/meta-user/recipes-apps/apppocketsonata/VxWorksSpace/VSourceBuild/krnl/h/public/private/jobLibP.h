/* jobLibP.h - private job facility library header */

/* 
 * Copyright (c) 2004-2005, 2009-2010 Wind River Systems, Inc. 
 *
 * The right to copy, distribute, modify or otherwise make use 
 * of this software may be licensed only pursuant to the terms 
 * of an applicable Wind River license agreement. 
 */ 

/*
modification history
--------------------
01f,08apr10,jpb  Added func binding prototypes.
01e,26mar09,zl   updated for LP64 build. Removed isrJobMsgQId. Moved back 
                 jobAdd(). Added jobTaskWorkAdd().
01d,07jun05,yvp  Deleted jobTaskLibInit, jobExcAdd. jobAdd moved to excLibP.h.
                 Updated copyright.
01c,06sep04,aeg  added jobExcAdd () prototype.
01b,07sep04,bpn  Added isrJobMsgQId definition.
01a,27aug04,ans  written
*/

#ifndef __INCjobLibPh
#define __INCjobLibPh

#ifdef __cplusplus
extern "C" {
#endif

/* function declarations */

extern STATUS jobTaskLibInit (size_t jobTaskStackSz);
extern STATUS jobTaskWorkAdd (FUNCPTR func, _Vx_usr_arg_t arg1, 
			      _Vx_usr_arg_t arg2, _Vx_usr_arg_t arg3,
			      _Vx_usr_arg_t arg4, _Vx_usr_arg_t arg5,
			      _Vx_usr_arg_t arg6, int * pResult);
extern STATUS jobAdd (VOIDFUNCPTR func,
		      _Vx_usr_arg_t arg1, _Vx_usr_arg_t arg2,
		      _Vx_usr_arg_t arg3, _Vx_usr_arg_t arg4,
		      _Vx_usr_arg_t arg5, _Vx_usr_arg_t arg6);

/* function pointer prototypes */

extern STATUS (*_func_jobTaskWorkAdd)(FUNCPTR func, _Vx_usr_arg_t arg1, 
				      _Vx_usr_arg_t arg2, _Vx_usr_arg_t arg3,
				      _Vx_usr_arg_t arg4, _Vx_usr_arg_t arg5,
				      _Vx_usr_arg_t arg6, int * pResult);

#ifdef __cplusplus
}
#endif

#endif /* __INCjobLibPh */
