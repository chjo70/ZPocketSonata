/* scMemVal.h - header file for system call validation routines */

/*
 * Copyright (c) 2003-2004, 2009-2010, 2016 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement. 
 */
/*
modification history
--------------------
27jan16,pcs  Added prototype for scMemValidateStr.(V7COR-4002)
17may10,zl   added SC_PROT_ATOMIC_RMW.
29apr10,pad  Moved extern C statement after include statements.
16dec09,pcs  Updated for LP64 support.
04nov04,zl   created from private file.
*/

#ifndef __INCscMemValh
#define __INCscMemValh

#include <vxWorks.h>

#ifdef __cplusplus
extern "C" {
#endif

/* defines */

#define SC_PROT_READ		0x1	/* read access in supervisor mode  */
#define SC_PROT_WRITE		0x2	/* write access in supervisor mode */
#define SC_PROT_ATOMIC_RMW	0x4	/* atomic read-modify-write access */

#ifndef  _ASMLANGUAGE

/* type definitions */

typedef unsigned int SC_PROT_ATTR;

/* function declarations */

IMPORT STATUS scMemValidate (const void * addr, size_t size, SC_PROT_ATTR prot);
IMPORT STATUS scMemValidateStr (const char * name, size_t len);
IMPORT void   scMemValEnable (BOOL enable);

#endif /* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCscMemValh */
