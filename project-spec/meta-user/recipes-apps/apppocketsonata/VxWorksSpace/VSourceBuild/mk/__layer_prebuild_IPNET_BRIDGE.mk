
	
# this file is automatically generated by mk/krnl/defs.layers.mk. Please do not edit

__FILE_COPIED += $(__FILES_COPIED_IPNET_BRIDGE)




	
	

	
# copying directory h to D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/h/public




PRENOBUILD : D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/h/public/mirrorEnd.h

__FILES_TO_COPY_IPNET_BRIDGE += D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/h/public/mirrorEnd.h





 

D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/h/public/mirrorEnd.h : D:/vxWorks7/vxworks-7/pkgs/net/ipnet-1.1.1.2/linkproto/bridge-1.0.1.3/h/mirrorEnd.h | D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/h/public
ifdef __LAYER_DEPENDENCY_TEST
	cp -rfLs $< $@
else
	cp -rfL $< $@
endif
 
PRENOBUILD : D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/h/public/bridge.h

__FILES_TO_COPY_IPNET_BRIDGE += D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/h/public/bridge.h





D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/h/public/bridge.h : D:/vxWorks7/vxworks-7/pkgs/net/ipnet-1.1.1.2/linkproto/bridge-1.0.1.3/h/bridge.h | D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/h/public
ifdef __LAYER_DEPENDENCY_TEST
	cp -rfLs $< $@
else
	cp -rfL $< $@
endif




	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	


	
	
	
	
	
	
	
BUILD : IPNET_BRIDGE_src_diab__BUILD

.PHONY : IPNET_BRIDGE_src_diab__BUILD

__BUILD_FB_IDS += kernel_top_IPNET_BRIDGE_src_diab

IPNET_BRIDGE_src_diab__BUILD : 
	@ echo building IPNET_BRIDGE directory src
	+ @ cd D:/vxWorks7/vxworks-7/pkgs/net/ipnet-1.1.1.2/linkproto/bridge-1.0.1.3/src && D:/vxWorks7/vxworks-7/host/binutils/x86-win32/bin/make _mk CPU=PPCE6500 TOOL=diab TOOL_VERSION=diab_5_9_6_1 _CC_VERSION=diab_5_9_6_5 SPACE=kernel _VSB_CONFIG_ADDEDCFLAGS="" _WRS_CONFIG_APP_TOOL=diab VSBL_NAME=IPNET_BRIDGE VSB_DIR=D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild _WRS_CONFIG_FP=hard _WRS_CLI_CFLAGS="-I. " _FB_ID=kernel_top_IPNET_BRIDGE_src_diab BSPNAME=hmt_t2080vpx3u_1_0_0_0 BUILDSTAGE=BUILD


	
	
	

	
	
	

	

	


	
# copying directory cdf to D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/cdf




PRENOBUILD : D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/cdf/10bridge.cdf

__FILES_TO_COPY_IPNET_BRIDGE += D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/cdf/10bridge.cdf





 

D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/cdf/10bridge.cdf : D:/vxWorks7/vxworks-7/pkgs/net/ipnet-1.1.1.2/linkproto/bridge-1.0.1.3/cdf/10bridge.cdf | D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/cdf
ifdef __LAYER_DEPENDENCY_TEST
	cp -rfLs $< $@
else
	cp -rfL $< $@
endif


	
cdf_PRENOBUILD_IPNET_BRIDGE_FILES = cdf/10bridge.cdf

cdf_PRENOBUILD_IPNET_BRIDGE_DIR = D:/vxWorks7/vxworks-7/pkgs/net/ipnet-1.1.1.2/linkproto/bridge-1.0.1.3

PRENOBUILD_FILES += $(addprefix $(cdf_PRENOBUILD_IPNET_BRIDGE_DIR)/,$(cdf_PRENOBUILD_IPNET_BRIDGE_FILES))

PRENOBUILD : PRENOBUILD_IPNET_BRIDGE

PRENOBUILD_IPNET_BRIDGE : cdf_PRENOBUILD_IPNET_BRIDGE

cdf_PRENOBUILD_IPNET_BRIDGE : D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/cdf/cdf_PRENOBUILD_IPNET_BRIDGE.cdf

D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/cdf/cdf_PRENOBUILD_IPNET_BRIDGE.cdf : | D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/cdf
	$(file >D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/cdf/cdf_PRENOBUILD_IPNET_BRIDGE.tmp,$(call __vsb_tmpl_cdf_inter,$(addprefix $(cdf_PRENOBUILD_IPNET_BRIDGE_DIR)/,$(sort $(cdf_PRENOBUILD_IPNET_BRIDGE_FILES))),IPNET_BRIDGE))
	$(CDFCOMP) -i D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/cdf/cdf_PRENOBUILD_IPNET_BRIDGE.tmp -o $@ -cpp "$(CPP) $(__OPTION_LANG_CDF)" -cpu PPCE6500 -layer IPNET_BRIDGE -vsb D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild
	rm -f D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/cdf/cdf_PRENOBUILD_IPNET_BRIDGE.tmp

	

	
# copying directory cfg to D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/configlette




PRENOBUILD : D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/configlette/usrNetBridgeCfg.c

__FILES_TO_COPY_IPNET_BRIDGE += D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/configlette/usrNetBridgeCfg.c





 

D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/configlette/usrNetBridgeCfg.c : D:/vxWorks7/vxworks-7/pkgs/net/ipnet-1.1.1.2/linkproto/bridge-1.0.1.3/cfg/usrNetBridgeCfg.c | D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/configlette
ifdef __LAYER_DEPENDENCY_TEST
	cp -rfLs $< $@
else
	cp -rfL $< $@
endif



	
__DIR_TARGETS += $(__DIR_TARGETS_IPNET_BRIDGE)

__DIR_TARGETS_IPNET_BRIDGE += D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/cdf D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/configlette D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/h D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/h/public D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/share/h D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/h D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/vsblCdf

