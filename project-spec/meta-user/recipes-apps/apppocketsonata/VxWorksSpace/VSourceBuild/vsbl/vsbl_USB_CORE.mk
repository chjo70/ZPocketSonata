# Automatically generated file: do not edit

##########################
# USB_CORE Section
##########################


ifdef _WRS_CONFIG_USB_CORE
VSBL_USB_CORE_SRC = 
VSBL_USB_CORE_DEPEND = 

ifdef _WRS_CONFIG_USB_1_1_0_6_CORE_1_0_3_0
VSBL_USB_CORE_SRC += USB_CORE
VSBL_USB_CORE_DEPEND += CORE_KERNEL
VSBL_USB_CORE_DEPEND += LANG_LIB_LIBC_LIBC_KERNEL
USB_CORE_FASTBUILD = YES
VSBL_USB_CORE_PATH = $(WIND_BASE)/pkgs/connectivity/usb-1.1.0.6/core-1.0.3.0
VSBL_USB_CORE_VERSION = USB_1_1_0_6_CORE_1_0_3_0
endif
endif

