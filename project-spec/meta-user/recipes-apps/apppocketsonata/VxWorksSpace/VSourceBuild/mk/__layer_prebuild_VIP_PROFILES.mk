
	
# this file is automatically generated by mk/krnl/defs.layers.mk. Please do not edit

__FILE_COPIED += $(__FILES_COPIED_VIP_PROFILES)




	
	

	


	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	


	
	
	
	
	
	
	

	
	
	

	
	
	

	

	


	
# copying directory profiles to D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/cdf





	
profiles_PRENOBUILD_VIP_PROFILES_FILES = 

profiles_PRENOBUILD_VIP_PROFILES_DIR = D:/vxWorks7/vxworks-7/pkgs/vip_profiles

PRENOBUILD_FILES += $(addprefix $(profiles_PRENOBUILD_VIP_PROFILES_DIR)/,$(profiles_PRENOBUILD_VIP_PROFILES_FILES))

PRENOBUILD : PRENOBUILD_VIP_PROFILES

PRENOBUILD_VIP_PROFILES : profiles_PRENOBUILD_VIP_PROFILES

profiles_PRENOBUILD_VIP_PROFILES : D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/cdf/profiles_PRENOBUILD_VIP_PROFILES.cdf

D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/cdf/profiles_PRENOBUILD_VIP_PROFILES.cdf : | D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/cdf
	$(file >D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/cdf/profiles_PRENOBUILD_VIP_PROFILES.tmp,$(call __vsb_tmpl_cdf_inter,$(addprefix $(profiles_PRENOBUILD_VIP_PROFILES_DIR)/,$(sort $(profiles_PRENOBUILD_VIP_PROFILES_FILES))),VIP_PROFILES))
	$(CDFCOMP) -i D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/cdf/profiles_PRENOBUILD_VIP_PROFILES.tmp -o $@ -cpp "$(CPP) $(__OPTION_LANG_CDF)" -cpu PPCE6500 -layer VIP_PROFILES -vsb D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild
	rm -f D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/cdf/profiles_PRENOBUILD_VIP_PROFILES.tmp

	

	

	
__DIR_TARGETS += $(__DIR_TARGETS_VIP_PROFILES)

__DIR_TARGETS_VIP_PROFILES += D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/cdf D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/configlette D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/h D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/share/h D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/usr/h D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/vsblCdf

