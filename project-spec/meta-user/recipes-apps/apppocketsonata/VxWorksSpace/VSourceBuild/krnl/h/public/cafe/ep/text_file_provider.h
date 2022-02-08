/* text_file_provider.h - configuration for firing events from a text file */

/*
 * Copyright (c) 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

#if !defined(__text_file_provider_h)
#define __text_file_provider_h

#ifdef __cplusplus
extern "C" {
#endif

extern int text_file_provider_unregister(void);
extern int text_file_provider_register(void);

#ifdef __cplusplus
}
#endif	/* __cplusplus */

#endif  /* if !defined(__text_file_provider_h) */
