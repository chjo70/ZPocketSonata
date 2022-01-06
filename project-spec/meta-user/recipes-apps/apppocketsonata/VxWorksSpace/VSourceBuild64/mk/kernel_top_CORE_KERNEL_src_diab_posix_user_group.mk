
#
# This file is automatically generated by mk/krnl/defs.fastlibgen.mk .
#
# build configuration :
#	VSB : D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64
#	CPU : PPCE6500
#	TOOL : diab
#	FP : hard
# 	ENDIAN : big
#	LIB_DIR_TAG = 
#	LIBDIRBASE = krnl/PPCE6500/common
#	LIBDIRBASE = krnl/$(CPU)$(CPU_OPTION_SUFFIX)/$(TOOL_COMMON_DIR)$(LIB_DIR_TAG)$(MINOR_OPTION_SUFFIX)






LIBOBJS = $(LIBOBJS_pxUserGroup)

# DEP_OBJS = (DEP_OBJS)

 
LIBOBJS_krnl_PPCE6500_common_pxUserGroup_kernel_top_CORE_KERNEL_src_diab_posix_user_group =  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/objpxUserGroup/pxUserGroupLib.o  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/objpxUserGroup/getlogin.o  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/objpxUserGroup/pxUserGroupScLib.o 

arcmdfile_krnl_PPCE6500_common_pxUserGroup : $(LIBOBJS_krnl_PPCE6500_common_pxUserGroup_kernel_top_CORE_KERNEL_src_diab_posix_user_group)

LIBOBJS_krnl_PPCE6500_common_pxUserGroup_CORE_KERNEL += $(LIBOBJS_krnl_PPCE6500_common_pxUserGroup_kernel_top_CORE_KERNEL_src_diab_posix_user_group)

LIBOBJS_krnl_PPCE6500_common_pxUserGroup += $(LIBOBJS_krnl_PPCE6500_common_pxUserGroup_kernel_top_CORE_KERNEL_src_diab_posix_user_group)

__OBJS_TO_CLEAN_CORE_KERNEL += $(LIBOBJS_krnl_PPCE6500_common_pxUserGroup_kernel_top_CORE_KERNEL_src_diab_posix_user_group) $(LIBOBJS_krnl_PPCE6500_common_pxUserGroup_kernel_top_CORE_KERNEL_src_diab_posix_user_group:.o=.d)

ifndef _DONEBASE_LIB_krnl_PPCE6500_common_pxUserGroup

_DONEBASE_LIB_krnl_PPCE6500_common_pxUserGroup = TRUE

# LIBBASES += pxUserGroup

__LIBS_TO_BUILD += krnl_PPCE6500_common_pxUserGroup

__LIBS_TO_BUILD_CORE_KERNEL += krnl_PPCE6500_common_pxUserGroup

__BUILT_LIBS += krnl_PPCE6500_common_pxUserGroup

__LIB_krnl_PPCE6500_common_pxUserGroup = D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libpxUserGroup$(OPT).a


D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/objpxUserGroup :
	$(MKDIR) $@


lib : D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libpxUserGroup$(OPT).a  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libpxUserGroup.cdf

# need to pass the lib.a file twice to D:/vxWorks7/compilers/diab-5.9.6.5/WIN32/bin/ddump -Ng to workaround ddump problem
D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libpxUserGroup.nm : D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libpxUserGroup$(OPT).a
	$(if $(wildcard $<),cd D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common && $(NM) libpxUserGroup$(OPT).a libpxUserGroup$(OPT).a > $@, $(info skipping $@ : non existant $<))

D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libpxUserGroup.cdf : D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libpxUserGroup.nm 
	$(if $(wildcard $<),$(LIB2CDF) -i $< -a libpxUserGroup.a -o $@, $(info skipping $@ : non existant $<))

arcmdfiles : arcmdfile_krnl_PPCE6500_common_pxUserGroup

arcmdfile_krnl_PPCE6500_common_pxUserGroup :
	$(file >$@,$(call uniq,$(LIBOBJS_krnl_PPCE6500_common_pxUserGroup)))
	@echo created $@

D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libpxUserGroup$(OPT).a : arcmdfile_krnl_PPCE6500_common_pxUserGroup
	D:/vxWorks7/compilers/diab-5.9.6.5/WIN32/bin/dar crusv $@ @arcmdfile_krnl_PPCE6500_common_pxUserGroup


clean _layer_clean_CORE_KERNEL : _clean_LIB_BASE_krnl_PPCE6500_common_pxUserGroup

_clean_LIB_BASE_krnl_PPCE6500_common_pxUserGroup :
	rm -f D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libpxUserGroup$(OPT).a


endif

ifndef _DONEBASE_LIB_CORE_KERNEL_krnl_PPCE6500_common_pxUserGroup

_DONEBASE_LIB_CORE_KERNEL_krnl_PPCE6500_common_pxUserGroup = TRUE

lib : D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/layerCORE_KERNEL_libpxUserGroup.cdf

D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/layerCORE_KERNEL_libpxUserGroup.cdf :  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libpxUserGroup$(OPT).a
	$(file >$@, $(call __tmpl_layercdf,CORE_KERNEL,libpxUserGroup.a,$(LIBOBJS_krnl_PPCE6500_common_pxUserGroup)))

endif


D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libpxUserGroup$(OPT).a : $(LIBOBJS_krnl_PPCE6500_common_pxUserGroup)




 

################
# rules defined locally in Makefile
##



################

objs : $(LIBOBJS)
 
# this is the end of the file 
