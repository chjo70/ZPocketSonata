
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



include kernel_top_CORE_KERNEL_src_diab_demo_smp_perf.mk 
include kernel_top_CORE_KERNEL_src_diab_demo_smp_phil.mk



LIBOBJS = $(LIBOBJS_smpdemo)

# DEP_OBJS = (DEP_OBJS)

 
LIBOBJS_krnl_PPCE6500_common_smpdemo_kernel_top_CORE_KERNEL_src_diab_demo_smp =  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/objsmpdemo/smpDemo.o  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/objsmpdemo/graphLib.o  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/objsmpdemo/smpLockDemo.o  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/objsmpdemo/smpDemo.o  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/objsmpdemo/graphLib.o  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/objsmpdemo/smpLockDemo.o 

arcmdfile_krnl_PPCE6500_common_smpdemo : $(LIBOBJS_krnl_PPCE6500_common_smpdemo_kernel_top_CORE_KERNEL_src_diab_demo_smp)

LIBOBJS_krnl_PPCE6500_common_smpdemo_CORE_KERNEL += $(LIBOBJS_krnl_PPCE6500_common_smpdemo_kernel_top_CORE_KERNEL_src_diab_demo_smp)

LIBOBJS_krnl_PPCE6500_common_smpdemo += $(LIBOBJS_krnl_PPCE6500_common_smpdemo_kernel_top_CORE_KERNEL_src_diab_demo_smp)

__OBJS_TO_CLEAN_CORE_KERNEL += $(LIBOBJS_krnl_PPCE6500_common_smpdemo_kernel_top_CORE_KERNEL_src_diab_demo_smp) $(LIBOBJS_krnl_PPCE6500_common_smpdemo_kernel_top_CORE_KERNEL_src_diab_demo_smp:.o=.d)

ifndef _DONEBASE_LIB_krnl_PPCE6500_common_smpdemo

_DONEBASE_LIB_krnl_PPCE6500_common_smpdemo = TRUE

# LIBBASES += smpdemo

__LIBS_TO_BUILD += krnl_PPCE6500_common_smpdemo

__LIBS_TO_BUILD_CORE_KERNEL += krnl_PPCE6500_common_smpdemo

__BUILT_LIBS += krnl_PPCE6500_common_smpdemo

__LIB_krnl_PPCE6500_common_smpdemo = D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libsmpdemo$(OPT).a


D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/objsmpdemo :
	$(MKDIR) $@


lib : D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libsmpdemo$(OPT).a  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libsmpdemo.cdf

# need to pass the lib.a file twice to D:/vxWorks7/compilers/diab-5.9.6.5/WIN32/bin/ddump -Ng to workaround ddump problem
D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libsmpdemo.nm : D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libsmpdemo$(OPT).a
	$(if $(wildcard $<),cd D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common && $(NM) libsmpdemo$(OPT).a libsmpdemo$(OPT).a > $@, $(info skipping $@ : non existant $<))

D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libsmpdemo.cdf : D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libsmpdemo.nm 
	$(if $(wildcard $<),$(LIB2CDF) -i $< -a libsmpdemo.a -o $@, $(info skipping $@ : non existant $<))

arcmdfiles : arcmdfile_krnl_PPCE6500_common_smpdemo

arcmdfile_krnl_PPCE6500_common_smpdemo :
	$(file >$@,$(call uniq,$(LIBOBJS_krnl_PPCE6500_common_smpdemo)))
	@echo created $@

D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libsmpdemo$(OPT).a : arcmdfile_krnl_PPCE6500_common_smpdemo
	D:/vxWorks7/compilers/diab-5.9.6.5/WIN32/bin/dar crusv $@ @arcmdfile_krnl_PPCE6500_common_smpdemo


clean _layer_clean_CORE_KERNEL : _clean_LIB_BASE_krnl_PPCE6500_common_smpdemo

_clean_LIB_BASE_krnl_PPCE6500_common_smpdemo :
	rm -f D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libsmpdemo$(OPT).a


endif

ifndef _DONEBASE_LIB_CORE_KERNEL_krnl_PPCE6500_common_smpdemo

_DONEBASE_LIB_CORE_KERNEL_krnl_PPCE6500_common_smpdemo = TRUE

lib : D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/layerCORE_KERNEL_libsmpdemo.cdf

D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/layerCORE_KERNEL_libsmpdemo.cdf :  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libsmpdemo$(OPT).a
	$(file >$@, $(call __tmpl_layercdf,CORE_KERNEL,libsmpdemo.a,$(LIBOBJS_krnl_PPCE6500_common_smpdemo)))

endif


D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libsmpdemo$(OPT).a : $(LIBOBJS_krnl_PPCE6500_common_smpdemo)




 

################
# rules defined locally in Makefile
##



################

objs : $(LIBOBJS)
 
# this is the end of the file 
