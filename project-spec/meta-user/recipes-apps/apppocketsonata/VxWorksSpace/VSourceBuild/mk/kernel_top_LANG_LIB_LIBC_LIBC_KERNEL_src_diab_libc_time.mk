
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






LIBOBJS = $(LIBOBJS_c_wr)

# DEP_OBJS = (DEP_OBJS)

 
LIBOBJS_krnl_PPCE6500_common_c_wr_kernel_top_LANG_LIB_LIBC_LIBC_KERNEL_src_diab_libc_time =  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/objc_wr/locTime.o  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/objc_wr/asctime.o  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/objc_wr/clock.o  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/objc_wr/ctime.o  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/objc_wr/gmtime.o  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/objc_wr/localtime.o  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/objc_wr/mktime.o  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/objc_wr/strftime.o  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/objc_wr/time.o  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/objc_wr/difftime.o 

arcmdfile_krnl_PPCE6500_common_c_wr : $(LIBOBJS_krnl_PPCE6500_common_c_wr_kernel_top_LANG_LIB_LIBC_LIBC_KERNEL_src_diab_libc_time)

LIBOBJS_krnl_PPCE6500_common_c_wr_LANG_LIB_LIBC_LIBC_KERNEL += $(LIBOBJS_krnl_PPCE6500_common_c_wr_kernel_top_LANG_LIB_LIBC_LIBC_KERNEL_src_diab_libc_time)

LIBOBJS_krnl_PPCE6500_common_c_wr += $(LIBOBJS_krnl_PPCE6500_common_c_wr_kernel_top_LANG_LIB_LIBC_LIBC_KERNEL_src_diab_libc_time)

__OBJS_TO_CLEAN_LANG_LIB_LIBC_LIBC_KERNEL += $(LIBOBJS_krnl_PPCE6500_common_c_wr_kernel_top_LANG_LIB_LIBC_LIBC_KERNEL_src_diab_libc_time) $(LIBOBJS_krnl_PPCE6500_common_c_wr_kernel_top_LANG_LIB_LIBC_LIBC_KERNEL_src_diab_libc_time:.o=.d)

ifndef _DONEBASE_LIB_krnl_PPCE6500_common_c_wr

_DONEBASE_LIB_krnl_PPCE6500_common_c_wr = TRUE

# LIBBASES += c_wr

__LIBS_TO_BUILD += krnl_PPCE6500_common_c_wr

__LIBS_TO_BUILD_LANG_LIB_LIBC_LIBC_KERNEL += krnl_PPCE6500_common_c_wr

__BUILT_LIBS += krnl_PPCE6500_common_c_wr

__LIB_krnl_PPCE6500_common_c_wr = D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/libc_wr$(OPT).a


D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/objc_wr :
	$(MKDIR) $@


lib : D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/libc_wr$(OPT).a  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/libc_wr.cdf

# need to pass the lib.a file twice to D:/vxWorks7/compilers/diab-5.9.6.5/WIN32/bin/ddump -Ng to workaround ddump problem
D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/libc_wr.nm : D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/libc_wr$(OPT).a
	$(if $(wildcard $<),cd D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common && $(NM) libc_wr$(OPT).a libc_wr$(OPT).a > $@, $(info skipping $@ : non existant $<))

D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/libc_wr.cdf : D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/libc_wr.nm 
	$(if $(wildcard $<),$(LIB2CDF) -i $< -a libc_wr.a -o $@, $(info skipping $@ : non existant $<))

arcmdfiles : arcmdfile_krnl_PPCE6500_common_c_wr

arcmdfile_krnl_PPCE6500_common_c_wr :
	$(file >$@,$(call uniq,$(LIBOBJS_krnl_PPCE6500_common_c_wr)))
	@echo created $@

D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/libc_wr$(OPT).a : arcmdfile_krnl_PPCE6500_common_c_wr
	D:/vxWorks7/compilers/diab-5.9.6.5/WIN32/bin/dar crusv $@ @arcmdfile_krnl_PPCE6500_common_c_wr


clean _layer_clean_LANG_LIB_LIBC_LIBC_KERNEL : _clean_LIB_BASE_krnl_PPCE6500_common_c_wr

_clean_LIB_BASE_krnl_PPCE6500_common_c_wr :
	rm -f D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/libc_wr$(OPT).a


endif

ifndef _DONEBASE_LIB_LANG_LIB_LIBC_LIBC_KERNEL_krnl_PPCE6500_common_c_wr

_DONEBASE_LIB_LANG_LIB_LIBC_LIBC_KERNEL_krnl_PPCE6500_common_c_wr = TRUE

lib : D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/layerLANG_LIB_LIBC_LIBC_KERNEL_libc_wr.cdf

D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/layerLANG_LIB_LIBC_LIBC_KERNEL_libc_wr.cdf :  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/libc_wr$(OPT).a
	$(file >$@, $(call __tmpl_layercdf,LANG_LIB_LIBC_LIBC_KERNEL,libc_wr.a,$(LIBOBJS_krnl_PPCE6500_common_c_wr)))

endif


D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/libc_wr$(OPT).a : $(LIBOBJS_krnl_PPCE6500_common_c_wr)




 

################
# rules defined locally in Makefile
##



################

objs : $(LIBOBJS)
 
# this is the end of the file 
