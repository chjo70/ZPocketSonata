# Automatically generated file: do not edit

##########################
# USB_DWC2DR Section
##########################


ifdef _WRS_CONFIG_USB_DWC2DR
VSBL_USB_DWC2DR_SRC = 
VSBL_USB_DWC2DR_DEPEND = 

ifdef _WRS_CONFIG_USB_1_1_0_6_CTLR_1_2_0_4_DWC2DR_1_0_2_3
VSBL_USB_DWC2DR_SRC += USB_DWC2DR
VSBL_USB_DWC2DR_DEPEND += USB_CCORE
VSBL_USB_DWC2DR_DEPEND += USB_HCORE
ifdef _WRS_CONFIG_VXBUS
VSBL_USB_DWC2DR_DEPEND += USB_PHY
endif
USB_DWC2DR_FASTBUILD = YES
VSBL_USB_DWC2DR_PATH = $(WIND_BASE)/pkgs/connectivity/usb-1.1.0.6/ctlr/dwc2dr-1.0.2.3
VSBL_USB_DWC2DR_VERSION = USB_1_1_0_6_CTLR_1_2_0_4_DWC2DR_1_0_2_3
endif
endif

