
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






LIBOBJS = $(LIBOBJS_BRIDGE)

# DEP_OBJS = (DEP_OBJS)

 
LIBOBJS_krnl_PPCE6500_common_BRIDGE_kernel_top_IPNET_BRIDGE_src_diab =  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/objBRIDGE/bridge.o  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/objBRIDGE/mirrorEnd.o  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/objBRIDGE/mirrorUtils.o  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/objBRIDGE/bridge.o  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/objBRIDGE/mirrorEnd.o  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/objBRIDGE/mirrorUtils.o 

arcmdfile_krnl_PPCE6500_common_BRIDGE : $(LIBOBJS_krnl_PPCE6500_common_BRIDGE_kernel_top_IPNET_BRIDGE_src_diab)

LIBOBJS_krnl_PPCE6500_common_BRIDGE_IPNET_BRIDGE += $(LIBOBJS_krnl_PPCE6500_common_BRIDGE_kernel_top_IPNET_BRIDGE_src_diab)

LIBOBJS_krnl_PPCE6500_common_BRIDGE += $(LIBOBJS_krnl_PPCE6500_common_BRIDGE_kernel_top_IPNET_BRIDGE_src_diab)

__OBJS_TO_CLEAN_IPNET_BRIDGE += $(LIBOBJS_krnl_PPCE6500_common_BRIDGE_kernel_top_IPNET_BRIDGE_src_diab) $(LIBOBJS_krnl_PPCE6500_common_BRIDGE_kernel_top_IPNET_BRIDGE_src_diab:.o=.d)

ifndef _DONEBASE_LIB_krnl_PPCE6500_common_BRIDGE

_DONEBASE_LIB_krnl_PPCE6500_common_BRIDGE = TRUE

# LIBBASES += BRIDGE

__LIBS_TO_BUILD += krnl_PPCE6500_common_BRIDGE

__LIBS_TO_BUILD_IPNET_BRIDGE += krnl_PPCE6500_common_BRIDGE

__BUILT_LIBS += krnl_PPCE6500_common_BRIDGE

__LIB_krnl_PPCE6500_common_BRIDGE = D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libBRIDGE$(OPT).a


D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/objBRIDGE :
	$(MKDIR) $@


lib : D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libBRIDGE$(OPT).a  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libBRIDGE.cdf

# need to pass the lib.a file twice to D:/vxWorks7/compilers/diab-5.9.6.5/WIN32/bin/ddump -Ng to workaround ddump problem
D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libBRIDGE.nm : D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libBRIDGE$(OPT).a
	$(if $(wildcard $<),cd D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common && $(NM) libBRIDGE$(OPT).a libBRIDGE$(OPT).a > $@, $(info skipping $@ : non existant $<))

D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libBRIDGE.cdf : D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libBRIDGE.nm 
	$(if $(wildcard $<),$(LIB2CDF) -i $< -a libBRIDGE.a -o $@, $(info skipping $@ : non existant $<))

arcmdfiles : arcmdfile_krnl_PPCE6500_common_BRIDGE

arcmdfile_krnl_PPCE6500_common_BRIDGE :
	$(file >$@,$(call uniq,$(LIBOBJS_krnl_PPCE6500_common_BRIDGE)))
	@echo created $@

D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libBRIDGE$(OPT).a : arcmdfile_krnl_PPCE6500_common_BRIDGE
	D:/vxWorks7/compilers/diab-5.9.6.5/WIN32/bin/dar crusv $@ @arcmdfile_krnl_PPCE6500_common_BRIDGE


clean _layer_clean_IPNET_BRIDGE : _clean_LIB_BASE_krnl_PPCE6500_common_BRIDGE

_clean_LIB_BASE_krnl_PPCE6500_common_BRIDGE :
	rm -f D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libBRIDGE$(OPT).a


endif

ifndef _DONEBASE_LIB_IPNET_BRIDGE_krnl_PPCE6500_common_BRIDGE

_DONEBASE_LIB_IPNET_BRIDGE_krnl_PPCE6500_common_BRIDGE = TRUE

lib : D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/layerIPNET_BRIDGE_libBRIDGE.cdf

D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/layerIPNET_BRIDGE_libBRIDGE.cdf :  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libBRIDGE$(OPT).a
	$(file >$@, $(call __tmpl_layercdf,IPNET_BRIDGE,libBRIDGE.a,$(LIBOBJS_krnl_PPCE6500_common_BRIDGE)))

endif


D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libBRIDGE$(OPT).a : $(LIBOBJS_krnl_PPCE6500_common_BRIDGE)




 

################
# rules defined locally in Makefile
##



################

objs : $(LIBOBJS)
 
# this is the end of the file 
