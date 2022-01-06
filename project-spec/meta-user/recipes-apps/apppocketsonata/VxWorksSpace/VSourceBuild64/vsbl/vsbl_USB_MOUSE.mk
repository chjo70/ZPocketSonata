# Automatically generated file: do not edit

##########################
# USB_MOUSE Section
##########################


ifdef _WRS_CONFIG_USB_MOUSE
VSBL_USB_MOUSE_SRC = 
VSBL_USB_MOUSE_DEPEND = 

ifdef _WRS_CONFIG_USB_1_1_0_6_HOST_1_0_0_4_CLASS_1_0_0_3_MOUSE_1_0_0_5
VSBL_USB_MOUSE_SRC += USB_MOUSE
VSBL_USB_MOUSE_DEPEND += USB_HID
USB_MOUSE_FASTBUILD = YES
VSBL_USB_MOUSE_PATH = $(WIND_BASE)/pkgs/connectivity/usb-1.1.0.6/host/class/mouse-1.0.0.5
VSBL_USB_MOUSE_VERSION = USB_1_1_0_6_HOST_1_0_0_4_CLASS_1_0_0_3_MOUSE_1_0_0_5
endif
endif

