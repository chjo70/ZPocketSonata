/* 10libc_cert.cdf - VxWorks libc cert component definitions */

/*
 * Copyright (c) 2016 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history            
--------------------
27apr16,pee  created
*/

#ifdef _WRS_CONFIG_CERT_KERNEL_OBJECT
Component INCLUDE_KERNEL {
        REQUIRES +=     INCLUDE_ANSI_ASSERT \
			INCLUDE_ANSI_CTYPE \
			INCLUDE_ANSI_LONGJMP \
			INCLUDE_ANSI_STDIO \
			INCLUDE_ANSI_STDLIB \
			INCLUDE_ANSI_ABORT \
			INCLUDE_ANSI_STRTOD \
			INCLUDE_ANSI_ATOF \
			INCLUDE_ANSI_STDLIB_NUMBERS \
			INCLUDE_ANSI_STRING \
			INCLUDE_ANSI_TIME \
			INCLUDE_ANSI_ABS \
			INCLUDE_ANSI_MEMCHR \
			INCLUDE_ANSI_MEMCPY \
			INCLUDE_ANSI_MEMSET \
			INCLUDE_ANSI_MEMCMP \
			INCLUDE_ANSI_MEMMOVE \
			INCLUDE_ANSI_STRCAT \
			INCLUDE_ANSI_STRNCAT \
			INCLUDE_ANSI_STRCMP \
			INCLUDE_ANSI_STRNCMP \
			INCLUDE_ANSI_STRCPY \
			INCLUDE_ANSI_STRNCPY \
			INCLUDE_ANSI_STRLCPY \
			INCLUDE_ANSI_STRLEN \
			INCLUDE_ANSI_STRDUP \
			INCLUDE_ANSI_STRERROR \
			INCLUDE_FP_TYPE \
			INCLUDE_FLOATING_POINT \
			INCLUDE_FORMATTED_IO \
			INCLUDE_FORMATTED_OUT_BASIC \
			INCLUDE_STDIO
}
#endif

