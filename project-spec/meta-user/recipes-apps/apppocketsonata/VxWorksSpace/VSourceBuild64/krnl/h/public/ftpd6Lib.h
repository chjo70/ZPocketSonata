/* ftpd6Lib.h - header file for ftpd6Lib.c */

/*
 * Copyright (c) 2001-2006, 2014 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01l,09jan12,h_x  Move extern "C" after last header file include.
01k,27dec06,kch  Removed references to the obsolete coreip virtual stack.
01j,15dec04,syy  Fixed SPR#104035: add support for guest login
01i,20aug04,rp   merged from COMP_WN_IPV6_BASE6_ITER5_TO_UNIFIED_PRE_MERGE
01h,12apr04,spm  removed virtual stack #include (already in source code)
01g,15mar04,rp   merged from orion
01f,20nov03,niq  Remove copyright_wrs.h file inclusion
01e,05nov03,cdw  Removal of unnecessary _KERNEL guards.
01d,04nov03,rlm  Ran batch header path update for header re-org.
01c,03nov03,rlm  Removed wrn/coreip/ prefix from #includes for header re-org.
01b,10jun03,vvv  include netVersion.h
01a,14sep01,ant  written
*/

#ifndef __INCftpd6Libh
#define __INCftpd6Libh


#ifdef __cplusplus
extern "C" {
#endif

/* function declarations */

#if defined(__STDC__) || defined(__cplusplus)

extern STATUS 	ftpd6Init (char *, FUNCPTR, int stackSize);
extern STATUS 	ftpd6Delete (void);
extern void     ftpd6EnableSecurity(void);
extern void     ftpd6DisableSecurity(void);
extern STATUS   ftpd6GuestIdSet (const char *, u_int);
extern STATUS   ftpd6GuestAllow (const char *, const char *, BOOL);
    
#else	/* __STDC__ */

extern STATUS 	ftpd6Init ();
extern void 	ftpd6Delete ();
extern void ftpd6EnableSecurity();
extern void ftpd6DisableSecurity();

#endif	/* __STDC__ */

#ifdef __cplusplus
}
#endif

#endif /* __INCftpd6Libh */
