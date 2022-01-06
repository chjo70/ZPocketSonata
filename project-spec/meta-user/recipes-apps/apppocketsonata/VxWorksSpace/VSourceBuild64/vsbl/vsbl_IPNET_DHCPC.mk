# Automatically generated file: do not edit

##########################
# IPNET_DHCPC Section
##########################


ifdef _WRS_CONFIG_IPNET_DHCPC
VSBL_IPNET_DHCPC_SRC = 
VSBL_IPNET_DHCPC_DEPEND = 

ifdef _WRS_CONFIG_IPNET_1_1_1_2_DHCPC_1_0_1_11
VSBL_IPNET_DHCPC_SRC += IPNET_DHCPC
VSBL_IPNET_DHCPC_DEPEND += IPNET_COREIP
IPNET_DHCPC_FASTBUILD = YES
VSBL_IPNET_DHCPC_PATH = $(WIND_BASE)/pkgs/net/ipnet-1.1.1.2/app/dhcpc-1.0.1.11
VSBL_IPNET_DHCPC_VERSION = IPNET_1_1_1_2_DHCPC_1_0_1_11
endif
endif

