# Automatically generated file: do not edit

##########################
# CORE_KERNEL Section
##########################


ifdef _WRS_CONFIG_CORE_KERNEL
VSBL_CORE_KERNEL_SRC = 
VSBL_CORE_KERNEL_DEPEND = 

ifdef _WRS_CONFIG_CORE_KERNEL_1_2_5_1
ifdef _WRS_CONFIG_CORE_KERNEL_VXTEST
VSBL_CORE_KERNEL_SRC += CORE_KERNEL_VXTEST
endif
VSBL_CORE_KERNEL_SRC += CORE_KERNEL
VSBL_CORE_KERNEL_DEPEND += SYSCALLS_VXWORKS
VSBL_CORE_KERNEL_DEPEND += SYSCALLS_VXWORKS
VSBL_CORE_KERNEL_DEPEND += SYSCALLS_VXWORKS
VSBL_CORE_KERNEL_DEPEND += SYSCALLS_VXWORKS
CORE_KERNEL_FASTBUILD = YES
VSBL_CORE_KERNEL_PATH = $(WIND_BASE)/pkgs/os/core/kernel-1.2.5.1
VSBL_CORE_KERNEL_VERSION = CORE_KERNEL_1_2_5_1
endif
endif

