# Automatically generated file: do not edit

##########################
# PPC_KERNEL Section
##########################


ifdef _WRS_CONFIG_PPC_KERNEL
VSBL_PPC_KERNEL_SRC = 
VSBL_PPC_KERNEL_DEPEND = 

ifdef _WRS_CONFIG_PPC_1_3_1_5_KERNEL_1_0_5_5
ifdef _WRS_CONFIG_PPC_60x
VSBL_PPC_KERNEL_SRC += PPC_60x
endif
ifdef _WRS_CONFIG_PPC_BASE
VSBL_PPC_KERNEL_SRC += PPC_BASE
endif
ifdef _WRS_CONFIG_PPC_DRV
VSBL_PPC_KERNEL_SRC += PPC_DRV
endif
ifdef _WRS_CONFIG_PPC_E500
VSBL_PPC_KERNEL_SRC += PPC_E500
endif
VSBL_PPC_KERNEL_SRC += PPC_KERNEL
VSBL_PPC_KERNEL_DEPEND += CORE_KERNEL
VSBL_PPC_KERNEL_DEPEND += CORE_KERNEL
PPC_KERNEL_FASTBUILD = YES
VSBL_PPC_KERNEL_PATH = $(WIND_BASE)/pkgs/os/arch/ppc-1.3.1.5/kernel
VSBL_PPC_KERNEL_VERSION = PPC_1_3_1_5_KERNEL_1_0_5_5
endif
endif

