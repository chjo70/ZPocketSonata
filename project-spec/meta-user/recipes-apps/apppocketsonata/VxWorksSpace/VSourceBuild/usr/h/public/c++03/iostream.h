// iostream.h standard header
#ifndef _IOSTREAM_H_
#define _IOSTREAM_H_
#include <istream>
_STD_BEGIN

		// OBJECTS
static ios_base::Init _Ios_init0;
extern istream cin;
extern ostream cout;
extern ostream cerr, clog;
_STD_END

 #if _HAS_NAMESPACE
using namespace std;
 #endif /* _HAS_NAMESPACE */

#endif /* _IOSTREAM_H_ */

/*
 * Copyright (c) 1992-2002 by P.J. Plauger.  ALL RIGHTS RESERVED.
 * Consult your license regarding permissions and restrictions.
V4.00:1278 */
