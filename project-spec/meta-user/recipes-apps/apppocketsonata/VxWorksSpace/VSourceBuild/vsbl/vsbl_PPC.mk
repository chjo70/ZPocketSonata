# Automatically generated file: do not edit

##########################
# PPC Section
##########################


ifdef _WRS_CONFIG_PPC
VSBL_PPC_SRC = 
VSBL_PPC_DEPEND = 

ifdef _WRS_CONFIG_PPC_1_3_1_5
ifdef _WRS_CONFIG_PPC_KERNEL
VSBL_PPC_SRC += PPC_KERNEL
endif
ifdef _WRS_CONFIG_PPC_60x
VSBL_PPC_SRC += PPC_60x
endif
ifdef _WRS_CONFIG_PPC_BASE
VSBL_PPC_SRC += PPC_BASE
endif
ifdef _WRS_CONFIG_PPC_DRV
VSBL_PPC_SRC += PPC_DRV
endif
ifdef _WRS_CONFIG_PPC_E500
VSBL_PPC_SRC += PPC_E500
endif
ifdef _WRS_CONFIG_PPC_PPCMATH
VSBL_PPC_SRC += PPC_PPCMATH
endif
ifdef _WRS_CONFIG_PPC_USER
VSBL_PPC_SRC += PPC_USER
endif
VSBL_PPC_SRC += PPC
VSBL_PPC_DEPEND += CORE_KERNEL
VSBL_PPC_DEPEND += LOADER
PPC_FASTBUILD = YES
VSBL_PPC_PATH = $(WIND_BASE)/pkgs/os/arch/ppc-1.3.1.5
VSBL_PPC_VERSION = PPC_1_3_1_5
endif
endif

