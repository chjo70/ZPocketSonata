# Automatically generated file: do not edit

##########################
# FSAPI Section
##########################


ifdef _WRS_CONFIG_FSAPI
VSBL_FSAPI_SRC = 
VSBL_FSAPI_DEPEND = 

ifdef _WRS_CONFIG_FSAPI_1_0_0_1
ifdef _WRS_CONFIG_FSAPI_USR
VSBL_FSAPI_SRC += FSAPI_USR
endif
ifdef _WRS_CONFIG_FSAPI_UTIL
VSBL_FSAPI_SRC += FSAPI_UTIL
endif
VSBL_FSAPI_SRC += FSAPI
FSAPI_FASTBUILD = YES
VSBL_FSAPI_PATH = $(WIND_BASE)/pkgs/storage/api-1.0.0.1
VSBL_FSAPI_VERSION = FSAPI_1_0_0_1
endif
endif

