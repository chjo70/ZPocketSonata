/* usrNetEndLib.c - End Init routines */

/*
 * Copyright (c) 2002, 2004-2009, 2014-2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement. No license to Wind River intellectual property rights
 * is granted herein. All rights not licensed by Wind River are reserved
 * by Wind River.
 */

/*
modification history
--------------------
06aug15,m_w  Start the stats polling of all end drivers in usrNetEndLibInit()
             for VxBus GEN2. (V7PRO-2249)
09jul15,dlk  V7NET-618: Ensure that END_POLL_STATS_ROUTINE_HOOK is declared.
06may15,dlk  Fix merge error.
20nov14,wap  Allow use of this configlette with VxBus GEN2
05sep14,wap  Add support for initializing job queues
04nov14,jpb  added header file for _func_printErr (V7COR-910)
01jun09,h_k  updated the arg type for vxbDevMethodRun().
17jun08,dlk  Reference endDevTbl only if INCLUDE_END is defined.
22mar08,dlk  Initial support for END2 drivers.
30jul07,mze  extern usrTipcHendAttach and fix Copyright and mod history
03apr07,d_c  Method update on behalf of Radzy
12jun06,wap  Modified usrNetEndLibInit() to initialize function pointer
             _func_m2PollStatsIfPoll with END_POLL_STATS_ROUTINE_HOOK
             configuration.
21sep05,dsk  added usrTipcHendAttach 
02sep05,mdo  vxBus: Add vxb prefix
08aug05,mdo  Change WINDBUS to VXBUS
08aug05,wap  Change polled stats hook into a component
28jul04,rcs  Added vxbus support
04oct04,wap  Add missing polling stats hook (SPR #101616)
11mar02,ham  set ON to the processed flag after sucessful muxDevStart
28feb02,ham  added netDevBootFlag.
28jan02,ham  revised from TOR3_1-FCS(01f).
*/

/*
DESCRIPTION

This configlette contains the initialization routine for the
INCLUDE_END component.

NOMANUAL
*/

#include <vsbConfig.h>
#include <vxWorks.h>
#include <muxLib.h>

#include <ctype.h>
#include <string.h>

#ifdef __WRS_CONFIG_VXBUS_LEGACY
#ifdef INCLUDE_VXBUS
#include <hwif/vxbus/vxBus.h>
#endif /* INCLUDE_VXBUS */
#endif /* _WRS_CONFIG_VXBUS_LEGACY */

#include <private/fioLibP.h>		/* _func_printErr */
#include <private/muxLibP.h>

#if defined (INCLUDE_END) || defined (INCLUDE_END2)
void usrEndJobQueueInit (void);
LOCAL STATUS getNameUnit (char * ifName, int * ifIndex);
LOCAL STATUS fieldSplit (char *, char ** ifName, char ** qName);
#endif

#ifndef END_NET_JOB_INIT_STRING
#define END_NET_JOB_INIT_STRING "dummy0:0|dummy1:1"
#endif

LOCAL char endString[] = END_NET_JOB_INIT_STRING;

#ifdef INCLUDE_END_POLLED_STATS
IMPORT FUNCPTR  _func_m2PollStatsIfPoll; 
#ifndef END_POLL_STATS_ROUTINE_HOOK
#define END_POLL_STATS_ROUTINE_HOOK     m2PollStatsIfPoll
#endif
IMPORT STATUS END_POLL_STATS_ROUTINE_HOOK (END_IFDRVCONF *);
#endif

#ifdef INCLUDE_TIPC_HEND_INIT
/* defined in pkgs/ipc/tipc/tipc_kernel/configlette/usrTipc.c */
IMPORT STATUS usrTipcHendAttach (void);
#endif

#if defined (INCLUDE_END2) && defined(INCLUDE_VXBUS)
LOCAL void end2VxBusConnect (void)
    {
    /* Add in mux ENDs from bus subsystem */
    vxbDevMethodRun((VXB_METHOD_ID)&mux2DevConnect_desc, NULL);
    }
#endif /* defined (INCLUDE_END2) && defined(INCLUDE_VXBUS) */

/*****************************************************************************
*
* usrNetEndLibInit - load and start the end driver
*
* On previous generation of VxBus, this initialization routine will load 
* and start the end drivers, the muxDevConnect() method of each end driver
* will be called and then muxDevLoad()/muxDevStart() will be called. Also
* the _func_m2PollStatsIfPoll will initializied before end driver is loaded.
* 
* On VxBus GEN2, the end driver will be loaded and started through this path:
* usrRoot() -> vxbLibInit()-> vxbDevAttach() of end ->  
* muxDevLoad()/muxDevStart(), which is earlier then this initialization 
* routine is called. The main job here is to start the stats polling machine
* if it was assigned.
*
* RETURNS: N/A
*
* ERRNO: N/A
*/

STATUS usrNetEndLibInit()
    {
#ifdef _WRS_CONFIG_VXBUS_LEGACY
#ifdef INCLUDE_END
    int             count;
    END_TBL_ENTRY * pDevTbl;
    void          * pCookie = NULL;
#endif
#endif /* _WRS_CONFIG_VXBUS_LEGACY */

#ifdef INCLUDE_TIPC_HEND_INIT
    usrTipcHendAttach();
#endif

#ifdef INCLUDE_END_POLLED_STATS

    /* initialize the _m2PollStatsIfPoll function pointer */

    _func_m2PollStatsIfPoll = (FUNCPTR)END_POLL_STATS_ROUTINE_HOOK;

#ifndef _WRS_CONFIG_VXBUS_LEGACY

    /* 
     * On VxBus GEN2, the vxbDevAttach() method of end drivers will be
     * called earlier than _func_m2PollStatsIfPoll is initializied,
     * this will lead a issue: endPollStatsInit() in end driver is not
     * called when end is attached into vxbus, because
     * _func_m2PollStatsIfPoll is NULL at that moment.
     * So, there must be somewhere that endPollStatsInit() should be
     * called to make sure the poll stats is started for end drivers,
     * here is a appropriate position for this.
     * For the end driver which is launched after system is boot up
     * (which means _func_m2PollStatsIfPoll has already been initializied),
     * for example, launch the end driver from target shell, the end
     * driver should call the endPollStatsInit() itself.
     */

    (void)muxEndExecute ((MUX_END_EXEC_FUNC)endPollStatsInit,
                         (_Vx_usr_arg_t)END_POLL_STATS_ROUTINE_HOOK,
                         (_Vx_usr_arg_t)0,
                         (_Vx_usr_arg_t)0);

#endif /* !_WRS_CONFIG_VXBUS_LEGACY */
#endif /* INCLUDE_END_POLLED_STATS */

#ifdef _WRS_CONFIG_VXBUS_LEGACY
#ifdef INCLUDE_VXBUS
#ifdef INCLUDE_END2
#ifdef INCLUDE_VXMUX_PKT_POOL_MIN
    /*
     * Perform late end2VxBusConnect() operation now that the VXMUX
     * minimal packet pool should be ready.
     */
    end2VxBusConnect ();
#else
    /*
     * For now, delay connection (load/start) of END2 drivers until the
     * ipnet packt pool is ready.
     */
    _func_end2VxBusConnect = end2VxBusConnect;
#endif
#endif /* INCLUDE_END2 */
    /* Add in mux ENDs from bus subsystem */
    vxbDevMethodRun((VXB_METHOD_ID)&muxDevConnect_desc, NULL);
#endif /* INCLUDE_VXBUS */
 
#ifdef INCLUDE_END
    /* Add in mux ENDs from BSP. */
    for (count = 0, pDevTbl = endDevTbl; pDevTbl->endLoadFunc != END_TBL_END;
         pDevTbl++, count++)
        {
        /* Make sure that WDB has not already installed the device. */
        if (!pDevTbl->processed)
            {
            pCookie = muxDevLoad (pDevTbl->unit,
                                  pDevTbl->endLoadFunc,
                                  pDevTbl->endLoadString,
                                  pDevTbl->endLoan, pDevTbl->pBSP);
            if (pCookie == NULL)
                {
                if (_func_printErr)
                    {
                    (* _func_printErr)
                    ("muxDevLoad failed for device entry %d!\n", count);
                    }
                }
            else
                {
                if (muxDevStart(pCookie) == ERROR)
                    {
                    if (_func_printErr)
                        {
                        (* _func_printErr)
                        ("muxDevStart failed for entry %d!\n", count);
                        }
                    }
                    else
                    {
                    pDevTbl->processed = TRUE;
#ifdef INCLUDE_END_POLLED_STATS
                    endPollStatsInit (pCookie, END_POLL_STATS_ROUTINE_HOOK);
#endif /* INCLUDE_END_POLLED_STATS */
                    }
                }
            }
        }
#endif /* INCLUDE_END */
#endif /* _WRS_CONFIG_VXBUS_LEGACY */

#if defined (INCLUDE_END) || defined (INCLUDE_END2)
    usrEndJobQueueInit ();
#endif

#ifdef INCLUDE_NET_BOOT
    netDevBootFlag = TRUE;
#endif /* INCLUDE_NET_BOOT */
    return (OK);
    }

#if defined (INCLUDE_END) || defined (INCLUDE_END2)

/*****************************************************************************
*
* fieldSplit - split the string by colon
*
* This routine will split the string by colon.
*
* RETURNS: OK or ERROR if do not find colon in string.
*
* ERRNO: N/A
*/

LOCAL STATUS fieldSplit
    (
    char * field,
    char ** ifName,
    char ** qName
    )
    {
    char * tok;
    char * holder = NULL;

    tok = strtok_r (field, ":", &holder);

    if (tok == NULL)
        return (ERROR);

    *ifName = tok;

    tok = strtok_r (NULL, ":", &holder);

    if (tok == NULL)
        return (ERROR);

    *qName = tok;

    return (OK);
    }

/*****************************************************************************
*
* getNameUnit - extract the name and unit from a string.
*
* This routine will extract the name and unit from a string like "enet0".
*
* RETURNS: OK or ERROR if do not find a digit in string.
*
* ERRNO: N/A
*/

LOCAL STATUS getNameUnit
    (
    char * ifName,
    int * ifIndex
    )
    {
    int i;
    for (i = 0; i < 255; i++)
        {
        if (ifName[i] == '\0')
            return (ERROR);
        if (isdigit (ifName[i]) != 0)
            break;
        }

    *ifIndex = (int)strtoul (&ifName[i], NULL, 10);
    ifName[i] = '\0';

    return (OK);
    }

/*****************************************************************************
*
* usrEndJobQueueInit - set default job queues for specified network devices
*
* This initialization routine sets the default network job queue for various
* network interfaces present in the system. This applies to those devices
* which implement the EIOCGRCVJOBQ and EIOCSRCVJOBQ ioctls. (Ultimately all
* END devices should support these ioctls.) The initialization is done
* using a string which be set as a workbench parameter. The string is
* in the form of "enet0:1|enet1:2|enet2:3", where enet0, enet1 and enet2
* are the names of network interfaces to be configured. The desired default
* queue value is specified as an integer value separated from the interface
* name using a colon character. Multiple interfaces can be specified as
* separate fields, using a pipe (|) character as a field separator.
*
* The netjob queue index typically refers to an instence of tNetX running
* on a given CPU core. The queue index is therefore synonymous with a
* CPU core index. The queue is set using the muxEndQnumSet() routine,
* which in turn uses the EIOCSRCVJOBQ ioctl. The underlying driver must
* implement this ioctl in order for the queue selection mechanism to work.
*
* Note that if the interface is already in the up state, muxEndQnumSet()
* will stop and restart it in order for the change to take effect.
*
* RETURNS: N/A
*
* ERRNO: N/A
*/

void usrEndJobQueueInit (void)
    {
    char * tok;
    char * holder = NULL;
    char * ifName;
    char * qName;
    int qNum;
    int ifIndex;

    tok = strtok_r (endString, "|", &holder);

    while (tok != NULL)
        {
        if (fieldSplit (tok, &ifName, &qName) == OK)
            {
            if (getNameUnit (ifName, &ifIndex) == OK)
                {
                qNum = (int)strtoul (qName, NULL, 10);
                (void) muxEndQnumSet (ifName, ifIndex, qNum);
                }
            }
        tok = strtok_r (NULL, "|", &holder);
        }

    return;
    }

#endif /* INCLUDE_END || INCLUDE_END2 */
