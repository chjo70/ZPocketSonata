# Automatically generated file: do not edit

##########################
# IA Section
##########################


ifdef _WRS_CONFIG_IA
VSBL_IA_SRC = 
VSBL_IA_DEPEND = 

ifdef _WRS_CONFIG_IA_1_2_4_1
ifdef _WRS_CONFIG_IA_KERNEL
VSBL_IA_SRC += IA_KERNEL
endif
ifdef _WRS_CONFIG_IA_USER
VSBL_IA_SRC += IA_USER
endif
ifdef _WRS_CONFIG_IA_VXTEST
VSBL_IA_SRC += IA_VXTEST
endif
VSBL_IA_SRC += IA
VSBL_IA_DEPEND += CORE_KERNEL
VSBL_IA_DEPEND += CORE_KERNEL
VSBL_IA_DEPEND += CORE_KERNEL
VSBL_IA_DEPEND += CORE_KERNEL
VSBL_IA_DEPEND += CORE_KERNEL
IA_FASTBUILD = YES
VSBL_IA_PATH = $(WIND_BASE)/pkgs/os/arch/ia-1.2.4.1
VSBL_IA_VERSION = IA_1_2_4_1
endif
endif

