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

BUILD_SPEC = VSourceBuild_PPCE6500gnu_SMP
DEBUG_MODE = 1
ifeq ($(DEBUG_MODE),1)
MODE_DIR := Debug
else
MODE_DIR := NonDebug
endif
OBJ_DIR := .
WS_ROOT_DIR := D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace
PRJ_ROOT_DIR := $(WS_ROOT_DIR)/VSIGA



#Global Build Macros
PROJECT_TYPE = DKM
DEFINES = 
EXPAND_DBG = 0
APICHECK_OPTIONS = -warning
POST_BUILD_RULE = dir


#BuildSpec specific Build Macros
VX_CPU_FAMILY = ppc
CPU = PPCE6500
TOOL_FAMILY = gnu
TOOL_VERSION = gnu_4_8_1_8
_CC_VERSION = gnu_4_8_1_10
TOOL = gnu
TOOL_PATH = $(WIND_HOME)/compilers/gnu-4.8.1.10/$(WIND_VX7_GNU_HOST_TYPE)/bin
CC_ARCH_SPEC = -mcpu=e6500 -D_WRS_HARDWARE_FP -fstrength-reduce -fno-builtin -mhard-float -fno-implicit-fp -mstrict-align
VSB_DIR = $(PRJ_ROOT_DIR)/../VSourceBuild_T2MS
VSB_CONFIG_FILE = $(VSB_DIR)/h/config/vsbConfig.h
LIBPATH = 
LIBS = 
DKM_LONGCALL = -mlongcall
BDGEN_VSB_INCLUDE = $(VSB_DIR)/h/config/auto.conf
APICHECK_CMD = apicheck.sh -r "$(VSB_DIR)/krnl/apicheck/forbidden_api.lst" -n "nmppc" -u -s "$<" "$@" $(APICHECK_OPTIONS)
APICHECK = 0

IDE_INCLUDES = -I$(VSB_DIR)/share/h -I$(VSB_DIR)/krnl/h/system -I$(VSB_DIR)/krnl/h/public -I$(PRJ_ROOT_DIR)/../../MSC/MSIGA 

IDE_LIBRARIES = 

IDE_DEFINES = -DCPU=_VX_$(CPU) -DSQLITE_THREADSAFE=1 -D_SIMPDW_ -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -D_WRS_VX_SMP -D_WRS_CONFIG_SMP -D_VSB_CONFIG_FILE=\"$(VSB_DIR)/h/config/vsbConfig.h\" -D_TRACK_ENABLED1_ -D__VXWORKS__ -D_POCKETSONATA_ -D_SQLITE_ -D_TESTSBC1_ 



#BuildTool flags
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C-Compiler = -gdwarf-3
DEBUGFLAGS_C++-Compiler = -gdwarf-3
DEBUGFLAGS_Linker = -gdwarf-3
DEBUGFLAGS_Partial-Image-Linker = 
DEBUGFLAGS_Librarian = 
DEBUGFLAGS_Assembler = -gdwarf-3
DEBUGFLAGS_POST = 
else
DEBUGFLAGS_C-Compiler = -O2
DEBUGFLAGS_C++-Compiler = -O2
DEBUGFLAGS_Linker = -O2
DEBUGFLAGS_Partial-Image-Linker = 
DEBUGFLAGS_Librarian = 
DEBUGFLAGS_Assembler = -O2
DEBUGFLAGS_POST = 
endif


#Project Targets
PROJECT_TARGETS = VSIGA/$(MODE_DIR)/VSIGA.out \
	 VSIGA_partialImage/$(MODE_DIR)/VSIGA_partialImage.o


#Rules

# VSIGA
ifeq ($(DEBUG_MODE),1)
VSIGA/$(MODE_DIR)/% : DEBUGFLAGS_C-Compiler = -gdwarf-3
VSIGA/$(MODE_DIR)/% : DEBUGFLAGS_C++-Compiler = -gdwarf-3
VSIGA/$(MODE_DIR)/% : DEBUGFLAGS_Linker = -gdwarf-3
VSIGA/$(MODE_DIR)/% : DEBUGFLAGS_Partial-Image-Linker = 
VSIGA/$(MODE_DIR)/% : DEBUGFLAGS_Librarian = 
VSIGA/$(MODE_DIR)/% : DEBUGFLAGS_Assembler = -gdwarf-3
VSIGA/$(MODE_DIR)/% : DEBUGFLAGS_POST = 
else
VSIGA/$(MODE_DIR)/% : DEBUGFLAGS_C-Compiler = -O2
VSIGA/$(MODE_DIR)/% : DEBUGFLAGS_C++-Compiler = -O2
VSIGA/$(MODE_DIR)/% : DEBUGFLAGS_Linker = -O2
VSIGA/$(MODE_DIR)/% : DEBUGFLAGS_Partial-Image-Linker = 
VSIGA/$(MODE_DIR)/% : DEBUGFLAGS_Librarian = 
VSIGA/$(MODE_DIR)/% : DEBUGFLAGS_Assembler = -O2
VSIGA/$(MODE_DIR)/% : DEBUGFLAGS_POST = 
endif
VSIGA/$(MODE_DIR)/% : IDE_INCLUDES = -I$(VSB_DIR)/share/h -I$(VSB_DIR)/krnl/h/system -I$(VSB_DIR)/krnl/h/public -I$(PRJ_ROOT_DIR)/../../MSC/MSIGA 
VSIGA/$(MODE_DIR)/% : IDE_LIBRARIES = 
VSIGA/$(MODE_DIR)/% : IDE_DEFINES = -DCPU=_VX_$(CPU) -DSQLITE_THREADSAFE=1 -D_SIMPDW_ -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -D_WRS_VX_SMP -D_WRS_CONFIG_SMP -D_VSB_CONFIG_FILE=\"$(VSB_DIR)/h/config/vsbConfig.h\" -D_TRACK_ENABLED1_ -D__VXWORKS__ -D_POCKETSONATA_ -D_SQLITE_ -D_TESTSBC1_ 
VSIGA/$(MODE_DIR)/% : PROJECT_TYPE = DKM
VSIGA/$(MODE_DIR)/% : DEFINES = 
VSIGA/$(MODE_DIR)/% : EXPAND_DBG = 0
VSIGA/$(MODE_DIR)/% : APICHECK_OPTIONS = -warning
VSIGA/$(MODE_DIR)/% : POST_BUILD_RULE = ls
VSIGA/$(MODE_DIR)/% : VX_CPU_FAMILY = ppc
VSIGA/$(MODE_DIR)/% : CPU = PPCE6500
VSIGA/$(MODE_DIR)/% : TOOL_FAMILY = gnu
VSIGA/$(MODE_DIR)/% : TOOL_VERSION = gnu_4_8_1_8
VSIGA/$(MODE_DIR)/% : _CC_VERSION = gnu_4_8_1_10
VSIGA/$(MODE_DIR)/% : TOOL = gnu
VSIGA/$(MODE_DIR)/% : TOOL_PATH = $(WIND_HOME)/compilers/gnu-4.8.1.10/$(WIND_VX7_GNU_HOST_TYPE)/bin
VSIGA/$(MODE_DIR)/% : CC_ARCH_SPEC = -mcpu=e6500 -D_WRS_HARDWARE_FP -fstrength-reduce -fno-builtin -mhard-float -fno-implicit-fp -mstrict-align
VSIGA/$(MODE_DIR)/% : VSB_DIR = $(PRJ_ROOT_DIR)/../VSourceBuild_T2MS
VSIGA/$(MODE_DIR)/% : VSB_CONFIG_FILE = $(VSB_DIR)/h/config/vsbConfig.h
VSIGA/$(MODE_DIR)/% : LIBPATH = 
VSIGA/$(MODE_DIR)/% : LIBS = 
VSIGA/$(MODE_DIR)/% : DKM_LONGCALL = -mlongcall
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
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building link $@";rm -f "$@";nmppc @VSIGA/$(MODE_DIR)/.VSIGAObject.list | tclsh $(WIND_BASE)/build/mk/tcl/munch.tcl -c ppc -tags $(VSB_DIR)/krnl/tags/dkm.tags > $(OBJ_DIR)/ctdt.c; $(TOOL_PATH)/ccppc $(DEBUGFLAGS_Linker) $(CC_ARCH_SPEC) -fdollars-in-identifiers -Wall   $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES)  $(DKM_LONGCALL) $(IDE_DEFINES) $(DEFINES) -o $(OBJ_DIR)/ctdt.o -c $(OBJ_DIR)/ctdt.c;  $(TOOL_PATH)/ccppc -r -nostdlib -Wl,-X -T $(WIND_BASE)/build/tool/gnu_4_8_1_8/krnl/ldscripts/link.OUT -o "$@" $(OBJ_DIR)/ctdt.o @VSIGA/$(MODE_DIR)/.VSIGAObject.list $(IDE_LIBRARIES) $(LIBPATH) $(LIBS) $(ADDED_LIBPATH) $(ADDED_LIBS) && if [ "$(EXPAND_DBG)" = "1" ]; then plink "$@";fi && $(if $(_WRS_CONFIG_SECURE_LOADER),signtool  --key=$(_WRS_CONFIG_SECURE_LOADER_PRIVATE_SIGNING_KEY_FILE) --cert=$(_WRS_CONFIG_SECURE_LOADER_PUBLIC_SIGNING_CERT_FILE) --type=ELF $@,true);rm "d:/tftpboot/*.out";cp "$@" d:/tftpboot/.

else
VSIGA/$(MODE_DIR)/VSIGA.out : VSIGA/$(MODE_DIR)/VSIGA.out_jobs

endif
VSIGA/$(MODE_DIR)/VSIGA_compile_file : $(FILE) ;

_clean :: VSIGA/$(MODE_DIR)/VSIGA_clean

VSIGA/$(MODE_DIR)/VSIGA_clean : 
	$(TRACE_FLAG)if [ -d "VSIGA" ]; then cd "VSIGA"; rm -rf $(MODE_DIR); fi


# VSIGA_partialImage
ifeq ($(DEBUG_MODE),1)
VSIGA_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_C-Compiler = -gdwarf-3
VSIGA_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_C++-Compiler = -gdwarf-3
VSIGA_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Linker = -gdwarf-3
VSIGA_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Partial-Image-Linker = 
VSIGA_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Librarian = 
VSIGA_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Assembler = -gdwarf-3
VSIGA_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_POST = 
else
VSIGA_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_C-Compiler = -O2
VSIGA_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_C++-Compiler = -O2
VSIGA_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Linker = -O2
VSIGA_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Partial-Image-Linker = 
VSIGA_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Librarian = 
VSIGA_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Assembler = -O2
VSIGA_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_POST = 
endif
VSIGA_partialImage/$(MODE_DIR)/% : IDE_INCLUDES = -I$(VSB_DIR)/share/h -I$(VSB_DIR)/krnl/h/system -I$(VSB_DIR)/krnl/h/public -I$(PRJ_ROOT_DIR)/../../MSC/MSIGA 
VSIGA_partialImage/$(MODE_DIR)/% : IDE_LIBRARIES = 
VSIGA_partialImage/$(MODE_DIR)/% : IDE_DEFINES = -DCPU=_VX_$(CPU) -DSQLITE_THREADSAFE=1 -D_SIMPDW_ -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -D_WRS_VX_SMP -D_WRS_CONFIG_SMP -D_VSB_CONFIG_FILE=\"$(VSB_DIR)/h/config/vsbConfig.h\" -D_TRACK_ENABLED1_ -D__VXWORKS__ -D_POCKETSONATA_ -D_SQLITE_ -D_TESTSBC1_ 
VSIGA_partialImage/$(MODE_DIR)/% : PROJECT_TYPE = DKM
VSIGA_partialImage/$(MODE_DIR)/% : DEFINES = 
VSIGA_partialImage/$(MODE_DIR)/% : EXPAND_DBG = 0
VSIGA_partialImage/$(MODE_DIR)/% : APICHECK_OPTIONS = -warning
VSIGA_partialImage/$(MODE_DIR)/% : POST_BUILD_RULE = dir
VSIGA_partialImage/$(MODE_DIR)/% : VX_CPU_FAMILY = ppc
VSIGA_partialImage/$(MODE_DIR)/% : CPU = PPCE6500
VSIGA_partialImage/$(MODE_DIR)/% : TOOL_FAMILY = gnu
VSIGA_partialImage/$(MODE_DIR)/% : TOOL_VERSION = gnu_4_8_1_8
VSIGA_partialImage/$(MODE_DIR)/% : _CC_VERSION = gnu_4_8_1_10
VSIGA_partialImage/$(MODE_DIR)/% : TOOL = gnu
VSIGA_partialImage/$(MODE_DIR)/% : TOOL_PATH = $(WIND_HOME)/compilers/gnu-4.8.1.10/$(WIND_VX7_GNU_HOST_TYPE)/bin
VSIGA_partialImage/$(MODE_DIR)/% : CC_ARCH_SPEC = -mcpu=e6500 -D_WRS_HARDWARE_FP -fstrength-reduce -fno-builtin -mhard-float -fno-implicit-fp -mstrict-align
VSIGA_partialImage/$(MODE_DIR)/% : VSB_DIR = $(PRJ_ROOT_DIR)/../VSourceBuild_T2MS
VSIGA_partialImage/$(MODE_DIR)/% : VSB_CONFIG_FILE = $(VSB_DIR)/h/config/vsbConfig.h
VSIGA_partialImage/$(MODE_DIR)/% : LIBPATH = 
VSIGA_partialImage/$(MODE_DIR)/% : LIBS = 
VSIGA_partialImage/$(MODE_DIR)/% : DKM_LONGCALL = -mlongcall
VSIGA_partialImage/$(MODE_DIR)/% : BDGEN_VSB_INCLUDE = $(VSB_DIR)/h/config/auto.conf
VSIGA_partialImage/$(MODE_DIR)/% : APICHECK_CMD = apicheck.sh -r "$(VSB_DIR)/krnl/apicheck/forbidden_api.lst" -n "nmppc" -u -s "$<" "$@" $(APICHECK_OPTIONS)
VSIGA_partialImage/$(MODE_DIR)/% : APICHECK = 0
VSIGA_partialImage/$(MODE_DIR)/% : OBJ_DIR := VSIGA_partialImage/$(MODE_DIR)

VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/cmain.o : D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/files/cmain.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)/g++ppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi  -fno-zero-initialized-in-bss -Wall    -MD -MP $(DKM_LONGCALL) -fexceptions $(IDE_DEFINES) $(DEFINES) $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -std=c++11 -o "$@" -c "$<" && if [ "$(APICHECK)" = "1" ]; then $(APICHECK_CMD);fi


VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/dkm.o : $(PRJ_ROOT_DIR)/dkm.c $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)/ccppc $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -ansi  -fno-zero-initialized-in-bss -Wall    -MD -MP $(DKM_LONGCALL) $(IDE_DEFINES) $(DEFINES) $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -o "$@" -c "$<" && if [ "$(APICHECK)" = "1" ]; then $(APICHECK_CMD);fi


VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/Collect/DataFile/DataFile.o : D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/files/Anal/Collect/DataFile/DataFile.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)/g++ppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi  -fno-zero-initialized-in-bss -Wall  -std=c++11 -MD -MP $(DKM_LONGCALL) -fexceptions -w -mstrict-align $(IDE_DEFINES) $(DEFINES) $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -std=c++11 -o "$@" -c "$<" && if [ "$(APICHECK)" = "1" ]; then $(APICHECK_CMD);fi


VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/Collect/GenPDW/CGenPDW.o : D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/files/Anal/Collect/GenPDW/CGenPDW.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)/g++ppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi  -fno-zero-initialized-in-bss -Wall  -std=c++11 -MD -MP $(DKM_LONGCALL) -fexceptions -w -mstrict-align $(IDE_DEFINES) $(DEFINES) $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -std=c++11 -o "$@" -c "$<" && if [ "$(APICHECK)" = "1" ]; then $(APICHECK_CMD);fi


VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/Collect/ccollectbank/ccollectbank.o : D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/files/Anal/Collect/ccollectbank/ccollectbank.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)/g++ppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi  -fno-zero-initialized-in-bss -Wall  -std=c++11 -MD -MP $(DKM_LONGCALL) -fexceptions -w -mstrict-align $(IDE_DEFINES) $(DEFINES) $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -std=c++11 -o "$@" -c "$<" && if [ "$(APICHECK)" = "1" ]; then $(APICHECK_CMD);fi


VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/EmitterMerge/CEP/AnalyticCEP.o : D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/files/Anal/EmitterMerge/CEP/AnalyticCEP.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)/g++ppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi  -fno-zero-initialized-in-bss -Wall  -std=c++11 -MD -MP $(DKM_LONGCALL) -fexceptions -w -mstrict-align $(IDE_DEFINES) $(DEFINES) $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -std=c++11 -o "$@" -c "$<" && if [ "$(APICHECK)" = "1" ]; then $(APICHECK_CMD);fi


VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/EmitterMerge/Coordinate/Coordinate.o : D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/files/Anal/EmitterMerge/Coordinate/Coordinate.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)/g++ppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi  -fno-zero-initialized-in-bss -Wall  -std=c++11 -MD -MP $(DKM_LONGCALL) -fexceptions -w -mstrict-align $(IDE_DEFINES) $(DEFINES) $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -std=c++11 -o "$@" -c "$<" && if [ "$(APICHECK)" = "1" ]; then $(APICHECK_CMD);fi


VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/EmitterMerge/DistanceLeastSquare/DistanceLeastSquare.o : D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/files/Anal/EmitterMerge/DistanceLeastSquare/DistanceLeastSquare.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)/g++ppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi  -fno-zero-initialized-in-bss -Wall  -std=c++11 -MD -MP $(DKM_LONGCALL) -fexceptions -w -mstrict-align $(IDE_DEFINES) $(DEFINES) $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -std=c++11 -o "$@" -c "$<" && if [ "$(APICHECK)" = "1" ]; then $(APICHECK_CMD);fi


VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/EmitterMerge/ELEmitterMergeMngr.o : D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/files/Anal/EmitterMerge/ELEmitterMergeMngr.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)/g++ppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi  -fno-zero-initialized-in-bss -Wall  -std=c++11 -MD -MP $(DKM_LONGCALL) -fexceptions -w -mstrict-align $(IDE_DEFINES) $(DEFINES) $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -std=c++11 -o "$@" -c "$<" && if [ "$(APICHECK)" = "1" ]; then $(APICHECK_CMD);fi


VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/EmitterMerge/ELEnvironVariableMngr.o : D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/files/Anal/EmitterMerge/ELEnvironVariableMngr.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)/g++ppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi  -fno-zero-initialized-in-bss -Wall  -std=c++11 -MD -MP $(DKM_LONGCALL) -fexceptions -w -mstrict-align $(IDE_DEFINES) $(DEFINES) $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -std=c++11 -o "$@" -c "$<" && if [ "$(APICHECK)" = "1" ]; then $(APICHECK_CMD);fi


VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/EmitterMerge/ELThreat.o : D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/files/Anal/EmitterMerge/ELThreat.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)/g++ppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi  -fno-zero-initialized-in-bss -Wall  -std=c++11 -MD -MP $(DKM_LONGCALL) -fexceptions -w -mstrict-align $(IDE_DEFINES) $(DEFINES) $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -std=c++11 -o "$@" -c "$<" && if [ "$(APICHECK)" = "1" ]; then $(APICHECK_CMD);fi


VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/EmitterMerge/GeoCoordConv/GeoCoordConv.o : D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/files/Anal/EmitterMerge/GeoCoordConv/GeoCoordConv.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)/g++ppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi  -fno-zero-initialized-in-bss -Wall  -std=c++11 -MD -MP $(DKM_LONGCALL) -fexceptions -w -mstrict-align $(IDE_DEFINES) $(DEFINES) $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -std=c++11 -o "$@" -c "$<" && if [ "$(APICHECK)" = "1" ]; then $(APICHECK_CMD);fi


VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/EmitterMerge/InverseMethod/CInverseMethod.o : D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/files/Anal/EmitterMerge/InverseMethod/CInverseMethod.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)/g++ppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi  -fno-zero-initialized-in-bss -Wall  -std=c++11 -MD -MP $(DKM_LONGCALL) -fexceptions -w -mstrict-align $(IDE_DEFINES) $(DEFINES) $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -std=c++11 -o "$@" -c "$<" && if [ "$(APICHECK)" = "1" ]; then $(APICHECK_CMD);fi


VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/EmitterMerge/LOBClustering.o : D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/files/Anal/EmitterMerge/LOBClustering.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)/g++ppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi  -fno-zero-initialized-in-bss -Wall  -std=c++11 -MD -MP $(DKM_LONGCALL) -fexceptions -w -mstrict-align $(IDE_DEFINES) $(DEFINES) $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -std=c++11 -o "$@" -c "$<" && if [ "$(APICHECK)" = "1" ]; then $(APICHECK_CMD);fi


VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/EmitterMerge/Matrix/Matrix.o : D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/files/Anal/EmitterMerge/Matrix/Matrix.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)/g++ppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi  -fno-zero-initialized-in-bss -Wall  -std=c++11 -MD -MP $(DKM_LONGCALL) -fexceptions -w -mstrict-align $(IDE_DEFINES) $(DEFINES) $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -std=c++11 -o "$@" -c "$<" && if [ "$(APICHECK)" = "1" ]; then $(APICHECK_CMD);fi


VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/EmitterMerge/PositionEstimationAlg.o : D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/files/Anal/EmitterMerge/PositionEstimationAlg.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)/g++ppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi  -fno-zero-initialized-in-bss -Wall  -std=c++11 -MD -MP $(DKM_LONGCALL) -fexceptions -w -mstrict-align $(IDE_DEFINES) $(DEFINES) $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -std=c++11 -o "$@" -c "$<" && if [ "$(APICHECK)" = "1" ]; then $(APICHECK_CMD);fi


VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/EmitterMerge/Quadratic/Quadratic.o : D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/files/Anal/EmitterMerge/Quadratic/Quadratic.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)/g++ppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi  -fno-zero-initialized-in-bss -Wall  -std=c++11 -MD -MP $(DKM_LONGCALL) -fexceptions -w -mstrict-align $(IDE_DEFINES) $(DEFINES) $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -std=c++11 -o "$@" -c "$<" && if [ "$(APICHECK)" = "1" ]; then $(APICHECK_CMD);fi


VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/EmitterMerge/UTM/UTM.o : D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/files/Anal/EmitterMerge/UTM/UTM.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)/g++ppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi  -fno-zero-initialized-in-bss -Wall  -std=c++11 -MD -MP $(DKM_LONGCALL) -fexceptions -w -mstrict-align $(IDE_DEFINES) $(DEFINES) $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -std=c++11 -o "$@" -c "$<" && if [ "$(APICHECK)" = "1" ]; then $(APICHECK_CMD);fi


VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/Identify/ELUtil.o : D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/files/Anal/Identify/ELUtil.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)/g++ppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi  -fno-zero-initialized-in-bss -Wall  -std=c++11 -MD -MP $(DKM_LONGCALL) -fexceptions -w -mstrict-align $(IDE_DEFINES) $(DEFINES) $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -std=c++11 -o "$@" -c "$<" && if [ "$(APICHECK)" = "1" ]; then $(APICHECK_CMD);fi


VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/Identify/Identify.o : D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/files/Anal/Identify/Identify.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)/g++ppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi  -fno-zero-initialized-in-bss -Wall  -std=c++11 -MD -MP $(DKM_LONGCALL) -fexceptions -w -mstrict-align $(IDE_DEFINES) $(DEFINES) $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -std=c++11 -o "$@" -c "$<" && if [ "$(APICHECK)" = "1" ]; then $(APICHECK_CMD);fi


VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/Identify/cipl.o : D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/files/Anal/Identify/cipl.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)/g++ppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi  -fno-zero-initialized-in-bss -Wall  -std=c++11 -MD -MP $(DKM_LONGCALL) -fexceptions -w -mstrict-align $(IDE_DEFINES) $(DEFINES) $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -std=c++11 -o "$@" -c "$<" && if [ "$(APICHECK)" = "1" ]; then $(APICHECK_CMD);fi


VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/IntraSigAnal/IntraSigAnal.o : D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/files/Anal/IntraSigAnal/IntraSigAnal.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)/g++ppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi  -fno-zero-initialized-in-bss -Wall  -std=c++11 -MD -MP $(DKM_LONGCALL) -fexceptions -w -mstrict-align $(IDE_DEFINES) $(DEFINES) $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -std=c++11 -o "$@" -c "$<" && if [ "$(APICHECK)" = "1" ]; then $(APICHECK_CMD);fi


VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/KnownSigAnal/KAnalPRI.o : D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/files/Anal/KnownSigAnal/KAnalPRI.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)/g++ppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi  -fno-zero-initialized-in-bss -Wall  -std=c++11 -MD -MP $(DKM_LONGCALL) -fexceptions -w -mstrict-align $(IDE_DEFINES) $(DEFINES) $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -std=c++11 -o "$@" -c "$<" && if [ "$(APICHECK)" = "1" ]; then $(APICHECK_CMD);fi


VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/KnownSigAnal/KGroup.o : D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/files/Anal/KnownSigAnal/KGroup.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)/g++ppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi  -fno-zero-initialized-in-bss -Wall  -std=c++11 -MD -MP $(DKM_LONGCALL) -fexceptions -w -mstrict-align $(IDE_DEFINES) $(DEFINES) $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -std=c++11 -o "$@" -c "$<" && if [ "$(APICHECK)" = "1" ]; then $(APICHECK_CMD);fi


VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/KnownSigAnal/KMakeAET.o : D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/files/Anal/KnownSigAnal/KMakeAET.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)/g++ppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi  -fno-zero-initialized-in-bss -Wall  -std=c++11 -MD -MP $(DKM_LONGCALL) -fexceptions -w -mstrict-align $(IDE_DEFINES) $(DEFINES) $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -std=c++11 -o "$@" -c "$<" && if [ "$(APICHECK)" = "1" ]; then $(APICHECK_CMD);fi


VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/KnownSigAnal/KPulExt.o : D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/files/Anal/KnownSigAnal/KPulExt.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)/g++ppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi  -fno-zero-initialized-in-bss -Wall  -std=c++11 -MD -MP $(DKM_LONGCALL) -fexceptions -w -mstrict-align $(IDE_DEFINES) $(DEFINES) $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -std=c++11 -o "$@" -c "$<" && if [ "$(APICHECK)" = "1" ]; then $(APICHECK_CMD);fi


VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/KnownSigAnal/KnownSigAnal.o : D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/files/Anal/KnownSigAnal/KnownSigAnal.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)/g++ppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi  -fno-zero-initialized-in-bss -Wall  -std=c++11 -MD -MP $(DKM_LONGCALL) -fexceptions -w -mstrict-align $(IDE_DEFINES) $(DEFINES) $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -std=c++11 -o "$@" -c "$<" && if [ "$(APICHECK)" = "1" ]; then $(APICHECK_CMD);fi


VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/MIDAS/ELDecoder.o : D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/files/Anal/MIDAS/ELDecoder.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)/g++ppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi  -fno-zero-initialized-in-bss -Wall  -std=c++11 -MD -MP $(DKM_LONGCALL) -fexceptions -w -mstrict-align $(IDE_DEFINES) $(DEFINES) $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -std=c++11 -o "$@" -c "$<" && if [ "$(APICHECK)" = "1" ]; then $(APICHECK_CMD);fi


VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/MIDAS/Midas.o : D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/files/Anal/MIDAS/Midas.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)/g++ppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi  -fno-zero-initialized-in-bss -Wall  -std=c++11 -MD -MP $(DKM_LONGCALL) -fexceptions -w -mstrict-align $(IDE_DEFINES) $(DEFINES) $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -std=c++11 -o "$@" -c "$<" && if [ "$(APICHECK)" = "1" ]; then $(APICHECK_CMD);fi


VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/MIDAS/PDW2SP370.o : D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/files/Anal/MIDAS/PDW2SP370.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)/g++ppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi  -fno-zero-initialized-in-bss -Wall  -std=c++11 -MD -MP $(DKM_LONGCALL) -fexceptions -w -mstrict-align $(IDE_DEFINES) $(DEFINES) $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -std=c++11 -o "$@" -c "$<" && if [ "$(APICHECK)" = "1" ]; then $(APICHECK_CMD);fi


VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/MIDAS/RawFile.o : D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/files/Anal/MIDAS/RawFile.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)/g++ppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi  -fno-zero-initialized-in-bss -Wall  -std=c++11 -MD -MP $(DKM_LONGCALL) -fexceptions -w -mstrict-align $(IDE_DEFINES) $(DEFINES) $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -std=c++11 -o "$@" -c "$<" && if [ "$(APICHECK)" = "1" ]; then $(APICHECK_CMD);fi


VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/NewSigAnal/NAnalPRI.o : D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/files/Anal/NewSigAnal/NAnalPRI.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)/g++ppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi  -fno-zero-initialized-in-bss -Wall  -std=c++11 -MD -MP $(DKM_LONGCALL) -fexceptions -w -mstrict-align $(IDE_DEFINES) $(DEFINES) $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -std=c++11 -o "$@" -c "$<" && if [ "$(APICHECK)" = "1" ]; then $(APICHECK_CMD);fi


VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/NewSigAnal/NGroup.o : D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/files/Anal/NewSigAnal/NGroup.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)/g++ppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi  -fno-zero-initialized-in-bss -Wall  -std=c++11 -MD -MP $(DKM_LONGCALL) -fexceptions -w -mstrict-align $(IDE_DEFINES) $(DEFINES) $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -std=c++11 -o "$@" -c "$<" && if [ "$(APICHECK)" = "1" ]; then $(APICHECK_CMD);fi


VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/NewSigAnal/NMakeAET.o : D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/files/Anal/NewSigAnal/NMakeAET.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)/g++ppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi  -fno-zero-initialized-in-bss -Wall  -std=c++11 -MD -MP $(DKM_LONGCALL) -fexceptions -w -mstrict-align $(IDE_DEFINES) $(DEFINES) $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -std=c++11 -o "$@" -c "$<" && if [ "$(APICHECK)" = "1" ]; then $(APICHECK_CMD);fi


VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/NewSigAnal/NPulExt.o : D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/files/Anal/NewSigAnal/NPulExt.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)/g++ppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi  -fno-zero-initialized-in-bss -Wall  -std=c++11 -MD -MP $(DKM_LONGCALL) -fexceptions -w -mstrict-align $(IDE_DEFINES) $(DEFINES) $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -std=c++11 -o "$@" -c "$<" && if [ "$(APICHECK)" = "1" ]; then $(APICHECK_CMD);fi


VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/NewSigAnal/NewSigAnal.o : D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/files/Anal/NewSigAnal/NewSigAnal.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)/g++ppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi  -fno-zero-initialized-in-bss -Wall  -std=c++11 -MD -MP $(DKM_LONGCALL) -fexceptions -w -mstrict-align $(IDE_DEFINES) $(DEFINES) $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -std=c++11 -o "$@" -c "$<" && if [ "$(APICHECK)" = "1" ]; then $(APICHECK_CMD);fi


VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/ScanSigAnal/SAnalSCN.o : D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/files/Anal/ScanSigAnal/SAnalSCN.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)/g++ppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi  -fno-zero-initialized-in-bss -Wall  -std=c++11 -MD -MP $(DKM_LONGCALL) -fexceptions -w -mstrict-align $(IDE_DEFINES) $(DEFINES) $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -std=c++11 -o "$@" -c "$<" && if [ "$(APICHECK)" = "1" ]; then $(APICHECK_CMD);fi


VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/ScanSigAnal/SGroup.o : D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/files/Anal/ScanSigAnal/SGroup.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)/g++ppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi  -fno-zero-initialized-in-bss -Wall  -std=c++11 -MD -MP $(DKM_LONGCALL) -fexceptions -w -mstrict-align $(IDE_DEFINES) $(DEFINES) $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -std=c++11 -o "$@" -c "$<" && if [ "$(APICHECK)" = "1" ]; then $(APICHECK_CMD);fi


VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/ScanSigAnal/SPulExt.o : D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/files/Anal/ScanSigAnal/SPulExt.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)/g++ppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi  -fno-zero-initialized-in-bss -Wall  -std=c++11 -MD -MP $(DKM_LONGCALL) -fexceptions -w -mstrict-align $(IDE_DEFINES) $(DEFINES) $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -std=c++11 -o "$@" -c "$<" && if [ "$(APICHECK)" = "1" ]; then $(APICHECK_CMD);fi


VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/ScanSigAnal/ScanSigAnal.o : D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/files/Anal/ScanSigAnal/ScanSigAnal.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)/g++ppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi  -fno-zero-initialized-in-bss -Wall  -std=c++11 -MD -MP $(DKM_LONGCALL) -fexceptions -w -mstrict-align $(IDE_DEFINES) $(DEFINES) $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -std=c++11 -o "$@" -c "$<" && if [ "$(APICHECK)" = "1" ]; then $(APICHECK_CMD);fi


VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/SigAnal/AnalPRI.o : D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/files/Anal/SigAnal/AnalPRI.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)/g++ppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi  -fno-zero-initialized-in-bss -Wall  -std=c++11 -MD -MP $(DKM_LONGCALL) -fexceptions -w -mstrict-align $(IDE_DEFINES) $(DEFINES) $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -std=c++11 -o "$@" -c "$<" && if [ "$(APICHECK)" = "1" ]; then $(APICHECK_CMD);fi


VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/SigAnal/Group.o : D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/files/Anal/SigAnal/Group.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)/g++ppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi  -fno-zero-initialized-in-bss -Wall  -std=c++11 -MD -MP $(DKM_LONGCALL) -fexceptions -w -mstrict-align $(IDE_DEFINES) $(DEFINES) $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -std=c++11 -o "$@" -c "$<" && if [ "$(APICHECK)" = "1" ]; then $(APICHECK_CMD);fi


VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/SigAnal/MakeAET.o : D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/files/Anal/SigAnal/MakeAET.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)/g++ppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi  -fno-zero-initialized-in-bss -Wall  -std=c++11 -MD -MP $(DKM_LONGCALL) -fexceptions -w -mstrict-align $(IDE_DEFINES) $(DEFINES) $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -std=c++11 -o "$@" -c "$<" && if [ "$(APICHECK)" = "1" ]; then $(APICHECK_CMD);fi


VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/SigAnal/PulExt.o : D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/files/Anal/SigAnal/PulExt.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)/g++ppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi  -fno-zero-initialized-in-bss -Wall  -std=c++11 -MD -MP $(DKM_LONGCALL) -fexceptions -w -mstrict-align $(IDE_DEFINES) $(DEFINES) $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -std=c++11 -o "$@" -c "$<" && if [ "$(APICHECK)" = "1" ]; then $(APICHECK_CMD);fi


VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/SigAnal/SigAnal.o : D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/files/Anal/SigAnal/SigAnal.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)/g++ppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi  -fno-zero-initialized-in-bss -Wall  -std=c++11 -MD -MP $(DKM_LONGCALL) -fexceptions -w -mstrict-align $(IDE_DEFINES) $(DEFINES) $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -std=c++11 -o "$@" -c "$<" && if [ "$(APICHECK)" = "1" ]; then $(APICHECK_CMD);fi


VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/SigAnal/SysPara.o : D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/files/Anal/SigAnal/SysPara.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)/g++ppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi  -fno-zero-initialized-in-bss -Wall  -std=c++11 -MD -MP $(DKM_LONGCALL) -fexceptions -w -mstrict-align $(IDE_DEFINES) $(DEFINES) $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -std=c++11 -o "$@" -c "$<" && if [ "$(APICHECK)" = "1" ]; then $(APICHECK_CMD);fi


VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/SigAnal/cencdec.o : D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/files/Anal/SigAnal/cencdec.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)/g++ppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi  -fno-zero-initialized-in-bss -Wall  -std=c++11 -MD -MP $(DKM_LONGCALL) -fexceptions -w -mstrict-align $(IDE_DEFINES) $(DEFINES) $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -std=c++11 -o "$@" -c "$<" && if [ "$(APICHECK)" = "1" ]; then $(APICHECK_CMD);fi


VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/MinIni/minIni.o : D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/files/MinIni/minIni.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)/g++ppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi  -fno-zero-initialized-in-bss -Wall  -std=c++11 -MD -MP $(DKM_LONGCALL) -fexceptions -w -mstrict-align $(IDE_DEFINES) $(DEFINES) $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -std=c++11 -o "$@" -c "$<" && if [ "$(APICHECK)" = "1" ]; then $(APICHECK_CMD);fi


VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/SQLite/KompexSQLiteBlob.o : D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/files/SQLite/KompexSQLiteBlob.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)/g++ppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi  -fno-zero-initialized-in-bss -Wall  -std=c++11 -MD -MP $(DKM_LONGCALL) -fexceptions -w -mstrict-align $(IDE_DEFINES) $(DEFINES) $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -std=c++11 -o "$@" -c "$<" && if [ "$(APICHECK)" = "1" ]; then $(APICHECK_CMD);fi


VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/SQLite/KompexSQLiteDatabase.o : D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/files/SQLite/KompexSQLiteDatabase.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)/g++ppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi  -fno-zero-initialized-in-bss -Wall  -std=c++11 -MD -MP $(DKM_LONGCALL) -fexceptions -w -mstrict-align $(IDE_DEFINES) $(DEFINES) $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -std=c++11 -o "$@" -c "$<" && if [ "$(APICHECK)" = "1" ]; then $(APICHECK_CMD);fi


VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/SQLite/KompexSQLiteStatement.o : D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/files/SQLite/KompexSQLiteStatement.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)/g++ppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi  -fno-zero-initialized-in-bss -Wall  -std=c++11 -MD -MP $(DKM_LONGCALL) -fexceptions -w -mstrict-align $(IDE_DEFINES) $(DEFINES) $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -std=c++11 -o "$@" -c "$<" && if [ "$(APICHECK)" = "1" ]; then $(APICHECK_CMD);fi


VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/SQLite/sqlite3.o : D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/files/SQLite/sqlite3.c $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)/ccppc $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -ansi  -fno-zero-initialized-in-bss -Wall    -MD -MP $(DKM_LONGCALL) $(IDE_DEFINES) $(DEFINES) $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -o "$@" -c "$<" && if [ "$(APICHECK)" = "1" ]; then $(APICHECK_CMD);fi


VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/System/csharedmemory.o : D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/files/System/csharedmemory.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)/g++ppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi  -fno-zero-initialized-in-bss -Wall  -std=c++11 -MD -MP $(DKM_LONGCALL) -fexceptions -w -mstrict-align $(IDE_DEFINES) $(DEFINES) $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -std=c++11 -o "$@" -c "$<" && if [ "$(APICHECK)" = "1" ]; then $(APICHECK_CMD);fi


VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/System/csysconfig.o : D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/files/System/csysconfig.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)/g++ppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi  -fno-zero-initialized-in-bss -Wall  -std=c++11 -MD -MP $(DKM_LONGCALL) -fexceptions -w -mstrict-align $(IDE_DEFINES) $(DEFINES) $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -std=c++11 -o "$@" -c "$<" && if [ "$(APICHECK)" = "1" ]; then $(APICHECK_CMD);fi


VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Thread/ccgi.o : D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/files/Thread/ccgi.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)/g++ppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi  -fno-zero-initialized-in-bss -Wall  -std=c++11 -MD -MP $(DKM_LONGCALL) -fexceptions -w -mstrict-align $(IDE_DEFINES) $(DEFINES) $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -std=c++11 -o "$@" -c "$<" && if [ "$(APICHECK)" = "1" ]; then $(APICHECK_CMD);fi


VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Thread/cdetectanalysis.o : D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/files/Thread/cdetectanalysis.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)/g++ppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi  -fno-zero-initialized-in-bss -Wall  -std=c++11 -MD -MP $(DKM_LONGCALL) -fexceptions -w -mstrict-align $(IDE_DEFINES) $(DEFINES) $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -std=c++11 -o "$@" -c "$<" && if [ "$(APICHECK)" = "1" ]; then $(APICHECK_CMD);fi


VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Thread/cemittermerge.o : D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/files/Thread/cemittermerge.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)/g++ppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi  -fno-zero-initialized-in-bss -Wall  -std=c++11 -MD -MP $(DKM_LONGCALL) -fexceptions -w -mstrict-align $(IDE_DEFINES) $(DEFINES) $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -std=c++11 -o "$@" -c "$<" && if [ "$(APICHECK)" = "1" ]; then $(APICHECK_CMD);fi


VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Thread/cjamtech.o : D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/files/Thread/cjamtech.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)/g++ppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi  -fno-zero-initialized-in-bss -Wall  -std=c++11 -MD -MP $(DKM_LONGCALL) -fexceptions -w -mstrict-align $(IDE_DEFINES) $(DEFINES) $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -std=c++11 -o "$@" -c "$<" && if [ "$(APICHECK)" = "1" ]; then $(APICHECK_CMD);fi


VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Thread/coperationconsole.o : D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/files/Thread/coperationconsole.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)/g++ppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi  -fno-zero-initialized-in-bss -Wall  -std=c++11 -MD -MP $(DKM_LONGCALL) -fexceptions -w -mstrict-align $(IDE_DEFINES) $(DEFINES) $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -std=c++11 -o "$@" -c "$<" && if [ "$(APICHECK)" = "1" ]; then $(APICHECK_CMD);fi


VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Thread/cprompt.o : D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/files/Thread/cprompt.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)/g++ppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi  -fno-zero-initialized-in-bss -Wall  -std=c++11 -MD -MP $(DKM_LONGCALL) -fexceptions -w -mstrict-align $(IDE_DEFINES) $(DEFINES) $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -std=c++11 -o "$@" -c "$<" && if [ "$(APICHECK)" = "1" ]; then $(APICHECK_CMD);fi


VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Thread/cpulsetrk.o : D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/files/Thread/cpulsetrk.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)/g++ppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi  -fno-zero-initialized-in-bss -Wall  -std=c++11 -MD -MP $(DKM_LONGCALL) -fexceptions -w -mstrict-align $(IDE_DEFINES) $(DEFINES) $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -std=c++11 -o "$@" -c "$<" && if [ "$(APICHECK)" = "1" ]; then $(APICHECK_CMD);fi


VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Thread/cscananalysis.o : D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/files/Thread/cscananalysis.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)/g++ppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi  -fno-zero-initialized-in-bss -Wall  -std=c++11 -MD -MP $(DKM_LONGCALL) -fexceptions -w -mstrict-align $(IDE_DEFINES) $(DEFINES) $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -std=c++11 -o "$@" -c "$<" && if [ "$(APICHECK)" = "1" ]; then $(APICHECK_CMD);fi


VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Thread/csignalcollect.o : D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/files/Thread/csignalcollect.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)/g++ppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi  -fno-zero-initialized-in-bss -Wall  -std=c++11 -MD -MP $(DKM_LONGCALL) -fexceptions -w -mstrict-align $(IDE_DEFINES) $(DEFINES) $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -std=c++11 -o "$@" -c "$<" && if [ "$(APICHECK)" = "1" ]; then $(APICHECK_CMD);fi


VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Thread/ctaskmngr.o : D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/files/Thread/ctaskmngr.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)/g++ppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi  -fno-zero-initialized-in-bss -Wall  -std=c++11 -MD -MP $(DKM_LONGCALL) -fexceptions -w -mstrict-align $(IDE_DEFINES) $(DEFINES) $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -std=c++11 -o "$@" -c "$<" && if [ "$(APICHECK)" = "1" ]; then $(APICHECK_CMD);fi


VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Thread/ctrackanalysis.o : D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/files/Thread/ctrackanalysis.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)/g++ppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi  -fno-zero-initialized-in-bss -Wall  -std=c++11 -MD -MP $(DKM_LONGCALL) -fexceptions -w -mstrict-align $(IDE_DEFINES) $(DEFINES) $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -std=c++11 -o "$@" -c "$<" && if [ "$(APICHECK)" = "1" ]; then $(APICHECK_CMD);fi


VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Thread/curbit.o : D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/files/Thread/curbit.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)/g++ppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi  -fno-zero-initialized-in-bss -Wall  -std=c++11 -MD -MP $(DKM_LONGCALL) -fexceptions -w -mstrict-align $(IDE_DEFINES) $(DEFINES) $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -std=c++11 -o "$@" -c "$<" && if [ "$(APICHECK)" = "1" ]; then $(APICHECK_CMD);fi


VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Thread/cusercollect.o : D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/files/Thread/cusercollect.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)/g++ppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi  -fno-zero-initialized-in-bss -Wall  -std=c++11 -MD -MP $(DKM_LONGCALL) -fexceptions -w -mstrict-align $(IDE_DEFINES) $(DEFINES) $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -std=c++11 -o "$@" -c "$<" && if [ "$(APICHECK)" = "1" ]; then $(APICHECK_CMD);fi


VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Utils/DMA/dma.o : D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/files/Utils/DMA/dma.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)/g++ppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi  -fno-zero-initialized-in-bss -Wall  -std=c++11 -MD -MP $(DKM_LONGCALL) -fexceptions -w -mstrict-align $(IDE_DEFINES) $(DEFINES) $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -std=c++11 -o "$@" -c "$<" && if [ "$(APICHECK)" = "1" ]; then $(APICHECK_CMD);fi


VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Utils/MulDiv64.o : D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/files/Utils/MulDiv64.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)/g++ppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi  -fno-zero-initialized-in-bss -Wall  -std=c++11 -MD -MP $(DKM_LONGCALL) -fexceptions -w -mstrict-align $(IDE_DEFINES) $(DEFINES) $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -std=c++11 -o "$@" -c "$<" && if [ "$(APICHECK)" = "1" ]; then $(APICHECK_CMD);fi


VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Utils/PCIDriver.o : D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/files/Utils/PCIDriver.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)/g++ppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi  -fno-zero-initialized-in-bss -Wall  -std=c++11 -MD -MP $(DKM_LONGCALL) -fexceptions -w -mstrict-align $(IDE_DEFINES) $(DEFINES) $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -std=c++11 -o "$@" -c "$<" && if [ "$(APICHECK)" = "1" ]; then $(APICHECK_CMD);fi


VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Utils/carraymsgdata.o : D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/files/Utils/carraymsgdata.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)/g++ppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi  -fno-zero-initialized-in-bss -Wall  -std=c++11 -MD -MP $(DKM_LONGCALL) -fexceptions -w -mstrict-align $(IDE_DEFINES) $(DEFINES) $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -std=c++11 -o "$@" -c "$<" && if [ "$(APICHECK)" = "1" ]; then $(APICHECK_CMD);fi


VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Utils/ccommonutils.o : D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/files/Utils/ccommonutils.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)/g++ppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi  -fno-zero-initialized-in-bss -Wall  -std=c++11 -MD -MP $(DKM_LONGCALL) -fexceptions -w -mstrict-align $(IDE_DEFINES) $(DEFINES) $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -std=c++11 -o "$@" -c "$<" && if [ "$(APICHECK)" = "1" ]; then $(APICHECK_CMD);fi


VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Utils/chwio.o : D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/files/Utils/chwio.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)/g++ppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi  -fno-zero-initialized-in-bss -Wall  -std=c++11 -MD -MP $(DKM_LONGCALL) -fexceptions -w -mstrict-align $(IDE_DEFINES) $(DEFINES) $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -std=c++11 -o "$@" -c "$<" && if [ "$(APICHECK)" = "1" ]; then $(APICHECK_CMD);fi


VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Utils/clog.o : D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/files/Utils/clog.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)/g++ppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi  -fno-zero-initialized-in-bss -Wall  -std=c++11 -MD -MP $(DKM_LONGCALL) -fexceptions -w -mstrict-align $(IDE_DEFINES) $(DEFINES) $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -std=c++11 -o "$@" -c "$<" && if [ "$(APICHECK)" = "1" ]; then $(APICHECK_CMD);fi


VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Utils/cmultiserver.o : D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/files/Utils/cmultiserver.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)/g++ppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi  -fno-zero-initialized-in-bss -Wall  -std=c++11 -MD -MP $(DKM_LONGCALL) -fexceptions -w -mstrict-align $(IDE_DEFINES) $(DEFINES) $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -std=c++11 -o "$@" -c "$<" && if [ "$(APICHECK)" = "1" ]; then $(APICHECK_CMD);fi


VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Utils/csingleclient.o : D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/files/Utils/csingleclient.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)/g++ppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi  -fno-zero-initialized-in-bss -Wall  -std=c++11 -MD -MP $(DKM_LONGCALL) -fexceptions -w -mstrict-align $(IDE_DEFINES) $(DEFINES) $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -std=c++11 -o "$@" -c "$<" && if [ "$(APICHECK)" = "1" ]; then $(APICHECK_CMD);fi


VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Utils/cthread.o : D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/files/Utils/cthread.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)/g++ppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi  -fno-zero-initialized-in-bss -Wall  -std=c++11 -MD -MP $(DKM_LONGCALL) -fexceptions -w -mstrict-align $(IDE_DEFINES) $(DEFINES) $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -std=c++11 -o "$@" -c "$<" && if [ "$(APICHECK)" = "1" ]; then $(APICHECK_CMD);fi


VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Utils/programrev.o : D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/files/Utils/programrev.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)/g++ppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi  -fno-zero-initialized-in-bss -Wall  -std=c++11 -MD -MP $(DKM_LONGCALL) -fexceptions -w -mstrict-align $(IDE_DEFINES) $(DEFINES) $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -std=c++11 -o "$@" -c "$<" && if [ "$(APICHECK)" = "1" ]; then $(APICHECK_CMD);fi


OBJECTS_VSIGA_partialImage = VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/cmain.o \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/dkm.o \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/Collect/DataFile/DataFile.o \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/Collect/GenPDW/CGenPDW.o \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/Collect/ccollectbank/ccollectbank.o \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/EmitterMerge/CEP/AnalyticCEP.o \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/EmitterMerge/Coordinate/Coordinate.o \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/EmitterMerge/DistanceLeastSquare/DistanceLeastSquare.o \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/EmitterMerge/ELEmitterMergeMngr.o \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/EmitterMerge/ELEnvironVariableMngr.o \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/EmitterMerge/ELThreat.o \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/EmitterMerge/GeoCoordConv/GeoCoordConv.o \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/EmitterMerge/InverseMethod/CInverseMethod.o \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/EmitterMerge/LOBClustering.o \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/EmitterMerge/Matrix/Matrix.o \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/EmitterMerge/PositionEstimationAlg.o \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/EmitterMerge/Quadratic/Quadratic.o \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/EmitterMerge/UTM/UTM.o \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/Identify/ELUtil.o \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/Identify/Identify.o \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/Identify/cipl.o \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/IntraSigAnal/IntraSigAnal.o \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/KnownSigAnal/KAnalPRI.o \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/KnownSigAnal/KGroup.o \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/KnownSigAnal/KMakeAET.o \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/KnownSigAnal/KPulExt.o \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/KnownSigAnal/KnownSigAnal.o \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/MIDAS/ELDecoder.o \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/MIDAS/Midas.o \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/MIDAS/PDW2SP370.o \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/MIDAS/RawFile.o \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/NewSigAnal/NAnalPRI.o \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/NewSigAnal/NGroup.o \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/NewSigAnal/NMakeAET.o \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/NewSigAnal/NPulExt.o \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/NewSigAnal/NewSigAnal.o \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/ScanSigAnal/SAnalSCN.o \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/ScanSigAnal/SGroup.o \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/ScanSigAnal/SPulExt.o \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/ScanSigAnal/ScanSigAnal.o \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/SigAnal/AnalPRI.o \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/SigAnal/Group.o \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/SigAnal/MakeAET.o \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/SigAnal/PulExt.o \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/SigAnal/SigAnal.o \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/SigAnal/SysPara.o \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/SigAnal/cencdec.o \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/MinIni/minIni.o \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/SQLite/KompexSQLiteBlob.o \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/SQLite/KompexSQLiteDatabase.o \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/SQLite/KompexSQLiteStatement.o \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/SQLite/sqlite3.o \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/System/csharedmemory.o \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/System/csysconfig.o \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Thread/ccgi.o \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Thread/cdetectanalysis.o \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Thread/cemittermerge.o \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Thread/cjamtech.o \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Thread/coperationconsole.o \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Thread/cprompt.o \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Thread/cpulsetrk.o \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Thread/cscananalysis.o \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Thread/csignalcollect.o \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Thread/ctaskmngr.o \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Thread/ctrackanalysis.o \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Thread/curbit.o \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Thread/cusercollect.o \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Utils/DMA/dma.o \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Utils/MulDiv64.o \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Utils/PCIDriver.o \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Utils/carraymsgdata.o \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Utils/ccommonutils.o \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Utils/chwio.o \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Utils/clog.o \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Utils/cmultiserver.o \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Utils/csingleclient.o \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Utils/cthread.o \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Utils/programrev.o

checkDirVSIGA_partialImage : 
	mkdir -p VSIGA_partialImage/$(MODE_DIR)/
VSIGA_partialImage/$(MODE_DIR)/.VSIGA_partialImageObject.list: $(OBJECTS_VSIGA_partialImage) | checkDirVSIGA_partialImage
	$(file >$@,$^)
ifeq ($(TARGET_JOBS),1)
VSIGA_partialImage/$(MODE_DIR)/VSIGA_partialImage.o : VSIGA_partialImage/$(MODE_DIR)/.VSIGA_partialImageObject.list | check_objdirs
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@";  $(TOOL_PATH)/ccppc -r -nostdlib -Wl,-X  -o "$@" @VSIGA_partialImage/$(MODE_DIR)/.VSIGA_partialImageObject.list $(ADDED_OBJECTS) $(IDE_LIBRARIES) $(LIBPATH) $(LIBS) $(ADDED_LIBPATH) $(ADDED_LIBS) && if [ "$(EXPAND_DBG)" = "1" ]; then plink "$@";fi

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

DEP_FILES := VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/cmain.d VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/dkm.d VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/Collect/DataFile/DataFile.d \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/Collect/GenPDW/CGenPDW.d VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/Collect/ccollectbank/ccollectbank.d VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/EmitterMerge/CEP/AnalyticCEP.d \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/EmitterMerge/Coordinate/Coordinate.d VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/EmitterMerge/DistanceLeastSquare/DistanceLeastSquare.d VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/EmitterMerge/ELEmitterMergeMngr.d \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/EmitterMerge/ELEnvironVariableMngr.d VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/EmitterMerge/ELThreat.d VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/EmitterMerge/GeoCoordConv/GeoCoordConv.d \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/EmitterMerge/InverseMethod/CInverseMethod.d VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/EmitterMerge/LOBClustering.d VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/EmitterMerge/Matrix/Matrix.d \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/EmitterMerge/PositionEstimationAlg.d VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/EmitterMerge/Quadratic/Quadratic.d VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/EmitterMerge/UTM/UTM.d \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/Identify/ELUtil.d VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/Identify/Identify.d VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/Identify/cipl.d \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/IntraSigAnal/IntraSigAnal.d VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/KnownSigAnal/KAnalPRI.d VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/KnownSigAnal/KGroup.d \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/KnownSigAnal/KMakeAET.d VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/KnownSigAnal/KPulExt.d VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/KnownSigAnal/KnownSigAnal.d \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/MIDAS/ELDecoder.d VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/MIDAS/Midas.d VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/MIDAS/PDW2SP370.d \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/MIDAS/RawFile.d VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/NewSigAnal/NAnalPRI.d VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/NewSigAnal/NGroup.d \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/NewSigAnal/NMakeAET.d VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/NewSigAnal/NPulExt.d VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/NewSigAnal/NewSigAnal.d \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/ScanSigAnal/SAnalSCN.d VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/ScanSigAnal/SGroup.d VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/ScanSigAnal/SPulExt.d \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/ScanSigAnal/ScanSigAnal.d VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/SigAnal/AnalPRI.d VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/SigAnal/Group.d \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/SigAnal/MakeAET.d VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/SigAnal/PulExt.d VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/SigAnal/SigAnal.d \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/SigAnal/SysPara.d VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/SigAnal/cencdec.d VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/MinIni/minIni.d \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/SQLite/KompexSQLiteBlob.d VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/SQLite/KompexSQLiteDatabase.d VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/SQLite/KompexSQLiteStatement.d \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/SQLite/sqlite3.d VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/System/csharedmemory.d VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/System/csysconfig.d \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Thread/ccgi.d VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Thread/cdetectanalysis.d VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Thread/cemittermerge.d \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Thread/cjamtech.d VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Thread/coperationconsole.d VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Thread/cprompt.d \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Thread/cpulsetrk.d VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Thread/cscananalysis.d VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Thread/csignalcollect.d \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Thread/ctaskmngr.d VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Thread/ctrackanalysis.d VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Thread/curbit.d \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Thread/cusercollect.d VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Utils/DMA/dma.d VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Utils/MulDiv64.d \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Utils/PCIDriver.d VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Utils/carraymsgdata.d VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Utils/ccommonutils.d \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Utils/chwio.d VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Utils/clog.d VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Utils/cmultiserver.d \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Utils/csingleclient.d VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Utils/cthread.d VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Utils/programrev.d
-include $(DEP_FILES)

OBJ_DIRS := VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/EmitterMerge/DistanceLeastSquare \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/EmitterMerge/InverseMethod \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/EmitterMerge/GeoCoordConv \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/EmitterMerge/Coordinate \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/Collect/ccollectbank \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/EmitterMerge/Quadratic \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/EmitterMerge/CEP \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/EmitterMerge/Matrix \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/Collect/DataFile \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/IntraSigAnal \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/KnownSigAnal \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/ScanSigAnal \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/SQLite \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/Collect/GenPDW \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/NewSigAnal \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/EmitterMerge/UTM \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Thread \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/Identify \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/MIDAS \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Anal/SigAnal \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/System \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Utils \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/MinIni \
	 VSIGA_partialImage/$(MODE_DIR)/Objects/VSIGA/files/Utils/DMA
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
