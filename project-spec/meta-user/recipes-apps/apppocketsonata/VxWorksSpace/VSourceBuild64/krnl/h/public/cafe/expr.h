/* expr.h - Cafe expression handling */

/* Copyright (c) 2010-2012 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

#ifndef INCcafe_expr_h
#define INCcafe_expr_h

#include <cafe/types.h>

#ifdef __cplusplus
extern "C" {
#endif

struct mm_inst_data;

struct cafe_expr_tmp_dynarray;

struct cafe_expr_eval_context {
	const struct cafe_allocator *allocator;
	struct cafe_expr_tmp_dynarray *tmpdynarray;
	struct cafe_vm_dynarray tmpblob;
	struct cafe_event_descr *event;
	void **event_data;
	struct mm_inst_data *mm_inst;
	int (*mm_gen)(
		struct cafe_expr_eval_context *context,
		unsigned long long address_space_uid,
		unsigned long long *current_gen);
	int (*mm_sym_resolve)(
		struct cafe_expr_eval_context *context,
		const struct cafe_vm_dynarray *stack,
		unsigned long long address_space_uid,
		unsigned long long current_gen,
		const struct cafe_value_type *result_type,
		struct cafe_vm_dynarray *result);
};

/*
 * cafe_expr_parse - parse an expression.
 *
 * Expression :
 * 	TernaryExpression
 * ;
 *
 * TernaryExpression :
 * 	OrExpression ('?' OrExpression ':' TernaryExpression)?
 * ;
 *
 * OrExpression :
 * 	 AndExpression ('||' AndExpression)*
 * ;
 *
 * AndExpression :
 * 	BitOrExpression ('&&' BitOrExpression)*
 * ;
 *
 * BitOrExpression :
 * 	BitXorExpression ('|' BitXorExpression)*
 * ;
 *
 * BitXorExpression :
 * 	 BitAndExpression ('^' BitAndExpression)*
 * ;
 *
 * BitAndExpression :
 * 	EqualityExpression ('&' EqualityExpression)*
 * ;
 *
 * EqualityExpression :
 * 	RelationalExpression (('=='|'!=') RelationalExpression)*
 * ;
 *
 * RelationalExpression :
 * 	ShiftExpression (('>='|'<='|'>'|'<') ShiftExpression)*
 * ;
 *
 * ShiftExpression :
 * 	AdditiveExpression (('<<'|'>>') AdditiveExpression)*
 * ;
 *
 * AdditiveExpression :
 * 	MultiplicativeExpression (('+'|'-') MultiplicativeExpression)*
 * ;
 *
 * MultiplicativeExpression :
 * 	UnaryExpression (('*'|'/') UnaryExpression)*
 * ;
 *
 * UnaryExpression :
 * 	'-' UnaryExpression |
 * 	'+' UnaryExpression |
 * 	'!' UnaryExpression |
 * 	'~' UnaryExpression |
 * 	cast=('(' TypeRef ')') UnaryExpression |
 * 	paren=('(' Expression ')') |
 *	InfixExpression
 * 	;
 *
 * InfixExpression :
 * 	PrimaryExpression (
 * 	    (field='.' ident) |
 * 	    (index='[' Expression ']') |
 * 	    (call='(' (Expression (',' Expression)*)? ')')
 * 	)* |
 * 	list=('[' (Expression (',' Expression)*)? ']')
 * ;
 *
 * PrimaryExpression :
 *   (LONG| HEX| OCTAL) |
 *   REAL |
 *   STRING |
 *   ident |
 *   curobj='@' |
 *   TypeRef
 * ;
 *
 * TypeRef :
 * 	'{' value_type_ref '}'
 * ;
 *
 * Defined functions:
 *
 * - typename(expression)
 *
 *   Returns the type name of <expression>.
 *
 * - bucket(value, bucketSize)
 * - bucket_log2(value, numBuckets)
 * - bucket_log10(value, numBuckets)
 *
 *   Supported types of value are signed and unsigned integers.
 *   Floating point support can be added when needed.
 *
 *   The numBuckets argument is an integer specifying how many
 *   sub-buckets to create within each integer exponent range.  If
 *   numBuckets is 0 it has the same meaning as 1.  If it is positive
 *   then the sub-buckets are distributed linearly and if it is
 *   negative they are distributed logarithmically.
 *
 *   Negative values are supported with logarithmic bucket functions
 *   and will bucketize as the corresponding positive value, i.e. the
 *   absolute value, except that the bucket start is the negative
 *   value of the end of the corresponding positive bucket.  Examples:
 *
 *     bucket_log2(500, 1) -> 256
 *     bucket_log2(({q})-500, 1) -> -512
 *     bucket_log10(1234, 1) -> 1000
 *     bucket_log10(({q})-1234, 1) -> -10000
 *
 *   The value 0 is supported with logarithmic bucket functions by
 *   creating a separate bucket for these values.
 *
 *   For now numBuckets with negative values are not supported, so it
 *   behaves as if it was set to 1.
 *
 * - mm_gen(memory-space-id)
 *
 *   Returns the current generation number for the argument memory
 *   space id.  The generation number is of type Q and is needed to do
 *   symbol resolution.
 *
 * - mm_sym_resolve(stack, memory-space-id, generation-number, result-type)
 *
 *   Resolve the <stack> in the context of the given memory space's
 *   memory map at the time of the given generation number.  Returns a
 *   dynamic array of type <result-type>.  The <stack> parameter
 *   should have a value type of "a[Q]".
 *
 *   The <result-type> should be of type struct with one or more of
 *   the following fields:
 *
 *   - v[object_name,s]
 *
 *     The path of the executable, shared library, object files, etc
 *     mapped at the corresponding stack address.
 *
 *   - v[object_address,Q]
 *
 *     The offset within the executable, shared library, object files,
 *     etc.
 *
 *   - v[symbol_name,s]
 *
 *     The symbol name of the corresponding stack address.
 *
 *   - v[symbol_offset,Q]
 *
 *     The offset from the start of the symbol.
 *
 *   - v[stack_index,Q]
 *
 *     The index/level of the stack.
 *
 *   - v[original_address,Q]
 *
 *     The original address from the stack.
 *
 *   Additional <result-type> fields will be added over time.  For example:
 *
 *   - v[source_name,s]
 *
 *     The path of the source file mapped at the corresponding stack
 *     address.
 *
 *   - v[line_number,Q]
 *
 *     The line number within the source file.  A value of 0 indicates
 *     that no line number is specified.
 *
 *   - v[column_number,Q]
 *
 *     The column number within the source line number.  A value of 0
 *     indicates that no column number is specified.
 *
 * - mod(expr1, expr2)
 *
 *   expr1 modulo expr2
 *
 * - flatten()
 *
 *   Special marker used for the aggregator
 *
 */
extern int cafe_expr_parse(
	const struct cafe_value_context *context,
	const char **fmtp,
	struct cafe_vm_expr **result);

extern int cafe_expr_list_parse(
	const struct cafe_value_context *context,
	const char **fmtp,
	struct cafe_vm_expr **result);

extern int cafe_expr_var(
	struct cafe_value_context *context,
	struct cafe_value_type *type,
	void *p,
	struct cafe_vm_expr **result);

extern int cafe_expr_arg(
	const struct cafe_value_context *context,
	struct cafe_value_type *type,
	unsigned int argno,
	struct cafe_vm_expr **result);

extern int cafe_expr_field(
	struct cafe_value_context *context,
	struct cafe_vm_expr *e,
	struct cafe_vm_attr *attr,
	struct cafe_vm_expr **result);

extern int cafe_expr_unset(
	struct cafe_value_context *context,
	struct cafe_value_type *type,
	struct cafe_vm_expr **result);

/*
 *  Builds an expression which executes a symbol resolution action.
 */
extern int cafe_expr_symresolve(
	const struct cafe_value_context *context,
	struct cafe_vm_expr *raw_stack_arg,
	struct cafe_vm_expr *address_space_arg,
	struct cafe_vm_expr *mm_generation_arg,
	struct cafe_value_type *result_type,
	struct cafe_vm_expr **result);

extern int cafe_expr_cast(
	struct cafe_value_context *context,
	struct cafe_vm_expr *e,
	struct cafe_value_type *type,
	struct cafe_vm_expr **result);

/*
 * cafe_expr_free - free an expression.
 */
extern void cafe_expr_free(
	const struct cafe_allocator *allocator,
	struct cafe_vm_expr *r);

extern struct cafe_vm_expr *cafe_expr_new_list(
	const struct cafe_allocator *allocator);

extern struct cafe_vm_expr *cafe_expr_new_element(
	const struct cafe_allocator *allocator,
	struct cafe_vm_expr *e);

/*
 * cafe_expr_resolve - resolve types of expression.
 */
struct cafe_vm_expr *cafe_expr_resolve(
	struct cafe_value_context *context,
	struct cafe_vm_expr *e);
struct cafe_vm_expr *cafe_expr_resolve_for_type(
	struct cafe_value_context *context,
	struct cafe_vm_expr *e,
	struct cafe_value_type *type);

/*
 * cafe_expr_copy - copy an expression.
 */
extern struct cafe_vm_expr *cafe_expr_copy(
	const struct cafe_allocator *allocator,
	const struct cafe_vm_expr *expr);

/*
 * cafe_expr_same - test of two expressions are the same.
 */
extern int cafe_expr_same(
	const struct cafe_vm_expr *expr1,
	const struct cafe_vm_expr *expr2);

static inline
bool cafe_expr_is_iconst(const struct cafe_vm_expr *e)
{
	return (e->kind == CAFE_EXPR_UVALUE ||
		e->kind == CAFE_EXPR_SVALUE);
}

static inline
unsigned long long cafe_expr_to_ull(const struct cafe_vm_expr *e)
{
	if (e->kind == CAFE_EXPR_UVALUE)
		return e->u.ull;
	if (e->kind == CAFE_EXPR_SVALUE)
		return e->u.ll;
	return 0;
}

static inline
long long cafe_expr_to_ll(const struct cafe_vm_expr *e)
{
	if (e->kind == CAFE_EXPR_UVALUE)
		return e->u.ull;
	if (e->kind == CAFE_EXPR_SVALUE)
		return e->u.ll;
	return 0;
}

#define cafe_expr_eval_context_create(CONTEXT, ALLOCATOR)	\
	((CONTEXT)->allocator = (ALLOCATOR),			\
	 (CONTEXT)->tmpdynarray = NULL,				\
	 (CONTEXT)->tmpblob.l = 0,				\
	 (CONTEXT)->tmpblob.c = 0,				\
	 (CONTEXT)->tmpblob.p = NULL,				\
	 (CONTEXT)->event = NULL,				\
	 (CONTEXT)->event_data = NULL,				\
	 (CONTEXT)->mm_inst = NULL,				\
	 (CONTEXT)->mm_gen = NULL,				\
	 (CONTEXT)->mm_sym_resolve = NULL)

extern void cafe_expr_eval_context_delete(
	struct cafe_expr_eval_context *context);

extern int cafe_expr_eval_value(
	struct cafe_expr_eval_context *context,
	const struct cafe_vm_expr *e,
	cafe_any_value *result);

extern int cafe_expr_eval_addr(
	struct cafe_expr_eval_context *context,
	const struct cafe_vm_expr *e,
	cafe_any_value *result);

extern int cafe_tmp_dynarray_new(
	struct cafe_expr_eval_context *ctx,
	struct cafe_value_type *type,
	struct cafe_vm_dynarray **result);

extern int cafe_tmp_blob_new(
	struct cafe_expr_eval_context *ctx,
	struct cafe_vm_blob *blob);

extern int cafe_tmp_string_new(
	struct cafe_expr_eval_context *ctx,
	char *str);

extern void cafe_tmp_dynarray_clean(
	struct cafe_expr_eval_context *ctx);

extern void cafe_tmp_blob_clean(
	struct cafe_expr_eval_context *ctx);

extern int cafe_tmp_blob_persist(
	struct cafe_expr_eval_context *ctx,
	struct cafe_vm_blob *blob);

extern int cafe_tmp_string_persist(
	struct cafe_expr_eval_context *ctx,
	char **str);

#ifdef __cplusplus
}
#endif

#endif	/* INCcafe_expr_h */
