/*
 * Copyright (c) 2006-2013 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */
#ifndef IPCOM_STRLIB_H
#define IPCOM_STRLIB_H

/*
 ****************************************************************************
 * 1                    DESCRIPTION
 ****************************************************************************
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

#include "ipcom_type.h"
#include "ipcom_cstyle.h"

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

/*
 ****************************************************************************
 * 6                    FUNCTIONS
 ****************************************************************************
 */

/*
 *===========================================================================
 *                    ipcom_parse_argstr
 *===========================================================================
 * Description:
 *  Parses a string to an argc/argv array. Arguments containing a space must
 *  be enclosed by ' characters, e.g. 'a space'.
 *
 * Parameters:
 *  arg_str: the string to parse. This string is modified.
 *  argc:    updated to hold the number of arguments in argv
 *  argv:    an array of pointers to the arguments. The pointers
 *           actually points into the modified arg_str. The
 *           array is NULL terminated.
 * Returns:
 *  IPCOM_ERR_FAILED - Failed to parse the string.
 *  IPCOM_ERR_INVALID_ARG - Badly matched escape characters.
 *  IPCOM_SUCCESS    - The string has been successfully parsed.
 *
 *  If successful, the argv array must be freed by the caller.
 *  If failed, the values of argc and argv are undefined.
 */
IP_PUBLIC Ip_err ipcom_parse_argstr(char *arg_str, int *argc, char ***argv);
IP_PUBLIC char  *ipcom_str_in_list(char *str, char *list);

#ifdef __cplusplus
}
#endif

#endif

/*
 ****************************************************************************
 *                      END OF FILE
 ****************************************************************************
 */

