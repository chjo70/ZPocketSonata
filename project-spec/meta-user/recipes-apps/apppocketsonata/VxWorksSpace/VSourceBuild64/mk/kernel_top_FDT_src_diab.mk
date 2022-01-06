
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



include kernel_top_FDT_src_diab_libfdt.mk



LIBOBJS = $(LIBOBJS_fdt)

# DEP_OBJS = (DEP_OBJS)

 
LIBOBJS_krnl_PPCE6500_common_fdt_kernel_top_FDT_src_diab =  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/objfdt/vxFdtLib.o  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/objfdt/vxFdtCpu.o  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/objfdt/vxFdtRwLib.o  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/objfdt/vxFdtShow.o 

arcmdfile_krnl_PPCE6500_common_fdt : $(LIBOBJS_krnl_PPCE6500_common_fdt_kernel_top_FDT_src_diab)

LIBOBJS_krnl_PPCE6500_common_fdt_FDT += $(LIBOBJS_krnl_PPCE6500_common_fdt_kernel_top_FDT_src_diab)

LIBOBJS_krnl_PPCE6500_common_fdt += $(LIBOBJS_krnl_PPCE6500_common_fdt_kernel_top_FDT_src_diab)

__OBJS_TO_CLEAN_FDT += $(LIBOBJS_krnl_PPCE6500_common_fdt_kernel_top_FDT_src_diab) $(LIBOBJS_krnl_PPCE6500_common_fdt_kernel_top_FDT_src_diab:.o=.d)

ifndef _DONEBASE_LIB_krnl_PPCE6500_common_fdt

_DONEBASE_LIB_krnl_PPCE6500_common_fdt = TRUE

# LIBBASES += fdt

__LIBS_TO_BUILD += krnl_PPCE6500_common_fdt

__LIBS_TO_BUILD_FDT += krnl_PPCE6500_common_fdt

__BUILT_LIBS += krnl_PPCE6500_common_fdt

__LIB_krnl_PPCE6500_common_fdt = D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libfdt$(OPT).a


D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/objfdt :
	$(MKDIR) $@


lib : D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libfdt$(OPT).a  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libfdt.cdf

# need to pass the lib.a file twice to D:/vxWorks7/compilers/diab-5.9.6.5/WIN32/bin/ddump -Ng to workaround ddump problem
D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libfdt.nm : D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libfdt$(OPT).a
	$(if $(wildcard $<),cd D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common && $(NM) libfdt$(OPT).a libfdt$(OPT).a > $@, $(info skipping $@ : non existant $<))

D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libfdt.cdf : D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libfdt.nm 
	$(if $(wildcard $<),$(LIB2CDF) -i $< -a libfdt.a -o $@, $(info skipping $@ : non existant $<))

arcmdfiles : arcmdfile_krnl_PPCE6500_common_fdt

arcmdfile_krnl_PPCE6500_common_fdt :
	$(file >$@,$(call uniq,$(LIBOBJS_krnl_PPCE6500_common_fdt)))
	@echo created $@

D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libfdt$(OPT).a : arcmdfile_krnl_PPCE6500_common_fdt
	D:/vxWorks7/compilers/diab-5.9.6.5/WIN32/bin/dar crusv $@ @arcmdfile_krnl_PPCE6500_common_fdt


clean _layer_clean_FDT : _clean_LIB_BASE_krnl_PPCE6500_common_fdt

_clean_LIB_BASE_krnl_PPCE6500_common_fdt :
	rm -f D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libfdt$(OPT).a


endif

ifndef _DONEBASE_LIB_FDT_krnl_PPCE6500_common_fdt

_DONEBASE_LIB_FDT_krnl_PPCE6500_common_fdt = TRUE

lib : D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/layerFDT_libfdt.cdf

D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/layerFDT_libfdt.cdf :  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libfdt$(OPT).a
	$(file >$@, $(call __tmpl_layercdf,FDT,libfdt.a,$(LIBOBJS_krnl_PPCE6500_common_fdt)))

endif


D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libfdt$(OPT).a : $(LIBOBJS_krnl_PPCE6500_common_fdt)




 

################
# rules defined locally in Makefile
##



################

objs : $(LIBOBJS)
 
# this is the end of the file 
