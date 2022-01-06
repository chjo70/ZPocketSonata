# Automatically generated file: do not edit

##########################
# USB_HID Section
##########################


ifdef _WRS_CONFIG_USB_HID
VSBL_USB_HID_SRC = 
VSBL_USB_HID_DEPEND = 

ifdef _WRS_CONFIG_USB_1_1_0_6_HOST_1_0_0_4_CLASS_1_0_0_3_HID_1_0_0_5
VSBL_USB_HID_SRC += USB_HID
VSBL_USB_HID_DEPEND += USB_HELPER
USB_HID_FASTBUILD = YES
VSBL_USB_HID_PATH = $(WIND_BASE)/pkgs/connectivity/usb-1.1.0.6/host/class/hid-1.0.0.5
VSBL_USB_HID_VERSION = USB_1_1_0_6_HOST_1_0_0_4_CLASS_1_0_0_3_HID_1_0_0_5
endif
endif

