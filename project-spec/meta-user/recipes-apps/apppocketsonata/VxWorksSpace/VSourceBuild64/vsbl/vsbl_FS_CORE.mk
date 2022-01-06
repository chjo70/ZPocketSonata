# Automatically generated file: do not edit

##########################
# FS_CORE Section
##########################


ifdef _WRS_CONFIG_FS_CORE
VSBL_FS_CORE_SRC = 
VSBL_FS_CORE_DEPEND = 

ifdef _WRS_CONFIG_FS_1_0_0_2_CORE_1_0_0_2
ifdef _WRS_CONFIG_FS_COMMON
VSBL_FS_CORE_SRC += FS_COMMON
endif
ifdef _WRS_CONFIG_FS_DEVFS
VSBL_FS_CORE_SRC += FS_DEVFS
endif
ifdef _WRS_CONFIG_FS_VDFS
VSBL_FS_CORE_SRC += FS_VDFS
endif
ifdef _WRS_CONFIG_FS_VFS
VSBL_FS_CORE_SRC += FS_VFS
endif
VSBL_FS_CORE_SRC += FS_CORE
FS_CORE_FASTBUILD = YES
VSBL_FS_CORE_PATH = $(WIND_BASE)/pkgs/storage/fs-1.0.0.2/core
VSBL_FS_CORE_VERSION = FS_1_0_0_2_CORE_1_0_0_2
endif
endif

