# Automatically generated file: do not edit

##########################
# ARM_ARMV8A Section
##########################


ifdef _WRS_CONFIG_ARM_ARMV8A
VSBL_ARM_ARMV8A_SRC = 
VSBL_ARM_ARMV8A_DEPEND = 

ifdef _WRS_CONFIG_ARM_1_1_10_2_KERNEL_1_0_13_2_ARMV8A_1_0_1_2
VSBL_ARM_ARMV8A_SRC += ARM_ARMV8A
VSBL_ARM_ARMV8A_DEPEND += ARM_ARMBASE
ifdef _WRS_CONFIG_LOADER
VSBL_ARM_ARMV8A_DEPEND += LOADER
endif
ifdef _WRS_CONFIG_LOADER*
VSBL_ARM_ARMV8A_DEPEND += LOADER
endif
ARM_ARMV8A_FASTBUILD = YES
VSBL_ARM_ARMV8A_PATH = $(WIND_BASE)/pkgs/os/arch/arm-1.1.10.2/kernel/armv8a
VSBL_ARM_ARMV8A_VERSION = ARM_1_1_10_2_KERNEL_1_0_13_2_ARMV8A_1_0_1_2
endif
endif

