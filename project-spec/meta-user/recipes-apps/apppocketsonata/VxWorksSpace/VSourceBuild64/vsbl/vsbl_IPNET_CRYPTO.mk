# Automatically generated file: do not edit

##########################
# IPNET_CRYPTO Section
##########################


ifdef _WRS_CONFIG_IPNET_CRYPTO
VSBL_IPNET_CRYPTO_SRC = 
VSBL_IPNET_CRYPTO_DEPEND = 

ifdef _WRS_CONFIG_IPNET_1_1_1_2_CRYPTO_1_0_0_10
ifdef _WRS_CONFIG_IPNET_IPCRYPTO
VSBL_IPNET_CRYPTO_SRC += IPNET_IPCRYPTO
endif
ifdef _WRS_CONFIG_IPNET_IPFREESCALE
VSBL_IPNET_CRYPTO_SRC += IPNET_IPFREESCALE
endif
ifdef _WRS_CONFIG_IPNET_IPHWCRYPTO
VSBL_IPNET_CRYPTO_SRC += IPNET_IPHWCRYPTO
endif
VSBL_IPNET_CRYPTO_SRC += IPNET_CRYPTO
IPNET_CRYPTO_FASTBUILD = YES
VSBL_IPNET_CRYPTO_PATH = $(WIND_BASE)/pkgs/net/ipnet-1.1.1.2/crypto-1.0.0.10
VSBL_IPNET_CRYPTO_VERSION = IPNET_1_1_1_2_CRYPTO_1_0_0_10
endif
endif
