/* allocator.h - declarations for memory allocator class  */

/* Copyright 2004 Wind River Systems, Inc. */

/*
modification history
--------------------
01a,07oct04,f_b   added
*/

/**********************************************************************
*
*       Copyright (c) 2004 Wind River Systems, Inc.
*
***********************************************************************/

#ifndef _ALLOCATOR_H
#define _ALLOCATOR_H

class Allocator {
  public:
    Allocator();
    ~Allocator();

    void *allocate( unsigned long size );
    void *allocate( unsigned long elements, unsigned long size );

    void initialize();
  private:
    Allocator( const Allocator & );
    const Allocator &operator =( const Allocator & );

    void outOfMemory();

    unsigned long  remaining_size;
    unsigned char *pointer;
};

extern Allocator *theAllocator;

#endif /* _ALLOCATOR_H */

