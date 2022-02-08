/* bootLibP.h - boot parser library private header */

/*
 * Copyright (c) 2014 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
14may14,jpb  written.
*/

#ifndef __INCbootLibPh
#define __INCbootLibPh

#ifdef __cplusplus
extern "C" {
#endif

char * bootParamsReserveGet (char * token);
STATUS bootParamsReserveSet (char * string);

#ifdef __cplusplus
}
#endif

#endif /* __INCbootLibPh */
