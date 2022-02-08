/* resolvLib.h - VxWorks DNS resolver facilities */

/* 
 * Copyright (c) 1996-2007 Wind River Systems, Inc. 
 * 
 * The right to copy, distribute, modify or otherwise make use 
 * of this software may be licensed only pursuant to the terms 
 * of an applicable Wind River license agreement. 
 */

/*
modification history
--------------------
01t,08feb07,tkf  Updated for integration with IPNET.
01s,20dec05,dlk  Allow scaling out of DNS resolver debug.
01r,10may05,vvv  updated MAXPACKET definition
01q,21mar05,ijm  corrected MAXIPADDRLEN for IPv6, SPR#106912 
01p,23aug04,rp   merged from COMP_WN_IPV6_BASE6_ITER5_TO_UNIFIED_PRE_MERGE
01o,28may04,niq  Merging from base6 label POST_ITER5_FRZ16_REBASE (ver
                 /main/vdt/base6_itn5_networking-int/2)
01n,25feb04,xli  add resolvInit prototype for non__STDC__ compilation 
01m,28jan04,xli  add the resolvInit() function for user land which is different
                 from the resolvInit(char* , char*, FUNCPTR) in kernel
01l,20nov03,niq  Remove copyright_wrs.h file inclusion
01k,05nov03,cdw  Removal of unnecessary _KERNEL guards.
01j,04nov03,rlm  Ran batch header path update for header re-org.
01i,03nov03,rlm  Removed wrn/coreip/ prefix from #includes for header re-org.
01h,24oct03,cdw  update include statements post header re-org.
01g,15sep03,vvv  updated path for new headers
01f,06aug03,nee  Accordion Base6 merge from ACCORDION_BASE6_MERGE_BASELINE
                 label
01e,15may03,spm  Tornado 2.2 FCS merge (SPR #67238; ver 01e12oct01,rae:
                 TOR2_2-FCS-COPY label, tor2 branch, /wind/river VOB)
01d,20sep01,vlk  removed declaration of routines: resolvQuery(), resMkQuery(), resSend()
01c,19may97,spm  added S_resolvLib_INVALID_PARAMETER error value (SPR #8603),
                 corrected format of modification history
01b,02apr97,jag  removed reference to header file resolv/param.h. 
01a,29jul96,rjc  written. 
*/
#ifndef __INCresolvLibh
#define __INCresolvLibh

#ifdef __cplusplus
extern "C" {
#endif

/* includes */

/* defines */
#define MAXDNAME    256	/* maximum domain name */
#define	MAXNS		  4	/* max # name servers we'll track */

/*
 * name server address length. For IPv6, it must be large enough to
 * accomodate link layer address plus the interface name and unit number.
 */

#ifdef INET6
#define MAXIPADDRLEN            64    /* INET6_ADDR_LEN+%+IFNAMESIZE+unit*/
#else
#define MAXIPADDRLEN            20    /* assuming decimal dot notation */
#endif

#define  QUERY_LOCAL_FIRST      1     /* Query static host table first */
#define  QUERY_DNS_FIRST        2     /* Query DNS first */
#define  QUERY_DNS_ONLY         3     /* Query DNS only */

#define S_resolvLib_NO_RECOVERY       (M_resolvLib | 1)
#define S_resolvLib_TRY_AGAIN         (M_resolvLib | 2)
#define S_resolvLib_HOST_NOT_FOUND    (M_resolvLib | 3)
#define S_resolvLib_NO_DATA           (M_resolvLib | 4)
#define S_resolvLib_BUFFER_2_SMALL    (M_resolvLib | 5)
#define S_resolvLib_INVALID_PARAMETER (M_resolvLib | 6)
#define S_resolvLib_INVALID_ADDRESS   (M_resolvLib | 7)

#define     MAXPACKET       (64 * 1024)

/* Resolver parameter configuration structures */

#ifdef _WRS_KERNEL

    typedef struct 
        {
        /* order in which to query hostLib database and DNS */
        char   queryOrder;   
        /* maximum domain name based on rfc883 */
        char   domainName [MAXDNAME]; 
        /* IP address of name servers */
        char   nameServersAddr [MAXNS][MAXIPADDRLEN];   

        } RESOLV_PARAMS_S;

#endif /* _WRS_KERNEL */

/* function declarations */

#if defined(__STDC__) || defined(__cplusplus)

#ifdef _WRS_KERNEL
    STATUS             resolvParamsSet (RESOLV_PARAMS_S *);
    void               resolvParamsGet (RESOLV_PARAMS_S *);
#endif

#else   /* __STDC__ */

#ifdef _WRS_KERNEL
    void               resolvParamsSet ();
    void               resolvParamsGet ();
#endif

    int                resolvDNExpand ();
    int                resolvDNComp ();

#endif  /* __STDC__ */


#ifdef __cplusplus
}
#endif


#endif /* __INCresolvLibh */
