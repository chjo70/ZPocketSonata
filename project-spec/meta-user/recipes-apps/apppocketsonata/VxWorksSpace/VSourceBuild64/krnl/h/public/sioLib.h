/* sioLib.h - header file for binary interface serial drivers */

/*
 * Copyright 1995, 1997, 2000-2002, 2005, 2010, 2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use 
 * of this software may be licensed only pursuant to the terms 
 * of an applicable Wind River license agreement. 
 */ 

/*
modification history
--------------------
18feb15,pad  Replaced sioIoctl macro with an inlined function (CERT).
03mar10,pch  improve robustness of sioIoctl()
22mar05,hya  moved common part into sioLibCommon.h.
09may02,wef  adding keyboard led set and get ioctls.
29sep01,dat  added SIO_ERRROR_NONE, new MODEM ctrl values.
26apr00,dat  added error callback
04feb00,db   added support for handling modem control signals and 
             multiple keyboard modes(SPR #29348).
14jan97,db   added SIO_OPEN and SIO_HUP for modem control(SPR #7637).
24oct95,ms   removed "static __inline__" (SPR #4500)
15jun95,ms   Added SIO_MODE_SET, SIO_MODE_GET, SIO_AVAIL_MODES_GET iotcl's
              Renamed SIO_CHAN to SIO_CHAN
              Changed prototype and name of callbackInstall()
              Added documentation.
22may95,ms   removed unneeded include file.
21feb95,ms   written.
*/

#ifndef __INCsioLibh
#define __INCsioLibh

#include <types/vxTypes.h>
#include <types/vxTypesOld.h>
#include <errno.h>
#include <sioLibCommon.h>

#ifdef __cplusplus
extern "C" {
#endif

/* callback type codes */

#define SIO_CALLBACK_GET_TX_CHAR	1
#define SIO_CALLBACK_PUT_RCV_CHAR	2
#define SIO_CALLBACK_ERROR		3

/* Get Tx Chara callback (getTxCallbk) (callbkArg, pChar) */

/* Put Rx Chara callback (putRxCallbk) (callbkArg, char) */

/* Error callback codes: (errorCallbk) (callbkArg, code, pData, size) */

#define SIO_ERROR_NONE			(-1)
#define SIO_ERROR_FRAMING		0
#define SIO_ERROR_PARITY		1
#define SIO_ERROR_OFLOW			2
#define SIO_ERROR_UFLOW			3
#define SIO_ERROR_CONNECT		4
#define SIO_ERROR_DISCONNECT		5
#define SIO_ERROR_NO_CLK		6
#define SIO_ERROR_UNKNWN		7

/* serial device data structures */

typedef struct sio_drv_funcs SIO_DRV_FUNCS;

typedef struct sio_chan				/* a serial channel */
    {
    SIO_DRV_FUNCS * pDrvFuncs;
    /* device data */
    } SIO_CHAN;

struct sio_drv_funcs				/* driver functions */
    {
    int		(*ioctl)
			(
			SIO_CHAN *	pSioChan,
			int		cmd,
			void *		arg
			);

    int		(*txStartup)
			(
			SIO_CHAN *	pSioChan
			);

    int		(*callbackInstall)
			(
			SIO_CHAN *	pSioChan,
			int		callbackType,
			STATUS		(*callback)(void *, ...),
			void *		callbackArg
			);

    int		(*pollInput)
			(
			SIO_CHAN *	pSioChan,
			char *		inChar
			);

    int		(*pollOutput)
			(
			SIO_CHAN *	pSioChan,
			char 		outChar
			);
    };


/* in-line function */

/*******************************************************************************
*
* sioIoctl - invokes the SIO driver's ioctl support routine
*
* This inlined function invokes the SIO driver's ioctl support routine after
* some sanity verifications.
*
* RETURNS: a status code from the SIO driver's ioctl support routine, or
* ENOSYS if no such routine exists.
*
* \NOMANUAL
*/

_WRS_INLINE int sioIoctl
    (
    SIO_CHAN * pSioChan,
    int        cmd,
    void *     arg
    )
    {
    if ((pSioChan != NULL) && (pSioChan->pDrvFuncs != NULL) &&
        (pSioChan->pDrvFuncs->ioctl != NULL))
        {
        return pSioChan->pDrvFuncs->ioctl (pSioChan, cmd, arg);
        }

    return ENOSYS;
    }

/* in-line macros */

#define sioTxStartup(pSioChan) \
	((pSioChan)->pDrvFuncs->txStartup (pSioChan))

#define sioCallbackInstall(pSioChan, callbackType, callback, callbackArg)   \
	((pSioChan)->pDrvFuncs->callbackInstall (pSioChan, callbackType,    \
						 callback, callbackArg))

#define sioPollInput(pSioChan, inChar) \
	((pSioChan)->pDrvFuncs->pollInput (pSioChan, inChar))

#define sioPollOutput(pSioChan, thisChar) \
	((pSioChan)->pDrvFuncs->pollOutput (pSioChan, thisChar))

#ifdef __cplusplus
}
#endif

#endif  /* __INCsioLibh */
