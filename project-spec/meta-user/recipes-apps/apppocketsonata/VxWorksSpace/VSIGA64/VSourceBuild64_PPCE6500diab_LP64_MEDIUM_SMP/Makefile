# Wind River Workbench generated Makefile.
# Do not edit!!!
#
# The file ".wrmakefile" is the template used by the Wind River Workbench to
# generate the makefiles of this project. Add user-specific build targets and
# make rules only(!) in this project's ".wrmakefile" file. These will then be
# automatically dumped into the makefiles.

WIND_HOME := $(subst \,/,$(WIND_HOME))
WIND_BASE := $(subst \,/,$(WIND_BASE))
WIND_USR := $(subst \,/,$(WIND_USR))
WRVX_COMPBASE := $(subst \,/,$(WRVX_COMPBASE))
WIND_KRNL_MK := $(subst \,/,$(WIND_KRNL_MK))
WIND_USR_MK := $(subst \,/,$(WIND_USR_MK))
WIND_BUILD := $(subst \,/,$(WIND_BUILD))
WIND_BUILD_TOOL := $(subst \,/,$(WIND_BUILD_TOOL))

all : check_vsb pre_build main_all post_build

_clean ::
	@echo "make: removing targets and objects of `pwd`"

TRACE=0
TRACEON=$(TRACE:0=@)
TRACE_FLAG=$(TRACEON:1=)

JOBS?=1
TARGET_JOBS?=$(JOBS)

MAKEFILE := Makefile

FLEXIBLE_BUILD := 1

BUILD_SPEC = VSourceBuild64_PPCE6500diab_LP64_MEDIUM_SMP
DEBUG_MODE = 1
ifeq ($(DEBUG_MODE),1)
MODE_DIR := Debug
else
MODE_DIR := NonDebug
endif
OBJ_DIR := .
WS_ROOT_DIR := D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace64
PRJ_ROOT_DIR := D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSIGA64



#Global Build Macros
PROJECT_TYPE = DKM
DEFINES = 
EXPAND_DBG = 0
APICHECK_OPTIONS = -warning


#BuildSpec specific Build Macros
VX_CPU_FAMILY = ppc
CPU = PPCE6500
TOOL_FAMILY = diab
TOOL_VERSION = diab_5_9_6_1
_CC_VERSION = diab_5_9_6_5
TOOL = diab
TOOL_PATH = $(WIND_HOME)/compilers/diab-5.9.6.5/$(WIND_VX7_DIAB_HOST_TYPE)/bin
CC_ARCH_SPEC =  -tPPCLP64FV:vxworks7 -Xkeywords=0x0 -D_WRS_HARDWARE_FP -ffixed-r13 -I$(WIND_BASE)/pkgs/os/arch/ppc/kernel/base/h/arch/ppc/private/globRegs.h -Xcode-model-medium
VSB_DIR = $(PRJ_ROOT_DIR)/../VSourceBuild64
VSB_CONFIG_FILE = $(VSB_DIR)/h/config/vsbConfig.h
LIBPATH = 
LIBS = 
DKM_LONGCALL = -Xcode-absolute-far
BDGEN_VSB_INCLUDE = $(VSB_DIR)/h/config/auto.conf
APICHECK_CMD = apicheck.sh -r "$(VSB_DIR)/krnl/apicheck/forbidden_api.lst" -n "nmppc" -u -s "$<" "$@" $(APICHECK_OPTIONS)
APICHECK = 0

IDE_INCLUDES = -I$(VSB_DIR)/share/h -I$(VSB_DIR)/krnl/h/system -I$(VSB_DIR)/krnl/h/public -I$(PRJ_ROOT_DIR)/../../MSC/MSIGA 

IDE_LIBRARIES = 

IDE_DEFINES = -DCPU=_VX_$(CPU) -D_NO_SQLITE_ -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -D_WRS_VX_SMP -D_WRS_CONFIG_SMP -D_VSB_CONFIG_FILE=\"$(VSB_DIR)/h/config/vsbConfig.h\" -D__VXWORKS__ 



#BuildTool flags
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C-Compiler = -g -Xdebug-dwarf3
DEBUGFLAGS_C++-Compiler = -g -Xdebug-dwarf3
DEBUGFLAGS_Linker = -g -Xdebug-dwarf3
DEBUGFLAGS_Partial-Image-Linker = 
DEBUGFLAGS_Librarian = 
DEBUGFLAGS_Assembler = -g -Xdebug-dwarf3
else
DEBUGFLAGS_C-Compiler = -XO -Xsize-opt
DEBUGFLAGS_C++-Compiler = -XO -Xsize-opt
DEBUGFLAGS_Linker = -XO -Xsize-opt
DEBUGFLAGS_Partial-Image-Linker = 
DEBUGFLAGS_Librarian = 
DEBUGFLAGS_Assembler = -XO -Xsize-opt
endif


#Project Targets
PROJECT_TARGETS = VSIGA64/$(MODE_DIR)/VSIGA64.out \
	 VSIGA64_partialImage/$(MODE_DIR)/VSIGA64_partialImage.o


#Rules

# VSIGA64
ifeq ($(DEBUG_MODE),1)
VSIGA64/$(MODE_DIR)/% : DEBUGFLAGS_C-Compiler = -g -Xdebug-dwarf3
VSIGA64/$(MODE_DIR)/% : DEBUGFLAGS_C++-Compiler = -g -Xdebug-dwarf3
VSIGA64/$(MODE_DIR)/% : DEBUGFLAGS_Linker = -g -Xdebug-dwarf3
VSIGA64/$(MODE_DIR)/% : DEBUGFLAGS_Partial-Image-Linker = 
VSIGA64/$(MODE_DIR)/% : DEBUGFLAGS_Librarian = 
VSIGA64/$(MODE_DIR)/% : DEBUGFLAGS_Assembler = -g -Xdebug-dwarf3
else
VSIGA64/$(MODE_DIR)/% : DEBUGFLAGS_C-Compiler = -XO -Xsize-opt
VSIGA64/$(MODE_DIR)/% : DEBUGFLAGS_C++-Compiler = -XO -Xsize-opt
VSIGA64/$(MODE_DIR)/% : DEBUGFLAGS_Linker = -XO -Xsize-opt
VSIGA64/$(MODE_DIR)/% : DEBUGFLAGS_Partial-Image-Linker = 
VSIGA64/$(MODE_DIR)/% : DEBUGFLAGS_Librarian = 
VSIGA64/$(MODE_DIR)/% : DEBUGFLAGS_Assembler = -XO -Xsize-opt
endif
VSIGA64/$(MODE_DIR)/% : IDE_INCLUDES = -I$(VSB_DIR)/share/h -I$(VSB_DIR)/krnl/h/system -I$(VSB_DIR)/krnl/h/public -I$(PRJ_ROOT_DIR)/../../MSC/MSIGA 
VSIGA64/$(MODE_DIR)/% : IDE_LIBRARIES = 
VSIGA64/$(MODE_DIR)/% : IDE_DEFINES = -DCPU=_VX_$(CPU) -D_NO_SQLITE_ -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -D_WRS_VX_SMP -D_WRS_CONFIG_SMP -D_VSB_CONFIG_FILE=\"$(VSB_DIR)/h/config/vsbConfig.h\" -D__VXWORKS__ 
VSIGA64/$(MODE_DIR)/% : PROJECT_TYPE = DKM
VSIGA64/$(MODE_DIR)/% : DEFINES = 
VSIGA64/$(MODE_DIR)/% : EXPAND_DBG = 0
VSIGA64/$(MODE_DIR)/% : APICHECK_OPTIONS = -warning
VSIGA64/$(MODE_DIR)/% : VX_CPU_FAMILY = ppc
VSIGA64/$(MODE_DIR)/% : CPU = PPCE6500
VSIGA64/$(MODE_DIR)/% : TOOL_FAMILY = diab
VSIGA64/$(MODE_DIR)/% : TOOL_VERSION = diab_5_9_6_1
VSIGA64/$(MODE_DIR)/% : _CC_VERSION = diab_5_9_6_5
VSIGA64/$(MODE_DIR)/% : TOOL = diab
VSIGA64/$(MODE_DIR)/% : TOOL_PATH = $(WIND_HOME)/compilers/diab-5.9.6.5/$(WIND_VX7_DIAB_HOST_TYPE)/bin
VSIGA64/$(MODE_DIR)/% : CC_ARCH_SPEC =  -tPPCLP64FV:vxworks7 -Xkeywords=0x0 -D_WRS_HARDWARE_FP -ffixed-r13 -I$(WIND_BASE)/pkgs/os/arch/ppc/kernel/base/h/arch/ppc/private/globRegs.h -Xcode-model-medium
VSIGA64/$(MODE_DIR)/% : VSB_DIR = $(PRJ_ROOT_DIR)/../VSourceBuild64
VSIGA64/$(MODE_DIR)/% : VSB_CONFIG_FILE = $(VSB_DIR)/h/config/vsbConfig.h
VSIGA64/$(MODE_DIR)/% : LIBPATH = 
VSIGA64/$(MODE_DIR)/% : LIBS = 
VSIGA64/$(MODE_DIR)/% : DKM_LONGCALL = -Xcode-absolute-far
VSIGA64/$(MODE_DIR)/% : BDGEN_VSB_INCLUDE = $(VSB_DIR)/h/config/auto.conf
VSIGA64/$(MODE_DIR)/% : APICHECK_CMD = apicheck.sh -r "$(VSB_DIR)/krnl/apicheck/forbidden_api.lst" -n "nmppc" -u -s "$<" "$@" $(APICHECK_OPTIONS)
VSIGA64/$(MODE_DIR)/% : APICHECK = 0
VSIGA64/$(MODE_DIR)/% : OBJ_DIR := VSIGA64/$(MODE_DIR)

OBJECTS_VSIGA64 = VSIGA64_partialImage/$(MODE_DIR)/VSIGA64_partialImage.o

checkDirVSIGA64 : 
	mkdir -p VSIGA64/$(MODE_DIR)/
VSIGA64/$(MODE_DIR)/.VSIGA64Object.list: $(OBJECTS_VSIGA64) | checkDirVSIGA64
	$(file >$@,$^)
ifeq ($(TARGET_JOBS),1)
VSIGA64/$(MODE_DIR)/VSIGA64.out : VSIGA64/$(MODE_DIR)/.VSIGA64Object.list | check_objdirs
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@";rm -f "$@";$(TOOL_PATH)/ddump -Ng @VSIGA64/$(MODE_DIR)/.VSIGA64Object.list | tclsh $(WIND_BASE)/build/mk/tcl/munch.tcl -c ppc -tags $(VSB_DIR)/krnl/tags/dkm.tags > $(OBJ_DIR)/ctdt.c; $(TOOL_PATH)/dcc $(DEBUGFLAGS_Linker) $(CC_ARCH_SPEC) -Xdollar-in-ident -ei4177,4301,4550 -ei4177,4550,2273,5387,5388,1546,5849,1824 -ei4111,4171,4188,4191,4513,5457 -Xforce-declarations  $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES)  $(DKM_LONGCALL) $(IDE_DEFINES) $(DEFINES) -o $(OBJ_DIR)/ctdt.o -c $(OBJ_DIR)/ctdt.c;  $(TOOL_PATH)/dld -tPPCLP64FV:vxworks7 -X -r5 -r4 -o "$@" $(OBJ_DIR)/ctdt.o @VSIGA64/$(MODE_DIR)/.VSIGA64Object.list $(IDE_LIBRARIES) $(LIBPATH) $(LIBS) $(ADDED_LIBPATH) $(ADDED_LIBS) && if [ "$(EXPAND_DBG)" = "1" ]; then plink "$@";fi && $(if $(_WRS_CONFIG_SECURE_LOADER),signtool  --key=$(_WRS_CONFIG_SECURE_LOADER_PRIVATE_SIGNING_KEY_FILE) --cert=$(_WRS_CONFIG_SECURE_LOADER_PUBLIC_SIGNING_CERT_FILE) --type=ELF $@,true) && true;cp "$@" d:/tftpboot/.

else
VSIGA64/$(MODE_DIR)/VSIGA64.out : VSIGA64/$(MODE_DIR)/VSIGA64.out_jobs

endif
VSIGA64/$(MODE_DIR)/VSIGA64_compile_file : $(FILE) ;

_clean :: VSIGA64/$(MODE_DIR)/VSIGA64_clean

VSIGA64/$(MODE_DIR)/VSIGA64_clean : 
	$(TRACE_FLAG)if [ -d "VSIGA64" ]; then cd "VSIGA64"; rm -rf $(MODE_DIR); fi


# VSIGA64_partialImage
ifeq ($(DEBUG_MODE),1)
VSIGA64_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_C-Compiler = -g -Xdebug-dwarf3
VSIGA64_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_C++-Compiler = -g -Xdebug-dwarf3
VSIGA64_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Linker = -g -Xdebug-dwarf3
VSIGA64_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Partial-Image-Linker = 
VSIGA64_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Librarian = 
VSIGA64_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Assembler = -g -Xdebug-dwarf3
else
VSIGA64_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_C-Compiler = -XO -Xsize-opt
VSIGA64_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_C++-Compiler = -XO -Xsize-opt
VSIGA64_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Linker = -XO -Xsize-opt
VSIGA64_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Partial-Image-Linker = 
VSIGA64_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Librarian = 
VSIGA64_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Assembler = -XO -Xsize-opt
endif
VSIGA64_partialImage/$(MODE_DIR)/% : IDE_INCLUDES = -I$(VSB_DIR)/share/h -I$(VSB_DIR)/krnl/h/system -I$(VSB_DIR)/krnl/h/public -I$(PRJ_ROOT_DIR)/../../MSC/MSIGA 
VSIGA64_partialImage/$(MODE_DIR)/% : IDE_LIBRARIES = 
VSIGA64_partialImage/$(MODE_DIR)/% : IDE_DEFINES = -DCPU=_VX_$(CPU) -D_NO_SQLITE_ -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -D_WRS_VX_SMP -D_WRS_CONFIG_SMP -D_VSB_CONFIG_FILE=\"$(VSB_DIR)/h/config/vsbConfig.h\" -D__VXWORKS__ 
VSIGA64_partialImage/$(MODE_DIR)/% : PROJECT_TYPE = DKM
VSIGA64_partialImage/$(MODE_DIR)/% : DEFINES = 
VSIGA64_partialImage/$(MODE_DIR)/% : EXPAND_DBG = 0
VSIGA64_partialImage/$(MODE_DIR)/% : APICHECK_OPTIONS = -warning
VSIGA64_partialImage/$(MODE_DIR)/% : VX_CPU_FAMILY = ppc
VSIGA64_partialImage/$(MODE_DIR)/% : CPU = PPCE6500
VSIGA64_partialImage/$(MODE_DIR)/% : TOOL_FAMILY = diab
VSIGA64_partialImage/$(MODE_DIR)/% : TOOL_VERSION = diab_5_9_6_1
VSIGA64_partialImage/$(MODE_DIR)/% : _CC_VERSION = diab_5_9_6_5
VSIGA64_partialImage/$(MODE_DIR)/% : TOOL = diab
VSIGA64_partialImage/$(MODE_DIR)/% : TOOL_PATH = $(WIND_HOME)/compilers/diab-5.9.6.5/$(WIND_VX7_DIAB_HOST_TYPE)/bin
VSIGA64_partialImage/$(MODE_DIR)/% : CC_ARCH_SPEC =  -tPPCLP64FV:vxworks7 -Xkeywords=0x0 -D_WRS_HARDWARE_FP -ffixed-r13 -I$(WIND_BASE)/pkgs/os/arch/ppc/kernel/base/h/arch/ppc/private/globRegs.h -Xcode-model-medium
VSIGA64_partialImage/$(MODE_DIR)/% : VSB_DIR = $(PRJ_ROOT_DIR)/../VSourceBuild64
VSIGA64_partialImage/$(MODE_DIR)/% : VSB_CONFIG_FILE = $(VSB_DIR)/h/config/vsbConfig.h
VSIGA64_partialImage/$(MODE_DIR)/% : LIBPATH = 
VSIGA64_partialImage/$(MODE_DIR)/% : LIBS = 
VSIGA64_partialImage/$(MODE_DIR)/% : DKM_LONGCALL = -Xcode-absolute-far
VSIGA64_partialImage/$(MODE_DIR)/% : BDGEN_VSB_INCLUDE = $(VSB_DIR)/h/config/auto.conf
VSIGA64_partialImage/$(MODE_DIR)/% : APICHECK_CMD = apicheck.sh -r "$(VSB_DIR)/krnl/apicheck/forbidden_api.lst" -n "nmppc" -u -s "$<" "$@" $(APICHECK_OPTIONS)
VSIGA64_partialImage/$(MODE_DIR)/% : APICHECK = 0
VSIGA64_partialImage/$(MODE_DIR)/% : OBJ_DIR := VSIGA64_partialImage/$(MODE_DIR)

VSIGA64_partialImage/$(MODE_DIR)/Objects/VSIGA64/cmain.o : D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/files/cmain.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)/dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -Xclib-optim-off -Xansi -Xlocal-data-area-static-only  -W:c++:.CPP  -ei4177,4301,4550 -ei4177,4550,2273,5387,5388,1546,5849,1824 -ei4111,4171,4188,4191,4513,5457 -Xforce-declarations   -Xmake-dependency=0xd $(DKM_LONGCALL) -ei4007,4169,4010,4870 $(IDE_DEFINES) $(DEFINES) $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -o "$@" -c "$<" && if [ "$(APICHECK)" = "1" ]; then $(APICHECK_CMD);fi


VSIGA64_partialImage/$(MODE_DIR)/Objects/VSIGA64/dkm.o : $(PRJ_ROOT_DIR)/dkm.c $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)/dcc $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -Xclib-optim-off -Xansi -Xlocal-data-area-static-only  -W:c++:.CPP  -Xc-new -Xdialect-c89  -ei4177,4301,4550 -ei4177,4550,2273,5387,5388,1546,5849,1824 -ei4111,4171,4188,4191,4513,5457 -Xforce-declarations   -Xmake-dependency=0xd $(DKM_LONGCALL) $(IDE_DEFINES) $(DEFINES) $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -o "$@" -c "$<" && if [ "$(APICHECK)" = "1" ]; then $(APICHECK_CMD);fi


OBJECTS_VSIGA64_partialImage = VSIGA64_partialImage/$(MODE_DIR)/Objects/VSIGA64/cmain.o \
	 VSIGA64_partialImage/$(MODE_DIR)/Objects/VSIGA64/dkm.o

checkDirVSIGA64_partialImage : 
	mkdir -p VSIGA64_partialImage/$(MODE_DIR)/
VSIGA64_partialImage/$(MODE_DIR)/.VSIGA64_partialImageObject.list: $(OBJECTS_VSIGA64_partialImage) | checkDirVSIGA64_partialImage
	$(file >$@,$^)
ifeq ($(TARGET_JOBS),1)
VSIGA64_partialImage/$(MODE_DIR)/VSIGA64_partialImage.o : VSIGA64_partialImage/$(MODE_DIR)/.VSIGA64_partialImageObject.list | check_objdirs
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@";  $(TOOL_PATH)/dld -tPPCLP64FV:vxworks7 -X -r5  -o "$@" @VSIGA64_partialImage/$(MODE_DIR)/.VSIGA64_partialImageObject.list $(ADDED_OBJECTS) $(IDE_LIBRARIES) $(LIBPATH) $(LIBS) $(ADDED_LIBPATH) $(ADDED_LIBS) && if [ "$(EXPAND_DBG)" = "1" ]; then plink "$@";fi

else
VSIGA64_partialImage/$(MODE_DIR)/VSIGA64_partialImage.o : VSIGA64_partialImage/$(MODE_DIR)/VSIGA64_partialImage.o_jobs

endif
VSIGA64_partialImage/$(MODE_DIR)/VSIGA64_partialImage_compile_file : $(FILE) ;

_clean :: VSIGA64_partialImage/$(MODE_DIR)/VSIGA64_partialImage_clean

VSIGA64_partialImage/$(MODE_DIR)/VSIGA64_partialImage_clean : 
	$(TRACE_FLAG)if [ -d "VSIGA64_partialImage" ]; then cd "VSIGA64_partialImage"; rm -rf $(MODE_DIR); fi

force : 

TARGET_JOBS_RULE?=echo "Update the makefile template via File > Import > Build Settings : Update makefile template";exit 1
%_jobs : 
	$(TRACE_FLAG)$(TARGET_JOBS_RULE)

DEP_FILES := VSIGA64_partialImage/$(MODE_DIR)/Objects/VSIGA64/cmain.d VSIGA64_partialImage/$(MODE_DIR)/Objects/VSIGA64/dkm.d
-include $(DEP_FILES)

OBJ_DIRS := VSIGA64_partialImage/$(MODE_DIR)/Objects/VSIGA64
check_objdirs : 
	$(TRACE_FLAG)echo "Creating object dirs";\
	for dir in $(OBJ_DIRS); do\
		if [ ! -d "$$dir" ]; then mkdir -p "$$dir"; fi;\
	done


ifdef BDGEN_VSB_INCLUDE
include $(BDGEN_VSB_INCLUDE)
endif

-include $(PRJ_ROOT_DIR)/*.makefile

-include *.makefile

TARGET_JOBS_RULE=$(MAKE) -f $(MAKEFILE) --jobs $(TARGET_JOBS) $(MFLAGS) $* TARGET_JOBS=1
ifeq ($(JOBS),1)
main_all : external_build $(PROJECT_TARGETS)
	@echo "make: built targets of `pwd`"
else
main_all : external_build 
	@$(MAKE) -f $(MAKEFILE) --jobs $(JOBS) $(MFLAGS) $(PROJECT_TARGETS) TARGET_JOBS=1 &&\
	echo "make: built targets of `pwd`"
endif 

check_vsb :
	@if [ "$(SKIP_VSB_CHECK)" = "" ]; then\
		if [ -f $(WIND_BASE)/build/mk/scripts/check_vsb.sh ]; then\
			jobsoption="";\
			if [ "$(JOBS)" != "" ]; then\
				jobsoption="-j $(JOBS)";\
			fi;\
			sh $(WIND_BASE)/build/mk/scripts/check_vsb.sh $$jobsoption $(VSB_DIR);\
		fi;\
	fi

# entry point for extending the build
external_build ::
	@echo ""

# main entry point for pre processing prior to the build
pre_build :: check_objdirs $(PRE_BUILD_STEP) generate_sources
	@echo ""

# entry point for generating sources prior to the build
generate_sources ::
	@echo ""

# main entry point for post processing after the build
post_build :: $(POST_BUILD_STEP) deploy_output
	@echo ""

# entry point for deploying output after the build
deploy_output ::
	@echo ""

clean :: external_clean $(CLEAN_STEP) _clean

# entry point for extending the build clean
external_clean ::
	@echo ""
