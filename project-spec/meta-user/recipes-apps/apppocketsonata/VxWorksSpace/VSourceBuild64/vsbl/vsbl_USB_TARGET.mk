# Automatically generated file: do not edit

##########################
# USB_TARGET Section
##########################


ifdef _WRS_CONFIG_USB_TARGET
VSBL_USB_TARGET_SRC = 
VSBL_USB_TARGET_DEPEND = 

ifdef _WRS_CONFIG_USB_1_1_0_6_TARGET_1_1_0_1
ifdef _WRS_CONFIG_USB_FUNCTION
VSBL_USB_TARGET_SRC += USB_FUNCTION
endif
ifdef _WRS_CONFIG_USB_TCORE
VSBL_USB_TARGET_SRC += USB_TCORE
endif
VSBL_USB_TARGET_SRC += USB_TARGET
USB_TARGET_FASTBUILD = YES
VSBL_USB_TARGET_PATH = $(WIND_BASE)/pkgs/connectivity/usb-1.1.0.6/target
VSBL_USB_TARGET_VERSION = USB_1_1_0_6_TARGET_1_1_0_1
endif
endif

