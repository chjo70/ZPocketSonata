
#
# This file is automatically generated by mk/krnl/defs.fastlibgen.mk .
#
# build configuration :
#	VSB : D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild
#	CPU : PPCE6500
#	TOOL : diab
#	FP : hard
# 	ENDIAN : big
#	LIB_DIR_TAG = 
#	LIBDIRBASE = krnl/PPCE6500/common
#	LIBDIRBASE = krnl/$(CPU)$(CPU_OPTION_SUFFIX)/$(TOOL_COMMON_DIR)$(LIB_DIR_TAG)$(MINOR_OPTION_SUFFIX)






LIBOBJS = $(LIBOBJS_my_qspi_flash_layer)

# DEP_OBJS = (DEP_OBJS)

 
LIBOBJS_krnl_PPCE6500_common_my_qspi_flash_layer_kernel_top_MY_QSPI_FLASH_LAYER_src_diab =  D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/objmy_qspi_flash_layer/vxbMySpiFlash.o  D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/objmy_qspi_flash_layer/vxbMySpiFlash.o 

arcmdfile_krnl_PPCE6500_common_my_qspi_flash_layer : $(LIBOBJS_krnl_PPCE6500_common_my_qspi_flash_layer_kernel_top_MY_QSPI_FLASH_LAYER_src_diab)

LIBOBJS_krnl_PPCE6500_common_my_qspi_flash_layer_MY_QSPI_FLASH_LAYER += $(LIBOBJS_krnl_PPCE6500_common_my_qspi_flash_layer_kernel_top_MY_QSPI_FLASH_LAYER_src_diab)

LIBOBJS_krnl_PPCE6500_common_my_qspi_flash_layer += $(LIBOBJS_krnl_PPCE6500_common_my_qspi_flash_layer_kernel_top_MY_QSPI_FLASH_LAYER_src_diab)

__OBJS_TO_CLEAN_MY_QSPI_FLASH_LAYER += $(LIBOBJS_krnl_PPCE6500_common_my_qspi_flash_layer_kernel_top_MY_QSPI_FLASH_LAYER_src_diab) $(LIBOBJS_krnl_PPCE6500_common_my_qspi_flash_layer_kernel_top_MY_QSPI_FLASH_LAYER_src_diab:.o=.d)

ifndef _DONEBASE_LIB_krnl_PPCE6500_common_my_qspi_flash_layer

_DONEBASE_LIB_krnl_PPCE6500_common_my_qspi_flash_layer = TRUE

# LIBBASES += my_qspi_flash_layer

__LIBS_TO_BUILD += krnl_PPCE6500_common_my_qspi_flash_layer

__LIBS_TO_BUILD_MY_QSPI_FLASH_LAYER += krnl_PPCE6500_common_my_qspi_flash_layer

__BUILT_LIBS += krnl_PPCE6500_common_my_qspi_flash_layer

__LIB_krnl_PPCE6500_common_my_qspi_flash_layer = D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/libmy_qspi_flash_layer$(OPT).a


D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/objmy_qspi_flash_layer :
	$(MKDIR) $@


lib : D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/libmy_qspi_flash_layer$(OPT).a  D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/libmy_qspi_flash_layer.cdf

# need to pass the lib.a file twice to D:/vxWorks7/compilers/diab-5.9.6.5/WIN32/bin/ddump -Ng to workaround ddump problem
D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/libmy_qspi_flash_layer.nm : D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/libmy_qspi_flash_layer$(OPT).a
	$(if $(wildcard $<),cd D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common && $(NM) libmy_qspi_flash_layer$(OPT).a libmy_qspi_flash_layer$(OPT).a > $@, $(info skipping $@ : non existant $<))

D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/libmy_qspi_flash_layer.cdf : D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/libmy_qspi_flash_layer.nm 
	$(if $(wildcard $<),$(LIB2CDF) -i $< -a libmy_qspi_flash_layer.a -o $@, $(info skipping $@ : non existant $<))

arcmdfiles : arcmdfile_krnl_PPCE6500_common_my_qspi_flash_layer

arcmdfile_krnl_PPCE6500_common_my_qspi_flash_layer :
	$(file >$@,$(call uniq,$(LIBOBJS_krnl_PPCE6500_common_my_qspi_flash_layer)))
	@echo created $@

D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/libmy_qspi_flash_layer$(OPT).a : arcmdfile_krnl_PPCE6500_common_my_qspi_flash_layer
	D:/vxWorks7/compilers/diab-5.9.6.5/WIN32/bin/dar crusv $@ @arcmdfile_krnl_PPCE6500_common_my_qspi_flash_layer


clean _layer_clean_MY_QSPI_FLASH_LAYER : _clean_LIB_BASE_krnl_PPCE6500_common_my_qspi_flash_layer

_clean_LIB_BASE_krnl_PPCE6500_common_my_qspi_flash_layer :
	rm -f D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/libmy_qspi_flash_layer$(OPT).a


endif

ifndef _DONEBASE_LIB_MY_QSPI_FLASH_LAYER_krnl_PPCE6500_common_my_qspi_flash_layer

_DONEBASE_LIB_MY_QSPI_FLASH_LAYER_krnl_PPCE6500_common_my_qspi_flash_layer = TRUE

lib : D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/layerMY_QSPI_FLASH_LAYER_libmy_qspi_flash_layer.cdf

D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/layerMY_QSPI_FLASH_LAYER_libmy_qspi_flash_layer.cdf :  D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/libmy_qspi_flash_layer$(OPT).a
	$(file >$@, $(call __tmpl_layercdf,MY_QSPI_FLASH_LAYER,libmy_qspi_flash_layer.a,$(LIBOBJS_krnl_PPCE6500_common_my_qspi_flash_layer)))

endif


D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild/krnl/PPCE6500/common/libmy_qspi_flash_layer$(OPT).a : $(LIBOBJS_krnl_PPCE6500_common_my_qspi_flash_layer)




 

################
# rules defined locally in Makefile
##



################

objs : $(LIBOBJS)
 
# this is the end of the file 
