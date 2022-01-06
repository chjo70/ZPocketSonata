# Automatically generated file: do not edit

##########################
# USB_UVC Section
##########################


ifdef _WRS_CONFIG_USB_UVC
VSBL_USB_UVC_SRC = 
VSBL_USB_UVC_DEPEND = 

ifdef _WRS_CONFIG_USB_1_1_0_6_HOST_1_0_0_4_CLASS_1_0_0_3_UVC_1_0_0_0
VSBL_USB_UVC_SRC += USB_UVC
VSBL_USB_UVC_DEPEND += USB_CORE
VSBL_USB_UVC_DEPEND += USB_HELPER
USB_UVC_FASTBUILD = YES
VSBL_USB_UVC_PATH = $(WIND_BASE)/pkgs/connectivity/usb-1.1.0.6/host/class/uvc-1.0.0.0
VSBL_USB_UVC_VERSION = USB_1_1_0_6_HOST_1_0_0_4_CLASS_1_0_0_3_UVC_1_0_0_0
endif
endif

