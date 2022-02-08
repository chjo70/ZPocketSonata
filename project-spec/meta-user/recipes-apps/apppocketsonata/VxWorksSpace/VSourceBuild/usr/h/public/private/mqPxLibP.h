/* mqPxLibP.h - usr-level private header for POSIX message queues */

/*
 * Copyright (c) 2003, 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement. 
 */


/*
modification history
--------------------
01e,29jul10,pad  Moved extern C statement after include statements.
01d,14nov03,m_s  Written
*/

#ifndef __INCmqPxLibPh
#define __INCmqPxLibPh

/* includes */

#include <objLib.h>

#ifdef _cplusplus
extern "C" {
#endif

/* defines */

/* typedefs */

/* message queue descriptor for user applications */

struct mq_des
    {
    int        f_flag;
    OBJ_HANDLE f_data;
    };

/* function declarations */


#ifdef __cplusplus
}
#endif

#endif /* __INCmqPxLibPh */
