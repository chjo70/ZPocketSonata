# Automatically generated file: do not edit

##########################
# SHELL Section
##########################


ifdef _WRS_CONFIG_SHELL
VSBL_SHELL_SRC = 
VSBL_SHELL_DEPEND = 

ifdef _WRS_CONFIG_SHELL_1_1_6_1
ifdef _WRS_CONFIG_SHELL_VXTEST
VSBL_SHELL_SRC += SHELL_VXTEST
endif
VSBL_SHELL_SRC += SHELL
VSBL_SHELL_DEPEND += CORE_KERNEL
VSBL_SHELL_DEPEND += CORE_KERNEL
VSBL_SHELL_DEPEND += CORE_KERNEL
VSBL_SHELL_DEPEND += CORE_KERNEL
ifdef _WRS_CONFIG_USER_MANAGEMENT
VSBL_SHELL_DEPEND += USER_MANAGEMENT
endif
ifdef _WRS_CONFIG_USER_MANAGEMENT
VSBL_SHELL_DEPEND += USER_MANAGEMENT
endif
ifdef _WRS_CONFIG_USER_MANAGEMENT*
VSBL_SHELL_DEPEND += USER_MANAGEMENT
endif
VSBL_SHELL_DEPEND += OSTOOLS
SHELL_FASTBUILD = YES
VSBL_SHELL_PATH = $(WIND_BASE)/pkgs/os/utils/shell-1.1.6.1
VSBL_SHELL_VERSION = SHELL_1_1_6_1
endif
endif

