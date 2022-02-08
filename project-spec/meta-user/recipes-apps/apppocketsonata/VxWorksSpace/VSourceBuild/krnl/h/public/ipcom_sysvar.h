/* ipcom_sysvar.h - IPCOM system variable library */

/*
 * Copyright (c) 2006-2013 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */
#ifndef IPCOM_SYSVAR_H
#define IPCOM_SYSVAR_H

/*
 ****************************************************************************
 * 1                    DESCRIPTION
 ****************************************************************************
 */

/*
DESCRIPTION
This library contains the public API for IPCOM system variables.
INCLUDE FILES: ipcom_cmd.h, ipcom_cstyle.h, ipcom_type.h
*/

/*
 ****************************************************************************
 * 2                    CONFIGURATION
 ****************************************************************************
 */

#include "ipcom_config.h"


/*
 ****************************************************************************
 * 3                    INCLUDE FILES
 ****************************************************************************
 */

#include <ipcom_cmd.h>
#include <ipcom_cstyle.h>
#include <ipcom_hash.h>
#include <ipcom_observer.h>
#include <ipcom_type.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 ****************************************************************************
 * 4                    DEFINES
 ****************************************************************************
 */

#if (!defined(IPCOM_KERNEL) && defined(IPCOM_USRLIB)) || defined(IPCOM_USE_REMOTE_SYSVAR)
#define ipcom_sysvar_get       ipcom_sysvar_get_usr
#define ipcom_sysvar_set       ipcom_sysvar_set_usr
#define ipcom_sysvar_unset     ipcom_sysvar_unset_usr
#define ipcom_sysvar_for_each  ipcom_sysvar_for_each_usr
#endif

#if defined(IP_WB_BUILD)
#define IP_SYSVAR(name, value, cdf_define) { name, cdf_define }
#else
#define IP_SYSVAR(name, value, cdf_define) { name, value }
#endif

/*
 ****************************************************************************
 * 5                    TYPES
 ****************************************************************************
 */

typedef struct Ipcom_sysvar_struct
{
    IP_CONST char *name;
    IP_CONST char *value;
}
Ipcom_sysvar;

typedef struct Ipcom_sysvar_entry_struct
{
    int          flags;
    int          refcount;
    const char  *name;
    const char  *value;
    /* Memory for 'name' and 'value' follows. */
}
Ipcom_sysvar_entry;

typedef struct Ipcom_sysvar_tree_struct
{
    Ipcom_hash *sysvars;    /* Hash table containing all system
                               variable for all VR:s */
    Ip_u16      vr;         /* Virtual router this sysvar tree
                               belongs to */
    int         referenced; /* Reference count of this tree */
    Ip_bool     modified;   /* Has this tree been modified since it
                               was last synchronized with persistent
                               storage */
    Ip_fd       fd_lock;    /* Used by LAS for file locking */
} Ipcom_sysvar_tree;

typedef int (*Ipcom_sysvar_for_each)(const char *name, const char *value, int flags, void *cookie);


#ifdef IPCOM_USE_SYSVAR_EXT

/*
 * Traditionally, for each component, there are two types of system global
 * variables (sysvar) supported by the stack:
 * 1) sysvar that applies globally to all interfaces
 * 2) sysvar that can be configured on a per-interface basis
 *
 * Although the Ipcom_sysvar_struct supports both type of sysvar
 * configurations, it does not provide an easy mechanism to configure the
 * interface specific sysvar especially when multiple interfaces are involved.
 * Let say, to  configure the radvd's 'MinRtrAdvInterval' for differnt
 * interfaces, user must explicitly list the desirable 'MinRtrAdvInterval'
 * value for each interface as follows:
 *
 *      {"ipnet.inet6.radvd.eth0.MinRtrAdvInterval", "10000"}
 *      {"ipnet.inet6.radvd.eth1.MinRtrAdvInterval", "20000"}
 *
 * Ipcom_sysvar_ext_struct is an extension to Ipcom_sysvar_struct created
 * specifically to handle any interface specific sysvar. User would provide
 * a list of values associated with interface(s) for a given sysvar in the
 * <param> field. The <param> field must be in the form of
 * "<ifparam>=<value>" with a '=' separated the <ifparam> and <value>. Each
 * pair of "<ifparam>=<value>" is semicolon separated. The general syntax is
 * as follows:
 *
 *     {"<sysvar name>, <sysvar ext name>,
 *      "<ifparam1>=<value1>;<ifparam2>=<value2>;..."}
 *
 * Using the 'MinRtrAdvInterval' example, user would then specify the value
 * of the 'MinRtrAdvInterval' for each interface as follows:
 *
 *      {"ipnet.inet6.radvd","MinRtrAdvInterval", "eth0=10000;eth1=20000"}
 *
 */
typedef struct Ipcom_sysvar_ext_struct
{
    IP_CONST char *name1;     /* sysvar name, if exist */
    IP_CONST char *name2;     /* sysvar name, if exist */
    IP_CONST char *param;     /* parameter(s) to configure for the sysvar */
}
Ipcom_sysvar_ext;

#endif /* IPCOM_USE_SYSVAR_EXT */


/*
 *===========================================================================
 *                  Ipnet_neigh_observer_action
 *===========================================================================
 * Description: This function will be called when the sysvar database
 *              changes.
 *              NOTE: the observer action hook is called with the sysvar
 *                    database lock held so the hook is NOT allowed to
 *                    make calls to any of the ipcom_sysvar_xxx() functions.
 * Parameters:  name - name of the sysvar
 *              value - the new value (for set operation) or IP_NULL for
 *                      unset operation.
 *              observer_ctx - user defined context specific data
 * Returns:
 *
 */
typedef void (*Ipcom_sysvar_observer_action) (const char *name,
                                              const char *value,
                                              void *observer_ctx);



/*
 ****************************************************************************
 * 6                    FUNCTIONS
 ****************************************************************************
 */

IP_GLOBAL void ipcom_sysvar_add_observer(Ipcom_observer *observer,
                                         void *observer_ctx,
                                         Ipcom_sysvar_observer_action action);
IP_GLOBAL void ipcom_sysvar_remove_observer(Ipcom_observer *observer);

IP_GLOBAL Ip_err ipcom_sysvar_set_tree(const char *name, const char *value, int flags, Ipcom_sysvar_tree *tree);

/*******************************************************************************
*
* ipcom_sysvar_get - get a system variable
*
* DESCRIPTION
* This routine gets a system variable.
*
* Parameters:
* \is
* \i <name>
* The name of the system variable to fetch.
* \i <value>
* Buffer to store the system variable in. If NULL, a buffer will be allocated
* that must be freed by the caller. If the provided buffer is too small,
* NULL will be returned and <value_size> will be updated to the length of the
* system variable.
* \i <value_size>
* Size of the value buffer
* \ie
*
* RETURNS: The string value stored under <name>, or NULL.
*
* ERRNO:
*/
IP_PUBLIC char * ipcom_sysvar_get(
				  const char *name,
				  char *value,
				  Ip_size_t *value_size
				  );



/*******************************************************************************
*
* ipcom_sysvar_getvr - get a system variable
*
* DESCRIPTION
* This routine gets a system variable.
*
* Parameters:
* \is
* \i <name>
* The name of the system variable to fetch.
* \i <value>
* Buffer to store the system variable in. If NULL, a buffer will be allocated
* that must be freed by the caller. If the provided buffer is too small,
* NULL will be returned and <value_size> will be updated to the length of the
* system variable.
* \i <value_size>
* Size of the value buffer
* \i <vr>
* Virtual router, -1 will resolve current.
* \ie
*
* RETURNS: The string value stored under <name> in the virtual router <vr>, or NULL.
*
* ERRNO:
*/
IP_PUBLIC char * ipcom_sysvar_getvr
(
    const char *name,
    char *value,
    Ip_size_t *value_size,
    int vr
);


/*******************************************************************************
*
* ipcom_sysvar_get_as_int - get a system variable as an integer
*
* DESCRIPTION
* This routine gets a system variable as an integer.
*
* Parameters:
* \is
* \i <name>
* The name of the system variable to fetch.
* \i <default_value>
* Default value returned in case the system variable is not set.
* \ie
*
* RETURNS: Integer value stored under <name> or <default_value> if not found.
*
* ERRNO:
*/
IP_PUBLIC int ipcom_sysvar_get_as_int(
				      const char *name,
				      int default_value
				      );

/*******************************************************************************
*
* ipcom_sysvar_get_as_int_vr - get a special VR system variable as an integer
*
* DESCRIPTION
* This routine gets a VR system variable as an integer.
*
* Parameters:
* \is
* \i <name>
* The name of the system variable to fetch.
* \i <default_value>
* Default value returned in case the system variable is not set.
* \i <vr>
* The VR number of the system variable belongs to.
* \ie
*
* RETURNS: Integer value stored under <name> or <default_value> if not found.
*
* ERRNO:
*/
IP_PUBLIC int ipcom_sysvar_get_as_int_vr(
				      const char *name,
				      int default_value,
				      int vr
				      );

/*
 *===========================================================================
 *                    ipcom_sysvar_get_conf
 *===========================================================================
 * Description:   Tries to get <name> configuration in three places:
 *                1) if <username) -> ipcom.users.<username>.<name>
 *                2) if <ifname> -> ipcom.if.<ifname>.<name>
 *                3) <name>
 * Parameters:
 * Returns:
 */
IP_PUBLIC char *
ipcom_sysvar_get_conf(const char *name, char *value, Ip_size_t *value_size,
                      const char *username, const char *ifname);


/*
 *===========================================================================
 *                    ipcom_sysvar_get_conf_as_int
 *===========================================================================
 * Description:
 * Parameters:
 * Returns:      Integer config value stored under 'name' or -1 if not found.
 */
IP_PUBLIC int
ipcom_sysvar_get_conf_as_int(const char *name,
                             const char *username, const char *ifname);


/*******************************************************************************
*
* ipcom_sysvar_set - set a system variable
*
* DESCRIPTION
* This routine sets a system variable.
*
* Parameters:
* \is
* \i <name>
* The name of the system variable to set.
* \i <value>
* New value for the system variable specified by <name>.
* \i <flags>
* The following flags are defined:
* \is
* \i IPCOM_SYSVAR_FLAG_OVERWRITE
* OK to overwrite sysvar.
* \i IPCOM_SYSVAR_FLAG_READONLY
* Sysvar cannot be changed.
* \i IPCOM_SYSVAR_FLAG_NOCREATE
* Not OK to create new sysvar.
* \i IPCOM_SYSVAR_FLAG_TMP
* Temporary sysvar.
* \ie
* \ie
*
* RETURNS:
* \is
* \i IPCOM_SUCCESS
* Variable was successfully updated.
* \i IPCOM_ERR_DUPLICATE
* Variable exists and IPCOM_SYSVAR_FLAG_OVERWRITE is not set.
* \i IPCOM_ERR_NO_MEMORY
* Not enough memory is available in the system to complete the operation.
* \i IPCOM_ERR_READONLY
* Variable has this flag set.
* \i IPCOM_ERR_FAILED
* Variable does not exist and IPCOM_SYSVAR_FLAG_NOCREATE flag is set.
* \ie
*
* ERRNO:
*/
IP_PUBLIC Ip_err ipcom_sysvar_set(
				  const char *name,
				  const char *value,
				  int flags
				  );


/*******************************************************************************
*
* ipcom_sysvar_setvr - set a system variable
*
* DESCRIPTION
* This routine sets a system variable.
*
* Parameters:
* \is
* \i <name>
* The name of the system variable to set.
* \i <value>
* New value for the system variable specified by <name>.
* \i <flags>
* The following flags are defined:
* \i <vr>
* Virtual router to operate in, -1 will resolve current.
* \is
* \i IPCOM_SYSVAR_FLAG_OVERWRITE
* OK to overwrite sysvar.
* \i IPCOM_SYSVAR_FLAG_READONLY
* Sysvar cannot be changed.
* \i IPCOM_SYSVAR_FLAG_NOCREATE
* Not OK to create new sysvar.
* \i IPCOM_SYSVAR_FLAG_TMP
* Temporary sysvar.
* \ie
* \ie
*
* RETURNS:
* \is
* \i IPCOM_SUCCESS
* Variable was successfully updated.
* \i IPCOM_ERR_DUPLICATE
* Variable exists and IPCOM_SYSVAR_FLAG_OVERWRITE is not set.
* \i IPCOM_ERR_NO_MEMORY
* Not enough memory is available in the system to complete the operation.
* \i IPCOM_ERR_READONLY
* Variable has this flag set.
* \i IPCOM_ERR_FAILED
* Variable does not exist and IPCOM_SYSVAR_FLAG_NOCREATE flag is set.
* \ie
*
* ERRNO:
*/
IP_PUBLIC Ip_err ipcom_sysvar_setvr
(
    const char *name,
    const char *value,
    int flags,
    int vr
);


#define IPCOM_SYSVAR_FLAG_OVERWRITE   0x01 /* Ok to overwrite sysvar */
#define IPCOM_SYSVAR_FLAG_READONLY    0x02 /* Sysvar can not be changed */
#define IPCOM_SYSVAR_FLAG_NOCREATE    0x04 /* Not ok to create new sysvar */
#define IPCOM_SYSVAR_FLAG_TMP         0x08 /* Temporary sysvar. */
#define IPCOM_SYSVAR_FLAG_MODIFIED    0x10 /* Sysvar has been modified. */
#define IPCOM_SYSVAR_FLAG_KERNEL      0x20 /* LKM sysvar */
#define IPCOM_SYSVAR_FLAG_INIT        0x40 /* Added by INIT */

/*******************************************************************************
*
* ipcom_sysvar_set0 - set a system variable
*
* DESCRIPTION
* This routine sets a system variable explicitly in vr0
*
* Parameters:
* \is
* \i <name>
* The name of the system variable to set.
* \i <value>
* New value for the system variable specified by <name>.
* \i <flags>
* The following flags are defined:
* \is
* \i IPCOM_SYSVAR_FLAG_OVERWRITE
* OK to overwrite sysvar.
* \i IPCOM_SYSVAR_FLAG_READONLY
* Sysvar cannot be changed.
* \i IPCOM_SYSVAR_FLAG_NOCREATE
* Not OK to create new sysvar.
* \i IPCOM_SYSVAR_FLAG_TMP
* Temporary sysvar.
* \ie
* \ie
*
* RETURNS:
* \is
* \i IPCOM_SUCCESS
* Variable was successfully updated.
* \i IPCOM_ERR_DUPLICATE
* Variable exists and IPCOM_SYSVAR_FLAG_OVERWRITE is not set.
* \i IPCOM_ERR_NO_MEMORY
* Not enough memory is available in the system to complete the operation.
* \i IPCOM_ERR_READONLY
* Variable has this flag set.
* \i IPCOM_ERR_FAILED
* Variable does not exist and IPCOM_SYSVAR_FLAG_NOCREATE flag is set.
* \ie
*
* ERRNO:
*/
IP_PUBLIC Ip_err ipcom_sysvar_set0(
                  const char *name,
                  const char *value,
                  int flags
);


/*******************************************************************************
*
* ipcom_sysvar_setv - set an array of values
*
* DESCRIPTION
* This routine sets an array of values.
*
* Parameters:
* \is
* \i <entries>
* Array of name/value pairs. Ends with an element where both name and value are IP_NULL.
* \i <flags>
* 'IPCOM_SYSVAR_FLAG_'<xxx> flags, which applies to all elements.
* \ie
*
* RETURNS:
* \is
* \i IPCOM_SUCCESS
* Variable was successfully updated.
* \i IPCOM_ERR_DUPLICATE
* Variable exists and IPCOM_SYSVAR_FLAG_OVERWRITE is not set.
* \i IPCOM_ERR_NO_MEMORY
* Not enough memory is available in the system to complete the operation.
* \i IPCOM_ERR_READONLY
* Variable has this flag set.
* \i IPCOM_ERR_FAILED
* Variable does not exist and IPCOM_SYSVAR_FLAG_NOCREATE flag is set.
* \ie
*
* ERRNO:
*/
IP_PUBLIC Ip_err ipcom_sysvar_setv(
				   const Ipcom_sysvar entries[],
				   int flags
				   );


#ifdef IPCOM_USE_SYSVAR_EXT
/*
 *===========================================================================
 *                    ipcom_sysvar_ext_setv
 *===========================================================================
 * Description: Atomically sets an array of values for interface-specific
 *              parameters.
 * Parameters:  entries - Array of name/ext_name/value pairs. Ends with a
 *                        element where both name and vaulue is IP_NULL.
 *              flags   - IPCOM_SYSVAR_FLAG_xxx flags, applies to all elements.
 * Returns:
 */
IP_PUBLIC Ip_err
ipcom_sysvar_ext_setv(const Ipcom_sysvar_ext entries[], int flags);
#endif /* IPCOM_USE_SYSVAR_EXT */


/*
 *===========================================================================
 *                    ipcom_sysvar_set_conf
 *===========================================================================
 * Description:
 * Parameters:
 * Returns:
 */
IP_PUBLIC Ip_err
ipcom_sysvar_set_conf(const char *name, const char *value, int flags,
                      const char *username, const char *ifname);



/*******************************************************************************
*
* ipcom_sysvar_unset - delete a system variable or range of variables
*
* DESCRIPTION
* This routine deletes a system variable or range of variables.
*
* Parameter:
* \is
* \i <name>
* Name of the system variable to delete. If the last character in the name
* is '*', all systems variables starting with <name> will be deleted.
* \ie
*
* RETURNS:
* \is
* \i IPCOM_SUCCESS
* System variable was successfully deleted.
* \i IPCOM_ERR_NOT_FOUND
* System variable does not exist.
* \i IPCOM_ERR_READONLY
* System variable is read-only.
* \i IPCOM_ERR_NO_MEMORY
* Insufficient memory available to complete the operation.
* \ie
*
* ERRNO:
*/
IP_PUBLIC Ip_err ipcom_sysvar_unset(
				    const char *name
				    );


/*******************************************************************************
*
* ipcom_sysvar_for_each - invoke callback function on system variables
*
* DESCRIPTION
* This routine calls the callback function for all matching system variables.
*
* Parameters:
* \is
* \i <name>
* Defines a filter used to determine matching system variables. All system
* variables starting with <name> will be called.
* \i <cb_func>
* The callback function to call.
* \i <cookie>
* Argument provided in callback function in addition to matching system variable.
* \ie
*
* RETURNS:
* \is
* \i IPCOM_SUCCESS
* Variable was successfully updated.
* \i IPCOM_ERR_DUPLICATE
* Variable exists and IPCOM_SYSVAR_FLAG_OVERWRITE is not set.
* \i IPCOM_ERR_NO_MEMORY
* Not enough memory is available in the system to complete the operation.
* \i IPCOM_ERR_READONLY
* Variable has this flag set.
* \i IPCOM_ERR_FAILED
* Variable does not exist and IPCOM_SYSVAR_FLAG_NOCREATE flag is set.
* \ie
*
* ERRNO:
*/
IP_PUBLIC Ip_err ipcom_sysvar_for_each(
				       const char            *name,
				       Ipcom_sysvar_for_each cb_func,
				       void                  *cookie
				       );

/*
 ****************************************************************************
 * 7                    VR0 FUNCTIONS
 ****************************************************************************
 */

IP_PUBLIC char *
ipcom_sysvar_get0(const char *name, char *value, Ip_size_t *value_size);

IP_PUBLIC int
ipcom_sysvar_get_as_int0(const char *name, int default_value);

/*
 *===========================================================================
 *                  ipcom_sysvar_get_descriptive_int0
 *===========================================================================
 * Description:
 * Parameters: name - name of the sysvar to get.
 *             default_value - will be put into 'value' if something goes
 *                             with the variable lookup.
 *             value - pointer to where the integer will be stored.
 *             map - IP_NULL or a pointer to a string to int map.
 * Returns:    0 = specified sysvar was found and successfully converted to int.
 *            <0 = sysvar not found
 *            >0 = sysvar found but was not found in the map (if map != IP_NULL),
                   the value was interpreted as a integer string representation
 */
IP_PUBLIC int
ipcom_sysvar_get_descriptive_int0(const char *name,
                                  int default_value,
                                  int *value,
                                  const Ipcom_cmd_int_str_map *map);


/*
 *===========================================================================
 *                    ipcom_sysvar_get_descriptive_int_vr
 *===========================================================================
 * Description: Returns the value of a specific sysvar in a vr as an integer.
 * Parameters:  name - name of the sysvar
 *              default_value - the value that will be loaded into "value"
 *                              if sysvar "name" does not exists.
 *              value - points to the location where the integer will be
 *                      stored
 *              map - mapping from a name to an integer value or IP_NULL
 *              vr - the vr this sysvar belongs to
 * Returns:     -1 = sysvar "name" does not exist
 *               0 = value was given by mapping name to integer via "map"
 *               1 = value was given by transforming the string value to
 *                   its corresponding integer value via ipcom_atoi().
 */
IP_PUBLIC int
ipcom_sysvar_get_descriptive_int_vr(const char *name,
                                  int default_value,
                                  int *value,
                                  const Ipcom_cmd_int_str_map *map,
                                  int vr);


#ifdef __cplusplus
}
#endif

#endif

/*
 ****************************************************************************
 *                      END OF FILE
 ****************************************************************************
 */
