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

BUILD_SPEC = VSourceBuild_PPCE6500diab_SMP
DEBUG_MODE = 1
ifeq ($(DEBUG_MODE),1)
MODE_DIR := Debug
else
MODE_DIR := NonDebug
endif
OBJ_DIR := .
WS_ROOT_DIR := D:/VirtualBoxVMs/Git
PRJ_ROOT_DIR := $(WS_ROOT_DIR)/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSIGA



#Global Build Macros
PROJECT_TYPE = DKM
DEFINES = 
EXPAND_DBG = 0
APICHECK_OPTIONS = -warning
POST_BUILD_RULE = dir


#BuildSpec specific Build Macros
VX_CPU_FAMILY = ppc
CPU = PPCE6500
TOOL_FAMILY = diab
TOOL_VERSION = diab_5_9_6_1
_CC_VERSION = diab_5_9_6_5
TOOL = diab
TOOL_PATH = $(WIND_HOME)/compilers/diab-5.9.6.5/$(WIND_VX7_DIAB_HOST_TYPE)/bin
CC_ARCH_SPEC =  -tPPCE6500FV:vxworks7 -Xkeywords=0x0 -D_WRS_HARDWARE_FP
VSB_DIR = $(PRJ_ROOT_DIR)/../VSourceBuild
VSB_CONFIG_FILE = $(VSB_DIR)/h/config/vsbConfig.h
LIBPATH = 
LIBS = 
DKM_LONGCALL = -Xcode-absolute-far
BDGEN_VSB_INCLUDE = $(VSB_DIR)/h/config/auto.conf
APICHECK_CMD = apicheck.sh -r "$(VSB_DIR)/krnl/apicheck/forbidden_api.lst" -n "nmppc" -u -s "$<" "$@" $(APICHECK_OPTIONS)
APICHECK = 0

IDE_INCLUDES = -I$(VSB_DIR)/share/h -I$(VSB_DIR)/krnl/h/system -I$(VSB_DIR)/krnl/h/public -I$(PRJ_ROOT_DIR)/../../MSC/MSIGA 

IDE_LIBRARIES = 

IDE_DEFINES = -DCPU=_VX_$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -D_WRS_VX_SMP -D_WRS_CONFIG_SMP -D_VSB_CONFIG_FILE=\"$(VSB_DIR)/h/config/vsbConfig.h\"   



#BuildTool flags
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C-Compiler = -g -Xdebug-dwarf3
DEBUGFLAGS_C++-Compiler = -g -Xdebug-dwarf3
DEBUGFLAGS_Linker = -g -Xdebug-dwarf3
DEBUGFLAGS_Partial-Image-Linker = 
DEBUGFLAGS_Librarian = 
DEBUGFLAGS_Assembler = -g -Xdebug-dwarf3
DEBUGFLAGS_POST = 
else
DEBUGFLAGS_C-Compiler = -XO -Xsize-opt
DEBUGFLAGS_C++-Compiler = -XO -Xsize-opt
DEBUGFLAGS_Linker = -XO -Xsize-opt
DEBUGFLAGS_Partial-Image-Linker = 
DEBUGFLAGS_Librarian = 
DEBUGFLAGS_Assembler = -XO -Xsize-opt
DEBUGFLAGS_POST = 
endif


#Project Targets
PROJECT_TARGETS = VSIGA/$(MODE_DIR)/VSIGA.out \
	 VSIGA_partialImage/$(MODE_DIR)/VSIGA_partialImage.o


#Rules

# VSIGA
ifeq ($(DEBUG_MODE),1)
VSIGA/$(MODE_DIR)/% : DEBUGFLAGS_C-Compiler = -g -Xdebug-dwarf3
VSIGA/$(MODE_DIR)/% : DEBUGFLAGS_C++-Compiler = -g -Xdebug-dwarf3
VSIGA/$(MODE_DIR)/% : DEBUGFLAGS_Linker = -g -Xdebug-dwarf3
VSIGA/$(MODE_DIR)/% : DEBUGFLAGS_Partial-Image-Linker = 
VSIGA/$(MODE_DIR)/% : DEBUGFLAGS_Librarian = 
VSIGA/$(MODE_DIR)/% : DEBUGFLAGS_Assembler = -g -Xdebug-dwarf3
VSIGA/$(MODE_DIR)/% : DEBUGFLAGS_POST = 
else
VSIGA/$(MODE_DIR)/% : DEBUGFLAGS_C-Compiler = -XO -Xsize-opt
VSIGA/$(MODE_DIR)/% : DEBUGFLAGS_C++-Compiler = -XO -Xsize-opt
VSIGA/$(MODE_DIR)/% : DEBUGFLAGS_Linker = -XO -Xsize-opt
VSIGA/$(MODE_DIR)/% : DEBUGFLAGS_Partial-Image-Linker = 
VSIGA/$(MODE_DIR)/% : DEBUGFLAGS_Librarian = 
VSIGA/$(MODE_DIR)/% : DEBUGFLAGS_Assembler = -XO -Xsize-opt
VSIGA/$(MODE_DIR)/% : DEBUGFLAGS_POST = 
endif
VSIGA/$(MODE_DIR)/% : IDE_INCLUDES = -I$(VSB_DIR)/share/h -I$(VSB_DIR)/krnl/h/system -I$(VSB_DIR)/krnl/h/public -I$(PRJ_ROOT_DIR)/../../MSC/MSIGA 
VSIGA/$(MODE_DIR)/% : IDE_LIBRARIES = 
VSIGA/$(MODE_DIR)/% : IDE_DEFINES = -DCPU=_VX_$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -D_WRS_VX_SMP -D_WRS_CONFIG_SMP -D_VSB_CONFIG_FILE=\"$(VSB_DIR)/h/config/vsbConfig.h\"   
VSIGA/$(MODE_DIR)/% : PROJECT_TYPE = DKM
VSIGA/$(MODE_DIR)/% : DEFINES = 
VSIGA/$(MODE_DIR)/% : EXPAND_DBG = 0
VSIGA/$(MODE_DIR)/% : APICHECK_OPTIONS = -warning
VSIGA/$(MODE_DIR)/% : POST_BUILD_RULE = dir
VSIGA/$(MODE_DIR)/% : VX_CPU_FAMILY = ppc
VSIGA/$(MODE_DIR)/% : CPU = PPCE6500
VSIGA/$(MODE_DIR)/% : TOOL_FAMILY = diab
VSIGA/$(MODE_DIR)/% : TOOL_VERSION = diab_5_9_6_1
VSIGA/$(MODE_DIR)/% : _CC_VERSION = diab_5_9_6_5
VSIGA/$(MODE_DIR)/% : TOOL = diab
VSIGA/$(MODE_DIR)/% : TOOL_PATH = $(WIND_HOME)/compilers/diab-5.9.6.5/$(WIND_VX7_DIAB_HOST_TYPE)/bin
VSIGA/$(MODE_DIR)/% : CC_ARCH_SPEC =  -tPPCE6500FV:vxworks7 -Xkeywords=0x0 -D_WRS_HARDWARE_FP
VSIGA/$(MODE_DIR)/% : VSB_DIR = $(PRJ_ROOT_DIR)/../VSourceBuild
VSIGA/$(MODE_DIR)/% : VSB_CONFIG_FILE = $(VSB_DIR)/h/config/vsbConfig.h
VSIGA/$(MODE_DIR)/% : LIBPATH = 
VSIGA/$(MODE_DIR)/% : LIBS = 
VSIGA/$(MODE_DIR)/% : DKM_LONGCALL = -Xcode-absolute-far
VSIGA/$(MODE_DIR)/% : BDGEN_VSB_INCLUDE = $(VSB_DIR)/h/config/auto.conf
VSIGA/$(MODE_DIR)/% : APICHECK_CMD = apicheck.sh -r "$(VSB_DIR)/krnl/apicheck/forbidden_api.lst" -n "nmppc" -u -s "$<" "$@" $(APICHECK_OPTIONS)
VSIGA/$(MODE_DIR)/% : APICHECK = 0
VSIGA/$(MODE_DIR)/% : OBJ_DIR := VSIGA/$(MODE_DIR)

OBJECTS_VSIGA = VSIGA_partialImage/$(MODE_DIR)/VSIGA_partialImage.o

checkDirVSIGA : 
	mkdir -p VSIGA/$(MODE_DIR)/
VSIGA/$(MODE_DIR)/.VSIGAObject.list: $(OBJECTS_VSIGA) | checkDirVSIGA
	$(file >$@,$^)
ifeq ($(TARGET_JOBS),1)
VSIGA/$(MODE_DIR)/VSIGA.out : VSIGA/$(MODE_DIR)/.VSIGAObject.list | check_objdirs
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@";rm -f "$@";$(TOOL_PATH)/ddump -Ng @VSIGA/$(MODE_DIR)/.VSIGAObject.list | tclsh $(WIND_BASE)/build/mk/tcl/munch.tcl -c ppc -tags $(VSB_DIR)/krnl/tags/dkm.tags > $(OBJ_DIR)/ctdt.c; $(TOOL_PATH)/dcc $(DEBUGFLAGS_Linker) $(CC_ARCH_SPEC) -Xdollar-in-ident -ei4177,4301,4550 -ei4177,4550,2273,5387,5388,1546,5849,1824 -ei4111,4171,4188,4191,4513,5457 -Xforce-declarations  $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES)  $(DKM_LONGCALL) $(IDE_DEFINES) $(DEFINES) -o $(OBJ_DIR)/ctdt.o -c $(OBJ_DIR)/ctdt.c;  $(TOOL_PATH)/dld -tPPCE6500FV:vxworks7 -X -r5 -r4 -o "$@" $(OBJ_DIR)/ctdt.o @VSIGA/$(MODE_DIR)/.VSIGAObject.list $(IDE_LIBRARIES) $(LIBPATH) $(LIBS) $(ADDED_LIBPATH) $(ADDED_LIBS) && if [ "$(EXPAND_DBG)" = "1" ]; then plink "$@";fi && $(if $(_WRS_CONFIG_SECURE_LOADER),signtool  --key=$(_WRS_CONFIG_SECURE_LOADER_PRIVATE_SIGNING_KEY_FILE) --cert=$(_WRS_CONFIG_SECURE_LOADER_PUBLIC_SIGNING_CERT_FILE) --type=ELF $@,true) && true

else
VSIGA/$(MODE_DIR)/VSIGA.out : VSIGA/$(MODE_DIR)/VSIGA.out_jobs

endif
VSIGA/$(MODE_DIR)/VSIGA_compile_file : $(FILE) ;

_clean :: VSIGA/$(MODE_DIR)/VSIGA_clean

VSIGA/$(MODE_DIR)/VSIGA_clean : 
	$(TRACE_FLAG)if [ -d "VSIGA" ]; then cd "VSIGA"; rm -rf $(MODE_DIR); fi


# VSIGA_partialImage
ifeq ($(DEBUG_MODE),1)
VSIGA_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_C-Compiler = -g -Xdebug-dwarf3
VSIGA_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_C++-Compiler = -g -Xdebug-dwarf3
VSIGA_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Linker = -g -Xdebug-dwarf3
VSIGA_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Partial-Image-Linker = 
VSIGA_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Librarian = 
VSIGA_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Assembler = -g -Xdebug-dwarf3
VSIGA_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_POST = 
else
VSIGA_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_C-Compiler = -XO -Xsize-opt
VSIGA_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_C++-Compiler = -XO -Xsize-opt
VSIGA_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Linker = -XO -Xsize-opt
VSIGA_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Partial-Image-Linker = 
VSIGA_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Librarian = 
VSIGA_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Assembler = -XO -Xsize-opt
VSIGA_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_POST = 
endif
VSIGA_partialImage/$(MODE_DIR)/% : IDE_INCLUDES = -I$(VSB_DIR)/share/h -I$(VSB_DIR)/krnl/h/system -I$(VSB_DIR)/krnl/h/public -I$(PRJ_ROOT_DIR)/../../MSC/MSIGA 
VSIGA_partialImage/$(MODE_DIR)/% : IDE_LIBRARIES = 
VSIGA_partialImage/$(MODE_DIR)/% : IDE_DEFINES = -DCPU=_VX_$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -D_WRS_VX_SMP -D_WRS_CONFIG_SMP -D_VSB_CONFIG_FILE=\"$(VSB_DIR)/h/config/vsbConfig.h\"   
VSIGA_partialImage/$(MODE_DIR)/% : PROJECT_TYPE = DKM
VSIGA_partialImage/$(MODE_DIR)/% : DEFINES = 
VSIGA_partialImage/$(MODE_DIR)/% : EXPAND_DBG = 0
VSIGA_partialImage/$(MODE_DIR)/% : APICHECK_OPTIONS = -warning
VSIGA_partialImage/$(MODE_DIR)/% : POST_BUILD_RULE = dir
VSIGA_partialImage/$(MODE_DIR)/% : VX_CPU_FAMILY = ppc
VSIGA_partialImage/$(MODE_DIR)/% : CPU = PPCE6500
VSIGA_partialImage/$(MODE_DIR)/% : TOOL_FAMILY = diab
VSIGA_partialImage/$(MODE_DIR)/% : TOOL_VERSION = diab_5_9_6_1
VSIGA_partialImage/$(MODE_DIR)/% : _CC_VERSION = diab_5_9_6_5
VSIGA_partialImage/$(MODE_DIR)/% : TOOL = diab
VSIGA_partialImage/$(MODE_DIR)/% : TOOL_PATH = $(WIND_HOME)/compilers/diab-5.9.6.5/$(WIND_VX7_DIAB_HOST_TYPE)/bin
VSIGA_partialImage/$(MODE_DIR)/% : CC_ARCH_SPEC =  -tPPCE6500FV:vxworks7 -Xkeywords=0x0 -D_WRS_HARDWARE_FP
VSIGA_partialImage/$(MODE_DIR)/% : VSB_DIR = $(PRJ_ROOT_DIR)/../VSourceBuild
VSIGA_partialImage/$(MODE_DIR)/% : VSB_CONFIG_FILE = $(VSB_DIR)/h/config/vsbConfig.h
VSIGA_partialImage/$(MODE_DIR)/% : LIBPATH = 
VSIGA_partialImage/$(MODE_DIR)/% : LIBS = 
VSIGA_partialImage/$(MODE_DIR)/% : DKM_LONGCALL = -Xcode-absolute-far
VSIGA_partialImage/$(MODE_DIR)/% : BDGEN_VSB_INCLUDE = $(VSB_DIR)/h/config/auto.conf
VSIGA_partialImage/$(MODE_DIR)/% : APICHECK_CMD = apicheck.sh -r "$(VSB_DIR)/krnl/apicheck/forbidden_api.lst" -n "nmppc" -u -s "$<" "$@" $(APICHECK_OPTIONS)
VSIGA_partialImage/$(MODE_DIR)/% : APICHECK = 0
VSIGA_partialImage/$(MODE_DIR)/% : OBJ_DIR := VSIGA_partialImage/$(MODE_DIR)

VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/Anal/Collect/DataFile/DataFile.o : $(WS_ROOT_DIR)/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/files/Anal/Collect/DataFile/DataFile.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)/dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -Xclib-optim-off -Xansi -Xlocal-data-area-static-only  -W:c++:.CPP  -ei4177,4301,4550 -ei4177,4550,2273,5387,5388,1546,5849,1824 -ei4111,4171,4188,4191,4513,5457 -Xforce-declarations   -Xmake-dependency=0xd $(DKM_LONGCALL) $(IDE_DEFINES) $(DEFINES) $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -o "$@" -c "$<" && if [ "$(APICHECK)" = "1" ]; then $(APICHECK_CMD);fi


VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/Anal/Collect/ccollectbank/ccollectbank.o : $(WS_ROOT_DIR)/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/files/Anal/Collect/ccollectbank/ccollectbank.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)/dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -Xclib-optim-off -Xansi -Xlocal-data-area-static-only  -W:c++:.CPP  -ei4177,4301,4550 -ei4177,4550,2273,5387,5388,1546,5849,1824 -ei4111,4171,4188,4191,4513,5457 -Xforce-declarations   -Xmake-dependency=0xd $(DKM_LONGCALL) $(IDE_DEFINES) $(DEFINES) $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -o "$@" -c "$<" && if [ "$(APICHECK)" = "1" ]; then $(APICHECK_CMD);fi


VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/Anal/EmitterMerge/CEP/AnalyticCEP.o : $(WS_ROOT_DIR)/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/files/Anal/EmitterMerge/CEP/AnalyticCEP.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)/dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -Xclib-optim-off -Xansi -Xlocal-data-area-static-only  -W:c++:.CPP  -ei4177,4301,4550 -ei4177,4550,2273,5387,5388,1546,5849,1824 -ei4111,4171,4188,4191,4513,5457 -Xforce-declarations   -Xmake-dependency=0xd $(DKM_LONGCALL) $(IDE_DEFINES) $(DEFINES) $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -o "$@" -c "$<" && if [ "$(APICHECK)" = "1" ]; then $(APICHECK_CMD);fi


VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/Anal/EmitterMerge/Coordinate/Coordinate.o : $(WS_ROOT_DIR)/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/files/Anal/EmitterMerge/Coordinate/Coordinate.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)/dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -Xclib-optim-off -Xansi -Xlocal-data-area-static-only  -W:c++:.CPP  -ei4177,4301,4550 -ei4177,4550,2273,5387,5388,1546,5849,1824 -ei4111,4171,4188,4191,4513,5457 -Xforce-declarations   -Xmake-dependency=0xd $(DKM_LONGCALL) $(IDE_DEFINES) $(DEFINES) $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -o "$@" -c "$<" && if [ "$(APICHECK)" = "1" ]; then $(APICHECK_CMD);fi


VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/Anal/EmitterMerge/DistanceLeastSquare/DistanceLeastSquare.o : $(WS_ROOT_DIR)/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/files/Anal/EmitterMerge/DistanceLeastSquare/DistanceLeastSquare.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)/dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -Xclib-optim-off -Xansi -Xlocal-data-area-static-only  -W:c++:.CPP  -ei4177,4301,4550 -ei4177,4550,2273,5387,5388,1546,5849,1824 -ei4111,4171,4188,4191,4513,5457 -Xforce-declarations   -Xmake-dependency=0xd $(DKM_LONGCALL) $(IDE_DEFINES) $(DEFINES) $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -o "$@" -c "$<" && if [ "$(APICHECK)" = "1" ]; then $(APICHECK_CMD);fi


VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/Anal/EmitterMerge/GeoCoordConv/GeoCoordConv.o : $(WS_ROOT_DIR)/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/files/Anal/EmitterMerge/GeoCoordConv/GeoCoordConv.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)/dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -Xclib-optim-off -Xansi -Xlocal-data-area-static-only  -W:c++:.CPP  -ei4177,4301,4550 -ei4177,4550,2273,5387,5388,1546,5849,1824 -ei4111,4171,4188,4191,4513,5457 -Xforce-declarations   -Xmake-dependency=0xd $(DKM_LONGCALL) $(IDE_DEFINES) $(DEFINES) $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -o "$@" -c "$<" && if [ "$(APICHECK)" = "1" ]; then $(APICHECK_CMD);fi


VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/Anal/EmitterMerge/InverseMethod/CInverseMethod.o : $(WS_ROOT_DIR)/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/files/Anal/EmitterMerge/InverseMethod/CInverseMethod.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)/dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -Xclib-optim-off -Xansi -Xlocal-data-area-static-only  -W:c++:.CPP  -ei4177,4301,4550 -ei4177,4550,2273,5387,5388,1546,5849,1824 -ei4111,4171,4188,4191,4513,5457 -Xforce-declarations   -Xmake-dependency=0xd $(DKM_LONGCALL) $(IDE_DEFINES) $(DEFINES) $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -o "$@" -c "$<" && if [ "$(APICHECK)" = "1" ]; then $(APICHECK_CMD);fi


VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/Anal/EmitterMerge/Matrix/Matrix.o : $(WS_ROOT_DIR)/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/files/Anal/EmitterMerge/Matrix/Matrix.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)/dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -Xclib-optim-off -Xansi -Xlocal-data-area-static-only  -W:c++:.CPP  -ei4177,4301,4550 -ei4177,4550,2273,5387,5388,1546,5849,1824 -ei4111,4171,4188,4191,4513,5457 -Xforce-declarations   -Xmake-dependency=0xd $(DKM_LONGCALL) $(IDE_DEFINES) $(DEFINES) $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -o "$@" -c "$<" && if [ "$(APICHECK)" = "1" ]; then $(APICHECK_CMD);fi


VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/Anal/EmitterMerge/Quadratic/Quadratic.o : $(WS_ROOT_DIR)/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/files/Anal/EmitterMerge/Quadratic/Quadratic.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)/dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -Xclib-optim-off -Xansi -Xlocal-data-area-static-only  -W:c++:.CPP  -ei4177,4301,4550 -ei4177,4550,2273,5387,5388,1546,5849,1824 -ei4111,4171,4188,4191,4513,5457 -Xforce-declarations   -Xmake-dependency=0xd $(DKM_LONGCALL) $(IDE_DEFINES) $(DEFINES) $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -o "$@" -c "$<" && if [ "$(APICHECK)" = "1" ]; then $(APICHECK_CMD);fi


VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/Anal/EmitterMerge/UTM/UTM.o : $(WS_ROOT_DIR)/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/files/Anal/EmitterMerge/UTM/UTM.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)/dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -Xclib-optim-off -Xansi -Xlocal-data-area-static-only  -W:c++:.CPP  -ei4177,4301,4550 -ei4177,4550,2273,5387,5388,1546,5849,1824 -ei4111,4171,4188,4191,4513,5457 -Xforce-declarations   -Xmake-dependency=0xd $(DKM_LONGCALL) $(IDE_DEFINES) $(DEFINES) $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -o "$@" -c "$<" && if [ "$(APICHECK)" = "1" ]; then $(APICHECK_CMD);fi


VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/Anal/Identify/ELUtil.o : $(WS_ROOT_DIR)/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/files/Anal/Identify/ELUtil.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)/dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -Xclib-optim-off -Xansi -Xlocal-data-area-static-only  -W:c++:.CPP  -ei4177,4301,4550 -ei4177,4550,2273,5387,5388,1546,5849,1824 -ei4111,4171,4188,4191,4513,5457 -Xforce-declarations   -Xmake-dependency=0xd $(DKM_LONGCALL) $(IDE_DEFINES) $(DEFINES) $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -o "$@" -c "$<" && if [ "$(APICHECK)" = "1" ]; then $(APICHECK_CMD);fi


VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/Anal/Identify/Identify.o : $(WS_ROOT_DIR)/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/files/Anal/Identify/Identify.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)/dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -Xclib-optim-off -Xansi -Xlocal-data-area-static-only  -W:c++:.CPP  -ei4177,4301,4550 -ei4177,4550,2273,5387,5388,1546,5849,1824 -ei4111,4171,4188,4191,4513,5457 -Xforce-declarations   -Xmake-dependency=0xd $(DKM_LONGCALL) $(IDE_DEFINES) $(DEFINES) $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -o "$@" -c "$<" && if [ "$(APICHECK)" = "1" ]; then $(APICHECK_CMD);fi


VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/Anal/Identify/cipl.o : $(WS_ROOT_DIR)/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/files/Anal/Identify/cipl.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)/dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -Xclib-optim-off -Xansi -Xlocal-data-area-static-only  -W:c++:.CPP  -ei4177,4301,4550 -ei4177,4550,2273,5387,5388,1546,5849,1824 -ei4111,4171,4188,4191,4513,5457 -Xforce-declarations   -Xmake-dependency=0xd $(DKM_LONGCALL) $(IDE_DEFINES) $(DEFINES) $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -o "$@" -c "$<" && if [ "$(APICHECK)" = "1" ]; then $(APICHECK_CMD);fi


VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/Anal/MIDAS/ELDecoder.o : $(WS_ROOT_DIR)/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/files/Anal/MIDAS/ELDecoder.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)/dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -Xclib-optim-off -Xansi -Xlocal-data-area-static-only  -W:c++:.CPP  -ei4177,4301,4550 -ei4177,4550,2273,5387,5388,1546,5849,1824 -ei4111,4171,4188,4191,4513,5457 -Xforce-declarations   -Xmake-dependency=0xd $(DKM_LONGCALL) $(IDE_DEFINES) $(DEFINES) $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -o "$@" -c "$<" && if [ "$(APICHECK)" = "1" ]; then $(APICHECK_CMD);fi


VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/Anal/MIDAS/Midas.o : $(WS_ROOT_DIR)/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/files/Anal/MIDAS/Midas.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)/dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -Xclib-optim-off -Xansi -Xlocal-data-area-static-only  -W:c++:.CPP  -ei4177,4301,4550 -ei4177,4550,2273,5387,5388,1546,5849,1824 -ei4111,4171,4188,4191,4513,5457 -Xforce-declarations   -Xmake-dependency=0xd $(DKM_LONGCALL) $(IDE_DEFINES) $(DEFINES) $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -o "$@" -c "$<" && if [ "$(APICHECK)" = "1" ]; then $(APICHECK_CMD);fi


VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/Anal/MIDAS/PDW2SP370.o : $(WS_ROOT_DIR)/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/files/Anal/MIDAS/PDW2SP370.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)/dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -Xclib-optim-off -Xansi -Xlocal-data-area-static-only  -W:c++:.CPP  -ei4177,4301,4550 -ei4177,4550,2273,5387,5388,1546,5849,1824 -ei4111,4171,4188,4191,4513,5457 -Xforce-declarations   -Xmake-dependency=0xd $(DKM_LONGCALL) $(IDE_DEFINES) $(DEFINES) $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -o "$@" -c "$<" && if [ "$(APICHECK)" = "1" ]; then $(APICHECK_CMD);fi


VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/Anal/MIDAS/RawFile.o : $(WS_ROOT_DIR)/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/files/Anal/MIDAS/RawFile.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)/dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -Xclib-optim-off -Xansi -Xlocal-data-area-static-only  -W:c++:.CPP  -ei4177,4301,4550 -ei4177,4550,2273,5387,5388,1546,5849,1824 -ei4111,4171,4188,4191,4513,5457 -Xforce-declarations   -Xmake-dependency=0xd $(DKM_LONGCALL) $(IDE_DEFINES) $(DEFINES) $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -o "$@" -c "$<" && if [ "$(APICHECK)" = "1" ]; then $(APICHECK_CMD);fi


VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/System/csharedmemory.o : $(WS_ROOT_DIR)/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/files/System/csharedmemory.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)/dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -Xclib-optim-off -Xansi -Xlocal-data-area-static-only  -W:c++:.CPP  -ei4177,4301,4550 -ei4177,4550,2273,5387,5388,1546,5849,1824 -ei4111,4171,4188,4191,4513,5457 -Xforce-declarations   -Xmake-dependency=0xd $(DKM_LONGCALL) $(IDE_DEFINES) $(DEFINES) $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -o "$@" -c "$<" && if [ "$(APICHECK)" = "1" ]; then $(APICHECK_CMD);fi


VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/System/csysconfig.o : $(WS_ROOT_DIR)/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/files/System/csysconfig.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)/dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -Xclib-optim-off -Xansi -Xlocal-data-area-static-only  -W:c++:.CPP  -ei4177,4301,4550 -ei4177,4550,2273,5387,5388,1546,5849,1824 -ei4111,4171,4188,4191,4513,5457 -Xforce-declarations   -Xmake-dependency=0xd $(DKM_LONGCALL) $(IDE_DEFINES) $(DEFINES) $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -o "$@" -c "$<" && if [ "$(APICHECK)" = "1" ]; then $(APICHECK_CMD);fi


VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/Thread/creclan.o : $(WS_ROOT_DIR)/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/files/Thread/creclan.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)/dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -Xclib-optim-off -Xansi -Xlocal-data-area-static-only  -W:c++:.CPP  -ei4177,4301,4550 -ei4177,4550,2273,5387,5388,1546,5849,1824 -ei4111,4171,4188,4191,4513,5457 -Xforce-declarations   -Xmake-dependency=0xd $(DKM_LONGCALL) $(IDE_DEFINES) $(DEFINES) $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -o "$@" -c "$<" && if [ "$(APICHECK)" = "1" ]; then $(APICHECK_CMD);fi


VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/Thread/csignalcollect.o : $(WS_ROOT_DIR)/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/files/Thread/csignalcollect.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)/dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -Xclib-optim-off -Xansi -Xlocal-data-area-static-only  -W:c++:.CPP  -ei4177,4301,4550 -ei4177,4550,2273,5387,5388,1546,5849,1824 -ei4111,4171,4188,4191,4513,5457 -Xforce-declarations   -Xmake-dependency=0xd $(DKM_LONGCALL) $(IDE_DEFINES) $(DEFINES) $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -o "$@" -c "$<" && if [ "$(APICHECK)" = "1" ]; then $(APICHECK_CMD);fi


VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/Thread/ctaskmngr.o : $(WS_ROOT_DIR)/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/files/Thread/ctaskmngr.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)/dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -Xclib-optim-off -Xansi -Xlocal-data-area-static-only  -W:c++:.CPP  -ei4177,4301,4550 -ei4177,4550,2273,5387,5388,1546,5849,1824 -ei4111,4171,4188,4191,4513,5457 -Xforce-declarations   -Xmake-dependency=0xd $(DKM_LONGCALL) $(IDE_DEFINES) $(DEFINES) $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -o "$@" -c "$<" && if [ "$(APICHECK)" = "1" ]; then $(APICHECK_CMD);fi


VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/Thread/curbit.o : $(WS_ROOT_DIR)/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/files/Thread/curbit.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)/dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -Xclib-optim-off -Xansi -Xlocal-data-area-static-only  -W:c++:.CPP  -ei4177,4301,4550 -ei4177,4550,2273,5387,5388,1546,5849,1824 -ei4111,4171,4188,4191,4513,5457 -Xforce-declarations   -Xmake-dependency=0xd $(DKM_LONGCALL) $(IDE_DEFINES) $(DEFINES) $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -o "$@" -c "$<" && if [ "$(APICHECK)" = "1" ]; then $(APICHECK_CMD);fi


VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/Thread/cusercollect.o : $(WS_ROOT_DIR)/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/files/Thread/cusercollect.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)/dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -Xclib-optim-off -Xansi -Xlocal-data-area-static-only  -W:c++:.CPP  -ei4177,4301,4550 -ei4177,4550,2273,5387,5388,1546,5849,1824 -ei4111,4171,4188,4191,4513,5457 -Xforce-declarations   -Xmake-dependency=0xd $(DKM_LONGCALL) $(IDE_DEFINES) $(DEFINES) $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -o "$@" -c "$<" && if [ "$(APICHECK)" = "1" ]; then $(APICHECK_CMD);fi


VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/Utils/carraymsgdata.o : $(WS_ROOT_DIR)/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/files/Utils/carraymsgdata.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)/dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -Xclib-optim-off -Xansi -Xlocal-data-area-static-only  -W:c++:.CPP  -ei4177,4301,4550 -ei4177,4550,2273,5387,5388,1546,5849,1824 -ei4111,4171,4188,4191,4513,5457 -Xforce-declarations   -Xmake-dependency=0xd $(DKM_LONGCALL) $(IDE_DEFINES) $(DEFINES) $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -o "$@" -c "$<" && if [ "$(APICHECK)" = "1" ]; then $(APICHECK_CMD);fi


VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/Utils/ccommonutils.o : $(WS_ROOT_DIR)/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/files/Utils/ccommonutils.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)/dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -Xclib-optim-off -Xansi -Xlocal-data-area-static-only  -W:c++:.CPP  -ei4177,4301,4550 -ei4177,4550,2273,5387,5388,1546,5849,1824 -ei4111,4171,4188,4191,4513,5457 -Xforce-declarations   -Xmake-dependency=0xd $(DKM_LONGCALL) $(IDE_DEFINES) $(DEFINES) $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -o "$@" -c "$<" && if [ "$(APICHECK)" = "1" ]; then $(APICHECK_CMD);fi


VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/Utils/clog.o : $(WS_ROOT_DIR)/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/files/Utils/clog.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)/dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -Xclib-optim-off -Xansi -Xlocal-data-area-static-only  -W:c++:.CPP  -ei4177,4301,4550 -ei4177,4550,2273,5387,5388,1546,5849,1824 -ei4111,4171,4188,4191,4513,5457 -Xforce-declarations   -Xmake-dependency=0xd $(DKM_LONGCALL) $(IDE_DEFINES) $(DEFINES) $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -o "$@" -c "$<" && if [ "$(APICHECK)" = "1" ]; then $(APICHECK_CMD);fi


VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/Utils/csingleclient.o : $(WS_ROOT_DIR)/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/files/Utils/csingleclient.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)/dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -Xclib-optim-off -Xansi -Xlocal-data-area-static-only  -W:c++:.CPP  -ei4177,4301,4550 -ei4177,4550,2273,5387,5388,1546,5849,1824 -ei4111,4171,4188,4191,4513,5457 -Xforce-declarations   -Xmake-dependency=0xd $(DKM_LONGCALL) $(IDE_DEFINES) $(DEFINES) $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -o "$@" -c "$<" && if [ "$(APICHECK)" = "1" ]; then $(APICHECK_CMD);fi


VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/Utils/csingleserver.o : $(WS_ROOT_DIR)/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/files/Utils/csingleserver.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)/dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -Xclib-optim-off -Xansi -Xlocal-data-area-static-only  -W:c++:.CPP  -ei4177,4301,4550 -ei4177,4550,2273,5387,5388,1546,5849,1824 -ei4111,4171,4188,4191,4513,5457 -Xforce-declarations   -Xmake-dependency=0xd $(DKM_LONGCALL) $(IDE_DEFINES) $(DEFINES) $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -o "$@" -c "$<" && if [ "$(APICHECK)" = "1" ]; then $(APICHECK_CMD);fi


VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/Utils/cthread.o : $(WS_ROOT_DIR)/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/files/Utils/cthread.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)/dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -Xclib-optim-off -Xansi -Xlocal-data-area-static-only  -W:c++:.CPP  -ei4177,4301,4550 -ei4177,4550,2273,5387,5388,1546,5849,1824 -ei4111,4171,4188,4191,4513,5457 -Xforce-declarations   -Xmake-dependency=0xd $(DKM_LONGCALL) $(IDE_DEFINES) $(DEFINES) $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -o "$@" -c "$<" && if [ "$(APICHECK)" = "1" ]; then $(APICHECK_CMD);fi


VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/Utils/programrev.o : $(WS_ROOT_DIR)/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/files/Utils/programrev.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)/dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -Xclib-optim-off -Xansi -Xlocal-data-area-static-only  -W:c++:.CPP  -ei4177,4301,4550 -ei4177,4550,2273,5387,5388,1546,5849,1824 -ei4111,4171,4188,4191,4513,5457 -Xforce-declarations   -Xmake-dependency=0xd $(DKM_LONGCALL) $(IDE_DEFINES) $(DEFINES) $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -o "$@" -c "$<" && if [ "$(APICHECK)" = "1" ]; then $(APICHECK_CMD);fi


VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/cmain.o : $(WS_ROOT_DIR)/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/files/cmain.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)/dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -Xclib-optim-off -Xansi -Xlocal-data-area-static-only  -W:c++:.CPP  -ei4177,4301,4550 -ei4177,4550,2273,5387,5388,1546,5849,1824 -ei4111,4171,4188,4191,4513,5457 -Xforce-declarations   -Xmake-dependency=0xd $(DKM_LONGCALL) $(IDE_DEFINES) $(DEFINES) $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -o "$@" -c "$<" && if [ "$(APICHECK)" = "1" ]; then $(APICHECK_CMD);fi


VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/dkm.o : $(PRJ_ROOT_DIR)/dkm.c $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)/dcc $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -Xclib-optim-off -Xansi -Xlocal-data-area-static-only  -W:c++:.CPP  -Xc-new -Xdialect-c89  -ei4177,4301,4550 -ei4177,4550,2273,5387,5388,1546,5849,1824 -ei4111,4171,4188,4191,4513,5457 -Xforce-declarations   -Xmake-dependency=0xd $(DKM_LONGCALL) $(IDE_DEFINES) $(DEFINES) $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -o "$@" -c "$<" && if [ "$(APICHECK)" = "1" ]; then $(APICHECK_CMD);fi


OBJECTS_VSIGA_partialImage = VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/Anal/Collect/DataFile/DataFile.o \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/Anal/Collect/ccollectbank/ccollectbank.o \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/Anal/EmitterMerge/CEP/AnalyticCEP.o \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/Anal/EmitterMerge/Coordinate/Coordinate.o \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/Anal/EmitterMerge/DistanceLeastSquare/DistanceLeastSquare.o \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/Anal/EmitterMerge/GeoCoordConv/GeoCoordConv.o \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/Anal/EmitterMerge/InverseMethod/CInverseMethod.o \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/Anal/EmitterMerge/Matrix/Matrix.o \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/Anal/EmitterMerge/Quadratic/Quadratic.o \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/Anal/EmitterMerge/UTM/UTM.o \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/Anal/Identify/ELUtil.o \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/Anal/Identify/Identify.o \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/Anal/Identify/cipl.o \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/Anal/MIDAS/ELDecoder.o \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/Anal/MIDAS/Midas.o \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/Anal/MIDAS/PDW2SP370.o \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/Anal/MIDAS/RawFile.o \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/System/csharedmemory.o \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/System/csysconfig.o \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/Thread/creclan.o \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/Thread/csignalcollect.o \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/Thread/ctaskmngr.o \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/Thread/curbit.o \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/Thread/cusercollect.o \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/Utils/carraymsgdata.o \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/Utils/ccommonutils.o \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/Utils/clog.o \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/Utils/csingleclient.o \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/Utils/csingleserver.o \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/Utils/cthread.o \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/Utils/programrev.o \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/cmain.o \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/dkm.o

checkDirVSIGA_partialImage : 
	mkdir -p VSIGA_partialImage/$(MODE_DIR)/
VSIGA_partialImage/$(MODE_DIR)/.VSIGA_partialImageObject.list: $(OBJECTS_VSIGA_partialImage) | checkDirVSIGA_partialImage
	$(file >$@,$^)
ifeq ($(TARGET_JOBS),1)
VSIGA_partialImage/$(MODE_DIR)/VSIGA_partialImage.o : VSIGA_partialImage/$(MODE_DIR)/.VSIGA_partialImageObject.list | check_objdirs
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@";  $(TOOL_PATH)/dld -tPPCE6500FV:vxworks7 -X -r5  -o "$@" @VSIGA_partialImage/$(MODE_DIR)/.VSIGA_partialImageObject.list $(ADDED_OBJECTS) $(IDE_LIBRARIES) $(LIBPATH) $(LIBS) $(ADDED_LIBPATH) $(ADDED_LIBS) && if [ "$(EXPAND_DBG)" = "1" ]; then plink "$@";fi

else
VSIGA_partialImage/$(MODE_DIR)/VSIGA_partialImage.o : VSIGA_partialImage/$(MODE_DIR)/VSIGA_partialImage.o_jobs

endif
VSIGA_partialImage/$(MODE_DIR)/VSIGA_partialImage_compile_file : $(FILE) ;

_clean :: VSIGA_partialImage/$(MODE_DIR)/VSIGA_partialImage_clean

VSIGA_partialImage/$(MODE_DIR)/VSIGA_partialImage_clean : 
	$(TRACE_FLAG)if [ -d "VSIGA_partialImage" ]; then cd "VSIGA_partialImage"; rm -rf $(MODE_DIR); fi

force : 

TARGET_JOBS_RULE?=echo "Update the makefile template via File > Import > Build Settings : Update makefile template";exit 1
%_jobs : 
	$(TRACE_FLAG)$(TARGET_JOBS_RULE)

DEP_FILES := VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/Anal/Collect/DataFile/DataFile.d VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/Anal/Collect/ccollectbank/ccollectbank.d VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/Anal/EmitterMerge/CEP/AnalyticCEP.d \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/Anal/EmitterMerge/Coordinate/Coordinate.d VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/Anal/EmitterMerge/DistanceLeastSquare/DistanceLeastSquare.d VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/Anal/EmitterMerge/GeoCoordConv/GeoCoordConv.d \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/Anal/EmitterMerge/InverseMethod/CInverseMethod.d VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/Anal/EmitterMerge/Matrix/Matrix.d VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/Anal/EmitterMerge/Quadratic/Quadratic.d \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/Anal/EmitterMerge/UTM/UTM.d VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/Anal/Identify/ELUtil.d VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/Anal/Identify/Identify.d \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/Anal/Identify/cipl.d VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/Anal/MIDAS/ELDecoder.d VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/Anal/MIDAS/Midas.d \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/Anal/MIDAS/PDW2SP370.d VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/Anal/MIDAS/RawFile.d VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/System/csharedmemory.d \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/System/csysconfig.d VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/Thread/creclan.d VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/Thread/csignalcollect.d \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/Thread/ctaskmngr.d VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/Thread/curbit.d VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/Thread/cusercollect.d \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/Utils/carraymsgdata.d VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/Utils/ccommonutils.d VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/Utils/clog.d \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/Utils/csingleclient.d VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/Utils/csingleserver.d VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/Utils/cthread.d \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/Utils/programrev.d VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/cmain.d VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/dkm.d
-include $(DEP_FILES)

OBJ_DIRS := VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/Anal/EmitterMerge/DistanceLeastSquare \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/Anal/EmitterMerge/InverseMethod \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/Anal/EmitterMerge/GeoCoordConv \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/Anal/EmitterMerge/Coordinate \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/Anal/Collect/ccollectbank \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/Anal/EmitterMerge/Quadratic \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/Anal/EmitterMerge/CEP \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/Anal/EmitterMerge/Matrix \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/Anal/Collect/DataFile \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/Anal/EmitterMerge/UTM \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/Anal/Identify \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/Thread \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/Anal/MIDAS \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/System \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/Utils
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
