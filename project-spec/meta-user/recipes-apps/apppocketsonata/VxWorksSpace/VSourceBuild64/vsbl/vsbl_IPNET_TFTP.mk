# Automatically generated file: do not edit

##########################
# IPNET_TFTP Section
##########################


ifdef _WRS_CONFIG_IPNET_TFTP
VSBL_IPNET_TFTP_SRC = 
VSBL_IPNET_TFTP_DEPEND = 

ifdef _WRS_CONFIG_IPNET_1_1_1_2_TFTP_1_0_1_7
VSBL_IPNET_TFTP_SRC += IPNET_TFTP
VSBL_IPNET_TFTP_DEPEND += IPNET_COREIP
IPNET_TFTP_FASTBUILD = YES
VSBL_IPNET_TFTP_PATH = $(WIND_BASE)/pkgs/net/ipnet-1.1.1.2/app/tftp-1.0.1.7
VSBL_IPNET_TFTP_VERSION = IPNET_1_1_1_2_TFTP_1_0_1_7
endif
endif

