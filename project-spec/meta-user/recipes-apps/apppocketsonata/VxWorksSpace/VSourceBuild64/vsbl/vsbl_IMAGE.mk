# Automatically generated file: do not edit

##########################
# IMAGE Section
##########################


ifdef _WRS_CONFIG_IMAGE
VSBL_IMAGE_SRC = 
VSBL_IMAGE_DEPEND = 

ifdef _WRS_CONFIG_IMAGE_1_0_0_2
ifdef _WRS_CONFIG_IMAGE_JPEG
VSBL_IMAGE_SRC += IMAGE_JPEG
endif
ifdef _WRS_CONFIG_IMAGE_PNG
VSBL_IMAGE_SRC += IMAGE_PNG
endif
VSBL_IMAGE_SRC += IMAGE
IMAGE_FASTBUILD = YES
VSBL_IMAGE_PATH = $(WIND_BASE)/pkgs/ui/image-1.0.0.2
VSBL_IMAGE_VERSION = IMAGE_1_0_0_2
endif
endif

