
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






LIBOBJS = $(LIBOBJS_arch)

# DEP_OBJS = (DEP_OBJS)

 
LIBOBJS_krnl_PPCE6500_common_arch__top_PPC_PPCMATH_src_motorolaLib =  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/objarch/atan.o  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/objarch/pow.o  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/objarch/sqrt.o  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/objarch/trig.o  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/objarch/atan.o  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/objarch/pow.o  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/objarch/sqrt.o  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/objarch/trig.o 

arcmdfile_krnl_PPCE6500_common_arch : $(LIBOBJS_krnl_PPCE6500_common_arch__top_PPC_PPCMATH_src_motorolaLib)

LIBOBJS_krnl_PPCE6500_common_arch_PPC_PPCMATH += $(LIBOBJS_krnl_PPCE6500_common_arch__top_PPC_PPCMATH_src_motorolaLib)

LIBOBJS_krnl_PPCE6500_common_arch += $(LIBOBJS_krnl_PPCE6500_common_arch__top_PPC_PPCMATH_src_motorolaLib)

__OBJS_TO_CLEAN_PPC_PPCMATH += $(LIBOBJS_krnl_PPCE6500_common_arch__top_PPC_PPCMATH_src_motorolaLib) $(LIBOBJS_krnl_PPCE6500_common_arch__top_PPC_PPCMATH_src_motorolaLib:.o=.d)

ifndef _DONEBASE_LIB_krnl_PPCE6500_common_arch

_DONEBASE_LIB_krnl_PPCE6500_common_arch = TRUE

# LIBBASES += arch

__LIBS_TO_BUILD += krnl_PPCE6500_common_arch

__LIBS_TO_BUILD_PPC_PPCMATH += krnl_PPCE6500_common_arch

__BUILT_LIBS += krnl_PPCE6500_common_arch

__LIB_krnl_PPCE6500_common_arch = D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/libarch$(OPT).a


D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/objarch :
	$(MKDIR) $@


lib : D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/libarch$(OPT).a  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/libarch.cdf

# need to pass the lib.a file twice to D:/vxWorks7/compilers/diab-5.9.6.5/WIN32/bin/ddump -Ng to workaround ddump problem
D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/libarch.nm : D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/libarch$(OPT).a
	$(if $(wildcard $<),cd D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common && $(NM) libarch$(OPT).a libarch$(OPT).a > $@, $(info skipping $@ : non existant $<))

D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/libarch.cdf : D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/libarch.nm 
	$(if $(wildcard $<),$(LIB2CDF) -i $< -a libarch.a -o $@, $(info skipping $@ : non existant $<))

arcmdfiles : arcmdfile_krnl_PPCE6500_common_arch

arcmdfile_krnl_PPCE6500_common_arch :
	$(file >$@,$(call uniq,$(LIBOBJS_krnl_PPCE6500_common_arch)))
	@echo created $@

D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/libarch$(OPT).a : arcmdfile_krnl_PPCE6500_common_arch
	D:/vxWorks7/compilers/diab-5.9.6.5/WIN32/bin/dar crusv $@ @arcmdfile_krnl_PPCE6500_common_arch


clean _layer_clean_PPC_PPCMATH : _clean_LIB_BASE_krnl_PPCE6500_common_arch

_clean_LIB_BASE_krnl_PPCE6500_common_arch :
	rm -f D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/libarch$(OPT).a


endif

ifndef _DONEBASE_LIB_PPC_PPCMATH_krnl_PPCE6500_common_arch

_DONEBASE_LIB_PPC_PPCMATH_krnl_PPCE6500_common_arch = TRUE

lib : D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/layerPPC_PPCMATH_libarch.cdf

D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/layerPPC_PPCMATH_libarch.cdf :  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/libarch$(OPT).a
	$(file >$@, $(call __tmpl_layercdf,PPC_PPCMATH,libarch.a,$(LIBOBJS_krnl_PPCE6500_common_arch)))

endif


D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/libarch$(OPT).a : $(LIBOBJS_krnl_PPCE6500_common_arch)




 

################
# rules defined locally in Makefile
##



################

objs : $(LIBOBJS)
 
# this is the end of the file 
