# Automatically generated file: do not edit

##########################
# DSI Section
##########################


ifdef _WRS_CONFIG_DSI
VSBL_DSI_SRC = 
VSBL_DSI_DEPEND = 

ifdef _WRS_CONFIG_DSI_1_0_0_1
ifdef _WRS_CONFIG_DSI_DSI_KERNEL
VSBL_DSI_SRC += DSI_DSI_KERNEL
endif
ifdef _WRS_CONFIG_DSI_DSI_USER
VSBL_DSI_SRC += DSI_DSI_USER
endif
VSBL_DSI_SRC += DSI
DSI_FASTBUILD = YES
VSBL_DSI_PATH = $(WIND_BASE)/pkgs/ipc/dsi-1.0.0.1
VSBL_DSI_VERSION = DSI_1_0_0_1
endif
endif

