# Automatically generated file: do not edit

##########################
# USB_SERIAL Section
##########################


ifdef _WRS_CONFIG_USB_SERIAL
VSBL_USB_SERIAL_SRC = 
VSBL_USB_SERIAL_DEPEND = 

ifdef _WRS_CONFIG_USB_1_1_0_6_HOST_1_0_0_4_CLASS_1_0_0_3_SERIAL_1_0_0_9
VSBL_USB_SERIAL_SRC += USB_SERIAL
VSBL_USB_SERIAL_DEPEND += USB_HELPER
USB_SERIAL_FASTBUILD = YES
VSBL_USB_SERIAL_PATH = $(WIND_BASE)/pkgs/connectivity/usb-1.1.0.6/host/class/serial-1.0.0.9
VSBL_USB_SERIAL_VERSION = USB_1_1_0_6_HOST_1_0_0_4_CLASS_1_0_0_3_SERIAL_1_0_0_9
endif
endif

