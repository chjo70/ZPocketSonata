/* usrNetIpAttachCommon.c - Common code to attach a END device to IP */

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
04nov14,jpb  04nov14,jpb  added header file for _func_printErr (V7COR-910)
06oct06,kch  Comment out ppp device check.
10feb04,elp  usrNetIpAttachCommon() returns without message when
	     devName==NULL.
08jan04,rp   fixed SPR 92684
14dec03,ijm  if boot device is not configured, try "other", SPR#70284
28feb02,ham  added netAttachFlag.
26nov01,ham  revised from TOR3_1-FCS (01i).
*/

/*
DESCRIPTION
NOMANUAL
*/

#include <private/fioLibP.h>		/* _func_printErr */

/*******************************************************************************
*
* usrNetIpAttachCommon - attach a network device
*
* RETURNS: N/A
*
* NOMANUAL
*/

void usrNetIpAttachCommon
    (
    char *    pDeviceName,	/* Device name */
    int       unitNum,		/* unit number */
    char *    pStr,		/* e.g. "IPv4", "IPv6" */
    FUNCPTR   pAttachRtn	/* attach routine */
    )
    {

    int unitNumber = unitNum;

    /* skip if no device is available */
    if (pDeviceName == NULL)
    	return;

#if 0    
    /* ipAttach for ppp is done during its bringup */
    if (strncmp (pDeviceName, "ppp", 3) == 0)
        return;
#endif

    if (endFindByName (pDeviceName, unitNum) == NULL)
        {
        if (sysBootParams.other [0] != EOS)
            {
            char *pStr;

            /*
             * the other parameter may or may not contain a
             * unit number.  If there is one, use it
             * and update sysBootParams.unitNum.
             */

            pStr = (char *)&sysBootParams.other;
            while (!isdigit ((int)*pStr) && *pStr != EOS)
                pStr++;

            if (pStr != EOS && sscanf (pStr, "%d", &unitNumber) == 1)
                {
                sysBootParams.unitNum = unitNumber;
                uNum = unitNumber;
                *pStr = EOS;
                }

            pDevName = sysBootParams.other;
            }
        else
            pDevName = NULL;

        pDeviceName = pDevName;
        }

    if (pAttachRtn == NULL) 
    	return;

    if ((*pAttachRtn) (unitNumber, pDeviceName) != OK)
        {
        if ( _func_printErr)
            (* _func_printErr) ("Failed to attach to device %s%d",
                            pDeviceName, unitNumber);
        return;
        }

    netAttachFlag = TRUE;       /* usrNetBoot.c */

    if (_func_printErr)
        (*_func_printErr)
        ("Attached %s interface to %s unit %d\n",pStr,pDeviceName,unitNumber);

    return;
    }
