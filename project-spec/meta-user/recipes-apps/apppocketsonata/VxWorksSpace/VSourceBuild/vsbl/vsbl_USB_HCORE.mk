# Automatically generated file: do not edit

##########################
# USB_HCORE Section
##########################


ifdef _WRS_CONFIG_USB_HCORE
VSBL_USB_HCORE_SRC = 
VSBL_USB_HCORE_DEPEND = 

ifdef _WRS_CONFIG_USB_1_1_0_6_HOST_1_0_0_4_HCORE_1_0_0_17
VSBL_USB_HCORE_SRC += USB_HCORE
VSBL_USB_HCORE_DEPEND += ERF
VSBL_USB_HCORE_DEPEND += USB_CORE
USB_HCORE_FASTBUILD = YES
VSBL_USB_HCORE_PATH = $(WIND_BASE)/pkgs/connectivity/usb-1.1.0.6/host/core-1.0.0.17
VSBL_USB_HCORE_VERSION = USB_1_1_0_6_HOST_1_0_0_4_HCORE_1_0_0_17
endif
endif

