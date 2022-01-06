# Automatically generated file: do not edit

##########################
# FS_VDFS Section
##########################


ifdef _WRS_CONFIG_FS_VDFS
VSBL_FS_VDFS_SRC = 
VSBL_FS_VDFS_DEPEND = 

ifdef _WRS_CONFIG_FS_1_0_0_2_CORE_1_0_0_2_VDFS_1_0_2_0
VSBL_FS_VDFS_SRC += FS_VDFS
VSBL_FS_VDFS_DEPEND += BDM_XBD
VSBL_FS_VDFS_DEPEND += ERF
VSBL_FS_VDFS_DEPEND += FS_COMMON
VSBL_FS_VDFS_DEPEND += CORE_IO
FS_VDFS_FASTBUILD = YES
VSBL_FS_VDFS_PATH = $(WIND_BASE)/pkgs/storage/fs-1.0.0.2/core/vdfs-1.0.2.0
VSBL_FS_VDFS_VERSION = FS_1_0_0_2_CORE_1_0_0_2_VDFS_1_0_2_0
endif
endif

