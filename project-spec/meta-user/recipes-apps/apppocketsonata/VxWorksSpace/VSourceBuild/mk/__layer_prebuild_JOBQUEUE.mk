
	
# this file is automatically generated by mk/krnl/defs.layers.mk. Please do not edit

__FILE_COPIED += $(__FILES_COPIED_JOBQUEUE)




	
	

	
# copying directory h to D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/h/public




PRENOBUILD : D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/h/public/jobQueueLib.h

__FILES_TO_COPY_JOBQUEUE += D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/h/public/jobQueueLib.h





 

D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/h/public/jobQueueLib.h : D:/vxWorks7/vxworks-7/pkgs/os/service/jobqueue-1.0.3.0/h/jobQueueLib.h | D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/h/public
ifdef __LAYER_DEPENDENCY_TEST
	cp -rfLs $< $@
else
	cp -rfL $< $@
endif
 
# copying directory h/private to D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/h/public/private




PRENOBUILD : D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/h/public/private/jobQueueLibP.h

__FILES_TO_COPY_JOBQUEUE += D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/h/public/private/jobQueueLibP.h





 

D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/h/public/private/jobQueueLibP.h : D:/vxWorks7/vxworks-7/pkgs/os/service/jobqueue-1.0.3.0/h/private/jobQueueLibP.h | D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/h/public/private
ifdef __LAYER_DEPENDENCY_TEST
	cp -rfLs $< $@
else
	cp -rfL $< $@
endif





	
	
	
	
	
	
	
	
	
	
# copying directory h to D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/h/public




PRENOBUILD : D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/h/public/jobQueueLib.h

__FILES_TO_COPY_JOBQUEUE += D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/h/public/jobQueueLib.h





 

D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/h/public/jobQueueLib.h : D:/vxWorks7/vxworks-7/pkgs/os/service/jobqueue-1.0.3.0/h/jobQueueLib.h | D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/h/public
ifdef __LAYER_DEPENDENCY_TEST
	cp -rfLs $< $@
else
	cp -rfL $< $@
endif
 
# copying directory h/private to D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/h/public/private




PRENOBUILD : D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/h/public/private/jobQueueLibP.h

__FILES_TO_COPY_JOBQUEUE += D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/h/public/private/jobQueueLibP.h





 

D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/h/public/private/jobQueueLibP.h : D:/vxWorks7/vxworks-7/pkgs/os/service/jobqueue-1.0.3.0/h/private/jobQueueLibP.h | D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/h/public/private
ifdef __LAYER_DEPENDENCY_TEST
	cp -rfLs $< $@
else
	cp -rfL $< $@
endif



	
	
	
	
	
	
	


	
	
	
	
	
	
	
BUILD : JOBQUEUE_src_diab__BUILD

.PHONY : JOBQUEUE_src_diab__BUILD

__BUILD_FB_IDS += kernel_top_JOBQUEUE_src_diab

JOBQUEUE_src_diab__BUILD : 
	@ echo building JOBQUEUE directory src
	+ @ cd D:/vxWorks7/vxworks-7/pkgs/os/service/jobqueue-1.0.3.0/src && D:/vxWorks7/vxworks-7/host/binutils/x86-win32/bin/make _mk CPU=PPCE6500 TOOL=diab TOOL_VERSION=diab_5_9_6_1 _CC_VERSION=diab_5_9_6_5 SPACE=kernel _VSB_CONFIG_ADDEDCFLAGS="" _WRS_CONFIG_APP_TOOL=diab VSBL_NAME=JOBQUEUE VSB_DIR=D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild _WRS_CONFIG_FP=hard _WRS_CLI_CFLAGS="-I. " _FB_ID=kernel_top_JOBQUEUE_src_diab BSPNAME=hmt_t2080vpx3u_1_0_0_0 BUILDSTAGE=BUILD


	
BUILD_USR_STATIC : JOBQUEUE_src_diab__BUILD_USR_STATIC

.PHONY : JOBQUEUE_src_diab__BUILD_USR_STATIC

__BUILD_USR_STATIC_FB_IDS += user_static_top_JOBQUEUE_src_diab

JOBQUEUE_src_diab__BUILD_USR_STATIC : 
	@ echo building JOBQUEUE directory src
	+ @ cd D:/vxWorks7/vxworks-7/pkgs/os/service/jobqueue-1.0.3.0/src && D:/vxWorks7/vxworks-7/host/binutils/x86-win32/bin/make _mk CPU=PPCE6500 TOOL=diab TOOL_VERSION=diab_5_9_6_1 _CC_VERSION=diab_5_9_6_5 SPACE=user LAYER_FORMAT=static _VSB_CONFIG_ADDEDCFLAGS="" _WRS_CONFIG_APP_TOOL=diab VSBL_NAME=JOBQUEUE VSB_DIR=D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild _WRS_CONFIG_FP=hard _WRS_CLI_CFLAGS="-I. " _FB_ID=user_static_top_JOBQUEUE_src_diab BSPNAME=hmt_t2080vpx3u_1_0_0_0 BUILDSTAGE=BUILD_USR_STATIC

	
	
BUILD_USR_SHARED : JOBQUEUE_src_diab__BUILD_USR_SHARED

.PHONY : JOBQUEUE_src_diab__BUILD_USR_SHARED

__BUILD_USR_SHARED_FB_IDS += user_shared_top_JOBQUEUE_src_diab

JOBQUEUE_src_diab__BUILD_USR_SHARED : 
	@ echo building JOBQUEUE directory src
	+ @ cd D:/vxWorks7/vxworks-7/pkgs/os/service/jobqueue-1.0.3.0/src && D:/vxWorks7/vxworks-7/host/binutils/x86-win32/bin/make _mk CPU=PPCE6500 TOOL=diab TOOL_VERSION=diab_5_9_6_1 _CC_VERSION=diab_5_9_6_5 SPACE=user LAYER_FORMAT=shared _VSB_CONFIG_ADDEDCFLAGS="" _WRS_CONFIG_APP_TOOL=diab VSBL_NAME=JOBQUEUE VSB_DIR=D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild _WRS_CONFIG_FP=hard _WRS_CLI_CFLAGS="-I. " _FB_ID=user_shared_top_JOBQUEUE_src_diab BSPNAME=hmt_t2080vpx3u_1_0_0_0 BUILDSTAGE=BUILD_USR_SHARED


	
	
	

	

	


	
# copying directory cdf to D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/cdf




PRENOBUILD : D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/cdf/00comp_job_queue.cdf

__FILES_TO_COPY_JOBQUEUE += D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/cdf/00comp_job_queue.cdf





 

D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/cdf/00comp_job_queue.cdf : D:/vxWorks7/vxworks-7/pkgs/os/service/jobqueue-1.0.3.0/cdf/00comp_job_queue.cdf | D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/cdf
ifdef __LAYER_DEPENDENCY_TEST
	cp -rfLs $< $@
else
	cp -rfL $< $@
endif


	
cdf_PRENOBUILD_JOBQUEUE_FILES = cdf/00comp_job_queue.cdf

cdf_PRENOBUILD_JOBQUEUE_DIR = D:/vxWorks7/vxworks-7/pkgs/os/service/jobqueue-1.0.3.0

PRENOBUILD_FILES += $(addprefix $(cdf_PRENOBUILD_JOBQUEUE_DIR)/,$(cdf_PRENOBUILD_JOBQUEUE_FILES))

PRENOBUILD : PRENOBUILD_JOBQUEUE

PRENOBUILD_JOBQUEUE : cdf_PRENOBUILD_JOBQUEUE

cdf_PRENOBUILD_JOBQUEUE : D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/cdf/cdf_PRENOBUILD_JOBQUEUE.cdf

D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/cdf/cdf_PRENOBUILD_JOBQUEUE.cdf : | D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/cdf
	$(file >D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/cdf/cdf_PRENOBUILD_JOBQUEUE.tmp,$(call __vsb_tmpl_cdf_inter,$(addprefix $(cdf_PRENOBUILD_JOBQUEUE_DIR)/,$(sort $(cdf_PRENOBUILD_JOBQUEUE_FILES))),JOBQUEUE))
	$(CDFCOMP) -i D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/cdf/cdf_PRENOBUILD_JOBQUEUE.tmp -o $@ -cpp "$(CPP) $(__OPTION_LANG_CDF)" -cpu PPCE6500 -layer JOBQUEUE -vsb D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild
	rm -f D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/cdf/cdf_PRENOBUILD_JOBQUEUE.tmp

	

	
# copying directory configlette to D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/configlette






	
__DIR_TARGETS += $(__DIR_TARGETS_JOBQUEUE)

__DIR_TARGETS_JOBQUEUE += D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/cdf D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/configlette D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/h D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/h/public D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/h/public/private D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/share/h D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/h D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/h/public D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/h/public/private D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/vsblCdf

