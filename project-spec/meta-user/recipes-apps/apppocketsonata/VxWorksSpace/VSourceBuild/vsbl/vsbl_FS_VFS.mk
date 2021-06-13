# Automatically generated file: do not edit

##########################
# FS_VFS Section
##########################


ifdef _WRS_CONFIG_FS_VFS
VSBL_FS_VFS_SRC = 
VSBL_FS_VFS_DEPEND = 

ifdef _WRS_CONFIG_FS_1_0_0_2_CORE_1_0_0_2_VFS_1_0_1_1
VSBL_FS_VFS_SRC += FS_VFS
VSBL_FS_VFS_DEPEND += BDM_XBD
VSBL_FS_VFS_DEPEND += FS_COMMON
VSBL_FS_VFS_DEPEND += CORE_IO
FS_VFS_FASTBUILD = YES
VSBL_FS_VFS_PATH = $(WIND_BASE)/pkgs/storage/fs-1.0.0.2/core/vfs-1.0.1.1
VSBL_FS_VFS_VERSION = FS_1_0_0_2_CORE_1_0_0_2_VFS_1_0_1_1
endif
endif

