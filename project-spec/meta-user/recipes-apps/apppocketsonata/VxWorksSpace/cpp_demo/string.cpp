/* string.cpp - implements simple string class */

/* Copyright 2004 Wind River Systems, Inc. */

/*
modification history
--------------------
01a,07oct04,f_b   added
*/

#include	<string>
#include    "string.h"
#include    "allocator.h"

//---------------------------------------------------------------------------
//  Default Constructor
//
//---------------------------------------------------------------------------

String::String()
{
    buf = 0;
    length = 0;
}

//---------------------------------------------------------------------------
//  Constructor 
//
//      Takes a char pointer for input.
//
//---------------------------------------------------------------------------
String::String( const char *s )
{
    length = (unsigned)strlen( s );
    buf    = createBuffer( length + 1 );
	strcpy( buf, s );
}

//---------------------------------------------------------------------------
//  Constructor
//
//      Takes a char pointer and a count
//
//---------------------------------------------------------------------------
String::String( char c, unsigned n )
{
    length = n;
    buf    = createBuffer( length + 1 );
    memset( buf, c, length );
    buf[length] = '\0';
}

//---------------------------------------------------------------------------
//  Copy Constructor
//
//---------------------------------------------------------------------------
String::String( const String &other )
{
    length = other.length;
    buf    = createBuffer( length + 1 );
    strcpy( buf, other.buf );
}

//---------------------------------------------------------------------------
//  Assignment operator overload
//
//---------------------------------------------------------------------------
String &String::operator=( const String &other )
{
    if (&other != this) {
	length = other.length;
	buf    = createBuffer( length+1 );
	strcpy( buf, other.buf );
    }
    return *this;
}

//---------------------------------------------------------------------------
//  append
//
//      Appends a String to another String.
//
//---------------------------------------------------------------------------
void String::append( const char *addition )
{
    char *temp;

    length += strlen( addition );
    temp    = createBuffer( length + 1 ); // Allocate a new buffer
    strcpy( temp, buf );                // Copy contents of old buffer
    strcat( temp, addition );           // Append new String
    buf = temp;
}

//---------------------------------------------------------------------------
//  append
//
//      Appends a String to another String.
//
//---------------------------------------------------------------------------
void String::append( const String &addition )
{
    char *temp;

    length += addition.getLength();
    temp    = createBuffer( length + 1 ); // Allocate a new buffer
    strcpy( temp, buf );                // Copy contents of old buffer
    strcat( temp, addition.buf );       // Append new String
    buf = temp;
}

//---------------------------------------------------------------------------
//  appendOverloading the '+' operator to append one string to another
//---------------------------------------------------------------------------
String& String::operator +(const String &s)
{
    append(s);
    return *this;
}
        
//---------------------------------------------------------------------------
//  Destructor
//
//---------------------------------------------------------------------------
String::~String()
{
}

//---------------------------------------------------------------------------
//  empty
//
//      Makes a String empty.
//
//---------------------------------------------------------------------------
void String::empty()
{
    length = 0;
    buf    = 0;
}

//---------------------------------------------------------------------------
//  operator [] overload
//
//---------------------------------------------------------------------------
char String::operator[]( unsigned index ) const
{
    // If index is not within the String then return null char. This also
    // works if the string length == 0.
    if( index >= length ) 
        return '\0';
    else
        return buf[index];
}

//---------------------------------------------------------------------------
//  operator [] overload
//
//--------------------------------------------------------------------------- 
char *String::createBuffer( unsigned index ) const
{
  return (char *)theAllocator->allocate( index );
}

