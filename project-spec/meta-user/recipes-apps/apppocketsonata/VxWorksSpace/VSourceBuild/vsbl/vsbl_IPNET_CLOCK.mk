# Automatically generated file: do not edit

##########################
# IPNET_CLOCK Section
##########################


ifdef _WRS_CONFIG_IPNET_CLOCK
VSBL_IPNET_CLOCK_SRC = 
VSBL_IPNET_CLOCK_DEPEND = 

ifdef _WRS_CONFIG_IPNET_1_1_1_2_TSN_1_0_3_0_CLOCK_1_0_1_0
VSBL_IPNET_CLOCK_SRC += IPNET_CLOCK
VSBL_IPNET_CLOCK_DEPEND += END_LIB
VSBL_IPNET_CLOCK_DEPEND += END
VSBL_IPNET_CLOCK_DEPEND += VXBUS_SUBSYSTEM
IPNET_CLOCK_FASTBUILD = YES
VSBL_IPNET_CLOCK_PATH = $(WIND_BASE)/pkgs/net/ipnet-1.1.1.2/tsn-1.0.3.0/clock
VSBL_IPNET_CLOCK_VERSION = IPNET_1_1_1_2_TSN_1_0_3_0_CLOCK_1_0_1_0
endif
endif

