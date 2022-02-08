/* eventPointLibP.h - */

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
01a,08dec10,tcr  created
*/

#ifndef __eventPointLibPh
#define __eventPointLibPh

#ifdef __cplusplus
extern "C" {
#endif

STATUS eventPointSwHandle(int evtId, void *data, unsigned int length);

#ifdef __cplusplus
}
#endif


#endif /* __eventPointLibPh */

