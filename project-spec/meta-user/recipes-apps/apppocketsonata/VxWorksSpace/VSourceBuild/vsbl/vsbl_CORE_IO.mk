# Automatically generated file: do not edit

##########################
# CORE_IO Section
##########################


ifdef _WRS_CONFIG_CORE_IO
VSBL_CORE_IO_SRC = 
VSBL_CORE_IO_DEPEND = 

ifdef _WRS_CONFIG_CORE_IO_1_2_7_1
ifdef _WRS_CONFIG_CORE_IO_VXTEST
VSBL_CORE_IO_SRC += CORE_IO_VXTEST
endif
VSBL_CORE_IO_SRC += CORE_IO
ifdef _WRS_CONFIG_BOARDLIB
VSBL_CORE_IO_DEPEND += BOARDLIB
endif
ifdef _WRS_CONFIG_BOARDLIB*
VSBL_CORE_IO_DEPEND += BOARDLIB
endif
ifdef _WRS_CONFIG_CONFIG_LEGACY
VSBL_CORE_IO_DEPEND += CONFIG_LEGACY
endif
ifdef _WRS_CONFIG_CONFIG_LEGACY*
VSBL_CORE_IO_DEPEND += CONFIG_LEGACY
endif
VSBL_CORE_IO_DEPEND += CORE_KERNEL
ifdef _WRS_CONFIG_SYSCALLS_VXWORKS
VSBL_CORE_IO_DEPEND += SYSCALLS_VXWORKS
endif
ifdef _WRS_CONFIG_SYSCALLS_VXWORKS
VSBL_CORE_IO_DEPEND += SYSCALLS_VXWORKS
endif
ifdef _WRS_CONFIG_SYSCALLS_VXWORKS*
VSBL_CORE_IO_DEPEND += SYSCALLS_VXWORKS
endif
ifdef _WRS_CONFIG_SYSCALLS_VXWORKS
VSBL_CORE_IO_DEPEND += SYSCALLS_VXWORKS
endif
ifdef _WRS_CONFIG_SYSCALLS_VXWORKS*
VSBL_CORE_IO_DEPEND += SYSCALLS_VXWORKS
endif
VSBL_CORE_IO_DEPEND += CORE_KERNEL
VSBL_CORE_IO_DEPEND += CORE_KERNEL
VSBL_CORE_IO_DEPEND += CORE_KERNEL
VSBL_CORE_IO_DEPEND += CORE_KERNEL
VSBL_CORE_IO_DEPEND += CORE_KERNEL
VSBL_CORE_IO_DEPEND += CORE_KERNEL
CORE_IO_FASTBUILD = YES
VSBL_CORE_IO_PATH = $(WIND_BASE)/pkgs/os/core/io-1.2.7.1
VSBL_CORE_IO_VERSION = CORE_IO_1_2_7_1
endif
endif
