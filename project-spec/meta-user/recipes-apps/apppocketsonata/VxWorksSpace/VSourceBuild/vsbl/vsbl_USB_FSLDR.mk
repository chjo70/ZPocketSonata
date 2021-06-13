# Automatically generated file: do not edit

##########################
# USB_FSLDR Section
##########################


ifdef _WRS_CONFIG_USB_FSLDR
VSBL_USB_FSLDR_SRC = 
VSBL_USB_FSLDR_DEPEND = 

ifdef _WRS_CONFIG_USB_1_1_0_6_CTLR_1_2_0_4_FSLDR_1_0_2_5
VSBL_USB_FSLDR_SRC += USB_FSLDR
VSBL_USB_FSLDR_DEPEND += USB_CCORE
VSBL_USB_FSLDR_DEPEND += USB_TCORE
ifdef _WRS_CONFIG_VXBUS
VSBL_USB_FSLDR_DEPEND += USB_PHY
endif
USB_FSLDR_FASTBUILD = YES
VSBL_USB_FSLDR_PATH = $(WIND_BASE)/pkgs/connectivity/usb-1.1.0.6/ctlr/fsldr-1.0.2.5
VSBL_USB_FSLDR_VERSION = USB_1_1_0_6_CTLR_1_2_0_4_FSLDR_1_0_2_5
endif
endif

