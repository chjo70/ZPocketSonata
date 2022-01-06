# Automatically generated file: do not edit

##########################
# SNMP_ENGINE Section
##########################


ifdef _WRS_CONFIG_SNMP_ENGINE
VSBL_SNMP_ENGINE_SRC = 
VSBL_SNMP_ENGINE_DEPEND = 

ifdef _WRS_CONFIG_SNMP_1_0_0_3_ENGINE_1_0_1_8
VSBL_SNMP_ENGINE_SRC += SNMP_ENGINE
VSBL_SNMP_ENGINE_DEPEND += IPNET_COREIP
SNMP_ENGINE_FASTBUILD = YES
VSBL_SNMP_ENGINE_PATH = $(WIND_BASE)/pkgs/app/snmp-1.0.0.3/engine-1.0.1.8
VSBL_SNMP_ENGINE_VERSION = SNMP_1_0_0_3_ENGINE_1_0_1_8
endif
endif

