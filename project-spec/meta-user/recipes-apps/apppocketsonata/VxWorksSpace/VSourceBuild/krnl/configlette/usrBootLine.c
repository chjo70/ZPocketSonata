/* usrBootLine.c - Routines to parse the bootline */

/*
 * Copyright (c) 1998-2007,2013,2014,2016 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
21jul16,j_l  use bootapp bootline first, then NVRAM or FDT (V7PRO-3156)
03apr14,elp  Do not set default boot line on simulators.
19mar14,j_l  US32795 - changes for new gnu compiler
18feb14,d_z  Move to kernel. VXW7-1937
12feb14,h_s  Cleanup coverity defects. (us17404)
14jan14,h_s  Remove startType judgement due to the current BOOT design.
             (VXW7-1253)
16dec13,h_x  Fix WIND00446997
21oct13,l_z  use FDT to initialize the bootline when FDT is included
04nov10,swg  add the explicit declaration for _procNumWasSet
             (to fix WIND00237118).
27aug07,tkf  Support IPv6 Only configuration.
10apr07,rlg  Defect 92458 - removal of previous attempt to fix
             usrBootLineInit - needed to make fix in bootInit not here.
21mar07,rlg  Defect WIND00091114 - usrBootLineInit has problems -
             discovered in testing bootroms for 6.5
09nov06,kch  Replaced net/inet.h with inetLib.h.
06oct06,kch  Added net/inet.h include to fix warning.
19may06,tkf  Add usrBootLineGet() routine.
08aug05,wap  Change dependencies for micro stack
08aug05,wap  Change dependencies for micro stack
15jun04,j_b  handle case where bootline is specified on boot cmd line
27feb02,ham  ported from TOR3_1-FCS (01a).
18aug98,ann  created this configlette from usrNetwork.c
*/

/*
DESCRIPTION
This configlette is included when the INCLUDE_BOOT_LINE_INIT component
is chosen. It contains the routines to parse the bootline parameters.

NOMANUAL
*/

#if defined(INET) && (defined(INCLUDE_NET_INIT) ||      \
                      defined(INCLUDE_NET_DEFER_INIT))
#include <inetLib.h>
#endif

#ifdef _WRS_CONFIG_FDT
#include <vxFdtLib.h>
#endif /* _WRS_CONFIG_FDT */

#if defined(INET) && (defined(INCLUDE_NET_INIT) ||      \
                      defined(INCLUDE_NET_DEFER_INIT))
STATUS checkInetAddrField (char *pInetAddr, BOOL subnetMaskOK);
#endif /* defined(INET) && (defined(INCLUDE_NET_INIT) ||     */
       /*                   defined(INCLUDE_NET_DEFER_INIT)) */

extern BOOL _procNumWasSet;

/* forward declaration */

STATUS usrBootLineCrack (char * bootString, BOOT_PARAMS *pParams);

/******************************************************************************
*
* usrBootLineInit - initialize system boot line
*
* Initializes system boot line.  If the boot line is empty
* then the boot line is initialized from non-volatile ram, if any,
* otherwise from the compiled in default boot line.
*
* NOMANUAL
*/

void usrBootLineInit
    (
    int startType
    )
    {
    BOOT_PARAMS pParams;

    ((char *)(BOOT_LINE_ADRS))[BOOT_LINE_SIZE-1] = EOS;

    /*
     * If there is boot line passed from bootapp, use it,
     * otherwise get it either from non-volatile RAM or FDT.
     */

    if (*((char *)(BOOT_LINE_ADRS)) != EOS &&
        (usrBootLineCrack ((char *)(BOOT_LINE_ADRS), &pParams) == OK) &&
        (bootParamCheck (&pParams, TRUE, NULL) == OK))
        {

        /* boot line exist, just return */

        return;
        }

    /* There is no boot line passed from bootapp. */

    /* read the bootline from NVRAM */

#ifdef _WRS_CONFIG_FDT

#ifdef INCLUDE_BOOTAPP_NVRAM_SUPPORT

    if (bootAppNvGet &&
        (bootAppNvGet ((char *)BOOT_LINE_ADRS, BOOT_LINE_SIZE, 0) == OK))
        {

        /* found boot line in NVRAM, just return */

        return;
        }

#endif /* INCLUDE_BOOTAPP_NVRAM_SUPPORT */

#else

    if (sysNvRamGet ((char *)BOOT_LINE_ADRS, BOOT_LINE_SIZE, 0) == OK)
        {

        /* found boot line in NVRAM, just return */

        return;
        }

#endif /*  _WRS_CONFIG_FDT */

#ifdef _WRS_CONFIG_FDT

    /* read the bootline from FDT */

    if (vxFdtBootargsGet ((char *)BOOT_LINE_ADRS, BOOT_LINE_SIZE) == OK)
        {

        /* found the boot line in FDT, use it */

        return;
        }

#endif /* _WRS_CONFIG_FDT */

    /* bootline is not found, use default boot line */

    strncpy ((char *)BOOT_LINE_ADRS, DEFAULT_BOOT_LINE, BOOT_LINE_SIZE);

    }

/******************************************************************************
*
* usrBootLineCrack - interpret and verify boot line
*
* This routine interprets the specified boot line and checks the validity
* of certain parameters.  If there are errors, a diagnostic message is
* printed.
*
* NOMANUAL
*/

STATUS usrBootLineCrack
    (
    char * bootString,
    BOOT_PARAMS *pParams
    )
    {
    FAST char * pS;

    pS = bootStringToStruct (bootString, pParams);
    if ((*pS != EOS) || (pS == bootString))
        {
        bootParamsErrorPrint (bootString, pS);
        return (ERROR);
        }

#if defined(INET) && (defined(INCLUDE_NET_INIT) ||      \
                      defined(INCLUDE_NET_DEFER_INIT))

    /* check inet addresses */

    if ((checkInetAddrField (pParams->ead, TRUE) != OK) ||
        (checkInetAddrField (pParams->bad, TRUE) != OK) ||
        (checkInetAddrField (pParams->had, FALSE) != OK) ||
        (checkInetAddrField (pParams->gad, FALSE) != OK))
        {
        return (ERROR);
        }
#endif /* defined(INET) && (defined(INCLUDE_NET_INIT) ||     */
       /*                   defined(INCLUDE_NET_DEFER_INIT)) */

    return (OK);
    }

#if defined(INET) && (defined(INCLUDE_NET_INIT) ||      \
                      defined(INCLUDE_NET_DEFER_INIT))
/******************************************************************************
*
* checkInetAddrField - check for valid inet address in boot field
*
* RETURNS: OK, or ERROR if invalid inet address
*
* NOMANUAL
*/

STATUS checkInetAddrField
    (
    char *pInetAddr,
    BOOL subnetMaskOK
    )
    {
    char inetAddr [30];
    int netmask;

    bzero (inetAddr, 30);   /* SPR 6326 - prevents error if address invalid. */

    if (*pInetAddr == EOS)
        return (OK);

    strncpy (inetAddr, pInetAddr, sizeof(inetAddr)-1);
    inetAddr[sizeof(inetAddr)-1] = EOS;

    if (subnetMaskOK)
        {
        if (bootNetmaskExtract (inetAddr, &netmask) < 0)
            {
            printf ("Error: invalid netmask in boot field \"%s\".\n", inetAddr);
            return (ERROR);
            }
        }

    if (inet_addr (inetAddr) == (uint32_t) ERROR)
        {
        printf ("Error: invalid inet address in boot field \"%s\".\n",inetAddr);
        return (ERROR);
        }

    return (OK);
    }
#endif /* defined(INET) && (defined(INCLUDE_NET_INIT) ||     */
       /*                   defined(INCLUDE_NET_DEFER_INIT)) */

/******************************************************************************
*
* usrBootLineParse - parse the boot line
*/

STATUS usrBootLineParse
    (
    char* bootString
    )
    {
    BOOT_PARAMS params;

    usrBootLineInit (sysStartType);     /* crack the bootline */

    /* interpret boot command */

    if (bootString == NULL)
        bootString = (char *)BOOT_LINE_ADRS;

    if (usrBootLineCrack (bootString, &params) != OK)
        return (ERROR);

    /* fill in any default values specified in configAll */

    if ((params.hostName [0] == EOS) &&                 /* host name */
        (strcmp (HOST_NAME_DEFAULT, "") != 0))
        {
        strncpy (params.hostName, HOST_NAME_DEFAULT, BOOT_HOST_LEN);
        printf ("Host Name: %s \n", params.hostName);
        }

    if ((params.targetName [0] == EOS) &&               /* targetname */
        (strcmp (TARGET_NAME_DEFAULT, "") != 0))
        {
        strncpy (params.targetName, TARGET_NAME_DEFAULT, BOOT_HOST_LEN);
        printf ("Target Name: %s \n", params.targetName);
        }

    if ((params.usr [0] == EOS) &&                      /* user name (u) */
        (strcmp (HOST_USER_DEFAULT, "") != 0))
        {
        strncpy (params.usr, HOST_USER_DEFAULT, BOOT_USR_LEN);
        printf ("User: %s \n", params.usr);
        }

    /* SCRIPT_DEFAULT can be configured in config file */

    /* coverity[pointless_string_compare] */

    if ((params.startupScript [0] == EOS) &&    /* startup script (s) */
        (strcmp (SCRIPT_DEFAULT, "") != 0))
        {
        strncpy (params.startupScript, SCRIPT_DEFAULT, BOOT_FILE_LEN);
        printf ("StartUp Script: %s \n", params.startupScript);
        }

    /* OTHER_DEFAULT can be configured in config file */

    /* coverity[pointless_string_compare] */

    if ((params.other [0] == EOS) &&                    /* other (o) */
        (strcmp (OTHER_DEFAULT, "") != 0))
        {
        strncpy (params.other, OTHER_DEFAULT, BOOT_OTHER_LEN);
        printf ("Other: %s \n", params.other);
        }

    if (params.passwd [0] == EOS)                       /* password */
        strncpy (params.passwd, HOST_PASSWORD_DEFAULT, BOOT_PASSWORD_LEN);

    /* fill in system-wide variables */

    bcopy ((char *) &params, (char *) &sysBootParams, sizeof (sysBootParams));

    sysFlags = params.flags;

    /* backwards compatibility */

    strncpy (sysBootHost, params.hostName, sizeof(sysBootHost)-1);
    sysBootHost[sizeof(sysBootHost)-1] = EOS;
    strncpy (sysBootFile, params.bootFile, sizeof(sysBootFile)-1);
    sysBootFile[sizeof(sysBootFile)-1] = EOS;

    /* set processor number: may establish vme bus access, etc. */

    if (_procNumWasSet != TRUE)
        {
        sysProcNumSet (params.procNum);
        _procNumWasSet = TRUE;
        }

    return OK;
    }

/******************************************************************************
* usrBootLineGet - Return the boot line address
*
* This routine returns the boot line address. This prevents allows to
* access the boot line without having to include config.h.
*
* NOMANUAL
*/

char * usrBootLineGet
    (
    )
    {
    return (char *)BOOT_LINE_ADRS;
    }
