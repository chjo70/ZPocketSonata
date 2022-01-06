/* 01stopmode.cdf - Stop Mode Debug Agent component description file */

/*
 * Copyright (c) 2014-2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify, or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
21dec17,syc  Added serial debug support for stop mode (US107861).
07dec16,mca  Break hard dependency between END and IPNET (US85582).
07jun16,jmp  Removed unnecessary dependency on INCLUDE_BANNER (V7COR-4204).
14dec15,elp  Fix description (V7COR-3672).
29apr15,elp  Only allow serial connection on compat69 bsps (V7COR-2833).
17jan15,elp  Only allow END configuration if network is present.
05jan15,jmp  Removed dependency on INCLUDE_CLASS_LIST as stop mode debugger
             is able to debug a target configured without INCLUDE_CLASS_LIST.
23dec14,elp  Added mbuf pool parameters (US46080).
20nov14,jmp  Added missing dependency for OS-awareness on INCLUDE_CLASS_LIST.
19nov14,sdt  Added EDR hooks dependency for exceptions support (US44279)
21oct14,vhe  Changed agent start mechanism (US46091)
14oct14,jmp  Changed serial baud rate default to 38400 (WB4-4400).
26aug14,elp  Made END connection the default.
18aug14,elp  Added END connection configuration.
09jul14,jmp  written.
*/

/*
DESCRIPTION
This file contains descriptions for the Stop Mode agent components.
*/

Folder FOLDER_STOP_MODE_AGENT {
        NAME            Stop Mode Debug Agent components
        SYNOPSIS        Stop Mode Debug Agent
        _CHILDREN       FOLDER_TOOLS
        CHILDREN        INCLUDE_STOP_MODE_AGENT \
                        SELECT_STOP_MODE_AGENT_COMM_TYPE \
                        INCLUDE_STOP_MODE_AGENT_START \
                        INCLUDE_STOP_MODE_AGENT_BANNER
        DEFAULTS        INCLUDE_STOP_MODE_AGENT \
                        SELECT_STOP_MODE_AGENT_COMM_TYPE
}

/*
 * The stop mode agent END connection depends on the IPNET stack
 * because it calls ipcom_socket() directly instead of sockLib's
 * socket() routine. Since serial connection depends on COMPAT69
 * we have to let the whole agent require IPNET in VxWorks 7 mode.
 */

Component INCLUDE_STOP_MODE_AGENT {
        NAME            Stop Mode Debug Agent
        SYNOPSIS        Support for stop mode debug agent. \
                        This agent does not provide a secured network connection; \
                        it is advised to not include it in your development system \
                        or make sure it is not automatically started at boot time \
                        through boot line parameter or dedicated component.
        MODULES         smaLib.o
        CONFIGLETTES    usrSma.c
        HDR_FILES       smaLib.h
        INIT_RTN        usrSmaInit ();
        CFG_PARAMS      STOP_MODE_AGENT_STACK_SIZE
        _INIT_ORDER     usrToolsInit
#ifdef _WRS_CONFIG_COMPAT69
        REQUIRES        SELECT_STOP_MODE_AGENT_COMM_TYPE \
                        INCLUDE_SYSDBG_FLAG \
                        INCLUDE_EDR_POLICY_HOOKS
#else
        REQUIRES        SELECT_STOP_MODE_AGENT_COMM_TYPE \
                        INCLUDE_SYSDBG_FLAG \
                        INCLUDE_EDR_POLICY_HOOKS \
                        INCLUDE_IPNET
#endif
}

Component INCLUDE_STOP_MODE_AGENT_START {
        NAME            Start Stop Mode Debug Agent
        SYNOPSIS        Automatically start the stop mode debug agent at boot.\
                        For security reasons, it is advisable for production \
                        systems to reconfigure VxWorks with only those \
                        components needed for deployed operation.
        _INIT_ORDER     usrToolsInit
        REQUIRES        INCLUDE_STOP_MODE_AGENT

}

Component INCLUDE_STOP_MODE_AGENT_BANNER {
        NAME            Stop Mode Debug Agent banner
        SYNOPSIS        Add stop mode debug agent specific elements in banner
        INIT_RTN        usrSmaBannerInit ();
        REQUIRES        INCLUDE_STOP_MODE_AGENT \
                        INCLUDE_SYSDBG_FLAG
        INCLUDE_WHEN    INCLUDE_BANNER \
                        INCLUDE_STOP_MODE_AGENT
        _INIT_ORDER     usrRoot
        INIT_BEFORE     INCLUDE_BANNER
}

Component INCLUDE_STOP_MODE_AGENT_SERIAL {
        NAME            Stop Mode Agent serial connection
        SYNOPSIS        Serial line connection.\
                        The stop mode agent uses a serial line connection \
                        to communicate with host tools.
        CONFIGLETTES    usrSmaSerial.c
        CFG_PARAMS      STOP_MODE_AGENT_TTY_CHANNEL \
                        STOP_MODE_AGENT_TTY_BAUD_RATE
        REQUIRES        INCLUDE_STOP_MODE_AGENT
}

#ifdef _WRS_CONFIG_END
Component INCLUDE_STOP_MODE_AGENT_END {
        NAME            Stop Mode Agent END connection
        SYNOPSIS        END connection. \
                        The stop mode agent uses a network connection\
                        to communicate with the host tools.
        CONFIGLETTES    usrSmaEnd.c
        CFG_PARAMS      STOP_MODE_AGENT_END_DEVICE_NAME \
                        STOP_MODE_AGENT_END_DEVICE_UNIT \
                        STOP_MODE_AGENT_END_DEVICE_ADDRESS \
                        STOP_MODE_AGENT_MTU \
                        STOP_MODE_AGENT_END_NUM_MBUFS \
                        STOP_MODE_AGENT_END_NUM_CL_BLKS \
                        STOP_MODE_AGENT_END_PORT
        REQUIRES        INCLUDE_STOP_MODE_AGENT \
                        INCLUDE_IPNET
}
#endif

Selection SELECT_STOP_MODE_AGENT_COMM_TYPE {
        NAME            Stop Mode Agent communication type
        SYNOPSIS        Select Stop Mode Agent connection type
        COUNT           1-1
#ifdef _WRS_CONFIG_END
        CHILDREN        INCLUDE_STOP_MODE_AGENT_SERIAL \
                        INCLUDE_STOP_MODE_AGENT_END
        DEFAULTS        INCLUDE_STOP_MODE_AGENT_END
#else
        CHILDREN        INCLUDE_STOP_MODE_AGENT_SERIAL
        DEFAULTS        INCLUDE_STOP_MODE_AGENT_SERIAL
#endif
}

Parameter STOP_MODE_AGENT_TTY_CHANNEL {
        NAME            Serial channel for Stop Mode Agent connection
        SYNOPSIS        Defines the serial channel number to use for Stop Mode Agent connection
        TYPE            uint
	DEFAULT		1
}

Parameter STOP_MODE_AGENT_TTY_BAUD_RATE {
        NAME            Baud rate for Stop Mode Agent serial channel
        SYNOPSIS        Defines Stop Mode Agent serial baud rate
        TYPE            uint
	DEFAULT		38400
}

#ifdef _WRS_CONFIG_END
Parameter STOP_MODE_AGENT_END_DEVICE_NAME {
        NAME            Device to use for Stop Mode Agent connection
        SYNOPSIS        Alternative device to use for Stop Mode Agent connection. If none specified, use boot device.
        DEFAULT         NULL
        TYPE            string
}

Parameter STOP_MODE_AGENT_END_DEVICE_UNIT {
        NAME            Device unit number for Stop Mode Agent connection
        SYNOPSIS        Device unit number to use for Stop Mode Agent connection. This is used only if a Stop Mode Agent END device name is specified.
        DEFAULT         0
        TYPE            uint
}

Parameter STOP_MODE_AGENT_END_DEVICE_ADDRESS {
        NAME            IP address to use for Stop Mode Agent connection
        SYNOPSIS        Alternative IP address to use for Stop Mode Agent connection. If none specified, use boot address.
        DEFAULT         NULL
        TYPE            string
}

Parameter STOP_MODE_AGENT_END_PORT {
        NAME            Default Stop Mode Agent communication port
        SYNOPSIS        Defines Stop Mode Agent communication port number
        DEFAULT         0x4321
        TYPE            uint16_t
}

Parameter STOP_MODE_AGENT_MTU {
        NAME            MTU for Stop Mode Agent communication channel
        SYNOPSIS        Defines Stop Mode Agent communication MTU
        TYPE            uint
        DEFAULT         1500
}

Parameter STOP_MODE_AGENT_END_NUM_MBUFS {
        NAME            Stop Mode Agent number of network buffers
        SYNOPSIS        Used to initialize Stop Mode Agent buffer pool
        TYPE            uint
        DEFAULT         5
}

Parameter STOP_MODE_AGENT_END_NUM_CL_BLKS {
        NAME            Stop Mode Agent number of network buffer clusters
        SYNOPSIS        Used to initialize Stop Mode Agent buffer pool
        TYPE            uint
        DEFAULT         5
}
#endif

Parameter STOP_MODE_AGENT_STACK_SIZE {
        NAME            Stack size of the Stop Mode Agent
        SYNOPSIS        The stack size of the context executing the Stop Mode Agent
        TYPE            uint
	DEFAULT		8192
}
