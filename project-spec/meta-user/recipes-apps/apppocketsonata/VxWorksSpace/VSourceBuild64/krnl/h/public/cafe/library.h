/* library.h - public api for general cafe library functions */

/*
 * Copyright (c) 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

#ifndef INClibrary_h
#define INClibrary_h

#ifdef __cplusplus
extern "C" {
#endif

extern int cafe_version_number
	(
	void
	);

extern const char *cafe_version_string
	(
	void
	);

extern const char *cafe_strerror
	(
	int error_number	/* predefined Cafe error number */
	);

extern int cafe_lib_init
	(
	void
	);

extern void cafe_lib_release
	(
	void
	);

#ifdef __cplusplus
}
#endif	/* __cplusplus */

#endif	/* INClibrary_h */
