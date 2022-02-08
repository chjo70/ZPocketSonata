/* cxa_atexit.h - private header describing the atexit stack */

/*
 * Copyright (c) 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement. No license to Wind River intellectual property rights
 * is granted herein. All rights not licensed by Wind River are reserved
 * by Wind River.
 */

/*
modification history
--------------------
01,28sep10,gvm   split from cxa_atexit.c
*/

#ifndef __INCcxaatexith
#define __INCcxaatexith

typedef struct atexit_node {
	void (*fn)(void *);
	void * data;
	void * dso_handle;
	struct atexit_node * next;
} atexit_node;

#endif /* __INCcxaatexith */
