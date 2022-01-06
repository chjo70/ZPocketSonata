# Automatically generated file: do not edit

##########################
# BDM_SIM Section
##########################


ifdef _WRS_CONFIG_BDM_SIM
VSBL_BDM_SIM_SRC = 
VSBL_BDM_SIM_DEPEND = 

ifdef _WRS_CONFIG_BDM_1_0_1_3_FLASH_1_0_0_1_SIM_1_0_1_1
VSBL_BDM_SIM_SRC += BDM_SIM
VSBL_BDM_SIM_DEPEND += BDM_MTD
VSBL_BDM_SIM_DEPEND += BDM_TFFS
BDM_SIM_FASTBUILD = YES
VSBL_BDM_SIM_PATH = $(WIND_BASE)/pkgs/storage/bdm-1.0.1.3/flash/sim-1.0.1.1
VSBL_BDM_SIM_VERSION = BDM_1_0_1_3_FLASH_1_0_0_1_SIM_1_0_1_1
endif
endif

