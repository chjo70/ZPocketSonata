/* allocator.cpp - implements simple memory allocator class  */

/* Copyright 2004 Wind River Systems, Inc. */

/*
modification history
--------------------
01a,07oct04,f_b   added
*/

#include "allocator.h"

Allocator *theAllocator;

Allocator::Allocator()
{
  theAllocator = this;
  initialize();
} /* Allocator::Allocator */

Allocator::~Allocator()
{
  theAllocator = 0;
} /* Allocator::~Allocator */

void *
Allocator::allocate( unsigned long size )
{
  unsigned char *p = pointer;

  size += ((size+7uL)/8uL) * 8uL;
  if( size > remaining_size )
    outOfMemory();

  pointer += size;

  return (void *)p;
} /* Allocator::allocate */

void *
Allocator::allocate( unsigned long elements, unsigned long size )
{
  return allocate( size * elements );
} /* Allocator::allocate */

void
Allocator::initialize()
{
  static unsigned char buffer[2048];

  pointer        = buffer;
  remaining_size = sizeof(buffer);
} /* Allocator::initialize */

void
Allocator::outOfMemory()
{
  while( 1 )
    ;
} /* Allocator::outOfMemory */
 
