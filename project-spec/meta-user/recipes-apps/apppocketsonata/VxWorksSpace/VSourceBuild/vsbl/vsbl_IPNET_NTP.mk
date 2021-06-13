# Automatically generated file: do not edit

##########################
# IPNET_NTP Section
##########################


ifdef _WRS_CONFIG_IPNET_NTP
VSBL_IPNET_NTP_SRC = 
VSBL_IPNET_NTP_DEPEND = 

ifdef _WRS_CONFIG_IPNET_1_1_1_2_NTP_1_2_0_6
VSBL_IPNET_NTP_SRC += IPNET_NTP
VSBL_IPNET_NTP_DEPEND += IPNET_COREIP
VSBL_IPNET_NTP_DEPEND += IPNET_SNTP
IPNET_NTP_FASTBUILD = YES
VSBL_IPNET_NTP_PATH = $(WIND_BASE)/pkgs/net/ipnet-1.1.1.2/app/ntp-1.2.0.6
VSBL_IPNET_NTP_VERSION = IPNET_1_1_1_2_NTP_1_2_0_6
endif
endif

