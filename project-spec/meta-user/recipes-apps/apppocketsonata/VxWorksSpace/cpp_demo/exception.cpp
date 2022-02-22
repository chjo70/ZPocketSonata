/* exception.cpp - implements function that generates a C++ exception */

/* Copyright 2004 Wind River Systems, Inc. */

/*
modification history
--------------------
01a,07oct04,f_b   added
*/

void exceptionDemo()
{
//#if 0
    /* On all the compilers, this requires extensive
     * runtime support. You must turn on exception support
     * before compiling this block.
     */
    int value = 0;

    try {
      throw 'A';
    } catch( char a ) {
       value = 1;
    }

    value++;
//#endif
}

