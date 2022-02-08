/*
 * Copyright (c) 2010-2011 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

#ifndef INC_CAFE_HASHTBL_H
#define INC_CAFE_HASHTBL_H

#ifdef __cplusplus
extern "C" {
#endif

/*
 * A hash table: efficiently maps keys to values.
 *
 * Note: neither the keys or the values are copied so their lifetime
 * must match that of the hash table instance.  NULL keys are not
 * permitted either.
 *
 * SYNOPSIS
 *
 * 1. A hash table is created with hashtbl_new().
 * 2. To insert an entry use hashtbl_insert().
 * 3. To lookup a key use hashtbl_lookup().
 * 4. To remove a key use hashtbl_remove().
 * 5. To iterate on all keys use hashtbl_iter_{init,next}().
 * 5. To clear all keys use hashtbl_clear().
 * 6. To delete a hash table instance use hashtbl_delete().
 *
 * The hash table doesn't resize itself by default, but can be
 * triggered to do so using cafe_hashtbl_autoresize_enable().
 */

struct cafe_allocator;
struct cafe_hashtbl;

struct cafe_hashtbl_iter {
	void *key;
	void *val;
	/* The remaining fields are private. */
	unsigned int pos;
	struct cafe_hashtbl_entry *entry;
};

/* Hash function. */
typedef unsigned long (*CAFE_HASHTBL_HASH_FUNC)(const void *k);

/* Equals function. */
typedef int (*CAFE_HASHTBL_EQUALS_FUNC)(const void *a, const void *b);

/* Map/Apply function. */
typedef int (*CAFE_HASHTBL_APPLY_FUNC)(const void *k, const void *v, const void *u);

/* Functions for deleting keys and values. */
typedef void (*CAFE_HASHTBL_KEY_FREE_FUNC)(void *k, void *arg);
typedef void (*CAFE_HASHTBL_VAL_FREE_FUNC)(void *v, void *arg);

/*
 * [Default] Hash function.
 */
extern unsigned long cafe_hashtbl_direct_hash(const void *k);

/*
 * [Default] Key equals function.
 *
 * Returns 1 if key "a" equals key "b".
 */
extern int cafe_hashtbl_direct_equals(const void *a, const void *b);

/* Hash functions for integer keys/values. */
extern unsigned long cafe_hashtbl_int_hash(const void *k);
extern int cafe_hashtbl_int_equals(const void *a, const void *b);

/* Hash functions for nul-terminated string keys/values. */
extern int cafe_hashtbl_string_equals(const void *a, const void *b);
extern unsigned long cafe_hashtbl_string_hash(const void *k);

/*
 * Creates a new hash table.
 *
 * @param initial_size - initial size of the table
 * @param hfunc        - function that creates a hash value from a key
 * @param hequals      - function that checks keys for equality
 *
 * Returns non-null if the table was created succesfully.
 */
extern struct cafe_hashtbl *cafe_hashtbl_new
	(
	unsigned int initial_size,
	const struct cafe_allocator *allocator,
	CAFE_HASHTBL_HASH_FUNC hashfun,
	CAFE_HASHTBL_EQUALS_FUNC hasheql
	);

/*
 * Deletes the hash table instance.
 *
 * All the keys are removed via cafe_hashtbl_clear().

 * @param h         - hash table
 * @param kfreefunc - function to delete key
 * @param kfreearg  - argument provided to kfreefunc()
 * @param vfreefunc - function to delete value
 * @param vfreearg  - argument provided to vfreefunc()
 */
extern void cafe_hashtbl_delete
	(
	struct cafe_hashtbl *h,
	CAFE_HASHTBL_KEY_FREE_FUNC kfreefunc,
	void *kfreearg,
	CAFE_HASHTBL_VAL_FREE_FUNC vfreefunc,
	void *vfreearg
	);

/*
 * Removes a key from the table, returning the associated value.
 *
 * @param h         - hash table instance
 * @param k         - key to remove
 * @param kfreefunc - key free function (maybe NULL)
 * @param kfreearg  - argument provided to kfreefunc()
 *
 * Returns the value if the key was found, otherwise NULL.
 */
extern void *cafe_hashtbl_remove
	(
	struct cafe_hashtbl *h,
	const void *k,
	CAFE_HASHTBL_KEY_FREE_FUNC kfreefunc,
	void *kfreearg
	);

/*
 * Clears all entries and reclaims memory used by each entry.
 *
 * @param kfreefunc - function to delete key
 * @param kfreearg  - argument provided to kfreefunc()
 * @param vfreefunc - function to delete value
 * @param vfreearg  - argument provided to vfreefunc()
 *
 */
extern void cafe_hashtbl_clear
	(
	struct cafe_hashtbl *h,
	CAFE_HASHTBL_KEY_FREE_FUNC kfreefunc,
	void *kfreearg,
	CAFE_HASHTBL_VAL_FREE_FUNC vfreefunc,
	void *vfreearg
	);

/*
 * Inserts a new key with associated value.
 *
 * @param h - hashtable instance
 * @param k - key to insert
 * @param v - value associated with key
 *
 * Returns 0 on success, or -1 if a new entry cannot be created.
 */
extern int cafe_hashtbl_insert
	(
	struct cafe_hashtbl *h,
	void *k,
	void *v
	);

/*
 * Lookup an existing key.
 *
 * @param h - hashtable instance
 * @param k - the search key
 *
 * Returns the value associated with key, or NULL if not found.
 */
extern void *cafe_hashtbl_lookup
	(
	struct cafe_hashtbl *h,
	const void *k
	);

/*
 * Replace value for an existing key.
 *
 * @param h - hashtable instance
 * @param k - the search key
 * @param v - new value for key
 *
 * Returns the old value associated with key, or NULL if not found.
 */
extern void *cafe_hashtbl_replace
	(
	struct cafe_hashtbl *h,
	void *k,
	void *v
	);

/*
 * Returns the number of entries in the table.
 */
extern unsigned int cafe_hashtbl_count
	(
	const struct cafe_hashtbl *h
	);

/*
 * Returns the capacity of the hash table.
 */
extern unsigned int cafe_hashtbl_capacity
	(
	const struct cafe_hashtbl *h
	);

/*
 * Apply a function to all keys in the table.
 *
 * The apply function should return 0 to terminate the enumeration
 * early.
 *
 * Returns the number of keys the function was applied to.
 */
extern unsigned int cafe_hashtbl_map
	(
	const struct cafe_hashtbl *h,
	CAFE_HASHTBL_APPLY_FUNC f,
	void *user_arg
	);

/*
 * Initialize an iterator.
 *
 * @param h - hash table instance
 * @param iter - iterator to initialize
 */
extern void cafe_hashtbl_iter_init
	(
	struct cafe_hashtbl *h,
	struct cafe_hashtbl_iter *iter
	);

/*
 * Advance the iterator.
 *
 * Returns 1 while there more entries, otherwise 0.  The key and value
 * for each entry can be accessed through the iterator structure.
 */
extern int cafe_hashtbl_iter_next
	(
	struct cafe_hashtbl *h,
	struct cafe_hashtbl_iter *iter
	);

/*
 * Enable autoresizing.
 *
 * @param h - hashtable instance
 * @param load_factor - expressed as a percentage
 *
 * Allow the table to grow when it becomes "full".  The table's
 * fullness is determined by a ratio known as its load factor.  The
 * load factor is calculated as (count / capacity).
 *
 * A value of 75% is considered to be a good tradeoff between
 * potential collisions and the amount of memory not used by the
 * table.
 */
extern void cafe_hashtbl_autoresize_enable
	(
	struct cafe_hashtbl *h,
	unsigned int load_factor
	);

/*
 * Disable autoresizing.
 *
 * @param h - hashtable instance
 */
extern void cafe_hashtbl_autoresize_disable
	(
	struct cafe_hashtbl *h
	);

/* Grow or shrink the table.
 *
 * @param h - hashtable instance
 * @param capacity - new capacity
 *
 * Returns CAFE_OK on success, CAFE_NOMEM if the table could not be allocated.
 */
extern int cafe_hashtbl_resize
	(
	struct cafe_hashtbl *h,
	unsigned int capacity
	);

#ifdef __cplusplus
}
#endif	/* __cplusplus */

#endif	/* INC_CAFE_HASHTBL_H */
