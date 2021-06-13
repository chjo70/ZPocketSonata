# Automatically generated file: do not edit

##########################
# FS_DEVFS Section
##########################


ifdef _WRS_CONFIG_FS_DEVFS
VSBL_FS_DEVFS_SRC = 
VSBL_FS_DEVFS_DEPEND = 

ifdef _WRS_CONFIG_FS_1_0_0_2_CORE_1_0_0_2_DEVFS_1_0_1_0
VSBL_FS_DEVFS_SRC += FS_DEVFS
VSBL_FS_DEVFS_DEPEND += BDM_XBD
VSBL_FS_DEVFS_DEPEND += ERF
VSBL_FS_DEVFS_DEPEND += FS_COMMON
VSBL_FS_DEVFS_DEPEND += CORE_IO
FS_DEVFS_FASTBUILD = YES
VSBL_FS_DEVFS_PATH = $(WIND_BASE)/pkgs/storage/fs-1.0.0.2/core/devfs-1.0.1.0
VSBL_FS_DEVFS_VERSION = FS_1_0_0_2_CORE_1_0_0_2_DEVFS_1_0_1_0
endif
endif

