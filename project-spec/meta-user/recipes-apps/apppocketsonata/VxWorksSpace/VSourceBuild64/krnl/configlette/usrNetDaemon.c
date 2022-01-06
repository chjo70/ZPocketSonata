/* usrNetDaemon.c - the daemon init */

/*
 * Copyright (c) 2001-2002, 2007, 2009-2010, 2014-2015 Wind River Systems, Inc.
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
28jan16,h_x  Support to set NUM_NET_DAEMONS to 0 in VIP, V7NET-747
07jul15,jxy  Replace IP_NULL with NULL. (V7NET-613)
06may15,zan  Configuration of affinity and priority for networking task.
23dec14,chm  Network stack 64-bit big-endian validation.(US49760)
26sep10,dlk  Remove obsolete references to _func_wdbIsNowExternal.
20may09,dlk  Remove obsolete INCLUDE_SHELL_DEBUG setting of
             _func_bdall.
10jul07,dlk  Pass in network task daemon function to decouple
             network stack from network daemon support.
06may07,dlk  Correct typo.
02may07,dlk  Multiple network daemon support.
17oct02,ham  fixed vxWorks.st build error due to WDB symbols (SPR 83160).
01apr02,ham  guard _func_* initialization with inclusion macro.
28mar02,ann  added the code to enable system mode debugging when
             tNetTask is spawned as BREAKABLE.
21feb02,ham  changed in response to obsolete usrNetDaemonStart.
09dec01,ham  wrote.
*/

extern unsigned int netJobNum;
extern TASK_ID  netTaskId;
extern int      netTaskPriority;
extern int      netTaskOptions;
extern size_t   netTaskStackSize;

unsigned int    *nettask_priorities;
unsigned int    *nettask_affinities;

#ifdef INCLUDE_IPCOM

STATUS ipcomNetTask
    (
    JOB_QUEUE_ID qId,
    int jobQueueIndex
    )
    {
    extern int ipcom_ima_stack_task (int stack_idx);

    /* Declare this task a stack daemon. */

    if (ipcom_ima_stack_task(jobQueueIndex) != 0)
	return ERROR;

    return jobQueueProcessFunc (qId); /* normally won't return */
    }

#else

STATUS netTaskS
    (
    JOB_QUEUE_ID qId,
    int jobQueueIndex
    )
    {
    WIND_TCB * pTcb = taskTcb (0);
    /* This routine is called only when ipcom is not configured into the
     * system; so pTcb->pIpcomInfo is available to use to support
     * netTaskDaemonIndex().
     */
    pTcb->pIpcomInfo = (void *)(long)(jobQueueIndex + 1);
    return jobQueueProcessFunc (qId); /* normally won't return */
    }

#endif /* INCLUDE_IPCOM */

/***************************************************************************
*
* netTaskDaemonIndex - return the network daemon index of the specified task
*
* This routine returns the network task index of the specified task.
* <tid> may be specified as 0 to indicate the current task.
* If the specified task is not a network daemon, the function returns -1.
* Otherwise it returns the daemon's index (from 0 up to netDaemonsCount() - 1).
*
* If not NULL, <tid> must be a valid TASK_ID, but for performance reasons
* this routine does not check that it is.
*
* RETURNS: -1, or the network task index of the specified network task.
* NOMANUAL
*/
int netTaskDaemonIndex 
    (
    TASK_ID tid
    )
    {
    /*
     * netTaskDaemonIndex is defined here rather than in daemon.c because its
     * implementation depends upon whether or not INCLUDE_IPCOM is defined.
     */

#ifdef INCLUDE_IPCOM

    extern int ipcom_stack_index_of_vxtask (TASK_ID tid);
    return ipcom_stack_index_of_vxtask (tid);

#else
    /*
     * This version is used when ipcom is not configured in the system.
     * When ipcom is configured, it provides its own version of this function
     * in ipcom_vxworks.c.
     */
    WIND_TCB * pTcb;
    long val;

#if 0
    pTcb = taskTcb (tid);
#else
    if (tid == 0)
        pTcb = taskTcb (0);
    else
        pTcb = (WIND_TCB *)tid;
#endif

    val = (long)pTcb->pIpcomInfo;

    /*
     * pTcb->pIpcomInfo defaults to NULL; but netTask() sets it to its own
     * stack index plus one (cast as a void *).
     */
    return (int)(val - 1);

#endif /* INCLUDE_IPCOM */
    }


/* format:"1,50;2,50" */
LOCAL void usrNetTaskPriorityParse()
{
    unsigned int i;
    char *buf;
    char *token,*saveptr;
    char *str;
    unsigned int taskid,taskpriority,numDaemons;

    numDaemons = NUM_NET_DAEMONS;
    if (NUM_NET_DAEMONS == 0)
    {
#ifdef _WRS_CONFIG_SMP 
        numDaemons = vxCpuConfiguredGet (); 
#else            
        numDaemons = 1;
#endif
    }
    
    for	(i = 0; i < numDaemons; i++)
        nettask_priorities[i] = NET_TASK_DEFAULT_PRIORITY;

    buf = strdup(NET_TASK_PRIORITIES);	
    if (buf == NULL)
        return;

    if (strlen(buf) < 3)
    {
        goto cleanup;
    }
    
    for (i = 0, str = buf; ; i++,str = NULL)
    {
        token = strtok_r(str,";",&saveptr);

        if (token == NULL)
            break;

        if (sscanf(token," %d , %d ",&taskid,&taskpriority) != 2)
            goto cleanup;

        if (taskid >= NUM_NET_DAEMONS)
            goto cleanup;
        if (taskpriority > 255)
            goto cleanup;
        nettask_priorities[taskid] = taskpriority;
    }
        
cleanup:
    free(buf);	
}


/* format:"1,1;2,2" */
LOCAL void usrNetTaskAffinityParse()
{
    unsigned int i;
    char *buf;
    char *token,*saveptr;
    char *str;
    unsigned int taskid,taskaffinity,numDaemons;  
    unsigned int  ncpus;

    ncpus = vxCpuConfiguredGet();

    numDaemons = NUM_NET_DAEMONS;
    if (NUM_NET_DAEMONS == 0)
    {
#ifdef _WRS_CONFIG_SMP 
        numDaemons = vxCpuConfiguredGet ();
#else 
        numDaemons = 1;
#endif            
    }

    for	(i = 0; i < numDaemons; i++)
    {
        /* Note, setting the affinity to 'ncpus' implies no affinity */
        nettask_affinities[i] = (NET_DAEMONS_CPU_AFFINITY && i < ncpus) ? i : ncpus;
    }

    buf = strdup(NET_DAEMONS_CPU_AFFINITIES);
    if (buf == NULL)
        return;

    if (strlen(buf) < 3)
    {
        goto cleanup;
    }  	

    for (i = 0, str = buf; ; i++, str = NULL)
    {

        token = strtok_r(str,";",&saveptr);

        if (token==NULL)
            break;

        if (sscanf(token," %d , %d ",&taskid,&taskaffinity) != 2)
            goto cleanup;

        if (taskid >= NUM_NET_DAEMONS)
        {
            goto cleanup;
        }

        nettask_affinities[taskid] = taskaffinity;
    }
    
cleanup:    	
    free(buf);	
}

#if 0
void showNettaskAffinities()
{
    int i;
    for (i = 0; i < NUM_NET_DAEMONS; i++)
    {
        printf("NetTask%d:%d\n",i,nettask_affinities[i]);
    }
}

void showNettaskPriorities()
{
    int i;
    for (i = 0; i < NUM_NET_DAEMONS; i++)
    {
        printf("NetTask%d:%d\n",i,nettask_priorities[i]);
    }
}
#endif
	
STATUS usrNetDaemonInit
    (
    unsigned int	jobNum,
    unsigned int	pri,
    int			opts,
    unsigned int	stack
    )
    {
    int numDaemons;
    netJobNum = jobNum;
    netTaskPriority = pri;
    netTaskOptions = opts;
    netTaskStackSize = stack;
    numDaemons = NUM_NET_DAEMONS;
    if (NUM_NET_DAEMONS == 0)
    {
#ifdef _WRS_CONFIG_SMP
        numDaemons = vxCpuConfiguredGet ();
#else
        numDaemons = 1;
#endif
    }
    nettask_priorities = malloc(sizeof(int)*numDaemons);
    nettask_affinities = malloc(sizeof(int)*numDaemons);    
    usrNetTaskPriorityParse();
    usrNetTaskAffinityParse();
#ifdef INCLUDE_IPCOM
    return (netLibInitialize(NUM_NET_DAEMONS, NET_DAEMONS_CPU_AFFINITY,
			     ipcomNetTask, nettask_priorities, nettask_affinities));
#else
    return (netLibInitialize(NUM_NET_DAEMONS, NET_DAEMONS_CPU_AFFINITY,
                             netTaskS, nettask_priorities, nettask_affinities));
#endif /* INCLUDE_IPCOM */
    }
