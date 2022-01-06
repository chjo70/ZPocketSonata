# Automatically generated file: do not edit

##########################
# CAN Section
##########################


ifdef _WRS_CONFIG_CAN
VSBL_CAN_SRC = 
VSBL_CAN_DEPEND = 

ifdef _WRS_CONFIG_CAN_1_0_1_0
ifdef _WRS_CONFIG_CAN_CORE
VSBL_CAN_SRC += CAN_CORE
endif
ifdef _WRS_CONFIG_CAN_CTLR
VSBL_CAN_SRC += CAN_CTLR
endif
VSBL_CAN_SRC += CAN
VSBL_CAN_DEPEND += SOCKET
VSBL_CAN_DEPEND += VXBUS
CAN_FASTBUILD = YES
VSBL_CAN_PATH = $(WIND_BASE)/pkgs/connectivity/can-1.0.1.0
VSBL_CAN_VERSION = CAN_1_0_1_0
endif
endif

