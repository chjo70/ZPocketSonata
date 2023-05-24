// Macros.h: interface for the macro definetion
//
//////////////////////////////////////////////////////////////////////


#pragma once


#include <stdio.h>

#define TICK_COUNT									(100)
#define OS_ONE_SEC									TICK_COUNT
#define OS_TEN_MILLISEC								(1)
#define OS_ONE_MILLISEC								(0.1)

#ifndef WhereIs
#define WhereIs									printf( "...in %s file, %d line(s)" , __FILE__, __LINE__ )
#endif

#ifndef PrintErr
#define PrintErr(A)							{ printf A; WhereIs; }
#endif



