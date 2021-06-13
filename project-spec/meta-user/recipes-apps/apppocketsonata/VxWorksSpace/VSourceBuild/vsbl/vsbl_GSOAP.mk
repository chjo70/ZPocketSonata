# Automatically generated file: do not edit

##########################
# GSOAP Section
##########################


ifdef _WRS_CONFIG_GSOAP
VSBL_GSOAP_SRC = 
VSBL_GSOAP_DEPEND = 

ifdef _WRS_CONFIG_GSOAP_2_8_15_1
ifdef _WRS_CONFIG_GSOAP_CORE
VSBL_GSOAP_SRC += GSOAP_CORE
endif
ifdef _WRS_CONFIG_GSOAP_DEMO
VSBL_GSOAP_SRC += GSOAP_DEMO
endif
ifdef _WRS_CONFIG_GSOAP_SOAP
VSBL_GSOAP_SRC += GSOAP_SOAP
endif
VSBL_GSOAP_SRC += GSOAP
GSOAP_FASTBUILD = YES
VSBL_GSOAP_PATH = $(WIND_BASE)/pkgs/app/gsoap-2.8.15.1
VSBL_GSOAP_VERSION = GSOAP_2_8_15_1
endif
endif

