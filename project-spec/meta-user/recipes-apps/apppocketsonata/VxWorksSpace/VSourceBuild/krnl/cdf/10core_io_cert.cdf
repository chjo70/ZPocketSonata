/* 00core_io.cdf - VxWorks Core I/O cert component definitions */

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
        REQUIRES +=     INCLUDE_POSIX_FTRUNC \
			INCLUDE_TTY_DEV \
			INCLUDE_POSIX_FS \
			INCLUDE_IO_BASIC \
			INCLUDE_IO_FILE_SYSTEM \
			INCLUDE_IO_POSIX \
			INCLUDE_IO_RTP \
			INCLUDE_TYLIB \
			INCLUDE_SELECT
}
#endif


