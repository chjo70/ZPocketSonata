# The file "vxWorks.makefile" is the external makefile fragment used by the
# Wind River Workbench to invoke the build process for vxWorks image builds.
# It contains all special rules for redirection to vxprj builds.

CONFIG_FILE_LIST := prjComps.h prjParams.h linkSyms.c prjConfig.c
PROJECT_FILE := $(wildcard *.wpj)

DEFAULT_BUILD_SPEC_LIST := default default_rom default_romCompress default_romResident
DEFAULT_BUILD_SPEC := default
VXWORKS_BIN := vxWorks.bin
VXWORKS_HEX := vxWorks.hex
ifneq ($(DEFAULT_BUILD_SPEC), $(BUILD_SPEC))
	BUILD_SPEC_LIST_CHECK := $(findstring $(BUILD_SPEC),$(DEFAULT_BUILD_SPEC_LIST))
	ifneq ($(BUILD_SPEC_LIST_CHECK),)
		VXWORKS_TYPE := $(subst $(DEFAULT_BUILD_SPEC),,$(BUILD_SPEC))
		VXWORKS_BIN := vxWorks$(VXWORKS_TYPE).bin
		VXWORKS_HEX := vxWorks$(VXWORKS_TYPE).hex
	endif
endif

$(CONFIG_FILE_LIST) : $(PROJECT_FILE)
	@echo "make: generating VxWorks configuration files...";\
	_PWD=`pwd`;\
	cd $(OBJ_DIR);\
	$(VXPRJ_BUILDCMD) BUILD_SPEC=$(BUILD_SPEC) ../$@;\
	cd "$$_PWD"

pre_recursion :: check_objectdir $(CONFIG_FILE_LIST)

external_clean :: check_objectdir
	@echo "make: removing targets and objects of `pwd`";\
	_PWD=`pwd`;\
	cd $(OBJ_DIR);\
	$(VXPRJ_BUILDCMD) BUILD_SPEC=$(BUILD_SPEC) WS_ROOT_DIR="$(WS_ROOT_DIR)" clean;\
	cd "$$_PWD";\
	rm -f $(wildcard $(OBJ_DIR)/*);\
	rm -f $(wildcard *.romfs);\
	rm -f $(wildcard *.lst);\
	rm -f vxWorks.include

target_vxWorks : check_objectdir $(CONFIG_FILE_LIST) subdirs_all
	@echo "building default vxWorks image of `pwd`";\
	cd $(OBJ_DIR);\
	$(VXPRJ_BUILDCMD) BUILD_SPEC=$(BUILD_SPEC) ROMFS_CONTENT="$(ROMFS_CONTENT)" SUB_TARGETS="$(SUB_TARGETS)" WS_ROOT_DIR="$(WS_ROOT_DIR)"

target_vxWorks.bin : target_vxWorks
	@echo "building binary vxWorks image of `pwd`";\
	cd $(OBJ_DIR);\
	$(VXPRJ_BUILDCMD) BUILD_SPEC=$(BUILD_SPEC) ROMFS_CONTENT="$(ROMFS_CONTENT)" SUB_TARGETS="$(SUB_TARGETS)" WS_ROOT_DIR="$(WS_ROOT_DIR)" $(VXWORKS_BIN)

target_vxWorks.hex : target_vxWorks
	@echo "building hex record vxWorks image of `pwd`";\
	cd $(OBJ_DIR);\
	$(VXPRJ_BUILDCMD) BUILD_SPEC=$(BUILD_SPEC) ROMFS_CONTENT="$(ROMFS_CONTENT)" SUB_TARGETS="$(SUB_TARGETS)" WS_ROOT_DIR="$(WS_ROOT_DIR)" $(VXWORKS_HEX)

target_vxWorks% : target_vxWorks
	@echo "building vxWorks$* image of `pwd`";\
	cd $(OBJ_DIR);\
	$(VXPRJ_BUILDCMD) BUILD_SPEC=$(BUILD_SPEC) ROMFS_CONTENT="$(ROMFS_CONTENT)" SUB_TARGETS="$(SUB_TARGETS)" WS_ROOT_DIR="$(WS_ROOT_DIR)" vxWorks$*

target_uVxWorks : check_objectdir $(CONFIG_FILE_LIST) subdirs_all
	@echo "building uVxWorks image of `pwd`";\
	cd $(OBJ_DIR);\
	$(VXPRJ_BUILDCMD) BUILD_SPEC=$(BUILD_SPEC) ROMFS_CONTENT="$(ROMFS_CONTENT)" SUB_TARGETS="$(SUB_TARGETS)" WS_ROOT_DIR="$(WS_ROOT_DIR)" uVxWorks

# If during vxWorks image builds the link line limit is exceeded, uncomment
# the following make rules and use them instead of the corresponding make
# rules above.
# Note, that this only works since VxWorks 6.4.
#
#create_includefile :
#	@echo "override SUB_TARGETS := $(SUB_TARGETS)" > vxWorks.include
#
#target_vxWorks : create_includefile check_objectdir $(CONFIG_FILE_LIST) subdirs_all
#	@echo "building default vxWorks image of `pwd`";\
#	cd $(OBJ_DIR);\
#	$(VXPRJ_BUILDCMD) BUILD_SPEC=$(BUILD_SPEC) ROMFS_CONTENT="$(ROMFS_CONTENT)" WRWB_VIP_MAKE_INCLUDE=../vxWorks.include WS_ROOT_DIR="$(WS_ROOT_DIR)"
#
#target_vxWorks.bin : target_vxWorks
#	@echo "building binary vxWorks image of `pwd`";\
#	cd $(OBJ_DIR);\
#	$(VXPRJ_BUILDCMD) BUILD_SPEC=$(BUILD_SPEC) ROMFS_CONTENT="$(ROMFS_CONTENT)" WRWB_VIP_MAKE_INCLUDE=../vxWorks.include WS_ROOT_DIR="$(WS_ROOT_DIR)" $(VXWORKS_BIN)
#
#target_vxWorks.hex : target_vxWorks
#	@echo "building hex record vxWorks image of `pwd`";\
#	cd $(OBJ_DIR);\
#	$(VXPRJ_BUILDCMD) BUILD_SPEC=$(BUILD_SPEC) ROMFS_CONTENT="$(ROMFS_CONTENT)" WRWB_VIP_MAKE_INCLUDE=../vxWorks.include WS_ROOT_DIR="$(WS_ROOT_DIR)" $(VXWORKS_HEX)
#
#target_vxWorks% : target_vxWorks
#	@echo "building vxWorks$* image of `pwd`";\
#	cd $(OBJ_DIR);\
#	$(VXPRJ_BUILDCMD) BUILD_SPEC=$(BUILD_SPEC) ROMFS_CONTENT="$(ROMFS_CONTENT)" WRWB_VIP_MAKE_INCLUDE=../vxWorks.include WS_ROOT_DIR="$(WS_ROOT_DIR)" vxWorks$*

target_% : check_objectdir
	@cd $(OBJ_DIR);\
	$(VXPRJ_BUILDCMD) BUILD_SPEC=$(BUILD_SPEC) WS_ROOT_DIR="$(WS_ROOT_DIR)" $*

compile_%.o : check_objectdir
	@cd $(OBJ_DIR);\
	$(VXPRJ_BUILDCMD) BUILD_SPEC=$(BUILD_SPEC) $*.o
