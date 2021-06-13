# Automatically generated file: do not edit

##########################
# USB_PLX Section
##########################


ifdef _WRS_CONFIG_USB_PLX
VSBL_USB_PLX_SRC = 
VSBL_USB_PLX_DEPEND = 

ifdef _WRS_CONFIG_USB_1_1_0_6_CTLR_1_2_0_4_PLX_1_1_0_7
VSBL_USB_PLX_SRC += USB_PLX
VSBL_USB_PLX_DEPEND += USB_CCORE
VSBL_USB_PLX_DEPEND += USB_TCORE
USB_PLX_FASTBUILD = YES
VSBL_USB_PLX_PATH = $(WIND_BASE)/pkgs/connectivity/usb-1.1.0.6/ctlr/plx-1.1.0.7
VSBL_USB_PLX_VERSION = USB_1_1_0_6_CTLR_1_2_0_4_PLX_1_1_0_7
endif
endif

