/*
 * Copyright (c) 2006-2013 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */
#ifndef IPCOM_STDIO_SYSLOG_H
#define IPCOM_STDIO_SYSLOG_H


/*
 ****************************************************************************
 * 1                    DESCRIPTION
 ****************************************************************************
 *
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
#include "ipcom_clibmap.h"

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
 * 6                    STANDARD FUNCTIONS
 ****************************************************************************
 */

IP_PUBLIC int ipcom_printf_syslog(const char *format, /*args*/ ...);
IP_PUBLIC int ipcom_fprintf_syslog(IP_FILE *stream, const char *format, /* args*/ ...);
IP_PUBLIC int ipcom_fputs_syslog(const char *str, IP_FILE *stream);
IP_PUBLIC void ipcom_perror_syslog(const char *s);
IP_PUBLIC int ipcom_fputc_syslog(int c, IP_FILE *stream);
IP_PUBLIC int ipcom_putc_syslog(int c, IP_FILE *stream);
IP_PUBLIC int ipcom_putchar_syslog(int c);
IP_PUBLIC Ip_size_t ipcom_fwrite_syslog(const void *ptr, Ip_size_t size, Ip_size_t nitems, IP_FILE *stream);
IP_PUBLIC int ipcom_fflush_syslog(IP_FILE *file);
IP_PUBLIC int ipcom_feof_syslog(IP_FILE *stream);
IP_PUBLIC int ipcom_ferror_syslog(IP_FILE *stream);
IP_PUBLIC void ipcom_exit_syslog(int status);


#ifdef __cplusplus
}
#endif

#endif

/*
 ****************************************************************************
 *                      END OF FILE
 ****************************************************************************
 */


