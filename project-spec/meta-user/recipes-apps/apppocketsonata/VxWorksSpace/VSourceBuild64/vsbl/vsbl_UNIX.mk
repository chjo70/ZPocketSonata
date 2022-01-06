# Automatically generated file: do not edit

##########################
# UNIX Section
##########################


ifdef _WRS_CONFIG_UNIX
VSBL_UNIX_SRC = 
VSBL_UNIX_DEPEND = 

ifdef _WRS_CONFIG_UNIX_1_0_0_3
ifdef _WRS_CONFIG_UNIX_VXTEST
VSBL_UNIX_SRC += UNIX_VXTEST
endif
VSBL_UNIX_SRC += UNIX
VSBL_UNIX_DEPEND += SOCKET
UNIX_FASTBUILD = YES
VSBL_UNIX_PATH = $(WIND_BASE)/pkgs/os/utils/unix-1.0.0.3
VSBL_UNIX_VERSION = UNIX_1_0_0_3
endif
endif

