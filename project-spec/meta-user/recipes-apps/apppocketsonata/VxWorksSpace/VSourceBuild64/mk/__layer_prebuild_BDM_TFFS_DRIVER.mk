
	
# this file is automatically generated by mk/krnl/defs.layers.mk. Please do not edit

__FILE_COPIED += $(__FILES_COPIED_BDM_TFFS_DRIVER)




	
	

	
# copying directory h to D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/h/public




# copying directory h/tffs to D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/h/public/tffs




PRENOBUILD : D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/h/public/tffs/tffsConfig.c

__FILES_TO_COPY_BDM_TFFS_DRIVER += D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/h/public/tffs/tffsConfig.c





 

D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/h/public/tffs/tffsConfig.c : D:/vxWorks7/vxworks-7/pkgs/storage/bdm-1.0.1.3/flash/tffs_drv-1.0.1.3/h/tffs/tffsConfig.c | D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/h/public/tffs
ifdef __LAYER_DEPENDENCY_TEST
	cp -rfLs $< $@
else
	cp -rfL $< $@
endif





	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	


	
	
	
	
	
	
	
BUILD : BDM_TFFS_DRIVER_src_diab__BUILD

.PHONY : BDM_TFFS_DRIVER_src_diab__BUILD

__BUILD_FB_IDS += kernel_top_BDM_TFFS_DRIVER_src_diab

BDM_TFFS_DRIVER_src_diab__BUILD : 
	@ echo building BDM_TFFS_DRIVER directory src
	+ @ cd D:/vxWorks7/vxworks-7/pkgs/storage/bdm-1.0.1.3/flash/tffs_drv-1.0.1.3/src && D:/vxWorks7/vxworks-7/host/binutils/x86-win32/bin/make _mk CPU=PPCE6500 TOOL=diab TOOL_VERSION=diab_5_9_6_1 _CC_VERSION=diab_5_9_6_5 SPACE=kernel _VSB_CONFIG_ADDEDCFLAGS="" _WRS_CONFIG_APP_TOOL=diab VSBL_NAME=BDM_TFFS_DRIVER VSB_DIR=D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64 _WRS_CONFIG_FP=hard _WRS_CLI_CFLAGS="-I. " _FB_ID=kernel_top_BDM_TFFS_DRIVER_src_diab BSPNAME=hmt_t2080vpx3u_1_0_0_0 BUILDSTAGE=BUILD


	
	
	

	
	
	

	

	


	
	
	

	

	
__DIR_TARGETS += $(__DIR_TARGETS_BDM_TFFS_DRIVER)

__DIR_TARGETS_BDM_TFFS_DRIVER += D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/cdf D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/configlette D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/h D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/h/public/tffs D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/share/h D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/usr/h D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/vsblCdf
