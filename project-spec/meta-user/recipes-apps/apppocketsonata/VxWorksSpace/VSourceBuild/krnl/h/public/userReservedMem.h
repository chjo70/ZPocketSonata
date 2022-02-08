/* userReservedMem.h - user-reserved memory header */

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
01b,19apr10,jpb  Updated for new HLD requirements.
01a,31mar10,jpb  written.
*/

#ifndef __INCuserReservedMemh
#define __INCuserReservedMemh

#ifdef __cplusplus
extern "C" {
#endif

void userReservedGet       (char **  pUserReservedAddr, 
                            size_t * pUserResrvedSize);

#ifdef __cplusplus
}
#endif

#endif /* __INCuserReservedMemh */
