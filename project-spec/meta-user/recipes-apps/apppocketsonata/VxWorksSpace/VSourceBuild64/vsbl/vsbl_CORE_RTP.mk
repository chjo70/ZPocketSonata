# Automatically generated file: do not edit

##########################
# CORE_RTP Section
##########################


ifdef _WRS_CONFIG_CORE_RTP
VSBL_CORE_RTP_SRC = 
VSBL_CORE_RTP_DEPEND = 

ifdef _WRS_CONFIG_CORE_RTP_1_1_4_1
ifdef _WRS_CONFIG_CORE_RTP_VXTEST
VSBL_CORE_RTP_SRC += CORE_RTP_VXTEST
endif
VSBL_CORE_RTP_SRC += CORE_RTP
VSBL_CORE_RTP_DEPEND += OSTOOLS
VSBL_CORE_RTP_DEPEND += CORE_KERNEL
VSBL_CORE_RTP_DEPEND += LOADER
VSBL_CORE_RTP_DEPEND += CORE_KERNEL
VSBL_CORE_RTP_DEPEND += CORE_KERNEL
VSBL_CORE_RTP_DEPEND += CORE_KERNEL
VSBL_CORE_RTP_DEPEND += SYSCALLS_VXWORKS
VSBL_CORE_RTP_DEPEND += CORE_KERNEL
VSBL_CORE_RTP_DEPEND += CORE_KERNEL
VSBL_CORE_RTP_DEPEND += CORE_KERNEL
CORE_RTP_FASTBUILD = YES
VSBL_CORE_RTP_PATH = $(WIND_BASE)/pkgs/os/core/rtp-1.1.4.1
VSBL_CORE_RTP_VERSION = CORE_RTP_1_1_4_1
endif
endif
