# Automatically generated file: do not edit

##########################
# SDMMC_SDHC Section
##########################


ifdef _WRS_CONFIG_SDMMC_SDHC
VSBL_SDMMC_SDHC_SRC = 
VSBL_SDMMC_SDHC_DEPEND = 

ifdef _WRS_CONFIG_SDMMC_1_0_1_3_HOST_1_0_0_4_SDHC_1_0_5_1
VSBL_SDMMC_SDHC_SRC += SDMMC_SDHC
VSBL_SDMMC_SDHC_DEPEND += ERF
VSBL_SDMMC_SDHC_DEPEND += SDMMC_CORE
SDMMC_SDHC_FASTBUILD = YES
VSBL_SDMMC_SDHC_PATH = $(WIND_BASE)/pkgs/connectivity/sdmmc-1.0.1.3/host/sdhc-1.0.5.1
VSBL_SDMMC_SDHC_VERSION = SDMMC_1_0_1_3_HOST_1_0_0_4_SDHC_1_0_5_1
endif
endif

