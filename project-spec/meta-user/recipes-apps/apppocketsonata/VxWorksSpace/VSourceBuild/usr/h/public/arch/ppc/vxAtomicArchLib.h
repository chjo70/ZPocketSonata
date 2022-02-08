/* vxAtomicArchLibCommon.h - PowerPC specific atomic library header */

/*
 * Copyright (c) 2009 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
01a,17may09,gls  written.
*/

#ifndef __INCvxAtomicArchLibCommonh
#define __INCvxAtomicArchLibCommonh

#ifdef __cplusplus
extern "C" {
#endif

#define _WRS_ARCH_SUPPORTS_MEM_BARRIER

/*
 * Macros to provide memory barrier; lightweight sync is enough for
 * load/store memory barrier. However not all CPU support lwsync.
 */

#define VX_MEM_BARRIER_R()	    _WRS_BARRIER("sync");
#define VX_MEM_BARRIER_W()	    _WRS_BARRIER("sync");
#define VX_MEM_BARRIER_RW()	    _WRS_BARRIER("sync");
#define VX_INSTR_BARRIER()          _WRS_BARRIER("isync")

#ifdef __cplusplus
}
#endif

#endif /* __INCvxAtomicArchLibCommonh */
