
#
# This file is automatically generated by mk/krnl/defs.fastlibgen.mk .
#
# build configuration :
#	VSB : D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild
#	CPU : PPCE6500
#	TOOL : diab
#	FP : hard
# 	ENDIAN : big
#	LIB_DIR_TAG = 
#	LIBDIRBASE = krnl/PPCE6500/common
#	LIBDIRBASE = krnl/$(CPU)$(CPU_OPTION_SUFFIX)/$(TOOL_COMMON_DIR)$(LIB_DIR_TAG)$(MINOR_OPTION_SUFFIX)






LIBOBJS = $(LIBOBJS_IPCOM)

# DEP_OBJS = (DEP_OBJS)

 
LIBOBJS_krnl_PPCE6500_common_IPCOM_kernel_top_IPNET_COREIP_src_ipcom_arch_powerpc_src_diab =  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/objIPCOM/ipcom_powerpc_vxworks.o  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/objIPCOM/ipcom_powerpc_vxworks.o 

arcmdfile_krnl_PPCE6500_common_IPCOM : $(LIBOBJS_krnl_PPCE6500_common_IPCOM_kernel_top_IPNET_COREIP_src_ipcom_arch_powerpc_src_diab)

LIBOBJS_krnl_PPCE6500_common_IPCOM_IPNET_COREIP += $(LIBOBJS_krnl_PPCE6500_common_IPCOM_kernel_top_IPNET_COREIP_src_ipcom_arch_powerpc_src_diab)

LIBOBJS_krnl_PPCE6500_common_IPCOM += $(LIBOBJS_krnl_PPCE6500_common_IPCOM_kernel_top_IPNET_COREIP_src_ipcom_arch_powerpc_src_diab)

__OBJS_TO_CLEAN_IPNET_COREIP += $(LIBOBJS_krnl_PPCE6500_common_IPCOM_kernel_top_IPNET_COREIP_src_ipcom_arch_powerpc_src_diab) $(LIBOBJS_krnl_PPCE6500_common_IPCOM_kernel_top_IPNET_COREIP_src_ipcom_arch_powerpc_src_diab:.o=.d)

ifndef _DONEBASE_LIB_krnl_PPCE6500_common_IPCOM

_DONEBASE_LIB_krnl_PPCE6500_common_IPCOM = TRUE

# LIBBASES += IPCOM

__LIBS_TO_BUILD += krnl_PPCE6500_common_IPCOM

__LIBS_TO_BUILD_IPNET_COREIP += krnl_PPCE6500_common_IPCOM

__BUILT_LIBS += krnl_PPCE6500_common_IPCOM

__LIB_krnl_PPCE6500_common_IPCOM = D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/libIPCOM$(OPT).a


D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/objIPCOM :
	$(MKDIR) $@


lib : D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/libIPCOM$(OPT).a  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/libIPCOM.cdf

# need to pass the lib.a file twice to D:/vxWorks7/compilers/diab-5.9.6.5/WIN32/bin/ddump -Ng to workaround ddump problem
D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/libIPCOM.nm : D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/libIPCOM$(OPT).a
	$(if $(wildcard $<),cd D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common && $(NM) libIPCOM$(OPT).a libIPCOM$(OPT).a > $@, $(info skipping $@ : non existant $<))

D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/libIPCOM.cdf : D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/libIPCOM.nm 
	$(if $(wildcard $<),$(LIB2CDF) -i $< -a libIPCOM.a -o $@, $(info skipping $@ : non existant $<))

arcmdfiles : arcmdfile_krnl_PPCE6500_common_IPCOM

arcmdfile_krnl_PPCE6500_common_IPCOM :
	$(file >$@,$(call uniq,$(LIBOBJS_krnl_PPCE6500_common_IPCOM)))
	@echo created $@

D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/libIPCOM$(OPT).a : arcmdfile_krnl_PPCE6500_common_IPCOM
	D:/vxWorks7/compilers/diab-5.9.6.5/WIN32/bin/dar crusv $@ @arcmdfile_krnl_PPCE6500_common_IPCOM


clean _layer_clean_IPNET_COREIP : _clean_LIB_BASE_krnl_PPCE6500_common_IPCOM

_clean_LIB_BASE_krnl_PPCE6500_common_IPCOM :
	rm -f D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/libIPCOM$(OPT).a


endif

ifndef _DONEBASE_LIB_IPNET_COREIP_krnl_PPCE6500_common_IPCOM

_DONEBASE_LIB_IPNET_COREIP_krnl_PPCE6500_common_IPCOM = TRUE

lib : D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/layerIPNET_COREIP_libIPCOM.cdf

D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/layerIPNET_COREIP_libIPCOM.cdf :  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/libIPCOM$(OPT).a
	$(file >$@, $(call __tmpl_layercdf,IPNET_COREIP,libIPCOM.a,$(LIBOBJS_krnl_PPCE6500_common_IPCOM)))

endif


D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/libIPCOM$(OPT).a : $(LIBOBJS_krnl_PPCE6500_common_IPCOM)




 

################
# rules defined locally in Makefile
##



################

objs : $(LIBOBJS)
 
# this is the end of the file 