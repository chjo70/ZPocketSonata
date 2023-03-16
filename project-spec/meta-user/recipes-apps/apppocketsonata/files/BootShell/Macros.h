// Macros.h: interface for the macro definetion
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MACRO_H__93E04DDF_CE5E_4DB7_95B5_D35B77F287E7__INCLUDED_)
#define AFX_MACRO_H__93E04DDF_CE5E_4DB7_95B5_D35B77F287E7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <stdio.h>

#define TICK_COUNT									(100)
#define OS_ONE_SEC									TICK_COUNT
#define OS_TEN_MILLISEC								(1)
#define OS_ONE_MILLISEC								(0.1)

#ifndef WhereIs
#define WhereIs									printf( "...in %s file, %d line(s)" , __FILE__, __LINE__ )
#endif

#define PrintErr(A)							{ printf A; WhereIs; }


#endif // !defined(AFX_MACRO_H__93E04DDF_CE5E_4DB7_95B5_D35B77F287E7__INCLUDED_)
