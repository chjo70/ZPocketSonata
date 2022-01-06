# Automatically generated file: do not edit

##########################
# TILCON Section
##########################


ifdef _WRS_CONFIG_TILCON
VSBL_TILCON_SRC = 
VSBL_TILCON_DEPEND = 

ifdef _WRS_CONFIG_TILCON_7_0_0_1
ifdef _WRS_CONFIG_TILCON_DEMO
VSBL_TILCON_SRC += TILCON_DEMO
endif
ifdef _WRS_CONFIG_TILCON_KERNEL
VSBL_TILCON_SRC += TILCON_KERNEL
endif
VSBL_TILCON_SRC += TILCON
TILCON_FASTBUILD = YES
VSBL_TILCON_PATH = $(WIND_BASE)/pkgs/ui/tilcon-7.0.0.1
VSBL_TILCON_VERSION = TILCON_7_0_0_1
endif
endif

