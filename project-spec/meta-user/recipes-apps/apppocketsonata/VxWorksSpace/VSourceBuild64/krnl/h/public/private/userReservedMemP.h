/* userReservedMemP.h - user-reserved memory private header */

/*
 * Copyright (c) 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01a,19may10,jpb  written.
*/

#ifndef __INCuserReservedMemPh
#define __INCuserReservedMemPh

#ifdef __cplusplus
extern "C" {
#endif

STATUS userReservedMemInit (size_t userReservedSize, BOOL clearMemory);

#ifdef __cplusplus
}
#endif

#endif /* __INCuserReservedMemPh */
