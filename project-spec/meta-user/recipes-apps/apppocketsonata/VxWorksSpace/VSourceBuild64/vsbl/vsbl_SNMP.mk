# Automatically generated file: do not edit

##########################
# SNMP Section
##########################


ifdef _WRS_CONFIG_SNMP
VSBL_SNMP_SRC = 
VSBL_SNMP_DEPEND = 

ifdef _WRS_CONFIG_SNMP_1_0_0_3
ifdef _WRS_CONFIG_SNMP_AGENT
VSBL_SNMP_SRC += SNMP_AGENT
endif
ifdef _WRS_CONFIG_SNMP_ENGINE
VSBL_SNMP_SRC += SNMP_ENGINE
endif
ifdef _WRS_CONFIG_SNMP_WRSNMP
VSBL_SNMP_SRC += SNMP_WRSNMP
endif
VSBL_SNMP_SRC += SNMP
VSBL_SNMP_DEPEND += IPNET_COREIP
SNMP_FASTBUILD = YES
VSBL_SNMP_PATH = $(WIND_BASE)/pkgs/app/snmp-1.0.0.3
VSBL_SNMP_VERSION = SNMP_1_0_0_3
endif
endif

