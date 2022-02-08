/* sysinfo.h - cafe configuration for target information. */

/*
 * Copyright (c) 2009-2010, 2014 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
26aug14,tle  Register system_info EP for wrlinux targets (US30550)
02apr14,tle  Add getCapabilities command providing system information (US30548)
*/

#if !defined(__sysconfig_h)
#define __sysconfig_h

#define SYSINFO_SNAPSHOT_EVENT_REF  "t[system_info.snapshot]"


struct cafe_sysconfig_info {
	/* Operating system name. */
	char *sysname;

	/* Current release level of this system. */
	char *release;

	/* Current version level of this release. */
	char *version;

	/* properties: a list of key-value pairs. */
	struct cafe_dict_struct properties;
};


struct cafe_sysconfig_property {
	char *key;
	char *value;
};


extern int sysinfo_cfg_register(void);
extern int sysinfo_cfg_unregister(void);

/*
 * Fill given struct with sysinfo properties.
 */
extern int cafe_sysinfo_get(struct cafe_sysconfig_info *sysinfo);

/*
* Released allocated field of sysinfo struct
*/
extern void cafe_sysinfo_free(struct cafe_sysconfig_info *sysinfo);

#endif  /* if !defined(__sysconfig_h) */

