/* usrAta.c - ATA/ATAPI initialization */

/*
 * Copyright (c) 2014, 2016 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */
 
/*
modification history
--------------------
02Feb16,hma  Fix the parse of disk parameters (V7STO-576/V7STO-578)
27jan16,hma  surpport rename sata disk/partition(US74194)
18apr14,myt  move ataDeviceName[4] define to vxbSataXbd.c (VXW7-3037)
01apr14,myt  written.
*/

/*
DESCRIPTION
This file is used to provide a configuration for customer's customized device name.
This file is included by the prjConfig.c configuration file created by the
Project Manager.

NOMANUAL
*/
#include <vxWorks.h>
#include <fsMonitor.h>

/* typedefs */
typedef struct ataDevName
    {
    char    deviceName[32];
    } ATA_DEV_NAME;

/* globals */

/*******************************************************************************
*
* usrAtaConfig - configure an ATA drive name
*
* This routine configures an ATA hard disk name by customers themselves. 
*
*
* RETURNS: OK or ERROR.
*/
STATUS usrAtaConfig
    (
    int      idx,
    char    *devNames
    )
    {

    return (OK);
    }
    
#ifdef INCLUDE_SATA_DISK_NAME_CFG

#ifdef PART_MAX_ENTRIES
#undef PART_MAX_ENTRIES
#endif
#define PART_MAX_ENTRIES 128

/*
 * ataDeviceName[][0] : diskName; ataDeviceName[][1-n] : partitionNames; 
 */
extern char * ataDeviceName[4][PART_MAX_ENTRIES + 1];

#define RENAME_DISK_NAME_KEYWORD       "disk:"
#define RENAME_PARTITION_NAME_KEYWORD  "partition:"

/*******************************************************************************
*
* usrAtaPartitionRename - configure an ATA drive name
*
* This routine configures an ATA hard disk name by customers themselves. 
*
* examples: 
*    1.	Change the disk name: 
*            the partition names will be /diskname:1, /diskname:2,... 
*                 FS_NAMES_SATA_DISK0 "disk:/diskname" 
*
*           Also, in order to be compatible with old version, the following usage is provided. 
*                 FS_NAMES_SATA_DISK0 "/diskname"
*
*    2.	Change the partition names, the partition name will be /partname1, /partname2,...: 
*                FS_NAMES_SATA_DISK0 "partition:/p1,/p2,/p3"
*                the partition names would be "/p1", "/p2", "/p3", "/atan:4"
*                Here:
*                     /atan:4 - n is the port index on the board
                              - 4 is the fourth partition
*
*    3.	Change both disk and partitions names. 
*                FS_NAMES_SATA_DISK0 "disk:/diskname;partition:/p1,/p2,,/p4"
*                the partition names would be "/p1", "/p2", "diskname:3", "/p4"
*                Here:
*                     "diskname:3" - diskname is the specified disk name 
                                   - 3 is the third partition
* Note:
*      The disk and partition names should start with '/'
*      
*       
* RETURNS: OK or ERROR.
*
* \NOMANUAL
*/
STATUS usrAtaPartitionRename
    (
    int     idx,
    char    *devNames
    )
    {
    int          nameLen,i;
    char *       pDevNames;
    char *       pName;
    char *       pStart;
    char         szTmp[32] = {0};
    int          j = 0;
    int          tmpLen = 0;
    int          partIndex_offset = 1;
    
    if ((idx >= 4) || (devNames == NULL))
        return (ERROR);

    /* record the customer's customized device name */
    nameLen = strlen(devNames);
    
    if (nameLen == 0)
        return (OK);
            
        memset(szTmp,0,sizeof(szTmp));
#ifdef _WRS_CONFIG_VXBUS_LEGACY
        pDevNames = hwMemAlloc((nameLen + 1) * sizeof(char));
#else    
        pDevNames = (char*)malloc((nameLen + 1) * sizeof(char));
#endif
    if (pDevNames == NULL)
        {
        printErr("usrAtaConfig: calloc returned NULL\n");        
        return (ERROR);
        }
    
    strcpy(pDevNames, devNames);

   /*
    * NOTE: 
    * The "disk:" and "partition:" are the keywords, that are used to  
    * distinguish the disk name or partition names. 
    * Both disk and partition names begin with "/"
    * Disk name and partition names are separated by ';'
    * Partition names are separated by ","
    */
   
    /* find RENAME_DISK_NAME_KEYWORD  */
   
    tmpLen = strlen(RENAME_DISK_NAME_KEYWORD) ;
    
    pStart = pDevNames;

    /* omit the spaces before the RENAME_DISK_NAME_KEYWORD */
    
    while(' ' == *(char *)pStart)
        {
        pStart++;
        }
    
    for(j = 0; j < tmpLen; j++)
        szTmp[j] = tolower((int)pStart[j]);
    
    if (0 == memcmp (RENAME_DISK_NAME_KEYWORD, szTmp, tmpLen))
        pName = pStart + tmpLen;
    else
        pName = pStart;

    /* omit the spaces between the RENAME_DISK_NAME_KEYWORD and the disk name */

    while(' ' == *(char *)pName)
        {
        pName++;
        }
    
    if (';' == *(char *)pName) /* disk name is null */
        pName++;
        
    if ('/' != *(char *)pName) /* disk name begins with flag "/" */
        ataDeviceName[idx][0] = NULL;
    else
        ataDeviceName[idx][0] = pName;

    while((*pName != ';') && (*pName != EOS))
        pName++;
    
    if (*pName == EOS)
        return OK;
    else
        *pName = EOS;
        
    /* find the disk name , skip the ";" */
    
    pName++;        

    /* omit the spaces between the ';' and the RENAME_PARTITION_NAME_KEYWORD */
    
    while(' ' == *(char *)pName)
        {
        pName++;
        }
                
    /* find RENAME_PARTITION_NAME_KEYWORD  */
    
    memset(szTmp,0,sizeof(szTmp));
    
    tmpLen = strlen(RENAME_PARTITION_NAME_KEYWORD) ;
    
    for(j = 0; j < tmpLen; j++ )
        szTmp[j] = tolower((int)pName[j]);

    if (0 == memcmp (RENAME_PARTITION_NAME_KEYWORD, szTmp, tmpLen))
        pName = pName + tmpLen;
    else
        {
        for (i = 0; i < PART_MAX_ENTRIES; i++)
            ataDeviceName[idx][i + partIndex_offset] = NULL;
        
        return OK;      
        }

    /* omit the spaces 
     * between the RENAME_PARTITION_NAME_KEYWORD and the partition name
     */
     
    while(' ' == *(char *)pName)
        {
        pName++;
        }

    /* find partition name, should begin with "/", end with ";" */
    
    for (i = 1; i < PART_MAX_ENTRIES; i++)
        {
        if ('/' != *(char *)pName)
            ataDeviceName[idx][i] = NULL;
        else  
            ataDeviceName[idx][i] = pName;       
    
        while ((*pName != ',') && (*pName != EOS))
            pName++;

        if (*pName == EOS)                  /* Any more names? */
            {
            i++;
            break;                          /* Break if no more. */
            }
        

        *pName = EOS;                       /* NULL terminate and go again. */
        pName++;
        
        /* omit the spaces between the ',' and the partition name */
         
        while(' ' == *(char *)pName)
            {
            pName++;
            }
        }

    for (; i < PART_MAX_ENTRIES; i++)
        ataDeviceName[idx][i + partIndex_offset] = NULL;
    
    return (OK);
    }
#endif
