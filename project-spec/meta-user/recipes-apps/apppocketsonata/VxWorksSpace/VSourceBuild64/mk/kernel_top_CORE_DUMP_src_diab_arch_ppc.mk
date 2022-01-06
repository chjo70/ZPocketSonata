
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






LIBOBJS = $(LIBOBJS_coredump)

# DEP_OBJS = (DEP_OBJS)

 
LIBOBJS_krnl_PPCE6500_common_coredump_kernel_top_CORE_DUMP_src_diab_arch_ppc =  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/objcoredump/coreDumpPpcLib.o  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/objcoredump/coreDumpPpcLib.o 

arcmdfile_krnl_PPCE6500_common_coredump : $(LIBOBJS_krnl_PPCE6500_common_coredump_kernel_top_CORE_DUMP_src_diab_arch_ppc)

LIBOBJS_krnl_PPCE6500_common_coredump_CORE_DUMP += $(LIBOBJS_krnl_PPCE6500_common_coredump_kernel_top_CORE_DUMP_src_diab_arch_ppc)

LIBOBJS_krnl_PPCE6500_common_coredump += $(LIBOBJS_krnl_PPCE6500_common_coredump_kernel_top_CORE_DUMP_src_diab_arch_ppc)

__OBJS_TO_CLEAN_CORE_DUMP += $(LIBOBJS_krnl_PPCE6500_common_coredump_kernel_top_CORE_DUMP_src_diab_arch_ppc) $(LIBOBJS_krnl_PPCE6500_common_coredump_kernel_top_CORE_DUMP_src_diab_arch_ppc:.o=.d)

ifndef _DONEBASE_LIB_krnl_PPCE6500_common_coredump

_DONEBASE_LIB_krnl_PPCE6500_common_coredump = TRUE

# LIBBASES += coredump

__LIBS_TO_BUILD += krnl_PPCE6500_common_coredump

__LIBS_TO_BUILD_CORE_DUMP += krnl_PPCE6500_common_coredump

__BUILT_LIBS += krnl_PPCE6500_common_coredump

__LIB_krnl_PPCE6500_common_coredump = D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libcoredump$(OPT).a


D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/objcoredump :
	$(MKDIR) $@


lib : D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libcoredump$(OPT).a  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libcoredump.cdf

# need to pass the lib.a file twice to D:/vxWorks7/compilers/diab-5.9.6.5/WIN32/bin/ddump -Ng to workaround ddump problem
D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libcoredump.nm : D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libcoredump$(OPT).a
	$(if $(wildcard $<),cd D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common && $(NM) libcoredump$(OPT).a libcoredump$(OPT).a > $@, $(info skipping $@ : non existant $<))

D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libcoredump.cdf : D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libcoredump.nm 
	$(if $(wildcard $<),$(LIB2CDF) -i $< -a libcoredump.a -o $@, $(info skipping $@ : non existant $<))

arcmdfiles : arcmdfile_krnl_PPCE6500_common_coredump

arcmdfile_krnl_PPCE6500_common_coredump :
	$(file >$@,$(call uniq,$(LIBOBJS_krnl_PPCE6500_common_coredump)))
	@echo created $@

D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libcoredump$(OPT).a : arcmdfile_krnl_PPCE6500_common_coredump
	D:/vxWorks7/compilers/diab-5.9.6.5/WIN32/bin/dar crusv $@ @arcmdfile_krnl_PPCE6500_common_coredump


clean _layer_clean_CORE_DUMP : _clean_LIB_BASE_krnl_PPCE6500_common_coredump

_clean_LIB_BASE_krnl_PPCE6500_common_coredump :
	rm -f D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libcoredump$(OPT).a


endif

ifndef _DONEBASE_LIB_CORE_DUMP_krnl_PPCE6500_common_coredump

_DONEBASE_LIB_CORE_DUMP_krnl_PPCE6500_common_coredump = TRUE

lib : D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/layerCORE_DUMP_libcoredump.cdf

D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/layerCORE_DUMP_libcoredump.cdf :  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libcoredump$(OPT).a
	$(file >$@, $(call __tmpl_layercdf,CORE_DUMP,libcoredump.a,$(LIBOBJS_krnl_PPCE6500_common_coredump)))

endif


D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libcoredump$(OPT).a : $(LIBOBJS_krnl_PPCE6500_common_coredump)




 

################
# rules defined locally in Makefile
##



################

objs : $(LIBOBJS)
 
# this is the end of the file 
