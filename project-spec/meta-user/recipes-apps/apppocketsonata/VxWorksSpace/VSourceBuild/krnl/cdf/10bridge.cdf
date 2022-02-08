/*
Copyright 2000-2006, 2016 Wind River Systems, Inc.

@format.tab-size 8

modification history
--------------------
20may16,chm  Port TSR defect fix forward from vxworks6.9 into vx7. (F6988)
21apr16,l_y  added bridge aging time.(VXW6-85482)
16nov06,tlu  Added contatenate symbol "\" for bridge dependencies 
16aug06,tlu  Added INCLUDE_ETHERNET and INCLUDE_NET_POOL as bridge 
             dependency
24jun05,svk  Remove tabs from IPv6 prefix length default value
04may05,zhu  Updated parameter name and synopsis
28apr05,zhu  Moved bridge to layer2 folder and updated case of the name
19mar05,zhu  Changed the string format to be consistent with NAT and 
             Firewall
28mar05,svk  Allow bridge to attach to IPv6 stack
25apr03,zhu  Updated copyright
29apr02,zhu  Changed INIT order with DHCPS
24apr02,vks  Removed mirror parameters, renamed mirror addr and mask
             parameters, modified usrNetBridgeInit() call
10apr02,vks  Merged mirror and bridge configlettes
09apr02,svk  Added configuration parameters
16feb01,ann  Written

DESCRIPTION

This file contains the Bridge component description.
*/

#ifdef _WRS_CONFIG_COMPONENT_BRIDGE

Component INCLUDE_BRIDGE 
	{
	NAME        	Learning Bridge
	SYNOPSIS	Core Bridge module
	MODULES     	bridge.o
	CONFIGLETTES	usrNetBridgeCfg.c
	HDR_FILES	    bridge.h
	INIT_RTN    	usrNetBridgeInit (BRIDGE_PORTS, \
			BRIDGE_IP_ADDR, BRIDGE_IP_MASK, \
			BRIDGE_IPV6_ADDR, BRIDGE_IPV6_PREFIXLEN, \
                        BRIDGE_AGING_TIMEOUT);
	CFG_PARAMS	BRIDGE_PORTS \
			BRIDGE_IP_ADDR \
			BRIDGE_IP_MASK \
                        BRIDGE_IPV6_ADDR \
			BRIDGE_IPV6_PREFIXLEN \
                        BRIDGE_AGING_TIMEOUT
	REQUIRES	INCLUDE_MUX \
			INCLUDE_ETHERNET \
			INCLUDE_NET_POOL
	_INIT_ORDER	usrNetAppInit
	INIT_BEFORE     INCLUDE_DHCPS
	}

Parameter BRIDGE_PORTS
	{
	NAME	 	Bridge port list
	SYNOPSIS	Specify list of interfaces to be added as bridge ports.\
e.g.,"fei,0,fei,1,elPci,0"
	TYPE		string
	DEFAULT		""
	}

Parameter BRIDGE_IP_ADDR
	{
	NAME		Bridge IP address
	SYNOPSIS	Specify the bridge IP address. e.g.,"10.11.12.1"
	TYPE		string
	DEFAULT		""
	}

Parameter BRIDGE_IP_MASK
	{
	NAME		Bridge network mask
	SYNOPSIS	Specify the network mask of the bridge. e.g.,0xFF000000
	TYPE		int
	DEFAULT		0
	}

Parameter BRIDGE_IPV6_ADDR
	{
	NAME		Bridge IPv6 address
	SYNOPSIS	Specify the IPv6 address of the bridge. \
e.g.,"2001:DB8:1234:100::1"
	TYPE		string
	DEFAULT		""
	}

Parameter BRIDGE_IPV6_PREFIXLEN
	{
	NAME		Bridge IPv6 prefix length
	SYNOPSIS	Specify the IPv6 prefix length of the bridge. e.g.,64
	TYPE		int
	DEFAULT		0
	}

Parameter BRIDGE_AGING_TIMEOUT
        {
        NAME            Bridge aging timeout time
        SYNOPSIS        Specify the bridge aging time. e.g.,300
        TYPE            int
        DEFAULT         300
        }

#endif
