/* device.h - Removable device header file */

/* 
 * Copyright (c) 2004-2006, 2011-2013 Wind River Systems, Inc. 
 * 
 * The right to copy, distribute, modify, or otherwise make use 
 * of this software may be licensed only pursuant to the terms 
 * of an applicable Wind River license agreement. 
 */

/*
modification history
--------------------
01g,26sep13,d_l  add devGetByName declaration. (WIND00432646)
01f,29nov12,xwu  Coverity isuue of COMMON.
01e,14jun11,sjz  Configure device name length for the requirement WIND00190568
01d,29apr10,pad  Moved extern C statement after include statements.
01c,12apr06,dee  SPR 119990, WIND00037359 - add cplusplus constructs
01b,20apr05,rfr  Added devName() function
01a,25mar05,rfr  Removed prototype eventing system.
*/

#ifndef __INCdeviceh
#define __INCdeviceh

#include <types.h>
#include <vsbConfig.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef  _WRS_CONFIG_MAX_DEVNAME
#define MAX_DEVNAME _WRS_CONFIG_MAX_DEVNAME
#else
#define MAX_DEVNAME 10
#endif

#define NULLDEV 0

#define DV_TYPE_NONE  0
#define DV_TYPE_XBD   1

struct device;

typedef uint32_t device_t;
typedef char devname_t[MAX_DEVNAME + 1];

struct device 
{
    device_t dv_dev;		/* This device's device_t */
    int dv_type;		/* DV_TYPE_XBD, etc */
    devname_t dv_xname;		/* The name of this device */
    int dv_error;		/* insert/delete errors */
};

/* 
* These are functions to be called by device drivers that conform to this 
* interface. 
*/

int devAttach(struct device *dev, const char *name, int type, device_t *result);
STATUS devDetach(struct device *dev);

/*
* This is the initialization function for the device infrastructure. It must be 
* called before any other device infrastructure calls
*/

STATUS devInit(uint16_t ndevs);

/* 
* These functions manage the mapping between device_t and struct device *.
* Every call to devMap() should be paired with a call to devUnmap().
*/

struct device *devMap(device_t dev);
int devUnmap(struct device *);

STATUS devName(device_t dev, devname_t name);

device_t devGetByName(char *deviceName);

#ifdef __cplusplus
}
#endif

#endif /* __INCdeviceh */
