/* usrMtd.c - MTD config module */

/*
 * Copyright (c) 2012, 2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify, or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
08jun15,sye  fixed compiler warnings. (V7STO-385)
06nov12,x_z  fixed mtdCfgPartAdd() issue.
02nov12,x_z  fixed duplicated free issue.
22oct12,x_z  added support for Flash usage.
10oct12,x_z  adjusted for mtd.h.
25sep12,x_z  saved config string to avoid text segment modification.
30aug12,x_z  redesigned and rewritten.
31may12,m_y  written.
*/

/*
DESCRIPTION

This module parases the MTD config string and then pass Flash partition table to
MTD module.

Every Flash chip can be splited into several physical partitions, and one or
more partitions with the same chip model can be involved into one Flash group,
and one or more groups can be involved into one MTD device.

Note:

1. All the Flash physical partitions in one MTD device must have the same chip
model;
2. All the Flash physical partitions in one Flash group must have the same block
count, and can be parallel to be accessed.
3. All the Flash groups in one MTD device must have the same Flash physical
partition number;
4. The overlapped Flash partitions for one Flash chip are NOT supported;
5. The Flash partitions in one MTD device must be for the same usage (The
Flash usage is defined in flash.h);

MTD configuration string is composed of several Flash chip strings:

    <Flash chip 0 string>;<Flash chip 1 string>...

And Flash chip string is composed of several Flash partition strings:

    $<Flash instance name>#<chip index>:
    <Flash partition 0 string>;<Flash partition 1 string>...

And Flash partition string is the following:

    <start block address>,<block count>,<MTD device name>#<Flash group index>,<Flash usage>

Note:
    1. The space and LF(line break) are NOT allowed in the MTD config string;
    2. The sperators (',', ';', ':', '#' and '$') mentioned above are NOT
    allowed in <Flash instance name> and <MTD device name>;
    3. If vxprj is used to configured the MTD config string, some special
    characters, such as '"', '$' and ';', MUST be used with one '\' ahead. For
    example:

    vxprj parameter set MTD_CFG_STR \"\$gpmc0#0:0x0,0x100,/nvram#0,1\;0x100,0x200,/ftl0#0,0\"

The following are several examples:

    1. 2 Flash chips with 2 physical partitions, 2 MTD devices with 2 Flash
    groups, and then each group has 1 Flash partition:

    "$gpmc0#0:0x100,0x100,/ftl0#0,0;0x200,0x100,/ftl0#1,0;$gpmc0#1:0x100,0x100,/nvram#0,1;0x200,0x100,/nvram#1,0"

    2. 2 Flash chips with 2 physical partitions for FTL, 1 MTD devices with 2 Flash
    groups, and then each group has 2 Flash partition:

    "$gpmc0#0:0x100,0x100,/ftl0#0,0;0x200,0x100,/ftl0#1,0;$gpmc0#1:0x100,0x100,/ftl0#0,0;0x200,0x100,/ftl0#1,0"

INCLUDE FILES: mtd.h

SEE ALSO: mtd.h mtdCore.c
*/

#include <vxWorks.h>
#include <stdio.h>
#include <string.h>
#include <mtd.h>
#include <ctype.h>

/* defines */

#ifndef MTD_CFG_STR
#define MTD_CFG_STR                 ""
#endif /* MTD_CFG_STR */

#define MTD_CFG_STR_LEN_MIN         13
#define MTD_CFG_CHIP_STR_LEN_MIN    12
#define MTD_CFG_PART_STR_LEN_MIN    7

/* locals */

LOCAL STATUS mtdCfgNumParse
    (
    char *      pStr,
    UINT32 *    pVal
    );
LOCAL STATUS mtdCfgPartAdd
    (
    char *              pDevName,
    UINT32              uDevUnit,
    UINT32              uChipId,
    pMTD_FLASH_PART_CFG pPartCfg
    );
LOCAL void mtdClean (void);

/* forward declarations */

LOCAL DL_LIST   gChipList;
LOCAL DL_LIST   gMtdList;

/*******************************************************************************
*
* usrMtdInit - initialize MTD module
*
* This routine parases the MTD config string and then pass Flash partition table
* to MTD module.
*
* RETURNS: N/A
*
* ERRNO: N/A
*
* \NOMANUAL
*/

void usrMtdInit
    (
    char * pMtdCfgStr
    )
    {
    char *                  pCfgStr;
    char *                  pCurChip;
    char *                  pNextChip;
    char *                  pCurPart;
    char *                  pNextPart;
    char *                  pCurField;
    char *                  pNextField;
    char *                  pCh;
    UINT32                  uStrLen;
    char                    devName[MTD_NAME_LEN];
    UINT32                  uDevUnit;
    UINT32                  uChipId;
    MTD_FLASH_PART_CFG      partCfg;

    DLL_INIT (&gChipList);
    DLL_INIT (&gMtdList);

    /* check chip string length */

    uStrLen = strlen (pMtdCfgStr);
    if (uStrLen < MTD_CFG_STR_LEN_MIN)
        return;

    /* allocate to save config string to avoid text segment modification */

    pCfgStr = malloc (uStrLen + 1);
    if (pCfgStr == NULL)
        return;

    strcpy (pCfgStr, pMtdCfgStr);
    pCurChip = pCfgStr;

    /* skip first '$' */

    pNextChip = strchr (pCurChip, '$');
    if (pNextChip == NULL)
        goto usrMtdInitErr;
    pCurChip = pNextChip + 1;

    /* parse Flash chip infromation */

    while (pCurChip != NULL)
        {
        pNextChip = strchr (pCurChip, '$');
        if (pNextChip != NULL)
            {
            *pNextChip = EOS;
            pNextChip++;
            }

        /* check chip string length */

        if (strlen (pCurChip) < MTD_CFG_CHIP_STR_LEN_MIN)
            goto usrMtdInitErr;

        /* find Flash device or controller name and unit */

        pCurField = pCurPart = pCurChip;
        pNextField = strchr (pCurField, '#');
        if (pNextField == NULL)
            goto usrMtdInitErr;

        *pNextField = EOS;
        pCh = pCurField;
        uStrLen = 0;
        while (((*pCh) != EOS) && (!isdigit ((int) (*pCh))))
            {
            pCh++;
            uStrLen++;
            }
        if ((pCh == pCurField) || (pCh == EOS) || (uStrLen >= MTD_NAME_LEN))
            goto usrMtdInitErr;

        strncpy ((char *) &devName, pCurField, uStrLen);
        devName[uStrLen] = EOS;
        if (mtdCfgNumParse (pCh, &uDevUnit) != OK)
            goto usrMtdInitErr;

        /* find chip index */

        pCurField = pNextField + 1;
        pNextField = strchr (pCurField, ':');
        if (pNextField == NULL)
            goto usrMtdInitErr;

        *pNextField = EOS;
        if (mtdCfgNumParse (pCurField, &uChipId) != OK)
            goto usrMtdInitErr;

        /* parse chip partitions */

        pCurPart = pNextField + 1;
        while (pCurPart != NULL)
            {
            pNextPart = strchr (pCurPart, ';');
            if (pNextPart != NULL)
                {
                *pNextPart = EOS;
                pNextPart++;
                }
            pCurField = pCurPart;

            /*
             * check partition string length and break if final partition string
             */

            uStrLen = strlen (pCurPart);
            if (uStrLen == 0)
                break;
            else if (uStrLen < MTD_CFG_PART_STR_LEN_MIN)
                goto usrMtdInitErr;

            /* find start block address */

            pNextField = strchr (pCurField, ',');
            if (pNextField == NULL)
                goto usrMtdInitErr;

            *pNextField = EOS;
            if (mtdCfgNumParse (pCurField, &partCfg.uBlkAddr) != OK)
                goto usrMtdInitErr;

            /* find block number */

            pCurField = pNextField + 1;
            pNextField = strchr (pCurField, ',');
            if (pNextField == NULL)
                goto usrMtdInitErr;

            *pNextField = EOS;
            if (mtdCfgNumParse (pCurField, &partCfg.uBlkCnt) != OK)
                goto usrMtdInitErr;

            /* find MTD device name */

            pCurField = pNextField + 1;
            pNextField = strchr (pCurField, '#');
            if (pNextField == NULL)
                goto usrMtdInitErr;

            *pNextField = EOS;
            uStrLen = strlen (pCurField);
            if (uStrLen >= MTD_NAME_LEN)
                goto usrMtdInitErr;

            strncpy (partCfg.mtdName, pCurField, uStrLen);
            partCfg.mtdName[uStrLen] = EOS;

            /* find Flash group index */

            pCurField = pNextField + 1;
            pNextField = strchr (pCurField, ',');
            if (pNextField == NULL)
                goto usrMtdInitErr;

            *pNextField = EOS;
            if (mtdCfgNumParse (pCurField, &partCfg.uGrpId) != OK)
                goto usrMtdInitErr;

            /* find Flash usage */

            pCurField = pNextField + 1;
            if (mtdCfgNumParse (pCurField,
                                (UINT32 *)&partCfg.flashUsage) != OK)
                goto usrMtdInitErr;

            partCfg.uOp = 0;

            /* add to partition list of the chip */

            if (mtdCfgPartAdd ((char *) devName, uDevUnit, uChipId,
                               &partCfg) != OK)
                goto usrMtdInitErr;

            pCurPart = pNextPart;
            }

        /* next Flash chip */

        pCurChip = pNextChip;
        }

    if (mtdInit (&gChipList, &gMtdList) == OK)
        {
        free (pCfgStr);
        return;
        }

usrMtdInitErr:
    mtdClean ();
    free (pCfgStr);
    }

/*******************************************************************************
*
* mtdCfgNumParse - parse MTD config string for numeric value
*
* This routine parases the MTD config string for numeric value.
*
* RETURNS: OK or ERROR if failed.
*
* ERRNO: N/A
*
* \NOMANUAL
*/

LOCAL STATUS mtdCfgNumParse
    (
    char *      pStr,
    UINT32 *    pVal
    )
    {
    char *  pCh = pStr;
    UINT8   uCh;
    UINT8   uVal;
    UINT32  uRet = 0;
    BOOL    bHex = FALSE;

    if ((strncmp (pCh, "0x", 2) == 0) || (strncmp (pCh, "0X", 2) == 0))
        {
        pCh += 2;
        bHex = TRUE;
        }

    /* scan string */

    while ((*pCh) != EOS)
        {
        uCh = *pCh;
        if (!isascii ((int) uCh))
            return (ERROR);

        if (isdigit ((int) uCh))
            uVal = uCh - '0';
        else if (bHex)
            {
            if ((uCh >= 'a') && (uCh <= 'f'))
                uVal = uCh - 'a' + 10;
            else if ((uCh >= 'A') && (uCh <= 'F'))
                uVal = uCh - 'A' + 10;
            else
                return (ERROR);
            }
        else
            return (ERROR);

        uRet = (uRet * (bHex ? 16 : 10)) + uVal;
        pCh++;
        }

    /* error for NULL string */

    if (pCh == pStr)
        return (ERROR);

    *pVal = uRet;
    return (OK);
    }

/*******************************************************************************
*
* mtdCfgPartAdd - add Flash partition to chip list and MTD list
*
* This routine adds the Flash partition to the chip list and MTD list.
*
* RETURNS: OK or ERROR if failed.
*
* ERRNO: N/A
*
* \NOMANUAL
*/

LOCAL STATUS mtdCfgPartAdd
    (
    char *              pDevName,
    UINT32              uDevUnit,
    UINT32              uChipId,
    pMTD_FLASH_PART_CFG pPartCfg
    )
    {
    pMTD_FLASH_CHIP_CFG     pChipCfg;
    pMTD_FLASH_PART_CFG     pNewPartCfg;
    pMTD_DEV_NODE           pMtdDevCfg;
    pMTD_FLASH_GROUP_NODE   pMtdGrpCfg;
    pMTD_FLASH_GROUP_NODE   pCurMtdGrpCfg;
    pMTD_FLASH_PART_NODE    pMtdPartCfg;
    DL_NODE *               pNode;
    UINT32                  uGrpId;
    UINT32                  i;

    /* search for specified chip */

    pNode = DLL_FIRST (&gChipList);
    while (pNode != NULL)
        {
        pChipCfg = (pMTD_FLASH_CHIP_CFG) pNode;
        if ((strcmp (pChipCfg->devName, pDevName) == 0) &&
            (pChipCfg->uDevUnit == uDevUnit) &&
            (pChipCfg->uChipId == uChipId))
            break;

        pNode = DLL_NEXT (pNode);
        }

    /* allocate and initialize chip config structure if chip doesn't exist */

    if (pNode == NULL)
        {
        pChipCfg = (pMTD_FLASH_CHIP_CFG) malloc (sizeof (MTD_FLASH_CHIP_CFG));
        if (pChipCfg == NULL)
            return (ERROR);

        strncpy (pChipCfg->devName, pDevName, MTD_NAME_LEN);
        pChipCfg->devName[MTD_NAME_LEN - 1]= EOS;
        pChipCfg->uDevUnit = uDevUnit;
        pChipCfg->uChipId = uChipId;
        pChipCfg->uOp = 0;
        DLL_INIT (&pChipCfg->partList);

        DLL_ADD (&gChipList, &pChipCfg->node);
        }

    /* allocate and initialize partition config structure  */

    pNewPartCfg = (pMTD_FLASH_PART_CFG) malloc (sizeof (MTD_FLASH_PART_CFG));
    if (pNewPartCfg == NULL)
        return (ERROR);
    bcopy ((char *) pPartCfg, (char *) pNewPartCfg,
           sizeof (MTD_FLASH_PART_CFG));

    /* add to partition list */

    DLL_ADD (&pChipCfg->partList, &pNewPartCfg->node);

    /* search for specified MTD */

    pNode =  DLL_FIRST (&gMtdList);
    while (pNode != NULL)
        {
        pMtdDevCfg = (pMTD_DEV_NODE) pNode;
        if (strcmp (pMtdDevCfg->mtdName, pPartCfg->mtdName) == 0)
            break;

        pNode = DLL_NEXT (pNode);
        }

    /* allocate MTD node if doesn't exist */

    if (pNode == NULL)
        {

        /* allocate and initialize one new MTD node */

        pMtdDevCfg = (pMTD_DEV_NODE) malloc (sizeof (MTD_DEV_NODE));
        if (pMtdDevCfg == NULL)
            return (ERROR);

        strncpy (pMtdDevCfg->mtdName, pPartCfg->mtdName, MTD_NAME_LEN);
        pMtdDevCfg->mtdName[MTD_NAME_LEN - 1]= EOS;
        pMtdDevCfg->flashUsage = pPartCfg->flashUsage;
        pMtdDevCfg->uOp = 0;
        DLL_INIT (&pMtdDevCfg->grpList);
        DLL_ADD (&gMtdList, &pMtdDevCfg->node);

        /*
         * allocate and initialize enough Flash group nodes, then add them
         * to group list
         */

        pMtdGrpCfg =
            (pMTD_FLASH_GROUP_NODE) malloc (sizeof (MTD_FLASH_GROUP_NODE) *
                                            (pPartCfg->uGrpId + 1));
        if (pMtdGrpCfg == NULL)
            return (ERROR);

        for (i = 0; i < (pPartCfg->uGrpId + 1); i++)
            {
            pMtdGrpCfg[i].uOp = 0;
            DLL_INIT (&pMtdGrpCfg[i].partList);
            DLL_ADD (&pMtdDevCfg->grpList, &pMtdGrpCfg[i].node);
            }

        pCurMtdGrpCfg = &pMtdGrpCfg[pPartCfg->uGrpId];
        }
    else
        {

        /*
         * Flash partitions that belong to one same MTD device must be for the
         * same usage.
         */

        if (pMtdDevCfg->flashUsage != pPartCfg->flashUsage)
            return (ERROR);

        /* search the specified Flash group */

        uGrpId = 0;
        pNode = DLL_FIRST (&pMtdDevCfg->grpList);
        while (pNode != NULL)
            {
            if (pPartCfg->uGrpId == uGrpId)
                break;

            pNode = DLL_NEXT (pNode);
            uGrpId++;
            }

        /*
         * allocate and initialize enough Flash group nodes, then add them
         * to group list if
         */

        if (pNode == NULL)
            {
            pMtdGrpCfg =
                (pMTD_FLASH_GROUP_NODE) malloc (sizeof (MTD_FLASH_GROUP_NODE) *
                                                (pPartCfg->uGrpId + 1 - uGrpId));
            if (pMtdGrpCfg == NULL)
                return (ERROR);

            for (i = 0; i < (pPartCfg->uGrpId + 1 - uGrpId); i++)
                {
                pMtdGrpCfg[i].uOp = 0;
                DLL_INIT (&pMtdGrpCfg[i].partList);
                DLL_ADD (&pMtdDevCfg->grpList, &pMtdGrpCfg[i].node);
                }

            pCurMtdGrpCfg = &pMtdGrpCfg[pPartCfg->uGrpId - uGrpId];
            }
        else
            pCurMtdGrpCfg = (pMTD_FLASH_GROUP_NODE) pNode;
        }

    /*
     * allocate and initialize one new Flash partition node, then add it
     * to group list
     */

    pMtdPartCfg = (pMTD_FLASH_PART_NODE) malloc (sizeof (MTD_FLASH_PART_NODE));
    if (pMtdPartCfg == NULL)
        return (ERROR);

    pMtdPartCfg->pDevName = pChipCfg->devName;
    pMtdPartCfg->uDevUnit = pChipCfg->uDevUnit;
    pMtdPartCfg->uChipId  = pChipCfg->uChipId;
    pMtdPartCfg->uBlkAddr = pPartCfg->uBlkAddr;
    pMtdPartCfg->uBlkCnt  = pPartCfg->uBlkCnt;

    DLL_ADD (&pCurMtdGrpCfg->partList, &pMtdPartCfg->node);
    return (OK);
    }

/*******************************************************************************
*
* mtdClean - clean MTD module
*
* This routine parases the MTD config string and then pass Flash partition table
* to MTD module.
*
* RETURNS: N/A
*
* ERRNO: N/A
*
* \NOMANUAL
*/

LOCAL void mtdClean (void)
    {
    pMTD_FLASH_CHIP_CFG     pCurChipCfg;
    pMTD_FLASH_CHIP_CFG     pNextChipCfg;
    pMTD_FLASH_PART_CFG     pCurPartCfg;
    pMTD_FLASH_PART_CFG     pNextPartCfg;
    pMTD_DEV_NODE           pCurMtdNode;
    pMTD_DEV_NODE           pNextMtdNode;
    pMTD_FLASH_GROUP_NODE   pCurGrpNode;
    pMTD_FLASH_GROUP_NODE   pNextGrpNode;
    pMTD_FLASH_PART_NODE    pCurPartNode;
    pMTD_FLASH_PART_NODE    pNextPartNode;

    /* clean chip list */

    for (pCurChipCfg = (pMTD_FLASH_CHIP_CFG) DLL_FIRST (&gChipList);
        pCurChipCfg != NULL; pCurChipCfg = pNextChipCfg)
        {
        for (pCurPartCfg =
            (pMTD_FLASH_PART_CFG) DLL_FIRST (&pCurChipCfg->partList);
            pCurPartCfg != NULL; pCurPartCfg = pNextPartCfg)
            {
            pNextPartCfg = (pMTD_FLASH_PART_CFG) DLL_NEXT (&pCurPartCfg->node);
            DLL_REMOVE (&pCurChipCfg->partList, &pCurPartCfg->node);
            free (pCurPartCfg);
            }

        pNextChipCfg = (pMTD_FLASH_CHIP_CFG) DLL_NEXT (&pCurChipCfg->node);
        DLL_REMOVE (&gChipList, &pCurChipCfg->node);
        free (pCurChipCfg);
        }

    /* clean MTD list */

    for (pCurMtdNode = (pMTD_DEV_NODE) DLL_FIRST (&gMtdList);
        pCurMtdNode != NULL; pCurMtdNode = pNextMtdNode)
        {
        for (pCurGrpNode =
            (pMTD_FLASH_GROUP_NODE) DLL_FIRST (&pCurMtdNode->grpList);
            pCurGrpNode != NULL; pCurGrpNode = pNextGrpNode)
            {
            for (pCurPartNode =
                (pMTD_FLASH_PART_NODE) DLL_FIRST (&pCurGrpNode->partList);
                pCurPartNode != NULL; pCurPartNode = pNextPartNode)
                {
                pNextPartNode =
                    (pMTD_FLASH_PART_NODE) DLL_NEXT (&pCurPartNode->node);
                DLL_REMOVE (&pCurGrpNode->partList, &pCurPartNode->node);
                free (pCurPartNode);
                }

            pNextGrpNode =
                (pMTD_FLASH_GROUP_NODE) DLL_NEXT (&pCurGrpNode->node);
            DLL_REMOVE (&pCurMtdNode->grpList, &pCurGrpNode->node);
            free (pCurGrpNode);
            }

        pNextMtdNode = (pMTD_DEV_NODE) DLL_NEXT (&pCurMtdNode->node);
        DLL_REMOVE (&gMtdList, &pCurMtdNode->node);
        free (pCurMtdNode);
        }
    }


