# Automatically generated file: do not edit

##########################
# IPNET_SNTP Section
##########################


ifdef _WRS_CONFIG_IPNET_SNTP
VSBL_IPNET_SNTP_SRC = 
VSBL_IPNET_SNTP_DEPEND = 

ifdef _WRS_CONFIG_IPNET_1_1_1_2_SNTP_1_0_1_0
VSBL_IPNET_SNTP_SRC += IPNET_SNTP
VSBL_IPNET_SNTP_DEPEND += IPNET_COREIP
IPNET_SNTP_FASTBUILD = YES
VSBL_IPNET_SNTP_PATH = $(WIND_BASE)/pkgs/net/ipnet-1.1.1.2/app/sntp-1.0.1.0
VSBL_IPNET_SNTP_VERSION = IPNET_1_1_1_2_SNTP_1_0_1_0
endif
endif

