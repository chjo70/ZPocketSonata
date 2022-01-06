/* Copyright (c) 2010-2012 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */


#ifndef __value_print_h
#define __value_print_h

#include <stdlib.h>
#include <stddef.h>
#include <cafe/stdio.h>		/* for FILE */
#include <cafe/value_type.h>
#include <cafe/stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

struct cafe_value_print_options {
	bool include_private;	/* Include private fields */
	bool field_names;	/* Print field names */
	unsigned int radix;	/* Radix for integers (0=default,
				   10=decimal,16=hex) */
	int field_width;	/* Number of characters in field
				 * (-1=no padding, 0=default width */
	bool type_name;		/* Print type name */
};

#define CAFE_VALUE_PRINT_OPTIONS_INIT { false, false, 0, -1, 0 }

/*
 * cafe_value_print - Print the given value using a value-specific format
 *
 * <out>: output file stream
 *
 * <type>: pointer to type of data
 *
 * <p>: pointer to data
 *
 * <options>: print formatting options
 */
extern void cafe_value_print(FILE *out, const struct cafe_vm_ident *attr,
			     const struct cafe_value_type *type,
			     const char *p,
			     const struct cafe_value_print_options *options);


#if !defined(NDEBUG)
extern void value_type_print(const char *name,
			     const struct cafe_value_type *vt,
			     unsigned int indent_lvl);
#endif

#ifdef __cplusplus
}
#endif

#endif
