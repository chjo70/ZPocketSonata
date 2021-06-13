# Automatically generated file: do not edit

##########################
# USB_PRINTER Section
##########################


ifdef _WRS_CONFIG_USB_PRINTER
VSBL_USB_PRINTER_SRC = 
VSBL_USB_PRINTER_DEPEND = 

ifdef _WRS_CONFIG_USB_1_1_0_6_HOST_1_0_0_4_CLASS_1_0_0_3_PRINTER_1_0_0_6
VSBL_USB_PRINTER_SRC += USB_PRINTER
VSBL_USB_PRINTER_DEPEND += USB_HELPER
USB_PRINTER_FASTBUILD = YES
VSBL_USB_PRINTER_PATH = $(WIND_BASE)/pkgs/connectivity/usb-1.1.0.6/host/class/printer-1.0.0.6
VSBL_USB_PRINTER_VERSION = USB_1_1_0_6_HOST_1_0_0_4_CLASS_1_0_0_3_PRINTER_1_0_0_6
endif
endif

