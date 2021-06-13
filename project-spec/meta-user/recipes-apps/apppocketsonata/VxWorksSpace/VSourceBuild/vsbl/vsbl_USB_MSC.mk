# Automatically generated file: do not edit

##########################
# USB_MSC Section
##########################


ifdef _WRS_CONFIG_USB_MSC
VSBL_USB_MSC_SRC = 
VSBL_USB_MSC_DEPEND = 

ifdef _WRS_CONFIG_USB_1_1_0_6_TARGET_1_1_0_1_FUNCTION_1_1_0_1_MSC_1_0_1_10
VSBL_USB_MSC_SRC += USB_MSC
VSBL_USB_MSC_DEPEND += BDM_XBD
VSBL_USB_MSC_DEPEND += ERF
VSBL_USB_MSC_DEPEND += FS_COMMON
VSBL_USB_MSC_DEPEND += USB_HLP
USB_MSC_FASTBUILD = YES
VSBL_USB_MSC_PATH = $(WIND_BASE)/pkgs/connectivity/usb-1.1.0.6/target/function/msc-1.0.1.10
VSBL_USB_MSC_VERSION = USB_1_1_0_6_TARGET_1_1_0_1_FUNCTION_1_1_0_1_MSC_1_0_1_10
endif
endif

