/* 00comp_net_daemon.cdf - Component configuration file */

/* Copyright 2001-2003, 2006-2008, 2015-2016 Wind River Systems, Inc. */

/*
modification history
--------------------
18jan17,jbm  NAME and SYNOPSIS editorial clean up
07dec16,mca  Break hard dependency between END and IPNET (US85582)
28jun16,rjq  Set the net daemons in runtime in SMP mode. (V7NET-811)
04may15,zan  Add parameter for net task, priority and affinity. Can set each task's priority and affinity.
16oct08,dlk  Set affinity of tNet0 task to CPU0 by default.
02may07,dlk  Add multiple net daemon support.
12sep06,dlk  Added HDR_FILES netLib.h to INCLUDE_NET_DAEMON
08dec03,ann  added VX_UNBREAKABLE to NET_TASK_OPTIONS
12sep03,vvv  updated configlette path
16apr02,rvr  removed entry points and PREF_DOMAIN attribute
24feb02,ham  renamed CONFIGLETTES.
21feb02,ham  merged 00comp_net_daemon_start.cdf
26nov01,ham  wrote.
*/

Component INCLUDE_NET_DAEMON {
        NAME            Network daemon support
        SYNOPSIS        This component includes support for the network daemon. \
                        The network daemon, tNet0, performs network driver and \
                        network protocol processing for the VxWorks network stack.
        CONFIGLETTES    usrNetDaemon.c
        HDR_FILES       netLib.h
        INIT_RTN        usrNetDaemonInit(NET_JOB_NUM_CFG,\
                        NET_TASK_DEFAULT_PRIORITY, NET_TASK_OPTIONS,\
                        NET_TASK_STACKSIZE);
        MODULES         daemon.o
        CFG_PARAMS      NET_JOB_NUM_CFG \
                        NET_TASK_DEFAULT_PRIORITY \
                        NET_TASK_PRIORITIES \
                        NET_TASK_OPTIONS \
                        NET_TASK_STACKSIZE \
                        NUM_NET_DAEMONS \
                        NET_DAEMONS_CPU_AFFINITY \
                        NET_DAEMONS_CPU_AFFINITIES
}

Parameter NET_JOB_NUM_CFG {
        NAME            Maximum number of network jobs 
        SYNOPSIS        This parameter specifies the maximum number of network \
                        jobs, netJobNum. 
        DEFAULT         85
        TYPE            uint
}

Parameter NET_TASK_DEFAULT_PRIORITY {
        NAME            Daemon task default priority
        SYNOPSIS        This parameter specifies the default priority for the \
                        daemon task.
        DEFAULT         50
        TYPE            uint
}

Parameter NET_TASK_PRIORITIES {
        NAME            Network daemon task priorities
        SYNOPSIS        This parameter specifies the task priorities for each \
                        network daemon. The format is "0,50;1,51", which means \
                        the priority for network daemon 0 is 50 and the priority \
                        for network daemon 1 is 51. When any error (invalid \
                        format or value) happens, the part of the parameter \
                        string after the error is ignored. If not specified, \
                        a network daemon's priority is set to \
                        NET_TASK_DEFAULT_PRIORITY. The default value of this \
                        parameter is "", which means that \
                        NET_TASK_DEFAULT_PRIORITY is the priority assigned to \
                        all network tasks.
        DEFAULT         ""
        TYPE            char *
}

Parameter NET_TASK_STACKSIZE {
        NAME            Daemon stack size
        SYNOPSIS        This parameter specifies the daemon stack size. 
        DEFAULT         10000
        TYPE            uint
}

Parameter NET_TASK_OPTIONS {
        NAME            DAEMON_TASK_OPTIONS
        SYNOPSIS        This parameter specifies the taskSpawn options for the \
                        daemon. 
        DEFAULT         VX_SUPERVISOR_MODE | VX_UNBREAKABLE
        TYPE            int
}

Parameter NUM_NET_DAEMONS {
        NAME            Number of network daemon tasks
        SYNOPSIS        This parameter specifies the number of network daemon \
                        job queues to create. A value of zero means 1 \
                        for uniprocessor builds or, for SMP builds, the \
                        number of CPUs. Any other value is treated literally.
        DEFAULT         1
        TYPE            uint
}

Parameter NET_DAEMONS_CPU_AFFINITY {
        NAME            Default CPU affinity setting for network daemon tasks
        SYNOPSIS        This parameter sets the default CPU affinity for network \
                        tasks in SMP builds. This parameter has no meaning for \
                        uniprocessor builds. If this parameter is set to TRUE, \
                        each network daemon number N is given (by default) \
                        affinity to CPU number N (when CPU N is configured). \
                        When this parameter is set to FALSE, network tasks \
                        are given no CPU affinity by default. You can override \
                        this parameter for specific network tasks using the \
                        NET_DAEMONS_CPU_AFFINITIES parameter.
        DEFAULT         TRUE
        TYPE            BOOL
}

Parameter NET_DAEMONS_CPU_AFFINITIES {
        NAME            NET_TASK_AFFINITIES
        SYNOPSIS        This parameter configures the CPU affinity of each \
                        network daemon. This parameter overrides the default \
                        setting from NET_DAEMONS_CPU_AFFINITY. The format \
                        is "0,1;1,2", which means network daemon 0 is assigned \
                        to CPU 1, and network daemon 1 is assigned to CPU 2. \
                        If any error (invalid format or value) is encountered, \
                        the part of the parameter string after the error is \
                        ignored. For any network task not assigned by this \
                        parameter, the default setting from \
                        NET_DAEMONS_CPU_AFFINITY is used. The default value of \
                        this parameter is "", which means all network tasks use \
                        the NET_DAEMONS_CPU_AFFINITY setting.
        DEFAULT         ""
        TYPE            char *
}
