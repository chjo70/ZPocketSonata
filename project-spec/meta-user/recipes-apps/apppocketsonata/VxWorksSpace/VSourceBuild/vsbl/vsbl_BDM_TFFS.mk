# Automatically generated file: do not edit

##########################
# BDM_TFFS Section
##########################


ifdef _WRS_CONFIG_BDM_TFFS
VSBL_BDM_TFFS_SRC = 
VSBL_BDM_TFFS_DEPEND = 

ifdef _WRS_CONFIG_BDM_1_0_1_3_FLASH_1_0_0_1_TFFS_1_0_1_3
VSBL_BDM_TFFS_SRC += BDM_TFFS
VSBL_BDM_TFFS_DEPEND += BDM_MTD
VSBL_BDM_TFFS_DEPEND += BDM_XBD
BDM_TFFS_FASTBUILD = YES
VSBL_BDM_TFFS_PATH = $(WIND_BASE)/pkgs/storage/bdm-1.0.1.3/flash/tffs-1.0.1.3
VSBL_BDM_TFFS_VERSION = BDM_1_0_1_3_FLASH_1_0_0_1_TFFS_1_0_1_3
endif
endif

