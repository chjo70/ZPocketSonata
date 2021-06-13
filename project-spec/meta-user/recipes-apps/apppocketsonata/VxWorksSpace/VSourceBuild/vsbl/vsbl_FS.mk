# Automatically generated file: do not edit

##########################
# FS Section
##########################


ifdef _WRS_CONFIG_FS
VSBL_FS_SRC = 
VSBL_FS_DEPEND = 

ifdef _WRS_CONFIG_FS_1_0_0_2
ifdef _WRS_CONFIG_FS_CDROMFS
VSBL_FS_SRC += FS_CDROMFS
endif
ifdef _WRS_CONFIG_FS_CORE
VSBL_FS_SRC += FS_CORE
endif
ifdef _WRS_CONFIG_FS_COMMON
VSBL_FS_SRC += FS_COMMON
endif
ifdef _WRS_CONFIG_FS_DEVFS
VSBL_FS_SRC += FS_DEVFS
endif
ifdef _WRS_CONFIG_FS_VDFS
VSBL_FS_SRC += FS_VDFS
endif
ifdef _WRS_CONFIG_FS_VFS
VSBL_FS_SRC += FS_VFS
endif
ifdef _WRS_CONFIG_FS_DOSFS
VSBL_FS_SRC += FS_DOSFS
endif
ifdef _WRS_CONFIG_FS_HRFS
VSBL_FS_SRC += FS_HRFS
endif
ifdef _WRS_CONFIG_FS_NFS
VSBL_FS_SRC += FS_NFS
endif
ifdef _WRS_CONFIG_FS_ROMFS
VSBL_FS_SRC += FS_ROMFS
endif
ifdef _WRS_CONFIG_FS_VRFS
VSBL_FS_SRC += FS_VRFS
endif
VSBL_FS_SRC += FS
FS_FASTBUILD = YES
VSBL_FS_PATH = $(WIND_BASE)/pkgs/storage/fs-1.0.0.2
VSBL_FS_VERSION = FS_1_0_0_2
endif
endif

