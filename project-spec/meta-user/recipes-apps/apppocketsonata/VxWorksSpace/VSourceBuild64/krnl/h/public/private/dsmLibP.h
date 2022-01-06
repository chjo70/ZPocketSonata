/* dsmLibP.h - private disassembler library header */

/*
 * Copyright (c) 2013-2014 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify, or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
31jan14,to   include vxWorks.h for IMPORT
07oct13,h_k  created.
*/

#ifndef __INCdsmLibPh
#define __INCdsmLibPh

#include <vxWorks.h>    /* for IMPORT */
#include <dsmLib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* function declarations */

IMPORT int dsmInst (INSTR * pD,
                    _Vx_usr_arg_t address,
                    NPRTADDRESS_OUTPUT_FUNCPTR prtAddress,
                    OPRINTF_OUTPUT_FUNCPTR oFn,
                    _Vx_usr_arg_t oArg);

IMPORT int (* _func_dsmInst) (INSTR * pD,
			      _Vx_usr_arg_t address,
			      NPRTADDRESS_OUTPUT_FUNCPTR prtAddress,
			      OPRINTF_OUTPUT_FUNCPTR oFn,
			      _Vx_usr_arg_t oArg);

/* alias for backward compatibility */

IMPORT int (* _dbgDsmInstRtn) (INSTR * pD,
			       _Vx_usr_arg_t address,
			       NPRTADDRESS_OUTPUT_FUNCPTR prtAddress,
			       OPRINTF_OUTPUT_FUNCPTR oFn,
			       _Vx_usr_arg_t oArg);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __INCdsmLibPh */
