# Automatically generated file: do not edit

##########################
# OPENSSL_FIPS Section
##########################


ifdef _WRS_CONFIG_OPENSSL_FIPS
VSBL_OPENSSL_FIPS_SRC = 
VSBL_OPENSSL_FIPS_DEPEND = 

ifdef _WRS_CONFIG_OPENSSL_FIPS_1_1_0_1
VSBL_OPENSSL_FIPS_SRC += OPENSSL_FIPS
VSBL_OPENSSL_FIPS_DEPEND += OPENSSL
VSBL_OPENSSL_FIPS_DEPEND += SEC_CRYPTO
VSBL_OPENSSL_FIPS_DEPEND += SHELL
OPENSSL_FIPS_FASTBUILD = YES
VSBL_OPENSSL_FIPS_PATH = $(WIND_BASE)/pkgs/security/openssl-fips-2.0-1.1.0.1
VSBL_OPENSSL_FIPS_VERSION = OPENSSL_FIPS_1_1_0_1
endif
endif
