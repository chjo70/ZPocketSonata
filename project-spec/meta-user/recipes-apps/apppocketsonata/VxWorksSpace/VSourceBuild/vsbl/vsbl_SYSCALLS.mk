# Automatically generated file: do not edit

##########################
# SYSCALLS Section
##########################


ifdef _WRS_CONFIG_SYSCALLS
VSBL_SYSCALLS_SRC = 
VSBL_SYSCALLS_DEPEND = 

ifdef _WRS_CONFIG_SYSCALLS_1_0_14_0
ifdef _WRS_CONFIG_SYSCALLS_CUSTOM
VSBL_SYSCALLS_SRC += SYSCALLS_CUSTOM
endif
ifdef _WRS_CONFIG_SYSCALLS_VXWORKS
VSBL_SYSCALLS_SRC += SYSCALLS_VXWORKS
endif
VSBL_SYSCALLS_SRC += SYSCALLS
SYSCALLS_FASTBUILD = YES
VSBL_SYSCALLS_PATH = $(WIND_BASE)/pkgs/os/core/syscalls-1.0.14.0
VSBL_SYSCALLS_VERSION = SYSCALLS_1_0_14_0
endif
endif

