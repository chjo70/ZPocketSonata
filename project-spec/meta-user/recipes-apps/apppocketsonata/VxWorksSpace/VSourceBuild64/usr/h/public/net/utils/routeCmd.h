/* rtadvLib.h - Router Advertisement for IPv6 */

/* Copyright 1992-2003, 2014 Wind River Systems, Inc. */

/*
modification history
--------------------
01f,09jan12,h_x  Move extern "C" after last header file include.
01e,05nov03,cdw  Removal of unnecessary _KERNEL guards.
01d,04nov03,rlm  Ran batch header path update for header re-org.
01c,03nov03,rlm  Removed wrn/coreip/ prefix from #includes for header re-org.
01b,10jun03,vvv  include netVersion.h
01a,09Apr02,nee  written.
*/

#ifndef __INCrouteCmdh
#define __INCrouteCmdh


#ifdef __cplusplus
extern "C" {
#endif

#if defined(__STDC__) || defined(__cplusplus)

extern int routec (char *options);

#else	/* __STDC__ */

extern int      routec ();

#endif	/* __STDC__ */

#ifdef __cplusplus
}
#endif

#endif /* __INCrouteCmdh */
