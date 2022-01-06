# Automatically generated file: do not edit

##########################
# USB_PHY Section
##########################


ifdef _WRS_CONFIG_USB_PHY
VSBL_USB_PHY_SRC = 
VSBL_USB_PHY_DEPEND = 

ifdef _WRS_CONFIG_USB_1_1_0_6_PHY_1_0_6_2
VSBL_USB_PHY_SRC += USB_PHY
VSBL_USB_PHY_DEPEND += USB_CORE
VSBL_USB_PHY_DEPEND += VXBUS
USB_PHY_FASTBUILD = YES
VSBL_USB_PHY_PATH = $(WIND_BASE)/pkgs/connectivity/usb-1.1.0.6/phy-1.0.6.2
VSBL_USB_PHY_VERSION = USB_1_1_0_6_PHY_1_0_6_2
endif
endif

