
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






LIBOBJS = $(LIBOBJS_DHCPC)

# DEP_OBJS = (DEP_OBJS)

 
LIBOBJS_krnl_PPCE6500_common_DHCPC_kernel_top_IPNET_DHCPC_src_diab =  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/objDHCPC/ipdhcpc.o  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/objDHCPC/ipdhcpc_cmd_dhcpc.o  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/objDHCPC/ipdhcpc.o  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/objDHCPC/ipdhcpc_cmd_dhcpc.o 

arcmdfile_krnl_PPCE6500_common_DHCPC : $(LIBOBJS_krnl_PPCE6500_common_DHCPC_kernel_top_IPNET_DHCPC_src_diab)

LIBOBJS_krnl_PPCE6500_common_DHCPC_IPNET_DHCPC += $(LIBOBJS_krnl_PPCE6500_common_DHCPC_kernel_top_IPNET_DHCPC_src_diab)

LIBOBJS_krnl_PPCE6500_common_DHCPC += $(LIBOBJS_krnl_PPCE6500_common_DHCPC_kernel_top_IPNET_DHCPC_src_diab)

__OBJS_TO_CLEAN_IPNET_DHCPC += $(LIBOBJS_krnl_PPCE6500_common_DHCPC_kernel_top_IPNET_DHCPC_src_diab) $(LIBOBJS_krnl_PPCE6500_common_DHCPC_kernel_top_IPNET_DHCPC_src_diab:.o=.d)

ifndef _DONEBASE_LIB_krnl_PPCE6500_common_DHCPC

_DONEBASE_LIB_krnl_PPCE6500_common_DHCPC = TRUE

# LIBBASES += DHCPC

__LIBS_TO_BUILD += krnl_PPCE6500_common_DHCPC

__LIBS_TO_BUILD_IPNET_DHCPC += krnl_PPCE6500_common_DHCPC

__BUILT_LIBS += krnl_PPCE6500_common_DHCPC

__LIB_krnl_PPCE6500_common_DHCPC = D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/libDHCPC$(OPT).a


D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/objDHCPC :
	$(MKDIR) $@


lib : D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/libDHCPC$(OPT).a  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/libDHCPC.cdf

# need to pass the lib.a file twice to D:/vxWorks7/compilers/diab-5.9.6.5/WIN32/bin/ddump -Ng to workaround ddump problem
D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/libDHCPC.nm : D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/libDHCPC$(OPT).a
	$(if $(wildcard $<),cd D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common && $(NM) libDHCPC$(OPT).a libDHCPC$(OPT).a > $@, $(info skipping $@ : non existant $<))

D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/libDHCPC.cdf : D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/libDHCPC.nm 
	$(if $(wildcard $<),$(LIB2CDF) -i $< -a libDHCPC.a -o $@, $(info skipping $@ : non existant $<))

arcmdfiles : arcmdfile_krnl_PPCE6500_common_DHCPC

arcmdfile_krnl_PPCE6500_common_DHCPC :
	$(file >$@,$(call uniq,$(LIBOBJS_krnl_PPCE6500_common_DHCPC)))
	@echo created $@

D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/libDHCPC$(OPT).a : arcmdfile_krnl_PPCE6500_common_DHCPC
	D:/vxWorks7/compilers/diab-5.9.6.5/WIN32/bin/dar crusv $@ @arcmdfile_krnl_PPCE6500_common_DHCPC


clean _layer_clean_IPNET_DHCPC : _clean_LIB_BASE_krnl_PPCE6500_common_DHCPC

_clean_LIB_BASE_krnl_PPCE6500_common_DHCPC :
	rm -f D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/libDHCPC$(OPT).a


endif

ifndef _DONEBASE_LIB_IPNET_DHCPC_krnl_PPCE6500_common_DHCPC

_DONEBASE_LIB_IPNET_DHCPC_krnl_PPCE6500_common_DHCPC = TRUE

lib : D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/layerIPNET_DHCPC_libDHCPC.cdf

D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/layerIPNET_DHCPC_libDHCPC.cdf :  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/libDHCPC$(OPT).a
	$(file >$@, $(call __tmpl_layercdf,IPNET_DHCPC,libDHCPC.a,$(LIBOBJS_krnl_PPCE6500_common_DHCPC)))

endif


D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/libDHCPC$(OPT).a : $(LIBOBJS_krnl_PPCE6500_common_DHCPC)




 

################
# rules defined locally in Makefile
##



################

objs : $(LIBOBJS)
 
# this is the end of the file 