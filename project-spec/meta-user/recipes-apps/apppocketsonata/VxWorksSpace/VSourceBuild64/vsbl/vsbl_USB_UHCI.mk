# Automatically generated file: do not edit

##########################
# USB_UHCI Section
##########################


ifdef _WRS_CONFIG_USB_UHCI
VSBL_USB_UHCI_SRC = 
VSBL_USB_UHCI_DEPEND = 

ifdef _WRS_CONFIG_USB_1_1_0_6_CTLR_1_2_0_4_UHCI_1_0_1_8
VSBL_USB_UHCI_SRC += USB_UHCI
VSBL_USB_UHCI_DEPEND += USB_CCORE
VSBL_USB_UHCI_DEPEND += USB_HCORE
USB_UHCI_FASTBUILD = YES
VSBL_USB_UHCI_PATH = $(WIND_BASE)/pkgs/connectivity/usb-1.1.0.6/ctlr/uhci-1.0.1.8
VSBL_USB_UHCI_VERSION = USB_1_1_0_6_CTLR_1_2_0_4_UHCI_1_0_1_8
endif
endif

