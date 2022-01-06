# Automatically generated file: do not edit

##########################
# USB_OTG Section
##########################


ifdef _WRS_CONFIG_USB_OTG
VSBL_USB_OTG_SRC = 
VSBL_USB_OTG_DEPEND = 

ifdef _WRS_CONFIG_USB_1_1_0_6_OTG_1_0_0_8
VSBL_USB_OTG_SRC += USB_OTG
VSBL_USB_OTG_DEPEND += USB_HCORE
VSBL_USB_OTG_DEPEND += USB_TCORE
USB_OTG_FASTBUILD = YES
VSBL_USB_OTG_PATH = $(WIND_BASE)/pkgs/connectivity/usb-1.1.0.6/otg-1.0.0.8
VSBL_USB_OTG_VERSION = USB_1_1_0_6_OTG_1_0_0_8
endif
endif

