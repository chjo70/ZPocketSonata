
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






LIBOBJS = $(LIBOBJS_obj)

# DEP_OBJS = (DEP_OBJS)

 
LIBOBJS_krnl_PPCE6500_common_obj_kernel_top_CORE_KERNEL_src_diab_wind_obj =  D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/objobj/classLib.o  D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/objobj/handleLib.o  D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/objobj/objFuncBind.o  D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/objobj/objLib.o  D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/objobj/handleShow.o  D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/objobj/objSymLib.o  D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/objobj/classListLib.o  D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/objobj/objInfo.o  D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/objobj/objOpen.o  D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/objobj/classShow.o  D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/objobj/objShow.o  D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/objobj/objOwnerLib.o  D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/objobj/objRtpLib.o 

arcmdfile_krnl_PPCE6500_common_obj : $(LIBOBJS_krnl_PPCE6500_common_obj_kernel_top_CORE_KERNEL_src_diab_wind_obj)

LIBOBJS_krnl_PPCE6500_common_obj_CORE_KERNEL += $(LIBOBJS_krnl_PPCE6500_common_obj_kernel_top_CORE_KERNEL_src_diab_wind_obj)

LIBOBJS_krnl_PPCE6500_common_obj += $(LIBOBJS_krnl_PPCE6500_common_obj_kernel_top_CORE_KERNEL_src_diab_wind_obj)

__OBJS_TO_CLEAN_CORE_KERNEL += $(LIBOBJS_krnl_PPCE6500_common_obj_kernel_top_CORE_KERNEL_src_diab_wind_obj) $(LIBOBJS_krnl_PPCE6500_common_obj_kernel_top_CORE_KERNEL_src_diab_wind_obj:.o=.d)

ifndef _DONEBASE_LIB_krnl_PPCE6500_common_obj

_DONEBASE_LIB_krnl_PPCE6500_common_obj = TRUE

# LIBBASES += obj

__LIBS_TO_BUILD += krnl_PPCE6500_common_obj

__LIBS_TO_BUILD_CORE_KERNEL += krnl_PPCE6500_common_obj

__BUILT_LIBS += krnl_PPCE6500_common_obj

__LIB_krnl_PPCE6500_common_obj = D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/libobj$(OPT).a


D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/objobj :
	$(MKDIR) $@


lib : D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/libobj$(OPT).a  D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/libobj.cdf

# need to pass the lib.a file twice to D:/vxWorks7/compilers/diab-5.9.6.5/WIN32/bin/ddump -Ng to workaround ddump problem
D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/libobj.nm : D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/libobj$(OPT).a
	$(if $(wildcard $<),cd D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common && $(NM) libobj$(OPT).a libobj$(OPT).a > $@, $(info skipping $@ : non existant $<))

D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/libobj.cdf : D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/libobj.nm 
	$(if $(wildcard $<),$(LIB2CDF) -i $< -a libobj.a -o $@, $(info skipping $@ : non existant $<))

arcmdfiles : arcmdfile_krnl_PPCE6500_common_obj

arcmdfile_krnl_PPCE6500_common_obj :
	$(file >$@,$(call uniq,$(LIBOBJS_krnl_PPCE6500_common_obj)))
	@echo created $@

D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/libobj$(OPT).a : arcmdfile_krnl_PPCE6500_common_obj
	D:/vxWorks7/compilers/diab-5.9.6.5/WIN32/bin/dar crusv $@ @arcmdfile_krnl_PPCE6500_common_obj


clean _layer_clean_CORE_KERNEL : _clean_LIB_BASE_krnl_PPCE6500_common_obj

_clean_LIB_BASE_krnl_PPCE6500_common_obj :
	rm -f D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/libobj$(OPT).a


endif

ifndef _DONEBASE_LIB_CORE_KERNEL_krnl_PPCE6500_common_obj

_DONEBASE_LIB_CORE_KERNEL_krnl_PPCE6500_common_obj = TRUE

lib : D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/layerCORE_KERNEL_libobj.cdf

D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/layerCORE_KERNEL_libobj.cdf :  D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/libobj$(OPT).a
	$(file >$@, $(call __tmpl_layercdf,CORE_KERNEL,libobj.a,$(LIBOBJS_krnl_PPCE6500_common_obj)))

endif


D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/libobj$(OPT).a : $(LIBOBJS_krnl_PPCE6500_common_obj)




 

################
# rules defined locally in Makefile
##



################

objs : $(LIBOBJS)
 
# this is the end of the file 
