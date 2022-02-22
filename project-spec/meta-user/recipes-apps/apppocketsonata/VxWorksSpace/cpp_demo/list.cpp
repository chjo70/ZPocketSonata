/* list.cpp - implements linked list classes */

/* Copyright 2004 Wind River Systems, Inc. */

/*
modification history
--------------------
01a,07oct04,f_b   added
*/

#include    "list.h"

void ListItem::addBefore(ListItem & item)
{
    /* Place "item" before "this" in the list.
     */
    item.previous        = this->previous;
    item.next            = this;
    if (this->previous != 0)
        this->previous->next = &item;
    this->previous       = &item;
}

void ListItem::addAfter(ListItem & item)
{
    /* Place "item" after "this" in the list.
     */
    item.previous = this;
    item.next     = this->next;
    this->next    = &item;
}

/* The default for adding an item to the end of the list.
 */
void List::add(ListItem &item)
{
    /* Place item at the end of the list.
     */
    if (itemCount == 0)
    {
        head = tail = &item;
    }
    else
    {
        tail->addAfter(item);
        tail = &item;
    }
    itemCount++;
}

/* This will remove an item from the list whose value matched "item".
 * It will return a pointer to the item removed, or 0 if not found.
 */
void List::remove(ListItem &item)
{
    ListItem *p, *n;

    /* Make sure item is in the list.
     */
    for (p = getFirst(); p != &item; p = p->getNext())
    {
        if (p == 0)
            return;
    }

    p = item.getPrevious();
    n = item.getNext();
    item.setPrevious(0);
    item.setNext(0);

    itemCount--;
    
    /* If this is the last item in the list then clear out everything.
     */
    if (itemCount == 0)
    {
        head = tail = 0;
        return;
    }

    if (p != 0)
    {
        p->setNext(n);
        if (n == 0)
        {
            tail = p;
        }
    }
    if (n != 0)
    {
        n->setPrevious(p);
        if (p == 0)
        {
            head = n;
        }
    }
}

ListItem * List::getFirst(void)
{
    return head;
}

/*-------------------------------------------------------------------
 *
 *      SortedList class functions
 *
 *-------------------------------------------------------------------
 */
void SortedList::add (ListItem &item)
{
    ListItem    *curr;

    /* Place item at the end of the list.
     */
    if (itemCount == 0)
    {
        head = tail = &item;
    }
    else
    {
        /* Find a place to add this item.
         */
        for (curr = head; curr != 0; curr = curr->getNext() )
        {
            if (curr->compare(item) == -1)
                break;
        }

        /* curr now should point to the item we want to add before.
         * If it is 0, then we want this add this to the end of the list.
         */
        if (curr == 0)
        {
            tail->addAfter(item);
            tail = &item;
        }
        else
        {
            curr->addBefore(item);
            if (curr == head)
                head = &item;
        }
    }
    itemCount++;
}
