/*
 * Copyright (c) 2010-2011 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/* The parser facilitates running Cafe instruments using a simple
 * language that is syntactically similar to a unix shell.
 *
 * DEFINITIONS:
 *
 * blank  - space or tab
 * word   - any sequence of characters not including <blank>.
 *
 * QUOTING:
 *
 * Quoting is used to remove the meaning of <blank> characters.  There
 * is only one quote character, namely double-quote (") and these can
 * be escaped by a backslash (\).  For example:
 *
 *   table "S[task_tbl,k[tid,i,n[cafe.LABEL,\"Task Table\"]]]"
 *
 * COMMENTS:
 *
 * The comment character is hash (#), and comments run until the
 * newline character.
 *
 * POSITIONAL PARAMETERS:
 *
 * Positional parameters are represented using $<digit>.  Positional
 * parameters are assigned values from the script's arguments.
 *
 * GRAMMAR:
 *
 * A script file is a line orientated sequence of commands where each
 * line is a sequence of blank-separated words; the first word
 * represents the command and the remaining words its arguments.
 *
 * The formal grammar is:
 *
 *      script ::= cmds.
 *
 *      cmds ::=.
 *      cmds ::= cmds NL.
 *      cmds ::= cmds cmd NL.
 *
 *      cmd ::= 'connect' ep_ident TO ep_ident.
 *      cmd ::= 'contribute' ep_ident TO ep_ident.
 *      cmd ::= 'create' ep_ident optional_name.
 *      cmd ::= 'source' filename source_arguments.
 *      cmd ::= 'typedef' value_type_def_or_ref.
 *      cmd ::= 'set' workarea_field value.
 *      cmd ::= 'enable' 'for' ep_ident.
 *      cmd ::= 'enable' value_type_list.
 *      cmd ::= 'table' value_type.
 *      cmd ::= 'action' words.
 *
 *      optional_name ::=.
 *      optional_name ::= 'as' ep_ident.
 *
 *      source_arguments ::=.
 *      source_arguments ::= source_arguments word.
 *
 *      value_type_list ::= value_type.
 *      value_type_list ::= value_type_list value_type.
 *
 *      ep_ident ::= word.
 *      filename ::= word.
 *      value ::= word.
 *      value_type ::= word.
 *      workarea_field ::= word.
 *
 *      words ::= word.
 *      words ::= words word.
 *
 *      word ::= WORD|STRING.
 *
 * The semantic ordering or interleaving of commands is very loose;
 * semantic checks are done once the script parses.  The following
 * constraints are applied:
 *
 *	all 'set' commands must follow a 'create' command
 *	all 'enable' commands must follow a 'create' command
 *
 *	all 'table' commands must follow a 'create cafe_aggregator' command
 *	all 'action' commands must follow a 'create cafe_aggregator' command
 */

#ifndef INCscript_parser_h
#define INCscript_parser_h

#include <stdarg.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Opaque types. */
struct cafe_instrument;
struct cafe_allocator;
struct cafe_script;

typedef void (*CAFE_SCRIPT_ERROR_HANDLER)
	(
	struct cafe_script *script,
	const void *client_data,
	const char *filename,
	int line_number,
	const char *fmt,
	va_list ap
	);

extern int cafe_script_parse_from_file
	(
	const struct cafe_allocator *allocator,
	FILE *stream,
	const char *filename,
	int argc,
	const char *argv[],
	CAFE_SCRIPT_ERROR_HANDLER error_handler,
	void *error_handler_client_data,
	struct cafe_instrument **result
	);

extern int cafe_script_parse_from_string
	(
	const struct cafe_allocator *allocator,
	const char *str,
	int argc,
	const char *argv[],
	CAFE_SCRIPT_ERROR_HANDLER error_handler,
	void *error_handler_client_data,
	struct cafe_instrument **result
	);

#ifdef __cplusplus
}
#endif	/* __cplusplus */

#endif	/* INCscript_parser_h */
