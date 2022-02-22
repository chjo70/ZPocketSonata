/* string.h - declarations for string class */

/* Copyright 2004 Wind River Systems, Inc. */

/*
modification history
--------------------
01a,07oct04,f_b   added
*/

#ifndef _STRING_H
#define _STRING_H

class   String
{
public:
    String();
    String( const char *s );
    String( char c, unsigned n );
    String( const String &other );              // Copy Constructor
    ~String();

    String &operator=( const String &other );   // Assignment operator

    inline unsigned getLength() const { return length; }
    inline bool     isempty() const   { return length == 0 ? true : false; }

    void append( const char *addition );
    void append( const String &addition );
    String& operator + (const String &s);

    void empty();

    char operator [] ( unsigned index ) const;

private:
    char *createBuffer( unsigned length ) const;

    unsigned length;
    char    *buf;
};

#endif /* _STRING_H */

