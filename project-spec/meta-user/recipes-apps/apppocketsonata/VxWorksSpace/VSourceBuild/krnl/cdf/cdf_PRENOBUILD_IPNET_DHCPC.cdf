

/* this file is automatically generated */


Layer Layer::IPNET_DHCPC {
}




/*********************************
 Component INCLUDE_IPDHCPC 
 original object sources located at 
 $(WIND_BASE)/pkgs/net/ipnet-1.1.1.2/app/dhcpc-1.0.1.11/cdf/00comp_ipnet_appl_dhcp.cdf 
**********************************/
Component	INCLUDE_IPDHCPC {
		LAYER += Layer::IPNET_DHCPC
		LAYER_SOURCE		{$(WIND_BASE)/pkgs/net/ipnet-1.1.1.2/app/dhcpc-1.0.1.11/cdf/00comp_ipnet_appl_dhcp.cdf}
}


/*********************************
 Folder FOLDER_DHCP 
 original object sources located at 
 $(WIND_BASE)/pkgs/net/ipnet-1.1.1.2/app/dhcpc-1.0.1.11/cdf/00comp_ipnet_appl_dhcp.cdf 
**********************************/
Folder	FOLDER_DHCP {
		LAYER += Layer::IPNET_DHCPC
		LAYER_SOURCE		{$(WIND_BASE)/pkgs/net/ipnet-1.1.1.2/app/dhcpc-1.0.1.11/cdf/00comp_ipnet_appl_dhcp.cdf}
}


/*********************************
 Layer Layer::IPNET_DHCPC 
 original object sources located at 
 $(VSB_DIR) 
**********************************/
Layer	Layer::IPNET_DHCPC {
		LAYER += Layer::IPNET_DHCPC
		LAYER_SOURCE		{$(VSB_DIR)}
}


/*********************************
 Parameter DHCPC_CLIENT_PORT 
 original object sources located at 
 $(WIND_BASE)/pkgs/net/ipnet-1.1.1.2/app/dhcpc-1.0.1.11/cdf/00comp_ipnet_appl_dhcp.cdf 
**********************************/
Parameter	DHCPC_CLIENT_PORT {
		LAYER += Layer::IPNET_DHCPC
		LAYER_SOURCE		{$(WIND_BASE)/pkgs/net/ipnet-1.1.1.2/app/dhcpc-1.0.1.11/cdf/00comp_ipnet_appl_dhcp.cdf}
}


/*********************************
 Parameter DHCPC_SERVER_PORT 
 original object sources located at 
 $(WIND_BASE)/pkgs/net/ipnet-1.1.1.2/app/dhcpc-1.0.1.11/cdf/00comp_ipnet_appl_dhcp.cdf 
**********************************/
Parameter	DHCPC_SERVER_PORT {
		LAYER += Layer::IPNET_DHCPC
		LAYER_SOURCE		{$(WIND_BASE)/pkgs/net/ipnet-1.1.1.2/app/dhcpc-1.0.1.11/cdf/00comp_ipnet_appl_dhcp.cdf}
}


/*********************************
 Parameter DHCPC_REQ_OPTS 
 original object sources located at 
 $(WIND_BASE)/pkgs/net/ipnet-1.1.1.2/app/dhcpc-1.0.1.11/cdf/00comp_ipnet_appl_dhcp.cdf 
**********************************/
Parameter	DHCPC_REQ_OPTS {
		LAYER += Layer::IPNET_DHCPC
		LAYER_SOURCE		{$(WIND_BASE)/pkgs/net/ipnet-1.1.1.2/app/dhcpc-1.0.1.11/cdf/00comp_ipnet_appl_dhcp.cdf}
}


/*********************************
 Parameter DHCPC_CLIENT_ID 
 original object sources located at 
 $(WIND_BASE)/pkgs/net/ipnet-1.1.1.2/app/dhcpc-1.0.1.11/cdf/00comp_ipnet_appl_dhcp.cdf 
**********************************/
Parameter	DHCPC_CLIENT_ID {
		LAYER += Layer::IPNET_DHCPC
		LAYER_SOURCE		{$(WIND_BASE)/pkgs/net/ipnet-1.1.1.2/app/dhcpc-1.0.1.11/cdf/00comp_ipnet_appl_dhcp.cdf}
}


/*********************************
 Parameter DHCPC_CLIENT_UUID 
 original object sources located at 
 $(WIND_BASE)/pkgs/net/ipnet-1.1.1.2/app/dhcpc-1.0.1.11/cdf/00comp_ipnet_appl_dhcp.cdf 
**********************************/
Parameter	DHCPC_CLIENT_UUID {
		LAYER += Layer::IPNET_DHCPC
		LAYER_SOURCE		{$(WIND_BASE)/pkgs/net/ipnet-1.1.1.2/app/dhcpc-1.0.1.11/cdf/00comp_ipnet_appl_dhcp.cdf}
}


/*********************************
 Parameter DHCPC_RFC2131_INIT_DELAY 
 original object sources located at 
 $(WIND_BASE)/pkgs/net/ipnet-1.1.1.2/app/dhcpc-1.0.1.11/cdf/00comp_ipnet_appl_dhcp.cdf 
**********************************/
Parameter	DHCPC_RFC2131_INIT_DELAY {
		LAYER += Layer::IPNET_DHCPC
		LAYER_SOURCE		{$(WIND_BASE)/pkgs/net/ipnet-1.1.1.2/app/dhcpc-1.0.1.11/cdf/00comp_ipnet_appl_dhcp.cdf}
}


/*********************************
 Parameter DHCPC_RFC2131_EXP_BACKOFF 
 original object sources located at 
 $(WIND_BASE)/pkgs/net/ipnet-1.1.1.2/app/dhcpc-1.0.1.11/cdf/00comp_ipnet_appl_dhcp.cdf 
**********************************/
Parameter	DHCPC_RFC2131_EXP_BACKOFF {
		LAYER += Layer::IPNET_DHCPC
		LAYER_SOURCE		{$(WIND_BASE)/pkgs/net/ipnet-1.1.1.2/app/dhcpc-1.0.1.11/cdf/00comp_ipnet_appl_dhcp.cdf}
}


/*********************************
 Parameter DHCPC_DISCOVER_RETRIES 
 original object sources located at 
 $(WIND_BASE)/pkgs/net/ipnet-1.1.1.2/app/dhcpc-1.0.1.11/cdf/00comp_ipnet_appl_dhcp.cdf 
**********************************/
Parameter	DHCPC_DISCOVER_RETRIES {
		LAYER += Layer::IPNET_DHCPC
		LAYER_SOURCE		{$(WIND_BASE)/pkgs/net/ipnet-1.1.1.2/app/dhcpc-1.0.1.11/cdf/00comp_ipnet_appl_dhcp.cdf}
}


/*********************************
 Parameter DHCPC_OFFER_TIMEOUT 
 original object sources located at 
 $(WIND_BASE)/pkgs/net/ipnet-1.1.1.2/app/dhcpc-1.0.1.11/cdf/00comp_ipnet_appl_dhcp.cdf 
**********************************/
Parameter	DHCPC_OFFER_TIMEOUT {
		LAYER += Layer::IPNET_DHCPC
		LAYER_SOURCE		{$(WIND_BASE)/pkgs/net/ipnet-1.1.1.2/app/dhcpc-1.0.1.11/cdf/00comp_ipnet_appl_dhcp.cdf}
}


/*********************************
 Parameter DHCPC_IF_REQ_OPTS_LIST 
 original object sources located at 
 $(WIND_BASE)/pkgs/net/ipnet-1.1.1.2/app/dhcpc-1.0.1.11/cdf/00comp_ipnet_appl_dhcp.cdf 
**********************************/
Parameter	DHCPC_IF_REQ_OPTS_LIST {
		LAYER += Layer::IPNET_DHCPC
		LAYER_SOURCE		{$(WIND_BASE)/pkgs/net/ipnet-1.1.1.2/app/dhcpc-1.0.1.11/cdf/00comp_ipnet_appl_dhcp.cdf}
}


/*********************************
 Parameter DHCPC_IF_CLIENT_ID_LIST 
 original object sources located at 
 $(WIND_BASE)/pkgs/net/ipnet-1.1.1.2/app/dhcpc-1.0.1.11/cdf/00comp_ipnet_appl_dhcp.cdf 
**********************************/
Parameter	DHCPC_IF_CLIENT_ID_LIST {
		LAYER += Layer::IPNET_DHCPC
		LAYER_SOURCE		{$(WIND_BASE)/pkgs/net/ipnet-1.1.1.2/app/dhcpc-1.0.1.11/cdf/00comp_ipnet_appl_dhcp.cdf}
}


/*********************************
 Parameter DHCPC_INSTALL_OPTION_CALLBACK_HOOK 
 original object sources located at 
 $(WIND_BASE)/pkgs/net/ipnet-1.1.1.2/app/dhcpc-1.0.1.11/cdf/00comp_ipnet_appl_dhcp.cdf 
**********************************/
Parameter	DHCPC_INSTALL_OPTION_CALLBACK_HOOK {
		LAYER += Layer::IPNET_DHCPC
		LAYER_SOURCE		{$(WIND_BASE)/pkgs/net/ipnet-1.1.1.2/app/dhcpc-1.0.1.11/cdf/00comp_ipnet_appl_dhcp.cdf}
}


/*********************************
 Parameter DHCPC_INSTALL_REPLY_CALLBACK_HOOK 
 original object sources located at 
 $(WIND_BASE)/pkgs/net/ipnet-1.1.1.2/app/dhcpc-1.0.1.11/cdf/00comp_ipnet_appl_dhcp.cdf 
**********************************/
Parameter	DHCPC_INSTALL_REPLY_CALLBACK_HOOK {
		LAYER += Layer::IPNET_DHCPC
		LAYER_SOURCE		{$(WIND_BASE)/pkgs/net/ipnet-1.1.1.2/app/dhcpc-1.0.1.11/cdf/00comp_ipnet_appl_dhcp.cdf}
}


/*********************************
 Parameter DHCPC_OPTION_CALLBACK_HOOK 
 original object sources located at 
 $(WIND_BASE)/pkgs/net/ipnet-1.1.1.2/app/dhcpc-1.0.1.11/cdf/00comp_ipnet_appl_dhcp.cdf 
**********************************/
Parameter	DHCPC_OPTION_CALLBACK_HOOK {
		LAYER += Layer::IPNET_DHCPC
		LAYER_SOURCE		{$(WIND_BASE)/pkgs/net/ipnet-1.1.1.2/app/dhcpc-1.0.1.11/cdf/00comp_ipnet_appl_dhcp.cdf}
}


/*********************************
 Parameter DHCPC_REPLY_CALLBACK_HOOK 
 original object sources located at 
 $(WIND_BASE)/pkgs/net/ipnet-1.1.1.2/app/dhcpc-1.0.1.11/cdf/00comp_ipnet_appl_dhcp.cdf 
**********************************/
Parameter	DHCPC_REPLY_CALLBACK_HOOK {
		LAYER += Layer::IPNET_DHCPC
		LAYER_SOURCE		{$(WIND_BASE)/pkgs/net/ipnet-1.1.1.2/app/dhcpc-1.0.1.11/cdf/00comp_ipnet_appl_dhcp.cdf}
}


/*********************************
 Parameter DHCPC_BOOTP_MODE 
 original object sources located at 
 $(WIND_BASE)/pkgs/net/ipnet-1.1.1.2/app/dhcpc-1.0.1.11/cdf/00comp_ipnet_appl_dhcp.cdf 
**********************************/
Parameter	DHCPC_BOOTP_MODE {
		LAYER += Layer::IPNET_DHCPC
		LAYER_SOURCE		{$(WIND_BASE)/pkgs/net/ipnet-1.1.1.2/app/dhcpc-1.0.1.11/cdf/00comp_ipnet_appl_dhcp.cdf}
}


/*********************************
 Parameter DHCPC_BOOT_FILENAME 
 original object sources located at 
 $(WIND_BASE)/pkgs/net/ipnet-1.1.1.2/app/dhcpc-1.0.1.11/cdf/00comp_ipnet_appl_dhcp.cdf 
**********************************/
Parameter	DHCPC_BOOT_FILENAME {
		LAYER += Layer::IPNET_DHCPC
		LAYER_SOURCE		{$(WIND_BASE)/pkgs/net/ipnet-1.1.1.2/app/dhcpc-1.0.1.11/cdf/00comp_ipnet_appl_dhcp.cdf}
}


/*********************************
 Parameter DHCPC_SERVER_HOSTNAME 
 original object sources located at 
 $(WIND_BASE)/pkgs/net/ipnet-1.1.1.2/app/dhcpc-1.0.1.11/cdf/00comp_ipnet_appl_dhcp.cdf 
**********************************/
Parameter	DHCPC_SERVER_HOSTNAME {
		LAYER += Layer::IPNET_DHCPC
		LAYER_SOURCE		{$(WIND_BASE)/pkgs/net/ipnet-1.1.1.2/app/dhcpc-1.0.1.11/cdf/00comp_ipnet_appl_dhcp.cdf}
}


/*********************************
 Parameter DHCPC_OPTION_HOSTNAME 
 original object sources located at 
 $(WIND_BASE)/pkgs/net/ipnet-1.1.1.2/app/dhcpc-1.0.1.11/cdf/00comp_ipnet_appl_dhcp.cdf 
**********************************/
Parameter	DHCPC_OPTION_HOSTNAME {
		LAYER += Layer::IPNET_DHCPC
		LAYER_SOURCE		{$(WIND_BASE)/pkgs/net/ipnet-1.1.1.2/app/dhcpc-1.0.1.11/cdf/00comp_ipnet_appl_dhcp.cdf}
}


/*********************************
 Parameter DHCPC_OPTION_NETMASK 
 original object sources located at 
 $(WIND_BASE)/pkgs/net/ipnet-1.1.1.2/app/dhcpc-1.0.1.11/cdf/00comp_ipnet_appl_dhcp.cdf 
**********************************/
Parameter	DHCPC_OPTION_NETMASK {
		LAYER += Layer::IPNET_DHCPC
		LAYER_SOURCE		{$(WIND_BASE)/pkgs/net/ipnet-1.1.1.2/app/dhcpc-1.0.1.11/cdf/00comp_ipnet_appl_dhcp.cdf}
}


/*********************************
 Parameter DHCPC_OPTION_VENDOR_CLASS_ID 
 original object sources located at 
 $(WIND_BASE)/pkgs/net/ipnet-1.1.1.2/app/dhcpc-1.0.1.11/cdf/00comp_ipnet_appl_dhcp.cdf 
**********************************/
Parameter	DHCPC_OPTION_VENDOR_CLASS_ID {
		LAYER += Layer::IPNET_DHCPC
		LAYER_SOURCE		{$(WIND_BASE)/pkgs/net/ipnet-1.1.1.2/app/dhcpc-1.0.1.11/cdf/00comp_ipnet_appl_dhcp.cdf}
}


/*********************************
 Parameter DHCPC_OPTION_IPADDRESS_LEASE_TIME 
 original object sources located at 
 $(WIND_BASE)/pkgs/net/ipnet-1.1.1.2/app/dhcpc-1.0.1.11/cdf/00comp_ipnet_appl_dhcp.cdf 
**********************************/
Parameter	DHCPC_OPTION_IPADDRESS_LEASE_TIME {
		LAYER += Layer::IPNET_DHCPC
		LAYER_SOURCE		{$(WIND_BASE)/pkgs/net/ipnet-1.1.1.2/app/dhcpc-1.0.1.11/cdf/00comp_ipnet_appl_dhcp.cdf}
}


/*********************************
 Parameter DHCPC_OPTION_VI_VENDOR_CLASS 
 original object sources located at 
 $(WIND_BASE)/pkgs/net/ipnet-1.1.1.2/app/dhcpc-1.0.1.11/cdf/00comp_ipnet_appl_dhcp.cdf 
**********************************/
Parameter	DHCPC_OPTION_VI_VENDOR_CLASS {
		LAYER += Layer::IPNET_DHCPC
		LAYER_SOURCE		{$(WIND_BASE)/pkgs/net/ipnet-1.1.1.2/app/dhcpc-1.0.1.11/cdf/00comp_ipnet_appl_dhcp.cdf}
}


/*********************************
 Parameter DHCPC_REMOVE_EXISTING_ADDRESSES 
 original object sources located at 
 $(WIND_BASE)/pkgs/net/ipnet-1.1.1.2/app/dhcpc-1.0.1.11/cdf/00comp_ipnet_appl_dhcp.cdf 
**********************************/
Parameter	DHCPC_REMOVE_EXISTING_ADDRESSES {
		LAYER += Layer::IPNET_DHCPC
		LAYER_SOURCE		{$(WIND_BASE)/pkgs/net/ipnet-1.1.1.2/app/dhcpc-1.0.1.11/cdf/00comp_ipnet_appl_dhcp.cdf}
}


/*********************************
 Parameter DHCPC_REMOVE_LEASED_ADDRESS 
 original object sources located at 
 $(WIND_BASE)/pkgs/net/ipnet-1.1.1.2/app/dhcpc-1.0.1.11/cdf/00comp_ipnet_appl_dhcp.cdf 
**********************************/
Parameter	DHCPC_REMOVE_LEASED_ADDRESS {
		LAYER += Layer::IPNET_DHCPC
		LAYER_SOURCE		{$(WIND_BASE)/pkgs/net/ipnet-1.1.1.2/app/dhcpc-1.0.1.11/cdf/00comp_ipnet_appl_dhcp.cdf}
}


/*********************************
 Parameter DHCPC_AUTO_DISABLE 
 original object sources located at 
 $(WIND_BASE)/pkgs/net/ipnet-1.1.1.2/app/dhcpc-1.0.1.11/cdf/00comp_ipnet_appl_dhcp.cdf 
**********************************/
Parameter	DHCPC_AUTO_DISABLE {
		LAYER += Layer::IPNET_DHCPC
		LAYER_SOURCE		{$(WIND_BASE)/pkgs/net/ipnet-1.1.1.2/app/dhcpc-1.0.1.11/cdf/00comp_ipnet_appl_dhcp.cdf}
}


/*********************************
 Parameter DHCPC_TTL 
 original object sources located at 
 $(WIND_BASE)/pkgs/net/ipnet-1.1.1.2/app/dhcpc-1.0.1.11/cdf/00comp_ipnet_appl_dhcp.cdf 
**********************************/
Parameter	DHCPC_TTL {
		LAYER += Layer::IPNET_DHCPC
		LAYER_SOURCE		{$(WIND_BASE)/pkgs/net/ipnet-1.1.1.2/app/dhcpc-1.0.1.11/cdf/00comp_ipnet_appl_dhcp.cdf}
}


/*********************************
 Parameter DHCPC_OPTION_MAX_MESSAGE_SIZE 
 original object sources located at 
 $(WIND_BASE)/pkgs/net/ipnet-1.1.1.2/app/dhcpc-1.0.1.11/cdf/00comp_ipnet_appl_dhcp.cdf 
**********************************/
Parameter	DHCPC_OPTION_MAX_MESSAGE_SIZE {
		LAYER += Layer::IPNET_DHCPC
		LAYER_SOURCE		{$(WIND_BASE)/pkgs/net/ipnet-1.1.1.2/app/dhcpc-1.0.1.11/cdf/00comp_ipnet_appl_dhcp.cdf}
}


/*********************************
 Parameter DHCPC_OPTION_USER_SPECIFIED 
 original object sources located at 
 $(WIND_BASE)/pkgs/net/ipnet-1.1.1.2/app/dhcpc-1.0.1.11/cdf/00comp_ipnet_appl_dhcp.cdf 
**********************************/
Parameter	DHCPC_OPTION_USER_SPECIFIED {
		LAYER += Layer::IPNET_DHCPC
		LAYER_SOURCE		{$(WIND_BASE)/pkgs/net/ipnet-1.1.1.2/app/dhcpc-1.0.1.11/cdf/00comp_ipnet_appl_dhcp.cdf}
}


/*********************************
 Parameter DHCPC_IF_INFORMATION_ONLY_LIST 
 original object sources located at 
 $(WIND_BASE)/pkgs/net/ipnet-1.1.1.2/app/dhcpc-1.0.1.11/cdf/00comp_ipnet_appl_dhcp.cdf 
**********************************/
Parameter	DHCPC_IF_INFORMATION_ONLY_LIST {
		LAYER += Layer::IPNET_DHCPC
		LAYER_SOURCE		{$(WIND_BASE)/pkgs/net/ipnet-1.1.1.2/app/dhcpc-1.0.1.11/cdf/00comp_ipnet_appl_dhcp.cdf}
}


/*********************************
 Parameter DHCPC_FLAGS_BIT_BROADCAST 
 original object sources located at 
 $(WIND_BASE)/pkgs/net/ipnet-1.1.1.2/app/dhcpc-1.0.1.11/cdf/00comp_ipnet_appl_dhcp.cdf 
**********************************/
Parameter	DHCPC_FLAGS_BIT_BROADCAST {
		LAYER += Layer::IPNET_DHCPC
		LAYER_SOURCE		{$(WIND_BASE)/pkgs/net/ipnet-1.1.1.2/app/dhcpc-1.0.1.11/cdf/00comp_ipnet_appl_dhcp.cdf}
}


/*********************************
 Parameter DHCPC_TASK_PRIORITY 
 original object sources located at 
 $(WIND_BASE)/pkgs/net/ipnet-1.1.1.2/app/dhcpc-1.0.1.11/cdf/00comp_ipnet_appl_dhcp.cdf 
**********************************/
Parameter	DHCPC_TASK_PRIORITY {
		LAYER += Layer::IPNET_DHCPC
		LAYER_SOURCE		{$(WIND_BASE)/pkgs/net/ipnet-1.1.1.2/app/dhcpc-1.0.1.11/cdf/00comp_ipnet_appl_dhcp.cdf}
}


/*********************************
 Parameter DHCPC_DEBUG_ENABLE 
 original object sources located at 
 $(WIND_BASE)/pkgs/net/ipnet-1.1.1.2/app/dhcpc-1.0.1.11/cdf/00comp_ipnet_appl_dhcp.cdf 
**********************************/
Parameter	DHCPC_DEBUG_ENABLE {
		LAYER += Layer::IPNET_DHCPC
		LAYER_SOURCE		{$(WIND_BASE)/pkgs/net/ipnet-1.1.1.2/app/dhcpc-1.0.1.11/cdf/00comp_ipnet_appl_dhcp.cdf}
}


/*********************************
 Parameter DHCPC_CFGFILE 
 original object sources located at 
 $(WIND_BASE)/pkgs/net/ipnet-1.1.1.2/app/dhcpc-1.0.1.11/cdf/00comp_ipnet_appl_dhcp.cdf 
**********************************/
Parameter	DHCPC_CFGFILE {
		LAYER += Layer::IPNET_DHCPC
		LAYER_SOURCE		{$(WIND_BASE)/pkgs/net/ipnet-1.1.1.2/app/dhcpc-1.0.1.11/cdf/00comp_ipnet_appl_dhcp.cdf}
}


/*********************************
 SubProject DHCPC_CFGFILE_EXAMPLE 
 original object sources located at 
 $(WIND_BASE)/pkgs/net/ipnet-1.1.1.2/app/dhcpc-1.0.1.11/cdf/00comp_ipnet_appl_dhcp.cdf 
**********************************/
SubProject	DHCPC_CFGFILE_EXAMPLE {
		LAYER += Layer::IPNET_DHCPC
		LAYER_SOURCE		{$(WIND_BASE)/pkgs/net/ipnet-1.1.1.2/app/dhcpc-1.0.1.11/cdf/00comp_ipnet_appl_dhcp.cdf}
}