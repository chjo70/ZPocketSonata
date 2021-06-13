# Automatically generated file: do not edit

##########################
# IEEE1394 Section
##########################


ifdef _WRS_CONFIG_IEEE1394
VSBL_IEEE1394_SRC = 
VSBL_IEEE1394_DEPEND = 

ifdef _WRS_CONFIG_IEEE1394_1_1_0_1
ifdef _WRS_CONFIG_IEEE1394_STACK
VSBL_IEEE1394_SRC += IEEE1394_STACK
endif
VSBL_IEEE1394_SRC += IEEE1394
IEEE1394_FASTBUILD = YES
VSBL_IEEE1394_PATH = $(WIND_BASE)/pkgs/connectivity/ieee1394-1.1.0.1
VSBL_IEEE1394_VERSION = IEEE1394_1_1_0_1
endif
endif

