
#
# This file is automatically generated by mk/krnl/defs.fastlibgen.mk .
#
# build configuration :
#	VSB : D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild
#	CPU : PPCE6500
#	TOOL : diab
#	FP : hard
# 	ENDIAN : big
#	LIB_DIR_TAG = 
#	LIBDIRBASE = krnl/PPCE6500/common
#	LIBDIRBASE = krnl/$(CPU)$(CPU_OPTION_SUFFIX)/$(TOOL_COMMON_DIR)$(LIB_DIR_TAG)$(MINOR_OPTION_SUFFIX)






LIBOBJS = $(LIBOBJS_fsapiUtil)

# DEP_OBJS = (DEP_OBJS)

 
LIBOBJS_krnl_PPCE6500_common_fsapiUtil_kernel_top_FSAPI_UTIL_src_diab =  D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/objfsapiUtil/usrDosFsOld.o  D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/objfsapiUtil/tarLib.o  D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/objfsapiUtil/usrFsLib.o  D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/objfsapiUtil/usrDosFsOld.o  D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/objfsapiUtil/tarLib.o  D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/objfsapiUtil/usrFsLib.o 

arcmdfile_krnl_PPCE6500_common_fsapiUtil : $(LIBOBJS_krnl_PPCE6500_common_fsapiUtil_kernel_top_FSAPI_UTIL_src_diab)

LIBOBJS_krnl_PPCE6500_common_fsapiUtil_FSAPI_UTIL += $(LIBOBJS_krnl_PPCE6500_common_fsapiUtil_kernel_top_FSAPI_UTIL_src_diab)

LIBOBJS_krnl_PPCE6500_common_fsapiUtil += $(LIBOBJS_krnl_PPCE6500_common_fsapiUtil_kernel_top_FSAPI_UTIL_src_diab)

__OBJS_TO_CLEAN_FSAPI_UTIL += $(LIBOBJS_krnl_PPCE6500_common_fsapiUtil_kernel_top_FSAPI_UTIL_src_diab) $(LIBOBJS_krnl_PPCE6500_common_fsapiUtil_kernel_top_FSAPI_UTIL_src_diab:.o=.d)

ifndef _DONEBASE_LIB_krnl_PPCE6500_common_fsapiUtil

_DONEBASE_LIB_krnl_PPCE6500_common_fsapiUtil = TRUE

# LIBBASES += fsapiUtil

__LIBS_TO_BUILD += krnl_PPCE6500_common_fsapiUtil

__LIBS_TO_BUILD_FSAPI_UTIL += krnl_PPCE6500_common_fsapiUtil

__BUILT_LIBS += krnl_PPCE6500_common_fsapiUtil

__LIB_krnl_PPCE6500_common_fsapiUtil = D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/libfsapiUtil$(OPT).a


D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/objfsapiUtil :
	$(MKDIR) $@


lib : D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/libfsapiUtil$(OPT).a  D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/libfsapiUtil.cdf

# need to pass the lib.a file twice to D:/vxWorks7/compilers/diab-5.9.6.5/WIN32/bin/ddump -Ng to workaround ddump problem
D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/libfsapiUtil.nm : D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/libfsapiUtil$(OPT).a
	$(if $(wildcard $<),cd D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common && $(NM) libfsapiUtil$(OPT).a libfsapiUtil$(OPT).a > $@, $(info skipping $@ : non existant $<))

D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/libfsapiUtil.cdf : D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/libfsapiUtil.nm 
	$(if $(wildcard $<),$(LIB2CDF) -i $< -a libfsapiUtil.a -o $@, $(info skipping $@ : non existant $<))

arcmdfiles : arcmdfile_krnl_PPCE6500_common_fsapiUtil

arcmdfile_krnl_PPCE6500_common_fsapiUtil :
	$(file >$@,$(call uniq,$(LIBOBJS_krnl_PPCE6500_common_fsapiUtil)))
	@echo created $@

D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/libfsapiUtil$(OPT).a : arcmdfile_krnl_PPCE6500_common_fsapiUtil
	D:/vxWorks7/compilers/diab-5.9.6.5/WIN32/bin/dar crusv $@ @arcmdfile_krnl_PPCE6500_common_fsapiUtil


clean _layer_clean_FSAPI_UTIL : _clean_LIB_BASE_krnl_PPCE6500_common_fsapiUtil

_clean_LIB_BASE_krnl_PPCE6500_common_fsapiUtil :
	rm -f D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/libfsapiUtil$(OPT).a


endif

ifndef _DONEBASE_LIB_FSAPI_UTIL_krnl_PPCE6500_common_fsapiUtil

_DONEBASE_LIB_FSAPI_UTIL_krnl_PPCE6500_common_fsapiUtil = TRUE

lib : D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/layerFSAPI_UTIL_libfsapiUtil.cdf

D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/layerFSAPI_UTIL_libfsapiUtil.cdf :  D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/libfsapiUtil$(OPT).a
	$(file >$@, $(call __tmpl_layercdf,FSAPI_UTIL,libfsapiUtil.a,$(LIBOBJS_krnl_PPCE6500_common_fsapiUtil)))

endif


D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/libfsapiUtil$(OPT).a : $(LIBOBJS_krnl_PPCE6500_common_fsapiUtil)




 

################
# rules defined locally in Makefile
##



################

objs : $(LIBOBJS)
 
# this is the end of the file 
