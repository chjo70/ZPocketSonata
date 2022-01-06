
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






LIBOBJS = $(LIBOBJS_fsDevfs)

# DEP_OBJS = (DEP_OBJS)

 
LIBOBJS_krnl_PPCE6500_common_fsDevfs_kernel_top_FS_DEVFS_src_diab =  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/objfsDevfs/rawFsLib.o  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/objfsDevfs/rawFsLib.o 

arcmdfile_krnl_PPCE6500_common_fsDevfs : $(LIBOBJS_krnl_PPCE6500_common_fsDevfs_kernel_top_FS_DEVFS_src_diab)

LIBOBJS_krnl_PPCE6500_common_fsDevfs_FS_DEVFS += $(LIBOBJS_krnl_PPCE6500_common_fsDevfs_kernel_top_FS_DEVFS_src_diab)

LIBOBJS_krnl_PPCE6500_common_fsDevfs += $(LIBOBJS_krnl_PPCE6500_common_fsDevfs_kernel_top_FS_DEVFS_src_diab)

__OBJS_TO_CLEAN_FS_DEVFS += $(LIBOBJS_krnl_PPCE6500_common_fsDevfs_kernel_top_FS_DEVFS_src_diab) $(LIBOBJS_krnl_PPCE6500_common_fsDevfs_kernel_top_FS_DEVFS_src_diab:.o=.d)

ifndef _DONEBASE_LIB_krnl_PPCE6500_common_fsDevfs

_DONEBASE_LIB_krnl_PPCE6500_common_fsDevfs = TRUE

# LIBBASES += fsDevfs

__LIBS_TO_BUILD += krnl_PPCE6500_common_fsDevfs

__LIBS_TO_BUILD_FS_DEVFS += krnl_PPCE6500_common_fsDevfs

__BUILT_LIBS += krnl_PPCE6500_common_fsDevfs

__LIB_krnl_PPCE6500_common_fsDevfs = D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libfsDevfs$(OPT).a


D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/objfsDevfs :
	$(MKDIR) $@


lib : D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libfsDevfs$(OPT).a  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libfsDevfs.cdf

# need to pass the lib.a file twice to D:/vxWorks7/compilers/diab-5.9.6.5/WIN32/bin/ddump -Ng to workaround ddump problem
D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libfsDevfs.nm : D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libfsDevfs$(OPT).a
	$(if $(wildcard $<),cd D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common && $(NM) libfsDevfs$(OPT).a libfsDevfs$(OPT).a > $@, $(info skipping $@ : non existant $<))

D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libfsDevfs.cdf : D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libfsDevfs.nm 
	$(if $(wildcard $<),$(LIB2CDF) -i $< -a libfsDevfs.a -o $@, $(info skipping $@ : non existant $<))

arcmdfiles : arcmdfile_krnl_PPCE6500_common_fsDevfs

arcmdfile_krnl_PPCE6500_common_fsDevfs :
	$(file >$@,$(call uniq,$(LIBOBJS_krnl_PPCE6500_common_fsDevfs)))
	@echo created $@

D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libfsDevfs$(OPT).a : arcmdfile_krnl_PPCE6500_common_fsDevfs
	D:/vxWorks7/compilers/diab-5.9.6.5/WIN32/bin/dar crusv $@ @arcmdfile_krnl_PPCE6500_common_fsDevfs


clean _layer_clean_FS_DEVFS : _clean_LIB_BASE_krnl_PPCE6500_common_fsDevfs

_clean_LIB_BASE_krnl_PPCE6500_common_fsDevfs :
	rm -f D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libfsDevfs$(OPT).a


endif

ifndef _DONEBASE_LIB_FS_DEVFS_krnl_PPCE6500_common_fsDevfs

_DONEBASE_LIB_FS_DEVFS_krnl_PPCE6500_common_fsDevfs = TRUE

lib : D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/layerFS_DEVFS_libfsDevfs.cdf

D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/layerFS_DEVFS_libfsDevfs.cdf :  D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libfsDevfs$(OPT).a
	$(file >$@, $(call __tmpl_layercdf,FS_DEVFS,libfsDevfs.a,$(LIBOBJS_krnl_PPCE6500_common_fsDevfs)))

endif


D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64/krnl/PPCE6500/common/libfsDevfs$(OPT).a : $(LIBOBJS_krnl_PPCE6500_common_fsDevfs)




 

################
# rules defined locally in Makefile
##



################

objs : $(LIBOBJS)
 
# this is the end of the file 
