
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






LIBOBJS = $(LIBOBJS_VXCOREIP)

# DEP_OBJS = (DEP_OBJS)

 
LIBOBJS_krnl_PPCE6500_common_VXCOREIP_kernel_top_IPNET_COREIP_src_utils_src_legacy_apps_remlib_diab =  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/objVXCOREIP/remLib.o  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/objVXCOREIP/remLib.o 

arcmdfile_krnl_PPCE6500_common_VXCOREIP : $(LIBOBJS_krnl_PPCE6500_common_VXCOREIP_kernel_top_IPNET_COREIP_src_utils_src_legacy_apps_remlib_diab)

LIBOBJS_krnl_PPCE6500_common_VXCOREIP_IPNET_COREIP += $(LIBOBJS_krnl_PPCE6500_common_VXCOREIP_kernel_top_IPNET_COREIP_src_utils_src_legacy_apps_remlib_diab)

LIBOBJS_krnl_PPCE6500_common_VXCOREIP += $(LIBOBJS_krnl_PPCE6500_common_VXCOREIP_kernel_top_IPNET_COREIP_src_utils_src_legacy_apps_remlib_diab)

__OBJS_TO_CLEAN_IPNET_COREIP += $(LIBOBJS_krnl_PPCE6500_common_VXCOREIP_kernel_top_IPNET_COREIP_src_utils_src_legacy_apps_remlib_diab) $(LIBOBJS_krnl_PPCE6500_common_VXCOREIP_kernel_top_IPNET_COREIP_src_utils_src_legacy_apps_remlib_diab:.o=.d)

ifndef _DONEBASE_LIB_krnl_PPCE6500_common_VXCOREIP

_DONEBASE_LIB_krnl_PPCE6500_common_VXCOREIP = TRUE

# LIBBASES += VXCOREIP

__LIBS_TO_BUILD += krnl_PPCE6500_common_VXCOREIP

__LIBS_TO_BUILD_IPNET_COREIP += krnl_PPCE6500_common_VXCOREIP

__BUILT_LIBS += krnl_PPCE6500_common_VXCOREIP

__LIB_krnl_PPCE6500_common_VXCOREIP = D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libVXCOREIP$(OPT).a


D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/objVXCOREIP :
	$(MKDIR) $@


lib : D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libVXCOREIP$(OPT).a  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libVXCOREIP.cdf

# need to pass the lib.a file twice to D:/vxWorks7/compilers/diab-5.9.6.5/WIN32/bin/ddump -Ng to workaround ddump problem
D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libVXCOREIP.nm : D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libVXCOREIP$(OPT).a
	$(if $(wildcard $<),cd D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common && $(NM) libVXCOREIP$(OPT).a libVXCOREIP$(OPT).a > $@, $(info skipping $@ : non existant $<))

D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libVXCOREIP.cdf : D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libVXCOREIP.nm 
	$(if $(wildcard $<),$(LIB2CDF) -i $< -a libVXCOREIP.a -o $@, $(info skipping $@ : non existant $<))

arcmdfiles : arcmdfile_krnl_PPCE6500_common_VXCOREIP

arcmdfile_krnl_PPCE6500_common_VXCOREIP :
	$(file >$@,$(call uniq,$(LIBOBJS_krnl_PPCE6500_common_VXCOREIP)))
	@echo created $@

D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libVXCOREIP$(OPT).a : arcmdfile_krnl_PPCE6500_common_VXCOREIP
	D:/vxWorks7/compilers/diab-5.9.6.5/WIN32/bin/dar crusv $@ @arcmdfile_krnl_PPCE6500_common_VXCOREIP


clean _layer_clean_IPNET_COREIP : _clean_LIB_BASE_krnl_PPCE6500_common_VXCOREIP

_clean_LIB_BASE_krnl_PPCE6500_common_VXCOREIP :
	rm -f D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libVXCOREIP$(OPT).a


endif

ifndef _DONEBASE_LIB_IPNET_COREIP_krnl_PPCE6500_common_VXCOREIP

_DONEBASE_LIB_IPNET_COREIP_krnl_PPCE6500_common_VXCOREIP = TRUE

lib : D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/layerIPNET_COREIP_libVXCOREIP.cdf

D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/layerIPNET_COREIP_libVXCOREIP.cdf :  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libVXCOREIP$(OPT).a
	$(file >$@, $(call __tmpl_layercdf,IPNET_COREIP,libVXCOREIP.a,$(LIBOBJS_krnl_PPCE6500_common_VXCOREIP)))

endif


D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libVXCOREIP$(OPT).a : $(LIBOBJS_krnl_PPCE6500_common_VXCOREIP)




 

################
# rules defined locally in Makefile
##



################

objs : $(LIBOBJS)
 
# this is the end of the file 
