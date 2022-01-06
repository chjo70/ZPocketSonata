/* vx_list.h - simple circular doubly-linked list type and macros */

#ifndef VX_LIST_H
#define VX_LIST_H

#include <vxWorks.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Circ_list_struct Circ_list;

struct Circ_list_struct
{
    Circ_list * prev;
    Circ_list * next;
};

/* A Circ_list used as a list head */
typedef Circ_list Circ_head;

/* A Circ_list used as a list entry */
typedef Circ_list Circ_entry;

/*
 * CIRC_LIST_INIT(l) initializes the list node l as a list
 * containing a single node (itself). Used for list heads/sentinels.
 */
#define CIRC_LIST_INIT(l) \
    do  { \
        Circ_list * l_ = (l); \
	l_->prev = l_; \
	l_->next = l_; \
        } while ((0))

#define CIRC_LIST_IS_EMPTY(l) (circ_list_is_empty (l))

_WRS_INLINE BOOL circ_list_is_empty
    (
    Circ_list *l
    )
    {
    return (l->next == l);
    }

/*
 * CIRC_LIST_REMOVE(n) removes the node n from the list
 * that it is in. (n must be in a list).
 * n is left with dangling references to the list.
 * If n is alone in the list, this is a no-op.
 */
#define CIRC_LIST_REMOVE(n) do { circ_list_remove (n); } while ((0))

_WRS_INLINE void circ_list_remove
    (
    Circ_entry *l
    )
    {
    Circ_list *prev = l->prev;
    Circ_list *next = l->next;
    prev->next = next;
    next->prev = prev;
    }

/*
 * CIRC_LIST_INSERT_AFTER(l, n) inserts node n after node l
 * in the list that l currently belongs to. n should
 * be a free node.  If l represents the 'head' of the list
 * rather than an 'item', this operation inserts n as the
 * first item in list.
 */
#define CIRC_LIST_INSERT_AFTER(l, n) \
    do { circ_list_insert_after ((l), (n)); } while ((0))

_WRS_INLINE void circ_list_insert_after
    (
    Circ_list *l,
    Circ_list *n
    )
    {
    Circ_list *next = l->next;
    n->prev = l;
    n->next = next;
    l->next = n;
    next->prev = n;
    }

/*
 * CIRC_LIST_INSERT_BEFORE(l, n) inserts node n before node l
 * in the list that l currently belongs to. n should
 * be a free node.  If l represents the head of the list,
 * this operation corresponds to inserting n at the tail.
 */
#define CIRC_LIST_INSERT_BEFORE(l, n) \
    do { circ_list_insert_before ((l), (n)); } while ((0))

_WRS_INLINE void circ_list_insert_before
    (
    Circ_list *l,
    Circ_list *n
    )
    {
    Circ_list *prev = l->prev;
    n->prev = prev;
    n->next = l;
    prev->next = n;
    l->prev = n;
    }

/*
 * CIRC_LIST_SPLICE(h, n) removes any entries from the list headed
 * by h and splices them into the list containing n immediately after
 * n. The nodes h and n must not belong to the same list.
 */
#define CIRC_LIST_SPLICE(h, n) \
    do { circ_list_splice ((h), (n)); } while ((0))

_WRS_INLINE void circ_list_splice
    (
    Circ_head *h,
    Circ_list *n
    )
    {
    Circ_list *first = h->next;
    Circ_list *last = h->prev;
    Circ_list *next = n->next;
    h->next = h;
    h->prev = h;
    last->next = next;
    next->prev = last;
    first->prev = n;
    n->next = first;
    }

#ifdef __cplusplus
}
#endif

#endif /* VX_LIST_H */
