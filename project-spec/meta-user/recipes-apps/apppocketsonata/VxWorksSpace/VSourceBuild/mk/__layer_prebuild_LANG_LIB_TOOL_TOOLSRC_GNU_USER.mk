
	
# this file is automatically generated by mk/krnl/defs.layers.mk. Please do not edit

__FILE_COPIED += $(__FILES_COPIED_LANG_LIB_TOOL_TOOLSRC_GNU_USER)




	
	

	


	
	
	
	
	
	
	
	
	
	
# copying directory h to D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/h/public




# copying directory h/tool to D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/h/public/tool




# copying directory h/tool/gnu to D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/h/public/tool/gnu




PRENOBUILD : D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/h/public/tool/gnu/toolMacros.h

__FILES_TO_COPY_LANG_LIB_TOOL_TOOLSRC_GNU_USER += D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/h/public/tool/gnu/toolMacros.h





 

D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/h/public/tool/gnu/toolMacros.h : D:/vxWorks7/vxworks-7/pkgs/os/lang-lib/tool-1.0.0.3/toolsrc_gnu-20.0.2.6/usr/h/tool/gnu/toolMacros.h | D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/h/public/tool/gnu
ifdef __LAYER_DEPENDENCY_TEST
	cp -rfLs $< $@
else
	cp -rfL $< $@
endif
 
PRENOBUILD : D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/h/public/tool/gnu/limits.h

__FILES_TO_COPY_LANG_LIB_TOOL_TOOLSRC_GNU_USER += D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/h/public/tool/gnu/limits.h





D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/h/public/tool/gnu/limits.h : D:/vxWorks7/vxworks-7/pkgs/os/lang-lib/tool-1.0.0.3/toolsrc_gnu-20.0.2.6/usr/h/tool/gnu/limits.h | D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/h/public/tool/gnu
ifdef __LAYER_DEPENDENCY_TEST
	cp -rfLs $< $@
else
	cp -rfL $< $@
endif




	
	
	
	
	
	
	


	
	
	
	
	
	
	

	
BUILD_USR_STATIC : LANG_LIB_TOOL_TOOLSRC_GNU_USER_src_gnu__BUILD_USR_STATIC

.PHONY : LANG_LIB_TOOL_TOOLSRC_GNU_USER_src_gnu__BUILD_USR_STATIC

__BUILD_USR_STATIC_FB_IDS += user_static_top_LANG_LIB_TOOL_TOOLSRC_GNU_USER_src_gnu

LANG_LIB_TOOL_TOOLSRC_GNU_USER_src_gnu__BUILD_USR_STATIC : 
	@ echo building LANG_LIB_TOOL_TOOLSRC_GNU_USER directory src
	+ @ cd D:/vxWorks7/vxworks-7/pkgs/os/lang-lib/tool-1.0.0.3/toolsrc_gnu-20.0.2.6/usr/src && D:/vxWorks7/vxworks-7/host/binutils/x86-win32/bin/make _mk CPU=PPCE6500 TOOL=gnu TOOL_VERSION=gnu_4_8_1_8 _CC_VERSION=gnu_4_8_1_10 SPACE=user LAYER_FORMAT=static _VSB_CONFIG_ADDEDCFLAGS="" _WRS_CONFIG_APP_TOOL=diab VSBL_NAME=LANG_LIB_TOOL_TOOLSRC_GNU_USER VSB_DIR=D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild _WRS_CONFIG_FP=hard _WRS_CLI_CFLAGS="-I. " _FB_ID=user_static_top_LANG_LIB_TOOL_TOOLSRC_GNU_USER_src_gnu BSPNAME=hmt_t2080vpx3u_1_0_0_0 BUILDSTAGE=BUILD_USR_STATIC
 
BUILD_USR_STATIC : LANG_LIB_TOOL_TOOLSRC_GNU_USER_libs_gnu__BUILD_USR_STATIC

.PHONY : LANG_LIB_TOOL_TOOLSRC_GNU_USER_libs_gnu__BUILD_USR_STATIC

__BUILD_USR_STATIC_FB_IDS += user_static_top_LANG_LIB_TOOL_TOOLSRC_GNU_USER_libs_gnu

LANG_LIB_TOOL_TOOLSRC_GNU_USER_libs_gnu__BUILD_USR_STATIC : 
	@ echo building LANG_LIB_TOOL_TOOLSRC_GNU_USER directory libs
	+ @ cd D:/vxWorks7/vxworks-7/pkgs/os/lang-lib/tool-1.0.0.3/toolsrc_gnu-20.0.2.6/usr/libs && D:/vxWorks7/vxworks-7/host/binutils/x86-win32/bin/make _mk CPU=PPCE6500 TOOL=gnu TOOL_VERSION=gnu_4_8_1_8 _CC_VERSION=gnu_4_8_1_10 SPACE=user LAYER_FORMAT=static _VSB_CONFIG_ADDEDCFLAGS="" _WRS_CONFIG_APP_TOOL=diab VSBL_NAME=LANG_LIB_TOOL_TOOLSRC_GNU_USER VSB_DIR=D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild _WRS_CONFIG_FP=hard _WRS_CLI_CFLAGS="-I. " _FB_ID=user_static_top_LANG_LIB_TOOL_TOOLSRC_GNU_USER_libs_gnu BSPNAME=hmt_t2080vpx3u_1_0_0_0 BUILDSTAGE=BUILD_USR_STATIC

	
	
BUILD_USR_SHARED : LANG_LIB_TOOL_TOOLSRC_GNU_USER_src_gnu__BUILD_USR_SHARED

.PHONY : LANG_LIB_TOOL_TOOLSRC_GNU_USER_src_gnu__BUILD_USR_SHARED

__BUILD_USR_SHARED_FB_IDS += user_shared_top_LANG_LIB_TOOL_TOOLSRC_GNU_USER_src_gnu

LANG_LIB_TOOL_TOOLSRC_GNU_USER_src_gnu__BUILD_USR_SHARED : 
	@ echo building LANG_LIB_TOOL_TOOLSRC_GNU_USER directory src
	+ @ cd D:/vxWorks7/vxworks-7/pkgs/os/lang-lib/tool-1.0.0.3/toolsrc_gnu-20.0.2.6/usr/src && D:/vxWorks7/vxworks-7/host/binutils/x86-win32/bin/make _mk CPU=PPCE6500 TOOL=gnu TOOL_VERSION=gnu_4_8_1_8 _CC_VERSION=gnu_4_8_1_10 SPACE=user LAYER_FORMAT=shared _VSB_CONFIG_ADDEDCFLAGS="" _WRS_CONFIG_APP_TOOL=diab VSBL_NAME=LANG_LIB_TOOL_TOOLSRC_GNU_USER VSB_DIR=D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild _WRS_CONFIG_FP=hard _WRS_CLI_CFLAGS="-I. " _FB_ID=user_shared_top_LANG_LIB_TOOL_TOOLSRC_GNU_USER_src_gnu BSPNAME=hmt_t2080vpx3u_1_0_0_0 BUILDSTAGE=BUILD_USR_SHARED
 
BUILD_USR_SHARED : LANG_LIB_TOOL_TOOLSRC_GNU_USER_libs_gnu__BUILD_USR_SHARED

.PHONY : LANG_LIB_TOOL_TOOLSRC_GNU_USER_libs_gnu__BUILD_USR_SHARED

__BUILD_USR_SHARED_FB_IDS += user_shared_top_LANG_LIB_TOOL_TOOLSRC_GNU_USER_libs_gnu

LANG_LIB_TOOL_TOOLSRC_GNU_USER_libs_gnu__BUILD_USR_SHARED : 
	@ echo building LANG_LIB_TOOL_TOOLSRC_GNU_USER directory libs
	+ @ cd D:/vxWorks7/vxworks-7/pkgs/os/lang-lib/tool-1.0.0.3/toolsrc_gnu-20.0.2.6/usr/libs && D:/vxWorks7/vxworks-7/host/binutils/x86-win32/bin/make _mk CPU=PPCE6500 TOOL=gnu TOOL_VERSION=gnu_4_8_1_8 _CC_VERSION=gnu_4_8_1_10 SPACE=user LAYER_FORMAT=shared _VSB_CONFIG_ADDEDCFLAGS="" _WRS_CONFIG_APP_TOOL=diab VSBL_NAME=LANG_LIB_TOOL_TOOLSRC_GNU_USER VSB_DIR=D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild _WRS_CONFIG_FP=hard _WRS_CLI_CFLAGS="-I. " _FB_ID=user_shared_top_LANG_LIB_TOOL_TOOLSRC_GNU_USER_libs_gnu BSPNAME=hmt_t2080vpx3u_1_0_0_0 BUILDSTAGE=BUILD_USR_SHARED


	
	
	

	

	


	
	
	

	

	
__DIR_TARGETS += $(__DIR_TARGETS_LANG_LIB_TOOL_TOOLSRC_GNU_USER)

__DIR_TARGETS_LANG_LIB_TOOL_TOOLSRC_GNU_USER += D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/cdf D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/configlette D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/h D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/share/h D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/h D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/h/public/tool/gnu D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/vsblCdf

