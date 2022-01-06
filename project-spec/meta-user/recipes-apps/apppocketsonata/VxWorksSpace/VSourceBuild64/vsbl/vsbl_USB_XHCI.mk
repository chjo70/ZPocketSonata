# Automatically generated file: do not edit

##########################
# USB_XHCI Section
##########################


ifdef _WRS_CONFIG_USB_XHCI
VSBL_USB_XHCI_SRC = 
VSBL_USB_XHCI_DEPEND = 

ifdef _WRS_CONFIG_USB_1_1_0_6_CTLR_1_2_0_4_XHCI_1_0_3_4
VSBL_USB_XHCI_SRC += USB_XHCI
VSBL_USB_XHCI_DEPEND += USB_CCORE
VSBL_USB_XHCI_DEPEND += USB_HCORE
ifdef _WRS_CONFIG_VXBUS
VSBL_USB_XHCI_DEPEND += USB_PHY
endif
USB_XHCI_FASTBUILD = YES
VSBL_USB_XHCI_PATH = $(WIND_BASE)/pkgs/connectivity/usb-1.1.0.6/ctlr/xhci-1.0.3.4
VSBL_USB_XHCI_VERSION = USB_1_1_0_6_CTLR_1_2_0_4_XHCI_1_0_3_4
endif
endif

