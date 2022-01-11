
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






LIBOBJS = $(LIBOBJS_pthread)

# DEP_OBJS = (DEP_OBJS)

 
LIBOBJS_krnl_PPCE6500_common_pthread_kernel_top_CORE_KERNEL_src_diab_posix_pthread =  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/objpthread/pthreadFuncBind.o  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/objpthread/pthreadLib.o  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/objpthread/_pthreadLib.o  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/objpthread/schedPxLib.o  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/objpthread/_schedPxLib.o  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/objpthread/schedPxScLib.o 

arcmdfile_krnl_PPCE6500_common_pthread : $(LIBOBJS_krnl_PPCE6500_common_pthread_kernel_top_CORE_KERNEL_src_diab_posix_pthread)

LIBOBJS_krnl_PPCE6500_common_pthread_CORE_KERNEL += $(LIBOBJS_krnl_PPCE6500_common_pthread_kernel_top_CORE_KERNEL_src_diab_posix_pthread)

LIBOBJS_krnl_PPCE6500_common_pthread += $(LIBOBJS_krnl_PPCE6500_common_pthread_kernel_top_CORE_KERNEL_src_diab_posix_pthread)

__OBJS_TO_CLEAN_CORE_KERNEL += $(LIBOBJS_krnl_PPCE6500_common_pthread_kernel_top_CORE_KERNEL_src_diab_posix_pthread) $(LIBOBJS_krnl_PPCE6500_common_pthread_kernel_top_CORE_KERNEL_src_diab_posix_pthread:.o=.d)

ifndef _DONEBASE_LIB_krnl_PPCE6500_common_pthread

_DONEBASE_LIB_krnl_PPCE6500_common_pthread = TRUE

# LIBBASES += pthread

__LIBS_TO_BUILD += krnl_PPCE6500_common_pthread

__LIBS_TO_BUILD_CORE_KERNEL += krnl_PPCE6500_common_pthread

__BUILT_LIBS += krnl_PPCE6500_common_pthread

__LIB_krnl_PPCE6500_common_pthread = D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libpthread$(OPT).a


D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/objpthread :
	$(MKDIR) $@


lib : D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libpthread$(OPT).a  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libpthread.cdf

# need to pass the lib.a file twice to D:/vxWorks7/compilers/diab-5.9.6.5/WIN32/bin/ddump -Ng to workaround ddump problem
D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libpthread.nm : D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libpthread$(OPT).a
	$(if $(wildcard $<),cd D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common && $(NM) libpthread$(OPT).a libpthread$(OPT).a > $@, $(info skipping $@ : non existant $<))

D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libpthread.cdf : D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libpthread.nm 
	$(if $(wildcard $<),$(LIB2CDF) -i $< -a libpthread.a -o $@, $(info skipping $@ : non existant $<))

arcmdfiles : arcmdfile_krnl_PPCE6500_common_pthread

arcmdfile_krnl_PPCE6500_common_pthread :
	$(file >$@,$(call uniq,$(LIBOBJS_krnl_PPCE6500_common_pthread)))
	@echo created $@

D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libpthread$(OPT).a : arcmdfile_krnl_PPCE6500_common_pthread
	D:/vxWorks7/compilers/diab-5.9.6.5/WIN32/bin/dar crusv $@ @arcmdfile_krnl_PPCE6500_common_pthread


clean _layer_clean_CORE_KERNEL : _clean_LIB_BASE_krnl_PPCE6500_common_pthread

_clean_LIB_BASE_krnl_PPCE6500_common_pthread :
	rm -f D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libpthread$(OPT).a


endif

ifndef _DONEBASE_LIB_CORE_KERNEL_krnl_PPCE6500_common_pthread

_DONEBASE_LIB_CORE_KERNEL_krnl_PPCE6500_common_pthread = TRUE

lib : D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/layerCORE_KERNEL_libpthread.cdf

D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/layerCORE_KERNEL_libpthread.cdf :  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libpthread$(OPT).a
	$(file >$@, $(call __tmpl_layercdf,CORE_KERNEL,libpthread.a,$(LIBOBJS_krnl_PPCE6500_common_pthread)))

endif


D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libpthread$(OPT).a : $(LIBOBJS_krnl_PPCE6500_common_pthread)




 

################
# rules defined locally in Makefile
##



################

objs : $(LIBOBJS)
 
# this is the end of the file 