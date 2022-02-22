/* array.cpp - implements simple integer array class  */

/* Copyright 2004 Wind River Systems, Inc. */

/*
modification history
--------------------
01a,07oct04,f_b   added
*/

#include    "array.h"
#include    "allocator.h"

IntArray::IntArray(unsigned sz)
{
    init (sz, 0);
}

IntArray::IntArray(unsigned sz, int x)
{
    init (sz, x);
}

IntArray::~IntArray()
{    
    value = 0;
    size  = 0;
}    

void IntArray::init(unsigned sz, int x)
{
    value = (int *)theAllocator->allocate( sz, sizeof(int) );

    if (value == 0)
        return;

    for (unsigned i = 0; i < sz; i++)
    {
        value[i] = x;
    } 

    size = sz;

} /* IntArray::init */

void IntArray::clear()
{
    value = 0;
    size  = 0;
} /* IntArray::clear */

