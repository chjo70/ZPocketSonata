# Automatically generated file: do not edit

##########################
# RPC Section
##########################


ifdef _WRS_CONFIG_RPC
VSBL_RPC_SRC = 
VSBL_RPC_DEPEND = 

ifdef _WRS_CONFIG_RPC_1_0_0_12
VSBL_RPC_SRC += RPC
VSBL_RPC_DEPEND += IPNET_COREIP
VSBL_RPC_DEPEND += SOCKET
VSBL_RPC_DEPEND += CORE_KERNEL
RPC_FASTBUILD = YES
VSBL_RPC_PATH = $(WIND_BASE)/pkgs/os/service/rpc-1.0.0.12
VSBL_RPC_VERSION = RPC_1_0_0_12
endif
endif

