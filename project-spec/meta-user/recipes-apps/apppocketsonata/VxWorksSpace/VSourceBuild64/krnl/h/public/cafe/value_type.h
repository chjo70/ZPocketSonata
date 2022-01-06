/* value_type.h - type and value facility used by Cafe  */

/* Copyright (c) 2010-2012 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
DESCRIPTION
valueLib provides ways of managing data in both simple and complex structures on the
target.


Cafe Value Type and Data Management Interface

This library manages dynamically created types and objects created
from the types.

Valid types are:
- integer types - same as in the C language
- floating point types - same as in the C language
- structure
- array - fixed size
- dynarray - dynamic size
- string - null terminated
- blob - size + data
- dictionary (aka associative array)
- object - using accessor function to construct, destruct, copy,
  aggregate and access it


INCLUDE FILES: value_type.h

SEE ALSO: cafe, dict
*/


#ifndef INCvalue_type_h
#define INCvalue_type_h

#include <stdlib.h>
#include <stddef.h>
#include <assert.h>
#include <cafe/array.h>
#include <cafe/stdbool.h>
#include <cafe/ccdiff.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
	CAFE_TYPE_CHAR,			/* 0 */
	CAFE_TYPE_UCHAR,
	CAFE_TYPE_SHORT,
	CAFE_TYPE_USHORT,
	CAFE_TYPE_INT,
	CAFE_TYPE_UINT,			/* 5 */
	CAFE_TYPE_LONG,
	CAFE_TYPE_ULONG,
	CAFE_TYPE_LONGLONG,
	CAFE_TYPE_ULONGLONG,
	CAFE_TYPE_STRING,		/* 10 */
	CAFE_TYPE_BLOB,
	CAFE_TYPE_DICT,
	CAFE_TYPE_BOOL,
	CAFE_TYPE_TYPE,
	CAFE_TYPE_FLOAT,		/* 15 */
	CAFE_TYPE_DOUBLE,
	CAFE_TYPE_NATURE_DEF,
	CAFE_TYPE_STRUCT,
	CAFE_TYPE_ARRAY,
	CAFE_TYPE_DYNARRAY,		/* 20 */
	CAFE_TYPE_TYPEDEF,
	CAFE_TYPE_INSTANCE,
	CAFE_TYPE_FILTER
} cafe_value_type_tag;

typedef enum {
	CAFE_IDENT_TYPE,
	CAFE_IDENT_ATTR
} cafe_ident_type_tag;

typedef enum {
	CAFE_ATTR_VAR,
	CAFE_ATTR_KEY,
	CAFE_ATTR_CONST,
	CAFE_ATTR_PARAM
} cafe_attr_type_tag;

typedef enum {
	CAFE_EXPR_UVALUE,
	CAFE_EXPR_SVALUE,
	CAFE_EXPR_STRING,
	CAFE_EXPR_IDENT,
	CAFE_EXPR_TYPE,
	CAFE_EXPR_LIST,
	CAFE_EXPR_CALL,
	CAFE_EXPR_INDEX,
	CAFE_EXPR_INDEX_ARRAY,
	CAFE_EXPR_INDEX_DYNARRAY,
	CAFE_EXPR_DICT_LOOKUP,
	CAFE_EXPR_DICT_GET,
	CAFE_EXPR_DICT_CLEAR,
	CAFE_EXPR_FIELD,
	CAFE_EXPR_CAST,
	CAFE_EXPR_ADD,
	CAFE_EXPR_SUB,
	CAFE_EXPR_MUL,
	CAFE_EXPR_DIV,
	CAFE_EXPR_MOD,
	CAFE_EXPR_IADD,
	CAFE_EXPR_ISUB,
	CAFE_EXPR_DADD,
	CAFE_EXPR_DSUB,
	CAFE_EXPR_UMUL,
	CAFE_EXPR_UDIV,
	CAFE_EXPR_UMOD,
	CAFE_EXPR_SMUL,
	CAFE_EXPR_SDIV,
	CAFE_EXPR_SMOD,
	CAFE_EXPR_DMUL,
	CAFE_EXPR_DDIV,
	CAFE_EXPR_DMOD,
	CAFE_EXPR_EQ,
	CAFE_EXPR_NE,
	CAFE_EXPR_LT,
	CAFE_EXPR_LE,
	CAFE_EXPR_GT,
	CAFE_EXPR_GE,
	CAFE_EXPR_STR_EQ,
	CAFE_EXPR_STR_NE,
	CAFE_EXPR_IEQ,
	CAFE_EXPR_INE,
	CAFE_EXPR_ULT,
	CAFE_EXPR_ULE,
	CAFE_EXPR_UGT,
	CAFE_EXPR_UGE,
	CAFE_EXPR_SLT,
	CAFE_EXPR_SLE,
	CAFE_EXPR_SGT,
	CAFE_EXPR_SGE,
	CAFE_EXPR_AND,
	CAFE_EXPR_XOR,
	CAFE_EXPR_OR,
	CAFE_EXPR_ANDAND,
	CAFE_EXPR_OROR,
	CAFE_EXPR_QUEST,
	CAFE_EXPR_COLON,
	CAFE_EXPR_COMMA,
	CAFE_EXPR_NEG,
	CAFE_EXPR_NOT,
	CAFE_EXPR_COMPL,
	CAFE_EXPR_ELEMENT,
	CAFE_EXPR_ATTR,
	CAFE_EXPR_NS,
	CAFE_EXPR_VAR,
	CAFE_EXPR_ARG,
	CAFE_EXPR_TYPENAME,
	CAFE_EXPR_BUCKET_Q,
	CAFE_EXPR_BUCKET_q,
	CAFE_EXPR_BUCKET_LOG2_Q,
	CAFE_EXPR_BUCKET_LOG2_q,
	CAFE_EXPR_BUCKET_LOG10_Q,
	CAFE_EXPR_BUCKET_LOG10_q,
	CAFE_EXPR_MM_GEN,
	CAFE_EXPR_MM_SYM_RESOLVE,
	CAFE_EXPR_FLATTEN,
	CAFE_EXPR_UNSET,
	CAFE_EXPR_NORMALIZE_STACK,
	CAFE_EXPR_MINMAX
} cafe_expr_type_tag;


struct cafe_value_type;

struct cafe_vm_blob {
	size_t l;
	void *p;
};

struct cafe_vm_dynarray {
	size_t c;		/* Capacity */
	size_t l;		/* Length */
	void *p;		/* Data */
};

struct cafe_namespace {
	const struct cafe_allocator *allocator;
	struct cafe_vm_ident *children;
};

struct cafe_vm_ident {
	cafe_ident_type_tag kind;
	struct cafe_namespace *ns;
	struct cafe_vm_ident *parent;
	struct cafe_vm_ident *children;
	struct cafe_vm_ident *peer;
	struct cafe_value_type *type;
	struct cafe_value_nature_ref *natures;
	struct cafe_vm_expr *expr;
	size_t len;
	char name[1];
};

#define cafe_type_attr_foreach(attr, type)			\
	for (attr = (type)->attributes;				\
	     attr < (type)->attributes + (type)->elements;	\
	     attr++)

struct cafe_vm_attr {
	cafe_attr_type_tag kind;
	struct cafe_vm_ident *ident;
	struct cafe_value_type *type;	/* Enclosing type  */
	unsigned int index;		/* attr - attr->index == first attr */
	size_t offset;			/* Offset in value data */
};

struct cafe_vm_expr {
	cafe_expr_type_tag kind;
	struct cafe_value_type *type;	/* Result type (NULL if unresolved) */
	union {
		void *p;
		long long ll;
		unsigned long long ull;
		struct cafe_vm_ident *t;
		struct cafe_vm_expr *e;
		struct cafe_vm_attr *attr;
		struct {
			size_t l;
			char *p;
		} str;
		struct {
			struct cafe_vm_expr *l;
			struct cafe_vm_expr *r;
		} bin;
		struct {
			struct cafe_vm_expr *e;
			struct cafe_vm_expr *next;
		} elem;
	} u;
};

typedef union cafe_any_value {
	long long ll;
	unsigned long long ull;
	double d;
	char *str;
	struct cafe_value_data *ref;
	void *p;
	struct cafe_vm_blob blob;
	struct cafe_vm_blob ary;
	struct cafe_vm_dynarray dary;
} cafe_any_value;

#define alignof(TYPE) offsetof(struct { char c; TYPE val; }, val)

/* Type description */
struct cafe_value_type {
	int kind;
	unsigned int align;
	unsigned int elements;
	size_t size;
	struct cafe_vm_ident *ident;
	struct cafe_vm_attr *attributes;
	struct cafe_vm_ident *element;
	struct cafe_vm_ident *init_attr;
	struct cafe_vm_attr **keymap;
	char *type_str;
};

struct cafe_type_attr_iter {
	struct cafe_vm_attr *attrcur;
	struct cafe_vm_attr *attrend;
};

#if 0
#define cafe_attr_type(ATTR)					\
	((void)((ATTR) == (struct cafe_vm_attr *)0),		\
	 (ATTR)->ident->children->type)

#define cafe_element_type(TYPE)					\
	((void)((TYPE) == (struct cafe_value_type *)0),		\
	 (TYPE)->element->type)
#endif

extern struct cafe_vm_attr *cafe_type_first_attr(
	const struct cafe_value_type *type,
	struct cafe_type_attr_iter *iter);

extern struct cafe_vm_attr *cafe_type_next_attr(
	struct cafe_type_attr_iter *iter);

static inline
struct cafe_value_type *cafe_attr_type(const struct cafe_vm_attr *attr)
{
	assert(attr->kind == CAFE_ATTR_VAR ||
	       attr->kind == CAFE_ATTR_KEY ||
	       attr->kind == CAFE_ATTR_CONST ||
	       attr->kind == CAFE_ATTR_PARAM);
	assert(attr->ident->kind == CAFE_IDENT_ATTR);
	assert(attr->ident->children->kind == CAFE_IDENT_TYPE);

	return attr->ident->children->type;
}

static inline
struct cafe_value_type *cafe_element_type(const struct cafe_value_type *type)
{
	assert(type->kind == CAFE_TYPE_DICT ||
	       type->kind == CAFE_TYPE_ARRAY ||
	       type->kind == CAFE_TYPE_DYNARRAY ||
	       type->kind == CAFE_TYPE_TYPEDEF ||
	       type->kind == CAFE_TYPE_INSTANCE);
	assert(type->element != NULL);
	assert(type->element->kind == CAFE_IDENT_TYPE);

	return type->element->type;
}

static inline
struct cafe_value_type *cafe_base_type(const struct cafe_value_type *type)
{
	while (type &&
	       (type->kind == CAFE_TYPE_TYPEDEF ||
		type->kind == CAFE_TYPE_INSTANCE))
		type = cafe_element_type(type);
	return (struct cafe_value_type *)type;
}

extern struct cafe_vm_attr *cafe_type_attr_by_index(
	const struct cafe_value_type *type,
	size_t idx);

extern struct cafe_vm_attr *cafe_type_attr_by_name(
	const struct cafe_value_type *type,
	const char *name);


static inline
bool cafe_type_is_sint(const struct cafe_value_type *type)
{
	int kind = type->kind;
	return (kind == CAFE_TYPE_CHAR ||
		kind == CAFE_TYPE_SHORT ||
		kind == CAFE_TYPE_INT ||
		kind == CAFE_TYPE_LONG ||
		kind == CAFE_TYPE_LONGLONG ||
		kind == CAFE_TYPE_BOOL);
}


static inline
bool cafe_type_is_uint(const struct cafe_value_type *type)
{
	int kind = type->kind;
	return (kind == CAFE_TYPE_UCHAR ||
		kind == CAFE_TYPE_USHORT ||
		kind == CAFE_TYPE_UINT ||
		kind == CAFE_TYPE_ULONG ||
		kind == CAFE_TYPE_ULONGLONG);
}


static inline
bool cafe_type_is_int(const struct cafe_value_type *type)
{
	return cafe_type_is_sint(type) || cafe_type_is_uint(type);
}


static inline
bool cafe_type_is_float(const struct cafe_value_type *type)
{
	int kind = type->kind;
	return (kind == CAFE_TYPE_FLOAT ||
		kind == CAFE_TYPE_DOUBLE);
}


/* Using a struct for this to get type checking. */
struct cafe_value_data {
	struct cafe_value_type *type;	/* Type of the data */
	union {			/* Align data on largest types */
		cafe_any_value v;
		char data[sizeof(cafe_any_value)];	/* Variable size array */
	} u;
};

struct cafe_value_nature_ref {
	struct cafe_value_nature_ref *next;	/* List of natures */
	struct cafe_vm_ident *def;	/* Nature definition */
	struct cafe_vm_expr *args;	/* Arguments */
};

/*
 * cafe_namespace_create - Create namespace for cafe types
 *
 * <allocator>: allocator to use for all types in namespace
 *
 * <ns>: Pointer to resulting namespace pointer or NULL
 *
 * Returns CAFE error status.
 */
extern int cafe_namespace_create(const struct cafe_allocator *allocator,
				 struct cafe_namespace **ns);

/*
 * cafe_namespace_delete - Delete namespace and all associated content
 *
 * <ns>: namespace to delete
 */
extern void cafe_namespace_delete(struct cafe_namespace *ns);

/*
 * cafe_type_dynarray - wrap type in a dynamic array
 */
extern int cafe_type_dynarray(
	const struct cafe_value_type *type,
	struct cafe_value_type **result);

/*
 * cafe_type_parse - Build type data structure from type description string
 *
 * <fmt>: string of format: value_type*
 *
 * value_type	: value_type_ref | struct_def
 *		| builtin_type | type_def | nature_def;
 *
 * value_type_ref : simple_type | dict_type
 *		| array_type | type_ref;
 *
 * simple_type	: 'c' // char
 *		| 'C' // unsigned char
 *		| 'h' // short
 *		| 'H' // unsigned short
 *		| 'i' // int
 *		| 'I' // unsigned int
 *		| 'l' // long
 *		| 'L' // unsigned long
 *		| 'q' // long long
 *		| 'Q' // unsigned long long
 *		| '?' // bool
 *		| 'Y' // type
 *		| 's' // string
 *		| 'b' // blob
 *		| 'f' // float
 *		| 'd' // double
 *		;
 *
 * struct_def	: 'S' '[' name=qualified_ident
 *		     (',' attributes=attribute_def*
 *		     (',' natures=nature_ref*)?)? ']';
 *
 * instance	: 'P' '[' name=qualified_ident parameter_values=(',' Expression)+ ']';
 *
 * dict_type	: 'D' '[' elementType=value_type_ref ']';
 *
 * array_type	: 'a' '[' elementType=value_type_ref (',' number)? ']';
 *
 * builtin_type	: 'B' '[' type=value_type_ref ',' size=number ',' align=number ']';
 *
 * type_def	: 'T' '[' name=qualified_ident ',' type=value_type_ref
 *			  (',' natures=nature_ref*)? ']';
 *
 * type_ref	: 't' '[' name=qualified_ident ']';
 *
 * nature_def	: 'N' '[' name=qualified_ident
 *		     (',' attributes=attribute_def*
 *		     (',' natures=nature_ref*)?)? ']';
 *
 * nature_ref	: 'n' '[' name=qualified_ident attribute_values=(',' Expression)* ']';
 *
 * filter	: 'F' '[' Expression ']';
 *
 * attribute_def : 'v' '[' name=ident ',' type=value_type_ref
 *			   (',' natures=nature_ref*
 *			    (',' default=Expression)?)? ']'
 *
 *		// Key member
 *		| 'k' '[' name=ident ',' type=value_type_ref
 *			 (',' natures=nature_ref*
 *			  (',' default=Expression)?)? ']'
 *
 *		// Const (calculated) member
 *		| 'K' '[' name=ident ',' type=value_type_ref
 *			  (',' natures=nature_ref*
 *			   (',' value=Expression)?)? ']'
 *
 *		// Instance parameter
 *		| 'p' '[' name=ident ',' type=value_type_ref
 *			  (',' natures=nature_ref*
 *			   (',' default=Expression)?)? ']'
 *		;
 *
 * qualified_ident : ident ('.' ident)*
 *		;
 *
 * number	: integer ('.' [0-9]+)? (('e' | 'E') '-'? integer)?
 *		;
 *
 * integer	: '0' | [1-9] [0-9]*
 *		;
 */
extern int cafe_type_parse2(struct cafe_namespace *ns,
			    const char **fmt,
			    const char *endchars,
			    struct cafe_value_type **typep);
static inline
int cafe_type_parse(struct cafe_namespace *ns, const char *fmt,
		    struct cafe_value_type **typep)
{
	return cafe_type_parse2(ns, &fmt, NULL, typep);
}

extern int cafe_type_ref_parse(
	struct cafe_namespace *ns,
	const char **fmtp,
	struct cafe_vm_ident **identp);

extern int cafe_builtin_type(struct cafe_namespace *ns,
			     cafe_value_type_tag kind,
			     struct cafe_value_type **result);

/*
 * cafe_type_based_on - returns true if <type> is based on <base>
 */
extern bool cafe_type_based_on(const struct cafe_value_type *type,
			       const struct cafe_value_type *base);

/*
 * cafe_type_ref_str - Build value type reference string for type
 *
 * The caller is responsible to free the returned string.
 */
extern char *cafe_type_ref_str(const struct cafe_value_type *type);

/*
 * cafe_type_name_str - Build value type name string for type
 *
 * The caller is responsible to free the returned string.
 */
extern char *cafe_type_name_str(const struct cafe_value_type *type);

/*
 * cafe_type_iter_dep_types - Iterates over all types used by the provided type
 *
 * <type>: starting point
 *
 * <pre_cb>: callback that is called before recursively looking for
 * dependent types, if this functions returns true then the dependent
 * types are not included in the iteration.
 *
 * <post_cb>: callback that is called after recursively looking for
 * dependent types.
 *
 * <client_arg>: opaque argument passed to <pre_cb> and <post_cb>
 */
extern void cafe_type_iter_dep_types(
	struct cafe_value_type *type,
	bool (*pre_cb)(struct cafe_value_type *, void *),
	void (*post_cb)(struct cafe_value_type *, void *),
	void *client_arg);

/*
 * cafe_value_create - Create object based on value type
 *
 * <type>: pointer to type of object
 *
 * <data>: pointer to resulting data or NULL if error
 */
extern int cafe_value_create2(struct cafe_value_type *type,
			      const struct cafe_vm_expr *expr,
			      struct cafe_value_data **data);
static inline
int cafe_value_create(struct cafe_value_type *type,
		      struct cafe_value_data **data)
{
	return cafe_value_create2(type, NULL, data);
}

/*
 * cafe_value_delete - Delete object
 *
 * <type>: pointer to type of object
 *
 * <p>: pointer to object
 */
extern void cafe_value_delete(struct cafe_value_data *p);

/*
 * cafe_value_clear - Clear object
 *
 * <p>: pointer to object
 */
extern void cafe_value_clear(struct cafe_value_data *p);


/*
 * cafe_value_load_type - Load type from memory to value
 *
 * <type>: type to load
 *
 * <base>: pointer to data in memory
 *
 * <value>: value to load into
 */
extern void cafe_value_load_type(const struct cafe_value_type *type,
				 const void *base,
				 cafe_any_value *value);

/*
 * cafe_value_store_string - store string to memory
 *
 * <dest>: pointer to memory to store value
 *
 * <src>: value to store
 *
 * <allocator>: memory allocator
 */
extern int cafe_value_store_string(char **dest,
				   const char *src,
				   const struct cafe_allocator *allocator);

/*
 * cafe_value_store_blob - store blob to memory
 *
 * <dest>: pointer to destination
 *
 * <src>: value to store
 *
 * <allocator>: memory allocator
 */
extern int cafe_value_store_blob(struct cafe_vm_blob *dest,
				 const struct cafe_vm_blob *src,
				 const struct cafe_allocator *allocator);

/*
 * cafe_value_store_type - store type from value to memory
 *
 * <type>: type to load
 *
 * <base>: pointer to memory to store value
 *
 * <value>: value to store
 *
 * <allocator>: memory allocator
 */
extern int cafe_value_store_type(const struct cafe_value_type *type,
				 void *base,
				 const cafe_any_value *value,
				 const struct cafe_allocator *allocator);

/*
 * cafe_value_store - Store a value into named field
 *
 * <type>: pointer to type of data
 *
 * <data>: pointer to data
 *
 * <name>: pointer to name of field
 *
 * <value>: pointer to value to store
 *
 * For now this function only supports storing into a a direct field
 * in a struct.  In the future we can enhance this to allow name to be
 * a '.' separated list of fields perhaps also have a syntax for array
 * and dict looks up, if needed.
 */
extern int cafe_value_store(const struct cafe_value_type *type, void *data,
			    const char *name, const cafe_any_value *value,
			    const struct cafe_allocator *allocator);

/*
 * cafe_find_nature_str - find nature associated with identifier
 *
 * <ident>: identifier to search
 *
 * <nature_str>: value type string of nature to look for
 *
 * returns pointer to nature reference if found or NULL
 */
extern const struct cafe_value_nature_ref *cafe_find_nature_str(
	const struct cafe_vm_ident *ident,
	const char *nature_str);

/*
 * cafe_vm_dynarray_set_size - set size of dynamic array
 *
 * returns CAFE_OK on okay
 *
 * Release all memory when size is 0
 */
extern int cafe_vm_dynarray_set_size(struct cafe_vm_dynarray *array,
				     size_t size, const struct cafe_value_type *type);

/*
 * cafe_vm_dynarray_elem_get - Get an element from a dynamic array.
 *
 * Returns a pointer to the element at INDEX, growing the array if
 * necessary.  If successful *RESULT is a pointer to the element.
 *
 * RETURNS: CAFE_OK on success, or CAFE_NOMEM on error.
 */
extern int cafe_vm_dynarray_elem_get
	(
	struct cafe_vm_dynarray *array,
	const struct cafe_value_type *type,
	size_t index,
	void **result
	);

typedef enum {
	CAFE_EXPR_RESOLVE_LOAD,
	CAFE_EXPR_RESOLVE_STORE,
	CAFE_EXPR_RESOLVE_CLEAR
} cafe_expr_resolve_mode_t;

struct cafe_value_context {
	struct cafe_value_context *parent;
	const struct cafe_allocator *allocator;
	struct cafe_namespace *ns;
	struct cafe_ep_inst *inst;
	struct cafe_vm_ident *type;
	struct cafe_value_type *curobj_type;
	struct cafe_event_descr *event;
	struct cafe_event_descr *trigger_type;
	unsigned int *odmap;
	cafe_expr_resolve_mode_t expr_resolve_mode;

	struct cafe_vm_expr *(*resolve_expr_type)(
		struct cafe_value_context *context,
		struct cafe_vm_expr *e);
	struct cafe_vm_expr *(*resolve_expr_arg)(
		struct cafe_value_context *context,
		struct cafe_vm_expr *e);
	bool (*valid_mm_sym_resolve_type)(
		const struct cafe_value_context *context,
		const struct cafe_value_type *t);
};

extern struct cafe_value_context *cafe_value_context_create(
	const struct cafe_allocator *allocator);

extern struct cafe_value_context *cafe_value_context_add(
	struct cafe_value_context *context);

extern struct cafe_value_context *cafe_value_context_delete(
	struct cafe_value_context *context);

extern struct cafe_vm_expr *cafe_param_value_get(
	const struct cafe_value_type *type,
	const char *param_name);

/*
 * Create new value type representing a structure with the given name,
 * attributes, and natures.
 */
extern int cafe_value_struct_create(const char *name, struct cafe_namespace *ns,
				    struct cafe_array *attr_list,
				    struct cafe_value_nature_ref *natures,
				    struct cafe_value_type **type);

/*
 * Given an attribute describing an existing struct-type's member, add a new
 * entry to the given list representing an attribute with the same name and
 * type.
 */
extern int cafe_value_attr_list_add(struct cafe_vm_attr *attr,
				    struct cafe_array *list);

/*
 * Add a new entry to the given attribute list.  The new entry will have the
 * given kind, ident, natures, and name.
 */
extern int cafe_value_attr_list_add_ident(cafe_attr_type_tag kind,
					  struct cafe_vm_ident *ident,
					  const char *name,
					  struct cafe_value_nature_ref *natures,
					  struct cafe_array *list);
#ifdef __cplusplus
}
#endif

#endif	/* INCvalue_type_h */
