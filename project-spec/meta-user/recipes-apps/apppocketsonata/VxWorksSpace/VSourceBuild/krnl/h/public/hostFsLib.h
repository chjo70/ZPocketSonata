/* hostFsLib.h - TCF Host filesystem library header file */

/*
 * Copyright 2013-2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
04mar15,elp  Added multiclient support (US51673).
16apr14,jeg  Added autoPathMap support.
23jan14,jeg  Updated to support multiple mount points.
01aug13,jeg  Added hostFsMountPointDelete and hostFsMountPointAdd.
21jun13,jeg  Updated hostFsDevInit and added hostFsDevDelete.
31may13,rlp  Written.
*/

#ifndef __INChostFsLibh
#define __INChostFsLibh

/* includes */

#include <types.h>

#ifdef __cplusplus
extern "C" {
#endif

/* typedefs */

typedef struct 
    {
    /* device/mount point common info */
	
    BOOL 	isDev;		/* TRUE: device, FALSE: mount point */
    char *	name;		/* device/mount point name */
    char *	clientData;	/* device/mount point client specific data */
    union
	{			/* hostfs device specific structure */
	struct 
	    {
	    BOOL	autoMount;	/* TRUE: auto mount host devices */
	    BOOL 	autoReadOnly;   /* TRUE: auto mounted with READ perm */
	    BOOL 	autoPathMap;    /* TRUE: PathMap rules updated */
	    BOOL 	createdByChannel;  /* TRUE: device can be used */
	    } dev;
	struct
	    {
	    char * 	rootPath;	/* host path */
	    char * 	targetPath;	/* <device name>/<mnt name> */
	    BOOL 	readOnly;	/* TRUE: read only mount point */
            char * devId;               /* ID of hostfs device */
	    } mnt;
	} prop;
    } HOSTFS_PROP_INFO;

/* function prototypes */

extern STATUS	hostFsLibInit (void);
extern STATUS	hostFsDevInit (void * tcfChannel, char * name, BOOL autoMount,
			       BOOL autoMountRW, BOOL autoPathMap, 
			       char * clientData, char ** devId);
extern STATUS   hostFsDevDelete (void * tcfChannel);
extern STATUS 	hostFsMountPointDelete (void * tcfChannel, char * id);
extern STATUS 	hostFsMountPointAdd (void * tcfChannel, char * devid, 
			char * name, char * rootPath, BOOL readOnly, 
			char * clientData, char ** mntId, BOOL autoMnt,
		        BOOL autoPathMap);
extern STATUS 	hostFsPropertyGet (void * tcfChannel, char * id,
                                   HOSTFS_PROP_INFO * pInfo);
extern STATUS 	hostFsDevListGet (char ** devIdList, int * nbDev);
extern STATUS 	hostFsMntListGet (char * devId, char ** mntIdList, int * nbMnt);
extern STATUS   hostFsAutoMountRefresh (void * tcfChannel, char ** rootLst);
#ifdef __cplusplus
}
#endif

#endif  /* __INChostFsLibh */

