/* array.h - declarations for array classes  */

/* Copyright 2004 Wind River Systems, Inc. */

/*
modification history
--------------------
01b,14mar06,mcm  Fix for SPR#118178
01a,07oct04,f_b   added
*/

#ifndef _ARRAY_H
#define _ARRAY_H

#include "allocator.h"

class IntArray
{
private:
    int     *value;
    unsigned size;

public:
    // Constructors
    IntArray(unsigned sz);
    IntArray(unsigned sz, int x);

    // Destructor
    ~IntArray();

    void    clear();

    // Overload the [] operator
    inline int& operator [] (unsigned index)
    {
            return value[index];
    }

    inline unsigned getSize() const
    {
            return size;
    } 

private:
    void    init(unsigned sz, int v);
};


/*************************************************************************
 *
 *  Array template class
 *
 *************************************************************************
 */
template <class Type>
class   Array
{
public:
    /* Setup a array */
    Array(unsigned sz)
    {
      size   = sz;
      parray = (Type *)theAllocator->allocate( sz, sizeof(Type) );
    }
    ~Array ()
    {
    }

    // Overload the [] operator
    inline Type & operator [] (unsigned index);

    inline unsigned getSize() const
    {
            return size;
    } 

private:
    unsigned  size;
    Type     *parray;
};

// Overload the [] operator
template <class Type>
inline
Type & Array<Type>::operator [] (unsigned index)
{
    return parray[index];
}

#endif /* _ARRAY_H */

