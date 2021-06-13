# Automatically generated file: do not edit

##########################
# USB_HELPER Section
##########################


ifdef _WRS_CONFIG_USB_HELPER
VSBL_USB_HELPER_SRC = 
VSBL_USB_HELPER_DEPEND = 

ifdef _WRS_CONFIG_USB_1_1_0_6_HOST_1_0_0_4_CLASS_1_0_0_3_HELPER_1_0_0_7
VSBL_USB_HELPER_SRC += USB_HELPER
VSBL_USB_HELPER_DEPEND += USB_CLASS
VSBL_USB_HELPER_DEPEND += USB_HCORE
USB_HELPER_FASTBUILD = YES
VSBL_USB_HELPER_PATH = $(WIND_BASE)/pkgs/connectivity/usb-1.1.0.6/host/class/helper-1.0.0.7
VSBL_USB_HELPER_VERSION = USB_1_1_0_6_HOST_1_0_0_4_CLASS_1_0_0_3_HELPER_1_0_0_7
endif
endif

