
	
# this file is automatically generated by mk/krnl/defs.layers.mk. Please do not edit

__FILE_COPIED += $(__FILES_COPIED_LANG_LIB_TOOL_TOOLSRC_COMMON_KERNEL)




	
	

	
# copying directory h to D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/h/public




# copying directory h/tool to D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/h/public/tool




# copying directory h/tool/common to D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/h/public/tool/common




# copying directory h/tool/common/private to D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/h/public/tool/common/private




PRENOBUILD : D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/h/public/tool/common/private/toolMacrosP.h

__FILES_TO_COPY_LANG_LIB_TOOL_TOOLSRC_COMMON_KERNEL += D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/h/public/tool/common/private/toolMacrosP.h





 

D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/h/public/tool/common/private/toolMacrosP.h : D:/vxWorks7/vxworks-7/pkgs/os/lang-lib/tool-1.0.0.3/common-1.0.3.5/kernel/h/tool/common/private/toolMacrosP.h | D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/h/public/tool/common/private
ifdef __LAYER_DEPENDENCY_TEST
	cp -rfLs $< $@
else
	cp -rfL $< $@
endif







	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	


	
	
	
	
	
	
	
BUILD : LANG_LIB_TOOL_TOOLSRC_COMMON_KERNEL_src_diab__BUILD

.PHONY : LANG_LIB_TOOL_TOOLSRC_COMMON_KERNEL_src_diab__BUILD

__BUILD_FB_IDS += kernel_top_LANG_LIB_TOOL_TOOLSRC_COMMON_KERNEL_src_diab

LANG_LIB_TOOL_TOOLSRC_COMMON_KERNEL_src_diab__BUILD : 
	@ echo building LANG_LIB_TOOL_TOOLSRC_COMMON_KERNEL directory src
	+ @ cd D:/vxWorks7/vxworks-7/pkgs/os/lang-lib/tool-1.0.0.3/common-1.0.3.5/kernel/src && D:/vxWorks7/vxworks-7/host/binutils/x86-win32/bin/make _mk CPU=PPCE6500 TOOL=diab TOOL_VERSION=diab_5_9_6_1 _CC_VERSION=diab_5_9_6_5 SPACE=kernel _VSB_CONFIG_ADDEDCFLAGS="" _WRS_CONFIG_APP_TOOL=diab VSBL_NAME=LANG_LIB_TOOL_TOOLSRC_COMMON_KERNEL VSB_DIR=D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild _WRS_CONFIG_FP=hard _WRS_CLI_CFLAGS="-I. " _FB_ID=kernel_top_LANG_LIB_TOOL_TOOLSRC_COMMON_KERNEL_src_diab BSPNAME=hmt_t2080vpx3u_1_0_0_0 BUILDSTAGE=BUILD


	
	
	

	
	
	

	

	


	
# copying directory cdf to D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/cdf




PRENOBUILD : D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/cdf/00tool.cdf

__FILES_TO_COPY_LANG_LIB_TOOL_TOOLSRC_COMMON_KERNEL += D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/cdf/00tool.cdf





 

D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/cdf/00tool.cdf : D:/vxWorks7/vxworks-7/pkgs/os/lang-lib/tool-1.0.0.3/common-1.0.3.5/kernel/cdf/00tool.cdf | D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/cdf
ifdef __LAYER_DEPENDENCY_TEST
	cp -rfLs $< $@
else
	cp -rfL $< $@
endif


	
cdf_PRENOBUILD_LANG_LIB_TOOL_TOOLSRC_COMMON_KERNEL_FILES = cdf/00tool.cdf

cdf_PRENOBUILD_LANG_LIB_TOOL_TOOLSRC_COMMON_KERNEL_DIR = D:/vxWorks7/vxworks-7/pkgs/os/lang-lib/tool-1.0.0.3/common-1.0.3.5/kernel

PRENOBUILD_FILES += $(addprefix $(cdf_PRENOBUILD_LANG_LIB_TOOL_TOOLSRC_COMMON_KERNEL_DIR)/,$(cdf_PRENOBUILD_LANG_LIB_TOOL_TOOLSRC_COMMON_KERNEL_FILES))

PRENOBUILD : PRENOBUILD_LANG_LIB_TOOL_TOOLSRC_COMMON_KERNEL

PRENOBUILD_LANG_LIB_TOOL_TOOLSRC_COMMON_KERNEL : cdf_PRENOBUILD_LANG_LIB_TOOL_TOOLSRC_COMMON_KERNEL

cdf_PRENOBUILD_LANG_LIB_TOOL_TOOLSRC_COMMON_KERNEL : D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/cdf/cdf_PRENOBUILD_LANG_LIB_TOOL_TOOLSRC_COMMON_KERNEL.cdf

D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/cdf/cdf_PRENOBUILD_LANG_LIB_TOOL_TOOLSRC_COMMON_KERNEL.cdf : | D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/cdf
	$(file >D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/cdf/cdf_PRENOBUILD_LANG_LIB_TOOL_TOOLSRC_COMMON_KERNEL.tmp,$(call __vsb_tmpl_cdf_inter,$(addprefix $(cdf_PRENOBUILD_LANG_LIB_TOOL_TOOLSRC_COMMON_KERNEL_DIR)/,$(sort $(cdf_PRENOBUILD_LANG_LIB_TOOL_TOOLSRC_COMMON_KERNEL_FILES))),LANG_LIB_TOOL_TOOLSRC_COMMON_KERNEL))
	$(CDFCOMP) -i D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/cdf/cdf_PRENOBUILD_LANG_LIB_TOOL_TOOLSRC_COMMON_KERNEL.tmp -o $@ -cpp "$(CPP) $(__OPTION_LANG_CDF)" -cpu PPCE6500 -layer LANG_LIB_TOOL_TOOLSRC_COMMON_KERNEL -vsb D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild
	rm -f D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/cdf/cdf_PRENOBUILD_LANG_LIB_TOOL_TOOLSRC_COMMON_KERNEL.tmp

	

	
# copying directory configlette to D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/configlette




PRENOBUILD : D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/configlette/intrinsics.c

__FILES_TO_COPY_LANG_LIB_TOOL_TOOLSRC_COMMON_KERNEL += D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/configlette/intrinsics.c





 

D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/configlette/intrinsics.c : D:/vxWorks7/vxworks-7/pkgs/os/lang-lib/tool-1.0.0.3/common-1.0.3.5/kernel/configlette/intrinsics.c | D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/configlette
ifdef __LAYER_DEPENDENCY_TEST
	cp -rfLs $< $@
else
	cp -rfL $< $@
endif



	
__DIR_TARGETS += $(__DIR_TARGETS_LANG_LIB_TOOL_TOOLSRC_COMMON_KERNEL)

__DIR_TARGETS_LANG_LIB_TOOL_TOOLSRC_COMMON_KERNEL += D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/cdf D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/configlette D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/h D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/h/public/tool/common/private D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/share/h D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/h D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/vsblCdf

