# Automatically generated file: do not edit

##########################
# SDMMC_HOST Section
##########################


ifdef _WRS_CONFIG_SDMMC_HOST
VSBL_SDMMC_HOST_SRC = 
VSBL_SDMMC_HOST_DEPEND = 

ifdef _WRS_CONFIG_SDMMC_1_0_1_3_HOST_1_0_0_4
ifdef _WRS_CONFIG_SDMMC_SDHC
VSBL_SDMMC_HOST_SRC += SDMMC_SDHC
endif
ifdef _WRS_CONFIG_SDMMC_TIMMCHS
VSBL_SDMMC_HOST_SRC += SDMMC_TIMMCHS
endif
VSBL_SDMMC_HOST_SRC += SDMMC_HOST
SDMMC_HOST_FASTBUILD = YES
VSBL_SDMMC_HOST_PATH = $(WIND_BASE)/pkgs/connectivity/sdmmc-1.0.1.3/host
VSBL_SDMMC_HOST_VERSION = SDMMC_1_0_1_3_HOST_1_0_0_4
endif
endif

