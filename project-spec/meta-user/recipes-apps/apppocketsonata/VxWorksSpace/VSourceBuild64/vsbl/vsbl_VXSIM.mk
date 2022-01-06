# Automatically generated file: do not edit

##########################
# VXSIM Section
##########################


ifdef _WRS_CONFIG_VXSIM
VSBL_VXSIM_SRC = 
VSBL_VXSIM_DEPEND = 

ifdef _WRS_CONFIG_VXSIM_1_0_7_9
ifdef _WRS_CONFIG_VXSIM_KERNEL
VSBL_VXSIM_SRC += VXSIM_KERNEL
endif
ifdef _WRS_CONFIG_VXSIM_USER
VSBL_VXSIM_SRC += VXSIM_USER
endif
VSBL_VXSIM_SRC += VXSIM
VSBL_VXSIM_DEPEND += CORE_KERNEL
VXSIM_FASTBUILD = YES
VSBL_VXSIM_PATH = $(WIND_BASE)/pkgs/os/arch/simulator-1.0.7.9
VSBL_VXSIM_VERSION = VXSIM_1_0_7_9
endif
endif

