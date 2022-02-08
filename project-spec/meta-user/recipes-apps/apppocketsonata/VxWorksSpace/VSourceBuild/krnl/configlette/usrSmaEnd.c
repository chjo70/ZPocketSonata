/* usrSmaEnd.c - Stopmode agent END communication initialization library */

/*
 * Copyright 2014,2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
04nov14,jpb  added heder file for _func_printErr (V7COR-910)
12jan15,elp  Fixed usrSmaDevInit() return value.
23dec14,elp  Listen on every interface by default (US46080).
21oct14,vhe  Added configuration string
18aug14,elp  written from smaEnd.c
*/

/*
DESCRIPTION
Initializes the END network connection for the Stop Mode Agent.

NOMANUAL
*/

/* includes */

#include <configNet.h>
#include <smaEndPktDrv.h>
#include <smaMbufLib.h>
#include <private/fioLibP.h>		/* _func_printErr */

/* defines */

#if	STOP_MODE_AGENT_MTU > STOP_MODE_AGENT_END_PKT_MTU
#undef	STOP_MODE_AGENT_MTU
#define	STOP_MODE_AGENT_MTU	STOP_MODE_AGENT_END_PKT_MTU
#endif	/* STOP_MODE_AGENT_MTU > STOP_MODE_AGENT_END_PKT_MTU */

#ifdef STOP_MODE_AGENT_END_NUM_MBUFS
#define SMA_NUM_MBUFS STOP_MODE_AGENT_END_NUM_MBUFS
#else
#define SMA_NUM_MBUFS   5
#endif

#ifdef STOP_MODE_AGENT_END_NUM_CL_BLKS
#define SMA_NUM_CL_BLKS STOP_MODE_AGENT_END_NUM_CL_BLKS
#else
#define SMA_NUM_CL_BLKS 5
#endif

/* globals */

char * smaEndDeviceAddress = NULL;

/* locals */

static struct mbuf      smaMbufs[SMA_NUM_MBUFS];
static CL_BLK           smaClBlks[SMA_NUM_CL_BLKS];

/******************************************************************************
*
* usrSmaDevInit - initialize the END connection
*
* This routine initializes the END connection used by the Stop Mode Agent.
*
* RETURNS :
* OK or ERROR if the END connection can not be initialized.
*
* NOMANUAL
*/

STATUS usrSmaDevInit 
    (
    char * config       /* configuration string */ 
    )
    {
    END_OBJ *	pEnd = NULL;
    char *	smaEndDeviceName = STOP_MODE_AGENT_END_DEVICE_NAME;
    STATUS      status = OK;
    END_OBJ * endBuf [16];
    END_OBJ ** ebuf;
    int nSlots = NELEMENTS(endBuf);
    int n;

    /* update communication interface mtu */

    smaCommMtu = STOP_MODE_AGENT_MTU;
    smaPort = STOP_MODE_AGENT_END_PORT;
    smaMbufInit (smaMbufs, SMA_NUM_MBUFS, smaClBlks, SMA_NUM_CL_BLKS);

    smaEndDeviceAddress = STOP_MODE_AGENT_END_DEVICE_ADDRESS;

    /*
     * First look if the user has specified a network adapter to use for
     * SMA connection. In this case only connect on this one.
     */

    if ((smaEndDeviceName != NULL) && (smaEndDeviceName [0] != EOS))
    	{
	/* Try to find this device */

    	pEnd = endFindByName (smaEndDeviceName,
                              STOP_MODE_AGENT_END_DEVICE_UNIT);

    	if (pEnd == NULL)
	    {
	    if (_func_printErr != NULL)
	    	_func_printErr ("usrSmaDevInit: Could not find device "
			    	"%s, unit %d !\n",
			    	smaEndDeviceName,
			    	STOP_MODE_AGENT_END_DEVICE_UNIT, 0, 0, 0, 0);
                 return ERROR;
	    }
        return (smaEndPktDevInit((char *)pEnd->devObject.name,
                                 pEnd->devObject.unit));
	}
    n = muxEndListGet (NULL, 0); /* get number of END devices */

    if (n <= nSlots)
        ebuf = endBuf;
    else
        {
        if ((ebuf = malloc ((n+4) * sizeof (END_OBJ *))) == NULL)
            ebuf = endBuf;
        else
            nSlots = n+4;
        }
        
    n = muxEndListGet (ebuf, nSlots);
    if (n > nSlots)
        _func_printErr (
            "usrSmaDevInit: Do not monitor every END devices\n",
            0,0,0,0,0,0);
         
    status = ERROR; /* error if no device is successfully initialized */
    nSlots = n;
    for (n = 0; n < nSlots; ++n)
        {
        pEnd = ebuf[n];
        if (smaEndPktDevInit((char *)pEnd->devObject.name,
                             pEnd->devObject.unit) == OK)
            {
            status = OK;
            }
        else
            {
            _func_printErr ("usrSmaDevInit: warning: interface %s%d "
                            "initialization failure\n",
                            pEnd->devObject.name, pEnd->devObject.unit);
            }
        muxDevRelease (pEnd); /* release ref count on END device */
        }
    return (status);
    }
