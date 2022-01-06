/*
 * Copyright (c) 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

#ifndef INCcafe_list_h
#define INCcafe_list_h

/* Type oblivious circular doubly linked list. */

#include <stddef.h>		/* offsetof */
#include <cafe/ccdiff.h>	/* compiler differences */

#ifdef __cplusplus
extern "C" {
#endif

#define CAFE_LIST_ENTRY(PTR, TYPE, FIELD) \
	((TYPE *)(((char *)PTR) - offsetof(TYPE, FIELD)))

#define CAFE_LIST_INIT(list)			\
	{&list, &list}

#define cafe_list_foreach(ptr, head) \
	for (ptr = (head)->next; ptr != head; ptr = ptr->next)

#define cafe_list_foreach_rev(ptr, head) \
	for (ptr = (head)->prev; ptr != head; ptr = ptr->prev)

#define cafe_list_foreach_safe(ptr, head, tmp)		\
	for (ptr = (head)->next, tmp = ptr->next;	\
	     ptr != head;				\
	     ptr = tmp, tmp = tmp->next)

#define cafe_list_foreach_rev_safe(ptr, head, tmp)	\
	for (ptr = (head)->prev, tmp = ptr->prev;	\
	     ptr != head;				\
	     ptr = tmp, tmp = tmp->prev)

struct cafe_list_head {
	struct cafe_list_head *next;
	struct cafe_list_head *prev;
};

static inline void cafe_list_init(struct cafe_list_head *head)
{
	head->next = head;
	head->prev = head;
}

static inline int cafe_list_is_empty(struct cafe_list_head *list)
{
	return list->next == list && list->prev == list;
}

static inline void cafe_list_remove(struct cafe_list_head *item)
{
	item->prev->next = item->next;
	item->next->prev = item->prev;
}

static inline void cafe_list_add_first(struct cafe_list_head *item,
				       struct cafe_list_head *list)
{
	item->next = list->next;
	item->prev = list;
	list->next->prev = item;
	list->next = item;
}

static inline void cafe_list_add_last(struct cafe_list_head *item,
				      struct cafe_list_head *list)
{
	item->next = list;
	item->prev = list->prev;
	list->prev->next = item;
	list->prev = item;
}

static inline void cafe_list_concat(struct cafe_list_head *item,
				    struct cafe_list_head *list)
{
	if (!cafe_list_is_empty(list)) {
		item->prev->next = list->next;
		list->next->prev = item->prev;
		item->prev = list->prev;
		list->prev->next = item;
	}
}

#ifdef __cplusplus
}
#endif	/* __cplusplus */

#endif	/* INCcafe_list_h */
