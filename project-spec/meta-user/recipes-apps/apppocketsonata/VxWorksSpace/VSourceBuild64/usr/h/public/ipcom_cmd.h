/*
 * Copyright (c) 2006-2013 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */
#ifndef IPCOM_CMD_H
#define IPCOM_CMD_H

/*
 ****************************************************************************
 * 1                    DESCRIPTION
 ****************************************************************************
 */
/* Helper functions for shell commands */

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

#include <ipcom_type.h>
#include <ipcom_cstyle.h>
#include <ipcom_sock.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 ****************************************************************************
 * 4                    DEFINES
 ****************************************************************************
 */

/*
 ****************************************************************************
 * 5                    TYPES
 ****************************************************************************
 */

typedef struct Ipcom_cmd_int_str_map_struct
{
    int             key;
    IP_CONST char  *str;
}
Ipcom_cmd_int_str_map;


/*
 ****************************************************************************
 * 6                    FUNCTIONS
 ****************************************************************************
 */

IP_PUBLIC IP_CONST char *
ipcom_cmd_if_flags_to_str(int flags, char *str, Ip_size_t len);

IP_PUBLIC IP_CONST char *
ipcom_cmd_if_caps_to_str(int caps, char *str, Ip_size_t len);

IP_PUBLIC IP_CONST char *
ipcom_cmd_sockaddr_to_str(struct Ip_sockaddr *sa, Ip_bool include_port, Ip_bool no_dns, char *str, Ip_size_t len);

IP_PUBLIC IP_CONST char *
ipcom_cmd_key_to_str(Ipcom_cmd_int_str_map *map, int key, char *str, Ip_size_t str_len);

IP_PUBLIC int
ipcom_cmd_str_to_key(IP_CONST Ipcom_cmd_int_str_map *map, IP_CONST char *key);

IP_PUBLIC int
ipcom_cmd_str_to_key2(IP_CONST Ipcom_cmd_int_str_map *map,
                      IP_CONST char *key,
                      int *val);


#ifdef __cplusplus
}
#endif

#endif

/*
 ****************************************************************************
 *                      END OF FILE
 ****************************************************************************
 */
