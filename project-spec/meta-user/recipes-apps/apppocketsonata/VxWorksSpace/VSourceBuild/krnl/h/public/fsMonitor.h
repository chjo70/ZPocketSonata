/* fsMonitor.h - header file for the fsMonitor component */

/* 
* Copyright (c) 2005-2006, 2011, 2012 Wind River Systems, Inc. 
* 
* The right to copy, distribute, modify or otherwise make use 
* of this software may be licensed only pursuant to the terms 
* of an applicable Wind River license agreement. 
*/

/*
modification history
--------------------
01i,06dec12,ywu  Added PBR_SYS_ID_LEN Macros for all file system use
01h,14jun11,sjz  Configure device name length for the requirement WIND00190568
01g,28apr10,jxu  Added void  to prototype fsMonitorInit for removing warning
01f,21jun06,jlk  Added unmount hook stuff
01e,29sep05,rfr  Changed return type of exported functions
01d,01jul05,rfr  Added prototype for fsmNameMap()
01c,24may05,pcm  added PBR_xxx defines
01b,18may05,jlk  changed instantiator to take XBD id as well as vol. name
01a,06may05,rfr  written
*/

#ifndef __INCfsMonitorh
#define __INCfsMonitorh

#include <ioLib.h>
#include <drv/manager/device.h>
#include <vsbConfig.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
* MAX_NAME_MAP is the maximum number of characters that a name-mapping function
* may map into. Pragmatically, this is the largest pathname which may be used
* as the root path by an automatically inserted device/filesystem combination.
*/
#ifdef  _WRS_CONFIG_MAX_DEVNAME
#define MAX_NAME_MAP _WRS_CONFIG_MAX_DEVNAME
#else
#define MAX_NAME_MAP 20
#endif

/*
 * The PBR_xxx defines mark the minimum set of info required for a
 * partition boot record.  
 */

#define PBR_JMP             0x00          /* x86 jump instruction (3 bytes) */
#define PBR_SYS_ID          0x03          /* system ID string     (8 bytes) */
#define PBR_BYTES_PER_BLK   0x0b          /* bytes per block      (2 bytes) */
#define PBR_NUM_BLKS        0x20          /* # of blocks on vol   (4 bytes) */

#define PBR_SYS_ID_LEN      8             /* length of system ID string */

/* Maximum number of unmount hook functions */
#define FSM_MAX_UNMOUNT_HOOK_TABLE_ENTRIES  (4)

/*
* Not that we maintain a terminating NUL in fsmName_t. This is so we can pass it
* to functions requiring a NUL terminated string 
*/
typedef char fsmName_t[MAX_NAME_MAP+1];


typedef STATUS (*fsmProbeFunc)(device_t xbdDev);
typedef STATUS (*fsmInstFunc)(device_t xbdDev, char *volName);
typedef void (*fsmUnmountHookFunc)(DEV_HDR *);

STATUS fsMonitorInit(void);

STATUS fsmProbeInstall(fsmProbeFunc probe, fsmInstFunc inst);
STATUS fsmProbeUninstall(fsmProbeFunc probe);

STATUS fsmNameInstall(char *driver, char *volume);
STATUS fsmNameUninstall(char *driver);

STATUS fsmGetDriver(char *volume, devname_t driver);
STATUS fsmGetVolume(char *driver, fsmName_t volume);

STATUS fsmNameMap(devname_t xbdName, fsmName_t path);

STATUS fsmUnmountHookAdd (FUNCPTR);
STATUS fsmUnmountHookDelete (FUNCPTR);
void   fsmUnmountHookRun (DEV_HDR *);

#ifdef __cplusplus
}
#endif

#endif
