
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






LIBOBJS = $(LIBOBJS_coreio)

# DEP_OBJS = (DEP_OBJS)

 
LIBOBJS_krnl_PPCE6500_common_coreio_kernel_top_CORE_IO_src_diab_aio =  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/objcoreio/aioPxLib.o  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/objcoreio/aioPxShow.o  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/objcoreio/aioSysDrv.o  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/objcoreio/ioQLib.o  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/objcoreio/aioPxLib.o  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/objcoreio/aioPxShow.o  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/objcoreio/aioSysDrv.o  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/objcoreio/ioQLib.o 

arcmdfile_krnl_PPCE6500_common_coreio : $(LIBOBJS_krnl_PPCE6500_common_coreio_kernel_top_CORE_IO_src_diab_aio)

LIBOBJS_krnl_PPCE6500_common_coreio_CORE_IO += $(LIBOBJS_krnl_PPCE6500_common_coreio_kernel_top_CORE_IO_src_diab_aio)

LIBOBJS_krnl_PPCE6500_common_coreio += $(LIBOBJS_krnl_PPCE6500_common_coreio_kernel_top_CORE_IO_src_diab_aio)

__OBJS_TO_CLEAN_CORE_IO += $(LIBOBJS_krnl_PPCE6500_common_coreio_kernel_top_CORE_IO_src_diab_aio) $(LIBOBJS_krnl_PPCE6500_common_coreio_kernel_top_CORE_IO_src_diab_aio:.o=.d)

ifndef _DONEBASE_LIB_krnl_PPCE6500_common_coreio

_DONEBASE_LIB_krnl_PPCE6500_common_coreio = TRUE

# LIBBASES += coreio

__LIBS_TO_BUILD += krnl_PPCE6500_common_coreio

__LIBS_TO_BUILD_CORE_IO += krnl_PPCE6500_common_coreio

__BUILT_LIBS += krnl_PPCE6500_common_coreio

__LIB_krnl_PPCE6500_common_coreio = D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/libcoreio$(OPT).a


D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/objcoreio :
	$(MKDIR) $@


lib : D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/libcoreio$(OPT).a  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/libcoreio.cdf

# need to pass the lib.a file twice to D:/vxWorks7/compilers/diab-5.9.6.5/WIN32/bin/ddump -Ng to workaround ddump problem
D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/libcoreio.nm : D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/libcoreio$(OPT).a
	$(if $(wildcard $<),cd D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common && $(NM) libcoreio$(OPT).a libcoreio$(OPT).a > $@, $(info skipping $@ : non existant $<))

D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/libcoreio.cdf : D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/libcoreio.nm 
	$(if $(wildcard $<),$(LIB2CDF) -i $< -a libcoreio.a -o $@, $(info skipping $@ : non existant $<))

arcmdfiles : arcmdfile_krnl_PPCE6500_common_coreio

arcmdfile_krnl_PPCE6500_common_coreio :
	$(file >$@,$(call uniq,$(LIBOBJS_krnl_PPCE6500_common_coreio)))
	@echo created $@

D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/libcoreio$(OPT).a : arcmdfile_krnl_PPCE6500_common_coreio
	D:/vxWorks7/compilers/diab-5.9.6.5/WIN32/bin/dar crusv $@ @arcmdfile_krnl_PPCE6500_common_coreio


clean _layer_clean_CORE_IO : _clean_LIB_BASE_krnl_PPCE6500_common_coreio

_clean_LIB_BASE_krnl_PPCE6500_common_coreio :
	rm -f D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/libcoreio$(OPT).a


endif

ifndef _DONEBASE_LIB_CORE_IO_krnl_PPCE6500_common_coreio

_DONEBASE_LIB_CORE_IO_krnl_PPCE6500_common_coreio = TRUE

lib : D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/layerCORE_IO_libcoreio.cdf

D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/layerCORE_IO_libcoreio.cdf :  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/libcoreio$(OPT).a
	$(file >$@, $(call __tmpl_layercdf,CORE_IO,libcoreio.a,$(LIBOBJS_krnl_PPCE6500_common_coreio)))

endif


D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/libcoreio$(OPT).a : $(LIBOBJS_krnl_PPCE6500_common_coreio)




 

################
# rules defined locally in Makefile
##



################

objs : $(LIBOBJS)
 
# this is the end of the file 
