/* list.h - declarations for linked list classes */

/* Copyright 2004 Wind River Systems, Inc. */

/*
modification history
--------------------
01a,07oct04,f_b   added
*/

#ifndef _LIST_H
#define _LIST_H

/* ListItem is a base class. It doesn't have any function by
 * itself, it's main purpose is to provide list functions for the
 * derived class.
 */
class ListItem
{
private:
    ListItem     *previous;
    ListItem     *next;

public:
    //* Constructor
    ListItem() :
      previous(0),
          next(0)
      { }

    void addBefore(ListItem & item);
    void addAfter(ListItem & item);

    ListItem *  getPrevious()               { return previous; }
    ListItem *  getNext()                   { return next; }
    void        setPrevious(ListItem *p)    { previous = p; }
    void        setNext(ListItem *p)        { next = p; }

    /* Compare will compare the current item with one passed and return:
     *  -1 - item passed in is less than "this" item
     *  0  - items are equal
     *  1  - item passed in is greater than "this" item.
     *
     *  This is a "pure virtual" function; derived classes must over ride
     *  this function.
     */
    virtual int     compare(const ListItem &) = 0; // { return 0; }

    /* This function is used for displaying the value
     */
    virtual void    displayValue() = 0; // { }
};

/* The List class defines a list of elements ListItem
 */
class List
{
protected:
    ListItem    *head;
    ListItem    *tail;
    int         itemCount;

public:
    List() :
      head(0),
      tail(0),
      itemCount(0)
    { }

    /* Make the following a virtual function so that derived classes
     * can override it.
     */

    /* add      - adds a item to the end of the list (default; but may
     *            over ridden
     * remove   - removes selected item from list.
     */
    virtual void    add(ListItem &item);
    virtual void    remove(ListItem &item);

    virtual ListItem *getFirst(void);
};


/* Now define some real lists.
 */
class  IntListItem : public ListItem
{
private:
    int     value;

public:
    IntListItem() :
      value(0)
    { }

    IntListItem(int v) :
      value (v)
    { }

    int getValue() const { return value; }

    int compare(const ListItem &l)
    {
        IntListItem *p = (IntListItem *)&l;

        if (p->value < value)
            return  -1;
        else if (p->value == value)
            return 0;
        else
            return 1;
    }

    void    displayValue()
    {
    }

};

class  FloatListItem : public ListItem
{
private:
    float   value;

public:
    FloatListItem() :
      value(0.0f)
    { }

    FloatListItem(float v) :
      value (v)
    { }

    float getValue() const { return value; }

    int compare(const ListItem &l)
    {
        FloatListItem *p = (FloatListItem *)&l;

        if (p->value < value)
            return  -1;
        else if (p->value == value)
            return 0;
        else
            return 1;
    }

    void    displayValue()
    {
    }

};


/* Now lets define a sorted list based on List
 */
class SortedList : public List
{
public:
    void    add(ListItem &item);
};

#endif /* _LIST_H */

