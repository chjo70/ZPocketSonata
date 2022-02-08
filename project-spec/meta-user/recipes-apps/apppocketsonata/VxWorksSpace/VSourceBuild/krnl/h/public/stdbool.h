/*
 * Copyright (c) 2010, 2016-2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
06nov17,mst  Modified to cope with Diab/C99 (V7COR-5408)
27oct16,jdw  Copied from rttools/CAFE version of stdbool.h
*/

#ifndef INCstdbool_h
#define INCstdbool_h

#ifndef __cplusplus

#if ( 199901L <= __STDC_VERSION__ )
#if defined(__GNUC__) && ( __GNUC__ < 3 )
typedef unsigned int _Bool;
#endif
#elif (!defined(__GNUC__)) && (defined(__STRICT_ANSI__))
typedef unsigned int _Bool;
#endif /* 199901L <= __STDC_VERSION__ ... */

#ifndef false
#define false (0)
#endif

#ifndef true
#define true (1)
#endif

#ifndef bool
#define bool _Bool
#endif
#endif /* __cplusplus */

#ifndef __bool_true_false_are_defined
#define __bool_true_false_are_defined (1)
#endif

#endif /* INCstdbool_h */
