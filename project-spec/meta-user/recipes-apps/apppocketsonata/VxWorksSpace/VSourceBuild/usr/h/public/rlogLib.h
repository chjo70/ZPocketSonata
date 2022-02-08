/* rlogLib.h - header file for rlogLib.c */

/* Copyright 1984-2004, 2006, 2009 Wind River Systems, Inc. */

/*
modification history
--------------------
01l,27may11,rjq  Fix for WIND00277167.
01k,02jun09,dlk  LP64 adaptation. Also WIND00169357.  Remove private
                 types and information to rlogLib.c.
01j,14aug06,tkf  Cleanup for IPNET integration.
01i,25feb04,asr  updates resulting from review comments
01h,06feb04,asr  included lstlib.h
01g,30jan04,dlk  Remove extra tokens at end of #ifndef directives.
01f,12dec03,rp   support for multiple rlogin sessions
01e,05nov03,cdw  Removal of unnecessary _KERNEL guards.
01d,04nov03,rlm  Ran batch header path update for header re-org.
01c,03nov03,rlm  Removed wrn/coreip/ prefix from #includes for header re-org.
01b,02oct02,ant    virtualization changes
01c,06aug03,nee  Accordion Base6 merge from ACCORDION_BASE6_MERGE_BASELINE
                 label
01b,10jun03,vvv  include netVersion.h
01a,10jun02,ann  ported to clarinet from AE1.1 ver 02b
*/

#ifndef __INCrlogLibh
#define __INCrlogLibh

#ifdef __cplusplus
extern "C" {
#endif

/* function declarations */

extern STATUS   rlogin (char *host);
extern void rlogcInit(int client_number);

#ifdef _WRS_KERNEL
    extern STATUS 	rlogInit (long maxclients);
    extern void 	rlogind (void);
#endif /* _WRS_KERNEL */

#ifdef __cplusplus
}
#endif

#endif /* __INCrlogLibh */
