
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






LIBOBJS = $(LIBOBJS_spl) $(LIBOBJS_splDbg)

# DEP_OBJS = (DEP_OBJS)

 
LIBOBJS_krnl_PPCE6500_common_spl_kernel_top_CORE_KERNEL_src_diab_multicore_lock =  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/objspl/kernelLockLib.o  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/objspl/spinLockIsrNdLib.o  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/objspl/spinLockSmpLib.o  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/objspl/spinLockNdTimedLib.o 

arcmdfile_krnl_PPCE6500_common_spl : $(LIBOBJS_krnl_PPCE6500_common_spl_kernel_top_CORE_KERNEL_src_diab_multicore_lock)

LIBOBJS_krnl_PPCE6500_common_spl_CORE_KERNEL += $(LIBOBJS_krnl_PPCE6500_common_spl_kernel_top_CORE_KERNEL_src_diab_multicore_lock)

LIBOBJS_krnl_PPCE6500_common_spl += $(LIBOBJS_krnl_PPCE6500_common_spl_kernel_top_CORE_KERNEL_src_diab_multicore_lock)

__OBJS_TO_CLEAN_CORE_KERNEL += $(LIBOBJS_krnl_PPCE6500_common_spl_kernel_top_CORE_KERNEL_src_diab_multicore_lock) $(LIBOBJS_krnl_PPCE6500_common_spl_kernel_top_CORE_KERNEL_src_diab_multicore_lock:.o=.d)

ifndef _DONEBASE_LIB_krnl_PPCE6500_common_spl

_DONEBASE_LIB_krnl_PPCE6500_common_spl = TRUE

# LIBBASES += spl

__LIBS_TO_BUILD += krnl_PPCE6500_common_spl

__LIBS_TO_BUILD_CORE_KERNEL += krnl_PPCE6500_common_spl

__BUILT_LIBS += krnl_PPCE6500_common_spl

__LIB_krnl_PPCE6500_common_spl = D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libspl$(OPT).a


D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/objspl :
	$(MKDIR) $@


lib : D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libspl$(OPT).a  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libspl.cdf

# need to pass the lib.a file twice to D:/vxWorks7/compilers/diab-5.9.6.5/WIN32/bin/ddump -Ng to workaround ddump problem
D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libspl.nm : D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libspl$(OPT).a
	$(if $(wildcard $<),cd D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common && $(NM) libspl$(OPT).a libspl$(OPT).a > $@, $(info skipping $@ : non existant $<))

D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libspl.cdf : D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libspl.nm 
	$(if $(wildcard $<),$(LIB2CDF) -i $< -a libspl.a -o $@, $(info skipping $@ : non existant $<))

arcmdfiles : arcmdfile_krnl_PPCE6500_common_spl

arcmdfile_krnl_PPCE6500_common_spl :
	$(file >$@,$(call uniq,$(LIBOBJS_krnl_PPCE6500_common_spl)))
	@echo created $@

D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libspl$(OPT).a : arcmdfile_krnl_PPCE6500_common_spl
	D:/vxWorks7/compilers/diab-5.9.6.5/WIN32/bin/dar crusv $@ @arcmdfile_krnl_PPCE6500_common_spl


clean _layer_clean_CORE_KERNEL : _clean_LIB_BASE_krnl_PPCE6500_common_spl

_clean_LIB_BASE_krnl_PPCE6500_common_spl :
	rm -f D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libspl$(OPT).a


endif

ifndef _DONEBASE_LIB_CORE_KERNEL_krnl_PPCE6500_common_spl

_DONEBASE_LIB_CORE_KERNEL_krnl_PPCE6500_common_spl = TRUE

lib : D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/layerCORE_KERNEL_libspl.cdf

D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/layerCORE_KERNEL_libspl.cdf :  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libspl$(OPT).a
	$(file >$@, $(call __tmpl_layercdf,CORE_KERNEL,libspl.a,$(LIBOBJS_krnl_PPCE6500_common_spl)))

endif


D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libspl$(OPT).a : $(LIBOBJS_krnl_PPCE6500_common_spl)
  
LIBOBJS_krnl_PPCE6500_common_splDbg_kernel_top_CORE_KERNEL_src_diab_multicore_lock =  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/objsplDbg/kernelLockLib.o  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/objsplDbg/spinLockIsrNdLib.o  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/objsplDbg/spinLockSmpDbgLib.o 

arcmdfile_krnl_PPCE6500_common_splDbg : $(LIBOBJS_krnl_PPCE6500_common_splDbg_kernel_top_CORE_KERNEL_src_diab_multicore_lock)

LIBOBJS_krnl_PPCE6500_common_splDbg_CORE_KERNEL += $(LIBOBJS_krnl_PPCE6500_common_splDbg_kernel_top_CORE_KERNEL_src_diab_multicore_lock)

LIBOBJS_krnl_PPCE6500_common_splDbg += $(LIBOBJS_krnl_PPCE6500_common_splDbg_kernel_top_CORE_KERNEL_src_diab_multicore_lock)

__OBJS_TO_CLEAN_CORE_KERNEL += $(LIBOBJS_krnl_PPCE6500_common_splDbg_kernel_top_CORE_KERNEL_src_diab_multicore_lock) $(LIBOBJS_krnl_PPCE6500_common_splDbg_kernel_top_CORE_KERNEL_src_diab_multicore_lock:.o=.d)

ifndef _DONEBASE_LIB_krnl_PPCE6500_common_splDbg

_DONEBASE_LIB_krnl_PPCE6500_common_splDbg = TRUE

# LIBBASES += splDbg

__LIBS_TO_BUILD += krnl_PPCE6500_common_splDbg

__LIBS_TO_BUILD_CORE_KERNEL += krnl_PPCE6500_common_splDbg

__BUILT_LIBS += krnl_PPCE6500_common_splDbg

__LIB_krnl_PPCE6500_common_splDbg = D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libsplDbg$(OPT).a


D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/objsplDbg :
	$(MKDIR) $@


lib : D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libsplDbg$(OPT).a  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libsplDbg.cdf

# need to pass the lib.a file twice to D:/vxWorks7/compilers/diab-5.9.6.5/WIN32/bin/ddump -Ng to workaround ddump problem
D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libsplDbg.nm : D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libsplDbg$(OPT).a
	$(if $(wildcard $<),cd D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common && $(NM) libsplDbg$(OPT).a libsplDbg$(OPT).a > $@, $(info skipping $@ : non existant $<))

D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libsplDbg.cdf : D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libsplDbg.nm 
	$(if $(wildcard $<),$(LIB2CDF) -i $< -a libsplDbg.a -o $@, $(info skipping $@ : non existant $<))

arcmdfiles : arcmdfile_krnl_PPCE6500_common_splDbg

arcmdfile_krnl_PPCE6500_common_splDbg :
	$(file >$@,$(call uniq,$(LIBOBJS_krnl_PPCE6500_common_splDbg)))
	@echo created $@

D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libsplDbg$(OPT).a : arcmdfile_krnl_PPCE6500_common_splDbg
	D:/vxWorks7/compilers/diab-5.9.6.5/WIN32/bin/dar crusv $@ @arcmdfile_krnl_PPCE6500_common_splDbg


clean _layer_clean_CORE_KERNEL : _clean_LIB_BASE_krnl_PPCE6500_common_splDbg

_clean_LIB_BASE_krnl_PPCE6500_common_splDbg :
	rm -f D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libsplDbg$(OPT).a


endif

ifndef _DONEBASE_LIB_CORE_KERNEL_krnl_PPCE6500_common_splDbg

_DONEBASE_LIB_CORE_KERNEL_krnl_PPCE6500_common_splDbg = TRUE

lib : D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/layerCORE_KERNEL_libsplDbg.cdf

D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/layerCORE_KERNEL_libsplDbg.cdf :  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libsplDbg$(OPT).a
	$(file >$@, $(call __tmpl_layercdf,CORE_KERNEL,libsplDbg.a,$(LIBOBJS_krnl_PPCE6500_common_splDbg)))

endif


D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libsplDbg$(OPT).a : $(LIBOBJS_krnl_PPCE6500_common_splDbg)


 

   

################
# rules defined locally in Makefile
##



################

objs : $(LIBOBJS)
 
# this is the end of the file 
