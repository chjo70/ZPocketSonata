/* smaSerialLib.h - stop mode agent serial library header file */

/*
 * Copyright (c) 2014 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
16jul14,rlp  Written
*/

#ifndef __INCsmaSerialLibh
#define __INCsmaSerialLibh

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* include */

/* define */

#ifndef _ASMLANGUAGE

/* function declaration */

extern STATUS smaSerialInit (int channel, int baudRate);

#endif /* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif  /* __INCsmaSerialLibh */
