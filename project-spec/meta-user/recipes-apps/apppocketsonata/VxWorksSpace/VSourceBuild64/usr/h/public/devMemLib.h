/* devMemLib.h - user-level device memory object library header file */

/* 
 * Copyright (c) 2010 Wind River Systems, Inc. 
 *
 * The right to copy, distribute, modify or otherwise make use 
 * of this software may be licensed only pursuant to the terms 
 * of an applicable Wind River license agreement. 
 */ 

/*
modification history
--------------------
01a,28jan04,pcs  created
*/

#ifndef __INCsdLibh
#define __INCsdLibh

#include <vxWorks.h>
#include <vmLibCommon.h>

#ifdef __cplusplus
extern "C" {
#endif


/* functional API to the library */

int devMemOpen
    (
    const char * name,          /* object name */
    int          oflag,         /* access control flag */
    mode_t       mode           /* permission mode */
    );


#ifdef __cplusplus
}
#endif	/* __cplusplus */

#endif /* __INCdevMemLibh */
