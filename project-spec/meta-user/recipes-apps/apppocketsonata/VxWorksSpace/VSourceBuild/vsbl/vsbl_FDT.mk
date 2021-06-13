# Automatically generated file: do not edit

##########################
# FDT Section
##########################


ifdef _WRS_CONFIG_FDT
VSBL_FDT_SRC = 
VSBL_FDT_DEPEND = 

ifdef _WRS_CONFIG_FDT_1_0_9_6
VSBL_FDT_SRC += FDT
ifdef _WRS_CONFIG_END_DRV
VSBL_FDT_DEPEND += END_DRV
endif
ifdef _WRS_CONFIG_END_DRV*
VSBL_FDT_DEPEND += END_DRV
endif
FDT_FASTBUILD = YES
VSBL_FDT_PATH = $(WIND_BASE)/pkgs/os/firmware/fdt-1.0.9.6
VSBL_FDT_VERSION = FDT_1_0_9_6
endif
endif

