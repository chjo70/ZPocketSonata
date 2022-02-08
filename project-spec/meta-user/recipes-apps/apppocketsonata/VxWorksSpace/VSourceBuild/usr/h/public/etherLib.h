/* etherLib.h - ethernet hook routines header */

/* 
 * Copyright 1984-2006, 2014 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
01g,09jan12,h_x  Move extern "C" after last header file include.
01f,19jun06,jpb  Removed I960 check.
01e,05nov03,cdw  Removal of unnecessary _KERNEL guards.
01d,04nov03,rlm  Ran batch header path update for header re-org.
01c,03nov03,rlm  Removed wrn/coreip/ prefix from #includes for header re-org.
01b,10jun03,vvv  include netVersion.h
01a,28sep02,ann  provided only for backward compatibility
*/

#ifndef __INCetherLibh
#define __INCetherLibh


#ifdef __cplusplus
extern "C" {
#endif

/* defints */
typedef struct enet_hdr
    {
    char dst [6];
    char src [6];
    USHORT type;
    } ENET_HDR;

#define ENET_HDR_SIZ        sizeof(ENET_HDR)
#define ENET_HDR_REAL_SIZ   14

#ifdef __cplusplus
}
#endif

#endif /* __INCetherLibh */
