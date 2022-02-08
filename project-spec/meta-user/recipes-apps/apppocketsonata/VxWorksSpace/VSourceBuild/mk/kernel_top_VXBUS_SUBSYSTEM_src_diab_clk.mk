
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






LIBOBJS = $(LIBOBJS_vxbus)

# DEP_OBJS = (DEP_OBJS)

 
LIBOBJS_krnl_PPCE6500_common_vxbus_kernel_top_VXBUS_SUBSYSTEM_src_diab_clk =  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/objvxbus/vxbClkLib.o 

arcmdfile_krnl_PPCE6500_common_vxbus : $(LIBOBJS_krnl_PPCE6500_common_vxbus_kernel_top_VXBUS_SUBSYSTEM_src_diab_clk)

LIBOBJS_krnl_PPCE6500_common_vxbus_VXBUS_SUBSYSTEM += $(LIBOBJS_krnl_PPCE6500_common_vxbus_kernel_top_VXBUS_SUBSYSTEM_src_diab_clk)

LIBOBJS_krnl_PPCE6500_common_vxbus += $(LIBOBJS_krnl_PPCE6500_common_vxbus_kernel_top_VXBUS_SUBSYSTEM_src_diab_clk)

__OBJS_TO_CLEAN_VXBUS_SUBSYSTEM += $(LIBOBJS_krnl_PPCE6500_common_vxbus_kernel_top_VXBUS_SUBSYSTEM_src_diab_clk) $(LIBOBJS_krnl_PPCE6500_common_vxbus_kernel_top_VXBUS_SUBSYSTEM_src_diab_clk:.o=.d)

ifndef _DONEBASE_LIB_krnl_PPCE6500_common_vxbus

_DONEBASE_LIB_krnl_PPCE6500_common_vxbus = TRUE

# LIBBASES += vxbus

__LIBS_TO_BUILD += krnl_PPCE6500_common_vxbus

__LIBS_TO_BUILD_VXBUS_SUBSYSTEM += krnl_PPCE6500_common_vxbus

__BUILT_LIBS += krnl_PPCE6500_common_vxbus

__LIB_krnl_PPCE6500_common_vxbus = D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/libvxbus$(OPT).a


D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/objvxbus :
	$(MKDIR) $@


lib : D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/libvxbus$(OPT).a  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/libvxbus.cdf

# need to pass the lib.a file twice to D:/vxWorks7/compilers/diab-5.9.6.5/WIN32/bin/ddump -Ng to workaround ddump problem
D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/libvxbus.nm : D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/libvxbus$(OPT).a
	$(if $(wildcard $<),cd D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common && $(NM) libvxbus$(OPT).a libvxbus$(OPT).a > $@, $(info skipping $@ : non existant $<))

D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/libvxbus.cdf : D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/libvxbus.nm 
	$(if $(wildcard $<),$(LIB2CDF) -i $< -a libvxbus.a -o $@, $(info skipping $@ : non existant $<))

arcmdfiles : arcmdfile_krnl_PPCE6500_common_vxbus

arcmdfile_krnl_PPCE6500_common_vxbus :
	$(file >$@,$(call uniq,$(LIBOBJS_krnl_PPCE6500_common_vxbus)))
	@echo created $@

D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/libvxbus$(OPT).a : arcmdfile_krnl_PPCE6500_common_vxbus
	D:/vxWorks7/compilers/diab-5.9.6.5/WIN32/bin/dar crusv $@ @arcmdfile_krnl_PPCE6500_common_vxbus


clean _layer_clean_VXBUS_SUBSYSTEM : _clean_LIB_BASE_krnl_PPCE6500_common_vxbus

_clean_LIB_BASE_krnl_PPCE6500_common_vxbus :
	rm -f D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/libvxbus$(OPT).a


endif

ifndef _DONEBASE_LIB_VXBUS_SUBSYSTEM_krnl_PPCE6500_common_vxbus

_DONEBASE_LIB_VXBUS_SUBSYSTEM_krnl_PPCE6500_common_vxbus = TRUE

lib : D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/layerVXBUS_SUBSYSTEM_libvxbus.cdf

D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/layerVXBUS_SUBSYSTEM_libvxbus.cdf :  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/libvxbus$(OPT).a
	$(file >$@, $(call __tmpl_layercdf,VXBUS_SUBSYSTEM,libvxbus.a,$(LIBOBJS_krnl_PPCE6500_common_vxbus)))

endif


D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/libvxbus$(OPT).a : $(LIBOBJS_krnl_PPCE6500_common_vxbus)




 

################
# rules defined locally in Makefile
##



################

objs : $(LIBOBJS)
 
# this is the end of the file 
