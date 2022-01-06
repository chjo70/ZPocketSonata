# Automatically generated file: do not edit

##########################
# USB_OHCI Section
##########################


ifdef _WRS_CONFIG_USB_OHCI
VSBL_USB_OHCI_SRC = 
VSBL_USB_OHCI_DEPEND = 

ifdef _WRS_CONFIG_USB_1_1_0_6_CTLR_1_2_0_4_OHCI_1_0_1_10
VSBL_USB_OHCI_SRC += USB_OHCI
VSBL_USB_OHCI_DEPEND += USB_CCORE
VSBL_USB_OHCI_DEPEND += USB_HCORE
ifdef _WRS_CONFIG_VXBUS
VSBL_USB_OHCI_DEPEND += USB_PHY
endif
USB_OHCI_FASTBUILD = YES
VSBL_USB_OHCI_PATH = $(WIND_BASE)/pkgs/connectivity/usb-1.1.0.6/ctlr/ohci-1.0.1.10
VSBL_USB_OHCI_VERSION = USB_1_1_0_6_CTLR_1_2_0_4_OHCI_1_0_1_10
endif
endif

