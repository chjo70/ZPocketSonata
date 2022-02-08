/* dict.h - dictionary access library */

/*
 * Copyright (c) 2009-2012 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

#ifndef INCdict_h
#define INCdict_h

#include <stdlib.h>
#include <cafe/value_type.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
DESCRIPTION:
Dictionary Library Interface.
The primary use for this is to support the phoenix language.
However, this is a pure library, so there is nothing that prevents
other projects from using it.
The data managed by this dictionary are rows of structures.  Each
structure must have at least one member, a key.  When a new
dictionary is created using cafe_dict_create() the metadata describing
the structure is given and all rows in the dictionary will use the
same structure layout.

At first glance it may seem counter intuitive to keep the keys as
part of the structure, but it seems to simplify both the
implementation of this library and the client code since very often
both the keys and the values needs to be processed, and separating
them will only lead to special handling and therefore more complex
code.

INCLUDE FILES: dict.h

SEE ALSO: value_type cafe
*/

typedef unsigned long cafe_hashval_t;

struct cafe_dict_entry {
	struct cafe_dict_entry *next;
	struct cafe_value_data *ref;
};

struct cafe_dict_struct {
	size_t nentries;
	size_t nbuckets;
	const struct cafe_value_type *type;
	struct cafe_dict_entry **buckets;
};

struct cafe_dict_iterator {
	/* All member are private to the implementation and should not
	 * be used by clients of dict. */
	size_t bucket;
	/* Number of buckets at time of iterator initialization */
	size_t nbuckets;
	struct cafe_dict_entry *next;
};


/*
 * cafe_value_copy - Copy value of type
 */
extern bool cafe_value_copy(const struct cafe_value_type *type,
			    void *base1, const void *base2,
			    const struct cafe_allocator *allocator);

/*
 * cafe_dict_create - Create new dictionary and return handle
 *
 * <dict>: handle to dictionary to create
 *
 * <dictType>: metadata for structure managed by this dictionary.
 */
extern void cafe_dict_create(struct cafe_dict_struct *dict,
			     const struct cafe_value_type *dict_type);

/*
 * cafe_dict_delete - Delete dictionary
 *
 * <dict>: handle to dictionary to delete
 */
extern void cafe_dict_delete(struct cafe_dict_struct *dict);

/*
 * cafe_dict_reset - Reset content of dictionary
 *
 * <dict>: handle to dictionary to reset
 */
extern void cafe_dict_reset(struct cafe_dict_struct *dict);

/*
 * cafe_dict_lookup - Lookup entry in dictionary, returns NULL if not
 * found, otherwise returns pointer to data
 *
 * <dict>: handle to dictionary to search
 *
 * <keys>: array of key values.  The number of keys must match the
 * dictionary type declaration passed to cafe_dict_create.
 */
extern struct cafe_value_data *cafe_dict_lookup(
	const struct cafe_dict_struct *dict,
	const cafe_any_value *keys);

/*
 * cafe_dict_get - Lookup entry in dictionary, allocates new entry if
 * not found, returns pointer to data
 *
 * <dict>: handle to dictionary to search
 *
 * <keys>: array of key values.  The number of keys must match the
 * dictionary type declaration passed to cafe_dict_create.
 */
extern struct cafe_value_data *cafe_dict_get(struct cafe_dict_struct *dict,
					     const cafe_any_value *keys);

/*
 * cafe_dict_replace - Replace or add an entry in dictionary
 *
 * <dict>: handle to dictionary to search
 *
 * <d>: data for dict entry
 */
extern struct cafe_value_data *cafe_dict_replace(struct cafe_dict_struct *dict,
						 struct cafe_value_data *d);

/*
 * cafe_dict_clear - Clear entry from dictionary
 *
 * <dict>: handle to dictionary to search
 *
 * <keys>: array of key values.  The number of keys must match the
 * dictionary type declaration passed to cafe_dict_create.
 */
extern void cafe_dict_clear(struct cafe_dict_struct *dict,
			    const cafe_any_value *keys);

/*
 * cafe_dict_remove - Remove an existing entry in dictionary
 *
 * <dict>: handle to dictionary to search
 *
 * <d>: data of dict entry to remove
 */
extern void cafe_dict_remove(struct cafe_dict_struct *dict,
			     struct cafe_value_data *d);

/*
 * cafe_dict_first - lookup and return first entry in dictionary and
 * initialize iterator, returns NULL if no more entries are available.
 *
 * <dict>: handle to dictionary to iterate over
 *
 * <iter>: opaque data structure used by cafe_dict_first and
 * cafe_dict_next iterate
 */
extern struct cafe_value_data *cafe_dict_first(const struct cafe_dict_struct *dict,
					       struct cafe_dict_iterator *iter);

/*
 * cafe_dict_next - lookup and return next entry in dictionary,
 * returns NULL if no more entries are available.
 *
 * <dict>: handle to dictionary to iterate over
 *
 * <iter>: opaque data structure used by cafe_dict_first and
 * cafe_dict_next iterate
 */
extern struct cafe_value_data *cafe_dict_next(const struct cafe_dict_struct *dict,
					      struct cafe_dict_iterator *iter);

extern cafe_hashval_t cafe_dict_hash(
	struct cafe_dict_struct *dict,
	struct cafe_value_data *d);

#define cafe_dict_count_rows(DICT) ((DICT)->nentries)

extern cafe_hashval_t cafe_hash_value(
	const struct cafe_value_type *type,
	const void *value);

extern bool cafe_same_value(
	const struct cafe_value_type *type,
	const void *base1,
	const void *base2);

#ifdef __cplusplus
}
#endif

#endif	/* INCdict_h */
