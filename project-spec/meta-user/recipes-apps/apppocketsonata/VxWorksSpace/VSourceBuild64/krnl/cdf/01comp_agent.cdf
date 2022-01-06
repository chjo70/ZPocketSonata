/* 01comp_agent.cdf - agent components */

/*
 * Copyright (c) 2009, 2013-2016 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
07dec16,mca  Break hard dependency between END and IPNET (US85582).
07jun16,jmp  Removed unnecessary dependency on INCLUDE_BANNER (V7COR-4204).
15jul15,elp  Updated DEBUG_AGENT_CONFIG synopsis (US60628).
06mar15,f_l  Renamed Debug Agent to Application Mode Agent
08jan15,rlp  Group Debug Agent components into a specific folder (V7COR-2302).
07jan15,rlp  Fixed Debug Agent synopsis message (V7COR-2301)
21oct14,vhe  Changed agent start mechanism (US36858)
24sep13,rlp  Renamed agent components
13jun13,rlp  Fixed initialization order for Vx7
02apr09,pca  created
*/

/*
DESCRIPTION
This file contains component descriptions for the agent and any intrinsic
services.
*/

Folder FOLDER_DEBUG_AGENT {
        NAME            Application Mode Agent components
        SYNOPSIS        Application Mode Agent
        _CHILDREN       FOLDER_TOOLS
        CHILDREN        INCLUDE_DEBUG_AGENT \
                        INCLUDE_DEBUG_AGENT_START \
                        INCLUDE_DEBUG_AGENT_BANNER
        DEFAULTS        INCLUDE_DEBUG_AGENT
}

/*
 * The application mode agent depends on the IPNET stack
 * since it calls ipcom_getsockaddrbyaddr()
 */

Component INCLUDE_DEBUG_AGENT {
        NAME            Application Mode Agent
	SYNOPSIS        The Application Mode Agent is a modular TCF based communication system for the purpose of debugging, profiling, code patching and other device software development needs. This agent does not provide a secured network connection; It is advised to not include it in deployed devices or make sure it is not automatically started at boot time through boot line parameter or dedicated component.
        CONFIGLETTES    usrDebugAgent.c
        CFG_PARAMS      DEBUG_AGENT_TASK_PRIORITY \
                        DEBUG_AGENT_CONFIG
        INIT_RTN        tcfLibCheckStart ();
        HDR_FILES       tcfLib.h
        MODULES         tcfLib.o
        REQUIRES        INCLUDE_SYSDBG_FLAG \
                        INCLUDE_IPNET
}

InitGroup tcfServicesInit {
        PROTOTYPE       void tcfServicesInit ()
        SYNOPSIS        Register subsystem services before TCF agent is started.
        INIT_RTN        tcfServicesInit ();
}

Parameter DEBUG_AGENT_TASK_PRIORITY {
        NAME            Priority of Application Mode Agent tasks
        SYNOPSIS        All Application Mode Agent tasks will be spawned with this priority. 49 is a sensible default.
        TYPE            uint
        DEFAULT         49
}

Parameter DEBUG_AGENT_CONFIG {
        NAME            Application Mode Agent configuration string
        SYNOPSIS        Options for Application Mode Agent configuration. Format is "-s <protocol>:<ipAddr>:<port>". Default <protocol> is TCP. Default <ipAddr> is empty meaning agent listens on every interfaces. Default <port> is 1534. For example setting "-s TCP::5656" modifies default port to use port 5656.
        TYPE            char *
        DEFAULT         NULL
}

Component INCLUDE_DEBUG_AGENT_START {
        NAME            Application Mode Agent Start
        SYNOPSIS        Automatically start the Application Mode Agent at boot up. For security reasons, it is advisable for production systems to reconfigure VxWorks with only those components needed for deployed operation.
        REQUIRES        INCLUDE_DEBUG_AGENT
}

Component INCLUDE_DEBUG_AGENT_BANNER {
        NAME            Application Mode Agent Banner
        SYNOPSIS        Toggles agent specific elements in banner
        INIT_RTN        usrDebugAgentBannerInit ();
        REQUIRES        INCLUDE_DEBUG_AGENT     \
                        INCLUDE_SYSDBG_FLAG
        INCLUDE_WHEN    INCLUDE_BANNER \
                        INCLUDE_DEBUG_AGENT
        _INIT_ORDER     usrRoot
        INIT_BEFORE     INCLUDE_BANNER
}
