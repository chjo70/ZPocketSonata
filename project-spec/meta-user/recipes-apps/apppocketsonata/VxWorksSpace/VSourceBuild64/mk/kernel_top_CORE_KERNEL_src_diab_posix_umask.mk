
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






LIBOBJS = $(LIBOBJS_umask)

# DEP_OBJS = (DEP_OBJS)

 
LIBOBJS_krnl_PPCE6500_common_umask_kernel_top_CORE_KERNEL_src_diab_posix_umask =  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/objumask/umaskLib.o  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/objumask/umaskScLib.o  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/objumask/umaskLib.o  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/objumask/umaskScLib.o 

arcmdfile_krnl_PPCE6500_common_umask : $(LIBOBJS_krnl_PPCE6500_common_umask_kernel_top_CORE_KERNEL_src_diab_posix_umask)

LIBOBJS_krnl_PPCE6500_common_umask_CORE_KERNEL += $(LIBOBJS_krnl_PPCE6500_common_umask_kernel_top_CORE_KERNEL_src_diab_posix_umask)

LIBOBJS_krnl_PPCE6500_common_umask += $(LIBOBJS_krnl_PPCE6500_common_umask_kernel_top_CORE_KERNEL_src_diab_posix_umask)

__OBJS_TO_CLEAN_CORE_KERNEL += $(LIBOBJS_krnl_PPCE6500_common_umask_kernel_top_CORE_KERNEL_src_diab_posix_umask) $(LIBOBJS_krnl_PPCE6500_common_umask_kernel_top_CORE_KERNEL_src_diab_posix_umask:.o=.d)

ifndef _DONEBASE_LIB_krnl_PPCE6500_common_umask

_DONEBASE_LIB_krnl_PPCE6500_common_umask = TRUE

# LIBBASES += umask

__LIBS_TO_BUILD += krnl_PPCE6500_common_umask

__LIBS_TO_BUILD_CORE_KERNEL += krnl_PPCE6500_common_umask

__BUILT_LIBS += krnl_PPCE6500_common_umask

__LIB_krnl_PPCE6500_common_umask = D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libumask$(OPT).a


D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/objumask :
	$(MKDIR) $@


lib : D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libumask$(OPT).a  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libumask.cdf

# need to pass the lib.a file twice to D:/vxWorks7/compilers/diab-5.9.6.5/WIN32/bin/ddump -Ng to workaround ddump problem
D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libumask.nm : D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libumask$(OPT).a
	$(if $(wildcard $<),cd D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common && $(NM) libumask$(OPT).a libumask$(OPT).a > $@, $(info skipping $@ : non existant $<))

D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libumask.cdf : D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libumask.nm 
	$(if $(wildcard $<),$(LIB2CDF) -i $< -a libumask.a -o $@, $(info skipping $@ : non existant $<))

arcmdfiles : arcmdfile_krnl_PPCE6500_common_umask

arcmdfile_krnl_PPCE6500_common_umask :
	$(file >$@,$(call uniq,$(LIBOBJS_krnl_PPCE6500_common_umask)))
	@echo created $@

D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libumask$(OPT).a : arcmdfile_krnl_PPCE6500_common_umask
	D:/vxWorks7/compilers/diab-5.9.6.5/WIN32/bin/dar crusv $@ @arcmdfile_krnl_PPCE6500_common_umask


clean _layer_clean_CORE_KERNEL : _clean_LIB_BASE_krnl_PPCE6500_common_umask

_clean_LIB_BASE_krnl_PPCE6500_common_umask :
	rm -f D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libumask$(OPT).a


endif

ifndef _DONEBASE_LIB_CORE_KERNEL_krnl_PPCE6500_common_umask

_DONEBASE_LIB_CORE_KERNEL_krnl_PPCE6500_common_umask = TRUE

lib : D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/layerCORE_KERNEL_libumask.cdf

D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/layerCORE_KERNEL_libumask.cdf :  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libumask$(OPT).a
	$(file >$@, $(call __tmpl_layercdf,CORE_KERNEL,libumask.a,$(LIBOBJS_krnl_PPCE6500_common_umask)))

endif


D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libumask$(OPT).a : $(LIBOBJS_krnl_PPCE6500_common_umask)




 

################
# rules defined locally in Makefile
##



################

objs : $(LIBOBJS)
 
# this is the end of the file 
