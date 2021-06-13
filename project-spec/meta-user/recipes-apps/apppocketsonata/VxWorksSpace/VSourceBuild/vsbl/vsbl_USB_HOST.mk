# Automatically generated file: do not edit

##########################
# USB_HOST Section
##########################


ifdef _WRS_CONFIG_USB_HOST
VSBL_USB_HOST_SRC = 
VSBL_USB_HOST_DEPEND = 

ifdef _WRS_CONFIG_USB_1_1_0_6_HOST_1_0_0_4
ifdef _WRS_CONFIG_USB_CLASS
VSBL_USB_HOST_SRC += USB_CLASS
endif
ifdef _WRS_CONFIG_USB_HCORE
VSBL_USB_HOST_SRC += USB_HCORE
endif
VSBL_USB_HOST_SRC += USB_HOST
USB_HOST_FASTBUILD = YES
VSBL_USB_HOST_PATH = $(WIND_BASE)/pkgs/connectivity/usb-1.1.0.6/host
VSBL_USB_HOST_VERSION = USB_1_1_0_6_HOST_1_0_0_4
endif
endif

