# Automatically generated file: do not edit

##########################
# USB_KEYBOARD Section
##########################


ifdef _WRS_CONFIG_USB_KEYBOARD
VSBL_USB_KEYBOARD_SRC = 
VSBL_USB_KEYBOARD_DEPEND = 

ifdef _WRS_CONFIG_USB_1_1_0_6_HOST_1_0_0_4_CLASS_1_0_0_3_KEYBOARD_1_0_0_9
VSBL_USB_KEYBOARD_SRC += USB_KEYBOARD
VSBL_USB_KEYBOARD_DEPEND += USB_HID
USB_KEYBOARD_FASTBUILD = YES
VSBL_USB_KEYBOARD_PATH = $(WIND_BASE)/pkgs/connectivity/usb-1.1.0.6/host/class/keyboard-1.0.0.9
VSBL_USB_KEYBOARD_VERSION = USB_1_1_0_6_HOST_1_0_0_4_CLASS_1_0_0_3_KEYBOARD_1_0_0_9
endif
endif

